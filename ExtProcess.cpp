#include "ExtProcess.h"
#include <QDebug>

#define THREAD_EXTPROCESS   200
ExtProcess::ExtProcess(QObject *parent)
    : QObject(parent)
    , shm_command("process_command")
    , shm_return("process_return")
    , shm_wifilist("process_wifilist")
{
    tick = 0;
    if(!shm_command.isAttached()){
        if (!shm_command.create(sizeof(Command), QSharedMemory::ReadWrite) && shm_command.error() == QSharedMemory::AlreadyExists)
        {
            if(shm_command.attach()){
                plog->write("[ExtProcess] SharedMemory is already exist. attach success. ");
                if(shm_command.isAttached()){
                    shm_command.lock();
                    memset(shm_command.data(),0,sizeof(shm_command.data()));
                    shm_command.unlock();
                    plog->write("[ExtProcess] Clear ShardMemory");
                }
            }else{
                plog->write("[ExtProcess] SharedMemory is already exist. attach failed. ");
            }
        }
        else
        {
            plog->write("[ExtProcess] SharedMemory is created. size : "+QString::number(sizeof(Command)));
        }
    }
    if(!shm_return.isAttached()){
        if (!shm_return.create(sizeof(Return), QSharedMemory::ReadWrite) && shm_return.error() == QSharedMemory::AlreadyExists)
        {
            if(shm_return.attach()){
                plog->write("[ExtProcess] SharedMemory(Return) is already exist. attach success. ");
//                if(shm_return.isAttached()){
//                    shm_return.lock();
//                    memset(shm_return.data(),0,sizeof(shm_return.data()));
//                    shm_return.unlock();
//                    plog->write("[ExtProcess] Clear ShardMemory(Return)");
//                }
            }else{
                plog->write("[ExtProcess] SharedMemory(Return) is already exist. attach failed. ");
            }
        }
        else
        {
            plog->write("[ExtProcess] SharedMemory(Return) is created. size : "+QString::number(sizeof(Return)));
        }
    }
    if(!shm_wifilist.isAttached()){
        if (!shm_wifilist.create(sizeof(WifiList), QSharedMemory::ReadWrite) && shm_wifilist.error() == QSharedMemory::AlreadyExists)
        {
            if(shm_wifilist.attach()){
                plog->write("[ExtProcess] SharedMemory(Wifilist) is already exist. attach success. ");
//                if(shm_wifilist.isAttached()){
//                    shm_wifilist.lock();
//                    memset(shm_wifilist.data(),0,sizeof(shm_wifilist.data()));
//                    shm_wifilist.unlock();
//                    plog->write("[ExtProcess] Clear ShardMemory(Wifilist)");
//                }
            }else{
                plog->write("[ExtProcess] SharedMemory(Wifilist) is already exist. attach failed. ");
            }
        }
        else
        {
            plog->write("[ExtProcess] SharedMemory(Wifilist) is created. size : "+QString::number(sizeof(WifiList)));
        }
    }

    command_list.clear();
    program = new QProcess();
    program->setWorkingDirectory(QDir::homePath()+"/RB_MOBILE/sh");
//    program->start("xterm",QStringList() << "./startextproc.sh",QProcess::ReadWrite);
//    program->start(QDir::homePath()+"/start_extproc.sh");

    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimer()));
    timer->start(THREAD_EXTPROCESS);

    timer500 = new QTimer();
    connect(timer500, SIGNAL(timeout()), this, SLOT(onTimer500()));
    timer500->start(500);
}

ExtProcess::~ExtProcess(){
    qDebug() << "destroy ExtProcess";
    shm_command.detach();
    shm_return.detach();
    shm_wifilist.detach();
    program->kill();
    program->close();
    proc->kill();
    proc->close();
    qDebug() << "done ExtProcess";
}

void ExtProcess::setSetting(QString file, QString name, QString value){
    QString ini_path = QDir::homePath()+"/RB_MOBILE/config/"+file+"_config.ini";
    QSettings setting(ini_path, QSettings::IniFormat);
    setting.setValue(name,value);
    plog->write("[SETTING] SET "+name+" VALUE TO "+value);
}

QString ExtProcess::getSetting(QString file, QString group, QString name){
    QString ini_path = QDir::homePath()+"/RB_MOBILE/config/"+file+"_config.ini";
    QSettings setting_robot(ini_path, QSettings::IniFormat);
    setting_robot.beginGroup(group);
    return setting_robot.value(name).toString();
}

void ExtProcess::onTimer500(){
    //이전 명령 timeout 처리
}

