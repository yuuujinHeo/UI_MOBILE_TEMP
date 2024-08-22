#include "Supervisor.h"
#include <QQmlApplicationEngine>
#include <QKeyEvent>
#include <iostream>
#include <fstream>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <QQmlEngine>
#include <QTextCodec>
#include <stdio.h>
#include <QSslSocket>
#include <exception>
#include <QMediaPlaylist>
#include <QGuiApplication>
#include <zlib.h>
#include <libusb-1.0/libusb.h>
#include <QMediaPlayer>
#include <QDir>
#include <QProcess>
#include <QFileSystemWatcher>
#include <QtQuick/qquickimageprovider.h>
#include <QtGui>
#include <QStringList>

extern QObject *object;
ST_ROBOT *probot;
ST_MAP *pmap;
std::atomic<int> ui_state = {UI_STATE_NONE};
bool is_test_moving = false;
bool is_debug = false;
#define MAIN_THREAD 200

QString getIniPath(QString file)
{
    return QDir::homePath()+"/RB_MOBILE/config/" + file + "_config.ini";
}

QString getSettings(QString file, QString group, QString name)
{
    QString ini_path = getIniPath(file);
    QSettings setting_robot(ini_path, QSettings::IniFormat);
    setting_robot.beginGroup(group);
    return setting_robot.value(name).toString();
}

Supervisor::Supervisor(QObject *parent)
    : QObject(parent)
{
    plog->write("[SUPERVISOR] Program Started. Supervisor constructed.");

    checkShellFiles();
    Py_Initialize();

    QProcess kill_all_programs_process;
    QString file = QDir::homePath() + "/RB_MOBILE/sh/killall.sh";
    kill_all_programs_process.start(file, QStringList(), QProcess::ReadWrite);
    if(!kill_all_programs_process.waitForFinished())
    {
        plog->write("[SUPERVISOR] Kill All Failed");
    }
    else
    {
        plog->write("[SUPERVISOR] Kill All");
    }

    timer = new QTimer();
    connect(timer, SIGNAL(timeout()),this,SLOT(onTimer()));
    timer->start(MAIN_THREAD);

    voice_player = new QMediaPlayer();
    bgm_player = new QMediaPlayer();
    click_effect = new QSoundEffect();
    list_bgm = new QMediaPlaylist();

    mMain = nullptr;
    usb_list.clear();
    ui_state = UI_STATE_NONE;

    probot = &robot;
    pmap = &map;
    pmap->call_queue.clear();

    ipc = new IPCHandler();
    server = new ServerHandler();
    maph = new MapHandler();
    zip = new ZIPHandler();
    call = new CallbellHandler();
    tts = new TTSHandler();
    checker = new CMD_CHECKER();

    connect(checker, SIGNAL(sig_con_wifi_success(QString)), this, SLOT(connect_wifi_success(QString)));
    connect(checker, SIGNAL(sig_con_wifi_fail(int,QString)), this, SLOT(connect_wifi_fail(int,QString)));
    connect(checker, SIGNAL(sig_set_wifi_success(QString)), this, SLOT(set_wifi_success(QString)));
    connect(checker, SIGNAL(sig_set_wifi_fail(int,QString)), this, SLOT(set_wifi_fail(int,QString)));
    connect(checker, SIGNAL(sig_gitpull_success()), this, SLOT(git_pull_success()));
    connect(checker, SIGNAL(sig_gitpull_fail(int)), this, SLOT(git_pull_fail(int)));


    connect(call, SIGNAL(new_call()),this,SLOT(new_call()));
    connect(ipc, SIGNAL(pathchanged()),this,SLOT(path_changed()));
    connect(ipc, SIGNAL(mappingin()),this,SLOT(mapping_update()));
    connect(ipc, SIGNAL(mapreset()),this,SLOT(map_reset()));
    connect(ipc, SIGNAL(cameraupdate()),this,SLOT(camera_update()));
    connect(server, SIGNAL(updatefail()),this,SLOT(update_fail()));
    connect(server, SIGNAL(newCallOrder(QString)),this,SLOT(new_call_order(QString)));
    connect(tts, SIGNAL(ready_play(ST_VOICE)),this,SLOT(play_voice(ST_VOICE)));
    connect(server, SIGNAL(updatesuccess()),this,SLOT(update_success()));
    connect(ipc, SIGNAL(emo_changed()),this,SLOT(emo_state_changed()));
    connect(ipc, SIGNAL(get_message(QString)),this,SLOT(got_message(QString)));

    checkRobotINI();
    readSetting();
    startSLAM();

    //Test USB
    QFileSystemWatcher *FSwatcher;
    FSwatcher = new QFileSystemWatcher(this);
    std::string user = getenv("USER");
    std::string path = "/media/" + user;
    FSwatcher->addPath(path.c_str());
    connect(FSwatcher, SIGNAL(directoryChanged(QString)),this,SLOT(usb_detect()));
    usb_detect();

    translator = new QTranslator();
    setlanguage(getSetting("setting","UI","language"));

    checker->getNetworkState();

    initServingPage();
}

Supervisor::~Supervisor()
{
    plog->write("[BUILDER] SUPERVISOR desployed");
    ipc->clearSharedMemory(ipc->shm_cmd);
    Py_FinalizeEx();

    timer->disconnect();
    timer->deleteLater();

    voice_player->disconnect();
    bgm_player->disconnect();
    click_effect->disconnect();
    list_bgm->disconnect();

    voice_player->deleteLater();
    bgm_player->deleteLater();
    click_effect->deleteLater();
    list_bgm->deleteLater();

    translator->deleteLater();
    server->disconnect();
    tts->disconnect();
    checker->disconnect();

    server->deleteLater();
    tts->deleteLater();
    checker->deleteLater();

    ipc->disconnect();
    slam_process->disconnect();
    zip->disconnect();
    maph->disconnect();
    call->disconnect();

    ipc->deleteLater();
    slam_process->deleteLater();
    zip->deleteLater();
    maph->deleteLater();
    call->deleteLater();
    plog->write("[BUILDER] KILLED SLAMNAV");
}

void Supervisor::emo_state_changed()
{
    QString func_str = "[SUPERVISOR][emo_state_changed] ";
    plog->write(func_str + "start func. params()");

    if(!probot)
    {
        log_advanced(func_str + "Error: probot is null.");
        return;
    }

    if(probot->status_emo == 0)
    {
        playVoice("error_emo");
    }
}

////*********************************************  WINDOW 관련   ***************************************************////
void Supervisor::setWindow(QQuickWindow *Window)
{
    QString func_str = "[SUPERVISOR][setWindow] ";
    plog->write(func_str + "start func. params()");

    mMain = Window;
}

QQuickWindow *Supervisor::getWindow()
{
    QString func_str = "[SUPERVISOR][getWindow] ";
    plog->write(func_str + "start func. params()");

    if(mMain)
    {
        return mMain;
    }
    log_advanced(func_str + "Error: mMain is null.");
}

void Supervisor::setObject(QObject *object)
{
    mObject = object;
}

QObject *Supervisor::getObject()
{
    QString func_str = "[SUPERVISOR][getObject] ";
    plog->write(func_str + "start func. params()");

    if(mObject)
    {
        return mObject;
    }

    log_advanced(func_str + "Error: mObject is null.");
}

void Supervisor::got_message(QString msg)
{
    QString func_str = "[SUPERVISOR][got_message] ";
    plog->write(func_str + "start func. params(msg):"+ msg);

    QMetaObject::invokeMethod(mMain,
                              "new_message",
                              Qt::DirectConnection,
                              Q_ARG(QVariant,QVariant().fromValue(msg)));
}

////***********************96980101451808****************************////
void Supervisor::update_fail()
{
    QString func_str = "[SUPERVISOR][update_fail] ";
    plog->write(func_str + "start func. params()");

    if(!mMain)
    {
        log_advanced(func_str + "Error: mMain is null.");
        return;
    }

    QMetaObject::invokeMethod(mMain, "update_fail");
}

void Supervisor::update_success()
{
    QString func_str = "[SUPERVISOR][update_success] ";
    plog->write(func_str + "start func. params()");

    if(!mMain)
    {
        log_advanced(func_str + "Error: mMain is null.");
        return;
    }

    QMetaObject::invokeMethod(mMain, "update_success");
}

void Supervisor::programRestart()
{
    QString func_str = "[SUPERVISOR][programRestart] ";
    plog->write(func_str + "start func. params()");

    if(!ipc)
    {
        log_advanced(func_str + "Error: ipc is null.");
        return;
    }

    ipc->clearSharedMemory(ipc->shm_cmd);
    slam_process->kill();
    QCoreApplication::quit();

}

void Supervisor::programExit()
{
    QString func_str = "[SUPERVISOR][programExit] ";
    plog->write(func_str + "start func. params()");

    slam_process->kill();
    QCoreApplication::quit();
}

void Supervisor::writelog(QString msg)
{
    plog->write(msg);
}

void Supervisor::setCursorView(bool visible)
{
    QString func_str = "[SUPERVISOR][setCursorView] ";
    plog->write(func_str + "start func. params(visible):" + QString::number((int)visible));

    if(visible)
    {
        QGuiApplication::setOverrideCursor(QCursor(Qt::ArrowCursor));
    }
    else
    {
        QGuiApplication::setOverrideCursor(QCursor(Qt::BlankCursor));
    }
}

QString Supervisor::getRawMapPath(QString name)
{
    QString func_str = "[SUPERVISOR][getRawMapPath] ";
    plog->write(func_str + "start func. params(name):" + name);

    return QDir::homePath() + "/RB_MOBILE/maps/" + name + "/map_raw.png";
}

QString Supervisor::getMapPath(QString name)
{
    QString func_str = "[SUPERVISOR][getMapPath] ";
    plog->write(func_str + "start func. params(name):" + name);

    return QDir::homePath() + "/RB_MOBILE/maps/" + name + "/map_edited.png";
}

QString Supervisor::getAnnotPath(QString name)
{
    QString func_str = "[SUPERVISOR][getAnnotPath] ";
    plog->write(func_str + "start func. params(name):" + name);

    return QDir::homePath() + "/RB_MOBILE/maps/" + name + "/annotation.ini";
}

QString Supervisor::getMetaPath(QString name)
{
    QString func_str = "[SUPERVISOR][getMetaPath] ";
    plog->write(func_str + "start func. params(name):" + name);

    return QDir::homePath() + "/RB_MOBILE/maps/" + name + "/map_meta.ini";
}

QString Supervisor::getTravelPath(QString name)
{
    QString func_str = "[SUPERVISOR][getTravelPath] ";
    plog->write(func_str + "start func. params(name):" + name);

    return QDir::homePath() + "/RB_MOBILE/maps/" + name + "/map_travel_line.png";
}

QString Supervisor::getCostPath(QString name)
{
    QString func_str = "[SUPERVISOR][getCostPath] ";
    plog->write(func_str + "start func. params(name):" + name);

    return QDir::homePath() + "/RB_MOBILE/maps/" + name + "/map_cost.png";
}

////*********************************수정해야해*****************************************//
void Supervisor::loadMapServer()
{

}

void Supervisor::sendMapServer()
{

}

bool Supervisor::checkGroupName(QString name)
{
    QString func_str = "[SUPERVISOR][checkGroupName] ";
    plog->write(func_str + "start func. params(name):" + name);

    if(!pmap)
    {
        log_advanced(func_str + "Error: pmap is null.");
        return false;
    }

    for(const auto& group_name : pmap->location_groups)
    {
        if(group_name == name)
        {
            return false;
        }
    }

    return true;
}

bool Supervisor::checkLocationName(int group, QString name)
{
    QString func_str = "[SUPERVISOR][checkLocationName] ";
    plog->write(func_str + "start func. params(group,name):" + QString::number(group) + "," + name);

    if(!pmap)
    {
        log_advanced(func_str + "Error: pmap is null.");
        return false;
    }

    for(const auto& locations : pmap->serving_locations)
    {
        if(locations.group == group && locations.name == name)
        {
            return false;
        }
    }

    return true;
}

////*********************************************  CALLING 관련   ***************************************************////
void Supervisor::clear_call()
{
    QString func_str = "[SUPERVISOR][clear_call] ";
    plog->write(func_str + "start func. params()");

    if(!pmap)
    {
        log_advanced(func_str + "Error: pmap is null.");
        return;
    }

    const std::map<QString, QList<LOCATION>&> location_map =
    {
        {"Charging", pmap->charging_locations},
        {"Resting", pmap->resting_locations},
        {"Cleaning", pmap->cleaning_locations},
        {"Init", pmap->init_locations},
        {"Serving", pmap->serving_locations}
    };

    auto it = location_map.find(setting_call_type);
    if(it != location_map.end())
    {
        QList<LOCATION>& locations = it->second;

        if(setting_call_num < 0 || setting_call_num >= locations.size())
        {
            log_advanced(func_str + "Error: setting_call_num is out of bounds.");
            return;
        }

        plog->write(func_str + " clear call(type,num,loc_type,loc_num):" +
                    setting_call_type + "," +
                    QString::number(setting_call_num) + "," +
                    locations.at(setting_call_num).type + "," +
                    locations.at(setting_call_num).name);

        locations[setting_call_num].call_id = "";
    }
    else
    {
        if(setting_call_num < 0 || setting_call_num >= pmap->serving_locations.size())
        {
            log_advanced(func_str + "Error: setting_call_num is out of bounds.");
            return;
        }

        plog->write(func_str + " clear call(type,num,loc_type,loc_num):" +
                    setting_call_type + "," +
                    QString::number(setting_call_num) + "," +
                    pmap->serving_locations.at(setting_call_num).type + "," +
                    pmap->serving_locations.at(setting_call_num).name);

        pmap->serving_locations[setting_call_num].call_id = "";
    }

    setting_call_num = -1;
    setting_call_type = "";
    QMetaObject::invokeMethod(mMain, "call_setting");
}

void Supervisor::new_call_order(QString table)
{
    QString func_str = "[SUPERVISOR][new_call_order] ";
    plog->write(func_str + "start func. params(table):" + table);

    if(!pmap)
    {
        log_advanced(func_str + "Error: pmap is null.");
        return;
    }

    bool match_call = false;
    for(const auto& locations : pmap->serving_locations)
    {
        if(locations.name == table)
        {
            match_call = true;
            break;
        }
    }

    if(match_call)
    {
        pmap->call_queue.push_back(table);
        plog->write(func_str + "NEW CALL ORDER : " + table + " ( queue size " + QString::number(pmap->call_queue.size()) + " )");
    }
    else
    {
        plog->write(func_str + "NEW CALL ORDER : " + table + " (Wrong ID -> Ignored)");
    }
}

void Supervisor::new_call()
{
    QString func_str = "[SUPERVISOR][new_call] ";
    plog->write(func_str + "start func. params()");

    if(!pmap)
    {
        log_advanced(func_str + "Error: pmap is null.");
        return;
    }

    if(setting_call_num <= -1)
    {

        QList<LOCATION> loc_list;
        loc_list.append(pmap->charging_locations);
        loc_list.append(pmap->resting_locations);
        loc_list.append(pmap->cleaning_locations);
        loc_list.append(pmap->init_locations);
        loc_list.append(pmap->serving_locations);

        QString bell_id = call->get_bell_ID();
        QString name = "";

        bool match = false;
        for(const auto& locs : loc_list)
        {
            if(locs.call_id == bell_id)
            {
                name = locs.name;
                match = true;
                break;
            }
        }

        bool already_in = false;
        for(const auto& call_info : pmap->call_queue)
        {
            if(call_info == name)
            {
                already_in = true;
                plog->write(func_str + " already queue in : " + name + " (" + bell_id + ")");
                break;
            }
        }

        if(!already_in)
        {
            if(name != "")
            {
                pmap->call_queue.push_back(name);
                plog->write(func_str + "found callbell : " + name + " (" + bell_id + ")");
            }
            else
            {
                plog->write(func_str + "no found callbell (" + bell_id + ")");
            }
        }
    }
    else
    {
        const std::map<QString, QList<LOCATION>&> location_map =
        {
            {"Charging", pmap->charging_locations},
            {"Resting", pmap->resting_locations},
            {"Cleaning", pmap->cleaning_locations},
            {"Init", pmap->init_locations},
            {"Serving", pmap->serving_locations}
        };

        auto it = location_map.find(setting_call_type);
        if(it != location_map.end())
        {
            QList<LOCATION>& locations = it->second;
            if(setting_call_num < 0 || setting_call_num >= locations.size())
            {
                log_advanced(func_str + "Error: setting_call_num is out of bounds.");
                return;
            }

            QString bell_id = call->get_bell_ID();

            locations[setting_call_num].call_id = bell_id;
            plog->write(func_str + "SET CallBell " + locations.at(setting_call_num).name + " -> " + bell_id);
        }
        else
        {
            if(setting_call_num < 0 || setting_call_num >= pmap->serving_locations.size())
            {
                log_advanced(func_str + "Error: setting_call_num is out of bounds.");
                return;
            }

            QString bell_id = call->get_bell_ID();
            pmap->serving_locations[setting_call_num].call_id = bell_id;
            plog->write(func_str + "SET CallBell " + pmap->serving_locations[setting_call_num].name + " -> " + bell_id);
        }
    }
}

void Supervisor::setCallbellForce(QString type, bool onoff)
{
    QString func_str = "[SUPERVISOR][setCallbellForce] ";
    plog->write(func_str + "start func. params(type,onoff):" + type + "," + QString::number((int)onoff));

    if(type == "Resting")
    {
        if(onoff)
        {
            setSetting("setting","CALL/force_resting","true");
        }
        else
        {
            setSetting("setting","CALL/force_resting","false");
        }
    }
    else if(type == "Cleaning")
    {
        if(onoff)
        {
            setSetting("setting","CALL/force_cleaning","true");
        }
        else
        {
            setSetting("setting","CALL/force_cleaning","false");
        }
    }
}

void Supervisor::setCallbell(QString type, int id)
{
    QString func_str = "[SUPERVISOR][setCallbell] ";
    plog->write(func_str + "start func. params(type,id):" + type + "," + QString::number(id));

    setting_call_type = type;
    setting_call_num = id;
    plog->write(func_str + " set call bell(type,setting_call_num): " + type + " , " + QString::number(setting_call_num));
}

////*********************************************  SETTING 관련   ***************************************************////
void Supervisor::git_pull_success()
{
    QString func_str = "[SUPERVISOR][git_pull_success] ";
    plog->write(func_str + " Git Pull : Success -> Program Restart");

    try
    {
        programRestart();
    }
    catch(const std::exception &e)
    {
        log_advanced(func_str + "Exception occurred, err: "  + QString(e.what()));
    }
    catch(...)
    {
        log_advanced(func_str + "Exception occurred, err: unknown.");
    }
}

void Supervisor::git_pull_fail(int reason)
{
    QString func_str = "[SUPERVISOR][git_pull_fail] ";
    plog->write(func_str + "start func. params(reason):" + QString::number(reason));

    if(!mMain)
    {
        log_advanced(func_str + "Error: mMain is null.");
        return;
    }

    if(reason == NEED_RESET)
    {
        QMetaObject::invokeMethod(mMain, "git_pull_fail");
    }
    else if(reason == ALREADY_NEWEWST)
    {
        QMetaObject::invokeMethod(mMain, "git_pull_already");
    }
}

void Supervisor::playSound(QString name, int volume)
{
    QString func_str = "[SUPERVISOR][playSound] ";
    plog->write(func_str + "start func. params(name,volume):" + name + "," + QString::number(volume));

    if(!click_effect)
    {
        log_advanced(func_str + "Error: click_effect is null.");
        return;
    }

    if(volume < 0)
    {
        volume = getSetting("setting", "UI", "volume_button").toInt();
        if(volume < 0)
        {
            log_advanced(func_str + "Error: volume is out of bound.");
            return;
        }
    }

    click_effect->stop();
    if(name == "click")
    {
        click_effect->setSource(QUrl("qrc:/bgm/click.wav"));
    }
    else if(name == "no")
    {
        click_effect->setSource(QUrl("qrc:/bgm/click_error.wav"));
    }
    else if(name == "start")
    {
        click_effect->setSource(QUrl("qrc:/bgm/click_start.wav"));
    }

    click_effect->setVolume(float(volume)/100.0);
    click_effect->play();
}

//깃 최신버전인지.
bool Supervisor::isNewVersion()
{
    QString func_str = "[SUPERVISOR][isNewVersion] ";
    plog->write(func_str + "start func. params()");

    if(!server)
    {
        log_advanced(func_str + "Error: server is null.");
        return false;
    }

    return server->need_update();
}

//서버업데이트 필요한 지.
bool Supervisor::isNeedUpdate()
{
    QString func_str = "[SUPERVISOR][isNeedUpdate] ";
    plog->write(func_str + "start func. params()");

    if(!server)
    {
        log_advanced(func_str + "Error: server is null.");
        return false;
    }

    return server->new_update;
}

void Supervisor::refreshVersion()
{
    QString func_str = "[SUPERVISOR][refreshVersion] ";
    plog->write(func_str + "start func. params()");

    if(!server)
    {
        log_advanced(func_str + "Error: server is null.");
        return;
    }

    server->getCurVersion("MAIN_MOBILE");
    server->getNewVersion("MAIN_MOBILE");
    server->getNewVersions("MAIN_MOBILE");
}

QString Supervisor::getNewVersion()
{
    QString func_str = "[SUPERVISOR][getNewVersion] ";
    plog->write(func_str + "start func. params()");

    if(!server)
    {
        log_advanced(func_str + "Error: server is null.");
        return "";
    }

    return server->ui_version_new.version;
}

QString Supervisor::getCurVersion()
{
    QString func_str = "[SUPERVISOR][getCurVersion] ";
    plog->write(func_str + "start func. params()");

    if(!server)
    {
        log_advanced(func_str + "Error: server is null.");
        return "";
    }

    return server->ui_version.version;
}

QString Supervisor::getCurVersionDate()
{
    QString func_str = "[SUPERVISOR][getCurVersionDate] ";
    plog->write(func_str + "start func. params()");

    if(!server)
    {
        log_advanced(func_str + "Error: server is null.");
        return "";
    }

    return server->ui_version.date;
}

QString Supervisor::getLocalVersion()
{
    return getSetting("robot","VERSION","last_update_date");
}

QString Supervisor::getServerVersion()
{
    QString func_str = "[SUPERVISOR][getServerVersion] ";
    plog->write(func_str + "start func. params()");

    if(!server)
    {
        log_advanced(func_str + "Error: server is null.");
        return "NONE";
    }

    if(!probot)
    {
        log_advanced(func_str + "Error: probot is null.");
        return "NONE";
    }

    if(server->program_version != "")
    {
        return server->program_version;
    }
    else
    {
        if(probot->gitList.size() > 0)
        {
            return probot->gitList[0].date;
        }
        else
        {
            return "NONE";
        }
    }
}

QString Supervisor::getLocalVersionDate()
{
    return getSetting("robot", "VERSION", "last_update_date");
}

QString Supervisor::getLocalVersionMessage()
{
    QString func_str = "[SUPERVISOR][getLocalVersionMessage] ";
    plog->write(func_str + "start func. params()");

    if(!probot)
    {
        log_advanced(func_str + "Error: probot is null.");
        return "";
    }

    return probot->program_message;
}

QString Supervisor::getServerVersionMessage()
{
    QString func_str = "[SUPERVISOR][getServerVersionMessage] ";
    plog->write(func_str + "start func. params()");

    if(!probot)
    {
        log_advanced(func_str + "Error: probot is null.");
        return "";
    }

    if(probot->gitList.size() > 0)
    {
        return probot->gitList[0].message;
    }
    else
    {
        return "";
    }
}

QString Supervisor::getUpdateDate()
{
    QString func_str = "[SUPERVISOR][getUpdateDate] ";
    plog->write(func_str + "start func. params()");

    if(!server)
    {
        log_advanced(func_str + "Error: server is null.");
        return "";
    }

    return server->last_update_date;
}

int Supervisor::getUpdateSize()
{
    QString func_str = "[SUPERVISOR][getUpdateSize] ";
    plog->write(func_str + "start func. params()");

    if(!server)
    {
        log_advanced(func_str + "Error: server is null.");
        return 0;
    }

    return server->update_list.size();
}

QString Supervisor::getUpdateFileName(int num)
{
    QString func_str = "[SUPERVISOR][getUpdateFileName] ";
    plog->write(func_str + "start func. params(num):" + QString::number(num));

    if(!server)
    {
        log_advanced(func_str + "Error: server is null.");
        return 0;
    }

    QStringList list = server->update_list.keys();

    return list[num];
}

QString Supervisor::getUpdateCommit(QString name)
{
    QString func_str = "[SUPERVISOR][getUpdateCommit] ";
    plog->write(func_str + "start func. params(name):" + name);

    if(!server)
    {
        log_advanced(func_str + "Error: server is null.");
        return "";
    }

    return server->update_list[name].commit;
}

QString Supervisor::getUpdateMessage(QString name)
{
    QString func_str = "[SUPERVISOR][getUpdateMessage] ";
    plog->write(func_str + "start func. params(name):" + name);

    if(!server)
    {
        log_advanced(func_str + "Error: server is null.");
        return "";
    }

    return server->update_list[name].message;
}

QString Supervisor::getLastUpdateDate(QString name)
{
    QString func_str = "[SUPERVISOR][getLastUpdateDate] ";
    plog->write(func_str + "start func. params(name):" + name);

    if(!server)
    {
        log_advanced(func_str + "Error: server is null.");
        return "";
    }

    return server->version_list[name].date;
}

void Supervisor::checkCleaningLocation()
{

}

int Supervisor::getNewVersionsSize()
{
    QString func_str = "[SUPERVISOR][getNewVersionsSize] ";
    plog->write(func_str + "start func. params()");

    if(!server)
    {
        log_advanced(func_str + "Error: server is null.");
        return 0;
    }

    return server->ui_new_versions.size();
}

QString Supervisor::getNewVersion(int i)
{
    QString func_str = "[SUPERVISOR][getNewVersionsSize] ";
    plog->write(func_str + "start func. params(i):" + QString::number(i));

    if(!server)
    {
        log_advanced(func_str + "Error: server is null.");
        return "";
    }

    if(i < 0 || i >= server->ui_new_versions.size())
    {
        log_advanced(func_str + "Error: num is out of bounds.");
        return "";
    }

    return server->ui_new_versions[i].version;
}

QString Supervisor::getNewVersionDate(int i)
{
    QString func_str = "[SUPERVISOR][getNewVersionsSize] ";
    plog->write(func_str + "start func. params(i):" + QString::number(i));

    if(!server)
    {
        log_advanced(func_str + "Error: server is null.");
        return "";
    }

    if(i < 0 || i >= server->ui_new_versions.size())
    {
        log_advanced(func_str + "Error: num is out of bounds.");
        return "";
    }

    return server->ui_new_versions[i].date;
}

QString Supervisor::getNewVersionMessage(int i)
{
    QString func_str = "[SUPERVISOR][getNewVersionMessage] ";
    plog->write(func_str + "start func. params(i):" + QString::number(i));

    if(!server)
    {
        log_advanced(func_str + "Error: server is null.");
        return "";
    }

    if(i < 0 || i >= server->ui_new_versions.size())
    {
        log_advanced(func_str + "Error: num is out of bounds.");
        return "";
    }

    return server->ui_new_versions[i].message;
}

QString Supervisor::getCurrentCommit(QString name)
{
    QString func_str = "[SUPERVISOR][getCurrentCommit] ";
    plog->write(func_str + "start func. params(name):" + name);

    if(!server)
    {
        log_advanced(func_str + "Error: server is null.");
        return "";
    }

    return server->version_list[name].commit;
}

void Supervisor::updateProgram(QString _v)
{
    QString func_str = "[SUPERVISOR][updateProgram] ";
    plog->write(func_str + "start func. params(_v):" + _v);

    if(!server)
    {
        log_advanced(func_str + "Error: server is null.");
        return;
    }

    server->doUpdateUI(_v);
}

void Supervisor::updateProgram()
{
    QString func_str = "[SUPERVISOR][updateProgram] ";
    plog->write(func_str + "start func. params()");

    if(!server)
    {
        log_advanced(func_str + "Error: server is null.");
        return;
    }

    server->doUpdate();
}

void Supervisor::updateProgramGitPull()
{
    QString func_str = "[SUPERVISOR][updateProgramGitPull] ";
    plog->write(func_str + "start func. params()");

    if(!checker)
    {
        log_advanced(func_str + "Error: checker is null.");
        return;
    }

    checker->gitPull();
}

void Supervisor::gitReset()
{
    QString func_str = "[SUPERVISOR][gitReset] ";
    plog->write(func_str + "start func. params()");

    if(!probot)
    {
        log_advanced(func_str + "Error: probot is null.");
        return;
    }

    if(!checker)
    {
        log_advanced(func_str + "Error: checker is null.");
        return;
    }

    probot->program_branch = getSetting("setting","UI","program_branch");
    checker->gitReset();
}

void Supervisor::restartUpdate()
{
    QString func_str = "[SUPERVISOR][restartUpdate] ";
    plog->write(func_str + "start func. params()");

    setSetting("robot", "SERVER/update", "true");

    QString file = QDir::homePath()+"/RB_MOBILE/sh";
    QProcess *tempprocess = new QProcess(this);
    tempprocess->setWorkingDirectory(file);
    tempprocess->start("xterm", QStringList() << "./update.sh");
}

void Supervisor::startUpdate()
{

}

void Supervisor::checkVersionAgain()
{
    QString func_str = "[SUPERVISOR][checkVersionAgain] ";
    plog->write(func_str + "start func. params()");

    if(!server)
    {
        log_advanced(func_str + "Error: server is null.");
        return;
    }

    server->check_update = true;
    server->checkUpdate();
}

QString Supervisor::getGoqualID()
{
    QString func_str = "[SUPERVISOR][getGoqualID] ";
    plog->write(func_str + "start func. params()");

    if(!server)
    {
        log_advanced(func_str + "Error: server is null.");
        return "";
    }

    return server->goqual_login.id;
}

QString Supervisor::getGoqualPassword()
{
    QString func_str = "[SUPERVISOR][getGoqualPassword] ";
    plog->write(func_str + "start func. params()");

    if(!server)
    {
        log_advanced(func_str + "Error: server is null.");
        return "";
    }

    return server->goqual_login.passwd;
}

QString Supervisor::getGoqualClientID()
{
    QString func_str = "[SUPERVISOR][getGoqualClientID] ";
    plog->write(func_str + "start func. params()");

    if(!server)
    {
        log_advanced(func_str + "Error: server is null.");
        return "";
    }

    return server->goqual_login.client_id;
}

QString Supervisor::getGoqualClientSecret()
{
    QString func_str = "[SUPERVISOR][getGoqualClientSecret] ";
    plog->write(func_str + "start func. params()");

    if(!server)
    {
        log_advanced(func_str + "Error: server is null.");
        return "";
    }

    return server->goqual_login.client_secret;
}

QString Supervisor::getGoqualAccessKey()
{
    QString func_str = "[SUPERVISOR][getGoqualAccessKey] ";
    plog->write(func_str + "start func. params()");

    if(!server)
    {
        log_advanced(func_str + "Error: server is null.");
        return "";
    }

    return server->goqual_token.access_key;
}

QString Supervisor::getGoqualRefreshKey()
{
    QString func_str = "[SUPERVISOR][getGoqualRefreshKey] ";
    plog->write(func_str + "start func. params()");

    if(!server)
    {
        log_advanced(func_str + "Error: server is null.");
        return "";
    }

    return server->goqual_token.refresh_key;
}

QString Supervisor::getGoqualExpiresIn()
{
    QString func_str = "[SUPERVISOR][getGoqualExpiresIn] ";
    plog->write(func_str + "start func. params()");

    if(!server)
    {
        log_advanced(func_str + "Error: server is null.");
        return "";
    }

    return QString::number(server->goqual_token.expires_in);
}

void Supervisor::getGoqualKey()
{
    QString func_str = "[SUPERVISOR][getGoqualKey] ";
    plog->write(func_str + "start func. params()");

    if(!server)
    {
        log_advanced(func_str + "Error: server is null.");
        return;
    }

    server->getGoqualKey();
}

void Supervisor::refreshGoqualKey()
{
    QString func_str = "[SUPERVISOR][refreshGoqualKey] ";
    plog->write(func_str + "start func. params()");

    if(!server)
    {
        log_advanced(func_str + "Error: server is null.");
        return;
    }

    server->refreshGoqualKey();
}

void Supervisor::getGoqualDeviceList()
{
    QString func_str = "[SUPERVISOR][getGoqualDeviceList] ";
    plog->write(func_str + "start func. params()");

    if(!server)
    {
        log_advanced(func_str + "Error: server is null.");
        return;
    }

    server->getGoqualDevices();
}

void Supervisor::setGoqualDevice(QString id, bool onoff)
{
    QString func_str = "[SUPERVISOR][setGoqualDevice] ";
    plog->write(func_str + "start func. params(id,onoff):" + id + "," + QString::number(int(onoff)));

    if(!server)
    {
        log_advanced(func_str + "Error: server is null.");
        return;
    }

    server->setGoqualRelay(id,onoff);
}

int Supervisor::getGoqualDeviceSize()
{
    QString func_str = "[SUPERVISOR][getGoqualDeviceSize] ";
    plog->write(func_str + "start func. params()");

    if(!server)
    {
        log_advanced(func_str + "Error: server is null.");
        return 0;
    }

    return server->goqual_relays.size();
}

QString Supervisor::getGoqualDeviceID(int num)
{
    QString func_str = "[SUPERVISOR][getGoqualDeviceID] ";
    plog->write(func_str + "start func. params()");

    if(!server)
    {
        log_advanced(func_str + "Error: server is null.");
        return "";
    }

    QStringList key = server->goqual_relays.keys();
    if(num < 0 || num >= server->goqual_relays.size())
    {
        log_advanced(func_str + "Error: num is out of bounds.");
        return "";
    }

    return server->goqual_relays[key[num]].id;
}

QString Supervisor::getGoqualDeviceName(int num)
{
    QString func_str = "[SUPERVISOR][getGoqualDeviceName] ";
    plog->write(func_str + "start func. params(num):" + QString::number(num));

    if(!server)
    {
        log_advanced(func_str + "Error: server is null.");
        return "";
    }

    QStringList key = server->goqual_relays.keys();
    if(num < 0 || num >= server->goqual_relays.size())
    {
        log_advanced(func_str + "Error: num is out of bounds.");
        return "";
    }

    return server->goqual_relays[key[num]].name;
}

QString Supervisor::getGoqualDeviceType(int num)
{
    QString func_str = "[SUPERVISOR][getGoqualDeviceType] ";
    plog->write(func_str + "start func. params(num):" + QString::number(num));

    if(!server)
    {
        log_advanced(func_str + "Error: server is null.");
        return "";
    }

    QStringList key = server->goqual_relays.keys();
    if(num < 0 || num >= server->goqual_relays.size())
    {
        log_advanced(func_str + "Error: num is out of bounds.");
        return "";
    }

    return server->goqual_relays[key[num]].type;
}

bool Supervisor::getGoqualDeviceState(int num)
{
    QString func_str = "[SUPERVISOR][getGoqualDeviceState] ";
    plog->write(func_str + "start func. params(num):" + QString::number(num));

    if(!server)
    {
        log_advanced(func_str + "Error: server is null.");
        return false;
    }

    QStringList key = server->goqual_relays.keys();
    if(num < 0 || num >= server->goqual_relays.size())
    {
        log_advanced(func_str + "Error: num is out of bounds.");
        return false;
    }

    return server->goqual_relays[key[num]].state;
}

bool Supervisor::getGoqualDeviceOnline(int num)
{
    QString func_str = "[SUPERVISOR][getGoqualDeviceOnline] ";
    plog->write(func_str + "start func. params(num):" + QString::number(num));

    if(!server)
    {
        log_advanced(func_str + "Error: server is null.");
        return false;
    }

    QStringList key = server->goqual_relays.keys();
    if(num < 0 || num >= server->goqual_relays.size())
    {
        log_advanced(func_str + "Error: num is out of bounds.");
        return false;
    }

    return server->goqual_relays[key[num]].online;
}

void Supervisor::saveSetting()
{
    QString func_str = "[SUPERVISOR][saveSetting] ";
    plog->write(func_str + "start func. params()");

    struct config_file_path
    {
        QString original_path;
        QString backup_path;
        QString description;
    };

    QList<config_file_path> config_files =
    {
        {QDir::homePath() + "/RB_MOBILE/config/setting_config.ini", QDir::homePath() + "/RB_MOBILE/config/setting_config.backup", "setting_config"},
        {QDir::homePath() + "/RB_MOBILE/config/update_config.ini", QDir::homePath() + "/RB_MOBILE/config/update_config.backup", "update_config"},
        {QDir::homePath() + "/RB_MOBILE/config/static_config.ini", QDir::homePath() + "/RB_MOBILE/config/static_config.backup", "static_config"}
    };

    auto save_settings = [this](const QString& original_path, const QString& backup_path, const QString& description)
    {
        if (QFile::exists(original_path))
        {
            if (QFile::exists(backup_path))
            {
                QFile::remove(backup_path);
            }

            if (QFile::copy(original_path, backup_path))
            {
                plog->write("[SUPERVISOR][saveSetting] save: " + description + " -> success");
            }
            else
            {
                plog->write("[SUPERVISOR][saveSetting] save: " + description + " -> failed");
            }
        }
        else
        {
            plog->write("[SUPERVISOR][saveSetting] save: " + description + " -> no file found");
        }
    };

    for (const config_file_path& config : config_files)
    {
        save_settings(config.original_path, config.backup_path, config.description);
    }
}

void Supervisor::loadSetting()
{
    QString func_str = "[SUPERVISOR][loadSetting] ";
    plog->write(func_str + "start func. params()");

    QString setting_path = QDir::homePath()+"/RB_MOBILE/config/setting_config.ini";
    QString update_path = QDir::homePath()+"/RB_MOBILE/config/update_config.ini";
    QString static_path = QDir::homePath()+"/RB_MOBILE/config/static_config.ini";

    QString backup_setting_path = QDir::homePath()+"/RB_MOBILE/config/setting_config.backup";
    QString backup_update_path = QDir::homePath()+"/RB_MOBILE/config/update_config.backup";
    QString backup_static_path = QDir::homePath()+"/RB_MOBILE/config/static_config.backup";

    if(QFile::exists(backup_setting_path))
    {
        if(QFile::exists(setting_path))
        {
            QFile::remove(setting_path);
        }
        if(QFile::copy(backup_setting_path, setting_path))
        {
            plog->write("[COMMAND] loadSetting : setting_config -> success");
        }
        else
        {
            plog->write("[COMMAND] loadSetting : setting_config -> failed");
        }
    }
    else
    {
        plog->write("[COMMAND] loadSetting : setting_config -> no file found");
    }

    if(QFile::exists(backup_update_path))
    {
        if(QFile::exists(update_path))
        {
            QFile::remove(update_path);
        }
        if(QFile::copy(backup_update_path, update_path))
        {
            plog->write("[COMMAND] loadSetting : update_config -> success");
        }
        else
        {
            plog->write("[COMMAND] loadSetting : update_config -> failed");
        }
    }
    else
    {
        plog->write("[COMMAND] loadSetting : update_config -> no file found");
    }

    if(QFile::exists(backup_static_path))
    {
        if(QFile::exists(static_path))
        {
            QFile::remove(static_path);
        }
        if(QFile::copy(backup_static_path, static_path))
        {
            plog->write("[COMMAND] loadSetting : static_config -> success");
        }
        else
        {
            plog->write("[COMMAND] loadSetting : static_config -> failed");
        }
    }
    else
    {
        plog->write("[COMMAND] loadSetting : static_config -> no file found");
    }
}

