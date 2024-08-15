#include "CallbellHandler.h"

CallbellHandler::CallbellHandler(QObject *parent)
    : QObject(parent)
{
    last_bell_id = "";
    m_serialPort = new QSerialPort();

    connect(m_serialPort, SIGNAL(readyRead()), this, SLOT(read_data()));
    connect(m_serialPort, SIGNAL(errorOccurred(QSerialPort::SerialPortError)), this, SLOT(handle_error(QSerialPort::SerialPortError)));

    m_serialPort->setPortName("ttyCB0");
    m_serialPort->setBaudRate(QSerialPort::Baud115200);
    m_serialPort->setDataBits(QSerialPort::Data8);
    m_serialPort->setParity(QSerialPort::NoParity);
    m_serialPort->setStopBits(QSerialPort::OneStop);
    m_serialPort->setFlowControl(QSerialPort::SoftwareControl);

    if(m_serialPort->open(QIODevice::ReadWrite))
    {
        plog->write("[CALLBELL] Port ttyCB0 Open Success");
    }
    else
    {
        m_serialPort->setPortName("ttyUSB1");
        if(m_serialPort->open(QIODevice::ReadWrite))
        {
            plog->write("[CALLBELL] Port ttyUSB1 Open Success");
        }
    }

    reconnection_timer = new QTimer();
    connect(reconnection_timer, SIGNAL(timeout()), this, SLOT(onTimer()));
    reconnection_timer->start(200);

    read_data();
}

CallbellHandler::~CallbellHandler()
{
    if(m_serialPort->isOpen())
    {
        disconnect(m_serialPort, SIGNAL(readyRead()), this, SLOT(read_data()));
        disconnect(m_serialPort, SIGNAL(errorOccurred(QSerialPort::SerialPortError)), this, SLOT(handle_error(QSerialPort::SerialPortError)));
        m_serialPort->close();

        delete m_serialPort;
        m_serialPort = nullptr;
    }
}

void CallbellHandler::reconnection_loop()
{
    static int time_cnt = 0;
    time_cnt++;
    if(time_cnt > 10 && !m_serialPort->isOpen())
    {
        if(m_serialPort->open(QIODevice::ReadWrite))
        {
            plog->write("[CALLBELL] SERIAL " + m_serialPort->portName() + " Re-connection SUCCESS!");
        }
        time_cnt = 0;
    }
}

void CallbellHandler::read_data()
{
    QByteArray data = m_serialPort->readAll();
    datas += data;

    //QString str;
    //for(int i=0; i<data.size(); i++)
    //{
    //    str += QString().asprintf("0x%02X ", uchar(data[i]));
    //}

    QString data_str = "[CALLBELL] readData: " + QString(data) + " -> " + QString(datas) + " size:" + QString::number(data.size()) + "," + QString::number(datas.size());
    plog->write(data_str);

    /*
    * Syscall protocol v0.4
    *
    * [sender -> receiver]
    * Header
    * [0]version (0x03)
    * [1]flags (0x01)
    * [2,3]length (0x0014)
    * Basic data
    * [4,5]option (0xA505, C514)
    * -> 0xA501(connect) 0xA505(bell push) | 0xA511(device check) 0xA514(sender call)
    * [6,7]model number (0x00CC)
    * [8,9]firmware version (0xA102)
    * Bell data
    * [10,11,12,13] bell unique ID (0x3F4E070F)
    * [14] button info (0x0F)
    * [15] bell info (0x01, 0x03(3bell))
    * [16,17,18] reserved2 (0x000000)
    * [19] check sum
    *
    *
    * [receiver -> sender]
    * Header
    * [0]version (0x03)
    * [1]flags (0x01)
    * [2,3]length (0x0008)
    * Basic data
    * [4,5]option (0xA501, A514, C501, C505, C511)
    * -> 0xC501(connect response) 0xC505(bell response) | 0xC511(device check) 0xC514(sender call)
    * [6]result (0x00=success)
    * [7]check sum
    *
    */

    while (datas.length() > 5)
    {
        //plog->write("[CALLBELL] readData while : " + datas + " -> " + QString::number(datas.length()) + "," + QString::number(datas.size()));
        if((uchar)datas[0] == (uchar)0x03 && (uchar)datas[1] == (uchar)0x01)
        {
            ushort size = (ushort)((uchar)datas[3] | ((uchar)datas[2] << 8));
            if(size <= (ushort)0 || size > (ushort)20)
            {
                datas.remove(0, 1);
            }
            else
            {
                if(size <= datas.length())
                {
                    uint option = (ushort)(uchar(datas[5]) | (uchar(datas[4]) << 8));
                    if (option == BELL_CONNECT && size == 12)
                    {
                        // connection check
                        uchar checksum = uchar(datas[11]);
                        uchar temp_cs = calc_checksum(datas, size);
                        if (checksum == temp_cs)
                        {
                            send_connection_check_message();
                        }
                        datas.remove(0, size);
                    }
                    else if (option == BELL_PUSH && size == 20)
                    {
                        // data check
                        uint bell_id = (unsigned int)(uchar(datas.at(13)) | (uchar(datas.at(12)) << 8) | (uchar(datas.at(11)) << 16) | (uchar(datas.at(10)) << 24));
                        QString bell_str = QString().asprintf("%08X", bell_id);

                        uchar checksum = uchar(datas.at(19));
                        uchar temp_cs = calc_checksum(datas, size);
                        if (checksum == temp_cs)
                        {
                            send_data_check_message();

                            mtx.lock();
                            last_bell_id = bell_str;
                            mtx.unlock();

                            emit new_call();

                            plog->write("[CALLBELL] ReadData (NewCall) : " + last_bell_id);
                        }

                        datas.remove(0, size);
                    }
                    else if (option == SENDER_CALL)
                    {
                        datas.remove(0, size);
                    }
                    else
                    {
                        datas.remove(0, size); // 처리되지 않은 옵션의 경우 데이터 제거
                    }
                }
                else
                {
                    break;
                }
            }
        }
        else
        {
            datas.remove(0, 1);
        }
    }

    plog->write("[CALLBELL] readData : done");
}

