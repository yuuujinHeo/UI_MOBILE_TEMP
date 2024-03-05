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
    void getWifiInterface();
    void connectWifi(QString ssid, QString passwd);

    void setProperties(bool isprint){
        is_print = isprint;
    }
signals:
    void finished();
public:
    Worker(QString _name):name(_name){}
    QProcess *process;
    QString name;
    bool is_print;
    void setWork(const QString &_program, const QStringList &arg){
        program = _program;
        argument = arg;
    }
    QString program;
    QStringList argument;
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
    void getSystemVolume();
    void getWifiList();
    void getNetworkState();

private slots:
    void onTimer();
private:
    QList<ST_PROC> cmd_list;
    QThread *thread_1;
    QThread *thread_2;
    Worker *worker_1;
    Worker *worker_2;
    QTimer *timer;
};


#endif // CHECKER_H
