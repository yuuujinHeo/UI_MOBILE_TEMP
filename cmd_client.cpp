#include "cmd_client.h"

// json -----------------------
#include <QJsonDocument>
#include <QJsonValue>
#include <QWebSocket>
#include <QJsonArray>
#include <QJsonObject>
CMD_CLIENT::CMD_CLIENT(QObject *parent)
    : QObject(parent)
    , cmd_reconnect_timer(this)
    , error_reconnect_timer(this)
{
    connect(&cmd_client, &QWebSocket::connected, this, &CMD_CLIENT::cmd_connected);
    connect(&cmd_client, &QWebSocket::disconnected, this, &CMD_CLIENT::cmd_disconnected);
    connect(&cmd_client, QOverload<QAbstractSocket::SocketError>::of(&QWebSocket::error),
            this, &CMD_CLIENT::onError_cmd);

    connect(&cmd_client, &QWebSocket::textMessageReceived, this, &CMD_CLIENT::onTextMessageReceived_cmd);
    connect(&cmd_reconnect_timer, SIGNAL(timeout()), this, SLOT(cmd_reconnect_loop()));

    connect(&error_client, &QWebSocket::connected, this, &CMD_CLIENT::error_connected);
    connect(&error_client, &QWebSocket::disconnected, this, &CMD_CLIENT::error_disconnected);
    connect(&error_client, QOverload<QAbstractSocket::SocketError>::of(&QWebSocket::error),
            this, &CMD_CLIENT::onError_error);

    connect(&error_client, &QWebSocket::textMessageReceived, this, &CMD_CLIENT::onTextMessageReceived_error);
    connect(&error_reconnect_timer, SIGNAL(timeout()), this, SLOT(cmd_reconnect_loop()));
}

CMD_CLIENT::~CMD_CLIENT()
{
    cmd_client.close();
    error_client.close();
}

void CMD_CLIENT::test(){

    // 예제 벡터 데이터
    QVector<int> vectorData = {1, 2, 3, 4, 5};

    // JSON 형식으로 직렬화
    QJsonObject testObject;
    testObject["time"] = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");

    QJsonObject temp;
    temp["x"] = "0.1";
    temp["y"] = "0.1";
    temp["rz"] = "0.1";
    testObject["pose"] = temp;

    QJsonObject temp2;
    temp2["vx"] = "0.2";
    temp2["vy"] = "0.2";
    temp2["wz"] = "0.2";
    testObject["vel"] = temp2;

    QJsonArray tempa;
    QJsonObject t;
    t["connection"] = "true";
    t["status"] = "0";
    t["temp"] = "36.5";
    tempa.push_back(t);
    tempa.push_back(t);
    testObject["motor"] = tempa;

    QJsonObject temp3;
    temp3["bat_in"] = "0.2";
    temp3["bat_out"] = "0.2";
    temp3["bat_current"] = "0.2";
    temp3["power"] = "0.2";
    temp3["total_power"] = "0.2";
    testObject["power"] = temp3;


    QJsonObject temp4;
    temp4["power"] = "false";
    temp4["emo"] = "false";
    temp4["charge"] = "false";
    temp4["localization"] = "busy";
    testObject["state"] = temp4;

    QJsonObject temp5;
    temp5["inlier_error"] = "0.2";
    temp5["inlier_ratio"] = "0.8";
    testObject["condition"] = temp5;

    QJsonDocument jsonDoc(testObject);

    // 서버로 JSON 데이터 전송
    cmd_client.sendTextMessage(jsonDoc.toJson(QJsonDocument::Compact));
}

void CMD_CLIENT::onError_cmd(QAbstractSocket::SocketError error){
    // std::cerr << "WebSocket error: " << error << std::endl;
}

void CMD_CLIENT::onError_error(QAbstractSocket::SocketError error){
    // std::cerr << "WebSocket error: " << error << std::endl;
}

