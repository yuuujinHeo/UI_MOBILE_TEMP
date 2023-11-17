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
#include "MapView.h"

extern QObject *object;

PixmapContainer::PixmapContainer(QObject *parent){

}

MapView::MapView(QQuickItem *parent):
    QQuickPaintedItem(parent)
{
    map_width = 1000;
    map_height = 1000;
    scale = 1;
    map_x = 0;
    map_y = 0;
    tool = "move";

    //선택한 오브젝트 번호
    select_location = -1;
    select_object = -1;
    select_object_point = -1;

    //메인 타이머
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()),this,SLOT(onTimer()));
    timer->start(200);
}

void MapView::onTimer(){
    // QML 오브젝트 매칭
    if(mMain == nullptr && object != nullptr){
        setObject(object);
        setWindow(qobject_cast<QQuickWindow*>(object));
    }

    //Robot Following
    if(robot_following){
        setZoomCenter();
    }

    if(flag_drawing){
        drawTline();
    }

    if(mode != "mapping"){
        if(probot->ipc_use){
            setMapCurrent();
        }
    }else{
        mapping_size = 1000;
        mapping_grid = pmap->mapping_gridwidth*pmap->mapping_width/1000;

        if(probot->ipc_use){
            setMapCurrent();
        }
    }
}


void MapView::setMode(QString name){
    mode = name;
    plog->write("[MAPVIEW] "+object_name+" set Mode to "+name);
    if(mode == "none"){
        show_robot = true;
        show_global_path = false;
        show_local_path = false;
        show_lidar = true;
        show_object = true;
        show_object_box = true;
        show_location = false;
        show_location_icon = true;
        robot_following = false;
        setFullScreen();
    }else if(mode == "mapping"){
        show_robot = true;
        show_global_path = false;
        show_local_path = false;
        show_lidar = true;
        show_object = false;
        show_object_box = false;
        show_location = false;
        show_location_icon = false;
        robot_following = true;
        setFullScreen();
    }else if(mode == "current"){
        show_robot = true;
        show_global_path = true;
        show_local_path = true;
        show_lidar = true;
        show_object = true;
        show_object_box = true;
        show_location = false;
        show_location_icon = true;
        robot_following = true;
        setFullScreen();
    }else if(mode == "annot_view"){
        show_robot = false;
        show_global_path = false;
        show_local_path = false;
        show_lidar = false;
        show_object = true;
        show_object_box = true;
        show_location = true;
        show_location_icon = true;
        robot_following = false;
        initObject();
        setFullScreen();
    }else if(mode == "annot_objecting" || mode == "annot_object"){
        show_robot = true;
        show_global_path = false;
        show_local_path = false;
        show_lidar = true;
        show_object = true;
        show_object_box = true;
        show_location = true;
        show_location_icon = true;
        robot_following = false;
        initObject();
        setFullScreen();
    }else if(mode == "annot_drawing" || mode == "annot_rotate"){
        show_robot = false;
        show_global_path = false;
        show_local_path = false;
        show_lidar = false;
        show_object = false;
        show_object_box = false;
        show_location = false;
        show_location_icon = false;
        robot_following = false;
        setFullScreen();
    }else if(mode == "annot_velmap"){
        show_robot = false;
        show_global_path = false;
        show_local_path = false;
        show_lidar = false;
        show_object = false;
        show_object_box = false;
        show_location = false;
        show_location_icon = false;
        robot_following = false;
        setFullScreen();
    }else if(mode == "annot_location"){
        show_robot = true;
        show_global_path = false;
        show_local_path = false;
        show_lidar = true;
        show_object = true;
        show_object_box = true;
        show_location = true;
        show_location_icon = true;
        robot_following = false;
        setFullScreen();
    }else if(mode == "annot_tline"){
        show_robot = false;
        show_global_path = false;
        show_local_path = false;
        show_lidar = false;
        show_object = true;
        show_object_box = true;
        show_location = true;
        show_location_icon = true;
        robot_following = false;
        setFullScreen();
    }else if(mode == "localization"){
        show_robot = true;
        show_global_path = false;
        show_local_path = false;
        show_lidar = true;
        show_object = true;
        show_object_box = true;
        show_location = false;
        show_location_icon = false;
        robot_following = true;
        pmap->annotation_edited = false;
        pmap->annot_edit_object = false;
        pmap->annot_edit_drawing = false;
        pmap->annot_edit_location = false;
        pmap->annot_edit_tline = false;
        setFullScreen();
    }else if(mode == "local_view"){
        show_robot = true;
        show_global_path = false;
        show_local_path = false;
        show_lidar = true;
        show_object = true;
        show_object_box = false;
        show_location = false;
        show_location_icon = true;
        robot_following = true;
        scale = 0.7;
        setZoomCenter(0,0);
    }else if(mode == "mapviewer"){
        show_robot = false;
        show_global_path = false;
        show_local_path = false;
        show_lidar = false;
        show_object = false;
        show_object_box = false;
        show_location = false;
        show_location_icon = false;
        robot_following = false;
        setFullScreen();
    }
    updateMap();
}

void MapView::setScreen(float s, int centerx, int centery){
    scale = s;
    setZoomCenter(centerx,centery);
    updateMap();
}

void MapView::initObject(){
    QString file_path = QDir::homePath() + "/maps/" + map_name + "/map_obs.png";;
    objects.clear();
    map_objecting.release();
    pmap->annot_edit_object = false;
    map_objecting = cv::imread(file_path.toStdString(),cv::IMREAD_GRAYSCALE);
    cv::flip(map_objecting,map_objecting,0);
    cv::rotate(map_objecting,map_objecting,cv::ROTATE_90_COUNTERCLOCKWISE);

    for(int i=0; i<pmap->objects.size(); i++){
        OBJECT temp;
        temp.type = pmap->objects[i].type;
        temp.is_rect = pmap->objects[i].is_rect;
        for(int j=0; j<pmap->objects[i].points.size(); j++){
            temp.points.push_back(setAxis(pmap->objects[i].points[j]));
        }
        objects.push_back(temp);
    }
}

void MapView::startDrawingTline(){
    flag_drawing = true;
    prev_pose.x = 0;
    prev_pose.y = 0;
}
void MapView::stopDrawingTline(){
    flag_drawing = false;

    int rad = pmap->robot_radius/pmap->gridwidth;
    for(int i=0; i<map_drawing.rows; i++){
        for(int j=0; j<map_drawing.cols; j++){
            if(map_drawing.at<uchar>(i,j) == 255){
                int kk=0;
                for(int k=0; k<rad; k++){
                    if(map_drawing.at<uchar>(i,j+k) == 255){
                        kk=j+k;
                    }
                }
                if(kk>0){
                    for(int k=j; k<kk; k++){
                        map_drawing.at<uchar>(i,k) = 255;
                    }
                }
            }
        }
    }
}

void MapView::initLocation(){
    //Read annotation.ini
    locations.clear();
    pmap->annot_edit_location = false;
    for(int i=0; i<pmap->locations.size(); i++){
        LOCATION temp;
        temp.group = pmap->locations[i].group;
        temp.call_id = pmap->locations[i].call_id;
        temp.number = pmap->locations[i].number;
        temp.type = pmap->locations[i].type;
        temp.name = pmap->locations[i].name;
        temp.point = setAxis(pmap->locations[i].point);
        temp.angle = setAxis(pmap->locations[i].angle);
//        qDebug() << "locations push " << temp.type << temp.number;
        locations.push_back(temp);
    }
}
void MapView::setFullScreen(){
    map_x = 0;
    map_y = 0;
    float max_ws = (float)pmap->width/map_width;
    float max_hs = (float)pmap->height/map_height;
    if(mode == "mapping"){
        max_ws = (float)mapping_size/map_width;
        max_hs = (float)mapping_size/map_height;
    }
    if(max_ws > max_hs){
        scale = max_hs;
    }else{
        scale = max_ws;
    }
//    qDebug() << "fullscreen" << object_name << mapping_size << scale;
}

void MapView::setMap(QObject *pixmapContainer){
    PixmapContainer *pc = qobject_cast<PixmapContainer*>(pixmapContainer);
    Q_ASSERT(pc);
    pixmap_map.pixmap = pc->pixmap;
    delete pc;
    update();
}
void MapView::moveMap(){
    if(mode == "mapping"){
        //Crop Show Rect
        cv::Mat source;
        if(pmap->map_mapping.rows > 0 && pmap->map_mapping.cols > 0){
            pmap->map_mapping(cv::Rect(map_x,map_y,map_width*scale,map_height*scale)).copyTo(source);
        }else{
            source = cv::Mat(1000,1000,CV_8U,cv::Scalar::all(0));
        }
        pixmap_map.pixmap = QPixmap::fromImage(mat_to_qimage_cpy(source));

        QPixmap temp_pixmap = map_current.copy(map_x*res,map_y*res,map_width*scale*res,map_height*scale*res);
        pixmap_current.pixmap = temp_pixmap;
        update();
    }else if(map_orin.cols > 0 && map_orin.rows > 0){
        //Crop Show Rect
        cv::Mat source;
        if(mode == "mapping" && pmap->map_mapping.rows > 0 && pmap->map_mapping.cols > 0){
            pmap->map_mapping(cv::Rect(map_x*1000/pmap->width,map_y*1000/mapping_size,map_width*scale*1000/mapping_size,map_height*scale*1000/mapping_size)).copyTo(source);
        }else{
            map_map(cv::Rect(map_x,map_y,map_width*scale,map_height*scale)).copyTo(source);
        }

        pixmap_map.pixmap = QPixmap::fromImage(mat_to_qimage_cpy(source));

        QPixmap temp_pixmap = map_object.copy(map_x*res,map_y*res,map_width*scale*res,map_height*scale*res);
        pixmap_object.pixmap = temp_pixmap;
        temp_pixmap = map_location.copy(map_x*res,map_y*res,map_width*scale*res,map_height*scale*res);
        pixmap_location.pixmap = temp_pixmap;
        temp_pixmap = map_current.copy(map_x*res,map_y*res,map_width*scale*res,map_height*scale*res);
        pixmap_current.pixmap = temp_pixmap;
        update();
    }
}
void MapView::updateMap(){
    initObject();
    initDrawing();
    initLocation();

    setMapDrawing();
    setMapMap();
    setMapCurrent();
    setMapLocation();
    setMapObject();
    update();
//    qDebug() << "updatemap done";
}
void MapView::setMapMap(){
    if(map_orin.cols > 0 && map_orin.rows > 0 && mode != "mapping"){

        //Rotation Map
        cv::Mat temp_orin;
        cv::Mat temp_drawing;
        cv::Mat temp_drawing_mask;
        cv::Mat temp_objecting;
        cv::Mat temp_tline;
        cv::Mat temp_velmap;
        if(rotate_angle != 0){
            cv::Mat rot = cv::getRotationMatrix2D(cv::Point2f(map_orin.cols/2, map_orin.rows/2),-rotate_angle,1.0);
            cv::warpAffine(map_orin,temp_orin,rot,map_orin.size(),cv::INTER_NEAREST);
            cv::warpAffine(map_drawing,temp_drawing,rot,map_drawing.size(),cv::INTER_NEAREST);
            cv::warpAffine(map_drawing_mask,temp_drawing_mask,rot,map_drawing_mask.size(),cv::INTER_NEAREST);
        }else{
            map_orin.copyTo(temp_orin);
            map_drawing.copyTo(temp_drawing);
            map_drawing_mask.copyTo(temp_drawing_mask);
        }
        map_objecting.copyTo(temp_objecting);
        map_tline.copyTo(temp_tline);
        map_velmap.copyTo(temp_velmap);

        if(temp_orin.channels() == 3)
            cv::cvtColor(temp_orin,temp_orin,cv::COLOR_BGR2BGRA);
        if(temp_tline.channels() == 3 && temp_tline.rows > 0)
            cv::cvtColor(temp_tline,temp_tline,cv::COLOR_BGR2BGRA);
        if(temp_orin.channels() == 1)
            cv::cvtColor(temp_orin,temp_orin,cv::COLOR_GRAY2BGRA);
        if(temp_tline.channels() == 1 && temp_tline.rows > 0)
            cv::cvtColor(temp_tline,temp_tline,cv::COLOR_GRAY2BGRA);
        if(temp_drawing.channels() == 3)
            cv::cvtColor(temp_drawing,temp_drawing,cv::COLOR_BGR2BGRA);
        if(temp_objecting.channels() == 3 && temp_objecting.rows > 0)
            cv::cvtColor(temp_objecting,temp_objecting,cv::COLOR_BGR2BGRA);
        if(temp_objecting.channels() == 1 && temp_objecting.rows > 0)
            cv::cvtColor(temp_objecting,temp_objecting,cv::COLOR_GRAY2BGRA);
        if(temp_drawing_mask.channels() == 3)
            cv::cvtColor(temp_drawing_mask,temp_drawing_mask,cv::COLOR_BGR2BGRA);
        if(temp_velmap.channels() == 1 && temp_velmap.rows > 0)
            cv::cvtColor(temp_velmap,temp_velmap,cv::COLOR_GRAY2BGRA);
        if(temp_velmap.channels() == 3 && temp_velmap.rows > 0)
            cv::cvtColor(temp_velmap,temp_velmap,cv::COLOR_BGR2BGRA);


        if(mode == "annot_tline" && temp_tline.cols > 0 && temp_tline.rows > 0){
            cv::multiply(cv::Scalar::all(1.0)-temp_drawing_mask,temp_tline,temp_tline);
            cv::add(temp_tline,temp_drawing,temp_tline);
            temp_orin.copyTo(map_map);
        }else if(mode == "annot_velmap" && temp_velmap.cols > 0 && temp_velmap.rows > 0){
            //qDebug() << temp_velmap.cols << temp_velmap.rows ;
            cv::multiply(cv::Scalar::all(1.0)-temp_drawing_mask,temp_velmap,temp_velmap);
            cv::add(temp_velmap,temp_drawing,temp_velmap);
            temp_orin.copyTo(map_map);
        }else{
            cv::multiply(cv::Scalar::all(1.0)-temp_drawing_mask,temp_orin,temp_orin);
            cv::add(temp_orin,temp_drawing,map_map);
        }

        if(mode == "annot_tline" && temp_tline.cols > 0 && temp_tline.rows > 0){
            cv::addWeighted(map_map,0.5,temp_tline,1,0,map_map);
        }else if(mode == "annot_object" && temp_objecting.cols > 0 && temp_objecting.rows > 0){
            if(show_object){
                cv::addWeighted(map_map,1,temp_objecting,0.7,0,map_map);
            }
        }else if(mode == "annot_velmap" && temp_velmap.cols > 0 && temp_velmap.rows > 0){
            cv::addWeighted(map_map,1,temp_velmap,0.5,0,map_map);
        }

        //Cur Brush View
        if(show_brush){
            if(cur_line_color == 255)
                cv::circle(map_map,curPoint,cur_line_width/2,cv::Scalar(0,0,0,255),1,8,0);
            else
                cv::circle(map_map,curPoint,cur_line_width/2,cv::Scalar(255,255,255,255),1,8,0);
        }
        //Crop Show Rect
        cv::Mat source;
        map_map(cv::Rect(map_x,map_y,map_width*scale,map_height*scale)).copyTo(source);
//        cv::imshow("source",source);
        pixmap_map.pixmap = QPixmap::fromImage(mat_to_qimage_cpy(source));
    }else{
        QPixmap blank(map_width,map_height);{
            QPainter painter(&blank);
            painter.fillRect(blank.rect(),"black");
        }
        pixmap_map.pixmap = blank;
    }
    update();
}

