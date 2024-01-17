#ifndef SERVERHANDLER_H
#define SERVERHANDLER_H

#include <QObject>
#include <QtNetwork>
#include <QTimer>
#include <QDebug>

#include <QGuiApplication>
// json -----------------------
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>

// connection ------------------
#include <QEventLoop>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>
#include <QNetworkRequest>

#include <QTimer>

#include "GlobalHeader.h"
#include "ZIPHandler.h"

// websocket ------------------
#include <websocket/QtHttpServer.h>
#include <websocket/QtHttpRequest.h>
#include <websocket/QtHttpReply.h>
#include <QApplication>
#include <websocket/QtHttpHeader.h>


class ServerHandler : public QObject
{
    Q_OBJECT
public:
    ServerHandler();
    void sendfilePost(QString file_dir, QString url);
    void generalPost(QByteArray post_data, QString url);
    void generalGet(QString url);
    void generalPut(QString url, QByteArray put_data);
    void generalDelete(QString url);
    void ClearJson(QJsonObject &json);
    void setSetting(QString file, QString name, QString value);
    void postStatus();

    void checkUpdate();
    void doUpdate();


    void uploadRelease(QString file, QString message);

    void getNewID();
    void sendRobotConfig();
    void sendUpdateConfig();
    void sendStaticConfig();
    void sendSettingConfig();
    void sendMaps();

    void getGitCommits();

    bool need_update();
    void rename_all();

    void parsingReply(QString type, QString url, QNetworkReply *reply);
    QString getSetting(QString file, QString group, QString name);
    QJsonObject json_in;
    QJsonObject json_out;
    QProcess *process;

    //New Variables
    QMap<QString, ST_UPDATE> update_list;
    QMap<QString, ST_UPDATE> version_list;
    QString last_update_date;
    QString last_update_mode;

    bool connection = true;
    bool send_config = false;
    bool send_map = false;
    bool first_response = false;

    bool check_update = false;
    bool new_update = false;
    bool new_update_local = false;
    bool update_config = false;
    bool update_program = false;
    bool update_map = false;
    bool update_auto = false;
    QString config_version;
    QString program_version;
    QString maps_version;
    QString config_str;
    QString program_str;
    QString maps_str;
    QString message;


    int TIMER_MS = 1000;
    QString serverURL = "http://rbyujin.com:8080";
    QString myID = "";

signals:
    void updatefail();
    void updatesuccess();
private slots:
    void onCallRequestReply(QtHttpRequest *request, QtHttpReply *reply);
    void onTimer();
private:
    QNetworkAccessManager   *manager;
    QtHttpServer *call_server;
    QTimer  *timer;
};

#endif // SERVERHANDLER_H