void ExtProcess::onTimer(){

#ifdef EXTPROC_TEST
#else
    static uint32_t prev_tick = 0;
    static uint32_t prev_wifilist_tick = 0;
    ExtProcess::Return _return = get_return();
    if(_return.tick != prev_tick){
        timeout_count = 0;
        if(_return.result == PROCESS_RETURN_ACCEPT){
            plog->write("[ExtProcess] Accept : ");
            process_working = true;
            if(_return.command == PROCESS_CMD_SET_WIFI_IP){
                char temp[100];
                memcpy(temp,_return.params,sizeof(unsigned char)*100);
                QString ssid = QString::fromUtf8(temp);
//                qDebug() << ssid;
                probot->wifi_map[ssid].state = 1;
            }
            emit got_accept(_return.command);
        }else if(_return.result == PROCESS_RETURN_DONE){
            process_working = false;
            if(_return.command == PROCESS_CMD_SET_SYSTEM_VOLUME){
                plog->write("[ExtProcess] Done : Set System Volume ");
            }else if(_return.command == PROCESS_CMD_GET_SYSTEM_VOLUME){
                plog->write("[ExtProcess] Done : Get System Volume "+QString::number(_return.params[0]));
                probot->volume_system = _return.params[0];
            }else if(_return.command == PROCESS_CMD_GET_WIFI_LIST){
                plog->write("[ExtProcess] Done : Get Wifi List " + QString::number(_return.params[0]),false);
                wifi_list_size = _return.params[0];
            }else if(_return.command == PROCESS_CMD_GET_WIFI_IP){
                char temp[100];
                char temp22[100];
                char temp33[100];

                memcpy(temp,_return.params,sizeof(unsigned char)*100);
                probot->cur_ip = QString::fromUtf8(temp);

                memcpy(temp22,_return.params2,sizeof(unsigned char)*100);
                probot->cur_gateway = QString::fromUtf8(temp22);

                memcpy(temp33,_return.params3,sizeof(unsigned char)*100);
                probot->cur_dns = QString::fromUtf8(temp33);

                plog->write("[ExtProcess] Done : Get Current IP -> "+probot->cur_ip+", "+probot->cur_gateway+", "+probot->cur_dns);
            }else if(_return.command == PROCESS_CMD_CONNECT_WIFI){
                char temp[100];
                memcpy(temp, _return.params, 100);
                QString ssid = QString::fromUtf8(temp);
                plog->write("[ExtProcess] Done : Connect Wifi " + ssid);
                probot->wifi_ssid = ssid;
                probot->wifi_connection = WIFI_CONNECT;
            }else if(_return.command == PROCESS_CMD_SET_WIFI_IP){
                char temp[100];
                char temp22[100];
                char temp33[100];

                memcpy(temp,_return.params,sizeof(unsigned char)*100);
                probot->cur_ip = QString::fromUtf8(temp);

                memcpy(temp22,_return.params2,sizeof(unsigned char)*100);
                probot->cur_gateway = QString::fromUtf8(temp22);

                memcpy(temp33,_return.params3,sizeof(unsigned char)*100);
                probot->cur_dns = QString::fromUtf8(temp33);

                plog->write("[ExtProcess] Done : Get Current IP -> "+probot->cur_ip+", "+probot->cur_gateway+", "+probot->cur_dns);
            }else if(_return.command == PROCESS_CMD_CHECK_CONNECTION ){
                char temp[100];
                memcpy(temp,_return.params,sizeof(unsigned char)*100);
                QString result = QString::fromUtf8(temp);
                if(result == "full"){
                    plog->write("[ExtProcess] Check Connection : Connected (Internet Good)");
                    probot->wifi_connection = WIFI_CONNECT;
                }else if(result == "limited"){
                    plog->write("[ExtProcess] Check Connection : Connected (Internet Bad)");
                    probot->wifi_connection = WIFI_CONNECT_NO_INTERNET;
                }else if(result == "none"){
                    plog->write("[ExtProcess] Check Connection : Disconnected (Or Connecting)");
                    probot->wifi_connection = WIFI_NONE;
                }else if(result == "unknown"){
                    plog->write("[ExtProcess] Check Connection : Unknown");
                    probot->wifi_connection = WIFI_UNKNOWN;
                }
            }else if(_return.command == PROCESS_CMD_GIT_PULL){
                char temp[100];
                char temp2[100];
                char temp3[100];
                memcpy(temp, _return.params,100);
                memcpy(temp2, _return.params2,100);
                memcpy(temp3, _return.params3,100);
                probot->program_version = QString::fromUtf8(temp3);
                probot->program_date = QString::fromUtf8(temp2);
                probot->program_message = QString::fromUtf8(temp3);
                plog->write("[ExtProcess] Git pull : Success");
            }else if(_return.command == PROCESS_CMD_GIT_UPDATE){
//                qDebug() << "======================================================";
                char temp[100];
                memcpy(temp, _return.params,100);
                if(QString::fromUtf8(temp) == "newest"){
                    plog->write("[ExtProcess] Git Update : Already Newest");
                }else{
                    probot->program_version = QString::fromUtf8(temp);
                    plog->write("[ExtProcess] Git Update Version : "+probot->program_version);
                    for(int i=0; i<probot->gitList.size();i++){
                        if(probot->gitList[i].commit == QString::fromUtf8(temp)){
                            plog->write("[ExtProcess] Git Update : Match");
                            probot->program_date = probot->gitList[i].date;
                            probot->program_message = probot->gitList[i].message;
                        }
                    }
                    setSetting("robot","VERSION/last_update_mode","git");
                    setSetting("robot","VERSION/last_update_date",probot->program_date);

                    QString list = getSetting("robot","VERSION","update_list");//.split(",");

                    if(!list.contains("MAIN_MOBILE")){
                        list +=",MAIN_MOBILE";
                    }
                    if(!list.contains("ExtProcess")){
                        list +=",ExtProcess";
                    }
                    if(!list.contains("SLAMNAV")){
                        list +=",SLAMNAV";
                    }


                    setSetting("robot","MAIN_MOBILE/commit",probot->program_version);
                    setSetting("robot","ExtProcess/commit",probot->program_version);
                    setSetting("robot","SLAMNAV/commit",probot->program_version);
                    setSetting("robot","MAIN_MOBILE/last_update_date",probot->program_date);
                    setSetting("robot","ExtProcess/last_update_date",probot->program_date);
                    setSetting("robot","SLAMNAV/last_update_date",probot->program_date);
                    setSetting("robot","MAIN_MOBILE/last_update_mode","git");
                    setSetting("robot","ExtProcess/last_update_date","git");
                    setSetting("robot","SLAMNAV/last_update_date","git");
                    plog->write("[ExtProcess] Git update : Success "+probot->program_version+", " +probot->program_date);
                }
            }else if(_return.command == PROCESS_CMD_GIT_RESET){
                char temp[100];
                char temp2[100];
                char temp3[100];
                memcpy(temp, _return.params,100);
                memcpy(temp2, _return.params2,100);
                memcpy(temp3, _return.params3,100);
                probot->program_version = QString::fromUtf8(temp3);
                probot->program_date = QString::fromUtf8(temp2);
                probot->program_message = QString::fromUtf8(temp3);
                plog->write("[ExtProcess] Git reset : Success");
            }else if(_return.command == PROCESS_CMD_UNZIP){

            }
            emit got_done(_return.command);
        }else if(_return.result == PROCESS_RETURN_ERROR){
            process_working = false;
            plog->write("[ExtProcess] Error : ");
            int param = 0;
            if(_return.command == PROCESS_CMD_CHECK_CONNECTION){
                char temp[100];
                memcpy(temp, _return.params, sizeof(char)*100);
                QString ssid = QString::fromUtf8(temp);
                setSetting("setting","NETWORK/wifi_ssid",ssid);
                plog->write("[ExtProcess] Check Connection : Disconnected "+ssid);
                probot->wifi_map[ssid].state = 0;
            }else if(_return.command == PROCESS_CMD_CONNECT_WIFI){
                char temp[100];
                memcpy(temp, _return.params, sizeof(char)*100);
                QString ssid = QString::fromUtf8(temp);
                plog->write("[ExtProcess] Connect Wifi Failed : "+ssid);
            }else if(_return.command == PROCESS_CMD_GIT_PULL){
                plog->write("[ExtProcess] Git pull : Failed");
            }else if(_return.command == PROCESS_CMD_GIT_UPDATE){
                char temp[100];
                memcpy(temp, _return.params,100);
                if(QString::fromUtf8(temp) == "newest"){
                    plog->write("[ExtProcess] Git Update : Already Newest");
                    param = 1;
                }else{
                    plog->write("[ExtProcess] Git update : Failed");
                }
            }else if(_return.command == PROCESS_CMD_GIT_RESET){
                plog->write("[ExtProcess] Git reset : Failed");
            }
            emit got_error(_return.command,param);
        }
        prev_tick = _return.tick;
    }

    if(!process_working){
        if(command_list.size() > 0){
            shm_command.lock();
            command_list[0].tick = ++tick;
            memcpy((char*)shm_command.data(), &command_list[0], sizeof(ExtProcess::Command));

            timeout_sec = 10000;
            prev_cmd = command_list[0].cmd;
            command_list.pop_front();
            shm_command.unlock();
        }
    }

    ExtProcess::WifiList _wifilist = get_wifilist();
    if(_wifilist.tick != prev_wifilist_tick){
        WifiList temp_wifi_list;
        for(int i=0; i<_wifilist.size; i++){
            ST_WIFI temp_wifi;
            char temp[100];
            memcpy(temp,_wifilist.ssid[i],sizeof(char)*100);
            temp_wifi.ssid = QString::fromUtf8(temp);
            temp_wifi.inuse = _wifilist.param[i][0];
            temp_wifi.rate = _wifilist.param[i][1];
            temp_wifi.level = _wifilist.param[i][2];
            temp_wifi.security = _wifilist.param[i][3];
            temp_wifi.discon_count = _wifilist.param[i][4];
            temp_wifi.state = _wifilist.param[i][5];
            temp_wifi.prev_state = _wifilist.param[i][6];

            if(temp_wifi.level>1){
                probot->wifi_map[temp_wifi.ssid] = temp_wifi;
                if(temp_wifi.inuse){
                    if(getSetting("setting","NETWORK","wifi_ssid") == ""){
                        setSetting("setting","NETWORK/wifi_ssid",temp_wifi.ssid);
                    }
                }
            }
            prev_wifilist_tick = _wifilist.tick;
        }

        QList<QString> keys = probot->wifi_map.keys();
        for(int i=0; i<keys.size(); i++){
            if(probot->wifi_map[keys[i]].discon_count++ > 5){
                probot->wifi_map.remove(keys[i]);
            }
        }
    }
    //timeout check
    if(process_working){
        if(timeout_count++ > timeout_sec/THREAD_EXTPROCESS){
            process_working = false;
            plog->write("[ExtProcess] Timeout ");
            emit timeout(prev_cmd);
        }
    }
#endif
}

