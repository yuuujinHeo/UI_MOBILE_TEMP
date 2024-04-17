#include <QtMath>
#include <QQmlApplicationEngine>
#include <QDir>
#include <QSettings>
#include <iostream>
#include <QPainterPath>
#include <exception>
#include <QJsonDocument>
#include <QGuiApplication>
#include <fstream>
#include <QJsonObject>
#include <QJsonArray>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <QQmlEngine>
#include "MapHandler.h"

MapHandler::MapHandler()
{
    scale = 1;
    draw_x = 0;
    draw_y = 0;
    draw_width = 1000;
    tool = "move";

    map_orin = cv::Mat(1000,1000,CV_8U,cv::Scalar::all(0));
    map_drawing = cv::Mat(1000,1000,CV_8UC4,cv::Scalar::all(0));
    map_drawing_tline = cv::Mat(1000,1000,CV_8UC4,cv::Scalar::all(0));
    map_drawing_mask = cv::Mat(1000,1000,CV_8UC4,cv::Scalar::all(0));
    file_velocity = cv::Mat(1000,1000,CV_8UC3,cv::Scalar::all(0));
    file_travelline = cv::Mat(1000,1000,CV_8UC3,cv::Scalar::all(0));
    file_travelline_ui = cv::Mat(1000,1000,CV_8UC3,cv::Scalar::all(0));
    file_object = cv::Mat(1000,1000,CV_8UC3,cv::Scalar::all(0));
    file_avoid = cv::Mat(1000,1000,CV_8UC3,cv::Scalar::all(0));
    grid_width = 0.03;
    file_width = 1000;

    clearLocation();

    //메인 타이머
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()),this,SLOT(onTimer()));
    timer->start(200);
}

bool MapHandler::getCutBoxFlag(){
    if(cut_box[0].x == 0 && cut_box[0].y == 0){
        if(cut_box[1].x == file_width && cut_box[1].y == file_width){
            return false;
        }
    }
    return true;
}

void MapHandler::loadFile(){
    loadFile(map_name,"");
}
void MapHandler::loadFile(QString name, QString type){
    QString file_path = QDir::homePath() + "/RB_MOBILE/maps/"+name + "/map_raw.png";
    QString log_str;
    if(QFile::exists(file_path)){
        file_raw = cv::imread(file_path.toStdString(), cv::IMREAD_GRAYSCALE);
        cv::flip(file_raw,file_raw,0);
        file_width = file_raw.rows;
        cv::rotate(file_raw,file_raw,cv::ROTATE_90_COUNTERCLOCKWISE);
        log_str = "RAW(success) ";
        exist_raw = true;
    }else{
        exist_raw = false;
        file_raw = cv::Mat(file_width,file_width,CV_8U,cv::Scalar::all(0));
        log_str = "RAW(failed) ";
    }

    file_path = QDir::homePath() + "/RB_MOBILE/maps/"+name + "/map_edited.png";
    if(QFile::exists(file_path)){
        file_edited = cv::imread(file_path.toStdString(), cv::IMREAD_GRAYSCALE);
        cv::flip(file_edited,file_edited,0);
        cv::rotate(file_edited,file_edited,cv::ROTATE_90_COUNTERCLOCKWISE);
        exist_edited = true;
        file_width = file_edited.rows;
        log_str += ", EDITED(success) ";
        file_edited.copyTo(map_orin);
    }else{
        exist_edited = false;
        file_edited = cv::Mat(file_width,file_width,CV_8U,cv::Scalar::all(0));
        log_str += ", EDITED(failed) ";
        if(exist_raw){
            file_raw.copyTo(map_orin);
        }else{
            map_orin = cv::Mat(file_width,file_width,CV_8U,cv::Scalar::all(0));
        }
    }

    if(type == "T_TEMP"){
        file_path = QDir::homePath() + "/RB_MOBILE/maps/"+name + "/map_travel_line_ui.png";
    }else{
        file_path = QDir::homePath() + "/RB_MOBILE/maps/"+name + "/map_travel_line.png";
    }

    if(QFile::exists(file_path)){
        file_travelline = cv::imread(file_path.toStdString(), cv::IMREAD_COLOR);
        cv::flip(file_travelline,file_travelline,0);
        cv::rotate(file_travelline,file_travelline,cv::ROTATE_90_COUNTERCLOCKWISE);

        for(int i=0; i<file_travelline.cols; i++){
            for(int j=0; j<file_travelline.rows; j++){
                if(file_travelline.at<cv::Vec3b>(i,j)[0] == 255){
                    file_travelline.at<cv::Vec3b>(i,j)[0] = 80;
                    file_travelline.at<cv::Vec3b>(i,j)[1] = 200;
                    file_travelline.at<cv::Vec3b>(i,j)[2] = 255;
                }
            }
        }

        log_str += ", TRAVELLINE(success "+QString::number(file_travelline.rows)+" ) ";
        exist_travelline = true;
    }else{
        file_travelline = cv::Mat(file_width, file_width, CV_8UC3 ,cv::Scalar::all(0));
        exist_travelline = false;
        log_str += ", TRAVELLINE(failed) ";
    }


    file_path = QDir::homePath() + "/RB_MOBILE/maps/"+name + "/map_travel_line_ui.png";
    if(QFile::exists(file_path)){
        file_travelline_ui = cv::imread(file_path.toStdString(), cv::IMREAD_COLOR);
        cv::flip(file_travelline_ui,file_travelline_ui,0);
        cv::rotate(file_travelline_ui,file_travelline_ui,cv::ROTATE_90_COUNTERCLOCKWISE);

        for(int i=0; i<file_travelline_ui.cols; i++){
            for(int j=0; j<file_travelline_ui.rows; j++){
                if(file_travelline_ui.at<cv::Vec3b>(i,j)[0] == 255){
                    file_travelline_ui.at<cv::Vec3b>(i,j)[0] = 77;
                    file_travelline_ui.at<cv::Vec3b>(i,j)[1] = 47;
                    file_travelline_ui.at<cv::Vec3b>(i,j)[2] = 34;
                }
            }
        }

        log_str += ", TRAVELLINE_UI(success "+QString::number(file_travelline_ui.rows)+" ) ";
        exist_travelline_ui = true;
    }else{
        file_travelline_ui = cv::Mat(file_width, file_width, CV_8UC3 ,cv::Scalar::all(0));
        exist_travelline_ui = false;
        log_str += ", TRAVELLINE_UI(failed) ";
    }

    file_path = QDir::homePath() + "/RB_MOBILE/maps/"+name + "/map_velocity.png";
    if(QFile::exists(file_path)){
        file_velocity = cv::imread(file_path.toStdString(), cv::IMREAD_COLOR);
        cv::flip(file_velocity,file_velocity,0);
        cv::rotate(file_velocity,file_velocity,cv::ROTATE_90_COUNTERCLOCKWISE);


        for(int i=0; i<file_velocity.cols; i++){
            for(int j=0; j<file_velocity.rows; j++){
                if(file_velocity.at<cv::Vec3b>(i,j)[0] == 100){
                    file_velocity.at<cv::Vec3b>(i,j)[0] = 80;
                    file_velocity.at<cv::Vec3b>(i,j)[1] = 200;
                    file_velocity.at<cv::Vec3b>(i,j)[2] = 255;
                }else if(file_velocity.at<cv::Vec3b>(i,j)[0] == 200){
                    file_velocity.at<cv::Vec3b>(i,j)[0] = 77;
                    file_velocity.at<cv::Vec3b>(i,j)[1] = 88;
                    file_velocity.at<cv::Vec3b>(i,j)[2] = 231;
                }
            }
        }

        log_str += ", VELOCITY(success "+QString::number(file_velocity.rows)+" ) ";
        exist_velmap = true;
    }else{
        file_velocity = cv::Mat(file_width, file_width, CV_8UC3 ,cv::Scalar::all(0));
        exist_velmap = false;
        log_str += ", VELOCITY(failed) ";
    }
    file_path = QDir::homePath() + "/RB_MOBILE/maps/"+name + "/map_obs.png";
    if(QFile::exists(file_path)){
        file_object = cv::imread(file_path.toStdString(), cv::IMREAD_COLOR);
        cv::flip(file_object,file_object,0);
        cv::rotate(file_object,file_object,cv::ROTATE_90_COUNTERCLOCKWISE);


        for(int i=0; i<file_object.cols; i++){
            for(int j=0; j<file_object.rows; j++){
                if(file_object.at<cv::Vec3b>(i,j)[0] == 255){
                    file_object.at<cv::Vec3b>(i,j)[0] = 249;
                    file_object.at<cv::Vec3b>(i,j)[1] = 184;
                    file_object.at<cv::Vec3b>(i,j)[2] = 131;
                }
            }
        }

        log_str += ", OBJECT(success "+QString::number(file_object.rows)+" ) ";
    }else{
        file_object = cv::Mat(file_width, file_width, CV_8UC3,cv::Scalar::all(0));
        log_str += ", OBJECT(failed) ";
    }
    file_path = QDir::homePath() + "/RB_MOBILE/maps/"+name + "/map_avoid.png";
    if(QFile::exists(file_path)){
        file_avoid = cv::imread(file_path.toStdString(), cv::IMREAD_COLOR);
        cv::flip(file_avoid,file_avoid,0);
        cv::rotate(file_avoid,file_avoid,cv::ROTATE_90_COUNTERCLOCKWISE);

        for(int i=0; i<file_avoid.cols; i++){
            for(int j=0; j<file_avoid.rows; j++){
                if(file_avoid.at<cv::Vec3b>(i,j)[0] == 255){
                    file_avoid.at<cv::Vec3b>(i,j)[0] = 18;
                    file_avoid.at<cv::Vec3b>(i,j)[1] = 210;
                    file_avoid.at<cv::Vec3b>(i,j)[2] = 124;
                }
            }
        }

        log_str += ", AVOID(success "+QString::number(file_avoid.rows)+" ) ";
    }else{
        file_avoid = cv::Mat(file_width, file_width, CV_8UC3,cv::Scalar::all(0));
        log_str += ", AVOID(failed) ";
    }
    map_name = name;
    loadNode();

    draw_x = 0;
    draw_y = 0;
    draw_width = file_width;
    log_str += QString().asprintf(", FILEWIDTH(%d)",draw_width);
    initDrawing();
    initLocation();
    initRotate();
    setMap();
    plog->write("[MAP] Load File : " + name + " (type = "+type+", width = "+draw_width+") => "+log_str);
}

void MapHandler::setMapOrin(QString type){
    if(type == "RAW"){
        plog->write("[MAP] Set Map to map_raw");
        file_raw.copyTo(map_orin);
        file_width = map_orin.rows;
        file_velocity = cv::Mat(file_width, file_width, CV_8UC3, cv::Scalar::all(0));
        file_avoid = cv::Mat(file_width, file_width, CV_8UC3, cv::Scalar::all(0));
        file_travelline = cv::Mat(file_width, file_width, CV_8UC3, cv::Scalar::all(0));
        file_travelline_ui = cv::Mat(file_width, file_width, CV_8UC3, cv::Scalar::all(0));
        file_object = cv::Mat(file_width, file_width, CV_8UC3, cv::Scalar::all(0));
        show_location = false;
        show_avoid = false;
        show_object = false;
        show_travelline = false;
        show_velocitymap = false;
        initDrawing();
        setFullScreen();
        setMap();
        update();
    }else if(type == "EDITED"){
        plog->write("[MAP] Set Map to map_edited");
        loadFile(map_name,"");
    }
}


void MapHandler::setMapSize(int width, int height){
//    qDebug() << "setMapSize " << width << height;
    canvas_width = width;
    canvas_height = height;
}

void MapHandler::onTimer(){
    if(flag_drawing){
        show_robot = true;
        show_travelline = true;
        drawTline();
    }

    //Robot Following
    if(robot_following){
        cv::Point2f robot_pose;
        robot_pose = setAxis(probot->curPose.point);
        setZoomCenter(robot_pose.x, robot_pose.y);
    }else{
        if(show_robot || show_lidar){
            setMapLayer();
        }
    }
}


void MapHandler::setMode(QString name){
    mode = name;
    tool = "move";
    plog->write("[MAP] Set Mode : "+name);

    show_node = false;
    show_edge = false;
    show_name = false;
    show_number = false;

    show_robot = false;
    show_lidar = false;
    robot_following = false;

    show_global_path = false;
    show_local_path = false;

    show_velocitymap = false;
    show_travelline = false;
    show_avoid = false;


    show_object = false;
    show_location = false;
    show_location_icon = false;

    if(mode == "mapping"){//o
        show_robot = true;
        show_lidar = true;
        robot_following = true;
        setFullScreen();
    }else if(mode == "current"){//o
        show_robot = true;
        show_global_path = true;
        show_local_path = true;
        show_lidar = true;
        show_location = true;
        show_location_icon = true;
        robot_following = true;
        setFullScreen();
    }else if(mode == "annot_view"){//o
        show_location = true;
        show_location_icon = true;
        setFullScreen();
    }else if(mode == "annot_velmap"){//o
        show_location = true;
        show_location_icon = true;
        show_velocitymap = true;
        show_travelline = true;
        setFullScreen();
    }else if(mode == "annot_location"){//o
        show_robot = true;
        show_lidar = true;
        show_location = true;
        show_location_icon = true;
        robot_following = true;
        show_travelline = true;
    }else if(mode == "annot_tline"){//o
        show_location = true;
        show_location_icon = true;
        show_travelline = true;
        setFullScreen();
    }else if(mode == "localization"){//o
        show_robot = true;
        show_lidar = true;
        show_location = true;
        show_location_icon = true;
        pmap->annotation_edited = false;
        pmap->annot_edit_drawing = false;
        pmap->annot_edit_location = false;
        pmap->annot_edit_tline = false;
        setFullScreen();
    }else if(mode == "annot_object_png"){//o
        show_robot = true;
        show_object = true;
        show_location = true;
        show_location_icon = true;
        show_travelline = true;
        initObject();
        setFullScreen();
    }else if(mode == "annot_obs_area"){//o
        show_robot = true;
        show_location = true;
        show_avoid = true;
        show_location_icon = true;
        show_travelline = true;
        initObject();
        setFullScreen();
    }else{
        setFullScreen();
    }



    setMap();
}

void MapHandler::startDrawingTline(){
    plog->write("[MAP] Start Draw Travel line");
    flag_drawing = true;
    prev_pose.x = 0;
    prev_pose.y = 0;
}
void MapHandler::stopDrawingTline(){
    plog->write("[MAP] Stop Draw Travel line");
    flag_drawing = false;
}

void MapHandler::initLocation(){
    //Read annotation.ini
    locations.clear();
    pmap->annot_edit_location = false;
    for(int i=0; i<pmap->locations.size(); i++){
        LOCATION temp;
        temp.group = pmap->locations[i].group;
        temp.call_id = pmap->locations[i].call_id;
        temp.group_name = pmap->locations[i].group_name;
        temp.type = pmap->locations[i].type;
        temp.name = pmap->locations[i].name;

        temp.point = setAxis(pmap->locations[i].point);
        temp.angle = setAxis(pmap->locations[i].angle);

//        qDebug() <<"locations push " << temp.type << temp.name;
        locations.push_back(temp);
    }
}

void MapHandler::setFullScreen(){
    draw_x = 0;
    draw_y = 0;
    draw_width = file_width;
    scale = 1;
}

