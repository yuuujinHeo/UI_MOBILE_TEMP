#include "IPCHandler.h"

IPCHandler::IPCHandler(QObject *parent)
    : QObject(parent)
    , shm_cmd("slamnav_cmd")
    , shm_status("slamnav_status")
    , shm_path("slamnav_path")
    , shm_map("slamnav_map")
    , shm_obs("slamnav_obs")
    , shm_cam0("slamnav_cam0")
    , shm_cam1("slamnav_cam1")
    , shm_ui_status("slamnav_ui_status")
    , shm_cam_color0("slamnav_cam_color0")
    , shm_cam_color1("slamnav_cam_color1")
    , shm_loc_status("slamnav_loc_status")
    , shm_call_status("slamnav_call_status")
    , shm_call_loc("slamnav_call_loc")
    , shm_check_travel("slamnav_check_travel")
{
    // msg tick clear, check for new data
    tick = 0;

    // create or attach
    updateSharedMemory(shm_cmd,"Command",sizeof(IPCHandler::CMD));
    updateSharedMemory(shm_ui_status,"UiStatus",sizeof(IPCHandler::UI_STATUS));
    updateSharedMemory(shm_status,"Status",sizeof(IPCHandler::STATUS));
    updateSharedMemory(shm_path,"Path",sizeof(IPCHandler::PATH));
    updateSharedMemory(shm_map,"Map",sizeof(IPCHandler::MAP));
    updateSharedMemory(shm_obs,"ObsMap",sizeof(IPCHandler::MAP));
    updateSharedMemory(shm_cam0,"Camera0",sizeof(IPCHandler::IMG));
    updateSharedMemory(shm_cam1,"Camera1",sizeof(IPCHandler::IMG));
    updateSharedMemory(shm_cam_color0,"CameraColor0",sizeof(IPCHandler::IMG_COLOR));
    updateSharedMemory(shm_cam_color1,"CameraColor1",sizeof(IPCHandler::IMG_COLOR));
    updateSharedMemory(shm_loc_status,"LocationStatus",sizeof(IPCHandler::LOC_STATUS));
    updateSharedMemory(shm_call_loc,"CallLocation",sizeof(IPCHandler::CALL_LOC));
    updateSharedMemory(shm_call_status,"CallStatus",sizeof(IPCHandler::CALL_STATUS));
    updateSharedMemory(shm_check_travel,"CheckTravel",sizeof(IPCHandler::CHECK_TRAVEL));
    clearSharedMemory(shm_cmd);
    clearSharedMemory(shm_call_status);
    clearSharedMemory(shm_call_loc);
    clearSharedMemory(shm_check_travel);

    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimer()));
    timer->start(200);

    probot->ipc_use = true;
    if(probot->ipc_use){
        plog->write("[IPC] IPCHandler Constructed. IPC_USE = TRUE");
    }else{
        plog->write("[IPC] IPCHandler Constructed. IPC_USE = FALSE");
    }
}

void IPCHandler::clearSharedMemory(QSharedMemory &mem){
    if(mem.isAttached()){
        mem.lock();
        memset(mem.data(),0,sizeof(mem.data()));
        mem.unlock();
        plog->write("[IPC] Clear CMD ShardMemory");
    }
}

