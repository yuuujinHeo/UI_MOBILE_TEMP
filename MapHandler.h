#ifndef MAPHANDLER_H
#define MAPHANDLER_H

#include <QTimer>
#include <QObject>
#include <QSettings>
#include "spline.h"
#include "GlobalHeader.h"
#include <QKeyEvent>

class MapHandler : public QObject
{
    Q_OBJECT
public:
    MapHandler();
    struct NODE
    {
        QString id;
        QString attrib; // Route, Charging, Resting, Cleaning, Serving
        cv::Vec3d pose;
        std::vector<QString> linked;

        NODE()
        {
            id = "";
            attrib = "";
            pose = cv::Vec3d(0,0,0);
            linked.clear();
        }

        NODE(const NODE& p)
        {
            id = p.id;
            attrib = p.attrib;
            pose = p.pose;
            linked = p.linked;
        }

        NODE& operator=(const NODE& p)
        {
            id = p.id;
            attrib = p.attrib;
            pose = p.pose;
            linked = p.linked;
            return *this;
        }
    };

    struct CLICK_INFO
    {
        cv::Vec3d pose;

        QString cur_node;
        QString pre_node;
        QString sel_node;
    };
    CLICK_INFO click_info;
    bool enable = false;
    QString tool = "move";
    QString mode = "none";
    QString map_name = "";

    int res = 1;

    cv::Point2f curPoint;

    bool exist_raw = false;
    bool exist_edited = false;
    bool exist_travelline = false;
    bool exist_travelline_ui = false;
    bool exist_velmap = false;

    //맵 파일 크기
    int file_width = 0;
    float grid_width = 0;
    float scale = 1;
    float prev_scale = 1;
    int rotate_angle = 0;

    //맵 표시범위
    int draw_x = 0;
    int draw_y = 0;
    int draw_width = 0;

    float avoid_width = 0.7;

    //캔버스(맵뷰어) 크기
    int canvas_width = 0;
    int canvas_height = 0;


    //------------file load--------------//
    Q_INVOKABLE void loadFile(QString name="", QString type="");
    void setMapOrin(QString type);
    //------------draw map--------------//
    Q_INVOKABLE void setMap();
    Q_INVOKABLE void setMapTest();
    Q_INVOKABLE void setMapLayer();
    Q_INVOKABLE void setFullScreen();
    Q_INVOKABLE void setMapDrawing();

    void setObjPose();
    //------------map variables--------------//
    Q_INVOKABLE void setTool(QString name){tool = name;setMap();}
    Q_INVOKABLE QString getTool(){return tool;}
    Q_INVOKABLE void setMode(QString name);
    Q_INVOKABLE void setEnable(bool en){enable = en;}
    Q_INVOKABLE QString getMode(){return mode;}
    Q_INVOKABLE void setShowBrush(bool onoff){show_brush = onoff;}
    Q_INVOKABLE void setShowLidar(bool onoff){
        show_lidar = onoff;
        setMap();
    }
    Q_INVOKABLE void setShowLocation(bool onoff){
        show_location = onoff;
        show_location_icon = onoff;
        show_location_detail=onoff;
        initLocation();
        setMap();
    }
    Q_INVOKABLE void setShowLocationDetail(bool onoff){
        show_location = onoff;
        show_location_detail = onoff;
        //show_location_icon = onoff;
        //initLocation();
        //setMap();
    }
    Q_INVOKABLE void setRobotFollowing(bool onoff){
        robot_following = onoff;
        if(mode == "annot_drawing" || mode == "annot_velmap" || mode == "annot_location" || mode == "annot_tline" || mode == "annot_tline2"){
            show_robot = robot_following;
        }

        if(onoff){
            cv::Point2f robot_pose;
            robot_pose = setAxis(probot->curPose.point);
            setZoomCenter(robot_pose.x, robot_pose.y);
        }
    }

    Q_INVOKABLE void setShowObject(bool onoff){
        show_object = onoff;
        setMap();
    }
    Q_INVOKABLE void setShowAvoidMap(bool onoff){
        show_avoid = onoff;
        setMap();
    }
    Q_INVOKABLE void setShowRobot(bool onoff){
//        qDebug() << "setShowRobot " << onoff;
        show_robot = onoff;
        setMapLayer();
    }
    Q_INVOKABLE void setShowNode(bool onoff){
        show_node = onoff;
        setMapLayer();
    }