void MapHandler::setMapLayer(){
    map_layer = QPixmap(2000,2000);
    map_layer.fill(Qt::transparent);
    QPainter painter_layer(&map_layer);
    painter_layer.setRenderHint(QPainter::Antialiasing, true);
    painter_layer.setRenderHint(QPainter::SmoothPixmapTransform, true);
    float news = float(map_layer.width())/draw_width;//map.width();
//    qDebug() << "setMapLayer << " <<  draw_width << map_layer.width() << news;

    //공용 변수
    cv::Point2f temp_robot_pose;
    cv::Point2f robot_pose;
    if(mode == "mapping"){
        temp_robot_pose = setAxisMapping(probot->curPose.point);
//        news = (float(map_layer.width())/draw_width)*1000/pmap->mapping_width;
    }else{
        temp_robot_pose = setAxis(probot->curPose.point);
    }

    robot_pose.x = (temp_robot_pose.x - draw_x)*news;
    robot_pose.y = (temp_robot_pose.y - draw_y)*news;
    float robot_angle = setAxis(probot->curPose.angle);

//    qDebug() << probot->curPose.point.y << temp_robot_pose.x << robot_pose.x;

    //위치
    if(show_location){
        for(int i=0; i<locations.size(); i++){
            float loc_x = (locations[i].point.x - draw_x)*news;
            float loc_y = (locations[i].point.y - draw_y)*news;
            float distance = (pmap->robot_radius/grid_width)*2*news;
            float distance2 = distance*0.8;
            float th_dist = (M_PI/8);
            float rad = (pmap->robot_radius/grid_width)*news;

            float x =   (loc_x + distance    * qCos(locations[i].angle));
            float y =   (loc_y + distance    * qSin(locations[i].angle));
            float x1 =  (loc_x + distance2   * qCos(locations[i].angle-th_dist));
            float y1 =  (loc_y + distance2   * qSin(locations[i].angle-th_dist));
            float x2 =  (loc_x + distance2   * qCos(locations[i].angle+th_dist));
            float y2 =  (loc_y + distance2   * qSin(locations[i].angle+th_dist));

            QPainterPath path;
            if(mode == "annot_tline" || mode == "annot_tline2"){
                bool match = false;
                for(int k=0; k<pmap->tline_issue; k++){
                    if(pmap->tline_issues[k].group == locations[i].group_name){
                        if(pmap->tline_issues[k].name == locations[i].name){
                            match = true;
                            break;
                        }
                    }
                }

                if(match){
                    if(locations[i].type == "Serving"){
                        path.addRoundedRect((loc_x-rad),(loc_y-rad),rad*2,rad*2,rad,rad);
                        painter_layer.setPen(QPen(Qt::red,3*news));
                        painter_layer.drawPath(path);
                        painter_layer.drawLine(x1,y1,x,y);
                        painter_layer.drawLine(x,y,x2,y2);
                    }else if(locations[i].type == "Resting"){
                    }else if(locations[i].type == "Charging"){
                    }
                }else{
                    if(locations[i].type == "Serving"){
                        path.addRoundedRect((loc_x-rad),(loc_y-rad),rad*2,rad*2,rad,rad);
                        painter_layer.setPen(QPen(Qt::white,1*news));

                        painter_layer.drawPath(path);
                        painter_layer.setPen(QPen(Qt::white,1.5*news));
                        painter_layer.drawLine(QLine(x1,y1,x,y));
                        painter_layer.drawLine(QLine(x2,y2,x,y));
                    }else if(locations[i].type == "Resting"){
                    }else if(locations[i].type == "Charging"){
                    }
                }
            }else{
                if(locations[i].type == "Serving"){
                    path.addRoundedRect((loc_x-rad),(loc_y-rad),rad*2,rad*2,rad,rad);
                    painter_layer.setPen(QPen(Qt::white,1*news));

                    if(mode == "annot_tline" || mode == "annot_tline2"){

                    }else{
                        painter_layer.fillPath(path,QBrush(QColor(hex_color_pink)));
                    }

                    painter_layer.drawPath(path);
                    painter_layer.setPen(QPen(Qt::white,1.5*news));
                    painter_layer.drawLine(QLine(x1,y1,x,y));
                    painter_layer.drawLine(QLine(x2,y2,x,y));
                }else if(locations[i].type == "Resting"){
                }else if(locations[i].type == "Charging"){
                }
            }


            if(show_number){
                int num;
                if(probot->type == "CLEANING"){
                    num = i-2;
                }else{
                    num = i-1;
                }
                if(num>9){
                    painter_layer.setFont(QFont("font/NotoSansKR-Medium",rad/1.5));
                }else if(num>99){
                    painter_layer.setFont(QFont("font/NotoSansKR-Medium",rad/2));
                }else{
                    painter_layer.setFont(QFont("font/NotoSansKR-Medium",rad));
                }
                if(num>0)
                    painter_layer.drawText(QRect((loc_x-rad),(loc_y-rad),rad*2,rad*2),Qt::AlignVCenter | Qt::AlignHCenter,QString().asprintf("%d",num));

            }

        }
        if(new_location_flag){
            float loc_x = (new_location.point.x - draw_x)*news;
            float loc_y = (new_location.point.y - draw_y)*news;
            float distance = (pmap->robot_radius/grid_width)*2*news;
            float distance2 = distance*0.8;
            float th_dist = (M_PI/8);
            float rad = (pmap->robot_radius/grid_width)*news;

            float x =   (loc_x + distance    * qCos(new_location.angle));
            float y =   (loc_y + distance    * qSin(new_location.angle));
            float x1 =  (loc_x + distance2   * qCos(new_location.angle-th_dist));
            float y1 =  (loc_y + distance2   * qSin(new_location.angle-th_dist));
            float x2 =  (loc_x + distance2   * qCos(new_location.angle+th_dist));
            float y2 =  (loc_y + distance2   * qSin(new_location.angle+th_dist));
            QPainterPath path;
            path.addRoundedRect((loc_x-rad),(loc_y-rad),rad*2,rad*2,rad,rad);
            painter_layer.setPen(QPen(Qt::white,3*news));

            painter_layer.fillPath(path,QBrush(QColor(hex_color_blue)));

            painter_layer.drawPath(path);
            painter_layer.drawLine(QLine(x1,y1,x,y));
            painter_layer.drawLine(QLine(x2,y2,x,y));
        }
    }

    if(show_location_icon){
        for(int i=0; i<locations.size(); i++){
            float loc_x = (locations[i].point.x - draw_x)*news;
            float loc_y = (locations[i].point.y - draw_y)*news;
            float distance = (pmap->robot_radius/grid_width)*2*news;
            float distance2 = distance*0.8;
            float th_dist = (M_PI/8);
            float rad = (pmap->robot_radius/grid_width)*news;

            float x =   (loc_x + distance    * qCos(locations[i].angle));
            float y =   (loc_y + distance    * qSin(locations[i].angle));
            float x1 =  (loc_x + distance2   * qCos(locations[i].angle-th_dist));
            float y1 =  (loc_y + distance2   * qSin(locations[i].angle-th_dist));
            float x2 =  (loc_x + distance2   * qCos(locations[i].angle+th_dist));
            float y2 =  (loc_y + distance2   * qSin(locations[i].angle+th_dist));
//            qDebug() << locations[i].type << locations[i].point.x << locations[i].point.y << draw_x << draw_y << loc_x << loc_y << rad;

            QPainterPath path;
            if(locations[i].type == "Resting"){

                    path.addRoundedRect((loc_x-rad),(loc_y-rad),rad*2,rad*2,rad,rad);
                    painter_layer.setPen(QPen(Qt::white,1*news));

                    painter_layer.drawPath(path);
                    painter_layer.drawLine(x1,y1,x,y);
                    painter_layer.drawLine(x,y,x2,y2);
                    painter_layer.drawPath(path);
                    QImage image(":/icon/icon_home_2.png");
                    painter_layer.drawImage(QRectF((loc_x-rad),(loc_y-rad),rad*2,rad*2),image,QRectF(0,0,image.width(),image.height()));

            }else if(locations[i].type == "Charging"){

                    path.addRoundedRect((loc_x-rad),(loc_y-rad),rad*2,rad*2,rad,rad);
                    painter_layer.setPen(QPen(Qt::white,1*news));
                    painter_layer.drawPath(path);
                    painter_layer.drawLine(x1,y1,x,y);
                    painter_layer.drawLine(x,y,x2,y2);
                    painter_layer.drawPath(path);
                    QImage image(":/icon/icon_charge_2.png");
                    painter_layer.drawImage(QRectF((loc_x-rad),(loc_y-rad),rad*2,rad*2),image,QRectF(0,0,image.width(),image.height()));

            }else if(locations[i].type == "Cleaning"){

                path.addRoundedRect((loc_x-rad),(loc_y-rad),rad*2,rad*2,rad,rad);

                painter_layer.setPen(QPen(Qt::white,1*news));

                painter_layer.drawPath(path);
                painter_layer.drawLine(x1,y1,x,y);
                painter_layer.drawLine(x,y,x2,y2);
                painter_layer.drawPath(path);
                QImage image(":/icon/icon_home_2.png");
                painter_layer.drawImage(QRectF((loc_x-rad),(loc_y-rad),rad*2,rad*2),image,QRectF(0,0,image.width(),image.height()));

        }
        }
    }

    if(select_location > -1 && select_location < locations.size()){
        float loc_x = (locations[select_location].point.x - draw_x)*news;
        float loc_y = (locations[select_location].point.y - draw_y)*news;
        float distance = (pmap->robot_radius/grid_width)*2*news;
        float distance2 = distance*0.8;
        float th_dist = (M_PI/8);
        float rad = (pmap->robot_radius/grid_width)*news;

        float x =   (loc_x + distance    * qCos(locations[select_location].angle));
        float y =   (loc_y + distance    * qSin(locations[select_location].angle));
        float x1 =  (loc_x + distance2   * qCos(locations[select_location].angle-th_dist));
        float y1 =  (loc_y + distance2   * qSin(locations[select_location].angle-th_dist));
        float x2 =  (loc_x + distance2   * qCos(locations[select_location].angle+th_dist));
        float y2 =  (loc_y + distance2   * qSin(locations[select_location].angle+th_dist));

        QPainterPath path;
        if(locations[select_location].type == "Serving"){
            path.addRoundedRect((loc_x-rad),(loc_y-rad),rad*2,rad*2,rad,rad);
            painter_layer.setPen(QPen(Qt::white,2*news));

            painter_layer.fillPath(path,QBrush(QColor(hex_color_green)));

            painter_layer.drawPath(path);
            painter_layer.drawLine(x1,y1,x,y);
            painter_layer.drawLine(x,y,x2,y2);
            if(show_number){
                int num;
                if(probot->type == "CLEANING"){
                    num = select_location-2;
                }else{
                    num = select_location-1;
                }
                if(num>9){
                    painter_layer.setFont(QFont("font/NotoSansKR-Medium",rad/1.5));
                }else if(num>99){
                    painter_layer.setFont(QFont("font/NotoSansKR-Medium",rad/2));
                }else{
                    painter_layer.setFont(QFont("font/NotoSansKR-Medium",rad));
                }
                painter_layer.drawText(QRect((loc_x-rad),(loc_y-rad),rad*2,rad*2),Qt::AlignVCenter | Qt::AlignHCenter,QString().asprintf("%d",num));

            }

        }else if(locations[select_location].type == "Resting"){
            path.addRoundedRect((loc_x-rad),(loc_y-rad),rad*2,rad*2,rad,rad);
            painter_layer.setPen(QPen(QColor(hex_color_green),2*news));
            painter_layer.fillPath(path,QBrush("black"));

            painter_layer.drawPath(path);
            painter_layer.drawLine(x1,y1,x,y);
            painter_layer.drawLine(x,y,x2,y2);
            QImage image(":/icon/icon_home_1.png");
            painter_layer.drawImage(QRectF((loc_x-rad),(loc_y-rad),rad*2,rad*2),image,QRectF(0,0,image.width(),image.height()));
        }else if(locations[select_location].type == "Charging"){
            path.addRoundedRect((loc_x-rad),(loc_y-rad),rad*2,rad*2,rad,rad);

            painter_layer.setPen(QPen(QColor(hex_color_green),2*news));
            painter_layer.fillPath(path,QBrush("black"));

            painter_layer.drawPath(path);
            painter_layer.drawLine(x1,y1,x,y);
            painter_layer.drawLine(x,y,x2,y2);
            QImage image(":/icon/icon_charge_1.png");
            painter_layer.drawImage(QRectF((loc_x-rad),(loc_y-rad),rad*2,rad*2),image,QRectF(0,0,image.width(),image.height()));
        }else if(locations[select_location].type == "Cleaning"){
            path.addRoundedRect((loc_x-rad),(loc_y-rad),rad*2,rad*2,rad,rad);

            painter_layer.setPen(QPen(QColor(hex_color_green),2*news));
            painter_layer.fillPath(path,QBrush("black"));

            painter_layer.drawPath(path);
            painter_layer.drawLine(x1,y1,x,y);
            painter_layer.drawLine(x,y,x2,y2);
            QImage image(":/icon/icon_home_1.png");
            painter_layer.drawImage(QRectF((loc_x-rad),(loc_y-rad),rad*2,rad*2),image,QRectF(0,0,image.width(),image.height()));
        }

    }
    //로봇 경로 표시
    if(show_global_path){
        painter_layer.setPen(QPen(QColor(hex_color_pink),2*news));
        cv::Point2f cur_path;
        cv::Point2f next_path;
        float cur_x =0;
        float cur_y =0;
        float next_x=0;
        float next_y=0;
        float target_angle=0;
        for(int i=0; i<probot->curPath.size()-1; i++){
            cur_path = setAxis(probot->curPath[i].point);
            next_path = setAxis(probot->curPath[i+1].point);
            target_angle = setAxis(probot->curPath[i+1].angle);
            cur_x = (cur_path.x - draw_x)*news;
            cur_y = (cur_path.y - draw_y)*news;
            next_x = (next_path.x - draw_x)*news;
            next_y = (next_path.y - draw_y)*news;
            painter_layer.drawLine(cur_x,cur_y,next_x,next_y);
        }

        if(probot->curPath.size() > 0){
            float distance = (pmap->robot_radius/grid_width)*2*news;
            float distance2 = distance*0.8;
            float th_dist = M_PI/8;

            float x =   (next_x - distance    * qSin(target_angle));
            float y =   (next_y - distance    * qCos(target_angle));
            float x1 =  (next_x - distance2   * qSin(target_angle-th_dist));
            float y1 =  (next_y - distance2   * qCos(target_angle-th_dist));
            float x2 =  (next_x - distance2   * qSin(target_angle+th_dist));
            float y2 =  (next_y - distance2   * qCos(target_angle+th_dist));
            float rad = pmap->robot_radius*news/grid_width;

            QPainterPath path;
            path.addRoundedRect((next_x-rad),(next_y-rad),rad*2,rad*2,rad,rad);
            painter_layer.setPen(QPen(QColor(hex_color_pink),2*news));
            painter_layer.fillPath(path,QBrush(QColor("white")));
            painter_layer.drawPath(path);
            painter_layer.drawLine(QLine(x1,y1,x,y));
            painter_layer.drawLine(QLine(x2,y2,x,y));


            if(show_local_path){
                QPainterPath circles;
                for(int i=0; i<probot->localpathSize; i++){
                    int rad = 2;
                    int xx = (setAxis(probot->localPath[i].point).x - draw_x)*news - rad;
                    int yy = (setAxis(probot->localPath[i].point).y - draw_y)*news - rad;
                    circles.addRoundedRect(xx,yy,rad*2,rad*2,rad,rad);
                    painter_layer.fillPath(circles,Qt::white);
                }
            }
        }
    }



    //Cur Brush View
    if(show_brush){
        float cur_x = (curPoint.x - draw_x)*news;
        float cur_y = (curPoint.y - draw_y)*news;
        if(cur_line_color == 255){
            painter_layer.setPen(QPen(Qt::black,1*news));
            painter_layer.drawRoundedRect(cur_x-cur_line_width*news/2,cur_y-cur_line_width*news/2,cur_line_width*news,cur_line_width*news,cur_line_width*news/2,cur_line_width*news/2);
        }else{
            painter_layer.setPen(QPen(Qt::white,1*news));
            painter_layer.drawRoundedRect(cur_x-cur_line_width*news/2,cur_y-cur_line_width*news/2,cur_line_width*news,cur_line_width*news,cur_line_width*news/2,cur_line_width*news/2);
        }
    }

    //로봇 현재 위치 기준으로 라이다 표시
    if(show_lidar){        
        for(int i=0; i<360; i++){
            painter_layer.setPen(QPen(QColor("red"),2*news));
            float robot_x = robot_pose.x;
            float robot_y = robot_pose.y;
            if(probot->lidar_data[i] > grid_width){
                float x = (robot_x + (probot->lidar_data[i]/grid_width)*news*cos((-M_PI*i)/180 + robot_angle));
                float y = (robot_y + (probot->lidar_data[i]/grid_width)*news*sin((-M_PI*i)/180 + robot_angle));
                painter_layer.drawPoint(round(x),round(y));
            }
        }

    }
    //로봇 현재 위치 표시(매핑 중이거나 위치 초기화 성공했을 때만)
//    qDebug() << "show robot " << show_robot << ", " << set_init_flag;
    if(show_robot){
        if(probot->localization_state == LOCAL_READY || mode == "mapping"){
            float loc_x = robot_pose.x;
            float loc_y = robot_pose.y;
            float distance = (pmap->robot_radius/grid_width)*2*news;
            float distance2 = distance*0.8;
            float th_dist = (M_PI/8);
            float rad = (pmap->robot_radius/grid_width)*news;

            float x =   (loc_x + distance    * qCos(robot_angle));
            float y =   (loc_y + distance    * qSin(robot_angle));
            float x1 =  (loc_x + distance2   * qCos(robot_angle-th_dist));
            float y1 =  (loc_y + distance2   * qSin(robot_angle-th_dist));
            float x2 =  (loc_x + distance2   * qCos(robot_angle+th_dist));
            float y2 =  (loc_y + distance2   * qSin(robot_angle+th_dist));
            QPainterPath path;
            QPolygonF polygon;
            polygon << QPointF(x1,y1) << QPointF(x2,y2) << QPointF(x,y) << QPointF(x1,y1);
            path.addRoundedRect((loc_x-rad),(loc_y-rad),rad*2,rad*2,rad,rad);
            painter_layer.setPen(QPen(QColor("white"),2*news));
            painter_layer.fillPath(path,QBrush(QColor("red")));
            painter_layer.drawPath(path);
            QPainterPath direction;
            direction.addPolygon(polygon);
            painter_layer.fillPath(direction,QBrush(QColor("red")));

            if(set_init_pressed){
                cv::Point2f init_pose = set_init_pose.point;
                float init_angle = set_init_pose.angle;
                float init_x = (init_pose.x - draw_x)*news;
                float init_y = (init_pose.y - draw_y)*news;
                float distance = (pmap->robot_radius/grid_width)*2*news;
                float distance2 = distance*0.8;
                float th_dist = (M_PI/8);
                float rad = (pmap->robot_radius/grid_width)*news;

                float x =   (init_x + distance    * qCos(init_angle));
                float y =   (init_y + distance    * qSin(init_angle));
                float x1 =  (init_x + distance2   * qCos(init_angle-th_dist));
                float y1 =  (init_y + distance2   * qSin(init_angle-th_dist));
                float x2 =  (init_x + distance2   * qCos(init_angle+th_dist));
                float y2 =  (init_y + distance2   * qSin(init_angle+th_dist));

                QPainterPath path;
                path.addRoundedRect((init_x-rad),(init_y-rad),rad*2,rad*2,rad,rad);
                painter_layer.setPen(QPen(QColor("white"),2*news));
                painter_layer.fillPath(path,QBrush(QColor(hex_color_green)));
                painter_layer.drawPath(path);
                painter_layer.drawLine(QLine(x1,y1,x,y));
                painter_layer.drawLine(QLine(x2,y2,x,y));
            }
        }else if(set_init_flag){
            cv::Point2f init_pose = set_init_pose.point;
            float init_angle = set_init_pose.angle;
            float init_x = (init_pose.x - draw_x)*news;
            float init_y = (init_pose.y - draw_y)*news;
            float distance = (pmap->robot_radius/grid_width)*2*news;
            float distance2 = distance*0.8;
            float th_dist = (M_PI/8);
            float rad = (pmap->robot_radius/grid_width)*news;

            float x =   (init_x + distance    * qCos(init_angle));
            float y =   (init_y + distance    * qSin(init_angle));
            float x1 =  (init_x + distance2   * qCos(init_angle-th_dist));
            float y1 =  (init_y + distance2   * qSin(init_angle-th_dist));
            float x2 =  (init_x + distance2   * qCos(init_angle+th_dist));
            float y2 =  (init_y + distance2   * qSin(init_angle+th_dist));
            QPainterPath path;
            path.addRoundedRect((init_x-rad),(init_y-rad),rad*2,rad*2,rad,rad);
            painter_layer.setPen(QPen(QColor("white"),2*news));
            painter_layer.fillPath(path,QBrush(QColor(hex_color_green)));
            painter_layer.drawPath(path);
            painter_layer.drawLine(QLine(x1,y1,x,y));
            painter_layer.drawLine(QLine(x2,y2,x,y));
        }
    }

    if(show_edge){
        for(auto& it: nodes){
            if(it.second == nullptr)
            {
                continue;
            }
            // get cur id
            QString id0 = it.second->id;

            // draw node
            cv::Vec3d pose = nodes[id0]->pose;
            float loc_x = (pose[0] - draw_x)*news;
            float loc_y = (pose[1] - draw_y)*news;
            float distance = (pmap->robot_radius/grid_width)*2*news;
            float distance2 = distance*0.8;
            float th_dist = (M_PI/8);
            float rad = (pmap->robot_radius/grid_width)*news;

            float x =   (loc_x + distance    * qCos(pose[2]));
            float y =   (loc_y + distance    * qSin(pose[2]));
            float x1 =  (loc_x + distance2   * qCos(pose[2]-th_dist));
            float y1 =  (loc_y + distance2   * qSin(pose[2]-th_dist));
            float x2 =  (loc_x + distance2   * qCos(pose[2]+th_dist));
            float y2 =  (loc_y + distance2   * qSin(pose[2]+th_dist));
            QPainterPath path;

            painter_layer.setPen(QPen(Qt::white,1*news));
            for(size_t p = 0; p < it.second->linked.size(); p++){
                QString id1 = it.second->linked[p];

                int n1x = (nodes[it.second->id]->pose[0] - draw_x)*news;
                int n1y = (nodes[it.second->id]->pose[1] - draw_y)*news;
                int n2x = (nodes[id1]->pose[0] - draw_x)*news;
                int n2y = (nodes[id1]->pose[1] - draw_y)*news;

                painter_layer.setPen(QPen(Qt::yellow,1*news));
                painter_layer.drawLine(QLine(n1x,n1y,n2x,n2y));
            }




        }
    }

    if(show_node){
        for(auto& it: nodes){
            if(it.second == nullptr)
            {
                continue;
            }
            // get cur id
            QString id0 = it.second->id;

            // draw node
            cv::Vec3d pose = nodes[id0]->pose;
            float loc_x = (pose[0] - draw_x)*news;
            float loc_y = (pose[1] - draw_y)*news;
            float distance = (pmap->robot_radius/grid_width)*2*news;
            float distance2 = distance*0.8;
            float th_dist = (M_PI/8);
            float rad = (pmap->robot_radius/grid_width)*news;

            float x =   (loc_x + distance    * qCos(pose[2]));
            float y =   (loc_y + distance    * qSin(pose[2]));
            float x1 =  (loc_x + distance2   * qCos(pose[2]-th_dist));
            float y1 =  (loc_y + distance2   * qSin(pose[2]-th_dist));
            float x2 =  (loc_x + distance2   * qCos(pose[2]+th_dist));
            float y2 =  (loc_y + distance2   * qSin(pose[2]+th_dist));
            QPainterPath path;

            if(it.second->attrib == "Route"){
                path.addRoundedRect((loc_x-rad/2),(loc_y-rad/2),rad,rad,rad/2,rad/2);
                painter_layer.setPen(QPen(QColor(hex_color_yellow),1*news));
                painter_layer.fillPath(path,QBrush(QColor(hex_color_yellow)));
                painter_layer.drawPath(path);

            }else if(it.second->attrib == "Charging"){
                path.addRoundedRect((loc_x-rad),(loc_y-rad),rad*2,rad*2,rad,rad);
                painter_layer.setPen(QPen(Qt::white,1*news));
                painter_layer.drawPath(path);
                painter_layer.drawLine(x1,y1,x,y);
                painter_layer.drawLine(x,y,x2,y2);
                painter_layer.drawPath(path);
                QImage image(":/icon/icon_charge_2.png");
                painter_layer.drawImage(QRectF((loc_x-rad),(loc_y-rad),rad*2,rad*2),image,QRectF(0,0,image.width(),image.height()));

            }else if(it.second->attrib == "Resting"){
                path.addRoundedRect((loc_x-rad),(loc_y-rad),rad*2,rad*2,rad,rad);
                painter_layer.setPen(QPen(Qt::white,1*news));

                painter_layer.drawPath(path);
                painter_layer.drawLine(x1,y1,x,y);
                painter_layer.drawLine(x,y,x2,y2);
                painter_layer.drawPath(path);
                QImage image(":/icon/icon_home_2.png");
                painter_layer.drawImage(QRectF((loc_x-rad),(loc_y-rad),rad*2,rad*2),image,QRectF(0,0,image.width(),image.height()));

            }else if(it.second->attrib == "Cleaning"){
                path.addRoundedRect((loc_x-rad),(loc_y-rad),rad*2,rad*2,rad,rad);

                painter_layer.setPen(QPen(Qt::white,1*news));

                painter_layer.drawPath(path);
                painter_layer.drawLine(x1,y1,x,y);
                painter_layer.drawLine(x,y,x2,y2);
                painter_layer.drawPath(path);
                QImage image(":/icon/icon_home_2.png");
                painter_layer.drawImage(QRectF((loc_x-rad),(loc_y-rad),rad*2,rad*2),image,QRectF(0,0,image.width(),image.height()));


            }else if(it.second->attrib == "Serving"){
                path.addRoundedRect((loc_x-rad),(loc_y-rad),rad*2,rad*2,rad,rad);
                painter_layer.setPen(QPen(Qt::white,1*news));

                painter_layer.fillPath(path,QBrush(QColor(hex_color_pink)));

                painter_layer.drawPath(path);
                painter_layer.drawLine(QLine(x1,y1,x,y));
                painter_layer.drawLine(QLine(x2,y2,x,y));
            }

        }

        QPainterPath path1;
        auto it_sel = nodes.find(click_info.sel_node);
        if(it_sel != nodes.end() && it_sel->second != nullptr)
        {
            float loc_x = (it_sel->second->pose[0] - draw_x)*news;
            float loc_y = (it_sel->second->pose[1] - draw_y)*news;
            float rad = ((pmap->robot_radius/grid_width))*news;
            if(it_sel->second->attrib == "Route"){
                path1.addRoundedRect((loc_x-rad/2),(loc_y-rad/2),rad,rad,rad/2,rad/2);
                painter_layer.setPen(QPen(QColor(hex_color_blue),1*news));
                painter_layer.fillPath(path1,QBrush(QColor(hex_color_blue)));
                painter_layer.drawPath(path1);
            }else if(it_sel->second->attrib == "Charging"){
                path1.addRoundedRect((loc_x-rad),(loc_y-rad),rad*2,rad*2,rad,rad);

                painter_layer.setPen(QPen(Qt::white,2*news));
                painter_layer.fillPath(path1,QBrush(QColor(hex_color_blue)));

                painter_layer.drawPath(path1);
                QImage image(":/icon/icon_charge_2.png");
                painter_layer.drawImage(QRectF((loc_x-rad),(loc_y-rad),rad*2,rad*2),image,QRectF(0,0,image.width(),image.height()));

            }else if(it_sel->second->attrib == "Resting"){
                path1.addRoundedRect((loc_x-rad),(loc_y-rad),rad*2,rad*2,rad,rad);
                painter_layer.setPen(QPen(Qt::white,2*news));
                painter_layer.fillPath(path1,QBrush(QColor(hex_color_blue)));

                painter_layer.drawPath(path1);
                QImage image(":/icon/icon_home_2.png");
                painter_layer.drawImage(QRectF((loc_x-rad),(loc_y-rad),rad*2,rad*2),image,QRectF(0,0,image.width(),image.height()));
            }else if(it_sel->second->attrib == "Cleaning"){
                path1.addRoundedRect((loc_x-rad),(loc_y-rad),rad*2,rad*2,rad,rad);

                painter_layer.setPen(QPen(Qt::white,2*news));
                painter_layer.fillPath(path1,QBrush(QColor(hex_color_blue)));

                painter_layer.drawPath(path1);
                QImage image(":/icon/icon_home_2.png");
                painter_layer.drawImage(QRectF((loc_x-rad),(loc_y-rad),rad*2,rad*2),image,QRectF(0,0,image.width(),image.height()));

            }else if(it_sel->second->attrib == "Serving"){
                path1.addRoundedRect((loc_x-rad),(loc_y-rad),rad*2,rad*2,rad,rad);
                painter_layer.setPen(QPen(Qt::white,2*news));

                painter_layer.fillPath(path1,QBrush(QColor(hex_color_blue)));

                painter_layer.drawPath(path1);
            }
        }

        QPainterPath path2;
        auto it_pre = nodes.find(click_info.pre_node);
        if(it_pre != nodes.end() && it_pre->second != nullptr)
        {
            float loc_x = (it_pre->second->pose[0] - draw_x)*news;
            float loc_y = (it_pre->second->pose[1] - draw_y)*news;
//                qDebug() << "it_pre " << it_pre->second->id <<  loc_x << loc_y;
            float rad = ((pmap->robot_radius/grid_width)+2)*news;
            path2.addRoundedRect((loc_x-rad),(loc_y-rad),rad*2,rad*2,rad,rad);
            painter_layer.setPen(QPen(QColor(hex_color_pink),1*news));
            painter_layer.drawPath(path2);
        }

        QPainterPath path3;
        auto it_cur = nodes.find(click_info.cur_node);
        if(it_cur != nodes.end() && it_cur->second != nullptr)
        {
            float loc_x = (it_cur->second->pose[0] - draw_x)*news;
            float loc_y = (it_cur->second->pose[1] - draw_y)*news;
//                qDebug() << "it_cur " << it_cur->second->id <<  loc_x << loc_y;
            float rad = ((pmap->robot_radius/grid_width)+2)*news;
            path3.addRoundedRect((loc_x-rad),(loc_y-rad),rad*2,rad*2,rad,rad);
            painter_layer.setPen(QPen(QColor(hex_color_blue),1*news));
            painter_layer.drawPath(path3);
        }
    }

    if(show_name){
        for(auto& it: nodes){
            if(it.second == nullptr)
            {
                continue;
            }
            // get cur id
            QString id0 = it.second->id;

            // draw node
            cv::Vec3d pose = nodes[id0]->pose;
            float loc_x = (pose[0] - draw_x)*news;
            float loc_y = (pose[1] - draw_y)*news;
            float distance = (pmap->robot_radius/grid_width)*2*news;
            float distance2 = distance*0.8;
            float th_dist = (M_PI/8);
            float rad = (pmap->robot_radius/grid_width)*news;

            float x =   (loc_x + distance    * qCos(pose[2]));
            float y =   (loc_y + distance    * qSin(pose[2]));
            float x1 =  (loc_x + distance2   * qCos(pose[2]-th_dist));
            float y1 =  (loc_y + distance2   * qSin(pose[2]-th_dist));
            float x2 =  (loc_x + distance2   * qCos(pose[2]+th_dist));
            float y2 =  (loc_y + distance2   * qSin(pose[2]+th_dist));
            QPainterPath path;

            if(it.second->attrib!= "Route"){
                QString name = id0;
                QStringList name_split = name.split(":");
                painter_layer.setPen(QPen(Qt::white,1*news));
                painter_layer.setFont(QFont("font/NotoSansKR-Medium",rad/2,QFont::Bold));
                painter_layer.drawText(loc_x+rad,loc_y-rad,name_split.back());
            }
        }
        auto it_sel = nodes.find(click_info.sel_node);
        if(it_sel != nodes.end() && it_sel->second != nullptr)
        {
            float loc_x = (it_sel->second->pose[0] - draw_x)*news;
            float loc_y = (it_sel->second->pose[1] - draw_y)*news;
            float rad = ((pmap->robot_radius/grid_width))*news;
            if(it_sel->second->attrib!= "Route"){
                QString name = it_sel->second->id;
                QStringList name_split = name.split(":");
                painter_layer.setPen(QPen(QColor(hex_color_blue),2*news));
                painter_layer.setFont(QFont("font/NotoSansKR-Bold",rad/2,QFont::Bold));
                painter_layer.drawText(loc_x+rad,loc_y-rad,name_split.back());
            }
        }
    }



    if(tempnode.isnew){
        float loc_x = (tempnode.point.x - draw_x)*news;
        float loc_y = (tempnode.point.y - draw_y)*news;
        float distance = (pmap->robot_radius/grid_width)*2*news;
        float distance2 = distance*0.8;
        float th_dist = (M_PI/8);
        float rad = ((pmap->robot_radius/grid_width)+2)*news;

        float x =   (loc_x + distance    * qCos(tempnode.angle));
        float y =   (loc_y + distance    * qSin(tempnode.angle));
        float x1 =  (loc_x + distance2   * qCos(tempnode.angle-th_dist));
        float y1 =  (loc_y + distance2   * qSin(tempnode.angle-th_dist));
        float x2 =  (loc_x + distance2   * qCos(tempnode.angle+th_dist));
        float y2 =  (loc_y + distance2   * qSin(tempnode.angle+th_dist));
        QPainterPath path;
        path.addRoundedRect((loc_x-rad),(loc_y-rad),rad*2,rad*2,rad,rad);
        painter_layer.setPen(QPen(Qt::cyan,1*news));

        painter_layer.drawPath(path);
        painter_layer.drawLine(QLine(loc_x,loc_y,x,y));

    }
    //줄 자 표시
    if(tool == "ruler"){
        QPainterPath path;
        if(ruler_point.size() == 1){
            float x = (ruler_point[0].x - draw_x)*news;
            float y = (ruler_point[0].y - draw_y)*news;
            path.addRoundedRect((x),(y),5*2,5*2,5,5);
//            qDebug() << ruler_point[0].x << ruler_point[0].y << x << y << news << x-5*news << y-5*news;
            painter_layer.fillPath(path,QBrush(QColor(hex_color_pink)));
            painter_layer.setPen(QPen(Qt::red,3*news));
            painter_layer.drawPath(path);
        }else if(ruler_point.size() == 2){
            float x1 = (ruler_point[0].x - draw_x);
            float y1 = (ruler_point[0].y - draw_y);
            path.addRoundedRect((x1*news-3),(y1*news-3),3*2,3*2,3,3);
            float x2 = (ruler_point[1].x - draw_x);
            float y2 = (ruler_point[1].y - draw_y);
            path.addRoundedRect((x2*news-5),(y2*news-5),5*2,5*2,5,5);
            painter_layer.fillPath(path,QBrush(QColor(hex_color_pink)));
            painter_layer.setPen(QPen(Qt::red,3*news));
            painter_layer.drawPath(path);

            painter_layer.setPen(QPen(QColor("red"),2*news));
            painter_layer.drawLine(round(x1*news),round(y1*news),round(x2*news),round(y2*news));

            float length = sqrt(pow(x1-x2,2)+pow(y1-y2,2));

            float angle = calculateAngle(cv::Point2f(x1,y1),cv::Point2f(x2,y2))*M_PI/180;
            cv::Point2f pos;
            pos.x = (x1+x2)/2;
            pos.y = (y1+y2)/2;
            float h = -30;
            float m = length/2;

            float angle2 = atan(h/m);
            float l = sqrt(m*m+h*h);

            float xdot = x1 + l*cos(angle+angle2);
            float ydot = y1 + l*sin(angle+angle2);

            painter_layer.setPen(QPen(QColor("yellow"),2*news));
            cv::Point2f center = cv::Point2f(xdot,ydot);

            int width = 100*news;
            int height= 30*news;
            painter_layer.translate(center.x*news,center.y*news);
            painter_layer.setFont(QFont("font/NotoSansKR-Medium",10*news));
            if(angle*180/M_PI > 90 || angle*180/M_PI < -90){
                painter_layer.rotate(angle*180/M_PI-180);
                painter_layer.drawText(QRect(-width/2,-height/2 - 60*news,width,height),Qt::AlignCenter,QString().asprintf("%.2f [m]",length*grid_width));

            }else{
                painter_layer.rotate(angle*180/M_PI);
                painter_layer.drawText(QRect(-width/2,-height/2,width,height),Qt::AlignCenter,QString().asprintf("%.2f [m]",length*grid_width));

            }
        }
    }
    update();
}