void IPCHandler::updateSharedMemory(QSharedMemory &mem, QString name, int size){
    if(!mem.isAttached()){
        if (!mem.create(size, QSharedMemory::ReadWrite) && mem.error() == QSharedMemory::AlreadyExists)
        {
            if(mem.attach()){
                plog->write("[IPC] "+name+" is already exist. attach success. ");
            }else{
                plog->write("[IPC] "+name+" is already exist. attach failed. ");
            }
        }
        else
        {
            plog->write("[IPC] "+name+" is created. size : "+QString::number(size));
        }
    }
}
void IPCHandler::detachSharedMemory(QSharedMemory &mem, QString name){
    if(shm_cmd.detach())
    {
        plog->write("[IPC] "+name+" is detached success.");
    }else{
        plog->write("[IPC] "+name+" is detached failed.");
    }
}
void IPCHandler::update(){
    updateSharedMemory(shm_cmd,"Command",sizeof(IPCHandler::CMD));
    updateSharedMemory(shm_ui_status,"UiStatus",sizeof(IPCHandler::UI_STATUS));
    updateSharedMemory(shm_status,"Status",sizeof(IPCHandler::STATUS));
    updateSharedMemory(shm_path,"Path",sizeof(IPCHandler::PATH));
    updateSharedMemory(shm_map,"Map",sizeof(IPCHandler::MAP));
    updateSharedMemory(shm_obs,"ObsMap",sizeof(IPCHandler::MAP));
    updateSharedMemory(shm_cam0,"Camera0",sizeof(IPCHandler::IMG));
    updateSharedMemory(shm_cam1,"Camera1",sizeof(IPCHandler::IMG));
    updateSharedMemory(shm_cam_color0,"CameraColor0",sizeof(IPCHandler::IMG_COLOR));
    updateSharedMemory(shm_cam_color1,"CameraColor1",sizeof(IPCHandler::IMG_COLOR));
    updateSharedMemory(shm_loc_status,"LocationStatus",sizeof(IPCHandler::LOC_STATUS));
    updateSharedMemory(shm_call_loc,"CallLocation",sizeof(IPCHandler::CALL_LOC));
    updateSharedMemory(shm_call_status,"CallStatus",sizeof(IPCHandler::CALL_STATUS));
    updateSharedMemory(shm_check_travel,"CheckTravel",sizeof(IPCHandler::CHECK_TRAVEL));

}

IPCHandler::~IPCHandler()
{
    detachSharedMemory(shm_cmd,"Command");
    detachSharedMemory(shm_ui_status,"UiStatus");
    detachSharedMemory(shm_status,"Status");
    detachSharedMemory(shm_path,"Path");
    detachSharedMemory(shm_map,"Map");
    detachSharedMemory(shm_obs,"ObsMap");
    detachSharedMemory(shm_cam0,"Camera0");
    detachSharedMemory(shm_cam1,"Camera1");
    detachSharedMemory(shm_cam_color0,"CameraColor0");
    detachSharedMemory(shm_cam_color1,"CameraColor1");
    detachSharedMemory(shm_loc_status,"LocationStatus");
    detachSharedMemory(shm_call_loc,"CallLocation");
    detachSharedMemory(shm_call_status,"CallStatus");
    detachSharedMemory(shm_check_travel,"CheckTravel");

}