void MapView::setBoxPoint(int num, int x, int y){
    int min,max;
    if(x < 0) x = 0;
    if(y < 0) y = 0;

    if(x > pmap->width) x = pmap->width;
    if(y > pmap->height) y = pmap->height;
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
        cut_box[0] = orin_box[0] + (cv::Point2f(x,y) - orin_box[2]);
        cut_box[1] = orin_box[1] + (cv::Point2f(x,y) - orin_box[2]);
    }
    setMapCurrent();
}
int MapView::getPointBox(int x, int y){
    for(int i=0; i<2; i++){
        if(fabs(cut_box[i].x - x) < 50){
            if(fabs(cut_box[i].y - y) < 50){
                orin_box[0] = cut_box[0];
                orin_box[1] = cut_box[1];
                return i;
            }
        }
    }

    //detect line
    for(int i=0; i<2; i++){
        if(fabs(cut_box[i].x - x) < 30){
            if(y>cut_box[0].y && y<cut_box[1].y){
                orin_box[0] = cut_box[0];
                orin_box[1] = cut_box[1];
                orin_box[2] = cv::Point2f(x,y);
                return 3;
            }
        }
        if(fabs(cut_box[i].y - y) < 30){
            if(x>cut_box[0].x && x<cut_box[1].x){
                orin_box[0] = cut_box[0];
                orin_box[1] = cut_box[1];
                orin_box[2] = cv::Point2f(x,y);
                return 3;
            }
        }
    }
    return -1;
}
void MapView::cutMap(){
    cv::Mat map_edited_ui;
    map_orin.copyTo(map_edited_ui);
//    map_orin(cv::Rect(cut_box[0].x,cut_box[0].y,(cut_box[1].x-cut_box[0].x),(cut_box[1].y-cut_box[0].y))).copyTo(map_edited_ui);

    cv::Mat rot = cv::getRotationMatrix2D(cv::Point2f(map_edited_ui.cols/2, map_edited_ui.rows/2),-rotate_angle,1.0);
    rotate_angle = 0;
    cv::warpAffine(map_edited_ui,map_edited_ui,rot,map_edited_ui.size(),cv::INTER_NEAREST);


    cv::rotate(map_edited_ui,map_edited_ui,cv::ROTATE_90_CLOCKWISE);
    cv::flip(map_edited_ui,map_edited_ui,0);

    QString path = QDir::homePath() + "/maps/" + pmap->map_name + "/map_edited.png";
    plog->write("[Annotation] Map Size Cut : "+QString().sprintf("%d,%d ~ %d,%d",cut_box[0].x,cut_box[0].y,cut_box[1].x,cut_box[1].y));
    cv::imwrite(path.toStdString(),map_edited_ui);
//    updateMeta();

}
void MapView::reloadMap(){
//    initLocation();
//    initObject();
    updateMap();
}
void MapView::updateMeta(){
    QString path = QDir::homePath() + "/maps/" + pmap->map_name + "/map_meta.ini";
    QSettings setting(path, QSettings::IniFormat);
    pmap->width = cut_box[1].x-cut_box[0].x;
    pmap->height = cut_box[1].y-cut_box[0].y;
    pmap->origin[0] = (int)((cut_box[1].x-cut_box[0].x)/2.);
    pmap->origin[1] = (int)((cut_box[1].y-cut_box[0].y)/2.);
    setting.setValue("map_metadata/map_w",QString::number(cut_box[1].x-cut_box[0].x));
    setting.setValue("map_metadata/map_h",QString::number(cut_box[1].y-cut_box[0].y));
    setting.setValue("map_metadata/map_origin_u",QString::number(pmap->origin[0]));
    setting.setValue("map_metadata/map_origin_v",QString::number(pmap->origin[1]));
    plog->write("[Annotation] Update Meta.ini");
    reloadMap();
}
void MapView::setMapping(){
    cv::Mat source;
    if(scale < 10 && scale > -10){
//        qDebug() << map_x << map_y << scale << map_width << map_height << pmap->map_mapping.rows;
        pmap->map_mapping(cv::Rect(map_x,map_y,map_width*scale,map_height*scale)).copyTo(source);
        pixmap_map.pixmap = QPixmap::fromImage(mat_to_qimage_cpy(source));
        Q_ASSERT(!pixmap_map.pixmap.isNull());
        update();
    }else{
        qDebug() << "setMapping Fail" << scale;
    }
}
void MapView::setObjecting(){
    cv::Mat source;

    pmap->map_objecting(cv::Rect(map_x*1000/pmap->width,map_y*1000/pmap->width,map_width*scale*1000/pmap->width,map_height*scale*1000/pmap->width)).copyTo(source);
    pixmap_map.pixmap = QPixmap::fromImage(mat_to_qimage_cpy(source));
    Q_ASSERT(!pixmap_map.pixmap.isNull());
    update();
}

bool MapView::checkRobotCollision(){
    POSE temp = setAxis(probot->lastPose);
    return isCollision(temp.point.x, temp.point.y);
}
bool MapView::checkLocationCollision(int num){
    if(num > -1 && num < locations.size()){
        return isCollision(locations[num].point.x, locations[num].point.y);
    }
}
bool MapView::checkLocationCollision(){
    if(new_location_flag){
//        //qDebug() << "FUNCTION : " << new_location.point.x << new_location.point.y;
        return isCollision(new_location.point.x, new_location.point.y);
    }else{
        return checkRobotCollision();
    }
}
bool MapView::isCollision(int _x, int _y){
    if(map_cost.cols > 0 && map_cost.rows > 0){
        if(map_cost.at<uchar>(_y,_x) > 180 || map_orin.at<uchar>(_y,_x) == 0){
//            //qDebug() << _x << _y << " is collision!!" <<map_cost.at<uchar>(_x,_y)<<map_cost.at<uchar>(_y,_x);
            return true;
        }else{
//            //qDebug() << _x << _y << " is not collision!! " <<map_cost.at<uchar>(_x,_y)<<map_cost.at<uchar>(_y,_x);
            return false;
        }
    }else{
        return false;
    }
}

