#ifndef CALLBELLHANDLER_H
#define CALLBELLHANDLER_H

#include <QObject>
#include <QTimer>
#include <QSerialPort>
#include <QDebug>
#include "GlobalHeader.h"

enum bell_info
{
    BELL_CONNECT=0xA501,
    BELL_PUSH=0xA505,
    BELL_CHECK=0xA511,
    SENDER_CALL=0xA514
};

class CallbellHandler : public QObject
{
    Q_OBJECT
public:
    explicit CallbellHandler(QObject *parent = nullptr);
    ~CallbellHandler();

    std::mutex mtx;

    QString get_bell_ID();
    bool is_open_port();

    void send_call(QString id);

public slots:
    void reconnection_loop();
    void read_data();
    void handle_error(QSerialPort::SerialPortError error);

signals:
    void new_call();

private:
    QSerialPort *m_serialPort = nullptr;
    QTimer *reconnection_timer;
    QByteArray datas;
    QString last_bell_id;

    void send_connection_check_message();
    void send_data_check_message();

    uchar calc_checksum(QByteArray ba, int size);
};

#endif // CALLBELLHANDLER_H
