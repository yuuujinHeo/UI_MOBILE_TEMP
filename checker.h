#ifndef CHECKER_H
#define CHECKER_H

#include <memory>

#include <QCoreApplication>
#include <QNetworkConfigurationManager>
#include <QProcess>
#include <QNetworkInterface>
#include <QJsonDocument>
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>
#include <QObject>
#include <QThread>
#include "GlobalHeader.h"

enum
{
    PROCESS_CMD_NONE = 0,
    PROCESS_CMD_SET_SYSTEM_VOLUME,
    PROCESS_CMD_GET_SYSTEM_VOLUME,
    PROCESS_CMD_GET_WIFI_LIST,
    PROCESS_CMD_GET_WIFI_IP,
    PROCESS_CMD_SET_WIFI_IP,
    PROCESS_CMD_CONNECT_WIFI,
    PROCESS_CMD_CHECK_CONNECTION,
    PROCESS_CMD_GIT_PULL,
    PROCESS_CMD_GIT_RESET,
    PROCESS_CMD_GIT_UPDATE,
    PROCESS_CMD_ZIP,
    PROCESS_CMD_UNZIP
};

enum WIFI_CONNECT_ERR_LIST
{
    WIFI_PW_FAILED=1,
    WIFI_CONNECTION_FAILED=2,
    WIFI_CMD_IGNORED=3,
    WIFI_NOT_FOUND_SSID=4,
};

enum WIFI_SET_ERR_LIST
{
    WIFI_SET_FAILED_ERROR=1,
};

enum WIFI_SIGNAL_LEVEL
{
    VERY_LOW=0,
    LOW=1,
    MIDDLE=2,
    HIGH=3,
    VERY_HIGH=4
};

typedef struct
{
    QString cmd;
    QStringList arg;
    QString name;
    bool print;
}ST_PROC;

class Checker : public QObject
{
    Q_OBJECT
public:
    Checker(QObject *parent=0);
    ~Checker();

    //functions
    void setSystemVolume(int volume);
    void getSystemVolume();
    void getWifiList(bool read_all=false);
    void getNetworkState();
    void getNetworkState(QString name);
    void getPing(QString host);
    void getCurrentInterface();
    void gitPull();
    void gitReset();
    void setIP(bool manual, QString ssid, QString ip="", QString subnet="", QString gateway="", QString dns1="", QString dns2="");
    void setEthernet(QString ip, QString subnet, QString gateway, QString dns1, QString dns2);
    void connectWifi(QString ssid, QString passwd);

    std::atomic<bool> is_print = {false};
    std::atomic<bool> is_error = {false};

signals:
    void sig_con_wifi_success(QString ssid);
    void sig_con_wifi_fail(int reason, QString ssid);
    void sig_set_wifi_success(QString ssid);
    void sig_set_wifi_fail(int reason, QString ssid);
    void sig_gitpull_success();
    void sig_gitpull_fail(int reason);

public slots:
    //functions
    void start_set_system_volume(int volume);
    void start_get_system_volume();
    void start_get_network_state(QString name);
    void start_check_ping(QString host);
    void start_get_wifi_interface(QString method);
    void start_git_pull();
    void start_git_reset();
    void start_set_ip(QString method, QString ssid, QString ip="", QString subnet="", QString gateway="", QString dns1="", QString dns2="");
    void start_set_ehternet(QString ip, QString subnet, QString gateway, QString dns1, QString dns2);
    void start_connect_wifi(QString ssid, QString passwd);

    void onTimer();
    void connect_wifi_success(QString ssid);
    void connect_wifi_fail(int reason, QString ssid);
    void set_wifi_success(QString ssid);
    void set_wifi_fail(int reason, QString ssid);

    void error_git_pull(QProcess* _process)
    {
        QByteArray error = _process->readAllStandardError();
        if(error.contains("error:"))
        {
            is_error = true;
        }
        plog->write("[checker][git_pull] Error : "+error);
    }

    void error_git_reset()
    {
        plog->write("[checker][git_reset] Error");
    }
    void error_set_wifi()
    {
        emit connect_wifi_fail(WIFI_PW_FAILED, "");
        plog->write("[checker] setWifi Error");
    }
    void error_connect_wifi(QProcess* _process)
    {
        QByteArray error = _process->readAllStandardError();
        plog->write("[checker] connectWifi Error : " + error);
        if(error.contains("[sudo]"))
        {
            QStringList path = QDir::homePath().split("/");
            if(path.size() < 2)
            {
                plog->write("[checker] invalid homepath. user name is odroid or rainbow");
                return;
            }

            if(path[2]=="odroid")
            {
                _process->write("odroid\n");
            }
            else if(path[2]=="rainbow")
            {
                _process->write("rainbow\n");
            }
            else
            {
                plog->write("[checker] invalid homepath. user name is odroid or rainbow");
                return;
            }

            if(!_process->waitForFinished())
            {
                emit connect_wifi_fail(WIFI_CMD_IGNORED, "");
                return;
            }
        }
        else if(error.contains("No network"))
        {
            emit connect_wifi_fail(WIFI_NOT_FOUND_SSID, "");
            return;
        }
        else
        {
            emit connect_wifi_fail(-1, "");
            return;
        }
    }

private:
    void set_work(ST_PROC cmd);
    QList<ST_PROC> cmd_list;
    QTimer *timer;
};


#endif // CHECKER_H