void IPCHandler::onTimer(){
    if(is_mapping){

    }else{
        if(flag_mapping){
            set_cmd(ROBOT_CMD_MAPPING_STOP, "MAPPING STOP");
        }
        flag_mapping = false;
    }

    if(is_objecting){

    }else{
        flag_objecting = false;
    }

    set_status_ui();
    if(getConnection() && probot->localization_state==LOCAL_READY){
        probot->lastPose = probot->curPose;
    }

    IPCHandler::STATUS temp1 = get_status();
    if(temp1.tick != prev_tick_status){
        flag_rx = true;
        read_count = 0;
        probot->battery_in = temp1.bat_in;
        probot->battery_out = temp1.bat_out;
        probot->power = temp1.power;
        probot->total_power = temp1.total_power;

        probot->bat_list.push_back(probot->battery_in);
        if(probot->bat_list.size() > 3){
            probot->bat_list.pop_front();
        }

        float sum_battery = 0;
        for(int i=0; i<probot->bat_list.size(); i++){
            sum_battery += probot->bat_list[i];
        }

        float av_battery = sum_battery/probot->bat_list.size();

        if(probot->battery < av_battery){
            probot->battery = av_battery;
        }else if(probot->battery - av_battery > 0.5){
            probot->battery = av_battery;
        }

        probot->battery_percent = (probot->battery-44)*100/10;

        if(probot->battery_percent > 100)
            probot->battery_percent = 100;
        if(probot->battery_percent < 0)
            probot->battery_percent = 0;

        probot->battery_cur = temp1.bat_cur;
        probot->motor[0].connection = temp1.connection_m0;
        probot->motor[1].connection = temp1.connection_m1;
        probot->motor[0].status = temp1.status_m0;
        probot->motor[1].status = temp1.status_m1;
        probot->motor[0].temperature = temp1.temp_m0;
        probot->motor[1].temperature = temp1.temp_m1;
        probot->motor[0].motor_temp = temp1.temp_ex_m0;
        probot->motor[1].motor_temp = temp1.temp_ex_m1;

//        qDebug() << probot->motor[0].motor_temp << probot->motor[1].motor_temp;
        probot->motor[0].current = temp1.cur_m0/10;
        probot->motor[1].current = temp1.cur_m1/10;
//        qDebug() << temp1.temp_ex_m0 << temp1.cur_m0;
        probot->status_power = temp1.status_power;
        if(probot->status_emo == temp1.status_emo){
            plog->write("[IPC] EMO status changed !! "+QString::number(!temp1.status_emo));
        }

        if(probot->status_lock != temp1.ui_motor_lock_state){
            plog->write("[IPC] MOTOR LOCK status changed !! "+QString::number(temp1.ui_motor_lock_state));
        }

        probot->status_lock = temp1.ui_motor_lock_state;
        probot->status_emo = !temp1.status_emo;
        probot->status_remote = temp1.status_remote;
        //DEBUG
        probot->status_charge = temp1.status_charge;
        probot->localization_state = temp1.ui_loc_state;
//        qDebug() << probot->localization_state;
        if(probot->localization_state == 2){
            pmap->cut_map[0] = 0;
            pmap->cut_map[1] = 0;
        }
        probot->multirobot_state = temp1.ui_multi_state;
        probot->running_state = temp1.ui_auto_state;
        probot->obs_state = temp1.ui_obs_state;
        probot->ui_fail_state = temp1.ui_fail_state;
        probot->robot_preset = temp1.ui_cur_velocity_preset;
        probot->obs_in_path_state = temp1.ui_face_state;
        probot->curPose.point.x = temp1.robot_pose[0];
        probot->curPose.point.y = temp1.robot_pose[1];
//        qDebug() << "status" << probot->localization_state;
        probot->curPose.angle = temp1.robot_pose[2];
        for(int i=0; i<360; i++){
            probot->lidar_data[i] = temp1.robot_scan[i];
        }
        probot->inlier_ratio = temp1.ui_loc_inlier_ratio;
        probot->inlier_error = temp1.ui_loc_inlier_error;
//        qDebug() << probot->curPose.point.x << probot->curPose.point.y << probot->curPose.angle << probot->lidar_data[0];
        prev_tick_status = temp1.tick;
    }

    IPCHandler::PATH temp2 = get_path();
    if(temp2.tick != prev_tick_path){
        flag_rx = true;
        read_count = 0;

        QList<POSE> temp_path;
        probot->pathSize = temp2.num;
        for(int i=0; i<probot->pathSize; i++){
            POSE temp;
            temp.point.x = temp2.x[i];
            temp.point.y = temp2.y[i];
            temp.angle = 0;
            temp_path.push_back(temp);
        }
        probot->curPath = temp_path;
        prev_tick_path = temp2.tick;
        emit pathchanged();
    }

    IPCHandler::CHECK_TRAVEL tempp = get_check_travel();
    if(tempp.tick != prev_tick_check_travel){
        flag_rx = true;
        read_count = 0;

        pmap->tline_issue = tempp.num;

        for(int i=0; i<pmap->tline_issue; i++){
            char temp_char[255];
            for (int a = 0; a < 255; a++) {
                temp_char[a] = (char)tempp.name[i][a];
            }
            pmap->tline_issues[i].name = QString::fromUtf8(temp_char);
            for (int a = 0; a < 255; a++) {
                temp_char[a] = (char)tempp.group[i][a];
            }
            pmap->tline_issues[i].group = QString::fromUtf8(temp_char);


            pmap->tline_issues[i].is_far = tempp.is_far[i];
            pmap->tline_issues[i].is_broken = tempp.is_broken[i];
//            plog->write("[IPC] Travelline Issue : "+pmap->tline_issues[i].group+", "+pmap->tline_issues[i].name+" -> "+QString().asprintf("%d, %d",tempp.is_far[i],tempp.is_broken[i]));

        }
    }

    IPCHandler::MAP temp3 = get_map();
    if(temp3.tick != prev_tick_map){
//        qDebug() << "map " << temp1.tick;
        flag_rx = true;
        read_count = 0;


        cv::Mat map1(temp3.height, temp3.width, CV_8U, cv::Scalar::all(0));
        memcpy((uint8_t*)map1.data, temp3.buf, temp3.height*temp3.width);
        cv::flip(map1, map1, 0);
        cv::rotate(map1, map1, cv::ROTATE_90_COUNTERCLOCKWISE);

        pmap->map_mapping = map1;

        if(is_mapping){
            flag_mapping = true;
        }
        prev_tick_map = temp3.tick;
        emit mappingin();
    }

    temp3 = get_obs();
    if(temp3.tick != prev_tick_obs){
        flag_rx = true;
        qDebug() << "obs " << temp3.tick;
        read_count = 0;

        cv::Mat map1(temp3.height, temp3.width, CV_8U, cv::Scalar::all(0));
        memcpy((uint8_t*)map1.data, temp3.buf, temp3.width*temp3.height);
        cv::flip(map1, map1, 0);
        cv::rotate(map1, map1, cv::ROTATE_90_COUNTERCLOCKWISE);

//        cv::Mat colortemp(temp3.height, temp3.width, CV_8UC3, cv::Scalar(127,255,200));
//        cv::Mat a(temp3.height, temp3.width, CV_32F, cv::Scalar::all(0.5));
//        cv::cvtColor(colortemp,colortemp,cv::COLOR_BGR2GRAY);

//        cv::bl"\n"inear(map1,colortemp,a,a,map1);
        pmap->map_objecting = map1;

        flag_objecting = true;
        prev_tick_obs = temp3.tick;
        emit objectingin();
    }

    IPCHandler::IMG cam0 = get_cam0();
    if(cam0.tick != prev_tick_cam0)
    {
        flag_rx = true;
        read_count = 0;
        ST_CAMERA temp_info;
        char temp_char[255];
        for (int a = 0; a < 255; a++) {
            temp_char[a] = (char)cam0.serial[a];
        }
        char* temp_pchar = &temp_char[0];
        temp_info.serial = QString::fromUtf8(temp_pchar);
//        qDebug() << temp_info.serial;

        temp_info.width = cam0.width;
        temp_info.height = cam0.height;
        temp_info.imageSize = cam0.width*cam0.height;


        cv::Mat cam0_img(temp_info.height, temp_info.width, CV_8U, cv::Scalar(0));
        memcpy((uint8_t*)cam0_img.data, cam0.buf, sizeof(cam0.buf));
        temp_info.pixmap = QPixmap::fromImage(mat_to_qimage_cpy(cam0_img));

        if(pmap->camera_info.count() > 0){
            pmap->camera_info[0] = temp_info;
        }else{
            pmap->camera_info.push_back(temp_info);
        }

        try{
            emit cameraupdate();
        }catch(std::bad_alloc){
            qDebug() << "bad alloc?";
        }
        prev_tick_cam0 = cam0.tick;
    }

    IPCHandler::IMG cam1 = get_cam1();
    if(cam1.tick != prev_tick_cam1)
    {
        flag_rx = true;
        read_count = 0;
        ST_CAMERA temp_info;
        char temp_char[255];
        for (int a = 0; a < 255; a++) {
            temp_char[a] = (char)cam1.serial[a];
        }
        char* temp_pchar = &temp_char[0];
        temp_info.serial = QString::fromUtf8(temp_pchar);
//        qDebug() << temp_info.serial;

        temp_info.width = cam1.width;
        temp_info.height = cam1.height;
        temp_info.imageSize = cam1.width*cam1.height;

        cv::Mat cam1_img(temp_info.height, temp_info.width, CV_8U, cv::Scalar(0));
        memcpy((uint8_t*)cam1_img.data, cam1.buf, sizeof(cam1.buf));
        temp_info.pixmap = QPixmap::fromImage(mat_to_qimage_cpy(cam1_img));

        if(pmap->camera_info.count() > 1){
            pmap->camera_info[1] = temp_info;
        }else{
            pmap->camera_info.push_back(temp_info);
        }

        try{
            emit cameraupdate();
        }catch(std::bad_alloc){
            qDebug() << "bad alloc?";
        }
        prev_tick_cam1 = cam1.tick;
    }

    IPCHandler::IMG_COLOR camcolor0 = get_cam_color0();
    if(camcolor0.tick != prev_tick_cam_color0)
    {
        flag_rx = true;
        read_count = 0;
        ST_CAMERA temp_info;
        char temp_char[255];
        for (int a = 0; a < 255; a++) {
            temp_char[a] = (char)camcolor0.serial[a];
        }
        char* temp_pchar = &temp_char[0];
        temp_info.serial = QString::fromUtf8(temp_pchar);
//        qDebug() << temp_info.serial;

        temp_info.width = camcolor0.width;
        temp_info.height = camcolor0.height;
        temp_info.imageSize = camcolor0.width*camcolor0.height;


        cv::Mat cam0_img(temp_info.height, temp_info.width, CV_8UC3, cv::Scalar(0));
        memcpy((uint8_t*)cam0_img.data, camcolor0.buf, sizeof(camcolor0.buf));
        temp_info.pixmap = QPixmap::fromImage(mat_to_qimage_cpy(cam0_img));

        if(pmap->camera_info.count() > 0){
            pmap->camera_info[0] = temp_info;
        }else{
            pmap->camera_info.push_back(temp_info);
        }

        try{
            emit cameraupdate();
        }catch(std::bad_alloc){
            qDebug() << "bad alloc?";
        }
        prev_tick_cam_color0 = camcolor0.tick;
    }

    IPCHandler::IMG_COLOR camcolor1 = get_cam_color1();
    if(camcolor1.tick != prev_tick_cam_color1)
    {
        flag_rx = true;
        read_count = 0;
        ST_CAMERA temp_info;
        char temp_char[255];
        for (int a = 0; a < 255; a++) {
            temp_char[a] = (char)camcolor1.serial[a];
        }
        char* temp_pchar = &temp_char[0];
        temp_info.serial = QString::fromUtf8(temp_pchar);
//        qDebug() << temp_info.serial;

        temp_info.width = camcolor1.width;
        temp_info.height = camcolor1.height;
        temp_info.imageSize = camcolor1.width*camcolor1.height;


        cv::Mat cam0_img(temp_info.height, temp_info.width, CV_8UC3, cv::Scalar(0));
        memcpy((uint8_t*)cam0_img.data, camcolor1.buf, sizeof(camcolor1.buf));
        temp_info.pixmap = QPixmap::fromImage(mat_to_qimage_cpy(cam0_img));

        if(pmap->camera_info.count() > 1){
            pmap->camera_info[1] = temp_info;
        }else{
            pmap->camera_info.push_back(temp_info);
        }

        try{
            emit cameraupdate();
        }catch(std::bad_alloc){
            qDebug() << "bad alloc?";
        }
        prev_tick_cam_color1 = camcolor1.tick;
    }

    IPCHandler::LOC_STATUS loc_status = get_loc_status();
    if(loc_status.tick != prev_tick_loc_status){
        flag_rx = true;
        read_count = 0;
        prev_tick_loc_status = loc_status.tick;
        for(int i=0; i<pmap->locations.size(); i++){
            if(i > 254)
                break;

            if(loc_status.serving[i] == 0){
                pmap->locations[i].available = false;
            }else{
                pmap->locations[i].available = true;
            }
//            qDebug() << i << loc_status.serving[i] << pmap->locations[i].available;
        }
    }


    IPCHandler::CALL_LOC call_loc = get_call_loc();
    if(call_loc.tick != prev_tick_call_loc){
        flag_rx = true;
        read_count = 0;
        probot->server_call_size = 1;
        prev_tick_call_loc = call_loc.tick;
        probot->server_call_location = call_loc.loc_id;
//        plog->write("[IPC] GET CAll Location : "+QString::number(call_loc.loc_id)+", "+QString::number(ui_state));
//        if(call_loc.loc_id )
    }
    flag_rx = true;
    static int count=0;
    if(count++%5==0){
        flag_rx = false;
        flag_tx = false;
    }

    read_count++;
}
void IPCHandler::handsup(){
    IPCHandler::CALL_STATUS res;
    shm_call_status.lock();
    flag_tx = true;
    res.call_acceptable = 1;
    res.tick = ++tick;
    memcpy((char*)shm_call_status.data(),&res,sizeof(IPCHandler::CALL_STATUS));;
    shm_call_status.unlock();
}
void IPCHandler::handsdown(){
    IPCHandler::CALL_STATUS res;
    shm_call_status.lock();
    flag_tx = true;
    res.call_acceptable = 0;
    res.tick = ++tick;
    memcpy((char*)shm_call_status.data(),&res,sizeof(IPCHandler::CALL_STATUS));;
    shm_call_status.unlock();

}
IPCHandler::CALL_LOC IPCHandler::get_call_loc(){
    IPCHandler::CALL_LOC res;

    shm_call_loc.lock();
    memcpy(&res, (char*)shm_call_loc.constData(), sizeof(IPCHandler::CALL_LOC));
    shm_call_loc.unlock();

    return res;
}