    Q_INVOKABLE void setShowTravelline(bool onoff){
        show_travelline = onoff;
        setMap();
    }

    Q_INVOKABLE void setShowVelocitymap(bool onoff){
        show_velocitymap = onoff;
        setMap();
    }
    Q_INVOKABLE void setShowName(bool onoff){
        show_name = onoff;
        setMapLayer();
    }
    Q_INVOKABLE void setShowEdge(bool onoff){
        show_edge = onoff;
        setMapLayer();
    }
    void autoTline();

    Q_INVOKABLE bool getshowLocation(){return show_location;}
    Q_INVOKABLE bool getshowLocationDetail(){return show_location_detail;}
    Q_INVOKABLE bool getRobotFollowing(){return robot_following;}
    Q_INVOKABLE bool getShowLidar(){return show_lidar;}
    Q_INVOKABLE bool getShowNode(){return show_node;}
    Q_INVOKABLE bool getShowName(){return show_name;}
    Q_INVOKABLE bool getShowEdge(){return show_edge;}
    Q_INVOKABLE bool getShowVelmap(){return show_velocitymap;}
    Q_INVOKABLE bool getShowAvoid(){return show_avoid;}
    Q_INVOKABLE bool getShowObject(){return show_object;}
    Q_INVOKABLE bool getShowTline(){return show_travelline;}
    bool show_travelline = false;
    bool show_velocitymap = false;
    bool show_number = true;
    bool show_brush = false;
    bool show_robot = false;
    bool show_name = false;
    bool show_edge = false;
    bool show_node = false;
    bool show_global_path = false;
    bool show_local_path = false;
    bool show_lidar = false;
    bool show_avoid = false;
    bool show_location = false;
    bool show_location_icon = false;
    bool show_location_detail = false;
    bool show_object = false;
    bool robot_following = false;

    //------------localization--------------//
    POSE set_init_pose;
    bool set_init_flag = false;
    bool set_init_pressed = false;
    Q_INVOKABLE void setInitPose(int x, int y, float th);
    Q_INVOKABLE void clearInitPose();
    Q_INVOKABLE void setInitFlag(bool onoff){
        set_init_pressed = onoff;
    }

    //------------drawing--------------//
    bool flag_drawing=false;
    cv::Point2f prev_pose;
    int select_box;
    void drawTline();
    Q_INVOKABLE void startDrawingTline();
    Q_INVOKABLE void stopDrawingTline();
    Q_INVOKABLE bool getDrawingTline(){
        return flag_drawing;
    }


    //-------------topo-------------------//
    std::map<QString, std::unique_ptr<NODE>> nodes;
    QString first_group_name = "Default";
    POSE tempnode;
    cv::Point2f init_tempnode;
    QString getNode(int x, int y);
    void tempNodeInit(int x, int y);
    void tempNodeSet(int x, int y);
    QString auto_node_name(QString attrib);
    void addNode(QString id, QString attrib);
    void addNode(QString name, QString group, QString attrib);
    void editNode();
    void editNode(QString id, int x, int y, float th);
    void editNode(QString attr);
    void deleteNode();
    void linkNode();
    void alignXNode();
    void alignYNode();
    void alignTHNode();
    void loadAnnotation();
    void saveAnnotation();
    void saveNode();
    void loadNode();
    bool isExistNode(QString type);

    //---------------test----------------//
    void pressed(QString tool, int x, int y);
    void double_pressed(QString tool, int x1, int y1, int x2, int y2);
    void moved(QString tool, int x, int y);
    void double_moved(QString tool, int x1, int y1, int x2, int y2);
    void released(QString tool, int x, int y);
    void double_released(QString tool, int x1, int y1, int x2, int y2);
    bool shift_move = false;
    void releaseShift(){shift_move = false;}
    void pressShift(){shift_move = true;}

    float zoom_init_distance;
    cv::Point2f move_init_pose;

    bool press_release = false;
    cv::Point2f ruler_init_point;
    QList<cv::Point2f> ruler_point;
    Q_INVOKABLE void setRulerInit(int x, int y);
    Q_INVOKABLE void setRulerEnd(int x, int y);
    Q_INVOKABLE void setRulerPoint(int x, int y);


