#ifndef EXTPROCESS_H
#define EXTPROCESS_H

#include <QProcess>
#include <QObject>
#include <QSettings>
#include <QTimer>
#include <QSharedMemory>
#include <QApplication>
#include "GlobalHeader.h"

class ExtProcess : public QObject
{
    Q_OBJECT
public:
    explicit ExtProcess(QObject *parent = nullptr);
    ~ExtProcess();

    enum{
        PROCESS_RETURN_NONE = 0,
        PROCESS_RETURN_ACCEPT,
        PROCESS_RETURN_DONE,
        PROCESS_RETURN_ERROR,
        PROCESS_RETURN_SENDING
    };
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
    struct Command{
        uint32_t tick = 0;
        uint32_t cmd = 0;
        uint8_t params[100] = {0,};
        uint8_t params2[100] = {0,};
        uint8_t params3[100] = {0,};
        Command()
        {
        }
        Command(const Command& p)
        {
            tick = p.tick;
            cmd = p.cmd;
            memcpy(params, p.params, 100);
            memcpy(params2, p.params2, 100);
            memcpy(params3, p.params3, 100);
        }
    };

    struct WifiList{
        uint32_t tick = 0;
        uint8_t size = 0;
        uint8_t ssid[10][100] = {0,};
        uint8_t param[10][10] = {0,};
        WifiList(){

        }
        WifiList(const WifiList& p){
            tick = p.tick;
            size = p.size;
            memcpy(ssid, p.ssid, 1000);
            memcpy(param, p.param, 100);

        }
    };

    struct Return{
        uint32_t tick = 0;
        uint32_t result = 0;
        uint32_t command = 0;
        uint8_t params[100] = {0,};
        uint8_t params2[100] = {0,};
        uint8_t params3[100] = {0,};
        Return()
        {
        }
        Return(const Return& p)
        {
            tick = p.tick;
            result = p.result;
            command = p.command;
            memcpy(params, p.params, 100);
            memcpy(params2, p.params2, 100);
            memcpy(params3, p.params3, 100);
        }
    };

    void setSetting(QString file, QString name, QString value);
    QString getSetting(QString file, QString group, QString name);
    void set_command(Command cmd, QString log = "");

    void update_unzip();
    void git_pull();
    void git_reset();

    int wifi_list_size = 0;

signals:
    void got_accept(int cmd);
    void got_done(int cmd);
    void got_error(int cmd);
    void timeout(int cmd);

private slots:
    void onTimer();
    void onTimer500();

private:
    int tick = 0;
    int timeout_count = 0;
    int timeout_sec = 3000;
    int prev_cmd = -1;
    bool process_working = false;
    QProcess *proc;
    QProcess *program;
    QSharedMemory shm_command;
    QSharedMemory shm_return;
    QSharedMemory shm_wifilist;

    Command get_command();
    Return get_return();
    WifiList get_wifilist();

    Command current_cmd;
    QList<Command> command_list;
    QTimer *timer;
    QTimer *timer500;
};

#endif // EXTPROCESS_H