void MapHandler::autoTline(){
    file_travelline_ui = cv::Mat(file_width, file_width, CV_8UC3, cv::Scalar::all(0));
    file_avoid = cv::Mat(file_width, file_width, CV_8UC3, cv::Scalar::all(0));
    for(auto& it: nodes)
    {
        if(it.second == nullptr)
        {
            continue;
        }
        // get cur id
        QString id0 = it.second->id;

        // draw node
        cv::Vec3d pose = nodes[id0]->pose;
        for(size_t p = 0; p < it.second->linked.size(); p++)
        {
            QString id = it.second->linked[p];
            cv::Vec3d pose2 = nodes[id]->pose;
            cv::line(file_travelline_ui, cv::Point(pose[0], pose[1]), cv::Point(pose2[0], pose2[1]), color_navy, 1);
            cv::line(file_avoid, cv::Point(pose[0], pose[1]), cv::Point(pose2[0], pose2[1]), color_green, avoid_width*2/grid_width);
        }
    }
    qDebug() << "auto T line ";
    setMap();
}

void MapHandler::setMapTest(){

}
QJsonArray pose_to_array(cv::Vec3d pose)
{
    QJsonArray res;
    res.append(pose[0]);
    res.append(pose[1]);
    res.append(pose[2]);
    return res;
}

QJsonArray linked_to_array(std::vector<QString> linked)
{
    QJsonArray res;
    for(size_t p = 0; p < linked.size(); p++)
    {
        res.append(linked[p]);
    }
    return res;
}

cv::Vec3d array_to_pose(QJsonArray arr)
{
    cv::Vec3d res;
    res[0] = arr[0].toDouble();
    res[1] = arr[1].toDouble();
    res[2] = arr[2].toDouble();
    return res;
}
std::vector<QString> array_to_linked(QJsonArray arr)
{
    std::vector<QString> res;
    for(int p = 0; p < arr.size(); p++)
    {
        res.push_back(arr[p].toString());
    }
    return res;
}