void Supervisor::setSetting(QString file, QString name, QString value)
{
    QString func_str = "[SUPERVISOR][setSetting] ";
    plog->write(func_str + "start func. params(file,name,value):" + file + "," + name + "," + value);

    QString ini_path = getIniPath(file);
    QSettings setting(ini_path, QSettings::IniFormat);
    setting.setValue(name, value);
}

QString Supervisor::getSetting(QString file, QString group, QString name)
{
    QString func_str = "[SUPERVISOR][getSetting] ";
    plog->write(func_str + "start func. params(file,group,name):" + file + "," + group + "," + name);

    return getSettings(file,group,name);
}

void Supervisor::readSetting(QString map_name)
{
    QString func_str = "[SUPERVISOR][readSetting] ";
    plog->write(func_str + "start func. params(map_name):" + map_name);

    if(!pmap)
    {
        log_advanced(func_str + "Error: pmap is null.");
        return;
    }

    if(!probot)
    {
        log_advanced(func_str + "Error: probot is null.");
        return;
    }

    if(!server)
    {
        log_advanced(func_str + "Error: server is null.");
        return;
    }

    if(!maph)
    {
        log_advanced(func_str + "Error: maph is null.");
        return;
    }

    if(!mMain)
    {
        log_advanced(func_str + "Error: mMain is null.");
        return;
    }

    QString ini_path = getIniPath("setting");
    QSettings setting_config(ini_path, QSettings::IniFormat);

    setting_config.beginGroup("ROBOT_TYPE");
    probot->model = setting_config.value("model").toString();
    probot->serial_num = setting_config.value("serial_num").toInt();
    probot->name = probot->model;
    setting_config.endGroup();

    setting.tray_num = getSetting("setting","ROBOT_TYPE","tray_num").toInt();

    setting_config.beginGroup("CALL");
    probot->max_moving_count = setting_config.value("call_maximum").toInt();
    setting_config.endGroup();

#ifdef EXTPROC_TEST
#else
    setting_config.beginGroup("NETWORK");
    probot->wifi_ssid = setting_config.value("wifi_ssid").toInt();
    setting_config.endGroup();
#endif

    setting_config.beginGroup("MAP");
    pmap->map_name = setting_config.value("map_name").toString();
    pmap->map_path = setting_config.value("map_path").toString();
    setting_config.endGroup();

    probot->program_branch = getSetting("setting", "UI", "probram_branch");

    ini_path = getIniPath("static");
    QSettings static_config(ini_path, QSettings::IniFormat);
    static_config.beginGroup("ROBOT_HW");
    probot->radius = static_config.value("robot_radius").toFloat();
    pmap->robot_radius = probot->radius;
    static_config.endGroup();

    ini_path = getIniPath("robot");
    QSettings robot_config(ini_path, QSettings::IniFormat);
    robot_config.beginGroup("VERSION");
    server->last_update_date = robot_config.value("last_update_date").toString();
    server->last_update_mode = robot_config.value("last_update_mode").toString();
    robot_config.endGroup();

    //release 경로 내 파일 목록
    QDir dir_release = QDir(QDir::homePath() + "/RB_MOBILE/release");
    QList<QString> releases = dir_release.entryList();
    server->version_list.clear();
    for(int i=0; i<releases.size(); i++)
    {
        if(i >= server->version_list.size())
        {
            log_advanced(func_str + "Error: num is out of bounds. server->version_list mem crash.");
            continue;
        }

        ST_UPDATE temp_update;
        robot_config.beginGroup(releases[i]);
        temp_update.commit = robot_config.value("commit").toString();
        temp_update.message = robot_config.value("message").toString();
        temp_update.date = robot_config.value("last_update_date").toString();
        server->version_list[releases[i]] = temp_update;
        robot_config.endGroup();
    }

    ini_path = getIniPath("update");
    QSettings update_config(ini_path, QSettings::IniFormat);
    update_config.beginGroup("DRIVING");
    probot->cur_preset = update_config.value("cur_preset").toInt();
    probot->comeback_preset = update_config.value("comeback_preset").toInt();
    update_config.endGroup();

    if(map_name == "")
    {
        map_name = pmap->map_name;
    }

    pmap->annot_edit_location = false;
    pmap->annot_edit_tline = false;
    pmap->annot_edit_object = false;
    pmap->annot_edit_drawing = false;
    pmap->annotation_edited = false;

    //Map Meta Data======================================================================
    ini_path = getMetaPath(map_name);
    QSettings setting_meta(ini_path, QSettings::IniFormat);

    setting_meta.beginGroup("map_metadata");
    pmap->width = setting_meta.value("map_w").toInt();
    pmap->height = setting_meta.value("map_h").toInt();
    pmap->gridwidth = setting_meta.value("map_grid_width").toFloat();
    pmap->origin[0] = setting_meta.value("map_origin_u").toInt();
    pmap->origin[1] = setting_meta.value("map_origin_v").toInt();
    pmap->edited_width = setting_meta.value("map_edited_w").toInt();
    pmap->edited_height = setting_meta.value("map_edited_h").toInt();
    pmap->edited_origin[0] = setting_meta.value("map_edited_origin_u").toInt();
    pmap->edited_origin[1] = setting_meta.value("map_edited_origin_v").toInt();
    if(pmap->edited_width > 0)
    {
        pmap->width = pmap->edited_width;
        pmap->height = pmap->edited_height;
        pmap->origin[0] = pmap->edited_origin[0];
        pmap->origin[1] = pmap->edited_origin[1];
    }
    setting_meta.endGroup();

    //Annotation======================================================================
    ini_path = getAnnotPath(map_name);
    QSettings setting_anot(ini_path, QSettings::IniFormat);

    QFileInfo annot_info(ini_path);
    QDateTime lastModified = annot_info.lastModified();
    pmap->annot_modified_date = lastModified.toString("yyyy-MM-dd hh:mm:ss");

    pmap->charging_locations.clear();
    pmap->resting_locations.clear();
    pmap->cleaning_locations.clear();
    pmap->init_locations.clear();
    pmap->serving_locations.clear();

    setting_anot.beginGroup("charging_locations");
    int charging_loc_num = setting_anot.value("num").toInt();
    for(int i=0; i<charging_loc_num; i++)
    {
        LOCATION temp_loc;
        QString loc_str = setting_anot.value("loc" + QString::number(i)).toString();
        QStringList strlist = loc_str.split(",");
        if(strlist.size() < 4)
        {
            continue;
        }

        QString name = strlist[0];
        float x = strlist[1].toFloat();
        float y = strlist[2].toFloat();
        float th = strlist[3].toFloat();

        temp_loc.point = cv::Point2f(x,y);
        temp_loc.angle = th;
        temp_loc.group = 0;
        temp_loc.group_name = "Charging";
        temp_loc.type = "Charging";
        temp_loc.name = name;

        if(strlist.size() >= 5)
        {
            temp_loc.call_id = "";
            temp_loc.ling_id = "";
            pmap->charging_locations.push_back(temp_loc);
            continue;
        }

        QStringList bell_info_list = strlist[4].split(":");
        if(bell_info_list.size() == 1)
        {
            temp_loc.call_id = bell_info_list.value(0, "");
        }
        else if(bell_info_list.size() == 2)
        {
            temp_loc.call_id = bell_info_list.value(0, "");
            temp_loc.ling_id = bell_info_list.value(1, "");
        }
        else
        {
            temp_loc.ling_id = "";
        }

        pmap->charging_locations.push_back(temp_loc);
    }
    setting_anot.endGroup();

    setting_anot.beginGroup("resting_locations");
    int resting_loc_num = setting_anot.value("num").toInt();
    for(int i=0; i<resting_loc_num; i++)
    {
        LOCATION temp_loc;
        QString loc_str = setting_anot.value("loc" + QString::number(i)).toString();
        QStringList strlist = loc_str.split(",");
        if(strlist.size() < 4)
        {
            continue;
        }

        QString name = strlist[0];
        float x = strlist[1].toFloat();
        float y = strlist[2].toFloat();
        float th = strlist[3].toFloat();

        temp_loc.point = cv::Point2f(x,y);
        temp_loc.angle = th;
        temp_loc.group = 0;
        temp_loc.group_name = "Resting";
        temp_loc.type = "Resting";
        temp_loc.name = name;

        if(strlist.size() >= 5)
        {
            temp_loc.call_id = "";
            temp_loc.ling_id = "";
            pmap->resting_locations.push_back(temp_loc);
            continue;
        }

        QStringList bell_info_list = strlist[4].split(":");
        if(bell_info_list.size() == 1)
        {
            temp_loc.call_id = bell_info_list.value(0, "");
        }
        else if(bell_info_list.size() == 2)
        {
            temp_loc.call_id = bell_info_list.value(0, "");
            temp_loc.ling_id = bell_info_list.value(1, "");
        }
        else
        {
            temp_loc.ling_id = "";
        }

        pmap->resting_locations.push_back(temp_loc);
    }
    setting_anot.endGroup();


    setting_anot.beginGroup("cleaning_locations");
    int cleaning_loc_num = setting_anot.value("num").toInt();
    for(int i=0; i<cleaning_loc_num; i++)
    {
        LOCATION temp_loc;
        QString loc_str = setting_anot.value("loc" + QString::number(i)).toString();
        QStringList strlist = loc_str.split(",");
        if(strlist.size() < 4)
        {
            continue;
        }

        QString name = strlist[0];
        float x = strlist[1].toFloat();
        float y = strlist[2].toFloat();
        float th = strlist[3].toFloat();

        temp_loc.point = cv::Point2f(x,y);
        temp_loc.angle = th;
        temp_loc.group = 0;
        temp_loc.group_name = "Cleaning";
        temp_loc.type = "Cleaning";
        temp_loc.name = name;

        if(strlist.size() >= 5)
        {
            temp_loc.call_id = "";
            temp_loc.ling_id = "";
            pmap->cleaning_locations.push_back(temp_loc);
            continue;
        }

        QStringList bell_info_list = strlist[4].split(":");
        if(bell_info_list.size() == 1)
        {
            temp_loc.call_id = bell_info_list.value(0, "");
        }
        else if(bell_info_list.size() == 2)
        {
            temp_loc.call_id = bell_info_list.value(0, "");
            temp_loc.ling_id = bell_info_list.value(1, "");
        }
        else
        {
            temp_loc.ling_id = "";
        }

        pmap->cleaning_locations.push_back(temp_loc);
    }
    setting_anot.endGroup();

    setting_anot.beginGroup("init_locations");
    int init_loc_num = setting_anot.value("num").toInt();
    for(int i=0; i<init_loc_num; i++)
    {
        LOCATION temp_loc;
        QString loc_str = setting_anot.value("loc" + QString::number(i)).toString();
        QStringList strlist = loc_str.split(",");
        if(strlist.size() < 4)
        {
            continue;
        }

        QString name = strlist[0];
        float x = strlist[1].toFloat();
        float y = strlist[2].toFloat();
        float th = strlist[3].toFloat();

        temp_loc.point = cv::Point2f(x,y);
        temp_loc.angle = th;
        temp_loc.group = 0;
        temp_loc.group_name = "Init";
        temp_loc.type = "Init";
        temp_loc.name = name;

        if(strlist.size() >= 5)
        {
            temp_loc.call_id = "";
            temp_loc.ling_id = "";
            pmap->init_locations.push_back(temp_loc);
            continue;
        }

        QStringList bell_info_list = strlist[4].split(":");
        if(bell_info_list.size() == 1)
        {
            temp_loc.call_id = bell_info_list.value(0, "");
        }
        else if(bell_info_list.size() == 2)
        {
            temp_loc.call_id = bell_info_list.value(0, "");
            temp_loc.ling_id = bell_info_list.value(1, "");
        }
        else
        {
            temp_loc.ling_id = "";
        }

        pmap->init_locations.push_back(temp_loc);
    }
    setting_anot.endGroup();

    pmap->location_groups.clear();
    setting_anot.beginGroup("serving_locations");
    int total_serv_num = 0;
    int group_num = setting_anot.value("group", 0).toInt();
    setting_anot.endGroup();
    for(int i=0; i<group_num; i++)
    {
        setting_anot.beginGroup("serving_" + QString::number(i));
        int serv_num = setting_anot.value("num").toInt();
        total_serv_num +=serv_num;

        QString group_name = setting_anot.value("name").toString();
        pmap->location_groups.append(group_name);

        for(int j=0; j<serv_num; j++)
        {
            LOCATION temp_loc;
            QString loc_str = setting_anot.value("loc" + QString::number(j)).toString();
            QStringList strlist = loc_str.split(",");
            if(strlist.size() < 4)
            {
                continue;
            }

            QString name = strlist[0];
            float x = strlist[1].toFloat();
            float y = strlist[2].toFloat();
            float th = strlist[3].toFloat();

            temp_loc.point = cv::Point2f(x,y);
            temp_loc.angle = th;
            temp_loc.type = "Serving";
            temp_loc.name = name;
            temp_loc.group_name = pmap->location_groups[i];

            if(strlist.size() >= 5)
            {
                temp_loc.group = i;
                temp_loc.call_id = "";
                temp_loc.ling_id = "";
                pmap->serving_locations.push_back(temp_loc);
                continue;
            }

            QStringList bell_info_list = strlist[4].split(":");
            if(bell_info_list.size() == 1)
            {
                temp_loc.call_id = bell_info_list.value(0, "");
            }
            else if(bell_info_list.size() == 2)
            {
                temp_loc.call_id = bell_info_list.value(0, "");
                temp_loc.ling_id = bell_info_list.value(1, "");
            }
            else
            {
                temp_loc.ling_id = "";
            }

            temp_loc.group = i;
            pmap->serving_locations.push_back(temp_loc);
        }
        setting_anot.endGroup();
    }

    tts->readVoiceSetting();

    //Set Variable
    probot->trays.clear();
    for(int i=0; i<setting.tray_num; i++)
    {
        ST_TRAY temp;
        probot->trays.push_back(temp);
    }

    maph->loadFile(map_name, "");
    QMetaObject::invokeMethod(mMain, "update_ini");

    plog->write(func_str + "READ SETTING : annot done");
}

QString Supervisor::makeLingbell()
{
    QString func_str = "[SUPERVISOR][makeLingbell] ";
    plog->write(func_str + "start func. params()");

    int maxnum = 1;
    for(int i=0; i<pmap->charging_locations.size(); i++)
    {
        if(pmap->charging_locations[i].ling_id.right(7).toInt() >= maxnum)
        {
            maxnum = pmap->charging_locations[i].ling_id.right(7).toInt();
        }
    }
    for(int i=0; i<pmap->resting_locations.size(); i++)
    {
        if(pmap->resting_locations[i].ling_id.right(7).toInt() >= maxnum)
        {
            maxnum = pmap->resting_locations[i].ling_id.right(7).toInt();
        }
    }
    for(int i=0; i<pmap->cleaning_locations.size(); i++)
    {
        if(pmap->cleaning_locations[i].ling_id.right(7).toInt() >= maxnum)
        {
            maxnum = pmap->cleaning_locations[i].ling_id.right(7).toInt();
        }
    }
    for(int i=0; i<pmap->init_locations.size(); i++)
    {
        if(pmap->init_locations[i].ling_id.right(7).toInt() >= maxnum)
        {
            maxnum = pmap->init_locations[i].ling_id.right(7).toInt();
        }
    }
    for(int i=0; i<pmap->serving_locations.size(); i++)
    {
        if(pmap->serving_locations[i].ling_id.right(7).toInt() >= maxnum)
        {
            maxnum = pmap->serving_locations[i].ling_id.right(7).toInt();
        }
    }

    return "F"+QString::asprintf("%07d",maxnum+1);
}
void Supervisor::resetLingbell(int id)
{
    QString func_str = "[SUPERVISOR][resetLingbell] ";
    plog->write(func_str + "start func. params(id):" + QString::number(id));

    if(id < 0 || id > pmap->serving_locations.size())
    {
        log_advanced(func_str + "Error: id is out of bounds.");
        return;
    }

    pmap->serving_locations[id].ling_id = "";
}

void Supervisor::editLocation(QString type, int num)
{
    QString func_str = "[SUPERVISOR][editLocation] ";
    plog->write(func_str + "start func. params(type,num):" + type + "," + QString::number(num));

    if(!maph)
    {
        log_advanced(func_str + "Error: maph is null.");
        return;
    }

    if(!pmap)
    {
        log_advanced(func_str + "Error: pmap is null.");
        return;
    }

    if(!probot)
    {
        log_advanced(func_str + "Error: probot is null.");
        return;
    }

    LOCATION temp;
    if(maph->select_charging>-1)
    {
        temp = pmap->charging_locations[maph->select_charging];
        pmap->charging_locations[maph->select_charging].point = probot->lastPose.point;
        pmap->charging_locations[maph->select_charging].angle = probot->lastPose.angle;
    }
    else if(maph->select_resting>-1)
    {
        temp = pmap->resting_locations[maph->select_resting];
        pmap->resting_locations[maph->select_resting].point = probot->lastPose.point;
        pmap->resting_locations[maph->select_resting].angle = probot->lastPose.angle;
    }
    else if(maph->select_cleaning>-1)
    {
        temp = pmap->cleaning_locations[maph->select_cleaning];
        pmap->cleaning_locations[maph->select_cleaning].point = probot->lastPose.point;
        pmap->cleaning_locations[maph->select_cleaning].angle = probot->lastPose.angle;
    }
    else if(maph->select_init>-1)
    {
        temp = pmap->init_locations[maph->select_init];
        pmap->init_locations[maph->select_init].point = probot->lastPose.point;
        pmap->init_locations[maph->select_init].angle = probot->lastPose.angle;
    }
    else if(maph->select_serving>-1)
    {
        temp = pmap->serving_locations[maph->select_serving];
        pmap->serving_locations[maph->select_serving].point = probot->lastPose.point;
        pmap->serving_locations[maph->select_serving].angle = probot->lastPose.angle;
    }

    plog->write(func_str + "Edit Location " + QString::number(num) + " : " + QString().asprintf("(%f,%f,%f) -> (%f,%f,%f)",
                                                                                            temp.point.x,temp.point.y,temp.angle,
                                                                                            probot->lastPose.point.x,probot->lastPose.point.y,probot->lastPose.angle));
}

void Supervisor::map_reset()
{
    QString func_str = "[SUPERVISOR][map_reset] ";
    plog->write(func_str + "start func. params()");

    if(!maph)
    {
        log_advanced(func_str + "Error: maph is null.");
        return;
    }

    maph->setMapLayer();
}

void Supervisor::setSystemVolume(int volume)
{
    QString func_str = "[SUPERVISOR][map_reset] ";
    plog->write(func_str + "start func. params(volume):" + QString::number(volume));

    if(!checker)
    {
        log_advanced(func_str + "Error: checker is null.");
        return;
    }

    checker->setSystemVolume(volume);
}

void Supervisor::saveLocation(QString type, int groupnum, QString name)
{
    QString func_str = "[SUPERVISOR][saveLocation] ";
    plog->write(func_str + "start func. params(type,groupnum,name):" + type + "," + QString::number(groupnum) + "," + name);

    if(!pmap)
    {
        log_advanced(func_str + "Error: pmap is null.");
        return;
    }

    if(!maph)
    {
        log_advanced(func_str + "Error: maph is null.");
        return;
    }

    LOCATION temp;
    temp.type = type;
    temp.name = name;
    temp.group = groupnum;
    temp.call_id = "";
    temp.point = setAxisBack(maph->new_location.point);
    temp.angle = setAxisBack(maph->new_location.angle);

    if(pmap->location_groups.size() == 0)
    {
        pmap->location_groups.push_back("Default");
    }

    if(groupnum < pmap->location_groups.size())
    {
        temp.group_name = pmap->location_groups[groupnum];
    }

    const std::map<QString, QList<LOCATION>&> location_map =
    {
        {"Charging", pmap->charging_locations},
        {"Resting", pmap->resting_locations},
        {"Cleaning", pmap->cleaning_locations},
        {"Init", pmap->init_locations},
        {"Serving", pmap->serving_locations}
    };

    auto it = location_map.find(type);
    if(it != location_map.end())
    {
        QList<LOCATION>& location = it->second;

        if(type != "Serving" && type != "Init" && location.size() > 0)
        {
            pmap->charging_locations[0] = temp;
            plog->write(func_str + "saveLocation(Overwrite): " + type + "," + name + "," + QString().asprintf("%f,%f,%f", temp.point.x, temp.point.y, temp.angle));
        }
        else
        {
            location.push_back(temp);
            plog->write(func_str + "saveLocation: " + type + "," + name + "," + QString().asprintf("%f,%f,%f", temp.point.x, temp.point.y, temp.angle));
        }

    }

    pmap->annot_edit_location = true;
    saveAnnotation(maph->map_name, false);
}

////*********************************************  OBJECTING 관련   ***************************************************////
void Supervisor::addObject(int x, int y)
{
    QString func_str = "[SUPERVISOR][addObject] ";
    plog->write(func_str + "start func. params(x,y):" + QString::number(x) + "," + QString::number(y));

    if(!maph)
    {
        log_advanced(func_str + "Error: maph is null.");
        return;
    }

    maph->addObject(x,y);
}

void Supervisor::addObjectPoint(int x, int y)
{
    QString func_str = "[SUPERVISOR][addObjectPoint] ";
    plog->write(func_str + "start func. params(x,y):" + QString::number(x) + "," + QString::number(y));

    if(!maph)
    {
        log_advanced(func_str + "Error: maph is null.");
        return;
    }

    maph->addObjectPoint(x,y);
}

void Supervisor::setObject(int x, int y)
{
    QString func_str = "[SUPERVISOR][setObject] ";
    plog->write(func_str + "start func. params(x,y):" + QString::number(x) + "," + QString::number(y));

    if(!maph)
    {
        log_advanced(func_str + "Error: maph is null.");
        return;
    }

    maph->setObject(x,y);
}

void Supervisor::editObjectStart(int x, int y)
{
    QString func_str = "[SUPERVISOR][editObjectStart] ";
    plog->write(func_str + "start func. params(x,y):" + QString::number(x) + "," + QString::number(y));

    if(!maph)
    {
        log_advanced(func_str + "Error: maph is null.");
        return;
    }

    maph->editObjectStart(x,y);
}

void Supervisor::editObject(int x, int y)
{
    QString func_str = "[SUPERVISOR][editObject] ";
    plog->write(func_str + "start func. params(x,y):" + QString::number(x) + "," + QString::number(y));

    if(!maph)
    {
        log_advanced(func_str + "Error: maph is null.");
        return;
    }

    maph->editObject(x,y);
}

void Supervisor::saveObject()
{
    QString func_str = "[SUPERVISOR][saveObject] ";
    plog->write(func_str + "start func. params()");

    if(!maph)
    {
        log_advanced(func_str + "Error: maph is null.");
        return;
    }

    maph->saveObject();
    maph->setObjPose();
}

void Supervisor::clearObject()
{
    QString func_str = "[SUPERVISOR][clearObject] ";
    plog->write(func_str + "start func. params()");

    if(!maph)
    {
        log_advanced(func_str + "Error: maph is null.");
        return;
    }

    maph->clearObject();
}

void Supervisor::clearObjectAll()
{
    QString func_str = "[SUPERVISOR][clearObjectAll] ";
    plog->write(func_str + "start func. params()");

    if(!maph)
    {
        log_advanced(func_str + "Error: maph is null.");
        return;
    }

    maph->clearObjectAll();
}

int Supervisor::getObjectNum(int x, int y)
{
    QString func_str = "[SUPERVISOR][getObjectNum] ";
    plog->write(func_str + "start func. params(x,y):" + QString::number(x) + "," + QString::number(y));

    if(!maph)
    {
        log_advanced(func_str + "Error: maph is null.");
        return 0;
    }

    return maph->getObjectNum(x,y);
}

int Supervisor::getObjectPointNum(int x, int y)
{
    QString func_str = "[SUPERVISOR][getObjectNum] ";
    plog->write(func_str + "start func. params(x,y):" + QString::number(x) + "," + QString::number(y));

    if(!maph)
    {
        log_advanced(func_str + "Error: maph is null.");
        return 0;
    }

    return maph->getObjectPointNum(x,y);
}

void Supervisor::selectObject(int num)
{
    QString func_str = "[SUPERVISOR][selectObject] ";
    plog->write(func_str + "start func. params(num):" + QString::number(num));

    if(!maph)
    {
        log_advanced(func_str + "Error: maph is null.");
        return;
    }

    maph->selectObject(num);
}

bool Supervisor::getObjectflag()
{
    QString func_str = "[SUPERVISOR][getObjectflag] ";
    plog->write(func_str + "start func. params()");

    if(!ipc)
    {
        log_advanced(func_str + "Error: ipc is null.");
        return false;
    }

    if(!maph)
    {
        log_advanced(func_str + "Error: maph is null.");
        return false;
    }

    return (ipc->flag_objecting||maph->getObjectFlag());
}

void Supervisor::undoObject()
{
    QString func_str = "[SUPERVISOR][undoObject] ";
    plog->write(func_str + "start func. params()");

    if(!maph)
    {
        log_advanced(func_str + "Error: maph is null.");
        return;
    }

    maph->undoObject();
}

//-------------------------------------------------- DB ------------------------------------------------//
void Supervisor::setTableColNum(int col_num)
{
    QString func_str = "[SUPERVISOR][setTableColNum] ";
    plog->write(func_str + "start func. params(col_num):" + QString::number(col_num));

    setSetting("setting", "UI/table_col_num", QString::number(col_num));
    readSetting();
}

int Supervisor::getTrayNum()
{
    QString func_str = "[SUPERVISOR][getTrayNum] ";
    plog->write(func_str + "start func. params()");

    return setting.tray_num;
}

QString Supervisor::getRobotType()
{
    QString func_str = "[SUPERVISOR][getRobotType] ";
    plog->write(func_str + "start func. params()");

    return getSetting("setting","ROBOT_TYPE","type");
}

void Supervisor::setCamera(QString left, QString right)
{
    QString func_str = "[SUPERVISOR][setCamera] ";
    plog->write(func_str + "start func. params(left,right):" + left + "," + right);

    setSetting("static", "SENSOR/left_camera_serial", left);
    setSetting("static", "SENSOR/right_camera_serial", right);
}

QString Supervisor::getLeftCamera()
{
    QString func_str = "[SUPERVISOR][getLeftCamera] ";
    plog->write(func_str + "start func. params()");

    return getSetting("static","SENSOR","left_camera_serial");
}

QString Supervisor::getRightCamera()
{
    QString func_str = "[SUPERVISOR][getRightCamera] ";
    plog->write(func_str + "start func. params()");

    return getSetting("static","SENSOR","right_camera_serial");
}

int Supervisor::getCameraNum()
{
    QString func_str = "[SUPERVISOR][getCameraNum] ";
    plog->write(func_str + "start func. params()");

    if(!pmap)
    {
        log_advanced(func_str + "Error: pmap is null.");
        return 0;
    }

    return pmap->camera_info.size();
}

int Supervisor::getRunawayState()
{
    QString func_str = "[SUPERVISOR][getRunawayState] ";
    plog->write(func_str + "start func. params()");

    if(!probot)
    {
        log_advanced(func_str + "Error: probot is null.");
        return 0;
    }

    return probot->drawing_state;
}

QString Supervisor::getCameraSerial(int num)
{
    QString func_str = "[SUPERVISOR][getCameraSerial] ";
    plog->write(func_str + "start func. params(num):" + QString::number(num));

    if(!pmap)
    {
        log_advanced(func_str + "Error: pmap is null.");
        return "";
    }

    if(num < 0 || num >= pmap->camera_info.size())
    {
        log_advanced(func_str + "Error: num is out of bounds.");
        return "";
    }

    return pmap->camera_info[num].serial;
}

//------------------------------------------------- SLAM COMMAND --------------------------------------//
void Supervisor::requestCamera()
{
    QString func_str = "[SUPERVISOR][requestCamera] ";
    plog->write(func_str + "start func. params()");

    if(!ipc)
    {
        log_advanced(func_str + "Error: ipc is null.");
        return;
    }

    IPCHandler::CMD send_msg;
    send_msg.cmd = ROBOT_CMD_REQ_CAMERA;
    ipc->set_cmd(send_msg);
}

void Supervisor::drawingRunawayStart()
{
    QString func_str = "[SUPERVISOR][drawingRunawayStart] ";
    plog->write(func_str + "start func. params()");

    if(!maph)
    {
        log_advanced(func_str + "Error: maph is null.");
        return;
    }

    if(!ipc)
    {
        log_advanced(func_str + "Error: ipc is null.");
        return;
    }

    maph->startDrawingTline();
    IPCHandler::CMD send_msg;
    send_msg.cmd = ROBOT_CMD_DRAW_LINE_START;
    ipc->set_cmd(send_msg);
}

void Supervisor::drawingRunawayStop()
{
    maph->stopDrawingTline();
    IPCHandler::CMD send_msg;
    send_msg.cmd = ROBOT_CMD_DRAW_LINE_SAVE;
    ipc->set_cmd(send_msg);
}

void Supervisor::slam_map_reload(QString filename, int mode)
{
    IPCHandler::CMD send_msg;
    if(mode == HARD_RELOAD)
    {
        send_msg.cmd = ROBOT_CMD_MAP_RELOAD;
        memcpy(send_msg.params, filename.toUtf8(), sizeof(char)*255);
        ipc->set_cmd(send_msg, "MAP HARD RELOAD");

        probot->localization_state = 0;
        probot->motor[0].status = 0;
        probot->motor[1].status = 0;
        probot->localization_confirm = false;
    }
    else
    {
        send_msg.cmd = ROBOT_CMD_MAP_SOFT_RELOAD;
        memcpy(send_msg.params, filename.toUtf8(), sizeof(char)*255);
        ipc->set_cmd(send_msg,"MAP SOFT RELOAD");
    }
}

void Supervisor::slam_ini_reload()
{
    IPCHandler::CMD send_msg;
    send_msg.cmd = ROBOT_CMD_SETTING_RELOAD;
    ipc->set_cmd(send_msg,"INI RELOAD");
}

////*********************************************  INIT PAGE 관련   ***************************************************////
bool Supervisor::isConnectServer()
{
    return server->connection && server->first_response;
}

void Supervisor::deleteEditedMap()
{
    plog->write("[USER INPUT] Remove Edited Map Data");
    QFile *file = new QFile(QDir::homePath()+"/RB_MOBILE/maps/"+pmap->map_name+"/map_edited.png");
    file->remove();

    QString path = QDir::homePath() + "/RB_MOBILE/maps/"+ pmap->map_name + "/map_meta.ini";
    QSettings setting(path, QSettings::IniFormat);

    setting.setValue("map_metadata/map_edited_angle","");
    setting.setValue("map_metadata/map_edited_w","");
    setting.setValue("map_metadata/map_edited_h","");
    setting.setValue("map_metadata/map_edited_origin_u","");
    setting.setValue("map_metadata/map_edited_origin_v","");
    setting.setValue("map_metadata/map_edited_cut_u","");
    setting.setValue("map_metadata/map_edited_cut_v","");

    readSetting(pmap->map_name);
    slam_map_reload(pmap->map_name);
}

void Supervisor::deleteAnnotation()
{
    plog->write("[USER INPUT] Remove Annotation Data");

    pmap->charging_locations.clear();
    pmap->resting_locations.clear();
    pmap->cleaning_locations.clear();
    pmap->init_locations.clear();
    pmap->serving_locations.clear();
    QFile *file = new QFile(QDir::homePath()+"/RB_MOBILE/maps/"+pmap->map_name+"/map_travel_line.png");
    file->remove();
    QFile *file2 = new QFile(QDir::homePath()+"/RB_MOBILE/maps/"+pmap->map_name+"/map_velocity.png");
    file2->remove();

    file->deleteLater();
    file2->deleteLater();
    saveAnnotation(pmap->map_name);
}

