#ifndef CMD_CLIENT_H
#define CMD_CLIENT_H

#include "GlobalHeader.h"

#include <QObject>
#include <QTimer>
#include <QWebSocket>

class CMD_CLIENT : public QObject
{
    Q_OBJECT
public:
    explicit CMD_CLIENT(QObject *parent = nullptr);
    ~CMD_CLIENT();

    QString id = "";
    QWebSocket cmd_client;
    QWebSocket error_client;
    QTimer cmd_reconnect_timer;
    QTimer error_reconnect_timer;
    std::atomic<bool> is_cmd_connected = {false};
    std::atomic<bool> is_error_connected = {false};
    std::atomic<int> fms_tick = {0};

    void init();
    void test();

signals:
    void getMessage_cmd(QString msg);
    void getMessage_error(QString msg);

private slots:
    void cmd_connected();
    void cmd_disconnected();
    void cmd_reconnect_loop();
    void onTextMessageReceived_cmd(QString message);

    void error_connected();
    void error_disconnected();
    void error_reconnect_loop();
    void onTextMessageReceived_error(QString message);

    void onError_cmd(QAbstractSocket::SocketError error);
    void onError_error(QAbstractSocket::SocketError error);

public slots:
    void cts_cmd(QByteArray cur_cmd);
};

#endif // CMD_CLIENT_H
