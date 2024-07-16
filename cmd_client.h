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
    QWebSocket client;
    QTimer reconnect_timer;
    std::atomic<bool> is_connected = {false};
    std::atomic<int> fms_tick = {0};

    void init();
    void test();

signals:
    void getMessage(QString msg);

private slots:
    void connected();
    void disconnected();
    void reconnect_loop();
    void onTextMessageReceived(QString message);
    void onError(QAbstractSocket::SocketError error);

public slots:
    void cts_cmd(QByteArray cur_cmd);
};

#endif // CMD_CLIENT_H
