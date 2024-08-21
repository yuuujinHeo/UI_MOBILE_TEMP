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
int ui_state = 0;
bool is_test_moving = false;
bool is_debug = false;
#define MAIN_THREAD 200

QString getIniPath(QString file){
    return QDir::homePath()+"/RB_MOBILE/config/"+file+"_config.ini";
}

QString getSettings(QString file, QString group, QString name){
    QString ini_path = getIniPath(file);
    QSettings setting_robot(ini_path, QSettings::IniFormat);
    setting_robot.beginGroup(group);
    return setting_robot.value(name).toString();
}

Supervisor::Supervisor(QObject *parent)
    : QObject(parent)
{
    checkShellFiles();
    Py_Initialize();

    plog->write("[SUPERVISOR] Program Started. Supervisor constructed.");

    //기존 SLAM/NAV 모두 종료하고 다시 시작
    QList<QString> path_home_str = QDir::homePath().split("/");
    QProcess process;
    QString file = QDir::homePath() + "/RB_MOBILE/sh/killall.sh";
    process.start(file,QStringList(),QProcess::ReadWrite);
    if(!process.waitForFinished()){
        plog->write("[SUPERVISOR] Kill All Failed");
    }else{
        plog->write("[SUPERVISOR] Kill All");
    }
    // process->waitForReadyRead(3000);

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
    checker = new CMD_CHECKER();//Checker();

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

    //checker->getNetworkState("");
    checker->getNetworkState();

    initServingPage();
//    checker->setIP("mobile_robot_mesh","10.108.1.132","24","10.108.1.1","10.108.1.1","8.8.8.8");
//    qDebug() << "INTERNET : " << QNetworkConfigurationManager::isOnline();
}