IPCHandler::LOC_STATUS IPCHandler::get_loc_status()
{
    IPCHandler::LOC_STATUS res;

    shm_loc_status.lock();
    memcpy(&res, (char*)shm_loc_status.constData(), sizeof(IPCHandler::LOC_STATUS));
    shm_loc_status.unlock();

    return res;
}

IPCHandler::CMD IPCHandler::get_cmd()
{
    IPCHandler::CMD res;
    shm_cmd.lock();
    memcpy(&res, (char*)shm_cmd.constData(), sizeof(IPCHandler::CMD));
    shm_cmd.unlock();

    return res;
}
IPCHandler::CHECK_TRAVEL IPCHandler::get_check_travel()
{
    IPCHandler::CHECK_TRAVEL res;
    shm_check_travel.lock();
    memcpy(&res, (char*)shm_check_travel.constData(), sizeof(IPCHandler::CHECK_TRAVEL));
    shm_check_travel.unlock();

    return res;
}


IPCHandler::STATUS IPCHandler::get_status()
{
    IPCHandler::STATUS res;
    shm_status.lock();
    memcpy(&res, (char*)shm_status.constData(), sizeof(IPCHandler::STATUS));
    shm_status.unlock();

    return res;
}

IPCHandler::PATH IPCHandler::get_path()
{
    IPCHandler::PATH res;

    shm_path.lock();
    memcpy(&res, (char*)shm_path.constData(), sizeof(IPCHandler::PATH));
    shm_path.unlock();

    return res;
}

