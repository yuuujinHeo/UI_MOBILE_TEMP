#include <QtMath>
#include <QQmlApplicationEngine>
#include <QDir>
#include <QSettings>
#include <iostream>
#include <exception>
#include <QGuiApplication>
#include <fstream>
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
    map_drawing_mask = cv::Mat(1000,1000,CV_8UC4,cv::Scalar::all(0));
    file_velocity = cv::Mat(1000,1000,CV_8UC3,cv::Scalar::all(0));
    file_travelline = cv::Mat(1000,1000,CV_8U,cv::Scalar::all(0));
    file_object = cv::Mat(1000,1000,CV_8UC3,cv::Scalar::all(0));
    grid_width = 0.03;
    file_width = 1000;

    clearLocation();

    //메인 타이머
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()),this,SLOT(onTimer()));
    timer->start(200);

//    setTline();
}

bool MapHandler::getCutBoxFlag(){
    if(cut_box[0].x == 0 && cut_box[0].y == 0){
        if(cut_box[1].x == file_width && cut_box[1].y == file_width){
            return false;
        }
    }
    return true;
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
        log_str += ", EDITED(failed) ";
        if(exist_raw){
            file_raw.copyTo(map_orin);
        }
    }

    if(type == "T_TEMP"){
        file_path = QDir::homePath() + "/RB_MOBILE/maps/"+name + "/map_travel_line_ui.png";
    }else{
        file_path = QDir::homePath() + "/RB_MOBILE/maps/"+name + "/map_travel_line.png";
    }

    if(QFile::exists(file_path)){
        file_travelline = cv::imread(file_path.toStdString(), cv::IMREAD_GRAYSCALE);
        cv::flip(file_travelline,file_travelline,0);
        cv::rotate(file_travelline,file_travelline,cv::ROTATE_90_COUNTERCLOCKWISE);
        log_str += ", TRAVELLINE(success "+QString::number(file_travelline.rows)+" ) ";
        exist_travelline = true;
    }else{
        file_travelline = cv::Mat(file_width, file_width, CV_8U ,cv::Scalar::all(0));
        exist_travelline = false;
        log_str += ", TRAVELLINE(failed) ";
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
                    file_object.at<cv::Vec3b>(i,j)[0] = 80;
                    file_object.at<cv::Vec3b>(i,j)[1] = 200;
                    file_object.at<cv::Vec3b>(i,j)[2] = 255;
                }
            }
        }

        log_str += ", OBJECT(success "+QString::number(file_object.rows)+" ) ";
    }else{
        file_object = cv::Mat(file_width, file_width, CV_8UC3,cv::Scalar::all(0));
        log_str += ", OBJECT(failed) ";
    }
    map_name = name;

    draw_x = 0;
    draw_y = 0;
    draw_width = file_width;
    log_str += QString().sprintf(", FILEWIDTH(%d)",draw_width);
    initDrawing();
    initRotate();
    plog->write("[MapHandler] load File "+name+" : "+log_str);
}

void MapHandler::setMapOrin(QString type){
    if(type == "RAW"){
        plog->write("[MapHandler] set Map : map_raw.png");
        file_raw.copyTo(map_orin);
    }else if(type == "EDITED"){
        plog->write("[MapHandler] set Map : map_edited.png");
        file_edited.copyTo(map_orin);
    }
    file_width = map_orin.rows;
    file_velocity = cv::Mat(file_width, file_width, CV_8UC3, cv::Scalar::all(0));
    file_travelline = cv::Mat(file_width, file_width, CV_8U, cv::Scalar::all(0));
    initDrawing();
    setFullScreen();
    setMap();
    update();
}

//****setTline : 경로 좁은 사이 매꾸기 -> 미사용
void MapHandler::setTline(){
    int radius = pmap->robot_radius*2/grid_width;
    for(int i=0; i<file_travelline.rows;i++){
        //1줄 당
        for(int j=0; j<file_travelline.cols-1; j++){
            //실마리 찾음
            if(file_travelline.at<uchar>(i,j) == 255 && file_travelline.at<uchar>(i,j+1) == 0){

                //실마리 부터 시작해서 로봇 크기만큼 가까운 실이 있는 지 찾아봄(찾으면 그 사이 매꿈)
                for(int k=j+1; k<j+radius; k++){
                    if(k>=file_travelline.cols)
                        break;

                    if(file_travelline.at<uchar>(i,k) == 255){
                        for(int h=j+1; h<k+1; h++){
                            file_travelline.at<uchar>(i,h) = 255;
                        }
                        break;
                    }
                }
            }
        }
    }

    for(int i=0; i<file_travelline.cols;i++){
        //1줄 당
        for(int j=0; j<file_travelline.rows-1; j++){
            //실마리 찾음
            if(file_travelline.at<uchar>(j,i) == 255 && file_travelline.at<uchar>(j+1,i) == 0){

                //실마리 부터 시작해서 로봇 크기만큼 가까운 실이 있는 지 찾아봄(찾으면 그 사이 매꿈)
                for(int k=j+1; k<j+radius; k++){
                    if(k>=file_travelline.rows)
                        break;

                    if(file_travelline.at<uchar>(k,i) == 255){
                        for(int h=j+1; h<k+1; h++){
                            file_travelline.at<uchar>(h,i) = 255;
                        }
                        break;
                    }
                }
            }
        }
    }
}

void MapHandler::setMapSize(int width, int height){
    canvas_width = width;
    canvas_height = height;
}

void MapHandler::onTimer(){
    if(enable){
        if(flag_drawing){
            show_robot = true;
            robot_following = true;
            drawTline();
        }else if(mode == "annot_tline"){
            show_robot = false;
            robot_following = false;
        }

        //Robot Following
        if(robot_following){
            setZoomCenter();
        }

        setMap();
    }
}