void ExtProcess::update_unzip(){
    Command temp;
    temp.cmd = PROCESS_CMD_UNZIP;
    QString zippath = QDir::homePath()+"/RB_MOBILE/temp/update.zip";
    QString folderpath = QDir::homePath()+"/RB_MOBILE/temp/update";
    memcpy(temp.params,zippath.toUtf8(),100);
    memcpy(temp.params2,folderpath.toUtf8(),100);
    set_command(temp, "UnZip");
}

void ExtProcess::git_pull(){
    Command temp;
//    temp.cmd = PROCESS_CMD_GIT_PULL;
    temp.cmd = PROCESS_CMD_GIT_UPDATE;
    QString path = QDir::homePath()+"/RB_MOBILE";
//    QString path = QApplication::applicationDirPath();
    if(path.toUtf8().size() > 100){
        memcpy(temp.params,path.left(100).toUtf8(),100);
        path.remove(0,100);
        memcpy(temp.params2,path.toUtf8(),100);
    }else{
        memcpy(temp.params,path.toUtf8(),100);
    }
    set_command(temp,"Git Update");
}

void ExtProcess::git_reset(){
    Command temp;
    temp.cmd = PROCESS_CMD_GIT_RESET;
    QString path = QApplication::applicationDirPath();
    if(path.toUtf8().size() > 100){
        memcpy(temp.params,path.left(100).toUtf8(),100);
        path.remove(0,100);
        memcpy(temp.params2,path.toUtf8(),100);
    }else{
        memcpy(temp.params,QApplication::applicationDirPath().toUtf8(),100);
    }
    set_command(temp,"Git Reset");
}
void ExtProcess::set_command(Command cmd, QString log){
    bool match = false;
    for(int i=0; i<command_list.size(); i++){
        if(command_list[i].cmd == cmd.cmd){
            match = true;
        }
    }
    if(!match){
        command_list.push_back(cmd);
    }
}

ExtProcess::WifiList ExtProcess::get_wifilist(){
    ExtProcess::WifiList res;
    shm_wifilist.lock();
    memcpy(&res, (char*)shm_wifilist.constData(), sizeof(ExtProcess::WifiList));
    shm_wifilist.unlock();

    return res;
}
ExtProcess::Return ExtProcess::get_return(){
    ExtProcess::Return res;
    shm_return.lock();
    memcpy(&res, (char*)shm_return.constData(), sizeof(ExtProcess::Return));
    shm_return.unlock();

    return res;
}

ExtProcess::Command ExtProcess::get_command(){
    ExtProcess::Command res;
    shm_command.lock();
    memcpy(&res, (char*)shm_command.constData(), sizeof(ExtProcess::Command));
    shm_command.unlock();
    return res;
}