    bool new_straight_flag = false;
    cv::Point2f straight_init_point;
    QList<cv::Point2f> straight_point;
    Q_INVOKABLE void setStraightInit(int x, int y);
    Q_INVOKABLE void setStraightEnd(int x, int y);
    Q_INVOKABLE void setStraightPoint(int x, int y);
    Q_INVOKABLE void saveStraight();



    //------------cut / rotate--------------//
    cv::Point2f cut_box[2];
    cv::Point2f orin_box[3];
    Q_INVOKABLE void setBoxPoint(int num, int x, int y);
    Q_INVOKABLE int getPointBox(int x, int y);
    Q_INVOKABLE void saveRotateMap();
    Q_INVOKABLE void initRotate();
    Q_INVOKABLE void rotateMap(int angle);
    Q_INVOKABLE void rotateMapCW();
    Q_INVOKABLE void rotateMapCCW();

    Q_INVOKABLE void saveObjectPNG();
    Q_INVOKABLE void saveObsAreaPNG();

    float calculateAngle(cv::Point2f p1, cv::Point2f p2){
        if(p1 == p2){
            return 0;
        }else{
            float angle = atan2((p2.y-p1.y),p2.x-p1.x);
            return angle*180/M_PI;
        }
    }
    float calculateDistance(cv::Point2f p1, cv::Point2f p2){
        float dist = sqrt(pow(p1.x - p2.x,2) + pow(p1.y - p2.y, 2));
        return dist;
    }
//    //---------------------------------------------------Drawing
    QList<cv::Point2f> line;
    QList<cv::Point2f> line_spline;
    QList<cv::Point2f> spline_dot;
    QList<cv::Point2f> dot_trash;
    QList<cv::Point2f> temp_rect;
    QList<LINE> lines;
    QList<LINE> lines_trash;
    int cur_line_color=255;
    int cur_line_width=3;
    void initFileWidth(){
        file_width = map_orin.rows;
        initDrawing();
    }
    void initDrawing(){
        qDebug() << "initDrawing";
        map_drawing = cv::Mat(file_width, file_width, CV_8UC4, cv::Scalar::all(0));
        map_drawing_tline = cv::Mat(file_width, file_width, CV_8UC4, cv::Scalar::all(0));
        map_drawing_mask = cv::Mat(file_width, file_width, CV_8UC4, cv::Scalar::all(0));
    }
    Q_INVOKABLE bool getDrawingFlag();
    Q_INVOKABLE bool getDrawingUndoFlag();
    Q_INVOKABLE void startDrawing(int x, int y);
    Q_INVOKABLE void addLinePoint(int x, int y);
    Q_INVOKABLE void endDrawing(int x, int y);
    Q_INVOKABLE void startErase2(int x, int y);
    Q_INVOKABLE void addErase2(int x, int y);
    Q_INVOKABLE void endErase2(int x, int y);


    Q_INVOKABLE void startDrawingRect(int x, int y);
    Q_INVOKABLE void setDrawingRect(int x, int y);
    Q_INVOKABLE void endDrawingRect();

    Q_INVOKABLE void clearDrawing();
    Q_INVOKABLE void undoLine();
    Q_INVOKABLE void redoLine();
    Q_INVOKABLE void startSpline(int x, int y);
    Q_INVOKABLE void addSpline(int x, int y);
    Q_INVOKABLE void drawSpline();
    Q_INVOKABLE void endSpline(bool save);
    Q_INVOKABLE void startDrawingLine(int x, int y);
    Q_INVOKABLE void setDrawingLine(int x, int y);
    Q_INVOKABLE void stopDrawingLine(int x, int y);
    Q_INVOKABLE void setLineColor(int color){
        cur_line_color = color;
        qDebug() << "setlinecolor " << cur_line_color;
    }
    Q_INVOKABLE void setLineWidth(int width){
        cur_line_width = width;
    }

    //    //---------------------------------------------------Location
    QList<LOCATION> charging_locations;
    QList<LOCATION> resting_locations;
    QList<LOCATION> cleaning_locations;
    QList<LOCATION> init_locations;
    QList<LOCATION> serving_locations;
    LOCATION new_location;
    int select_serving = -1;
    int select_resting = -1;
    int select_cleaning = -1;
    int select_charging = -1;
    int select_init = -1;
//    QString select_location_type = "";
    bool new_location_flag;
    bool edit_location_flag;
    LOCATION orin_location;