Supervisor::~Supervisor(){
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

void Supervisor::emo_state_changed(){
    if(probot->status_emo==0){
        playVoice("error_emo");
    }
}
////*********************************************  WINDOW 관련   ***************************************************////
void Supervisor::setWindow(QQuickWindow *Window){
    plog->write("[SUPERVISOR] SET WINDOW ");
    mMain = Window;
}
QQuickWindow *Supervisor::getWindow()
{
    return mMain;
}
void Supervisor::setObject(QObject *object)
{
    mObject = object;
}
QObject *Supervisor::getObject()
{
    //rootobject를 리턴해준다.
    return mObject;
}

void Supervisor::got_message(QString msg){
    qDebug() << "got message" << msg;
    QMetaObject::invokeMethod(mMain, "new_message",Qt::DirectConnection,
      Q_ARG(QVariant,QVariant().fromValue(msg)));
}
////***********************96980101451808****************************////
void Supervisor::update_fail(){
    QMetaObject::invokeMethod(mMain, "update_fail");
}
void Supervisor::update_success(){
    QMetaObject::invokeMethod(mMain, "update_success");
}

void Supervisor::programRestart(){
    plog->write("[COMMAND] programRestart");
    ipc->clearSharedMemory(ipc->shm_cmd);

    //BJ_TRY
    slam_process->kill();
    //QCoreApplication::quit();

    //240809 yujin - pm2 start -> restart twice
    QProcess::startDetached(QApplication::applicationFilePath(),QStringList());
    QApplication::exit(12);
}

void Supervisor::programExit(){
    plog->write("[COMMAND] programExit");
    slam_process->kill();
    QCoreApplication::quit();
}

void Supervisor::writelog(QString msg){
    plog->write(msg);
}

void Supervisor::setCursorView(bool visible){
    if(visible){
        QGuiApplication::setOverrideCursor(QCursor(Qt::ArrowCursor));
    }else{
        QGuiApplication::setOverrideCursor(QCursor(Qt::BlankCursor));
    }
}


QString Supervisor::getRawMapPath(QString name){
    return QDir::homePath()+"/RB_MOBILE/maps/"+name+"/map_raw.png";
}
QString Supervisor::getMapPath(QString name){
    return QDir::homePath()+"/RB_MOBILE/maps/"+name+"/map_edited.png";
}
QString Supervisor::getAnnotPath(QString name){
    return QDir::homePath()+"/RB_MOBILE/maps/"+name+"/annotation.ini";
}
QString Supervisor::getMetaPath(QString name){
    return QDir::homePath()+"/RB_MOBILE/maps/"+name+"/map_meta.ini";
}
QString Supervisor::getTravelPath(QString name){
    return QDir::homePath()+"/RB_MOBILE/maps/"+name+"/map_travel_line.png";
}
QString Supervisor::getCostPath(QString name){
    return QDir::homePath()+"/RB_MOBILE/maps/"+name+"/map_cost.png";
}
// QString Supervisor::getIniPath(QString file){
//     return QDir::homePath()+"/RB_MOBILE/config/"+file+"_config.ini";
// }

////*********************************수정해야해*****************************************//
void Supervisor::loadMapServer(){
//    if(getSetting("SERVER",))
//    ipc->sendCommand(ROBOT_CMD_SERVER_MAP_LOAD);
}

void Supervisor::sendMapServer(){
    ipc->sendCommand(ROBOT_CMD_SERVER_MAP_UPDATE);
}

bool Supervisor::checkGroupName(QString name){
    for(int i=0; i<pmap->location_groups.size(); i++){
        if(pmap->location_groups[i] == name){
            return false;
        }
    }
    return true;
}

bool Supervisor::checkLocationName(int group, QString name){
    for(int i=0; i<pmap->serving_locations.size(); i++){
        if(pmap->serving_locations[i].group == group){
            if(pmap->serving_locations[i].name == name){
                return false;
            }
        }
    }
    return true;
}

////*********************************************  CALLING 관련   ***************************************************////
void Supervisor::clear_call(){
    if(setting_call_num > -1){
        if(setting_call_type == "Charging"){
            plog->write("[COMMAND] clear_call "+setting_call_type+" "+QString::number(setting_call_num)+" : "
                        +pmap->charging_locations[setting_call_num].type + ", "  + pmap->charging_locations[setting_call_num].name);
            pmap->charging_locations[setting_call_num].call_id = "";
        }else if(setting_call_type == "Resting"){
            plog->write("[COMMAND] clear_call "+setting_call_type+" "+QString::number(setting_call_num)+" : "
                        +pmap->resting_locations[setting_call_num].type + ", "  + pmap->resting_locations[setting_call_num].name);
            pmap->resting_locations[setting_call_num].call_id = "";
        }else if(setting_call_type == "Cleaning"){
            plog->write("[COMMAND] clear_call "+setting_call_type+" "+QString::number(setting_call_num)+" : "
                        +pmap->cleaning_locations[setting_call_num].type + ", "  + pmap->cleaning_locations[setting_call_num].name);
            pmap->cleaning_locations[setting_call_num].call_id = "";
        }else if(setting_call_type == "Init"){
            plog->write("[COMMAND] clear_call "+setting_call_type+" "+QString::number(setting_call_num)+" : "
                        +pmap->init_locations[setting_call_num].type + ", "  + pmap->init_locations[setting_call_num].name);
            pmap->init_locations[setting_call_num].call_id = "";
        }else{
            plog->write("[COMMAND] clear_call "+setting_call_type+" "+QString::number(setting_call_num)+" : "
                        +pmap->serving_locations[setting_call_num].type + ", "  + pmap->serving_locations[setting_call_num].name);
            pmap->serving_locations[setting_call_num].call_id = "";
        }

        setting_call_num = -1;
        setting_call_type = "";
        QMetaObject::invokeMethod(mMain, "call_setting");
    }
}

void Supervisor::new_call_order(QString table){
    bool match_call = false;
    for(int i=0; i<pmap->serving_locations.size(); i++){
        if(pmap->serving_locations[i].name == table){
            match_call = true;
            break;
        }
    }
    if(match_call){
        pmap->call_queue.push_back(table);
        plog->write("[SERVER] NEW CALL ORDER : "+table+" ( queue size "+QString::number(pmap->call_queue.size())+" )");
    }else{
        plog->write("[SERVER] NEW CALL ORDER : "+table+" (Wrong ID -> Ignored)");
    }
}

void Supervisor::new_call(){
    if(setting_call_num > -1){
        if(setting_call_type == "Charging"){
            if(setting_call_num<pmap->charging_locations.size()){
                plog->write("[CALL] newCall : SET CallBell "+pmap->charging_locations[setting_call_num].name+" -> "+call->getBellID());
                pmap->charging_locations[setting_call_num].call_id = call->getBellID();
            }
        }else if(setting_call_type == "Resting"){
            if(setting_call_num<pmap->resting_locations.size()){
                plog->write("[CALL] newCall : SET CallBell "+pmap->resting_locations[setting_call_num].name+" -> "+call->getBellID());
                pmap->resting_locations[setting_call_num].call_id = call->getBellID();
            }
        }else if(setting_call_type == "Cleaning"){
            if(setting_call_num<pmap->cleaning_locations.size()){
                plog->write("[CALL] newCall : SET CallBell "+pmap->cleaning_locations[setting_call_num].name+" -> "+call->getBellID());
                pmap->cleaning_locations[setting_call_num].call_id = call->getBellID();
            }
        }else if(setting_call_type == "Init"){
            if(setting_call_num<pmap->init_locations.size()){
                plog->write("[CALL] newCall : SET CallBell "+pmap->init_locations[setting_call_num].name+" -> "+call->getBellID());
                pmap->init_locations[setting_call_num].call_id = call->getBellID();
            }
        }else{
            if(setting_call_num<pmap->serving_locations.size()){
                plog->write("[CALL] newCall : SET CallBell "+pmap->serving_locations[setting_call_num].name+" -> "+call->getBellID());
                pmap->serving_locations[setting_call_num].call_id = call->getBellID();
            }
        }
        setting_call_num = -1;
        setting_call_type = "";
        QMetaObject::invokeMethod(mMain, "call_setting");
    }else{
        bool already_in = false;

        qDebug() <<"ui state = " << ui_state;

        bool match = false;
        QString name = "";
        for(int i=0; i<pmap->charging_locations.size(); i++){
            if(pmap->charging_locations[i].call_id == call->getBellID()){
                name = pmap->charging_locations[i].name;
                match = true;
                break;
            }
        }
        if(!match){
            for(int i=0; i<pmap->resting_locations.size(); i++){
                if(pmap->resting_locations[i].call_id == call->getBellID()){
                    name = pmap->resting_locations[i].name;
                    match = true;
                    break;
                }
            }
        }
        if(!match){
            for(int i=0; i<pmap->cleaning_locations.size(); i++){
                if(pmap->cleaning_locations[i].call_id == call->getBellID()){
                    name = pmap->cleaning_locations[i].name;
                    match = true;
                    break;
                }
            }
        }
        if(!match){
            for(int i=0; i<pmap->init_locations.size(); i++){
                if(pmap->init_locations[i].call_id == call->getBellID()){
                    name = pmap->init_locations[i].name;
                    match = true;
                    break;
                }
            }
        }
        if(!match){
            for(int i=0; i<pmap->serving_locations.size(); i++){
                if(pmap->serving_locations[i].call_id == call->getBellID()){
                    name = pmap->serving_locations[i].name;
                    match = true;
                    break;
                }
            }
        }

        for(int i=0; i<pmap->call_queue.size(); i++){
            if(pmap->call_queue[i] == name){
                already_in = true;
                plog->write("[CALL] newCall : "+name+" ("+call->getBellID()+") -> already queue in");
                break;
            }
        }
        if(!already_in){
            if(name != ""){
                pmap->call_queue.push_back(name);
                plog->write("[CALL] newCall : "+name+" ("+call->getBellID()+")");
            }else{
                plog->write("[CALL] newCall : no found callbell ("+call->getBellID()+")");
            }
        }
    }
}

void Supervisor::setCallbellForce(QString type, bool onoff){
    plog->write("[COMMAND] setCallbellForce : "+type+" -> "+onoff);
    if(type == "Resting"){
        if(onoff){
            setSetting("setting","CALL/force_resting","true");
        }else{
            setSetting("setting","CALL/force_resting","false");
        }
    }else if(type == "Cleaning"){
        if(onoff){
            setSetting("setting","CALL/force_cleaning","true");
        }else{
            setSetting("setting","CALL/force_cleaning","false");
        }
    }
}

void Supervisor::setCallbell(QString type, int id){
    setting_call_type = type;
    setting_call_num = id;
    plog->write("[COMMAND] setCallbell : "+type+" , "+QString::number(setting_call_num));
}


////*********************************************  SETTING 관련   ***************************************************////
void Supervisor::git_pull_success(){
    plog->write("[supervisor]git_pull_success:[UPDATE] Git Pull : Success -> Program Restart");
    programRestart();
}

void Supervisor::git_pull_fail(int reason){
    if(reason == 0){
        plog->write("[supervisor]git_pull_fail:[UPDATE] Git Pull : Failed -> Maybe need Reset");
        QMetaObject::invokeMethod(mMain, "git_pull_fail");
    }else{//nothing
        plog->write("[supervisor]git_pull_fail:[UPDATE] Git Pull : Failed -> Program Already Newest");
        QMetaObject::invokeMethod(mMain, "git_pull_already");
    }
}

void Supervisor::playSound(QString name, int volume){
    click_effect->stop();

    if(volume == -1){
        volume = getSetting("setting","UI","volume_button").toInt();
    }

    // qDebug() << "playSound : " << name << volume;

    if(name == "click"){
        click_effect->setSource(QUrl("qrc:/bgm/click.wav"));
        click_effect->setVolume(float(volume)/100.0);
        click_effect->play();
    }else if(name == "no"){
        click_effect->setSource(QUrl("qrc:/bgm/click_error.wav"));
        click_effect->setVolume(float(volume)/100.0);
        click_effect->play();
    }else if(name == "start"){
        click_effect->setSource(QUrl("qrc:/bgm/click_start.wav"));
        click_effect->setVolume(float(volume)/100.0);
        click_effect->play();
    }
}

bool Supervisor::isNewVersion(){
    //깃 최신버전인지.
    return server->need_update();
}
bool Supervisor::isNeedUpdate(){
    //서버업데이트 필요한 지.
    return server->new_update;
}
void Supervisor::refreshVersion(){
    qDebug() << "refreshVersion";
    server->getCurVersion("MAIN_MOBILE");
    server->getNewVersion("MAIN_MOBILE");
    server->getNewVersions("MAIN_MOBILE");
}
QString Supervisor::getNewVersion(){
    return server->ui_version_new.version;
}
QString Supervisor::getCurVersion(){
    return server->ui_version.version;
}
QString Supervisor::getCurVersionDate(){
    return server->ui_version.date;
}

QString Supervisor::getLocalVersion(){
    return getSetting("robot","VERSION","last_update_date");
}
QString Supervisor::getServerVersion(){
    if(server->program_version != ""){
        return server->program_version;
    }else{
        if(probot->gitList.size() > 0)
            return probot->gitList[0].date;
        else
            return "NONE";
    }
}
QString Supervisor::getLocalVersionDate(){
    return getSetting("robot","VERSION","last_update_date");
}
QString Supervisor::getLocalVersionMessage(){
    return probot->program_message;
}
QString Supervisor::getServerVersionMessage(){
    if(probot->gitList.size() > 0){
        return probot->gitList[0].message;
    }else{
        return "";
    }
}

QString Supervisor::getUpdateDate(){
    return server->last_update_date;
}

int Supervisor::getUpdateSize(){
    return server->update_list.size();
}

QString Supervisor::getUpdateFileName(int num){
    QStringList list = server->update_list.keys();
    return list[num];
}

QString Supervisor::getUpdateCommit(QString name){
    return server->update_list[name].commit;
}
QString Supervisor::getUpdateMessage(QString name){
    return server->update_list[name].message;
}
QString Supervisor::getLastUpdateDate(QString name){
    return server->version_list[name].date;
}
void Supervisor::checkCleaningLocation(){
    // if(getLocationNum("Cleaning") == 0){
    //     plog->write("[ANNOTATION] Cleaning Mode : no found Location. make new");
    //     LOCATION temp;
    //     temp.point = getLocation(0,"Resting0").point;
    //     temp.angle = getLocation(0,"Resting0").angle;
    //     temp.type = "Cleaning";
    //     temp.group = 0;
    //     temp.group_name = "Cleaning";
    //     temp.name = "Cleaning0";
    //     temp.call_id = "";
    //     pmap->locations.push_back(temp);
    //     saveAnnotation("");
    // }
}
int Supervisor::getNewVersionsSize(){
    return server->ui_new_versions.size();
}
QString Supervisor::getNewVersion(int i){
    return server->ui_new_versions[i].version;
}
QString Supervisor::getNewVersionDate(int i){
    return server->ui_new_versions[i].date;

}
QString Supervisor::getNewVersionMessage(int i){
    return server->ui_new_versions[i].message;

}
QString Supervisor::getCurrentCommit(QString name){
    return server->version_list[name].commit;
}
void Supervisor::updateProgram(QString _v){
    plog->write("[UPDATE] Update UI version : "+_v);
    server->doUpdateUI(_v);
}
void Supervisor::updateProgram(){
    server->doUpdate();
}
void Supervisor::updateProgramGitPull(){
    checker->gitPull();
    plog->write("[UPDATE][Checker]supervisor: update program git pull");
}
void Supervisor::gitReset(){
    checker->gitReset();
    probot->program_branch = getSetting("setting","UI","program_branch");
}

void Supervisor::restartUpdate(){
    plog->write("[UPDATE] USER CMD : Restart Update");
    //File rename.
//    server->rename_all();
    //Start Update.sh
    QString file = QDir::homePath()+"/RB_MOBILE/sh";

    QProcess *tempprocess = new QProcess(this);
    setSetting("robot","SERVER/update","true");
    slam_process = new QProcess(this);
    tempprocess->setWorkingDirectory(file);
    tempprocess->start("xterm",QStringList()<<"./update.sh");

}
void Supervisor::startUpdate(){
    //Zip 압축풀기
//#ifdef EXTPROC_TEST
//    checker->gitPull();
//#else
//    extproc->update_unzip();
//#endif
}

void Supervisor::checkVersionAgain(){
    server->check_update = true;
    server->checkUpdate();
}




QString Supervisor::getGoqualID(){
    return server->goqual_login.id;
}
QString Supervisor::getGoqualPassword(){
    return server->goqual_login.passwd;
}
QString Supervisor::getGoqualClientID(){
    return server->goqual_login.client_id;
}
QString Supervisor::getGoqualClientSecret(){
    return server->goqual_login.client_secret;
}
QString Supervisor::getGoqualAccessKey(){
    return server->goqual_token.access_key;
}
QString Supervisor::getGoqualRefreshKey(){
    return server->goqual_token.refresh_key;
}
QString Supervisor::getGoqualExpiresIn(){
    return QString::number(server->goqual_token.expires_in);
}

void Supervisor::getGoqualKey(){
    server->getGoqualKey();
}
void Supervisor::refreshGoqualKey(){
    server->refreshGoqualKey();
}
void Supervisor::getGoqualDeviceList(){
    server->getGoqualDevices();
}

void Supervisor::setGoqualDevice(QString id, bool onoff){
    qDebug() << "setRelay " << id << onoff;
    server->setGoqualRelay(id,onoff);
}


int Supervisor::getGoqualDeviceSize(){
    return server->goqual_relays.size();
}

QString Supervisor::getGoqualDeviceID(int num){
    if(num>-1 && num < server->goqual_relays.size()){
        QStringList key = server->goqual_relays.keys();
        return server->goqual_relays[key[num]].id;
    }
}
QString Supervisor::getGoqualDeviceName(int num){
    if(num>-1 && num < server->goqual_relays.size()){
        QStringList key = server->goqual_relays.keys();
        return server->goqual_relays[key[num]].name;
    }
}

QString Supervisor::getGoqualDeviceType(int num){
    if(num>-1 && num < server->goqual_relays.size()){
        QStringList key = server->goqual_relays.keys();
        return server->goqual_relays[key[num]].type;
    }
}
bool Supervisor::getGoqualDeviceState(int num){
    if(num>-1 && num < server->goqual_relays.size()){
        QStringList key = server->goqual_relays.keys();
        return server->goqual_relays[key[num]].state;
    }
}
bool Supervisor::getGoqualDeviceOnline(int num){
    if(num>-1 && num < server->goqual_relays.size()){
        QStringList key = server->goqual_relays.keys();
        return server->goqual_relays[key[num]].online;
    }
}


void Supervisor::saveSetting(){
    plog->write("[COMMAND] saveSetting");
    QString setting_path = QDir::homePath()+"/RB_MOBILE/config/setting_config.ini";
    QString update_path = QDir::homePath()+"/RB_MOBILE/config/update_config.ini";
    QString static_path = QDir::homePath()+"/RB_MOBILE/config/static_config.ini";

    QString new_setting_path = QDir::homePath()+"/RB_MOBILE/config/setting_config.backup";
    QString new_update_path = QDir::homePath()+"/RB_MOBILE/config/update_config.backup";
    QString new_static_path = QDir::homePath()+"/RB_MOBILE/config/static_config.backup";

    if(QFile::exists(setting_path)){

        if(QFile::exists(new_setting_path)){
            QFile::remove(new_setting_path);
        }

        if(QFile::copy(setting_path, new_setting_path)){
            plog->write("[COMMAND] saveSetting : setting_config -> success");
        }else{
            plog->write("[COMMAND] saveSetting : setting_config -> failed");
        }
    }else{
        plog->write("[COMMAND] saveSetting : setting_config -> no file found");
    }

    if(QFile::exists(update_path)){

        if(QFile::exists(new_update_path)){
            QFile::remove(new_update_path);
        }
        if(QFile::copy(update_path, new_update_path)){
            plog->write("[COMMAND] saveSetting : update_config -> success");
        }else{
            plog->write("[COMMAND] saveSetting : update_config -> failed");
        }
    }else{
        plog->write("[COMMAND] saveSetting : update_config -> no file found");
    }

    if(QFile::exists(static_path)){

        if(QFile::exists(new_static_path)){
            QFile::remove(new_static_path);
        }
        if(QFile::copy(static_path, new_static_path)){
            plog->write("[COMMAND] saveSetting : static_config -> success");
        }else{
            plog->write("[COMMAND] saveSetting : static_config -> failed");
        }
    }else{
        plog->write("[COMMAND] saveSetting : static_config -> no file found");
    }
}

void Supervisor::loadSetting(){
    plog->write("[COMMAND] loadSetting");

    QString setting_path = QDir::homePath()+"/RB_MOBILE/config/setting_config.ini";
    QString update_path = QDir::homePath()+"/RB_MOBILE/config/update_config.ini";
    QString static_path = QDir::homePath()+"/RB_MOBILE/config/static_config.ini";

    QString backup_setting_path = QDir::homePath()+"/RB_MOBILE/config/setting_config.backup";
    QString backup_update_path = QDir::homePath()+"/RB_MOBILE/config/update_config.backup";
    QString backup_static_path = QDir::homePath()+"/RB_MOBILE/config/static_config.backup";

    if(QFile::exists(backup_setting_path)){

        if(QFile::exists(setting_path)){
            QFile::remove(setting_path);
        }
        if(QFile::copy(backup_setting_path, setting_path)){
            plog->write("[COMMAND] loadSetting : setting_config -> success");
        }else{
            plog->write("[COMMAND] loadSetting : setting_config -> failed");
        }
    }else{
        plog->write("[COMMAND] loadSetting : setting_config -> no file found");
    }

    if(QFile::exists(backup_update_path)){

        if(QFile::exists(update_path)){
            QFile::remove(update_path);
        }
        if(QFile::copy(backup_update_path, update_path)){
            plog->write("[COMMAND] loadSetting : update_config -> success");
        }else{
            plog->write("[COMMAND] loadSetting : update_config -> failed");
        }
    }else{
        plog->write("[COMMAND] loadSetting : update_config -> no file found");
    }

    if(QFile::exists(backup_static_path)){

        if(QFile::exists(static_path)){
            QFile::remove(static_path);
        }
        if(QFile::copy(backup_static_path, static_path)){
            plog->write("[COMMAND] loadSetting : static_config -> success");
        }else{
            plog->write("[COMMAND] loadSetting : static_config -> failed");
        }
    }else{
        plog->write("[COMMAND] loadSetting : static_config -> no file found");
    }

}

void Supervisor::setSetting(QString file, QString name, QString value){
    QString ini_path = getIniPath(file);
    QSettings setting(ini_path, QSettings::IniFormat);
    setting.setValue(name,value);
    plog->write("[SETTING] SET "+name+" VALUE TO "+value);
}
QString Supervisor::getSetting(QString file, QString group, QString name){
    return getSettings(file,group,name);
    // QString ini_path = getIniPath(file);
    // QSettings setting_robot(ini_path, QSettings::IniFormat);
    // setting_robot.beginGroup(group);
    // return setting_robot.value(name).toString();
}

void Supervisor::readSetting(QString map_name){
    plog->write("[SUPERVISOR] READ SETTING : "+map_name);
    //Robot Setting================================================================
    QString ini_path = getIniPath("setting");
    QSettings setting_config(ini_path, QSettings::IniFormat);

    setting_config.beginGroup("ROBOT_TYPE");
    probot->model = setting_config.value("model").toString();
    probot->serial_num = setting_config.value("serial_num").toInt();
    probot->name = probot->model;// + QString::number(probot->serial_num);
    // probot->type = setting_config.value("type").toString();
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

    probot->program_branch = getSetting("setting","UI","probram_branch");

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
    QDir dir_release = QDir(QDir::homePath()+"/RB_MOBILE/release");
    QList<QString> releases = dir_release.entryList();
    server->version_list.clear();
    for(int i=0; i<releases.size(); i++){
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

    if(map_name == ""){
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
    if(pmap->edited_width > 0){
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
    LOCATION temp_loc;


    setting_anot.beginGroup("charging_locations");
    int num = setting_anot.value("num").toInt();
    QString loc_str;
    for(int i=0; i<num; i++){
        loc_str = setting_anot.value("loc"+QString::number(i)).toString();
        QStringList strlist = loc_str.split(",");
        if(strlist.size()>1){
            temp_loc.point = cv::Point2f(strlist[1].toFloat(),strlist[2].toFloat());
            temp_loc.angle = strlist[3].toFloat();
            temp_loc.group = 0;
            temp_loc.group_name = "Charging";
            temp_loc.type = "Charging";
            temp_loc.name = strlist[0];
            if(strlist.size() > 4){
                temp_loc.call_id = strlist[4].split(":")[0];
                if(strlist[4].split(":").size()>1)
                    temp_loc.ling_id = strlist[4].split(":")[1];
                else
                    temp_loc.ling_id = "";
            }else{
                temp_loc.call_id = "";
                temp_loc.ling_id = "";
            }
            pmap->charging_locations.push_back(temp_loc);
        }
    }
    setting_anot.endGroup();


    setting_anot.beginGroup("resting_locations");
    num = setting_anot.value("num").toInt();
    for(int i=0; i<num; i++){
        loc_str = setting_anot.value("loc"+QString::number(i)).toString();
        QStringList strlist = loc_str.split(",");
        if(strlist.size()>1){
            temp_loc.point = cv::Point2f(strlist[1].toFloat(),strlist[2].toFloat());
            temp_loc.angle = strlist[3].toFloat();
            temp_loc.group = 0;
            temp_loc.group_name = "Resting";
            temp_loc.type = "Resting";
            temp_loc.name = strlist[0];
            if(strlist.size() > 4){
                temp_loc.call_id = strlist[4].split(":")[0];
                if(strlist[4].split(":").size()>1)
                    temp_loc.ling_id = strlist[4].split(":")[1];
                else
                    temp_loc.ling_id = "";
            }else{
                temp_loc.call_id = "";
                temp_loc.ling_id = "";
            }
            pmap->resting_locations.push_back(temp_loc);
        }
    }
    setting_anot.endGroup();


    setting_anot.beginGroup("cleaning_locations");
    num = setting_anot.value("num").toInt();
    for(int i=0; i<num; i++){
        loc_str = setting_anot.value("loc"+QString::number(i)).toString();
        QStringList strlist = loc_str.split(",");
        if(strlist.size()>1){
            temp_loc.point = cv::Point2f(strlist[1].toFloat(),strlist[2].toFloat());
            temp_loc.angle = strlist[3].toFloat();
            temp_loc.group = 0;
            temp_loc.group_name = "Cleaning";
            temp_loc.type = "Cleaning";
            temp_loc.name = strlist[0];
            if(strlist.size() > 4){
                temp_loc.call_id = strlist[4].split(":")[0];
                if(strlist[4].split(":").size()>1)
                    temp_loc.ling_id = strlist[4].split(":")[1];
                else
                    temp_loc.ling_id = "";
            }else{
                temp_loc.call_id = "";
                temp_loc.ling_id = "";
            }
            pmap->cleaning_locations.push_back(temp_loc);
        }
    }
    setting_anot.endGroup();

    setting_anot.beginGroup("init_locations");
    num = setting_anot.value("num").toInt();
    for(int i=0; i<num; i++){
        loc_str = setting_anot.value("loc"+QString::number(i)).toString();
        QStringList strlist = loc_str.split(",");
        if(strlist.size()>1){
            temp_loc.point = cv::Point2f(strlist[1].toFloat(),strlist[2].toFloat());
            temp_loc.angle = strlist[3].toFloat();
            temp_loc.group = 0;
            temp_loc.group_name = "Init";
            temp_loc.type = "Init";
            temp_loc.name = strlist[0];
            if(strlist.size() > 4){
                temp_loc.call_id = strlist[4].split(":")[0];
                if(strlist[4].split(":").size()>1)
                    temp_loc.ling_id = strlist[4].split(":")[1];
                else
                    temp_loc.ling_id = "";
            }else{
                temp_loc.call_id = "";
                temp_loc.ling_id = "";
            }
            pmap->init_locations.push_back(temp_loc);
        }
    }
    setting_anot.endGroup();


    setting_anot.beginGroup("serving_locations");
    int total_serv_num = 0;
    int group_num = setting_anot.value("group").toInt();
    setting_anot.endGroup();
    pmap->location_groups.clear();
    int temp_id = 2;
    for(int i=0; i<group_num; i++){
        setting_anot.beginGroup("serving_"+QString::number(i));
        int serv_num = setting_anot.value("num").toInt();
        total_serv_num +=serv_num;
        QString group_name = setting_anot.value("name").toString();
        pmap->location_groups.append(group_name);
        for(int j=0; j<serv_num; j++){
            QString loc_str = setting_anot.value("loc"+QString::number(j)).toString();
            QStringList strlist = loc_str.split(",");
            temp_loc.point = cv::Point2f(strlist[1].toFloat(),strlist[2].toFloat());
            temp_loc.angle = strlist[3].toFloat();
            temp_loc.type = "Serving";
            temp_loc.name = strlist[0];
            temp_loc.group_name = pmap->location_groups[i];
            if(strlist.size() > 4){
                temp_loc.call_id = strlist[4].split(":")[0];
                if(strlist[4].split(":").size()>1)
                    temp_loc.ling_id = strlist[4].split(":")[1];
                else
                    temp_loc.ling_id = "";
            }else{
                temp_loc.call_id = "";
                temp_loc.ling_id = "";
            }

            temp_loc.group = i;
            pmap->serving_locations.push_back(temp_loc);
        }
        setting_anot.endGroup();
    }



    tts->readVoiceSetting();
    plog->write("[SUPERVISOR] READ SETTING : annot done");

    //Set Variable
    probot->trays.clear();
    for(int i=0; i<setting.tray_num; i++){
        ST_TRAY temp;
        probot->trays.push_back(temp);
    }
    maph->loadFile(map_name,"");
    QMetaObject::invokeMethod(mMain, "update_ini");
}

QString Supervisor::makeLingbell(){
    int maxnum = 1;
    for(int i=0; i<pmap->charging_locations.size(); i++){
        if(pmap->charging_locations[i].ling_id.right(7).toInt() >= maxnum){
            maxnum = pmap->charging_locations[i].ling_id.right(7).toInt();
        }
    }
    for(int i=0; i<pmap->resting_locations.size(); i++){
        if(pmap->resting_locations[i].ling_id.right(7).toInt() >= maxnum){
            maxnum = pmap->resting_locations[i].ling_id.right(7).toInt();
        }
    }
    for(int i=0; i<pmap->cleaning_locations.size(); i++){
        if(pmap->cleaning_locations[i].ling_id.right(7).toInt() >= maxnum){
            maxnum = pmap->cleaning_locations[i].ling_id.right(7).toInt();
        }
    }
    for(int i=0; i<pmap->init_locations.size(); i++){
        if(pmap->init_locations[i].ling_id.right(7).toInt() >= maxnum){
            maxnum = pmap->init_locations[i].ling_id.right(7).toInt();
        }
    }
    for(int i=0; i<pmap->serving_locations.size(); i++){
        if(pmap->serving_locations[i].ling_id.right(7).toInt() >= maxnum){
            maxnum = pmap->serving_locations[i].ling_id.right(7).toInt();
        }
    }

    return "F"+QString::asprintf("%07d",maxnum+1);
}
void Supervisor::resetLingbell(int id){
    if(id>-1 && id<pmap->serving_locations.size()){
        pmap->serving_locations[id].ling_id = "";
    }
}

void Supervisor::editLocation(QString type, int num){
    LOCATION temp;
    if(maph->select_charging>-1){
        temp = pmap->charging_locations[maph->select_charging];
        pmap->charging_locations[maph->select_charging].point = probot->lastPose.point;
        pmap->charging_locations[maph->select_charging].angle = probot->lastPose.angle;
    }else if(maph->select_resting>-1){
        temp = pmap->resting_locations[maph->select_resting];
        pmap->resting_locations[maph->select_resting].point = probot->lastPose.point;
        pmap->resting_locations[maph->select_resting].angle = probot->lastPose.angle;
    }else if(maph->select_cleaning>-1){
        temp = pmap->cleaning_locations[maph->select_cleaning];
        pmap->cleaning_locations[maph->select_cleaning].point = probot->lastPose.point;
        pmap->cleaning_locations[maph->select_cleaning].angle = probot->lastPose.angle;
    }else if(maph->select_init>-1){
        temp = pmap->init_locations[maph->select_init];
        pmap->init_locations[maph->select_init].point = probot->lastPose.point;
        pmap->init_locations[maph->select_init].angle = probot->lastPose.angle;
    }else if(maph->select_serving>-1){
        temp = pmap->serving_locations[maph->select_serving];
        pmap->serving_locations[maph->select_serving].point = probot->lastPose.point;
        pmap->serving_locations[maph->select_serving].angle = probot->lastPose.angle;

    }

    plog->write("[ANNOTATION] Edit Location "+QString::number(num)+" : "+QString().asprintf("(%f,%f,%f) -> (%f,%f,%f)",
                                                                                           temp.point.x,temp.point.y,temp.angle,
                                                                                                probot->lastPose.point.x,probot->lastPose.point.y,probot->lastPose.angle));
}

void Supervisor::map_reset(){
    maph->setMapLayer();
}

void Supervisor::setSystemVolume(int volume){
    qDebug() << "setSystemVolume" << volume;
    // setMasterVolume(volume);
    checker->setSystemVolume(volume);
}

// int Supervisor::getLocationNum(QString group, QString name){
//     for(int i=0; i<pmap->locations.size(); i++){
//         if(pmap->locations[i].group == group){
//             if(pmap->locations[i].name == name){
//                 return i;
//             }
//         }
//     }
//     return -1;
// }

void Supervisor::saveLocation(QString type, int groupnum, QString name){
    LOCATION temp;
    temp.type = type;
    temp.name = name;
    temp.group = groupnum;
    temp.call_id = "";
    temp.point = setAxisBack(maph->new_location.point);
    temp.angle = setAxisBack(maph->new_location.angle);

    if(pmap->location_groups.size() == 0){
        pmap->location_groups.push_back("Default");
    }
    if(groupnum < pmap->location_groups.size()){
        temp.group_name = pmap->location_groups[groupnum];
    }

    // bool overwrite = false;
    // int overwrite_num = -1;
    // for(int i=0; i<pmap->locations.size(); i++){
    //     if(pmap->locations[i].name == name){
    //         overwrite = true;
    //         overwrite_num = i;
    //     }else if(name == "Cleaning0" && pmap->locations[i].name == "CleaningTemp"){
    //         overwrite = true;
    //         overwrite_num = i;
    //     }
    // }

    if(type == "Serving"){
        plog->write("[COMMAND] saveLocation : "+type+","+name+","+QString().asprintf("%f,%f,%f",temp.point.x, temp.point.y, temp.angle));
        pmap->serving_locations.push_back(temp);
    }else if(type == "Charging"){
        if(pmap->charging_locations.size() > 0){
            plog->write("[COMMAND] saveLocation (Overwrite): "+type+","+name+","+QString().asprintf("%f,%f,%f",temp.point.x, temp.point.y, temp.angle));
            pmap->charging_locations[0] = temp;
        }else{
            plog->write("[COMMAND] saveLocation : "+type+","+name+","+QString().asprintf("%f,%f,%f",temp.point.x, temp.point.y, temp.angle));
            pmap->charging_locations.push_back(temp);
        }
    }else if(type == "Cleaning"){
        if(pmap->cleaning_locations.size() > 0){
            plog->write("[COMMAND] saveLocation (Overwrite): "+type+","+name+","+QString().asprintf("%f,%f,%f",temp.point.x, temp.point.y, temp.angle));
            pmap->cleaning_locations[0] = temp;
        }else{
            plog->write("[COMMAND] saveLocation : "+type+","+name+","+QString().asprintf("%f,%f,%f",temp.point.x, temp.point.y, temp.angle));
            pmap->cleaning_locations.push_back(temp);
        }
    }else if(type == "Resting"){
        if(pmap->resting_locations.size() > 0){
            plog->write("[COMMAND] saveLocation (Overwrite): "+type+","+name+","+QString().asprintf("%f,%f,%f",temp.point.x, temp.point.y, temp.angle));
            pmap->resting_locations[0] = temp;
        }else{
            plog->write("[COMMAND] saveLocation : "+type+","+name+","+QString().asprintf("%f,%f,%f",temp.point.x, temp.point.y, temp.angle));
            pmap->resting_locations.push_back(temp);
        }
    }else if(type == "Init"){
        plog->write("[COMMAND] saveLocation (init) : "+type+","+name+","+QString().asprintf("%f,%f,%f",temp.point.x, temp.point.y, temp.angle));
        pmap->init_locations.push_back(temp);
    }

    pmap->annot_edit_location = true;

    saveAnnotation(maph->map_name, false);

}
////*********************************************  OBJECTING 관련   ***************************************************////
void Supervisor::addObject(int x, int y){
    maph->addObject(x,y);
}
void Supervisor::addObjectPoint(int x, int y){
    maph->addObjectPoint(x,y);
}
void Supervisor::setObject(int x, int y){
    maph->setObject(x,y);
}
void Supervisor::editObjectStart(int x, int y){
    maph->editObjectStart(x,y);
}
void Supervisor::editObject(int x, int y){
    maph->editObject(x,y);
}
void Supervisor::saveObject(){
    maph->saveObject();
    maph->setObjPose();
}
void Supervisor::clearObject(){
    qDebug() << "clear";
    maph->clearObject();
}
void Supervisor::clearObjectAll(){
    qDebug() << "clear all";
    maph->clearObjectAll();
}
int Supervisor::getObjectNum(int x, int y){
    return maph->getObjectNum(x,y);
}
int Supervisor::getObjectPointNum(int x, int y){
    return maph->getObjectPointNum(x,y);
}
void Supervisor::selectObject(int num){
    maph->selectObject(num);
}
bool Supervisor::getObjectflag(){
    return (ipc->flag_objecting||maph->getObjectFlag());
}
void Supervisor::undoObject(){
    maph->undoObject();
}


//-------------------------------------------------- DB ------------------------------------------------//
void Supervisor::setTableColNum(int col_num){
    setSetting("setting","UI/table_col_num",QString::number(col_num));
    readSetting();
}
int Supervisor::getTrayNum(){
    return setting.tray_num;
}
QString Supervisor::getRobotType(){
    return getSetting("setting","ROBOT_TYPE","type");
}
void Supervisor::setCamera(QString left, QString right){
    setSetting("static","SENSOR/left_camera_serial",left);
    setSetting("static","SENSOR/right_camera_serial",right);
//    readSetting();
}
QString Supervisor::getLeftCamera(){
    return getSetting("static","SENSOR","left_camera_serial");
}
QString Supervisor::getRightCamera(){
    return getSetting("static","SENSOR","right_camera_serial");
}
int Supervisor::getCameraNum(){
    return pmap->camera_info.size();
}
int Supervisor::getRunawayState(){
    return probot->drawing_state;
}
QString Supervisor::getCameraSerial(int num){
    try{
        if(num > -1 && num < pmap->camera_info.size()){
            return pmap->camera_info[num].serial;
        }else{
            return "";
        }
    }catch(...){
        qDebug() << "Something Wrong to get Camera Serial " << num << pmap->camera_info.size();
        return "";
    }
}
//------------------------------------------------- SLAM COMMAND --------------------------------------//
void Supervisor::requestCamera(){
    IPCHandler::CMD send_msg;
    send_msg.cmd = ROBOT_CMD_REQ_CAMERA;
    ipc->set_cmd(send_msg);
}
void Supervisor::drawingRunawayStart(){
    maph->startDrawingTline();
    IPCHandler::CMD send_msg;
    send_msg.cmd = ROBOT_CMD_DRAW_LINE_START;
    ipc->set_cmd(send_msg);
}

void Supervisor::drawingRunawayStop(){
    maph->stopDrawingTline();
    IPCHandler::CMD send_msg;
    send_msg.cmd = ROBOT_CMD_DRAW_LINE_SAVE;
    ipc->set_cmd(send_msg);
}
void Supervisor::slam_map_reload(QString filename, int mode){
    IPCHandler::CMD send_msg;
    if(mode == 0){
        send_msg.cmd = ROBOT_CMD_MAP_RELOAD;
        memcpy(send_msg.params,filename.toUtf8(),sizeof(char)*255);
        ipc->set_cmd(send_msg,"MAP HARD RELOAD");
        probot->localization_state = 0;
        probot->motor[0].status = 0;
        probot->motor[1].status = 0;
        probot->localization_confirm = false;
    }else{
        send_msg.cmd = ROBOT_CMD_MAP_SOFT_RELOAD;
        memcpy(send_msg.params,filename.toUtf8(),sizeof(char)*255);
        ipc->set_cmd(send_msg,"MAP SOFT RELOAD");
    }
}
void Supervisor::slam_ini_reload(){
    IPCHandler::CMD send_msg;
    send_msg.cmd = ROBOT_CMD_SETTING_RELOAD;
    ipc->set_cmd(send_msg,"INI RELOAD");
}

////*********************************************  INIT PAGE 관련   ***************************************************////
bool Supervisor::isConnectServer(){
    return server->connection && server->first_response;
}
void Supervisor::deleteEditedMap(){
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

void Supervisor::deleteAnnotation(){
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
bool Supervisor::isAvailableAnnotation(){
    if(QFile::exists(getAnnotPath(pmap->map_name))){
        if(getLocationNum("Charging")>0 && getLocationNum("Resting")>0){
            return true;
        }else{
            return false;
        }
    }else{
        return false;
    }
}
bool Supervisor::isExistAnnotation(QString name){
    QString file_meta = getMetaPath(name);
    QString file_annot = getAnnotPath(name);

    return QFile::exists(file_annot);
}
bool Supervisor::isExistTravelMap(QString name){
    QString file = getTravelPath(name);
    return QFile::exists(file);
}

int Supervisor::getAvailableMap(){
    std::string path = QString(QDir::homePath()+"/RB_MOBILE/maps").toStdString();
    QDir directory(path.c_str());
    QStringList FileList = directory.entryList();
    map_list.clear();
    for(int i=0; i<FileList.size(); i++){
        if(FileList[i] == "." || FileList[i] == ".."){
            continue;
        }
        QString path3 = QDir::homePath() + "/RB_MOBILE/maps/"+FileList[i];
        QFileInfo info(path3);
        if(!info.isDir()){
            continue;
        }
//        QStringList namelist = FileList[i].split(".");
//        if(namelist.size() > 1){
//            continue;
//        }
        std::string path2 = QString(QDir::homePath()+"/RB_MOBILE/maps/"+FileList[i]).toStdString();
        QDir direc2(path2.c_str());
        QStringList detailList = direc2.entryList();
        bool available = false;
        for(int j=0; j<detailList.size(); j++){
            if(detailList[j].left(4) == "map_"){
                available = true;
                break;
            }

        }
        if(available){
            map_list.push_back(FileList[i]);
        }
    }
    return map_list.size();
}
QString Supervisor::getAvailableMapPath(int num){
    if(num>-1 && num<map_list.size()){
        return map_list[num];
    }
    return "";
}
bool Supervisor::isExistMap(QString name){
    if(name==""){
        name = getMapname();
    }

    if(QFile::exists(getMapPath(name))){
//        if(QFile::exists(getRawMapPath(name))){

//        }else{
//            //make map_raw.png
//            QFile::copy(getMapPath(name),getRawMapPath(name));
//        }
        return true;
    }else{
        return false;
    }
}
bool Supervisor::isExistTlineMap(QString name){
    if(name==""){
        name = getMapname();
    }
    if(QFile::exists(QDir::homePath()+"/RB_MOBILE/maps/"+name+"/map_travel_line.png")){
        return true;
    }else{
        return false;
    }
}
bool Supervisor::isExistVelMap(QString name){
    if(name==""){
        name = getMapname();
    }
    if(QFile::exists(QDir::homePath()+"/RB_MOBILE/maps/"+name+"/map_velocity.png")){
        return true;
    }else{
        return false;
    }
}
bool Supervisor::isExistObjectMap(QString name){
    if(name==""){
        name = getMapname();
    }
    if(QFile::exists(QDir::homePath()+"/RB_MOBILE/maps/"+name+"/map_obs.png")){
        return true;
    }else{
        return false;
    }
}
bool Supervisor::isExistAvoidMap(QString name){
    if(name==""){
        name = getMapname();
    }
    if(QFile::exists(QDir::homePath()+"/RB_MOBILE/maps/"+name+"/map_avoid.png")){
        return true;
    }else{
        return false;
    }
}
bool Supervisor::isExistRawMap(QString name){
    if(QFile::exists(getRawMapPath(name))){
        return true;
    }else{
        return false;
    }
}
bool Supervisor::isLoadMap(){
    //기본 설정된 맵파일 확인
    if(QFile::exists(getMapPath(getMapname()))){
        return true;
    }
    return false;
}
void Supervisor::removeMap(QString filename){
    plog->write("[USER INPUT] Remove Map : "+filename);
    QDir dir(QDir::homePath()+"/RB_MOBILE/maps/" + filename);

    if(dir.removeRecursively()){
        qDebug() << "true";
    }else{
        qDebug() << "false";
    }
}
bool Supervisor::isExistRobotINI(){
    QString file = getIniPath("robot");
    return QFile::exists(file);
}
bool Supervisor::checkINI(){
    QString file = getIniPath("static");
    if(QFile::exists(file)){
        if(getSetting("static","SENSOR","right_camera_serial")=="" || getSetting("static","SENSOR","left_camera_serial")==""){
            return false;
        }
        return true;
    }else{
        return false;
    }
}
void Supervisor::checkRobotINI(){
    //1. Update_config==========================================================
    if(getSetting("update","MOTOR","gear_ratio") == "")
        setSetting("update","MOTOR/gear_ratio","1.0");
    if(getSetting("update","MOTOR","k_d") == "")
        setSetting("update","MOTOR/k_d","4400.0");
    if(getSetting("update","MOTOR","k_i") == "")
        setSetting("update","MOTOR/k_i","0.0");
    if(getSetting("update","MOTOR","k_p") == "")
        setSetting("update","MOTOR/k_p","100.0");
    if(getSetting("update","MOTOR","left_id") == ""&&getSetting("update","MOTOR","right_id") == ""){
        setSetting("update","MOTOR/left_id","1");
        setSetting("update","MOTOR/right_id","0");
    }
    if(getSetting("update","MOTOR","limit_v") == "")
        setSetting("update","MOTOR/limit_v","2");
    if(getSetting("update","MOTOR","limit_v_acc") == "")
        setSetting("update","MOTOR/limit_v_acc","1.5");
    if(getSetting("update","MOTOR","limit_w") == "")
        setSetting("update","MOTOR/limit_w","180.0");
    if(getSetting("update","MOTOR","limit_w_acc") == "")
        setSetting("update","MOTOR/limit_w_acc","180.0");
    if(getSetting("update","MOTOR","wheel_dir") == "")
        setSetting("update","MOTOR/wheel_dir","-1");


    if(getSetting("setting","UI","box_size") == "")
        setSetting("setting","UI/box_size","1");

    if(getSetting("update","DRIVING","cur_preset") == "")
        setSetting("update","DRIVING/cur_preset","3");
    if(getSetting("update","DRIVING","comeback_preset") == "")
        setSetting("update","DRIVING/comeback_preset","3");
    if(getSetting("update","DRIVING","pause_check_ms") == "")
        setSetting("update","DRIVING/pause_check_ms","500");
    if(getSetting("update","DRIVING","pause_motor_current") == "")
        setSetting("update","DRIVING/pause_motor_current","3000");

    if(getSetting("update","DRIVING","goal_dist") == "")
        setSetting("update","DRIVING/goal_dist","0.05");
    if(getSetting("update","DRIVING","goal_th") == "")
        setSetting("update","DRIVING/goal_th","1");
    if(getSetting("update","DRIVING","goal_near_dist") == "")
        setSetting("update","DRIVING/goal_near_dist","0.3");
    if(getSetting("update","DRIVING","goal_near_th") == "")
        setSetting("update","DRIVING/goal_near_th","15");
    if(getSetting("update","DRIVING","goal_v") == "")
        setSetting("update","DRIVING/goal_v","0.05");
    if(getSetting("update","DRIVING","k_curve") == "")
        setSetting("update","DRIVING/k_curve","0.005");
    if(getSetting("update","DRIVING","k_v") == "")
        setSetting("update","DRIVING/k_v","1.5");
    if(getSetting("update","DRIVING","k_w") == "")
        setSetting("update","DRIVING/k_w","1.5");
    if(getSetting("update","DRIVING","k_dd") == "")
        setSetting("update","DRIVING/k_dd","1.25");
    if(getSetting("update","DRIVING","path_out_dist") == "")
        setSetting("update","DRIVING/path_out_dist","1");
    if(getSetting("update","DRIVING","st_v") == "")
        setSetting("update","DRIVING/st_v","0.05");
    if(getSetting("update","DRIVING","look_ahead_dist") == "")
        setSetting("update","DRIVING/look_ahead_dist","1");
    if(getSetting("update","DRIVING","min_look_ahead_dist") == "")
        setSetting("update","DRIVING/min_look_ahead_dist","0.1");
    if(getSetting("update","DRIVING","path_delta_v_acc_gain") == "")
        setSetting("update","DRIVING/path_delta_v_acc_gain","1");
    if(getSetting("update","DRIVING","path_delta_v_dec_gain") == "")
        setSetting("update","DRIVING/path_delta_v_dec_gain","0.5");
    if(getSetting("update","DRIVING","path_ref_v_gain") == "")
        setSetting("update","DRIVING/path_ref_v_gain","0.8");
    if(getSetting("update","DRIVING","path_shifting_val") == "")
        setSetting("update","DRIVING/path_shifting_val","0");

    if(getSetting("update","SLAM","slam_submap_cnt") == "")
        setSetting("update","SLAM/slam_submap_cnt","100");
    if(getSetting("update","SLAM","slam_lc_dist") == "")
        setSetting("update","SLAM/slam_lc_dist","10");
    if(getSetting("update","SLAM","slam_lc_icp_dist") == "")
        setSetting("update","SLAM/slam_lc_icp_dist","2");
    if(getSetting("update","SLAM","map_size") == "")
        setSetting("update","SLAM/map_size","1000");
    if(getSetting("update","SLAM","grid_size") == "")
        setSetting("update","SLAM/grid_size","0.05");


    if(getSetting("update","LOCALIZATION","icp_dist") == "")
        setSetting("update","LOCALIZATION/icp_dist","0.2");
    if(getSetting("update","LOCALIZATION","icp_error") == "")
        setSetting("update","LOCALIZATION/icp_error","0.1");
    if(getSetting("update","LOCALIZATION","icp_near") == "")
        setSetting("update","LOCALIZATION/icp_near","1");
    if(getSetting("update","LOCALIZATION","icp_odometry_weight") == "")
        setSetting("update","LOCALIZATION/icp_odometry_weight","0.8");
    if(getSetting("update","LOCALIZATION","icp_ratio") == "")
        setSetting("update","LOCALIZATION/icp_ratio","0.5");
    if(getSetting("update","LOCALIZATION","icp_repeat_dist") == "")
        setSetting("update","LOCALIZATION/icp_repeat_dist","0.1");
    if(getSetting("update","LOCALIZATION","icp_repeat_time") == "")
        setSetting("update","LOCALIZATION/icp_repeat_time","0.3");


    //2. Setting_config=========================================================
    if(getSetting("setting","UI","group_row_num") == "")
        setSetting("setting","UI/group_row_num","2");
    if(getSetting("setting","UI","group_col_num") == "")
        setSetting("setting","UI/group_col_num","4");
    if(getSetting("setting","UI","table_row_num") == "")
        setSetting("setting","UI/table_row_num","5");
    if(getSetting("setting","UI","table_col_num") == "")
        setSetting("setting","UI/table_col_num","1");
    if(getSetting("setting","UI","moving_face") == "")
        setSetting("setting","UI/moving_face","1");
    if(getSetting("setting","UI","language") == "")
        setSetting("setting","UI/language","korean");
    if(getSetting("setting","UI","voice_mode") == "")
        setSetting("setting","UI/voice_mode","basic");
    if(getSetting("setting","UI","program_branch") == "")
        setSetting("setting","UI/program_branch","master");
    if(getSetting("setting","UI","voice_language") == "")
        setSetting("setting","UI/voice_language","ko");
    if(getSetting("setting","UI","voice_name") == "")
        setSetting("setting","UI/voice_name","none");
    if(getSetting("setting","UI","voice_speed") == "")
        setSetting("setting","UI/voice_speed","0");
    if(getSetting("setting","UI","voice_pitch") == "")
        setSetting("setting","UI/voice_pitch","0");
    if(getSetting("setting","UI","voice_alpha") == "")
        setSetting("setting","UI/voice_alpha","0");
    if(getSetting("setting","UI","voice_emotion") == "")
        setSetting("setting","UI/voice_emotion","0");
    if(getSetting("setting","UI","voice_emotion_strength") == "")
        setSetting("setting","UI/voice_emotion_strength","1");
    if(getSetting("setting","UI","volume_bgm") == "")
        setSetting("setting","UI/volume_bgm","50");
    if(getSetting("setting","UI","volume_voice") == "")
        setSetting("setting","UI/volume_voice","50");
    if(getSetting("setting","UI","volume_button") == "")
        setSetting("setting","UI/volume_button","50");
    if(getSetting("setting","UI","user_passwd") == "")
        setSetting("setting","UI/user_passwd","1111");

    if(getSetting("setting","CALL","call_maximum") == "")
        setSetting("setting","CALL/call_maximum","1");

    if(getSetting("setting","CALL","use_lingbell") == "")
        setSetting("setting","CALL/use_lingbell","false");

    if(getSetting("setting","CALL","use_lingbell_repeat") == "")
        setSetting("setting","CALL/use_lingbell_repeat","false");

    if(getSetting("setting","CALL","lingbell_time") == "")
        setSetting("setting","CALL/lingbell_time","5");

    if(getSetting("setting","PRESET1","name")==""){
        setSetting("setting","PRESET1/name","매우느리게");
        setSetting("setting","PRESET1/limit_pivot","30.0");
        setSetting("setting","PRESET1/limit_pivot_acc","60");
        setSetting("setting","PRESET1/limit_v","0.2");
        setSetting("setting","PRESET1/limit_v_acc","0.3");
        setSetting("setting","PRESET1/limit_w","75");
        setSetting("setting","PRESET1/limit_w_acc","90");
    }
    if(getSetting("setting","PRESET2","name")==""){
        setSetting("setting","PRESET2/name","느리게");
        setSetting("setting","PRESET2/limit_pivot","30");
        setSetting("setting","PRESET2/limit_pivot_acc","60");
        setSetting("setting","PRESET2/limit_v","0.4");
        setSetting("setting","PRESET2/limit_v_acc","0.3");
        setSetting("setting","PRESET2/limit_w","75");
        setSetting("setting","PRESET2/limit_w_acc","90");
    }
    if(getSetting("setting","PRESET3","name")==""){
        setSetting("setting","PRESET3/name","보통");
        setSetting("setting","PRESET3/limit_pivot","30");
        setSetting("setting","PRESET3/limit_pivot_acc","60");
        setSetting("setting","PRESET3/limit_v","0.6");
        setSetting("setting","PRESET3/limit_v_acc","0.3");
        setSetting("setting","PRESET3/limit_w","75");
        setSetting("setting","PRESET3/limit_w_acc","90");
    }
    if(getSetting("setting","PRESET4","name")==""){
        setSetting("setting","PRESET4/name","빠르게");
        setSetting("setting","PRESET4/limit_pivot","30");
        setSetting("setting","PRESET4/limit_pivot_acc","60");
        setSetting("setting","PRESET4/limit_v","0.8");
        setSetting("setting","PRESET4/limit_v_acc","0.3");
        setSetting("setting","PRESET4/limit_w","75");
        setSetting("setting","PRESET4/limit_w_acc","90");
    }
    if(getSetting("setting","PRESET5","name")==""){
        setSetting("setting","PRESET5/name","매우빠르게");
        setSetting("setting","PRESET5/limit_pivot","30");
        setSetting("setting","PRESET5/limit_pivot_acc","60");
        setSetting("setting","PRESET5/limit_v","1.0");
        setSetting("setting","PRESET5/limit_v_acc","0.3");
        setSetting("setting","PRESET5/limit_w","75");
        setSetting("setting","PRESET5/limit_w_acc","90");
    }

    if(getSetting("setting","ROBOT_TYPE","type") == "")
        setSetting("setting","ROBOT_TYPE/type","BOTH");
    if(getSetting("setting","ROBOT_TYPE","model") == "")
        setSetting("setting","ROBOT_TYPE/model","None");
    if(getSetting("setting","ROBOT_TYPE","serial_num") == "")
        setSetting("setting","ROBOT_TYPE/serial_num","0");
    if(getSetting("setting","ROBOT_TYPE","tray_num") == "")
        setSetting("setting","ROBOT_TYPE/tray_num","2");

    if(getSetting("setting","USE_SLAM","use_uicmd") == "")
        setSetting("setting","USE_SLAM/use_uicmd","true");
    if(getSetting("setting","USE_SLAM","use_early_stop_resting") == "")
        setSetting("setting","USE_SLAM/use_early_stop_resting","false");
    if(getSetting("setting","USE_SLAM","use_early_stop_serving") == "")
        setSetting("setting","USE_SLAM/use_early_stop_serving","false");
    if(getSetting("setting","USE_SLAM","use_obs_preview") == "")
        setSetting("setting","USE_SLAM/use_obs_preview","true");

    if(getSetting("setting","SENSOR","cam_exposure")=="")
        setSetting("setting","SENSOR/cam_exposure","2000");
    if(getSetting("setting","SENSOR","mask")=="")
        setSetting("setting","SENSOR/mask","10.0");
    if(getSetting("setting","SENSOR","max_range")=="")
        setSetting("setting","SENSOR/max_range","40.0");

    if(getSetting("setting","OBSTACLE","obs_check_range")=="")
        setSetting("setting","OBSTACLE/obs_check_range","2.5");
    if(getSetting("setting","OBSTACLE","obs_deadzone")=="")
        setSetting("setting","OBSTACLE/obs_deadzone","0.4");
    if(getSetting("setting","OBSTACLE","obs_preview_time")=="")
        setSetting("setting","OBSTACLE/obs_preview_time","3");
    if(getSetting("setting","OBSTACLE","obs_wait_time")=="")
        setSetting("setting","OBSTACLE/obs_wait_time","1");
    if(getSetting("setting","OBSTACLE","obs_detect_area")=="")
        setSetting("setting","OBSTACLE/obs_detect_area","2");
    if(getSetting("setting","OBSTACLE","obs_detect_sensitivity")=="")
        setSetting("setting","OBSTACLE/obs_detect_sensitivity","2");
    if(getSetting("setting","OBSTACLE","obs_height_max")=="")
        setSetting("setting","OBSTACLE/obs_height_max","0.5");
    if(getSetting("setting","OBSTACLE","obs_height_min")=="")
        setSetting("setting","OBSTACLE/obs_height_min","0.1");
    if(getSetting("setting","OBSTACLE","obs_margin0")=="")
        setSetting("setting","OBSTACLE/obs_margin0","0.05");
    if(getSetting("setting","OBSTACLE","obs_margin1")=="")
        setSetting("setting","OBSTACLE/obs_margin1","0.05");
    if(getSetting("setting","OBSTACLE","obs_avoid_v")=="")
        setSetting("setting","OBSTACLE/obs_avoid_v","0.2");
    if(getSetting("setting","OBSTACLE","obs_avoid_width")=="")
        setSetting("setting","OBSTACLE/obs_avoid_width","1");
    if(getSetting("setting","OBSTACLE","obs_near")=="")
        setSetting("setting","OBSTACLE/obs_near","1");
    if(getSetting("setting","OBSTACLE","obs_early_stop_dist")=="")
        setSetting("setting","OBSTACLE/obs_early_stop_dist","1");
    if(getSetting("setting","OBSTACLE","obs_decel_gain")=="")
        setSetting("setting","OBSTACLE/obs_decel_gain","0.8");

    if(getSetting("setting","INITIALIZATION","icp_init_ratio") == "")
        setSetting("setting","INITIALIZATION/icp_init_ratio","0.7");
    if(getSetting("setting","INITIALIZATION","icp_init_error") == "")
        setSetting("setting","INITIALIZATION/icp_init_error","0.2");
    if(getSetting("setting","INITIALIZATION","icp_mapping_ratio") == "")
        setSetting("setting","INITIALIZATION/icp_mapping_ratio","0.7");
    if(getSetting("setting","INITIALIZATION","icp_mapping_error") == "")
        setSetting("setting","INITIALIZATION/icp_mapping_error","0.2");


    //3. Static_config==========================================================
    if(getSetting("static","ROBOT_HW","wheel_base") == "")
        setSetting("static","ROBOT_HW/wheel_base","0.3542");
    if(getSetting("static","ROBOT_HW","wheel_radius") == "")
        setSetting("static","ROBOT_HW/wheel_radius","0.0635");
    if(getSetting("static","ROBOT_HW","robot_radius") == "")
        setSetting("static","ROBOT_HW/robot_radius","0.3");
    if(getSetting("static","ROBOT_HW","robot_length") == "")
        setSetting("static","ROBOT_HW/robot_length","0.52");

    if(getSetting("static","SENSOR","lidar_offset_tf") == "")
        setSetting("static","SENSOR/lidar_offset_tf","0.17,0.0,-178.0");
    if(getSetting("static","SENSOR","left_camera_tf") == "")
        setSetting("static","SENSOR/left_camera_tf","0.27,0.1,0.2,62.0,0.0,115.0");
    if(getSetting("static","SENSOR","right_camera_tf") == "")
        setSetting("static","SENSOR/right_camera_tf","0.27,-0.1,0.2,-62.0,0.0,-115.0");

}
void Supervisor::makeRobotINI(){
    QString updatep = getIniPath("update");
    QString settingp = getIniPath("setting");
    QString staticp = getIniPath("static");
    QString robotp = getIniPath("robot");

    if(QFile::exists(updatep) && QFile::exists(settingp) && QFile::exists(staticp)){
        plog->write("[SUPERVISOR] Make Robot Ini : Already good");
    }else{
        checkRobotINI();
        readSetting();
        slam_ini_reload();
    }
}

bool Supervisor::rotate_map(QString _src, QString _dst, int mode){
    cv::Mat map1 = cv::imread(_src.toStdString());

    cv::rotate(map1,map1,cv::ROTATE_90_CLOCKWISE);
    cv::flip(map1, map1, 0);
    QImage temp_image = QPixmap::fromImage(mat_to_qimage_cpy(map1)).toImage();
    QString path = QDir::homePath()+"/RB_MOBILE/maps/"+_dst;
    QDir directory(path);
    if(!directory.exists()){
        directory.mkpath(".");
    }

    //Save PNG File
    if(mode == 1){//edited
        if(temp_image.save(QDir::homePath()+"/RB_MOBILE/maps/"+_dst+"/map_edited.png","PNG")){
            QFile *file = new QFile(QGuiApplication::applicationDirPath()+"/"+_src);
            file->remove();
            plog->write("[MAP] Save edited Map : "+_dst);
            return true;
        }else{
            plog->write("[MAP] Fail to save edited Map : "+_dst);
            return false;
        }
    }else if(mode == 2){//raw
        if(temp_image.save(QDir::homePath()+"/RB_MOBILE/maps/"+_dst+"/map_raw.png","PNG")){
            QFile *file = new QFile(QGuiApplication::applicationDirPath()+"/"+_src);
            file->remove();
            plog->write("[MAP] Save raw Map : "+_dst);
            return true;
        }else{
            plog->write("[MAP] Fail to save raw Map : "+_dst);
            return false;
        }
    }
}
bool Supervisor::getIPCConnection(){
    return ipc->getConnection();
}
int  Supervisor::getusbsize(){
    return usb_list.size();
}
QString Supervisor::getusbname(int num){
    if(num > -1 && num < usb_list.size()){
        return usb_list[num];
    }
    return "";
}

void Supervisor::readusb(){

}

void Supervisor::saveMapfromUsb(QString path){
    std::string user = getenv("USER");
    std::string path1 = "/media/" + user + "/";

    QString orin_path = path1.c_str() + path;
    QStringList kk = path.split('/');
    kk.pop_front();

    QString new_path = QCoreApplication::applicationDirPath();
    for(int i=0; i<kk.size(); i++){
        new_path += "/" + kk[i];
    }
    if(QFile::exists(orin_path)){
        if(QFile::copy(orin_path, new_path)){
            plog->write("[SETTING] Save Map from USB : "+kk[kk.length()-1]);
        }else{
            plog->write("[SETTING - ERROR] Save Map from USB (Copy failed): "+kk[kk.length()-1]);
        }
    }else{
        plog->write("[SETTING - ERROR] Save Map from USB (Origin not found): "+kk[kk.length()-1]);
    }
}
void Supervisor::CopyPath(QString src, QString dst){
    QDir dir(src);
    if (! dir.exists())
        return;

    foreach (QString d, dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot)) {
        QString dst_path = dst + QDir::separator() + d;
        dir.mkpath(dst_path);
        CopyPath(src+ QDir::separator() + d, dst_path);
    }

    foreach (QString f, dir.entryList(QDir::Files)) {
        QFile::copy(src + QDir::separator() + f, dst + QDir::separator() + f);
    }
}

int Supervisor::copyMap(QString orinname, QString newname){
    plog->write("[SETTING] Copy Map orin = "+orinname+", new = "+newname);

    QString orin_path = QDir::homePath() + "/RB_MOBILE/maps/" + orinname;
    QString new_path = QDir::homePath() + "/RB_MOBILE/maps/" + newname;

    QDir dir(orin_path);

    if(QFile::exists(orin_path)){
        if(QFile::exists(new_path)){
            plog->write("[SETTING] Copy Map failed : Already has");
            return 2;
        }else{
            if(QDir().mkdir(new_path)){
                CopyPath(orin_path, new_path);
                return 0;
            }else{
                plog->write("[SETTING] Copy Map failed : new Folder make failed");
                return 2;
            }
        }
    }else{
        plog->write("[SETTING] Copy Map failed : No orinFile");
        return 1;
    }
}
void Supervisor::loadMap(QString name){
    setSetting("setting","MAP/map_path",QDir::homePath()+"/RB_MOBILE/maps/"+name);
    setSetting("setting","MAP/map_name",name);
    readSetting(name);
    slam_map_reload(name);
}
void Supervisor::restartSLAM(){
    ipc->clearSharedMemory(ipc->shm_cmd);
    if(slam_process != nullptr){
        plog->write("[SUPERVISOR] RESTART SLAM -> PID : "+QString::number(slam_process->processId()));
        if(slam_process->state() == QProcess::NotRunning){
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
        }else if(slam_process->state() == QProcess::Starting){
            plog->write("[SUPERVISOR] RESTART SLAM -> STARTING");
        }else{
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
    }else{
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
void Supervisor::startSLAM(){
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
void Supervisor::startMapping(int mapsize, float grid){
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

void Supervisor::stopMapping(){
    plog->write("[USER INPUT] STOP MAPPING");
    ipc->flag_mapping = false;
    ipc->is_mapping = false;
    ipc->stopMapping();
    readSetting(getMapname());
}
void Supervisor::saveMapping(QString name){
    ipc->flag_mapping = false;
    ipc->is_mapping = false;
    ipc->saveMapping(name);

}
void Supervisor::setSLAMMode(int mode){

}
void Supervisor::setInitCurPos(){
    maph->set_init_pose = probot->curPose;
    plog->write("[LOCALIZATION] SET INIT POSE : "+QString().asprintf("%f, %f, %f",maph->set_init_pose.point.x, maph->set_init_pose.point.y, maph->set_init_pose.angle));
}

void Supervisor::slam_setInit(){
    POSE temp = setAxisBack(maph->set_init_pose.point,maph->set_init_pose.angle);
    plog->write("[SLAM] SLAM SET INIT : "+QString().asprintf("%f, %f, %f",temp.point.x,temp.point.y,temp.angle));

    ipc->setInitPose(temp.point.x, temp.point.y, temp.angle);
}
void Supervisor::slam_run(){
    ipc->set_cmd(ROBOT_CMD_SLAM_RUN, "LOCALIZATION RUN");

}
void Supervisor::slam_stop(){
    ipc->set_cmd(ROBOT_CMD_SLAM_STOP, "LOCALIZATION STOP");
}
void Supervisor::slam_autoInit(){
    plog->write("[LOCALIZATION] AUTO INIT : "+QString::number(pmap->map_rotate_angle));
    ipc->set_cmd(ROBOT_CMD_SLAM_AUTO, "LOCALIZATION AUTO INIT");
}
void Supervisor::slam_restInit(){
    plog->write("[LOCALIZATION] REST INIT : "+QString::number(pmap->map_rotate_angle));
    ipc->set_cmd(ROBOT_CMD_SLAM_RESTING, "LOCALIZATION REST INIT");
}
void Supervisor::slam_fullautoInit(){
    plog->write("[LOCALIZATION] FULL AUTO INIT : "+QString::number(pmap->map_rotate_angle));
    ipc->set_cmd(ROBOT_CMD_SLAM_FULL_AUTO, "LOCALIZATION FULL AUTO INIT");

}
bool Supervisor::is_slam_running(){
    if(probot->localization_state == LOCAL_READY){
        return true;
    }else{
        return false;
    }
}
bool Supervisor::getMappingflag(){
    return ipc->flag_mapping;

}

void Supervisor::play_voice(ST_VOICE voice){
    voice_player->stop();
    voice_player->setMedia(QUrl::fromLocalFile(voice.file_path));
    if(voice.volume == -1){
        voice.volume = getSetting("setting","UI","volume_voice").toInt();
    }
    voice_player->setVolume(voice.volume);
    voice_player->play();
    plog->write("[SOUND] play_voice : "+voice.file_path + "(volume = "+QString::number(voice.volume)+")");
}

void Supervisor::makePatrolTTS(int language, int voice, QString text, bool play){
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
QString Supervisor::getTTSMention(QString text){
    return tts->getMentionStr(text);
}
void Supervisor::setTTSMention(QString text, QString mention){
    tts->setMentionStr(text,mention);
}

void Supervisor::playVoice(QString file, QString voice, QString mode, QString language, int volume){
    ST_VOICE v;

    if(mode == ""){
        if(probot->is_patrol){
            if(current_patrol.voice_mode == "none"){
                v.mode = getSetting("setting","UI","voice_mode");
            }else{
                v.mode = current_patrol.voice_mode;
            }
        }else{
            v.mode = getSetting("setting","UI","voice_mode");
        }
    }else{
        v.mode = mode;
    }



    if(file == "test"){
        volume = 50;
    }else if(volume == -1){
        if(probot->is_patrol){
            if(current_patrol.voice_mode == "none"){
                volume = tts->curVoice.volume;
            }else{
                volume = current_patrol.voice_volume;
                if(current_patrol.voice_volume == 0){
                    volume = 50;
                    qDebug() << "fuck";
                }
            }
        }else{
            volume = tts->curVoice.volume;
        }
    }

    if(v.mode == "basic"){
        if(voice == ""){
            if(probot->is_patrol){
                if(current_patrol.voice_mode == "none"){
                    v.voice = getSetting("setting","UI","voice_name");
                }else{
                    v.voice = current_patrol.voice_name;
                }
            }else{
                v.voice = getSetting("setting","UI","voice_name");
            }
        }else{
            v.voice = voice;
        }

        if(v.voice == "woman"|| v.voice == "child"){

        }else{
            v.voice = "woman";
        }

        voice_player->stop();
        voice_player->setMedia(QUrl("qrc:/voice/"+v.voice+"_"+file+".mp3"));
        voice_player->setVolume(volume);
        voice_player->play();
        plog->write("[SUPERVISOR] Play Voice (Basic) : "+v.voice + ", " + file);
    }else{
        if(voice == ""){
            if(probot->is_patrol){
                if(current_patrol.voice_mode == "none"){
                    v.voice = tts->curVoice.voice;//getSetting("setting","UI","voice_name");
                }else{
                    v.voice = current_patrol.voice_name;
                }
            }else{
                v.voice = tts->curVoice.voice;//getSetting("setting","UI","voice_name");
            }
        }else{
            v.voice = voice;
        }

        QString filepath = QDir::homePath()+"/RB_MOBILE/voice/"+v.voice+"_"+file+".mp3";
        if(QFile::exists(filepath)){
            voice_player->stop();
            voice_player->setMedia(QUrl::fromLocalFile(filepath));
            voice_player->setVolume(volume);
            voice_player->play();
            plog->write("[SOUND] PlayVoiceTTS : "+filepath+", "+QString::number(volume));
        }else{
            v.file = file;
            v.file_path = filepath;
            v.volume = volume;
            if(probot->is_patrol){
                if(current_patrol.voice_mode == "none"){
                    v.mention = tts->getMentionStr(file);
                }else{
                    v.mention = tts->getMentionBasicStr(v.language,v.file);// (file);
                }

            }else{
                v.mention = tts->getMentionStr(file);
            }
            v.language = language;
            plog->write("[SOUND] PlayVoiceTTS : no file and make -> "+filepath);
            tts->makeTTS(v,true);
        }
    }
}

void Supervisor::makeTTSAll(){
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

    for(QString f : makeList){
        v.file = f;
        v.file_path = QDir::homePath()+"/RB_MOBILE/voice/"+v.voice+"_"+v.file+".mp3";
        v.mention = tts->getMentionStr(v.file);
        tts->makeTTS(v,false);
    }

}

bool Supervisor::isplayBGM(){
    if(bgm_player->state() == QMediaPlayer::PlayingState){
        return true;
    }else{
        return false;
    }
}
void Supervisor::playBGM(int volume){
    list_bgm->addMedia(QUrl("qrc:/bgm/song.mp3"));
    list_bgm->setPlaybackMode(QMediaPlaylist::Loop);
    bgm_player->setPlaylist(list_bgm);
    if(volume == -1){
        volume = getSetting("setting","UI","volume_bgm").toInt();
    }
    plog->write("[SOUND] playBGM : "+QString::number(volume));
    bgm_player->setVolume(volume);
    bgm_player->play();
}
void Supervisor::setvolumeBGM(int volume){
    bgm_player->setVolume(volume);
    plog->write("[SOUND] playBGMVolume : "+QString::number(volume));
}
void Supervisor::stopBGM(){
    bgm_player->stop();
}

QString Supervisor::getnewMapname(){
    int max_num = -1;
    for(int i=0; i<getAvailableMap(); i++){
        QStringList name = map_list[i].split("_");
        if(name.size() > 1 && name[0] == "map"){
            if(name[1].toInt() > max_num){
                max_num = name[1].toInt();
            }
        }
    }
    if(max_num == -1){
        return "map_0";
    }else{
        return "map_"+QString::number(max_num+1);
    }
}


void Supervisor::usb_detect(){
    std::string user = getenv("USER");
    std::string path = "/media/" + user;
    QDir directory(path.c_str());
    QStringList temp = directory.entryList();
    usb_list.clear();
    usb_file_list.clear();
    usb_file_full_list.clear();
    foreach (QString name, temp) {
        if(name != "." && name != ".."){
            usb_list.append(name);

            QDir dd(directory.path()+"/"+name);
            QStringList files = dd.entryList();

            foreach(QString file, files){
                QStringList ex = file.split(".");
                if(ex.size() > 1){

                    if(ex[1] == "zip"){
                        if(ex[0].left(11) == "MobileRobot"){
                            QStringList names = ex[0].split("_");
                            if(names.size() == 3){
                                usb_file_full_list.append(name+"/"+file);
                                usb_file_list.append(names[2]);
                                qDebug() << "FIND !!!!!" << ex[0];
                            }
                        }
                    }else{
                        continue;
                    }
                }else{
                    continue;
                }
            }
        }
    }

    plog->write("[USB] NEW USB Detected : "+QString::number(usb_list.size()));

}

int Supervisor::getusberrorsize(){
    return zip->errorlist.size();
}

int Supervisor::getusbfilesize(){
    return usb_file_list.size();
}
QString Supervisor::getusbfile(int num){
    if(usb_file_full_list.size() > num && num > -1)
        return usb_file_full_list[num];
    else
        return "";
}
QString Supervisor::getusbrecentfile(){
    double temp = 0;
    QString filename = "";
    for(int i=0; i<usb_file_list.size(); i++){
        QString tempstr = usb_file_list[i];
        if(temp < tempstr.toDouble()){
            temp = tempstr.toDouble();
            filename = tempstr;
        }
    }
    return filename;


}
QString Supervisor::getusberror(int num){
    if(num > -1 && num < zip->errorlist.size()){
        return zip->errorlist[num];
    }else{
        return "";
    }
}

void Supervisor::readusbrecentfile(){
    double temp = 0;
    int num = -1;
    for(int i=0; i<usb_file_list.size(); i++){
        QString tempstr = usb_file_list[i];
        if(temp < tempstr.toDouble()){
            temp = tempstr.toDouble();
            num = i;
        }
    }
    if(num == -1){
        return;
    }

    QString path = getusbfile(num);
    zip->getZip(path);
}

void Supervisor::callCallbell(QString id){
    call->sendCall(id);
}

void Supervisor::updateUSB(){
    QString updatestr = QDir::homePath()+"/RB_MOBILE/sh/updateusb.sh";
    if(!QFile::exists(updatestr)){
        makeUSBShell();
    }
    updatestr = QDir::homePath()+"/RB_MOBILE/sh/updatedummy.sh";
    if(!QFile::exists(updatestr)){
        QString file_name = QDir::homePath() + "/RB_MOBILE/sh/updatedummy.sh";
        QFile file(file_name);
        if(file.open(QIODevice::ReadWrite)){
            QTextStream stream(&file);
            stream << "#!/bin/bash" << "\n" << "\n";

            stream << "/home/odroid/RB_MOBILE/sh/updateusb.sh" << "\n";
        }
        file.close();
        //Chmod
        QProcess process;
        process.setWorkingDirectory(QDir::homePath()+"/RB_MOBILE/sh");
        process.start("chmod +x updatedummy.sh",QStringList(),QProcess::ReadWrite);
        process.waitForReadyRead(200);
    }
    QProcess process;
    process.setWorkingDirectory(QDir::homePath()+"/RB_MOBILE/sh");
    process.start("xterm ./updatedummy.sh",QStringList(),QProcess::ReadWrite);
    process.waitForReadyRead(3000);
}

void Supervisor::makeExtProcessShell(){
//    QString file_name = QDir::homePath() + "/RB_MOBILE/sh/startextproc.sh";
//    QFile file(file_name);
//    if(file.open(QIODevice::ReadWrite)){
//        QTextStream stream(&file);
//        stream << "#!/bin/bash" << "\n" << "\n";
//        stream << "while [ 1 ]"<<"\n";
//        stream << "do"<<"\n";
//        stream << "     pid=`ps -ef | grep \"ExtProcess\" | grep -v 'grep' | awk '{print $2}'`"<<"\n";
//        stream << "     if [ -z $pid ]" << "\n";
//        stream << "     then" << "\n";
//        stream << "         /home/odroid/RB_MOBILE/release/ExtProcess" << "\n";
//        stream << "     else" << "\n";
//        stream << "         kill -9 $pid" << "\n";
//        stream << "         /home/odroid/RB_MOBILE/release/ExtProcess" << "\n";
//        stream << "     fi" << "\n";
//        stream << "done" << "\n";
//    }
//    file.close();
//    //Chmod
//    QProcess process;
//    process.setWorkingDirectory(QDir::homePath()+"/RB_MOBILE/sh");
//    process.start("chmod +x startextproc.sh",QStringList(),QProcess::ReadWrite);
//    process.waitForReadyRead(200);

}
void Supervisor::makeUSBShell(){
//    QString file_name = QDir::homePath() + "/RB_MOBILE/sh/updateusb.sh";
//    QFile file(file_name);
//    if(file.open(QIODevice::ReadWrite)){
//        QTextStream stream(&file);
//        stream << "#!/bin/bash" << "\n" << "\n";
//        stream << "cd /home/odroid/RB_MOBILE" << "\n";

//        stream << "if [ -d \"config\" ]" << "\n";
//        stream << "then" << "\n";
//        stream << "    cp config/robot_config.ini /home/odroid/RB_MOBILE/config/robot_config.ini" << "\n";
//        stream << "fi" << "\n";

//        stream << "if [ -d \"sn_log\" ]" << "\n";
//        stream << "then" << "\n";
//        stream << "    cp -R sn_log /home/odroid/" << "\n";
//        stream << "fi" << "\n";

//        stream << "if [ -d \"ui_log\" ]" << "\n";
//        stream << "then" << "\n";
//        stream << "    cp -R ui_log /home/odroid/" << "\n";
//        stream << "fi" << "\n";

//        stream << "if [ -d \"maps\" ]" << "\n";
//        stream << "then" << "\n";
//        stream << "    cp -R maps /home/odroid/" << "\n";
//        stream << "fi" << "\n";

//        stream << "if [ -d \"SLAMNAV\" ]" << "\n";
//        stream << "then" << "\n";
//        stream << "    cp -R SLAMNAV /home/odroid/code/" << "\n";
//        stream << "fi" << "\n";

//        stream << "if [ -d \"build-SLAMNAV-Desktop-Release\" ]" << "\n";
//        stream << "then" << "\n";
//        stream << "    cp -R SLAMNAV_release /home/odroid/code/" << "\n";
//        stream << "fi" << "\n";

//        stream << "if [ -d \"build-SLAMNAV-Desktop-Debug\" ]" << "\n";
//        stream << "then" << "\n";
//        stream << "    cp -R build-SLAMNAV-Desktop-Debug /home/odroid/code/" << "\n";
//        stream << "fi" << "\n";

//        stream << "if [ -d \"UI_MOBILE_release\" ]" << "\n";
//        stream << "then" << "\n";
//        stream << "    cp -R UI_MOBILE_release /home/odroid/" << "\n";
//        stream << "fi" << "\n";

//        stream << "cd /home/odroid" << "\n";
//        stream << "rm -R tempBackup" << "\n";
//        stream << "rm tempBackup.zip" << "\n";

//        stream << "/home/odroid/auto_kill.sh" << "\n";
//        stream << "/home/odroid/UI_MOBILE_release/autostart.sh" << "\n";
//    }
//    file.close();
//    //Chmod
//    QProcess process;
//    process.setWorkingDirectory(QDir::homePath()+"/RB_MOBILE/sh");
//    process.start("chmod +x updateusb.sh");
//    process.waitForReadyRead(200);
}

////*********************************************  ANNOTATION 관련   ***************************************************////
/////Location
///
QString Supervisor::getNewServingName(int group){
    int count = 0;
    QString groupname = "";
    if(group > -1 && group < pmap->location_groups.size()){
        groupname = pmap->location_groups[group];
    }
    // for(int i=0; i<pmap->location_groups.size(); i+)
    // for(int i=0; i<pmap->serving_locations.size(); i++){
    //     if(pmap->serving_locations[i].type == "Serving"){
    //         if(pmap->serving_locations[i].group == group){
    //             groupname = pmap->serving_locations[i].group_name;
    //             break;
    //         }
    //     }
    // }

    if(groupname == "" || groupname == "Default"){
        groupname = "서빙";
    }

    while(isDuplicateName(group, groupname+QString::number(count+1))){
        count++;
    }
    return groupname+QString::number(count+1);
}

bool Supervisor::isDuplicateName(int group, QString name){
    for(int i=0; i<pmap->serving_locations.size(); i++){
        if(pmap->serving_locations[i].group == group){
            if(pmap->serving_locations[i].name == name){
                return true;
            }
        }

    }
    return false;

}
QString Supervisor::getServingName(int group, int num){
    int count = 0;
    QString name = "";
    for(int i=0; i<pmap->serving_locations.size(); i++){
        if(pmap->serving_locations[i].group == group){
            if(count == num)
                name = pmap->serving_locations[i].name;
            count++;
        }
    }
    qDebug() << "getServingName " << group << num << name << pmap->serving_locations.size();
    if(name == ""){
        name = tr("설정 안됨");
    }
    return name;
}
int Supervisor::getLocationNum(QString type){
    if(type == "Charging"){
        return pmap->charging_locations.size();
    }else if(type == "Resting"){
        return pmap->resting_locations.size();
    }else if(type == "Cleaning"){
        return pmap->cleaning_locations.size();
    }else if(type == "Init"){
        return pmap->init_locations.size();
    }else{
        return pmap->serving_locations.size();
    }
}

int Supervisor::getLocationGroupNum(int num){
    if(pmap->serving_locations.size()>num && num > -1){
        if(pmap->location_groups.size() > pmap->serving_locations[num].group)
            return pmap->serving_locations[num].group;
        else
            return 0;
    }
}

QString Supervisor::getLocationCallID(QString type, int num){
    if(type == "Charging" && num>-1 && num<pmap->charging_locations.size()){
        return pmap->charging_locations[num].call_id;
    }else if(type == "Resting" && num>-1 && num<pmap->resting_locations.size()){
        return pmap->resting_locations[num].call_id;
    }else if(type == "Cleaning" && num>-1 && num<pmap->cleaning_locations.size()){
        return pmap->cleaning_locations[num].call_id;
    }else if(type == "Init" && num>-1 && num<pmap->init_locations.size()){
        return pmap->init_locations[num].call_id;
    }else if(type == "Serving" && num>-1 && num<pmap->serving_locations.size()){
        return pmap->serving_locations[num].call_id;
    }
    return "";
}

QString Supervisor::getLocationLingID(QString type, int num){
    if(type == "Charging" && num>-1 && num<pmap->charging_locations.size()){
        return pmap->charging_locations[num].ling_id;
    }else if(type == "Resting" && num>-1 && num<pmap->resting_locations.size()){
        return pmap->resting_locations[num].ling_id;
    }else if(type == "Cleaning" && num>-1 && num<pmap->cleaning_locations.size()){
        return pmap->cleaning_locations[num].ling_id;
    }else if(type == "Init" && num>-1 && num<pmap->init_locations.size()){
        return pmap->init_locations[num].ling_id;
    }else if(type == "Serving" && num>-1 && num<pmap->serving_locations.size()){
        return pmap->serving_locations[num].ling_id;
    }
    return "";
}

void Supervisor::setLocationGroup(int num, int group){
    if(num > -1 && num < pmap->serving_locations.size()){
        pmap->serving_locations[num].group = group;
        plog->write("[ANNOTATION] SET Location Group "+QString().asprintf("%d : %d",num,group));
    }
}

QString Supervisor::getLocationGroup(int num){
    if(num>-1 && num<pmap->serving_locations.size()){
        if(pmap->location_groups.size() > pmap->serving_locations[num].group)
            return pmap->location_groups[pmap->serving_locations[num].group];
    }
    return "(-)";
}

void Supervisor::addLocationGroup(QString name){
    pmap->location_groups.append(name);
    plog->write("[SUPERVISOR] Add Location Group : "+name + "(size = "+QString::number(pmap->location_groups.size())+")");

}
void Supervisor::removeLocationGroup(int num){
    plog->write("[SUPERVISOR] Remove Location Group :"+QString::number(num)+"(size = "+QString::number(pmap->location_groups.size())+")");
    pmap->location_groups.removeAt(num);
}
int Supervisor::getLocationGroupNum(){
    return pmap->location_groups.size();
}
void Supervisor::selectLocation(QString type, int num){
    qDebug() << "selectLocation " << type << num;
    if(type == "Charging"){
        maph->setSelectCharging(num);
    }else if(type == "Resting"){
        maph->setSelectResting(num);
    }else if(type == "Cleaning"){
        maph->setSelectCleaning(num);
    }else if(type == "Init"){
        maph->setSelectInit(num);
    }else{
        maph->setSelectServing(num);
    }
}
bool Supervisor::setLocationUp(int num){
    if(num>0 && num < pmap->serving_locations.size()){
        plog->write("[ANNOTATION] Location "+QString::number(num)+"("+pmap->serving_locations[num].name+") Up");
        pmap->serving_locations.move(num,num-1);
        return true;
    }
    return false;
}
bool Supervisor::setLocationDown(int num){
    qDebug() << num << pmap->serving_locations.size();
    if(num>-1 && num < pmap->serving_locations.size()-1){
        plog->write("[ANNOTATION] Location "+QString::number(num)+"("+pmap->serving_locations[num].name+") Down");
        pmap->serving_locations.move(num,num+1);
        return true;
    }
    return false;
}
int Supervisor::getLocationGroupSize(int num){
    int size = 0;
    if(num > -1 && num < pmap->location_groups.size()){
        for(int i=0; i<pmap->serving_locations.size(); i++){
            if(pmap->serving_locations[i].group == num)
                size++;
        }
    }
//    qDebug() << "location group size " << num << size << pmap->locations.size();
    return size;
}
QString Supervisor::getLocationName(int num, QString type){
    if(type == "Charging" && num>-1 && num<pmap->charging_locations.size()){
        return pmap->charging_locations[num].name;
    }else if(type == "Resting" && num>-1 && num<pmap->resting_locations.size()){
        return pmap->resting_locations[num].name;
    }else if(type == "Cleaning" && num>-1 && num<pmap->cleaning_locations.size()){
        return pmap->cleaning_locations[num].name;
    }else if(type == "Init" && num>-1 && num<pmap->init_locations.size()){
        return pmap->init_locations[num].name;
    }else if(type == "Serving" && num>-1 && num<pmap->serving_locations.size()){
        return pmap->serving_locations[num].name;
    }
    return "-";
}

QString Supervisor::getLocationNameGroup(int num){
    if(num>-1 && num<pmap->serving_locations.size()){
        return pmap->serving_locations[num].group_name;
    }
    return "-";
}

float Supervisor::getLocationX(int num, QString type){
    if(type == "Charging" && num>-1 && num<pmap->charging_locations.size()){
        return setAxis(pmap->charging_locations[num].point).x;
    }else if(type == "Resting" && num>-1 && num<pmap->resting_locations.size()){
        return setAxis(pmap->resting_locations[num].point).x;
    }else if(type == "Cleaning" && num>-1 && num<pmap->cleaning_locations.size()){
        return setAxis(pmap->cleaning_locations[num].point).x;
    }else if(type == "Init" && num>-1 && num<pmap->init_locations.size()){
        return setAxis(pmap->init_locations[num].point).x;
    }else if(type == "Serving" && num>-1 && num<pmap->serving_locations.size()){
        return setAxis(pmap->serving_locations[num].point).x;
    }
    return 0;
}

void Supervisor::setLocation(int num, QString name, int group, int tablenum){
//     if(num > -1 && num < pmap->locations.size()){
//         int count = 0;
//         for(int i=0; i<pmap->locations.size(); i++){
//             if(pmap->locations[i].type == "Serving"){
//                 if(num==count){
//                     pmap->locations[i].name = name;
//                     pmap->locations[i].group = group;
// //                    pmap->locations[i].number = tablenum;
//                     pmap->annot_edit_location = true;
//                     plog->write("[SUPERVISOR] SET LOCATION : "+QString().asprintf("(%d) group : %d, number : %d, name : ",num,group,tablenum)+name);
//                 }
//                 count++;
//             }
//         }
//     }
}
QString Supervisor::getLocGroupname(int num){
    if(num > -1 && num <pmap->location_groups.size()){
        return pmap->location_groups[num];
    }
    return " - ";
}
float Supervisor::getLocationY(int num, QString type){
    if(type == "Charging" && num>-1 && num<pmap->charging_locations.size()){
        return setAxis(pmap->charging_locations[num].point).y;
    }else if(type == "Resting" && num>-1 && num<pmap->resting_locations.size()){
        return setAxis(pmap->resting_locations[num].point).y;
    }else if(type == "Cleaning" && num>-1 && num<pmap->cleaning_locations.size()){
        return setAxis(pmap->cleaning_locations[num].point).y;
    }else if(type == "Init" && num>-1 && num<pmap->init_locations.size()){
        return setAxis(pmap->init_locations[num].point).y;
    }else if(type == "Serving" && num>-1 && num<pmap->serving_locations.size()){
        return setAxis(pmap->serving_locations[num].point).y;
    }
    return 0;
}
float Supervisor::getLocationTH(int num, QString type){
    if(type == "Charging" && num>-1 && num<pmap->charging_locations.size()){
        return setAxis(pmap->charging_locations[num].angle);
    }else if(type == "Resting" && num>-1 && num<pmap->resting_locations.size()){
        return setAxis(pmap->resting_locations[num].angle);
    }else if(type == "Cleaning" && num>-1 && num<pmap->cleaning_locations.size()){
        return setAxis(pmap->cleaning_locations[num].angle);
    }else if(type == "Init" && num>-1 && num<pmap->init_locations.size()){
        return setAxis(pmap->init_locations[num].angle);
    }else if(type == "Serving" && num>-1 && num<pmap->serving_locations.size()){
        return setAxis(pmap->serving_locations[num].angle);
    }
    return 0;
}


float setAxis(float _angle){
    return -_angle - M_PI/2;
}
float setAxisBack(float _angle){
    return -_angle - M_PI/2;
}
cv::Point2f setAxis(cv::Point2f _point){
    cv::Point2f temp;
    temp.x = -_point.y/pmap->gridwidth + pmap->origin[1];
    temp.y = -_point.x/pmap->gridwidth + pmap->origin[0];
    return temp;
}
cv::Point2f setAxisMapping(cv::Point2f _point){
    cv::Point2f temp;
//    qDebug() << "mapping : " << pmap->mapping_gridwidth << pmap->mapping_width;
    float grid = pmap->mapping_gridwidth*pmap->mapping_width/1000;
    temp.x = -_point.y/grid + 1000/2;
    temp.y = -_point.x/grid + 1000/2;
    return temp;
}
cv::Point2f setAxisObject(cv::Point2f _point){
    cv::Point2f temp;
    float grid = pmap->gridwidth*pmap->width/pmap->mapping_width;
    temp.x = -_point.y/grid + pmap->mapping_width/2;
    temp.y = -_point.x/grid + pmap->mapping_width/2;
//    qDebug() << temp.x << temp.y << pmap->width;
    return temp;
}
cv::Point2f setAxisBack(cv::Point2f _point){
    cv::Point2f temp;
    temp.x = -pmap->gridwidth*(_point.y-pmap->origin[1]);
    temp.y = -pmap->gridwidth*(_point.x-pmap->origin[0]);
//    qDebug() << _point.y << temp.x << pmap->gridwidth << pmap->origin[1];
    return temp;
}
POSE setAxis(POSE _pose){
    POSE temp;
    temp.point = setAxis(_pose.point);
    temp.angle = setAxis(_pose.angle);
    return temp;
}

POSE setAxisBack(POSE _pose){
    POSE temp;
    temp.point = setAxisBack(_pose.point);
    temp.angle = setAxisBack(_pose.angle);
    return temp;
}
POSE setAxis(cv::Point2f _point, float _angle){
    POSE temp;
    temp.point = setAxis(_point);
    temp.angle = setAxis(_angle);
    return temp;
}
POSE setAxisBack(cv::Point2f _point, float _angle){
    POSE temp;
    temp.point = setAxisBack(_point);
    temp.angle = setAxisBack(_angle);
    return temp;
}

bool sortWifi(const QString &w1, const QString &w2){
    if(probot->wifi_map[w1].inuse)
        return true;
    else if(probot->wifi_map[w2].inuse)
        return true;
    else{
        return probot->wifi_map[w1].level > probot->wifi_map[w2].level;
    }
}
bool sortLocation2(const LOCATION &l1, const LOCATION &l2){
//    if(l1.group == l2.group)
//        return l1.number < l2.number;
//    else
        return false;
}

int Supervisor::getObjectNum(){
    return pmap->objects.size();
}
QString Supervisor::getObjectName(int num){
    int count = 0;
    if(num > -1 && num < pmap->objects.size()){
        for(int i=0; i<num; i++){
            if(pmap->objects[i].type == pmap->objects[num].type){
                count++;
            }
        }
        return pmap->objects[num].type + "_" + QString::number(count);
    }
}
int Supervisor::getObjectPointSize(int num){
    return pmap->objects[num].points.size();
}
float Supervisor::getObjectX(int num, int point){
    if(num > -1 && num < pmap->objects.size()){
        if(point > -1 && point < pmap->objects[num].points.size()){
            return setAxis(pmap->objects[num].points[point]).x;
        }
    }
    return 0;
}
float Supervisor::getObjectY(int num, int point){
    if(num > -1 && num < pmap->objects.size()){
        if(point > -1 && point < pmap->objects[num].points.size()){
            return setAxis(pmap->objects[num].points[point]).y;
        }
    }
    return 0;
}

bool Supervisor::getAnnotEditFlag(){
    qDebug() << pmap->annot_edit_object << pmap->annot_edit_location;
    if(pmap->annot_edit_object || pmap->annot_edit_location){
        return true;
    }else
        return false;
    return pmap->annotation_edited;
}
void Supervisor::setAnnotEditFlag(bool flag){
    pmap->annotation_edited = flag;
}

void Supervisor::clearSharedMemory(){
    ipc->clearSharedMemory(ipc->shm_cmd);
}
int Supervisor::getObjPointNum(int obj_num, int x, int y){
    //NEED DEBUG
    cv::Point2f pos = setAxisBack(cv::Point2f(x,y));
    if(obj_num < pmap->objects.size() && obj_num > -1){
        qDebug() << "check obj" << obj_num << pmap->objects[obj_num].points.size();
        if(obj_num != -1){
            for(int j=0; j<pmap->objects[obj_num].points.size(); j++){
                qDebug() << pmap->objects[obj_num].points[j].x << pmap->objects[obj_num].points[j].y;
                if(fabs(pmap->objects[obj_num].points[j].x - pos.x) < 0.1){
                    if(fabs(pmap->objects[obj_num].points[j].y - pos.y) < 0.1){
                        qDebug() << "Match Point !!" << obj_num << j;
                        return j;
                    }
                }
            }
        }
    }
    qDebug() << "can't find obj num : " << x << y;
    return -1;
}

void Supervisor::removeLocation(QString type, int num){
    plog->write("[UI-MAP] REMOVE LOCATION "+ type + QString::number(num));
    if(type == "Charging" && num>-1 && num<pmap->charging_locations.size()){
        pmap->annotation_edited = true;
        pmap->charging_locations.removeAt(num);
    }else if(type == "Resting" && num>-1 && num<pmap->resting_locations.size()){
        pmap->annotation_edited = true;
        pmap->resting_locations.removeAt(num);
    }else if(type == "Cleaning" && num>-1 && num<pmap->cleaning_locations.size()){
        pmap->annotation_edited = true;
        pmap->cleaning_locations.removeAt(num);
    }else if(type == "Init" && num>-1 && num<pmap->init_locations.size()){
        pmap->annotation_edited = true;
        pmap->init_locations.removeAt(num);
    }else if(type == "Serving" && num>-1 && num<pmap->serving_locations.size()){
        pmap->annotation_edited = true;
        pmap->serving_locations.removeAt(num);
    }else{
        plog->write("[UI-MAP] REMOVE LOCATION Failed "+ type + QString::number(num));
    }
}

int Supervisor::getObjectSize(QString type){
    int size = 0;
    for(int i=0; i<pmap->objects.size(); i++){
        if(pmap->objects[i].type == type)
            size++;
    }
    return size;
}

void Supervisor::saveLocations(){

}
void Supervisor::removeObject(int num){
//    clear_all();
    if(num > -1 && num < pmap->objects.size()){
        pmap->objects.removeAt(num);
        maph->setObjPose();
        pmap->annotation_edited = true;
        maph->clearObject();
        QMetaObject::invokeMethod(mMain, "updateobject");
        plog->write("[ANNOTATION - ERROR] removeObject " + QString().asprintf("(%d)",num));
    }else{
        plog->write("[ANNOTATION - ERROR] removeObject " + QString().asprintf("(%d)",num) + " but size error");
    }
}

bool Supervisor::isOdroid(){
    if(QDir::homePath().split("/")[2]=="odroid"){
        return true;
    }else{
        return false;
    }
}
void Supervisor::saveNode(){
    maph->saveNode();
    maph->saveAnnotation();
    saveAnnotation("");
}
bool Supervisor::saveAnnotation(QString filename, bool reload){
    plog->write("[COMMAND] saveAnnotation : "+filename);
    //기존 파일 백업
    QString backup = QDir::homePath()+"/RB_MOBILE/maps/"+filename+"/annotation_backup.ini";
    QString origin = getAnnotPath(filename);
    if(QFile::exists(origin) == true){
        if(QFile::copy(origin, backup)){
            plog->write("[DEBUG] Copy annotation.ini to annotation_backup.ini");
        }else{
            plog->write("[DEBUG] Fail to copy annotation.ini to annotation_backup.ini");
        }
    }else{
        plog->write("[DEBUG] Fail to copy annotation.ini to annotation_backup.ini (No file found)");
    }

    if(filename == ""){
        filename = getMapname();
    }

    //데이터 입력(로케이션)
    int other_num = 0;
    int resting_num = 0;
    int charging_num = 0;
    int cleaning_num = 0;
    int init_num = 0;
    int group_num[pmap->location_groups.size()];

    for(int i=0; i<pmap->location_groups.size(); i++)
        group_num[i] = 0;

    QString str_name;
    QSettings settings(getAnnotPath(filename), QSettings::IniFormat);
    settings.clear();

    //name,x,y,th,num,locnum,callid
    for(int i=0; i<pmap->charging_locations.size(); i++){
        str_name = pmap->charging_locations[i].name + QString().asprintf(",%f,%f,%f",pmap->charging_locations[i].point.x,pmap->charging_locations[i].point.y,pmap->charging_locations[i].angle)
                +","+pmap->charging_locations[i].call_id+":"+pmap->charging_locations[i].ling_id;
        settings.setValue("charging_locations/loc"+QString::number(charging_num),str_name);
        charging_num++;
    }
    for(int i=0; i<pmap->resting_locations.size(); i++){
        str_name = pmap->resting_locations[i].name + QString().asprintf(",%f,%f,%f",pmap->resting_locations[i].point.x,pmap->resting_locations[i].point.y,pmap->resting_locations[i].angle)
                +","+pmap->resting_locations[i].call_id+":"+pmap->resting_locations[i].ling_id;
        settings.setValue("resting_locations/loc"+QString::number(resting_num),str_name);
        resting_num++;
    }
    for(int i=0; i<pmap->cleaning_locations.size(); i++){
        str_name = pmap->cleaning_locations[i].name + QString().asprintf(",%f,%f,%f",pmap->cleaning_locations[i].point.x,pmap->cleaning_locations[i].point.y,pmap->cleaning_locations[i].angle)
                +","+pmap->cleaning_locations[i].call_id+":"+pmap->cleaning_locations[i].ling_id;
        settings.setValue("cleaning_locations/loc"+QString::number(cleaning_num),str_name);
        cleaning_num++;
    }
    for(int i=0; i<pmap->init_locations.size(); i++){
        str_name = pmap->init_locations[i].name + QString().asprintf(",%f,%f,%f",pmap->init_locations[i].point.x,pmap->init_locations[i].point.y,pmap->init_locations[i].angle)
                +","+pmap->init_locations[i].call_id+":"+pmap->init_locations[i].ling_id;
        settings.setValue("init_locations/loc"+QString::number(init_num),str_name);
        init_num++;
    }

    for(int i=0; i<pmap->serving_locations.size(); i++){
        QString groupname = "serving_" + QString::number(pmap->serving_locations[i].group);
        str_name = pmap->serving_locations[i].name + QString().asprintf(",%f,%f,%f",pmap->serving_locations[i].point.x,pmap->serving_locations[i].point.y,pmap->serving_locations[i].angle)
                +","+pmap->serving_locations[i].call_id+":"+pmap->serving_locations[i].ling_id;
        settings.setValue(groupname+"/loc"+QString::number(group_num[pmap->serving_locations[i].group]),str_name);
        group_num[pmap->serving_locations[i].group]++;
    }

    settings.setValue("cleaning_locations/num",cleaning_num);
    settings.setValue("resting_locations/num",resting_num);
    settings.setValue("serving_locations/group",pmap->location_groups.size());
    settings.setValue("other_locations/num",other_num);
    settings.setValue("init_locations/num",init_num);
    settings.setValue("charging_locations/num",charging_num);

    for(int i=0; i<pmap->location_groups.size(); i++){
        settings.setValue("serving_"+QString::number(i)+"/name",pmap->location_groups[i]);
        settings.setValue("serving_"+QString::number(i)+"/num",getLocationGroupSize(i));
    }

    //slam_map_reload(filename, 1); //08.14
    if(reload){
        readSetting(filename);
        maph->initLocation();
    }
    pmap->annotation_edited = false;

    return true;
}

void Supervisor::saveTTSVoice(){
    qDebug() <<"saveTTSVoice" << tts->curVoice.mode;

    if(getSetting("setting","UI","voice_language") != tts->curVoice.language)
        setSetting("setting","UI/voice_language",tts->curVoice.language);

    if(getSetting("setting","UI","voice_name") != tts->curVoice.voice)
        setSetting("setting","UI/voice_name",tts->curVoice.voice);

    if(getSetting("setting","UI","voice_mode") != tts->curVoice.mode)
        setSetting("setting","UI/voice_mode",tts->curVoice.mode);

    if(getSetting("setting","UI","voice_speed") != QString::number(tts->curVoice.speed))
        setSetting("setting","UI/voice_speed",QString::number(tts->curVoice.speed));

    if(getSetting("setting","UI","voice_pitch") != QString::number(tts->curVoice.pitch))
        setSetting("setting","UI/voice_pitch",QString::number(tts->curVoice.pitch));

    if(getSetting("setting","UI","voice_alpha") != QString::number(tts->curVoice.alpha))
        setSetting("setting","UI/voice_alpha",QString::number(tts->curVoice.alpha));

    if(getSetting("setting","UI","voice_emotion") != QString::number(tts->curVoice.emotion))
        setSetting("setting","UI/voice_emotion",QString::number(tts->curVoice.emotion));

    if(getSetting("setting","UI","voice_emotion_strength") != QString::number(tts->curVoice.emotion_strength))
        setSetting("setting","UI/voice_emotion_strength",QString::number(tts->curVoice.emotion_strength));
}

void Supervisor::clearTTSVoice(int lan, int name){
    QDir path = QDir::homePath()+"/RB_MOBILE/voice";
    QStringList files = path.entryList();
    QString voice = tts->getVoiceName("tts",lan,name);
    plog->write("[SOUND] clearTTSVoice : "+QString::number(lan)+","+QString::number(name)+" -> "+voice);
    for(QString file : files){
        if(file.split("_")[0] == voice){
            qDebug() << "remove : " << file;
            plog->write("[SOUND] clearTTSVoice : remove file ("+file+")");
            QFile::remove(path.path()+"/"+file);
        }
    }
}

void Supervisor::setTTSMode(QString mode){
    plog->write("[SOUND] setTTSMode : "+mode);
    tts->curVoice.mode = mode;
    setTTSVoice(0,0);
    setTTSVoiceDetail(0,0,0);
//    saveTTSVoice();
}
void Supervisor::setTTSMentionBasic(){
    tts->setMentionBasic(tts->curVoice.language);
}
void Supervisor::setTTSVoice(int lan, int name){
    plog->write("[SETTING] setTTSVoice : "+tts->getVoiceLanguage(lan)+"("+tts->getVoiceName("tts",lan,name)+")");
    tts->setVoice(tts->getVoiceName("tts",lan,name),tts->getVoiceLanguage(lan));
    saveTTSVoice();
}
void Supervisor::setTTSVoiceDetail(int speed, int pitch, int alpha, int emotion, int emostren){
    tts->setVoiceDetail(speed,pitch,alpha,emotion,emostren);
    saveTTSVoice();
}


////*********************************************  SCHEDULER(SERVING) 관련   ***************************************************////
void Supervisor::setTray(int tray_num, int group, int table){
    if(tray_num > -1 && tray_num < probot->trays.size()){
        probot->trays[tray_num].empty = false;
        probot->trays[tray_num].location = getServingLocation(group,getServingName(group,table));
        plog->write("[COMMAND] setTray : "+QString::number(tray_num)+" , "+getServingName(group,table));
    }
}

void Supervisor::startServing(){
    if(isRobotReady()){
        QString tray_str = "";
        for(int i = 0; i<probot->trays.size(); i++){
            if(!probot->trays[i].empty){
                plog->write("[COMMAND] startServing "+probot->trays[i].location.name);
                stateMoving();
                return;
            }
        }
        plog->write("[COMMAND] startServing : tray empty");
    }else{
        plog->write("[COMMAND] startServing : State not ready " + QString::asprintf("(UIstate: %d, Local: %d, Motor1: %d, Motor2: %d)",ui_state, probot->localization_state, probot->motor[0].status, probot->motor[1].status));
    }
}

void Supervisor::startServing(int group, int table){
    if(isRobotReady()){
        LOCATION target;
        patrol_mode = PATROL_NONE;
        int target_num = -1;
        int count = 0;
        for(int i=0; i<pmap->serving_locations.size(); i++){
            if(pmap->serving_locations[i].group == group){
                if(count == table){
                    target = pmap->serving_locations[i];
                    target_num = count;
                    break;
                }else{
                    count++;
                }
            }

        }
        if(target_num > -1){
            plog->write("[COMMAND] startServing : "+target.name+QString().asprintf(" (group : %d, table : %d)", group, table));
            for(int i=0; i<probot->trays.size(); i++){
                probot->trays[i].empty = false;
                probot->trays[i].location = target;
            }
            stateMoving();
        }else{
            plog->write("[COMMAND] startServing : target not found "+QString().asprintf(" (group : %d, table : %d)", group, table));
        }
    }else{
        plog->write("[COMMAND] startServing : State not ready " + QString::asprintf("(UIstate: %d, Local: %d, Motor1: %d, Motor2: %d)",ui_state, probot->localization_state, probot->motor[0].status, probot->motor[1].status));
    }
}

void Supervisor::setPreset(int preset){
    plog->write("[COMMAND] SET PRESET : "+QString::number(preset));
    probot->cur_preset = preset;
    setSetting("update","DRIVING/cur_preset",QString::number(preset));
}

void Supervisor::confirmPickup(QString mode){
    if(ui_state == UI_STATE_PICKUP){
        if(pmap->call_queue.size() > 0 && probot->is_calling){
            plog->write("[COMMAND] confirmPickup : Call queue pop front "+pmap->call_queue[0]);
            pmap->call_queue.pop_front();
        }
        if(isRobotReady()){
            plog->write("[COMMAND] confirmPickup -> Moving");
            stateMoving();
            if(mode == "Cleaning"){
                probot->current_target = getCleaningLocation(0);
            }
        }else{
            plog->write("[COMMAND] confirmPickup : Robot Not Ready");
            QMetaObject::invokeMethod(mMain,"robotnotready");
        }
    }else{
        probot->current_target.name = "";
        plog->write("[COMMAND] confirmPickup : (ui_state "+QString::number(ui_state)+") -> noting to do");
    }
}
QList<int> Supervisor::getPickuptrays(){
    return probot->pickupTrays;
}





////*********************************************  ROBOT MOVE 관련   ***************************************************////
void Supervisor::movePause(){
    plog->write("[COMMAND] Move Pause");
    ipc->movePause();

}
void Supervisor::moveResume(){
    plog->write("[COMMAND] Move Resume");
    ipc->moveResume();
}
void Supervisor::moveStopFlag(){
    plog->write("[COMMAND] Move Stop Flag");
    patrol_mode = PATROL_NONE;
    probot->is_patrol = false;
    pmap->call_queue.clear();
    for(int i=0; i<probot->trays.size(); i++){
        probot->trays[i].empty = true;
    }
}

void Supervisor::moveStop(){
    plog->write("[COMMAND] Move Stop");
    stateInit();
    QMetaObject::invokeMethod(mMain, "movestopped");
}

void Supervisor::moveToCharge(){
    if(isRobotReady()){
        plog->write("[COMMAND] moveToCharge");
        stateMoving();
        probot->current_target = getChargingLocation(0);
    }else{
        QMetaObject::invokeMethod(mMain,"robotnotready");
        plog->write("[COMMAND] moveToCharge : State not ready " + QString::asprintf("(UIstate: %d, Local: %d, Motor1: %d, Motor2: %d)",ui_state, probot->localization_state, probot->motor[0].status, probot->motor[1].status));
    }
}
void Supervisor::moveToWait(){
    if(isRobotReady()){
        plog->write("[COMMAND] moveToWait");
        stateMoving();
        probot->current_target = getRestingLocation(0);
    }else{
        QMetaObject::invokeMethod(mMain,"robotnotready");
        plog->write("[COMMAND] moveToWait : State not ready " + QString::asprintf("(UIstate: %d, Local: %d, Motor1: %d, Motor2: %d)",ui_state, probot->localization_state, probot->motor[0].status, probot->motor[1].status));
    }
}
bool Supervisor::isFinalLocation(){
    if(probot->is_patrol){
        return false;
    }
    bool tray_occupied = false;
    for(int i=0; i<setting.tray_num; i++){
        //트레이 점유됨
        if(!probot->trays[i].empty){
            tray_occupied = true;
        }
    }

    if(tray_occupied){
        return false;
    }else{
        return true;
    }

}
void Supervisor::moveToCleaning(){
    if(isRobotReady()){
        plog->write("[COMMAND] moveToCleaning");
        stateMoving();
        probot->current_target = getCleaningLocation(0);
    }else{
        is_test_moving = false;
        QMetaObject::invokeMethod(mMain,"robotnotready");
        plog->write("[COMMAND] moveToCleaning : State not ready " + QString::asprintf("(UIstate: %d, Local: %d, Motor1: %d, Motor2: %d)",ui_state, probot->localization_state, probot->motor[0].status, probot->motor[1].status));
    }
}
QString Supervisor::getcurLoc(){
    return probot->curLocation.name;
}
int Supervisor::getMultiState(){
    static int previousState = -1;  // 이전 상태를 저장하는 정적 변수
    int state = probot->fms_connection_state;

    if (state != previousState) {  // 현재 상태와 이전 상태를 비교
        plog->write("[FMS Connection State] : " + QString::number(state));
        previousState = state;  // 이전 상태를 현재 상태로 업데이트
    }

    return state;
}


////*********************************************  ROBOT STATUS 관련   ***************************************************////
int Supervisor::getBattery(){
    return probot->battery_percent;
}
bool Supervisor::getMotorConnection(int id){
    return probot->motor[id].connection;
}
int Supervisor::getMotorStatus(int id){
    return probot->motor[id].status;
}
QString Supervisor::getMotorStatusStr(int id){
    QString str = "";
    if(probot->motor[id].connection == 0){
        str = "CON";
    }else{
        if(probot->motor[id].status == 0){
            str += "POW";
        }
        if(MOTOR_RUN(probot->motor[id].status) == 1)
            str += " - ";

        if(MOTOR_MOD_ERROR(probot->motor[id].status) == 1)
            str += "M";

        if(MOTOR_JAM_ERROR(probot->motor[id].status) == 1)
            str += " J";

        if(MOTOR_CUR_ERROR(probot->motor[id].status) == 1)
            str += " CR";

        if(MOTOR_BIG_ERROR(probot->motor[id].status) == 1)
            str += " B";

        if(MOTOR_INP_ERROR(probot->motor[id].status) == 1)
            str += " I";

        if(MOTOR_PS_ERROR(probot->motor[id].status) == 1)
            str += " P";

        if(MOTOR_COL_ERROR(probot->motor[id].status) == 1)
            str += " CL";
    }
    return str;
}
int Supervisor::getMotorTemperature(int id){
    return probot->motor[id].temperature;
}
int Supervisor::getMotorInsideTemperature(int id){
    return probot->motor[id].motor_temp;
}
int Supervisor::getMotorWarningTemperature(){
    return 55;
}
int Supervisor::getMotorCurrent(int id){
    return probot->motor[id].current;
}
int Supervisor::getPowerStatus(){
    return probot->status_power;
}
int Supervisor::getRemoteStatus(){
    return probot->status_remote;
}
int Supervisor::getChargeConnectStatus(){
    return probot->status_charge_connect;
}
int Supervisor::getChargeStatus(){
    return probot->status_charge;
}
int Supervisor::getEmoStatus(){
    return probot->status_emo;
}
int Supervisor::getLockStatus(){
    return probot->status_lock;
}
int Supervisor::getObsinPath(){
    return probot->obs_in_path_state;
}

void Supervisor::setMotorLock(bool onoff){
    if(ipc->getConnection()){
        if(onoff){
            plog->write("[COMMAND] SET MOTOR LOCK : ON");
            ipc->set_cmd(ROBOT_CMD_MOTOR_LOCK_ON,"ROBOT_CMD_MOTOR_LOCK_ON");
        }else{
            plog->write("[COMMAND] SET MOTOR LOCK : OFF");
            ipc->set_cmd(ROBOT_CMD_MOTOR_LOCK_OFF2,"ROBOT_CMD_MOTOR_LOCK_OFF2");
        }
    }
}

int Supervisor::getRobotcurPreset(){
    return probot->robot_preset;
}
float Supervisor::getBatteryIn(){
    return probot->battery_in;
}
float Supervisor::getBatteryOut(){
    return probot->battery_out;
}
float Supervisor::getBatteryCurrent(){
    return probot->battery_cur;
}
float Supervisor::getPower(){
    return probot->power;
}

float Supervisor::getPowerTotal(){
    return probot->total_power;
}
int Supervisor::getMotorState(){
    if(probot->motor[0].status == 1 && probot->motor[1].status == 1){
        return 1;
    }else{
        return 0;
    }
}
int Supervisor::getLocalizationState(){
    return probot->localization_state;
}
int Supervisor::getStateMoving(){
    return probot->running_state;
}

QString Supervisor::getStateMovingStr(){
    if(probot->running_state == 0){
        return tr("준비 안됨");
    }else if(probot->running_state == 1){
        return tr("준비됨");
    }else if(probot->running_state == 2){
        return tr("이동중");
    }else if(probot->running_state == 3){
        return tr("이동중 (장애물 감지)");
    }else if(probot->running_state == 4){
        return tr("이동중 (일시정지됨)");
    }else{
        return tr("알수 없음 ")+QString::number(probot->running_state);
    }
}
QString Supervisor::getRobotName(){
    if(is_debug){
        return robot.name + "_" + robot.name_debug;
    }else{
        return robot.name;
    }
}
float Supervisor::getlastRobotx(){
    POSE temp = setAxis(probot->lastPose);
    return temp.point.x;
}
float Supervisor::getlastRoboty(){
    POSE temp = setAxis(probot->lastPose);
    return temp.point.y;
}
float Supervisor::getlastRobotth(){
    POSE temp = setAxis(probot->lastPose);
    return temp.angle;
}
int Supervisor::getuistate(){
    return ui_state;
}
QString Supervisor::getMapname(){
    return pmap->map_name;
}
QString Supervisor::getMappath(){
    return pmap->map_path;
}
int Supervisor::getMapWidth(){
    return pmap->width;
}
int Supervisor::getMapHeight(){
    return pmap->height;
}
float Supervisor::getGridWidth(){
    return pmap->gridwidth;
}
QList<int> Supervisor::getOrigin(){
    QList<int> temp;
    temp.push_back(pmap->origin[0]);
    temp.push_back(pmap->origin[1]);
    return temp;
}

void Supervisor::moveToServingTest(int group, QString name){
    if(isRobotReady()){
        if(name.left(8) == "Charging" || name == tr("충전위치")){
            plog->write("[COMMAND] moveToServingTest : "+name);
            stateMoving();
            probot->current_target = getChargingLocation(0);
        }else if(name.left(7) == "Resting"|| name == tr("대기위치")){
            plog->write("[COMMAND] moveToServingTest : "+name);
            stateMoving();
            probot->current_target = getRestingLocation(0);
        }else if(name.left(8) == "Cleaning"|| name == tr("퇴식위치")){
            plog->write("[COMMAND] moveToServingTest : "+name);
            stateMoving();
            probot->current_target = getCleaningLocation(0);
        }else{
            LOCATION temp_loc = getServingLocation(group, name);
            if(temp_loc.name == ""){
                plog->write("[COMMAND] moveToServingTest (Not found) : "+name);
                QMetaObject::invokeMethod(mMain,"notfoundlocation");
            }else{
                probot->trays[0].empty = false;
                probot->trays[0].location = temp_loc;
                plog->write("[COMMAND] moveToServingTest : "+name);
                stateMoving();
            }
        }
    }else{
        plog->write("[COMMAND] moveToServingTest : Robot not ready "+name);
        QMetaObject::invokeMethod(mMain,"robotnotready");
    }
}
void Supervisor::startPatrol(int num){
    if(num > -1 && num < patrols.size()){
        if(isRobotReady()){
            plog->write("[COMMAND] startPatrol : "+patrols[num].name);
            patrol_mode = PATROL_NEW;
            current_patrol = patrols[num];
            stateMoving();
        }else{
            QMetaObject::invokeMethod(mMain,"robotnotready");
            plog->write("[COMMAND] startPatrol : Robot Not Ready");
        }
    }else{
        plog->write("[COMMAND] startPatrol : patrol not found "+QString::number(num));
        QMetaObject::invokeMethod(mMain,"notfoundpatrol");
    }
}

//// *********************************** SLOTS *********************************** ////
void Supervisor::path_changed(){
    maph->setMap();
}
void Supervisor::camera_update(){
    QMetaObject::invokeMethod(mMain, "updatecamera");
}
void Supervisor::mapping_update(){
    maph->setMap();
}

void Supervisor::checkShellFiles(){//need check
//파일확인!
    QString file_path;
    QString path = QDir::homePath()+"/RB_MOBILE/log/ui_log";
    QDir directory(path);
    if(!directory.exists()){
        directory.mkpath(".");
        plog->write("[SUPERVISOR] ui_log directory not found. make new");
    }

    //auto_test.sh
    file_path = QDir::homePath() + "/RB_MOBILE/sh/startslam.sh";
    if(!QFile::exists(file_path)){
        plog->write("[SUPERVISOR] startslam.sh not found. make new");
        makeStartShell();
    }

//    file_path = QDir::homePath() + "/RB_MOBILE/sh/startextproc.sh";
//    if(!QFile::exists(file_path)){
//        plog->write("[SUPERVISOR] startextproc.sh not found. make new");
//        makeExtProcessShell();
//    }

    //kill_slam.sh
    file_path = QDir::homePath() + "/RB_MOBILE/sh/restartslam.sh";
    if(!QFile::exists(file_path)){
        plog->write("[SUPERVISOR] restartslam.sh not found. make new");
        makeKillShell();
    }

    //auto_kill.sh
    file_path = QDir::homePath() + "/RB_MOBILE/sh/killall.sh";
    if(!QFile::exists(file_path)){
        plog->write("[SUPERVISOR] killall.sh not found. make new");
        makeAllKillShell();
    }

    //auto_reset.sh
    file_path = QDir::homePath() + "/RB_MOBILE/sh/restartall.sh";
    if(!QFile::exists(file_path)){
        plog->write("[SUPERVISOR] restartall.sh not found. make new");
        makeKillSlam();
    }
}
void Supervisor::makeKillShell(){//need check
    //Make kill_slam.sh
    QString file_name = QDir::homePath() + "/RB_MOBILE/sh/restartslam.sh";
    QFile file(file_name);
    if(file.open(QIODevice::ReadWrite)){
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
    process.waitForReadyRead(200);
}
void Supervisor::checkUpdate(){//need check
//    server->checkUpdate();
}
void Supervisor::setlanguage(QString lan){
    QString path = "";
    if(lan == "KR"){
    }else if(lan=="US" || lan=="english"){
        //path = QDir::homePath() + "/RB_MOBILE/config/locale/lang_en.qm";
        path = QDir::homePath() + "/RB_MOBILE/release/lang_eddn.qm";
    }

    app->removeTranslator(translator);

    if(translator->load(path)){
        plog->write("[COMMAND] setlanguage : " + lan + " SUCCESS ("+path+")");
        app->installTranslator(translator);
    }else{
        plog->write("[COMMAND] setlanguage : " + lan + " FAILED ("+path+")");
    }
}
bool Supervisor::checkNewUpdateProgram(){//need check
    if(server->update_list.size() > 0){
        return true;
    }else{
        return false;
    }
//    return server->new_update;
}
void Supervisor::makeKillSlam(){//need check
    //Make kill_slam.sh
    QString file_name = QDir::homePath() + "/RB_MOBILE/sh/restartslam.sh";
    QFile file(file_name);
    if(file.open(QIODevice::ReadWrite)){
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
    process.setWorkingDirectory(QDir::homePath()+"/RB_MOBILE/sh");
    process.start("chmod +x restartslam.sh",QStringList(),QProcess::ReadWrite);
    process.waitForReadyRead(200);

}

void Supervisor::makeStartShell(){//need check
    //Make kill_slam.sh
    QString file_name = QDir::homePath() + "/RB_MOBILE/sh/startslam.sh";
    QFile file(file_name);

    if(file.open(QIODevice::ReadWrite)){
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
    process.waitForReadyRead(200);

}
void Supervisor::makeAllKillShell(){//need check
    //Make kill_slam.sh
    QString file_name = QDir::homePath() + "/killall.sh";
    QFile file(file_name);
    if(file.open(QIODevice::ReadWrite)){
        QTextStream stream(&file);
        stream << "#!/bin/bash" << "\n" << "\n";


        stream << "pid=`ps -ef | grep \"startslam.sh\" | grep -v 'grep' | awk '{print $2}'`"<<"\n";
        stream << "if [ -z $pid ]" << "\n";
        stream << "then" << "\n";
        stream << "     echo \"startslam.sh is not running\"" << "\n";
        stream << "else" << "\n";
        stream << "     kill -9 $pid" << "\n";
        stream << "fi" << "\n";

//        stream << "pid=`ps -ef | grep \"startextproc.sh\" | grep -v 'grep' | awk '{print $2}'`"<<"\n";
//        stream << "if [ -z $pid ]" << "\n";
//        stream << "then" << "\n";
//        stream << "     echo \"startextproc.sh is not running\"" << "\n";
//        stream << "else" << "\n";
//        stream << "     kill -9 $pid" << "\n";
//        stream << "fi" << "\n";


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
    process.waitForReadyRead(200);
}

//// *********************************** TIMER *********************************** ////
void Supervisor::onTimer(){
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
    if(mMain == nullptr && object != nullptr){
        setObject(object);
        setWindow(qobject_cast<QQuickWindow*>(object));
    }

    //
    if(timer_cnt++ > 30){
        timer_cnt = 0;
        checker->getCurrentInterface();
    }

    if(start_clear){
        start_clear = false;
        timer2 = new QTimer();
        connect(timer2, SIGNAL(timeout()),this,SLOT(clear_all()));
        timer2->start(500);
    }

    //************************** WiFi *********************************//

    switch(ui_state){
    case UI_STATE_NONE:{
        //State : None
        //Robot 연결 안됨, 초기화 시작 전(프로그램 실행직후)
        if(ipc->getConnection()){
            ui_state = UI_STATE_INITAILIZING;
            flag_annot_localization = false;
            plog->write("[STATE] None : Connection check done -> Initailizing");
        }else{
            clearStatus();
            if(curPage != "page_init" && !debug_mode){
                plog->write("[STATE] None : Disconnected -> UI Init");
                QMetaObject::invokeMethod(mMain, "need_init");
            }
        }
        cmd_accept = false;
        break;
    }
    case UI_STATE_INITAILIZING:{
        if(debug_mode){

        }else if(probot->status_charge_connect == 1){
            plog->write("[STATE] Initializing : Charging Connected -> Charging");
            ui_state = UI_STATE_CHARGING;
        }else if(probot->localization_confirm){
            if(getMotorState() == READY){
                plog->write("[STATE] Initializing : Localization Good, Motor state Good -> Resting");
                ui_state = UI_STATE_RESTING;
                flag_annot_localization = false;
            }else if(probot->status_lock==0){

            }else if(probot->localization_state != 2){
                probot->localization_confirm = false;
            }else{
                if(curPage != "page_init" && curPage != "page_annotation"){
                    plog->write("[STATE] Initializing : State not ready (Motor: "+ QString::number(getMotorState())+ ", LConfirm: " + QString::number(probot->localization_confirm) + ", LState: " + QString::number(probot->localization_state)+") -> UI Init");
                    QMetaObject::invokeMethod(mMain, "need_init");
                }else if(curPage == "page_annotation"){
                    if(!flag_annot_localization){
                        plog->write("[STATE] Initializing : State not ready (Motor: "+ QString::number(getMotorState())+ ", LConfirm: " + QString::number(probot->localization_confirm) + ", LState: " + QString::number(probot->localization_state)+") -> UI Init");
                        QMetaObject::invokeMethod(mMain, "need_init");
                        flag_annot_localization = true;
                    }
                }
            }
        }else{
            if(curPage != "page_init" && curPage != "page_annotation"){
                plog->write("[STATE] Initializing : State not ready (Motor: "+ QString::number(getMotorState())+ ", LConfirm: " + QString::number(probot->localization_confirm) + ", LState: " + QString::number(probot->localization_state)+") -> UI Init");
                QMetaObject::invokeMethod(mMain, "need_init");
            }else if(curPage == "page_annotation"){
                if(!flag_annot_localization){
                    plog->write("[STATE] Initializing : State not ready (Motor: "+ QString::number(getMotorState())+ ", LConfirm: " + QString::number(probot->localization_confirm) + ", LState: " + QString::number(probot->localization_state)+") -> UI Init");
                    QMetaObject::invokeMethod(mMain, "need_init");
                    flag_annot_localization = true;
                }
            }
        }
        break;
    }
    case UI_STATE_RESTING:{
        static int count_battery = 0;
        need_init = false;
        if(probot->battery_percent < 20){
            if(count_battery++ > 600000/MAIN_THREAD){//10분
                playVoice("error_battery");
                count_battery = 0;
            }
        }else{
            count_battery = 0;
        }

        cmd_accept = false;
        if(probot->status_charge_connect == 1){
            plog->write("[STATE] Resting : Charging Connected -> Charging");
            ui_state = UI_STATE_CHARGING;
        }else if(probot->motor[0].status > 1 || probot->motor[1].status > 1){
            plog->write("[STATE] Resting : State Failed "+QString().asprintf("(Motor1: %d, Motor2: %d) -> Kill Slam",probot->motor[0].status,probot->motor[1].status));
            killSLAM();
        }else if(probot->status_emo == 1){
        }else if(pmap->call_queue.size() > 0){
            plog->write("[STATE] Resting : Calling Detected "+QString::number(pmap->call_queue.size())+" -> Moving");
            stateMoving();
        }else if(getSetting("setting","SERVER","use_server_call") == "true"){//not used
            if(probot->server_call_size > 0){
                probot->server_call_size = 0;
                //콜 번호가 유효한 지 체크
            }else if(probot->server_call_size == -1){
                probot->server_call_size = 0;
            }
        }
        break;
    }
    case UI_STATE_CHARGING:{
        patrol_mode = PATROL_NONE;

        if(probot->status_charge_connect == 0){
            plog->write("[STATE] Charging : Charge Connect = 0 -> None");
            //stateInit();
            //QMetaObject::invokeMethod(mMain, "need_init");
            QMetaObject::invokeMethod(mMain, "charging");
            break;
        }else if(curPage != "page_charge" && !debug_mode){
            plog->write("[STATE] Charging -> UI Charging");
            QMetaObject::invokeMethod(mMain, "charging");
        }
        break;
    }
    case UI_STATE_MOVING:{
        static int timer_cnt2 = 0;
        if(probot->ui_fail_state == 1){
            //local fail, no path, charging, motor error, motor connection
            if(!getMotorConnection(0) || !getMotorConnection(1)){
                plog->write("[IPC] UI Fail State -> Motor Connection Error "+QString::asprintf("(%d, %d)",getMotorConnection(0),getMotorConnection(1)));
            }else if(getMotorState()==0){
                plog->write("[IPC] UI Fail State -> Motor Error "+QString::asprintf("(%d, %d)",probot->motor[0].status,probot->motor[1].status));
            }else if(getLocalizationState()!=LOCAL_READY){
                plog->write("[IPC] UI Fail State -> Localization Not ready"+QString::asprintf("(%d)",probot->localization_state));
            }else if(getChargeConnectStatus()){
                plog->write("[IPC] UI Fail State -> Charging"+QString::asprintf("(%d, %d)",probot->status_charge,probot->status_charge_connect));
            }else{
                plog->write("[IPC] UI Fail State -> No Path ?");
            }
            plog->write("[STATE] Moving : UI Fail State -> Kill Slam");
            killSLAM();
        }else if(probot->status_lock && getMotorState() == 0){//need check
            plog->write(QString::number(probot->status_emo)+QString::number(probot->status_lock)+QString::number(probot->status_remote)+QString::number(probot->status_power)+QString::number(probot->motor[0].status)+QString::number(probot->motor[1].status)+QString::number(probot->battery_in)+QString::number(probot->battery_out));
            plog->write("[STATE] Moving : MOTOR NOT READY -> Movefail");
            QMetaObject::invokeMethod(mMain, "movefail");
            ui_state = UI_STATE_MOVEFAIL;
        }else{
            if(getSetting("setting","USE_UI","use_current_pause")=="true"){
                float current_threshold = getSetting("update","DRIVING","pause_motor_current").toFloat();
                int check_count = getSetting("update","DRIVING","pause_current_ms").toInt()/MAIN_THREAD;
                if(probot->motor[0].current > current_threshold || probot->motor[1].current > current_threshold){
                    if(current_cnt++ > check_count){
                        //MOTOR THRESHOLD IN. PAUSED!
                        if(probot->running_state != ROBOT_MOVING_PAUSED){
                            plog->write("[STATE] Moving : Auto Paused. Motor Current Over "+QString().asprintf("(0 : %f, 1 : %f, limit: %f)",probot->motor[0].current,probot->motor[1].current,current_threshold));
                            ipc->movePause();
                            is_test_moving = false;
                        }
                    }
                }else{
                    current_cnt = 0;
                }
            }

            if(probot->running_state == ROBOT_MOVING_READY){
                if(cmd_accept){
                    if(probot->current_target.name == "Charging0"){
                        if(probot->is_patrol){
                            plog->write("[STATE] Moving : Arrived Location (Patrol Mode) "+probot->current_target.name);

                            //Play Voice
                            if(current_patrol.voice_mode != "none"){
                                playVoice(current_patrol.voice_file, current_patrol.voice_name, current_patrol.voice_mode, current_patrol.voice_language, current_patrol.voice_volume);
                            }
                            lingbell_count = 0;
                            ui_state = UI_STATE_PICKUP;
                        }else if(probot->is_calling){
                            if(pmap->call_queue.size() > 0){
                                plog->write("[STATE] Moving : Arrived Location (Calling Mode) "+probot->current_target.name+" -> Charging");
                                pmap->call_queue.pop_front();
                            }else{
                                probot->is_calling = false;
                            }
                            //Ling bell
                            if(getSetting("setting","CALL","use_lingbell") == "true" && probot->current_target.ling_id != ""){
                                plog->write("[STATE] Send Lingbell : "+probot->current_target.ling_id);
                                call->sendCall(probot->current_target.ling_id);
                            }
                            ui_state = UI_STATE_CHARGING;
                        }else{
                            plog->write("[STATE] Moving : Arrived Location "+probot->current_target.name+" -> Charging");
                            //Ling bell
                            if(getSetting("setting","CALL","use_lingbell") == "true" && probot->current_target.ling_id != ""){
                                plog->write("[STATE] Send Lingbell : "+probot->current_target.ling_id);
                                call->sendCall(probot->current_target.ling_id);
                            }
                            ui_state = UI_STATE_CHARGING;
                        }
                    }else if(probot->current_target.name == "Resting0"){
                        probot->call_moving_count = 0;
                        if(probot->is_patrol){
                            plog->write("[STATE] Moving : Arrived Location (Patrol Mode) "+probot->current_target.name);

                            //Play Voice
                            if(current_patrol.voice_mode != "none"){//basic
                                playVoice(current_patrol.voice_file, current_patrol.voice_name, current_patrol.voice_mode, current_patrol.voice_language, current_patrol.voice_volume);
                            }
                            lingbell_count = 0;
                            ui_state = UI_STATE_PICKUP;

                        }else if(probot->is_calling){
                            if(pmap->call_queue.size() > 0){
                                if(pmap->call_queue[0].left(7) == "Resting"){
                                    plog->write("[STATE] Moving : Arrived Location (Calling Mode) "+probot->current_target.name);
                                    pmap->call_queue.pop_front();
                                }else{
                                    plog->write("[STATE] Moving : Arrived Location (Calling Mode) -> Max Calling Resting (Next : "+pmap->call_queue[0]+", CallCount : "+QString::number(probot->call_moving_count)+", MaxCall : "+QString::number(probot->max_moving_count)+")");
                                }
                            }else{
                                probot->is_calling = false;
                                plog->write("[STATE] Moving : Arrived Location (Calling Mode?) "+probot->current_target.name);
                            }
                            //Ling bell
                            if(getSetting("setting","CALL","use_lingbell") == "true" && probot->current_target.ling_id != ""){
                                plog->write("[STATE] Send Lingbell : "+probot->current_target.ling_id);
                                call->sendCall(probot->current_target.ling_id);
                            }
                            QMetaObject::invokeMethod(mMain, "waitkitchen");
                            ui_state = UI_STATE_CLEANING;
                        }else{
                            plog->write("[STATE] Moving : Arrived Location "+probot->current_target.name);
                            //Ling bell
                            if(getSetting("setting","CALL","use_lingbell") == "true" && probot->current_target.ling_id != ""){
                                plog->write("[STATE] Send Lingbell : "+probot->current_target.ling_id);
                                call->sendCall(probot->current_target.ling_id);
                            }
                            QMetaObject::invokeMethod(mMain, "waitkitchen");
                            ui_state = UI_STATE_INITAILIZING;
                        }

                    }else if(probot->current_target.name == "Cleaning0"){
                        probot->call_moving_count = 0;
                        if(probot->is_patrol){
                            plog->write("[STATE] Moving : Arrived Location (Patrol Mode) "+probot->current_target.name);

                            //Play Voice
                            if(current_patrol.voice_mode != "none"){//basic
                                playVoice(current_patrol.voice_file, current_patrol.voice_name, current_patrol.voice_mode, current_patrol.voice_language, current_patrol.voice_volume);
                            }
                            lingbell_count = 0;
                            ui_state = UI_STATE_PICKUP;
                        }else if(probot->is_calling){
                            if(pmap->call_queue.size() > 0){
                                if(pmap->call_queue[0].left(8) == "Cleaning"){
                                    plog->write("[STATE] Moving : Arrived Location (Calling Mode) "+probot->current_target.name);
                                    pmap->call_queue.pop_front();
                                }else{
                                    plog->write("[STATE] Moving : Arrived Location (Calling Mode) -> Max Calling Cleaning (Next : "+pmap->call_queue[0]+", CallCount : "+QString::number(probot->call_moving_count)+", MaxCall : "+QString::number(probot->max_moving_count)+")");
                                }
                            }else{
                                probot->is_calling = false;
                                plog->write("[STATE] Moving : Arrived Location (Calling Mode?) "+probot->current_target.name);
                            }
                            //Ling bell
                            if(getSetting("setting","CALL","use_lingbell") == "true" && probot->current_target.ling_id != ""){
                                plog->write("[STATE] Send Lingbell : "+probot->current_target.ling_id);
                                call->sendCall(probot->current_target.ling_id);
                            }
                            QMetaObject::invokeMethod(mMain, "clearkitchen");
                            ui_state = UI_STATE_CLEANING;
                        }else{
                            //Ling bell
                            if(getSetting("setting","CALL","use_lingbell") == "true" && probot->current_target.ling_id != ""){
                                plog->write("[STATE] Send Lingbell : "+probot->current_target.ling_id);
                                call->sendCall(probot->current_target.ling_id);
                            }
                            plog->write("[STATE] Moving : Arrived Location "+probot->current_target.name);
                            QMetaObject::invokeMethod(mMain, "clearkitchen");
                            ui_state = UI_STATE_CLEANING;
                        }
                    }else{
                        if(probot->is_patrol){
                            plog->write("[STATE] Moving : Arrived Location (Patrol Mode) "+probot->current_target.name);

                            //Play Voice
                            if(current_patrol.voice_mode != "none"){//basic
                                playVoice(current_patrol.voice_file, current_patrol.voice_name, current_patrol.voice_mode, current_patrol.voice_language, current_patrol.voice_volume);
                            }
                            lingbell_count = 0;
                            ui_state = UI_STATE_PICKUP;
                        }else if(probot->is_calling){
                            plog->write("[STATE] Moving : Arrived Location (Calling Mode) "+probot->current_target.name + " -> Pickup");
                            probot->call_moving_count++;
                            lingbell_count = 0;
                            ui_state = UI_STATE_PICKUP;
                        }else{
                            LOCATION curLoc;
                            bool match = false;
                            //트레이 클리어
                            probot->pickupTrays.clear();
                            for(int i=0; i<setting.tray_num; i++){
                                //트레이 점유됨
                                if(!probot->trays[i].empty){
                                    if(!match){
                                        match = true;
                                        curLoc = probot->trays[i].location;
                                    }
                                    if(isSameLocation(probot->trays[i].location,curLoc)){
                                        plog->write("[STATE] Tray Reset : "+QString::number(i)+", " + probot->trays[i].location.name);
                                        probot->trays[i].empty = true;
                                        probot->pickupTrays.push_back(i+1);
                                    }
                                }else{
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
                }else{
                    if(probot->current_target.name == ""){
                        LOCATION cur_target;
                        probot->is_patrol = false;
                        probot->is_calling = false;

                        //1. 서빙 포인트 있는지 체크
                        int tray_num = -1;
                        for(int i=0; i<setting.tray_num; i++){
                            if(!probot->trays[i].empty){
                                tray_num = i;
                                break;
                            }
                        }
                        if(tray_num > -1){
                            //서빙 포인트 세팅
                            cur_target = probot->trays[tray_num].location;
                            plog->write("[STATE] Moving : New Target (Serving) -> "+cur_target.name+" ( tray num : "+QString::number(tray_num)+" , tray location )");
                        }else{
                            //최대 이동 횟수 초과 시 -> 대기장소로 이동
                            if(probot->call_moving_count + 1 > probot->max_moving_count){
                                probot->is_calling = true;
                                plog->write("[STATE] Moving : Call Move Count is Max "+QString::number(probot->call_moving_count)+","+QString::number(probot->max_moving_count));
                            }else{
                                //2. 들어온 콜 위치가 있는지 체크
                                for(QString call:pmap->call_queue){
                                    LOCATION temp_loc;

                                    if(call == "Charging0"){
                                        temp_loc = getChargingLocation(0);
                                    }else if(call == "Resting0"){
                                        temp_loc = getRestingLocation(0);
                                    }else if(call == "Cleaning0"){
                                        temp_loc = getCleaningLocation(0);
                                    }else{
                                        temp_loc = getServingLocation(call);
                                    }
                                    if(temp_loc.name != ""){
                                        cur_target = temp_loc;
                                        plog->write("[STATE] Moving : New Target (Calling) -> "+temp_loc.name+" ( call id : "+temp_loc.call_id+" )");
                                        probot->is_calling = true;
                                        break;
                                    }else{
                                        plog->write("[STATE] Moving : New Call but ID Wrong ("+pmap->call_queue[0]+")");
                                        pmap->call_queue.pop_front();
                                    }
                                }

                                if(cur_target.name == ""){
                                    if(getSetting("setting","SERVER","use_server_call") == "true"){

                                    }else{
                                        //3. PATROLLING
                                        if(patrol_mode == PATROL_NEW){
                                            if(current_patrol.location.size()>1){
                                                if(current_patrol.type == "random"){
                                                    //패트롤 위치 랜덤하게 지정
                                                    int temp = QRandomGenerator::global()->bounded(0,1000);

                                                    while(patrol_num == temp%(current_patrol.location.size())){
                                                        temp = QRandomGenerator::global()->bounded(0,1000);
                                                    }

                                                    patrol_num = temp%(current_patrol.location.size());
                                                    cur_target = current_patrol.location[patrol_num];
                                                    probot->is_patrol = true;
                                                    plog->write("[STATE] Moving : New Target (Patrol Random) -> "+cur_target.group_name+", "+cur_target.name);
                                                }else{
                                                    if(++patrol_num >= current_patrol.location.size())
                                                        patrol_num = 0;

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
                        if(cur_target.name == ""){
                            // if(probot->is_cleaning){
                            //     //세팅 되지 않음 -> 고 홈
                            //     plog->write("[STATE] Moving : No Target -> Back to Cleaning0");
                            //     probot->call_moving_count = 0;
                            //     cur_target = getLocation(0,"Cleaning0");
                            //     if(cur_target.name == ""){
                            //         LOCATION temp_cleaning = getLocation(0,"Resting0");
                            //         temp_cleaning.name = "Cleaning0";
                            //         temp_cleaning.type = "Cleaning";
                            //         temp_cleaning.group_name = "Cleaning";
                            //         cur_target = temp_cleaning;
                            //     }
                            // }else{
                                //세팅 되지 않음 -> 고 홈
                                plog->write("[STATE] Moving : No Target -> Back to Resting0");
                                probot->call_moving_count = 0;
                                cur_target = getRestingLocation(0);
                            // }
                        }

                        bool match = false;
                        //지정된 위치 실재하는 지 확인
                        for(int i=0; i<pmap->serving_locations.size(); i++){
                            if(pmap->serving_locations[i].group == cur_target.group){
                                if(pmap->serving_locations[i].name == cur_target.name){
                                    match = true;
                                    break;
                                }
                            }
                        }
                        if(cur_target.name == "Charging0" && pmap->charging_locations.size() > 0){
                            match = true;
                        }
                        if(cur_target.name == "Resting0" && pmap->resting_locations.size() > 0){
                            match = true;
                        }
                        if(cur_target.name == "Cleaning0" && pmap->cleaning_locations.size() > 0){
                            match = true;
                        }

                        if(match){
                            probot->current_target = cur_target;
                        }else{
                            plog->write("[STATE] Moving : Target not found -> "+cur_target.name+", "+QString::number(cur_target.group));
                            QMetaObject::invokeMethod(mMain, "nolocation");
                            ui_state = UI_STATE_RESTING;
                            break;
                        }
                    }else{
                        if(timer_cnt2%5==0){
                            plog->write("[DEBUG] Moving : "+QString::number(timer_cnt2)+", "+QString::number(count_moveto));
                            if(!probot->is_patrol && count_moveto++ > 5){//need check
                                plog->write("[STATE] Moving : Robot not moving "+probot->current_target.name + " (");
                                ipc->moveStop();
                                QMetaObject::invokeMethod(mMain, "movefail");
                                ui_state = UI_STATE_MOVEFAIL;
                            }else{
                                int preset = probot->cur_preset;

                                if(curPage == "page_annotation"){
                                    plog->write("[STATE] Moving : move to (test)"+probot->current_target.name+", preset "+QString::number(preset));
                                    ipc->moveToLocationTest(probot->current_target,preset);
                                }else{
                                    if(probot->current_target.name.left(7) == "Resting" || probot->current_target.name.left(8) == "Cleaning"){
                                        if(probot->comeback_preset != 0){
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
            }else if(probot->running_state == ROBOT_MOVING_MOVING){
                // moving
                if(!cmd_accept){
                    cmd_accept = true;
                    count_moveto = 0;
                    if(probot->is_calling){
                        plog->write("[STATE] Moving : Move Start (Calling)");
                    }else{
                        if(patrol_mode != PATROL_NONE){
                            plog->write("[STATE] Moving : Move Start (Patrol)");
                        }else{
                            plog->write("[STATE] Moving : Move Start (Serving)");
                        }
                    }
                    QMetaObject::invokeMethod(mMain, "movestart");
                }
            }else if(probot->running_state == ROBOT_MOVING_NOT_READY){
                plog->write("[STATE] Moving : Running state not ready -> Movefail");
                QMetaObject::invokeMethod(mMain, "movefail");
                ui_state = UI_STATE_MOVEFAIL;
            }else{
                if(!flag_movewait){
                    if(probot->running_state == ROBOT_MOVING_WAIT){
                        plog->write("[STATE] Moving : MOVE WAIT");
                        QMetaObject::invokeMethod(mMain, "movewait");
                        count_movewait = 0;
                        flag_movewait = true;
                    }else if(probot->obs_in_path_state != 0 && probot->running_state == ROBOT_MOVING_MOVING){
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
    case UI_STATE_CLEANING:{
        probot->call_moving_count = 0;
        if(getSetting("setting","USE_UI","use_calling_notice") != "true"){
            if(probot->current_target.name != "Cleaning0")
                ui_state = UI_STATE_INITAILIZING;
        }
        break;
    }
    case UI_STATE_PICKUP:{
        if(probot->ui_fail_state == 1){
            //local fail, no path, charging, motor error, motor connection
            if(!getMotorConnection(0) || !getMotorConnection(1)){
                plog->write("[IPC] UI Fail State -> Motor Connection Error "+QString::asprintf("(%d, %d)",getMotorConnection(0),getMotorConnection(1)));
            }else if(getMotorState()==0){
                plog->write("[IPC] UI Fail State -> Motor Error "+QString::asprintf("(%d, %d)",probot->motor[0].status,probot->motor[1].status));
            }else if(getLocalizationState()!=LOCAL_READY){
                plog->write("[IPC] UI Fail State -> Localization Not ready"+QString::asprintf("(%d)",probot->localization_state));
            }else if(getChargeConnectStatus()){
                plog->write("[IPC] UI Fail State -> Charging"+QString::asprintf("(%d, %d)",probot->status_charge,probot->status_charge_connect));
            }else{
                plog->write("[IPC] UI Fail State -> No Path ?");
            }
            plog->write("[STATE] Pickup : UI Fail State -> Kill Slam");
            killSLAM();
        }else if(probot->status_lock && getMotorState() == 0){
            plog->write(QString::number(probot->status_emo)+QString::number(probot->status_lock)+QString::number(probot->status_remote)+QString::number(probot->status_power)+QString::number(probot->motor[0].status)+QString::number(probot->motor[1].status)+QString::number(probot->battery_in)+QString::number(probot->battery_out));
            plog->write("[STATE] Pickup : MOTOR NOT READY -> Movefail");
            QMetaObject::invokeMethod(mMain, "movefail");
            ui_state = UI_STATE_MOVEFAIL;
        }else if(probot->running_state == ROBOT_MOVING_PAUSED){
            plog->write("[STATE] Pickup : Robot paused -> RESUME");
            ipc->moveResume();
        }

        //Call 강제귀환
        for(int i=0; i<pmap->call_queue.size(); i++){
            if(pmap->call_queue[i].left(7) == "Resting" && getSetting("setting","CALL","force_resting") == "true"){
                plog->write("[STATE] Pickup : Force Calling (Resting) -> Moving");
                QString temp = pmap->call_queue[i];
                pmap->call_queue.clear();
                pmap->call_queue.append(temp);
                stateMoving();
                break;
            }else if(pmap->call_queue[i].left(8) == "Cleaning" && getSetting("setting","CALL","force_cleaning") == "true"){
                plog->write("[STATE] Pickup : Force Calling (Cleaning) -> Moving");
                QString temp = pmap->call_queue[i];
                pmap->call_queue.clear();
                pmap->call_queue.append(temp);
                stateMoving();
                break;
            }
        }

        //Ling bell
        if(!probot->is_patrol){
            if(getSetting("setting","CALL","use_lingbell") == "true"){
                if(lingbell_count == 0){
                    plog->write("[STATE] Send Lingbell : "+probot->current_target.ling_id);
                    call->sendCall(probot->current_target.ling_id);
                    lingbell_count = 1;
                }
                if(getSetting("setting","CALL","use_lingbell_repeat") == "true"){
                    if(lingbell_count++ > getSetting("setting","CALL","lingbell_time").toInt()*1000/MAIN_THREAD){
                        plog->write("[STATE] Send Lingbell : "+probot->current_target.ling_id);
                        call->sendCall(probot->current_target.ling_id);
                        lingbell_count = 1;
                    }
                }else{
                }
            }
        }

        if(patrol_mode != PATROL_NONE){
            if(probot->current_target.type == "Serving"){
                if(current_patrol.arrive_page.mode == "calling" || current_patrol.arrive_page.mode == "pickup"){
                    if(patrol_wait_count == 0){
                        plog->write("[STATE] Pickup -> UI Pickup");
                        QMetaObject::invokeMethod(mMain, "showpickup");
                    }
                    if(current_patrol.pass_time == 0){
                        //0이면 auto pass 안함
                        patrol_wait_count++;
                    }else{
                        if(patrol_wait_count++ < current_patrol.pass_time*1000/MAIN_THREAD){
                            break;
                        }else{
                            plog->write("[STATE] Pickup -> AUTO PASS");
                            stateMoving();
                        }

                    }
                }else{
                    if(patrol_wait_count++ < current_patrol.wait_time*1000/MAIN_THREAD){
                        break;
                    }else{
                        plog->write("[STATE] Pickup -> AUTO PASS");
                        stateMoving();
                    }
                }
            }else{
                if(patrol_wait_count++ < current_patrol.wait_time*1000/MAIN_THREAD){
                    break;
                }else{
                    stateMoving();
                    plog->write("[STATE] Pickup -> AUTO PASS");
                }
            }

        }else{
            if(curPage != "page_pickup_calling" && curPage != "page_pickup" && !debug_mode){
                plog->write("[STATE] Pickup -> UI Pickup");
                QMetaObject::invokeMethod(mMain, "showpickup");
            }
        }
        break;
    }
    case UI_STATE_MOVEFAIL:{
        if(isRobotReady(false)){
            plog->write("[STATE] Movefail : Wake Up Auto -> None");
            QMetaObject::invokeMethod(mMain, "movefail_wake");
            stateInit();
        }else{
            if(probot->localization_state != LOCAL_READY && prev_local_state != probot->localization_state){
                QMetaObject::invokeMethod(mMain, "movefail");
            }else if(probot->motor[0].status != 1 && prev_motor_1_state != probot->motor[0].status){
                QMetaObject::invokeMethod(mMain, "movefail");
            }else if(probot->motor[1].status != 1 && prev_motor_2_state != probot->motor[1].status){
                QMetaObject::invokeMethod(mMain, "movefail");
            }else if(probot->status_charge_connect == 1 && prev_charge_state != probot->status_charge_connect){
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
    if(!ipc->getConnection()){
        //Clear Status
        if(ui_state != UI_STATE_NONE){
            plog->write("[STATE] "+curUiState()+" : SLAMNAV Disconnected -> None");
            QMetaObject::invokeMethod(mMain, "disconnected");
//            debug_mode = false;
            stateInit();
        }
    }

    if(probot->localization_state != LOCAL_READY){
        if(probot->localization_confirm){
            plog->write("[STATE] "+curUiState()+" : Localization State is "+QString::number(probot->localization_state)+" -> Localization Confirm false");
            probot->localization_confirm = false;
            if(!debug_mode){
                stateInit();
            }
        }
    }
    if(!debug_mode && (probot->motor[0].status>1 || probot->motor[1].status>1)){
        if(ui_state == UI_STATE_NONE || ui_state == UI_STATE_INITAILIZING){
        }else{
            plog->write("[STATE] "+curUiState()+" : Motor State is "+QString::number(probot->motor[0].status)+","+QString::number(probot->motor[1].status)+" -> Init");
            stateInit();
        }
    }

    if(flag_movewait){
        if(count_movewait++ > 15000/MAIN_THREAD){//15초
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

QString Supervisor::curUiState(){
    if(ui_state == UI_STATE_NONE){
        return "None";
    }else if(ui_state == UI_STATE_INITAILIZING){
        return "Initializing";
    }else if(ui_state == UI_STATE_SETTING){
        return "Setting";
    }else if(ui_state == UI_STATE_RESTING){
        return "Resting";
    }else if(ui_state == UI_STATE_CHARGING){
        return "Charging";
    }else if(ui_state == UI_STATE_MOVING){
        return "Moving";
    }else if(ui_state == UI_STATE_PICKUP){
        return "Pickup";
    }else if(ui_state == UI_STATE_MOVEFAIL){
        return "Movefail";
    }else if(ui_state == UI_STATE_CLEANING){
        return "Cleaning";
    }else{
        return QString::number(ui_state);
    }
}
void Supervisor::passInit(){
    plog->write("[COMMAND] ROBOT INIT PASS");
    debug_mode = true;
    stateInit();
}
QString Supervisor::getLogDate(int num){
    QString str = curLog[num].split("[")[0];
    if(str.length() > 20){
        return str.left(20);
    }else{
        return str;
    }
}
QString Supervisor::getLogAuth(int num){
    QString str = curLog[num];
    if(str.split("[").size() > 1)
        return str.split("[")[1].split("]")[0];
    else
        return "";
}
QString Supervisor::getLogMessage(int num){
    QString str = curLog[num];
    if(str.split("[").size() > 1){
        str = curLog[num];
        if(str.split("]").size() > 1)
            return str.split("]")[1];
        else
            return "";
    }else{
        if(str.split("[")[0].length() > 20){
            return str.mid(20,str.length()-20);
        }else{
            return "";
        }
    }

}
int Supervisor::getLogLineNum(){
    return curLog.size();
}
void Supervisor::readLog(QDateTime date){
    std::string path = QString().toStdString();
    QFile file(QDir::homePath()+"/RB_MOBILE/log/"+log_folder+"/"+date.toString("yyyy_MM_dd")+".txt");
    if(!file.open(QIODevice::ReadOnly)){
        curLog.clear();
        plog->write("[SUPERVISOR] READ LOG (File not opened) : "+file.fileName());
        return;
    }

    curLog.clear();
    QTextStream logs(&file);
    while(!logs.atEnd()){
        QString line = logs.readLine();
        curLog.append(line);
    }
}


LOCATION Supervisor::getServingLocation(int group, QString name){
    for(int i=0; i<pmap->serving_locations.size(); i++){
        if(pmap->serving_locations[i].group == group)
            if(pmap->serving_locations[i].name == name){
                return pmap->serving_locations[i];
            }
    }
    return LOCATION();
}
LOCATION Supervisor::getServingLocation(QString group, QString name){
    for(int i=0; i<pmap->serving_locations.size(); i++){
        if(pmap->serving_locations[i].group_name == group){
            if(pmap->serving_locations[i].name == name){
                return pmap->serving_locations[i];
            }
        }
    }
    return LOCATION();
}
LOCATION Supervisor::getServingLocation(QString name){
    for(int i=0; i<pmap->serving_locations.size(); i++){
        if(pmap->serving_locations[i].name == name){
            return pmap->serving_locations[i];
        }
    }
    return LOCATION();
}
LOCATION Supervisor::getChargingLocation(int num){
    if(num > -1 && num < pmap->charging_locations.size()){
        return pmap->charging_locations[num];
    }
    return LOCATION();
}
LOCATION Supervisor::getRestingLocation(int num){
    if(num > -1 && num < pmap->resting_locations.size()){
        return pmap->resting_locations[num];
    }
    return LOCATION();
}
LOCATION Supervisor::getInitLocation(int num){
    if(num > -1 && num < pmap->init_locations.size()){
        return pmap->init_locations[num];
    }
    return LOCATION();
}
LOCATION Supervisor::getCleaningLocation(int num){
    if(num > -1 && num < pmap->cleaning_locations.size()){
        return pmap->cleaning_locations[num];
    }
    return LOCATION();
}



int Supervisor::getzipstate(){
    return zip->process;
}
void Supervisor::usbsave(QString usb, bool _ui, bool _slam, bool _config, bool _map, bool _log){
    //need check
    zip->process = 0;
    std::string user = getenv("USER");
    std::string path = "/media/" + user;
    qDebug() << _ui << _slam;
    if(usb == "Desktop"){
        plog->write("[USER INPUT] USB SAVE : Desktop");
        zip->makeZip(QDir::homePath()+"/Desktop",_ui,_slam,_config,_map,_log);
    }else if(usb == ""){
        if(usb_list.size() > 0){
            QString usb_path = QString::fromStdString(path) + "/" + usb_list[0];
            plog->write("[USER INPUT] USB SAVE : "+usb_list[0]);
            zip->makeZip(usb_path,_ui,_slam,_config,_map,_log);
        }else{
            plog->write("[USER INPUT] USB SAVE ERROR : usb_list size = 0");
        }
    }else{
        QString usb_path = QString::fromStdString(path) + "/" + usb;
        qDebug() << usb_path;
        plog->write("[USER INPUT] USB SAVE : "+usb);
        zip->makeZip(usb_path,_ui,_slam,_config,_map,_log);
    }
}
int Supervisor::getWifiNum(){
#ifdef EXTPROC_TEST
    return probot->wifi_list.size();
#else
    return probot->wifi_map.size();
#endif
}
QString Supervisor::getCurWifiSSID(){
#ifdef EXTPROC_TEST
    return probot->wifi_interface.ssid;
#else
    return probot->wifi_ssid;
#endif
}

float Supervisor::getICPRatio(){
    return probot->inlier_ratio;
}
float Supervisor::getICPError(){
    return probot->inlier_error;
}
QString Supervisor::getWifiSSID(int num){//need check
#ifdef EXTPROC_TEST
    if(num < probot->wifi_list.size() && num > -1){
        qDebug() << probot->wifi_list[num].ssid;
        return QString::fromLocal8Bit(probot->wifi_list[num].ssid.toUtf8());
    }else{
        return "unknown";
    }
#else
    if(num < probot->wifi_map.size() && num > -1){
        QList<QString> keys = probot->wifi_map.keys();
        return probot->wifi_map[keys[num]].ssid;
        std::sort(keys.begin(),keys.end(),sortWifi);
        if(num < keys.size() && num > -1){
            return probot->wifi_map[keys[num]].ssid;
        }else
            return "unknown";
    }else{
        return "unknown";
    }
#endif
}
int Supervisor::getEthernetConnection(){
    return probot->ethernet_interface.state;
}

int Supervisor::getInternetConnection(){
    if(probot->con_internet){
        return 2;
    }else{
        return probot->con_internet2;
    }
}
int Supervisor::getWifiConnection(){
    return probot->wifi_interface.state;
}

void Supervisor::process_accept(int cmd){//need check

}

bool Supervisor::isRobotReady(bool print){
    //240401 lock state가 true면 motor status가 1이 아니어도 넘어가기에 삭제처리
    if(!debug_mode && getStateMoving() == READY && probot->localization_state == LOCAL_READY && (probot->motor[0].status == 1 && probot->motor[1].status == 1) && probot->status_charge_connect == 0){
        return true;
    }else{
        if(print){
            plog->write("[COMMAND] Robot not Ready : "+QString::asprintf("DState: %d, RState : %d, LState : %d, LockState: %d, MState1: %d, MState2: %d, CState: %d, UState: %d",debug_mode, getStateMoving(), probot->localization_state, probot->status_lock, probot->motor[0].status, probot->motor[1].status, probot->status_charge_connect, ui_state));
        }
        return false;
    }
}

void Supervisor::connect_wifi_fail(int reason, QString ssid){
    QMetaObject::invokeMethod(mMain, "wifi_con_fail");
}
void Supervisor::connect_wifi_success(QString ssid){
    QMetaObject::invokeMethod(mMain, "wifi_con_success");
}
void Supervisor::set_wifi_success(QString ssid){
    QMetaObject::invokeMethod(mMain, "wifi_set_success");
}
void Supervisor::set_wifi_fail(int reason,QString ssid){
    QMetaObject::invokeMethod(mMain, "wifi_set_fail");
}
void Supervisor::process_done(int cmd){//need check
#ifdef EXTPROC_TEST
#else
#endif
}

void Supervisor::process_error(int cmd, int param){//need check
#ifdef EXTPROC_TEST
#else
    if(cmd == ExtProcess::PROCESS_CMD_CHECK_CONNECTION){
        QMetaObject::invokeMethod(mMain, "checkwifidone");
    }else if(cmd == ExtProcess::PROCESS_CMD_CONNECT_WIFI){
        QMetaObject::invokeMethod(mMain, "wififailed");
    }else if(cmd == ExtProcess::PROCESS_CMD_SET_WIFI_IP){
        QMetaObject::invokeMethod(mMain, "setip_fail");
    }else if(cmd == ExtProcess::PROCESS_CMD_GIT_PULL){
        extproc->git_reset();
    }else if(cmd == ExtProcess::PROCESS_CMD_GIT_UPDATE){
        if(param == 0){
            plog->write("[PROCESS] Update failed");
            QMetaObject::invokeMethod(mMain, "gitfailed");
        }else if(param == 1){
            plog->write("[PROCESS] Update failed");
            QMetaObject::invokeMethod(mMain, "gitnewest");
        }
    }
#endif
}

void Supervisor::process_timeout(int cmd){//need check
    QMetaObject::invokeMethod(mMain, "checkwifidone");
}

void Supervisor::connectWifi(QString ssid, QString passwd){
    checker->connectWifi(ssid, passwd);
}

void Supervisor::setEthernet(QString ip, QString subnet, QString gateway, QString dns1, QString dns2){
    checker->setEthernet(ip,subnet,gateway,dns1,dns2);
}
void Supervisor::setWifiDHCP(){
    checker->setIP(false,probot->wifi_interface.ssid);
}
void Supervisor::setWifi(QString ssid, QString ip, QString subnet, QString gateway, QString dns1, QString dns2){
    if(ssid == ""){
        ssid = probot->wifi_interface.ssid;
    }
    checker->setIP(true,ssid,ip,subnet,gateway,dns1,dns2);
}
void Supervisor::setWifi(QString ip, QString gateway, QString dns){
#ifdef EXTPROC_TEST
//    checker->setIP(probot->wifi_interface.ssid,ip,
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

QString Supervisor::getcurIPMethod(){
    return probot->wifi_interface.method;
}
QString Supervisor::getcurIP(){
    return probot->wifi_interface.ipv4;
}
QString Supervisor::getcurGateway(){
    return probot->wifi_interface.gateway;
}

QString Supervisor::getcurNetmask(){
    return probot->wifi_interface.netmask;
}
QString Supervisor::getcurDNS2(){
    return probot->wifi_interface.dns2;
}
QString Supervisor::getcurDNS(){
    return probot->wifi_interface.dns1;
}

QString Supervisor::getethernetIP(){
    return probot->ethernet_interface.ipv4;
}
QString Supervisor::getethernetNetmask(){
    return probot->ethernet_interface.netmask;
}
QString Supervisor::getethernetGateway(){
    return probot->ethernet_interface.gateway;
}
QString Supervisor::getethernetDNS(){
    return probot->ethernet_interface.dns1;
}
QString Supervisor::getethernetDNS2(){
    return probot->ethernet_interface.dns2;
}
void Supervisor::getAllWifiList(){
    checker->getWifiList(true);
}
bool Supervisor::getWifiSecurity(QString ssid){
    for(ST_WIFI w : probot->wifi_list){
        if(w.ssid == ssid){
            return w.security;
        }
    }
    return false;
}
int Supervisor::getWifiLevel(){
    for(ST_WIFI w : probot->wifi_list){
        if(w.ssid == probot->wifi_interface.ssid){
            return w.level;
        }
    }
    return 0;
}
int Supervisor::getWifiLevel(QString ssid){
    for(ST_WIFI w : probot->wifi_list){
        if(w.ssid == ssid){
            return w.level;
        }
    }
    return 0;
}
int Supervisor::getWifiRate(QString ssid){
    return probot->wifi_map[ssid].rate;
}
bool Supervisor::getWifiInuse(QString ssid){
    if(ssid == probot->wifi_interface.ssid)
        return true;
    else
        return false;
}

void Supervisor::cleanTray(){
    plog->write("[COMMAND] cleanTray");
    if(ui_state == UI_STATE_CLEANING){
        ui_state = UI_STATE_INITAILIZING;
    }else{
        stateInit();
    }
}
int Supervisor::getCallQueueSize(){
    return pmap->call_queue.size();
}

void Supervisor::checkTravelline(){
    pmap->tline_issue = 0;
    ipc->set_cmd(ROBOT_CMD_CHECK_TRAVEL_LINE,"Check Travelline");
}

void Supervisor::confirmLocalization(){
    plog->write("[COMMAND] confirmLocalization");
    probot->localization_confirm = true;
    debug_mode = false;
}

void Supervisor::confirmLocalizationAnnot(){
    plog->write("[COMMAND] confirmLocalizationAnnot");
    probot->localization_confirm = true;
//    debug_mode = false;
}

void Supervisor::clearStatusAll(){
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
    probot->pathSize =0;
    probot->curPath.clear();
    probot->localpathSize =0;
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
    probot->is_calling=false;
    probot->is_patrol = false;
    probot->curLocation = LOCATION{};

    probot->call_moving_count=0;

    probot->server_call_size=0;
    probot->server_call_location=-1;

}

void Supervisor::resetLocalization(){
    plog->write("[COMMAND] resetLocalization");
    debug_mode = false;
    probot->localization_confirm = false;
}
void Supervisor::resetLocalizationConfirm(){
    plog->write("[COMMAND] resetLocalizationConfirm");
    probot->localization_confirm = false;
}

void Supervisor::clearStatus(){
    probot->localization_state = 0;
    probot->motor[0].status = 0;
    probot->motor[1].status = 0;
    pmap->call_queue.clear();
}

void Supervisor::stateMoving(){
    plog->write("[STATE] STATE MOVING");
    ui_state = UI_STATE_MOVING;
    count_moveto = 0;
    cmd_accept = false;
    patrol_wait_count = 0;
    probot->current_target.name = "";
    probot->call_moving_count = 0;
}

void Supervisor::stateInit(){
    if(ui_state != UI_STATE_NONE){
        plog->write("[STATE] STATE INIT");
        ui_state = UI_STATE_NONE;
    }
    patrol_mode = PATROL_NONE;
    probot->is_calling = false;
    for(int i=0; i<probot->trays.size(); i++){
        probot->trays[i].empty = true;
    }
    current_patrol = ST_PATROL();
    probot->is_patrol = false;
    pmap->call_queue.clear();
    probot->current_target.name = "";
    ipc->moveStop();
}
void Supervisor::killSLAM(){
    plog->write("[COMMAND] killSLAM");
    // ipc->set_cmd(ROBOT_CMD_RESTART,"Kill Slam");
    clearStatusAll();
    stateInit();
}

void Supervisor::clear_all(){
    plog->write("[COMMAND] Reset All (Remove all directories)");
    timer2->stop();

    //maps 폴더 지움.
    QMetaObject::invokeMethod(mMain, "setClear",Qt::DirectConnection,
                              Q_ARG(QVariant,QVariant().fromValue(QDateTime::currentDateTime().toString("[yyyy-MM-dd hh:mm:ss]")+" /RB_MOBILE/maps directory : remove")),
                              Q_ARG(QVariant,QVariant().fromValue(1)));

    QString path_maps = QDir::homePath()+"/RB_MOBILE/maps";
    QDir dir_maps(path_maps);
    if(dir_maps.removeRecursively()){
        plog->write("[CLEAR] Reset Clear : Remove maps");
        QMetaObject::invokeMethod(mMain, "setClear",Qt::DirectConnection,
                                  Q_ARG(QVariant,QVariant().fromValue(QDateTime::currentDateTime().toString("[yyyy-MM-dd hh:mm:ss]")+" /RB_MOBILE/maps directory : remove")),
                                  Q_ARG(QVariant,QVariant().fromValue(2)));
    }else{
        plog->write("[CLEAR] Reset Clear : Remove maps failed");
        QMetaObject::invokeMethod(mMain, "setClear",Qt::DirectConnection,
                                  Q_ARG(QVariant,QVariant().fromValue(QDateTime::currentDateTime().toString("[yyyy-MM-dd hh:mm:ss]")+" /RB_MOBILE/maps directory : remove")),
                                  Q_ARG(QVariant,QVariant().fromValue(3)));
    }
    QDir().mkdir(path_maps);

    //temp 폴더 지움.
    QString path_temp = QDir::homePath()+"/RB_MOBILE/temp";
    QDir dir_temp(path_temp);
    if(dir_temp.removeRecursively()){
        plog->write("[CLEAR] Reset Clear : Remove temp");
        QMetaObject::invokeMethod(mMain, "setClear",Qt::DirectConnection,
                                  Q_ARG(QVariant,QVariant().fromValue(QDateTime::currentDateTime().toString("[yyyy-MM-dd hh:mm:ss]")+" /RB_MOBILE/temp directory : remove")),
                                  Q_ARG(QVariant,QVariant().fromValue(2)));
    }else{
        plog->write("[CLEAR] Reset Clear : Remove temp failed");
        QMetaObject::invokeMethod(mMain, "setClear",Qt::DirectConnection,
                                  Q_ARG(QVariant,QVariant().fromValue(QDateTime::currentDateTime().toString("[yyyy-MM-dd hh:mm:ss]")+" /RB_MOBILE/temp directory : remove")),
                                  Q_ARG(QVariant,QVariant().fromValue(3)));
    }


    //patrol 폴더 지움.
    QString path_patrol = QDir::homePath()+"/RB_MOBILE/patrol";
    QDir dir_patrol(path_patrol);
    if(dir_patrol.removeRecursively()){
        plog->write("[CLEAR] Reset Clear : Remove patrol");
        QMetaObject::invokeMethod(mMain, "setClear",Qt::DirectConnection,
                                  Q_ARG(QVariant,QVariant().fromValue(QDateTime::currentDateTime().toString("[yyyy-MM-dd hh:mm:ss]")+" /RB_MOBILE/patrol directory : remove")),
                                  Q_ARG(QVariant,QVariant().fromValue(2)));
    }else{
        plog->write("[CLEAR] Reset Clear : Remove patrol failed");
        QMetaObject::invokeMethod(mMain, "setClear",Qt::DirectConnection,
                                  Q_ARG(QVariant,QVariant().fromValue(QDateTime::currentDateTime().toString("[yyyy-MM-dd hh:mm:ss]")+" /RB_MOBILE/patrol directory : remove")),
                                  Q_ARG(QVariant,QVariant().fromValue(3)));
    }

    //myID 등  robot_config.ini 수정
    //config 폴더 지움.
    QString path_config = QDir::homePath()+"/RB_MOBILE/config";
    QDir dir_config(path_config);
    if(dir_config.removeRecursively()){
        plog->write("[CLEAR] Reset Clear : Remove config");
        QMetaObject::invokeMethod(mMain, "setClear",Qt::DirectConnection,
                                  Q_ARG(QVariant,QVariant().fromValue(QDateTime::currentDateTime().toString("[yyyy-MM-dd hh:mm:ss]")+" /RB_MOBILE/config directory : remove")),
                                  Q_ARG(QVariant,QVariant().fromValue(2)));
    }else{
        plog->write("[CLEAR] Reset Clear : Remove config failed");
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
    if(dir_log.removeRecursively()){
        QDir().mkdir(QDir::homePath() + "/RB_MOBILE/log");
        QDir().mkdir(QDir::homePath() + "/RB_MOBILE/log/ui_log");
        QDir().mkdir(QDir::homePath() + "/RB_MOBILE/log/extproc_log");
        QDir().mkdir(QDir::homePath() + "/RB_MOBILE/log/sn_log");
        plog->write("[CLEAR] Reset Clear : Remove log Success");
        QMetaObject::invokeMethod(mMain, "setClear",Qt::DirectConnection,
                                  Q_ARG(QVariant,QVariant().fromValue(QDateTime::currentDateTime().toString("[yyyy-MM-dd hh:mm:ss]")+" /RB_MOBILE/log directory : remove")),
                                  Q_ARG(QVariant,QVariant().fromValue(2)));


    }else{
        if(!dir_log.exists()){
            QDir().mkdir(QDir::homePath() + "/RB_MOBILE/log");
            QDir().mkdir(QDir::homePath() + "/RB_MOBILE/log/ui_log");
            QDir().mkdir(QDir::homePath() + "/RB_MOBILE/log/extproc_log");
            QDir().mkdir(QDir::homePath() + "/RB_MOBILE/log/sn_log");
        }
        plog->write("[CLEAR] Reset Clear : Remove log Failed");
        QMetaObject::invokeMethod(mMain, "setClear",Qt::DirectConnection,
                                  Q_ARG(QVariant,QVariant().fromValue(QDateTime::currentDateTime().toString("[yyyy-MM-dd hh:mm:ss]")+" /RB_MOBILE/log directory : remove")),
                                  Q_ARG(QVariant,QVariant().fromValue(3)));

    }

    QMetaObject::invokeMethod(mMain, "setClear",Qt::DirectConnection,
                              Q_ARG(QVariant,QVariant().fromValue(QDateTime::currentDateTime().toString("[yyyy-MM-dd hh:mm:ss]")+" Reset All Done ")),
                              Q_ARG(QVariant,QVariant().fromValue(2)));
}

void Supervisor::factoryInit(){
    start_clear = true;
}



int Supervisor::getTravellineIssue(){
    return pmap->tline_issue;
}
QString Supervisor::getTravellineIssueGroup(int num){
    return pmap->tline_issues[num].group;
}
QString Supervisor::getTravellineIssueName(int num){

    return pmap->tline_issues[num].name;
}
bool Supervisor::getTravellineIssueFar(int num){

    return pmap->tline_issues[num].is_far;
}
bool Supervisor::getTravellineIssueBroken(int num){
    return pmap->tline_issues[num].is_broken;
}

void Supervisor::setVelmapView(bool onoff){
    maph->setShowVelocitymap(onoff);
}
void Supervisor::setTlineView(bool onoff){
    maph->setShowTravelline(onoff);
}
void Supervisor::setObjectView(bool onoff){
    maph->setShowObject(onoff);
}
void Supervisor::setAvoidmapView(bool onoff){
    maph->setShowAvoidMap(onoff);
}
void Supervisor::setLocationView(bool onoff){
    maph->setShowLocation(onoff);
}
void Supervisor::setRobotView(bool onoff){
    maph->setShowRobot(onoff);
}

void Supervisor::readPatrol(){
    patrols.clear();
    QString path = QDir::homePath() + "/RB_MOBILE/patrol";
    if(!QFile::exists(path)){
        QDir().mkdir(path);
        plog->write("[COMMAND] readPatrol : no path make new -> "+path);
    }else{
        QDir dir(path);
        QStringList files = dir.entryList();
        plog->write("[COMMAND] readPatrol : "+path);
        for(QString file:files){
            if(file.split(".").size() > 1){
                if(file.left(7) == "patrol_" && file.split(".")[1] == "ini"){
                    QSettings patrol(path+"/"+file, QSettings::IniFormat);
                    ST_PATROL temp;
                    patrol.beginGroup("SETTING");
                    if(patrol.value("name").toString() == ""){

                    }else{
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
                        for(int i=0; i<loc_num; i++){
                            LOCATION temp_loc;
                            if(patrol.value("group"+QString::number(i)).toString() == "Charging"){
                                temp_loc = getChargingLocation(0);
                            }else if(patrol.value("group"+QString::number(i)).toString() == "Resting"){
                                temp_loc = getRestingLocation(0);
                            }else if(patrol.value("group"+QString::number(i)).toString() == "Cleaning"){
                                temp_loc = getCleaningLocation(0);
                            }else{
                                temp_loc = getServingLocation(patrol.value("group"+QString::number(i)).toString(),patrol.value("loc"+QString::number(i)).toString());
                            }
                            if(temp_loc.name != ""){
                                temp.location.append(temp_loc);
                            }
                        }
                        patrol.endGroup();

                        if(temp.moving_page.mode == "custom"){
                            patrol.beginGroup("MOVING");
                            temp.moving_page.background = patrol.value("background").toString();
                            if(temp.moving_page.background == "color"){
                                temp.moving_page.color = patrol.value("color").toString();
                            }else if(temp.moving_page.background == "image"||temp.moving_page.background == "gif"){
                                temp.moving_page.image = patrol.value("image").toString();
                            }else if(temp.moving_page.background == "video"){
                                temp.moving_page.video = patrol.value("video").toString();
                                temp.moving_page.audio = patrol.value("video_audio").toString();

                                if(temp.moving_page.audio == ""){
                                    temp.moving_page.audio = "video";
                                }
                            }
                            temp.moving_page.volume = patrol.value("audio").toFloat();

                            int num = patrol.value("obj_num").toInt();
                            //object reading...(to be continue..)
                            for(int i=0; i<num; i++){
                                ST_PAGE_OBJECT temp_obj;
                                QStringList objs=patrol.value("obj"+QString::number(i)).toString().split(",");
                                if(objs.size() > 5){
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
                        plog->write("[COMMAND] readPatrol File : "+file + " -> "+temp.name+", "+temp.type+", "+QString::number(temp.location.size())+", "+temp.voice_name);
                        patrols.append(temp);
                    }
                }
            }
        }
    }
}

int Supervisor::getPatrolSize(){
    return patrols.size();
}

QString Supervisor::getPatrolName(int num){
    if(num > -1 && num < patrols.size())
        return patrols[num].name;
    else
        return "";
}

void Supervisor::loopClosing(){
    ipc->set_cmd(ROBOT_CMD_MAP_LOOP_CLOSING, "LoopClosing");
}

int Supervisor::getPatrolVoiceNameNum(int num){
    if(patrols[num].name == "vara" || patrols[num].name == "woman" || patrols[num].name == "danna" || patrols[num].name == "liangliang" || patrols[num].name == "ntomoko" || patrols[num].name == "jose"){
        return 1;
    }else if(patrols[num].name == "nhajun" || patrols[num].name == "matt" || patrols[num].name == "dayumu" ){
        return 2;
    }else if(patrols[num].name == "njooahn" || patrols[num].name == "shinji"){
        return 3;
    }else if(patrols[num].name == "nsangdo"){
        return 4;
    }else if(patrols[num].name == "nsunhee"){
        return 5;
    }else if(patrols[num].name == "nkyungtae"){
        return 6;
    }else if(patrols[num].name == "nsabina"){
        return 7;
    }else if(patrols[num].name == "nmammon"){
        return 8;
    }else{
        return 0;
    }
}

QString Supervisor::getPatrolType(int num){
    if(num > -1 && num < patrols.size())
        return patrols[num].type;
    else
        return "";
}
QString Supervisor::getPatrolLocation(int num){
    if(num > -1 && num < patrols.size())
        return patrols[num].location_mode;
    else
        return "";
}
QString Supervisor::getPatrolMovingPage(int num){
    if(num > -1 && num < patrols.size())
        return patrols[num].moving_page.mode;
    else
        return "";
}
QString Supervisor::getPatrolArrivePage(int num){
    if(num > -1 && num < patrols.size())
        return patrols[num].arrive_page.mode;
    else
        return "";
}
int Supervisor::getPatrolWaitTime(int num){
    if(num > -1 && num < patrols.size())
        return patrols[num].wait_time;
    else
        return -1;
}
int Supervisor::getPatrolPassTime(int num){
    if(num > -1 && num < patrols.size())
        return patrols[num].pass_time;
    else
        return -1;
}
QString Supervisor::getPatrolVoiceMode(int num){
    if(num > -1 && num < patrols.size())
        return patrols[num].voice_mode;
    else
        return "";
}
QString Supervisor::getPatrolVoiceLanguage(int num){
    if(num > -1 && num < patrols.size())
        return patrols[num].voice_language;
    else
        return "";
}
bool Supervisor::isPatrolPage(){
    return probot->is_patrol;
}
QString Supervisor::getPatrolMovingMode(){
    return current_patrol.moving_page.mode;
}
QString Supervisor::getPatrolArriveMode(){
    return current_patrol.arrive_page.mode;
}
QString Supervisor::getPatrolVoice(int num){
    if(num > -1 && num < patrols.size())
        return patrols[num].voice_path;
    else
        return "";
}

QString Supervisor::getPatrolVoiceMention(int num){
    if(num > -1 && num < patrols.size())
        if(patrols[num].voice_mode == "tts"){
            return patrols[num].voice_mention;
        }else{
            return patrols[num].voice_file;
        }
    else
        return "";
}
int Supervisor::getPatrolLocationSize(int num){
    if(num > -1 && num < patrols.size())
        return patrols[num].location.size();
    else
        return 0;
}

void Supervisor::initCurrentPatrol(){
    current_patrol = ST_PATROL();
    current_patrol.moving_page.mode = "face1";
    current_patrol.arrive_page.mode = "pass";
}

void Supervisor::saveServingPage(){
    QString path = QDir::homePath() + "/RB_MOBILE/patrol";
    if(!QFile::exists(path)){
        QDir().mkdir(path);
    }
    QString filestr = path + "/serving.ini";
    QSettings file(filestr, QSettings::IniFormat);
    file.clear();

    file.setValue("MOVING/background",serving_page.background);
    file.setValue("MOVING/image",serving_page.image);
    file.setValue("MOVING/video",serving_page.video);
    file.setValue("MOVING/video_audio",serving_page.audio);
    file.setValue("MOVING/color",serving_page.color);
    file.setValue("MOVING/obj_num",serving_page.objects.size());
    file.setValue("MOVING/audio",serving_page.volume);

    for(int i=0; i<serving_page.objects.size(); i++){
        QString str = serving_page.objects[i].type + "," + QString::number(serving_page.objects[i].x) + "," + QString::number(serving_page.objects[i].y) + "," + QString::number(serving_page.objects[i].width) + "," + QString::number(serving_page.objects[i].height) +
                "," + serving_page.objects[i].source +","+serving_page.objects[i].color;
        file.setValue("MOVING/obj"+QString::number(i),str);
    }
}

void Supervisor::savePatrolPage(){
}
void Supervisor::initServingPage(){
    QString path = QDir::homePath() + "/RB_MOBILE/patrol";
    if(!QFile::exists(path)){
        QDir().mkdir(path);
        plog->write("[COMMAND] initServingPage : no path make new -> "+path);
    }


    QString file = path + "/serving.ini";
    if(!QFile::exists(file)){
        plog->write("[COMMAND] initServingPage : no file -> "+file);
        serving_page.mode = "face1";
    }else{
        QSettings patrol(file, QSettings::IniFormat);
        patrol.beginGroup("MOVING");
        serving_page.background = patrol.value("background").toString();
        if(serving_page.background == "color"){
            serving_page.color = patrol.value("color").toString();
        }else if(serving_page.background == "image"||serving_page.background == "gif"){
            serving_page.image = patrol.value("image").toString();
        }else if(serving_page.background == "video"){
            serving_page.video = patrol.value("video").toString();

            serving_page.audio = patrol.value("video_audio").toString();
            if(serving_page.audio == ""){
                serving_page.audio = "video";
            }
        }
        serving_page.volume = patrol.value("audio").toFloat();

        int num = patrol.value("obj_num").toInt();
        serving_page.objects.clear();
        //object reading...(to be continue..)
        for(int i=0; i<num; i++){
            ST_PAGE_OBJECT temp_obj;
            QStringList objs=patrol.value("obj"+QString::number(i)).toString().split(",");
            if(objs.size() > 5){
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

void Supervisor::setCurrentPatrol(int num){
    if(num > -1 && num < patrols.size()){
        current_patrol.location.clear();
        current_patrol = patrols[num];
        plog->write("[COMMAND] setCurrentPatrol : "+QString::number(num)+", " + current_patrol.name);
    }else if(num == -1){
        plog->write("[COMMAND] setCurrentPatrol : no found patrol " + QString::number(num) + ", " + QString::number(patrols.size()));
    }
}
QString Supervisor::getPatrolLocation(int num, int loc){
    if(num > -1 && num < patrols.size()){
        if(loc > -1 && loc < patrols[num].location.size()){
            return patrols[num].location[loc].name;
        }else{
            return "";
        }
    }else{
        return "";
    }
}
QString Supervisor::getPatrolLocationGroup(int num, int loc){
    if(num > -1 && num < patrols.size()){
        if(loc > -1 && loc < patrols[num].location.size()){
            return patrols[num].location[loc].group_name;
        }else{
            return "";
        }
    }else{
        return "";
    }
}

void Supervisor::clearPatrolLocation(QString mode){
    current_patrol.location.clear();
    current_patrol.location_mode = mode;
}

void Supervisor::addPatrolLocation(QString type, QString group, QString name){
    if(type == "Charging"){
        if(getChargingLocation(0).name != ""){
            current_patrol.location.append(getChargingLocation(0));
        }
    }else if(type == "Resting"){
        if(getRestingLocation(0).name != ""){
            current_patrol.location.append(getRestingLocation(0));
        }
    }else if(type == "Cleaning"){
        if(getCleaningLocation(0).name != ""){
            current_patrol.location.append(getCleaningLocation(0));
        }
    }else if(type == "Serving"){
        if(getServingLocation(name).name != ""){
            current_patrol.location.append(getServingLocation(group,name));
        }
    }
}
void Supervisor::setPatrolMovingPage(QString mode, QString param1, QString param2, QString param3){
    current_patrol.moving_page.mode = mode;
}
void Supervisor::setPatrolArrivePage(QString mode, QString param1, QString param2, QString param3){
    if(mode == "custom"){

    }else{
        current_patrol.arrive_page.mode = mode;
    }
}
void Supervisor::savePatrolVoiceBasic(QString voice, QString text){
    qDebug() << "savePatrolVoiceBasic " <<voice <<text;
}
void Supervisor::setPatrolVoice(QString mode, int language, int voice, int volume, int mention){
    qDebug() << "setPatrolVoice " << mode << language << voice << volume;
    current_patrol.voice_mode = mode;
    current_patrol.voice_language = tts->getVoiceLanguage(language);
    current_patrol.voice_volume = volume;
    if(mode == "basic"){
        if(voice == 1){
            current_patrol.voice_name = "child";
        }else{
            current_patrol.voice_name = "woman";
        }

        if(mention == 0){
            current_patrol.voice_file = "thanks";
        }else if(mention == 1){
            current_patrol.voice_file = "hello";
        }else if(mention == 2){
            current_patrol.voice_file = "funny_working_hard";
        }else if(mention == 3){
            current_patrol.voice_file = "hello_rb";
        }else if(mention == 4){
            current_patrol.voice_file = "path_finding";
        }else if(mention == 5){
            current_patrol.voice_file = "rb_fighting";
        }else if(mention == 6){
            current_patrol.voice_file = "moving";
        }else if(mention == 7){
            current_patrol.voice_file = "sorry";
        }else if(mention == 8){
            current_patrol.voice_file = "move_next";
        }else if(mention == 9){
            current_patrol.voice_file = "move_patrol";
        }else if(mention == 10){
            current_patrol.voice_file = "wait_path";
        }else{
            current_patrol.voice_file = "thank_enjoy";
        }

        current_patrol.voice_path = "qrc:/"+current_patrol.voice_name+"_"+current_patrol.voice_file+".mp3";
    }else if(mode == "tts"){
        current_patrol.voice_file = "patrol";
        current_patrol.voice_name = tts->getVoiceName("tts",language,voice);
        current_patrol.voice_path = QDir::homePath() + "/RB_MOBILE/voice/"+current_patrol.voice_name+"_patrol.mp3";
    }
    qDebug() << "setPatrolVoice2 " << current_patrol.voice_mode << current_patrol.voice_language << current_patrol.voice_name << current_patrol.voice_volume;
}

int Supervisor::getTTSLanguageNum(){
    if(getSetting("setting","UI","voice_language") == "ko"){
        return 0;
    }else if(getSetting("setting","UI","voice_language") == "en"){
        return 1;
    }else if(getSetting("setting","UI","voice_language") == "zh-CN"){
        return 2;
    }else if(getSetting("setting","UI","voice_language") == "ja"){
        return 3;
    }else if(getSetting("setting","UI","voice_language") == "es"){
        return 4;
    }else if(getSetting("setting","UI","voice_language") == "ru"){
        return 5;
    }else if(getSetting("setting","UI","voice_language") == "ge"){
        return 6;
    }else if(getSetting("setting","UI","voice_language") == "la"){
        return 7;
    }else if(getSetting("setting","UI","voice_language") == "id"){
        return 8;
    }else{
        return 0;
    }
}

int Supervisor::getTTSNameNum(){
    for(int i=0; i<9; i++){
        if(getSetting("setting","UI","voice_name") == tts->getVoiceName("tts",getTTSLanguageNum(),i))
            return i;
    }

    if(getSetting("setting","UI","voice_name") == "woman"){
        return 1;
    }else{
        return 0;
    }

}
void Supervisor::setPatrol(int num, QString name, QString type, int wait_time, int pass_time){
    if(num > -1 && num < patrols.size()){
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

        for(int i=0; i<current_patrol.location.size(); i++){
            file.setValue("LOCATION/loc"+QString::number(i),current_patrol.location[i].name);
            file.setValue("LOCATION/group"+QString::number(i),current_patrol.location[i].group_name);
        }

        if(current_patrol.moving_page.mode == "custom"){
            file.setValue("MOVING/background",current_patrol.moving_page.background);
            file.setValue("MOVING/image",current_patrol.moving_page.image);
            file.setValue("MOVING/video",current_patrol.moving_page.video);
            file.setValue("MOVING/video_audio",current_patrol.moving_page.audio);
            file.setValue("MOVING/color",current_patrol.moving_page.color);
            file.setValue("MOVING/obj_num",current_patrol.moving_page.objects.size());
            file.setValue("MOVING/audio",current_patrol.moving_page.volume);

            for(int i=0; i<current_patrol.moving_page.objects.size(); i++){
                QString str = current_patrol.moving_page.objects[i].type + "," + QString::number(current_patrol.moving_page.objects[i].x) + "," + QString::number(current_patrol.moving_page.objects[i].y) + "," + QString::number(current_patrol.moving_page.objects[i].width) + "," + QString::number(current_patrol.moving_page.objects[i].height) +
                        "," + current_patrol.moving_page.objects[i].source +","+current_patrol.moving_page.objects[i].color;
                file.setValue("MOVING/obj"+QString::number(i),str);
            }
//            qDebug() << "setPatrol " << current_patrol.moving_page.background << current_patrol.moving_page.color;
        }

        plog->write("[COMMAND] setPatrol "+QString::number(num)+" : "+name);
    }
}

void Supervisor::deletePatrol(int num){
    if(num > -1 && num < patrols.size()){
        QString path = QDir::homePath() + "/RB_MOBILE/patrol";
        QString filename = patrols[num].filename;
        QFile *file = new QFile(path+"/"+filename);
        if(file->remove()){
            plog->write("[COMMAND] deletePatrol "+QString::number(num)+" : SUCCESS");
        }else{
            plog->write("[COMMAND] deletePatrol "+QString::number(num)+" : FAILED");
        }
    }
}

void Supervisor::savePatrol(QString name, QString type, int wait_time, int pass_time){
    QString path = QDir::homePath() + "/RB_MOBILE/patrol";
    if(!QFile::exists(path)){
        QDir().mkdir(path);
    }

    QDir dir(path);
    QStringList files = dir.entryList();
    int size = 0;
    for(QString file:files){
        int tempsize = file.split(".")[0].remove(0,7).toInt();
        if(tempsize > size)
            size = tempsize;
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

    for(int i=0; i<current_patrol.location.size(); i++){
        file.setValue("LOCATION/type"+QString::number(i),current_patrol.location[i].type);
        file.setValue("LOCATION/loc"+QString::number(i),current_patrol.location[i].name);
        file.setValue("LOCATION/group"+QString::number(i),current_patrol.location[i].group_name);
    }

    if(current_patrol.moving_page.mode == "custom"){
        file.setValue("MOVING/background",current_patrol.moving_page.background);
        file.setValue("MOVING/image",current_patrol.moving_page.image);
        file.setValue("MOVING/video_audio",current_patrol.moving_page.audio);
        file.setValue("MOVING/video",current_patrol.moving_page.video);
        file.setValue("MOVING/color",current_patrol.moving_page.color);
        file.setValue("MOVING/obj_num",current_patrol.moving_page.objects.size());
        file.setValue("MOVING/audio",current_patrol.moving_page.volume);

        for(int i=0; i<current_patrol.moving_page.objects.size(); i++){
            QString str = current_patrol.moving_page.objects[i].type + "," + QString::number(current_patrol.moving_page.objects[i].x) + "," + QString::number(current_patrol.moving_page.objects[i].y) + "," + QString::number(current_patrol.moving_page.objects[i].width) + "," + QString::number(current_patrol.moving_page.objects[i].height) +
                    "," + current_patrol.moving_page.objects[i].source +","+current_patrol.moving_page.objects[i].color;
            file.setValue("MOVING/obj"+QString::number(i),str);
        }
    }
    plog->write("[COMMAND] savePatrol : "+name);
}


void Supervisor::setMovingPageColor(QString file){
    setMovingPageBackground("color");
    current_patrol.moving_page.color = file;
}

QString Supervisor::getMovingPageColor(){
    return current_patrol.moving_page.color;
}

void Supervisor::setMovingPageMode(QString mode){
    current_patrol.moving_page.mode = mode;
}

QString Supervisor::getMovingPageMode(){
    return current_patrol.moving_page.mode;
}

void Supervisor::setMovingPageBackground(QString mode){
    current_patrol.moving_page.background = mode;
}

QString Supervisor::getMovingPageBackground(){
    return current_patrol.moving_page.background;
}


void Supervisor::setMovingPageImage(QString file){
    current_patrol.moving_page.image = file;
}

QString Supervisor::getMovingPageImage(){
    return current_patrol.moving_page.image;
}


void Supervisor::setServingPageVideoAudio(QString mode){
    serving_page.audio = mode;
}
QString Supervisor::getServingPageVideoAudio(){
    return serving_page.audio;
}
void Supervisor::setMovingPageVideoAudio(QString mode){
    current_patrol.moving_page.audio = mode;
}
QString Supervisor::getMovingPageVideoAudio(){
    return current_patrol.moving_page.audio;
}
void Supervisor::setMovingPageVideo(QString file){
    setMovingPageBackground("video");
    current_patrol.moving_page.video = file;
}

QString Supervisor::getMovingPageVideo(){
    return current_patrol.moving_page.video;
}
void Supervisor::setMovingPageAudio(float volume){
    qDebug() << "setMovingPageAudio " << volume;
    setMovingPageBackground("video");
    current_patrol.moving_page.volume = volume;
}

float Supervisor::getMovingPageAudio(){
    return current_patrol.moving_page.volume;
}

void Supervisor::setServingPageColor(QString file){
    setServingPageBackground("color");
    serving_page.color = file;
}

QString Supervisor::getServingPageColor(){
    return serving_page.color;
}

void Supervisor::setServingPageMode(QString mode){
    serving_page.mode = mode;
}

QString Supervisor::getServingPageMode(){
    return serving_page.mode;
}

void Supervisor::setServingPageBackground(QString mode){
    serving_page.background = mode;
}

QString Supervisor::getServingPageBackground(){
    return serving_page.background;
}


void Supervisor::setServingPageImage(QString file){
    serving_page.image = file;
}

QString Supervisor::getServingPageImage(){
    return serving_page.image;
}

void Supervisor::setServingPageVideo(QString file){
    setServingPageBackground("video");
    serving_page.video = file;
}

QString Supervisor::getServingPageVideo(){
    return serving_page.video;
}
void Supervisor::setServingPageAudio(float volume){
    setServingPageBackground("video");
    serving_page.volume = volume;
}

float Supervisor::getServingPageAudio(){
    return serving_page.volume;
}

void Supervisor::addPatrolObject(QString page, QString obj){
    plog->write("[PATROL] add Patrol Object ("+page+") : "+obj);
    ST_PAGE_OBJECT temp_obj = makeNewObj(obj);

    if(page == "moving"){
        current_patrol.moving_page.objects.append(temp_obj);
    }else{
        current_patrol.arrive_page.objects.append(temp_obj);
    }
}
void Supervisor::addServingObject(QString page, QString obj){
    plog->write("[PATROL] add Serving Object ("+page+") : "+obj);
    ST_PAGE_OBJECT temp_obj = makeNewObj(obj);
    serving_page.objects.append(temp_obj);
}

ST_PAGE_OBJECT Supervisor::makeNewObj(QString obj){
    ST_PAGE_OBJECT ob;
    ob.type = obj;
    if(obj == "image"){
        ob.x = 0;
        ob.y = 0;
        ob.width = 100;
        ob.height = 100;
        ob.source = "image/robot_head.png";
    }else if(obj == "text"){
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

int Supervisor::getPatrolObjectSize(){
    return current_patrol.moving_page.objects.size();
}

QString Supervisor::getPageObjectType(int num){
    if(num > -1 && num < current_patrol.moving_page.objects.size()){
        return current_patrol.moving_page.objects[num].type;
    }
    return "";
}
void Supervisor::setPageObjectSource(int num, QString src){
    if(num > -1 && num < current_patrol.moving_page.objects.size()){
        current_patrol.moving_page.objects[num].source = src;
    }
}
void Supervisor::setPageObjectColor(int num, QString color){
    if(num > -1 && num < current_patrol.moving_page.objects.size()){
        current_patrol.moving_page.objects[num].color = color;
    }
}
QString Supervisor::getPageObjectSource(int num){
    if(num > -1 && num < current_patrol.moving_page.objects.size()){
        return current_patrol.moving_page.objects[num].source;
    }
    return "";
}
QString Supervisor::getPageObjectColor(int num){
    if(num > -1 && num < current_patrol.moving_page.objects.size()){
        return current_patrol.moving_page.objects[num].color;
    }
    return "";
}
int Supervisor::getPageObjectX(int num){
    if(num > -1 && num < current_patrol.moving_page.objects.size()){
        return current_patrol.moving_page.objects[num].x;
    }
    return -1;
}
int Supervisor::getPageObjectY(int num){
    if(num > -1 && num < current_patrol.moving_page.objects.size()){
        return current_patrol.moving_page.objects[num].y;
    }
    return -1;
}
int Supervisor::getPageObjectWidth(int num){
    if(num > -1 && num < current_patrol.moving_page.objects.size()){
        return current_patrol.moving_page.objects[num].width;
    }
    return -1;
}
int Supervisor::getPageObjectHeight(int num){
    if(num > -1 && num < current_patrol.moving_page.objects.size()){
        return current_patrol.moving_page.objects[num].height;
    }
    return -1;
}
int Supervisor::getPageObjectFontsize(int num){
    if(num > -1 && num < current_patrol.moving_page.objects.size()){
        return current_patrol.moving_page.objects[num].fontsize;
    }
}

int Supervisor::getPageObjectNum(int x, int y){
    for(int i=current_patrol.moving_page.objects.size()-1; i>-1; i--){
        if(x>(current_patrol.moving_page.objects[i].x-10) && x < current_patrol.moving_page.objects[i].x + current_patrol.moving_page.objects[i].width+10){
            if(y>(current_patrol.moving_page.objects[i].y-10) && y < current_patrol.moving_page.objects[i].y + current_patrol.moving_page.objects[i].height+10){
                return i;
            }
        }
    }
    return -1;
}


















int Supervisor::getServingObjectSize(){
    return serving_page.objects.size();
}

QString Supervisor::getServingObjectType(int num){
    if(num > -1 && num < serving_page.objects.size()){
        return serving_page.objects[num].type;
    }
    return "";
}
void Supervisor::setServingObjectSource(int num, QString src){
    if(num > -1 && num < serving_page.objects.size()){
        serving_page.objects[num].source = src;
    }
}
void Supervisor::setServingObjectColor(int num, QString color){
    if(num > -1 && num < serving_page.objects.size()){
        serving_page.objects[num].color = color;
    }
}
QString Supervisor::getServingObjectSource(int num){
    if(num > -1 && num < serving_page.objects.size()){
        return serving_page.objects[num].source;
    }
    return "";
}
QString Supervisor::getServingObjectColor(int num){
    if(num > -1 && num < serving_page.objects.size()){
        return serving_page.objects[num].color;
    }
    return "";
}
int Supervisor::getServingObjectX(int num){
    if(num > -1 && num < serving_page.objects.size()){
        return serving_page.objects[num].x;
    }
    return -1;
}
int Supervisor::getServingObjectY(int num){
    if(num > -1 && num < serving_page.objects.size()){
        return serving_page.objects[num].y;
    }
    return -1;
}
int Supervisor::getServingObjectWidth(int num){
    if(num > -1 && num < serving_page.objects.size()){
        return serving_page.objects[num].width;
    }
    return -1;
}
int Supervisor::getServingObjectHeight(int num){
    if(num > -1 && num < serving_page.objects.size()){
        return serving_page.objects[num].height;
    }
    return -1;
}
int Supervisor::getServingObjectFontsize(int num){
    if(num > -1 && num < serving_page.objects.size()){
        return serving_page.objects[num].fontsize;
    }
}

int Supervisor::getServingObjectNum(int x, int y){
    for(int i=serving_page.objects.size()-1; i>-1; i--){
        if(x>(serving_page.objects[i].x-10) && x < serving_page.objects[i].x + serving_page.objects[i].width+10){
            if(y>(serving_page.objects[i].y-10) && y < serving_page.objects[i].y + serving_page.objects[i].height+10){
                return i;
            }
        }
    }
    return -1;
}


void Supervisor::movePatrolObject(int num, int x, int y){
//    qDebug() << "movePatrolObject " << num << x << y;
    if(num > -1 && num < current_patrol.moving_page.objects.size()){
        current_patrol.moving_page.objects[num].x = x;
        current_patrol.moving_page.objects[num].y = y;
    }
}

void Supervisor::setPatrolObjectSize(int num, int x, int y, int width, int height){
    if(num > -1 && num < current_patrol.moving_page.objects.size()){
        current_patrol.moving_page.objects[num].x = x;
        current_patrol.moving_page.objects[num].y = y;
        current_patrol.moving_page.objects[num].width = width;
        current_patrol.moving_page.objects[num].height = height;
    }
}
void Supervisor::deletePatrolObject(int num){
    if(num > -1 && num < current_patrol.moving_page.objects.size()){
        current_patrol.moving_page.objects.removeAt(num);
    }
}
void Supervisor::setPatrolObjectSize(int num, int point, int x, int y){
    if(num > -1 && num < current_patrol.moving_page.objects.size()){
        qDebug() << "setPatrolObjectSize" << num << point << x << y;
        current_patrol.moving_page.objects[num].x += x;
        current_patrol.moving_page.objects[num].y += y;
        current_patrol.moving_page.objects[num].width -= x;
        current_patrol.moving_page.objects[num].height -= y;
    }

}

void Supervisor::clearPatrolPage(int num){
    if(num == -1){
        current_patrol.moving_page.objects.clear();
    }else if(num > -1 && num < patrols.size()){
        current_patrol.moving_page = patrols[num].moving_page;
    }
}

void Supervisor::moveServingObject(int num, int x, int y){
//    qDebug() << "moveServingObject " << num << x << y;
    if(num > -1 && num < serving_page.objects.size()){
        serving_page.objects[num].x = x;
        serving_page.objects[num].y = y;
    }
}

void Supervisor::setServingObjectSize(int num, int x, int y, int width, int height){
    if(num > -1 && num < serving_page.objects.size()){
        serving_page.objects[num].x = x;
        serving_page.objects[num].y = y;
        serving_page.objects[num].width = width;
        serving_page.objects[num].height = height;
    }
}
void Supervisor::deleteServingObject(int num){
    if(num > -1 && num < serving_page.objects.size()){
        serving_page.objects.removeAt(num);
    }
}
void Supervisor::setServingObjectSize(int num, int point, int x, int y){
    if(num > -1 && num < serving_page.objects.size()){
        qDebug() << "setServingObjectSize" << num << point << x << y;
        serving_page.objects[num].x += x;
        serving_page.objects[num].y += y;
        serving_page.objects[num].width -= x;
        serving_page.objects[num].height -= y;
    }

}

void Supervisor::clearServingPage(){
    qDebug() << "clearServingPage";
    serving_page.objects.clear();
}