void MapHandler::loadNode(){
    // load topology
    nodes.clear();
    QString topo_path = QDir::homePath()+"/RB_MOBILE/maps/"+map_name+"/topo.json";
    QFile file(topo_path);
    if(file.open(QIODevice::ReadOnly))
    {
        QByteArray data = file.readAll();
        QJsonDocument doc = QJsonDocument::fromJson(data);

        QJsonArray arr = doc.array();
        foreach(const QJsonValue &val, arr)
        {
            NODE *node = new NODE();

            QJsonObject obj = val.toObject();
            node->id = obj["id"].toString();
            node->attrib = obj["attrib"].toString();
            node->pose = array_to_pose(obj["pose"].toArray());
            node->linked = array_to_linked(obj["linked"].toArray());

            nodes[node->id] = node;
        }

        file.close();

        qDebug() << "[TOPOMAP] "+topo_path+" loaded, num:" << (int)nodes.size();
    }

}
void MapHandler::saveNode(){
    QString topo_path = QDir::homePath()+"/RB_MOBILE/maps/"+map_name+"/topo.json";
    QFile file(topo_path);
    if(file.open(QIODevice::WriteOnly))
    {
        QJsonArray arr;

        for(auto& it: nodes)
        {
            if(it.second == nullptr)
            {
                continue;
            }

            QString id = it.second->id;
            QString attrib = it.second->attrib;
            cv::Vec3d pose = it.second->pose;
            std::vector<QString> linked = it.second->linked;

            QJsonObject obj;
            obj["id"] = id;
            obj["attrib"] = attrib;
            obj["pose"] = pose_to_array(pose);
            obj["linked"] = linked_to_array(linked);
            arr.append(obj);
        }

        QJsonDocument doc(arr);
        file.write(doc.toJson());
        file.close();

        plog->write("[TOPOMAP] save : "+ topo_path);
    }
}
void MapHandler::setMap(){
    if(mode == "mapping"){
        map = QPixmap::fromImage(mat_to_qimage_cpy(pmap->map_mapping));
        grid_width = pmap->mapping_gridwidth*pmap->mapping_width/file_width;
        if(file_width != pmap->map_mapping.rows){
            file_width = pmap->map_mapping.rows;
            setFullScreen();
        }
    }else if(map_orin.rows > 0){
        file_width = map_orin.rows;
        grid_width = pmap->gridwidth;
        cv::Mat temp_orin, temp_travel, temp_travel_ui, temp_velmap;
        cv::Mat temp_obj, temp_avoid;
        cv::Mat temp_layer = cv::Mat(file_width,file_width,CV_8UC4,cv::Scalar::all(0));
        cv::cvtColor(map_orin,temp_orin,cv::COLOR_GRAY2BGRA);
        cv::cvtColor(file_velocity,temp_velmap,cv::COLOR_BGR2BGRA);
        cv::cvtColor(file_travelline,temp_travel,cv::COLOR_BGR2BGRA);
        cv::cvtColor(file_travelline_ui,temp_travel_ui,cv::COLOR_BGR2BGRA);
        cv::cvtColor(file_object,temp_obj,cv::COLOR_BGR2BGRA);
        cv::cvtColor(file_avoid,temp_avoid,cv::COLOR_BGR2BGRA);

//        qDebug() << show_velocitymap << show_avoid << show_robot << show_object << show_travelline;

        if(show_velocitymap){
            if(mode == "annot_velmap"){
                cv::multiply(cv::Scalar::all(1.0)-map_drawing_mask,temp_velmap,temp_velmap);
                //cv::add(temp_velmap,map_drawing,temp_velmap);
                cv::add(temp_velmap,map_drawing,temp_velmap);
            }
            cv::add(temp_layer,temp_velmap,temp_layer);
//            cv::imshow("vel",temp_layer);
        }
        if(show_avoid){
            if(mode == "annot_obs_area"){
                cv::multiply(cv::Scalar::all(1.0)-map_drawing_mask,temp_avoid,temp_avoid);
                cv::add(temp_avoid,map_drawing,temp_avoid);
            }
            cv::add(temp_layer,temp_avoid,temp_layer);
//            cv::imshow("obs",temp_layer);
        }
        if(show_object){
            if(mode == "annot_object_png"){
                cv::multiply(cv::Scalar::all(1.0)-map_drawing_mask,temp_obj,temp_obj);
                cv::add(temp_obj,map_drawing,temp_obj);
            }
            cv::multiply(cv::Scalar::all(1.0)-temp_obj,temp_layer,temp_layer);
            cv::add(temp_layer,temp_obj,temp_layer);
//            cv::imshow("obj",temp_layer);
        }

        if(show_velocitymap || show_object || show_avoid){
            cv::addWeighted(temp_orin,1,temp_layer,0.5,0,temp_orin);
        }

        if(show_travelline){
            if(flag_drawing){
                cv::add(temp_orin,map_drawing_tline,temp_orin);
            }
            if(mode == "annot_tline" || mode == "annot_location"){
                cv::multiply(cv::Scalar::all(1.0)-map_drawing_mask,temp_travel_ui,temp_travel_ui);
                cv::add(temp_travel_ui,map_drawing,temp_travel_ui);
                cv::addWeighted(temp_orin,1,temp_travel,0.5,0,temp_orin);
                cv::add(temp_orin,temp_travel_ui,temp_orin);
            }else{
                cv::addWeighted(temp_orin,1,temp_travel,0.5,0,temp_orin);
                cv::addWeighted(temp_orin,1,temp_travel_ui,1,0,temp_orin);
            }

        }

        if(!show_object && !show_velocitymap && !show_travelline && !show_avoid){
            cv::multiply(cv::Scalar::all(1.0)-map_drawing_mask,temp_orin,temp_orin);
            cv::add(temp_orin,map_drawing,temp_orin);
        }

        //orin
        map = QPixmap::fromImage(mat_to_qimage_cpy(temp_orin));
    }

    QPainter painter(&map);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);

    //잘라내기 박스 표시
    if(tool == "cut_map"){
        QPainterPath path;
        painter.setPen(QPen(Qt::red,10));
        path.addRect(QRectF(QPointF(cut_box[0].x,cut_box[0].y),QPointF(cut_box[1].x,cut_box[1].y)));
        painter.drawPath(path);

        QPainterPath circles;
        for(int j=0; j<2; j++){
            int rad = 30*res;
            int xx = cut_box[j].x*res - rad;
            int yy = cut_box[j].y*res - rad;
            circles.addRect(xx,yy,rad*2,rad*2);
            painter.fillPath(circles,Qt::white);
        }
    }
    setMapLayer();

}
void MapHandler::update(){
    final_map = QPixmap(2000,2000);
    QPainter pp(&final_map);
    pp.fillRect(0,0,2000,2000,Qt::black);
    pp.drawPixmap(0,0,2000,2000,map,draw_x,draw_y,draw_width,draw_width);
    pp.drawPixmap(0,0,2000,2000,map_layer);
    pmap->map = final_map;
}

void MapHandler::saveRotateMap(){
    cv::Mat map_edited_ui;
    if(tool == "cut_map"){
        map_orin(cv::Rect(cut_box[0].x,cut_box[0].y,(cut_box[1].x-cut_box[0].x),(cut_box[1].y-cut_box[0].y))).copyTo(map_edited_ui);
        pmap->cut_map[0] = cut_box[0].x;
        pmap->cut_map[1] = cut_box[0].y;
    }else{
        map_orin.copyTo(map_edited_ui);
        pmap->cut_map[0] = 0;
        pmap->cut_map[1] = 0;
    }
    rotate_angle = 0;

    cv::rotate(map_edited_ui,map_edited_ui,cv::ROTATE_90_CLOCKWISE);
    cv::flip(map_edited_ui,map_edited_ui,0);

    QString path = QDir::homePath() + "/RB_MOBILE/maps/" + map_name + "/map_edited.png";
    plog->write("[MapHandler] Save Map (Rotate) : "+tool+", "+QString().asprintf("%f,%f ~ %f,%f",cut_box[0].x,cut_box[0].y,cut_box[1].x,cut_box[1].y));

    //travel line 파일 없을 경우 대비해서 더미 제작
    if(!exist_travelline){
        cv::Mat temp_travelline = cv::Mat(map_edited_ui.rows,map_edited_ui.cols, CV_8U,cv::Scalar::all(0));
        QString path1 = QDir::homePath() + "/RB_MOBILE/maps/" + map_name + "/map_travel_line.png";
        cv::imwrite(path1.toStdString(),temp_travelline);
    }
    if(!exist_travelline_ui){
        cv::Mat temp_travellineui = cv::Mat(map_edited_ui.rows,map_edited_ui.cols, CV_8U,cv::Scalar::all(0));
        QString path1 = QDir::homePath() + "/RB_MOBILE/maps/" + map_name + "/map_travel_line_ui.png";
        cv::imwrite(path1.toStdString(),temp_travellineui);
    }
    cv::imwrite(path.toStdString(),map_edited_ui);
    updateMeta();
    loadFile(map_name,"");
}

void MapHandler::addObject(int x, int y){
    new_obj_flag = true;
    new_obj.is_rect = true;
    new_obj.points.clear();
    new_obj.points.push_back(cv::Point2f(x,y));
    new_obj.points.push_back(cv::Point2f(x,y));
    new_obj.points.push_back(cv::Point2f(x,y));
    new_obj.points.push_back(cv::Point2f(x,y));
    setMap();
}

void MapHandler::addObjectPoint(int x, int y){
    new_obj_flag = true;
    new_obj.is_rect = false;
    new_obj.points.push_back(cv::Point2f(x,y));
    setMap();
}
void MapHandler::setObject(int x, int y){
    if(new_obj.is_rect){
        if(new_obj.points.size() > 3){
            cv::Point2f orin = new_obj.points[0];
            new_obj.points[1] = cv::Point2f(orin.x,y);
            new_obj.points[2] = cv::Point2f(x,y);
            new_obj.points[3] = cv::Point2f(x,orin.y);
        }
    }else{
        new_obj.points[new_obj.points.size()-1] = cv::Point2f(x,y);
    }
    setMap();
}
void MapHandler::editObjectStart(int x, int y){
    select_obj_point = getObjectPointNum(x,y);
}
void MapHandler::editObject(int x, int y){
    int num = select_obj;
    int point = select_obj_point;
    if(num > -1 && num < pmap->objects.size()){
        if(pmap->objects[num].is_rect){
            if(point == 0){
                cv::Point2f pos = setAxisBack(cv::Point2f(x,y));
                pmap->objects[num].points[0].x = pos.x;
                pmap->objects[num].points[0].y = pos.y;
                pmap->objects[num].points[1].y = pos.y;
                pmap->objects[num].points[3].x = pos.x;
            }else if(point == 1){
                cv::Point2f pos = setAxisBack(cv::Point2f(x,y));
                pmap->objects[num].points[1].x = pos.x;
                pmap->objects[num].points[1].y = pos.y;
                pmap->objects[num].points[0].y = pos.y;
                pmap->objects[num].points[2].x = pos.x;
            }else if(point == 2){
                cv::Point2f pos = setAxisBack(cv::Point2f(x,y));
                pmap->objects[num].points[2].x = pos.x;
                pmap->objects[num].points[2].y = pos.y;
                pmap->objects[num].points[3].y = pos.y;
                pmap->objects[num].points[1].x = pos.x;
            }else if(point == 3){
                cv::Point2f pos = setAxisBack(cv::Point2f(x,y));
                pmap->objects[num].points[3].x = pos.x;
                pmap->objects[num].points[3].y = pos.y;
                pmap->objects[num].points[2].y = pos.y;
                pmap->objects[num].points[0].x = pos.x;
            }
            plog->write("[MapHandler] edit Object : " + QString().asprintf("(%d, %d, %d, %d)",num,point,x,y));
        }else{
            if(point > -1 && point < pmap->objects[num].points.size()){
                cv::Point2f pos = setAxisBack(cv::Point2f(x,y));
                pmap->objects[num].points[point].x = pos.x;
                pmap->objects[num].points[point].y = pos.y;
                plog->write("[MapHandler] edit Object : "+ QString().asprintf("(%d, %d, %d, %d)",num,point,x,y));
            }else{
                plog->write("[MapHandler] edit Object : " + QString().asprintf("(%d, %d, %d, %d)",num,point,x,y) + " but pose size error");
            }
        }

        pmap->annotation_edited = true;
    }
    initObject();
    setMap();
}
void MapHandler::saveObject(){
    OBJECT temp;
    if(new_obj.is_rect){
        plog->write("[MapHandler] ADD Object (Rect) : "+QString().asprintf("(%f,%f) ,(%f,%f)",new_obj.points[0].x, new_obj.points[0].y, new_obj.points[2].x,new_obj.points[2].y));
    }else{
        plog->write("[MapHandler] ADD Object : "+QString().asprintf("%d",new_obj.points.size()));
    }

    temp.is_rect = new_obj.is_rect;
    for(int i=0; i<new_obj.points.size(); i++){
        temp.points.push_back(setAxisBack(new_obj.points[i]));
    }
    pmap->annotation_edited = true;
    pmap->objects.push_back(temp);
    clearObjectAll();
    setMap();
}
void MapHandler::clearObject(){
    new_obj_flag = false;
    new_obj.points.clear();
    initObject();
    setMap();
}
void MapHandler::clearObjectAll(){
    new_obj_flag = false;
    new_obj.points.clear();
    select_obj = -1;
    select_obj_point = -1;
    initObject();
    setMap();
}
void MapHandler::undoObject(){
    new_obj.points.pop_back();
    if(new_obj.points.size() <= 0){
        new_obj_flag = false;
    }
    initObject();
    setMap();
}
int MapHandler::getObjectNum(int x, int y){
    cv::Point2f pos = setAxisBack(cv::Point2f(x,y));
    for(int i=0; i<pmap->list_obj_uL.size(); i++){
        if(pos.x<pmap->list_obj_uL[i].x && pos.x>pmap->list_obj_dR[i].x){
            if(pos.y<pmap->list_obj_uL[i].y && pos.y>pmap->list_obj_dR[i].y){
                return i;
            }
        }
    }
    return -1;
}
int MapHandler::getObjectPointNum(int x, int y){
    cv::Point2f pos = setAxisBack(cv::Point2f(x,y));
    int num = select_obj;
    if(num < pmap->objects.size() && num > -1){
        if(num != -1){
            for(int j=0; j<pmap->objects[num].points.size(); j++){
                qDebug() << pmap->objects[num].points[j].x << pmap->objects[num].points[j].y;
                if(fabs(pmap->objects[num].points[j].x - pos.x) < 0.2){
                    if(fabs(pmap->objects[num].points[j].y - pos.y) < 0.2){
                        qDebug() << "Match Point !!" << num << j;
                        return j;
                    }
                }
            }
        }
    }
    qDebug() << "can't find obj num : " << x << y;
    return -1;
}
void MapHandler::selectObject(int num){
    select_obj = num;
    setMap();
}
void MapHandler::removeObject(int num){
    clearObjectAll();
}
bool MapHandler::getObjectFlag(){
    return new_obj_flag;
}
void MapHandler::initObject(){
    objs.clear();
    for(int i=0; i<pmap->objects.size(); i++){
        OBJECT temp;
        temp.is_rect = pmap->objects[i].is_rect;
        for(int j=0; j<pmap->objects[i].points.size(); j++){
            temp.points.push_back(setAxis(pmap->objects[i].points[j]));
        }
        objs.push_back(temp);
    }
}
void MapHandler::updateMeta(){
    QString path = QDir::homePath() + "/RB_MOBILE/maps/"+ map_name + "/map_meta.ini";
    QSettings setting(path, QSettings::IniFormat);
    pmap->width = cut_box[1].x - cut_box[0].x;
    pmap->height = cut_box[1].y - cut_box[0].y;
    pmap->origin[0] = round(pmap->width/2);
    pmap->origin[1] = round(pmap->height/2);
    setting.setValue("map_metadata/map_edited_angle",QString::number(pmap->map_rotate_angle));
    setting.setValue("map_metadata/map_edited_w",QString::number(pmap->width));
    setting.setValue("map_metadata/map_edited_h",QString::number(pmap->height));
    setting.setValue("map_metadata/map_edited_origin_u",QString::number(pmap->origin[0]));
    setting.setValue("map_metadata/map_edited_origin_v",QString::number(pmap->origin[1]));
    setting.setValue("map_metadata/map_edited_cut_u",QString::number(pmap->cut_map[0]));
    setting.setValue("map_metadata/map_edited_cut_v",QString::number(pmap->cut_map[1]));
    plog->write("[MapHandler] UPDATE META : "+QString().asprintf("%d, %d, %d, %d, %d, %d, %d",pmap->map_rotate_angle, pmap->cut_map[0], pmap->cut_map[1], pmap->width,pmap->height, pmap->origin[0],pmap->origin[1]));
}
void MapHandler::setBoxPoint(int num, int x, int y){
    int min,max;
    if(x < 0) x = 0;
    if(y < 0) y = 0;

    if(x > file_width) x = file_width;
    if(y > file_width) y = file_width;
    if(x < y){
        min = x;
        max = y;
    }else{
        min = y;
        max = x;
    }

    if(num == 0){
        cut_box[0].x = orin_box[0].x - (orin_box[0].x - max);
        cut_box[0].y = orin_box[0].y - (orin_box[0].x - max);
    }else if(num == 1){
        cut_box[1].x = orin_box[1].x - (orin_box[1].x - max);
        cut_box[1].y = orin_box[1].y - (orin_box[1].x - max);
    }else{
        int width = cut_box[1].x - cut_box[0].x;
        int height = cut_box[1].y - cut_box[0].y;

        cv::Point2f temp_1 = orin_box[0] + (cv::Point2f(x,y) - orin_box[2]);
        cv::Point2f temp_2 = orin_box[1] + (cv::Point2f(x,y) - orin_box[2]);

        if(temp_1.x < 0){
            temp_1.x = 0;
            temp_2.x = width;
        }else if(temp_2.x > file_width){
            temp_1.x = file_width-width;
            temp_2.x = file_width;
        }
        if(temp_1.y < 0){
            temp_1.y = 0;
            temp_2.y = height;
        }else if(temp_2.y > file_width){
            temp_1.y = file_width-height;
            temp_2.y = file_width;
        }
        cut_box[0] = temp_1;
        cut_box[1] = temp_2;
    }
    setMap();
}
int MapHandler::getPointBox(int x, int y){
    for(int i=0; i<2; i++){
        if(fabs(cut_box[i].x - x) < 50){
            if(fabs(cut_box[i].y - y) < 50){
                orin_box[0] = cut_box[0];
                orin_box[1] = cut_box[1];
                return i;
            }
        }
    }

    orin_box[0] = cut_box[0];
    orin_box[1] = cut_box[1];
    orin_box[2] = cv::Point2f(x,y);
    return -1;
}