IPCHandler::MAP IPCHandler::get_map()
{
    IPCHandler::MAP res;

    shm_map.lock();
    memcpy(&res, (char*)shm_map.constData(), sizeof(IPCHandler::MAP));
    shm_map.unlock();

    return res;
}

IPCHandler::IMG_COLOR IPCHandler::get_cam_color0()
{
    IPCHandler::IMG_COLOR res;

    shm_cam_color0.lock();
    memcpy(&res, (char*)shm_cam_color0.constData(), sizeof(IPCHandler::IMG_COLOR));
    shm_cam_color0.unlock();

    return res;
}
IPCHandler::IMG_COLOR IPCHandler::get_cam_color1()
{
    IPCHandler::IMG_COLOR res;

    shm_cam_color1.lock();
    memcpy(&res, (char*)shm_cam_color1.constData(), sizeof(IPCHandler::IMG_COLOR));
    shm_cam_color1.unlock();

    return res;
}
IPCHandler::MAP IPCHandler::get_obs()
{
    IPCHandler::MAP res;

    shm_obs.lock();
    memcpy(&res, (char*)shm_obs.constData(), sizeof(IPCHandler::MAP));
    shm_obs.unlock();

    return res;
}

IPCHandler::IMG IPCHandler::get_cam0()
{
    IPCHandler::IMG res;

    shm_cam0.lock();
    memcpy(&res, (char*)shm_cam0.constData(), sizeof(IPCHandler::IMG));
    shm_cam0.unlock();

    return res;
}

