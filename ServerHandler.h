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

#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/aes.h>
#include "GlobalHeader.h"
#include "ZIPHandler.h"

// websocket ------------------
#include <websocket/QtHttpServer.h>
#include <websocket/QtHttpRequest.h>
#include <websocket/QtHttpReply.h>
#include <QApplication>
#include <websocket/QtHttpHeader.h>

#define SERVER_URL "http://127.0.0.1:11334"
#define MONITOR_URL "http://10.108.1.10:11335"

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

    void newPost(QByteArray post_data, QString url);
    void newPostFile(QString file_dir, QString url);

    void goqualPost(QByteArray body, QString url);
    void goqualGet(QString url);

    void checkUpdate();
    void doUpdateUI(QString version);
    void doUpdate();

    void uploadRelease(QString file, QString message);

    void serverPost(QString url, QByteArray body);

    void getNewID();
    void sendRobotConfig();
    void sendUpdateConfig();
    void sendStaticConfig();
    void sendSettingConfig();
    void sendMaps();

    void getGitCommits();

    bool need_update();
    void rename_all();
    void sendStatus();

    //new
    void getCurVersion(QString filename);
    void getNewVersion(QString filename);
    void getNewVersions(QString filename);

    void generalReply(QtHttpReply *reply, QByteArray post_data);
    void parsingReply(QString type, QString url, QNetworkReply *reply);
    void parsingServer(QString url, QNetworkReply *reply);
    QString getSetting(QString file, QString group, QString name);
    QJsonObject json_in;
    QJsonObject json_out;
    QProcess *process;

    //New Variables
    QMap<QString, ST_UPDATE> update_list;
    QMap<QString, ST_UPDATE> version_list;
    QString last_update_date;
    QString last_update_mode;

    //---------------------goqual
    QString goqual_url = "https://goqual.io";
    ST_GOQUAL_LOGIN goqual_login;
    ST_GOQUAL_TOKEN goqual_token;
    QMap<QString,ST_GOQUAL_RELAY> goqual_relays;

    QByteArray encrypt(const QByteArray &text);

    void getGoqualKey();
    void refreshGoqualKey();
    void getGoqualDevices();
    void setGoqualRelay(QString id, bool onoff);

    bool mobile_connection = true;
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
//    QString serverURL = "http://rbyujin.com:8080";
    QString serverURL = "http://127.0.0.1:11334";
    QString fileserverURL = "http://10.108.1.10:11335";
//    QString serverURL = "http://49.50.173.53:11334";
    QString myID = "YUJIN_NUC";

    QTime startTime;
    QTime elapsedTime;

    ST_VERSION ui_version;
    ST_VERSION ui_version_new;
    QList<ST_VERSION> ui_new_versions;
signals:
    void updatefail();
    void updatesuccess();
    void newCallOrder(QString table);

private slots:
    void onCallRequestReply(QtHttpRequest *request, QtHttpReply *reply);
    void onCallRequestReply2(QtHttpRequest *request, QtHttpReply *reply);
    void onTimer();
private:
    QNetworkAccessManager   *manager;
    QNetworkAccessManager   *goqual_manager;
    QtHttpServer *call_server;
    QTimer  *timer;
};

#endif // SERVERHANDLER_H
