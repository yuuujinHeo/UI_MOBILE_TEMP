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
#include <QSslSocket>
#include <exception>
#include <QGuiApplication>
#include <zlib.h>
#include <usb.h>
#include <QDir>
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

Supervisor::Supervisor(QObject *parent)
    : QObject(parent)
{
    checkShellFiles();

    plog->write("");
    plog->write("");
    plog->write("");
    plog->write("");
    plog->write("");
    plog->write("[BUILDER] Program Started. Supervisor constructed.");

    //기존 SLAM/NAV 모두 종료하고 다시 시작
    QList<QString> path_home_str = QDir::homePath().split("/");
    QProcess *process = new QProcess(this);
    QString file = QDir::homePath() + "/RB_MOBILE/sh/killall.sh";
    process->start(file);
    process->waitForReadyRead(3000);


    timer = new QTimer();
    connect(timer, SIGNAL(timeout()),this,SLOT(onTimer()));
    timer->start(MAIN_THREAD);

    mMain = nullptr;
    usb_list.clear();
    usb_backup_list.clear();
    call_queue.clear();
    ui_state = UI_STATE_NONE;

    probot = &robot;
    pmap = &map;

    server = new ServerHandler();
    maph = new MapHandler();
    zip = new ZIPHandler();
    ipc = new IPCHandler();
    call = new CallbellHandler();
    extproc = new ExtProcess();
    connect(extproc, SIGNAL(timeout(int)),this,SLOT(process_timeout(int)));
    connect(extproc, SIGNAL(got_done(int)),this,SLOT(process_done(int)));
    connect(extproc, SIGNAL(got_accept(int)),this,SLOT(process_accept(int)));
    connect(extproc, SIGNAL(got_error(int,int)),this,SLOT(process_error(int,int)));
    connect(call, SIGNAL(new_call()),this,SLOT(new_call()));
    connect(ipc, SIGNAL(pathchanged()),this,SLOT(path_changed()));
    connect(ipc, SIGNAL(mappingin()),this,SLOT(mapping_update()));
    connect(ipc, SIGNAL(cameraupdate()),this,SLOT(camera_update()));
    connect(server, SIGNAL(updatefail()),this,SLOT(update_fail()));
    connect(server, SIGNAL(updatesuccess()),this,SLOT(update_success()));

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
    setLangauge(getSetting("setting","UI","langauge"));

}

Supervisor::~Supervisor(){
    plog->write("[BUILDER] SUPERVISOR desployed");
    ipc->clearSharedMemory(ipc->shm_cmd);
    delete extproc;
    delete ipc;
    delete slam_process;
    delete zip;
    delete maph;
    delete call;
//    delete
//    extproc->deleteLater();
//    ipc->deleteLater();
//    slam_process->close();
//    QString file = QDir::homePath() + "/RB_MOBILE/sh/killall.sh";
//    slam_process->start(file);
//    slam_process->waitForReadyRead(3000);
//    QThread::sleep(1);
//    slam_process->waitForFinished(3000);
//    slam_process->kill();
//    slam_process->close();
//    wifi_process->close();
    plog->write("[BUILDER] KILLED SLAMNAV");
}

