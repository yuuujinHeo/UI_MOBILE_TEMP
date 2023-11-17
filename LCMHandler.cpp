#include "LCMHandler.h"
#include <QQmlApplicationEngine>
#include <iostream>
#include <QDebug>
#include <QPixmap>


LCMHandler::LCMHandler()
    : lcm("udpm://239.255.76.67:7667?ttl=1")
{
    if(bThread == NULL){
        bFlag = true;
        bThread = new std::thread(&LCMHandler::bLoop, this);
    }

    probot->joystick[0] = 0;
    probot->joystick[1] = 0;

    timer = new QTimer();
    connect(timer, SIGNAL(timeout()),this,SLOT(onTimer()));
    timer->start(200);

    plog->write("[BUILDER] LCM HANDLER constructed");
}

LCMHandler::~LCMHandler(){
    if(bThread != NULL)
    {
        bFlag = false;
        bThread->join();
    }
    plog->write("[BUILDER] LCM HANDLER destroyed");
}



////*********************************************  COMMAND FUNCTIONS   ***************************************************////
void LCMHandler::sendCommand(command cmd, QString msg, bool force){
    if(!pmap->use_uicmd){
        if(msg != ""){
            plog->write("[LCM ERROR] SEND COMMAND (BLOCKED) : " + msg);
        }
    }else if(isconnect){
        if(is_debug){
            lcm.publish("COMMAND_"+probot->name_debug.toStdString(),&cmd);
            if(msg != ""){
                plog->write("[LCM] SEND COMMAND TO COMMAND_" + probot->name_debug + ": " + msg);
            }
        }else{
            lcm.publish("COMMAND_"+probot->name.toStdString(),&cmd);
            if(msg != ""){
                plog->write("[LCM] SEND COMMAND TO COMMAND_" + probot->name + ": " + msg);
            }
        }
        flag_tx = true;
    }else{
//        lcm.publish("COMMAND_"+probot->name.toStdString(),&cmd);
        if(msg != ""){
            plog->write("[LCM ERROR] SEND COMMAND (DISCONNECTED) TO COMMAND_" + probot->name + ": " + msg);
        }
    }
}

void LCMHandler::sendCommand(int cmd, QString msg){
    command send_msg;
    send_msg.cmd = cmd;

    if(!pmap->use_uicmd){
        if(msg != ""){
            plog->write("[LCM ERROR] SEND COMMAND (BLOCKED) : " + msg);
        }
    }else if(isconnect){
        if(is_debug){
            lcm.publish("COMMAND_"+probot->name_debug.toStdString(),&send_msg);
            if(msg != ""){
                plog->write("[LCM] SEND COMMAND TO COMMAND_" + probot->name_debug + ": " + msg);
            }
        }else{
            lcm.publish("COMMAND_"+probot->name.toStdString(),&send_msg);
            if(msg != ""){
                plog->write("[LCM] SEND COMMAND TO COMMAND_" + probot->name + ": " + msg);
            }
        }
        flag_tx = true;
    }else{
        if(msg != ""){
            plog->write("[LCM ERROR] SEND COMMAND (DISCONNECTED) TO COMMAND_" + probot->name + ": " + msg);
        }
        lcm.publish("COMMAND_"+probot->name.toStdString(),&send_msg);
    }
}

void LCMHandler::moveToLast(){
    command send_msg;
    send_msg.cmd = ROBOT_CMD_MOVE_LOCATION;
    memcpy(send_msg.params,probot->curLocation.name.toUtf8(),sizeof(char)*255);

    sendCommand(send_msg, "MOVE LOCATION TO"+probot->curLocation.name);
}
void LCMHandler::moveTo(QString target_loc){
    command send_msg;
    send_msg.cmd = ROBOT_CMD_MOVE_LOCATION;
    memcpy(send_msg.params,target_loc.toUtf8(),sizeof(char)*255);

//    probot->curLocation = target_loc;
    sendCommand(send_msg, "MOVE LOCATION TO"+target_loc);
}