void CMD_CLIENT::onTextMessageReceived_cmd(QString message) {

    plog->write("[IPC][CMD] SLAMNAV send Message : " + message);

    QStringList msg_list = message.split(",");
    if(msg_list.size() < 3)
    {
        plog->write("[IPC][ERROR] invalid msg format");
        return;
    }

    int cmd = msg_list[1].toInt();
    QString accept = msg_list[2];

    if(cmd == ROBOT_CMD_MOVE_TARGET_EX)
    {
        if(accept == "failed")
        {
            if(msg_list.size() != 4)
            {
                plog->write("[IPC][ERROR][ROBOT_CMD_MOVE_TARGET_EX] invalid size:" + QString::number(msg_list.size()));
                return;
            }

            // check ROBOT_CMD_ERROR_LIST
            int err_code = msg_list[3].toInt();
        }
        else if(accept == "success")
        {
            if(msg_list.size() != 7)
            {
                plog->write("[IPC][ERROR][ROBOT_CMD_MOVE_TARGET_EX] invalid size:" + QString::number(msg_list.size()));
                return;
            }

            double x = msg_list[3].toDouble();
            double y = msg_list[4].toDouble();
            double deg = msg_list[5].toDouble();
            int preset = msg_list[6].toInt();
        }
    }
    else if(cmd == ROBOT_CMD_MOVE_TARGET)
    {
        if(accept == "failed")
        {
            if(msg_list.size() != 4)
            {
                plog->write("[IPC][ERROR][ROBOT_CMD_MOVE_TARGET] invalid size:" + QString::number(msg_list.size()));
                return;
            }

            int err_code = msg_list[3].toInt();



        }
        else if(accept == "success")
        {
            if(msg_list.size() != 7)
            {
                plog->write("[IPC][ERROR][ROBOT_CMD_MOVE_TARGET] invalid size:" + QString::number(msg_list.size()));
                return;
            }

            double x = msg_list[3].toDouble();
            double y = msg_list[4].toDouble();
            double deg = msg_list[5].toDouble();
            int preset = msg_list[6].toInt();
        }
    }
    else if(cmd == ROBOT_CMD_MOVE_STOP)
    {
        if(accept == "success")
        {
            // do something
        }
    }
    else if(cmd == ROBOT_CMD_MOVE_PAUSE)
    {
        if(accept == "success")
        {
            // do something
        }
    }
    else if(cmd == ROBOT_CMD_MOVE_RESUME)
    {
        if(accept == "success")
        {
            // do something
        }
    }
    else if(cmd == ROBOT_CMD_RESTART)
    {
        if(accept == "success")
        {
            // do something
        }
    }
    else if(cmd == ROBOT_CMD_SET_INIT)
    {
        if(accept == "success")
        {
            if(msg_list.size() != 6)
            {
                plog->write("[IPC][ERROR][ROBOT_CMD_MOVE_TARGET] invalid size:" + QString::number(msg_list.size()));
                return;
            }

            double x = msg_list[3].toDouble();
            double y = msg_list[4].toDouble();
            double deg = msg_list[5].toDouble();
        }
    }
    else if(cmd == ROBOT_CMD_SLAM_RUN)
    {
        if(accept == "success")
        {
            // do something
        }
    }
    else if(cmd == ROBOT_CMD_SLAM_STOP)
    {
        if(accept == "success")
        {
            // do something
        }
    }
    else if(cmd == ROBOT_CMD_SLAM_AUTO)
    {
        if(accept == "success")
        {
            // do something
        }
    }
    else if(cmd == ROBOT_CMD_SLAM_FULL_AUTO)
    {
        if(accept == "success")
        {
            // do something
        }
    }
    else if(cmd == ROBOT_CMD_MAPPING_START)
    {
        if(accept == "failed")
        {
            if(msg_list.size() != 6)
            {
                plog->write("[IPC][ERROR][ROBOT_CMD_MAPPING_START] invalid size:" + QString::number(msg_list.size()));
                return;
            }

            int err_code = msg_list[3].toInt();
            int map_size = msg_list[4].toInt();
            double grid_size = msg_list[5].toDouble();
        }
        else if(accept == "success")
        {
            if(msg_list.size() != 5)
            {
                plog->write("[IPC][ERROR][ROBOT_CMD_MAPPING_START] invalid size:" + QString::number(msg_list.size()));
                return;
            }

            int map_size = msg_list[3].toInt();
            double grid_size = msg_list[4].toDouble();
        }
    }
    else if(cmd == ROBOT_CMD_MAPPING_STOP)
    {
        if(accept == "failed")
        {
            if(msg_list.size() != 4)
            {
                plog->write("[IPC][ERROR][ROBOT_CMD_MAPPING_STOP] invalid size:" + QString::number(msg_list.size()));
                return;
            }

            int err_code = msg_list[3].toInt();
        }
        else if(accept == "success")
        {
            // do something
        }
    }
    else if(cmd == ROBOT_CMD_MAPPING_SAVE)
    {
        if(accept == "failed")
        {
            if(msg_list.size() != 4)
            {
                plog->write("[IPC][ERROR][ROBOT_CMD_MAPPING_SAVE] invalid size:" + QString::number(msg_list.size()));
                return;
            }

            int err_code = msg_list[3].toInt();
        }
        else if(accept == "success")
        {
            // do something
        }
    }
    else if(cmd == ROBOT_CMD_MOTOR_LOCK_ON)
    {
        if(accept == "success")
        {
            // do something
        }
    }
    else if(cmd == ROBOT_CMD_DRAW_LINE_START)
    {
        if(accept == "success")
        {
            // do something
        }
    }
    else if(cmd == ROBOT_CMD_DRAW_LINE_SAVE)
    {
        if(accept == "success")
        {
            // do something
        }
    }
    else if(cmd == ROBOT_CMD_MAP_RELOAD)
    {
        if(accept == "failed")
        {
            if(msg_list.size() != 4)
            {
                plog->write("[IPC][ERROR][ROBOT_CMD_MAP_RELOAD] invalid size:" + QString::number(msg_list.size()));
                return;
            }

            int err_code = msg_list[3].toInt();
        }
        else if(accept == "success")
        {
            // do something
        }
    }
    else if(cmd == ROBOT_CMD_SETTING_RELOAD)
    {
        if(accept == "success")
        {
            // do something
        }
    }
    else if(cmd == ROBOT_CMD_SERVER_MAP_UPDATE)
    {
        if(accept == "failed")
        {
            if(msg_list.size() != 4)
            {
                plog->write("[IPC][ERROR][ROBOT_CMD_SERVER_MAP_UPDATE] invalid size:" + QString::number(msg_list.size()));
                return;
            }

            int err_code = msg_list[3].toInt();
        }
        else if(accept == "success")
        {
            // do something
        }
    }
    else if(cmd == ROBOT_CMD_CHECK_TRAVEL_LINE)
    {
        if(accept == "success")
        {
            // do something
        }
    }
    else if(cmd == ROBOT_CMD_MAP_SOFT_RELOAD)
    {
        if(accept == "failed")
        {
            if(msg_list.size() != 4)
            {
                plog->write("[IPC][ERROR][ROBOT_CMD_SERVER_MAP_UPDATE] invalid size:" + QString::number(msg_list.size()));
                return;
            }

            int err_code = msg_list[3].toInt();
        }
        else if(accept == "success")
        {
            // do something
        }
    }
    else if(cmd == ROBOT_CMD_MAP_LOOP_CLOSING)
    {
        if(accept == "success")
        {
            // do something
        }
    }
    else if(cmd == ROBOT_CMD_SLAM_RESTING)
    {
        if(accept == "success")
        {
            // do something
        }
    }
    else if(cmd == ROBOT_CMD_MOTOR_LOCK_OFF2)
    {
        if(accept == "success")
        {
            // do something
        }
    }
    else if(cmd == ROBOT_CMD_AUTO_FIND_DEVICE)
    {
        if(accept == "failed")
        {
            if(msg_list.size() != 4)
            {
                plog->write("[IPC][ERROR][ROBOT_CMD_SERVER_MAP_UPDATE] invalid size:" + QString::number(msg_list.size()));
                return;
            }

            int err_code = msg_list[3].toInt();
        }
        else if(accept == "success")
        {
            // do something
        }
    }
    else if(cmd == -1)
    {

    }

    //probot->notice_message = message;
    emit getMessage_cmd(message);

}