void MapHandler::initRotate(){
    rotate_angle = 0;
    pmap->map_rotate_angle = 0;
    cut_box[0].x = 0;
    cut_box[0].y = 0;
    cut_box[1].x = file_width;
    cut_box[1].y = file_width;
    setMap();
}

void MapHandler::removeLocation(int num){
    int count = 0;
    for(int i=0; i<pmap->locations.size(); i++){
        if(pmap->locations[i].type == "Serving"){
            if(count == num){
                plog->write("[MapHandler] Remove Location : "+pmap->locations[i].name+" ("+QString::number(i)+" )");
                pmap->locations.removeAt(i);
            }
            count++;
        }
    }
    initLocation();
    setMapLayer();
}

void MapHandler::setTableNumberAuto(){
    QMap<int,int> group_num;/*
    plog->write("[MapHandler] Set Table Number Auto : "+QString::number(pmap->locations.size()));
    for(int i=0; i<pmap->locations.size(); i++){
        if(pmap->locations[i].type == "Serving"){
            if(group_num[pmap->locations[i].group] == 0){
                group_num[pmap->locations[i].group] = 2;
            }else{
                pmap->locations[i].number = group_num[pmap->locations[i].group]++;
            }
        }
    }*/
}

void MapHandler::setSize(int x, int y, float s){
    float over = canvas_width*(s-1)/2;
    scale = scale/s;
    draw_width = round(file_width*scale);
    setX(-x + over);
    setY(-y + over);
    setMapLayer();
}
void MapHandler::zoomIn(int x, int y, float dist){
    float scale_prev = scale;
    scale -= dist*0.001;
    if(scale < 0.1){
        scale = 0.1;
    }

    float realx = draw_x + (float)x * draw_width/canvas_width;//file_width*(scale - prev_scale)*((float)x/canvas_width);
    float realy = draw_y + (float)y * draw_width/canvas_width;
    draw_width = round(scale*file_width);

//    qDebug() << "zoomIn" << x << y << canvas_width << realx << realy;

    prev_scale = scale;

    float newx = ((float)draw_x - realx)*scale/scale_prev + realx;// * draw_width / draw_width_prev;
    float newy = ((float)draw_y - realy)*scale/scale_prev + realy;// * draw_width / draw_width_prev;

//    qDebug() << "zoomIn2 " << draw_x << draw_y <<newx << newy << draw_width;

    setX(newx);
    setY(newy);

    setMapLayer();
}
void MapHandler::zoomOut(int x, int y, float dist){
    float scale_prev = scale;
    scale += dist*0.001;
    if(scale > 1)
        scale =1;
    float realx = draw_x + (float)x * draw_width/canvas_width;//file_width*(scale - prev_scale)*((float)x/canvas_width);
    float realy = draw_y + (float)y * draw_width/canvas_width;
//    qDebug() << "zoomOut" << x << y << draw_width << canvas_width << realx << realy;

    draw_width = round(scale*file_width);
    prev_scale = scale;
    float newx = ((float)draw_x - realx)*scale/scale_prev + realx;// * draw_width / draw_width_prev;
    float newy = ((float)draw_y - realy)*scale/scale_prev + realy;// * draw_width / draw_width_prev;

    setX(newx);
    setY(newy);
//    setZoomCenter(realx,realy);
    setMapLayer();
//    update();
}

void MapHandler::setInitPose(int x, int y, float th){
    set_init_flag = true;
    set_init_pose.point.x = x;
    set_init_pose.point.y = y;
    set_init_pose.angle = th;
    setMap();
}

void MapHandler::clearInitPose(){
    set_init_flag = false;
}

void MapHandler::rotateMap(int angle){
    rotate_angle = angle;
    pmap->map_rotate_angle = angle;
//    qDebug() << "rotate map " << angle << file_width << map_orin.rows;
    //맵 회전
    cv::Mat rot = cv::getRotationMatrix2D(cv::Point2f(file_width/2, file_width/2),-rotate_angle,1.0);
    if(exist_edited)
        file_edited.copyTo(map_orin);
    else if(exist_raw)
        file_raw.copyTo(map_orin);
    else
        map_orin = cv::Mat(1000,1000,CV_8U,cv::Scalar::all(0));

    cv::warpAffine(map_orin,map_orin,rot,map_orin.size(),cv::INTER_NEAREST);
    setMap();
}

void MapHandler::rotateMapCW(){
    rotate_angle++;
    pmap->map_rotate_angle = rotate_angle;
    //맵 회전
    cv::Mat rot = cv::getRotationMatrix2D(cv::Point2f(file_width/2, file_width/2),-rotate_angle,1.0);
    if(exist_edited)
        file_edited.copyTo(map_orin);
    else if(exist_raw)
        file_raw.copyTo(map_orin);
    else
        map_orin = cv::Mat(1000,1000,CV_8U,cv::Scalar::all(0));

    cv::warpAffine(map_orin,map_orin,rot,map_orin.size(),cv::INTER_NEAREST);
    setMap();
}

void MapHandler::rotateMapCCW(){
    rotate_angle--;
    pmap->map_rotate_angle = rotate_angle;
    //맵 회전
    cv::Mat rot = cv::getRotationMatrix2D(cv::Point2f(file_width/2, file_width/2),-rotate_angle,1.0);

    if(exist_edited)
        file_edited.copyTo(map_orin);
    else if(exist_raw)
        file_raw.copyTo(map_orin);
    else
        map_orin = cv::Mat(1000,1000,CV_8U,cv::Scalar::all(0));
    cv::warpAffine(map_orin,map_orin,rot,map_orin.size(),cv::INTER_NEAREST);
    setMap();
}

void MapHandler::move(int x, int y){
    setX(x);
    setY(y);
    setMapLayer();
}

void MapHandler::setX(int newx){
    if(newx < 0)
        draw_x = 0;
    else if(newx > file_width - draw_width)
        draw_x = file_width - draw_width;
    else
        draw_x = round(newx);
}

void MapHandler::setY(int newy){
    if(newy < 0)
        draw_y = 0;
    else if(newy > file_width - draw_width)
        draw_y = file_width - draw_width;
    else
        draw_y = round(newy);

}

void MapHandler::setZoomCenter(int x, int y){
    float newx = (float)x-draw_width/2;//*(scale)*((float)x/file_width);
    float newy = (float)y-draw_width/2;//*(scale)*((float)y/file_width);

//    qDebug() << "setZoomCenter " << file_width << draw_width << canvas_width << scale << x << y << draw_x << draw_y << newx << newy;
    setX(newx);
    setY(newy);

    setMapLayer();
}

bool MapHandler::getDrawingFlag(){
    if(lines.size() > 0 || line.size() > 0){
        return true;
    }else{
        return false;
    }
}

bool MapHandler::getDrawingUndoFlag(){
    if(dot_trash.size() > 0 || lines_trash.size() > 0){
        return true;
    }else{
        return false;
    }
}

void MapHandler::startDrawingLine(int x, int y){
//    new_straight_flag = true;
//    spline_dot.clear();
//    straight[0].x = x;
//    straight[0].y = y;
//    straight[1].x = x;
//    straight[1].y = y;
//    setMap();
}

void MapHandler::startSpline(int x, int y){
    line.clear();
    spline_dot.clear();
    lines_trash.clear();
    curPoint.x = x;
    curPoint.y = y;
    line.push_back(curPoint);
    spline_dot.push_back(curPoint);
}

void MapHandler::endSpline(bool save){
    if(save){
        LINE temp_line;
        temp_line.color = cur_line_color;
        temp_line.width = cur_line_width;
        temp_line.points = line;
        lines.push_back(temp_line);
    }
    line.clear();
    spline_dot.clear();
    lines_trash.clear();
    setMap();
}

void MapHandler::drawSpline(){
    line.clear();
    setMapDrawing();
    if(spline_dot.size() > 2){
        std::vector<double> x_list;
        std::vector<double> y_list;
        std::vector<double> d_list;

        double sum_d = 0;
        d_list.push_back(sum_d);
        x_list.push_back(spline_dot[0].x);
        y_list.push_back(spline_dot[0].y);
        for(size_t p = 1; p<spline_dot.size(); p++){
            double x0 = spline_dot[p-1].x;
            double y0 = spline_dot[p-1].y;
            double x1 = spline_dot[p].x;
            double y1 = spline_dot[p].y;

            double dx = x1-x0;
            double dy = y1-y0;

            if(std::sqrt(dx*dx + dy*dy) > 0){
                sum_d += std::sqrt(dx*dx + dy*dy);
                d_list.push_back(sum_d);
                x_list.push_back(spline_dot[p].x);
                y_list.push_back(spline_dot[p].y);
            }
        }

        tk::spline::spline_type type = tk::spline::cspline_hermite;
        tk::spline sx, sy;
        if(d_list.size() > 2 && x_list.size() > 2 && y_list.size() > 2){
            sx.set_points(d_list, x_list, type);
            sx.make_monotonic();
            sy.set_points(d_list, y_list, type);
            sy.make_monotonic();

            for(double d = 0; d<=sum_d; d+= grid_width){
                line.push_back(cv::Point2f(sx(d),sy(d)));
            }
            for(int i=0; i<line.size()-1; i++){
                cv::line(map_drawing,line[i],line[i+1],cv::Scalar(cur_line_color,cur_line_color,cur_line_color,255),cur_line_width,8,0);
                cv::line(map_drawing_mask,line[i],line[i+1],cv::Scalar::all(255),cur_line_width,8,0);
            }

        }else{
            line = spline_dot;
        }
    }else{
        if(spline_dot.size() == 1){
            line.push_back(spline_dot[0]);
            line.push_back(spline_dot[0]);
            cv::circle(map_drawing, spline_dot[0], 1, cv::Scalar(cur_line_color,cur_line_color,cur_line_color),-1,8,0);
            cv::circle(map_drawing_mask, spline_dot[0], 1, cv::Scalar::all(255),-1,8,0);
        }else if(spline_dot.size() == 2){
            line.push_back(spline_dot[0]);
            line.push_back(spline_dot[1]);
            cv::line(map_drawing,spline_dot[0],spline_dot[1],cv::Scalar(cur_line_color,cur_line_color,cur_line_color),cur_line_width,8,0);
            cv::line(map_drawing_mask,spline_dot[0],spline_dot[1],cv::Scalar::all(255),cur_line_width,8,0);
        }
    }
    setMap();
}

void MapHandler::setMapDrawing(){
    initDrawing();
    for(int line=0; line<lines.size(); line++){
        if(lines[line].type == 0){
            if(mode == "annot_velmap"){
                if(lines[line].color == 100){
                    for(int i=0; i<lines[line].points.size()-1; i++){
                        cv::line(map_drawing,cv::Point2f(lines[line].points[i].x,lines[line].points[i].y),cv::Point2f(lines[line].points[i+1].x,lines[line].points[i+1].y),color_yellow,lines[line].width,8,0);
                        cv::line(map_drawing_mask,cv::Point2f(lines[line].points[i].x,lines[line].points[i].y),cv::Point2f(lines[line].points[i+1].x,lines[line].points[i+1].y),cv::Scalar::all(255),lines[line].width,8,0);
                    }
                }else if(lines[line].color == 200){
                    for(int i=0; i<lines[line].points.size()-1; i++){
                        cv::line(map_drawing,cv::Point2f(lines[line].points[i].x,lines[line].points[i].y),cv::Point2f(lines[line].points[i+1].x,lines[line].points[i+1].y),color_red,lines[line].width,8,0);
                        cv::line(map_drawing_mask,cv::Point2f(lines[line].points[i].x,lines[line].points[i].y),cv::Point2f(lines[line].points[i+1].x,lines[line].points[i+1].y),cv::Scalar::all(255),lines[line].width,8,0);
                    }
                }else{
                    for(int i=0; i<lines[line].points.size()-1; i++){
                        cv::line(map_drawing,cv::Point2f(lines[line].points[i].x,lines[line].points[i].y),cv::Point2f(lines[line].points[i+1].x,lines[line].points[i+1].y),cv::Scalar(lines[line].color,lines[line].color,lines[line].color,255),lines[line].width,8,0);
                        cv::line(map_drawing_mask,cv::Point2f(lines[line].points[i].x,lines[line].points[i].y),cv::Point2f(lines[line].points[i+1].x,lines[line].points[i+1].y),cv::Scalar::all(255),lines[line].width,8,0);
                    }
                }
            }else if(mode == "annot_object_png"){
                if(lines[line].color == 255){
                    for(int i=0; i<lines[line].points.size()-1; i++){
                        cv::line(map_drawing,cv::Point2f(lines[line].points[i].x,lines[line].points[i].y),cv::Point2f(lines[line].points[i+1].x,lines[line].points[i+1].y),color_blue,lines[line].width,8,0);
                        cv::line(map_drawing_mask,cv::Point2f(lines[line].points[i].x,lines[line].points[i].y),cv::Point2f(lines[line].points[i+1].x,lines[line].points[i+1].y),cv::Scalar::all(255),lines[line].width,8,0);
                    }
                }else{
                    for(int i=0; i<lines[line].points.size()-1; i++){
                        cv::line(map_drawing,cv::Point2f(lines[line].points[i].x,lines[line].points[i].y),cv::Point2f(lines[line].points[i+1].x,lines[line].points[i+1].y),cv::Scalar(lines[line].color,lines[line].color,lines[line].color,255),lines[line].width,8,0);
                        cv::line(map_drawing_mask,cv::Point2f(lines[line].points[i].x,lines[line].points[i].y),cv::Point2f(lines[line].points[i+1].x,lines[line].points[i+1].y),cv::Scalar::all(255),lines[line].width,8,0);
                    }
                }
            }else if(mode == "annot_obs_area"){
                if(lines[line].color == 255){
                    for(int i=0; i<lines[line].points.size()-1; i++){
                        cv::line(map_drawing,cv::Point2f(lines[line].points[i].x,lines[line].points[i].y),cv::Point2f(lines[line].points[i+1].x,lines[line].points[i+1].y),color_green,lines[line].width,8,0);
                        cv::line(map_drawing_mask,cv::Point2f(lines[line].points[i].x,lines[line].points[i].y),cv::Point2f(lines[line].points[i+1].x,lines[line].points[i+1].y),cv::Scalar::all(255),lines[line].width,8,0);
                    }
                }else{
                    for(int i=0; i<lines[line].points.size()-1; i++){
                        cv::line(map_drawing,cv::Point2f(lines[line].points[i].x,lines[line].points[i].y),cv::Point2f(lines[line].points[i+1].x,lines[line].points[i+1].y),cv::Scalar(lines[line].color,lines[line].color,lines[line].color,255),lines[line].width,8,0);
                        cv::line(map_drawing_mask,cv::Point2f(lines[line].points[i].x,lines[line].points[i].y),cv::Point2f(lines[line].points[i+1].x,lines[line].points[i+1].y),cv::Scalar::all(255),lines[line].width,8,0);
                    }
                }
            }else if(mode == "annot_tline" || mode == "annot_tline2"){
                if(lines[line].color == 255){
                    for(int i=0; i<lines[line].points.size()-1; i++){
                        cv::line(map_drawing,cv::Point2f(lines[line].points[i].x,lines[line].points[i].y),cv::Point2f(lines[line].points[i+1].x,lines[line].points[i+1].y),color_navy,lines[line].width,8,0);
                        cv::line(map_drawing_mask,cv::Point2f(lines[line].points[i].x,lines[line].points[i].y),cv::Point2f(lines[line].points[i+1].x,lines[line].points[i+1].y),cv::Scalar::all(255),lines[line].width,8,0);
                    }
                }else{
                    for(int i=0; i<lines[line].points.size()-1; i++){
                        cv::line(map_drawing,cv::Point2f(lines[line].points[i].x,lines[line].points[i].y),cv::Point2f(lines[line].points[i+1].x,lines[line].points[i+1].y),cv::Scalar(lines[line].color,lines[line].color,lines[line].color,255),lines[line].width,8,0);
                        cv::line(map_drawing_mask,cv::Point2f(lines[line].points[i].x,lines[line].points[i].y),cv::Point2f(lines[line].points[i+1].x,lines[line].points[i+1].y),cv::Scalar::all(255),lines[line].width,8,0);
                    }
                }
            }else{
                for(int i=0; i<lines[line].points.size()-1; i++){
                    cv::line(map_drawing,cv::Point2f(lines[line].points[i].x,lines[line].points[i].y),cv::Point2f(lines[line].points[i+1].x,lines[line].points[i+1].y),cv::Scalar(lines[line].color,lines[line].color,lines[line].color,255),lines[line].width,8,0);
                    cv::line(map_drawing_mask,cv::Point2f(lines[line].points[i].x,lines[line].points[i].y),cv::Point2f(lines[line].points[i+1].x,lines[line].points[i+1].y),cv::Scalar::all(255),lines[line].width,8,0);
                }
            }
        }else if(lines[line].type == 1){
            if(lines[line].color == 100){
                cv::rectangle(map_drawing,lines[line].points[0],lines[line].points[2],color_yellow,-1,8,0);
                cv::rectangle(map_drawing_mask,lines[line].points[0],lines[line].points[2],cv::Scalar::all(255),-1,8,0);
            }else if(lines[line].color == 200){
                cv::rectangle(map_drawing,lines[line].points[0],lines[line].points[2],color_red,-1,8,0);
                cv::rectangle(map_drawing_mask,lines[line].points[0],lines[line].points[2],cv::Scalar::all(255),-1,8,0);
            }else if(lines[line].color == -1){
                cv::rectangle(map_drawing,lines[line].points[0],lines[line].points[2],cv::Scalar(-1,-1,-1,255),-1,8,0);
                cv::rectangle(map_drawing_mask,lines[line].points[0],lines[line].points[2],cv::Scalar::all(255),-1,8,0);
            }else if(mode == "annot_object_png"){
                cv::rectangle(map_drawing,lines[line].points[0],lines[line].points[2],color_blue,-1,8,0);
                cv::rectangle(map_drawing_mask,lines[line].points[0],lines[line].points[2],cv::Scalar::all(255),-1,8,0);
            }else if(mode == "annot_obs_area"){
                cv::rectangle(map_drawing,lines[line].points[0],lines[line].points[2],color_green,-1,8,0);
                cv::rectangle(map_drawing_mask,lines[line].points[0],lines[line].points[2],cv::Scalar::all(255),-1,8,0);
            }
        }
    }
    if(new_straight_flag){
        if(mode == "annot_velmap"){
            if(cur_line_color == 100){
                if(straight_point.size() == 1){
                    cv::circle(map_drawing,straight_point[0],cur_line_width,color_yellow);
                    cv::circle(map_drawing_mask,straight_point[0],cur_line_width,cv::Scalar::all(255));
                }else if(straight_point.size() == 2){
                    cv::line(map_drawing,straight_point[0],straight_point[1],color_yellow,cur_line_width,8,0);
                    cv::line(map_drawing_mask,straight_point[0],straight_point[1],cv::Scalar::all(255),cur_line_width,8,0);
                }
            }else if(cur_line_color == 200){
                if(straight_point.size() == 1){
                    cv::circle(map_drawing,straight_point[0],cur_line_width,color_red);
                    cv::circle(map_drawing_mask,straight_point[0],cur_line_width,cv::Scalar::all(255));
                }else if(straight_point.size() == 2){
                    cv::line(map_drawing,straight_point[0],straight_point[1],color_red,cur_line_width,8,0);
                    cv::line(map_drawing_mask,straight_point[0],straight_point[1],cv::Scalar::all(255),cur_line_width,8,0);
                }
            }
        }else if(mode == "annot_object_png"){
            if(straight_point.size() == 1){
                cv::circle(map_drawing,straight_point[0],cur_line_width,color_blue);
                cv::circle(map_drawing_mask,straight_point[0],cur_line_width,cv::Scalar::all(255));
            }else if(straight_point.size() == 2){
                cv::line(map_drawing,straight_point[0],straight_point[1],color_blue,cur_line_width,8,0);
                cv::line(map_drawing_mask,straight_point[0],straight_point[1],cv::Scalar::all(255),cur_line_width,8,0);
            }
        }else if(mode == "annot_tline" || mode == "annot_tline2"){
            if(straight_point.size() == 1){
                cv::circle(map_drawing,straight_point[0],cur_line_width,color_navy);
                cv::circle(map_drawing_mask,straight_point[0],cur_line_width,cv::Scalar::all(255));
            }else if(straight_point.size() == 2){
                cv::line(map_drawing,straight_point[0],straight_point[1],color_navy,cur_line_width,8,0);
                cv::line(map_drawing_mask,straight_point[0],straight_point[1],cv::Scalar::all(255),cur_line_width,8,0);
            }
        }else{
            if(straight_point.size() == 1){
                cv::circle(map_drawing,straight_point[0],cur_line_width,cv::Scalar(cur_line_color,cur_line_color,cur_line_color,255));
                cv::circle(map_drawing_mask,straight_point[0],cur_line_width,cv::Scalar::all(255));
            }else if(straight_point.size() == 2){
                cv::line(map_drawing,straight_point[0],straight_point[1],cv::Scalar(cur_line_color,cur_line_color,cur_line_color,255),cur_line_width,8,0);
                cv::line(map_drawing_mask,straight_point[0],straight_point[1],cv::Scalar::all(255),cur_line_width,8,0);
            }
        }
    }
    if(temp_rect.size() > 3){
        if(cur_line_color == 100){
            cv::rectangle(map_drawing,temp_rect[0],temp_rect[2],color_yellow,-1,8,0);
            cv::rectangle(map_drawing_mask,temp_rect[0],temp_rect[2],cv::Scalar::all(255),-1,8,0);
        }else if(cur_line_color == 200){
            cv::rectangle(map_drawing,temp_rect[0],temp_rect[2],color_red,-1,8,0);
            cv::rectangle(map_drawing_mask,temp_rect[0],temp_rect[2],cv::Scalar::all(255),-1,8,0);
        }else if(cur_line_color == -1){
            cv::rectangle(map_drawing,temp_rect[0],temp_rect[2],cv::Scalar(-1,-1,-1,255),-1,8,0);
            cv::rectangle(map_drawing_mask,temp_rect[0],temp_rect[2],cv::Scalar::all(255),-1,8,0);
        }else if(mode == "annot_object_png"){
            cv::rectangle(map_drawing,temp_rect[0],temp_rect[2],color_blue,-1,8,0);
            cv::rectangle(map_drawing_mask,temp_rect[0],temp_rect[2],cv::Scalar::all(255),-1,8,0);
        }else if(mode == "annot_obs_area"){
            cv::rectangle(map_drawing,temp_rect[0],temp_rect[2],color_green,-1,8,0);
            cv::rectangle(map_drawing_mask,temp_rect[0],temp_rect[2],cv::Scalar::all(255),-1,8,0);
        }
    }
}
void MapHandler::addSpline(int x, int y){
    curPoint.x = x;
    curPoint.y = y;
    spline_dot.push_back(curPoint);
    dot_trash.clear();
    drawSpline();
}

