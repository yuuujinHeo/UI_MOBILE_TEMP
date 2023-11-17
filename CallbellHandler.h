#ifndef CALLBELLHANDLER_H
#define CALLBELLHANDLER_H

#include <QObject>
#include <QTimer>
#include <QSerialPort>
#include <QDebug>
#include "GlobalHeader.h"


class CallbellHandler : public QObject
{
    Q_OBJECT
public:
    CallbellHandler();

    QString getBellID(){return last_bell_id;}
    bool isOpenPort(){return m_serialPort->isOpen();}

    int connection_count;

public slots:
    void onTimer();
    void readData();
    void handleError(QSerialPort::SerialPortError error);

signals:
    void new_call();

private:
    QSerialPort *m_serialPort = nullptr;
    QTimer *timer;
    QByteArray datas;
    QString last_bell_id;


    void SendConnectionCheckMessage();
    void SendDataCheckMessage();

    uchar CalcCheckSum(QByteArray ba, int size);
};

#endif // CALLBELLHANDLER_H