bool Supervisor::isAvailableAnnotation()
{
    if(QFile::exists(getAnnotPath(pmap->map_name)))
    {
        if(getLocationNum("Charging")>0 && getLocationNum("Resting")>0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool Supervisor::isExistAnnotation(QString name)
{
    QString file_meta = getMetaPath(name);
    QString file_annot = getAnnotPath(name);

    return QFile::exists(file_annot);
}

bool Supervisor::isExistTravelMap(QString name)
{
    QString file = getTravelPath(name);
    return QFile::exists(file);
}

int Supervisor::getAvailableMap()
{
    std::string path = QString(QDir::homePath()+"/RB_MOBILE/maps").toStdString();
    QDir directory(path.c_str());
    QStringList FileList = directory.entryList();
    map_list.clear();
    for(int i=0; i<FileList.size(); i++)
    {
        if(FileList[i] == "." || FileList[i] == "..")
        {
            continue;
        }

        QString path3 = QDir::homePath() + "/RB_MOBILE/maps/"+FileList[i];
        QFileInfo info(path3);
        if(!info.isDir())
        {
            continue;
        }

        std::string path2 = QString(QDir::homePath()+"/RB_MOBILE/maps/"+FileList[i]).toStdString();
        QDir direc2(path2.c_str());
        QStringList detailList = direc2.entryList();
        bool available = false;
        for(int j=0; j<detailList.size(); j++)
        {
            if(detailList[j].left(4) == "map_")
            {
                available = true;
                break;
            }
        }

        if(available)
        {
            map_list.push_back(FileList[i]);
        }
    }

    return map_list.size();
}

QString Supervisor::getAvailableMapPath(int num)
{
    if(num>-1 && num<map_list.size())
    {
        return map_list[num];
    }
    return "";
}

bool Supervisor::isExistMap(QString name)
{
    if(name == "")
    {
        name = getMapname();
    }

    if(QFile::exists(getMapPath(name)))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Supervisor::isExistTlineMap(QString name)
{
    if(name=="")
    {
        name = getMapname();
    }

    if(QFile::exists(QDir::homePath()+"/RB_MOBILE/maps/"+name+"/map_travel_line.png"))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Supervisor::isExistVelMap(QString name)
{
    if(name=="")
    {
        name = getMapname();
    }

    if(QFile::exists(QDir::homePath()+"/RB_MOBILE/maps/"+name+"/map_velocity.png"))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Supervisor::isExistObjectMap(QString name)
{
    if(name=="")
    {
        name = getMapname();
    }

    if(QFile::exists(QDir::homePath()+"/RB_MOBILE/maps/"+name+"/map_obs.png"))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Supervisor::isExistAvoidMap(QString name)
{
    if(name=="")
    {
        name = getMapname();
    }

    if(QFile::exists(QDir::homePath()+"/RB_MOBILE/maps/"+name+"/map_avoid.png"))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Supervisor::isExistRawMap(QString name)
{
    if(QFile::exists(getRawMapPath(name)))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Supervisor::isLoadMap()
{
    //기본 설정된 맵파일 확인
    if(QFile::exists(getMapPath(getMapname())))
    {
        return true;
    }
    return false;
}

void Supervisor::removeMap(QString filename)
{
    plog->write("[USER INPUT] Remove Map : "+filename);
    QDir dir(QDir::homePath()+"/RB_MOBILE/maps/" + filename);

    if(dir.removeRecursively())
    {
        qDebug() << "true";
    }
    else
    {
        qDebug() << "false";
    }
}

bool Supervisor::isExistRobotINI()
{
    QString file = getIniPath("robot");
    return QFile::exists(file);
}

bool Supervisor::checkINI()
{
    bool is_ini = false;
    QString file = getIniPath("static");
    if(QFile::exists(file))
    {
        if(!(getSetting("static","SENSOR","right_camera_serial")=="" || getSetting("static","SENSOR","left_camera_serial")==""))
        {
            is_ini = true;
        }
    }

    return is_ini;
}

void Supervisor::checkRobotINI()
{

    auto func_check_ini = [this](const QString& config, const QString& title, const QString& key, const QString& value)
    {
        if (getSetting(config, title, key) != value)
        {
            setSetting(config, title+ "/" + key, value);
        }
    };

    func_check_ini("update", "MOTOR", "gear_ratio", "1.0");
    func_check_ini("update", "MOTOR", "k_d", "4400.0");
    func_check_ini("update", "MOTOR", "k_i", "0.0");
    func_check_ini("update", "MOTOR", "k_p", "100.0");
    func_check_ini("update", "MOTOR", "left_id", "1");
    func_check_ini("update", "MOTOR", "right_id", "0");
    func_check_ini("update", "MOTOR", "limit_v", "2.0");
    func_check_ini("update", "MOTOR", "limit_v_acc", "1.5");
    func_check_ini("update", "MOTOR", "limit_w", "180.0");
    func_check_ini("update", "MOTOR", "limit_w_acc", "180.0");
    func_check_ini("update", "MOTOR", "wheel_dir", "-1");
    func_check_ini("update", "MOTOR", "box_size", "1");
    func_check_ini("update", "MOTOR", "cur_preset", "3");

    func_check_ini("update", "UI", "box_size", "1");

    func_check_ini("update", "DRIVING", "cur_preset", "3");
    func_check_ini("update", "DRIVING", "comeback_preset", "3");
    func_check_ini("update", "DRIVING", "pause_check_ms", "500");
    func_check_ini("update", "DRIVING", "pause_motor_current", "3000");
    func_check_ini("update", "DRIVING", "goal_dist", "0.1");
    func_check_ini("update", "DRIVING", "goal_th", "3.0");
    func_check_ini("update", "DRIVING", "goal_near_dist", "0.3");
    func_check_ini("update", "DRIVING", "goal_near_th", "15.0");
    func_check_ini("update", "DRIVING", "st_v", "0.05");
    func_check_ini("update", "DRIVING", "goal_v", "0.05");
    func_check_ini("update", "DRIVING", "k_v", "1.0");
    func_check_ini("update", "DRIVING", "k_w", "1.0");
    func_check_ini("update", "DRIVING", "path_out_dist", "1.0");
    func_check_ini("update", "DRIVING", "look_ahead_dist", "1.0");
    func_check_ini("update", "DRIVING", "min_look_ahead_dist", "0.5");
    func_check_ini("update", "DRIVING", "path_delta_v_acc_gain", "1.0");
    func_check_ini("update", "DRIVING", "path_delta_v_dec_gain", "0.5");
    func_check_ini("update", "DRIVING", "goal_v", "0.05");
    func_check_ini("update", "DRIVING", "goal_v", "0.05");

    func_check_ini("update", "SLAM", "slam_submap_cnt", "300");
    func_check_ini("update", "SLAM", "slam_lc_dist", "5.0");
    func_check_ini("update", "SLAM", "slam_lc_icp_dist", "0.5");
    func_check_ini("update", "SLAM", "map_size", "1000");
    func_check_ini("update", "SLAM", "grid_size", "0.05");

    func_check_ini("update", "LOCALIZATION", "icp_dist", "0.2");
    func_check_ini("update", "LOCALIZATION", "icp_error", "0.2");
    func_check_ini("update", "LOCALIZATION", "icp_near", "0.5");
    func_check_ini("update", "LOCALIZATION", "icp_odometry_weight", "0.5");
    func_check_ini("update", "LOCALIZATION", "icp_ratio", "0.3");
    func_check_ini("update", "LOCALIZATION", "icp_repeat_dist", "0.05");
    func_check_ini("update", "LOCALIZATION", "icp_repeat_time", "0.1");


    func_check_ini("setting", "UI", "group_row_num", "2");
    func_check_ini("setting", "UI", "group_col_num", "4");
    func_check_ini("setting", "UI", "table_row_num", "5");
    func_check_ini("setting", "UI", "table_col_num", "1");
    func_check_ini("setting", "UI", "moving_face", "1");
    func_check_ini("setting", "UI", "language", "korean");
    func_check_ini("setting", "UI", "voice_mode", "basic");
    func_check_ini("setting", "UI", "program_branch", "master");
    func_check_ini("setting", "UI", "voice_language", "ko");
    func_check_ini("setting", "UI", "voice_name", "ko");
    func_check_ini("setting", "UI", "voice_language", "none");
    func_check_ini("setting", "UI", "voice_speed", "0");
    func_check_ini("setting", "UI", "voice_pitch", "0");
    func_check_ini("setting", "UI", "voice_alpha", "0");
    func_check_ini("setting", "UI", "voice_emotion", "0");
    func_check_ini("setting", "UI", "voice_emotion_strength", "1");
    func_check_ini("setting", "UI", "volume_bgm", "50");
    func_check_ini("setting", "UI", "volume_voice", "50");
    func_check_ini("setting", "UI", "volume_button", "50");
    func_check_ini("setting", "UI", "user_passwd", "1111");
    func_check_ini("setting", "UI", "call_maximum", "1");
    func_check_ini("setting", "UI", "user_passwd", "1111");
    func_check_ini("setting", "UI", "use_lingbell", "false");
    func_check_ini("setting", "UI", "use_lingbell_repeat", "false");
    func_check_ini("setting", "UI", "lingbell_time", "5");

    if(getSetting("setting","PRESET1","name")=="")
    {
        setSetting("setting","PRESET1/name","매우느리게");
        setSetting("setting","PRESET1/limit_pivot","45");
        setSetting("setting","PRESET1/limit_pivot_acc","360");
        setSetting("setting","PRESET1/limit_v","0.2");
        setSetting("setting","PRESET1/limit_v_acc","0.3");
        setSetting("setting","PRESET1/limit_w","40");
        setSetting("setting","PRESET1/limit_w_acc","360");
    }

    if(getSetting("setting","PRESET2","name")=="")
    {
        setSetting("setting","PRESET2/name","느리게");
        setSetting("setting","PRESET2/limit_pivot","45");
        setSetting("setting","PRESET2/limit_pivot_acc","360");
        setSetting("setting","PRESET2/limit_v","0.4");
        setSetting("setting","PRESET2/limit_v_acc","0.3");
        setSetting("setting","PRESET2/limit_w","40");
        setSetting("setting","PRESET2/limit_w_acc","360");
    }

    if(getSetting("setting","PRESET3","name")=="")
    {
        setSetting("setting","PRESET3/name","보통");
        setSetting("setting","PRESET3/limit_pivot","45");
        setSetting("setting","PRESET3/limit_pivot_acc","360");
        setSetting("setting","PRESET3/limit_v","0.6");
        setSetting("setting","PRESET3/limit_v_acc","0.3");
        setSetting("setting","PRESET3/limit_w","40");
        setSetting("setting","PRESET3/limit_w_acc","360");
    }

    if(getSetting("setting","PRESET4","name")=="")
    {
        setSetting("setting","PRESET4/name","빠르게");
        setSetting("setting","PRESET4/limit_pivot","45");
        setSetting("setting","PRESET4/limit_pivot_acc","360");
        setSetting("setting","PRESET4/limit_v","0.8");
        setSetting("setting","PRESET4/limit_v_acc","0.3");
        setSetting("setting","PRESET4/limit_w","40");
        setSetting("setting","PRESET4/limit_w_acc","360");
    }

    if(getSetting("setting","PRESET5","name")=="")
    {
        setSetting("setting","PRESET5/name","매우빠르게");
        setSetting("setting","PRESET5/limit_pivot","45");
        setSetting("setting","PRESET5/limit_pivot_acc","360");
        setSetting("setting","PRESET5/limit_v","1.0");
        setSetting("setting","PRESET5/limit_v_acc","0.3");
        setSetting("setting","PRESET5/limit_w","40");
        setSetting("setting","PRESET5/limit_w_acc","360");
    }


    func_check_ini("setting", "ROBOT_TYPE", "type", "BOTH");
    func_check_ini("setting", "ROBOT_TYPE", "model", "None");
    func_check_ini("setting", "ROBOT_TYPE", "serial_num", "0");
    func_check_ini("setting", "ROBOT_TYPE", "tray_num", "2");

    func_check_ini("setting", "USE_SLAM", "use_uicmd", "true");
    func_check_ini("setting", "USE_SLAM", "use_early_stop_resting", "false");
    func_check_ini("setting", "USE_SLAM", "use_early_stop_serving", "false");
    func_check_ini("setting", "USE_SLAM", "use_obs_preview", "true");

    func_check_ini("setting", "SENSOR", "mask", "10.0");
    func_check_ini("setting", "SENSOR", "max_range", "40.0");

    func_check_ini("setting", "OBSTACLE", "obs_check_range", "2.5");
    func_check_ini("setting", "OBSTACLE", "obs_deadzone", "0.35");
    func_check_ini("setting", "OBSTACLE", "obs_preview_time", "3.0");
    func_check_ini("setting", "OBSTACLE", "obs_wait_time", "1.0");
    func_check_ini("setting", "OBSTACLE", "obs_detect_area", "2");
    func_check_ini("setting", "OBSTACLE", "obs_detect_area", "2");
    func_check_ini("setting", "OBSTACLE", "obs_detect_sensitivity", "2");
    func_check_ini("setting", "OBSTACLE", "obs_height_max", "1.0");
    func_check_ini("setting", "OBSTACLE", "obs_height_min", "0.1");
    func_check_ini("setting", "OBSTACLE", "obs_margin0", "0.05");
    func_check_ini("setting", "OBSTACLE", "obs_margin1", "0.05");
    func_check_ini("setting", "OBSTACLE", "obs_early_stop_dist", "1");

    func_check_ini("setting", "INITIALIZATION", "icp_init_ratio", "0.7");
    func_check_ini("setting", "INITIALIZATION", "icp_init_error", "0.2");
    func_check_ini("setting", "INITIALIZATION", "icp_mapping_ratio", "0.7");
    func_check_ini("setting", "INITIALIZATION", "icp_mapping_error", "0.2");


    func_check_ini("static", "ROBOT_HW", "wheel_base", "0.3542");
    func_check_ini("static", "ROBOT_HW", "wheel_radius", "0.0635");
    func_check_ini("static", "ROBOT_HW", "robot_radius", "0.3");
    func_check_ini("static", "ROBOT_HW", "robot_length", "0.52");

    func_check_ini("static", "SENSOR", "lidar_offset_tf", "0.17,0.0,-178.0");
    func_check_ini("static", "SENSOR", "left_camera_tf", "0.223,0.0831,0.2,64,0,115");
    func_check_ini("static", "SENSOR", "right_camera_tf", "0.235,-0.0881,0.2,-62,0,-115");

}

void Supervisor::makeRobotINI()
{
    QString updatep = getIniPath("update");
    QString settingp = getIniPath("setting");
    QString staticp = getIniPath("static");
    QString robotp = getIniPath("robot");

    if(QFile::exists(updatep) && QFile::exists(settingp) && QFile::exists(staticp))
    {
        plog->write("[SUPERVISOR] Make Robot Ini : Already good");
    }
    else
    {
        checkRobotINI();
        readSetting();
        slam_ini_reload();
    }
}

bool Supervisor::rotate_map(QString _src, QString _dst, int mode)
{
    cv::Mat map1 = cv::imread(_src.toStdString());

    cv::rotate(map1,map1,cv::ROTATE_90_CLOCKWISE);
    cv::flip(map1, map1, 0);
    QImage temp_image = QPixmap::fromImage(mat_to_qimage_cpy(map1)).toImage();
    QString path = QDir::homePath()+"/RB_MOBILE/maps/"+_dst;
    QDir directory(path);
    if(!directory.exists())
    {
        directory.mkpath(".");
    }

    //Save PNG File
    if(mode == 1)
    {
        //edited
        if(temp_image.save(QDir::homePath()+"/RB_MOBILE/maps/"+_dst+"/map_edited.png","PNG"))
        {
            QFile *file = new QFile(QGuiApplication::applicationDirPath()+"/"+_src);
            file->remove();
            plog->write("[MAP] Save edited Map : "+_dst);
            return true;
        }
        else
        {
            plog->write("[MAP] Fail to save edited Map : "+_dst);
            return false;
        }
    }
    else if(mode == 2)
    {
        //raw
        if(temp_image.save(QDir::homePath()+"/RB_MOBILE/maps/"+_dst+"/map_raw.png","PNG"))
        {
            QFile *file = new QFile(QGuiApplication::applicationDirPath()+"/"+_src);
            file->remove();
            plog->write("[MAP] Save raw Map : "+_dst);
            return true;
        }
        else
        {
            plog->write("[MAP] Fail to save raw Map : "+_dst);
            return false;
        }
    }
}

bool Supervisor::getIPCConnection()
{
    return ipc->getConnection();
}

int Supervisor::getusbsize()
{
    return usb_list.size();
}

QString Supervisor::getusbname(int num)
{
    if(num > -1 && num < usb_list.size())
    {
        return usb_list[num];
    }
    return "";
}

void Supervisor::readusb()
{

}

void Supervisor::saveMapfromUsb(QString path)
{
    std::string user = getenv("USER");
    std::string path1 = "/media/" + user + "/";

    QString orin_path = path1.c_str() + path;
    QStringList kk = path.split('/');
    kk.pop_front();

    QString new_path = QCoreApplication::applicationDirPath();
    for(int i=0; i<kk.size(); i++)
    {
        new_path += "/" + kk[i];
    }

    if(QFile::exists(orin_path))
    {
        if(QFile::copy(orin_path, new_path))
        {
            plog->write("[SETTING] Save Map from USB : "+kk[kk.length()-1]);
        }
        else
        {
            plog->write("[SETTING - ERROR] Save Map from USB (Copy failed): "+kk[kk.length()-1]);
        }
    }
    else
    {
        plog->write("[SETTING - ERROR] Save Map from USB (Origin not found): "+kk[kk.length()-1]);
    }
}

void Supervisor::CopyPath(QString src, QString dst)
{
    QDir dir(src);
    if (! dir.exists())
    {
        return;
    }

    foreach (QString d, dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot))
    {
        QString dst_path = dst + QDir::separator() + d;
        dir.mkpath(dst_path);
        CopyPath(src+ QDir::separator() + d, dst_path);
    }

    foreach (QString f, dir.entryList(QDir::Files))
    {
        QFile::copy(src + QDir::separator() + f, dst + QDir::separator() + f);
    }
}

int Supervisor::copyMap(QString orinname, QString newname)
{
    plog->write("[SETTING] Copy Map orin = "+orinname+", new = "+newname);

    QString orin_path = QDir::homePath() + "/RB_MOBILE/maps/" + orinname;
    QString new_path = QDir::homePath() + "/RB_MOBILE/maps/" + newname;

    QDir dir(orin_path);

    if(QFile::exists(orin_path))
    {
        if(QFile::exists(new_path))
        {
            plog->write("[SETTING] Copy Map failed : Already has");
            return 2;
        }
        else
        {
            if(QDir().mkdir(new_path))
            {
                CopyPath(orin_path, new_path);
                return 0;
            }
            else
            {
                plog->write("[SETTING] Copy Map failed : new Folder make failed");
                return 2;
            }
        }
    }
    else
    {
        plog->write("[SETTING] Copy Map failed : No orinFile");
        return 1;
    }
}

void Supervisor::loadMap(QString name)
{
    setSetting("setting","MAP/map_path",QDir::homePath()+"/RB_MOBILE/maps/"+name);
    setSetting("setting","MAP/map_name",name);
    readSetting(name);
    slam_map_reload(name);
}

void Supervisor::restartSLAM()
{
    ipc->clearSharedMemory(ipc->shm_cmd);
    if(slam_process != nullptr)
    {
        plog->write("[SUPERVISOR] RESTART SLAM -> PID : " + QString::number(slam_process->processId()));
        if(slam_process->state() == QProcess::NotRunning)
        {
            plog->write("[SUPERVISOR] RESTART SLAM -> NOT RUNNING -> KILL");
            slam_process->kill();
            slam_process->close();
            probot->localization_state = LOCAL_NOT_READY;
            probot->status_charge_connect = 0;
            probot->status_charge = 0;
            probot->status_emo = 0;
            probot->status_power = 0;
            probot->status_remote = 0;
            QString file = "xterm ./startslam.sh";
            slam_process->setWorkingDirectory(QDir::homePath()+"/RB_MOBILE/sh");
            slam_process->start(file,QStringList(),QProcess::ReadWrite);
            slam_process->waitForReadyRead(3000);
            plog->write("[SUPERVISOR] RESTART SLAM -> START SLAM "+QString::number(slam_process->processId()));
        }
        else if(slam_process->state() == QProcess::Starting)
        {
            plog->write("[SUPERVISOR] RESTART SLAM -> STARTING");
        }
        else
        {
            plog->write("[SUPERVISOR] RESTART SLAM -> RUNNING");
            QProcess *tempprocess = new QProcess(this);
            tempprocess->start(QDir::homePath() + "/RB_MOBILE/sh/killslam.sh",QStringList(),QProcess::ReadWrite);
            tempprocess->waitForReadyRead(3000);
        }
        probot->localization_state = LOCAL_NOT_READY;
        probot->status_charge = 0;
        probot->status_charge_connect = 0;
        probot->status_emo = 0;
        probot->status_power = 0;
        probot->status_remote = 0;
    }
    else
    {
        plog->write("[SUPERVISOR] RESTART SLAM -> SLAM PROCESS IS NEW ");
        slam_process = new QProcess(this);
        slam_process->setWorkingDirectory(QDir::homePath()+"/RB_MOBILE/sh");
        slam_process->start("xterm",QStringList() << "./startslam.sh");
        plog->write("[SUPERVISOR] RESTART SLAM -> START SLAM "+QString::number(slam_process->processId()));
    }
    probot->localization_state = LOCAL_NOT_READY;
    probot->status_charge = 0;
    probot->status_charge_connect = 0;
    probot->status_emo = 0;
    probot->status_power = 0;
    probot->status_remote = 0;
    ipc->update();
}

void Supervisor::startSLAM()
{
    plog->write("[SUPERVISOR] START SLAM");
    probot->localization_state = LOCAL_NOT_READY;
    probot->status_charge = 0;
    probot->status_charge_connect = 0;
    probot->status_emo = 0;
    probot->status_power = 0;
    probot->status_remote = 0;

    slam_process = new QProcess(this);
    slam_process->setWorkingDirectory(QDir::homePath()+"/RB_MOBILE/sh");
    slam_process->start("xterm",QStringList() << "./startslam.sh");
    ipc->update();
    plog->write("[SUPERVISOR] START SLAM "+QString::number(slam_process->processId()));
}

////*******************************************  SLAM(LOCALIZATION) 관련   ************************************************////
void Supervisor::startMapping(int mapsize, float grid)
{
    plog->write("[USER INPUT] START MAPPING");
    pmap->width = getSetting("update","SLAM","map_size").toInt();
    pmap->height = getSetting("update","SLAM","map_size").toInt();
    pmap->gridwidth = getSetting("update","SLAM","grid_size").toFloat();
    pmap->origin[0] = pmap->width/2;
    pmap->origin[1] = pmap->height/2;
    pmap->mapping_width=mapsize;
    pmap->mapping_gridwidth=grid;
    debug_mode = true;
    ipc->startMapping(mapsize, grid);
    ipc->is_mapping = true;
}

void Supervisor::stopMapping()
{
    plog->write("[USER INPUT] STOP MAPPING");
    ipc->flag_mapping = false;
    ipc->is_mapping = false;
    ipc->stopMapping();
    readSetting(getMapname());
}

void Supervisor::saveMapping(QString name)
{
    ipc->flag_mapping = false;
    ipc->is_mapping = false;
    ipc->saveMapping(name);
}

void Supervisor::setSLAMMode(int mode)
{

}

void Supervisor::setInitCurPos()
{
    maph->set_init_pose = probot->curPose;
    plog->write("[LOCALIZATION] SET INIT POSE : "+QString().asprintf("%f, %f, %f",maph->set_init_pose.point.x, maph->set_init_pose.point.y, maph->set_init_pose.angle));
}

void Supervisor::slam_setInit()
{
    POSE temp = setAxisBack(maph->set_init_pose.point,maph->set_init_pose.angle);
    plog->write("[SLAM] SLAM SET INIT : "+QString().asprintf("%f, %f, %f",temp.point.x,temp.point.y,temp.angle));

    ipc->setInitPose(temp.point.x, temp.point.y, temp.angle);
}

void Supervisor::slam_run()
{
    ipc->set_cmd(ROBOT_CMD_SLAM_RUN, "LOCALIZATION RUN");
}

void Supervisor::slam_stop()
{
    ipc->set_cmd(ROBOT_CMD_SLAM_STOP, "LOCALIZATION STOP");
}

void Supervisor::slam_autoInit()
{
    plog->write("[LOCALIZATION] AUTO INIT : "+QString::number(pmap->map_rotate_angle));
    ipc->set_cmd(ROBOT_CMD_SLAM_AUTO, "LOCALIZATION AUTO INIT");
}

void Supervisor::slam_restInit()
{
    plog->write("[LOCALIZATION] REST INIT : "+QString::number(pmap->map_rotate_angle));
    ipc->set_cmd(ROBOT_CMD_SLAM_RESTING, "LOCALIZATION REST INIT");
}

void Supervisor::slam_fullautoInit()
{
    plog->write("[LOCALIZATION] FULL AUTO INIT : "+QString::number(pmap->map_rotate_angle));
    ipc->set_cmd(ROBOT_CMD_SLAM_FULL_AUTO, "LOCALIZATION FULL AUTO INIT");
}

bool Supervisor::is_slam_running()
{
    if(probot->localization_state == LOCAL_READY)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Supervisor::getMappingflag()
{
    return ipc->flag_mapping;
}

void Supervisor::play_voice(ST_VOICE voice)
{
    voice_player->stop();
    voice_player->setMedia(QUrl::fromLocalFile(voice.file_path));
    if(voice.volume == -1)
    {
        voice.volume = getSetting("setting","UI","volume_voice").toInt();
    }
    voice_player->setVolume(voice.volume);
    voice_player->play();
    plog->write("[SOUND] play_voice : "+voice.file_path + "(volume = "+QString::number(voice.volume)+")");
}

void Supervisor::makePatrolTTS(int language, int voice, QString text, bool play)
{
    ST_VOICE temp;
    temp.mode = "tts";
    temp.language = tts->getVoiceLanguage(language);
    temp.voice = tts->getVoiceName("tts",language, voice);
    current_patrol.voice_mention = text;
    temp.mention = text;
    temp.file = "patrol";
    temp.file_path = QDir::homePath()+"/RB_MOBILE/voice/"+temp.voice+"_patrol.mp3";
    tts->makeTTS(temp, play);
}

QString Supervisor::getTTSMention(QString text)
{
    return tts->getMentionStr(text);
}

void Supervisor::setTTSMention(QString text, QString mention)
{
    tts->setMentionStr(text,mention);
}

void Supervisor::playVoice(QString file, QString voice, QString mode, QString language, int volume)
{
    ST_VOICE v;

    if(mode == "")
    {
        if(probot->is_patrol)
        {
            if(current_patrol.voice_mode == "none")
            {
                v.mode = getSetting("setting","UI","voice_mode");
            }
            else
            {
                v.mode = current_patrol.voice_mode;
            }
        }
        else
        {
            v.mode = getSetting("setting","UI","voice_mode");
        }
    }
    else
    {
        v.mode = mode;
    }

    if(file == "test")
    {
        volume = 50;
    }
    else if(volume == -1)
    {
        if(probot->is_patrol)
        {
            if(current_patrol.voice_mode == "none")
            {
                volume = tts->curVoice.volume;
            }
            else
            {
                volume = current_patrol.voice_volume;
                if(current_patrol.voice_volume == 0)
                {
                    volume = 50;
                    qDebug() << "fuck";
                }
            }
        }
        else
        {
            volume = tts->curVoice.volume;
        }
    }

    if(v.mode == "basic")
    {
        if(voice == "")
        {
            if(probot->is_patrol)
            {
                if(current_patrol.voice_mode == "none")
                {
                    v.voice = getSetting("setting","UI","voice_name");
                }
                else
                {
                    v.voice = current_patrol.voice_name;
                }
            }
            else
            {
                v.voice = getSetting("setting","UI","voice_name");
            }
        }
        else
        {
            v.voice = voice;
        }

        if(v.voice == "woman"|| v.voice == "child")
        {

        }
        else
        {
            v.voice = "woman";
        }

        voice_player->stop();
        voice_player->setMedia(QUrl("qrc:/voice/"+v.voice+"_"+file+".mp3"));
        voice_player->setVolume(volume);
        voice_player->play();
        plog->write("[SUPERVISOR] Play Voice (Basic) : "+v.voice + ", " + file);
    }
    else
    {
        if(voice == "")
        {
            if(probot->is_patrol)
            {
                if(current_patrol.voice_mode == "none")
                {
                    v.voice = tts->curVoice.voice;//getSetting("setting","UI","voice_name");
                }
                else
                {
                    v.voice = current_patrol.voice_name;
                }
            }
            else
            {
                v.voice = tts->curVoice.voice;//getSetting("setting","UI","voice_name");
            }
        }
        else
        {
            v.voice = voice;
        }

        QString filepath = QDir::homePath()+"/RB_MOBILE/voice/"+v.voice+"_"+file+".mp3";
        if(QFile::exists(filepath))
        {
            voice_player->stop();
            voice_player->setMedia(QUrl::fromLocalFile(filepath));
            voice_player->setVolume(volume);
            voice_player->play();
            plog->write("[SOUND] PlayVoiceTTS : "+filepath+", "+QString::number(volume));
        }
        else
        {
            v.file = file;
            v.file_path = filepath;
            v.volume = volume;
            if(probot->is_patrol)
            {
                if(current_patrol.voice_mode == "none")
                {
                    v.mention = tts->getMentionStr(file);
                }
                else
                {
                    v.mention = tts->getMentionBasicStr(v.language,v.file);// (file);
                }

            }
            else
            {
                v.mention = tts->getMentionStr(file);
            }
            v.language = language;
            plog->write("[SOUND] PlayVoiceTTS : no file and make -> "+filepath);
            tts->makeTTS(v,true);
        }
    }
}

void Supervisor::makeTTSAll()
{
    ST_VOICE v = tts->curVoice;
    v.mode = getSetting("setting","UI","voice_mode");

    QStringList makeList = {"move_serving",
                            "move_calling",
                            "move_charging",
                            "move_resting",
                            "move_cleaning",
                            "move_patrol",
                            "move_next",
                            "hello",
                            "thanks",
                            "sorry",
                            "excuseme",
                            "moving",
                            "error_no_path",
                            "error_localization",
                            "error_battery",
                            "error_emo",
                            "pickup",
                            "callme",
                            "start_operation",
                            "start_charging"
                            "stop_charging",
                            "charging",
                            "start_mapping",
                            "stop_mapping",
                            "test"};

    for(QString f : makeList)
    {
        v.file = f;
        v.file_path = QDir::homePath()+"/RB_MOBILE/voice/"+v.voice+"_"+v.file+".mp3";
        v.mention = tts->getMentionStr(v.file);
        tts->makeTTS(v,false);
    }
}

bool Supervisor::isplayBGM()
{
    if(bgm_player->state() == QMediaPlayer::PlayingState)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Supervisor::playBGM(int volume)
{
    list_bgm->addMedia(QUrl("qrc:/bgm/song.mp3"));
    list_bgm->setPlaybackMode(QMediaPlaylist::Loop);
    bgm_player->setPlaylist(list_bgm);
    if(volume == -1)
    {
        volume = getSetting("setting","UI","volume_bgm").toInt();
    }
    plog->write("[SOUND] playBGM : "+QString::number(volume));
    bgm_player->setVolume(volume);
    bgm_player->play();
}

void Supervisor::setvolumeBGM(int volume)
{
    bgm_player->setVolume(volume);
    plog->write("[SOUND] playBGMVolume : "+QString::number(volume));
}

void Supervisor::stopBGM()
{
    bgm_player->stop();
}

QString Supervisor::getnewMapname()
{
    int max_num = -1;
    for(int i=0; i<getAvailableMap(); i++)
    {
        QStringList name = map_list[i].split("_");
        if(name.size() > 1 && name[0] == "map")
        {
            if(name[1].toInt() > max_num)
            {
                max_num = name[1].toInt();
            }
        }
    }
    if(max_num == -1)
    {
        return "map_0";
    }
    else
    {
        return "map_"+QString::number(max_num+1);
    }
}

void Supervisor::usb_detect()
{
    try
    {
        const char* user_c = getenv("USER");
        std::string user = (user_c != nullptr) ? user_c : "";
        std::string path = "/media/" + user;
        QDir directory(path.c_str());
        if(!directory.exists())
        {
            plog->write("[SUPERVISOR][usb_detect] Directory does not exist: " + QString::fromStdString(path));
            return;
        }

        // clear usb list
        usb_list.clear();
        usb_file_list.clear();
        usb_file_full_list.clear();

        QStringList temp = directory.entryList();
        foreach (QString name, temp)
        {
            if(name != "." && name != "..")
            {
                usb_list.append(name);

                QString full_path = directory.path() + "/" + name;
                QDir dd(full_path);

                QStringList files = dd.entryList();
                foreach(QString file, files)
                {
                    QStringList ex = file.split(".");
                    if(ex.size() > 1)
                    {
                        if(ex[1] == "zip")
                        {
                            if(ex[0].left(11) == "MobileRobot")
                            {
                                QStringList names = ex[0].split("_");
                                if(names.size() == 3)
                                {
                                    std::cout << "[SUPERVISOR][usb_detect] find device: " << ex[0].toStdString() << std::endl;

                                    usb_file_full_list.append(name+"/"+file);
                                    usb_file_list.append(names[2]);
                                }
                            }
                        }
                        else
                        {
                            continue;
                        }
                    }
                    else
                    {
                        continue;
                    }
                }
            }
        }
        plog->write("[SUPERVISOR][usb_detect] NEW USB Detected cnt: " + QString::number(usb_list.size()));
    }
    catch(const std::exception &e)
    {
        QString err_str = "[SUPERVISOR][usb_detect] Exception occurred, err: "  + QString(e.what());
        std::cerr << err_str.toStdString() << std::endl;
        plog->write(err_str);
    }
    catch(...)
    {
        QString err_str = "[SUPERVISOR][usb_detect] Exception occurred, err: unknown.";
        std::cerr << err_str.toStdString() << std::endl;
        plog->write(err_str);
    }
}

int Supervisor::getusberrorsize()
{
    return zip->errorlist.size();
}

int Supervisor::getusbfilesize()
{
    return usb_file_list.size();
}

QString Supervisor::getusbfile(int num)
{
    QString usb_str = "";
    if(usb_file_full_list.isEmpty())
    {
        return usb_str;
    }

    if(num >= 0 && num < usb_file_full_list.size())
    {
        usb_str = usb_file_full_list[num];
    }

    return usb_str;
}

QString Supervisor::getusbrecentfile()
{
    QString filename = "";
    if(usb_file_list.isEmpty())
    {
        return filename;
    }

    double temp = 0;
    for(int i=0; i<usb_file_list.size(); i++)
    {
        QString tempstr = usb_file_list[i];
        if(temp < tempstr.toDouble())
        {
            temp = tempstr.toDouble();
            filename = tempstr;
        }
    }

    return filename;
}

QString Supervisor::getusberror(int num)
{
    QString usb_err_str = "";
    if(zip->errorlist.isEmpty())
    {
        return usb_err_str;
    }

    if(num >= 0 && num < zip->errorlist.size())
    {
        usb_err_str = zip->errorlist[num];
    }

    return usb_err_str;
}

void Supervisor::readusbrecentfile()
{
    if(usb_file_list.isEmpty())
    {
        return;
    }

    double temp = 0;
    int num = -1;
    for(int i=0; i<usb_file_list.size(); i++)
    {
        QString tempstr = usb_file_list[i];
        if(temp < tempstr.toDouble())
        {
            temp = tempstr.toDouble();
            num = i;
        }
    }
    if(num == -1)
    {
        return;
    }

    QString path = getusbfile(num);
    zip->getZip(path);
}

void Supervisor::callCallbell(QString id)
{
    QString func_str = "[SUPERVISOR][callCallbell] ";
    plog->write(func_str + "start func. params(id):" + id);

    if(!call)
    {
        log_advanced(func_str + "Error: call is null.");
        return;
    }

    call->send_call(id);
}

////*********************************************  ANNOTATION 관련   ***************************************************////
/////Location
///
QString Supervisor::getNewServingName(int group)
{
    QString func_str = "[SUPERVISOR][getNewServingName] ";
    plog->write(func_str + "start func. params(group):" + QString::number(group));

    QString groupname = "";
    if(!pmap)
    {
        log_advanced(func_str + "Error: pmap is null.");
        return groupname;
    }

    if(group < 0 || group > pmap->location_groups.size())
    {
        log_advanced(func_str + "Error: group is out of bounds.");
        return groupname;
    }
    else
    {
        groupname = pmap->location_groups[group];
        if(groupname == "" || groupname == "Default")
        {
            groupname = "서빙";
        }
    }

    int count = 0;
    while(isDuplicateName(group, groupname + QString::number(count + 1)))
    {
        count++;
    }

    return groupname + QString::number(count + 1);
}

bool Supervisor::isDuplicateName(int group, QString name)
{
    for (const auto& location : pmap->serving_locations)
    {
        if (location.group == group && location.name == name)
        {
            return true;
        }
    }

    return false;
}

QString Supervisor::getServingName(int group, int num)
{
    QString func_str = "[SUPERVISOR][getServingName] ";
    plog->write(func_str + "start func. params(group, num):" + QString::number(group) + "," + QString::number(num));

    QString name = tr("설정 안됨");
    if(!pmap)
    {
        log_advanced(func_str + "Error: pmap is null.");
        return name;
    }

    int count = 0;
    for(const auto& location : pmap->serving_locations)
    {
        if(location.group == group)
        {
            if(count == num)
            {
                name = location.name;
            }
            count++;
        }
    }

    return name;
}

int Supervisor::getLocationNum(QString type)
{
    QString func_str = "[SUPERVISOR][getLocationNum] ";
    plog->write(func_str + "start func. params(type):" + type);

    int loc_num = 0;
    if(!pmap)
    {
        log_advanced(func_str + "Error: pmap is null.");
        return loc_num;
    }

    const std::map<QString, QList<LOCATION>> location_map =
    {
        {"Charging", pmap->charging_locations},
        {"Resting", pmap->resting_locations},
        {"Cleaning", pmap->cleaning_locations},
        {"Init", pmap->init_locations},
        {"Serving", pmap->serving_locations}
    };

    auto it = location_map.find(type);
    if(it != location_map.end())
    {
        const QList<LOCATION>& locations = it->second;
        loc_num = locations.size();
    }

    return loc_num;
}

int Supervisor::getLocationGroupNum(int num)
{
    QString func_str = "[SUPERVISOR][getLocationGroupNum] ";
    plog->write(func_str + "start func. params(num):" + QString::number(num));

    int group_num = 0;
    if(!pmap)
    {
        log_advanced(func_str + "Error: pmap is null.");
        return group_num;
    }

    if(num < 0 || num >= pmap->serving_locations.size())
    {
        log_advanced(func_str + "Error: num is out of bounds.");
        return group_num;
    }

    try
    {
        if(pmap->location_groups.size() <= pmap->serving_locations[num].group)
        {
            log_advanced(func_str + "Error: group index out of bounds.");
            return group_num;
        }
        else
        {
            group_num = pmap->serving_locations[num].group;
        }
    }
    catch(const std::exception &e)
    {
        log_advanced(func_str + "Exception occurred, err: "  + QString(e.what()));
    }
    catch(...)
    {
        log_advanced(func_str + "Exception occurred, err: unknown.");
    }

    return group_num;
}

QString Supervisor::getLocationCallID(QString type, int num)
{
    QString func_str = "[SUPERVISOR][getLocationCallID] ";
    plog->write(func_str + "start func. params(type,num):" + type + "," + QString::number(num));

    QString loc_call_id_str = "";
    if(!pmap)
    {
        log_advanced(func_str + "Error: pmap is null.");
        return loc_call_id_str;
    }

    const std::map<QString, QList<LOCATION>> location_map =
    {
        {"Charging", pmap->charging_locations},
        {"Resting", pmap->resting_locations},
        {"Cleaning", pmap->cleaning_locations},
        {"Init", pmap->init_locations},
        {"Serving", pmap->serving_locations}
    };

    auto it = location_map.find(type);
    if(it != location_map.end())
    {
        const QList<LOCATION>& locations = it->second;
        if(num < 0 || num > locations.size())
        {
            log_advanced(func_str + "Error: num is out of bounds.");
        }
        else
        {
            loc_call_id_str =locations.at(num).call_id;
        }
    }
    else
    {
        log_advanced(func_str + "Error: unknown type: " + type);
    }

    return loc_call_id_str;
}

QString Supervisor::getLocationLingID(QString type, int num)
{
    QString func_str = "[SUPERVISOR][getLocationLingID] ";
    plog->write(func_str + "start func. params(type,num):" + type + "," + QString::number(num));

    QString loc_ling_id_str = "";
    if(!pmap)
    {
        log_advanced(func_str + "Error: pmap is null.");
        return loc_ling_id_str;
    }

    const std::map<QString, QList<LOCATION>> location_map =
    {
        {"Charging", pmap->charging_locations},
        {"Resting", pmap->resting_locations},
        {"Cleaning", pmap->cleaning_locations},
        {"Init", pmap->init_locations},
        {"Serving", pmap->serving_locations}
    };

    auto it = location_map.find(type);
    if(it != location_map.end())
    {
        const QList<LOCATION>& locations = it->second;
        if(num < 0 || num > locations.size())
        {
            log_advanced(func_str + "Error: num is out of bounds.");
        }
        else
        {
            loc_ling_id_str =locations.at(num).ling_id;
        }
    }
    else
    {
        log_advanced(func_str + "Error: unknown type: " + type);
    }

    return loc_ling_id_str;
}

void Supervisor::setLocationGroup(int num, int group)
{
    QString func_str = "[SUPERVISOR][getLocationGroup] ";
    plog->write(func_str + "start func. params(num,group):" + QString::number(num) + "," + QString::number(group));

    if(!pmap)
    {
        log_advanced(func_str + "Error: pmap is null.");
        return;
    }

    if(num < 0 || num >= pmap->serving_locations.size())
    {
        log_advanced(func_str + "Error: num is out of bound.");
        return;
    }
    else
    {
        plog->write(func_str + "SET Location Group (num, group) " + QString().asprintf("%d:%d", num, group));
        pmap->serving_locations[num].group = group;
    }
}

QString Supervisor::getLocationGroup(int num)
{
    QString func_str = "[SUPERVISOR][getLocationGroup] ";
    plog->write(func_str + "start func. params(num):" + QString::number(num));

    QString loc_group_str = "(-)";
    if(!pmap)
    {
        log_advanced(func_str + "Error: pmap is null.");
        return loc_group_str;
    }

    if(num < 0 || num >= pmap->serving_locations.size())
    {
        log_advanced(func_str + "Error: num is out of bounds.");
        return loc_group_str;
    }

    int group_index = pmap->serving_locations[num].group;
    if(group_index < 0 || pmap->location_groups.size() <= group_index)
    {
        log_advanced(func_str + "Error: group size invalid.");
        return loc_group_str;
    }

    loc_group_str = pmap->location_groups[pmap->serving_locations[num].group];

    return loc_group_str;
}

void Supervisor::addLocationGroup(QString name)
{
    QString func_str = "[SUPERVISOR][addLocationGroup] ";
    plog->write(func_str + "start func. params(name):" + name);

    if(!pmap)
    {
        log_advanced(func_str + "Error: pmap is null.");
        return;
    }

    pmap->location_groups.append(name);
    plog->write(func_str + "Add Location Group : " + name + "(size = " + QString::number(pmap->location_groups.size()) + ")");
}

void Supervisor::removeLocationGroup(int num)
{
    QString func_str = "[SUPERVISOR][removeLocationGroup] ";
    plog->write(func_str + "start func. params(num):" + QString::number(num));

    if(!pmap)
    {
        log_advanced(func_str + "Error: pmap is null.");
        return;
    }

    if(num < 0 || num > pmap->location_groups.size())
    {
        log_advanced(func_str + "Error: num is out of bounds.");
        return;
    }

    pmap->location_groups.removeAt(num);
    plog->write(func_str + " remove:" + QString::number(num) + "(size = " + QString::number(pmap->location_groups.size()) + ")");
}

int Supervisor::getLocationGroupNum()
{
    QString func_str = "[SUPERVISOR][getLocationGroupNum] ";
    plog->write(func_str + "start func. params()");

    int loc_group_num = 0;
    if(!pmap)
    {
        log_advanced(func_str + "Error: pmap is null.");
        return loc_group_num;
    }

    return pmap->location_groups.size();
}

void Supervisor::selectLocation(QString type, int num)
{   
    QString func_str = "[SUPERVISOR][getLocationName] ";
    plog->write(func_str + "start func. params(type,num):" + type + "," + QString::number(num));

    const std::map<QString, void (MapHandler::*)(int)> location_map =
    {
        {"Charging", &MapHandler::setSelectCharging},
        {"Resting", &MapHandler::setSelectResting},
        {"Cleaning", &MapHandler::setSelectCleaning},
        {"Init", &MapHandler::setSelectInit},
        {"Serving", &MapHandler::setSelectServing}
    };

    auto it = location_map.find(type);
    if(it != location_map.end())
    {
        (maph->*(it->second))(num);
    }
    else
    {
        log_advanced(func_str + "Error: loc type invalid.");
        return;
    }
}

bool Supervisor::setLocationUp(int num)
{
    QString func_str = "[SUPERVISOR][setLocationUp] ";
    plog->write(func_str + "start func. params(num):" + QString::number(num));

    if(!pmap)
    {
        log_advanced(func_str + "Error: pmap is null.");
        return false;
    }

    if(num <= 0 || num >= pmap->serving_locations.size())
    {
        log_advanced(func_str + "Error: num is out of bounds.");
        return false;
    }

    plog->write(func_str + " Location "+QString::number(num) + "(" + pmap->serving_locations[num].name + ") Up");
    pmap->serving_locations.move(num, num-1);

    return true;
}

bool Supervisor::setLocationDown(int num)
{
    QString func_str = "[SUPERVISOR][setLocationDown] ";
    plog->write(func_str + "start func. params(num):" + QString::number(num));

    if(!pmap)
    {
        log_advanced(func_str + "Error: pmap is null.");
        return false;
    }

    if(num < 0 || num >= pmap->serving_locations.size())
    {
        log_advanced(func_str + "Error: num is out of bounds.");
        return false;
    }

    plog->write(func_str + "Location " + QString::number(num) + "(" + pmap->serving_locations[num].name + ") Down");
    pmap->serving_locations.move(num, num + 1);

    return true;
}

int Supervisor::getLocationGroupSize(int num)
{
    QString func_str = "[SUPERVISOR][getLocationGroupSize] ";
    plog->write(func_str + "start func. params(num):" + QString::number(num));

    int size = 0;
    if(!pmap)
    {
        log_advanced(func_str + "Error: pmap is null.");
        return size;
    }

    if(num < 0 || num >= pmap->location_groups.size())
    {
        log_advanced(func_str + "Error: num is out of bounds.");
        return size;
    }

    for(const auto& location : pmap->serving_locations)
    {
        if(location.group == num)
        {
            size++;
        }
    }

    return size;
}

QString Supervisor::getLocationName(int num, QString type)
{
    QString func_str = "[SUPERVISOR][getLocationName] ";
    plog->write(func_str + "start func. params(num,type):" + QString::number(num) + "," + type);

    QString loc_name_str = "-";
    if(!pmap)
    {
        log_advanced(func_str + "Error: pmap is null.");
        return loc_name_str;
    }

    const std::map<QString, QList<LOCATION>> location_map =
    {
        {"Charging", pmap->charging_locations},
        {"Resting", pmap->resting_locations},
        {"Cleaning", pmap->cleaning_locations},
        {"Init", pmap->init_locations},
        {"Serving", pmap->serving_locations}
    };

    auto it = location_map.find(type);
    if (it != location_map.end())
    {
        const QList<LOCATION>& locations = it->second;
        if(num < 0 || num >= locations.size())
        {
            log_advanced(func_str + "Error: num is out of bounds.");
        }
        else
        {
            loc_name_str = locations[num].name;
        }
    }
    else
    {
        log_advanced(func_str + "Error: unknown location type '" + type + "'.");
    }

    return loc_name_str;
}

QString Supervisor::getLocationNameGroup(int num)
{
    QString func_str = "[SUPERVISOR][getLocGroupname] ";
    plog->write(func_str + "start func. params(num):" + QString::number(num));

    QString loc_group_name_str = "-";
    if(!pmap)
    {
        log_advanced(func_str + "Error: pmap is null.");
        return loc_group_name_str;
    }

    if(num < 0 || num >= pmap->serving_locations.size())
    {
        log_advanced(func_str + "Error: num is out of bounds.");
        return loc_group_name_str;
    }
    else
    {
        loc_group_name_str = pmap->serving_locations[num].group_name;
    }

    return loc_group_name_str;
}

void Supervisor::setLocation(int num, QString name, int group, int tablenum)
{
    QString func_str = "[SUPERVISOR][setLocation] ";
    plog->write(func_str + "start func. params(num,name,group,tablenum):" +
                QString::number(num) + "," +
                name + "," +
                QString::number(group) + "," +
                QString::number(tablenum));

}

QString Supervisor::getLocGroupname(int num)
{
    QString func_str = "[SUPERVISOR][getLocGroupname] ";
    plog->write(func_str + "start func. params(num):" + QString::number(num));

    QString loc_group_name_str = " - ";
    if(!pmap)
    {
        log_advanced(func_str + "Error: pmap is null.");
        return loc_group_name_str;
    }

    if(num < 0 || num >= pmap->location_groups.size())
    {
        log_advanced(func_str + "Error: num is out of bounds.");
    }
    else
    {
        loc_group_name_str = pmap->location_groups[num];
    }

    return loc_group_name_str;
}

float Supervisor::getLocationX(int num, QString type)
{
    QString func_str = "[SUPERVISOR][getLocationX] ";
    plog->write(func_str + "start func. params(num,type):" + QString::number(num) + "," + type);

    float loc_x = 0.f;
    if(!pmap)
    {
        log_advanced(func_str + "Error: pmap is null.");
        return loc_x;
    }

    const std::map<QString, QList<LOCATION>> location_map =
    {
        {"Charging", pmap->charging_locations},
        {"Resting", pmap->resting_locations},
        {"Cleaning", pmap->cleaning_locations},
        {"Init", pmap->init_locations},
        {"Serving", pmap->serving_locations}
    };

    auto it = location_map.find(type);
    if(it != location_map.end())
    {
        const QList<LOCATION>& locations = it->second;
        if(num < 0 || num >= locations.size())
        {
            log_advanced(func_str + "Error: num is out of bounds.");
        }
        else
        {
            loc_x = setAxis(locations.at(num).point).x;
        }
    }
    else
    {
        log_advanced(func_str + "Error: unknown location type '" + type + "'.");
    }

    return loc_x;
}

float Supervisor::getLocationY(int num, QString type)
{
    QString func_str = "[SUPERVISOR][getLocationY] ";
    plog->write(func_str + "start func. params(num,type):" + QString::number(num) + "," + type);

    float loc_y = 0.f;
    if(!pmap)
    {
        log_advanced(func_str + "Error: pmap is null.");
        return loc_y;
    }

    const std::map<QString, QList<LOCATION>> location_map =
    {
        {"Charging", pmap->charging_locations},
        {"Resting", pmap->resting_locations},
        {"Cleaning", pmap->cleaning_locations},
        {"Init", pmap->init_locations},
        {"Serving", pmap->serving_locations}
    };

    auto it = location_map.find(type);
    if(it != location_map.end())
    {
        const QList<LOCATION>& locations = it->second;
        if(num < 0 || num >= locations.size())
        {
            log_advanced(func_str + "Error: num is out of bounds.");
        }
        else
        {
            loc_y = setAxis(locations.at(num).point).y;
        }
    }
    else
    {
        log_advanced(func_str + "Error: unknown location type '" + type + "'.");
    }

    return loc_y;
}

float Supervisor::getLocationTH(int num, QString type)
{
    QString func_str = "[SUPERVISOR][getLocationTH] ";
    plog->write(func_str + "start func. params(num,type):" + QString::number(num) + "," + type);

    float loc_th = 0.f;
    if(!pmap)
    {
        log_advanced(func_str + "Error: pmap is null.");
        return loc_th;
    }

    const std::map<QString, QList<LOCATION>> location_map =
    {
        {"Charging", pmap->charging_locations},
        {"Resting", pmap->resting_locations},
        {"Cleaning", pmap->cleaning_locations},
        {"Init", pmap->init_locations},
        {"Serving", pmap->serving_locations}
    };

    auto it = location_map.find(type);
    if(it != location_map.end())
    {
        const QList<LOCATION>& locations = it->second;
        if(num < 0 || num >= locations.size())
        {
            log_advanced(func_str + "Error: num is out of bounds.");
        }
        else
        {
            loc_th = setAxis(locations.at(num).angle);
        }
    }
    else
    {
        log_advanced(func_str + "Error: unknown location type '" + type + "'.");
    }

    return loc_th;
}

float setAxis(float _angle)
{
    float val = -_angle - M_PI/2;
    //plog->write("[SUPERVISOR][setAxis] angle:" + QString::number(val));

    return val;
}

float setAxisBack(float _angle)
{
    float val = -_angle - M_PI/2;
    //plog->write("[SUPERVISOR][setAxisBack] angle:" + QString::number(val));

    return val;
}

cv::Point2f setAxis(cv::Point2f _point)
{
    cv::Point2f temp;
    temp.x = -_point.y/pmap->gridwidth + pmap->origin[1];
    temp.y = -_point.x/pmap->gridwidth + pmap->origin[0];

    //plog->write("[SUPERVISOR][setAxis] (x,y):" + QString::number(temp.x) + "," + QString::number(temp.y));
    return temp;
}

cv::Point2f setAxisMapping(cv::Point2f _point)
{
    float grid = pmap->mapping_gridwidth*pmap->mapping_width/1000;
    cv::Point2f temp;
    temp.x = -_point.y/grid + 1000/2;
    temp.y = -_point.x/grid + 1000/2;

    //plog->write("[SUPERVISOR][setAxisMapping] (x,y):" + QString::number(temp.x) + "," + QString::number(temp.y));
    return temp;
}

cv::Point2f setAxisObject(cv::Point2f _point)
{
    float grid = pmap->gridwidth*pmap->width/pmap->mapping_width;
    cv::Point2f temp;
    temp.x = -_point.y/grid + pmap->mapping_width/2;
    temp.y = -_point.x/grid + pmap->mapping_width/2;

    //plog->write("[SUPERVISOR][setAxisObject] (x,y):" + QString::number(temp.x) + "," + QString::number(temp.y));
    return temp;
}

cv::Point2f setAxisBack(cv::Point2f _point)
{
    cv::Point2f temp;
    temp.x = -pmap->gridwidth*(_point.y-pmap->origin[1]);
    temp.y = -pmap->gridwidth*(_point.x-pmap->origin[0]);

    //plog->write("[SUPERVISOR][setAxisBack] (x,y):" + QString::number(temp.x) + "," + QString::number(temp.y));
    return temp;
}

POSE setAxis(POSE _pose)
{
    POSE temp;
    temp.point = setAxis(_pose.point);
    temp.angle = setAxis(_pose.angle);
    return temp;
}

POSE setAxisBack(POSE _pose)
{
    POSE temp;
    temp.point = setAxisBack(_pose.point);
    temp.angle = setAxisBack(_pose.angle);
    return temp;
}

POSE setAxis(cv::Point2f _point, float _angle)
{
    POSE temp;
    temp.point = setAxis(_point);
    temp.angle = setAxis(_angle);
    return temp;
}

POSE setAxisBack(cv::Point2f _point, float _angle)
{
    POSE temp;
    temp.point = setAxisBack(_point);
    temp.angle = setAxisBack(_angle);

    return temp;
}

bool sortWifi(const QString &w1, const QString &w2)
{
    if(probot->wifi_map[w1].inuse)
    {
        return true;
    }
    else if(probot->wifi_map[w2].inuse)
    {
        return true;
    }
    else
    {
        return probot->wifi_map[w1].level > probot->wifi_map[w2].level;
    }
}

int Supervisor::getObjectNum()
{
    QString func_str = "[SUPERVISOR][getObjectNum] ";
    plog->write(func_str + "start func. params()");

    int obj_size = 0;
    if(!pmap)
    {
        log_advanced(func_str + "Error: pmap is null.");
        return obj_size;
    }

    obj_size = pmap->objects.size();
    return obj_size;
}

QString Supervisor::getObjectName(int num)
{
    QString func_str = "[SUPERVISOR][getObjectName] ";
    plog->write(func_str + "start func. params(num):" + QString::number(num));

    QString name_str = "_";
    if(!pmap)
    {
        log_advanced(func_str + "Error: pmap is null.");
        return name_str;
    }

    if(num < 0 || num >= pmap->objects.size())
    {
        log_advanced(func_str + "Error: num is out of bounds.");
        return name_str;
    }

    int count = 0;
    for(int i=0; i<num; i++)
    {
        if(pmap->objects[i].type == pmap->objects[num].type)
        {
            count++;
        }
    }

    name_str = pmap->objects[num].type + "_" + QString::number(count);
    return name_str;
}

int Supervisor::getObjectPointSize(int num)
{
    QString func_str = "[SUPERVISOR][getObjectPointSize] ";
    plog->write(func_str + "start func. params(num):" + QString::number(num));

    int obj_pt_size = 0;
    if(!pmap)
    {
        log_advanced(func_str + "Error: pmap is null.");
        return obj_pt_size;
    }

    if(num < 0 || num >= pmap->objects.size())
    {
        log_advanced(func_str + "Error: num is out of bounds.");
        return obj_pt_size;
    }

    obj_pt_size = pmap->objects[num].points.size();
    return obj_pt_size;
}

float Supervisor::getObjectX(int num, int point)
{
    QString func_str = "[SUPERVISOR][getObjectX] ";
    plog->write(func_str + "start func. params(num,point):" + QString::number(num) + "," + QString::number(point));

    float obj_x = 0.f;
    if(!pmap)
    {
        log_advanced(func_str + "Error: pmap is null.");
        return obj_x;
    }

    if(num < 0 || num >= pmap->objects.size())
    {
        log_advanced(func_str + "Error: num is out of bounds.");
        return obj_x;
    }

    if(point < 0 || point >= pmap->objects[num].points.size())
    {
        log_advanced(func_str + "Error: point is out of bounds.");
        return obj_x;
    }

    try
    {
        obj_x = setAxis(pmap->objects[num].points[point]).x;
    }
    catch(const std::exception &e)
    {
        log_advanced(func_str + "Exception : " + QString(e.what()));
        obj_x = 0.f;
    }
    catch(...)
    {
        log_advanced(func_str + "Exception : unknwon.");
        obj_x = 0.f;
    }

    return obj_x;
}

float Supervisor::getObjectY(int num, int point)
{
    QString func_str = "[SUPERVISOR][getObjectY] ";
    plog->write(func_str + "start func. params(num,point):" + QString::number(num) + "," + QString::number(point));

    float obj_y = 0.f;
    if(!pmap)
    {
        log_advanced(func_str + "Error: pmap is null.");
        return obj_y;
    }

    if(num < 0 || num >= pmap->objects.size())
    {
        log_advanced(func_str + "Error: num is out of bounds.");
        return obj_y;
    }

    if(point < 0 || point >= pmap->objects[num].points.size())
    {
        log_advanced(func_str + "Error: point is out of bounds.");
        return obj_y;
    }

    try
    {
        obj_y = setAxis(pmap->objects[num].points[point]).y;
    }
    catch(const std::exception &e)
    {
        log_advanced(func_str + "Exception : " + QString(e.what()));
        obj_y = 0.f;
    }
    catch(...)
    {
        log_advanced(func_str + "Exception : unknwon.");
        obj_y = 0.f;
    }

    return obj_y;
}

bool Supervisor::getAnnotEditFlag()
{
    QString func_str = "[SUPERVISOR][getAnnotEditFlag] ";
    plog->write(func_str + "start func. params()");

    bool is_edit = false;
    if(!pmap)
    {
        log_advanced(func_str + "Error: pmap is null.");
        return is_edit;
    }

    is_edit = pmap->annotation_edited;
    return is_edit;
}

void Supervisor::setAnnotEditFlag(bool flag)
{
    QString func_str = "[SUPERVISOR][setAnnotEditFlag] ";
    plog->write(func_str + "start func. params(flag):" + QString::number((int)flag));

    if(!pmap)
    {
        log_advanced(func_str + "Error: pmap is null.");
        return;
    }

    pmap->annotation_edited = flag;
}

void Supervisor::clearSharedMemory()
{
    QString func_str = "[SUPERVISOR][clearSharedMemory] ";
    plog->write(func_str + "start func. params()");

    if(!ipc)
    {
        log_advanced(func_str + "Error: ipc is null.");
        return;
    }

    ipc->clearSharedMemory(ipc->shm_cmd);
}

int Supervisor::getObjPointNum(int obj_num, int x, int y)
{
    QString func_str = "[SUPERVISOR][getObjPointNum] ";
    plog->write(func_str + "start func. params(obj_num,x,y):" + QString::number(obj_num) + "," + QString::number(x) + "," + QString::number(y));

    int idx = -1;
    if(!pmap)
    {
        log_advanced(func_str + "Error: pmap is null.");
        return idx;
    }

    if(obj_num < 0 || obj_num >= pmap->objects.size())
    {
        log_advanced(func_str + "Error: num is out of bounds.");
        return idx;
    }

    cv::Point2f pos = setAxisBack(cv::Point2f(x,y));

    const auto& pts = pmap->objects[obj_num].points;
    for(int p=0; p<pts.size(); p++)
    {
        if(fabs(pts[p].x - pos.x) < 0.1 && fabs(pts[p].y - pos.y) < 0.1)
        {
            idx = p;
            break;
        }
    }

    if(idx == -1)
    {
        plog->write(func_str + "can't find obj num (obj_num,idx):" +QString::number(obj_num) + "," + QString::number(idx));
    }
    else
    {
        plog->write(func_str + "match point (obj_num,idx):" +QString::number(obj_num) + "," + QString::number(idx));
    }

    return idx;
}

void Supervisor::removeLocation(QString type, int num)
{
    QString func_str = "[SUPERVISOR][removeLocation] ";
    plog->write(func_str + "start func. params(type,num):" + type + "," + QString::number(num));

    if(!pmap)
    {
        log_advanced(func_str + "Error: pmap is null.");
        return;
    }

    const std::map<QString, QList<LOCATION>&> location_map =
    {
        {"Charging", pmap->charging_locations},
        {"Resting", pmap->resting_locations},
        {"Cleaning", pmap->cleaning_locations},
        {"Init", pmap->init_locations},
        {"Serving", pmap->serving_locations}
    };

    auto it = location_map.find(type);
    if(it != location_map.end())
    {
        QList<LOCATION>& locations = it->second;
        if(num < 0 || num > locations.size())
        {
            log_advanced(func_str + "Error: num is out of bounds.");
            return;
        }

        pmap->annotation_edited = true;
        locations.removeAt(num);
    }
    else
    {
        log_advanced(func_str + "Error: unknown locatio type '" + type + "'.");
    }
}

void Supervisor::removeObject(int num)
{
    QString func_str = "[SUPERVISOR][removeObject] ";
    plog->write(func_str + "start func. params(num):" + QString::number(num));

    if(!pmap)
    {
        log_advanced(func_str + "Error: pmap is null.");
        return;
    }

    if(num < 0 || num >= pmap->objects.size())
    {
        log_advanced(func_str + "Error: num is out of bounds.");
        return;
    }

    pmap->annotation_edited = true;
    pmap->objects.removeAt(num);

    try
    {
        maph->setObjPose();
        maph->clearObject();
        QMetaObject::invokeMethod(mMain, "updateobject");
        plog->write(func_str + "remove obj " + QString().asprintf("(%d)", num));
    }
    catch(const std::exception &e)
    {
        log_advanced(func_str + "Exception occurred, err: "  + QString(e.what()));
    }
    catch(...)
    {
        log_advanced(func_str + "Exception occurred, err: unknown.");
    }
}

int Supervisor::getObjectSize(QString type)
{
    QString func_str = "[SUPERVISOR][isOdroid] ";
    plog->write(func_str + "start func. params(type):" + type);

    int size = 0;
    if(!pmap)
    {
        log_advanced(func_str + "Error: pmap is null.");
        return size;
    }

    for(const auto& obj : pmap->objects)
    {
        if(obj.type == type)
        {
            size++;
        }
    }
    return size;
}

bool Supervisor::isOdroid()
{
    QString func_str = "[SUPERVISOR][isOdroid] ";
    plog->write(func_str + "start func. params()");

    bool is_odroid = true;
    try
    {
        QStringList str_list = QDir::homePath().split("/");
        if(str_list.size() < 2)
        {
            log_advanced(func_str + "Error: str_list size under 2.");
            return is_odroid;
        }

        if(str_list[2] != "odroid")
        {
            is_odroid = false;
        }
    }
    catch(const std::exception &e)
    {
        log_advanced(func_str + "Exception occurred, err: "  + QString(e.what()));
        is_odroid = true;
    }
    catch(...)
    {
        log_advanced(func_str + "Exception occurred, err: unknown.");
        is_odroid = true;
    }

    return is_odroid;
}

void Supervisor::saveNode()
{
    QString func_str = "[SUPERVISOR][saveNode] ";
    plog->write(func_str + "start func. params()");

    if(!maph)
    {
        log_advanced(func_str + "Error: maph is null.");
        return;
    }

    try
    {
        maph->saveNode();
        maph->saveAnnotation();
        saveAnnotation("");
    }
    catch(const std::exception &e)
    {
        log_advanced(func_str + "Exception occurred, err: "  + QString(e.what()));
    }
    catch(...)
    {
        log_advanced(func_str + "Exception occurred, err: unknown.");
    }
}

bool Supervisor::saveAnnotation(QString filename, bool reload)
{
    QString func_str = "[SUPERVISOR][saveAnnotation] ";
    plog->write(func_str + "start func. params(filename, reload):" + filename + "," + QString::number((int)reload));

    if(!pmap)
    {
        log_advanced(func_str + "Error: pmap is null.");
        return false;
    }

    if(!maph)
    {
        log_advanced(func_str + "Error: maph is null.");
        return false;
    }

    if(filename == "")
    {
        filename = getMapname();
    }

    bool is_save_annot = true;
    try
    {
        QString origin = getAnnotPath(filename);
        if(QFile::exists(origin) == true)
        {
            QString backup = QDir::homePath() + "/RB_MOBILE/maps/" + filename + "/annotation_backup.ini";
            if(QFile::copy(origin, backup))
            {
                plog->write(func_str + "Copy annotation.ini to annotation_backup.ini");
            }
            else
            {
                plog->write(func_str + "Fail to copy annotation.ini to annotation_backup.ini");
                return false;
            }
        }
        else
        {
            plog->write(func_str + "Fail to copy annotation.ini to annotation_backup.ini (No file found)");
            return false;
        }

        //데이터 입력(로케이션)
        int resting_num = 0;
        int charging_num = 0;
        int cleaning_num = 0;
        int init_num = 0;
        std::vector<int> group_num(pmap->location_groups.size(), 0);

        QString path_anot = getAnnotPath(filename);
        QFileInfo file_info(path_anot);
        if(file_info.exists() && file_info.isFile())
        {
            QSettings settings(path_anot, QSettings::IniFormat);
            settings.clear();

            //name, x, y, th, num, locnum, callid
            for(const auto& loc : pmap->charging_locations)
            {
                QString loc_name = loc.name + QString().asprintf(",%f,%f,%f", loc.point.x, loc.point.y, loc.angle) + "," + loc.call_id + ":" + loc.ling_id;
                settings.setValue("charging_locations/loc" + QString::number(charging_num), loc_name);
                charging_num++;
            }

            for(const auto& loc : pmap->resting_locations)
            {
                QString loc_name = loc.name + QString().asprintf(",%f,%f,%f", loc.point.x, loc.point.y, loc.angle) + "," + loc.call_id + ":" + loc.ling_id;
                settings.setValue("resting_locations/loc" + QString::number(resting_num), loc_name);
                resting_num++;
            }

            for(const auto& loc : pmap->cleaning_locations)
            {
                QString loc_name = loc.name + QString().asprintf(",%f,%f,%f", loc.point.x, loc.point.y, loc.angle) + "," + loc.call_id + ":" + loc.ling_id;
                settings.setValue("cleaning_locations/loc" + QString::number(cleaning_num), loc_name);
                cleaning_num++;
            }

            for(const auto& loc : pmap->init_locations)
            {
                QString loc_name = loc.name + QString().asprintf(",%f,%f,%f", loc.point.x, loc.point.y, loc.angle) + "," + loc.call_id + ":" + loc.ling_id;
                settings.setValue("init_locations/loc" + QString::number(init_num), loc_name);
                init_num++;
            }

            for(const auto& loc : pmap->serving_locations)
            {
                QString groupname = "serving_" + QString::number(loc.group);
                QString loc_name = loc.name + QString().asprintf(",%f,%f,%f", loc.point.x, loc.point.y, loc.angle) + "," + loc.call_id + ":" + loc.ling_id;
                settings.setValue(groupname + "/loc" + QString::number(group_num[loc.group]), loc_name);
                group_num[loc.group]++;
            }

            settings.setValue("charging_locations/num",charging_num);
            settings.setValue("resting_locations/num", resting_num);
            settings.setValue("cleaning_locations/num", cleaning_num);
            settings.setValue("init_locations/num", init_num);
            settings.setValue("serving_locations/group", pmap->location_groups.size());

            for(int i=0; i<pmap->location_groups.size(); i++)
            {
                settings.setValue("serving_" + QString::number(i) + "/name", pmap->location_groups[i]);
                settings.setValue("serving_" + QString::number(i) + "/num", getLocationGroupSize(i));
            }

            slam_map_reload(filename, SOFT_RELOAD);

            if(reload == true)
            {
                readSetting(filename);
                maph->initLocation();
            }
            pmap->annotation_edited = false;
        }
    }
    catch(const std::exception &e)
    {
        log_advanced(func_str + "Exception occurred, err: "  + QString(e.what()));
        is_save_annot = false;
    }
    catch(...)
    {
        log_advanced(func_str + "Exception occurred, err: unknown.");
        is_save_annot = false;
    }

    return is_save_annot;
}

void Supervisor::saveTTSVoice()
{
    QString func_str = "[SUPERVISOR][saveTTSVoice] ";
    plog->write(func_str + "start func. params()");

    if(!tts)
    {
        log_advanced(func_str + "Error: tts is null.");
        return;
    }

    try
    {
        auto func_save_setting_if_changed = [this](const QString& key, const QString& value)
        {
            if (getSetting("setting", "UI", key) != value)
            {
                setSetting("setting", "UI/" + key, value);
            }
        };

        func_save_setting_if_changed("voice_language", tts->curVoice.language);
        func_save_setting_if_changed("voice_name", tts->curVoice.voice);
        func_save_setting_if_changed("voice_mode", tts->curVoice.mode);
        func_save_setting_if_changed("voice_speed", QString::number(tts->curVoice.speed));
        func_save_setting_if_changed("voice_pitch", QString::number(tts->curVoice.pitch));
        func_save_setting_if_changed("voice_alpha", QString::number(tts->curVoice.alpha));
        func_save_setting_if_changed("voice_emotion", QString::number(tts->curVoice.emotion));
        func_save_setting_if_changed("voice_emotion_strength", QString::number(tts->curVoice.emotion_strength));

        plog->write(func_str + "save tts voice: " + tts->curVoice.mode);
    }
    catch(const std::exception &e)
    {
        log_advanced(func_str + "Exception occurred, err: "  + QString(e.what()));
    }
    catch(...)
    {
        log_advanced(func_str + "Exception occurred, err: unknown.");
    }
}

void Supervisor::clearTTSVoice(int lan, int name)
{
    QString func_str = "[SUPERVISOR][clearTTSVoice] ";
    plog->write(func_str + "start func. params(lan, name):" + QString::number(lan) + "," + QString::number(name));

    if(!tts)
    {
        log_advanced(func_str + "Error: tts is null.");
        return;
    }

    try
    {
        QDir path = QDir::homePath() + "/RB_MOBILE/voice";
        QStringList files = path.entryList();
        QString voice = tts->getVoiceName("tts", lan, name);
        plog->write(func_str + " set clear(lan, name, voice) : " + QString::number(lan) + "," + QString::number(name) + " -> " + voice);

        for(const QString& file : files)
        {
            if(file.startsWith(voice +"_"))
            {
                QString filePath = path.filePath(file);
                if (QFile::remove(filePath))
                {
                    plog->write(func_str + "remove file (" + file + ")");
                }
                else
                {
                    plog->write(func_str + "failed to remove file (" + file + ")");
                }
            }
        }
    }
    catch(const std::exception &e)
    {
        log_advanced(func_str + "Exception occurred, err: "  + QString(e.what()));
    }
    catch(...)
    {
        log_advanced(func_str + "Exception occurred, err: unknown.");
    }
}

void Supervisor::setTTSMode(QString mode)
{
    QString func_str = "[SUPERVISOR][setTTSMode] ";
    plog->write(func_str + "start func. params(mode):" + mode);

    if(!tts)
    {
        log_advanced(func_str + "Error: tts is null.");
        return;
    }

    try
    {
        tts->curVoice.mode = mode;
        setTTSVoice(0,0);
        setTTSVoiceDetail(0,0,0);
        plog->write(func_str + " set tts mode : " + mode);
    }
    catch(const std::exception &e)
    {
        log_advanced(func_str + "Exception occurred, err: "  + QString(e.what()));
    }
    catch(...)
    {
        log_advanced(func_str + "Exception occurred, err: unknown.");
    }
}

void Supervisor::setTTSMentionBasic()
{
    QString func_str = "[SUPERVISOR][setTTSMentionBasic] ";
    plog->write(func_str + "start func. params()");

    if(!tts)
    {
        log_advanced(func_str + "Error: tts is null.");
        return;
    }

    try
    {
        tts->setMentionBasic(tts->curVoice.language);
    }
    catch(const std::exception &e)
    {
        log_advanced(func_str + "Exception occurred, err: "  + QString(e.what()));
    }
    catch(...)
    {
        log_advanced(func_str + "Exception occurred, err: unknown.");
    }
}

void Supervisor::setTTSVoice(int lan, int name)
{
    QString func_str = "[SUPERVISOR][setTTSVoice] ";
    plog->write(func_str + "start func. params(lan, name):" + QString::number(lan) + "," + QString::number(name));

    if(!tts)
    {
        log_advanced(func_str + "Error: tts is null.");
        return;
    }

    try
    {
        tts->setVoice(tts->getVoiceName("tts", lan, name), tts->getVoiceLanguage(lan));
        saveTTSVoice();
        plog->write(func_str + " set voice: " + tts->getVoiceLanguage(lan) + "(" + tts->getVoiceName("tts", lan, name) + ")");
    }
    catch(const std::exception &e)
    {
        log_advanced(func_str + "Exception occurred, err: "  + QString(e.what()));
    }
    catch(...)
    {
        log_advanced(func_str + "Exception occurred, err: unknown.");
    }
}

void Supervisor::setTTSVoiceDetail(int speed, int pitch, int alpha, int emotion, int emostren)
{
    QString func_str = "[SUPERVISOR][setTTSVoiceDetail] ";
    plog->write(func_str + "start func. params(speed, pitch, alpha, emotion, emostren):" +
                QString::number(speed) + "," +
                QString::number(pitch) + "," +
                QString::number(alpha) + "," +
                QString::number(emotion) + "," +
                QString::number(emostren));

    if(!tts)
    {
        log_advanced(func_str + "Error: tts is null.");
        return;
    }

    try
    {
        tts->setVoiceDetail(speed, pitch, alpha, emotion, emostren);
        saveTTSVoice();
    }
    catch(const std::exception &e)
    {
        log_advanced(func_str + "Exception occurred, err: "  + QString(e.what()));
    }
    catch(...)
    {
        log_advanced(func_str + "Exception occurred, err: unknown.");
    }
}

////*********************************************  SCHEDULER(SERVING) 관련   ***************************************************////
void Supervisor::setTray(int tray_num, int group, int table)
{
    QString func_str = "[SUPERVISOR][setTray] ";
    plog->write(func_str + "start func. params(group, table):" + QString::number(group) + "," + QString::number(table));

    if(!probot)
    {
        log_advanced(func_str + "Error: probot is null.");
        return;
    }

    if(tray_num < 0 || tray_num >= probot->trays.size())
    {
        log_advanced(func_str + "Error: tray_num is out of bounds.");
        return;
    }

    try
    {
        QString serving_name = getServingName(group,table);
        probot->trays[tray_num].location = getServingLocation(group, serving_name);
        probot->trays[tray_num].empty = false;
        plog->write(func_str + "setTray : " + QString::number(tray_num) + " , " + serving_name);
    }
    catch(const std::exception &e)
    {
        log_advanced(func_str + "Exception occurred, err: "  + QString(e.what()));
    }
    catch(...)
    {
        log_advanced(func_str + "Exception occurred, err: unknown.");
    }
}

void Supervisor::startServing()
{
    QString func_str = "[SUPERVISOR][startServing] ";
    plog->write(func_str + "start func.");

    if(!probot)
    {
        log_advanced(func_str + "Error: probot is null.");
        return;
    }

    try
    {
        if(isRobotReady())
        {
            bool is_empty = true;
            for(const auto &trays : probot->trays)
            {
                if(!trays.empty)
                {
                    is_empty = false;
                    plog->write(func_str + "start serving. location name: " + trays.location.name);
                    stateMoving();
                    break;
                }
            }

            if(is_empty)
            {
                plog->write(func_str + "empty tray");
            }
        }
        else
        {
            plog->write(func_str + "robot state not ready " + QString::asprintf("(UIstate: %d, Local: %d, Motor1: %d, Motor2: %d)", (int)ui_state, probot->localization_state, probot->motor[0].status, probot->motor[1].status));
        }
    }
    catch(const std::exception &e)
    {
        log_advanced(func_str + "Exception occurred, err: "  + QString(e.what()));
    }
    catch(...)
    {
        log_advanced(func_str + "Exception occurred, err: unknown.");
    }
}

void Supervisor::startServing(int group, int table)
{
    QString func_str = "[SUPERVISOR][startServing(group,table)] ";
    plog->write(func_str + "start func. params(group, table):" + QString::number(group) + "," + QString::number(table));

    if(!probot)
    {
        log_advanced(func_str + "Error: probot is null.");
        return;
    }

    try
    {
        if(isRobotReady())
        {
            LOCATION target;
            patrol_mode = PATROL_NONE;
            int target_num = -1;
            int count = 0;

            for(const auto& loc : pmap->serving_locations)
            {
                if(loc.group == group)
                {
                    if(count == table)
                    {
                        target = loc;
                        target_num = count;
                        break;
                    }
                    else
                    {
                        count++;
                    }
                }
            }

            if(target_num > -1)
            {
                plog->write(func_str + "start serving" + target.name+QString().asprintf("%d,%d", group, table));
                for(int i=0; i<probot->trays.size(); i++)
                {
                    probot->trays[i].empty = false;
                    probot->trays[i].location = target;
                }
                stateMoving();
            }
            else
            {
                plog->write(func_str + "target not found " + QString().asprintf("%d,%d", group, table));
            }
        }
        else
        {
            plog->write(func_str + "robot state not ready, " + QString::asprintf("(UIstate: %d, Loc: %d, Motor1: %d, Motor2: %d)",
                                                                                  (int)ui_state,
                                                                                  probot->localization_state,
                                                                                  probot->motor[0].status,
                                                                                  probot->motor[1].status));
        }
    }
    catch(const std::exception &e)
    {
        log_advanced(func_str + "Exception occurred, err: "  + QString(e.what()));
    }
    catch(...)
    {
        log_advanced(func_str + "Exception occurred, err: unknown.");
    }
}

void Supervisor::setPreset(int preset)
{
    QString func_str = "[SUPERVISOR][setPreset] ";
    plog->write(func_str + "start func. params(preset):" + QString::number(preset));

    if(!probot)
    {
        log_advanced(func_str + "Error: probot is null.");
        return;
    }

    try
    {
        probot->cur_preset = preset;
        setSetting("update", "DRIVING/cur_preset", QString::number(preset));
    }
    catch(const std::exception &e)
    {
        log_advanced(func_str + "Exception occurred, err: "  + QString(e.what()));
    }
    catch(...)
    {
        log_advanced(func_str + "[SUPERVISOR][setPreset] Exception occurred, err: unknown.");
    }
}

void Supervisor::confirmPickup(QString mode)
{
    QString func_str = "[SUPERVISOR][confirmPickup] ";
    plog->write(func_str + "start func. params(mode):" + mode);

    if(!probot)
    {
        log_advanced(func_str + "Error: probot is null.");
        return;
    }

    try
    {
        if(ui_state == UI_STATE_PICKUP)
        {
            if(pmap->call_queue.size() > 0 && probot->is_calling)
            {
                plog->write(func_str + "Call queue pop front " + pmap->call_queue[0]);
                pmap->call_queue.pop_front();
            }

            if(isRobotReady())
            {
                plog->write(func_str + "Moving");
                stateMoving();
                if(mode == "Cleaning")
                {
                    probot->current_target = getCleaningLocation(0);
                }
            }
            else
            {
                plog->write(func_str + "robot state Not Ready");
                QMetaObject::invokeMethod(mMain,"robotnotready");
            }
        }
        else
        {
            probot->current_target.name = "";
            plog->write(func_str + " (ui_state " + QString::number(ui_state) + ") -> noting to do");
        }
    }
    catch(const std::exception &e)
    {
        log_advanced(func_str + "Exception occurred, err: "  + QString(e.what()));
    }
    catch(...)
    {
        log_advanced(func_str + "Exception occurred, err: unknown.");
    }
}

QList<int> Supervisor::getPickuptrays()
{
    QString func_str = "[SUPERVISOR][getPickuptrays] ";
    plog->write(func_str + "start func. params()");

    QList<int> _pickupTrays;
    if(!probot)
    {
        log_advanced(func_str + "Error: probot is null.");
        return _pickupTrays;
    }

    try
    {
        _pickupTrays= probot->pickupTrays;
    }
    catch(const std::exception &e)
    {
        log_advanced(func_str + "Exception occurred, err: "  + QString(e.what()));
    }
    catch(...)
    {
        log_advanced(func_str + "Exception occurred, err: unknown.");
    }

    return _pickupTrays;
}

////*********************************************  ROBOT MOVE 관련   ***************************************************////
void Supervisor::movePause()
{
    QString func_str = "[SUPERVISOR][movePause] ";
    plog->write(func_str + "start func. params()");

    if(!ipc)
    {
        log_advanced(func_str + "Error: ipc is null.");
        return;
    }

    ipc->movePause();
}

void Supervisor::moveResume()
{
    QString func_str = "[SUPERVISOR][moveResume] ";
    plog->write(func_str + "start func. params()");

    if(!ipc)
    {
        log_advanced(func_str + "Error: ipc is null.");
        return;
    }

    ipc->moveResume();
}

void Supervisor::moveStopFlag()
{
    QString func_str = "[SUPERVISOR][moveStopFlag] ";
    plog->write(func_str + "start func. params()");

    if(!pmap)
    {
        log_advanced(func_str + "Error: pmap is null.");
        return;
    }

    if(!probot)
    {
        log_advanced(func_str + "Error: probot is null.");
        return;
    }

    try
    {
        patrol_mode = PATROL_NONE;
        probot->is_patrol = false;
        pmap->call_queue.clear();
        for(int i=0; i<probot->trays.size(); i++)
        {
            probot->trays[i].empty = true;
        }
    }
    catch(const std::exception &e)
    {
        log_advanced(func_str + "Exception occurred, err: "  + QString(e.what()));
    }
    catch(...)
    {
        log_advanced(func_str + "Exception occurred, err: unknown.");
    }
}

void Supervisor::moveStop()
{
    QString func_str = "[SUPERVISOR][moveStop] ";
    plog->write(func_str + "start func. params()");

    if(!mMain)
    {
        log_advanced(func_str + "Error: mMain is null.");
        return;
    }

    try
    {
        stateInit();
        QMetaObject::invokeMethod(mMain, "movestopped");
    }
    catch(const std::exception &e)
    {
        log_advanced(func_str + "Exception occurred, err: "  + QString(e.what()));
    }
    catch(...)
    {
        log_advanced(func_str + "Exception occurred, err: unknown.");
    }
}

void Supervisor::moveToCharge()
{
    QString func_str = "[SUPERVISOR][moveToCharge] ";
    plog->write(func_str + "start func. params()");

    if(!mMain)
    {
        log_advanced(func_str + "Error: mMain is null.");
        return;
    }

    if(!probot)
    {
        log_advanced(func_str + "Error: probot is null.");
        return;
    }

    try
    {
        if(isRobotReady())
        {
            stateMoving();
            probot->current_target = getChargingLocation(0);
            plog->write(func_str + "move");
        }
        else
        {
            QMetaObject::invokeMethod(mMain, "robotnotready");
            plog->write(func_str + "robot state not ready " + QString::asprintf("(UIstate: %d, Local: %d, Motor1: %d, Motor2: %d)", (int)ui_state, probot->localization_state, probot->motor[0].status, probot->motor[1].status));
        }
    }
    catch(const std::exception &e)
    {
        log_advanced(func_str + "Exception occurred, err: "  + QString(e.what()));
    }
    catch(...)
    {
        log_advanced(func_str + "Exception occurred, err: unknown.");
    }
}

void Supervisor::moveToCleaning()
{
    QString func_str = "[SUPERVISOR][moveToCleaning] ";
    plog->write(func_str + "start func. params()");

    if(!mMain)
    {
        log_advanced(func_str + "Error: mMain is null.");
        return;
    }

    if(!probot)
    {
        log_advanced(func_str + "Error: probot is null.");
        return;
    }

    try
    {
        if(isRobotReady())
        {
            stateMoving();
            probot->current_target = getCleaningLocation(0);
            plog->write(func_str + "move");
        }
        else
        {
            QMetaObject::invokeMethod(mMain, "robotnotready");
            plog->write(func_str + "robot state not ready " + QString::asprintf("(UIstate: %d, Local: %d, Motor1: %d, Motor2: %d)", (int)ui_state, probot->localization_state, probot->motor[0].status, probot->motor[1].status));
        }
    }
    catch(const std::exception &e)
    {
        log_advanced(func_str + "Exception occurred, err: "  + QString(e.what()));
    }
    catch(...)
    {
        log_advanced(func_str + "Exception occurred, err: unknown.");
    }
}

void Supervisor::moveToWait()
{
    QString func_str = "[SUPERVISOR][moveToWait] ";
    plog->write(func_str + "start func. params()");

    if(!mMain)
    {
        log_advanced(func_str + "Error: mMain is null.");
        return;
    }

    if(!probot)
    {
        log_advanced(func_str + "Error: probot is null.");
        return;
    }

    try
    {
        if(isRobotReady())
        {
            stateMoving();
            probot->current_target = getRestingLocation(0);
            plog->write(func_str + "move");
        }
        else
        {
            QMetaObject::invokeMethod(mMain,"robotnotready");
            plog->write(func_str + "robot state not ready " + QString::asprintf("(UIstate: %d, Local: %d, Motor1: %d, Motor2: %d)", (int)ui_state, probot->localization_state, probot->motor[0].status, probot->motor[1].status));
        }
    }
    catch(const std::exception &e)
    {
        log_advanced(func_str + "Exception occurred, err: "  + QString(e.what()));
    }
    catch(...)
    {
        log_advanced(func_str + "Exception occurred, err: unknown.");
    }
}

bool Supervisor::isFinalLocation()
{
    QString func_str = "[SUPERVISOR][isFinalLocation] ";
    plog->write(func_str + "start func. params()");

    if(!probot)
    {
        log_advanced(func_str + "Error: probot is null.");
        return false;
    }

    bool is_final_loc = true;
    try
    {
        bool tray_occupied = false;
        for(int i=0; i<setting.tray_num; i++)
        {
            if(!probot->trays[i].empty)
            {
                tray_occupied = true;
                break;
            }
        }

        if(tray_occupied == true || probot->is_patrol)
        {
            is_final_loc = false;
        }
    }
    catch(const std::exception &e)
    {
        log_advanced(func_str + "Exception occurred, err: "  + QString(e.what()));
    }
    catch(...)
    {
        log_advanced(func_str + "Exception occurred, err: unknown.");
    }

    return is_final_loc;
}

QString Supervisor::getcurLoc()
{
    QString func_str = "[SUPERVISOR][getcurLoc] ";
    plog->write(func_str + "start func. params()");

    if(!probot)
    {
        log_advanced(func_str + "Error: probot is null.");
        return "";
    }

    return probot->curLocation.name;
}

int Supervisor::getMultiState()
{
    QString func_str = "[SUPERVISOR][getMultiState] ";
    plog->write(func_str + "start func. params()");

    if(!probot)
    {
        log_advanced(func_str + "Error: probot is null.");
        return 0;
    }

    return probot->multirobot_state;
}

////*********************************************  ROBOT STATUS 관련   ***************************************************////
int Supervisor::getBattery()
{
    QString func_str = "[SUPERVISOR][getBattery] ";
    //plog->write(func_str + "start func. params()");

    if(!probot)
    {
        log_advanced(func_str + "Error: probot is null.");
        return 0;
    }

    return probot->battery_percent;
}

bool Supervisor::getMotorConnection(int id)
{
    QString func_str = "[SUPERVISOR][getMotorConnection] ";
    //plog->write(func_str + "start func. params()");

    if(!probot)
    {
        log_advanced(func_str + "Error: probot is null.");
        return false;
    }

    return probot->motor[id].connection;
}

int Supervisor::getMotorStatus(int id)
{
    QString func_str = "[SUPERVISOR][getMotorStatus] ";
    //plog->write(func_str + "start func. params(id):" + QString::number(id));

    if(!probot)
    {
        log_advanced(func_str + "Error: probot is null.");
        return 0;
    }

    return probot->motor[id].status;
}

QString Supervisor::getMotorStatusStr(int id)
{
    QString func_str = "[SUPERVISOR][getMotorStatusStr] ";
    //plog->write(func_str + "start func. params(id):" + QString::number(id));

    if(!probot)
    {
        log_advanced(func_str + "Error: probot is null.");
        return 0;
    }

    QString str = "";
    if(probot->motor[id].connection == 0)
    {
        str = "CON";
    }
    else
    {
        str = "POW";
        auto append_error = [&str](bool condition, const char* text)
        {
            if (condition)
            {
                str += text;
            }
        };

        append_error(MOTOR_RUN(probot->motor[id].status) == 1, " - ");
        append_error(MOTOR_MOD_ERROR(probot->motor[id].status) == 1, "M");
        append_error(MOTOR_JAM_ERROR(probot->motor[id].status) == 1, " J");
        append_error(MOTOR_CUR_ERROR(probot->motor[id].status) == 1, " CR");
        append_error(MOTOR_BIG_ERROR(probot->motor[id].status) == 1, " B");
        append_error(MOTOR_INP_ERROR(probot->motor[id].status) == 1, " I");
        append_error(MOTOR_PS_ERROR(probot->motor[id].status) == 1, " P");
        append_error(MOTOR_COL_ERROR(probot->motor[id].status) == 1, " CL");
    }

    return str;
}
int Supervisor::getMotorTemperature(int id)
{
    QString func_str = "[SUPERVISOR][getMotorTemperature] ";
    //plog->write(func_str + "start func. params(id):" + QString::number(id));

    if(!probot)
    {
        log_advanced(func_str + "Error: probot is null.");
        return 0;
    }

    return probot->motor[id].temperature;
}

int Supervisor::getMotorInsideTemperature(int id)
{
    QString func_str = "[SUPERVISOR][getMotorInsideTemperature] ";
    //plog->write(func_str + "start func. params(id):" + QString::number(id));

    if(!probot)
    {
        log_advanced(func_str + "Error: probot is null.");
        return 0;
    }

    return probot->motor[id].motor_temp;
}

int Supervisor::getMotorWarningTemperature()
{
    QString func_str = "[SUPERVISOR][getMotorWarningTemperature] ";
    //plog->write(func_str + "start func. params()");

    return 55;
}

int Supervisor::getMotorCurrent(int id)
{
    QString func_str = "[SUPERVISOR][getMotorCurrent] ";
    //plog->write(func_str + "start func. params(id):" + QString::number(id));

    if(!probot)
    {
        log_advanced(func_str + "Error: probot is null.");
        return 0;
    }

    return probot->motor[id].current;
}

int Supervisor::getPowerStatus()
{
    QString func_str = "[SUPERVISOR][getPowerStatus] ";
    //plog->write(func_str + "start func. params()");

    if(!probot)
    {
        log_advanced(func_str + "Error: probot is null.");
        return 0;
    }

    return probot->status_power;
}

int Supervisor::getChargeConnectStatus()
{
    QString func_str = "[SUPERVISOR][getChargeConnectStatus] ";
    //plog->write(func_str + "start func. params()");

    if(!probot)
    {
        log_advanced(func_str + "Error: probot is null.");
        return 0;
    }

    return probot->status_charge_connect;
}

int Supervisor::getChargeStatus()
{
    QString func_str = "[SUPERVISOR][getChargeStatus] ";
    //plog->write(func_str + "start func. params()");

    if(!probot)
    {
        log_advanced(func_str + "Error: probot is null.");
        return 0;
    }

    return probot->status_charge;
}

int Supervisor::getEmoStatus()
{
    QString func_str = "[SUPERVISOR][getEmoStatus] ";
    //plog->write(func_str + "start func. params()");

    if(!probot)
    {
        log_advanced(func_str + "Error: probot is null.");
        return 0;
    }

    return probot->status_emo;
}

int Supervisor::getLockStatus()
{
    QString func_str = "[SUPERVISOR][getLockStatus] ";
    //plog->write(func_str + "start func. params()");

    if(!probot)
    {
        log_advanced(func_str + "Error: probot is null.");
        return 0;
    }

    return probot->status_lock;
}

int Supervisor::getObsinPath()
{
    QString func_str = "[SUPERVISOR][getObsinPath] ";
    //plog->write(func_str + "start func. params()");

    if(!probot)
    {
        log_advanced(func_str + "Error: probot is null.");
        return 0;
    }

    return probot->obs_in_path_state;
}

void Supervisor::setMotorLock(bool onoff)
{
    QString func_str = "[SUPERVISOR][setMotorLock] ";
    //plog->write(func_str + "start func. params()");

    if(!probot)
    {
        log_advanced(func_str + "Error: probot is null.");
        return;
    }

    if(!ipc)
    {
        log_advanced(func_str + "Error: ipc is null.");
        return;
    }

    try
    {
        if(ipc->getConnection())
        {
            if(onoff == true)
            {
                plog->write("[COMMAND] SET MOTOR LOCK : ON");
                ipc->set_cmd(ROBOT_CMD_MOTOR_LOCK_ON,"ROBOT_CMD_MOTOR_LOCK_ON");
            }
            else
            {
                plog->write("[COMMAND] SET MOTOR LOCK : OFF");
                ipc->set_cmd(ROBOT_CMD_MOTOR_LOCK_OFF2,"ROBOT_CMD_MOTOR_LOCK_OFF2");
            }
        }
    }
    catch(const std::exception &e)
    {
        log_advanced(func_str + "Exception occurred, err: "  + QString(e.what()));
    }
    catch(...)
    {
        log_advanced(func_str + "Exception occurred, err: unknown.");
    }
}

float Supervisor::getBatteryIn()
{
    QString func_str = "[SUPERVISOR][getBatteryIn] ";
    //plog->write(func_str + "start func. params()");

    if(!probot)
    {
        log_advanced(func_str + "Error: probot is null.");
        return 0.f;
    }

    return probot->battery_in;
}

float Supervisor::getBatteryOut()
{
    QString func_str = "[SUPERVISOR][getBatteryOut] ";
    //plog->write(func_str + "start func. params()");

    if(!probot)
    {
        log_advanced(func_str + "Error: probot is null.");
        return 0.f;
    }

    return probot->battery_out;
}

float Supervisor::getBatteryCurrent()
{
    QString func_str = "[SUPERVISOR][getBatteryCurrent] ";
    //plog->write(func_str + "start func. params()");

    if(!probot)
    {
        log_advanced(func_str + "Error: probot is null.");
        return 0.f;
    }

    return probot->battery_cur;
}

float Supervisor::getPower()
{
    QString func_str = "[SUPERVISOR][getPower] ";
    //plog->write(func_str + "start func. params()");

    if(!probot)
    {
        log_advanced(func_str + "Error: probot is null.");
        return 0.f;
    }

    return probot->power;
}

float Supervisor::getPowerTotal()
{
    QString func_str = "[SUPERVISOR][getPowerTotal] ";
    //plog->write(func_str + "start func. params()");

    if(!probot)
    {
        log_advanced(func_str + "Error: probot is null.");
        return 0.f;
    }

    return probot->total_power;
}

int Supervisor::getMotorState()
{
    QString func_str = "[SUPERVISOR][getMotorState] ";
    //plog->write(func_str + "start func. params()");

    int motor_state = 0;
    if(!probot)
    {
        log_advanced(func_str + "Error: probot is null.");
        return motor_state;
    }

    if(probot->motor[0].status == 1 && probot->motor[1].status == 1)
    {
        motor_state = 1;
    }

    return motor_state;
}

int Supervisor::getLocalizationState()
{
    QString func_str = "[SUPERVISOR][getLocalizationState] ";
    //plog->write(func_str + "start func. params()");

    if(!probot)
    {
        log_advanced(func_str + "Error: probot is null.");
        return 0;
    }

    return probot->localization_state;
}

int Supervisor::getStateMoving()
{
    QString func_str = "[SUPERVISOR][getStateMoving] ";
    plog->write(func_str + "start func. params()");

    if(!probot)
    {
        log_advanced(func_str + "Error: probot is null.");
        return 0;
    }

    return probot->running_state;
}

QString Supervisor::getStateMovingStr()
{
    QString func_str = "[SUPERVISOR][getStateMovingStr] ";
    plog->write(func_str + "start func. params()");

    QString state_moving_str = tr("알수 없음 ");
    if(!probot)
    {
        log_advanced(func_str + "Error: probot is null.");
        return state_moving_str;
    }

    try
    {
        if(probot->running_state == 0)
        {
            state_moving_str = tr("준비 안됨");
        }
        else if(probot->running_state == 1)
        {
            state_moving_str = tr("준비됨");
        }
        else if(probot->running_state == 2)
        {
            state_moving_str = tr("이동중");
        }
        else if(probot->running_state == 3)
        {
            state_moving_str = tr("이동중 (장애물 감지)");
        }
        else if(probot->running_state == 4)
        {
            state_moving_str = tr("이동중 (일시정지됨)");
        }
        else
        {
            state_moving_str = tr("알수 없음 ")+QString::number(probot->running_state);
        }
    }
    catch(const std::exception &e)
    {
        log_advanced(func_str + "Exception occurred, err: "  + QString(e.what()));
        state_moving_str = tr("알수 없음 ");
    }
    catch(...)
    {
        log_advanced(func_str + "Exception occurred, err: unknown.");
        state_moving_str = tr("알수 없음 ");
    }

    return state_moving_str;
}

QString Supervisor::getRobotName()
{
    QString func_str = "[SUPERVISOR][getRobotName] ";
    plog->write(func_str + "start func. params()");

    QString robot_name_str = robot.name;
    if(is_debug)
    {
        robot_name_str = robot.name + "_" + robot.name_debug;
    }

    return robot_name_str;
}

float Supervisor::getlastRobotx()
{
    QString func_str = "[SUPERVISOR][getlastRobotx] ";
    plog->write(func_str + "start func. params()");

    float x = 0.f;
    if(!probot)
    {
        log_advanced(func_str + "Error: probot is null.");
        return x;
    }

    try
    {
        POSE temp;
        temp = setAxis(probot->lastPose);
        x = temp.point.x;
    }
    catch(const std::exception &e)
    {
        log_advanced(func_str + "Exception occurred, err: "  + QString(e.what()));
        x = 0.f;
    }
    catch(...)
    {
        log_advanced(func_str + "Exception occurred, err: unknown.");
        x = 0.f;
    }

    return x;
}

float Supervisor::getlastRoboty()
{
    QString func_str = "[SUPERVISOR][getlastRoboty] ";
    plog->write(func_str + "start func. params()");

    float y = 0.f;
    if(!probot)
    {
        log_advanced(func_str + "Error: probot is null.");
        return y;
    }

    try
    {
        POSE temp;
        temp = setAxis(probot->lastPose);
        y = temp.point.y;
    }
    catch(const std::exception &e)
    {
        log_advanced(func_str + "Exception occurred, err: "  + QString(e.what()));
        y = 0.f;
    }
    catch(...)
    {
        log_advanced(func_str + "Exception occurred, err: unknown.");
        y = 0.f;
    }

    return y;
}

float Supervisor::getlastRobotth()
{
    QString func_str = "[SUPERVISOR][getlastRobotth] ";
    plog->write(func_str + "start func. params()");

    float ang = 0.f;
    if(!probot)
    {
        log_advanced(func_str + "Error: probot is null.");
        return ang;
    }

    try
    {
        POSE temp;
        temp = setAxis(probot->lastPose);
        ang = temp.angle;
    }
    catch(const std::exception &e)
    {
        log_advanced(func_str + "Exception occurred, err: "  + QString(e.what()));
    }
    catch(...)
    {
        log_advanced(func_str + "Exception occurred, err: unknown.");
    }

    return ang;
}

QString Supervisor::getMapname()
{
    QString func_str = "[SUPERVISOR][getMapname] ";
    plog->write(func_str + "start func. params()");

    QString map_name = pmap->map_name;
    return map_name;
}

QString Supervisor::getMappath()
{
    QString func_str = "[SUPERVISOR][getMappath] ";
    plog->write(func_str + "start func. params()");

    QString map_path = pmap->map_path;
    return map_path;
}

int Supervisor::getMapWidth()
{
    QString func_str = "[SUPERVISOR][getMapWidth] ";
    plog->write(func_str + "start func. params()");

    int width = pmap->width;
    return width;
}

int Supervisor::getMapHeight()
{
    QString func_str = "[SUPERVISOR][getMapHeight] ";
    plog->write(func_str + "start func. params()");

    int height = pmap->height;
    return height;
}

float Supervisor::getGridWidth()
{
    QString func_str = "[SUPERVISOR][getGridWidth] ";
    plog->write(func_str + "start func. params()");

    float gridwidth = pmap->gridwidth;
    return gridwidth;
}

QList<int> Supervisor::getOrigin()
{
    QString func_str = "[SUPERVISOR][getOrigin] ";
    plog->write(func_str + "start func. params()");

    QList<int> temp;
    if(!pmap)
    {
        log_advanced(func_str + "Error: pmap is null.");
        return temp;
    }

    temp.push_back(pmap->origin[0]);
    temp.push_back(pmap->origin[1]);
    return temp;
}

void Supervisor::moveToServingTest(int group, QString name)
{
    QString func_str = "[SUPERVISOR][moveToServingTest] ";
    plog->write(func_str + "start func. params(group, name):" + QString::number(group) + "," + name);

    if(!probot)
    {
        log_advanced(func_str + "Error: probot is null.");
        return;
    }

    if(!mMain)
    {
        log_advanced(func_str + "Error: mMain is null.");
        return;
    }

    try
    {
        if(isRobotReady())
        {
            auto move_and_log = [&](const QString& locationType, const LOCATION& location, const QString& logSuffix)
            {
                stateMoving();
                probot->current_target = location;
                plog->write(func_str + locationType + " : move " + logSuffix);
            };

            if(name.left(8) == "Charging" || name == tr("충전위치"))
            {
                move_and_log("move to charging(test)", getChargingLocation(0), name);
            }
            else if(name.left(7) == "Resting"|| name == tr("대기위치"))
            {
                move_and_log("move to resting(test)", getRestingLocation(0), name);
            }
            else if(name.left(8) == "Cleaning"|| name == tr("퇴식위치"))
            {
                move_and_log("move to cleaning(test)", getCleaningLocation(0), name);
            }
            else
            {
                LOCATION temp_loc = getServingLocation(group, name);
                if(temp_loc.name.isEmpty())
                {
                    plog->write(func_str + " move to serving(test) : move failed: not found name " + name);
                    QMetaObject::invokeMethod(mMain,"notfoundlocation");
                }
                else
                {
                    probot->trays[0].empty = false;
                    probot->trays[0].location = temp_loc;
                    move_and_log("move to serving(test)", temp_loc, name);
                }
            }
        }
        else
        {
            plog->write(func_str + " move to serving(test) : robot state not ready " + name);
            QMetaObject::invokeMethod(mMain,"robotnotready");
        }
    }
    catch(const std::exception &e)
    {
        log_advanced(func_str + "Exception occurred, err: "  + QString(e.what()));
    }
    catch(...)
    {
        log_advanced(func_str + "Exception occurred, err: unknown.");
    }
}

void Supervisor::startPatrol(int num)
{
    QString func_str = "[SUPERVISOR][startPatrol] ";
    plog->write(func_str + "start func. params(num):" + QString::number(num));

    if(!mMain)
    {
        log_advanced(func_str + "Error: mMain is null.");
        return;
    }

    try
    {
        if(num > -1 && num < patrols.size())
        {
            if(isRobotReady())
            {
                plog->write(func_str + "start : " + patrols[num].name);
                patrol_mode = PATROL_NEW;
                current_patrol = patrols[num];
                stateMoving();
            }
            else
            {
                plog->write(func_str + "robot status Not Ready");
                QMetaObject::invokeMethod(mMain,"robotnotready");
            }
        }
        else
        {
            plog->write(func_str + "patrol not found " + QString::number(num));
            QMetaObject::invokeMethod(mMain,"notfoundpatrol");
        }
    }
    catch(const std::exception &e)
    {
        log_advanced(func_str + "Exception occurred, err: "  + QString(e.what()));
    }
    catch(...)
    {
        log_advanced(func_str + "Exception occurred, err: unknown.");
    }
}

//// *********************************** SLOTS *********************************** ////
void Supervisor::path_changed()
{
    QString func_str = "[SUPERVISOR][path_changed] ";
    plog->write(func_str + "start func. params()");

    if(!maph)
    {
        log_advanced(func_str + "Error: maph is null.");
        return;
    }

    try
    {
        maph->setMap();
    }
    catch(const std::exception &e)
    {
        log_advanced(func_str + "Exception occurred, err: "  + QString(e.what()));
    }
    catch(...)
    {
        log_advanced(func_str + "Exception occurred, err: unknown.");
    }
}

void Supervisor::camera_update()
{
    QString func_str = "[SUPERVISOR][camera_update] ";
    plog->write(func_str + "start func. params()");

    if(!mMain)
    {
        log_advanced(func_str + "Error: mMain is null.");
        return;
    }

    try
    {
        QMetaObject::invokeMethod(mMain, "updatecamera");
    }
    catch(const std::exception &e)
    {
        log_advanced(func_str + "Exception occurred, err: "  + QString(e.what()));
    }
    catch(...)
    {
        log_advanced(func_str + "Exception occurred, err: unknown.");
    }
}

void Supervisor::mapping_update()
{
    QString func_str = "[SUPERVISOR][mapping_update] ";
    plog->write(func_str + "start func. params()");

    if(!maph)
    {
        log_advanced(func_str + "Error: maph is null.");
        return;
    }

    try
    {
        maph->setMap();
    }
    catch(const std::exception &e)
    {
        log_advanced(func_str + "Exception occurred, err: "  + QString(e.what()));
    }
    catch(...)
    {
        log_advanced(func_str + "Exception occurred, err: unknown.");
    }
}

void Supervisor::checkShellFiles()
{
    QString func_str = "[SUPERVISOR][checkShellFiles] ";
    plog->write(func_str + "start func. params()");

    try
    {
        //need check
        //파일확인!
        QString file_path;
        QString path = QDir::homePath() + "/RB_MOBILE/log/ui_log";
        QDir directory(path);
        if(!directory.exists())
        {
            directory.mkpath(".");
            plog->write("[SUPERVISOR] ui_log directory not found. make new");
        }

        //auto_test.sh
        file_path = QDir::homePath() + "/RB_MOBILE/sh/startslam.sh";
        if(!QFile::exists(file_path))
        {
            plog->write("[SUPERVISOR] startslam.sh not found. make new");
            makeStartShell();
        }

        //kill_slam.sh
        file_path = QDir::homePath() + "/RB_MOBILE/sh/restartslam.sh";
        if(!QFile::exists(file_path))
        {
            plog->write("[SUPERVISOR] restartslam.sh not found. make new");
            makeKillShell();
        }

        //auto_kill.sh
        file_path = QDir::homePath() + "/RB_MOBILE/sh/killall.sh";
        if(!QFile::exists(file_path))
        {
            plog->write("[SUPERVISOR] killall.sh not found. make new");
            makeAllKillShell();
        }

        //auto_reset.sh
        file_path = QDir::homePath() + "/RB_MOBILE/sh/restartall.sh";
        if(!QFile::exists(file_path))
        {
            plog->write("[SUPERVISOR] restartall.sh not found. make new");
            makeKillSlam();
        }
    }
    catch(const std::exception &e)
    {
        log_advanced(func_str + "Exception occurred, err: "  + QString(e.what()));
    }
    catch(...)
    {
        log_advanced(func_str + "Exception occurred, err: unknown.");
    }
}

void Supervisor::makeKillShell()
{
    QString func_str = "[SUPERVISOR][makeKillShell] ";
    plog->write(func_str + "start func. params()");

    try
    {
        //need check
        //Make kill_slam.sh
        QString file_name = QDir::homePath() + "/RB_MOBILE/sh/restartslam.sh";
        QFile file(file_name);
        if (!file.open(QIODevice::ReadWrite))
        {
            throw std::runtime_error("Failed to open file: " + file_name.toStdString());
        }
        else
        {
            QTextStream stream(&file);
            stream << "#!/bin/bash" << "\n" << "\n";
            stream << "pid=`ps -ef | grep \"SLAMNAV\" | grep -v 'grep' | awk '{print $2}'`"<<"\n";
            stream << "if [ -z $pid ]" << "\n";
            stream << "then" << "\n";
            stream << "     echo \"SLAMNAV is not running\"" << "\n";
            stream << "else" << "\n";
            stream << "     kill -9 $pid" << "\n";
            stream << "fi" << "\n";
        }
        file.close();

        //Chmod
        QProcess process;
        process.setWorkingDirectory(QDir::homePath());
        process.start("chmod +x kill_slam.sh",QStringList(),QProcess::ReadWrite);

        if (!process.waitForFinished(2000)) // Increased wait time to ensure the process has enough time
        {
            throw std::runtime_error("Failed to execute chmod command.");
        }

        if (process.exitStatus() != QProcess::NormalExit || process.exitCode() != 0)
        {
            throw std::runtime_error("Chmod command failed with exit code: " + QString::number(process.exitCode()).toStdString());
        }
    }
    catch(const std::exception &e)
    {
        log_advanced(func_str + "Exception occurred, err: "  + QString(e.what()));
    }
    catch(...)
    {
        log_advanced(func_str + "Exception occurred, err: unknown.");
    }
}

void Supervisor::checkUpdate()
{
    QString func_str = "[SUPERVISOR][checkUpdate] ";
    plog->write(func_str + "start func. params()");

    //need check
    //server->checkUpdate();
}

void Supervisor::setlanguage(QString lan)
{
    QString func_str = "[SUPERVISOR][setlanguage] ";
    plog->write(func_str + "start func. params(lan):" + lan);

    try
    {
        QString path = "";
        if(lan == "KR")
        {

        }
        else if(lan=="US" || lan=="english")
        {
            path = QDir::homePath() + "/RB_MOBILE/release/lang_eddn.qm";
        }
        app->removeTranslator(translator);

        if(translator->load(path))
        {
            plog->write("[SUPERVISOR][setlanguage] setlanguage : " + lan + " SUCCESS ("+path+")");
            app->installTranslator(translator);
        }
        else
        {
            plog->write("[SUPERVISOR][setlanguage] setlanguage : " + lan + " FAILED ("+path+")");
        }
    }
    catch(const std::exception &e)
    {
        log_advanced(func_str + "Exception occurred, err: "  + QString(e.what()));
    }
    catch(...)
    {
        log_advanced(func_str + "Exception occurred, err: unknown.");
    }
}

bool Supervisor::checkNewUpdateProgram()
{
    QString func_str = "[SUPERVISOR][checkNewUpdateProgram] ";
    plog->write(func_str + "start func. params()");

    if(!server)
    {
        log_advanced(func_str + "Error: server is null.");
        return false;
    }

    if(server->update_list.size() > 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Supervisor::makeKillSlam()
{
    QString func_str = "[SUPERVISOR][makeKillSlam] ";
    plog->write(func_str + "start func. params()");

    try
    {
        //need check
        //Make kill_slam.sh
        QString file_name = QDir::homePath() + "/RB_MOBILE/sh/restartslam.sh";
        QFile file(file_name);
        if (!file.open(QIODevice::ReadWrite))
        {
            throw std::runtime_error("Failed to open file: " + file_name.toStdString());
        }
        else
        {
            QTextStream stream(&file);
            stream << "#!/bin/bash" << "\n" << "\n";
            stream << "pid=`ps -ef | grep \"SLAMNAV\" | grep -v 'grep' | awk '{print $2}'`"<<"\n";
            stream << "if [ -z $pid ]" << "\n";
            stream << "then" << "\n";
            stream << "     echo \"SLAMNAV is not running\"" << "\n";
            stream << "else" << "\n";
            stream << "     kill -9 $pid" << "\n";
            stream << "fi" << "\n";
        }
        file.close();

        //Chmod
        QProcess process;
        process.setWorkingDirectory(QDir::homePath() + "/RB_MOBILE/sh");
        process.start("chmod +x restartslam.sh",QStringList(),QProcess::ReadWrite);

        if (!process.waitForFinished(2000)) // Increased wait time to ensure the process has enough time
        {
            throw std::runtime_error("Failed to execute chmod command.");
        }

        if (process.exitStatus() != QProcess::NormalExit || process.exitCode() != 0)
        {
            throw std::runtime_error("Chmod command failed with exit code: " + QString::number(process.exitCode()).toStdString());
        }
    }
    catch(const std::exception &e)
    {
        log_advanced(func_str + "Exception occurred, err: "  + QString(e.what()));
    }
    catch(...)
    {
        log_advanced(func_str + "Exception occurred, err: unknown.");
    }
}

void Supervisor::makeStartShell()
{
    QString func_str = "[SUPERVISOR][makeStartShell] ";
    plog->write(func_str + "start func. params()");

    try
    {
        //need check
        //Make kill_slam.sh
        QString file_name = QDir::homePath() + "/RB_MOBILE/sh/startslam.sh";
        QFile file(file_name);
        if (!file.open(QIODevice::ReadWrite))
        {
            throw std::runtime_error("Failed to open file: " + file_name.toStdString());
        }
        else
        {
            QTextStream stream(&file);
            stream << "#!/bin/bash" << "\n" << "\n";
            stream << "while [ 1 ]"<<"\n";
            stream << "do"<<"\n";
            stream << "     pid=`ps -ef | grep \"SLAMNAV\" | grep -v 'grep' | awk '{print $2}'`"<<"\n";
            stream << "     if [ -z $pid ]" << "\n";
            stream << "     then" << "\n";
            stream << "         /home/odroid/RB_MOBILE/release/SLAMNAV" << "\n";
            stream << "     else" << "\n";
            stream << "         kill -9 $pid" << "\n";
            stream << "         /home/odroid/RB_MOBILE/release/SLAMNAV" << "\n";
            stream << "     fi" << "\n";
            stream << "done" << "\n";
        }
        file.close();

        //Chmod
        QProcess process;
        process.setWorkingDirectory(QDir::homePath()+"/RB_MOBILE/sh");
        process.start("chmod +x startslam.sh",QStringList(),QProcess::ReadWrite);

        if (!process.waitForFinished(2000)) // Increased wait time to ensure the process has enough time
        {
            throw std::runtime_error("Failed to execute chmod command.");
        }

        if (process.exitStatus() != QProcess::NormalExit || process.exitCode() != 0)
        {
            throw std::runtime_error("Chmod command failed with exit code: " + QString::number(process.exitCode()).toStdString());
        }
    }
    catch(const std::exception &e)
    {
        log_advanced(func_str + "Exception occurred, err: "  + QString(e.what()));
    }
    catch(...)
    {
        log_advanced(func_str + "Exception occurred, err: unknown.");
    }
}

void Supervisor::makeAllKillShell()
{
    QString func_str = "[SUPERVISOR][makeAllKillShell] ";
    plog->write(func_str + "start func. params()");

    try
    {
        //need check
        //Make kill_slam.sh
        QString file_name = QDir::homePath() + "/killall.sh";
        QFile file(file_name);
        if (!file.open(QIODevice::ReadWrite))
        {
            throw std::runtime_error("Failed to open file: " + file_name.toStdString());
        }
        else
        {
            QTextStream stream(&file);
            stream << "#!/bin/bash" << "\n" << "\n";

            stream << "pid=`ps -ef | grep \"startslam.sh\" | grep -v 'grep' | awk '{print $2}'`"<<"\n";
            stream << "if [ -z $pid ]" << "\n";
            stream << "then" << "\n";
            stream << "     echo \"startslam.sh is not running\"" << "\n";
            stream << "else" << "\n";
            stream << "     kill -9 $pid" << "\n";
            stream << "fi" << "\n";

            stream << "pid=`ps -ef | grep \"SLAMNAV\" | grep -v 'grep' | awk '{print $2}'`"<<"\n";
            stream << "if [ -z $pid ]" << "\n";
            stream << "then" << "\n";
            stream << "     echo \"SLAMNAV is not running\"" << "\n";
            stream << "else" << "\n";
            stream << "     kill -9 $pid" << "\n";
            stream << "fi" << "\n";

            stream << "pid=`ps -ef | grep \"ExtProcess\" | grep -v 'grep' | awk '{print $2}'`"<<"\n";
            stream << "if [ -z $pid ]" << "\n";
            stream << "then" << "\n";
            stream << "     echo \"ExtProcess is not running\"" << "\n";
            stream << "else" << "\n";
            stream << "     kill -9 $pid" << "\n";
            stream << "fi" << "\n";

            stream << "pid=`ps -ef | grep \"MAIN_MOBILE\" | grep -v 'grep' | awk '{print $2}'`"<<"\n";
            stream << "if [ -z $pid ]" << "\n";
            stream << "then" << "\n";
            stream << "     echo \"MAIN_MOBILE is not running\"" << "\n";
            stream << "else" << "\n";
            stream << "     kill -9 $pid" << "\n";
            stream << "fi" << "\n";
        }

        file.close();
        //Chmod
        QProcess process;
        process.setWorkingDirectory(QDir::homePath()+"/RB_MOBILE/sh");
        process.start("chmod +x killall.sh",QStringList(),QProcess::ReadWrite);

        if (!process.waitForFinished(2000)) // Increased wait time to ensure the process has enough time
        {
            throw std::runtime_error("Failed to execute chmod command.");
        }

        if (process.exitStatus() != QProcess::NormalExit || process.exitCode() != 0)
        {
            throw std::runtime_error("Chmod command failed with exit code: " + QString::number(process.exitCode()).toStdString());
        }
    }
    catch(const std::exception &e)
    {
        log_advanced(func_str + "Exception occurred, err: "  + QString(e.what()));
    }
    catch(...)
    {
        log_advanced(func_str + "Exception occurred, err: unknown.");
    }
}

//// *********************************** TIMER *********************************** ////
void Supervisor::onTimer()
{
    static int prev_local_state = -1;
    static int prev_motor_1_state = -1;
    static int prev_motor_2_state = -1;
    static int prev_charge_state = 0;
    static bool flag_annot_localization = false;

    static int lingbell_count = 0;
    static int timer_cnt = 0;
    static int current_cnt = 0;

    static int count_movewait = 0;
    static bool flag_movewait = false;

    // QML 오브젝트 매칭
    if(mMain == nullptr && object != nullptr)
    {
        setObject(object);
        setWindow(qobject_cast<QQuickWindow*>(object));
    }

    // check connected internet (intervel: 60s)
    if(timer_cnt++ > 300)
    {
        timer_cnt = 0;
        checker->getCurrentInterface();
    }

    switch(ui_state)
    {
        case UI_STATE_NONE:
        {
            //State : None
            //Robot 연결 안됨, 초기화 시작 전(프로그램 실행직후)
            if(ipc)
            {
                if(ipc->getConnection())
                {
                    ui_state = UI_STATE_INITAILIZING;
                    flag_annot_localization = false;
                    plog->write("[SUPERVISOR][TIMER] UI_STATE_NONE -> UI_STATE_INITAILIZING");
                }
                else
                {
                    clearStatus();
                    if(curPage != "page_init" && !debug_mode)
                    {
                        plog->write("[SUPERVISOR][TIMER] UI_STATE_NONE : ipc Disconnected -> go UI Init page");
                        QMetaObject::invokeMethod(mMain, "need_init");
                    }
                }
            }
            else
            {
                clearStatus();
                if(curPage != "page_init" && !debug_mode)
                {
                    plog->write("[SUPERVISOR][TIMER] UI_STATE_NONE Error: ipc is null -> go UI Init page");
                    QMetaObject::invokeMethod(mMain, "need_init");
                }
            }

            cmd_accept = false;
            break;
        }
        case UI_STATE_INITAILIZING:
        {
            if(debug_mode)
            {

            }

            if(probot->status_charge_connect == 1)
            {
                plog->write("[SUPERVISOR][TIMER] UI_STATE_INITAILIZING -> UI_STATE_CHARGING");
                ui_state = UI_STATE_CHARGING;
            }
            else if(probot->localization_confirm)
            {
                if(getMotorState() == READY)
                {
                    plog->write("[SUPERVISOR][TIMER] UI_STATE_INITAILIZING -> UI_STATE_RESTING");
                    ui_state = UI_STATE_RESTING;
                    flag_annot_localization = false;
                }
                else if(probot->localization_state != 2)
                {
                    probot->localization_confirm = false;
                }
                else
                {
                    if(curPage != "page_init" && curPage != "page_annotation")
                    {
                        plog->write("[SUPERVISOR][TIMER] UI_STATE_INITAILIZING : robot state not ready -> go UI Init page");
                        QMetaObject::invokeMethod(mMain, "need_init");
                    }
                    else if(curPage == "page_annotation")
                    {
                        if(!flag_annot_localization)
                        {
                            plog->write("[SUPERVISOR][TIMER] UI_STATE_INITAILIZING : robot state not ready -> go UI Init page");
                            QMetaObject::invokeMethod(mMain, "need_init");
                            flag_annot_localization = true;
                        }
                    }
                }
            }
            else
            {
                if(curPage != "page_init" && curPage != "page_annotation")
                {
                    plog->write("[SUPERVISOR][TIMER] UI_STATE_INITAILIZING : robot state not ready -> go UI Init page");
                    QMetaObject::invokeMethod(mMain, "need_init");
                }
                else if(curPage == "page_annotation")
                {
                    if(!flag_annot_localization)
                    {
                        plog->write("[SUPERVISOR][TIMER] UI_STATE_INITAILIZING : robot state not ready -> go UI Init page");
                        QMetaObject::invokeMethod(mMain, "need_init");
                        flag_annot_localization = true;
                    }
                }
            }
            break;
        }
        case UI_STATE_RESTING:
        {
            need_init = false;

            static int count_battery = 0;
            int cur_bat_percent = getBattery();
            if(cur_bat_percent < 20)
            {
                // 10min
                if(count_battery++ > 1200000/MAIN_THREAD)
                {
                    playVoice("error_battery");
                    count_battery = 0;
                }
            }
            else
            {
                count_battery = 0;
            }

            cmd_accept = false;
            if(probot->status_charge_connect == 1)
            {
                plog->write("[SUPERVISOR][TIMER] UI_STATE_RESTING -> UI_STATE_CHARGING");
                ui_state = UI_STATE_CHARGING;
            }
            else if(probot->motor[0].status > 1 || probot->motor[1].status > 1)
            {
                plog->write("[SUPERVISOR][TIMER] UI_STATE_RESTING: motor err, kill slam: " + QString().asprintf("(mo1:%d, mo2:%d)", probot->motor[0].status, probot->motor[1].status));
                killSLAM();
            }
            else if(pmap->call_queue.size() > 0)
            {
                plog->write("[SUPERVISOR][TIMER] UI_STATE_RESTING: Calling Detected " + QString::number(pmap->call_queue.size()) + " -> Moving");
                stateMoving();
            }
            else if(getSetting("setting", "SERVER", "use_server_call") == "true")
            {
                //not used
                if(probot->server_call_size > 0)
                {
                    probot->server_call_size = 0;
                }
                else if(probot->server_call_size == -1)
                {
                    probot->server_call_size = 0;
                }
            }
            break;
        }
        case UI_STATE_CHARGING:
        {
            patrol_mode = PATROL_NONE;
            if(probot->status_charge_connect == 0)
            {
                plog->write("[SUPERVISOR][TIMER] UI_STATE_CHARGING : Charge connector disconnected -> None");
                stateInit();
                QMetaObject::invokeMethod(mMain, "need_init");
                break;
            }
            else if(curPage != "page_charge" && !debug_mode)
            {
                plog->write("[SUPERVISOR][TIMER] UI_STATE_CHARGING -> go UI Charging page");
                QMetaObject::invokeMethod(mMain, "charging");
            }
            break;
        }
        case UI_STATE_MOVING:
        {
            static int timer_cnt2 = 0;
            if(probot->ui_fail_state == 1)
            {
                //local fail, no path, charging, motor error, motor connection
                if(!getMotorConnection(0) || !getMotorConnection(1))
                {
                    plog->write("[IPC] UI Fail State -> Motor Connection Error "+QString::asprintf("(%d, %d)",getMotorConnection(0),getMotorConnection(1)));
                }
                else if(getMotorState()==0)
                {
                    plog->write("[IPC] UI Fail State -> Motor Error "+QString::asprintf("(%d, %d)",probot->motor[0].status,probot->motor[1].status));
                }
                else if(getLocalizationState()!=LOCAL_READY)
                {
                    plog->write("[IPC] UI Fail State -> Localization Not ready"+QString::asprintf("(%d)",probot->localization_state));
                }
                else if(getChargeConnectStatus())
                {
                    plog->write("[IPC] UI Fail State -> Charging"+QString::asprintf("(%d, %d)",probot->status_charge,probot->status_charge_connect));
                }
                else
                {
                    plog->write("[IPC] UI Fail State -> No Path ?");
                }
                plog->write("[STATE] Moving : UI Fail State -> Kill Slam");
                killSLAM();
            }
            else if(probot->status_lock && getMotorState() == 0)
            {
                //need check
                plog->write(QString::number(probot->status_emo) +
                            QString::number(probot->status_lock) +
                            QString::number(probot->status_remote) +
                            QString::number(probot->status_power) +
                            QString::number(probot->motor[0].status) +
                            QString::number(probot->motor[1].status) +
                            QString::number(probot->battery_in) +
                            QString::number(probot->battery_out));
                plog->write("[STATE] Moving : MOTOR NOT READY -> Movefail");
                QMetaObject::invokeMethod(mMain, "movefail");
                ui_state = UI_STATE_MOVEFAIL;
            }
            else
            {
                if(getSetting("setting", "USE_UI", "use_current_pause")=="true")
                {
                    float current_threshold = getSetting("update", "DRIVING", "pause_motor_current").toFloat();
                    int check_count = getSetting("update", "DRIVING", "pause_current_ms").toInt()/MAIN_THREAD;
                    if(probot->motor[0].current > current_threshold || probot->motor[1].current > current_threshold)
                    {
                        if(current_cnt++ > check_count)
                        {
                            //MOTOR THRESHOLD IN. PAUSED!
                            if(probot->running_state != ROBOT_MOVING_PAUSED)
                            {
                                plog->write("[STATE] Moving : Auto Paused. Motor Current Over "+QString().asprintf("(0 : %f, 1 : %f, limit: %f)",probot->motor[0].current,probot->motor[1].current,current_threshold));
                                ipc->movePause();
                                is_test_moving = false;
                            }
                        }
                    }
                    else
                    {
                        current_cnt = 0;
                    }
                }

                if(probot->running_state == ROBOT_MOVING_READY)
                {
                    if(cmd_accept)
                    {
                        if(probot->current_target.name == "Charging0")
                        {
                            if(probot->is_patrol)
                            {
                                plog->write("[STATE] Moving : Arrived Location (Patrol Mode) "+probot->current_target.name);

                                //Play Voice
                                if(current_patrol.voice_mode != "none")
                                {
                                    playVoice(current_patrol.voice_file, current_patrol.voice_name, current_patrol.voice_mode, current_patrol.voice_language, current_patrol.voice_volume);
                                }
                                lingbell_count = 0;
                                ui_state = UI_STATE_PICKUP;
                            }
                            else if(probot->is_calling)
                            {
                                if(pmap->call_queue.size() > 0)
                                {
                                    plog->write("[STATE] Moving : Arrived Location (Calling Mode) "+probot->current_target.name+" -> Charging");
                                    pmap->call_queue.pop_front();
                                }
                                else
                                {
                                    probot->is_calling = false;
                                }

                                //Ling bell
                                if(getSetting("setting","CALL","use_lingbell") == "true" && probot->current_target.ling_id != "")
                                {
                                    plog->write("[STATE] Send Lingbell : "+probot->current_target.ling_id);
                                    call->send_call(probot->current_target.ling_id);
                                }
                                ui_state = UI_STATE_CHARGING;
                            }
                            else
                            {
                                plog->write("[STATE] Moving : Arrived Location "+probot->current_target.name+" -> Charging");
                                //Ling bell
                                if(getSetting("setting","CALL","use_lingbell") == "true" && probot->current_target.ling_id != "")
                                {
                                    plog->write("[STATE] Send Lingbell : "+probot->current_target.ling_id);
                                    call->send_call(probot->current_target.ling_id);
                                }
                                ui_state = UI_STATE_CHARGING;
                            }
                        }
                        else if(probot->current_target.name == "Resting0")
                        {
                            probot->call_moving_count = 0;
                            if(probot->is_patrol)
                            {
                                plog->write("[STATE] Moving : Arrived Location (Patrol Mode) "+probot->current_target.name);

                                //Play Voice
                                if(current_patrol.voice_mode != "none")
                                {
                                    //basic
                                    playVoice(current_patrol.voice_file, current_patrol.voice_name, current_patrol.voice_mode, current_patrol.voice_language, current_patrol.voice_volume);
                                }
                                lingbell_count = 0;
                                ui_state = UI_STATE_PICKUP;

                            }
                            else if(probot->is_calling)
                            {
                                if(pmap->call_queue.size() > 0)
                                {
                                    if(pmap->call_queue[0].left(7) == "Resting")
                                    {
                                        plog->write("[STATE] Moving : Arrived Location (Calling Mode) "+probot->current_target.name);
                                        pmap->call_queue.pop_front();
                                    }
                                    else
                                    {
                                        plog->write("[STATE] Moving : Arrived Location (Calling Mode) -> Max Calling Resting (Next : "+pmap->call_queue[0]+", CallCount : "+QString::number(probot->call_moving_count)+", MaxCall : "+QString::number(probot->max_moving_count)+")");
                                    }
                                }
                                else
                                {
                                    probot->is_calling = false;
                                    plog->write("[STATE] Moving : Arrived Location (Calling Mode?) "+probot->current_target.name);
                                }
                                //Ling bell
                                if(getSetting("setting","CALL","use_lingbell") == "true" && probot->current_target.ling_id != "")
                                {
                                    plog->write("[STATE] Send Lingbell : "+probot->current_target.ling_id);
                                    call->send_call(probot->current_target.ling_id);
                                }
                                QMetaObject::invokeMethod(mMain, "waitkitchen");
                                ui_state = UI_STATE_CLEANING;
                            }
                            else
                            {
                                plog->write("[STATE] Moving : Arrived Location "+probot->current_target.name);
                                //Ling bell
                                if(getSetting("setting","CALL","use_lingbell") == "true" && probot->current_target.ling_id != "")
                                {
                                    plog->write("[STATE] Send Lingbell : "+probot->current_target.ling_id);
                                    call->send_call(probot->current_target.ling_id);
                                }
                                QMetaObject::invokeMethod(mMain, "waitkitchen");
                                ui_state = UI_STATE_INITAILIZING;
                            }
                        }

                        else if(probot->current_target.name == "Cleaning0")
                        {
                            probot->call_moving_count = 0;
                            if(probot->is_patrol)
                            {
                                plog->write("[STATE] Moving : Arrived Location (Patrol Mode) "+probot->current_target.name);

                                //Play Voice
                                if(current_patrol.voice_mode != "none")
                                {
                                    //basic
                                    playVoice(current_patrol.voice_file, current_patrol.voice_name, current_patrol.voice_mode, current_patrol.voice_language, current_patrol.voice_volume);
                                }
                                lingbell_count = 0;
                                ui_state = UI_STATE_PICKUP;
                            }
                            else if(probot->is_calling)
                            {
                                if(pmap->call_queue.size() > 0)
                                {
                                    if(pmap->call_queue[0].left(8) == "Cleaning")
                                    {
                                        plog->write("[STATE] Moving : Arrived Location (Calling Mode) "+probot->current_target.name);
                                        pmap->call_queue.pop_front();
                                    }
                                    else
                                    {
                                        plog->write("[STATE] Moving : Arrived Location (Calling Mode) -> Max Calling Cleaning (Next : "+pmap->call_queue[0]+", CallCount : "+QString::number(probot->call_moving_count)+", MaxCall : "+QString::number(probot->max_moving_count)+")");
                                    }
                                }
                                else
                                {
                                    probot->is_calling = false;
                                    plog->write("[STATE] Moving : Arrived Location (Calling Mode?) "+probot->current_target.name);
                                }
                                //Ling bell
                                if(getSetting("setting","CALL","use_lingbell") == "true" && probot->current_target.ling_id != "")
                                {
                                    plog->write("[STATE] Send Lingbell : "+probot->current_target.ling_id);
                                    call->send_call(probot->current_target.ling_id);
                                }
                                QMetaObject::invokeMethod(mMain, "clearkitchen");
                                ui_state = UI_STATE_CLEANING;
                            }
                            else
                            {
                                //Ling bell
                                if(getSetting("setting","CALL","use_lingbell") == "true" && probot->current_target.ling_id != "")
                                {
                                    plog->write("[STATE] Send Lingbell : "+probot->current_target.ling_id);
                                    call->send_call(probot->current_target.ling_id);
                                }
                                plog->write("[STATE] Moving : Arrived Location "+probot->current_target.name);
                                QMetaObject::invokeMethod(mMain, "clearkitchen");
                                ui_state = UI_STATE_CLEANING;
                            }
                        }
                        else
                        {
                            if(probot->is_patrol)
                            {
                                plog->write("[STATE] Moving : Arrived Location (Patrol Mode) "+probot->current_target.name);

                                //Play Voice
                                if(current_patrol.voice_mode != "none")
                                {
                                    //basic
                                    playVoice(current_patrol.voice_file, current_patrol.voice_name, current_patrol.voice_mode, current_patrol.voice_language, current_patrol.voice_volume);
                                }
                                lingbell_count = 0;
                                ui_state = UI_STATE_PICKUP;
                            }
                            else if(probot->is_calling)
                            {
                                plog->write("[STATE] Moving : Arrived Location (Calling Mode) "+probot->current_target.name + " -> Pickup");
                                probot->call_moving_count++;
                                lingbell_count = 0;
                                ui_state = UI_STATE_PICKUP;
                            }
                            else
                            {
                                LOCATION curLoc;
                                bool match = false;

                                //트레이 클리어
                                probot->pickupTrays.clear();
                                for(int i=0; i<setting.tray_num; i++)
                                {
                                    //트레이 점유됨
                                    if(!probot->trays[i].empty)
                                    {
                                        if(!match)
                                        {
                                            match = true;
                                            curLoc = probot->trays[i].location;
                                        }

                                        if(isSameLocation(probot->trays[i].location,curLoc))
                                        {
                                            plog->write("[STATE] Tray Reset : "+QString::number(i)+", " + probot->trays[i].location.name);
                                            probot->trays[i].empty = true;
                                            probot->pickupTrays.push_back(i+1);
                                        }
                                    }
                                    else
                                    {
                                        LOCATION clearLoc;
                                        probot->trays[i].location = clearLoc;
                                    }
                                }
                                lingbell_count = 0;
                                plog->write("[STATE] Moving : Arrived Location "+probot->current_target.name+", "+curLoc.name+" -> Pickup");
                                ui_state = UI_STATE_PICKUP;
                            }
                        }
                        probot->current_target.name = "";
                        cmd_accept = false;
                    }
                    else
                    {
                        if(probot->current_target.name == "")
                        {
                                LOCATION cur_target;
                                probot->is_patrol = false;
                                probot->is_calling = false;

                                //1. 서빙 포인트 있는지 체크
                                int tray_num = -1;
                                for(int i=0; i<setting.tray_num; i++)
                                {
                                    if(!probot->trays[i].empty)
                                    {
                                        tray_num = i;
                                        break;
                                    }
                                }
                            if(tray_num > -1)
                            {
                                //서빙 포인트 세팅
                                cur_target = probot->trays[tray_num].location;
                                plog->write("[STATE] Moving : New Target (Serving) -> "+cur_target.name+" ( tray num : "+QString::number(tray_num)+" , tray location )");
                            }
                            else
                            {
                                //최대 이동 횟수 초과 시 -> 대기장소로 이동
                                if(probot->call_moving_count + 1 > probot->max_moving_count)
                                {
                                    probot->is_calling = true;
                                    plog->write("[STATE] Moving : Call Move Count is Max "+QString::number(probot->call_moving_count)+","+QString::number(probot->max_moving_count));
                                }
                                else
                                {
                                    //2. 들어온 콜 위치가 있는지 체크
                                    for(QString call:pmap->call_queue)
                                    {
                                        LOCATION temp_loc;
                                        if(call == "Charging0")
                                        {
                                            temp_loc = getChargingLocation(0);
                                        }
                                        else if(call == "Resting0")
                                        {
                                            temp_loc = getRestingLocation(0);
                                        }
                                        else if(call == "Cleaning0")
                                        {
                                            temp_loc = getCleaningLocation(0);
                                        }
                                        else
                                        {
                                            temp_loc = getServingLocation(call);
                                        }

                                        if(temp_loc.name != "")
                                        {
                                            cur_target = temp_loc;
                                            plog->write("[STATE] Moving : New Target (Calling) -> "+temp_loc.name+" ( call id : "+temp_loc.call_id+" )");
                                            probot->is_calling = true;
                                            break;
                                        }
                                        else
                                        {
                                            plog->write("[STATE] Moving : New Call but ID Wrong ("+pmap->call_queue[0]+")");
                                            pmap->call_queue.pop_front();
                                        }
                                    }

                                    if(cur_target.name == "")
                                    {
                                        if(getSetting("setting","SERVER","use_server_call") == "true")
                                        {

                                        }
                                        else
                                        {
                                            //3. PATROLLING
                                            if(patrol_mode == PATROL_NEW)
                                            {
                                                if(current_patrol.location.size()>1)
                                                {
                                                    if(current_patrol.type == "random")
                                                    {
                                                        //패트롤 위치 랜덤하게 지정
                                                        int temp = QRandomGenerator::global()->bounded(0,1000);

                                                        while(patrol_num == temp%(current_patrol.location.size()))
                                                        {
                                                            temp = QRandomGenerator::global()->bounded(0,1000);
                                                        }

                                                        patrol_num = temp%(current_patrol.location.size());
                                                        cur_target = current_patrol.location[patrol_num];
                                                        probot->is_patrol = true;
                                                        plog->write("[STATE] Moving : New Target (Patrol Random) -> "+cur_target.group_name+", "+cur_target.name);
                                                    }
                                                    else
                                                    {
                                                        if(++patrol_num >= current_patrol.location.size())
                                                        {
                                                            patrol_num = 0;
                                                        }

                                                        LOCATION temp_loc = current_patrol.location[patrol_num];
                                                        cur_target = current_patrol.location[patrol_num];
                                                        probot->is_patrol = true;
                                                        plog->write("[STATE] Moving : New Target (Patrol Sequence) -> "+cur_target.group_name+", "+ cur_target.name);
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }


                            count_moveto = 0;
                            if(cur_target.name == "")
                            {
                                plog->write("[STATE] Moving : No Target -> Back to Resting0");
                                probot->call_moving_count = 0;
                                cur_target = getRestingLocation(0);
                            }

                            //지정된 위치 실재하는 지 확인
                            bool match = false;
                            for(int i=0; i<pmap->serving_locations.size(); i++)
                            {
                                if(pmap->serving_locations[i].group == cur_target.group)
                                {
                                    if(pmap->serving_locations[i].name == cur_target.name)
                                    {
                                        match = true;
                                        break;
                                    }
                                }
                            }

                            if(cur_target.name == "Charging0" && pmap->charging_locations.size() > 0)
                            {
                                match = true;
                            }
                            if(cur_target.name == "Resting0" && pmap->resting_locations.size() > 0)
                            {
                                match = true;
                            }
                            if(cur_target.name == "Cleaning0" && pmap->cleaning_locations.size() > 0)
                            {
                                match = true;
                            }

                            if(match)
                            {
                                probot->current_target = cur_target;
                            }
                            else
                            {
                                plog->write("[STATE] Moving : Target not found -> "+cur_target.name+", "+QString::number(cur_target.group));
                                QMetaObject::invokeMethod(mMain, "nolocation");
                                ui_state = UI_STATE_RESTING;
                                break;
                            }
                        }
                        else
                        {
                            if(timer_cnt2%5==0)
                            {
                                plog->write("[DEBUG] Moving : "+QString::number(timer_cnt2)+", "+QString::number(count_moveto));
                                if(!probot->is_patrol && count_moveto++ > 5)
                                {
                                    //need check
                                    plog->write("[STATE] Moving : Robot not moving "+probot->current_target.name + " (");
                                    ipc->moveStop();
                                    QMetaObject::invokeMethod(mMain, "movefail");
                                    ui_state = UI_STATE_MOVEFAIL;
                                }
                                else
                                {
                                    int preset = probot->cur_preset;

                                    if(curPage == "page_annotation")
                                    {
                                        plog->write("[STATE] Moving : move to (test)"+probot->current_target.name+", preset "+QString::number(preset));
                                        ipc->moveToLocationTest(probot->current_target,preset);
                                    }
                                    else
                                    {
                                        if(probot->current_target.name.left(7) == "Resting" || probot->current_target.name.left(8) == "Cleaning")
                                        {
                                            if(probot->comeback_preset != 0)
                                            {
                                                preset = probot->comeback_preset;
                                            }
                                        }
                                        //무브 명령 보냄
                                        plog->write("[STATE] Moving : move to "+probot->current_target.name+", preset "+QString::number(preset));
                                        ipc->moveToLocation(probot->current_target,preset);
                                    }
                                }
                            }
                            timer_cnt2++;
                        }
                    }
                }
                else if(probot->running_state == ROBOT_MOVING_MOVING)
                {
                    // moving
                    if(!cmd_accept)
                    {
                        cmd_accept = true;
                        count_moveto = 0;
                        if(probot->is_calling)
                        {
                            plog->write("[STATE] Moving : Move Start (Calling)");
                        }
                        else
                        {
                            if(patrol_mode != PATROL_NONE)
                            {
                                plog->write("[STATE] Moving : Move Start (Patrol)");
                            }
                            else
                            {
                                plog->write("[STATE] Moving : Move Start (Serving)");
                            }
                        }
                        QMetaObject::invokeMethod(mMain, "movestart");
                    }
                }
                else if(probot->running_state == ROBOT_MOVING_NOT_READY)
                {
                    plog->write("[STATE] Moving : Running state not ready -> Movefail");
                    QMetaObject::invokeMethod(mMain, "movefail");
                    ui_state = UI_STATE_MOVEFAIL;
                }
                else
                {
                    if(!flag_movewait)
                    {
                        if(probot->running_state == ROBOT_MOVING_WAIT)
                        {
                            plog->write("[STATE] Moving : MOVE WAIT");
                            QMetaObject::invokeMethod(mMain, "movewait");
                            count_movewait = 0;
                            flag_movewait = true;
                        }
                        else if(probot->obs_in_path_state != 0 && probot->running_state == ROBOT_MOVING_MOVING)
                        {
                            plog->write("[STATE] Moving : EXCUSE ME");
                            QMetaObject::invokeMethod(mMain, "excuseme");
                            count_movewait = 0;
                            flag_movewait = true;
                        }
                    }
                }
            }
            break;
        }
        case UI_STATE_CLEANING:
        {
            probot->call_moving_count = 0;
            if(getSetting("setting","USE_UI","use_calling_notice") != "true")
            {
                if(probot->current_target.name != "Cleaning0")
                {
                    ui_state = UI_STATE_INITAILIZING;
                }
            }
            break;
        }
        case UI_STATE_PICKUP:
        {
            if(probot->ui_fail_state == 1)
            {
                //local fail, no path, charging, motor error, motor connection
                if(!getMotorConnection(0) || !getMotorConnection(1))
                {
                    plog->write("[IPC] UI Fail State -> Motor Connection Error "+QString::asprintf("(%d, %d)",getMotorConnection(0),getMotorConnection(1)));
                }
                else if(getMotorState()==0)
                {
                    plog->write("[IPC] UI Fail State -> Motor Error "+QString::asprintf("(%d, %d)",probot->motor[0].status,probot->motor[1].status));
                }
                else if(getLocalizationState()!=LOCAL_READY)
                {
                    plog->write("[IPC] UI Fail State -> Localization Not ready"+QString::asprintf("(%d)",probot->localization_state));
                }
                else if(getChargeConnectStatus())
                {
                    plog->write("[IPC] UI Fail State -> Charging"+QString::asprintf("(%d, %d)",probot->status_charge,probot->status_charge_connect));
                }
                else
                {
                    plog->write("[IPC] UI Fail State -> No Path ?");
                }
                plog->write("[STATE] Pickup : UI Fail State -> Kill Slam");
                killSLAM();
            }
            else if(probot->status_lock && getMotorState() == 0)
            {
                plog->write(QString::number(probot->status_emo)+QString::number(probot->status_lock)+QString::number(probot->status_remote)+QString::number(probot->status_power)+QString::number(probot->motor[0].status)+QString::number(probot->motor[1].status)+QString::number(probot->battery_in)+QString::number(probot->battery_out));
                plog->write("[STATE] Pickup : MOTOR NOT READY -> Movefail");
                QMetaObject::invokeMethod(mMain, "movefail");
                ui_state = UI_STATE_MOVEFAIL;
            }
            else if(probot->running_state == ROBOT_MOVING_PAUSED)
            {
                plog->write("[STATE] Pickup : Robot paused -> RESUME");
                ipc->moveResume();
            }

            //Call 강제귀환
            for(int i=0; i<pmap->call_queue.size(); i++)
            {
                if(pmap->call_queue[i].left(7) == "Resting" && getSetting("setting","CALL","force_resting") == "true")
                {
                    plog->write("[STATE] Pickup : Force Calling (Resting) -> Moving");
                    QString temp = pmap->call_queue[i];
                    pmap->call_queue.clear();
                    pmap->call_queue.append(temp);
                    stateMoving();
                    break;
                }
                else if(pmap->call_queue[i].left(8) == "Cleaning" && getSetting("setting","CALL","force_cleaning") == "true")
                {
                    plog->write("[STATE] Pickup : Force Calling (Cleaning) -> Moving");
                    QString temp = pmap->call_queue[i];
                    pmap->call_queue.clear();
                    pmap->call_queue.append(temp);
                    stateMoving();
                    break;
                }
            }

            //Ling bell
            if(!probot->is_patrol)
            {
                if(getSetting("setting","CALL","use_lingbell") == "true")
                {
                    if(lingbell_count == 0)
                    {
                        plog->write("[STATE] Send Lingbell : "+probot->current_target.ling_id);
                        call->send_call(probot->current_target.ling_id);
                        lingbell_count = 1;
                    }
                    if(getSetting("setting","CALL","use_lingbell_repeat") == "true")
                    {
                        if(lingbell_count++ > getSetting("setting","CALL","lingbell_time").toInt()*1000/MAIN_THREAD)
                        {
                            plog->write("[STATE] Send Lingbell : "+probot->current_target.ling_id);
                            call->send_call(probot->current_target.ling_id);
                            lingbell_count = 1;
                        }
                    }
                    else
                    {
                    }
                }
            }

            if(patrol_mode != PATROL_NONE)
            {
                if(probot->current_target.type == "Serving")
                {
                    if(current_patrol.arrive_page.mode == "calling" || current_patrol.arrive_page.mode == "pickup")
                    {
                        if(patrol_wait_count == 0)
                        {
                            plog->write("[STATE] Pickup -> UI Pickup");
                            QMetaObject::invokeMethod(mMain, "showpickup");
                        }
                        if(current_patrol.pass_time == 0)
                        {
                            //0이면 auto pass 안함
                            patrol_wait_count++;
                        }
                        else
                        {
                            if(patrol_wait_count++ < current_patrol.pass_time*1000/MAIN_THREAD)
                            {
                                break;
                            }
                            else
                            {
                                plog->write("[STATE] Pickup -> AUTO PASS");
                                stateMoving();
                            }
                        }
                    }
                    else
                    {
                        if(patrol_wait_count++ < current_patrol.wait_time*1000/MAIN_THREAD)
                        {
                            break;
                        }
                        else
                        {
                            plog->write("[STATE] Pickup -> AUTO PASS");
                            stateMoving();
                        }
                    }
                }
                else
                {
                    if(patrol_wait_count++ < current_patrol.wait_time*1000/MAIN_THREAD)
                    {
                        break;
                    }
                    else
                    {
                        stateMoving();
                        plog->write("[STATE] Pickup -> AUTO PASS");
                    }
                }
            }
            else
            {
                if(curPage != "page_pickup_calling" && curPage != "page_pickup" && !debug_mode)
                {
                    plog->write("[STATE] Pickup -> UI Pickup");
                    QMetaObject::invokeMethod(mMain, "showpickup");
                }
            }
            break;
        }

        case UI_STATE_MOVEFAIL:
        {
            if(isRobotReady(false))
            {
                plog->write("[STATE] Movefail : Wake Up Auto -> None");
                QMetaObject::invokeMethod(mMain, "movefail_wake");
                stateInit();
            }
            else
            {
                if(probot->localization_state != LOCAL_READY && prev_local_state != probot->localization_state)
                {
                    QMetaObject::invokeMethod(mMain, "movefail");
                }
                else if(probot->motor[0].status != 1 && prev_motor_1_state != probot->motor[0].status)
                {
                    QMetaObject::invokeMethod(mMain, "movefail");
                }
                else if(probot->motor[1].status != 1 && prev_motor_2_state != probot->motor[1].status)
                {
                    QMetaObject::invokeMethod(mMain, "movefail");
                }
                else if(probot->status_charge_connect == 1 && prev_charge_state != probot->status_charge_connect)
                {
                    plog->write("[STATE] Initializing : Charging Connected -> Charging");
                    ui_state = UI_STATE_CHARGING;
                }
            }
            patrol_mode = PATROL_NONE;
            probot->current_target.name = "";
            cmd_accept = false;
            break;
        }
    }

    //State 강제 변경조건
    if(!ipc->getConnection())
    {
        //Clear Status
        if(ui_state != UI_STATE_NONE)
        {
            plog->write("[STATE] "+curUiState()+" : SLAMNAV Disconnected -> None");
            QMetaObject::invokeMethod(mMain, "disconnected");
            stateInit();
        }
    }

    if(probot->localization_state != LOCAL_READY)
    {
        if(probot->localization_confirm)
        {
            plog->write("[STATE] "+curUiState()+" : Localization State is "+QString::number(probot->localization_state)+" -> Localization Confirm false");
            probot->localization_confirm = false;
            if(!debug_mode)
            {
                stateInit();
            }
        }
    }
    if(!debug_mode && (probot->motor[0].status>1 || probot->motor[1].status>1))
    {
        if(ui_state == UI_STATE_NONE || ui_state == UI_STATE_INITAILIZING)
        {
        }
        else
        {
            plog->write("[STATE] "+curUiState()+" : Motor State is "+QString::number(probot->motor[0].status)+","+QString::number(probot->motor[1].status)+" -> Init");
            stateInit();
        }
    }

    if(flag_movewait)
    {
        if(count_movewait++ > 15000/MAIN_THREAD)
        {
            //15초
            flag_movewait = false;
            count_movewait = 0;
        }
    }

    timer_cnt++;
    prev_motor_1_state = probot->motor[0].status;
    prev_motor_2_state = probot->motor[1].status;
    prev_local_state = probot->localization_state;
    prev_charge_state = probot->status_charge_connect;
}

QString Supervisor::curUiState()
{
    QString func_str = "[SUPERVISOR][curUiState] ";
    plog->write(func_str + "start func. params()");

    if(ui_state == UI_STATE_NONE)
    {
        return "None";
    }
    else if(ui_state == UI_STATE_INITAILIZING)
    {
        return "Initializing";
    }
    else if(ui_state == UI_STATE_SETTING)
    {
        return "Setting";
    }
    else if(ui_state == UI_STATE_RESTING)
    {
        return "Resting";
    }
    else if(ui_state == UI_STATE_CHARGING)
    {
        return "Charging";
    }
    else if(ui_state == UI_STATE_MOVING)
    {
        return "Moving";
    }
    else if(ui_state == UI_STATE_PICKUP)
    {
        return "Pickup";
    }
    else if(ui_state == UI_STATE_MOVEFAIL)
    {
        return "Movefail";
    }
    else if(ui_state == UI_STATE_CLEANING)
    {
        return "Cleaning";
    }
    else
    {
        return QString::number(ui_state);
    }
}

void Supervisor::passInit()
{
    QString func_str = "[SUPERVISOR][passInit] ";
    plog->write(func_str + "start func. params()");

    debug_mode = true;
    try
    {
        stateInit();
    }
    catch(const std::exception &e)
    {
        log_advanced(func_str + "Exception occurred, err: "  + QString(e.what()));
    }
    catch(...)
    {
        log_advanced(func_str + "Exception occurred, err: unknown.");
    }
}

LOCATION Supervisor::getServingLocation(int group, QString name)
{
    QString func_str = "[SUPERVISOR][getServingLocation] ";
    plog->write(func_str + "start func. params(group,name):" + QString::number(group) + "," + name);

    if(!pmap)
    {
        log_advanced(func_str + "Error: pmap is null.");
        return LOCATION();
    }

    if(group < 0 || group >= pmap->objects.size())
    {
        log_advanced(func_str + "Error: group is out of bounds.");
        return LOCATION();
    }

    for(const auto& loc : pmap->serving_locations)
    {
        if(loc.group == group && loc.name == name)
        {
            return loc;
        }
    }

    return LOCATION();
}

LOCATION Supervisor::getServingLocation(QString group, QString name)
{
    QString func_str = "[SUPERVISOR][getServingLocation] ";
    plog->write(func_str + "start func. params(group,name):" + group + "," + name);

    if(!pmap)
    {
        log_advanced(func_str + "Error: pmap is null.");
        return LOCATION();
    }

    for(const auto& loc : pmap->serving_locations)
    {
        if(loc.group_name == group && loc.name == name)
        {
            return loc;
        }
    }

    return LOCATION();
}

LOCATION Supervisor::getServingLocation(QString name)
{
    QString func_str = "[SUPERVISOR][getServingLocation] ";
    plog->write(func_str + "start func. params(name):" + name);

    if(!pmap)
    {
        log_advanced(func_str + "Error: pmap is null.");
        return LOCATION();
    }

    for(const auto& loc : pmap->serving_locations)
    {
        if(loc.name == name)
        {
            return loc;
        }
    }

    return LOCATION();
}

LOCATION Supervisor::getChargingLocation(int num)
{
    QString func_str = "[SUPERVISOR][getChargingLocation] ";
    plog->write(func_str + "start func. params(num):" + QString::number(num));

    if(!pmap)
    {
        log_advanced(func_str + "Error: pmap is null.");
        return LOCATION();
    }

    if(num < 0 || num >= pmap->charging_locations.size())
    {
        log_advanced(func_str + "Error: num is out of bounds.");
        return LOCATION();
    }

    return pmap->charging_locations[num];
}

LOCATION Supervisor::getRestingLocation(int num)
{
    QString func_str = "[SUPERVISOR][getRestingLocation] ";
    plog->write(func_str + "start func. params(num):" + QString::number(num));

    if(!pmap)
    {
        log_advanced(func_str + "Error: pmap is null.");
        return LOCATION();
    }

    if(num < 0 || num >= pmap->resting_locations.size())
    {
        log_advanced(func_str + "Error: num is out of bounds.");
        return LOCATION();
    }

    return pmap->resting_locations[num];
}

LOCATION Supervisor::getInitLocation(int num)
{
    QString func_str = "[SUPERVISOR][getInitLocation] ";
    plog->write(func_str + "start func. params(num):" + QString::number(num));

    if(!pmap)
    {
        log_advanced(func_str + "Error: pmap is null.");
        return LOCATION();
    }

    if(num < 0 || num >= pmap->init_locations.size())
    {
        log_advanced(func_str + "Error: num is out of bounds.");
        return LOCATION();
    }

    return pmap->init_locations[num];
}

LOCATION Supervisor::getCleaningLocation(int num)
{
    QString func_str = "[SUPERVISOR][getCleaningLocation] ";
    plog->write(func_str + "start func. params(num):" + QString::number(num));

    if(!pmap)
    {
        log_advanced(func_str + "Error: pmap is null.");
        return LOCATION();
    }

    if(num < 0 || num >= pmap->cleaning_locations.size())
    {
        log_advanced(func_str + "Error: num is out of bounds.");
        return LOCATION();
    }

    return pmap->cleaning_locations[num];
}

int Supervisor::getzipstate()
{
    QString func_str = "[SUPERVISOR][getzipstate] ";
    plog->write(func_str + "start func. params()");

    if(!zip)
    {
        log_advanced(func_str + "Error: zip is null.");
        return -1;
    }

    return zip->process;
}

void Supervisor::usbsave(QString usb, bool _ui, bool _slam, bool _config, bool _map, bool _log)
{
    QString func_str = "[SUPERVISOR][usbsave] ";
    plog->write(func_str + "start func. params(usb,_ui,_slam,_config,_map,_log)" +
                usb + "," +
                QString::number((int)_ui) + "," +
                QString::number((int)_slam) + "," +
                QString::number((int)_config) + "," +
                QString::number((int)_map) + "," +
                QString::number((int)_log));

    if(!zip)
    {
        log_advanced(func_str + "Error: zip is null.");
        return;
    }

    //need check
    zip->process = 0;
    std::string user = getenv("USER");
    std::string path = "/media/" + user;
    if(usb == "Desktop")
    {
        plog->write(func_str + " USB SAVE : Desktop");
        zip->makeZip(QDir::homePath() + "/Desktop", _ui, _slam, _config, _map, _log);
    }
    else if(usb == "")
    {
        if(usb_list.size() <= 0)
        {
            log_advanced(func_str + "USB SAVE ERROR : usb_list size = 0");
            return;
        }
        else
        {
            try
            {
                QString usb_list_str = usb_list.at(0);
                QString usb_path = QString::fromStdString(path) + "/" + usb_list_str;
                zip->makeZip(usb_path,_ui,_slam,_config,_map,_log);

                plog->write(func_str + " USB SAVE : " + usb_list_str);
            }
            catch(const std::exception &e)
            {
                log_advanced(func_str + "Exception occurred, err: "  + QString(e.what()));
            }
            catch(...)
            {
                log_advanced(func_str + "Exception occurred, err: unknown.");
            }
        }
    }
    else
    {
        try
        {
            QString usb_path = QString::fromStdString(path) + "/" + usb;
            zip->makeZip(usb_path,_ui,_slam,_config,_map,_log);

            plog->write(func_str + " USB SAVE : " + usb);
        }
        catch(const std::exception &e)
        {
            log_advanced(func_str + "Exception occurred, err: "  + QString(e.what()));
        }
        catch(...)
        {
            log_advanced(func_str + "Exception occurred, err: unknown.");
        }
    }
}

int Supervisor::getWifiNum()
{
    QString func_str = "[SUPERVISOR][getWifiNum] ";
    plog->write(func_str + "start func. params()");

    if(!probot)
    {
        log_advanced(func_str + "Error: probot is null.");
        return 0;
    }

    #ifdef EXTPROC_TEST
    return probot->wifi_list.size();
    #else
    return probot->wifi_map.size();
    #endif
}

QString Supervisor::getCurWifiSSID()
{
    QString func_str = "[SUPERVISOR][getCurWifiSSID] ";
    plog->write(func_str + "start func. params()");

    if(!probot)
    {
        log_advanced(func_str + "Error: probot is null.");
        return "";
    }

    #ifdef EXTPROC_TEST
    return probot->wifi_interface.ssid;
    #else
    return probot->wifi_ssid;
    #endif
}

float Supervisor::getICPRatio()
{
    QString func_str = "[SUPERVISOR][getICPRatio] ";
    plog->write(func_str + "start func. params()");

    if(!probot)
    {
        log_advanced(func_str + "Error: probot is null.");
        return 0.f;
    }

    return probot->inlier_ratio;
}

float Supervisor::getICPError()
{
    QString func_str = "[SUPERVISOR][getICPError] ";
    plog->write(func_str + "start func. params()");

    if(!probot)
    {
        log_advanced(func_str + "Error: probot is null.");
        return 0.f;
    }

    return probot->inlier_error;
}

QString Supervisor::getWifiSSID(int num)
{
    QString func_str = "[SUPERVISOR][getICPError] ";
    plog->write(func_str + "start func. params(num):" + QString::number(num));

    QString str = "unknown";
    if(!probot)
    {
        log_advanced(func_str + "Error: probot is null.");
        return str;
    }

    if(num < 0 || num >= probot->wifi_list.size())
    {
        log_advanced(func_str + "Error: num is out of bounds.");
        return str;
    }

    //need check
    #ifdef EXTPROC_TEST
    return QString::fromLocal8Bit(probot->wifi_list[num].ssid.toUtf8());
    #else
    if(num < probot->wifi_map.size() && num > -1)
    {
        QList<QString> keys = probot->wifi_map.keys();
        return probot->wifi_map[keys[num]].ssid;
        std::sort(keys.begin(),keys.end(),sortWifi);
        if(num < keys.size() && num > -1)
        {
            return probot->wifi_map[keys[num]].ssid;
        }
        else
        {
            return "unknown";
        }
    }
    else
    {
        return "unknown";
    }
    #endif
}

int Supervisor::getEthernetConnection()
{
    QString func_str = "[SUPERVISOR][getEthernetConnection] ";
    plog->write(func_str + "start func. params()");

    if(!probot)
    {
        log_advanced(func_str + "Error: probot is null.");
        return 0;
    }

    return probot->ethernet_interface.state;
}

int Supervisor::getInternetConnection()
{
    QString func_str = "[SUPERVISOR][getInternetConnection] ";
    plog->write(func_str + "start func. params()");

    if(!probot)
    {
        log_advanced(func_str + "Error: probot is null.");
        return 0;
    }

    if(probot->con_internet)
    {
        return 2;
    }
    else
    {
        return probot->con_internet2;
    }
}

int Supervisor::getWifiConnection()
{
    QString func_str = "[SUPERVISOR][getWifiConnection] ";
    plog->write(func_str + "start func. params()");

    if(!probot)
    {
        log_advanced(func_str + "Error: probot is null.");
        return 0;
    }

    return probot->wifi_interface.state;
}

void Supervisor::process_accept(int cmd)
{
    //need check
}

bool Supervisor::isRobotReady(bool print)
{
    QString func_str = "[SUPERVISOR][isRobotReady] ";
    plog->write(func_str + "start func. params(print):" + QString::number((int)print));

    if(!probot)
    {
        log_advanced(func_str + "Error: probot is null.");
        return false;
    }

    if(!debug_mode &&
            getStateMoving() == READY &&
            probot->localization_state == LOCAL_READY &&
            (probot->motor[0].status == 1 && probot->motor[1].status == 1) &&
            probot->status_charge_connect == 0)
    {
        return true;
    }
    else
    {
        if(print)
        {
            plog->write(func_str + "robot not Ready : " + QString::asprintf("DState: %d, RState : %d, LState : %d, LockState: %d, MState1: %d, MState2: %d, CState: %d, UState: %d",
                                                                         debug_mode,
                                                                         getStateMoving(),
                                                                         probot->localization_state,
                                                                         probot->status_lock,
                                                                         probot->motor[0].status,
                                                                         probot->motor[1].status,
                                                                         probot->status_charge_connect,
                                                                         (int)ui_state));
        }
        return false;
    }
}

void Supervisor::connect_wifi_fail(int reason, QString ssid)
{
    QString func_str = "[SUPERVISOR][connect_wifi_fail] ";
    plog->write(func_str + "start func. params(reason,ssid):" + QString::number(reason) + "," + ssid);

    if(!mMain)
    {
        log_advanced(func_str + "Error: mMain is null.");
        return;
    }

    try
    {
        QMetaObject::invokeMethod(mMain, "wifi_con_fail");
    }
    catch(const std::exception &e)
    {
        log_advanced(func_str + "Exception occurred, err: "  + QString(e.what()));
    }
    catch(...)
    {
        log_advanced(func_str + "Exception occurred, err: unknown.");
    }
}

void Supervisor::connect_wifi_success(QString ssid)
{
    QString func_str = "[SUPERVISOR][connect_wifi_fail] ";
    plog->write(func_str + "start func. params(ssid):" + ssid);

    if(!mMain)
    {
        log_advanced(func_str + "Error: mMain is null.");
        return;
    }

    try
    {
        QMetaObject::invokeMethod(mMain, "wifi_con_success");
    }
    catch(const std::exception &e)
    {
        log_advanced(func_str + "Exception occurred, err: "  + QString(e.what()));
    }
    catch(...)
    {
        log_advanced(func_str + "Exception occurred, err: unknown.");
    }
}

void Supervisor::set_wifi_success(QString ssid)
{
    QString func_str = "[SUPERVISOR][connect_wifi_fail] ";
    plog->write(func_str + "start func. params(ssid):" + ssid);

    if(!mMain)
    {
        log_advanced(func_str + "Error: mMain is null.");
        return;
    }

    try
    {
        QMetaObject::invokeMethod(mMain, "wifi_set_success");
    }
    catch(const std::exception &e)
    {
        log_advanced(func_str + "Exception occurred, err: "  + QString(e.what()));
    }
    catch(...)
    {
        log_advanced(func_str + "Exception occurred, err: unknown.");
    }
}

void Supervisor::set_wifi_fail(int reason,QString ssid)
{
    QString func_str = "[SUPERVISOR][connect_wifi_fail] ";
    plog->write(func_str + "start func. params(reason,ssid):" + QString::number(reason) + "," + ssid);

    if(!mMain)
    {
        log_advanced(func_str + "Error: mMain is null.");
        return;
    }

    try
    {
        QMetaObject::invokeMethod(mMain, "wifi_set_fail");
    }
    catch(const std::exception &e)
    {
        log_advanced(func_str + "Exception occurred, err: "  + QString(e.what()));
    }
    catch(...)
    {
        log_advanced(func_str + "Exception occurred, err: unknown.");
    }
}

void Supervisor::process_done(int cmd)
{
    //need check
}

void Supervisor::process_error(int cmd, int param)
{
    //need check
    #ifdef EXTPROC_TEST
    #else
    if(cmd == ExtProcess::PROCESS_CMD_CHECK_CONNECTION)
    {
        QMetaObject::invokeMethod(mMain, "checkwifidone");
    }
    else if(cmd == ExtProcess::PROCESS_CMD_CONNECT_WIFI)
    {
        QMetaObject::invokeMethod(mMain, "wififailed");
    }
    else if(cmd == ExtProcess::PROCESS_CMD_SET_WIFI_IP)
    {
        QMetaObject::invokeMethod(mMain, "setip_fail");
    }
    else if(cmd == ExtProcess::PROCESS_CMD_GIT_PULL)
    {
        extproc->git_reset();
    }
    else if(cmd == ExtProcess::PROCESS_CMD_GIT_UPDATE)
    {
        if(param == 0)
        {
            plog->write("[PROCESS] Update failed");
            QMetaObject::invokeMethod(mMain, "gitfailed");
        }
        else if(param == 1)
        {
            plog->write("[PROCESS] Update failed");
            QMetaObject::invokeMethod(mMain, "gitnewest");
        }
    }
    #endif
}

void Supervisor::process_timeout(int cmd)
{
    QString func_str = "[SUPERVISOR][connect_wifi_fail] ";
    plog->write(func_str + "start func. params(cmd):" + QString::number(cmd));

    if(!mMain)
    {
        log_advanced(func_str + "Error: mMain is null.");
        return;
    }

    try
    {
        //need check
        QMetaObject::invokeMethod(mMain, "checkwifidone");
    }
    catch(const std::exception &e)
    {
        log_advanced(func_str + "Exception occurred, err: "  + QString(e.what()));
    }
    catch(...)
    {
        log_advanced(func_str + "Exception occurred, err: unknown.");
    }
}

void Supervisor::connectWifi(QString ssid, QString passwd)
{
    QString func_str = "[SUPERVISOR][connectWifi] ";
    plog->write(func_str + "start func. params(ssid,passwd):" + ssid + "," + passwd);

    if(!checker)
    {
        log_advanced(func_str + "Error: checker is null.");
        return;
    }

    try
    {
        checker->connectWifi(ssid, passwd);
    }
    catch(const std::exception &e)
    {
        log_advanced(func_str + "Exception occurred, err: "  + QString(e.what()));
    }
    catch(...)
    {
        log_advanced(func_str + "Exception occurred, err: unknown.");
    }
}

void Supervisor::setEthernet(QString ip, QString subnet, QString gateway, QString dns1, QString dns2)
{
    QString func_str = "[SUPERVISOR][setEthernet] ";
    plog->write(func_str + "start func. params(ip,subnet,gateway,dns1,dns2):" +
                ip + "," +
                subnet + "," +
                gateway + "," +
                dns1 + "," +
                dns2);

    if(!checker)
    {
        log_advanced(func_str + "Error: checker is null.");
        return;
    }

    try
    {
        checker->setEthernet(ip, subnet, gateway, dns1, dns2);
    }
    catch(const std::exception &e)
    {
        log_advanced(func_str + "Exception occurred, err: "  + QString(e.what()));
    }
    catch(...)
    {
        log_advanced(func_str + "Exception occurred, err: unknown.");
    }
}

void Supervisor::setWifiDHCP()
{
    QString func_str = "[SUPERVISOR][setWifiDHCP] ";
    plog->write(func_str + "start func. params()");

    if(!probot)
    {
        log_advanced(func_str + "Error: probot is null.");
        return;
    }

    if(!checker)
    {
        log_advanced(func_str + "Error: checker is null.");
        return;
    }

    try
    {
        checker->setIP(false, probot->wifi_interface.ssid);
    }
    catch(const std::exception &e)
    {
        log_advanced(func_str + "Exception occurred, err: "  + QString(e.what()));
    }
    catch(...)
    {
        log_advanced(func_str + "Exception occurred, err: unknown.");
    }
}

void Supervisor::setWifi(QString ssid, QString ip, QString subnet, QString gateway, QString dns1, QString dns2)
{
    QString func_str = "[SUPERVISOR][setWifi] ";
    plog->write(func_str + "start func. params(ssid,ip,subnet,gateway,dns1,dns2):" +
                ssid + "," +
                ip + "," +
                subnet + "," +
                gateway + "," +
                dns1 + "," +
                dns2);

    if(!probot)
    {
        log_advanced(func_str + "Error: probot is null.");
        return;
    }

    if(!checker)
    {
        log_advanced(func_str + "Error: checker is null.");
        return;
    }

    if(ssid == "")
    {
        ssid = probot->wifi_interface.ssid;
    }

    try
    {
        checker->setIP(true, ssid, ip, subnet, gateway, dns1, dns2);
    }
    catch(const std::exception &e)
    {
        log_advanced(func_str + "Exception occurred, err: "  + QString(e.what()));
    }
    catch(...)
    {
        log_advanced(func_str + "Exception occurred, err: unknown.");
    }
}

void Supervisor::setWifi(QString ip, QString gateway, QString dns)
{
    #ifdef EXTPROC_TEST
    //checker->setIP(probot->wifi_interface.ssid,ip,
    #else
    plog->write("[COMMAND] setWifi : "+ip+", "+gateway+", "+dns+" (cur Connection : "+probot->wifi_connection+", SSID : "+probot->wifi_ssid+")");
    ExtProcess::Command temp;
    temp.cmd = ExtProcess::PROCESS_CMD_SET_WIFI_IP;
    memcpy(temp.params,ip.toUtf8(),sizeof(char)*100);
    memcpy(temp.params2,gateway.toUtf8(),sizeof(char)*100);
    memcpy(temp.params3,dns.toUtf8(),sizeof(char)*100);
    extproc->set_command(temp);
    #endif
}

QString Supervisor::getcurIPMethod()
{
    QString func_str = "[SUPERVISOR][getcurIPMethod] ";
    plog->write(func_str + "start func. params()");

    if(!probot)
    {
        log_advanced(func_str + "Error: probot is null.");
        return "";
    }

    return probot->wifi_interface.method;
}

QString Supervisor::getcurIP()
{
    QString func_str = "[SUPERVISOR][getcurIP] ";
    plog->write(func_str + "start func. params()");

    if(!probot)
    {
        log_advanced(func_str + "Error: probot is null.");
        return "";
    }

    return probot->wifi_interface.ipv4;
}

QString Supervisor::getcurGateway()
{
    QString func_str = "[SUPERVISOR][getcurGateway] ";
    plog->write(func_str + "start func. params()");

    if(!probot)
    {
        log_advanced(func_str + "Error: probot is null.");
        return "";
    }

    return probot->wifi_interface.gateway;
}

QString Supervisor::getcurNetmask()
{
    QString func_str = "[SUPERVISOR][getcurNetmask] ";
    plog->write(func_str + "start func. params()");

    if(!probot)
    {
        log_advanced(func_str + "Error: probot is null.");
        return "";
    }

    return probot->wifi_interface.netmask;
}

QString Supervisor::getcurDNS2()
{
    QString func_str = "[SUPERVISOR][getcurDNS2] ";
    plog->write(func_str + "start func. params()");

    if(!probot)
    {
        log_advanced(func_str + "Error: probot is null.");
        return "";
    }

    return probot->wifi_interface.dns2;
}

QString Supervisor::getcurDNS()
{
    QString func_str = "[SUPERVISOR][getcurDNS] ";
    plog->write(func_str + "start func. params()");

    if(!probot)
    {
        log_advanced(func_str + "Error: probot is null.");
        return "";
    }

    return probot->wifi_interface.dns1;
}

QString Supervisor::getethernetIP()
{
    QString func_str = "[SUPERVISOR][getethernetIP] ";
    plog->write(func_str + "start func. params()");

    if(!probot)
    {
        log_advanced(func_str + "Error: probot is null.");
        return "";
    }

    return probot->ethernet_interface.ipv4;
}

QString Supervisor::getethernetNetmask()
{
    QString func_str = "[SUPERVISOR][getethernetNetmask] ";
    plog->write(func_str + "start func. params()");

    if(!probot)
    {
        log_advanced(func_str + "Error: probot is null.");
        return "";
    }

    return probot->ethernet_interface.netmask;
}

QString Supervisor::getethernetGateway()
{
    QString func_str = "[SUPERVISOR][getethernetGateway] ";
    plog->write(func_str + "start func. params()");

    if(!probot)
    {
        log_advanced(func_str + "Error: probot is null.");
        return "";
    }

    return probot->ethernet_interface.gateway;
}

QString Supervisor::getethernetDNS()
{
    QString func_str = "[SUPERVISOR][getethernetDNS] ";
    plog->write(func_str + "start func. params()");

    if(!probot)
    {
        log_advanced(func_str + "Error: probot is null.");
        return "";
    }

    return probot->ethernet_interface.dns1;
}

QString Supervisor::getethernetDNS2()
{
    QString func_str = "[SUPERVISOR][getethernetDNS2] ";
    plog->write(func_str + "start func. params()");

    if(!probot)
    {
        log_advanced(func_str + "Error: probot is null.");
        return "";
    }

    return probot->ethernet_interface.dns2;
}

void Supervisor::getAllWifiList()
{
    QString func_str = "[SUPERVISOR][getAllWifiList] ";
    plog->write(func_str + "start func. params()");

    if(!checker)
    {
        log_advanced(func_str + "Error: checker is null.");
        return;
    }

    try
    {
        checker->getWifiList(true);
    }
    catch(const std::exception &e)
    {
        log_advanced(func_str + "Exception occurred, err: "  + QString(e.what()));
    }
    catch(...)
    {
        log_advanced(func_str + "Exception occurred, err: unknown.");
    }
}

bool Supervisor::getWifiSecurity(QString ssid)
{
    QString func_str = "[SUPERVISOR][getWifiSecurity] ";
    plog->write(func_str + "start func. params(ssid):" + ssid);

    if(!probot)
    {
        log_advanced(func_str + "Error: probot is null.");
        return false;
    }

    for(ST_WIFI w : probot->wifi_list)
    {
        if(w.ssid == ssid)
        {
            return w.security;
        }
    }
    return false;
}

int Supervisor::getWifiLevel()
{
    QString func_str = "[SUPERVISOR][getWifiLevel] ";
    plog->write(func_str + "start func. params()");

    if(!probot)
    {
        log_advanced(func_str + "Error: probot is null.");
        return 0;
    }

    for(ST_WIFI w : probot->wifi_list)
    {
        if(w.ssid == probot->wifi_interface.ssid)
        {
            return w.level;
        }
    }
    return 0;
}

int Supervisor::getWifiLevel(QString ssid)
{
    QString func_str = "[SUPERVISOR][getWifiLevel] ";
    plog->write(func_str + "start func. params(ssid):" + ssid);

    if(!probot)
    {
        log_advanced(func_str + "Error: probot is null.");
        return 0;
    }

    for(ST_WIFI w : probot->wifi_list)
    {
        if(w.ssid == ssid)
        {
            return w.level;
        }
    }
    return 0;
}

int Supervisor::getWifiRate(QString ssid)
{
    QString func_str = "[SUPERVISOR][getWifiRate] ";
    plog->write(func_str + "start func. params(ssid):" + ssid);

    if(!probot)
    {
        log_advanced(func_str + "Error: probot is null.");
        return 0;
    }

    return probot->wifi_map[ssid].rate;
}

bool Supervisor::getWifiInuse(QString ssid)
{
    QString func_str = "[SUPERVISOR][getWifiInuse] ";
    plog->write(func_str + "start func. params(ssid):" + ssid);

    if(!probot)
    {
        log_advanced(func_str + "Error: probot is null.");
        return false;
    }

    if(ssid == probot->wifi_interface.ssid)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Supervisor::cleanTray()
{
    QString func_str = "[SUPERVISOR][cleanTray] ";
    plog->write(func_str + "start func. params()");

    if(ui_state == UI_STATE_CLEANING)
    {
        ui_state = UI_STATE_INITAILIZING;
    }
    else
    {
        try
        {
            stateInit();
        }
        catch(const std::exception &e)
        {
            log_advanced(func_str + "Exception occurred, err: "  + QString(e.what()));
        }
        catch(...)
        {
            log_advanced(func_str + "Exception occurred, err: unknown.");
        }
    }
}

int Supervisor::getCallQueueSize()
{
    QString func_str = "[SUPERVISOR][getCallQueueSize] ";
    plog->write(func_str + "start func. params()");

    if(!pmap)
    {
        log_advanced(func_str + "Error: pmap is null.");
        return 0;
    }

    return pmap->call_queue.size();
}

void Supervisor::checkTravelline()
{
    QString func_str = "[SUPERVISOR][checkTravelline] ";
    plog->write(func_str + "start func. params()");

    if(!pmap)
    {
        log_advanced(func_str + "Error: pmap is null.");
        return;
    }

    pmap->tline_issue = 0;

    try
    {
        ipc->set_cmd(ROBOT_CMD_CHECK_TRAVEL_LINE, "Check Travelline");
    }
    catch(const std::exception &e)
    {
        log_advanced(func_str + "Exception occurred, err: "  + QString(e.what()));
    }
    catch(...)
    {
        log_advanced(func_str + "Exception occurred, err: unknown.");
    }
}

void Supervisor::confirmLocalization()
{
    QString func_str = "[SUPERVISOR][confirmLocalization] ";
    plog->write(func_str + "start func. params()");

    if(!probot)
    {
        log_advanced(func_str + "Error: probot is null.");
        return;
    }

    probot->localization_confirm = true;
    debug_mode = false;
}

void Supervisor::confirmLocalizationAnnot()
{
    QString func_str = "[SUPERVISOR][confirmLocalizationAnnot] ";
    plog->write(func_str + "start func. params()");

    if(!probot)
    {
        log_advanced(func_str + "Error: probot is null.");
        return;
    }

    probot->localization_confirm = true;
}

void Supervisor::clearStatusAll()
{
    QString func_str = "[SUPERVISOR][clearStatusAll] ";
    plog->write(func_str + "start func. params()");

    if(!probot)
    {
        log_advanced(func_str + "Error: probot is null.");
        return;
    }

    probot->status_power = 0;
    probot->status_emo = 0;
    probot->status_remote = 0;
    probot->status_charge = 0;
    probot->status_charge_connect = 0;
    probot->status_lock = 0;
    probot->bat_list.clear();
    probot->battery_percent = 0;
    probot->battery = 0.;
    probot->battery_in = 0;
    probot->battery_out = 0;
    probot->battery_cur = 0;
    probot->power = 0;
    probot->total_power = 0;

    probot->motor[0].connection = false;
    probot->motor[0].current = 0;
    probot->motor[0].motor_temp = 0;
    probot->motor[0].status = 0;
    probot->motor[0].temperature = 0;
    probot->motor[1].connection = false;
    probot->motor[1].current = 0;
    probot->motor[1].motor_temp = 0;
    probot->motor[1].status = 0;
    probot->motor[1].temperature = 0;

    probot->multirobot_state = 0;
    probot->localization_state = 0;
    probot->running_state = 0;
    probot->obs_state = 0;
    probot->ui_fail_state = 0;
    probot->obs_in_path_state = 0;
    probot->robot_preset = 0;
    probot->drawing_state = 0;
    probot->map_rotate_angle = 0;

    probot->localization_confirm = false;
    probot->curPose.point.x = 0;
    probot->curPose.point.y = 0;
    probot->curPose.angle = 0;
    probot->lastPose.point.x = 0;
    probot->lastPose.point.y = 0;
    probot->lastPose.angle = 0;
    probot->pickupTrays.clear();
    probot->curTarget.point.x = 0;
    probot->curTarget.point.y = 0;
    probot->curTarget.angle = 0;
    probot->pathSize = 0;
    probot->curPath.clear();
    probot->localpathSize = 0;
    probot->localPath[0].point.x = 0;
    probot->localPath[0].point.y = 0;
    probot->localPath[0].angle = 0;
    probot->localPath[1].point.x = 0;
    probot->localPath[1].point.y = 0;
    probot->localPath[1].angle = 0;
    probot->localPath[2].point.x = 0;
    probot->localPath[2].point.y = 0;
    probot->localPath[2].angle = 0;
    probot->localPath[3].point.x = 0;
    probot->localPath[3].point.y = 0;
    probot->localPath[3].angle = 0;

    //mine
//    probot->trays.clear();
    probot->is_calling = false;
    probot->is_patrol = false;
    probot->curLocation = LOCATION{};

    probot->call_moving_count = 0;

    probot->server_call_size = 0;
    probot->server_call_location = -1;
}

void Supervisor::resetLocalization()
{
    QString func_str = "[SUPERVISOR][resetLocalization] ";
    plog->write(func_str + "start func. params()");

    if(!probot)
    {
        log_advanced(func_str + "Error: probot is null.");
        return;
    }

    debug_mode = false;
    probot->localization_confirm = false;
}

void Supervisor::resetLocalizationConfirm()
{
    QString func_str = "[SUPERVISOR][resetLocalizationConfirm] ";
    plog->write(func_str + "start func. params()");

    if(!probot)
    {
        log_advanced(func_str + "Error: probot is null.");
        return;
    }

    probot->localization_confirm = false;
}

void Supervisor::clearStatus()
{
    QString func_str = "[SUPERVISOR][clearStatus] ";
    plog->write(func_str + "start func. params()");

    if(!pmap)
    {
        log_advanced(func_str + "Error: pmap is null.");
        return;
    }

    if(!probot)
    {
        log_advanced(func_str + "Error: probot is null.");
        return;
    }

    probot->localization_state = 0;
    probot->motor[0].status = 0;
    probot->motor[1].status = 0;
    pmap->call_queue.clear();
}

void Supervisor::stateMoving()
{
    QString func_str = "[SUPERVISOR][stateMoving] ";
    plog->write(func_str + "start func. params()");

    if(!probot)
    {
        log_advanced(func_str + "Error: probot is null.");
        return;
    }

    ui_state = UI_STATE_MOVING;
    count_moveto = 0;
    cmd_accept = false;
    patrol_wait_count = 0;
    probot->current_target.name = "";
    probot->call_moving_count = 0;
}

void Supervisor::stateInit()
{
    QString func_str = "[SUPERVISOR][stateInit] ";
    plog->write(func_str + "start func. params()");

    if(!pmap)
    {
        log_advanced(func_str + "Error: pmap is null.");
        return;
    }

    if(!probot)
    {
        log_advanced(func_str + "Error: probot is null.");
        return;
    }

    if(ui_state != UI_STATE_NONE)
    {
        ui_state = UI_STATE_NONE;
    }

    pmap->call_queue.clear();

    patrol_mode = PATROL_NONE;
    current_patrol = ST_PATROL();

    probot->is_calling = false;
    probot->is_patrol = false;
    probot->current_target.name = "";
    for(int i=0; i<probot->trays.size(); i++)
    {
        probot->trays[i].empty = true;
    }

    try
    {
        ipc->moveStop();
    }
    catch(const std::exception &e)
    {
        log_advanced(func_str + "Exception occurred, err: "  + QString(e.what()));
    }
    catch(...)
    {
        log_advanced(func_str + "Exception occurred, err: unknown.");
    }
}

void Supervisor::killSLAM()
{
    QString func_str = "[SUPERVISOR][killSLAM] ";
    plog->write(func_str + "start func. params()");

    try
    {
        clearStatusAll();
        stateInit();
    }
    catch(const std::exception &e)
    {
        log_advanced(func_str + "Exception occurred, err: "  + QString(e.what()));
    }
    catch(...)
    {
        log_advanced(func_str + "Exception occurred, err: unknown.");
    }
}

void Supervisor::start_folder_clear()
{
    QString func_str = "[SUPERVISOR][start_folder_clear] ";
    plog->write(func_str + "start func. params()");

    //maps 폴더 지움.
    QMetaObject::invokeMethod(mMain, "setClear",Qt::DirectConnection,
                              Q_ARG(QVariant,QVariant().fromValue(QDateTime::currentDateTime().toString("[yyyy-MM-dd hh:mm:ss]") + " /RB_MOBILE/maps directory : remove")),
                              Q_ARG(QVariant,QVariant().fromValue(1)));

    QString path_maps = QDir::homePath()+"/RB_MOBILE/maps";
    QDir dir_maps(path_maps);
    if(dir_maps.removeRecursively())
    {
        plog->write(func_str + "Reset Clear : Remove maps");
        QMetaObject::invokeMethod(mMain, "setClear",Qt::DirectConnection,
                                  Q_ARG(QVariant,QVariant().fromValue(QDateTime::currentDateTime().toString("[yyyy-MM-dd hh:mm:ss]")+" /RB_MOBILE/maps directory : remove")),
                                  Q_ARG(QVariant,QVariant().fromValue(2)));
    }
    else
    {
        plog->write(func_str + "Reset Clear : Remove maps failed");
        QMetaObject::invokeMethod(mMain, "setClear",Qt::DirectConnection,
                                  Q_ARG(QVariant,QVariant().fromValue(QDateTime::currentDateTime().toString("[yyyy-MM-dd hh:mm:ss]")+" /RB_MOBILE/maps directory : remove")),
                                  Q_ARG(QVariant,QVariant().fromValue(3)));
    }
    QDir().mkdir(path_maps);

    //temp 폴더 지움.
    QString path_temp = QDir::homePath()+"/RB_MOBILE/temp";
    QDir dir_temp(path_temp);
    if(dir_temp.removeRecursively())
    {
        plog->write(func_str + "Reset Clear : Remove temp");
        QMetaObject::invokeMethod(mMain, "setClear",Qt::DirectConnection,
                                  Q_ARG(QVariant,QVariant().fromValue(QDateTime::currentDateTime().toString("[yyyy-MM-dd hh:mm:ss]")+" /RB_MOBILE/temp directory : remove")),
                                  Q_ARG(QVariant,QVariant().fromValue(2)));
    }
    else
    {
        plog->write(func_str + "Reset Clear : Remove temp failed");
        QMetaObject::invokeMethod(mMain, "setClear",Qt::DirectConnection,
                                  Q_ARG(QVariant,QVariant().fromValue(QDateTime::currentDateTime().toString("[yyyy-MM-dd hh:mm:ss]")+" /RB_MOBILE/temp directory : remove")),
                                  Q_ARG(QVariant,QVariant().fromValue(3)));
    }

    //patrol 폴더 지움.
    QString path_patrol = QDir::homePath()+"/RB_MOBILE/patrol";
    QDir dir_patrol(path_patrol);
    if(dir_patrol.removeRecursively())
    {
        plog->write(func_str + "Reset Clear : Remove patrol");
        QMetaObject::invokeMethod(mMain, "setClear",Qt::DirectConnection,
                                  Q_ARG(QVariant,QVariant().fromValue(QDateTime::currentDateTime().toString("[yyyy-MM-dd hh:mm:ss]")+" /RB_MOBILE/patrol directory : remove")),
                                  Q_ARG(QVariant,QVariant().fromValue(2)));
    }
    else
    {
        plog->write(func_str + "Reset Clear : Remove patrol failed");
        QMetaObject::invokeMethod(mMain, "setClear",Qt::DirectConnection,
                                  Q_ARG(QVariant,QVariant().fromValue(QDateTime::currentDateTime().toString("[yyyy-MM-dd hh:mm:ss]")+" /RB_MOBILE/patrol directory : remove")),
                                  Q_ARG(QVariant,QVariant().fromValue(3)));
    }

    //myID 등  robot_config.ini 수정
    //config 폴더 지움.
    QString path_config = QDir::homePath()+"/RB_MOBILE/config";
    QDir dir_config(path_config);
    if(dir_config.removeRecursively())
    {
        plog->write(func_str + "Reset Clear : Remove config");
        QMetaObject::invokeMethod(mMain, "setClear",Qt::DirectConnection,
                                  Q_ARG(QVariant,QVariant().fromValue(QDateTime::currentDateTime().toString("[yyyy-MM-dd hh:mm:ss]")+" /RB_MOBILE/config directory : remove")),
                                  Q_ARG(QVariant,QVariant().fromValue(2)));
    }
    else
    {
        plog->write(func_str + "Reset Clear : Remove config failed");
        QMetaObject::invokeMethod(mMain, "setClear",Qt::DirectConnection,
                                  Q_ARG(QVariant,QVariant().fromValue(QDateTime::currentDateTime().toString("[yyyy-MM-dd hh:mm:ss]")+" /RB_MOBILE/config directory : remove")),
                                  Q_ARG(QVariant,QVariant().fromValue(3)));
    }

    QDir().mkdir(path_config);
    makeRobotINI();
    QMetaObject::invokeMethod(mMain, "setClear",Qt::DirectConnection,
                              Q_ARG(QVariant,QVariant().fromValue(QDateTime::currentDateTime().toString("[yyyy-MM-dd hh:mm:ss]")+" /RB_MOBILE/config directory : make new config")),
                              Q_ARG(QVariant,QVariant().fromValue(2)));

    //sh 파일 복구?
    checkShellFiles();
    QMetaObject::invokeMethod(mMain, "setClear",Qt::DirectConnection,
                              Q_ARG(QVariant,QVariant().fromValue(QDateTime::currentDateTime().toString("[yyyy-MM-dd hh:mm:ss]")+" /RB_MOBILE/sh directory : make new config")),
                              Q_ARG(QVariant,QVariant().fromValue(2)));


    //log 삭제
    QDir dir_log(QDir::homePath()+"/RB_MOBILE/log");
    if(dir_log.removeRecursively())
    {
        QDir().mkdir(QDir::homePath() + "/RB_MOBILE/log");
        QDir().mkdir(QDir::homePath() + "/RB_MOBILE/log/ui_log");
        QDir().mkdir(QDir::homePath() + "/RB_MOBILE/log/extproc_log");
        QDir().mkdir(QDir::homePath() + "/RB_MOBILE/log/sn_log");
        plog->write(func_str + "Reset Clear : Remove log Success");
        QMetaObject::invokeMethod(mMain, "setClear",Qt::DirectConnection,
                                  Q_ARG(QVariant,QVariant().fromValue(QDateTime::currentDateTime().toString("[yyyy-MM-dd hh:mm:ss]")+" /RB_MOBILE/log directory : remove")),
                                  Q_ARG(QVariant,QVariant().fromValue(2)));

    }
    else
    {
        if(!dir_log.exists())
        {
            QDir().mkdir(QDir::homePath() + "/RB_MOBILE/log");
            QDir().mkdir(QDir::homePath() + "/RB_MOBILE/log/ui_log");
            QDir().mkdir(QDir::homePath() + "/RB_MOBILE/log/extproc_log");
            QDir().mkdir(QDir::homePath() + "/RB_MOBILE/log/sn_log");
        }
        plog->write(func_str + "Reset Clear : Remove log Failed");
        QMetaObject::invokeMethod(mMain, "setClear",Qt::DirectConnection,
                                  Q_ARG(QVariant,QVariant().fromValue(QDateTime::currentDateTime().toString("[yyyy-MM-dd hh:mm:ss]")+" /RB_MOBILE/log directory : remove")),
                                  Q_ARG(QVariant,QVariant().fromValue(3)));

    }

    QMetaObject::invokeMethod(mMain, "setClear",Qt::DirectConnection,
                              Q_ARG(QVariant,QVariant().fromValue(QDateTime::currentDateTime().toString("[yyyy-MM-dd hh:mm:ss]")+" Reset All Done ")),
                              Q_ARG(QVariant,QVariant().fromValue(2)));
}

void Supervisor::factoryInit()
{
    start_folder_clear();
}

int Supervisor::getTravellineIssue()
{
    QString func_str = "[SUPERVISOR][getTravellineIssue] ";
    plog->write(func_str + "start func. params()");

    if(!pmap)
    {
        log_advanced(func_str + "Error: pmap is null.");
        return 0;
    }

    return pmap->tline_issue;
}

QString Supervisor::getTravellineIssueGroup(int num)
{
    QString func_str = "[SUPERVISOR][getTravellineIssueGroup] ";
    plog->write(func_str + "start func. params(num):" + QString::number(num));

    if(!pmap)
    {
        log_advanced(func_str + "Error: pmap is null.");
        return "";
    }

    return pmap->tline_issues[num].group;
}

QString Supervisor::getTravellineIssueName(int num)
{
    QString func_str = "[SUPERVISOR][getTravellineIssueName] ";
    plog->write(func_str + "start func. params(num):" + QString::number(num));

    if(!pmap)
    {
        log_advanced(func_str + "Error: pmap is null.");
        return "";
    }

    return pmap->tline_issues[num].name;
}

bool Supervisor::getTravellineIssueFar(int num)
{
    QString func_str = "[SUPERVISOR][getTravellineIssueFar] ";
    plog->write(func_str + "start func. params(num):" + QString::number(num));

    if(!pmap)
    {
        log_advanced(func_str + "Error: pmap is null.");
        return false;
    }

    return pmap->tline_issues[num].is_far;
}

bool Supervisor::getTravellineIssueBroken(int num)
{
    QString func_str = "[SUPERVISOR][getTravellineIssueBroken] ";
    plog->write(func_str + "start func. params(num):" + QString::number(num));

    if(!pmap)
    {
        log_advanced(func_str + "Error: pmap is null.");
        return false;
    }

    return pmap->tline_issues[num].is_broken;
}

void Supervisor::setVelmapView(bool onoff)
{
    QString func_str = "[SUPERVISOR][setVelmapView] ";
    plog->write(func_str + "start func. params(onoff):" + QString::number((int)onoff));

    if(!maph)
    {
        log_advanced(func_str + "Error: pmap is null.");
        return;
    }

    maph->setShowVelocitymap(onoff);
}

void Supervisor::setTlineView(bool onoff)
{
    QString func_str = "[SUPERVISOR][setTlineView] ";
    plog->write(func_str + "start func. params(onoff):" + QString::number((int)onoff));

    if(!maph)
    {
        log_advanced(func_str + "Error: pmap is null.");
        return;
    }

    maph->setShowTravelline(onoff);
}

void Supervisor::setObjectView(bool onoff)
{
    QString func_str = "[SUPERVISOR][setObjectView] ";
    plog->write(func_str + "start func. params(onoff):" + QString::number((int)onoff));

    if(!maph)
    {
        log_advanced(func_str + "Error: pmap is null.");
        return;
    }

    maph->setShowObject(onoff);
}

void Supervisor::setAvoidmapView(bool onoff)
{
    QString func_str = "[SUPERVISOR][setAvoidmapView] ";
    plog->write(func_str + "start func. params(onoff):" + QString::number((int)onoff));

    if(!maph)
    {
        log_advanced(func_str + "Error: pmap is null.");
        return;
    }

    maph->setShowAvoidMap(onoff);
}

void Supervisor::setLocationView(bool onoff)
{
    QString func_str = "[SUPERVISOR][setLocationView] ";
    plog->write(func_str + "start func. params(onoff):" + QString::number((int)onoff));

    if(!maph)
    {
        log_advanced(func_str + "Error: pmap is null.");
        return;
    }

    maph->setShowLocation(onoff);
}

void Supervisor::setRobotView(bool onoff)
{
    QString func_str = "[SUPERVISOR][setRobotView] ";
    plog->write(func_str + "start func. params(onoff):" + QString::number((int)onoff));

    if(!maph)
    {
        log_advanced(func_str + "Error: pmap is null.");
        return;
    }

    maph->setShowRobot(onoff);
}

void Supervisor::readPatrol()
{
    QString func_str = "[SUPERVISOR][readPatrol] ";
    plog->write(func_str + "start func. params()");

    patrols.clear();
    QString path = QDir::homePath() + "/RB_MOBILE/patrol";
    if(!QFile::exists(path))
    {
        QDir().mkpath(path);
        plog->write(func_str + " no path make new -> " + path);
    }
    else
    {
        QDir dir(path);
        QStringList files = dir.entryList();
        plog->write(func_str + "path: " + path);

        for(QString file : files)
        {
            if(file.startsWith("patrol_"))
            {
                if(file.left(7) == "patrol_" && file.split(".")[1] == "ini")
                {

                    QSettings patrol(path + "/" + file, QSettings::IniFormat);
                    patrol.beginGroup("SETTING");
                    if(patrol.value("name").toString() != "")
                    {
                        ST_PATROL temp;
                        temp.name = patrol.value("name").toString();
                        temp.filename = patrol.value("filename").toString();
                        temp.type = patrol.value("type").toString();
                        temp.wait_time = patrol.value("wait_time").toInt();
                        temp.pass_time = patrol.value("pass_time").toInt();
                        temp.moving_page.mode = patrol.value("moving_page").toString();
                        temp.arrive_page.mode = patrol.value("arrive_page").toString();
                        temp.voice_name = patrol.value("voice_name").toString();
                        temp.voice_path = patrol.value("voice_path").toString();
                        temp.voice_file = patrol.value("voice_file").toString();
                        temp.voice_mention = patrol.value("voice_mention").toString();
                        temp.voice_mode = patrol.value("voice_mode").toString();
                        temp.voice_language = patrol.value("voice_language").toString();
                        temp.voice_volume = patrol.value("voice_volume").toInt();
                        temp.location_mode = patrol.value("location_mode").toString();

                        int loc_num = patrol.value("location_num").toInt();

                        patrol.endGroup();
                        patrol.beginGroup("LOCATION");
                        for(int i=0; i<loc_num; i++)
                        {
                            LOCATION temp_loc;
                            if(patrol.value("group"+QString::number(i)).toString() == "Charging")
                            {
                                temp_loc = getChargingLocation(0);
                            }
                            else if(patrol.value("group"+QString::number(i)).toString() == "Resting")
                            {
                                temp_loc = getRestingLocation(0);
                            }
                            else if(patrol.value("group"+QString::number(i)).toString() == "Cleaning")
                            {
                                temp_loc = getCleaningLocation(0);
                            }
                            else
                            {
                                temp_loc = getServingLocation(patrol.value("group"+QString::number(i)).toString(),patrol.value("loc"+QString::number(i)).toString());
                            }
                            if(temp_loc.name != "")
                            {
                                temp.location.append(temp_loc);
                            }
                        }
                        patrol.endGroup();

                        if(temp.moving_page.mode == "custom")
                        {
                            patrol.beginGroup("MOVING");
                            temp.moving_page.background = patrol.value("background").toString();
                            if(temp.moving_page.background == "color")
                            {
                                temp.moving_page.color = patrol.value("color").toString();
                            }
                            else if(temp.moving_page.background == "image"||temp.moving_page.background == "gif")
                            {
                                temp.moving_page.image = patrol.value("image").toString();
                            }
                            else if(temp.moving_page.background == "video")
                            {
                                temp.moving_page.video = patrol.value("video").toString();
                                temp.moving_page.audio = patrol.value("video_audio").toString();

                                if(temp.moving_page.audio == "")
                                {
                                    temp.moving_page.audio = "video";
                                }
                            }
                            temp.moving_page.volume = patrol.value("audio").toFloat();

                            int num = patrol.value("obj_num").toInt();
                            for(int i=0; i<num; i++)
                            {
                                ST_PAGE_OBJECT temp_obj;
                                QStringList objs = patrol.value("obj" + QString::number(i)).toString().split(",");
                                if(objs.size() > 5)
                                {
                                    temp_obj.type = objs[0];
                                    temp_obj.x = objs[1].toInt();
                                    temp_obj.y = objs[2].toInt();
                                    temp_obj.width = objs[3].toInt();
                                    temp_obj.height = objs[4].toInt();
                                    temp_obj.source = objs[5];
                                    temp_obj.color = objs[6];
                                    temp.moving_page.objects.append(temp_obj);
                                }
                            }
                        }

                        //arrive_page도 똑같이
                        plog->write(func_str + "(file,name,type,loc_size,voice_name): " + file + " -> " + temp.name + "," + temp.type + "," + QString::number(temp.location.size()) + "," + temp.voice_name);
                        patrols.append(temp);
                    }
                }
            }
        }
    }
}

int Supervisor::getPatrolSize()
{
    QString func_str = "[SUPERVISOR][getPatrolSize] ";
    plog->write(func_str + "start func. params()");

    return patrols.size();
}

QString Supervisor::getPatrolName(int num)
{
    QString func_str = "[SUPERVISOR][getPatrolName] ";
    plog->write(func_str + "start func. params(num):" + QString::number(num));

    QString patrol_name = "";
    if(num < 0 || num >= patrols.size())
    {
        log_advanced(func_str + "Error: num is out of bounds.");
        return patrol_name;
    }

    patrol_name = patrols[num].name;
    return patrol_name;
}

void Supervisor::loopClosing()
{
    QString func_str = "[SUPERVISOR][loopClosing] ";
    plog->write(func_str + "start func. params()");

    try
    {
        ipc->set_cmd(ROBOT_CMD_MAP_LOOP_CLOSING, "LoopClosing");
    }
    catch(const std::exception &e)
    {
        log_advanced(func_str + "Exception : " + QString(e.what()));
    }
    catch(...)
    {
        log_advanced(func_str + "Exception : unknwon.");
    }
}

int Supervisor::getPatrolVoiceNameNum(int num)
{
    QString func_str = "[SUPERVISOR][getPatrolVoiceNameNum] ";
    plog->write(func_str + "start func. params(num):" + QString::number(num));

    const std::map<QString, int> voice_map =
    {
        {"vara", 1},{"woman", 1}, {"danna", 1},{"liangliang", 1},{"ntomoko", 1},{"jose", 1},
        {"nhajun", 2},{"matt", 2},{"dayumu", 2},
        {"njooahn", 3},{"shinji", 3},
        {"nsangdo", 4},
        {"nsunhee", 5},
        {"nkyungtae", 6},
        {"nsabina", 7},
        {"nmammon", 8},
    };

    auto it = voice_map.find(patrols[num].name);
    if(it != voice_map.end())
    {
        return it->second;
    }
    else
    {
        return 0;
    }
}

QString Supervisor::getPatrolType(int num)
{
    QString func_str = "[SUPERVISOR][getPatrolType] ";
    plog->write(func_str + "start func. params(num):" + QString::number(num));

    QString type_str = "";
    if(num < 0 || num >= patrols.size())
    {
        log_advanced(func_str + "Error: num is out of bounds.");
        return type_str;
    }

    type_str = patrols[num].type;
    return type_str;
}

QString Supervisor::getPatrolLocation(int num)
{
    QString func_str = "[SUPERVISOR][getPatrolLocation] ";
    plog->write(func_str + "start func. params(num):" + QString::number(num));

    QString loc_str = "";
    if(num < 0 || num >= patrols.size())
    {
        log_advanced(func_str + "Error: num is out of bounds.");
        return loc_str;
    }

    loc_str = patrols[num].location_mode;
    return loc_str;
}

QString Supervisor::getPatrolMovingPage(int num)
{
    QString func_str = "[SUPERVISOR][getPatrolMovingPage] ";
    plog->write(func_str + "start func. params(num):" + QString::number(num));

    QString page_str = "";
    if(num < 0 || num >= patrols.size())
    {
        log_advanced(func_str + "Error: num is out of bounds.");
        return page_str;
    }

    page_str = patrols[num].moving_page.mode;
    return page_str;
}

QString Supervisor::getPatrolArrivePage(int num)
{
    QString func_str = "[SUPERVISOR][getPatrolArrivePage] ";
    plog->write(func_str + "start func. params(num):" + QString::number(num));

    QString page_str = "";
    if(num < 0 || num >= patrols.size())
    {
        log_advanced(func_str + "Error: num is out of bounds.");
        return page_str;
    }

    page_str = patrols[num].arrive_page.mode;
    return page_str;
}

int Supervisor::getPatrolWaitTime(int num)
{
    QString func_str = "[SUPERVISOR][getPatrolWaitTime] ";
    plog->write(func_str + "start func. params(num):" + QString::number(num));

    int time = -1;
    if(num < 0 || num >= patrols.size())
    {
        log_advanced(func_str + "Error: num is out of bounds.");
        return time;
    }

    time = patrols[num].wait_time;
    return time;
}

int Supervisor::getPatrolPassTime(int num)
{
    QString func_str = "[SUPERVISOR][getPatrolPassTime] ";
    plog->write(func_str + "start func. params(num):" + QString::number(num));

    int time = -1;
    if(num < 0 || num >= patrols.size())
    {
        log_advanced(func_str + "Error: num is out of bounds.");
        return time;
    }

    time = patrols[num].wait_time;
    return time;
}

QString Supervisor::getPatrolVoiceMode(int num)
{
    QString func_str = "[SUPERVISOR][getPatrolVoiceMode] ";
    plog->write(func_str + "start func. params(num):" + QString::number(num));

    QString mode_str = "";
    if(num < 0 || num >= patrols.size())
    {
        log_advanced(func_str + "Error: num is out of bounds.");
        return mode_str;
    }

    mode_str = patrols[num].voice_mode;
    return mode_str;
}

QString Supervisor::getPatrolVoiceLanguage(int num)
{
    QString func_str = "[SUPERVISOR][getPatrolVoiceLanguage] ";
    plog->write(func_str + "start func. params(num):" + QString::number(num));

    QString voice_lan_str = "";
    if(num < 0 || num >= patrols.size())
    {
        log_advanced(func_str + "Error: num is out of bounds.");
        return voice_lan_str;
    }

    voice_lan_str = patrols[num].voice_language;
    return voice_lan_str;
}

bool Supervisor::isPatrolPage()
{
    QString func_str = "[SUPERVISOR][isPatrolPage] ";
    plog->write(func_str + "start func. params()");

    if(!probot)
    {
        log_advanced(func_str + "Error: probot is null.");
        return false;
    }

    return probot->is_patrol;
}

QString Supervisor::getPatrolMovingMode()
{
    QString func_str = "[SUPERVISOR][getPatrolMovingMode] ";
    plog->write(func_str + "start func. params()");

    return current_patrol.moving_page.mode;
}

QString Supervisor::getPatrolArriveMode()
{
    QString func_str = "[SUPERVISOR][getPatrolArriveMode] ";
    plog->write(func_str + "start func. params()");

    return current_patrol.arrive_page.mode;
}

QString Supervisor::getPatrolVoice(int num)
{
    QString func_str = "[SUPERVISOR][getPatrolVoice] ";
    plog->write(func_str + "start func. params(num):" + QString::number(num));

    QString patrol_voice_str = "";
    if(num < 0 || num >= patrols.size())
    {
        log_advanced(func_str + "Error: num is out of bounds.");
        return patrol_voice_str;
    }

    patrol_voice_str = patrols[num].voice_path;
    return patrol_voice_str;
}

QString Supervisor::getPatrolVoiceMention(int num)
{
    QString func_str = "[SUPERVISOR][getPatrolVoiceMention] ";
    plog->write(func_str + "start func. params(num):" + QString::number(num));

    QString voice_mention_str = "";
    if(num < 0 || num >= patrols.size())
    {
        log_advanced(func_str + "Error: num is out of bounds.");
        return voice_mention_str;
    }

    if(patrols[num].voice_mode == "tts")
    {
        voice_mention_str = patrols[num].voice_mention;
    }
    else
    {
        voice_mention_str = patrols[num].voice_file;
    }

    return voice_mention_str;
}

int Supervisor::getPatrolLocationSize(int num)
{
    QString func_str = "[SUPERVISOR][getPatrolVoiceMention] ";
    plog->write(func_str + "start func. params(num):" + QString::number(num));

    int loc_size = 0;
    if(num < 0 || num >= patrols.size())
    {
        log_advanced(func_str + "Error: num is out of bounds.");
        return loc_size;
    }

    loc_size = patrols[num].location.size();
    return loc_size;
}

void Supervisor::initCurrentPatrol()
{
    QString func_str = "[SUPERVISOR][initCurrentPatrol] ";
    plog->write(func_str + "start func. params()");

    current_patrol = ST_PATROL();
    current_patrol.moving_page.mode = "face1";
    current_patrol.arrive_page.mode = "pass";
}

void Supervisor::saveServingPage()
{
    QString func_str = "[SUPERVISOR][saveServingPage] ";
    plog->write(func_str + "start func. params()");

    QString path = QDir::homePath() + "/RB_MOBILE/patrol";
    if(!QFile::exists(path))
    {
        QDir().mkdir(path);
    }

    QString filestr = path + "/serving.ini";
    QSettings file(filestr, QSettings::IniFormat);
    file.clear();

    file.setValue("MOVING/background", serving_page.background);
    file.setValue("MOVING/image", serving_page.image);
    file.setValue("MOVING/video", serving_page.video);
    file.setValue("MOVING/video_audio", serving_page.audio);
    file.setValue("MOVING/color", serving_page.color);
    file.setValue("MOVING/obj_num", serving_page.objects.size());
    file.setValue("MOVING/audio", serving_page.volume);

    for(int i=0; i<serving_page.objects.size(); i++)
    {
        QString str = serving_page.objects[i].type + "," +
                      QString::number(serving_page.objects[i].x) + "," +
                      QString::number(serving_page.objects[i].y) + "," +
                      QString::number(serving_page.objects[i].width) + "," +
                      QString::number(serving_page.objects[i].height) + "," +
                      serving_page.objects[i].source +","+serving_page.objects[i].color;

        file.setValue("MOVING/obj" + QString::number(i), str);
    }
}

void Supervisor::savePatrolPage()
{
}

void Supervisor::initServingPage()
{
    QString func_str = "[SUPERVISOR][initServingPage] ";
    plog->write(func_str + "start func. params()");

    QString path = QDir::homePath() + "/RB_MOBILE/patrol";
    if(!QFile::exists(path))
    {
        QDir().mkdir(path);
        plog->write("[COMMAND] initServingPage : no path make new -> "+path);
    }

    QString file = path + "/serving.ini";
    if(!QFile::exists(file))
    {
        plog->write("[COMMAND] initServingPage : no file -> "+file);
        serving_page.mode = "face1";
    }
    else
    {
        QSettings patrol(file, QSettings::IniFormat);
        patrol.beginGroup("MOVING");

        serving_page.background = patrol.value("background").toString();
        if(serving_page.background == "color")
        {
            serving_page.color = patrol.value("color").toString();
        }
        else if(serving_page.background == "image"||serving_page.background == "gif")
        {
            serving_page.image = patrol.value("image").toString();
        }
        else if(serving_page.background == "video")
        {
            serving_page.video = patrol.value("video").toString();
            serving_page.audio = patrol.value("video_audio").toString();
            if(serving_page.audio == "")
            {
                serving_page.audio = "video";
            }

        }
        serving_page.volume = patrol.value("audio").toFloat();

        serving_page.objects.clear();
        int num = patrol.value("obj_num").toInt();
        for(int i=0; i<num; i++)
        {
            ST_PAGE_OBJECT temp_obj;
            QStringList objs=patrol.value("obj" + QString::number(i)).toString().split(",");
            if(objs.size() > 5)
            {
                temp_obj.type = objs[0];
                temp_obj.x = objs[1].toInt();
                temp_obj.y = objs[2].toInt();
                temp_obj.width = objs[3].toInt();
                temp_obj.height = objs[4].toInt();
                temp_obj.source = objs[5];
                temp_obj.color = objs[6];
                serving_page.objects.append(temp_obj);
            }
        }
    }
}

void Supervisor::setCurrentPatrol(int num)
{
    QString func_str = "[SUPERVISOR][setCurrentPatrol] ";
    plog->write(func_str + "start func. params(num):" + QString::number(num));

    if(num < 0 || num >= patrols.size())
    {
        log_advanced(func_str + "Error: num is out of bounds.");
        return;
    }

    current_patrol.location.clear();
    current_patrol = patrols[num];
    plog->write(func_str + " set current patrol (num,name): " + QString::number(num) + "," + current_patrol.name);
}

QString Supervisor::getPatrolLocation(int num, int loc)
{
    QString func_str = "[SUPERVISOR][getPatrolLocation] ";
    plog->write(func_str + "start func. params(num,loc):" + QString::number(num) + "," + QString::number(loc));

    QString patrol_loc_str = "";
    if(num < 0 || num >= patrols.size())
    {
        log_advanced(func_str + "Error: num is out of bounds.");
        return patrol_loc_str;
    }

    if(loc < 0 || loc >= patrols[num].location.size())
    {
        log_advanced(func_str + "Error: loc is out of bounds.");
        return patrol_loc_str;
    }

    patrol_loc_str = patrols[num].location[loc].name;
    return patrol_loc_str;
}

QString Supervisor::getPatrolLocationGroup(int num, int loc)
{
    QString func_str = "[SUPERVISOR][getPatrolLocationGroup] ";
    plog->write(func_str + "start func. params(num,loc):" + QString::number(num) + "," + QString::number(loc));

    QString patrol_loc_group_str = "";
    if(num < 0 || num >= patrols.size())
    {
        log_advanced(func_str + "Error: num is out of bounds.");
        return patrol_loc_group_str;
    }

    if(loc < 0 || loc >= patrols[num].location.size())
    {
        log_advanced(func_str + "Error: loc is out of bounds.");
        return patrol_loc_group_str;
    }

    patrol_loc_group_str = patrols[num].location[loc].group_name;
    return patrol_loc_group_str;
}

void Supervisor::clearPatrolLocation(QString mode)
{
    QString func_str = "[SUPERVISOR][clearPatrolLocation] ";
    plog->write(func_str + "start func. params(mode):" + mode);

    current_patrol.location.clear();
    current_patrol.location_mode = mode;
}

void Supervisor::addPatrolLocation(QString type, QString group, QString name)
{
    QString func_str = "[SUPERVISOR][clearPatrolLocation] ";
    plog->write(func_str + "start func. params(type,group,name):" + type + "," + group + "," + name);

    if(type == "Charging")
    {
        if(getChargingLocation(0).name != "")
        {
            current_patrol.location.append(getChargingLocation(0));
        }
    }
    else if(type == "Resting")
    {
        if(getRestingLocation(0).name != "")
        {
            current_patrol.location.append(getRestingLocation(0));
        }
    }
    else if(type == "Cleaning")
    {
        if(getCleaningLocation(0).name != "")
        {
            current_patrol.location.append(getCleaningLocation(0));
        }
    }
    else if(type == "Serving")
    {
        if(getServingLocation(name).name != "")
        {
            current_patrol.location.append(getServingLocation(group, name));
        }
    }
}

void Supervisor::setPatrolMovingPage(QString mode, QString param1, QString param2, QString param3)
{
    QString func_str = "[SUPERVISOR][setPatrolMovingPage] ";
    plog->write(func_str + "start func. params(mode):" + mode);

    current_patrol.moving_page.mode = mode;
}

void Supervisor::setPatrolArrivePage(QString mode, QString param1, QString param2, QString param3)
{
    QString func_str = "[SUPERVISOR][setPatrolArrivePage] ";
    plog->write(func_str + "start func. params(mode):" + mode);

    if(mode != "custom")
    {
        current_patrol.arrive_page.mode = mode;
    }
}

void Supervisor::setPatrolVoice(QString mode, int language, int voice, int volume, int mention)
{
    QString func_str = "[SUPERVISOR][clearPatrolLocation] ";
    plog->write(func_str + "start func. params(mode,language,voice,volume,mention):" +
                mode + "," +
                QString::number(language) + "," +
                QString::number(voice) + "," +
                QString::number(volume) + "," +
                QString::number(mention));

    current_patrol.voice_mode = mode;
    current_patrol.voice_language = tts->getVoiceLanguage(language);
    current_patrol.voice_volume = volume;
    if(mode == "basic")
    {
        if(voice == 1)
        {
            current_patrol.voice_name = "child";
        }
        else
        {
            current_patrol.voice_name = "woman";
        }

        if(mention == 0)
        {
            current_patrol.voice_file = "thanks";
        }
        else if(mention == 1)
        {
            current_patrol.voice_file = "hello";
        }
        else if(mention == 2)
        {
            current_patrol.voice_file = "funny_working_hard";
        }
        else if(mention == 3)
        {
            current_patrol.voice_file = "hello_rb";
        }
        else if(mention == 4)
        {
            current_patrol.voice_file = "path_finding";
        }
        else if(mention == 5)
        {
            current_patrol.voice_file = "rb_fighting";
        }
        else if(mention == 6)
        {
            current_patrol.voice_file = "moving";
        }
        else if(mention == 7)
        {
            current_patrol.voice_file = "sorry";
        }
        else if(mention == 8)
        {
            current_patrol.voice_file = "move_next";
        }
        else if(mention == 9)
        {
            current_patrol.voice_file = "move_patrol";
        }
        else if(mention == 10)
        {
            current_patrol.voice_file = "wait_path";
        }
        else
        {
            current_patrol.voice_file = "thank_enjoy";
        }

        current_patrol.voice_path = "qrc:/" + current_patrol.voice_name + "_" + current_patrol.voice_file + ".mp3";
    }
    else if(mode == "tts")
    {
        current_patrol.voice_file = "patrol";
        current_patrol.voice_name = tts->getVoiceName("tts", language, voice);
        current_patrol.voice_path = QDir::homePath() + "/RB_MOBILE/voice/" + current_patrol.voice_name + "_patrol.mp3";
    }
}

int Supervisor::getTTSLanguageNum()
{
    QString func_str = "[SUPERVISOR][getTTSLanguageNum] ";
    plog->write(func_str + "start func. params()");

    if(getSetting("setting","UI","voice_language") == "ko")
    {
        return VOICE_KOREAN;
    }
    else if(getSetting("setting","UI","voice_language") == "en")
    {
        return VOICE_ENGLISH;
    }
    else if(getSetting("setting","UI","voice_language") == "zh-CN")
    {
        return VOICE_CHINESE;
    }
    else if(getSetting("setting","UI","voice_language") == "ja")
    {
        return VOICE_JAPANESE;
    }
    else if(getSetting("setting","UI","voice_language") == "es")
    {
        return VOICE_SPANISH;
    }
    else if(getSetting("setting","UI","voice_language") == "ru")
    {
        return VOICE_RUSSIAN;
    }
    else if(getSetting("setting","UI","voice_language") == "ge")
    {
        return VOICE_GERMAN;
    }
    else if(getSetting("setting","UI","voice_language") == "la")
    {
        return VOICE_LAOTIAN;
    }
    else if(getSetting("setting","UI","voice_language") == "id")
    {
        return VOICE_INDONESIAN;
    }
    else
    {
        return VOICE_KOREAN;
    }
}

int Supervisor::getTTSNameNum()
{
    QString func_str = "[SUPERVISOR][getTTSNameNum] ";
    plog->write(func_str + "start func. params()");

    for(int i=VOICE_KOREAN; i<=VOICE_INDONESIAN; i++)
    {
        if(getSetting("setting","UI","voice_name") == tts->getVoiceName("tts", getTTSLanguageNum(), i))
        {
            return i;
        }
    }

    if(getSetting("setting","UI","voice_name") == "woman")
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void Supervisor::setPatrol(int num, QString name, QString type, int wait_time, int pass_time)
{
    if(num > -1 && num < patrols.size())
    {
        QString path = QDir::homePath() + "/RB_MOBILE/patrol";
        QString filename = patrols[num].filename;
        QSettings file(path+"/"+filename, QSettings::IniFormat);
        file.clear();
        file.setValue("SETTING/name",name);
        file.setValue("SETTING/filename",filename);
        file.setValue("SETTING/type",type);
        file.setValue("SETTING/wait_time",wait_time);
        file.setValue("SETTING/pass_time",pass_time);

        file.setValue("SETTING/moving_page",current_patrol.moving_page.mode);
        file.setValue("SETTING/arrive_page",current_patrol.arrive_page.mode);
        file.setValue("SETTING/voice_name",current_patrol.voice_name);
        file.setValue("SETTING/voice_language",current_patrol.voice_language);
        file.setValue("SETTING/voice_path",current_patrol.voice_path);
        file.setValue("SETTING/voice_file",current_patrol.voice_file);
        file.setValue("SETTING/voice_mode",current_patrol.voice_mode);
        file.setValue("SETTING/voice_volume",current_patrol.voice_volume);
        file.setValue("SETTING/voice_mention",current_patrol.voice_mention);
        file.setValue("SETTING/location_mode",current_patrol.location_mode);
        file.setValue("SETTING/location_num",current_patrol.location.size());

        for(int i=0; i<current_patrol.location.size(); i++)
        {
            file.setValue("LOCATION/loc"+QString::number(i),current_patrol.location[i].name);
            file.setValue("LOCATION/group"+QString::number(i),current_patrol.location[i].group_name);
        }

        if(current_patrol.moving_page.mode == "custom")
        {
            file.setValue("MOVING/background",current_patrol.moving_page.background);
            file.setValue("MOVING/image",current_patrol.moving_page.image);
            file.setValue("MOVING/video",current_patrol.moving_page.video);
            file.setValue("MOVING/video_audio",current_patrol.moving_page.audio);
            file.setValue("MOVING/color",current_patrol.moving_page.color);
            file.setValue("MOVING/obj_num",current_patrol.moving_page.objects.size());
            file.setValue("MOVING/audio",current_patrol.moving_page.volume);

            for(int i=0; i<current_patrol.moving_page.objects.size(); i++)
            {
                QString str = current_patrol.moving_page.objects[i].type + "," + QString::number(current_patrol.moving_page.objects[i].x) + "," + QString::number(current_patrol.moving_page.objects[i].y) + "," + QString::number(current_patrol.moving_page.objects[i].width) + "," + QString::number(current_patrol.moving_page.objects[i].height) +
                        "," + current_patrol.moving_page.objects[i].source +","+current_patrol.moving_page.objects[i].color;
                file.setValue("MOVING/obj"+QString::number(i),str);
            }
//            qDebug() << "setPatrol " << current_patrol.moving_page.background << current_patrol.moving_page.color;
        }

        plog->write("[COMMAND] setPatrol "+QString::number(num)+" : "+name);
    }
}

void Supervisor::deletePatrol(int num)
{
    if(num > -1 && num < patrols.size())
    {
        QString path = QDir::homePath() + "/RB_MOBILE/patrol";
        QString filename = patrols[num].filename;
        QFile *file = new QFile(path+"/"+filename);
        if(file->remove())
        {
            plog->write("[COMMAND] deletePatrol "+QString::number(num)+" : SUCCESS");
        }
        else
        {
            plog->write("[COMMAND] deletePatrol "+QString::number(num)+" : FAILED");
        }
    }
}

void Supervisor::savePatrol(QString name, QString type, int wait_time, int pass_time)
{
    QString path = QDir::homePath() + "/RB_MOBILE/patrol";
    if(!QFile::exists(path))
    {
        QDir().mkdir(path);
    }

    QDir dir(path);
    QStringList files = dir.entryList();
    int size = 0;
    for(QString file:files)
    {
        int tempsize = file.split(".")[0].remove(0,7).toInt();
        if(tempsize > size)
        {
            size = tempsize;
        }
    }
    QString filename = "patrol_" + QString::number(size+1) + ".ini";

    QSettings file(path+"/"+filename, QSettings::IniFormat);
    file.clear();
    file.setValue("SETTING/name",name);
    file.setValue("SETTING/filename",filename);
    file.setValue("SETTING/type",type);
    file.setValue("SETTING/wait_time",wait_time);
    file.setValue("SETTING/pass_time",pass_time);

    file.setValue("SETTING/moving_page",current_patrol.moving_page.mode);
    file.setValue("SETTING/arrive_page",current_patrol.arrive_page.mode);

    file.setValue("SETTING/voice_file",current_patrol.voice_file);
    file.setValue("SETTING/voice_mode",current_patrol.voice_mode);
    file.setValue("SETTING/voice_mention",current_patrol.voice_mention);
    file.setValue("SETTING/voice_language",current_patrol.voice_language);
    file.setValue("SETTING/voice_volume",current_patrol.voice_volume);
    file.setValue("SETTING/voice_path",current_patrol.voice_path);
    file.setValue("SETTING/voice_name",current_patrol.voice_name);
    file.setValue("SETTING/location_mode",current_patrol.location_mode);
    file.setValue("SETTING/location_num",current_patrol.location.size());

    for(int i=0; i<current_patrol.location.size(); i++)
    {
        file.setValue("LOCATION/type"+QString::number(i),current_patrol.location[i].type);
        file.setValue("LOCATION/loc"+QString::number(i),current_patrol.location[i].name);
        file.setValue("LOCATION/group"+QString::number(i),current_patrol.location[i].group_name);
    }

    if(current_patrol.moving_page.mode == "custom")
    {
        file.setValue("MOVING/background",current_patrol.moving_page.background);
        file.setValue("MOVING/image",current_patrol.moving_page.image);
        file.setValue("MOVING/video_audio",current_patrol.moving_page.audio);
        file.setValue("MOVING/video",current_patrol.moving_page.video);
        file.setValue("MOVING/color",current_patrol.moving_page.color);
        file.setValue("MOVING/obj_num",current_patrol.moving_page.objects.size());
        file.setValue("MOVING/audio",current_patrol.moving_page.volume);

        for(int i=0; i<current_patrol.moving_page.objects.size(); i++)
        {
            QString str = current_patrol.moving_page.objects[i].type + "," + QString::number(current_patrol.moving_page.objects[i].x) + "," + QString::number(current_patrol.moving_page.objects[i].y) + "," + QString::number(current_patrol.moving_page.objects[i].width) + "," + QString::number(current_patrol.moving_page.objects[i].height) +
                    "," + current_patrol.moving_page.objects[i].source +","+current_patrol.moving_page.objects[i].color;
            file.setValue("MOVING/obj"+QString::number(i),str);
        }
    }
    plog->write("[COMMAND] savePatrol : "+name);
}


void Supervisor::setMovingPageColor(QString file)
{
    setMovingPageBackground("color");
    current_patrol.moving_page.color = file;
}

QString Supervisor::getMovingPageColor()
{
    return current_patrol.moving_page.color;
}

void Supervisor::setMovingPageMode(QString mode)
{
    current_patrol.moving_page.mode = mode;
}

QString Supervisor::getMovingPageMode()
{
    return current_patrol.moving_page.mode;
}

void Supervisor::setMovingPageBackground(QString mode)
{
    current_patrol.moving_page.background = mode;
}

QString Supervisor::getMovingPageBackground()
{
    return current_patrol.moving_page.background;
}

void Supervisor::setMovingPageImage(QString file)
{
    current_patrol.moving_page.image = file;
}

QString Supervisor::getMovingPageImage()
{
    return current_patrol.moving_page.image;
}

void Supervisor::setServingPageVideoAudio(QString mode)
{
    serving_page.audio = mode;
}

QString Supervisor::getServingPageVideoAudio()
{
    return serving_page.audio;
}

void Supervisor::setMovingPageVideoAudio(QString mode)
{
    current_patrol.moving_page.audio = mode;
}

QString Supervisor::getMovingPageVideoAudio()
{
    return current_patrol.moving_page.audio;
}

void Supervisor::setMovingPageVideo(QString file)
{
    setMovingPageBackground("video");
    current_patrol.moving_page.video = file;
}

QString Supervisor::getMovingPageVideo()
{
    return current_patrol.moving_page.video;
}

void Supervisor::setMovingPageAudio(float volume)
{
    qDebug() << "setMovingPageAudio " << volume;
    setMovingPageBackground("video");
    current_patrol.moving_page.volume = volume;
}

float Supervisor::getMovingPageAudio()
{
    return current_patrol.moving_page.volume;
}

void Supervisor::setServingPageColor(QString file)
{
    setServingPageBackground("color");
    serving_page.color = file;
}

QString Supervisor::getServingPageColor()
{
    return serving_page.color;
}

void Supervisor::setServingPageMode(QString mode)
{
    serving_page.mode = mode;
}

QString Supervisor::getServingPageMode()
{
    return serving_page.mode;
}

void Supervisor::setServingPageBackground(QString mode)
{
    serving_page.background = mode;
}

QString Supervisor::getServingPageBackground()
{
    return serving_page.background;
}

void Supervisor::setServingPageImage(QString file)
{
    serving_page.image = file;
}

QString Supervisor::getServingPageImage()
{
    return serving_page.image;
}

void Supervisor::setServingPageVideo(QString file)
{
    setServingPageBackground("video");
    serving_page.video = file;
}

QString Supervisor::getServingPageVideo()
{
    return serving_page.video;
}

void Supervisor::setServingPageAudio(float volume)
{
    setServingPageBackground("video");
    serving_page.volume = volume;
}

float Supervisor::getServingPageAudio()
{
    return serving_page.volume;
}

void Supervisor::addPatrolObject(QString page, QString obj)
{
    plog->write("[PATROL] add Patrol Object ("+page+") : "+obj);
    ST_PAGE_OBJECT temp_obj = makeNewObj(obj);

    if(page == "moving")
    {
        current_patrol.moving_page.objects.append(temp_obj);
    }
    else
    {
        current_patrol.arrive_page.objects.append(temp_obj);
    }
}

void Supervisor::addServingObject(QString page, QString obj)
{
    plog->write("[PATROL] add Serving Object ("+page+") : "+obj);
    ST_PAGE_OBJECT temp_obj = makeNewObj(obj);
    serving_page.objects.append(temp_obj);
}

ST_PAGE_OBJECT Supervisor::makeNewObj(QString obj)
{
    ST_PAGE_OBJECT ob;
    ob.type = obj;
    if(obj == "image")
    {
        ob.x = 0;
        ob.y = 0;
        ob.width = 100;
        ob.height = 100;
        ob.source = "image/robot_head.png";
    }
    else if(obj == "text")
    {
        ob.x = 0;
        ob.y = 0;
        ob.fontsize = 20;
        ob.color = "#000000";
        ob.source = tr("안녕하세요");
        ob.width = 100;
        ob.height = 40;
    }
    return ob;
}

int Supervisor::getPatrolObjectSize()
{
    return current_patrol.moving_page.objects.size();
}

QString Supervisor::getPageObjectType(int num)
{
    if(num > -1 && num < current_patrol.moving_page.objects.size())
    {
        return current_patrol.moving_page.objects[num].type;
    }
    return "";
}

void Supervisor::setPageObjectSource(int num, QString src)
{
    if(num > -1 && num < current_patrol.moving_page.objects.size())
    {
        current_patrol.moving_page.objects[num].source = src;
    }
}

void Supervisor::setPageObjectColor(int num, QString color)
{
    if(num > -1 && num < current_patrol.moving_page.objects.size())
    {
        current_patrol.moving_page.objects[num].color = color;
    }
}

QString Supervisor::getPageObjectSource(int num)
{
    if(num > -1 && num < current_patrol.moving_page.objects.size())
    {
        return current_patrol.moving_page.objects[num].source;
    }
    return "";
}

QString Supervisor::getPageObjectColor(int num)
{
    if(num > -1 && num < current_patrol.moving_page.objects.size())
    {
        return current_patrol.moving_page.objects[num].color;
    }
    return "";
}

int Supervisor::getPageObjectX(int num)
{
    if(num > -1 && num < current_patrol.moving_page.objects.size())
    {
        return current_patrol.moving_page.objects[num].x;
    }
    return -1;
}

int Supervisor::getPageObjectY(int num)
{
    if(num > -1 && num < current_patrol.moving_page.objects.size())
    {
        return current_patrol.moving_page.objects[num].y;
    }
    return -1;
}

int Supervisor::getPageObjectWidth(int num)
{
    if(num > -1 && num < current_patrol.moving_page.objects.size())
    {
        return current_patrol.moving_page.objects[num].width;
    }
    return -1;
}

int Supervisor::getPageObjectHeight(int num)
{
    if(num > -1 && num < current_patrol.moving_page.objects.size()){
        return current_patrol.moving_page.objects[num].height;
    }
    return -1;
}

int Supervisor::getPageObjectFontsize(int num)
{
    if(num > -1 && num < current_patrol.moving_page.objects.size())
    {
        return current_patrol.moving_page.objects[num].fontsize;
    }
}

int Supervisor::getPageObjectNum(int x, int y)
{
    for(int i=current_patrol.moving_page.objects.size()-1; i>-1; i--)
    {
        if(x>(current_patrol.moving_page.objects[i].x-10) && x < current_patrol.moving_page.objects[i].x + current_patrol.moving_page.objects[i].width+10)
        {
            if(y>(current_patrol.moving_page.objects[i].y-10) && y < current_patrol.moving_page.objects[i].y + current_patrol.moving_page.objects[i].height+10)
            {
                return i;
            }
        }
    }
    return -1;
}

int Supervisor::getServingObjectSize()
{
    return serving_page.objects.size();
}

QString Supervisor::getServingObjectType(int num)
{
    if(num > -1 && num < serving_page.objects.size())
    {
        return serving_page.objects[num].type;
    }
    return "";
}

void Supervisor::setServingObjectSource(int num, QString src)
{
    if(num > -1 && num < serving_page.objects.size())
    {
        serving_page.objects[num].source = src;
    }
}

void Supervisor::setServingObjectColor(int num, QString color)
{
    if(num > -1 && num < serving_page.objects.size())
    {
        serving_page.objects[num].color = color;
    }
}

QString Supervisor::getServingObjectSource(int num)
{
    if(num > -1 && num < serving_page.objects.size())
    {
        return serving_page.objects[num].source;
    }
    return "";
}

QString Supervisor::getServingObjectColor(int num)
{
    if(num > -1 && num < serving_page.objects.size())
    {
        return serving_page.objects[num].color;
    }
    return "";
}

int Supervisor::getServingObjectX(int num)
{
    if(num > -1 && num < serving_page.objects.size())
    {
        return serving_page.objects[num].x;
    }
    return -1;
}

int Supervisor::getServingObjectY(int num)
{
    if(num > -1 && num < serving_page.objects.size())
    {
        return serving_page.objects[num].y;
    }
    return -1;
}

int Supervisor::getServingObjectWidth(int num)
{
    if(num > -1 && num < serving_page.objects.size())
    {
        return serving_page.objects[num].width;
    }
    return -1;
}

int Supervisor::getServingObjectHeight(int num)
{
    if(num > -1 && num < serving_page.objects.size())
    {
        return serving_page.objects[num].height;
    }
    return -1;
}

int Supervisor::getServingObjectFontsize(int num)
{
    if(num > -1 && num < serving_page.objects.size())
    {
        return serving_page.objects[num].fontsize;
    }
}

int Supervisor::getServingObjectNum(int x, int y)
{
    for(int i=serving_page.objects.size()-1; i>-1; i--)
    {
        if(x>(serving_page.objects[i].x-10) && x < serving_page.objects[i].x + serving_page.objects[i].width+10)
        {
            if(y>(serving_page.objects[i].y-10) && y < serving_page.objects[i].y + serving_page.objects[i].height+10)
            {
                return i;
            }
        }
    }
    return -1;
}

void Supervisor::movePatrolObject(int num, int x, int y)
{
//    qDebug() << "movePatrolObject " << num << x << y;
    if(num > -1 && num < current_patrol.moving_page.objects.size())
    {
        current_patrol.moving_page.objects[num].x = x;
        current_patrol.moving_page.objects[num].y = y;
    }
}

void Supervisor::setPatrolObjectSize(int num, int x, int y, int width, int height)
{
    if(num > -1 && num < current_patrol.moving_page.objects.size())
    {
        current_patrol.moving_page.objects[num].x = x;
        current_patrol.moving_page.objects[num].y = y;
        current_patrol.moving_page.objects[num].width = width;
        current_patrol.moving_page.objects[num].height = height;
    }
}

void Supervisor::deletePatrolObject(int num)
{
    if(num > -1 && num < current_patrol.moving_page.objects.size())
    {
        current_patrol.moving_page.objects.removeAt(num);
    }
}

void Supervisor::setPatrolObjectSize(int num, int point, int x, int y)
{
    if(num > -1 && num < current_patrol.moving_page.objects.size())
    {
        qDebug() << "setPatrolObjectSize" << num << point << x << y;
        current_patrol.moving_page.objects[num].x += x;
        current_patrol.moving_page.objects[num].y += y;
        current_patrol.moving_page.objects[num].width -= x;
        current_patrol.moving_page.objects[num].height -= y;
    }
}

void Supervisor::clearPatrolPage(int num)
{
    if(num == -1)
    {
        current_patrol.moving_page.objects.clear();
    }
    else if(num > -1 && num < patrols.size())
    {
        current_patrol.moving_page = patrols[num].moving_page;
    }
}

void Supervisor::moveServingObject(int num, int x, int y)
{
    if(num > -1 && num < serving_page.objects.size())
    {
        serving_page.objects[num].x = x;
        serving_page.objects[num].y = y;
    }
}

void Supervisor::setServingObjectSize(int num, int x, int y, int width, int height)
{
    if(num > -1 && num < serving_page.objects.size())
    {
        serving_page.objects[num].x = x;
        serving_page.objects[num].y = y;
        serving_page.objects[num].width = width;
        serving_page.objects[num].height = height;
    }
}

void Supervisor::deleteServingObject(int num)
{
    if(num > -1 && num < serving_page.objects.size())
    {
        serving_page.objects.removeAt(num);
    }
}

void Supervisor::setServingObjectSize(int num, int point, int x, int y)
{
    if(num > -1 && num < serving_page.objects.size())
    {
        qDebug() << "setServingObjectSize" << num << point << x << y;
        serving_page.objects[num].x += x;
        serving_page.objects[num].y += y;
        serving_page.objects[num].width -= x;
        serving_page.objects[num].height -= y;
    }
}

void Supervisor::clearServingPage()
{
    qDebug() << "clearServingPage";
    serving_page.objects.clear();
}

void Supervisor::log_advanced(const QString& str)
{
    std::cerr << str.toStdString() << std::endl;
    plog->write(str);
}