    Q_INVOKABLE void setTravellineIssue(int count, int num);
    Q_INVOKABLE void setSelectServing(int num);
    Q_INVOKABLE void setSelectCharging(int num);
    Q_INVOKABLE void setSelectResting(int num);
    Q_INVOKABLE void setSelectCleaning(int num);
    Q_INVOKABLE void setSelectInit(int num);
//    Q_INVOKABLE void saveLocation(QString type, int groupnum, QString name);
    Q_INVOKABLE void clearLocation();
//    Q_INVOKABLE void selectLocation(int num, QString type="");
    Q_INVOKABLE void addLocation(int x, int y,float th);
    Q_INVOKABLE void addLocationCur(int x, int y,float th);
    Q_INVOKABLE void setLocation(int x, int y, float th);
    Q_INVOKABLE void editLocation(int x, int y, float th);
    Q_INVOKABLE int getLocationNum(int x, int y);

    Q_INVOKABLE void removeLocation(QString type, int num);
    Q_INVOKABLE void setTableNumberAuto();
    Q_INVOKABLE int getLocationNum(QString type);
    Q_INVOKABLE int getLocGroupNum(int num);
    void initLocation();
    Q_INVOKABLE void saveMap();
    Q_INVOKABLE void saveEditedMap();
    Q_INVOKABLE void saveTline();
    Q_INVOKABLE void saveTlineTemp();
    Q_INVOKABLE void saveVelmap();
    Q_INVOKABLE void setMapSize(int width, int height);
    Q_INVOKABLE void zoomIn(int x, int y, float dist);
    Q_INVOKABLE void zoomOut(int x, int y, float dist);
    Q_INVOKABLE void move(int x, int y);
    Q_INVOKABLE int getFileWidth(){return file_width;}
    Q_INVOKABLE int getX(){return draw_x;}
    Q_INVOKABLE int getY(){return draw_y;}
    Q_INVOKABLE float getScale(){return scale;}

    Q_INVOKABLE void setSize(int x, int y, float width);

    Q_INVOKABLE bool getCutBoxFlag();

    void updateMeta();
    void setX(int newx);
    void setY(int newy);
    void setZoomCenter(int x=0, int y=0);

    int getLocationGroupSize(int num);
//    Q_INVOKABLE void saveAnnotation(QString filename);


    //travelline check
    int travelline_issue[5] = {-1,};


    ///Object
    QList<OBJECT> objs;
    bool new_obj_flag = false;
    OBJECT new_obj;
    int select_obj = -1;
    int select_obj_point = -1;
    void initObject();
    int getObjectNum(int x, int y);
    int getObjectPointNum(int x, int y);
    void addObject(int x, int y);
    void addObjectPoint(int x, int y);
    void setObject(int x, int y);
    void editObjectStart(int x, int y);
    void editObject(int x, int y);
    void saveObject();
    void clearObject();
    void clearObjectAll();
    void selectObject(int num);
    void undoObject();
    void removeObject(int num);
    void redoObject();
    bool getObjectFlag();

private:
    //직접 불러오는거
    //map_raw.png
    cv::Mat file_raw;
    //map_edited.png
    cv::Mat file_edited;
    //map_travelline
    cv::Mat file_travelline;
    //map_travelline_ui
    cv::Mat file_travelline_ui;
    //map_velocity
    cv::Mat file_velocity;
    //map_object
    cv::Mat file_object;
    //map_avoid
    cv::Mat file_avoid;

    //현재 사용중인 map(raw | edited)
    cv::Mat map_orin;
    cv::Mat map_tlines;
    cv::Mat map_objects;
    cv::Mat map_layers;
    cv::Mat map_drawing_tline;
    cv::Mat map_drawing;
    cv::Mat map_drawing_mask;

    QImage map_image;
    QPixmap map;
    QPixmap map_tline;
    QPixmap map_object;
    QPixmap map_layer;
    QPixmap map_obs;
    QPixmap final_map;

    void update();
private slots:
    void onTimer();
private:
    QTimer *timer;
protected:
    void keyPressEvent(QKeyEvent *ev);
    void keyReleaseEvent(QKeyEvent *ev);
};

#endif // MAPHANDLER_H