void MapHandler::setMode(QString name){
    mode = name;
    plog->write("[MapHandler] "+object_name+" set Mode to "+name);
    show_travelline = false;
    show_object = false;
    draw_object_flag = false;
    show_velocitymap = false;
    if(mode == "none"){
        file_width = map_orin.rows;
        show_robot = true;
        show_global_path = false;
        show_local_path = false;
        show_lidar = true;
        show_location = false;
        show_location_icon = true;
        robot_following = false;
        setFullScreen();
    }else if(mode == "mapping"){
        show_robot = true;
        show_global_path = false;
        show_local_path = false;
        show_lidar = true;
        show_location = false;
        show_location_icon = false;
        robot_following = true;
        setFullScreen();
    }else if(mode == "map_list"){
        show_robot = false;
        show_global_path = false;
        show_local_path = false;
        show_lidar = false;
        show_location = false;
        show_location_icon = false;
        robot_following = false;
        setFullScreen();
    }else if(mode == "current"){
        file_width = map_orin.rows;
        show_robot = true;
        show_global_path = true;
        show_local_path = true;
        show_lidar = true;
        show_location = true;
        show_location_icon = true;
        robot_following = true;
        setFullScreen();
    }else if(mode == "annot_view"){
        file_width = map_orin.rows;
        show_robot = false;
        show_global_path = false;
        show_local_path = false;
        show_lidar = false;
        show_location = true;
        show_location_icon = true;
        robot_following = false;
        setFullScreen();
    }else if(mode == "annot_drawing" || mode == "annot_rotate"){
        file_width = map_orin.rows;
        show_robot = false;
        show_global_path = false;
        show_local_path = false;
        show_lidar = false;
        show_location = false;
        show_location_icon = false;
        robot_following = false;
        setFullScreen();
    }else if(mode == "serving_list"){
        file_width = map_orin.rows;
        show_robot = false;
        show_global_path = false;
        show_local_path = false;
        show_lidar = false;
        show_location = true;
        show_location_icon = true;
        robot_following = false;
        show_velocitymap = false;

        setFullScreen();
    }else if(mode == "annot_velmap"){
        file_width = map_orin.rows;
        show_robot = false;
        show_global_path = false;
        show_local_path = false;
        show_lidar = false;
        show_location = false;
        show_location_icon = false;
        robot_following = false;
        show_velocitymap = true;
        setFullScreen();
    }else if(mode == "annot_location"){
        file_width = map_orin.rows;
        show_robot = true;
        show_global_path = false;
        show_local_path = false;
        show_lidar = true;
        show_location = true;
        show_location_icon = true;
        robot_following = true;
        show_travelline = true;
//        setFullScreen();
    }else if(mode == "annot_tline"){
        file_width = map_orin.rows;
        show_robot = false;
        show_global_path = false;
        show_local_path = false;
        show_lidar = false;
        show_location = true;
        show_location_icon = true;
        robot_following = false;
        show_travelline = true;
        setFullScreen();
    }else if(mode == "localization"){
        file_width = map_orin.rows;
        show_robot = true;
        show_global_path = false;
        show_local_path = false;
        show_lidar = true;
        show_location = false;
        show_location_icon = false;
        robot_following = true;
        pmap->annotation_edited = false;
        pmap->annot_edit_drawing = false;
        pmap->annot_edit_location = false;
        pmap->annot_edit_tline = false;
        setFullScreen();
    }else if(mode == "local_view"){
        file_width = map_orin.rows;
        show_robot = true;
        show_global_path = false;
        show_local_path = false;
        show_lidar = true;
        show_location = false;
        show_location_icon = true;
        robot_following = true;
        scale = 0.7;
        setZoomCenter(0,0);
    }else if(mode == "mapviewer"){
        file_width = map_orin.rows;
        show_robot = false;
        show_global_path = false;
        show_local_path = false;
        show_lidar = false;
        show_location = false;
        show_location_icon = false;
        robot_following = false;
        setFullScreen();
    }else if(mode == "annot_object"){
        file_width = map_orin.rows;
        show_robot = true;
        show_global_path = false;
        show_local_path = false;
        show_lidar = false;
        show_object = true;
        show_location = true;
        show_location_icon = true;
        robot_following = false;
        initObject();
        setFullScreen();
    }else if(mode == "annot_object_png"){
        file_width = map_orin.rows;
        show_robot = true;
        show_global_path = false;
        show_local_path = false;
        show_lidar = false;
        show_object = true;
        show_location = true;
        show_location_icon = true;
        robot_following = false;
        initObject();
        setFullScreen();
    }
    setMap();
}

void MapHandler::startDrawingTline(){
    plog->write("[MapHandler] Start Draw Travel line");
    flag_drawing = true;
    prev_pose.x = 0;
    prev_pose.y = 0;
}
void MapHandler::stopDrawingTline(){
    plog->write("[MapHandler] Stop Draw Travel line");
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
        temp.type = pmap->locations[i].type;
        temp.name = pmap->locations[i].name;
        if(draw_object_flag){
            temp.point = setAxisObject(pmap->locations[i].point);
            temp.angle = setAxis(pmap->locations[i].angle);
        }else{
            temp.point = setAxis(pmap->locations[i].point);
            temp.angle = setAxis(pmap->locations[i].angle);
        }
//        qDebug() <<"locations push " << temp.type << temp.number;
        locations.push_back(temp);
    }
}

void MapHandler::setFullScreen(){
    draw_x = 0;
    draw_y = 0;
    draw_width = file_width;
    scale = 1;
//    qDebug() << "set Full Screen " << file_width << pmap->mapping_width << pmap->map_mapping.rows << map_orin.rows;
}

void MapHandler::moveMap(){
    final_map = map.copy(draw_x,draw_y,draw_width,draw_width);
    update();
}