void LCMHandler::moveTo(float x, float y, float th){
    command send_msg;
    send_msg.cmd = ROBOT_CMD_MOVE_TARGET;
    uint8_t *array;
    array = reinterpret_cast<uint8_t*>(&x);
    send_msg.params[0] = array[0];
    send_msg.params[1] = array[1];
    send_msg.params[2] = array[2];
    send_msg.params[3] = array[3];
    array = reinterpret_cast<uint8_t*>(&y);
    send_msg.params[4] = array[0];
    send_msg.params[5] = array[1];
    send_msg.params[6] = array[2];
    send_msg.params[7] = array[3];
    array = reinterpret_cast<uint8_t*>(&th);
    send_msg.params[8] = array[0];
    send_msg.params[9] = array[1];
    send_msg.params[10]= array[2];
    send_msg.params[11]= array[3];

    probot->curTarget.point.x = x;
    probot->curTarget.point.y = y;
    probot->curTarget.angle = th;
    sendCommand(send_msg, "MOVE TARGET TO"+QString().sprintf("%f, %f, %f",x,y,th));
}
void LCMHandler::movePause(){
    command send_msg;
    send_msg.cmd = ROBOT_CMD_MOVE_PAUSE;
    sendCommand(send_msg, "MOVE PAUSE");
}
void LCMHandler::moveResume(){
    command send_msg;
    send_msg.cmd = ROBOT_CMD_MOVE_RESUME;
    sendCommand(send_msg, "MOVE RESUME");
}
void LCMHandler::moveJog(){
    command send_msg;
    send_msg.cmd = ROBOT_CMD_MOVE_JOG;
    uint8_t *array;
    array = reinterpret_cast<uint8_t*>(&probot->joystick[0]);
    send_msg.params[0] = array[0];
    send_msg.params[1] = array[1];
    send_msg.params[2] = array[2];
    send_msg.params[3] = array[3];

    array = reinterpret_cast<uint8_t*>(&probot->joystick[1]);
    send_msg.params[4] = array[0];
    send_msg.params[5] = array[1];
    send_msg.params[6] = array[2];
    send_msg.params[7] = array[3];

    sendCommand(send_msg, "MOVE JOYSTICK "+QString().sprintf("%f, %f",probot->joystick[0],probot->joystick[1]));
}
void LCMHandler::moveStop(){
    command send_msg;
    send_msg.cmd = ROBOT_CMD_MOVE_STOP;
    sendCommand(send_msg, "MOVE STOP");
}
void LCMHandler::moveManual(){
    command send_msg;
    send_msg.cmd = ROBOT_CMD_MOVE_MANUAL;
    sendCommand(send_msg, "MOVE MANUAL START");
}

void LCMHandler::setVelocity(float vel){
    command send_msg;
    send_msg.cmd = ROBOT_CMD_SET_VELOCITY;
    uint8_t *array;
    array = reinterpret_cast<uint8_t*>(&vel);
    send_msg.params[0] = array[0];
    send_msg.params[1] = array[1];
    send_msg.params[2] = array[2];
    send_msg.params[3] = array[3];

    sendCommand(send_msg, "SET VELOCITY TO "+QString().sprintf("%f",vel));
}

void LCMHandler::programStart(){
}

void LCMHandler::setInitPose(float x, float y, float th){
    command send_msg;
    send_msg.cmd = ROBOT_CMD_SET_INIT;
    uint8_t *array;
    array = reinterpret_cast<uint8_t*>(&x);
    send_msg.params[0] = array[0];
    send_msg.params[1] = array[1];
    send_msg.params[2] = array[2];
    send_msg.params[3] = array[3];
    array = reinterpret_cast<uint8_t*>(&y);
    send_msg.params[4] = array[0];
    send_msg.params[5] = array[1];
    send_msg.params[6] = array[2];
    send_msg.params[7] = array[3];
    array = reinterpret_cast<uint8_t*>(&th);
    send_msg.params[8] = array[0];
    send_msg.params[9] = array[1];
    send_msg.params[10] = array[2];
    send_msg.params[11] = array[3];

    sendCommand(send_msg, "SET INIT "+QString().sprintf("%f, %f, %f",x,y,th));
}