void MapHandler::tempNodeInit(int x, int y){
    tempnode.isnew = true;
    tempnode.point.x = x;
    tempnode.point.y = y;
    tempnode.angle = 0;
    init_tempnode = tempnode.point;

    QString id = getNode(x,y);
    if(id != ""){
        click_info.sel_node = id;
        click_info.pre_node = click_info.cur_node;
        click_info.cur_node = id;
        qDebug() << "select node is " << id;
    }else{
        click_info.pre_node = id;
        click_info.cur_node = id;
    }
    setMapLayer();
}
QString MapHandler::getNode(int x, int y){
    QString min_id = "";
    double min_d = 99999999;
    for(auto& it: nodes)
    {
        if(it.second == nullptr)
        {
            continue;
        }

        double d = cv::norm(cv::Vec2d(nodes[it.second->id]->pose[0], nodes[it.second->id]->pose[1]) - cv::Vec2d(x,y));
        if(d < min_d && d < (pmap->robot_radius/grid_width)*float(map_layer.width())/(2*draw_width))
        {
            min_d = d;
            min_id = it.second->id;
        }
    }
    return min_id;
}
void MapHandler::tempNodeSet(int x, int y){
    float angle = atan2((y-init_tempnode.y),(x-init_tempnode.x));
    tempnode.angle = angle;
    setMapLayer();
}

void MapHandler::addNode(QString name, QString group, QString attrib){
    int max_loc_id = -1;
    for(auto& it: nodes)
    {
        if(it.second == nullptr)
        {
            continue;
        }

        if(it.second->attrib == attrib)
        {
            QString id = it.second->id;
            QStringList id_split = id.split(":");

            int loc_id = id_split.back().remove(attrib).toInt();
            if(loc_id >= max_loc_id)
            {
                max_loc_id = loc_id;
            }
        }
    }

    int new_loc_id = max_loc_id+1;
    QString id;
    if(attrib == "Charging"){
        id = "0:Charging:0:Charging0";
    }else if(attrib == "Resting"){
        id = "0:Resting:0:Resting0";
    }else if(attrib == "Cleaning"){
        id = "0:Cleaning:0:Cleaning0";
    }else{
        if(name == ""){
            name = "Serving"+QString::number(new_loc_id);
        }
        if(group == ""){
            group = "Default";
        }
        id = QString::asprintf("0:%s:%d:%s", group.toLocal8Bit().data(), new_loc_id, name.toLocal8Bit().data());
    }
    addNode(id, attrib);
}

bool MapHandler::isExistNode(QString type){
    if(type == "Serving"){
    }else{
        for(auto& it: nodes)
        {
            if(it.second == nullptr)
            {
                continue;
            }

            if(it.second->attrib == type)
            {
                return true;
            }
        }
    }
    return false;
}
void MapHandler::addNode(QString id, QString attrib){
    if(attrib == "Route"){
        id = auto_node_name(attrib);
    }

    NODE *node = new NODE();
    node->id = id;
    node->attrib = attrib;
    node->pose[0] = tempnode.point.x;
    node->pose[1] = tempnode.point.y;
    node->pose[2] = tempnode.angle;
    nodes[node->id] = node;
    plog->write("[TOPOMAP] add node, id: " + id + QString::asprintf("(%f, %f, %f)",node->pose[0],node->pose[1],node->pose[2]));

    setMapLayer();
}

void MapHandler::editNode(QString attr){
    QString id = "";
    if(attr != "Serving"){
        for(auto& it: nodes)
        {
            if(it.second == nullptr)
            {
                continue;
            }
            if(it.second->attrib == attr)
            {
                id = it.second->id;
            }
        }
        if(id != ""){
            cv::Vec3d pose = click_info.pose;
            nodes[id]->pose[0] = tempnode.point.x;
            nodes[id]->pose[1] = tempnode.point.y;
            nodes[id]->pose[2] = tempnode.angle;
            qDebug() <<"[TOPOMAP] edit node, id:" << id;
            setMapLayer();
        }
    }
}
void MapHandler::editNode(){
    QString id = click_info.sel_node;
    if(id != ""){
        cv::Vec3d pose = click_info.pose;
        nodes[id]->pose[0] = tempnode.point.x;
        nodes[id]->pose[1] = tempnode.point.y;
        nodes[id]->pose[2] = tempnode.angle;
        qDebug() <<"[TOPOMAP] edit node, id:" << id;
        setMapLayer();
    }
}
void MapHandler::editNode(QString id, int x, int y, float th){
    if(id != ""){
        nodes[id]->pose[0] = x;
        nodes[id]->pose[1] = y;
        nodes[id]->pose[2] = th;
        qDebug() <<"[TOPOMAP] edit node, id:" << id;
        setMapLayer();
    }
}
void MapHandler::deleteNode(){
    QString id = click_info.sel_node;
    if(id != ""){
        if(nodes.find(id) != nodes.end())
        {
            // erase links
            for(auto& it: nodes)
            {
                if(it.second == nullptr)
                {
                    continue;
                }

                auto found_it = std::find(it.second->linked.begin(), it.second->linked.end(), id);
                if(found_it != it.second->linked.end())
                {
                    it.second->linked.erase(found_it);
                }
            }

            // erase node
            nodes.erase(id);
            qDebug() <<"[TOPOMAP] del node, id:" << id;
            setMapLayer();
        }
    }
}

void MapHandler::alignXNode(){
    QString id0 = click_info.pre_node;
    QString id1 = click_info.cur_node;
    if(id0 != "" && id1 != "")
    {
        cv::Vec3d pose0 = nodes[id0]->pose;
        cv::Vec3d pose1 = nodes[id1]->pose;
        // align x
        pose1[0] = pose0[0];
        editNode(id1, pose1[0],pose1[1],pose1[2]);
    }
}
void MapHandler::alignYNode(){
    QString id0 = click_info.pre_node;
    QString id1 = click_info.cur_node;
    if(id0 != "" && id1 != "")
    {
        cv::Vec3d pose0 = nodes[id0]->pose;
        cv::Vec3d pose1 = nodes[id1]->pose;
        // align y
        pose1[1] = pose0[1];
        editNode(id1, pose1[0],pose1[1],pose1[2]);
    }
}
void MapHandler::alignTHNode(){
    QString id0 = click_info.pre_node;
    QString id1 = click_info.cur_node;
    if(id0 != "" && id1 != "")
    {
        cv::Vec3d pose0 = nodes[id0]->pose;
        cv::Vec3d pose1 = nodes[id1]->pose;
        // align th
        pose1[2] = pose0[2];
        editNode(id1, pose1[0],pose1[1],pose1[2]);
    }
}
void MapHandler::linkNode(){
    QString id0 = click_info.pre_node;
    QString id1 = click_info.cur_node;
    if(id0 != "" && id1 != "" && id0 != id1)
    {
        auto it = std::find(nodes[id0]->linked.begin(), nodes[id0]->linked.end(), id1);
        if(it == nodes[id0]->linked.end())
        {
            nodes[id0]->linked.push_back(id1);
            qDebug() <<"[TOPOMAP] add link";
        }
        else
        {
            // forward erase
            {
                auto it = std::find(nodes[id0]->linked.begin(), nodes[id0]->linked.end(), id1);
                if(it != nodes[id0]->linked.end())
                {
                    nodes[id0]->linked.erase(it);
                    qDebug() << "[TOPOMAP] del link";
                }
            }

            // reverse erase
            {
                auto it = std::find(nodes[id1]->linked.begin(), nodes[id1]->linked.end(), id0);
                if(it != nodes[id1]->linked.end())
                {
                    nodes[id1]->linked.erase(it);
                    qDebug() << "[TOPOMAP] del link";
                }
            }
        }
        setMapLayer();
    }
}

void MapHandler::saveAnnotation(){
    // clear annotations
    QList<LOCATION> temp_location;
//    pmap->locations.clear();

    // topo nodes to annotations
    for(auto& it: nodes)
    {
        if(it.second == nullptr)
        {
            continue;
        }

        if(it.second->attrib == "Route")
        {
            continue;
        }
        else
        {
            QString name = it.second->id;
            QStringList name_split = name.split(":");

            int group_id = name_split[0].toInt();
            QString group_name = name_split[1];

//            int loc_id = name_split[2].toInt();
            QString loc_name = name_split[3];

            QString attrib = it.second->attrib;
            cv::Vec3d pose = it.second->pose;

            LOCATION anot;
            for(int i=0; i<pmap->locations.size(); i++){
                if(pmap->locations[i].group == group_id && pmap->locations[i].name == loc_name){
                    anot = pmap->locations[i];
                    break;
                }
            }
            anot.group = group_id;
            anot.group_name = group_name;
            anot.name = loc_name;
            anot.type = attrib;

            anot.point = setAxisBack(cv::Point2f(pose[0],pose[1]));
            anot.angle = setAxisBack(pose[2]);
            temp_location.push_back(anot);
        }
    }

    pmap->locations.clear();
    pmap->locations = temp_location;
    // save annotations to ini file
//    QString annotated_loc_path = map_dir + "/annotation.ini";
//    QFile::remove(annotated_loc_path);

//    QSettings settings(annotated_loc_path, QSettings::IniFormat);
//    settings.clear();

    // parsing group num
//    int group_num = 1;
//    for(size_t p = 0; p < annotations.size(); p++)
//    {
//        if(annotations[p].attrib == "Serving")
//        {
//            int group = annotations[p].group_id+1;
//            if(group > group_num)
//            {
//                group_num = group;
//            }
//        }
//    }
//    settings.setValue("serving_locations/group", group_num);

//    if(group_num == 1)
//    {
//        settings.setValue("serving_0/name", "Default");
//    }

//    // each locations num
//    std::vector<int> serving_num(group_num, 0);
//    int charging_num = 0;
//    int cleaning_num = 0;
//    int resting_num = 0;

//    for(size_t p = 0; p < annotations.size(); p++)
//    {
//        if(annotations[p].attrib == "Serving")
//        {
//            // set group name
//            {
//                QString sec;
//                sec.sprintf("serving_%d/name", annotations[p].group_id);
//                settings.setValue(sec, annotations[p].group_name);
//            }

//            // set loc
//            {
//                QString sec;
//                sec.sprintf("serving_%d/loc%d", annotations[p].group_id, annotations[p].loc_id);

//                QString value;
//                value.sprintf("%s,%f,%f,%f,%s", annotations[p].loc_name.toLocal8Bit().data(),
//                                                annotations[p].pose[0],
//                                                annotations[p].pose[1],
//                                                annotations[p].pose[2],
//                                                annotations[p].tmp.toLocal8Bit().data());
//                settings.setValue(sec, value);
//            }

//            // count up
//            serving_num[annotations[p].group_id]++;
//        }
//        else if(annotations[p].attrib == "Charging")
//        {
//            // set loc
//            {
//                QString sec;
//                sec.sprintf("charging_locations/loc%d", annotations[p].loc_id);

//                QString value;
//                value.sprintf("%s,%f,%f,%f,%s", annotations[p].loc_name.toLocal8Bit().data(),
//                                                annotations[p].pose[0],
//                                                annotations[p].pose[1],
//                                                annotations[p].pose[2],
//                                                annotations[p].tmp.toLocal8Bit().data());
//                settings.setValue(sec, value);
//            }

//            // count up
//            charging_num++;
//        }
//        else if(annotations[p].attrib == "Cleaning")
//        {
//            // set loc
//            {
//                QString sec;
//                sec.sprintf("cleaning_locations/loc%d", annotations[p].loc_id);

//                QString value;
//                value.sprintf("%s,%f,%f,%f,%s", annotations[p].loc_name.toLocal8Bit().data(),
//                                                annotations[p].pose[0],
//                                                annotations[p].pose[1],
//                                                annotations[p].pose[2],
//                                                annotations[p].tmp.toLocal8Bit().data());
//                settings.setValue(sec, value);
//            }

//            // count up
//            cleaning_num++;
//        }
//        else if(annotations[p].attrib == "Resting")
//        {
//            // set loc
//            {
//                QString sec;
//                sec.sprintf("resting_locations/loc%d", annotations[p].loc_id);

//                QString value;
//                value.sprintf("%s,%f,%f,%f,%s", annotations[p].loc_name.toLocal8Bit().data(),
//                                                annotations[p].pose[0],
//                                                annotations[p].pose[1],
//                                                annotations[p].pose[2],
//                                                annotations[p].tmp.toLocal8Bit().data());
//                settings.setValue(sec, value);
//            }

//            // count up
//            resting_num++;
//        }
//    }

//    for(size_t p = 0; p < serving_num.size(); p++)
//    {
//        QString sec;
//        sec.sprintf("serving_%d/num", (int)p);
//        settings.setValue(sec, serving_num[p]);
//    }

//    settings.setValue("charging_locations/num", charging_num);
//    settings.setValue("cleaning_locations/num", cleaning_num);
//    settings.setValue("resting_locations/num", resting_num);

//    settings.setValue("objects/num", 0);
//    settings.setValue("other_locations/num", 0);
}
void MapHandler::loadAnnotation(){
    if(pmap->locations.size() == 0)
    {
        qDebug() << "[TOPOMAP] no annotations";
        return;
    }

    // clear topo nodes
    nodes.clear();

    // set annotations to nodes
    for(size_t p = 0; p < pmap->locations.size(); p++)
    {
        QString name = QString::asprintf("%d:%s:%d:%s", pmap->locations[p].group,
                                    pmap->locations[p].group_name.toLocal8Bit().data(),
                                    p,
                                    pmap->locations[p].name.toLocal8Bit().data());
        NODE *node = new NODE();
        node->attrib = pmap->locations[p].type;
        node->id = name;
        cv::Point2f pos = setAxis(pmap->locations[p].point);
        float ang = setAxis(pmap->locations[p].angle);
        node->pose[0] = pos.x;
        node->pose[1] = pos.y;
        node->pose[2] = ang;
        nodes[name] = node;
        qDebug() <<"[TOPOMAP] load annotation, " << name.toLocal8Bit().data() << node->attrib << node->pose[0] << node->pose[1];
    }
    setMapLayer();
}
QString MapHandler::auto_node_name(QString attrib)
{
    QString res = "";

    int max_loc_id = -1;
    for(auto& it: nodes)
    {
        if(it.second == nullptr)
        {
            continue;
        }

        if(it.second->attrib == attrib)
        {
            QString id = it.second->id;
            QStringList id_split = id.split(":");

            int loc_id = id_split.back().remove(attrib).toInt();
            if(loc_id >= max_loc_id)
            {
                max_loc_id = loc_id;
            }
        }
    }

    int new_loc_id = max_loc_id+1;

    if(attrib == "Serving")
    {
        QString name = QString::asprintf("0:%s:%d:Serving%d", first_group_name.toLocal8Bit().data(), new_loc_id, new_loc_id);
        res = name;
    }
    else
    {
        QString name = QString::asprintf("0::%d:%s%d", new_loc_id, attrib.toLocal8Bit().data(), new_loc_id);
        res = name;
    }

    return res;
}
void MapHandler::setDrawingLine(int x, int y){
//    qDebug() << "setDrawingLine " << x << y;
//    straight[1].x = x;
//    straight[1].y = y;
//    initDrawing();
//    setMapDrawing();
//    setMap();
}
void MapHandler::stopDrawingLine(int x, int y){
//    //qDebug() << "stopDrawingLine";
//    line.clear();
//    lines_trash.clear();
//    new_straight_flag = false;
//    curPoint.x = straight[0].x;
//    curPoint.y = straight[0].y;
//    line.push_back(curPoint);
//    curPoint.x = straight[1].x;
//    curPoint.y = straight[1].y;
//    line.push_back(curPoint);
//    LINE temp_line;
//    temp_line.color = cur_line_color;
//    temp_line.width = cur_line_width;
//    temp_line.points = line;
//    lines.push_back(temp_line);
//    setMapDrawing();
//    setMap();
}
void MapHandler::startDrawing(int x, int y){
    line.clear();
    spline_dot.clear();
    lines_trash.clear();
    curPoint.x = x;
    curPoint.y = y;
    line.push_back(curPoint);
}
void MapHandler::startErase2(int x, int y){
    line.clear();
    spline_dot.clear();
    lines_trash.clear();
    curPoint.x = x;
    curPoint.y = y;
    line.push_back(curPoint);
}

