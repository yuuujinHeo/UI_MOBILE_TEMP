#include "cmd_client.h"

// json -----------------------
#include <QJsonDocument>
#include <QJsonValue>
#include <QWebSocket>
#include <QJsonArray>
#include <QJsonObject>
CMD_CLIENT::CMD_CLIENT(QObject *parent)
    : QObject(parent)
    , reconnect_timer(this)
{
    connect(&client, &QWebSocket::connected, this, &CMD_CLIENT::connected);
    connect(&client, &QWebSocket::disconnected, this, &CMD_CLIENT::disconnected);
    connect(&client, &QWebSocket::disconnected, this, &CMD_CLIENT::disconnected);
    connect(&client, QOverload<QAbstractSocket::SocketError>::of(&QWebSocket::error),
            this, &CMD_CLIENT::onError);
    connect(&client, &QWebSocket::textMessageReceived, this, &CMD_CLIENT::onTextMessageReceived);

    connect(&reconnect_timer, SIGNAL(timeout()), this, SLOT(reconnect_loop()));
}

CMD_CLIENT::~CMD_CLIENT()
{
    client.close();
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
    client.sendTextMessage(jsonDoc.toJson(QJsonDocument::Compact));

}

void CMD_CLIENT::onError(QAbstractSocket::SocketError error){
    std::cerr << "WebSocket error: " << error << std::endl;
}

void CMD_CLIENT::onTextMessageReceived(QString message) {
    std::cout << "Received from server: " << message.toStdString() << std::endl;

    // JSON 형식으로 역직렬화
    QJsonDocument jsonDoc = QJsonDocument::fromJson(message.toUtf8());
    QJsonArray jsonArray = jsonDoc.array();
    QVector<int> vectorData;
    for (const QJsonValue &value : jsonArray) {
        vectorData.append(value.toInt());
    }

    // 받은 데이터 처리 (예제에서는 출력)
    std::cout << "Processed data: ";
    for (int value : vectorData) {
        std::cout << value << " ";
    }
    std::cout << std::endl;
}

void CMD_CLIENT::init()
{
    //QString url = "ws://127.0.0.1:12335"; //what??? diff with SLAMNAV
    QString url = "ws://127.0.0.1:12335"; // change : 24.06.27
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
            //client.open(QUrl("ws://127.0.0.1:12335"));
            client.open(QUrl("ws://127.0.0.1:12335")); // change :24.06.27
        }
    }
}

void CMD_CLIENT::cts_cmd(QByteArray cur_cmd)
{
    client.sendBinaryMessage(cur_cmd);
}