void CMD_CLIENT::onTextMessageReceived_error(QString message) {

    plog->write("[IPC][ERROR] SLAMNAV send Message : " + message);

    probot->notice_message = message;
    emit getMessage_error(message);
}

void CMD_CLIENT::init()
{
    QString url = "ws://127.0.0.1:12335"; // change : 24.06.27
    plog->write("[IPC] Command Client : Init " + url);
    cmd_client.open(QUrl(url));
    cmd_reconnect_timer.start(3000);

    QString error_url = "ws://127.0.0.1:12336"; // change : 24.06.27
    plog->write("[IPC] Error Client : Init " + error_url);
    error_client.open(QUrl(error_url));
    error_reconnect_timer.start(3000);
}

void CMD_CLIENT::cmd_connected()
{
    if(!is_cmd_connected){
        is_cmd_connected = true;
        plog->write("[IPC] Command Client : Connected");
    }
}

void CMD_CLIENT::cmd_disconnected()
{
    if(is_cmd_connected){
        is_cmd_connected = false;
        plog->write("[IPC] Command Client : Disconnected");
    }
}

void CMD_CLIENT::cmd_reconnect_loop()
{
    if(cmd_client.state() == QAbstractSocket::ConnectedState)
    {

    }
    else if(cmd_client.state() == QAbstractSocket::ConnectingState)
    {

    }
    else
    {
        if(is_cmd_connected == false)
        {
            cmd_client.open(QUrl("ws://127.0.0.1:12335"));
        }
    }
}

void CMD_CLIENT::error_connected()
{
    if(!is_error_connected){
        is_error_connected = true;
        plog->write("[IPC] Error Client : Connected");
    }
}

void CMD_CLIENT::error_disconnected()
{
    if(is_error_connected){
        is_error_connected = false;
        plog->write("[IPC] Error Client : Disconnected");
    }
}

void CMD_CLIENT::error_reconnect_loop()
{
    if(error_client.state() == QAbstractSocket::ConnectedState)
    {

    }
    else if(error_client.state() == QAbstractSocket::ConnectingState)
    {

    }
    else
    {
        if(is_error_connected == false)
        {
            error_client.open(QUrl("ws://127.0.0.1:12336"));
        }
    }
}

void CMD_CLIENT::cts_cmd(QByteArray cur_cmd)
{
    cmd_client.sendBinaryMessage(cur_cmd);
}
