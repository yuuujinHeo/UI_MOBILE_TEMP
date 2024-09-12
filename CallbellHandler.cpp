#include "CallbellHandler.h"

CallbellHandler::CallbellHandler()
{
    connection_count = 0;
    last_bell_id = "";
    m_serialPort = new QSerialPort();

    //BJ&JY
    connect(m_serialPort, SIGNAL(readyRead()), this, SLOT(readData()));
    connect(m_serialPort, SIGNAL(errorOccurred(QSerialPort::SerialPortError)), this, SLOT(handleError(QSerialPort::SerialPortError)));

    m_serialPort->setPortName("ttyCB0");
    m_serialPort->setBaudRate(QSerialPort::Baud115200);
    m_serialPort->setDataBits(QSerialPort::Data8);
    m_serialPort->setParity(QSerialPort::NoParity);
    m_serialPort->setStopBits(QSerialPort::OneStop);
    m_serialPort->setFlowControl(QSerialPort::SoftwareControl);

    if(m_serialPort->open(QIODevice::ReadWrite)){
        //plog->write("[CALLBELL] Port ttyCB0 Open Success");


    }else{
        m_serialPort->setPortName("ttyUSB1");
        if(m_serialPort->open(QIODevice::ReadWrite)){
            //plog->write("[CALLBELL] Port ttyUSB1 Open Success");
        }
        //plog->write("[CALLBELL] Port ttyCB0 Open Faile");
        //return;
    }

    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimer()));
    timer->start(200);

    readData();
}

void CallbellHandler::onTimer(){
    static int time_cnt = 0;
    time_cnt++;
    if(time_cnt > 10 && !m_serialPort->isOpen()){
        if(m_serialPort->open(QIODevice::ReadWrite)){
            //plog->write("[CALLBELL] SERIAL "+m_serialPort->portName() + " OPEN SUCCESS!");
        }
        time_cnt = 0;
    }

    // sendCallTest();
}

void CallbellHandler::sendCallTest(){
    // if(test.size() == 0) return;

    // qDebug() << "TEST : " << test;
    // m_serialPort->write(test);
}

