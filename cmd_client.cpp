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
    QString url = "ws://127.0.0.1:12335";
    plog->write("[IPC] Command Client : Init "+url);
    client.open(QUrl(url));
    reconnect_timer.start(1000);
}

void CMD_CLIENT::connected()
{
    if(!is_connected){
        is_connected = true;
        plog->write("[IPC] Command Client : Connected");
    }
}

void CMD_CLIENT::disconnected()
{
    if(is_connected){
        is_connected = false;
        plog->write("[IPC] Command Client : Disconnected");
    }
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
            client.open(QUrl("ws://127.0.0.1:12335"));
        }
    }
}

void CMD_CLIENT::cts_cmd(QByteArray cur_cmd)
{
    client.sendBinaryMessage(cur_cmd);
}