void MapView::setRawMap(QString filename){
    PixmapContainer *pc = new PixmapContainer();
    QString file_path = QDir::homePath() + "/maps/"+filename + "/map_raw.png";
    map_name = filename;
    map_orin.release();
    scale = 1;

    if(filename == "" || !QFile::exists(file_path)){
        QPixmap blank(map_width,map_height);{
            QPainter painter(&blank);
            painter.fillRect(blank.rect(),"black");
        }

        pc->pixmap = blank;
        Q_ASSERT(!pc->pixmap.isNull());
        QQmlEngine::setObjectOwnership(pc, QQmlEngine::JavaScriptOwnership);
    }else{
        map_orin = cv::imread(file_path.toStdString(),cv::IMREAD_GRAYSCALE);
        cv::flip(map_orin,map_orin,0);
        cv::rotate(map_orin,map_orin,cv::ROTATE_90_COUNTERCLOCKWISE);
        cv::resize(map_orin,map_orin,map_orin.size());
        plog->write("[MAPVIEW] SET RAW MAP " + object_name + ": "+file_path+QString().sprintf(" (size = %d x %d)",map_orin.rows,map_orin.cols));
    }
    delete pc;
    reloadMap();
}
void MapView::setCostMap(){
    QString file_path_edited = QDir::homePath() + "/maps/"+ map_name + "/map_edited.png";
    QString file_path_cost = QDir::homePath() + "/maps/"+ map_name + "/map_cost.png";
    QString file_path_obs = QDir::homePath() + "/maps/" + map_name + "/map_obs.png";

    map_cost.release();
    if(map_name == ""){
        return;
    }else{
        if(QFile::exists(file_path_cost)){
            map_cost = cv::imread(file_path_cost.toStdString(),cv::IMREAD_GRAYSCALE);
        }else if(QFile::exists(file_path_edited)){
            map_cost = cv::imread(file_path_edited.toStdString(),cv::IMREAD_GRAYSCALE);
        }else{
            map_cost = cv::Mat(map_orin.rows, map_orin.cols, CV_8UC4,cv::Scalar::all(0));
            return;
        }
        cv::flip(map_cost,map_cost,0);
        cv::rotate(map_cost,map_cost,cv::ROTATE_90_COUNTERCLOCKWISE);

        //Make Objecting Margin
        int robot_radius = std::ceil(pmap->robot_radius/pmap->gridwidth);
        if(QFile::exists(file_path_obs)){
            map_objecting.release();
            map_objecting = cv::imread(file_path_obs.toStdString(), cv::IMREAD_GRAYSCALE);
            cv::flip(map_objecting,map_objecting,0);
            cv::rotate(map_objecting,map_objecting,cv::ROTATE_90_COUNTERCLOCKWISE);



            for(int i = 0; i<map_objecting.rows; i++){
                for(int j=0; j<map_objecting.cols; j++){
                    if(map_objecting.ptr<uchar>(i)[j] > 100){
                        cv::circle(map_cost, cv::Point(j,i),robot_radius, cv::Scalar(190), -1, 8, 0);
                    }
                }
            }
        }else{
            map_objecting = cv::Mat(map_orin.rows, map_orin.cols, CV_8U,cv::Scalar::all(0));
//            //qDebug() << map_objecting.rows, map_objecting.cols;
        }

        //Make Object Margin
        std::vector<std::vector<cv::Point>> _poly2;
        for(int obj=0; obj<objects.size(); obj++){
            if(objects[obj].is_rect){
//                //qDebug() << objects.size() << objects[obj].points[0].x << objects[obj].points[0].y << objects[obj].points[2].x << objects[obj].points[2].y;
                for(int i=objects[obj].points[0].x; i<objects[obj].points[2].x; i++){
                    cv::circle(map_cost, cv::Point(i,objects[obj].points[0].y),robot_radius, cv::Scalar(190), -1, 8, 0);
                    cv::circle(map_cost, cv::Point(i,objects[obj].points[2].y),robot_radius, cv::Scalar(190), -1, 8, 0);
                }
                for(int i=objects[obj].points[2].x; i<objects[obj].points[0].x; i++){
                    cv::circle(map_cost, cv::Point(i,objects[obj].points[0].y),robot_radius, cv::Scalar(190), -1, 8, 0);
                    cv::circle(map_cost, cv::Point(i,objects[obj].points[2].y),robot_radius, cv::Scalar(190), -1, 8, 0);
                }
                for(int i=objects[obj].points[0].y; i<objects[obj].points[2].y; i++){
                    cv::circle(map_cost, cv::Point(objects[obj].points[0].x,i),robot_radius, cv::Scalar(190), -1, 8, 0);
                    cv::circle(map_cost, cv::Point(objects[obj].points[2].x,i),robot_radius, cv::Scalar(190), -1, 8, 0);
                }
                for(int i=objects[obj].points[2].y; i<objects[obj].points[0].y; i++){
                    cv::circle(map_cost, cv::Point(objects[obj].points[0].x,i),robot_radius, cv::Scalar(190), -1, 8, 0);
                    cv::circle(map_cost, cv::Point(objects[obj].points[2].x,i),robot_radius, cv::Scalar(190), -1, 8, 0);
                }
                cv::rectangle(map_cost, cv::Point(objects[obj].points[0].x, objects[obj].points[0].y),cv::Point(objects[obj].points[2].x, objects[obj].points[2].y),
                        cv::Scalar(255), -1, 8, 0);
            }else{
                std::vector<cv::Point> _poly;
                if(objects[obj].points.size() > 0){
                    _poly.push_back(cv::Point(objects[obj].points[0].x, objects[obj].points[0].y));
                    for(int i=1; i<objects[obj].points.size(); i++){
                        _poly.push_back(cv::Point(objects[obj].points[i].x, objects[obj].points[i].y));


                        cv::line(map_cost, objects[obj].points[i-1], objects[obj].points[i],cv::Scalar(190),robot_radius*2,8,0);

                    }
                    cv::line(map_cost, objects[obj].points[objects[obj].points.size()-1], objects[obj].points[0],cv::Scalar(190),robot_radius*2,8,0);
                    _poly2.push_back(_poly);
                    if(_poly2.size() > 0)
                        cv::fillPoly(map_cost, _poly2, cv::Scalar(255));
                }
            }

        }

        cv::addWeighted(map_cost, 1, map_objecting, 1, 0, map_cost);
        cv::Mat map_cost_ui;
        map_cost.copyTo(map_cost_ui);
        cv::rotate(map_cost_ui,map_cost_ui,cv::ROTATE_90_CLOCKWISE);
        cv::flip(map_cost_ui,map_cost_ui,0);
        QString path = QDir::homePath() + "/maps/" + pmap->map_name + "/map_cost_ui.png";
        plog->write("[MAPVIEW] SAVE MAP "+path);
        cv::imwrite(path.toStdString(),map_cost_ui);
    }
}
void MapView::setLocalizationMap(QString filename){
    PixmapContainer *pc = new PixmapContainer();
    QString edited_path = QDir::homePath() + "/maps/"+filename + "/map_edited.png";
    QString raw_path = QDir::homePath() + "/maps/"+filename + "/map_raw.png";
    map_name = filename;
    map_orin.release();
    if(QFile::exists(edited_path)){
        map_orin = cv::imread(edited_path.toStdString(),cv::IMREAD_GRAYSCALE);
        cv::flip(map_orin,map_orin,0);
        cv::rotate(map_orin,map_orin,cv::ROTATE_90_COUNTERCLOCKWISE);
        cv::resize(map_orin,map_orin,map_orin.size());
        plog->write("[MAPVIEW] SET EDITED MAP " + object_name + " : "+edited_path+QString().sprintf(" (size = %d x %d)",map_orin.rows,map_orin.cols));

    }else if(QFile::exists(raw_path)){
        map_orin = cv::imread(raw_path.toStdString(),cv::IMREAD_GRAYSCALE);
        cv::flip(map_orin,map_orin,0);
        cv::rotate(map_orin,map_orin,cv::ROTATE_90_COUNTERCLOCKWISE);
        cv::resize(map_orin,map_orin,map_orin.size());
        plog->write("[MAPVIEW] SET EDITED MAP " + object_name + " : "+raw_path+QString().sprintf(" (size = %d x %d)",map_orin.rows,map_orin.cols));

    }else{
        QPixmap blank(map_width,map_height);{
            QPainter painter(&blank);
            painter.fillRect(blank.rect(),"black");
        }
        pc->pixmap = blank;
        Q_ASSERT(!pc->pixmap.isNull());
        QQmlEngine::setObjectOwnership(pc, QQmlEngine::JavaScriptOwnership);
    }
    delete pc;
    reloadMap();
}
void MapView::setEditedMap(QString filename){
    PixmapContainer *pc = new PixmapContainer();
    QString file_path = QDir::homePath() + "/maps/"+filename + "/map_edited.png";
    map_name = filename;
    map_orin.release();
    scale = 1;


    if(filename == "" || !QFile::exists(file_path)){
        QPixmap blank(map_width,map_height);{
            QPainter painter(&blank);
            painter.fillRect(blank.rect(),"black");
        }
        pc->pixmap = blank;
        Q_ASSERT(!pc->pixmap.isNull());
        plog->write("[MAPVIEW] setEditedMap Failed : "+filename);
        QQmlEngine::setObjectOwnership(pc, QQmlEngine::JavaScriptOwnership);
    }else{
        map_orin = cv::imread(file_path.toStdString(),cv::IMREAD_GRAYSCALE);
        cv::flip(map_orin,map_orin,0);
        cv::rotate(map_orin,map_orin,cv::ROTATE_90_COUNTERCLOCKWISE);
        cv::resize(map_orin,map_orin,map_orin.size());
        plog->write("[MAPVIEW] SET EDITED MAP " + object_name + " : "+file_path+QString().sprintf(" (size = %d x %d)",map_orin.rows,map_orin.cols));
    }
    delete pc;
    reloadMap();
}
void MapView::setCostMap(QString filename){
    PixmapContainer *pc = new PixmapContainer();
    QString file_path = QDir::homePath() + "/maps/"+filename + "/map_cost_ui.png";
    map_name = filename;
    map_orin.release();

    if(filename == "" || !QFile::exists(file_path)){
        QPixmap blank(map_width,map_height);{
            QPainter painter(&blank);
            painter.fillRect(blank.rect(),"black");
        }

        pc->pixmap = blank;
        Q_ASSERT(!pc->pixmap.isNull());
        QQmlEngine::setObjectOwnership(pc, QQmlEngine::JavaScriptOwnership);
    }else{
        map_orin = cv::imread(file_path.toStdString(),cv::IMREAD_GRAYSCALE);
        map_cost = cv::imread(file_path.toStdString(),cv::IMREAD_GRAYSCALE);
        cv::flip(map_orin,map_orin,0);
        cv::rotate(map_orin,map_orin,cv::ROTATE_90_COUNTERCLOCKWISE);
        cv::flip(map_cost,map_cost,0);
        cv::rotate(map_cost,map_cost,cv::ROTATE_90_COUNTERCLOCKWISE);
        plog->write("[MAPVIEW] SET COST MAP " + object_name + ": "+file_path+QString().sprintf(" (size = %d x %d)",map_orin.rows,map_orin.cols));
    }
    delete pc;
    reloadMap();
}
void MapView::setObjectMap(QString filename){
    PixmapContainer *pc = new PixmapContainer();
    QString file_path = QDir::homePath() + "/maps/"+filename + "/map_edited.png";
//    QString file_path = QDir::homePath() + "/maps/"+filename + "/map_obs.png";
    map_name = filename;
    map_orin.release();

    if(filename == "" || !QFile::exists(file_path)){
        QPixmap blank(map_width,map_height);{
            QPainter painter(&blank);
            painter.fillRect(blank.rect(),"black");
        }

        pc->pixmap = blank;
        Q_ASSERT(!pc->pixmap.isNull());
        QQmlEngine::setObjectOwnership(pc, QQmlEngine::JavaScriptOwnership);
    }else{
        map_orin = cv::imread(file_path.toStdString(),cv::IMREAD_GRAYSCALE);
        cv::flip(map_orin,map_orin,0);
        cv::rotate(map_orin,map_orin,cv::ROTATE_90_COUNTERCLOCKWISE);
        plog->write("[MAPVIEW] SET COST MAP " + object_name + ": "+file_path+QString().sprintf(" (size = %d x %d)",map_orin.rows,map_orin.cols));
    }
    delete pc;
    reloadMap();
}
void MapView::setMapCurrent(){
    if(mode == "mapping"){
        map_current=QPixmap(1000*res,1000*res);
        map_current.fill(Qt::transparent);
        QPainter painter(&map_current);
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
         cv::Point2f pose;
        pose.x = -probot->curPose.point.y*1000/(pmap->mapping_width*pmap->mapping_gridwidth) + 1000/2;
        pose.y = -probot->curPose.point.x*1000/(pmap->mapping_width*pmap->mapping_gridwidth) + 1000/2;

        cv::Point2f temp;
        temp = setAxis(probot->curPose.point);

//        qDebug() << pose.y << temp.y << probot->curPose.point.x;
//        cv::Point2f pose = setAxisMapping(probot->curPose.point);

        float angle = setAxis(probot->curPose.angle);
        float distance = (pmap->robot_radius/mapping_grid)*2;
        float distance2 = distance*0.8;
        float th_dist = M_PI/8;
//        qDebug() << "mapping " << pose.x << pose.y  <<probot->curPose.angle<< angle << mapping_size << mapping_grid;

        float x =   (pose.x + distance    * qCos(angle))*res;
        float y =   (pose.y + distance    * qSin(angle))*res;
        float x1 =  (pose.x + distance2   * qCos(angle-th_dist))*res;
        float y1 =  (pose.y + distance2   * qSin(angle-th_dist))*res;
        float x2 =  (pose.x + distance2   * qCos(angle+th_dist))*res;
        float y2 =  (pose.y + distance2   * qSin(angle+th_dist))*res;

        float rad = pmap->robot_radius*2*res/mapping_grid;
        QPainterPath path;
        QPolygonF polygon;
        polygon << QPointF(x1,y1) << QPointF(x2,y2) << QPointF(x,y) << QPointF(x1,y1);
        path.addRoundedRect((pose.x-rad/2)*res,(pose.y-rad/2)*res,rad,rad,rad,rad);
        painter.setPen(QPen(QColor("white"),2));
        painter.fillPath(path,QBrush(QColor("red")));
        painter.drawPath(path);
        QPainterPath direction;
        direction.addPolygon(polygon);
        painter.fillPath(direction,QBrush(QColor("red")));

        for(int i=0; i<360; i++){
            painter.setPen(QPen(QColor("red"),1*res*scale));
            if(probot->lidar_data[i] > mapping_grid){
                float x = (pose.x + (probot->lidar_data[i]/mapping_grid)*cos((-M_PI*i)/180 + angle))*res;
                float y = (pose.y + (probot->lidar_data[i]/mapping_grid)*sin((-M_PI*i)/180 + angle))*res;
                painter.drawPoint((int)x,(int)y);
            }
        }
        QPixmap temp_pixmap = map_current.copy(map_x*res,map_y*res,map_width*scale*res,map_height*scale*res);
        pixmap_current.pixmap = temp_pixmap;
        update();
    }else if(map_orin.cols > 0 && map_orin.rows > 0){
        map_current=QPixmap(map_orin.cols*res,map_orin.rows*res);
        map_current.fill(Qt::transparent);
        QPainter painter(&map_current);
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.setRenderHint(QPainter::SmoothPixmapTransform, true);

        if(show_global_path){
//            //qDebug() << "global path";
            painter.setPen(QPen(QColor(hex_color_pink),2));
            cv::Point2f pose;
            cv::Point2f pose_next;
            float target_angle=0;
            for(int i=0; i<probot->curPath.size()-1; i++){
                pose = setAxis(probot->curPath[i].point);
                pose_next = setAxis(probot->curPath[i+1].point);
                target_angle = setAxis(probot->curPath[i+1].angle);
                painter.drawLine(pose.x,pose.y,pose_next.x,pose_next.y);
            }

            //target Pose
            if(probot->curPath.size() > 0){
                float distance = (pmap->robot_radius/pmap->gridwidth)*2;
                float distance2 = distance*0.8;
                float th_dist = M_PI/8;

                float x =   (pose_next.x - distance    * qSin(target_angle))*res;
                float y =   (pose_next.y - distance    * qCos(target_angle))*res;
                float x1 =  (pose_next.x - distance2   * qSin(target_angle-th_dist))*res;
                float y1 =  (pose_next.y - distance2   * qCos(target_angle-th_dist))*res;
                float x2 =  (pose_next.x - distance2   * qSin(target_angle+th_dist))*res;
                float y2 =  (pose_next.y - distance2   * qCos(target_angle+th_dist))*res;
                float rad = pmap->robot_radius*2*res/pmap->gridwidth;
                QPainterPath path;
                path.addRoundedRect((pose_next.x-rad/2)*res,(pose_next.y-rad/2)*res,rad,rad,rad,rad);
                painter.setPen(QPen(QColor(hex_color_pink),2));
                painter.fillPath(path,QBrush(QColor("white")));
                painter.drawPath(path);
                painter.drawLine(QLine(x1,y1,x,y));
                painter.drawLine(QLine(x2,y2,x,y));


                if(show_local_path){
//                    //qDebug() << "local path";
                    QPainterPath circles;
                    for(int i=0; i<probot->localpathSize; i++){
                        int rad = 2*res;
                        int xx = setAxis(probot->localPath[i].point).x*res - rad;
                        int yy = setAxis(probot->localPath[i].point).y*res - rad;
                        circles.addRoundedRect(xx,yy,rad*2,rad*2,rad,rad);
                        painter.fillPath(circles,Qt::white);
                    }
                }
            }
        }
        if(set_init_flag){
//            //qDebug() << "init" << probot->localization_state << mode;
            cv::Point2f pose = set_init_pose.point;
//            qDebug() << "DRAW INIT " << pose.x << pose.y;
            float angle = set_init_pose.angle;
            float distance = (pmap->robot_radius/pmap->gridwidth)*2;
            float distance2 = distance*0.8;
            float th_dist = M_PI/8;

            float x =   (pose.x + distance    * qCos(angle))*res;
            float y =   (pose.y + distance    * qSin(angle))*res;
            float x1 =  (pose.x + distance2   * qCos(angle-th_dist))*res;
            float y1 =  (pose.y + distance2   * qSin(angle-th_dist))*res;
            float x2 =  (pose.x + distance2   * qCos(angle+th_dist))*res;
            float y2 =  (pose.y + distance2   * qSin(angle+th_dist))*res;
            float rad = pmap->robot_radius*2*res/pmap->gridwidth;
            QPainterPath path;
            path.addRoundedRect((pose.x-rad/2)*res,(pose.y-rad/2)*res,rad,rad,rad,rad);
            painter.setPen(QPen(QColor("white"),2));
            painter.fillPath(path,QBrush(QColor(hex_color_green)));
            painter.drawPath(path);
            painter.drawLine(QLine(x1,y1,x,y));
            painter.drawLine(QLine(x2,y2,x,y));
        }

        if(show_lidar){
            cv::Point2f pose = setAxis(probot->curPose.point);
            float angle = setAxis(probot->curPose.angle);
            if(mode == "local_view"){
                painter.setPen(QPen(QColor(hex_color_blue),3));
                float x1, y1;
                int num;
                float limit = pmap->robot_radius;
                for(int i=0; i<360; i++){
                    if(probot->lidar_data[i] <limit){

                    }else{
                        x1 = (pose.x + (probot->lidar_data[i]/pmap->gridwidth)*cos((-M_PI*(i))/180 + angle))*res;
                        y1 = (pose.y + (probot->lidar_data[i]/pmap->gridwidth)*sin((-M_PI*(i))/180 + angle))*res;
                        num = i;
                        break;
                    }
                }
                for(int i=num+1; i<360; i++){
                    if(probot->lidar_data[i] <limit){

                    }else{
                        float x2 = (pose.x + (probot->lidar_data[i]/pmap->gridwidth)*cos((-M_PI*i)/180 + angle))*res;
                        float y2 = (pose.y + (probot->lidar_data[i]/pmap->gridwidth)*sin((-M_PI*i)/180 + angle))*res;
                        painter.drawLine((int)x1, (int)y1, (int)x2, (int)y2);
                        x1 = x2;
                        y1 = y2;
                    }
                }
            }else if(mode == "mapping"){
                pose.x = -probot->curPose.point.y*mapping_size/(pmap->mapping_width*pmap->mapping_gridwidth) + mapping_size/2;
                pose.y = -probot->curPose.point.x*mapping_size/(pmap->mapping_width*pmap->mapping_gridwidth) + mapping_size/2;

                cv::Point2f temp;
                temp = setAxis(probot->curPose.point);

                qDebug() << pose.y << temp.y << probot->curPose.point.x;
                angle = setAxis(probot->curPose.angle);
                painter.setPen(QPen(QColor(hex_color_blue),3));
                float x1, y1;
                int num;
                float limit = pmap->robot_radius;
                for(int i=0; i<360; i++){
                    if(probot->lidar_data[i] <limit){

                    }else{
                        x1 = (pose.x + (probot->lidar_data[i]/mapping_grid)*cos((-M_PI*(i))/180 + angle))*res;
                        y1 = (pose.y + (probot->lidar_data[i]/mapping_grid)*sin((-M_PI*(i))/180 + angle))*res;
                        num = i;
                        break;
                    }
                }
                for(int i=num+1; i<360; i++){
                    if(probot->lidar_data[i] <limit){

                    }else{
                        float x2 = (pose.x + (probot->lidar_data[i]/mapping_grid)*cos((-M_PI*i)/180 + angle))*res;
                        float y2 = (pose.y + (probot->lidar_data[i]/mapping_grid)*sin((-M_PI*i)/180 + angle))*res;
                        painter.drawLine((int)x1, (int)y1, (int)x2, (int)y2);
                        x1 = x2;
                        y1 = y2;
                    }
                }
            }else{
                for(int i=0; i<360; i++){
                    painter.setPen(QPen(QColor("red"),3));
                    if(probot->lidar_data[i] > pmap->gridwidth){
                        float x = (pose.x + (probot->lidar_data[i]/pmap->gridwidth)*cos((-M_PI*i)/180 + angle))*res;
                        float y = (pose.y + (probot->lidar_data[i]/pmap->gridwidth)*sin((-M_PI*i)/180 + angle))*res;
                        painter.drawPoint((int)x,(int)y);
                    }
                }
            }
        }
        if(show_robot){
//            qDebug() << "robot" << object_name << mode;
            if(mode == "mapping"){
                set_init_flag = false;
                cv::Point2f pose = setAxisMapping(probot->curPose.point);
                qDebug() << "robot mapping " << pose.x << pose.y;
                float angle = setAxis(probot->curPose.angle);
                float distance = (pmap->robot_radius/mapping_grid)*2;
                float distance2 = distance*0.8;
                float th_dist = M_PI/8;

                float x =   (pose.x + distance    * qCos(angle))*res;
                float y =   (pose.y + distance    * qSin(angle))*res;
                float x1 =  (pose.x + distance2   * qCos(angle-th_dist))*res;
                float y1 =  (pose.y + distance2   * qSin(angle-th_dist))*res;
                float x2 =  (pose.x + distance2   * qCos(angle+th_dist))*res;
                float y2 =  (pose.y + distance2   * qSin(angle+th_dist))*res;

                float rad = pmap->robot_radius*2*res/mapping_grid;
                QPainterPath path;
                QPolygonF polygon;
                polygon << QPointF(x1,y1) << QPointF(x2,y2) << QPointF(x,y) << QPointF(x1,y1);
                path.addRoundedRect((pose.x-rad/2)*res,(pose.y-rad/2)*res,rad,rad,rad,rad);
                painter.setPen(QPen(QColor("white"),2));
                painter.fillPath(path,QBrush(QColor("red")));
                painter.drawPath(path);
                QPainterPath direction;
                direction.addPolygon(polygon);
                painter.fillPath(direction,QBrush(QColor("red")));
            }else if(probot->localization_state == LOCAL_READY){
                set_init_flag = false;
                cv::Point2f pose = setAxis(probot->curPose.point);
                float angle = setAxis(probot->curPose.angle);
                float distance = (pmap->robot_radius/pmap->gridwidth)*2;
                float distance2 = distance*0.8;
                float th_dist = M_PI/8;

                float x =   (pose.x + distance    * qCos(angle))*res;
                float y =   (pose.y + distance    * qSin(angle))*res;
                float x1 =  (pose.x + distance2   * qCos(angle-th_dist))*res;
                float y1 =  (pose.y + distance2   * qSin(angle-th_dist))*res;
                float x2 =  (pose.x + distance2   * qCos(angle+th_dist))*res;
                float y2 =  (pose.y + distance2   * qSin(angle+th_dist))*res;

                float rad = pmap->robot_radius*2*res/pmap->gridwidth;
                QPainterPath path;
                QPolygonF polygon;
                polygon << QPointF(x1,y1) << QPointF(x2,y2) << QPointF(x,y) << QPointF(x1,y1);
                path.addRoundedRect((pose.x-rad/2)*res,(pose.y-rad/2)*res,rad,rad,rad,rad);
                painter.setPen(QPen(QColor("white"),2));
                painter.fillPath(path,QBrush(QColor("red")));
                painter.drawPath(path);
                QPainterPath direction;
                direction.addPolygon(polygon);
                painter.fillPath(direction,QBrush(QColor("red")));
            }
        }

        if(mode == "annot_rotate"){
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
        QPixmap temp_pixmap = map_current.copy(map_x*res,map_y*res,map_width*scale*res,map_height*scale*res);
        pixmap_current.pixmap = temp_pixmap;
        update();
    }

}
void MapView::initRotate(){
    rotate_angle = 0;
    pmap->map_rotate_angle = 0;
    if(map_orin.rows > 0){
        cut_box[0].x = 0;
        cut_box[0].y = 0;
        cut_box[1].x = pmap->width;
        cut_box[1].y = pmap->height;
    }else{
        cut_box[0].x = 0;
        cut_box[1].x = 0;
        cut_box[0].y = 0;
        cut_box[1].y = 0;
    }
    setMapCurrent();
    setMapMap();
}
void MapView::setMapDrawing(){
    initDrawing();
//    qDebug() << "setmapdrawing" << cur_line_color;
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
        }
    }


    //    if(mode == "annot_velmap")
