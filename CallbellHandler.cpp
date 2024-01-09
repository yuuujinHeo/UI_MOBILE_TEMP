#include "CallbellHandler.h"
#include <iostream>

using namespace std;

CallbellHandler::CallbellHandler()
{
    connection_count = 0;
    last_bell_id = "";
    m_serialPort = new QSerialPort();

    connect(m_serialPort, SIGNAL(readyRead()), this, SLOT(readData()));
    connect(m_serialPort, SIGNAL(errorOccurred(QSerialPort::SerialPortError)), this, SLOT(handleError(QSerialPort::SerialPortError)));

    m_serialPort->setPortName("ttyCB0");
    m_serialPort->setBaudRate(QSerialPort::Baud115200);
    m_serialPort->setDataBits(QSerialPort::Data8);
    m_serialPort->setParity(QSerialPort::NoParity);
    m_serialPort->setStopBits(QSerialPort::OneStop);
    m_serialPort->setFlowControl(QSerialPort::SoftwareControl);

    if(m_serialPort->open(QIODevice::ReadWrite)){
        plog->write("[CALLBELL] Port Open Success");
    }else{
        m_serialPort->setPortName("ttyUSB1");
        plog->write("[CALLBELL] Port Open Failed");
    }

    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimer()));
    timer->start(200);
}

void CallbellHandler::onTimer(){
    static int time_cnt = 0;
    time_cnt++;
    if(time_cnt > 10 && !m_serialPort->isOpen()){
        if(m_serialPort->open(QIODevice::ReadWrite)){
            plog->write("[CALLBELL] SERIAL "+m_serialPort->portName() + " OPEN SUCCESS!");
        }else{
//            plog->write("[CALLBELL] SERIAL "+m_serialPort->portName() + " OPEN FAIL");
        }
        time_cnt = 0;
    }
}

void CallbellHandler::readData(){
    QByteArray data = m_serialPort->readAll();
    datas += data;

    QString str;
    for(int i=0; i<data.size(); i++){
        str += QString().asprintf("0x%02X ", uchar(data[i]));
    }
//    qDebug() << str;
//    qDebug() << "CALLBELL" << data;

    while(datas.length() > 4){
        if(uchar(datas[0]) == 0x03 && uchar(datas[1]) == 0x01){
            int size = (short)(uchar(datas[3]) | (uchar(datas[2])<<8));
//            qDebug() << "SIZE : " << size;

            if(size < 0 || size > 24){
                datas.remove(0, 1);
            }else{
                if(size <= datas.length()){
                    uint option = (ushort)(uchar(datas[5]) | (uchar(datas[4])<<8));
                    uint model_num = (ushort)(uchar(datas[7]) | (uchar(datas[6])<<8));
                    uint firmware_ver = (ushort)(uchar(datas[9]) | (uchar(datas[8])<<8));
                    uint bell_id;
                    uint button_info;
                    uint bell_info;
//                    qDebug() << QString().asprintf("Option: %04X", option);
//                    qDebug() << QString().asprintf("Model: %04X", model_num);
//                    qDebug() << QString().asprintf("Firmware: %04X", firmware_ver);

                    if(size == 12){
                        // connection check
                        uchar checksum = uchar(datas[11]);
                        uchar temp_cs = CalcCheckSum(datas, size);

//                        qDebug() << int(checksum) << " : " << int(temp_cs) ;
                        datas.remove(0, size);

                        if((checksum == temp_cs) && (option == 0xA501)){
                            SendConnectionCheckMessage();
                        }
                    }else if(size == 20){
                        // data check
                        bell_id = (unsigned int)(uchar(datas[13]) | (uchar(datas[12])<<8) | (uchar(datas[11])<<16) | (uchar(datas[10])<<24));
                        button_info = uchar(datas[14]);
                        bell_info = uchar(datas[15]);
//                        qDebug() << QString().asprintf("Bell ID: %08X", bell_id);
//                        qDebug() << QString().asprintf("Button Info: %d", button_info);
//                        qDebug() << QString().asprintf("Bell Info: %d", bell_info);

                        QString bell_str = QString().asprintf("%08X", bell_id);

                        uchar checksum = uchar(datas[19]);
                        uchar temp_cs = CalcCheckSum(datas, size);

//                        qDebug() << int(checksum) << " : " << int(temp_cs) ;
                        datas.remove(0, size);

                        if((checksum == temp_cs) && (option == 0xA505)){
                            SendDataCheckMessage();
                            last_bell_id = bell_str;
                            plog->write("[CALLBELL] NEW CALLING : " + last_bell_id);
                            emit new_call();
                        }
                    }
                }else{
                    break;
                }
            }
        }else{
            datas.remove(0, 1);
        }
    }
}

void CallbellHandler::handleError(QSerialPort::SerialPortError error){
    if(error == QSerialPort::ResourceError){
        plog->write("[SERIAL] PORT CRITICAL ERROR");
        if(m_serialPort->isOpen())
            m_serialPort->close();
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
//    qDebug() << strSend;
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
//    qDebug() << strSend;
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