void MapHandler::drawTline(){
    cv::Point2f pose = setAxis(probot->curPose.point);
    if(prev_pose.x == 0 && prev_pose.y == 0){
        //pass
    }else{
        cv::line(map_drawing_tline,prev_pose,pose,cur_line_color,1,8,0);
    }
    prev_pose = pose;
    setMap();
}

void MapHandler::addLinePoint(int x, int y){
    curPoint.x = x;
    curPoint.y = y;
    line.push_back(curPoint);
    if(mode == "annot_velmap"){
        if(cur_line_color == 100){
            cv::line(map_drawing,line[line.size()-2],line[line.size()-1],color_yellow,cur_line_width,8,0);
            cv::line(map_drawing_mask,line[line.size()-2],line[line.size()-1],cv::Scalar::all(255),cur_line_width,8,0);
        }else if(cur_line_color == 200){
            cv::line(map_drawing,line[line.size()-2],line[line.size()-1],color_red,cur_line_width,8,0);
            cv::line(map_drawing_mask,line[line.size()-2],line[line.size()-1],cv::Scalar::all(255),cur_line_width,8,0);
        }else{
            cv::line(map_drawing,line[line.size()-2],line[line.size()-1],cv::Scalar(cur_line_color,cur_line_color,cur_line_color,255),cur_line_width,8,0);
            cv::line(map_drawing_mask,line[line.size()-2],line[line.size()-1],cv::Scalar::all(255),cur_line_width,8,0);
        }
    }else if(mode == "annot_object_png"){
        if(cur_line_color == -1){
            cv::line(map_drawing,line[line.size()-2],line[line.size()-1],cv::Scalar(-1,-1,-1,255),cur_line_width,8,0);
            cv::line(map_drawing_mask,line[line.size()-2],line[line.size()-1],cv::Scalar::all(255),cur_line_width,8,0);
        }else{
            cv::line(map_drawing,line[line.size()-2],line[line.size()-1],color_blue,cur_line_width,8,0);
            cv::line(map_drawing_mask,line[line.size()-2],line[line.size()-1],cv::Scalar::all(255),cur_line_width,8,0);
        }
    }else if(mode == "annot_obs_area"){
        if(cur_line_color == -1){
            cv::line(map_drawing,line[line.size()-2],line[line.size()-1],cv::Scalar(-1,-1,-1,255),cur_line_width,8,0);
            cv::line(map_drawing_mask,line[line.size()-2],line[line.size()-1],cv::Scalar::all(255),cur_line_width,8,0);
        }else{
            cv::line(map_drawing,line[line.size()-2],line[line.size()-1],color_green,cur_line_width,8,0);
            cv::line(map_drawing_mask,line[line.size()-2],line[line.size()-1],cv::Scalar::all(255),cur_line_width,8,0);
        }
    }else if(mode == "annot_tline" || mode == "annot_tline2"){
        if(cur_line_color == -1){
            cv::line(map_drawing,line[line.size()-2],line[line.size()-1],cv::Scalar(-1,-1,-1,255),cur_line_width,8,0);
            cv::line(map_drawing_mask,line[line.size()-2],line[line.size()-1],cv::Scalar::all(255),cur_line_width,8,0);
        }else{
            cv::line(map_drawing,line[line.size()-2],line[line.size()-1],color_navy,cur_line_width,8,0);
            cv::line(map_drawing_mask,line[line.size()-2],line[line.size()-1],cv::Scalar::all(255),cur_line_width,8,0);
        }
    }else{
        cv::line(map_drawing,line[line.size()-2],line[line.size()-1],cv::Scalar(cur_line_color,cur_line_color,cur_line_color,255),cur_line_width,8,0);
        cv::line(map_drawing_mask,line[line.size()-2],line[line.size()-1],cv::Scalar::all(255),cur_line_width,8,0);
    }
//    qDebug() << "addlinepoint " << mode;
    setMap();
}
void MapHandler::addErase2(int x, int y){
    curPoint.x = x;
    curPoint.y = y;
    line.push_back(curPoint);
    if(mode == "annot_tline" || mode == "annot_tline2"){
        cv::line(file_travelline,line[line.size()-2],line[line.size()-1],cv::Scalar(-1,-1,-1,255),cur_line_width,8,0);
    }
    qDebug() << "addErase2 " << mode;
    setMap();
}

void MapHandler::endDrawing(int x, int y){
    //qDebug() << "endDrawing";
    curPoint.x = x;
    curPoint.y = y;
    line.push_back(curPoint);


    LINE temp_line;
    temp_line.color = cur_line_color;
    temp_line.width = cur_line_width;

    //SPLINE
    if(tool != "erase" && (mode == "annot_tline" || mode == "annot_tline2")){
        std::vector<double> x_list;
        std::vector<double> y_list;
        std::vector<double> d_list;

        double sum_d = 0;
        d_list.push_back(sum_d);
        x_list.push_back(line[0].x);
        y_list.push_back(line[0].y);
        for(size_t p = 1; p<line.size(); p++){
            double x0 = line[p-1].x;
            double y0 = line[p-1].y;
            double x1 = line[p].x;
            double y1 = line[p].y;

            double dx = x1-x0;
            double dy = y1-y0;

            if(std::sqrt(dx*dx + dy*dy) > 0){
                sum_d += std::sqrt(dx*dx + dy*dy);
                d_list.push_back(sum_d);
                x_list.push_back(line[p].x);
                y_list.push_back(line[p].y);
            }
        }

        tk::spline::spline_type type = tk::spline::cspline_hermite;
        tk::spline sx, sy;
        if(d_list.size() > 2 && x_list.size() > 2 && y_list.size() > 2){
            sx.set_points(d_list, x_list, type);
            sx.make_monotonic();
            sy.set_points(d_list, y_list, type);
            sy.make_monotonic();

            for(double d = 0; d<=sum_d; d+= grid_width){
                temp_line.points.push_back(cv::Point2f(sx(d),sy(d)));
            }
        }else{
            temp_line.points = line;
        }
    }else{
        temp_line.points = line;
    }

    lines.push_back(temp_line);
    line.clear();
    initDrawing();
    setMapDrawing();
    setMap();
}
void MapHandler::endErase2(int x, int y){
    line.clear();
//    initDrawing();
//    setMapDrawing();
//    saveTline();

    cv::rotate(file_travelline,file_travelline,cv::ROTATE_90_CLOCKWISE);
    cv::flip(file_travelline,file_travelline,0);
    QString path = QDir::homePath() + "/RB_MOBILE/maps/" + pmap->map_name + "/map_travel_line_test.png";
    plog->write("[MAP] saveTline : "+path);
    cv::imwrite(path.toStdString(),file_travelline);
    cv::flip(file_travelline,file_travelline,0);
    cv::rotate(file_travelline,file_travelline,cv::ROTATE_90_COUNTERCLOCKWISE);
    setMap();
}

void MapHandler::clearDrawing(){
    line.clear();
    lines.clear();
    spline_dot.clear();
    initDrawing();
    setMapDrawing();
    setMap();
}

void MapHandler::undoLine(){
    line.clear();
    if(straight_point.size() > 0){
        straight_point.clear();
        setMapDrawing();
        setMap();
    }else if(spline_dot.size() > 0){
        dot_trash.push_back(spline_dot[spline_dot.size()-1]);
        spline_dot.pop_back();
        drawSpline();
    }else if(lines.size() > 0 || line.size() > 0){
        lines_trash.push_back(lines[lines.size()-1]);
        lines.pop_back();
        setMapDrawing();
        setMap();
    }
}

void MapHandler::saveMap(){
    cv::Mat temp_orin;
    cv::Mat temp_draw;
    cv::Mat temp_mask;
    cv::Mat rotated;

    map_orin.copyTo(temp_orin);
    cv::cvtColor(map_drawing,temp_draw,cv::COLOR_BGRA2GRAY);
    cv::cvtColor(map_drawing_mask,temp_mask,cv::COLOR_BGRA2GRAY);

    cv::multiply(cv::Scalar::all(1.0)-temp_mask,temp_orin,temp_orin);
    cv::add(temp_orin,temp_draw,temp_orin);

    cv::Mat rot = cv::getRotationMatrix2D(cv::Point2f(temp_orin.cols/2, temp_orin.rows/2),-rotate_angle,1.0);
    rotate_angle = 0;
    cv::warpAffine(temp_orin,rotated,rot,temp_orin.size(),cv::INTER_NEAREST);

    cv::rotate(rotated,rotated,cv::ROTATE_90_CLOCKWISE);
    cv::flip(rotated,rotated,0);

    QString path = QDir::homePath() + "/RB_MOBILE/maps/" + pmap->map_name + "/map_edited.png";
    plog->write("[MapHandler] SAVE MAP "+path);
    cv::imwrite(path.toStdString(),rotated);
}

void MapHandler::saveVelmap(){
    initDrawing();
    QString file_path = QDir::homePath() + "/RB_MOBILE/maps/"+map_name + "/map_velocity.png";
    if(QFile::exists(file_path)){
        file_velocity = cv::imread(file_path.toStdString(), cv::IMREAD_COLOR);
        cv::flip(file_velocity,file_velocity,0);
        cv::rotate(file_velocity,file_velocity,cv::ROTATE_90_COUNTERCLOCKWISE);
    }else{
        file_velocity = cv::Mat(file_width,file_width,CV_8UC3, cv::Scalar::all(0));
    }
    for(int line=0; line<lines.size(); line++){
        if(lines[line].type == 0){
            for(int i=0; i<lines[line].points.size()-1; i++){
                cv::line(map_drawing,cv::Point2f(lines[line].points[i].x,lines[line].points[i].y),cv::Point2f(lines[line].points[i+1].x,lines[line].points[i+1].y),cv::Scalar(lines[line].color,lines[line].color,lines[line].color,255),lines[line].width,8,0);
                cv::line(map_drawing_mask,cv::Point2f(lines[line].points[i].x,lines[line].points[i].y),cv::Point2f(lines[line].points[i+1].x,lines[line].points[i+1].y),cv::Scalar::all(255),lines[line].width,8,0);
            }
        }else if(lines[line].type == 1){
            cv::rectangle(map_drawing,lines[line].points[0],lines[line].points[2],cv::Scalar(lines[line].color,lines[line].color,lines[line].color,255),-1,8,0);
            cv::rectangle(map_drawing_mask,lines[line].points[0],lines[line].points[2],cv::Scalar::all(255),-1,8,0);
        }
    }

    cv::Mat temp_velocity;
    cv::Mat temp_draw;
    cv::Mat temp_mask;

    cv::cvtColor(map_drawing,temp_draw,cv::COLOR_BGRA2GRAY);
    cv::cvtColor(map_drawing_mask,temp_mask,cv::COLOR_BGRA2GRAY);
    cv::cvtColor(file_velocity,temp_velocity,cv::COLOR_BGR2GRAY);

    cv::multiply(cv::Scalar::all(1.0)-temp_mask,temp_velocity,temp_velocity);
    cv::add(temp_velocity,temp_draw,temp_velocity);

    cv::rotate(temp_velocity,temp_velocity,cv::ROTATE_90_CLOCKWISE);
    cv::flip(temp_velocity,temp_velocity,0);

    QString path = QDir::homePath() + "/RB_MOBILE/maps/" + pmap->map_name + "/map_velocity.png";
    plog->write("[MapHandler] SAVE MAP "+path);
    cv::imwrite(path.toStdString(),temp_velocity);

    lines.clear();
    temp_rect.clear();
    loadFile(map_name,"");
    setMap();
}
void MapHandler::saveObjectPNG(){
    initDrawing();
    QString file_path = QDir::homePath() + "/RB_MOBILE/maps/"+map_name + "/map_obs.png";
    cv::Mat temp_draw;
    cv::Mat temp_mask;
    if(QFile::exists(file_path)){
        file_object = cv::imread(file_path.toStdString(), cv::IMREAD_COLOR);
        cv::flip(file_object,file_object,0);
        cv::rotate(file_object,file_object,cv::ROTATE_90_COUNTERCLOCKWISE);
    }else{
        file_width = map_orin.rows;
        file_object = cv::Mat(file_width,file_width,CV_8UC3, cv::Scalar::all(0));
    }
//    qDebug() << QFile::exists(file_path) << file_width << file_object.rows << map_drawing.rows << lines.size();


    for(int line=0; line<lines.size(); line++){
        if(lines[line].type == 0){
            for(int i=0; i<lines[line].points.size()-1; i++){
                cv::line(map_drawing,cv::Point2f(lines[line].points[i].x,lines[line].points[i].y),cv::Point2f(lines[line].points[i+1].x,lines[line].points[i+1].y),cv::Scalar(lines[line].color,lines[line].color,lines[line].color,255),lines[line].width,8,0);
                cv::line(map_drawing_mask,cv::Point2f(lines[line].points[i].x,lines[line].points[i].y),cv::Point2f(lines[line].points[i+1].x,lines[line].points[i+1].y),cv::Scalar::all(255),lines[line].width,8,0);
            }
        }else if(lines[line].type == 1){
            cv::rectangle(map_drawing,lines[line].points[0],lines[line].points[2],cv::Scalar::all(255),-1,8,0);
            cv::rectangle(map_drawing_mask,lines[line].points[0],lines[line].points[2],cv::Scalar::all(255),-1,8,0);
        }
    }
    cv::cvtColor(map_drawing,temp_draw,cv::COLOR_BGRA2BGR);
    cv::cvtColor(map_drawing_mask,temp_mask,cv::COLOR_BGRA2BGR);

    cv::multiply(cv::Scalar::all(1.0)-temp_mask,file_object,file_object);
    cv::add(file_object,temp_draw,file_object);

    cv::rotate(file_object,file_object,cv::ROTATE_90_CLOCKWISE);
    cv::flip(file_object,file_object,0);

    QString path = QDir::homePath() + "/RB_MOBILE/maps/" + pmap->map_name + "/map_obs.png";
    plog->write("[MapHandler] SAVE MAP "+path);
    cv::imwrite(path.toStdString(),file_object);

    lines.clear();
    line.clear();
    lines_trash.clear();
    initDrawing();

    loadFile(map_name,"");
}
void MapHandler::saveObsAreaPNG(){
    initDrawing();
    QString file_path = QDir::homePath() + "/RB_MOBILE/maps/"+map_name + "/map_avoid.png";
    cv::Mat temp_draw;
    cv::Mat temp_mask;
//    if(QFile::exists(file_path)){
//        file_avoid = cv::imread(file_path.toStdString(), cv::IMREAD_COLOR);
//        cv::flip(file_avoid,file_avoid,0);
//        cv::rotate(file_avoid,file_avoid,cv::ROTATE_90_COUNTERCLOCKWISE);
//    }else{
//        file_width = map_orin.rows;
//        file_avoid = cv::Mat(file_width,file_width,CV_8UC3, cv::Scalar::all(0));
//    }
//    qDebug() << QFile::exists(file_path) << file_width << file_avoid.rows << map_drawing.rows << lines.size();

    for(int line=0; line<lines.size(); line++){
        if(lines[line].type == 0){
            for(int i=0; i<lines[line].points.size()-1; i++){
                cv::line(map_drawing,cv::Point2f(lines[line].points[i].x,lines[line].points[i].y),cv::Point2f(lines[line].points[i+1].x,lines[line].points[i+1].y),cv::Scalar(lines[line].color,lines[line].color,lines[line].color,255),lines[line].width,8,0);
                cv::line(map_drawing_mask,cv::Point2f(lines[line].points[i].x,lines[line].points[i].y),cv::Point2f(lines[line].points[i+1].x,lines[line].points[i+1].y),cv::Scalar::all(255),lines[line].width,8,0);
            }
        }else if(lines[line].type == 1){
            cv::rectangle(map_drawing,lines[line].points[0],lines[line].points[2],cv::Scalar::all(255),-1,8,0);
            cv::rectangle(map_drawing_mask,lines[line].points[0],lines[line].points[2],cv::Scalar::all(255),-1,8,0);
        }
    }
    cv::cvtColor(map_drawing,temp_draw,cv::COLOR_BGRA2BGR);
    cv::cvtColor(map_drawing_mask,temp_mask,cv::COLOR_BGRA2BGR);

    cv::multiply(cv::Scalar::all(1.0)-temp_mask,file_avoid,file_avoid);
    cv::add(file_avoid,temp_draw,file_avoid);

    cv::rotate(file_avoid,file_avoid,cv::ROTATE_90_CLOCKWISE);
    cv::flip(file_avoid,file_avoid,0);

    QString path = QDir::homePath() + "/RB_MOBILE/maps/" + pmap->map_name + "/map_avoid.png";
    plog->write("[MapHandler] SAVE MAP "+path);
    cv::imwrite(path.toStdString(),file_avoid);

    lines.clear();
    line.clear();
    lines_trash.clear();
    initDrawing();
}
void MapHandler::saveEditedMap(){
    cv::Mat temp_draw;
    cv::Mat temp_mask;

    cv::cvtColor(map_drawing,temp_draw,cv::COLOR_BGRA2GRAY);
    cv::cvtColor(map_drawing_mask,temp_mask,cv::COLOR_BGRA2GRAY);
    cv::multiply(cv::Scalar::all(1.0)-temp_mask,file_edited,file_edited);
    cv::add(file_edited,temp_draw,file_edited);

    cv::rotate(file_edited,file_edited,cv::ROTATE_90_CLOCKWISE);
    cv::flip(file_edited,file_edited,0);

    QString path = QDir::homePath() + "/RB_MOBILE/maps/" + pmap->map_name + "/map_edited.png";
    plog->write("[MapHandler] SAVE MAP "+path);
    cv::imwrite(path.toStdString(),file_edited);
    lines.clear();
    line.clear();
    spline_dot.clear();
    lines_trash.clear();
    initDrawing();
    loadFile(map_name,"");
}
void MapHandler::saveTline(){
    cv::Mat temp_draw;
    cv::Mat temp_mask;
    cv::Mat temp_tline_ui;

    cv::cvtColor(map_drawing,temp_draw,cv::COLOR_BGRA2BGR);
    cv::cvtColor(map_drawing_mask,temp_mask,cv::COLOR_BGRA2BGR);

    cv::multiply(cv::Scalar::all(1.0)-temp_mask,file_travelline_ui,file_travelline_ui);
    cv::add(file_travelline_ui,temp_draw,file_travelline_ui);

    for(int i=0; i<file_travelline.cols; i++){
        for(int j=0; j<file_travelline.rows; j++){
            if(file_travelline.at<cv::Vec3b>(i,j)[0] == 80){
                file_travelline.at<cv::Vec3b>(i,j)[0] = 255;
                file_travelline.at<cv::Vec3b>(i,j)[1] = 255;
                file_travelline.at<cv::Vec3b>(i,j)[2] = 255;
            }
        }
    }

    for(int i=0; i<file_travelline_ui.cols; i++){
        for(int j=0; j<file_travelline_ui.rows; j++){
            if(file_travelline_ui.at<cv::Vec3b>(i,j)[0] > 0){
                file_travelline_ui.at<cv::Vec3b>(i,j)[0] = 255;
                file_travelline_ui.at<cv::Vec3b>(i,j)[1] = 255;
                file_travelline_ui.at<cv::Vec3b>(i,j)[2] = 255;
            }
        }
    }

    cv::rotate(file_travelline,file_travelline,cv::ROTATE_90_CLOCKWISE);
    cv::flip(file_travelline,file_travelline,0);
    cv::rotate(file_travelline_ui,file_travelline_ui,cv::ROTATE_90_CLOCKWISE);
    cv::flip(file_travelline_ui,file_travelline_ui,0);


    QString path222 = QDir::homePath() + "/RB_MOBILE/maps/" + pmap->map_name + "/map_travel_line.png";
    plog->write("[MAP] saveTline : "+path222);
    cv::imwrite(path222.toStdString(),file_travelline);

    QString path2 = QDir::homePath() + "/RB_MOBILE/maps/" + pmap->map_name + "/map_travel_line_ui.png";
    plog->write("[MAP] saveTline : "+path2);
    cv::imwrite(path2.toStdString(),file_travelline_ui);

    cv::flip(file_travelline,file_travelline,0);
    cv::rotate(file_travelline,file_travelline,cv::ROTATE_90_COUNTERCLOCKWISE);
    cv::flip(file_travelline_ui,file_travelline_ui,0);
    cv::rotate(file_travelline_ui,file_travelline_ui,cv::ROTATE_90_COUNTERCLOCKWISE);
    lines.clear();
    line.clear();
    spline_dot.clear();
    lines_trash.clear();
    initDrawing();
}