IPCHandler::IMG IPCHandler::get_cam1()
{
    IPCHandler::IMG res;

    shm_cam1.lock();
    memcpy(&res, (char*)shm_cam1.constData(), sizeof(IPCHandler::IMG));
    shm_cam1.unlock();

    return res;
}

void IPCHandler::set_cmd(IPCHandler::CMD val, QString log)
{
    shm_cmd.lock();
    flag_tx = true;
    val.tick = ++tick;
    memcpy((char*)shm_cmd.data(), &val, sizeof(IPCHandler::CMD));

    plog->write("[IPC] Set CMD "+QString::number(val.cmd)+" : "+log);

    shm_cmd.unlock();
}
void IPCHandler::set_cmd(int cmd, QString log){
    IPCHandler::CMD send_msg;
    send_msg.cmd = cmd;
    set_cmd(send_msg,log);
}
void IPCHandler::set_status_ui(){
    IPCHandler::UI_STATUS val;
    val.ui_map_rotate_angle = pmap->map_rotate_angle;
    val.ui_cut_map_x = pmap->cut_map[0];
    val.ui_cut_map_y = pmap->cut_map[1];
    shm_ui_status.lock();
    flag_tx = true;
    val.tick = ++tick;
    memcpy((char*)shm_ui_status.data(), &val, sizeof(IPCHandler::UI_STATUS));
//    plog->write("[IPC] SET UI Status");
    shm_ui_status.unlock();
}
////*********************************************  COMMAND FUNCTIONS   ***************************************************////
void IPCHandler::moveToServing(QString target_loc, int preset){
    bool match = false;
    float pose[3];
    LOCATION temp_loc;
    for(int i=0; i<pmap->locations.size(); i++){
        if(target_loc == pmap->locations[i].name){
            match = true;
            probot->curLocation = pmap->locations[i];
            pose[0] = pmap->locations[i].point.x;
            pose[1] = pmap->locations[i].point.y;
            pose[2] = pmap->locations[i].angle;
            temp_loc = pmap->locations[i];
        }
    }

    if(match){
        plog->write("[IPC] MOVE TO COMMAND : "+target_loc);
        moveTo(pose[0],pose[1],pose[2],preset);
    }else{
        plog->write("[IPC] MOVE TO COMMAND (UNMATCHED): "+target_loc);
//        IPCHandler::CMD send_msg;
//        send_msg.cmd = ROBOT_CMD_MOVE_LOCATION;
    }
    probot->curLocation = temp_loc;
}