////*********************************************  WINDOW 관련   ***************************************************////
void Supervisor::setWindow(QQuickWindow *Window){
    plog->write("[BUILDER] SUPERVISOR SET WINDOW ");
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

////*********************************************  Location  ***************************************************////
bool Supervisor::getLocationAvailable(int num){
    if(pmap->locations.size() <= num)
        return false;

    if(pmap->locations[num].available){
        return true;
    }else{
        return false;
    }
}

////***********************96980101451808****************************////
void Supervisor::update_fail(){
    QMetaObject::invokeMethod(mMain, "update_fail");
}
void Supervisor::update_success(){
    QMetaObject::invokeMethod(mMain, "update_success");
}

void Supervisor::programRestart(){
    plog->write("[USER INPUT] PROGRAM RESTART");
    ipc->clearSharedMemory(ipc->shm_cmd);
    slam_process->kill();
    QProcess::startDetached(QApplication::applicationFilePath());
    QApplication::exit(12);
}

void Supervisor::programExit(){
    plog->write("[USER INPUT] PROGRAM EXIT");
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
QString Supervisor::getIniPath(QString file){
    return QDir::homePath()+"/RB_MOBILE/config/"+file+"_config.ini";
}

////*********************************수정해야해*****************************************//
void Supervisor::loadMapServer(){
//    if(getSetting("SERVER",))
//    ipc->sendCommand(ROBOT_CMD_SERVER_MAP_LOAD);
}
void Supervisor::sendMapServer(){
    ipc->sendCommand(ROBOT_CMD_SERVER_MAP_UPDATE);
}

bool Supervisor::checkLocationName(int group, QString name){
    for(int i=0; i<pmap->locations.size(); i++){
        if(pmap->locations[i].group == group){
            if(pmap->locations[i].name == name){
                return false;
            }
        }
    }
    return true;
}
////*********************************************  CALLING 관련   ***************************************************////
void Supervisor::clear_call(){
    if(setting_call_num > -1){
        plog->write("[SETTING] Call Id ("+QString::number(setting_call_num)+")"+pmap->locations[setting_call_num].type + ", "  + pmap->locations[setting_call_num].name + " : (clear)");
        pmap->locations[setting_call_num].call_id = "";
        setting_call_num = -1;
        QMetaObject::invokeMethod(mMain, "call_setting");
    }
}
void Supervisor::new_call(){
    if(setting_call_num > -1){
        plog->write("[SETTING] Call Id ("+QString::number(setting_call_num)+")"+pmap->locations[setting_call_num].type + ", "  + pmap->locations[setting_call_num].name + " : "+call->getBellID());
        pmap->locations[setting_call_num].call_id = call->getBellID();
        setting_call_num = -1;
        QMetaObject::invokeMethod(mMain, "call_setting");
    }else{
        bool already_in = false;
        for(int i=0; i<call_queue.size(); i++){
            if(call_queue[i] == call->getBellID()){
                already_in = true;
                plog->write("[SUPERVISOR] NEW CALL (Already queue in "+QString::number(i)+" ) : " + call->getBellID());
                break;
            }
        }
        if(!already_in){
            bool match_call = false;
            for(int i=0; i<pmap->locations.size(); i++){
                if(pmap->locations[i].call_id == call->getBellID()){
                    match_call = true;
                    break;
                }
            }
            if(match_call){
                call_queue.push_back(call->getBellID());
                plog->write("[SUPERVISOR] NEW CALL (queue size "+QString::number(call_queue.size())+" ) : " + call->getBellID());
            }else{
                plog->write("[SUPERVISOR] NEW CALL (Wrong ID ->Ignored) : " + call->getBellID());

            }
        }
    }
}

void Supervisor::setCallbellForce(QString type, bool onoff){
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
    setting_call_num = id;
    //충전, 대기 위치가 1개보다 넘을 때를 대비해서 setting_Call_num 값을 세팅하는 용도
    //각 타입과 타입 내 번호를 받아서 매핑.
//    int serving_num = -1;
//    setting_call_num = -1;
//    int resting_start_num = -1;
//    int num = 0;
//    for(int i=0; i<pmap->locations.size(); i++){
//        if(pmap->locations[i].type == type){
//            if(type == "Serving"){
//                qDebug() << i << num << id-2;
//                if(num == id-2){
//                    serving_num = i;
//                    break;
//                }else{
//                    num++;
//                }
//            }else if(type == "Resting"){
//                resting_start_num = i;
//                break;
//            }
//        }
//    }
//    if(type == "Charging"){
//        setting_call_num = 0;
//    }else if(type == "Serving"){
//        setting_call_num = serving_num;
//    }else if(type == "Resting"){
//        setting_call_num = resting_start_num;
//    }else if(type == "Cleaning"){
//        setting_call_num = 2;
//    }
    plog->write("[SETTING] " + type + " " + QString::number(id)+" callbell setting num : "+QString::number(setting_call_num));
}

LOCATION Supervisor::getCallLocation(QString id){
    for(int i=0; i<pmap->locations.size(); i++){
        if(pmap->locations[i].call_id == id)
            return pmap->locations[i];
    }
    return LOCATION();
}

////*********************************************  SETTING 관련   ***************************************************////
void Supervisor::git_pull_success(){
}

void Supervisor::git_pull_failed(){
}

bool Supervisor::isNewVersion(){
    //깃 최신버전인지.
    return server->need_update();
}
bool Supervisor::isNeedUpdate(){
    //서버업데이트 필요한 지.
    return server->new_update;
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
QString Supervisor::getCurrentCommit(QString name){
    return server->version_list[name].commit;
}
void Supervisor::updateProgram(){
    server->doUpdate();
}
void Supervisor::updateProgramGitPull(){
    server->getGitCommits();
    extproc->git_pull();
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
    QString file2 = "xterm ./update.sh";
    tempprocess->setWorkingDirectory(file);
    tempprocess->start(file2);
    tempprocess->waitForReadyRead(3000);

    qDebug() << "done?";


}
void Supervisor::startUpdate(){
    //Zip 압축풀기
    extproc->update_unzip();
}

void Supervisor::checkVersionAgain(){
    server->check_update = true;
    server->checkUpdate();
}

void Supervisor::setSetting(QString file, QString name, QString value){
    QString ini_path = getIniPath(file);
    QSettings setting(ini_path, QSettings::IniFormat);
    setting.setValue(name,value);
    plog->write("[SETTING] SET "+name+" VALUE TO "+value);
}
QString Supervisor::getSetting(QString file, QString group, QString name){
    QString ini_path = getIniPath(file);
    QSettings setting_robot(ini_path, QSettings::IniFormat);
    setting_robot.beginGroup(group);
    return setting_robot.value(name).toString();
}

void Supervisor::readSetting(QString map_name){
    plog->write("[SUPERVISOR] READ SETTING : "+map_name);
    //Robot Setting================================================================
    QString ini_path = getIniPath("setting");
    qDebug() << "ini path : " << ini_path;
    QSettings setting_config(ini_path, QSettings::IniFormat);

    setting_config.beginGroup("ROBOT_TYPE");
    probot->model = setting_config.value("model").toString();
    probot->serial_num = setting_config.value("serial_num").toInt();
    probot->name = probot->model + QString::number(probot->serial_num);
    probot->type = setting_config.value("type").toString();
    if(probot->type == "CLEANING"){
        use_cleaning_location = true;
    }else{
        use_cleaning_location = false;
    }
    setting_config.endGroup();

    setting.tray_num = 3;

    setting_config.beginGroup("CALL");
    probot->max_moving_count = setting_config.value("call_maximum").toInt();
    setting_config.endGroup();

    setting_config.beginGroup("NETWORK");
    probot->wifi_ssid = setting_config.value("wifi_ssid").toInt();
    setting_config.endGroup();


    setting_config.beginGroup("MAP");
    pmap->map_name = setting_config.value("map_name").toString();
    pmap->map_path = setting_config.value("map_path").toString();
    qDebug() << pmap->map_name << pmap->map_path;
    setting_config.endGroup();

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

    plog->write("[SUPERVISOR] READ SETTING : SENSOR done");
    if(map_name == ""){
        map_name = pmap->map_name;
    }

    maph->loadFile(map_name,"");

    pmap->annot_edit_location = false;
    pmap->annot_edit_tline = false;
    pmap->annot_edit_object = false;
    pmap->annot_edit_drawing = false;
    pmap->annotation_edited = false;
    plog->write("[SUPERVISOR] READ SETTING : "+map_name);
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
    plog->write("[SUPERVISOR] READ SETTING : meta done");

    //Annotation======================================================================
    ini_path = getAnnotPath(map_name);
    QSettings setting_anot(ini_path, QSettings::IniFormat);

    pmap->locations.clear();
    LOCATION temp_loc;

    qDebug() << "?";
    setting_anot.beginGroup("charging_locations");
    QString loc_str = setting_anot.value("loc0").toString();
    QStringList strlist = loc_str.split(",");
    if(strlist.size()>1){
        temp_loc.point = cv::Point2f(strlist[1].toFloat(),strlist[2].toFloat());
        temp_loc.angle = strlist[3].toFloat();
        temp_loc.group = 0;
        temp_loc.group_name = "Charging";
        temp_loc.type = "Charging";
        temp_loc.name = strlist[0];
        if(strlist.size() > 4)
            temp_loc.call_id = strlist[4];
        else
            temp_loc.call_id = "";
    }
    pmap->locations.push_back(temp_loc);
    setting_anot.endGroup();


    setting_anot.beginGroup("resting_locations");
    loc_str = setting_anot.value("loc0").toString();
    strlist = loc_str.split(",");
    if(strlist.size()>1){
        temp_loc.point = cv::Point2f(strlist[1].toFloat(),strlist[2].toFloat());
        temp_loc.angle = strlist[3].toFloat();
        temp_loc.type = "Resting";
        temp_loc.group = 0;
        temp_loc.group_name = "Resting";
        temp_loc.name = strlist[0];
        if(strlist.size() > 4)
            temp_loc.call_id = strlist[4];
        else
            temp_loc.call_id = "";
        pmap->locations.push_back(temp_loc);

    }
    setting_anot.endGroup();

    if(probot->type == "CLEANING"){
        setting_anot.beginGroup("cleaning_locations");
        loc_str = setting_anot.value("loc0").toString();
        strlist = loc_str.split(",");
        if(strlist.size()>1){
            temp_loc.point = cv::Point2f(strlist[1].toFloat(),strlist[2].toFloat());
            temp_loc.angle = strlist[3].toFloat();
            temp_loc.type = "Cleaning";
            temp_loc.group = 0;
            temp_loc.group_name = "Cleaning";
            temp_loc.name = strlist[0];
            if(strlist.size() > 4)
                temp_loc.call_id = strlist[4];
            else
                temp_loc.call_id = "";
            pmap->locations.push_back(temp_loc);
        }else {
            temp_loc.type = "Cleaning";
            temp_loc.name = "Cleaning0";
            temp_loc.call_id = "";
            pmap->locations.push_back(temp_loc);
        }
        setting_anot.endGroup();
    }

    qDebug() << "?";
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

        qDebug() << "?????????????????" << serv_num;

        for(int j=0; j<serv_num; j++){
            QString loc_str = setting_anot.value("loc"+QString::number(j)).toString();
            QStringList strlist = loc_str.split(",");
            temp_loc.point = cv::Point2f(strlist[1].toFloat(),strlist[2].toFloat());
            temp_loc.angle = strlist[3].toFloat();
            temp_loc.type = "Serving";
            temp_loc.name = strlist[0];
            temp_loc.group_name = pmap->location_groups[i];
            if(strlist.size() > 4)
                temp_loc.call_id = strlist[4];
            else
                temp_loc.call_id = "";

            temp_loc.group = i;
            pmap->locations.push_back(temp_loc);
        }
        setting_anot.endGroup();
    }

    qDebug() << "?";
    plog->write("[SUPERVISOR] READ SETTING : annot done");
//    std::sort(pmap->locations.begin(),pmap->locations.end(),sortLocation2);


    qDebug() << pmap->locations.size() << map_name;




    setting_anot.beginGroup("objects");
    int obj_num = setting_anot.value("num").toInt();
    pmap->objects.clear();
    cv::Point2f temp_point;
    for(int i=0; i<obj_num; i++){
        QString name = setting_anot.value("poly"+QString::number(i)).toString();
        QStringList strlist = name.split(",");
        OBJECT temp_obj;
        QStringList templist = strlist[1].split(":");

        if(templist.size() > 1){
            temp_obj.is_rect = false;
            for(int j=1; j<strlist.size(); j++){
                temp_point.x = strlist[j].split(":")[0].toFloat();
                temp_point.y = strlist[j].split(":")[1].toFloat();
                temp_obj.points.push_back(temp_point);
            }
        }else{
            if(strlist[1].toInt() == 1){
                temp_obj.is_rect = true;
                for(int j=2; j<strlist.size(); j++){
                    temp_point.x = strlist[j].split(":")[0].toFloat();
                    temp_point.y = strlist[j].split(":")[1].toFloat();
                    temp_obj.points.push_back(temp_point);
                }
            }else{
                temp_obj.is_rect = false;
                for(int j=2; j<strlist.size(); j++){
                    temp_point.x = strlist[j].split(":")[0].toFloat();
                    temp_point.y = strlist[j].split(":")[1].toFloat();
                    temp_obj.points.push_back(temp_point);
                }
            }
        }
        pmap->objects.push_back(temp_obj);
    }
    setObjPose();
    setting_anot.endGroup();

    plog->write("[SUPERVISOR] READ SETTING : object done");
    //Set Variable
    probot->trays.clear();
    for(int i=0; i<setting.tray_num; i++){
        ST_TRAY temp;
        probot->trays.push_back(temp);
    }

    QMetaObject::invokeMethod(mMain, "update_ini");
}

void Supervisor::editLocation(int num){
    plog->write("[ANNOTATION] Edit Location "+QString::number(num)+" : "+QString().sprintf("(%f,%f,%f) -> (%f,%f,%f)",
                                                                                           pmap->locations[num].point.x,pmap->locations[num].point.y,pmap->locations[num].angle,
                                                                                                 probot->lastPose.point.x,probot->lastPose.point.y,probot->lastPose.angle));
    pmap->locations[num].point = probot->lastPose.point;
    pmap->locations[num].angle = probot->lastPose.angle;
}

void Supervisor::setSystemVolume(int volume){
    ExtProcess::Command temp;
    temp.cmd = ExtProcess::PROCESS_CMD_SET_SYSTEM_VOLUME;
    temp.params[0] = volume;
    extproc->set_command(temp);
}
void Supervisor::requestSystemVolume(){
    ExtProcess::Command temp;
    temp.cmd = ExtProcess::PROCESS_CMD_GET_SYSTEM_VOLUME;
    extproc->set_command(temp);
}


int Supervisor::getLocationNum(QString group, QString name){
    for(int i=0; i<pmap->locations.size(); i++){
        if(pmap->locations[i].group == group){
            if(pmap->locations[i].name == name){
                return i;
            }
        }
    }
    return -1;
}

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

    bool overwrite = false;
    int overwrite_num = -1;
    for(int i=0; i<pmap->locations.size(); i++){
        if(pmap->locations[i].name == name){
            overwrite = true;
            overwrite_num = i;
        }
    }
    if(type == "Serving"){
        plog->write("[MapHandler] Add Location : "+type+","+name+","+QString().sprintf("%f,%f,%f",temp.point.x, temp.point.y, temp.angle));
        pmap->locations.push_back(temp);
        pmap->annot_edit_location = true;
    }else if(type == "Charging"){
        if(overwrite){
            plog->write("[MapHandler] Add Location(Overwrite): "+type+","+name+","+QString().sprintf("%f,%f,%f",temp.point.x, temp.point.y, temp.angle));
            pmap->locations[overwrite_num] = temp;
        }else{
            plog->write("[MapHandler] Add Location : "+type+","+name+","+QString().sprintf("%f,%f,%f",temp.point.x, temp.point.y, temp.angle));
            pmap->locations.insert(getLocationNum("Charging"),temp);
        }
        pmap->annot_edit_location = true;
    }else if(type == "Resting"){
        if(overwrite){
            plog->write("[MapHandler] Add Location(Overwrite): "+type+","+name+","+QString().sprintf("%f,%f,%f",temp.point.x, temp.point.y, temp.angle));
            pmap->locations[overwrite_num] = temp;
        }else{
            plog->write("[MapHandler] Add Location : "+type+","+name+","+QString().sprintf("%f,%f,%f",temp.point.x, temp.point.y, temp.angle));
            pmap->locations.insert(getLocationNum("Charging")+getLocationNum("Resting"),temp);
        }
        pmap->annot_edit_location = true;
    }
    pmap->annot_edit_location = true;
//    std::sort(pmap->locations.begin(),pmap->locations.end(),sortLocation2);
    pmap->annot_edit_location = true;

    saveAnnotation(maph->map_name);
    maph->initLocation();

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
    setObjPose();
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
void Supervisor::startDrawObject(){
    ipc->startObject();
    maph->initObject();
    maph->draw_object_flag = true;
}
void Supervisor::stopDrawObject(){
    ipc->stopObject();
    maph->draw_object_flag = true;
}
void Supervisor::saveDrawObject(){
    ipc->saveObject();
    maph->loadFile(getMapname(),"");
//    maph->initFileWidth();
//    maph->initDrawing();
//    maph->initObject();
    maph->draw_object_flag = false;
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
QString Supervisor::getVoice(QString name, QString mode){
    if(mode == ""){
        mode = getSetting("setting","UI","voice_mode");
        if(mode == ""){
            setSetting("setting","UI/voice_mode","child");
            mode = getSetting("setting","UI","voice_mode");
        }
    }
    QString source = "voice/" + mode + "_" + name + ".mp3";
    plog->write("[SETTING] get Voice mode = "+mode+", name = "+name+", source = "+source);
    return source;
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
    IPCHandler::CMD send_msg;
    send_msg.cmd = ROBOT_CMD_DRAW_LINE_START;
    ipc->set_cmd(send_msg);
}
void Supervisor::drawingRunawayStop(){
    IPCHandler::CMD send_msg;
    send_msg.cmd = ROBOT_CMD_DRAW_LINE_SAVE;
    ipc->set_cmd(send_msg);
}
void Supervisor::slam_map_reload(QString filename){
    ui_state = UI_STATE_NONE;
    probot->localization_state = 0;
    probot->motor[0].status = 0;
    probot->motor[1].status = 0;
    probot->localization_confirm = 0;
    IPCHandler::CMD send_msg;
    send_msg.cmd = ROBOT_CMD_MAP_RELOAD;
    memcpy(send_msg.params,filename.toUtf8(),sizeof(char)*255);
    ipc->set_cmd(send_msg,"MAP RELOAD");
}
void Supervisor::slam_ini_reload(){
    ui_state = UI_STATE_NONE;
    probot->localization_state = 0;
    probot->motor[0].status = 0;
    probot->motor[1].status = 0;
    probot->localization_confirm = 0;
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

    pmap->locations.clear();
    QFile *file = new QFile(QDir::homePath()+"/RB_MOBILE/maps/"+pmap->map_name+"/map_travel_line.png");
    file->remove();
    QFile *file2 = new QFile(QDir::homePath()+"/RB_MOBILE/maps/"+pmap->map_name+"/map_velocity.png");
    file2->remove();

    file->deleteLater();
    file2->deleteLater();
    saveAnnotation(pmap->map_name);

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
        QStringList namelist = FileList[i].split(".");
        if(namelist.size() > 1){
            continue;
        }
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
int Supervisor::getMapFileSize(QString name){
    std::string path = QString(QDir::homePath()+"/RB_MOBILE/maps/"+name).toStdString();
    QDir directory(path.c_str());
    QStringList FileList = directory.entryList();
    map_detail_list.clear();
    for(int i=0; i<FileList.size(); i++){
        if(FileList[i] == "." || FileList[i] == ".."){
            continue;
        }
        map_detail_list.push_back(FileList[i]);
    }
    return map_detail_list.size();
}
QString Supervisor::getMapFile(int num){
    return map_detail_list[num];
}
bool Supervisor::isExistMap(QString name){
    if(name==""){
        name = getMapname();
    }

    if(QFile::exists(getMapPath(name))){
        if(QFile::exists(getRawMapPath(name))){

        }else{
            //make map_raw.png
            QFile::copy(getMapPath(name),getRawMapPath(name));
        }
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
    if(getSetting("setting","UI","group_row_num").toInt()==0)
        setSetting("setting","UI/group_row_num","2");
    if(getSetting("setting","UI","group_col_num").toInt()==0)
        setSetting("setting","UI/group_col_num","4");
    if(getSetting("setting","UI","table_row_num").toInt()==0)
        setSetting("setting","UI/table_row_num","5");
    if(getSetting("setting","UI","table_col_num").toInt()==0)
        setSetting("setting","UI/table_col_num","1");

    if(getSetting("setting","UI","language") == "")
        setSetting("setting","UI/language","KR");
    if(getSetting("setting","UI","voice_mode") == "")
        setSetting("setting","UI/voice_mode","woman");
    if(getSetting("setting","UI","volume_bgm").toInt()==0)
        setSetting("setting","UI/volume_bgm","50");
    if(getSetting("setting","UI","volume_voice").toInt()==0)
        setSetting("setting","UI/volume_voice","50");
    if(getSetting("setting","UI","volume_button").toInt()==0)
        setSetting("setting","UI/volume_button","50");

    if(getSetting("setting","CALL","call_maximum").toInt()==0)
        setSetting("setting","CALL/call_maximum","1");

    if(getSetting("setting","PRESET1","name")==""){
        setSetting("setting","PRESET1/name","매우느리게");
        setSetting("setting","PRESET1/limit_pivot","30");
        setSetting("setting","PRESET1/limit_pivot_acc","30");
        setSetting("setting","PRESET1/limit_v","0.25");
        setSetting("setting","PRESET1/limit_v_acc","0.25");
        setSetting("setting","PRESET1/limit_w","30");
        setSetting("setting","PRESET1/limit_w_acc","45");
    }
    if(getSetting("setting","PRESET2","name")==""){
        setSetting("setting","PRESET2/name","느리게");
        setSetting("setting","PRESET2/limit_pivot","50");
        setSetting("setting","PRESET2/limit_pivot_acc","50");
        setSetting("setting","PRESET2/limit_v","0.75");
        setSetting("setting","PRESET2/limit_v_acc","0.4");
        setSetting("setting","PRESET2/limit_w","50");
        setSetting("setting","PRESET2/limit_w_acc","50");
    }
    if(getSetting("setting","PRESET3","name")==""){
        setSetting("setting","PRESET3/name","보통");
        setSetting("setting","PRESET3/limit_pivot","80");
        setSetting("setting","PRESET3/limit_pivot_acc","80");
        setSetting("setting","PRESET3/limit_v","1.0");
        setSetting("setting","PRESET3/limit_v_acc","0.6");
        setSetting("setting","PRESET3/limit_w","80");
        setSetting("setting","PRESET3/limit_w_acc","80");
    }
    if(getSetting("setting","PRESET4","name")==""){
        setSetting("setting","PRESET4/name","빠르게");
        setSetting("setting","PRESET4/limit_pivot","95");
        setSetting("setting","PRESET4/limit_pivot_acc","95");
        setSetting("setting","PRESET4/limit_v","1.2");
        setSetting("setting","PRESET4/limit_v_acc","0.8");
        setSetting("setting","PRESET4/limit_w","95");
        setSetting("setting","PRESET4/limit_w_acc","95");
    }
    if(getSetting("setting","PRESET5","name")==""){
        setSetting("setting","PRESET5/name","매우빠르게");
        setSetting("setting","PRESET5/limit_pivot","120");
        setSetting("setting","PRESET5/limit_pivot_acc","120");
        setSetting("setting","PRESET5/limit_v","1.5");
        setSetting("setting","PRESET5/limit_v_acc","1.0");
        setSetting("setting","PRESET5/limit_w","120");
        setSetting("setting","PRESET5/limit_w_acc","120");
    }

    if(getSetting("setting","ROBOT_TYPE","type") == "")
        setSetting("setting","ROBOT_TYPE/type","SERVING");
    if(getSetting("setting","ROBOT_TYPE","model") == "")
        setSetting("setting","ROBOT_TYPE/model","None");

    if(getSetting("setting","SENSOR","cam_exposure").toFloat()==0)
        setSetting("setting","SENSOR/cam_exposure","2000");
    if(getSetting("setting","SENSOR","mask").toFloat()==0)
        setSetting("setting","SENSOR/mask","10.0");
    if(getSetting("setting","SENSOR","max_range").toFloat()==0)
        setSetting("setting","SENSOR/max_range","40.0");

    //============================================================================================

    if(getSetting("update","MOTOR","gear_ratio").toFloat()==0)
        setSetting("update","MOTOR/gear_ratio","1.0");
    if(getSetting("update","MOTOR","k_d").toFloat()==0)
        setSetting("update","MOTOR/k_d","4400.0");
    if(getSetting("update","MOTOR","k_i").toFloat()==0)
        setSetting("update","MOTOR/k_i","0.0");
    if(getSetting("update","MOTOR","k_p").toFloat()==0)
        setSetting("update","MOTOR/k_p","100.0");
    if(getSetting("update","MOTOR","left_id").toInt()==0&&getSetting("update","MOTOR","right_id").toInt()==0){
        setSetting("update","MOTOR/left_id","1");
        setSetting("update","MOTOR/right_id","0");
    }
    if(getSetting("update","MOTOR","limit_v").toFloat()==0)
        setSetting("update","MOTOR/limit_v","1.5");
    if(getSetting("update","MOTOR","limit_v_acc").toFloat()==0)
        setSetting("update","MOTOR/limit_v_acc","1.0");
    if(getSetting("update","MOTOR","limit_w").toFloat()==0)
        setSetting("update","MOTOR/limit_w","180.0");
    if(getSetting("update","MOTOR","limit_w_acc").toFloat()==0)
        setSetting("update","MOTOR/limit_w_acc","180.0");
    if(getSetting("update","MOTOR","wheel_dir").toInt()==0)
        setSetting("update","MOTOR/wheel_dir","-1");

    if(getSetting("update","DRIVING","pause_check_ms").toInt()==0)
        setSetting("update","DRIVING/pause_check_ms","500");
    if(getSetting("update","DRIVING","pause_motor_current").toInt()==0)
        setSetting("update","DRIVING/pause_motor_current","3000");
    if(getSetting("update","DRIVING","cur_preset").toInt()==0)
        setSetting("update","DRIVING/cur_preset","3");
    if(getSetting("update","DRIVING","comeback_preset").toInt()==0)
        setSetting("update","DRIVING/comeback_preset","3");

    if(getSetting("update","SLAM","map_size").toInt()==0)
        setSetting("update","SLAM/map_size","1000");
    if(getSetting("update","SLAM","grid_size").toFloat()==0)
        setSetting("update","SLAM/grid_size","0.05");


    if(getSetting("static","ROBOT_HW","wheel_base").toFloat() == 0){
        setSetting("static","ROBOT_HW/wheel_base","0.3542");
    }
    if(getSetting("static","ROBOT_HW","wheel_radius").toFloat() == 0){
        setSetting("static","ROBOT_HW/wheel_radius","0.0635");
    }
    if(getSetting("static","ROBOT_HW","robot_radius").toFloat() == 0){
        setSetting("static","ROBOT_HW/robot_radius","0.3");
    }
    if(getSetting("static","ROBOT_HW","robot_length").toFloat() == 0){
        setSetting("static","ROBOT_HW/robot_length","0.55");
    }
}
void Supervisor::makeRobotINI(){
    QString updatep = getIniPath("update");
    QString settingp = getIniPath("setting");
    QString staticp = getIniPath("static");
    QString robotp = getIniPath("server");

    if(QFile::exists(updatep) && QFile::exists(settingp) && QFile::exists(staticp) && QFile::exists(robotp)){
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
    if(probot->ipc_use)
        return ipc->getConnection();
}
bool Supervisor::getIPCRX(){
    if(probot->ipc_use)
        return ipc->flag_rx;
}
bool Supervisor::getIPCTX(){
    if(probot->ipc_use)
        return ipc->flag_tx;
}
int Supervisor::getusbsize(){
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

void Supervisor::setMap(QString name){
    setSetting("setting","MAP/map_path",QDir::homePath()+"/RB_MOBILE/maps/"+name);
    setSetting("setting","MAP/map_name",name);
    readSetting(name);
    slam_map_reload(name);
}

void Supervisor::copyMap(QString orinname, QString newname){


}

void Supervisor::loadMap(QString name){
    setSetting("setting","MAP/map_path",QDir::homePath()+"/RB_MOBILE/maps/"+name);
    setSetting("setting","MAP/map_name",name);
    readSetting(name);
    slam_map_reload(name);
}

void Supervisor::restartSLAM(){
    plog->write("[USER INPUT] Restart SLAM");
    ipc->clearSharedMemory(ipc->shm_cmd);
    if(slam_process != nullptr){
        plog->write("[SUPERVISOR] RESTART SLAM -> PID : "+QString::number(slam_process->pid()));
        if(slam_process->state() == QProcess::NotRunning){
            plog->write("[SUPERVISOR] RESTART SLAM -> NOT RUNNING -> KILL");
            slam_process->kill();
            slam_process->close();
            probot->localization_state = LOCAL_NOT_READY;
            probot->status_charge = 0;
            probot->status_emo = 0;
            probot->status_power = 0;
            probot->status_remote = 0;
            QString file = "xterm ./startslam.sh";
            slam_process->setWorkingDirectory(QDir::homePath()+"/RB_MOBILE/sh");
            slam_process->start(file);
            slam_process->waitForReadyRead(3000);
            plog->write("[SUPERVISOR] RESTART SLAM -> START SLAM "+QString::number(slam_process->pid()));
        }else if(slam_process->state() == QProcess::Starting){
            plog->write("[SUPERVISOR] RESTART SLAM -> STARTING");
        }else{
            plog->write("[SUPERVISOR] RESTART SLAM -> RUNNING");
            QProcess *tempprocess = new QProcess(this);
            tempprocess->start(QDir::homePath() + "/RB_MOBILE/sh/killslam.sh");
            tempprocess->waitForReadyRead(3000);
        }
        probot->localization_state = LOCAL_NOT_READY;
        probot->status_charge = 0;
        probot->status_emo = 0;
        probot->status_power = 0;
        probot->status_remote = 0;
    }else{
        plog->write("[SUPERVISOR] RESTART SLAM -> SLAM PROCESS IS NEW ");
        slam_process = new QProcess(this);
        QString file = "xterm ./startslam.sh";
        slam_process->setWorkingDirectory(QDir::homePath()+"/RB_MOBILE/sh");
        slam_process->start(file);
        slam_process->waitForReadyRead(3000);
        plog->write("[SUPERVISOR] RESTART SLAM -> START SLAM "+QString::number(slam_process->pid()));
    }
    probot->localization_state = LOCAL_NOT_READY;
    probot->status_charge = 0;
    probot->status_emo = 0;
    probot->status_power = 0;
    probot->status_remote = 0;
    ipc->update();
}

void Supervisor::killSLAM(){
    patrol_mode = PATROL_NONE;
    probot->is_patrol = false;
    call_queue.clear();
    clearRobot();
    probot->localization_confirm = 0;
    probot->localization_state = 0;
    probot->motor[0].status = 0;
    probot->motor[1].status = 0;
    ipc->set_cmd(ROBOT_CMD_RESTART,"Kill Slam");

}
void Supervisor::startSLAM(){
    plog->write("[SUPERVISOR] START SLAM");
    probot->localization_state = LOCAL_NOT_READY;
    probot->status_charge = 0;
    probot->status_emo = 0;
    probot->status_power = 0;
    probot->status_remote = 0;

    slam_process = new QProcess(this);
    QString file = "xterm ./startslam.sh";
    slam_process->setWorkingDirectory(QDir::homePath()+"/RB_MOBILE/sh");
    slam_process->start(file);
    slam_process->waitForReadyRead(3000);
    ipc->update();
    plog->write("[SUPERVISOR] RESTART SLAM -> START SLAM "+QString::number(slam_process->pid()));
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
void Supervisor::startDrawingObject(){
    plog->write("[COMMAND] Start Drawing Object");
    ipc->startObject();
}

void Supervisor::stopDrawingObject(){
    plog->write("[COMMAND] Stop Drawing Object");
    ipc->stopObject();
}

void Supervisor::saveDrawingObject(){
    plog->write("[COMMAND] Save Drawing Object");
    ipc->saveObject();
}

void Supervisor::stopMapping(){
    plog->write("[USER INPUT] STOP MAPPING");
    ipc->flag_mapping = false;
    ipc->is_mapping = false;
    ipc->stopMapping();
    readSetting(getMapname());
//    maph->loadFile(getMapname(),"");
}
void Supervisor::saveMapping(QString name){
    if(probot->ipc_use){
        ipc->flag_mapping = false;
        ipc->is_mapping = false;
        ipc->saveMapping(name);
    }
}
void Supervisor::setSLAMMode(int mode){

}
void Supervisor::setInitCurPos(){
    pmap->init_pose = probot->curPose;
    plog->write("[LOCALIZATION] SET INIT POSE : "+QString().sprintf("%f, %f, %f",pmap->init_pose.point.x, pmap->init_pose.point.y, pmap->init_pose.angle));
}

void Supervisor::setInitPos(int x, int y, float th){
    qDebug() << "INIT" << x << y << setAxisBack(cv::Point2f(x,y)).x << setAxisBack(cv::Point2f(x,y)).y;
    pmap->init_pose.point = setAxisBack(cv::Point2f(x,y));
    pmap->init_pose.angle = setAxisBack(th);
    plog->write("[LOCALIZATION] SET INIT POSE : "+QString().sprintf("%f, %f, %f",pmap->init_pose.point.x, pmap->init_pose.point.y, pmap->init_pose.angle));
}
float Supervisor::getInitPoseX(){
    cv::Point2f temp = setAxis(pmap->init_pose.point);
    return temp.x;
}
float Supervisor::getInitPoseY(){
    cv::Point2f temp = setAxis(pmap->init_pose.point);
    return temp.y;
}
float Supervisor::getInitPoseTH(){
    return setAxis(pmap->init_pose.angle);
}
void Supervisor::slam_setInit(){
    plog->write("[SLAM] SLAM SET INIT : "+QString().sprintf("%f, %f, %f",pmap->init_pose.point.x,pmap->init_pose.point.y,pmap->init_pose.angle));
//    if(probot->localization_confirm == LOCAL_READY){
//        ui_state = UI_STATE_INITAILIZING;
//        probot->localization_confirm = 0;
//        probot->localization_state = 0;
//    }
    if(probot->ipc_use){
        ipc->setInitPose(pmap->init_pose.point.x, pmap->init_pose.point.y, pmap->init_pose.angle);
    }
}
void Supervisor::slam_run(){
    if(probot->ipc_use){
        ipc->set_cmd(ROBOT_CMD_SLAM_RUN, "LOCALIZATION RUN");
    }
}
void Supervisor::slam_stop(){
    if(probot->ipc_use){
        ipc->set_cmd(ROBOT_CMD_SLAM_STOP, "LOCALIZATION STOP");
    }
}
void Supervisor::slam_autoInit(){
    plog->write("[LOCALIZATION] AUTO INIT : "+QString::number(pmap->map_rotate_angle));
    ipc->set_cmd(ROBOT_CMD_SLAM_AUTO, "LOCALIZATION AUTO INIT");

}
void Supervisor::slam_fullautoInit(){
    if(probot->ipc_use){
        plog->write("[LOCALIZATION] FULL AUTO INIT : "+QString::number(pmap->map_rotate_angle));
        ipc->set_cmd(ROBOT_CMD_SLAM_FULL_AUTO, "LOCALIZATION FULL AUTO INIT");
    }
}
bool Supervisor::is_slam_running(){
    if(probot->localization_state == LOCAL_READY){
        return true;
    }else{
        return false;
    }
}
bool Supervisor::getMappingflag(){
    if(probot->ipc_use){
        return ipc->flag_mapping;
    }
}


bool Supervisor::getObjectingflag(){
    return ipc->flag_objecting;
}

void Supervisor::setObjectingflag(bool flag){
    ipc->flag_objecting = flag;
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

void Supervisor::updateUSB(){
    QString updatestr = QDir::homePath()+"/RB_MOBILE/sh/updateusb.sh";
    if(!QFile::exists(updatestr)){
        makeUSBShell();;
    }
    updatestr = QDir::homePath()+"/RB_MOBILE/sh/updatedummy.sh";
    if(!QFile::exists(updatestr)){
        QString file_name = QDir::homePath() + "/RB_MOBILE/sh/updatedummy.sh";
        QFile file(file_name);
        if(file.open(QIODevice::ReadWrite)){
            QTextStream stream(&file);
            stream << "#!/bin/bash" << endl << endl;

            stream << "/home/odroid/RB_MOBILE/sh/updateusb.sh" << endl;
        }
        file.close();
        //Chmod
        QProcess process;
        process.setWorkingDirectory(QDir::homePath()+"/RB_MOBILE/sh");
        process.start("chmod +x updatedummy.sh");
        process.waitForReadyRead(200);
    }
    QProcess process;
    process.setWorkingDirectory(QDir::homePath()+"/RB_MOBILE/sh");
    process.start("xterm ./updatedummy.sh");
    process.waitForReadyRead(3000);
}

void Supervisor::makeExtProcessShell(){
    QString file_name = QDir::homePath() + "/RB_MOBILE/sh/startextproc.sh";
    QFile file(file_name);
    if(file.open(QIODevice::ReadWrite)){
        QTextStream stream(&file);
        stream << "#!/bin/bash" << endl << endl;
        stream << "while [ 1 ]"<<endl;
        stream << "do"<<endl;
        stream << "     pid=`ps -ef | grep \"ExtProcess\" | grep -v 'grep' | awk '{print $2}'`"<<endl;
        stream << "     if [ -z $pid ]" << endl;
        stream << "     then" << endl;
        stream << "         /home/odroid/RB_MOBILE/release/ExtProcess" << endl;
        stream << "     else" << endl;
        stream << "         kill -9 $pid" << endl;
        stream << "         /home/odroid/RB_MOBILE/release/ExtProcess" << endl;
        stream << "     fi" << endl;
        stream << "done" << endl;
    }
    file.close();
    //Chmod
    QProcess process;
    process.setWorkingDirectory(QDir::homePath()+"/RB_MOBILE/sh");
    process.start("chmod +x startextproc.sh");
    process.waitForReadyRead(200);

}
void Supervisor::makeUSBShell(){
//    QString file_name = QDir::homePath() + "/RB_MOBILE/sh/updateusb.sh";
//    QFile file(file_name);
//    if(file.open(QIODevice::ReadWrite)){
//        QTextStream stream(&file);
//        stream << "#!/bin/bash" << endl << endl;
//        stream << "cd /home/odroid/RB_MOBILE" << endl;

//        stream << "if [ -d \"config\" ]" << endl;
//        stream << "then" << endl;
//        stream << "    cp config/robot_config.ini /home/odroid/RB_MOBILE/config/robot_config.ini" << endl;
//        stream << "fi" << endl;

//        stream << "if [ -d \"sn_log\" ]" << endl;
//        stream << "then" << endl;
//        stream << "    cp -R sn_log /home/odroid/" << endl;
//        stream << "fi" << endl;

//        stream << "if [ -d \"ui_log\" ]" << endl;
//        stream << "then" << endl;
//        stream << "    cp -R ui_log /home/odroid/" << endl;
//        stream << "fi" << endl;

//        stream << "if [ -d \"maps\" ]" << endl;
//        stream << "then" << endl;
//        stream << "    cp -R maps /home/odroid/" << endl;
//        stream << "fi" << endl;

//        stream << "if [ -d \"SLAMNAV\" ]" << endl;
//        stream << "then" << endl;
//        stream << "    cp -R SLAMNAV /home/odroid/code/" << endl;
//        stream << "fi" << endl;

//        stream << "if [ -d \"build-SLAMNAV-Desktop-Release\" ]" << endl;
//        stream << "then" << endl;
//        stream << "    cp -R SLAMNAV_release /home/odroid/code/" << endl;
//        stream << "fi" << endl;

//        stream << "if [ -d \"build-SLAMNAV-Desktop-Debug\" ]" << endl;
//        stream << "then" << endl;
//        stream << "    cp -R build-SLAMNAV-Desktop-Debug /home/odroid/code/" << endl;
//        stream << "fi" << endl;

//        stream << "if [ -d \"UI_MOBILE_release\" ]" << endl;
//        stream << "then" << endl;
//        stream << "    cp -R UI_MOBILE_release /home/odroid/" << endl;
//        stream << "fi" << endl;

//        stream << "cd /home/odroid" << endl;
//        stream << "rm -R tempBackup" << endl;
//        stream << "rm tempBackup.zip" << endl;

//        stream << "/home/odroid/auto_kill.sh" << endl;
//        stream << "/home/odroid/UI_MOBILE_release/autostart.sh" << endl;
//    }
//    file.close();
//    //Chmod
//    QProcess process;
//    process.setWorkingDirectory(QDir::homePath()+"/RB_MOBILE/sh");
//    process.start("chmod +x updateusb.sh");
//    process.waitForReadyRead(200);
}

////*********************************************  ANNOTATION 관련   ***************************************************////
void Supervisor::setObjPose(){
    pmap->list_obj_dR.clear();
    pmap->list_obj_uL.clear();
    for(int i=0; i<pmap->objects.size(); i++){
        cv::Point2f temp_uL;
        cv::Point2f temp_dR;
        //Find Square Pos
        temp_uL.x = pmap->objects[i].points[0].x;
        temp_uL.y = pmap->objects[i].points[0].y;
        temp_dR.x = pmap->objects[i].points[0].x;
        temp_dR.y = pmap->objects[i].points[0].y;
        for(int j=1; j<pmap->objects[i].points.size(); j++){
            if(temp_uL.x > pmap->objects[i].points[j].x){
                temp_uL.x = pmap->objects[i].points[j].x;
            }
            if(temp_uL.y > pmap->objects[i].points[j].y){
                temp_uL.y = pmap->objects[i].points[j].y;
            }
            if(temp_dR.x < pmap->objects[i].points[j].x){
                temp_dR.x = pmap->objects[i].points[j].x;
            }
            if(temp_dR.y < pmap->objects[i].points[j].y){
                temp_dR.y = pmap->objects[i].points[j].y;
            }
        }
        pmap->list_obj_dR.push_back(temp_uL);
        pmap->list_obj_uL.push_back(temp_dR);
    }
}

/////Location
QString Supervisor::getServingName(int group, int num){
    int count = 0;
    for(int i=0; i<pmap->locations.size(); i++){
        if(pmap->locations[i].type == "Serving"){
            if(pmap->locations[i].group == group){
                if(count == num)
                    return pmap->locations[i].name;
                count++;
            }
        }
    }
    return "설정 안됨";
}
int Supervisor::getLocationNum(QString type){
    if(type==""){
        return pmap->locations.size();
    }else{
        int count = 0;
        for(int i=0; i<pmap->locations.size(); i++){
            if(pmap->locations[i].type == type){
                count++;
            }
        }
        return count;
    }
}
int Supervisor::getLocationGroupNum(int num){
    int count = 0;
    for(int i=0; i<pmap->locations.size(); i++){
        if(pmap->locations[i].type == "Serving"){
            if(count == num){
                if(pmap->location_groups.size() > pmap->locations[i].group)
                    return pmap->locations[i].group;
                else
                    return 0;
            }
            count++;
        }
    }
    return 0;
}
QString Supervisor::getLocationCallID(int num){
    int count = 0;
    if(num>-1 && num < pmap->locations.size()){
        return pmap->locations[num].call_id;
    }
    return "";
//    for(int i=0; i<pmap->locations.size(); i++){
//        if(pmap->locations[i].type == type){
//            if(count == num){
//                qDebug() << "callid " << type << num << i << pmap->locations[i].call_id;
//                return pmap->locations[i].call_id;
//            }
//            count++;
//        }
//    }
//    return "";
}
void Supervisor::setLocationGroup(int num, int group){
    if(num > -1 && num < pmap->locations.size()){
        pmap->locations[num].group = group;
        plog->write("[ANNOTATION] SET Location Group "+QString().sprintf("%d : %d",num,group));
    }
}
QString Supervisor::getLocationGroup(int num){
    int count = 0;
    for(int i=0; i<pmap->locations.size(); i++){
        if(pmap->locations[i].type == "Serving"){
            if(count == num){
                if(pmap->location_groups.size() > pmap->locations[i].group)
                    return pmap->location_groups[pmap->locations[i].group];
                else
                    return "(-)";
            }
            count++;
        }
    }
    return "(  )";

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
void Supervisor::selectLocation(int num){
    maph->setSelectLocation(num);
}
void Supervisor::setLocationUp(int num){
    if(num>2 && num<pmap->locations.size()){
        plog->write("[ANNOTATION] Location "+QString::number(num)+"("+pmap->locations[num].name+") Up");
        pmap->locations.move(num,num-1);
    }
}
void Supervisor::setLocationDown(int num){
    if(num>1 && num<pmap->locations.size()-1){
        plog->write("[ANNOTATION] Location "+QString::number(num)+"("+pmap->locations[num].name+") Down");
        pmap->locations.move(num,num+1);
    }

}
int Supervisor::getLocationGroupSize(int num){
    int size = 0;
    if(num > -1 && num < pmap->location_groups.size()){
        for(int i=0; i<pmap->locations.size(); i++){
            if(pmap->locations[i].type == "Serving")
                if(pmap->locations[i].group == num)
                    size++;
        }
    }
//    qDebug() << "location group size " << num << size << pmap->locations.size();
    return size;
}
QString Supervisor::getLocationName(int num, QString type){
    if(type == ""){
        if(num > -1 && num < pmap->locations.size()){
            return pmap->locations[num].name;
        }
        return "";
    }else{
        int count = 0;
        for(int i=0; i<pmap->locations.size(); i++){
            if(pmap->locations[i].type == type){
                if(count == num)
                    return pmap->locations[i].name;
                count++;
            }
        }
        return "설정 안됨";
    }
}
QString Supervisor::getLocationType(int num){
    if(num > -1 && num < pmap->locations.size()){
        return pmap->locations[num].type;
    }
    return "";
}
float Supervisor::getLocationX(int num, QString type){
    if(type == ""){
        if(num > -1 && num < pmap->locations.size()){
            return setAxis(pmap->locations[num].point).x;
        }
        return 0.;
    }else{
        int count = 0;
        for(int i=0; i<pmap->locations.size(); i++){
            if(pmap->locations[i].type == type){
                if(count == num){
                    return setAxis(pmap->locations[i].point).x;
                }
                count++;
            }
        }
        return 0.;
    }
}

int Supervisor::getLocationID(int group, int num){

//    if(num > -1 && num < pmap->locations.size()){
//        int count = 0;
//        for(int i=0; i<pmap->locations.size(); i++){
//            if(pmap->locations[i].type == "Serving"){
//                if(group == -1){
//                    if(count == num){
////                        qDebug() << num << i << " get number is " << pmap->locations[i].number;
//                        return pmap->locations[i].loc_id;
//                    }
//                    count++;
//                }else if(pmap->locations[i].group == group){
//                    if(count == num){
////                        qDebug() << num << i << " get number is " << pmap->locations[i].number;
//                        return pmap->locations[i].loc_id;
//                    }
//                    count++;
//                }
//            }
//        }
//    }
    return -1;
}

int Supervisor::getLocationNumber(int group, int num){
//    if(num > -1 && num < pmap->locations.size()){
//        int count = 0;
//        for(int i=0; i<pmap->locations.size(); i++){
//            if(pmap->locations[i].type == "Serving"){
//                if(group == -1){
//                    if(count == num){
////                        qDebug() << num << i << " get number is " << pmap->locations[i].number;
//                        return pmap->locations[i].number;
//                    }
//                    count++;
//                }else if(pmap->locations[i].group == group){
//                    if(count == num){
////                        qDebug() << num << i << " get number is " << pmap->locations[i].number;
//                        return pmap->locations[i].number;
//                    }
//                    count++;
//                }
//            }
//        }
//    }
    return -1;
}
void Supervisor::setLocation(int num, QString name, int group, int tablenum){
    if(num > -1 && num < pmap->locations.size()){
        int count = 0;
        for(int i=0; i<pmap->locations.size(); i++){
            if(pmap->locations[i].type == "Serving"){
                if(num==count){
                    pmap->locations[i].name = name;
                    pmap->locations[i].group = group;
//                    pmap->locations[i].number = tablenum;
                    pmap->annot_edit_location = true;
                    plog->write("[SUPERVISOR] SET LOCATION : "+QString().sprintf("(%d) group : %d, number : %d, name : ",num,group,tablenum)+name);
                }
                count++;
            }
        }
    }
}
QString Supervisor::getLocGroupname(int num){
    if(num > -1 && num <pmap->location_groups.size()){
        return pmap->location_groups[num];
    }
    return " - ";
}
void Supervisor::setLocationNumber(QString name, int num){
    for(int i=0; i<pmap->locations.size(); i++){
        if(pmap->locations[i].name == name){
            plog->write("[SUPERVISOR] SET LOCATION NUMBER "+name+" TO "+QString::number(num));
//            pmap->locations[i].number = num;
        }
    }
}
float Supervisor::getLocationY(int num, QString type){
    if(type == ""){
        if(num > -1 && num < pmap->locations.size()){
            return setAxis(pmap->locations[num].point).y;
        }
        return 0.;
    }else{
        int count = 0;
        for(int i=0; i<pmap->locations.size(); i++){
            if(pmap->locations[i].type == type){
                if(count == num){
                    return setAxis(pmap->locations[i].point).y;
                }
                count++;
            }
        }
        return 0.;
    }
}
float Supervisor::getLocationTH(int num, QString type){
    if(type == ""){
        if(num > -1 && num < pmap->locations.size()){
            return setAxis(pmap->locations[num].angle);
        }
        return 0.;
    }else{
        int count = 0;
        for(int i=0; i<pmap->locations.size(); i++){
            if(pmap->locations[i].type == type){
                if(count == num){
                    return setAxis(pmap->locations[i].angle);
                }
                count++;
            }
        }
        return 0.;
    }
}
int Supervisor::getLocationSize(QString type){
    int count = 0;
    for(int i=0; i<pmap->locations.size(); i++){
        if(pmap->locations[i].type == type){
            QStringList namelist = pmap->locations[i].name.split("_");
            if(namelist[0] == type && namelist.size() >1){
                if(namelist[1].toInt() > count){
                    count = namelist[1].toInt();
                }
            }
        }
    }
    return count + 1;
}

bool Supervisor::isExistLocation(int group, int num){
    int count = 0;
    if(pmap->locations.size() == 0){
        return false;
    }else{
        for(int i=0; i<pmap->locations.size(); i++){
            if(pmap->locations[i].type == "Serving"){
                if(group == pmap->locations[i].group || group == -1){
                    if(count == num){
                        return true;
                    }
                    count++;
                }
            }
        }
        return false;
    }
}
float Supervisor::getLidar(int num){
    return probot->lidar_data[num];
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
    float grid = pmap->mapping_gridwidth*pmap->mapping_width/1000;
    temp.x = -_point.y/grid + 1000/2;
    temp.y = -_point.x/grid + 1000/2;
    return temp;
}
cv::Point2f setAxisObject(cv::Point2f _point){
    cv::Point2f temp;
    float grid = pmap->gridwidth*pmap->width/1000;
    temp.x = -_point.y/grid + 1000/2;
    temp.y = -_point.x/grid + 1000/2;
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

int Supervisor::getLocNum(QString name){
    for(int i=0; i<pmap->locations.size(); i++){
        if(pmap->locations[i].name == name){
            return i;
        }
    }
    return -1;
}
int Supervisor::getLocNum(int x, int y){
    for(int i=0; i<pmap->locations.size(); i++){
        cv::Point2f pos = setAxisBack(cv::Point2f(x,y));
        if(fabs(pmap->locations[i].point.x - pos.x) < probot->radius){
            if(fabs(pmap->locations[i].point.y - pos.y) < probot->radius){
                return i;
            }
        }
    }
    return -1;
}

void Supervisor::removeLocation(int num){
    if(num>1 && num<pmap->locations.size()){
        plog->write("[UI-MAP] REMOVE LOCATION "+ num);
        pmap->locations.removeAt(num);
        pmap->annotation_edited = true;
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
        pmap->objects.remove(num);
        setObjPose();
        pmap->annotation_edited = true;
        maph->clearObject();
        QMetaObject::invokeMethod(mMain, "updateobject");
        plog->write("[ANNOTATION - ERROR] removeObject " + QString().sprintf("(%d)",num));
    }else{
        plog->write("[ANNOTATION - ERROR] removeObject " + QString().sprintf("(%d)",num) + " but size error");
    }
}

bool Supervisor::isOdroid(){
    if(QDir::homePath().split("/")[2]=="odroid"){
        return true;
    }else{
        return false;
    }
}
bool Supervisor::saveAnnotation(QString filename){
    plog->write("[SUPERVISOR] SAVE Annotation "+filename);
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

    qDebug() << getMapname() << getAnnotPath(filename);
    //데이터 입력(로케이션)
    int other_num = 0;
    int resting_num = 0;
    int charging_num = 0;
    int serving_num = 0;
    int cleaning_num = 0;
    int group_num[pmap->location_groups.size()];
    for(int i=0; i<pmap->location_groups.size(); i++)
        group_num[i] = 0;

    QString str_name;
    QSettings settings(getAnnotPath(filename), QSettings::IniFormat);
    settings.clear();
    int id_num = 0;

    //name,x,y,th,num,locnum,callid
    for(int i=0; i<pmap->locations.size(); i++){
        if(pmap->locations[i].type == "Charging"){
            str_name = pmap->locations[i].name + QString().sprintf(",%f,%f,%f",pmap->locations[i].point.x,pmap->locations[i].point.y,pmap->locations[i].angle)+","+pmap->locations[i].call_id;
            settings.setValue("charging_locations/loc"+QString::number(charging_num),str_name);
            charging_num++;
        }else if(pmap->locations[i].type == "Resting"){
            str_name = pmap->locations[i].name + QString().sprintf(",%f,%f,%f",pmap->locations[i].point.x,pmap->locations[i].point.y,pmap->locations[i].angle)+","+pmap->locations[i].call_id;
            settings.setValue("resting_locations/loc"+QString::number(resting_num),str_name);
            resting_num++;
        }else if(pmap->locations[i].type == "Cleaning"){
            str_name = pmap->locations[i].name + QString().sprintf(",%f,%f,%f",pmap->locations[i].point.x,pmap->locations[i].point.y,pmap->locations[i].angle)+","+pmap->locations[i].call_id;
            settings.setValue("cleaning_locations/loc"+QString::number(cleaning_num),str_name);
            cleaning_num++;
        }else if(pmap->locations[i].type == "Serving"){
            QString groupname = "serving_" + QString::number(pmap->locations[i].group);
            str_name = pmap->locations[i].name + QString().sprintf(",%f,%f,%f",pmap->locations[i].point.x,pmap->locations[i].point.y,pmap->locations[i].angle)+","+pmap->locations[i].call_id;
            settings.setValue(groupname+"/loc"+QString::number(group_num[pmap->locations[i].group]),str_name);
            group_num[pmap->locations[i].group]++;
        }
    }
    settings.setValue("cleaning_locations/num",cleaning_num);
    settings.setValue("resting_locations/num",resting_num);
    settings.setValue("serving_locations/group",pmap->location_groups.size());
    settings.setValue("other_locations/num",other_num);
    settings.setValue("charging_locations/num",charging_num);

    for(int i=0; i<pmap->location_groups.size(); i++){
        settings.setValue("serving_"+QString::number(i)+"/name",pmap->location_groups[i]);
        settings.setValue("serving_"+QString::number(i)+"/num",getLocationGroupSize(i));
    }

    for(int i=0; i<pmap->objects.size(); i++){
        QString str = "Object_"+QString::number(i);

        if(pmap->objects[i].is_rect){
            str += ",1";
        }else{
            str += ",0";
        }

        for(int j=0; j<pmap->objects[i].points.size(); j++){
            str += QString().sprintf(",%f:%f",pmap->objects[i].points[j].x,pmap->objects[i].points[j].y);

        }
        settings.setValue("objects/poly"+QString::number(i),str);
    }
    settings.setValue("objects/num",pmap->objects.size());

    readSetting(filename);
    pmap->annotation_edited = false;
    return true;
}



////*********************************************  SCHEDULER(CALLING) 관련   ***************************************************////
void Supervisor::acceptCall(bool yes){

}

////*********************************************  SCHEDULER(SERVING) 관련   ***************************************************////
void Supervisor::setTray(int tray_num, int group, int table){
    if(ui_state == UI_STATE_RESTING){
        if(tray_num > -1 && tray_num < probot->trays.size()){
            probot->trays[tray_num].empty = false;
            probot->trays[tray_num].location = getLocation(group,getServingName(group,table));
            plog->write("[COMMAND] Set Tray : "+QString::number(tray_num)+" , "+getServingName(group,table));
        }
    }
}

void Supervisor::startServing(){
    if(ui_state == UI_STATE_RESTING|| ui_state == UI_STATE_CLEANING){
        QString tray_str = "";
        for(int i = 0; i<probot->trays.size(); i++){
            if(!probot->trays[i].empty){
                plog->write("[COMMAND] START Serving ");
                ui_state = UI_STATE_MOVING;
                return;
            }
        }
        plog->write("[COMMAND] START Serving (tray empty)");
    }else{
        plog->write("[COMMAND] START Serving (State not ready) : "+QString::number(ui_state));
    }
}
void Supervisor::setPreset(int preset){
    plog->write("[COMMAND] SET PRESET : "+QString::number(preset));
    probot->cur_preset = preset;
    setSetting("update","DRIVING/cur_preset",QString::number(preset));
}
void Supervisor::confirmPickup(){
    if(ui_state == UI_STATE_PICKUP){
        plog->write("[COMMAND] Pickup Confirm : (ui_state = MOVING)");
        ui_state = UI_STATE_MOVING;
    }else{
        plog->write("[COMMAND] Pickup Confirm (ui_state "+QString::number(ui_state)+")");
    }
}
QVector<int> Supervisor::getPickuptrays(){
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
void Supervisor::clearFlagStop(){

}
void Supervisor::moveStopFlag(){
    patrol_mode = PATROL_NONE;
    plog->write("[COMMAND] Move Stop Flag");
    probot->is_patrol = false;
    call_queue.clear();
//    ui_state = UI_STATE_NONE;
    QMetaObject::invokeMethod(mMain, "movestopped");
}

void Supervisor::moveStop(){
    patrol_mode = PATROL_NONE;
    plog->write("[COMMAND] Move Stop");
    ipc->moveStop();
    probot->is_patrol = false;
    call_queue.clear();
    ui_state = UI_STATE_NONE;
    QMetaObject::invokeMethod(mMain, "movestopped");
}

void Supervisor::moveToCharge(){
    if(ui_state == UI_STATE_RESTING || ui_state == UI_STATE_MOVEFAIL|| ui_state == UI_STATE_CLEANING){
        plog->write("[COMMAND] Move to Charging");
        current_target = getLocation(0, "Charging0");
        ui_state = UI_STATE_MOVING;
        is_test_moving = false;
    }else{
        is_test_moving = false;
        QMetaObject::invokeMethod(mMain,"movefail");
        plog->write("[COMMAND] Move to Charging (State busy "+QString::number(ui_state)+")");
    }
}
void Supervisor::moveToWait(){
    if(ui_state == UI_STATE_RESTING|| ui_state == UI_STATE_MOVEFAIL || ui_state == UI_STATE_CLEANING){
        plog->write("[COMMAND] Move to Resting");
        current_target = getLocation(0, "Resting0");
        ui_state = UI_STATE_MOVING;
        is_test_moving = false;
    }else{
        is_test_moving = false;
        QMetaObject::invokeMethod(mMain,"movefail");
        plog->write("[COMMAND] Move to Resting (State busy "+QString::number(ui_state)+")");
    }
}
QString Supervisor::getcurLoc(){
    return probot->curLocation.name;
}
QString Supervisor::getcurTable(){
    for(int i=0; i<pmap->locations.size(); i++){
        if(pmap->locations[i].name == probot->curLocation.name)
            return "";//QString::number(pmap->locations[i].number);
    }
    return "-";
}
int Supervisor::getMultiState(){

}
void Supervisor::resetHomeFolders(){
    plog->write("[USER INPUT] RESET HOME FOLDERS");

//    QDir lcm_orin(QGuiApplication::applicationDirPath() + "/lcm_types");
//    QDir lcm_target(QDir::homePath() + "/lcm_types");

//    qDebug() <<QGuiApplication::applicationDirPath() + "/lcm_types";
//    qDebug() <<QDir::homePath() + "/lcm_types";
//    if(lcm_orin.exists()){
//        if(!lcm_target.exists()){
//            plog->write("[SUPERVISOR] MAKE LCM_TYPES FOLDER INTO HOME");
//            lcm_target.mkpath(".");
//        }

//        QStringList files = lcm_orin.entryList(QDir::Files);
//        for(int i=0; i<files.count(); i++){
//            qDebug() << QGuiApplication::applicationDirPath() + "/lcm_types/" + files[i];
//            qDebug() << QDir::homePath() + "/lcm_types/" + files[i];
//            QFile::copy(QGuiApplication::applicationDirPath() + "/lcm_types/" + files[i],
//                        QDir::homePath() + "/lcm_types/" + files[i]);
//            plog->write("[SUPERVISOR] COPY LCM_TYPES : " + files[i]);
//        }
//        files.clear();
//    }
}
bool Supervisor::issetLocation(int number){
//    for(int i=0; i<pmap->locations.size(); i++){
//        if(pmap->locations[i].number == number)
//            return true;
//    }
    return false;
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
    if(probot->motor[id].status == 0){
        return " ";
    }else{
        QString str = "";
        if(MOTOR_RUN(probot->motor[id].status) == 1)
            str += "RUN";

        if(MOTOR_MOD_ERROR(probot->motor[id].status) == 1)
            str += " MOD";

        if(MOTOR_JAM_ERROR(probot->motor[id].status) == 1)
            str += " JAM";

        if(MOTOR_CUR_ERROR(probot->motor[id].status) == 1)
            str += " CUR";

        if(MOTOR_BIG_ERROR(probot->motor[id].status) == 1)
            str += " BIG";

        if(MOTOR_INP_ERROR(probot->motor[id].status) == 1)
            str += " INP";

        if(MOTOR_PS_ERROR(probot->motor[id].status) == 1)
            str += " PS";

        if(MOTOR_COL_ERROR(probot->motor[id].status) == 1)
            str += " COL";

        return str;
    }
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
    if(onoff){
        plog->write("[COMMAND] SET MOTOR LOCK : ON");
        ipc->set_cmd(ROBOT_CMD_MOTOR_LOCK_ON,"ROBOT_CMD_MOTOR_LOCK_ON");
    }else{
        plog->write("[COMMAND] SET MOTOR LOCK : OFF");
        ipc->set_cmd(ROBOT_CMD_MOTOR_LOCK_OFF,"ROBOT_CMD_MOTOR_LOCK_OFF");
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
int Supervisor::getErrcode(){
    return probot->err_code;
}
QString Supervisor::getRobotName(){
    if(is_debug){
        return robot.name + "_" + robot.name_debug;
    }else{
        return robot.name;
    }
}
float Supervisor::getRobotRadius(){
    return probot->radius;
}
float Supervisor::getRobotx(){
    POSE temp = setAxis(probot->curPose);
    return temp.point.x;
}
float Supervisor::getRoboty(){
    POSE temp = setAxis(probot->curPose);
    return temp.point.y;
}
float Supervisor::getRobotth(){
    POSE temp = setAxis(probot->curPose);
    return temp.angle;
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
int Supervisor::getPathNum(){
    if(ipc->flag_path){
        return 0;
    }else{
        return probot->pathSize;
    }
}
float Supervisor::getPathx(int num){
    if(ipc->flag_path ){
        return 0;
    }else{
        POSE temp = setAxis(probot->curPath[num]);
        return temp.point.x;
    }
}
float Supervisor::getPathy(int num){
    if(ipc->flag_path){
        return 0;
    }else{
        POSE temp = setAxis(probot->curPath[num]);
        return temp.point.y;
    }
}
float Supervisor::getPathth(int num){
    if(ipc->flag_path){
        return 0;
    }else{
        POSE temp = setAxis(probot->curPath[num]);
        return temp.angle;
    }
}
int Supervisor::getLocalPathNum(){
    return probot->localpathSize;

}
float Supervisor::getLocalPathx(int num){
    POSE temp = setAxis(probot->localPath[num]);
    return temp.point.x;

}
float Supervisor::getLocalPathy(int num){
    POSE temp = setAxis(probot->localPath[num]);
    return temp.point.y;
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
QVector<int> Supervisor::getOrigin(){
    QVector<int> temp;
    temp.push_back(pmap->origin[0]);
    temp.push_back(pmap->origin[1]);
    return temp;
}

void Supervisor::moveToServingTest(int group, QString name){
    if(ui_state == UI_STATE_RESTING || ui_state == UI_STATE_MOVEFAIL || ui_state == UI_STATE_PICKUP|| ui_state == UI_STATE_CLEANING){
        if(name.left(8) == "Charging" || name == tr("충전위치")){
            current_target = getLocation(0, "Charging0");
            ui_state = UI_STATE_MOVING;
            is_test_moving = true;
            plog->write("[COMMAND] Serving Test : "+name);
        }else if(name.left(7) == "Resting"|| name == tr("대기위치")){
            current_target = getLocation(0, "Resting0");
            ui_state = UI_STATE_MOVING;
            is_test_moving = true;
            plog->write("[COMMAND] Serving Test : "+name);
        }else if(name.left(8) == "Cleaning"|| name == tr("퇴식위치")){
            current_target = getLocation(0, "Cleaning0");
            ui_state = UI_STATE_MOVING;
            is_test_moving = true;
            plog->write("[COMMAND] Serving Test : "+name);
        }else if(probot->trays[0].empty){
            LOCATION temp_loc = getLocation(group, name);
            if(temp_loc.name == ""){
                plog->write("[COMMAND] Serving Test (Not found) : "+name);
                is_test_moving = false;
            }else{
                probot->trays[0].empty = false;
                probot->trays[0].location = temp_loc;
                ui_state = UI_STATE_MOVING;
                is_test_moving = true;
                plog->write("[COMMAND] Serving Test : "+name);
            }
        }else{
            is_test_moving = false;
            plog->write("[COMMAND] Serving Test (Already Moving) : "+name+" (cur target is "+probot->trays[0].location.name+")");
        }
    }else{
        is_test_moving = false;
        QMetaObject::invokeMethod(mMain,"movefail");
        plog->write("[COMMAND] Serving Test (state busy) : "+name+" ("+QString::number(ui_state)+")");
    }
}
void Supervisor::clearRotateList(){
    plog->write("[SUPERVISOR] Clear Patrol List : "+QString::number(patrol_list.size()));
    patrol_list.clear();
}
void Supervisor::setRotateList(QString name){
    patrol_list.append(name);
    plog->write("[SUPERVISOR] Set Patrol List : "+name + " (size = "+QString::number(patrol_list.size())+")");
}
void Supervisor::startPatrol(QString mode, bool pickup){
    use_patrol_pickup = pickup;
    QString pickstr = pickup?"true":"false";
    if(patrol_list.size() > 1){
        if(mode == "random"){
            plog->write("[COMMAND] Start Patrol (Random) : "+QString::number(patrol_list.size())+" (pickup "+pickstr+")");
            ui_state = UI_STATE_MOVING;
            patrol_mode = PATROL_RANDOM;
        }else if(mode == "sequence"){
            plog->write("[COMMAND] Start Patrol (Sequence) : "+QString::number(patrol_list.size())+" (pickup "+pickstr+")");
            ui_state = UI_STATE_MOVING;
            patrol_mode = PATROL_SEQUENCE;
        }
    }else{
        plog->write("[COMMAND] Start Patrol (List Empty)");
    }
}

//// *********************************** SLOTS *********************************** ////
void Supervisor::path_changed(){
    maph->setMap();
//    QMetaObject::invokeMethod(mMain, "updatepath");
}
void Supervisor::camera_update(){
//    maph->setMap();
    QMetaObject::invokeMethod(mMain, "updatecamera");
}
void Supervisor::mapping_update(){
    maph->setMap();
//    QMetaObject::invokeMethod(mMain, "updatemapping");
}

void Supervisor::checkShellFiles(){
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

    file_path = QDir::homePath() + "/RB_MOBILE/sh/startextproc.sh";
    if(!QFile::exists(file_path)){
        plog->write("[SUPERVISOR] startextproc.sh not found. make new");
        makeExtProcessShell();
    }

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
void Supervisor::makeKillShell(){
    //Make kill_slam.sh
    QString file_name = QDir::homePath() + "/RB_MOBILE/sh/restartslam.sh";
    QFile file(file_name);
    if(file.open(QIODevice::ReadWrite)){
        QTextStream stream(&file);
        stream << "#!/bin/bash" << endl << endl;
        stream << "pid=`ps -ef | grep \"SLAMNAV\" | grep -v 'grep' | awk '{print $2}'`"<<endl;
        stream << "if [ -z $pid ]" << endl;
        stream << "then" << endl;
        stream << "     echo \"SLAMNAV is not running\"" << endl;
        stream << "else" << endl;
        stream << "     kill -9 $pid" << endl;
        stream << "fi" << endl;
    }
    file.close();
    //Chmod
    QProcess process;
    process.setWorkingDirectory(QDir::homePath());
    process.start("chmod +x kill_slam.sh");
    process.waitForReadyRead(200);
}
void Supervisor::checkUpdate(){
//    server->checkUpdate();
}
void Supervisor::setLangauge(QString lan){
    plog->write("[SUPERVISOR] SET LANGAUGE : "+lan);
    app->removeTranslator(translator);
    if(lan == "KR"){
    }else if(lan=="US"){
        QString pahhh = QDir::homePath() + "/RB_MOBILE/config/locale/lang_en.qm";
        qDebug() << pahhh << translator->load(pahhh);
        app->installTranslator(translator);
    }
}
bool Supervisor::checkNewUpdateProgram(){
    if(server->update_list.size() > 0){
        return true;
    }else{
        return false;
    }
//    return server->new_update;
}
void Supervisor::makeKillSlam(){
    //Make kill_slam.sh
    QString file_name = QDir::homePath() + "/RB_MOBILE/sh/restartslam.sh";
    QFile file(file_name);
    if(file.open(QIODevice::ReadWrite)){
        QTextStream stream(&file);
        stream << "#!/bin/bash" << endl << endl;
        stream << "pid=`ps -ef | grep \"SLAMNAV\" | grep -v 'grep' | awk '{print $2}'`"<<endl;
        stream << "if [ -z $pid ]" << endl;
        stream << "then" << endl;
        stream << "     echo \"SLAMNAV is not running\"" << endl;
        stream << "else" << endl;
        stream << "     kill -9 $pid" << endl;
        stream << "fi" << endl;
    }
    file.close();
    //Chmod
    QProcess process;
    process.setWorkingDirectory(QDir::homePath()+"/RB_MOBILE/sh");
    process.start("chmod +x restartslam.sh");
    process.waitForReadyRead(200);

}
void Supervisor::makeStartShell(){
    //Make kill_slam.sh
    QString file_name = QDir::homePath() + "/RB_MOBILE/sh/startslam.sh";
    QFile file(file_name);
    if(file.open(QIODevice::ReadWrite)){
        QTextStream stream(&file);
        stream << "#!/bin/bash" << endl << endl;
        stream << "while [ 1 ]"<<endl;
        stream << "do"<<endl;
        stream << "     pid=`ps -ef | grep \"SLAMNAV\" | grep -v 'grep' | awk '{print $2}'`"<<endl;
        stream << "     if [ -z $pid ]" << endl;
        stream << "     then" << endl;
        stream << "         /home/odroid/RB_MOBILE/release/SLAMNAV" << endl;
        stream << "     else" << endl;
        stream << "         kill -9 $pid" << endl;
        stream << "         /home/odroid/RB_MOBILE/release/SLAMNAV" << endl;
        stream << "     fi" << endl;
        stream << "done" << endl;
    }
    file.close();
    //Chmod
    QProcess process;
    process.setWorkingDirectory(QDir::homePath()+"/RB_MOBILE/sh");
    process.start("chmod +x startslam.sh");
    process.waitForReadyRead(200);

}
void Supervisor::makeAllKillShell(){
    //Make kill_slam.sh
    QString file_name = QDir::homePath() + "/killall.sh";
    QFile file(file_name);
    if(file.open(QIODevice::ReadWrite)){
        QTextStream stream(&file);
        stream << "#!/bin/bash" << endl << endl;


        stream << "pid=`ps -ef | grep \"startslam.sh\" | grep -v 'grep' | awk '{print $2}'`"<<endl;
        stream << "if [ -z $pid ]" << endl;
        stream << "then" << endl;
        stream << "     echo \"startslam.sh is not running\"" << endl;
        stream << "else" << endl;
        stream << "     kill -9 $pid" << endl;
        stream << "fi" << endl;

        stream << "pid=`ps -ef | grep \"startextproc.sh\" | grep -v 'grep' | awk '{print $2}'`"<<endl;
        stream << "if [ -z $pid ]" << endl;
        stream << "then" << endl;
        stream << "     echo \"startextproc.sh is not running\"" << endl;
        stream << "else" << endl;
        stream << "     kill -9 $pid" << endl;
        stream << "fi" << endl;


        stream << "pid=`ps -ef | grep \"SLAMNAV\" | grep -v 'grep' | awk '{print $2}'`"<<endl;
        stream << "if [ -z $pid ]" << endl;
        stream << "then" << endl;
        stream << "     echo \"SLAMNAV is not running\"" << endl;
        stream << "else" << endl;
        stream << "     kill -9 $pid" << endl;
        stream << "fi" << endl;

        stream << "pid=`ps -ef | grep \"ExtProcess\" | grep -v 'grep' | awk '{print $2}'`"<<endl;
        stream << "if [ -z $pid ]" << endl;
        stream << "then" << endl;
        stream << "     echo \"ExtProcess is not running\"" << endl;
        stream << "else" << endl;
        stream << "     kill -9 $pid" << endl;
        stream << "fi" << endl;

        stream << "pid=`ps -ef | grep \"MAIN_MOBILE\" | grep -v 'grep' | awk '{print $2}'`"<<endl;
        stream << "if [ -z $pid ]" << endl;
        stream << "then" << endl;
        stream << "     echo \"MAIN_MOBILE is not running\"" << endl;
        stream << "else" << endl;
        stream << "     kill -9 $pid" << endl;
        stream << "fi" << endl;
    }
    file.close();
    //Chmod
    QProcess process;
    process.setWorkingDirectory(QDir::homePath()+"/RB_MOBILE/sh");
    process.start("chmod +x killall.sh");
    process.waitForReadyRead(200);
}

//// *********************************** TIMER *********************************** ////
void Supervisor::onTimer(){
    static bool check_init = true;
    static int count_pass = 0;
    static int prev_state = -1;
    static int prev_running_state = -1;
    static int prev_local_state = -1;
    static int prev_motor_state = -1;

    //init상태 체크 카운트
    static int count_moveto = 0;
    static int wifi_count = 0;
    static int timer_cnt = 0;
    static int current_cnt = 0;
    static bool cmd_accept = false;

    //
    static int count_excuseme = 0;
    static bool flag_excuseme = false;
    static int count_movewait = 0;
    static bool flag_movewait = false;

    // QML 오브젝트 매칭
    if(mMain == nullptr && object != nullptr){
        setObject(object);
        setWindow(qobject_cast<QQuickWindow*>(object));
    }


    //State 강제 변경조건
    if(!ipc->getConnection()){
        //Clear Status
        if(ui_state != UI_STATE_NONE){
            probot->localization_state = 0;
            probot->motor[0].status = 0;
            probot->motor[1].status = 0;
            plog->write("[SUPERVISOR] IPC Disconnected. (ui_state = NONE)");
            ui_state = UI_STATE_NONE;
            QMetaObject::invokeMethod(mMain, "need_init");
        }
    }else{

    }

    //************************** WiFi *********************************//
//    if(wifi_temp_ssd != ""){
//        if(wifi_count++ > 1000/MAIN_THREAD){
//            QMetaObject::invokeMethod(mMain,"checkwifidone");
////            wifi_check_process->close();
//            wifi_temp_ssd = "";
//        }
//    }else{
//        wifi_count = 0;
//    }

//    if(probot->wifi_ssid == ""){
//        probot->wifi_ssid = getSetting("NETWORK","wifi_ssid");
//    }
//    if(extproc->wifi_list_size == 0){
//        getAllWifiList();
//    }else if(probot->cur_ip == ""){// && getWifiConnection("")){
//        getWifiIP();
//    }


    if(probot->localization_state != LOCAL_READY){
        if(probot->localization_confirm == LOCAL_READY){
            plog->write("[SETTING] Localization Confirm to 0");
        }
        probot->localization_confirm = 0;
    }

//    qDebug() << ui_state << probot->localization_confirm << getMotorState();

    switch(ui_state){
    case UI_STATE_NONE:{
        //State : None
        //Robot 연결 안됨, 초기화 시작 전(프로그램 실행직후)
        //변수 초기화, SharedMemory 초기화
        if(ipc->getConnection()){
            ipc->moveStop();
            current_target.name = "";
            check_init = true;
            ui_state = UI_STATE_INITAILIZING;
            plog->write("[SUPERVISOR] NONE -> Connection check done -> Initailizing");
        }
        cmd_accept = false;
        break;
    }
    case UI_STATE_INITAILIZING:{
        //State : Initializing
        //프로그램 루프 재 시작
        //init 상태 체크
//        qDebug() << "initializing";
        if(getMotorState() == READY && probot->localization_confirm == LOCAL_READY){
            if(probot->status_charge == 1){
                ui_state = UI_STATE_CHARGING;
            }else{
                plog->write("[SUPERVISOR] Initializing Success -> Resting");
                ui_state = UI_STATE_RESTING;
                debug_mode = false;
                ipc->handsup();
            }
        }else if(probot->localization_confirm == LOCAL_READY){
            if(probot->status_charge == 1){
                ui_state = UI_STATE_CHARGING;
            }else{
                qDebug() << "?!!!!!!!!!!!!!!!!!!!!!";
            }
        }else{
            if(check_init){
                plog->write("[SUPERVISOR] Initializing -> Init Page");
                QMetaObject::invokeMethod(mMain, "need_init");
                check_init = false;
            }
        }
        break;
    }
    case UI_STATE_RESTING:{
        static int count_battery = 0;
        if(probot->battery_percent < 20){
            if(count_battery++ > 60000/MAIN_THREAD){
                QMetaObject::invokeMethod(mMain, "lessbattery");
                plog->write("[SUPERVISOR] PLAY LESS BATTERY");
                count_battery = 0;
            }
        }else{
            count_battery = 0;
        }

        cmd_accept = false;
        if(probot->status_charge == 1){
            ipc->handsdown();
            plog->write("[SUPERVISOR] STATE Detect : Charging");
            ui_state = UI_STATE_CHARGING;
            QMetaObject::invokeMethod(mMain, "docharge");
        }else if(getLocalizationState() != LOCAL_READY || probot->motor[0].status > 1 || probot->motor[1].status > 1){
            ui_state = UI_STATE_INITAILIZING;
            plog->write("[SUPERVISOR] STATE Detect : Failed "+QString().sprintf("%d, %d, %d",getLocalizationState(),probot->motor[0].status,probot->motor[1].status));
            if(debug_mode){

            }else{
                killSLAM();
            }
        }else if(call_queue.size() > 0){
            ipc->handsdown();
            plog->write("[SUPERVISOR] STATE Detect : Calling");
            ui_state = UI_STATE_MOVING;
            probot->call_moving_count = 0;
        }else if(getSetting("setting","SERVER","use_server_call") == "true"){
            if(probot->server_call_size > 0){
                probot->server_call_size = 0;
                //콜 번호가 유효한 지 체크
                LOCATION temp_loc = getLocationbyID(probot->server_call_location);
//                if(temp_loc.loc_id == probot->server_call_location){
//                    //호출 포인트 세팅
//                    current_target = temp_loc;
//                    plog->write("[SUPERVISOR] MOVING (SERVER CALLING) : "+temp_loc.name+" ( loc id : "+temp_loc.loc_id+" )");
//                    probot->is_calling = true;
//                    ipc->handsdown();
//                    ui_state = UI_STATE_MOVING;
//                }else{
//                    plog->write("[SUPERVISOR] MOVING (SERVER CALLING) : Location ID Wrong ("+QString::number(probot->server_call_location)+")");
//                }
            }else if(probot->server_call_size == -1){
                probot->server_call_size = 0;
            }
        }
        break;
    }
    case UI_STATE_CHARGING:{
        patrol_mode = PATROL_NONE;
        if(probot->status_charge == 0){
            plog->write("[SCHEDULER] UI STATE IN CHARGING and Charge State = 0 -> NONE");
            ui_state = UI_STATE_NONE;
        }
        break;
    }
    case UI_STATE_HANDS_UP:{
        if(getSetting("setting","SERVER","use_server_call") == "true"){
            if(probot->server_call_size > 0){
                probot->server_call_size = 0;
                ipc->handsdown();
                //콜 번호가 유효한 지 체크
                LOCATION temp_loc = getLocationbyID(probot->server_call_location);
//                if(temp_loc.loc_id == probot->server_call_location){
//                    //호출 포인트 세팅
//                    current_target = temp_loc;
//                    plog->write("[SUPERVISOR] MOVING (SERVER CALLING) : "+temp_loc.name+" ( loc id : "+temp_loc.loc_id+" )");
//                    probot->is_calling = true;
//                    ui_state = UI_STATE_MOVING;
//                }else{
//                    plog->write("[SUPERVISOR] MOVING (SERVER CALLING) : Location ID Wrong ("+QString::number(probot->server_call_location)+")");
//                    //세팅 되지 않음 -> 고 홈
//                    plog->write("[SUPERVISOR] MOVING (No Target) : Back to Resting");
//                    probot->call_moving_count = 0;
//                    current_target = getLocation("Resting0");
//                    ui_state = UI_STATE_MOVING;
//                }

            }else if(probot->server_call_size == -1){
                if(use_cleaning_location){
                    ipc->handsdown();
                    probot->server_call_size = 0;
                    //세팅 되지 않음 -> 고 홈
                    plog->write("[SUPERVISOR] MOVING (No Target) : Back to CleaningLocation");
                    probot->call_moving_count = 0;
                    current_target = getLocation(0,"Cleaning0");
                    ui_state = UI_STATE_MOVING;
                }else{
                    ipc->handsdown();
                    probot->server_call_size = 0;
                    //세팅 되지 않음 -> 고 홈
                    plog->write("[SUPERVISOR] MOVING (No Target) : Back to Resting");
                    probot->call_moving_count = 0;
                    current_target = getLocation(0,"Resting0");
                    ui_state = UI_STATE_MOVING;

                }
            }
        }else{
            if(use_cleaning_location){
                //세팅 되지 않음 -> 고 홈
                plog->write("[SUPERVISOR] MOVING (No Target) : Back to CleaningLocation");
                probot->call_moving_count = 0;
                current_target = getLocation(0,"Cleaning0");
                ui_state = UI_STATE_MOVING;
            }else{
                //세팅 되지 않음 -> 고 홈
                plog->write("[SUPERVISOR] MOVING (No Target) : Back to Resting");
                probot->call_moving_count = 0;
                current_target = getLocation(0,"Resting0");
                ui_state = UI_STATE_MOVING;
            }
        }
        break;
    }
    case UI_STATE_MOVING:{
        static int timer_cnt2 = 0;
        static bool paused = false;
        //ERROR
        if(probot->running_state == ROBOT_MOVING_PAUSED){
            paused = true;
        }else if(probot->running_state == ROBOT_MOVING_MOVING){
            paused = false;
        }

        if(probot->ui_fail_state == 1){
//            ui_state = UI_STATE_NONE;
            ui_state = UI_STATE_INITAILIZING;
            plog->write("[SUPERVISOR] UI FAIL STATE -> KILL SLAM");
            killSLAM();
        }else if(getMotorState() == 0){
            if(probot->status_lock){
                plog->write(QString::number(probot->status_emo)+QString::number(probot->status_lock)+QString::number(probot->status_remote)+QString::number(probot->status_power)+QString::number(probot->motor[0].status)+QString::number(probot->motor[1].status)+QString::number(probot->battery_in)+QString::number(probot->battery_out));
                plog->write("[SUPERVISOR] MOTOR NOT READY -> UI_STATE = UI_STATE_MOVEFAIL ");
                QMetaObject::invokeMethod(mMain, "movefail");
                ui_state = UI_STATE_MOVEFAIL;
                is_test_moving = false;
            }
        }else if(probot->localization_state == LOCAL_NOT_READY){
            is_test_moving = false;
            plog->write("[SUPERVISOR] LOCAL NOT READY -> UI_STATE = UI_STATE_MOVEFAIL");
            ui_state = UI_STATE_MOVEFAIL;
            QMetaObject::invokeMethod(mMain, "movefail");
        }else{
            if(getSetting("setting","USE_UI","use_current_pause")=="true"){
                float current_threshold = getSetting("update","DRIVING","pause_motor_current").toFloat();
                int check_count = getSetting("update","DRIVING","pause_current_ms").toInt()/MAIN_THREAD;
                if(probot->motor[0].current > current_threshold || probot->motor[1].current > current_threshold){
                    if(current_cnt++ > check_count){
                        //MOTOR THRESHOLD IN. PAUSED!
                        if(probot->running_state != ROBOT_MOVING_PAUSED){
                            plog->write("[SUPERVISOR] AUTO PAUSED : Motor Current Over "+QString().sprintf("(0 : %f, 1 : %f, limit: %f)",probot->motor[0].current,probot->motor[1].current,current_threshold));
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
                    count_pass = 0;
                    if(current_target.name == "Charging0"){
                        if(probot->is_patrol){
                            ui_state = UI_STATE_MOVING;
                            count_pass = 0;
                            plog->write("[SCHEDULER] PICKUP -> AUTO PASS");
                        }else if(probot->is_calling){
                            ui_state = UI_STATE_CHARGING;
                            if(call_queue.size() > 0){
                                plog->write("[SCHEDULER] CALLING MOVE ARRIVED "+call_queue[0]);
                                call_queue.pop_front();
                            }
                            QMetaObject::invokeMethod(mMain, "docharge");
                        }else{
                            ui_state = UI_STATE_CHARGING;
                            plog->write("[SCHEDULER] GO CHARGE MOVING DONE -> docharge");
                            QMetaObject::invokeMethod(mMain, "docharge");
                        }
                    }else if(current_target.name == "Resting0"){
                        if(probot->is_patrol){
                            ui_state = UI_STATE_MOVING;
                            count_pass = 0;
                            plog->write("[SCHEDULER] PICKUP -> AUTO PASS");
                        }else if(probot->is_calling){
                            if(call_queue.size() > 0){
                                if(getCallLocation(call_queue[0]).name == "Resting0"){
                                    plog->write("[SCHEDULER] CALLING MOVE ARRIVED "+call_queue[0]);
                                    call_queue.pop_front();
                                }else{
                                    plog->write("[SCHEDULER] CALLING MOVE ARRIVED (max call) "+QString::number(call_queue.size()));
                                }
                            }else{
                                plog->write("[SCHEDULER] CALLING MOVE ARRIVED (resting) ");
                            }
                            QMetaObject::invokeMethod(mMain, "waitkitchen");
                            ui_state = UI_STATE_CLEANING;
                        }else{
                            plog->write("[SCHEDULER] GO HOME MOVING DONE -> waitkitchen");
                            QMetaObject::invokeMethod(mMain, "waitkitchen");
                            ipc->handsup();
                            ui_state = UI_STATE_RESTING;
                        }
                    }else if(current_target.name == "Cleaning0"){
                        if(probot->is_patrol){
                            ui_state = UI_STATE_MOVING;
                            count_pass = 0;
                            plog->write("[SCHEDULER] PICKUP -> AUTO PASS");
                        }else if(probot->is_calling){
                            if(call_queue.size() > 0){
                                if(getCallLocation(call_queue[0]).name == "Cleaning0"){
                                    plog->write("[SCHEDULER] CALLING MOVE ARRIVED "+call_queue[0]);
                                    call_queue.pop_front();
                                }else{
                                    plog->write("[SCHEDULER] CALLING MOVE ARRIVED (max call) "+QString::number(call_queue.size()));
                                }
                            }else{
                                plog->write("[SCHEDULER] CALLING MOVE ARRIVED (cleaning) ");
                            }
                            probot->is_calling = false;
                            QMetaObject::invokeMethod(mMain, "clearkitchen");
                            ui_state = UI_STATE_CLEANING;
                        }else{
                            plog->write("[SCHEDULER] GO HOME MOVING DONE -> clearkitchen");
                            QMetaObject::invokeMethod(mMain, "clearkitchen");
                            ui_state = UI_STATE_CLEANING;
                        }
                    }else{
                        if(probot->is_calling){
                            if(call_queue.size() > 0){
                                plog->write("[SCHEDULER] CALLING MOVE ARRIVED "+call_queue[0]);
                                call_queue.pop_front();
                            }
                            probot->call_moving_count++;
                            ui_state = UI_STATE_PICKUP;
                            QMetaObject::invokeMethod(mMain, "showpickup");
                        }else if(probot->is_patrol){
                            plog->write("[SCHEDULER] PATROLLING MOVE ARRIVED "+current_target.name);
                            if(use_patrol_pickup){
                                ui_state = UI_STATE_PICKUP;
                                QMetaObject::invokeMethod(mMain, "showpickup");
                            }else{
                                ui_state = UI_STATE_MOVING;
                                count_pass = 0;
                                plog->write("[SCHEDULER] PICKUP -> AUTO PASS");
                            }
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
                                        probot->trays[i].empty = true;
                                        probot->pickupTrays.push_back(i+1);
                                    }
                                }else{
                                    LOCATION clearLoc;
                                    probot->trays[i].location = clearLoc;
                                }
                            }
                            plog->write("[SCHEDULER] SERVING : PICK UP "+curLoc.name);
                            ui_state = UI_STATE_PICKUP;
                            QMetaObject::invokeMethod(mMain, "showpickup");
                        }
                    }
                    cmd_accept = false;
                    current_target.name = "";
                }else{
                    if(current_target.name == ""){
                        LOCATION cur_target;
                        probot->is_patrol = false;

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
                            probot->is_calling = false;
                            cur_target = probot->trays[tray_num].location;
                            plog->write("[SUPERVISOR] MOVING (SERVING) : "+cur_target.name+" ( tray num : "+QString::number(tray_num)+" )");
                        }else{
                            //최대 이동 횟수 초과 시 -> 대기장소로 이동
                            if(probot->call_moving_count > probot->max_moving_count){
                                probot->is_calling = true;
                                plog->write("[SUPERVISOR] MOVING (CALL MAX) : Call Move Count is Max "+QString::number(probot->call_moving_count)+","+QString::number(probot->max_moving_count));
                            }else{
                                //2. 들어온 콜 위치가 있는지 체크
                                bool call_set = false;
                                while(!call_set){
                                    if(call_queue.size() > 0){
                                        //콜 번호가 유효한 지 체크
                                        LOCATION temp_loc = getLocationbyCall(call_queue[0]);
                                        qDebug() << call_queue[0] << temp_loc.call_id;
                                        if(temp_loc.call_id == call_queue[0]){
                                            //호출 포인트 세팅
                                            call_set = true;
                                            cur_target = temp_loc;
                                            plog->write("[SUPERVISOR] MOVING (CALLING) : "+temp_loc.name+" ( call id : "+temp_loc.call_id+" )");
                                            probot->is_calling = true;
                                        }else{
                                            plog->write("[SUPERVISOR] MOVING (CALLING) : Call ID Wrong ("+call_queue[0]+")");
                                            call_queue.pop_front();
                                        }
                                    }else{
                                        call_set = true;
                                    }
                                }

                                if(cur_target.name == ""){
                                    if(getSetting("setting","SERVER","use_server_call") == "true"){

                                    }else{
                                        //3. PATROLLING
                                        if(patrol_list.size() > 0){
                                            if(patrol_mode == PATROL_RANDOM){
                                                //패트롤 위치 랜덤하게 지정
                                                int temp = qrand();
                                                while(patrol_num == temp%(patrol_list.size())){
                                                    temp = qrand();
                                                    qDebug() << "Next temp = " << temp << temp%(patrol_list.size());
                                                }
                                                plog->write("[SUPERVISOR] MOVING (PATROL RANDOM) : CUR ("+QString::number(temp%(patrol_list.size()))+") LAST ("+QString::number(patrol_num)+")");
                                                patrol_num = temp%(patrol_list.size());

                                                //패트롤 위치가 유효한 지 체크
                                                LOCATION temp_loc = getLocation(0, patrol_list[patrol_num]);
                                                if(temp_loc.name != ""){
                                                    cur_target = temp_loc;
                                                    probot->is_calling = false;
                                                    probot->is_patrol = true;
                                                    plog->write("[SUPERVISOR] MOVING (PATROL RANDOM) : "+temp_loc.name);
                                                }else{
                                                    plog->write("[SUPERVISOR] MOVING (PATROL RANDOM) : Name Wrong ("+patrol_list[patrol_num]+")");
                                                    patrol_mode = PATROL_NONE;
                                                }
                                            }else if(patrol_mode == PATROL_SEQUENCE){
                                                if(++patrol_num >= patrol_list.size())
                                                    patrol_num = 0;

                                                plog->write("[SUPERVISOR] MOVING (PATROL SEQUENCE) : CUR ("+QString::number(patrol_num)+")");

                                                //패트롤 위치가 유효한 지 체크
                                                LOCATION temp_loc = getLocation(0, patrol_list[patrol_num]);
                                                if(temp_loc.name != ""){
                                                    cur_target = temp_loc;
                                                    probot->is_calling = false;
                                                    probot->is_patrol = true;
                                                    plog->write("[SUPERVISOR] MOVING (PATROL SEQUENCE) : "+temp_loc.name);
                                                }else{
                                                    plog->write("[SUPERVISOR] MOVING (PATROL SEQUENCE) : Name Wrong ("+patrol_list[patrol_num]+")");
                                                    patrol_mode = PATROL_NONE;
                                                }
                                            }else{
                                                plog->write("[SUPERVISOR] PATROL LIST IS NOT EMPTY BUT MODE IS NONE "+QString().sprintf("(mode: %d, list size : %d)",patrol_mode,patrol_list.size()));
                                                patrol_list.clear();
                                            }
                                        }
                                    }
                                }
                            }
                        }

                        count_moveto = 0;
                        if(cur_target.name == ""){
                            ipc->handsup();
                            ui_state = UI_STATE_HANDS_UP;
                            break;
                        }else{
                            current_target = cur_target;
                        }
                    }else{
                        if(timer_cnt2%5==0){
                            if(count_moveto++ == 0){
                                if(current_target.name.left(7) == "Resting" || current_target.name.left(8) == "Cleaning"){
                                    if(probot->comeback_preset == 0){
                                        //무브 명령 보냄
                                        if(is_test_moving){
                                            plog->write("[SUPERVISOR] MOVING(TEST) SET TO "+current_target.name+QString::number(probot->cur_preset));
                                            ipc->moveToLocationTest(current_target,probot->cur_preset);
                                            is_test_moving = false;
                                        }else{
                                            plog->write("[SUPERVISOR] MOVING SET TO "+current_target.name+QString::number(probot->cur_preset));
                                            ipc->moveToLocation(current_target,probot->cur_preset);
                                        }
                                    }else{
                                        //무브 명령 보냄
                                        if(is_test_moving){
                                            plog->write("[SUPERVISOR] MOVING(TEST) SET TO "+current_target.name+QString::number(probot->cur_preset));
                                            ipc->moveToLocationTest(current_target,probot->cur_preset);
                                            is_test_moving = false;
                                        }else{
                                            plog->write("[SUPERVISOR] MOVING SET TO "+current_target.name+QString::number(probot->comeback_preset));
                                            ipc->moveToLocation(current_target,probot->comeback_preset);
                                        }
                                    }
                                }else{
                                    //무브 명령 보냄
                                    if(is_test_moving){
                                        plog->write("[SUPERVISOR] MOVING(TEST) SET TO "+current_target.name+QString::number(probot->cur_preset));
                                        ipc->moveToLocationTest(current_target,probot->cur_preset);
                                        is_test_moving = false;
                                    }else{
                                        plog->write("[SUPERVISOR] MOVING SET TO "+current_target.name+QString::number(probot->cur_preset));
                                        ipc->moveToLocation(current_target,probot->cur_preset);
                                    }
                                }
                            }else if(count_moveto++ > 5){
                                if(probot->ipc_use){
                                    ipc->moveStop();
                                }
                                QMetaObject::invokeMethod(mMain, "movefail");
                                ui_state = UI_STATE_MOVEFAIL;
                                plog->write("[SUPERVISOR] MOVING FAILED : ROBOT NOT MOVING (Max 5)");
                            }
                        }
                    }
                    timer_cnt2++;
                }
                is_test_moving = false;
            }else if(probot->running_state == ROBOT_MOVING_MOVING){
                // moving
                if(!cmd_accept){
                    cmd_accept = true;
                    count_moveto = 0;
                    if(probot->is_calling){
                        plog->write("[SUPERVISOR] CALLING : MOVE START");
                    }else{
                        if(patrol_mode != PATROL_NONE){
                            plog->write("[SUPERVISOR] PATROLIONG : MOVE START");
                        }else{
                            plog->write("[SUPERVISOR] SERVING : MOVE START");
                        }
                    }
                    QMetaObject::invokeMethod(mMain, "movelocation");
                }
            }else if(probot->running_state == ROBOT_MOVING_NOT_READY){
                plog->write("[SUPERVISOR] PATH NOT FOUND -> UI_STATE = UI_STATE_MOVEFAIL");
                QMetaObject::invokeMethod(mMain, "movefail");
                ui_state = UI_STATE_MOVEFAIL;
            }else if(probot->running_state == ROBOT_MOVING_WAIT){
                if(!flag_movewait){
                    plog->write("[SCHEDULER] ROBOT ERROR : MOVE WAIT");
                    QMetaObject::invokeMethod(mMain, "movewait");
                    count_movewait = 0;
                    flag_movewait = true;
                }
            }

            if(probot->obs_in_path_state != 0 && probot->running_state == ROBOT_MOVING_MOVING){
                if(!flag_excuseme){
                    plog->write("[SCHEDULER] ROBOT ERROR : EXCUSE ME");
                    QMetaObject::invokeMethod(mMain, "excuseme");
                    count_excuseme = 0;
                    flag_excuseme = true;
                }
            }

        }
        break;
    }
    case UI_STATE_CLEANING:{
        if(getSetting("setting","USE_UI","use_calling_notice") != "true"){
            ui_state = UI_STATE_RESTING;
        }
        break;
    }
    case UI_STATE_PICKUP:{
        if(probot->running_state == ROBOT_MOVING_PAUSED){
            plog->write("[SCHEDULER] IN PICKUP BUT ROBOT PAUSED -> RESUME");
            if(probot->ipc_use){
                ipc->moveResume();
            }
        }
        if(patrol_mode != PATROL_NONE){
            if(use_patrol_pickup){
                count_pass++;
                if(count_pass > 30){
                    ui_state = UI_STATE_MOVING;
                    count_pass = 0;
                    plog->write("[SCHEDULER] PICKUP -> AUTO PASS");
                }
            }else{
                ui_state = UI_STATE_MOVING;
                count_pass = 0;
                plog->write("[SCHEDULER] PICKUP -> AUTO PASS");
            }
        }
        for(int i=0; i<call_queue.size(); i++){
            if(getCallLocation(call_queue[i]).name == "Resting0" && getSetting("setting","CALL","force_resting") == "true"){
                plog->write("[SCHEDULER] PICKUP -> FORCE MOVE RESTING");
                count_pass = 0;
                ui_state = UI_STATE_MOVING;
                cmd_accept = false;
                QString temp = call_queue[i];
                call_queue.clear();
                call_queue.append(temp);
                break;
            }else if(getCallLocation(call_queue[i]).name == "Cleaning0" && getSetting("setting","CALL","force_cleaning") == "true"){
                plog->write("[SCHEDULER] PICKUP -> FORCE MOVE CLEANING");
                count_pass = 0;
                ui_state = UI_STATE_MOVING;
                cmd_accept = false;
                QString temp = call_queue[i];
                call_queue.clear();
                call_queue.append(temp);
                break;
            }
        }
        break;
    }
    case UI_STATE_MOVEFAIL:{
        if(getMotorState() == 1 && probot->status_charge == 0 && probot->localization_state == 2){
            if(probot->running_state == ROBOT_MOVING_NOT_READY){
            }else{
                plog->write("[SUPERVISOR] MOVEFAILED : Wake Up Auto");
                QMetaObject::invokeMethod(mMain, "movefail_wake");
                ui_state = UI_STATE_NONE;
            }
        }else{
            if(prev_motor_state != getMotorState()){
                QMetaObject::invokeMethod(mMain, "movefail");
            }else if(prev_local_state != probot->localization_state){
                QMetaObject::invokeMethod(mMain, "movefail");
            }else if(getMotorState() == 1 && probot->localization_state == LOCAL_READY && cmd_accept){
                QMetaObject::invokeMethod(mMain, "movefail");
            }
        }
        patrol_mode = PATROL_NONE;
        current_target.name = "";
        cmd_accept = false;
        break;
    }
    }

    if(flag_excuseme){
        if(count_excuseme++ > 15000/MAIN_THREAD){
            flag_excuseme = false;
            count_excuseme = 0;
        }
    }

    if(flag_movewait){
        if(count_movewait++ > 15000/MAIN_THREAD){
            flag_movewait = false;
            count_movewait = 0;
        }
    }

    timer_cnt++;
    prev_state = ui_state;
    prev_running_state = probot->running_state;
    prev_motor_state = getMotorState();
    prev_local_state = probot->localization_state;
}

void Supervisor::checkMoveFail(){
    if(getMotorState() == 0){
        plog->write(QString::number(probot->status_emo)+QString::number(probot->status_lock)+QString::number(probot->status_remote)+QString::number(probot->status_power)+QString::number(probot->motor[0].status)+QString::number(probot->motor[1].status)+QString::number(probot->battery_in)+QString::number(probot->battery_out));
        plog->write("[SUPERVISOR] MOTOR NOT READY -> UI_STATE = UI_STATE_MOVEFAIL ");
        QMetaObject::invokeMethod(mMain, "movefail");
        ui_state = UI_STATE_MOVEFAIL;
    }else if(probot->localization_state == LOCAL_NOT_READY){
        plog->write("[SUPERVISOR] LOCAL NOT READY -> UI_STATE = UI_STATE_MOVEFAIL");
        QMetaObject::invokeMethod(mMain, "movefail");
        ui_state = UI_STATE_MOVEFAIL;
    }
}

void Supervisor::passInit(){
    plog->write("[COMMAND] ROBOT INIT PASS");
    debug_mode = true;
//    ui_state = UI_STATE_RESTING;
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
bool Supervisor::checkCallQueue(){
    return false;
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

void Supervisor::goServing(int group, int table){
    if(ui_state == UI_STATE_RESTING || ui_state == UI_STATE_CLEANING){
        LOCATION target;
        patrol_mode = PATROL_NONE;
        int target_num = -1;
        int count = 0;
        for(int i=0; i<pmap->locations.size(); i++){
            if(pmap->locations[i].type == "Serving"){
                if(pmap->locations[i].group == group){// && pmap->locations[i].number == table){
                    if(count == table){
                        target = pmap->locations[i];
                        target_num = count;
                        break;
                    }else{
                        count++;
                    }
                }
            }
        }
        if(target_num > -1){
            plog->write("[COMMAND] START Serving : "+target.name+QString().sprintf(" (group : %d, table : %d)", group, table));
            for(int i=0; i<probot->trays.size(); i++){
                probot->trays[i].empty = false;
                probot->trays[i].location = target;
            }
            ui_state = UI_STATE_MOVING;
        }else{
            plog->write("[COMMAND] START Serving (target not found) : "+QString().sprintf(" (group : %d, table : %d)", group, table));
        }
    }else{
        plog->write("[COMMAND] START Serving (State not ready) : "+QString::number(ui_state));

    }
}

LOCATION Supervisor::getLocationbyID(int id){
//    for(int i=0; i<pmap->locations.size(); i++){
//        if(pmap->locations[i].loc_id == id){
//            return pmap->locations[i];
//        }
//    }
    return LOCATION();
}
LOCATION Supervisor::getLocationbyCall(QString call){
    for(int i=0; i<pmap->locations.size(); i++){
        if(pmap->locations[i].call_id == call){
            return pmap->locations[i];
        }
    }
    return LOCATION();
}
LOCATION Supervisor::getLocation(int group, QString name){
    for(int i=0; i<pmap->locations.size(); i++){
        if(pmap->locations[i].group == group)
            if(pmap->locations[i].name == name){
                return pmap->locations[i];
            }
    }
    return LOCATION();
}

int Supervisor::getzipstate(){
    return zip->process;
}
void Supervisor::usbsave(QString usb, bool _ui, bool _slam, bool _config, bool _map, bool _log){
    zip->process = 0;
    std::string user = getenv("USER");
    std::string path = "/media/" + user;
    qDebug() << _ui << _slam;
    if(usb == "Destkop"){
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
    return probot->wifi_map.size();
}
QString Supervisor::getCurWifiSSID(){
    return probot->wifi_ssid;
//    QList<QString> keys = probot->wifi_map.keys();
//    for(int i=0; i<keys.size(); i++){
//        if(probot->wifi_map[keys[i]].inuse)
//            return probot->wifi_map[keys[i]].ssid;
//    }

//    return getSetting("NETWORK","wifi_ssid");

}
QString Supervisor::getWifiSSID(int num){
    QList<QString> keys = probot->wifi_map.keys();
//    qDebug() << "Before : " << keys;
    std::sort(keys.begin(),keys.end(),sortWifi);
//    qDebug() << "After : " << keys;
    if(num < keys.size() && num > -1){
        return probot->wifi_map[keys[num]].ssid;
    }else
        return "unknown";
}
int Supervisor::getWifiConnection(QString ssid){
    if(ssid == ""){
        ssid = probot->wifi_ssid;
    }
//    qDebug() << "getwificonnection" << ssid << probot->wifi_ssid <<  probot->wifi_connection;
    if(probot->wifi_ssid == ssid){
        return probot->wifi_connection;
    }else{
        return 0;
    }
//    return probot->wifi_map[ssid].state;
}
void Supervisor::setWifiConnection(QString ssid, int con){
    probot->wifi_map[ssid].state = con;
}

void Supervisor::process_accept(int cmd){

}

void Supervisor::process_done(int cmd){
    qDebug() << "Process done" << cmd;
    if(cmd == ExtProcess::PROCESS_CMD_SET_WIFI_IP){
//        getWifiIP();
        QMetaObject::invokeMethod(mMain,"wifireset");
        setWifiConnection(probot->wifi_ssid,2);
    }else if(cmd == ExtProcess::PROCESS_CMD_GET_WIFI_LIST){
        QMetaObject::invokeMethod(mMain, "wifisuccess");
    }else if(cmd == ExtProcess::PROCESS_CMD_CHECK_CONNECTION){
        QMetaObject::invokeMethod(mMain, "checkwifidone");
    }else if(cmd == ExtProcess::PROCESS_CMD_CONNECT_WIFI){
        readWifiState(probot->wifi_ssid);
        QMetaObject::invokeMethod(mMain, "checkwifidone");
    }else if(cmd == ExtProcess::PROCESS_CMD_GET_WIFI_IP){
        QMetaObject::invokeMethod(mMain, "wifisuccess");
    }else if(cmd == ExtProcess::PROCESS_CMD_GIT_PULL || cmd == ExtProcess::PROCESS_CMD_GIT_UPDATE ||  cmd == ExtProcess::PROCESS_CMD_GIT_RESET){
        setSetting("robot","VERSION/last_update_mode","git");
        setSetting("robot","VERSION/last_update_date",probot->program_date);
        readSetting();
        QProcess::startDetached(QApplication::applicationFilePath());
        QApplication::exit(12);
    }else if(cmd == ExtProcess::PROCESS_CMD_UNZIP){
        plog->write("[UPDATE] Unzip Success");
        QDir updatedir(QDir::homePath() + "/RB_MOBILE/temp/update");
        QString jsondir = QDir::homePath() + "/RB_MOBILE/temp/update/update.json";
        QFile json(jsondir);
        QStringList filelist = updatedir.entryList();
        if(json.open(QFile::ReadOnly)){
            //read json?
//            QTextStream ts(&json);
//            QString ddddd = ts.readAll();
//            QJsonDocument jj = QJsonDocument::fromJson(ddddd.toUtf8());
//            QJsonObject updatejson = jj.object();
//            QStringList keys = updatejson["keys"].toString().split(",");

            QStringList keys = server->update_list.keys();
            if(keys.size() > 0){
                for(QString key : keys){
                    QString keyname = key + server->update_list[key].extension;

                    for(QString file : filelist){
                        if(keyname == file){
                            server->update_list[key].file_exist = true;
                            break;
                        }
                        server->update_list[key].file_exist = false;
                    }
                }
                for(QString key : keys){
                    if(server->update_list[key].file_exist){
                        plog->write("[UPDATE] File Update : "+ key + " is Exist");
                    }else{
                        plog->write("[UPDATE] File Update : "+ key + " is not Found");
                    }
                }
                QMetaObject::invokeMethod(mMain,"unzip_done");
            }else{
                //error
                plog->write("[UPDATE] File Update : No zip File");
                QMetaObject::invokeMethod(mMain,"unzip_failed");
            }
        }
    }
}

void Supervisor::process_error(int cmd, int param){
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
}

void Supervisor::process_timeout(int cmd){
    QMetaObject::invokeMethod(mMain, "checkwifidone");
}

void Supervisor::connectWifi(QString ssid, QString passwd){
    ExtProcess::Command temp;
    temp.cmd = ExtProcess::PROCESS_CMD_CONNECT_WIFI;

    memcpy(temp.params,ssid.toUtf8(),sizeof(char)*100);
    memcpy(temp.params2,passwd.toUtf8(),sizeof(char)*100);
    extproc->set_command(temp);
}

void Supervisor::setWifi(QString ip, QString gateway, QString dns){
    ExtProcess::Command temp;
    temp.cmd = ExtProcess::PROCESS_CMD_SET_WIFI_IP;
    memcpy(temp.params,ip.toUtf8(),sizeof(char)*100);
    memcpy(temp.params2,gateway.toUtf8(),sizeof(char)*100);
    memcpy(temp.params3,dns.toUtf8(),sizeof(char)*100);
    extproc->set_command(temp);
}

void Supervisor::readWifiState(QString ssid){
    if(probot->wifi_ssid == ""){
        QMetaObject::invokeMethod(mMain, "checkwifidone");
    }else{
        if(ssid == ""){
            ssid = probot->wifi_ssid;
        }
        if(probot->wifi_ssid != ssid){
            QMetaObject::invokeMethod(mMain, "checkwifidone");
        }else{
            ExtProcess::Command temp;
            temp.cmd = ExtProcess::PROCESS_CMD_CHECK_CONNECTION;
            memcpy(temp.params,ssid.toUtf8(),sizeof(char)*100);
            extproc->set_command(temp);
        }

    }
}

void Supervisor::setWifiSSD(QString ssid){
    probot->wifi_ssid = ssid;
}

void Supervisor::getWifiIP(){
    ExtProcess::Command temp;
    temp.cmd = ExtProcess::PROCESS_CMD_GET_WIFI_IP;
//    qDebug() << "getwifiip " << probot->wifi_ssid;
    if(probot->wifi_ssid == ""){

    }else{
        memcpy(temp.params,probot->wifi_ssid.toUtf8(),sizeof(char)*100);
        extproc->set_command(temp);
    }
}
QString Supervisor::getcurIP(){
    return probot->cur_ip;
}
QString Supervisor::getcurGateway(){
    return probot->cur_gateway;
}
QString Supervisor::getcurDNS(){
    return probot->cur_dns;
}
void Supervisor::getAllWifiList(){
    ExtProcess::Command temp;
    temp.cmd = ExtProcess::PROCESS_CMD_GET_WIFI_LIST;
    extproc->set_command(temp, "Get Wifi List");
    QNetworkConfigurationManager ncm;
    defaultWifiConf = ncm.defaultConfiguration();
    if(defaultWifiConf.name() != ""){
        probot->wifi_ssid = defaultWifiConf.name();
    }
}
bool Supervisor::getWifiSecurity(QString ssid){
    return probot->wifi_map[ssid].security;
}
int Supervisor::getWifiLevel(QString ssid){
    if(probot->wifi_map[ssid].level < 20){
        return 0;
    }else if(probot->wifi_map[ssid].level < 40){
        return 1;
    }else if(probot->wifi_map[ssid].level < 60){
        return 2;
    }else if(probot->wifi_map[ssid].level < 80){
        return 3;
    }else{
        return 4;
    }
}
int Supervisor::getWifiRate(QString ssid){
    return probot->wifi_map[ssid].rate;
}
bool Supervisor::getWifiInuse(QString ssid){
    return probot->wifi_map[ssid].inuse;
}

void Supervisor::cleanTray(){
    plog->write("[COMMAND] Clean Tray Set");
    ui_state = UI_STATE_RESTING;
    ipc->handsup();
    if(call_queue.size() == 0)
        probot->is_calling = false;
}
int Supervisor::getCallQueueSize(){
    if(call_queue.size() > 0)
        return call_queue.size();
    else
        return 0;
}

void Supervisor::checkTravelline(){
    ipc->set_cmd(ROBOT_CMD_CHECK_TRAVEL_LINE,"Check Travelline");
}

void Supervisor::confirmLocalization(){
    plog->write("[SETTING] Localization Confirm");
    probot->localization_confirm = LOCAL_READY;
}

void Supervisor::clearRobot(){
    probot->status_power = 0;
    probot->status_emo = 0;
    probot->status_remote = 0;
    probot->status_charge = 0;
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

    probot->localization_confirm = 0;
    probot->err_code = 0;
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
//    killSLAM();
    probot->localization_confirm = 0;
    QMetaObject::invokeMethod(mMain, "need_init");

}

void Supervisor::resetClear(){
    //log 삭제
//    QDir dir_log(QDir::homePath()+"/RB_MOBILE/log");
//    if(dir_log.removeRecursively()){
//        plog->reset();
//        plog->write("[SETTING] Reset Clear");
//        plog->write("[SETTING] Reset Clear : Remove logs");
//    }else{
//        plog->write("[SETTING] Reset Clear");
//        plog->write("[SETTING] Reset Clear : Remove logs failed");
//    }

//    //maps 폴더 지움.
//    QDir dir_maps(QDir::homePath()+"/RB_MOBILE/maps");
//    if(dir_maps.removeRecursively()){
//        plog->write("[SETTING] Reset Clear : Remove maps");
//    }else{
//        plog->write("[SETTING] Reset Clear : Remove maps failed");
//    }

//    //temp 폴더 지움.
//    QDir dir_temp(QDir::homePath()+"/RB_MOBILE/temp");
//    if(dir_temp.removeRecursively()){
//        plog->write("[SETTING] Reset Clear : Remove temp");
//    }else{
//        plog->write("[SETTING] Reset Clear : Remove temp failed");
//    }


    //myID 등  robot_config.ini 수정

    //sh 파일 복구?


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