void LCMHandler::restartSLAM(){
    command send_msg;
    send_msg.cmd = ROBOT_CMD_RESTART;
    QString msg = "RESTART SLAM";
    if(!pmap->use_uicmd){
        plog->write("[LCM ERROR] SEND COMMAND (BLOCKED) : " + msg);
    }else if(isconnect){
        lcm.publish("COMMAND_"+probot->name.toStdString(),&send_msg);
        plog->write("[LCM] SEND COMMAND TO COMMAND_" + probot->name + ": " + msg);
        flag_tx = true;
    }else{
        if(msg != ""){
            plog->write("[LCM ERROR] SEND COMMAND (DISCONNECTED) TO COMMAND_" + probot->name + ": " + msg);
            lcm.publish("COMMAND_"+probot->name.toStdString(),&send_msg);
        }
    }
}

void LCMHandler::sendMapPath(QString path){
    command send_msg;
    send_msg.cmd = ROBOT_CMD_RESTART;
    memcpy(send_msg.params,path.toUtf8(),sizeof(char)*255);

    sendCommand(send_msg,"SEND MAP PATH ("+path+")");
}

void LCMHandler::startMapping(float grid_size){
    command send_msg;
    send_msg.cmd = ROBOT_CMD_MAPPING_START;
    uint8_t *array;
    array = reinterpret_cast<uint8_t*>(&grid_size);
    send_msg.params[0] = array[0];
    send_msg.params[1] = array[1];
    send_msg.params[2] = array[2];
    send_msg.params[3] = array[3];
    sendCommand(send_msg,"START MAPPING "+QString().sprintf("(grid size = %f)",grid_size));
}

void LCMHandler::saveMapping(QString name){
    command send_msg;
    send_msg.cmd = ROBOT_CMD_MAPPING_SAVE;
    memcpy(send_msg.params,name.toUtf8(),sizeof(char)*255);
    sendCommand(send_msg,"SAVE MAPPING ("+name+")");
}

void LCMHandler::startObjecting(){
    command send_msg;
    send_msg.cmd = ROBOT_CMD_OBJECTING_START;
    sendCommand(send_msg,"START OBJECTING ");
}

void LCMHandler::saveObjecting(){
    command send_msg;
    send_msg.cmd = ROBOT_CMD_OBJECTING_SAVE;
    sendCommand(send_msg,"SAVE OBJECTING");
}
////*********************************************  CALLBACK FUNCTIONS   ***************************************************////
void LCMHandler::robot_status_callback(const lcm::ReceiveBuffer *rbuf, const std::string &chan, const robot_status *msg){
#ifdef NO_LCM
#else
    isconnect = true;
//    qDebug() << "read Status";
    flag_rx = true;
    connect_count = 0;
    probot->battery_in = msg->bat_in;
    probot->battery_out = msg->bat_out;
    probot->battery = (msg->bat_in-44)*100/10;
    if(probot->battery > 100) probot->battery = 100;
    if(probot->battery < 0) probot->battery = 0;

    probot->battery_cur = msg->bat_cur;
    probot->motor[0].connection = msg->connection_m0;
    probot->motor[1].connection = msg->connection_m1;
    probot->motor[0].status = msg->status_m0;
    probot->motor[1].status = msg->status_m1;
    probot->motor[0].temperature = msg->temp_m0;
    probot->motor[1].temperature = msg->temp_m1;
    probot->motor[0].current = msg->cur_m0;
    probot->motor[1].current = msg->cur_m1;
    probot->status_power = msg->status_power;
    if(probot->status_emo == msg->status_emo){
        plog->write("[LCM] EMO status changed !! "+QString::number(!msg->status_emo));
    }
    probot->status_emo = !msg->status_emo;
    probot->status_remote = msg->status_remote;
    //DEBUG
    probot->status_charge = msg->status_charge;
    probot->motor_state = msg->ui_motor_state;
    probot->localization_state = msg->ui_loc_state;
    probot->running_state = msg->ui_auto_state;
    probot->obs_state = msg->ui_obs_state;
    probot->curPose.point.x = msg->robot_pose[0];
    probot->curPose.point.y = msg->robot_pose[1];
    probot->curPose.angle = msg->robot_pose[2];
    for(int i=0; i<360; i++){
        probot->lidar_data[i] = msg->robot_scan[i];
    }
#endif
}