void IPCHandler::moveToLocation(LOCATION target_loc, int preset){
    if(target_loc.name != "" ){
        plog->write("[IPC] MOVE TO COMMAND : "+target_loc.name);
        probot->curLocation = target_loc;
        moveTo(target_loc.point.x, target_loc.point.y, target_loc.angle, preset);
    }else{
        plog->write("[IPC] MOVE TO COMMAND (UNMATCHED): "+target_loc.name + QString().asprintf("(group : %d)",target_loc.group));
    }
    probot->curLocation = target_loc;
}
void IPCHandler::moveToLocationTest(LOCATION target_loc, int preset){
    if(target_loc.name != "" ){
        plog->write("[IPC] MOVE(TEST) TO COMMAND : "+target_loc.name);
        probot->curLocation = target_loc;
        moveToTest(target_loc.point.x, target_loc.point.y, target_loc.angle, preset);
    }else{
        plog->write("[IPC] MOVE(TEST) TO COMMAND (UNMATCHED): "+target_loc.name + QString().asprintf("(group : %d)",target_loc.group));
    }
    probot->curLocation = target_loc;
}
void IPCHandler::moveToResting(int preset){
    for(int i=0; i<pmap->locations.size(); i++){
        if(pmap->locations[i].type == "Resting"){
            plog->write("[IPC] MOVE TO COMMAND : "+pmap->locations[i].name);
            probot->curLocation = pmap->locations[i];
            moveTo(pmap->locations[i].point.x, pmap->locations[i].point.y, pmap->locations[i].angle, preset);
            return;
        }
    }
    plog->write("[IPC] MOVE TO COMMAND : RESTING (NOT FOUND)");
}
void IPCHandler::moveToCharging(int preset){
    for(int i=0; i<pmap->locations.size(); i++){
        if(pmap->locations[i].type == "Charging"){
            plog->write("[IPC] MOVE TO COMMAND : "+pmap->locations[i].name);
            probot->curLocation = pmap->locations[i];
            moveTo(pmap->locations[i].point.x, pmap->locations[i].point.y, pmap->locations[i].angle, preset);
            return;
        }
    }
    plog->write("[IPC] MOVE TO COMMAND : CHARGING (NOT FOUND)");
}

