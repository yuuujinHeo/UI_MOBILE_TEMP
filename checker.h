#ifndef CHECKER_H
#define CHECKER_H

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
//BJ
#include <QTimer>
#include <QScopedPointer>   //QScopedPointe를 사용하기 위한 헤더 추가
#include <QMutex>           //QMutex를 사용하기 위한 헤더 추가

enum{
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

class Worker : public QObject
{
    Q_OBJECT
public slots:
    void getSystemVolume();
    void setSystemVolume();
    void getWifiInterface();
    void startMonitorNetwork();
    void connectWifi();
    void checkPing();
    void setIP();
    void setEthernet();
    void gitPull();
    void gitReset();
    void setProperties(bool isprint){
        is_print = isprint;
    }
    void getNetworkState();
    void network_output();

    void error_git_pull(){
        QByteArray error = process->readAllStandardError();
        if(error.contains("error:")){
            is_error = true;
        }
        plog->write("[checker] GitPull Error : "+error);
    }

    void error_git_reset(){
        QByteArray error = process->readAllStandardError();
        plog->write("[checker] GitReset Error : "+error);
    }
    void error_set_wifi(){
        QByteArray error = process->readAllStandardError();
        plog->write("[checker] setWifi Error : "+error);
        emit connect_wifi_fail(1, argument[0]);
        emit finished(this);
    }
    void error_connect_wifi(){
        QByteArray error = process->readAllStandardError();
        plog->write("[checker] connectWifi Error : "+error);
        if(error.contains("[sudo]")){

            if(QDir::homePath().split("/")[2]=="odroid"){
                process->write("odroid\n");
            }else{
                process->write("rainbow\n");
            }
            if(!process->waitForFinished()){
                emit connect_wifi_fail(3, argument[0]);
                emit finished(this);
                return;
            }
        }else if(error.contains("No network")){
            emit connect_wifi_fail(4, argument[0]);
            emit finished(this);
            return;
        }else{
            emit connect_wifi_fail(0, argument[0]);
            emit finished(this);
            return;
        }
    }

    //0725-BJ
    void outputAvailable();
    void processFinished(int exitCode, QProcess::ExitStatus exitStatus);

signals:
    void finished(Worker *w);
    void change_network(QString line);
    void connect_wifi_success(QString ssid);
    void connect_wifi_fail(int reason, QString ssid);
    void set_wifi_success(QString ssid);
    void set_wifi_fail(int reason, QString ssid);
    void git_pull_failed();
    void git_pull_nothing();
    void git_pull_success();

public:
    Worker(QString _name, QThread *th):name(_name),parent_thread(th){}
    ~Worker(){
        // disconnect(process,SIGNAL(readyReadStandardError()),this,SLOT(error_connect_wifi()));
    }
    QThread *parent_thread;
    QProcess *process;
    QString name;
    bool is_error = false;
    bool is_print;
    QString program;
    QStringList argument;
    void setWork(const QString &_program, const QStringList &arg){
        program = _program;
        argument = arg;
    }
};


typedef struct{
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

signals:
    void sig_con_wifi_success(QString ssid);
    void sig_con_wifi_fail(int reason, QString ssid);
    void sig_set_wifi_success(QString ssid);
    void sig_set_wifi_fail(int reason, QString ssid);
    void sig_gitpull_success();
    void sig_gitpull_fail(int reason);

    // 0725-BJ
    void wifi_connect_success();
    void wifi_connect_failed();
    void ethernet_config_success();
    void ethernet_config_failed();
    void ip_config_success();
    void ip_config_failed();

private slots:
    void onTimer();
    void connect_wifi_success(QString ssid);
    void connect_wifi_fail(int reason, QString ssid);
    void set_wifi_success(QString ssid);
    void set_wifi_fail(int reason, QString ssid);
    void change_network(QString line);
    void gitpull_success();
    void gitpull_fail();
    void gitpull_nothing();
private:
    void disWork(Worker *worker);
    void setWork(ST_PROC cmd, QThread *thread, Worker *worker);
    QList<ST_PROC> cmd_list;
    QThread *thread_1;
    QThread *thread_2;
    QThread *thread_3;
    Worker *worker_1;
    Worker *worker_2;
    Worker *worker_3;
    QTimer *timer;
    QProcess *process;  // 07.25-BJ
    QMutex mutex;       // 동기화를 위한 QMutex 추가
};


#endif // CHECKER_H