//        cv::imshow("map_drawing555",map_map);
}
void MapView::setMapDrawingVel(){
    initVelmap(map_name,0);
    initDrawing();
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

}
void MapView::setMapObject(){
    if(map_orin.cols > 0 && map_orin.rows > 0){
        map_object=QPixmap(map_orin.cols*res,map_orin.rows*res);
        map_object.fill(Qt::transparent);
        QPainter painter(&map_object);
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.setRenderHint(QPainter::SmoothPixmapTransform, true);

        if(show_object_box){
            for(int obj=0; obj<objects.size(); obj++){
                QPainterPath path;
                if(objects[obj].is_rect){
                    if(select_object == obj){
                        painter.setPen(QPen(Qt::white,3));
                        path.addRect(QRectF(QPointF(objects[obj].points[0].x*res,objects[obj].points[0].y*res),QPointF(objects[obj].points[2].x*res,objects[obj].points[2].y*res)));
                        painter.fillPath(path,QBrush(QColor(10,24,50,100)));
                        painter.drawPath(path);

                        QPainterPath circles;
                        for(int j=0; j<objects[obj].points.size(); j++){
                            int rad = 2*res;
                            int xx = objects[obj].points[j].x*res - rad;
                            int yy = objects[obj].points[j].y*res - rad;
                            circles.addRoundedRect(xx,yy,rad*2,rad*2,rad,rad);
                            painter.fillPath(circles,Qt::white);
                        }
                    }else{
                        painter.setPen(QPen(Qt::white,1));
                        path.addRect(QRectF(QPointF(objects[obj].points[0].x*res,objects[obj].points[0].y*res),QPointF(objects[obj].points[2].x*res,objects[obj].points[2].y*res)));
                        painter.fillPath(path,QBrush(QColor(0,0,0,100)));
                        painter.drawPath(path);
                    }
                }else{
                    QPolygonF polygon;
                    for(int j=0; j<objects[obj].points.size(); j++){
                        polygon << QPointF(objects[obj].points[j].x*res, objects[obj].points[j].y*res);
                    }

                    path.addPolygon(polygon);

                    if(select_object == obj){
                        painter.setPen(QPen(Qt::white,3));
                        painter.fillPath(path,QBrush(QColor(10,24,50,100)));
                        painter.drawPolygon(polygon);
                        QPainterPath circles;
                        for(int j=0; j<objects[obj].points.size(); j++){
                            int rad = 2*res;
                            int xx = objects[obj].points[j].x*res - rad;
                            int yy = objects[obj].points[j].y*res - rad;
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
            if(new_object_flag){
                QPainterPath path;
//                //qDebug() << "new object drawing";
                if(new_object.is_rect){
                    path.addRect(QRectF(QPointF(new_object.points[0].x*res,new_object.points[0].y*res),QPointF(new_object.points[2].x*res,new_object.points[2].y*res)));
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
                    for(int j=0; j<new_object.points.size(); j++){
                        polygon << QPointF(new_object.points[j].x*res, new_object.points[j].y*res);
                    }
                    painter.setPen(QPen(Qt::white,2));
                    path.addPolygon(polygon);
                    painter.fillPath(path,QBrush(QColor(10,24,50,100)));
                    painter.drawPolygon(polygon);
                }
            }
        }
        QPixmap temp_pixmap = map_object.copy(map_x*res,map_y*res,map_width*scale*res,map_height*scale*res);
        pixmap_object.pixmap = temp_pixmap;
        update();
    }
}
void MapView::setMapLocation(){
    if(map_orin.cols > 0 && map_orin.rows > 0){
        map_location=QPixmap(map_orin.cols*res,map_orin.rows*res);
        map_location.fill(Qt::transparent);
        QPainter painter(&map_location);
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.setRenderHint(QPainter::SmoothPixmapTransform, true);

        if(show_location){
            for(int i=0; i<locations.size(); i++){
                float distance = (pmap->robot_radius/pmap->gridwidth)*2;
                float distance2 = distance*0.8;
                float th_dist = M_PI/8;

                float x =   (locations[i].point.x + distance    * qCos(locations[i].angle))*res;
                float y =   (locations[i].point.y + distance    * qSin(locations[i].angle))*res;
                float x1 =  (locations[i].point.x + distance2   * qCos(locations[i].angle-th_dist))*res;
                float y1 =  (locations[i].point.y + distance2   * qSin(locations[i].angle-th_dist))*res;
                float x2 =  (locations[i].point.x + distance2   * qCos(locations[i].angle+th_dist))*res;
                float y2 =  (locations[i].point.y + distance2   * qSin(locations[i].angle+th_dist))*res;

                float rad = pmap->robot_radius*2*res/pmap->gridwidth;
                QPainterPath path;
                if(select_location == i){
                    qDebug() << select_location << locations[i].type << locations[i].name;
                    if(locations[i].type == "Serving"){
                        path.addRoundedRect((locations[i].point.x-rad/2)*res,(locations[i].point.y-rad/2)*res,rad,rad,rad,rad);
                        painter.setPen(QPen(Qt::white,3));

                        if(isCollision(locations[i].point.x*res, locations[i].point.y*res)){
                            painter.fillPath(path,QBrush(QColor(hex_color_red)));
                        }else{
                            painter.fillPath(path,QBrush(QColor(hex_color_blue)));
                        }
                        painter.drawPath(path);
                        painter.drawLine(x1,y1,x,y);
                        painter.drawLine(x,y,x2,y2);
                    }else if(locations[i].type == "Resting"){
                    }else if(locations[i].type == "Charging"){
                    }
                }else{
                    if(locations[i].type == "Serving"){
                        path.addRoundedRect((locations[i].point.x-rad/2)*res,(locations[i].point.y-rad/2)*res,rad,rad,rad,rad);
                        painter.setPen(QPen(Qt::white,1));

                        if(isCollision(locations[i].point.x*res, locations[i].point.y*res)){
                            painter.fillPath(path,QBrush(QColor(hex_color_red)));
                        }else{
                            painter.fillPath(path,QBrush(QColor(hex_color_pink)));
                        }
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
                float distance = (pmap->robot_radius/pmap->gridwidth)*2;
                float distance2 = distance*0.8;
                float th_dist = M_PI/8;

                float x =   (new_location.point.x + distance    * qCos(new_location.angle))*res;
                float y =   (new_location.point.y + distance    * qSin(new_location.angle))*res;
                float x1 =  (new_location.point.x + distance2   * qCos(new_location.angle-th_dist))*res;
                float y1 =  (new_location.point.y + distance2   * qSin(new_location.angle-th_dist))*res;
                float x2 =  (new_location.point.x + distance2   * qCos(new_location.angle+th_dist))*res;
                float y2 =  (new_location.point.y + distance2   * qSin(new_location.angle+th_dist))*res;
                float rad = pmap->robot_radius*2*res/pmap->gridwidth;
                QPainterPath path;
                path.addRoundedRect((new_location.point.x-rad/2)*res,(new_location.point.y-rad/2)*res,rad,rad,rad,rad);
                painter.setPen(QPen(Qt::white,3));
//                //qDebug() << "NEW LOCATION CHECK COLLISION : " << new_location.point.x*res << new_location.point.y*res;
                if(isCollision(new_location.point.x*res, new_location.point.y*res)){
                    painter.fillPath(path,QBrush(QColor(hex_color_red)));
                }else{
                    painter.fillPath(path,QBrush(QColor(hex_color_blue)));
                }
                painter.drawPath(path);
                painter.drawLine(QLine(x1,y1,x,y));
                painter.drawLine(QLine(x2,y2,x,y));
            }
        }

        if(show_location_icon){
            for(int i=0; i<locations.size(); i++){
                float distance = (pmap->robot_radius/pmap->gridwidth)*2;
                float distance2 = distance*0.8;
                float th_dist = M_PI/8;
                float rad = pmap->robot_radius*2*res/pmap->gridwidth;

                float x =   (locations[i].point.x + distance    * qCos(locations[i].angle))*res;
                float y =   (locations[i].point.y + distance    * qSin(locations[i].angle))*res;
                float x1 =  (locations[i].point.x + distance2   * qCos(locations[i].angle-th_dist))*res;
                float y1 =  (locations[i].point.y + distance2   * qSin(locations[i].angle-th_dist))*res;
                float x2 =  (locations[i].point.x + distance2   * qCos(locations[i].angle+th_dist))*res;
                float y2 =  (locations[i].point.y + distance2   * qSin(locations[i].angle+th_dist))*res;

                QPainterPath path;
                if(locations[i].type == "Resting"){
                    if(select_location == i){
                        path.addRoundedRect((locations[i].point.x-rad/2)*res,(locations[i].point.y-rad/2)*res,rad,rad,rad,rad);

                        if(isCollision(locations[i].point.x*res, locations[i].point.y*res)){
                            painter.setPen(QPen(Qt::red,3));
                        }else{
                            painter.setPen(QPen(Qt::yellow,3));
                        }
                        painter.drawPath(path);
                        painter.drawLine(x1,y1,x,y);
                        painter.drawLine(x,y,x2,y2);
                        QImage image(":/icon/icon_home_1.png");
                        painter.drawImage(QRectF((locations[i].point.x-rad/2)*res,(locations[i].point.y-rad/2)*res,rad,rad),image,QRectF(0,0,image.width(),image.height()));
                    }else{
                        path.addRoundedRect((locations[i].point.x-rad/2)*res,(locations[i].point.y-rad/2)*res,rad,rad,rad,rad);

                        if(isCollision(locations[i].point.x*res, locations[i].point.y*res)){
                            painter.setPen(QPen(Qt::red,1));
                        }else{
                            painter.setPen(QPen(Qt::white,1));
                        }
                        painter.drawPath(path);
                        painter.drawLine(x1,y1,x,y);
                        painter.drawLine(x,y,x2,y2);
                        painter.drawPath(path);
                        QImage image(":/icon/icon_home_2.png");
                        painter.drawImage(QRectF((locations[i].point.x-rad/2)*res,(locations[i].point.y-rad/2)*res,rad,rad),image,QRectF(0,0,image.width(),image.height()));
                    }
                }else if(locations[i].type == "Charging"){
                    if(select_location == i){
                        path.addRoundedRect((locations[i].point.x-rad/2)*res,(locations[i].point.y-rad/2)*res,rad,rad,rad,rad);

                        if(isCollision(locations[i].point.x*res, locations[i].point.y*res)){
                            painter.setPen(QPen(Qt::red,3));
                        }else{
                            painter.setPen(QPen(Qt::yellow,3));
                        }
                        painter.drawPath(path);
                        painter.drawLine(x1,y1,x,y);
                        painter.drawLine(x,y,x2,y2);
                        QImage image(":/icon/icon_charge_1.png");
                        painter.drawImage(QRectF((locations[i].point.x-rad/2)*res,(locations[i].point.y-rad/2)*res,rad,rad),image,QRectF(0,0,image.width(),image.height()));
                    }else{
                        path.addRoundedRect((locations[i].point.x-rad/2)*res,(locations[i].point.y-rad/2)*res,rad,rad,rad,rad);

                        if(isCollision(locations[i].point.x*res, locations[i].point.y*res)){
                            painter.setPen(QPen(Qt::red,1));
                        }else{
                            painter.setPen(QPen(Qt::white,1));
                        }
                        painter.drawPath(path);
                        painter.drawLine(x1,y1,x,y);
                        painter.drawLine(x,y,x2,y2);
                        painter.drawPath(path);
                        QImage image(":/icon/icon_charge_2.png");
                        painter.drawImage(QRectF((locations[i].point.x-rad/2)*res,(locations[i].point.y-rad/2)*res,rad,rad),image,QRectF(0,0,image.width(),image.height()));
                    }
                }
            }
        }
        QPixmap temp_pixmap = map_location.copy(map_x*res,map_y*res,map_width*scale*res,map_height*scale*res);
        pixmap_location.pixmap = temp_pixmap;
        update();
    }
}

void MapView::removeLocation(int num){
    int count = 0;
    for(int i=0; i<pmap->locations.size(); i++){
        if(pmap->locations[i].type == "Serving"){
            if(count == num){
                pmap->locations.removeAt(i);
            }
            count++;
        }
    }
}
void MapView::setMapSize(int width, int height){
    map_width = width;
    map_height = height;
//    //qDebug() << "setMapSize " << object_name << map_width <<  map_height;
    if(robot_following){
        if(map_orin.cols > 0 && map_orin.rows > 0){
            setZoomCenter();
        }else{
            setFullScreen();
        }
    }
}

void MapView::setTableNumberAuto(){
    QMap<int,int> group_num;
    for(int i=0; i<pmap->locations.size(); i++){
        if(pmap->locations[i].type == "Serving"){
            if(group_num[pmap->locations[i].group] == 0){
                pmap->locations[i].number = 1;
                group_num[pmap->locations[i].group] = 2;
            }else{
                pmap->locations[i].number = group_num[pmap->locations[i].group]++;
            }
        }
    }
}

void MapView::zoomIn(int x, int y){
    prev_scale = scale;
    scale -= 0.05;
    if(scale < 0.1){
        scale = 0.1;
    }
    //qDebug() << "ZOOM IN " << scale;
    setZoomCenter(x,y);
    moveMap();
}

void MapView::zoomOut(int x, int y){
    prev_scale = scale;
    scale += 0.05;
    float max_ws = (float)pmap->width/map_width;
    float max_hs = (float)pmap->height/map_height;
    if(mode == "mapping"){
        max_ws = (float)mapping_size/map_width;
        max_hs = (float)mapping_size/map_height;
    }
    if(scale > max_ws){
        scale = max_ws;
    }else if(scale > max_hs){
        scale = max_hs;
    }
//    qDebug() << "ZOOM OUT " << mapping_size << scale;
    setZoomCenter(x,y);
    moveMap();
}

void MapView::scaledIn(int x, int y){
//    //qDebug() << "scaledIn " << pixmap_map.pixmap.width();
    pixmap_map.pixmap.scaled(pixmap_map.pixmap.width()*0.9,pixmap_map.pixmap.height()*0.9);
//    prev_scale = scale;
//    scale -= 0.05;
//    if(scale < 0.1){
//        scale = 0.1;
//    }
////    //qDebug() << "ZOOM IN " << scale;
//    setZoomCenter(x,y);
//    moveMap();
}

void MapView::scaledOut(int x, int y){
    pixmap_map.pixmap.scaled(pixmap_map.pixmap.size()*1.1);
//    prev_scale = scale;
//    scale += 0.05;
//    float max_ws = (float)map_orin.cols/map_width;
//    float max_hs = (float)map_orin.rows/map_height;
//    if(scale > max_ws){
//        scale = max_ws;
//    }else if(scale > max_hs){
//        scale = max_hs;
//    }
////    //qDebug() << "ZOOM OUT " << scale;
//    setZoomCenter(x,y);
//    moveMap();
}
void MapView::setInitPose(int x, int y, float th){
    set_init_flag = true;
    set_init_pose.point.x = x;
    set_init_pose.point.y = y;
    set_init_pose.angle = th;
//    //qDebug() << object_name << "SET INIT " << x << y << th;
    setMapCurrent();
}

void MapView::clearInitPose(){
    set_init_flag = false;
}

void MapView::rotateMap(int angle){
    dangle = angle - rotate_angle;
    rotate_angle = angle;
    pmap->map_rotate_angle = angle;
    setMapMap();
//    updateMap();
}

void MapView::rotateMapCW(){
    dangle = 1;
    rotate_angle++;
    pmap->map_rotate_angle = rotate_angle;
//    //qDebug() << "rotateCW " << rotate_angle;
    setMapMap();
}

void MapView::rotateMapCCW(){
    rotate_angle--;
    dangle = -1;
    pmap->map_rotate_angle = rotate_angle;
//    //qDebug() << "rotateCCW " << rotate_angle;
    setMapMap();

}

void MapView::move(int x, int y){
    setX(x);
    setY(y);
    moveMap();
//    updateMap();
}

void MapView::setX(int newx){
    if(newx < 0) newx=0;

    if(mode == "mapping"){
        if(mapping_size > 0 && newx > (mapping_size - map_width*scale)){
            newx = mapping_size-map_width*scale;
        }
    }else{
        if(pmap->width > 0 && newx > (pmap->width - map_width*scale)){
            newx = pmap->width-map_width*scale;
        }
    }

    map_x = newx;
}

void MapView::setY(int newy){
    if(newy < 0) newy=0;
    if(mode == "mapping"){
        if(mapping_size > 0 && newy > (mapping_size - map_height*scale)){
            newy = mapping_size-map_height*scale;
        }
    }else{
        if(pmap->height > 0 && newy > pmap->height - map_height*scale){
            newy = pmap->height-map_height*scale;
        }
    }
    map_y = newy;

}

void MapView::setZoomCenter(int x, int y){
    if(mode == "mapping"){
        if(robot_following && pmap->map_mapping.cols > 0 && pmap->map_mapping.rows > 0){
            cv::Point2f pose = setAxisMapping(probot->curPose.point);
            float newx = pose.x - map_width*scale/2;
            float newy = pose.y - map_height*scale/2;
            setX((int)newx);
            setY((int)newy);
        }else if(prev_scale != scale){
            float newx = map_x+x*prev_scale - scale*x;
            float newy = map_y+y*prev_scale - scale*y;
            setX((int)newx);
            setY((int)newy);
        }
    }else{
        if(robot_following && map_orin.cols > 0 && map_orin.rows > 0){
            cv::Point2f pose = setAxis(probot->curPose.point);
            float newx = pose.x - map_width*scale/2;
            float newy = pose.y - map_height*scale/2;
            setX((int)newx);
            setY((int)newy);
        }else if(prev_scale != scale){
            float newx = map_x+x*prev_scale - scale*x;
            float newy = map_y+y*prev_scale - scale*y;
            setX((int)newx);
            setY((int)newy);
        }
    }
    prev_scale = scale;
}

void MapView::setCenter(int centerx, int centery){
    int newx = centerx - (map_width/2)*scale;
    int newy = centery - (map_height/2)*scale;
//    //qDebug() << centerx << centery << newx << newy;
    setX(newx);
    setY(newy);
}

bool MapView::getDrawingFlag(){
    if(lines.size() > 0 || line.size() > 0){
        return true;
    }else{
        return false;
    }
}
bool MapView::getDrawingUndoFlag(){
    if(dot_trash.size() > 0 || lines_trash.size() > 0){
        return true;
    }else{
        return false;
    }
}

void MapView::startDrawingLine(int x, int y){
//    //qDebug() << "startDrawingLine";
    new_straight_flag = true;
    spline_dot.clear();
    straight[0].x = x;
    straight[0].y = y;
    straight[1].x = x;
    straight[1].y = y;
    setMapDrawing();
}
void MapView::startSpline(int x, int y){
    line.clear();
    spline_dot.clear();
    lines_trash.clear();
    curPoint.x = x;
    curPoint.y = y;
    line.push_back(curPoint);
    spline_dot.push_back(curPoint);
}
void MapView::endSpline(bool save){
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
    setMapDrawing();
    setMapMap();
}
void MapView::drawSpline(){
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

            for(double d = 0; d<=sum_d; d+= pmap->gridwidth){
                line.push_back(cv::Point2f(sx(d),sy(d)));
            }
//            //qDebug() <<"spline done" << line.size();
            for(int i=0; i<line.size()-1; i++){
                cv::line(map_drawing,line[i],line[i+1],cv::Scalar(cur_line_color,cur_line_color,cur_line_color,255),cur_line_width,8,0);
                cv::line(map_drawing_mask,line[i],line[i+1],cv::Scalar::all(255),cur_line_width,8,0);
            }

        }else{
//            //qDebug() <<"spline faile";
            line = spline_dot;
        }
//        setMapDrawing();
    }else{
        if(spline_dot.size() == 1){
//            //qDebug() <<"spline dot";
            line.push_back(spline_dot[0]);
            line.push_back(spline_dot[0]);
            cv::circle(map_drawing, spline_dot[0], 1, cv::Scalar(cur_line_color,cur_line_color,cur_line_color),-1,8,0);
            cv::circle(map_drawing_mask, spline_dot[0], 1, cv::Scalar::all(255),-1,8,0);
        }else if(spline_dot.size() == 2){
//            //qDebug() <<"spline line";
            line.push_back(spline_dot[0]);
            line.push_back(spline_dot[1]);
            cv::line(map_drawing,spline_dot[0],spline_dot[1],cv::Scalar(cur_line_color,cur_line_color,cur_line_color),cur_line_width,8,0);
            cv::line(map_drawing_mask,spline_dot[0],spline_dot[1],cv::Scalar::all(255),cur_line_width,8,0);
        }
    }
    setMapMap();
}
void MapView::addSpline(int x, int y){
    curPoint.x = x;
    curPoint.y = y;
    spline_dot.push_back(curPoint);
    dot_trash.clear();
    drawSpline();
}
void MapView::setDrawingLine(int x, int y){
//    //qDebug() << "setDrawingLine" << x << y;
    straight[1].x = x;
    straight[1].y = y;
//    initTline(map_name);
    initDrawing();
    setMapDrawing();
    setMapMap();
}
void MapView::stopDrawingLine(int x, int y){
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
    setMapMap();
}
void MapView::startDrawing(int x, int y){
//    //qDebug() << "startDrawing";
    line.clear();
    spline_dot.clear();
    lines_trash.clear();
    curPoint.x = x;
    curPoint.y = y;
    line.push_back(curPoint);
}

void MapView::drawTline(){
    cv::Point2f pose = setAxis(probot->curPose.point);
    if(prev_pose.x == 0 && prev_pose.y == 0){
        //pass
    }else{
        cv::line(map_drawing,prev_pose,pose,cv::Scalar::all(255),1,8,0);
    }
    prev_pose = pose;
}
void MapView::addLinePoint(int x, int y){
//    //qDebug() << "addlinepoint";
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
    }else{
        cv::line(map_drawing,line[line.size()-2],line[line.size()-1],cv::Scalar(cur_line_color,cur_line_color,cur_line_color,255),cur_line_width,8,0);
        cv::line(map_drawing_mask,line[line.size()-2],line[line.size()-1],cv::Scalar::all(255),cur_line_width,8,0);
    }

//    setMapDrawing();
    setMapMap();
}

void MapView::endDrawing(int x, int y){
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

            for(double d = 0; d<=sum_d; d+= pmap->gridwidth){
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
//    initTline(map_name);
    initDrawing();
    setMapDrawing();
    setMapMap();
}

void MapView::clearDrawing(){
    line.clear();
    lines.clear();
    spline_dot.clear();
    initVelmap(map_name,1);
    initTline(map_name);
    initDrawing();
    setMapDrawing();
    setMapMap();
}

void MapView::undoLine(){
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
        initVelmap(map_name,1);
        initTline(map_name);
        setMapDrawing();
        setMapMap();
    }
}

void MapView::saveMap(){
    cv::Mat temp_orin;
    cv::Mat temp_draw;
    cv::Mat temp_mask;
    cv::Mat map_merge;

    map_orin.copyTo(temp_orin);
    map_drawing.copyTo(temp_draw);
    map_drawing_mask.copyTo(temp_mask);

    if(temp_orin.channels() == 3)
        cv::cvtColor(temp_orin,temp_orin,cv::COLOR_BGR2GRAY);
    else if(temp_orin.channels() == 4)
        cv::cvtColor(temp_orin,temp_orin,cv::COLOR_BGRA2GRAY);
    if(temp_draw.channels() == 3)
        cv::cvtColor(temp_draw,temp_draw,cv::COLOR_BGR2GRAY);
    else if(temp_draw.channels() == 4)
        cv::cvtColor(temp_draw,temp_draw,cv::COLOR_BGRA2GRAY);
    if(temp_mask.channels() == 3)
        cv::cvtColor(temp_mask,temp_mask,cv::COLOR_BGR2GRAY);
    else if(temp_mask.channels() == 4)
        cv::cvtColor(temp_mask,temp_mask,cv::COLOR_BGRA2GRAY);

    cv::multiply(cv::Scalar::all(1.0)-temp_mask,temp_orin,temp_orin);
    cv::add(temp_orin,temp_draw,map_merge);

////    cv::cvtColor(temp_orin,temp_orin,cv::COLOR_GRAY2BGRA);
////    cv::addWeighted(temp_orin, 1, map_drawing, 1, 0, map_merge);

    cv::Mat rot = cv::getRotationMatrix2D(cv::Point2f(map_merge.cols/2, map_merge.rows/2),-rotate_angle,1.0);
    rotate_angle = 0;
    cv::Mat rotated;
    cv::warpAffine(map_merge,rotated,rot,map_merge.size(),cv::INTER_NEAREST);

    cv::rotate(rotated,rotated,cv::ROTATE_90_CLOCKWISE);
    cv::flip(rotated,rotated,0);

    QString path = QDir::homePath() + "/maps/" + pmap->map_name + "/map_edited.png";
    plog->write("[MAPVIEW] SAVE MAP "+path);
    cv::imwrite(path.toStdString(),rotated);
}

void MapView::saveVelmap(){
    setMapDrawingVel();

    cv::Mat temp_orin;
    cv::Mat temp_draw;
    cv::Mat temp_mask;
    cv::Mat map_merge;

    if(map_drawing.channels() == 4)
        cv::cvtColor(map_drawing,temp_draw,cv::COLOR_BGRA2GRAY);
    if(map_drawing_mask.channels() == 4)
        cv::cvtColor(map_drawing_mask,temp_mask,cv::COLOR_BGRA2GRAY);

    if(map_velmap.channels() == 4)
        cv::cvtColor(map_velmap,temp_orin,cv::COLOR_BGRA2GRAY);
    else if(map_velmap.channels() == 3)
        cv::cvtColor(map_velmap,temp_orin,cv::COLOR_BGR2GRAY);
    else if(map_velmap.channels() == 1)
        map_velmap.copyTo(temp_orin);


    cv::multiply(cv::Scalar::all(1.0)-temp_mask,temp_orin,temp_orin);
    cv::add(temp_orin,temp_draw,map_merge);

    cv::rotate(map_merge,map_merge,cv::ROTATE_90_CLOCKWISE);
    cv::flip(map_merge,map_merge,0);

    QString path = QDir::homePath() + "/maps/" + pmap->map_name + "/map_velocity.png";
    plog->write("[MAPVIEW] SAVE MAP "+path);
    cv::imwrite(path.toStdString(),map_merge);

    lines.clear();
    temp_rect.clear();
    initVelmap(map_name,1);
    setMapDrawing();
}
void MapView::saveTline(){
    cv::Mat temp_orin;
    cv::Mat temp_draw;
    cv::Mat temp_mask;
    cv::Mat map_merge;

    if(map_drawing.channels() == 4)
        cv::cvtColor(map_drawing,temp_draw,cv::COLOR_BGRA2GRAY);
    if(map_drawing_mask.channels() == 4)
        cv::cvtColor(map_drawing_mask,temp_mask,cv::COLOR_BGRA2GRAY);

    if(map_tline.channels() == 4)
        cv::cvtColor(map_tline,temp_orin,cv::COLOR_BGRA2GRAY);
    else if(map_tline.channels() == 1)
        map_tline.copyTo(temp_orin);
    cv::multiply(cv::Scalar::all(1.0)-temp_mask,temp_orin,temp_orin);
    cv::add(temp_orin,temp_draw,map_merge);

    cv::rotate(map_merge,map_merge,cv::ROTATE_90_CLOCKWISE);
    cv::flip(map_merge,map_merge,0);

    QString path = QDir::homePath() + "/maps/" + pmap->map_name + "/map_travel_line.png";
    plog->write("[MAPVIEW] SAVE MAP "+path);
    cv::imwrite(path.toStdString(),map_merge);
}

void MapView::redoLine(){
    if(dot_trash.size() > 0){
        //qDebug() << "redoLine(Spline)";
        spline_dot.push_back(dot_trash[dot_trash.size()-1]);
        dot_trash.pop_back();
        drawSpline();
    }else if(lines_trash.size() > 0){
        //qDebug() << "redoLine";
        lines.push_back(lines_trash[lines_trash.size()-1]);
        lines_trash.pop_back();
        initVelmap(map_name,1);
        initTline(map_name);
        setMapDrawing();
        setMapMap();
    }
}

int MapView::getObjectNum(int x, int y){
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

int MapView::getObjectPointNum(int x, int y){
    cv::Point2f pos = setAxisBack(cv::Point2f(x,y));
    int num = select_object;
    if(num < pmap->objects.size() && num > -1){
//        //qDebug() << "check obj" << num << pmap->objects[num].points.size();
        if(num != -1){
            for(int j=0; j<pmap->objects[num].points.size(); j++){
//                //qDebug() << pmap->objects[num].points[j].x << pmap->objects[num].points[j].y;
                if(fabs(pmap->objects[num].points[j].x - pos.x) < 0.2){
                    if(fabs(pmap->objects[num].points[j].y - pos.y) < 0.2){
                        //qDebug() << "Match Point !!" << num << j;
                        return j;
                    }
                }
            }
        }
    }
    //qDebug() << "can't find obj num : " << x << y;
    return -1;
}

void MapView::startDrawingRect(int x, int y){
    temp_rect.clear();
    temp_rect.push_back(cv::Point2f(x,y));
    temp_rect.push_back(cv::Point2f(x,y));
    temp_rect.push_back(cv::Point2f(x,y));
    temp_rect.push_back(cv::Point2f(x,y));
    setMapDrawing();
}
void MapView::setDrawingRect(int x, int y){
    if(temp_rect.size() > 3){
        cv::Point2f orin = temp_rect[0];
        temp_rect[1] = cv::Point2f(orin.x,y);
        temp_rect[2] = cv::Point2f(x,y);
        temp_rect[3] = cv::Point2f(x,orin.y);
    }
    setMapDrawing();
    setMapMap();
}
void MapView::endDrawingRect(){
    LINE temp_line;
    temp_line.points = temp_rect;
    temp_line.width = cur_line_width;
    temp_line.color = cur_line_color;
    temp_line.type = 1;
    lines.push_back(temp_line);
    temp_rect.clear();
}
void MapView::addObject(int x, int y){
    //qDebug() << "ADD OBJECT " << x << y;
    new_object_flag = true;
    new_object.is_rect = true;
    new_object.points.clear();
    new_object.points.push_back(cv::Point2f(x,y));
    new_object.points.push_back(cv::Point2f(x,y));
    new_object.points.push_back(cv::Point2f(x,y));
    new_object.points.push_back(cv::Point2f(x,y));
    setMapObject();
//    initObject();
//    setMapDrawing();
//    setMapMap();
}
void MapView::addObjectPoint(int x, int y){
    //qDebug() << "ADD OBJECT POINT " << x << y;
    new_object_flag = true;
    new_object.is_rect = false;
    new_object.points.push_back(cv::Point2f(x,y));
    setMapObject();
}
void MapView::setObject(int x, int y){
    //qDebug() << "SET OBJECT " << x << y;
    if(new_object.is_rect){
        if(new_object.points.size() > 3){
            cv::Point2f orin = new_object.points[0];
            new_object.points[1] = cv::Point2f(orin.x,y);
            new_object.points[2] = cv::Point2f(x,y);
            new_object.points[3] = cv::Point2f(x,orin.y);
        }
    }else{
        new_object.points[new_object.points.size() -1] = cv::Point2f(x,y);
    }
    setMapObject();
}
void MapView::editObjectStart(int x, int y){
    select_object_point = getObjectPointNum(x,y);
}
void MapView::editObject(int x, int y){
    int num = select_object;
    int point = select_object_point;
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
            plog->write("[ANNOTATION] editObject " + QString().sprintf("(%d, %d, %d, %d)",num,point,x,y));
        }else{
            if(point > -1 && point < pmap->objects[num].points.size()){
                cv::Point2f pos = setAxisBack(cv::Point2f(x,y));
                pmap->objects[num].points[point].x = pos.x;
                pmap->objects[num].points[point].y = pos.y;
                plog->write("[ANNOTATION] editObject "+ QString().sprintf("(%d, %d, %d, %d)",num,point,x,y));
            }else{
                plog->write("[ANNOTATION - ERROR] editObject " + QString().sprintf("(%d, %d, %d, %d)",num,point,x,y) + " but pose size error");
            }
        }

        pmap->annot_edit_object = true;
    }
    initObject();
    setMapObject();
}
void MapView::saveObject(QString type){
    OBJECT temp;
    if(new_object.is_rect){
        plog->write("[ANNOTATION] ADD Object "+type+" (Rect) : "+QString().sprintf("(%f,%f) ,(%f,%f)",new_object.points[0].x, new_object.points[0].y, new_object.points[2].x,new_object.points[2].y));
    }else{
        plog->write("[ANNOTATION] ADD Object "+type+" : "+QString().sprintf("%d",new_object.points.size()));
    }

    temp.type = type;
    temp.is_rect = new_object.is_rect;
    for(int i=0; i<new_object.points.size(); i++){
        temp.points.push_back(setAxisBack(new_object.points[i]));
    }
    pmap->annot_edit_object = true;
    pmap->objects.push_back(temp);
    clearObject();
    setMapObject();
}

void MapView::clearObject(){
    //qDebug() << "clearobject";
    new_object_flag = false;
    new_object.points.clear();
    pmap->annot_edit_object = false;
    select_object = -1;
    select_object_point = -1;
    initObject();
    setMapObject();
}

void MapView::undoObject(){
    new_object.points.pop_back();
    if(new_object.points.size() > 0){

    }else{
        new_object_flag = false;
    }
    initObject();
    setMapObject();
}

void MapView::selectObject(int num){
//    plog->write("[MAPVIEW] SELECT OBJECT : "+QString::number(num));
    select_object = num;
    setMapObject();
}

void MapView::selectLocation(int num, QString type){
//    plog->write("[MAPVIEW] SELECT LOCATION : "+QString::number(num));

    int charging_num = 0;
    int resting_num = 0;
    for(int i=0; i<locations.size(); i++){
        if(locations[i].type == "Charging"){
            charging_num++;
        }else if(locations[i].type == "Resting"){
            resting_num++;
        }
    }

    if(type == "Resting"){
        if(charging_num == 0) num--;
        if(resting_num > 0)
            select_location = num;
        else
            select_location = -1;
    }else if(type == "Serving"){
        if(charging_num == 0) num--;
        if(resting_num == 0) num--;
        select_location = num;
    }else if(type == "Charging"){
        if(charging_num > 0)
            select_location = num;
        else
            select_location = -1;
    }else{
        select_location = num;
    }
    select_location_type = type;
    qDebug() << select_location << type;
    setMapLocation();
}


void MapView::saveLocation(QString type, int groupnum, QString name){
    LOCATION temp;
    temp.type = type;
    temp.name = name;
    temp.group = groupnum;
    temp.call_id = "";
    temp.point = setAxisBack(new_location.point);
    temp.angle = setAxisBack(new_location.angle);

    if(type == "Charging"){
        temp.number = -10;
    }else if(type == "Resting"){
        temp.number = -5;
    }else{
        temp.number = getLocGroupNum(groupnum)+1;
    }

    if(pmap->location_groups.size() == 0){
        pmap->location_groups.push_back("DEFAULT");
    }


    if(type == "Serving"){
        plog->write("[ANNOTATION] ADD Location : "+type+","+name+","+QString().sprintf("%f,%f,%f,%d",temp.point.x, temp.point.y, temp.angle,temp.number));
        pmap->locations.push_back(temp);
        pmap->annot_edit_location = true;
    }else if(getLocationNum(type) > 0){
        for(int i=0; i<pmap->locations.size(); i++){
            if(pmap->locations[i].type == type){
                plog->write("[ANNOTATION] ADD Location(Overwrite): "+type+","+name+","+QString().sprintf("%f,%f,%f",temp.point.x, temp.point.y, temp.angle));
                pmap->locations[i] = temp;
                pmap->annot_edit_location = true;
                break;
            }
        }
    }else{
        plog->write("[ANNOTATION] ADD Location : "+type+","+name+","+QString().sprintf("%f,%f,%f",temp.point.x, temp.point.y, temp.angle));
        if(type == "Charging"){
            pmap->locations.insert(0,temp);
            pmap->annot_edit_location = true;
        }else if(type == "Resting"){
            pmap->locations.insert(getLocationNum("Charging"),temp);
            pmap->annot_edit_location = true;
        }
        pmap->annot_edit_location = true;
    }

//    int prev_group = 0;
//    int start_point = 0;
//    for(int i=0; i<pmap->locations.size(); i++){
//        if(pmap->locations[i].type == "Serving"){
//            if(prev_group==pmap->locations[i].group){

//            }else{
//                std::sort(pmap->locations.at(start_point),pmap->locations.at(i-1),sortLocation2());
//            }
//        }
//    }
    std::sort(pmap->locations.begin(),pmap->locations.end(),sortLocation2);
    pmap->annot_edit_location = true;


    //ini setting

    saveAnnotation(map_name);


    initLocation();
}

void MapView::saveAnnotation(QString filename){

    if(filename == ""){
        qDebug() << "file name set";
        filename = pmap->map_name;
        qDebug() << filename;
    }
    //기존 파일 백업
    QString backup = QDir::homePath()+"/maps/"+filename+"/annotation_backup.ini";
    QString origin = QDir::homePath()+"/maps/"+filename+"/annotation.ini";
    plog->write("[MAPVIEW] SAVE Annotation "+origin);
    if(QFile::exists(origin) == true){
        if(QFile::copy(origin, backup)){
            plog->write("[DEBUG] Copy annotation.ini to annotation_backup.ini");
        }else{
            plog->write("[DEBUG] Fail to copy annotation.ini to annotation_backup.ini");
        }
    }else{
        plog->write("[DEBUG] Fail to copy annotation.ini to annotation_backup.ini (No file found)");
    }
    //데이터 입력(로케이션)
    int other_num = 0;
    int resting_num = 0;
    int charging_num = 0;
    int serving_num = 0;
    int group_num[pmap->location_groups.size()];
    for(int i=0; i<pmap->location_groups.size(); i++)
        group_num[i] = 0;

    QString str_name;
    QSettings settings(origin, QSettings::IniFormat);
    settings.clear();
    for(int i=0; i<pmap->locations.size(); i++){
        if(pmap->locations[i].type == "Resting"){
            str_name = pmap->locations[i].name + QString().sprintf(",%f,%f,%f,%d",pmap->locations[i].point.x,pmap->locations[i].point.y,pmap->locations[i].angle,pmap->locations[i].number)+","+pmap->locations[i].call_id;
            settings.setValue("resting_locations/loc"+QString::number(resting_num),str_name);
            resting_num++;
        }else if(pmap->locations[i].type == "Other"){
            str_name = pmap->locations[i].name + QString().sprintf(",%f,%f,%f,%d",pmap->locations[i].point.x,pmap->locations[i].point.y,pmap->locations[i].angle,pmap->locations[i].number)+","+pmap->locations[i].call_id;
            settings.setValue("other_locations/loc"+QString::number(other_num),str_name);
            other_num++;
        }else if(pmap->locations[i].type == "Serving"){
            QString groupname = "serving_" + QString::number(pmap->locations[i].group);
            str_name = pmap->locations[i].name + QString().sprintf(",%f,%f,%f,%d",pmap->locations[i].point.x,pmap->locations[i].point.y,pmap->locations[i].angle,pmap->locations[i].number)+","+pmap->locations[i].call_id;
            settings.setValue(groupname+"/loc"+QString::number(group_num[pmap->locations[i].group]),str_name);
            group_num[pmap->locations[i].group]++;
        }else if(pmap->locations[i].type == "Charging"){
            str_name = pmap->locations[i].name + QString().sprintf(",%f,%f,%f,%d",pmap->locations[i].point.x,pmap->locations[i].point.y,pmap->locations[i].angle,pmap->locations[i].number)+","+pmap->locations[i].call_id;
            settings.setValue("charging_locations/loc"+QString::number(charging_num),str_name);
            charging_num++;
        }
    }
    settings.setValue("resting_locations/num",resting_num);
    settings.setValue("serving_locations/group",pmap->location_groups.size());
    settings.setValue("other_locations/num",other_num);
    settings.setValue("charging_locations/num",charging_num);

    for(int i=0; i<pmap->location_groups.size(); i++){
        settings.setValue("serving_"+QString::number(i)+"/name",pmap->location_groups[i]);
        settings.setValue("serving_"+QString::number(i)+"/num",getLocationGroupSize(i));
    }

    pmap->annotation_edited = false;
}

int MapView::getLocationGroupSize(int num){
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
void MapView::clearLocation(){
    new_location_flag = false;
    new_location.name = "";
    edit_location_flag = false;
    pmap->annot_edit_location = false;
    new_location.type = "";
    select_location = -1;
    initLocation();
    setMapLocation();
}

void MapView::addLocation(int x, int y, float th){
    new_location_flag = true;
    new_location.point = cv::Point2f(x,y);
    new_location.angle = th;
    initLocation();
    setMapLocation();
}
void MapView::addLocationCur(int x, int y, float th){
    new_location_flag = true;
    new_location.point = setAxis(cv::Point2f(x,y));
    new_location.angle = setAxis(th);
    //qDebug() << "add:ocationCur" << x << y << th << new_location.point.x << new_location.point.y << new_location.angle;
    initLocation();
    setMapLocation();
}
void MapView::setLocation(int x, int y, float th){
    int num = select_location;
    new_location_flag = false;
    if(pmap->locations.size() > num && num > -1){
        plog->write("[ANNOTATION] EDIT LOCATION "+QString().sprintf("%d : %f,%f,%f -> %f,%f,%f",num,pmap->locations[num].point.x, pmap->locations[num].point.y, pmap->locations[num].angle,setAxisBack(cv::Point2f(x,y)).x,setAxisBack(cv::Point2f(x,y)).y,setAxisBack(th)));
        pmap->locations[num].point = setAxisBack(cv::Point2f(x,y));
        pmap->locations[num].angle = setAxisBack(th);
//        //qDebug() << pmap->locations[num].angle;
        pmap->annot_edit_location = true;
    }
    initLocation();
    setMapLocation();
}

int MapView::getLocationNum(int x, int y){
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

int MapView::getLocationNum(QString type){
    int count = 0;
    for(int i=0; i<locations.size(); i++){
        if(locations[i].type == type)
            count++;
    }
    return count;
}
int MapView::getLocGroupNum(int num){
    int count = 0;
    for(int i=0; i<pmap->locations.size(); i++){
        if(pmap->locations[i].type == "Serving" && pmap->locations[i].group == num){
            count++;
        }
    }
    return count;
}

void MapView::editLocation(int x, int y, float th){
    int num = select_location;
    if(pmap->locations.size() > num && num > -1){
        if(!edit_location_flag){
            edit_location_flag = true;
            orin_location = pmap->locations[num];
        }
        //qDebug() <<"1            " <<  orin_location.point.x  << setAxisBack(cv::Point2f(x,y)).x;
        pmap->locations[num].point = setAxisBack(cv::Point2f(x,y));
        pmap->locations[num].angle = setAxisBack(th);
        pmap->annot_edit_location = true;
//        //qDebug() << pmap->locations[num].angle;
    }
    initLocation();
    setMapLocation();
}
void MapView::redoLocation(){
    int num = select_location;
    edit_location_flag = false;
    if(pmap->locations.size() > num && num > -1){
//        //qDebug() <<"1            " <<  orin_location.point.x  << locations[num].point.x;
        pmap->locations[num].point = orin_location.point;
        pmap->locations[num].angle = orin_location.angle;
        pmap->annot_edit_location = true;
//        //qDebug() << pmap->locations[num].angle;
    }
    initLocation();
    setMapLocation();
}

void MapView::editLocation(){
    int num = select_location;
    if(new_location_flag){
        if(pmap->locations.size() > num && num > -1){
            pmap->locations[num].point = setAxisBack(new_location.point);
            pmap->locations[num].angle = setAxisBack(new_location.angle);
            pmap->annot_edit_location = true;
        }
        edit_location_flag = false;
        initLocation();
        setMapLocation();
    }
}

void MapView::initVelmap(QString filename, int mode){
    QString file_path = QDir::homePath() + "/maps/" + filename + "/map_velocity.png";

    map_velmap.release();
    if(filename == "" || !QFile::exists(file_path)){
        plog->write("[MAPVIEW] INIT VELMAP NO FOUND : "+filename+", "+file_path);
        map_velmap = cv::Mat(map_orin.rows, map_orin.cols, CV_8UC4,cv::Scalar::all(0));
    }else{
        map_name = filename;
        map_velmap = cv::imread(file_path.toStdString(),cv::IMREAD_COLOR);
        cv::flip(map_velmap,map_velmap,0);
        cv::rotate(map_velmap,map_velmap,cv::ROTATE_90_COUNTERCLOCKWISE);

        if(mode == 1){
            for(int i=0; i<map_velmap.cols; i++){
                for(int j=0; j<map_velmap.rows; j++){
                    if(map_velmap.at<cv::Vec3b>(i,j)[0] == 100){
                        map_velmap.at<cv::Vec3b>(i,j)[0] = 80;
                        map_velmap.at<cv::Vec3b>(i,j)[1] = 200;
                        map_velmap.at<cv::Vec3b>(i,j)[2] = 255;
                    }else if(map_velmap.at<cv::Vec3b>(i,j)[0] == 200){
                        map_velmap.at<cv::Vec3b>(i,j)[0] = 77;
                        map_velmap.at<cv::Vec3b>(i,j)[1] = 88;
                        map_velmap.at<cv::Vec3b>(i,j)[2] = 231;
                    }
                }
            }
        }
//        cv::imshow("initvel",map_velmap);
//        plog->write("[MAPVIEW] INIT VELMAP SUCCESS : "+filename+", "+QString().sprintf("size(%d, %d)",map_velmap.rows,map_velmap.cols));
    }
}

void MapView::initTline(QString filename){
    QString file_path;

    file_path = QDir::homePath() + "/maps/" + filename + "/map_travel_line.png";

    map_tline.release();
    if(filename == "" || !QFile::exists(file_path)){
        plog->write("[MAPVIEW] INIT TRAVEL LINE ERROR : "+filename+", "+file_path);
        map_tline = cv::Mat(map_orin.rows, map_orin.cols, CV_8UC4,cv::Scalar::all(0));
    }else{
        map_name = filename;
        map_tline = cv::imread(file_path.toStdString(),cv::IMREAD_GRAYSCALE);
        cv::flip(map_tline,map_tline,0);
        cv::rotate(map_tline,map_tline,cv::ROTATE_90_COUNTERCLOCKWISE);
//        plog->write("[MAPVIEW] INIT TRAVEL LINE SUCCESS : "+filename+", "+QString().sprintf("size(%d, %d)",map_tline.rows,map_tline.cols));
    }
}

void MapView::setMapVelmap(){
    setMapDrawing();
    if(map_orin.cols > 0 && map_orin.rows > 0 ){
        if(mode == "annot_velmap" && map_velmap.cols > 0 && map_velmap.rows > 0){
            cv::Mat temp_orin;
            map_velmap(cv::Rect(map_x,map_y,map_width*scale,map_height*scale)).copyTo(temp_orin);
            pixmap_velmap.pixmap = QPixmap::fromImage(mat_to_qimage_cpy(temp_orin));
        }else{
            QPixmap pixmap(map_orin.cols*res,map_orin.rows*res);
            pixmap.fill(Qt::transparent);
        }
    }
    update();
}
void MapView::setMapTline(){
    setMapDrawing();
    if(map_orin.cols > 0 && map_orin.rows > 0){
        if(mode == "annot_tline" && map_tline.cols > 0 && map_tline.rows > 0){
            cv::Mat temp_orin;
            map_tline(cv::Rect(map_x,map_y,map_width*scale,map_height*scale)).copyTo(temp_orin);
            pixmap_tline.pixmap = QPixmap::fromImage(mat_to_qimage_cpy(temp_orin));
        }else{
            QPixmap pixmap(map_orin.cols*res,map_orin.rows*res);
            pixmap.fill(Qt::transparent);
        }
    }
    update();
}


void MapView::paint(QPainter *painter){
//    //qDebug() << width() << height();
    painter->drawPixmap(0,0,width(),height(),pixmap_map.pixmap);
    painter->drawPixmap(0,0,width(),height(),pixmap_object.pixmap);
    painter->drawPixmap(0,0,width(),height(),pixmap_location.pixmap);
    painter->drawPixmap(0,0,width(),height(),pixmap_tline.pixmap);
    painter->drawPixmap(0,0,width(),height(),pixmap_velmap.pixmap);
    painter->drawPixmap(0,0,width(),height(),pixmap_current.pixmap);
}

void MapView::setWindow(QQuickWindow *Window){
    mMain = Window;
}

QQuickWindow *MapView::getWindow()
{
    return mMain;
}

void MapView::setObject(QObject *object)
{
    mObject = object;
}

QObject *MapView::getObject()
{
    //rootobject를 리턴해준다.
    return mObject;
}