void CallbellHandler::handle_error(QSerialPort::SerialPortError error)
{
    // https://doc.qt.io/qt-5/qserialport.html#SerialPortError-enum
    if(error == QSerialPort::DeviceNotFoundError)
    {
        plog->write("[CALLBELL] SerialPort Error: DeviceNotFoundError");
    }
    else if(error == QSerialPort::PermissionError)
    {
        plog->write("[CALLBELL] SerialPort Error : PermissionError");
    }
    else if(error == QSerialPort::OpenError)
    {
        plog->write("[CALLBELL] SerialPort Error : OpenError");
    }
    else if(error == QSerialPort::NotOpenError)
    {
        plog->write("[CALLBELL] SerialPort Error : NotOpenError");
    }
    else if(error == QSerialPort::ParityError)
    {
        plog->write("[CALLBELL] SerialPort Error : ParityError");
    }
    else if(error == QSerialPort::FramingError)
    {
        plog->write("[CALLBELL] SerialPort Error : FramingError");
    }
    else if(error == QSerialPort::BreakConditionError)
    {
        plog->write("[CALLBELL] SerialPort Error : BreakConditionError");
    }
    else if(error == QSerialPort::WriteError)
    {
        plog->write("[CALLBELL] SerialPort Error : WriteError");
    }
    else if(error == QSerialPort::ReadError)
    {
        plog->write("[CALLBELL] SerialPort Error : ReadError");
    }
    else if(error == QSerialPort::ResourceError)
    {
        plog->write("[CALLBELL] SerialPort Error : ResourceError");
    }
    else if(error == QSerialPort::UnsupportedOperationError)
    {
        plog->write("[CALLBELL] SerialPort Error : UnsupportedOperationError");
    }
    else if(error == QSerialPort::TimeoutError)
    {
        plog->write("[CALLBELL] SerialPort Error : TimeoutError");
    }
    else if(error == QSerialPort::UnknownError)
    {
        plog->write("[CALLBELL] SerialPort Error : UnknownError");
    }

    if(m_serialPort->isOpen() && error != QSerialPort::NoError)
    {
        m_serialPort->close();
        delete m_serialPort;
        m_serialPort = nullptr;
    }
}

void CallbellHandler::send_call(QString id)
{
    QByteArray sendData;
    sendData.push_back(uchar(0x03));
    sendData.push_back(uchar(0x01));
    sendData.push_back(uchar(0x00));
    sendData.push_back(uchar(0x14));
    sendData.push_back(uchar(0xC5));
    sendData.push_back(uchar(0x14));
    sendData.push_back(uchar(0x00));
    sendData.push_back(uchar(0xCC));
    sendData.push_back(uchar(0xA1));
    sendData.push_back(uchar(0x02));

    QByteArray id_array = QByteArray::fromHex(id.toUtf8());
    if(id_array.size() == 4)
    {
        sendData.push_back(uchar(id_array[0]));
        sendData.push_back(uchar(id_array[1]));
        sendData.push_back(uchar(id_array[2]));
        sendData.push_back(uchar(id_array[3]));

        sendData.push_back(uchar(0x0F));
        sendData.push_back(uchar(0x01));
        sendData.push_back(uchar(0x00));
        sendData.push_back(uchar(0x00));
        sendData.push_back(uchar(0x00));
        sendData.push_back(calc_checksum(sendData, 20));

        QString strSend;
        for(int i=0; i<sendData.size(); i++)
        {
            strSend += QString().asprintf("0x%02X ", uchar(sendData[i]));
        }
        plog->write("[CALLBELL] sendCall : ("+id+") -> " + strSend);
        m_serialPort->write(sendData);
    }
}


void CallbellHandler::send_connection_check_message()
{
    QByteArray sendData;
    sendData.push_back(uchar(0x03));
    sendData.push_back(uchar(0x01));
    sendData.push_back(uchar(0x00));
    sendData.push_back(uchar(0x08));
    sendData.push_back(uchar(0xC5));
    sendData.push_back(uchar(0x01));
    sendData.push_back(uchar(0x00));
    sendData.push_back(calc_checksum(sendData, 8));

    m_serialPort->write(sendData);
}

void CallbellHandler::send_data_check_message()
{
    QByteArray sendData;
    sendData.push_back(uchar(0x03));
    sendData.push_back(uchar(0x01));
    sendData.push_back(uchar(0x00));
    sendData.push_back(uchar(0x08));
    sendData.push_back(uchar(0xC5));
    sendData.push_back(uchar(0x05));
    sendData.push_back(uchar(0x00));
    sendData.push_back(calc_checksum(sendData, 8));

    m_serialPort->write(sendData);
}

uchar CallbellHandler::calc_checksum(QByteArray ba, int size)
{
    uint temp_sum = 0;
    for(int i=0; i<size-1; i++)
    {
        temp_sum += uchar(ba[i]);
    }
    uchar temp_cs = (temp_sum&0x000000FF);
    temp_cs = (~temp_cs) + 1;
    return temp_cs;
}

QString CallbellHandler::get_bell_ID()
{
    mtx.lock();
    QString _last_bell_id = last_bell_id;
    mtx.unlock();

    return _last_bell_id;
}

bool CallbellHandler::is_open_port()
{
    bool is_open = false;
    if(m_serialPort->isOpen())
    {
        is_open = true;
    }

    return is_open;
}