void LCMHandler::robot_path_callback(const lcm::ReceiveBuffer *rbuf, const std::string &chan, const robot_path *msg){
    isconnect = true;
    flag_rx = true;
    connect_count = 0;
    flagPath = true;
    probot->pathSize = msg->num;
    qDebug() <<"ROBOT PATH CALL BACK " << probot->pathSize;
    for(int i=0; i<probot->pathSize; i++){
        POSE temp;
        temp.point.x = msg->path[i][0];
        temp.point.y = msg->path[i][1];
        temp.angle = 0;//msg->path[i][2];
        if(probot->curPath.size() > i){
            probot->curPath[i] = temp;
        }else{
            probot->curPath.push_back(temp);
        }
    }
    emit pathchanged();
    flagPath = false;
}

void LCMHandler::robot_local_path_callback(const lcm::ReceiveBuffer *rbuf, const std::string &chan, const robot_path *msg){
    qDebug() << "PATH CALLBACK " << msg->num;
    isconnect = true;
    flag_rx = true;
    connect_count = 0;
    flagLocalPath = true;
    probot->localpathSize = msg->num;
    for(int i=0; i<probot->localpathSize; i++){
        POSE temp;
        temp.point.x = msg->path[i][0];
        temp.point.y = msg->path[i][1];
        temp.angle = msg->path[i][2];
        probot->localPath[i] = temp;
    }
    flagLocalPath = false;
}

void LCMHandler::robot_mapping_callback(const lcm::ReceiveBuffer *rbuf, const std::string &chan, const map_data *msg){
    isconnect = true;
    connect_count = 0;

     cv::Mat map1(msg->map_h, msg->map_w, CV_8U, cv::Scalar::all(0));
     memcpy(map1.data, msg->data.data(), msg->len);
     cv::flip(map1, map1, 0);
     cv::rotate(map1, map1, cv::ROTATE_90_COUNTERCLOCKWISE);

     pmap->map_mapping = map1;

     flagMapping = true;
     emit mappingin();
}

void LCMHandler::robot_objecting_callback(const lcm::ReceiveBuffer *rbuf, const std::string &chan, const map_data *msg){
     isconnect = true;
     connect_count = 0;

     cv::Mat map1(msg->map_h, msg->map_w, CV_8U, cv::Scalar::all(0));
     memcpy(map1.data, msg->data.data(), msg->len);
     cv::flip(map1, map1, 0);
     cv::rotate(map1, map1, cv::ROTATE_90_COUNTERCLOCKWISE);

     pmap->map_objecting = map1;

     flagObjecting = true;
     emit objectingin();
}

void LCMHandler::robot_command_callback(const lcm::ReceiveBuffer *rbuf, const std::string &chan, const command *msg){
//    qDebug() << "COMMAND CALLBACK" << msg->cmd;
}

void LCMHandler::robot_camera_callback(const lcm::ReceiveBuffer *rbuf, const std::string &chan, const camera_data *msg){
    for(int i=0; i<msg->num; i++){
        ST_CAMERA temp_info;
        temp_info.serial = QString::fromStdString(msg->serial[i]);
        temp_info.imageSize = msg->image_len;
        temp_info.width = msg->width;
        temp_info.height = msg->height;
        qDebug() << msg->width << msg->height;

         cv::Mat map(temp_info.height, temp_info.width, CV_8U, cv::Scalar::all(0));
         memcpy(map.data, msg->image[i].data(), temp_info.width*temp_info.height);
         temp_info.pixmap = QPixmap::fromImage(mat_to_qimage_cpy(map));
//         cv::imshow("map",map);
         if(pmap->camera_info.count() > i){
             pmap->camera_info[i] = temp_info;
         }else{
             pmap->camera_info.push_back(temp_info);
         }
    }
    try{
        emit cameraupdate();
    }catch(std::bad_alloc){
        qDebug() << "bad alloc?";
    }
}
////***********************************************   THREADS  ********************************************************////
void LCMHandler::bLoop()
{
    /*
    sudo ifconfig lo multicast
    sudo route add -net 224.0.0.0 netmask 240.0.0.0 dev lo
    */

    // lcm init
//    if(!lcm.good())
//    {
//        plog->write("[LCM ERROR] LCM CONNECT FAILED");
//        isconnect = false;
//    }

//    while(bFlag)
//    {
//        lcm.handleTimeout(1);
//    }
}