void IPCHandler::sendCommand(int cmd){
    IPCHandler::CMD send_msg;
    send_msg.cmd = cmd;
    set_cmd(send_msg,"");
}
void IPCHandler::moveTo(float x, float y, float th, int preset){
    IPCHandler::CMD send_msg;
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

    send_msg.params[12] = (uint8_t)preset;
    qDebug() << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << send_msg.params[12];

    probot->curTarget.point.x = x;
    probot->curTarget.point.y = y;
    probot->curTarget.angle = th;
    set_cmd(send_msg,"Move Target to "+QString().asprintf("%f, %f, %f, %d",x,y,th,preset));
}
void IPCHandler::moveToTest(float x, float y, float th, int preset){
    IPCHandler::CMD send_msg;
    send_msg.cmd = ROBOT_CMD_MOVE_TARGET_EX;
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

    send_msg.params[12] = (uint8_t)preset;
    qDebug() << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << send_msg.params[12];

    probot->curTarget.point.x = x;
    probot->curTarget.point.y = y;
    probot->curTarget.angle = th;
    set_cmd(send_msg,"Move Target to "+QString().asprintf("%f, %f, %f, %d",x,y,th,preset));
}
void IPCHandler::movePause(){
    IPCHandler::CMD send_msg;
    send_msg.cmd = ROBOT_CMD_MOVE_PAUSE;
    set_cmd(send_msg,"Move Pause");
}
void IPCHandler::moveResume(){
    IPCHandler::CMD send_msg;
    send_msg.cmd = ROBOT_CMD_MOVE_RESUME;
    set_cmd(send_msg,"Move Resume");
}
void IPCHandler::moveJog(){
    IPCHandler::CMD send_msg;
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

    set_cmd(send_msg, "MOVE JOYSTICK "+QString().asprintf("%f, %f",probot->joystick[0],probot->joystick[1]));
}
void IPCHandler::moveStop(){
    IPCHandler::CMD send_msg;
    send_msg.cmd = ROBOT_CMD_MOVE_STOP;
    set_cmd(send_msg, "MOVE STOP");
}
void IPCHandler::moveManual(){
    IPCHandler::CMD send_msg;
    send_msg.cmd = ROBOT_CMD_MOVE_MANUAL;
    set_cmd(send_msg, "MOVE MANUAL START");
}
void IPCHandler::setInitPose(float x, float y, float th){
    IPCHandler::CMD send_msg;
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

    set_cmd(send_msg, "SET INIT "+QString().asprintf("%f, %f, %f",x,y,th));
}
void IPCHandler::saveMapping(QString name){
    IPCHandler::CMD send_msg;
    send_msg.cmd = ROBOT_CMD_MAPPING_SAVE;
    memcpy(send_msg.params,name.toUtf8(),sizeof(char)*255);
    set_cmd(send_msg,"SAVE MAPPING ("+name+")");
}

void IPCHandler::startMapping(int map_size, float grid_size){
    IPCHandler::CMD send_msg;
    send_msg.cmd = ROBOT_CMD_MAPPING_START;
    uint8_t *array;
    array = reinterpret_cast<uint8_t*>(&map_size);
    send_msg.params[0] = array[0];
    send_msg.params[1] = array[1];
    send_msg.params[2] = array[2];
    send_msg.params[3] = array[3];
    array = reinterpret_cast<uint8_t*>(&grid_size);
    send_msg.params[4] = array[0];
    send_msg.params[5] = array[1];
    send_msg.params[6] = array[2];
    send_msg.params[7] = array[3];
    set_cmd(send_msg,"START MAPPING "+QString().asprintf("(map size = %d, grid size = %f)",map_size, grid_size));
}
void IPCHandler::stopMapping(){
    IPCHandler::CMD send_msg;
    send_msg.cmd = ROBOT_CMD_MAPPING_STOP;
    set_cmd(send_msg, "STOP MAPPING");
}
void IPCHandler::saveObject(){
    is_objecting = false;
    IPCHandler::CMD send_msg;
    send_msg.cmd = ROBOT_CMD_OBJECTING_SAVE;
    set_cmd(send_msg,"SAVE OBJECTING");
}
void IPCHandler::startObject(){
    is_objecting = true;
    IPCHandler::CMD send_msg;
    send_msg.cmd = ROBOT_CMD_OBJECTING_START;
    set_cmd(send_msg,"START OBJECTING ");
}
void IPCHandler::stopObject(){
    is_objecting = false;
    IPCHandler::CMD send_msg;
    send_msg.cmd = ROBOT_CMD_OBJECTING_STOP;
    set_cmd(send_msg, "STOP OBJECTING");
}
void IPCHandler::set_velocity(float vel){
    IPCHandler::CMD send_msg;
    send_msg.cmd = ROBOT_CMD_SET_VELOCITY;
    uint8_t *array;
    array = reinterpret_cast<uint8_t*>(&vel);
    send_msg.params[0] = array[0];
    send_msg.params[1] = array[1];
    send_msg.params[2] = array[2];
    send_msg.params[3] = array[3];
    set_cmd(send_msg, "SET Velocity to "+QString::number(vel));
}
