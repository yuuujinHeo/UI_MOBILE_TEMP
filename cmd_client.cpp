#include "cmd_client.h"

CMD_CLIENT::CMD_CLIENT(QObject *parent)
    : QObject(parent)
    , reconnect_timer(this)
{
    connect(&client, &QWebSocket::connected, this, &CMD_CLIENT::connected);
    connect(&client, &QWebSocket::disconnected, this, &CMD_CLIENT::disconnected);
    connect(&reconnect_timer, SIGNAL(timeout()), this, SLOT(reconnect_loop()));
}

CMD_CLIENT::~CMD_CLIENT()
{
    client.close();
}

void CMD_CLIENT::init()
{
    client.open(QUrl("ws://127.0.0.1:1234"));
    reconnect_timer.start(1000);
}

void CMD_CLIENT::connected()
{
    is_connected = true;
    printf("[WS] server(SLAM) connected\n");
}

void CMD_CLIENT::disconnected()
{
    is_connected = false;
    printf("[WS] server(SLAM) disconnected\n");
}

void CMD_CLIENT::reconnect_loop()
{
    if(client.state() == QAbstractSocket::ConnectedState)
    {

    }
    else if(client.state() == QAbstractSocket::ConnectingState)
    {

    }
    else
    {
        if(is_connected == false)
        {
            client.open(QUrl("ws://127.0.0.1:1234"));
        }
    }
}

void CMD_CLIENT::cts_cmd(QByteArray cur_cmd)
{
//    QByteArray message;
//    message.resize(sizeof(CMD));
//    memcpy(message.data(), &cur_cmd, sizeof(CMD));

    client.sendBinaryMessage(cur_cmd);
}