void LCMHandler::subscribe(){
//    lcm.unsubscribe(sub_status);
//    lcm.unsubscribe(sub_path);
//    lcm.unsubscribe(sub_localpath);
//    lcm.unsubscribe(sub_mapping);
//    lcm.unsubscribe(sub_objecting);
//    lcm.unsubscribe(sub_camera);
//    lcm.unsubscribe(sub_test_cmd);
//    if(is_debug){
//        qDebug() << "Change Subscribe " << probot->name_debug;
//        sub_mapping = lcm.subscribe("MAP_DATA_"+probot->name_debug.toStdString(), &LCMHandler::robot_mapping_callback, this);
//        sub_objecting = lcm.subscribe("OBS_DATA_"+probot->name_debug.toStdString(), &LCMHandler::robot_objecting_callback, this);
//        sub_status = lcm.subscribe("STATUS_DATA_"+probot->name_debug.toStdString(), &LCMHandler::robot_status_callback, this);
//        sub_path = lcm.subscribe("ROBOT_PATH_"+probot->name_debug.toStdString(), &LCMHandler::robot_path_callback, this);
//        sub_localpath = lcm.subscribe("ROBOT_LOCAL_PATH_"+probot->name_debug.toStdString(), &LCMHandler::robot_local_path_callback, this);
//        sub_camera = lcm.subscribe("CAMERA_DATA_"+probot->name_debug.toStdString(), &LCMHandler::robot_camera_callback, this);
//    }else{
//        qDebug() << "Change Subscribe " << probot->name;
//        sub_mapping = lcm.subscribe("MAP_DATA_"+probot->name.toStdString(), &LCMHandler::robot_mapping_callback, this);
//        sub_objecting = lcm.subscribe("OBS_DATA_"+probot->name.toStdString(), &LCMHandler::robot_objecting_callback, this);
//        sub_status = lcm.subscribe("STATUS_DATA_"+probot->name.toStdString(), &LCMHandler::robot_status_callback, this);
//        sub_path = lcm.subscribe("ROBOT_PATH_"+probot->name.toStdString(), &LCMHandler::robot_path_callback, this);
//        sub_localpath = lcm.subscribe("ROBOT_LOCAL_PATH_"+probot->name.toStdString(), &LCMHandler::robot_local_path_callback, this);
//        sub_camera = lcm.subscribe("CAMERA_DATA_"+probot->name.toStdString(), &LCMHandler::robot_camera_callback, this);
//        sub_test_cmd = lcm.subscribe("COMMAND_"+probot->name.toStdString(), &LCMHandler::robot_command_callback, this);
//    }
}
void LCMHandler::onTimer(){
    //10ms 조이스틱 값 읽어오기
//    if(flagJoystick){
//        moveJog();
//        flagJoystick = false;
//    }else{
//        if(probot->joystick[0] != 0 || probot->joystick[1] != 0 ){
//            moveJog();
//        }
//    }

//    if(is_mapping){

//    }else{
//        if(flagMapping){
//            sendCommand(ROBOT_CMD_MAPPING_STOP, "MAPPING STOP");
//        }
//        flagMapping = false;
//    }

//    if(is_objecting){

//    }else{
//        flagObjecting = false;
//    }

//    static int count=0;
//    if(count++%5==0){
//        flag_rx = false;
//        flag_tx = false;
//    }

//    //LCM 통신 연결상태 확인(2초)
//    if(connect_count++ > 5){
//        isconnect = false;
//    }

//    if(isconnect && probot->localization_state==LOCAL_READY){
//        probot->lastPose = probot->curPose;
//    }
}
