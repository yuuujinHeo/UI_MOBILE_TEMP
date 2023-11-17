#ifndef MAPHANDLER_H
#define MAPHANDLER_H

#include <QTimer>
#include <QObject>
#include <QSettings>
#include "spline.h"
#include "GlobalHeader.h"

class MapHandler : public QObject
{
    Q_OBJECT
public:
    MapHandler();

    bool enable = false;
    QString tool = "move";
    QString mode = "none";
    QString object_name = "";
    QString map_name = "";

    int res = 1;

    cv::Point2f curPoint;

    bool exist_raw = false;
    bool exist_edited = false;
    bool exist_travelline = false;
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

    //캔버스(맵뷰어) 크기
    int canvas_width = 0;
    int canvas_height = 0;

    //------------file load--------------//
    Q_INVOKABLE void loadFile(QString name, QString type);
    void setMapOrin(QString type);
    //------------draw map--------------//
    Q_INVOKABLE void setMap();
    Q_INVOKABLE void moveMap();
    Q_INVOKABLE void setFullScreen();
    Q_INVOKABLE void setMapDrawing();

    //------------map variables--------------//
    Q_INVOKABLE void setName(QString name){object_name = name;}
    Q_INVOKABLE void setTool(QString name){tool = name;}
    Q_INVOKABLE QString getTool(){return tool;}
    Q_INVOKABLE void setMode(QString name);
    Q_INVOKABLE void setEnable(bool en){enable = en;}
    Q_INVOKABLE QString getMode(){return mode;}
    Q_INVOKABLE void setShowBrush(bool onoff){show_brush = onoff;}
    Q_INVOKABLE void setShowLidar(bool onoff){show_lidar = onoff;}
    Q_INVOKABLE void setShowLocation(bool onoff){
        show_location = onoff;
        show_location_icon = onoff;
        initLocation();
    }
    Q_INVOKABLE void setRobotFollowing(bool onoff){
        robot_following = onoff;
        setZoomCenter();
    }

    Q_INVOKABLE void setShowTravelline(bool onoff){
        show_travelline = onoff;
        setMap();
    }
    Q_INVOKABLE void setShowVelocitymap(bool onoff){
        show_velocitymap = onoff;
        setMap();
    }


    Q_INVOKABLE bool getshowLocation(){return show_location;}
    Q_INVOKABLE bool getRobotFollowing(){return robot_following;}
    Q_INVOKABLE bool getShowLidar(){return show_lidar;}


    bool show_travelline = false;
    bool show_velocitymap = false;

    bool show_brush = false;
    bool show_robot = false;
    bool show_global_path = false;
    bool show_local_path = false;
    bool show_lidar = false;
    bool show_location = false;
    bool show_location_icon = false;
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
    void drawTline();
    Q_INVOKABLE void startDrawingTline();
    Q_INVOKABLE void stopDrawingTline();
    Q_INVOKABLE bool getDrawingTline(){
        return flag_drawing;
    }

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

//    //---------------------------------------------------Drawing
    QVector<cv::Point2f> line;
    QVector<cv::Point2f> line_spline;
    QVector<cv::Point2f> spline_dot;
    QVector<cv::Point2f> dot_trash;
    QVector<cv::Point2f> temp_rect;
    QVector<LINE> lines;
    QVector<LINE> lines_trash;
    int cur_line_color=255;
    int cur_line_width=3;
    bool new_straight_flag = false;
    cv::Point2f straight[2];
    void initFileWidth(){
        file_width = map_orin.rows;
        initDrawing();
    }
    void initDrawing(){
        map_drawing = cv::Mat(file_width, file_width, CV_8UC4, cv::Scalar::all(0));
        map_drawing_mask = cv::Mat(file_width, file_width, CV_8UC4, cv::Scalar::all(0));
    }
    Q_INVOKABLE bool getDrawingFlag();
    Q_INVOKABLE bool getDrawingUndoFlag();
    Q_INVOKABLE void startDrawing(int x, int y);
    Q_INVOKABLE void addLinePoint(int x, int y);
    Q_INVOKABLE void endDrawing(int x, int y);

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
    QVector<LOCATION> locations;
    LOCATION new_location;
    int select_location = -1;
//    QString select_location_type = "";
    bool new_location_flag;
    bool edit_location_flag;
    LOCATION orin_location;

    Q_INVOKABLE void setSelectLocation(int num);
//    Q_INVOKABLE void saveLocation(QString type, int groupnum, QString name);
    Q_INVOKABLE void clearLocation();
//    Q_INVOKABLE void selectLocation(int num, QString type="");
    Q_INVOKABLE void addLocation(int x, int y,float th);
    Q_INVOKABLE void addLocationCur(int x, int y,float th);
    Q_INVOKABLE void setLocation(int x, int y, float th);
    Q_INVOKABLE void editLocation(int x, int y, float th);
    Q_INVOKABLE int getLocationNum(int x, int y);
    Q_INVOKABLE void removeLocation(int num);
    Q_INVOKABLE void setTableNumberAuto();
    Q_INVOKABLE int getLocationNum(QString type);
    Q_INVOKABLE int getLocGroupNum(int num);
    void initLocation();
    Q_INVOKABLE void saveMap();
    void setTline();
    Q_INVOKABLE void saveEditedMap();
    Q_INVOKABLE void saveTline();
    Q_INVOKABLE void saveTlineTemp();
    Q_INVOKABLE void saveVelmap();
    Q_INVOKABLE void setMapSize(int width, int height);
    Q_INVOKABLE void zoomIn(int x, int y);
    Q_INVOKABLE void zoomOut(int x, int y);
    Q_INVOKABLE void move(int x, int y);
    Q_INVOKABLE int getFileWidth(){return file_width;}
    Q_INVOKABLE int getX(){return draw_x;}
    Q_INVOKABLE int getY(){return draw_y;}
    Q_INVOKABLE float getScale(){return scale;}

    Q_INVOKABLE void setSize(int x, int y, float width);

    void updateMeta();
    Q_INVOKABLE bool getCutBoxFlag();

    void setX(int newx);
    void setY(int newy);
    void setZoomCenter(int x=0, int y=0);

    int getLocationGroupSize(int num);
//    Q_INVOKABLE void saveAnnotation(QString filename);



    ///Object
    ///
    bool draw_object_flag = false;
    QVector<OBJECT> objs;
    bool new_obj_flag = false;
    OBJECT new_obj;
    int select_obj = -1;
    int select_obj_point = -1;
    void initObject();
    void startDrawObject();
    void stopDrawObject();
    void saveDrawObject();
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
    //map_velocity
    cv::Mat file_velocity;
    //map_object
    cv::Mat file_object;

    //현재 사용중인 map(raw | edited)
    cv::Mat map_orin;
    cv::Mat map_drawing;
    cv::Mat map_drawing_mask;

    QPixmap map;
    QPixmap map_obs;
    QPixmap final_map;

    void update();
private slots:
    void onTimer();
private:
    QTimer *timer;
};

#endif // MAPHANDLER_H