void MapHandler::saveTlineTemp(){
    cv::Mat temp_travel;
    cv::Mat temp_draw;
    cv::Mat temp_mask;

    cv::cvtColor(map_drawing,temp_draw,cv::COLOR_BGRA2BGR);
    cv::cvtColor(map_drawing_mask,temp_mask,cv::COLOR_BGRA2BGR);

    cv::multiply(cv::Scalar::all(1.0)-temp_mask,file_travelline,file_travelline);
    cv::add(file_travelline,temp_draw,file_travelline);

    for(int i=0; i<file_travelline.cols; i++){
        for(int j=0; j<file_travelline.rows; j++){
            if(file_travelline.at<cv::Vec3b>(i,j)[0] == 80){
                file_travelline.at<cv::Vec3b>(i,j)[0] = 255;
                file_travelline.at<cv::Vec3b>(i,j)[1] = 255;
                file_travelline.at<cv::Vec3b>(i,j)[2] = 255;
            }
        }
    }

    cv::rotate(file_travelline,file_travelline,cv::ROTATE_90_CLOCKWISE);
    cv::flip(file_travelline,file_travelline,0);

    QString path = QDir::homePath() + "/RB_MOBILE/maps/" + pmap->map_name + "/map_travel_line.png";
    plog->write("[MAP] saveTlineTemp : "+path);
    cv::imwrite(path.toStdString(),file_travelline);
    cv::flip(file_travelline,file_travelline,0);
    cv::rotate(file_travelline,file_travelline,cv::ROTATE_90_COUNTERCLOCKWISE);
    lines.clear();
    line.clear();
    spline_dot.clear();
    lines_trash.clear();
    initDrawing();
}

void MapHandler::redoLine(){
    if(dot_trash.size() > 0){
        //qDebug() << "redoLine(Spline)";
        spline_dot.push_back(dot_trash[dot_trash.size()-1]);
        dot_trash.pop_back();
        drawSpline();
    }else if(lines_trash.size() > 0){
        //qDebug() << "redoLine";
        lines.push_back(lines_trash[lines_trash.size()-1]);
        lines_trash.pop_back();
        setMapDrawing();
        setMap();
    }
}

void MapHandler::startDrawingRect(int x, int y){
    temp_rect.clear();
    temp_rect.push_back(cv::Point2f(x,y));
    temp_rect.push_back(cv::Point2f(x,y));
    temp_rect.push_back(cv::Point2f(x,y));
    temp_rect.push_back(cv::Point2f(x,y));
    setMapDrawing();
    setMap();
}
void MapHandler::setDrawingRect(int x, int y){
    if(temp_rect.size() > 3){
        cv::Point2f orin = temp_rect[0];
        temp_rect[1] = cv::Point2f(orin.x,y);
        temp_rect[2] = cv::Point2f(x,y);
        temp_rect[3] = cv::Point2f(x,orin.y);
    }
    setMapDrawing();
    setMap();
}
void MapHandler::endDrawingRect(){
    LINE temp_line;
    temp_line.points = temp_rect;
    temp_line.width = cur_line_width;
    temp_line.color = cur_line_color;
    temp_line.type = 1;
    lines.push_back(temp_line);
    temp_rect.clear();
    setMapDrawing();
    setMap();
}


int MapHandler::getLocationGroupSize(int num){
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
void MapHandler::clearLocation(){
    new_location_flag = false;
    new_location.name = "";
    edit_location_flag = false;
    pmap->annot_edit_location = false;
    new_location.type = "";
    select_location = -1;
    initLocation();
    setMap();
}

void MapHandler::addLocation(int x, int y, float th){
    new_location_flag = true;
    new_location.point = cv::Point2f(x,y);
    new_location.angle = th;
//    qDebug() << "addLocation" << x << y << th << new_location.point.x << new_location.point.y << new_location.angle;
    initLocation();
    setMap();
}

void MapHandler::addLocationCur(int x, int y, float th){
    new_location_flag = true;
    new_location.point = setAxis(cv::Point2f(x,y));
    new_location.angle = setAxis(th);
    //qDebug() << "add:ocationCur" << x << y << th << new_location.point.x << new_location.point.y << new_location.angle;
    initLocation();
    setMap();
}
void MapHandler::setTravellineIssue(int count, int num){
    travelline_issue[count]=num;
    setMap();
}
void MapHandler::setSelectLocation(int num){
    select_location = num;
    setMap();
}
void MapHandler::setLocation(int x, int y, float th){
    int num = select_location;
    new_location_flag = false;
    if(pmap->locations.size() > num && num > -1){
        plog->write("[MapHandler] Edit Location "+QString().asprintf("%d : %f,%f,%f -> %f,%f,%f",num,pmap->locations[num].point.x, pmap->locations[num].point.y, pmap->locations[num].angle,setAxisBack(cv::Point2f(x,y)).x,setAxisBack(cv::Point2f(x,y)).y,setAxisBack(th)));
        pmap->locations[num].point = setAxisBack(cv::Point2f(x,y));
        pmap->locations[num].angle = setAxisBack(th);
//        //qDebug() << pmap->locations[num].angle;
        pmap->annot_edit_location = true;
    }
    initLocation();
    setMap();
}

int MapHandler::getLocationNum(int x, int y){
    int loc_id = -1;
    for(int i=0; i<pmap->locations.size(); i++){
        cv::Point2f pos = setAxisBack(cv::Point2f(x,y));
        if(fabs(pmap->locations[i].point.x - pos.x) < probot->radius*1.2){
            if(fabs(pmap->locations[i].point.y - pos.y) < probot->radius*1.2){
                loc_id = i;
                break;
            }
        }
    }

    if(loc_id > -1){
        if(pmap->locations[loc_id].type == "Resting"){
            if(getLocationNum("Charging") == 0)
                loc_id++;

            return loc_id;
        }else if(pmap->locations[loc_id].type == "Serving"){
            if(getLocationNum("Resting") == 0)
                loc_id++;
            if(getLocationNum("Charging") == 0)
                loc_id++;

            return loc_id;
        }
        return loc_id;
    }
    return -1;
}

int MapHandler::getLocationNum(QString type){
    int count = 0;
    for(int i=0; i<locations.size(); i++){
        if(locations[i].type == type)
            count++;
    }
    return count;
}
int MapHandler::getLocGroupNum(int num){
    int count = 0;
    for(int i=0; i<pmap->locations.size(); i++){
        if(pmap->locations[i].type == "Serving" && pmap->locations[i].group == num){
            count++;
        }
    }
    return count;
}

void MapHandler::editLocation(int x, int y, float th){
    int num = select_location;
    if(pmap->locations.size() > num && num > -1){
        if(!edit_location_flag){
            edit_location_flag = true;
            orin_location = pmap->locations[num];
        }
        pmap->locations[num].point = setAxisBack(cv::Point2f(x,y));
        pmap->locations[num].angle = setAxisBack(th);
        pmap->annot_edit_location = true;
    }
    initLocation();
    setMap();
}

void MapHandler::setRulerInit(int x, int y){
    if(ruler_point.size() == 1){

    }else{
        ruler_point.clear();
    }
    ruler_init_point = cv::Point2f(x,y);
}

void MapHandler::setRulerEnd(int x, int y){
    if(ruler_point.size() == 0){
        ruler_point.append(ruler_init_point);
        ruler_point.append(cv::Point2f(x,y));
    }else if(ruler_point.size() == 1){
        ruler_point.clear();
        ruler_point.append(ruler_init_point);
        ruler_point.append(cv::Point2f(x,y));
    }else{
        ruler_point[1] = cv::Point2f(x,y);
    }
}
void MapHandler::setRulerPoint(int x, int y){
    cv::Point2f p = cv::Point2f(x,y);
    if(ruler_point.size() < 2){
        ruler_point.append(p);
    }else{
        ruler_point.pop_front();
        ruler_point.append(p);
    }
    setMapLayer();
}


void MapHandler::setStraightInit(int x, int y){//pressed
    new_straight_flag = true;
    spline_dot.clear();
    if(straight_point.size() == 1){

    }else{
        straight_point.clear();
    }
    straight_init_point = cv::Point2f(x,y);
    curPoint.x = straight_init_point.x;
    curPoint.y = straight_init_point.y;
}

void MapHandler::setStraightEnd(int x, int y){//moved
    if(straight_point.size() == 0){
        straight_point.append(straight_init_point);
        straight_point.append(cv::Point2f(x,y));
    }else if(straight_point.size() == 1){
        straight_point.clear();
        straight_point.append(straight_init_point);
        straight_point.append(cv::Point2f(x,y));
    }else{
        straight_point[1] = cv::Point2f(x,y);
    }
    qDebug() << "setStraightEnd " << straight_init_point.x << straight_init_point.y << x << y;
    initDrawing();
    setMapDrawing();
    setMap();
}
void MapHandler::setStraightPoint(int x, int y){//released
    cv::Point2f p = cv::Point2f(x,y);
    if(straight_point.size() == 0){
        straight_point.append(p);
        curPoint.x = straight_point[0].x;
        curPoint.y = straight_point[0].y;
        qDebug() << "setStraightPoint 0 " << p.x << p.y;
    }else{
        line.clear();
        lines_trash.clear();
        new_straight_flag = false;
        if(straight_point.size() == 1){
            straight_point.append(p);
        }
        qDebug() << "setStraightPoint 1 " << p.x << p.y;
        curPoint.x = straight_point[0].x;
        curPoint.y = straight_point[0].y;
        line.push_back(curPoint);
        curPoint.x = straight_point[1].x;
        curPoint.y = straight_point[1].y;
        line.push_back(curPoint);
        LINE temp_line;
        temp_line.color = cur_line_color;
        temp_line.width = cur_line_width;
        temp_line.points = line;
        lines.push_back(temp_line);
        qDebug() << "setStraight " << cur_line_color << lines.size();
    }
    setMapDrawing();
    setMap();
}



void MapHandler::pressed(QString tool, int _x, int _y){
    float x = draw_x + _x*scale*file_width/canvas_width;
    float y = draw_y + _y*scale*file_width/canvas_height;
    qDebug() << "pressed " << tool;
//    qDebug() << "pressed " << _x << _y << x << y << scale << canvas_width;
    press_release = true;
    if(tool == "ruler"){
        setRulerInit(x,y);
    }else if(tool == "straight"){
        setStraightInit(x,y);
    }else if(tool == "topo"){
        tempNodeInit(x,y);
    }
}
void MapHandler::double_pressed(QString tool, int _x1, int _y1, int _x2, int _y2){

}

void MapHandler::moved(QString tool, int _x, int _y){
    float x = draw_x + _x*scale*file_width/canvas_width;
    float y = draw_y + _y*scale*file_width/canvas_height;
    if(tool == "ruler"){
        if(calculateDistance(cv::Point2f(x,y),ruler_init_point) > 10){
            press_release = false;
            setRulerEnd(x,y);
        }
    }else if(tool == "straight"){
        if(calculateDistance(cv::Point2f(x,y),straight_init_point) > 10){
            press_release = false;
            setStraightEnd(x,y);
        }
    }else if(tool == "topo"){
        tempNodeSet(x,y);
    }
    setMapLayer();

}
void MapHandler::double_moved(QString tool, int _x1, int _y1, int _x2, int _y2){

}
void MapHandler::released(QString tool, int x, int y){

}
void MapHandler::double_released(QString tool, int x1, int y1, int x2, int y2){
    float x = draw_x + x1*scale*file_width/canvas_width;
    float y = draw_y + y1*scale*file_width/canvas_height;
    qDebug() << "released " << tool << press_release;
    if(tool == "ruler"){
        if(press_release){
            setRulerPoint(x,y);
        }
    }else if(tool == "straight"){
        setStraightPoint(x,y);
    }
    press_release = false;
}

void MapHandler::keyPressEvent(QKeyEvent *ev){
    if (ev->isAutoRepeat())
    {
        return;
    }
}

void MapHandler::keyReleaseEvent(QKeyEvent *ev){
    if (ev->isAutoRepeat())
    {
        return;
    }
    qDebug() << ev->key();
//    if(ev->key() == Qt::Key_N){
//        addNode("","Route");
//    }else if(ev->key() == Qt::Key_E){
//        editNode();
//    }else if(ev->key() == Qt::Key_D){
//        deleteNode();
//    }else if(ev->key() == Qt::Key_R){
//        linkNode();
//    }
}