void MapHandler::setMap(){
    if(mode == "mapping"){
        map = QPixmap::fromImage(mat_to_qimage_cpy(pmap->map_mapping));
        grid_width = pmap->mapping_gridwidth*pmap->mapping_width/file_width;
        if(file_width != pmap->map_mapping.rows){
            file_width = pmap->map_mapping.rows;
            setFullScreen();
        }
    }else if(draw_object_flag){
        map = QPixmap::fromImage(mat_to_qimage_cpy(pmap->map_objecting));
        grid_width = pmap->mapping_gridwidth*pmap->width/file_width;
        if(file_width != pmap->map_objecting.rows){
            file_width = pmap->map_objecting.rows;
            setFullScreen();
        }
    }else if(map_orin.rows > 0){
        file_width = map_orin.rows;
        grid_width = pmap->gridwidth;
        cv::Mat temp_orin, temp_travel, temp_velmap;
        cv::Mat temp_obj;
        cv::cvtColor(map_orin,temp_orin,cv::COLOR_GRAY2BGRA);
        cv::cvtColor(file_velocity,temp_velmap,cv::COLOR_BGR2BGRA);
        cv::cvtColor(file_travelline,temp_travel,cv::COLOR_GRAY2BGRA);

        cv::cvtColor(file_object,temp_obj,cv::COLOR_BGR2BGRA);

        //속도맵
        if(show_velocitymap){
            cv::multiply(cv::Scalar::all(1.0)-map_drawing_mask,temp_velmap,temp_velmap);
            cv::add(temp_velmap,map_drawing,temp_velmap);
            cv::addWeighted(temp_orin,1,temp_velmap,0.5,0,temp_orin);
        }

        //이동경로맵
        if(show_travelline){
            cv::multiply(cv::Scalar::all(1.0)-map_drawing_mask,temp_travel,temp_travel);
            cv::add(temp_travel,map_drawing,temp_travel);
            if(mode == "annot_location" || mode == "map_list"){
                cv::addWeighted(temp_orin,1,temp_travel,1,0,temp_orin);
            }else{
                cv::addWeighted(temp_orin,0.5,temp_travel,1,0,temp_orin);
            }
        }

        if(!show_velocitymap && !show_travelline){
            if(mode == "annot_object_png"){
                cv::multiply(cv::Scalar::all(1.0)-map_drawing_mask,temp_obj,temp_obj);
                cv::add(temp_obj,map_drawing,temp_obj);
                cv::addWeighted(temp_orin,1,temp_obj,0.5,0,temp_orin);
//                cv::multiply(cv::Scalar::all(1.0)-map_drawing_mask, temp_orin, temp_orin);
//                cv::addWeighted(temp_orin, 1,map_drawing,0.5,0,temp_orin);
            }else{
                cv::multiply(cv::Scalar::all(1.0)-map_drawing_mask,temp_orin,temp_orin);
                cv::add(temp_orin,map_drawing,temp_orin);
            }
//            qDebug() << map_drawing_mask.channels() << temp_orin.channels() << map_drawing_mask.rows << temp_orin.rows;

        }

        map = QPixmap::fromImage(mat_to_qimage_cpy(temp_orin));
    }


    QPainter painter(&map);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);


    //공용 변수
    cv::Point2f robot_pose;
    if(mode == "mapping"){
        robot_pose = setAxisMapping(probot->curPose.point);
    }else if(draw_object_flag){
        robot_pose = setAxisObject(probot->curPose.point);
    }else{
        robot_pose = setAxis(probot->curPose.point);
    }
    float robot_angle = setAxis(probot->curPose.angle);


    if(show_object && !draw_object_flag){
        for(int obj=0; obj<objs.size(); obj++){
            QPainterPath path;
            if(objs[obj].is_rect){
                if(select_obj == obj){
                    painter.setPen(QPen(Qt::white,3));
                    path.addRect(QRectF(QPointF(objs[obj].points[0].x*res,objs[obj].points[0].y*res),QPointF(objs[obj].points[2].x*res,objs[obj].points[2].y*res)));
                    painter.fillPath(path,QBrush(QColor(10,24,50,100)));
                    painter.drawPath(path);

                    QPainterPath circles;
                    for(int j=0; j<objs[obj].points.size(); j++){
                        int rad = 2*res;
                        int xx = objs[obj].points[j].x*res - rad;
                        int yy = objs[obj].points[j].y*res - rad;
                        circles.addRoundedRect(xx,yy,rad*2,rad*2,rad,rad);
                        painter.fillPath(circles,Qt::white);
                    }
                }else{
                    painter.setPen(QPen(Qt::white,1));
                    path.addRect(QRectF(QPointF(objs[obj].points[0].x*res,objs[obj].points[0].y*res),QPointF(objs[obj].points[2].x*res,objs[obj].points[2].y*res)));
                    painter.fillPath(path,QBrush(QColor(0,0,0,100)));
                    painter.drawPath(path);
                }
            }else{
                QPolygonF polygon;
                for(int j=0; j<objs[obj].points.size(); j++){
                    polygon << QPointF(objs[obj].points[j].x*res, objs[obj].points[j].y*res);
                }

                path.addPolygon(polygon);
                if(select_obj == obj){
                    painter.setPen(QPen(Qt::white,3));
                    painter.fillPath(path,QBrush(QColor(10,24,50,100)));
                    painter.drawPolygon(polygon);
                    QPainterPath circles;
                    for(int j=0; j<objs[obj].points.size(); j++){
                        int rad = 2*res;
                        int xx = objs[obj].points[j].x*res - rad;
                        int yy = objs[obj].points[j].y*res - rad;
                        circles.addRoundedRect(xx,yy,rad*2,rad*2,rad,rad);
                        painter.fillPath(circles,Qt::white);
                    }

                }else{
                    painter.setPen(QPen(Qt::white,1));
                    painter.fillPath(path,QBrush(QColor(0,0,0,100)));
                    painter.drawPolygon(polygon);
                }
            }
        }
        if(new_obj_flag){
            QPainterPath path;
            qDebug() << "new object drawing";
            if(new_obj.is_rect){
                path.addRect(QRectF(QPointF(new_obj.points[0].x*res,new_obj.points[0].y*res),QPointF(new_obj.points[2].x*res,new_obj.points[2].y*res)));
                painter.setPen(QPen(Qt::white,2));
                painter.fillPath(path,QBrush(QColor(10,24,50,100)));
                painter.drawPath(path);

//                    QPainterPath circles;
//                    for(int j=0; j<new_object.points.size(); j++){
//                        int rad = 2*res;
//                        int xx = new_object.points[j].x*res - rad;
//                        int yy = new_object.points[j].y*res - rad;
//                        circles.addRoundedRect(xx,yy,rad*2,rad*2,rad,rad);
//                        painter.fillPath(circles,Qt::white);
//                    }
            }else{
                QPolygonF polygon;
                for(int j=0; j<new_obj.points.size(); j++){
                    polygon << QPointF(new_obj.points[j].x*res, new_obj.points[j].y*res);
                }
                painter.setPen(QPen(Qt::white,2));
                path.addPolygon(polygon);
                painter.fillPath(path,QBrush(QColor(10,24,50,100)));
                painter.drawPolygon(polygon);
            }
        }
    }
    //위치
    if(show_location){
//        qDebug() << "location : " << locations.size() << pmap->locations.size();
//        qDebug() << "setmap : " << select_location;
        for(int i=0; i<locations.size(); i++){

            float distance = (pmap->robot_radius/grid_width)*2;
            float distance2 = distance*0.8;
            float th_dist = M_PI/8;

            float x =   (locations[i].point.x + distance    * qCos(locations[i].angle));
            float y =   (locations[i].point.y + distance    * qSin(locations[i].angle));
            float x1 =  (locations[i].point.x + distance2   * qCos(locations[i].angle-th_dist));
            float y1 =  (locations[i].point.y + distance2   * qSin(locations[i].angle-th_dist));
            float x2 =  (locations[i].point.x + distance2   * qCos(locations[i].angle+th_dist));
            float y2 =  (locations[i].point.y + distance2   * qSin(locations[i].angle+th_dist));

            float rad = pmap->robot_radius*2*res/grid_width;
            QPainterPath path;
            if(select_location == i){
                if(locations[i].type == "Serving"){
                    path.addRoundedRect((locations[i].point.x-rad/2),(locations[i].point.y-rad/2),rad,rad,rad,rad);
                    painter.setPen(QPen(Qt::white,3));

                    painter.fillPath(path,QBrush(QColor(hex_color_green)));

                    painter.drawPath(path);
                    painter.drawLine(x1,y1,x,y);
                    painter.drawLine(x,y,x2,y2);
                }else if(locations[i].type == "Resting"){
                }else if(locations[i].type == "Charging"){
                }
            }else{
                if(locations[i].type == "Serving"){
                    path.addRoundedRect((locations[i].point.x-rad/2),(locations[i].point.y-rad/2),rad,rad,rad,rad);
                    painter.setPen(QPen(Qt::white,1));

                    painter.fillPath(path,QBrush(QColor(hex_color_pink)));

                    painter.drawPath(path);
                    painter.setPen(QPen(Qt::white,1.5));
                    painter.drawLine(QLine(x1,y1,x,y));
                    painter.drawLine(QLine(x2,y2,x,y));
                }else if(locations[i].type == "Resting"){
                }else if(locations[i].type == "Charging"){
                }
            }
        }
        if(new_location_flag){
            float distance = (pmap->robot_radius/grid_width)*2;
            float distance2 = distance*0.8;
            float th_dist = M_PI/8;

            float x =   (new_location.point.x + distance    * qCos(new_location.angle));
            float y =   (new_location.point.y + distance    * qSin(new_location.angle));
            float x1 =  (new_location.point.x + distance2   * qCos(new_location.angle-th_dist));
            float y1 =  (new_location.point.y + distance2   * qSin(new_location.angle-th_dist));
            float x2 =  (new_location.point.x + distance2   * qCos(new_location.angle+th_dist));
            float y2 =  (new_location.point.y + distance2   * qSin(new_location.angle+th_dist));
            float rad = pmap->robot_radius*2*res/grid_width;
            QPainterPath path;
            path.addRoundedRect((new_location.point.x-rad/2),(new_location.point.y-rad/2),rad,rad,rad,rad);
            painter.setPen(QPen(Qt::white,3));

            painter.fillPath(path,QBrush(QColor(hex_color_blue)));

            painter.drawPath(path);
            painter.drawLine(QLine(x1,y1,x,y));
            painter.drawLine(QLine(x2,y2,x,y));
        }
    }

    if(show_location_icon){
        for(int i=0; i<locations.size(); i++){
            float distance = (pmap->robot_radius/grid_width)*2;
            float distance2 = distance*0.8;
            float th_dist = M_PI/8;
            float rad = pmap->robot_radius*2*res/grid_width;

            float x =   (locations[i].point.x + distance    * qCos(locations[i].angle));
            float y =   (locations[i].point.y + distance    * qSin(locations[i].angle));
            float x1 =  (locations[i].point.x + distance2   * qCos(locations[i].angle-th_dist));
            float y1 =  (locations[i].point.y + distance2   * qSin(locations[i].angle-th_dist));
            float x2 =  (locations[i].point.x + distance2   * qCos(locations[i].angle+th_dist));
            float y2 =  (locations[i].point.y + distance2   * qSin(locations[i].angle+th_dist));

            QPainterPath path;
            if(locations[i].type == "Resting"){
                if(select_location == i){
                    path.addRoundedRect((locations[i].point.x-rad/2),(locations[i].point.y-rad/2),rad,rad,rad,rad);

                    painter.setPen(QPen(QColor(hex_color_green),3));

                    painter.drawPath(path);
                    painter.drawLine(x1,y1,x,y);
                    painter.drawLine(x,y,x2,y2);
                    QImage image(":/icon/icon_home_1.png");
                    painter.drawImage(QRectF((locations[i].point.x-rad/2),(locations[i].point.y-rad/2),rad,rad),image,QRectF(0,0,image.width(),image.height()));
                }else{
                    path.addRoundedRect((locations[i].point.x-rad/2),(locations[i].point.y-rad/2),rad,rad,rad,rad);

                    painter.setPen(QPen(Qt::white,1));

                    painter.drawPath(path);
                    painter.drawLine(x1,y1,x,y);
                    painter.drawLine(x,y,x2,y2);
                    painter.drawPath(path);
                    QImage image(":/icon/icon_home_2.png");
                    painter.drawImage(QRectF((locations[i].point.x-rad/2),(locations[i].point.y-rad/2),rad,rad),image,QRectF(0,0,image.width(),image.height()));
                }
            }else if(locations[i].type == "Charging"){
                if(select_location == i){
                    path.addRoundedRect((locations[i].point.x-rad/2),(locations[i].point.y-rad/2),rad,rad,rad,rad);

                    painter.setPen(QPen(QColor(hex_color_green),3));

                    painter.drawPath(path);
                    painter.drawLine(x1,y1,x,y);
                    painter.drawLine(x,y,x2,y2);
                    QImage image(":/icon/icon_charge_1.png");
                    painter.drawImage(QRectF((locations[i].point.x-rad/2),(locations[i].point.y-rad/2),rad,rad),image,QRectF(0,0,image.width(),image.height()));
                }else{
                    path.addRoundedRect((locations[i].point.x-rad/2),(locations[i].point.y-rad/2),rad,rad,rad,rad);

                    painter.setPen(QPen(Qt::white,1));

                    painter.drawPath(path);
                    painter.drawLine(x1,y1,x,y);
                    painter.drawLine(x,y,x2,y2);
                    painter.drawPath(path);
                    QImage image(":/icon/icon_charge_2.png");
                    painter.drawImage(QRectF((locations[i].point.x-rad/2),(locations[i].point.y-rad/2),rad,rad),image,QRectF(0,0,image.width(),image.height()));
                }
            }
        }
    }

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

    //로봇 경로 표시
    if(show_global_path){
        painter.setPen(QPen(QColor(hex_color_pink),2));
        cv::Point2f cur_path;
        cv::Point2f next_path;
        float target_angle=0;
        for(int i=0; i<probot->curPath.size()-1; i++){
            cur_path = setAxis(probot->curPath[i].point);
            next_path = setAxis(probot->curPath[i+1].point);
            target_angle = setAxis(probot->curPath[i+1].angle);
            painter.drawLine(cur_path.x,cur_path.y,next_path.x,next_path.y);
        }

        if(probot->curPath.size() > 0){
            float distance = (pmap->robot_radius/grid_width)*2;
            float distance2 = distance*0.8;
            float th_dist = M_PI/8;

            float x =   (next_path.x - distance    * qSin(target_angle));
            float y =   (next_path.y - distance    * qCos(target_angle));
            float x1 =  (next_path.x - distance2   * qSin(target_angle-th_dist));
            float y1 =  (next_path.y - distance2   * qCos(target_angle-th_dist));
            float x2 =  (next_path.x - distance2   * qSin(target_angle+th_dist));
            float y2 =  (next_path.y - distance2   * qCos(target_angle+th_dist));
            float rad = pmap->robot_radius*2/grid_width;
            QPainterPath path;
            path.addRoundedRect((next_path.x-rad/2),(next_path.y-rad/2),rad,rad,rad,rad);
            painter.setPen(QPen(QColor(hex_color_pink),2));
            painter.fillPath(path,QBrush(QColor("white")));
            painter.drawPath(path);
            painter.drawLine(QLine(x1,y1,x,y));
            painter.drawLine(QLine(x2,y2,x,y));


            if(show_local_path){
                QPainterPath circles;
                for(int i=0; i<probot->localpathSize; i++){
                    int rad = 2;
                    int xx = setAxis(probot->localPath[i].point).x - rad;
                    int yy = setAxis(probot->localPath[i].point).y - rad;
                    circles.addRoundedRect(xx,yy,rad*2,rad*2,rad,rad);
                    painter.fillPath(circles,Qt::white);
                }
            }
        }
    }

    //로봇 현재 위치 표시(매핑 중이거나 위치 초기화 성공했을 때만)
    if(show_robot){
        if(probot->localization_state == LOCAL_READY || mode == "mapping" || draw_object_flag){
            float distance = (pmap->robot_radius/grid_width)*2;
            float distance2 = distance*0.8;
            float th_dist = M_PI/8;

            float x =   (robot_pose.x + distance    * qCos(robot_angle));
            float y =   (robot_pose.y + distance    * qSin(robot_angle));
            float x1 =  (robot_pose.x + distance2   * qCos(robot_angle-th_dist));
            float y1 =  (robot_pose.y + distance2   * qSin(robot_angle-th_dist));
            float x2 =  (robot_pose.x + distance2   * qCos(robot_angle+th_dist));
            float y2 =  (robot_pose.y + distance2   * qSin(robot_angle+th_dist));
            float rad = pmap->robot_radius*2/grid_width;
            QPainterPath path;
            QPolygonF polygon;
            polygon << QPointF(x1,y1) << QPointF(x2,y2) << QPointF(x,y) << QPointF(x1,y1);
            path.addRoundedRect((robot_pose.x-rad/2),(robot_pose.y-rad/2),rad,rad,rad,rad);
            painter.setPen(QPen(QColor("white"),2));
            painter.fillPath(path,QBrush(QColor("red")));
            painter.drawPath(path);
            QPainterPath direction;
            direction.addPolygon(polygon);
            painter.fillPath(direction,QBrush(QColor("red")));
            if(set_init_pressed){
                cv::Point2f init_pose = set_init_pose.point;
                float init_angle = set_init_pose.angle;
                float distance = (pmap->robot_radius/grid_width)*2;
                float distance2 = distance*0.8;
                float th_dist = M_PI/8;

                float x =   (init_pose.x + distance    * qCos(init_angle));
                float y =   (init_pose.y + distance    * qSin(init_angle));
                float x1 =  (init_pose.x + distance2   * qCos(init_angle-th_dist));
                float y1 =  (init_pose.y + distance2   * qSin(init_angle-th_dist));
                float x2 =  (init_pose.x + distance2   * qCos(init_angle+th_dist));
                float y2 =  (init_pose.y + distance2   * qSin(init_angle+th_dist));
                float rad = pmap->robot_radius*2*res/grid_width;
                QPainterPath path;
                path.addRoundedRect((init_pose.x-rad/2),(init_pose.y-rad/2),rad,rad,rad,rad);
                painter.setPen(QPen(QColor("white"),2));
                painter.fillPath(path,QBrush(QColor(hex_color_green)));
                painter.drawPath(path);
                painter.drawLine(QLine(x1,y1,x,y));
                painter.drawLine(QLine(x2,y2,x,y));
            }
        }else if(set_init_flag){
            cv::Point2f init_pose = set_init_pose.point;
            float init_angle = set_init_pose.angle;
            float distance = (pmap->robot_radius/grid_width)*2;
            float distance2 = distance*0.8;
            float th_dist = M_PI/8;

            float x =   (init_pose.x + distance    * qCos(init_angle));
            float y =   (init_pose.y + distance    * qSin(init_angle));
            float x1 =  (init_pose.x + distance2   * qCos(init_angle-th_dist));
            float y1 =  (init_pose.y + distance2   * qSin(init_angle-th_dist));
            float x2 =  (init_pose.x + distance2   * qCos(init_angle+th_dist));
            float y2 =  (init_pose.y + distance2   * qSin(init_angle+th_dist));
            float rad = pmap->robot_radius*2*res/grid_width;
            QPainterPath path;
            path.addRoundedRect((init_pose.x-rad/2),(init_pose.y-rad/2),rad,rad,rad,rad);
            painter.setPen(QPen(QColor("white"),2));
            painter.fillPath(path,QBrush(QColor(hex_color_green)));
            painter.drawPath(path);
            painter.drawLine(QLine(x1,y1,x,y));
            painter.drawLine(QLine(x2,y2,x,y));
        }
    }

    //로봇 현재 위치 기준으로 라이다 표시
    if(show_lidar){
        if(mode == "local_view"){
            painter.setPen(QPen(QColor(hex_color_blue),3));
            float x1, y1;
            int num=0;
            float limit = pmap->robot_radius;
            for(int i=0; i<360; i++){
                if(probot->lidar_data[i] > limit){
                    x1 = (robot_pose.x + (probot->lidar_data[i]/grid_width)*cos((-M_PI*(i))/180 + robot_angle));
                    y1 = (robot_pose.y + (probot->lidar_data[i]/grid_width)*sin((-M_PI*(i))/180 + robot_angle));
                    num = i;
                    break;
                }
            }
            for(int i=num+1; i<360; i++){
                if(probot->lidar_data[i] > limit){
                    float x2 = (robot_pose.x + (probot->lidar_data[i]/grid_width)*cos((-M_PI*i)/180 + robot_angle));
                    float y2 = (robot_pose.y + (probot->lidar_data[i]/grid_width)*sin((-M_PI*i)/180 + robot_angle));
                    painter.drawLine(round(x1), round(y1), round(x2), round(y2));
                    x1 = x2;
                    y1 = y2;
                }
            }
        }else{
            for(int i=0; i<360; i++){
                painter.setPen(QPen(QColor("red"),2));
                if(probot->lidar_data[i] > grid_width){
                    float x = (robot_pose.x + (probot->lidar_data[i]/grid_width)*cos((-M_PI*i)/180 + robot_angle));
                    float y = (robot_pose.y + (probot->lidar_data[i]/grid_width)*sin((-M_PI*i)/180 + robot_angle));
                    painter.drawPoint(round(x),round(y));
                }
            }
        }
    }

    //Cur Brush View
    if(show_brush){
        if(cur_line_color == 255){
            painter.setPen(QPen(Qt::black,1));
            painter.drawRoundedRect(curPoint.x-cur_line_width/2,curPoint.y-cur_line_width/2,cur_line_width,cur_line_width,cur_line_width,cur_line_width);
        }else{
            painter.setPen(QPen(Qt::white,1));
            painter.drawRoundedRect(curPoint.x-cur_line_width/2,curPoint.y-cur_line_width/2,cur_line_width,cur_line_width,cur_line_width,cur_line_width);
        }
    }

    final_map = map.copy(draw_x,draw_y,draw_width,draw_width);
    update();
}
void MapHandler::update(){
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
    plog->write("[MapHandler] Save Map (Rotate) : "+tool+", "+QString().sprintf("%f,%f ~ %f,%f",cut_box[0].x,cut_box[0].y,cut_box[1].x,cut_box[1].y));

    //travel line 파일 없을 경우 대비해서 더미 제작
    if(!exist_travelline){
        cv::Mat temp_travelline = cv::Mat(map_edited_ui.rows,map_edited_ui.cols, CV_8U,cv::Scalar::all(0));
        QString path1 = QDir::homePath() + "/RB_MOBILE/maps/" + map_name + "/map_travel_line.png";
        cv::imwrite(path1.toStdString(),temp_travelline);
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
            plog->write("[MapHandler] edit Object : " + QString().sprintf("(%d, %d, %d, %d)",num,point,x,y));
        }else{
            if(point > -1 && point < pmap->objects[num].points.size()){
                cv::Point2f pos = setAxisBack(cv::Point2f(x,y));
                pmap->objects[num].points[point].x = pos.x;
                pmap->objects[num].points[point].y = pos.y;
                plog->write("[MapHandler] edit Object : "+ QString().sprintf("(%d, %d, %d, %d)",num,point,x,y));
            }else{
                plog->write("[MapHandler] edit Object : " + QString().sprintf("(%d, %d, %d, %d)",num,point,x,y) + " but pose size error");
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
        plog->write("[MapHandler] ADD Object (Rect) : "+QString().sprintf("(%f,%f) ,(%f,%f)",new_obj.points[0].x, new_obj.points[0].y, new_obj.points[2].x,new_obj.points[2].y));
    }else{
        plog->write("[MapHandler] ADD Object : "+QString().sprintf("%d",new_obj.points.size()));
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
//    qDebug() << "check obj" << num;// << pmap->objects[num].points.size();
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
//    setting.setValue("map_metadata/map_w",QString::number(pmap->width));
//    setting.setValue("map_metadata/map_h",QString::number(pmap->height));
//    setting.setValue("map_metadata/map_origin_u",QString::number(pmap->origin[0]));
//    setting.setValue("map_metadata/map_origin_v",QString::number(pmap->origin[1]));

    setting.setValue("map_metadata/map_edited_angle",QString::number(pmap->map_rotate_angle));
    setting.setValue("map_metadata/map_edited_w",QString::number(pmap->width));
    setting.setValue("map_metadata/map_edited_h",QString::number(pmap->height));
    setting.setValue("map_metadata/map_edited_origin_u",QString::number(pmap->origin[0]));
    setting.setValue("map_metadata/map_edited_origin_v",QString::number(pmap->origin[1]));
    setting.setValue("map_metadata/map_edited_cut_u",QString::number(pmap->cut_map[0]));
    setting.setValue("map_metadata/map_edited_cut_v",QString::number(pmap->cut_map[1]));
    plog->write("[MapHandler] UPDATE META : "+QString().sprintf("%d, %d, %d, %d, %d, %d, %d",pmap->map_rotate_angle, pmap->cut_map[0], pmap->cut_map[1], pmap->width,pmap->height, pmap->origin[0],pmap->origin[1]));
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
    setMap();
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
    moveMap();
}
void MapHandler::zoomIn(int x, int y){
    scale -= 0.05;
    if(scale < 0.1){
        scale = 0.1;
    }
    draw_width = round(scale*file_width);
    setZoomCenter(x,y);
    prev_scale = scale;
    update();
}
void MapHandler::zoomOut(int x, int y){
    scale += 0.05;
    if(scale > 1)
        scale =1;
    draw_width = round(scale*file_width);
    setZoomCenter(x,y);
    prev_scale = scale;
    update();
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
    cv::warpAffine(map_orin,map_orin,rot,map_orin.size(),cv::INTER_NEAREST);
    setMap();
}

void MapHandler::rotateMapCCW(){
//    qDebug() << "rotate ccw " << rotate_angle << file_width;
    rotate_angle--;
    pmap->map_rotate_angle = rotate_angle;
    //맵 회전
    cv::Mat rot = cv::getRotationMatrix2D(cv::Point2f(file_width/2, file_width/2),-rotate_angle,1.0);

    if(exist_edited)
        file_edited.copyTo(map_orin);
    else if(exist_raw)
        file_raw.copyTo(map_orin);
    cv::warpAffine(map_orin,map_orin,rot,map_orin.size(),cv::INTER_NEAREST);
    setMap();
}

void MapHandler::move(int x, int y){
    setX(x);
    setY(y);
    moveMap();
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
    float newx = draw_x - file_width*(scale - prev_scale)*((float)x/canvas_width);
    float newy = draw_y - file_width*(scale - prev_scale)*((float)y/canvas_width);

    setX(newx);
    setY(newy);

    final_map = map.copy(draw_x,draw_y,draw_width,draw_width);
    update();
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
    new_straight_flag = true;
    spline_dot.clear();
    straight[0].x = x;
    straight[0].y = y;
    straight[1].x = x;
    straight[1].y = y;
    setMap();
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
        for(size_t p = 1; p<spline_dot.toStdVector().size(); p++){
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
                        cv::line(map_drawing,cv::Point2f(lines[line].points[i].x,lines[line].points[i].y),cv::Point2f(lines[line].points[i+1].x,lines[line].points[i+1].y),color_yellow,lines[line].width,8,0);
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
                cv::rectangle(map_drawing,lines[line].points[0],lines[line].points[2],color_yellow,-1,8,0);
                cv::rectangle(map_drawing_mask,lines[line].points[0],lines[line].points[2],cv::Scalar::all(255),-1,8,0);
            }
        }
    }
    if(new_straight_flag){
        if(mode == "annot_velmap"){
            if(cur_line_color == 100){
                cv::line(map_drawing,straight[0],straight[1],color_yellow,cur_line_width,8,0);
                cv::line(map_drawing_mask,straight[0],straight[1],cv::Scalar::all(255),cur_line_width,8,0);
            }else if(cur_line_color == 200){
                cv::line(map_drawing,straight[0],straight[1],color_red,cur_line_width,8,0);
                cv::line(map_drawing_mask,straight[0],straight[1],cv::Scalar::all(255),cur_line_width,8,0);
            }
        }else if(mode == "annot_object_png"){

            cv::line(map_drawing,straight[0],straight[1],color_yellow,cur_line_width,8,0);
            cv::line(map_drawing_mask,straight[0],straight[1],cv::Scalar::all(255),cur_line_width,8,0);
        }else{
            cv::line(map_drawing,straight[0],straight[1],cv::Scalar(cur_line_color,cur_line_color,cur_line_color,255),cur_line_width,8,0);
            cv::line(map_drawing_mask,straight[0],straight[1],cv::Scalar::all(255),cur_line_width,8,0);
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
            cv::rectangle(map_drawing,temp_rect[0],temp_rect[2],color_yellow,-1,8,0);
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
void MapHandler::setDrawingLine(int x, int y){
//    qDebug() << "setDrawingLine " << x << y;
    straight[1].x = x;
    straight[1].y = y;
    initDrawing();
    setMapDrawing();
    setMap();
}
void MapHandler::stopDrawingLine(int x, int y){
//    //qDebug() << "stopDrawingLine";
    line.clear();
    lines_trash.clear();
    new_straight_flag = false;
    curPoint.x = straight[0].x;
    curPoint.y = straight[0].y;
    line.push_back(curPoint);
    curPoint.x = straight[1].x;
    curPoint.y = straight[1].y;
    line.push_back(curPoint);
    LINE temp_line;
    temp_line.color = cur_line_color;
    temp_line.width = cur_line_width;
    temp_line.points = line;
    lines.push_back(temp_line);
    setMapDrawing();
    setMap();
}
void MapHandler::startDrawing(int x, int y){
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
        cv::line(map_drawing,prev_pose,pose,cv::Scalar::all(255),1,8,0);
    }
    prev_pose = pose;
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
            cv::line(map_drawing,line[line.size()-2],line[line.size()-1],color_yellow,cur_line_width,8,0);
            cv::line(map_drawing_mask,line[line.size()-2],line[line.size()-1],cv::Scalar::all(255),cur_line_width,8,0);
        }
    }else{
        cv::line(map_drawing,line[line.size()-2],line[line.size()-1],cv::Scalar(cur_line_color,cur_line_color,cur_line_color,255),cur_line_width,8,0);
        cv::line(map_drawing_mask,line[line.size()-2],line[line.size()-1],cv::Scalar::all(255),cur_line_width,8,0);
    }

//    setMapDrawing();
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
    if(tool != "erase" && mode == "annot_tline"){
        std::vector<double> x_list;
        std::vector<double> y_list;
        std::vector<double> d_list;

        double sum_d = 0;
        d_list.push_back(sum_d);
        x_list.push_back(line[0].x);
        y_list.push_back(line[0].y);
        for(size_t p = 1; p<line.toStdVector().size(); p++){
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
    if(spline_dot.size() > 0){
        //qDebug() << "undoLine(Spline)";
        dot_trash.push_back(spline_dot[spline_dot.size()-1]);
        spline_dot.pop_back();
        drawSpline();
    }else if(lines.size() > 0 || line.size() > 0){
        //qDebug() << "undoLine";
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
    qDebug() << QFile::exists(file_path) << file_width << file_object.rows << map_drawing.rows << lines.size();


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

    cv::cvtColor(map_drawing,temp_draw,cv::COLOR_BGRA2GRAY);
    cv::cvtColor(map_drawing_mask,temp_mask,cv::COLOR_BGRA2GRAY);

    cv::multiply(cv::Scalar::all(1.0)-temp_mask,file_travelline,file_travelline);
    cv::add(file_travelline,temp_draw,file_travelline);

//    setTline();

    cv::rotate(file_travelline,file_travelline,cv::ROTATE_90_CLOCKWISE);
    cv::flip(file_travelline,file_travelline,0);

    QString path = QDir::homePath() + "/RB_MOBILE/maps/" + pmap->map_name + "/map_travel_line.png";
    plog->write("[MapHandler] SAVE MAP "+path);
    cv::imwrite(path.toStdString(),file_travelline);

    cv::flip(file_travelline,file_travelline,0);
    cv::rotate(file_travelline,file_travelline,cv::ROTATE_90_COUNTERCLOCKWISE);
    lines.clear();
    line.clear();
    spline_dot.clear();
    lines_trash.clear();
    initDrawing();

    loadFile(map_name,"");
}

void MapHandler::saveTlineTemp(){
    cv::Mat temp_travel;
    cv::Mat temp_draw;
    cv::Mat temp_mask;

    cv::cvtColor(map_drawing,temp_draw,cv::COLOR_BGRA2GRAY);
    cv::cvtColor(map_drawing_mask,temp_mask,cv::COLOR_BGRA2GRAY);

    cv::multiply(cv::Scalar::all(1.0)-temp_mask,file_travelline,file_travelline);
    cv::add(file_travelline,temp_draw,file_travelline);

//    setTline();

    cv::rotate(file_travelline,file_travelline,cv::ROTATE_90_CLOCKWISE);
    cv::flip(file_travelline,file_travelline,0);

    QString path = QDir::homePath() + "/RB_MOBILE/maps/" + pmap->map_name + "/map_travel_line_ui.png";
    plog->write("[MapHandler] SAVE MAP "+path);
    cv::imwrite(path.toStdString(),file_travelline);
    cv::flip(file_travelline,file_travelline,0);
    cv::rotate(file_travelline,file_travelline,cv::ROTATE_90_COUNTERCLOCKWISE);
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
void MapHandler::setSelectLocation(int num){
    select_location = num;
}
void MapHandler::setLocation(int x, int y, float th){
    int num = select_location;
    new_location_flag = false;
    if(pmap->locations.size() > num && num > -1){
        plog->write("[MapHandler] Edit Location "+QString().sprintf("%d : %f,%f,%f -> %f,%f,%f",num,pmap->locations[num].point.x, pmap->locations[num].point.y, pmap->locations[num].angle,setAxisBack(cv::Point2f(x,y)).x,setAxisBack(cv::Point2f(x,y)).y,setAxisBack(th)));
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