void CallbellHandler::readData(){
    QByteArray data = m_serialPort->readAll();
    datas += data;

    QString str;
    for(int i=0; i<data.size(); i++){
        str += QString().asprintf("0x%02X ", uchar(data[i]));
    }

    //plog->write("[CALLBELL] readData: "+data+ " -> "+QString::number(datas.size()));
   /*
    * Syscall protocol v0.4
    *
    *[sender -> receiver]
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
    *[receiver -> sender]
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

    //plog->write("[CALLBELL] readData: " + QString::number(datas.length()) + "," + QString::number(datas.size()));
    //plog->write("[CALLBELL] readData: " + data + " -> " + datas);

    while (datas.length() > 5) {
        //plog->write("[CALLBELL] readData while : " + datas + " -> " + QString::number(datas.length()) + "," + QString::number(datas.size()));
        if (uchar(datas[0]) == 0x03 && uchar(datas[1]) == 0x01) {
            int size = (short)(uchar(datas[3]) | (uchar(datas[2]) << 8));
            if (size <= 0 || size > 24) {
                datas.remove(0, 1);
            } else {
                if (size <= datas.length()) {
                    uint option = (ushort)(uchar(datas[5]) | (uchar(datas[4]) << 8));

                    if (option == 0xA501 && size == 12) {
                        // connection check
                        uchar checksum = uchar(datas[11]);
                        uchar temp_cs = CalcCheckSum(datas, size);
                        if (checksum == temp_cs) {
                            SendConnectionCheckMessage();
                        }
                        datas.remove(0, size);
                    } else if (option == 0xA505 && size == 20) {
                        // data check
                        uint model_num = (ushort)(uchar(datas[7]) | (uchar(datas[6]) << 8));
                        uint firmware_ver = (ushort)(uchar(datas[9]) | (uchar(datas[8]) << 8));
                        uint bell_id = (unsigned int)(uchar(datas[13]) | (uchar(datas[12]) << 8) | (uchar(datas[11]) << 16) | (uchar(datas[10]) << 24));
                        uint button_info = uchar(datas[14]);
                        uint bell_info = uchar(datas[15]);

                        QString bell_str = QString().asprintf("%08X", bell_id);
                        QString button_info_str = QString().asprintf("%02X", button_info);
                        QString bell_info_str = QString().asprintf("%02X", bell_info);

                        uchar checksum = uchar(datas[19]);
                        uchar temp_cs = CalcCheckSum(datas, size);
                        if (checksum == temp_cs) {
                            SendDataCheckMessage();
                            last_bell_id = bell_str;
                            //plog->write("[CALLBELL] ReadData (NewCall) : " + last_bell_id);
                            emit new_call();
                        }
                        datas.remove(0, size);
                    } else if (option == 0xA514) {
                        datas.remove(0, size);
                    } else {
                        datas.remove(0, size); // 처리되지 않은 옵션의 경우 데이터 제거
                    }
                } else {
                    break;
                }
            }
        } else {
            datas.remove(0, 1);
        }
    }

    //plog->write("[CALLBELL] readData : done");

}

void CallbellHandler::handleError(QSerialPort::SerialPortError error){
    if(error == QSerialPort::ResourceError){
        //plog->write("[CALLBELL] SerialPort Error : "+QString::number(error));
        if(m_serialPort->isOpen())
            m_serialPort->close();
    }
}

void CallbellHandler::sendCall(QString id){
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
    if(id_array.size() == 4){
        sendData.push_back(uchar(id_array[0]));
        sendData.push_back(uchar(id_array[1]));
        sendData.push_back(uchar(id_array[2]));
        sendData.push_back(uchar(id_array[3]));

        sendData.push_back(uchar(0x0F));
        sendData.push_back(uchar(0x01));
        sendData.push_back(uchar(0x00));
        sendData.push_back(uchar(0x00));
        sendData.push_back(uchar(0x00));
        sendData.push_back(CalcCheckSum(sendData, 20));

        QString strSend;
        for(int i=0; i<sendData.size(); i++){
            strSend += QString().asprintf("0x%02X ", uchar(sendData[i]));
        }
        //plog->write("[CALLBELL] sendCall : ("+id+") -> "+strSend);
        m_serialPort->write(sendData);
    }
}


void CallbellHandler::SendConnectionCheckMessage(){
    QByteArray sendData;
    sendData.push_back(uchar(0x03));
    sendData.push_back(uchar(0x01));
    sendData.push_back(uchar(0x00));
    sendData.push_back(uchar(0x08));
    sendData.push_back(uchar(0xC5));
    sendData.push_back(uchar(0x01));
    sendData.push_back(uchar(0x00));
    sendData.push_back(CalcCheckSum(sendData, 8));

    QString strSend;
    for(int i=0; i<sendData.size(); i++){
        strSend += QString().asprintf("0x%02X ", uchar(sendData[i]));
    }
    m_serialPort->write(sendData);
}

void CallbellHandler::SendDataCheckMessage(){
    QByteArray sendData;
    sendData.push_back(uchar(0x03));
    sendData.push_back(uchar(0x01));
    sendData.push_back(uchar(0x00));
    sendData.push_back(uchar(0x08));
    sendData.push_back(uchar(0xC5));
    sendData.push_back(uchar(0x05));
    sendData.push_back(uchar(0x00));
    sendData.push_back(CalcCheckSum(sendData, 8));

    QString strSend;
    for(int i=0; i<sendData.size(); i++){
        strSend += QString().asprintf("0x%02X ", uchar(sendData[i]));
    }
    m_serialPort->write(sendData);
}


uchar CallbellHandler::CalcCheckSum(QByteArray ba, int size){
    uint temp_sum = 0;
    for(int i=0; i<size-1; i++){
        temp_sum += uchar(ba[i]);
    }
    uchar temp_cs = (temp_sum&0x000000FF);
    temp_cs = (~temp_cs) + 1;
    return temp_cs;
}
