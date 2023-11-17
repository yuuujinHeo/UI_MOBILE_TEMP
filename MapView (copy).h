#ifndef MAPVIEW_H
#define MAPVIEW_H

#include <QTimer>
#include <QObject>
#include <QSettings>
#include "MapHeader.h"
#include "spline.h"
#include "GlobalHeader.h"

class MapView : public QQuickPaintedItem
{
    Q_OBJECT
public:
    MapView(QQuickItem *parent = nullptr);

    bool enable = false;
    QString tool = "move";
    QString mode = "none";
    QString object_name = "";
    QString map_name = "";

    int res = 1;

    cv::Point2f curPoint;

    Q_INVOKABLE bool checkRobotCollision();
    Q_INVOKABLE bool checkLocationCollision();
    Q_INVOKABLE bool isCollision(int x, int y);
    Q_INVOKABLE bool checkLocationCollision(int num);
    Q_INVOKABLE void setEnable(bool en){enable = en;}
    Q_INVOKABLE void setName(QString name){object_name = name;}
    Q_INVOKABLE void setTool(QString name){tool = name;}
    Q_INVOKABLE QString getTool(){return tool;}
    Q_INVOKABLE void setMode(QString name);
    Q_INVOKABLE QString getMode(){return mode;}
    Q_INVOKABLE void setlidarView(bool onoff){show_lidar = onoff; updateMap();}
    Q_INVOKABLE void setobjectView(bool onoff){show_object = onoff;updateMap();}
    Q_INVOKABLE void setobjectBoxView(bool onoff){show_object_box = onoff;updateMap();}
    Q_INVOKABLE void setLocationView(bool onoff){show_location = onoff;updateMap();}
    Q_INVOKABLE void setRobotFollowing(bool onoff){
        robot_following = onoff;
        setZoomCenter();
        updateMap();
    }
    Q_INVOKABLE bool getlocationView(){return show_location;}
    Q_INVOKABLE bool getRobotFollowing(){return robot_following;}
    Q_INVOKABLE bool getlidarView(){return show_lidar;}
    Q_INVOKABLE bool getobjectView(){return show_object;}
    Q_INVOKABLE bool getobjectBoxView(){return show_object_box;}

    bool show_robot = false;
    bool show_global_path = false;
    bool show_local_path = false;
    bool show_lidar = false;
    bool show_object_box = false;
    bool show_object = false;
    bool show_location = false;
    bool show_location_icon = false;
    bool robot_following = false;

    //--------------------------------------------------Map Generation
    Q_INVOKABLE void setMap(QObject *pixmapContainer);
    Q_INVOKABLE void updateMap();
    Q_INVOKABLE void moveMap();
    Q_INVOKABLE void reloadMap();
    Q_INVOKABLE void setMapping();
    Q_INVOKABLE void setObjecting();
    Q_INVOKABLE void setRawMap(QString filename);
    Q_INVOKABLE void setEditedMap(QString filename);
    Q_INVOKABLE void setCostMap();
    Q_INVOKABLE void setCostMap(QString filename);
    Q_INVOKABLE void setObjectMap(QString filename);
    Q_INVOKABLE void setFullScreen();
    Q_INVOKABLE void setLocalizationMap(QString filename);
    void setMapCurrent();
    void setMapDrawing();
    void setMapDrawingVel();
    void setMapObject();
    void setMapMap();
    void setMapLocation();

    void updateMeta();

    //---------------------------------------------------Mapping, Localization
    POSE set_init_pose;
    bool set_init_flag = false;
    Q_INVOKABLE void setInitPose(int x, int y, float th);
    Q_INVOKABLE void clearInitPose();

    bool flag_drawing=false;
    Q_INVOKABLE void startDrawingTline();
    Q_INVOKABLE void stopDrawingTline();
    Q_INVOKABLE bool getDrawingTline(){
        return flag_drawing;
    }

    //---------------------------------------------------Rotation
    int rotate_angle = 0;
    int dangle = 0;
    Q_INVOKABLE void rotateMap(int angle);
    Q_INVOKABLE void rotateMapCW();
    Q_INVOKABLE void rotateMapCCW();
    cv::Point2f cut_box[2];
    cv::Point2f orin_box[3];
    Q_INVOKABLE void setBoxPoint(int num, int x, int y);
    Q_INVOKABLE int getPointBox(int x, int y);
    Q_INVOKABLE void cutMap();
    Q_INVOKABLE void initRotate();
    //---------------------------------------------------Drawing

    void initDrawing(){
//        qDebug() << "init drawing";
        map_drawing = cv::Mat(map_orin.rows, map_orin.cols, CV_8UC4, cv::Scalar::all(0));
        map_drawing_mask = cv::Mat(map_orin.rows, map_orin.cols, CV_8UC4, cv::Scalar::all(0));
    }
    QVector<cv::Point2f> line;
    QVector<cv::Point2f> line_spline;
    QVector<cv::Point2f> spline_dot;
    QVector<cv::Point2f> dot_trash;
    QVector<cv::Point2f> temp_rect;
    QVector<LINE> lines;
    QVector<LINE> lines_trash;
    int cur_line_color=255;
    int cur_line_width=3;
    bool show_brush = false;
    bool new_straight_flag = false;
    cv::Point2f straight[2];
    Q_INVOKABLE void showBrush(bool onoff){show_brush = onoff;}
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
    Q_INVOKABLE void setLineColor(int color){cur_line_color = color;}
    Q_INVOKABLE void setLineWidth(int width){
        cur_line_width = width;
    }

    cv::Point2f prev_pose;
    void drawTline();
    //---------------------------------------------------Object
    void initObject();
    QVector<OBJECT> objects;
    bool new_object_flag = false;
    OBJECT new_object;
    int select_object = -1;
    int select_object_point = -1;
    Q_INVOKABLE int getObjectNum(int x, int y);
    Q_INVOKABLE int getObjectPointNum(int x, int y);
    Q_INVOKABLE void addObject(int x, int y);
    Q_INVOKABLE void addObjectPoint(int x, int y);
    Q_INVOKABLE void setObject(int x, int y);
    Q_INVOKABLE bool getObjectFlag(){return new_object_flag;}
    Q_INVOKABLE void editObjectStart(int x, int y);
    Q_INVOKABLE void editObject(int x, int y);
    Q_INVOKABLE void saveObject(QString type);
    Q_INVOKABLE void clearObject();
    Q_INVOKABLE void undoObject();
    Q_INVOKABLE void selectObject(int num);


    Q_INVOKABLE void setScreen(float s, int centerx, int centery);

    //---------------------------------------------------Location
    QVector<LOCATION> locations;
    LOCATION new_location;
    int select_location = -1;
    QString select_location_type = "";
    bool new_location_flag;
    bool edit_location_flag;
    LOCATION orin_location;

    Q_INVOKABLE bool getLocationFlag(){return new_location_flag;}
    Q_INVOKABLE void saveLocation(QString type, int groupnum, QString name);
    Q_INVOKABLE void clearLocation();
    Q_INVOKABLE void selectLocation(int num, QString type="");
    Q_INVOKABLE void addLocation(int x, int y,float th);
    Q_INVOKABLE void addLocationCur(int x, int y,float th);
    Q_INVOKABLE void setLocation(int x, int y, float th);
    Q_INVOKABLE void editLocation(int x, int y, float th);
    Q_INVOKABLE void editLocation();
    Q_INVOKABLE void redoLocation();
    Q_INVOKABLE int getLocationNum(int x, int y);
    Q_INVOKABLE void removeLocation(int num);
    Q_INVOKABLE void setTableNumberAuto();
    //---------------------------------------------------Travel Line
    bool is_edited_tline = false;
    Q_INVOKABLE void initTline(QString filename);
    Q_INVOKABLE void setTlineMode(bool is_edit){is_edited_tline = is_edit;}
    Q_INVOKABLE void setMapTline();

    //---------------------------------------------------Velocity Map
    Q_INVOKABLE void initVelmap(QString filename, int mode);
    Q_INVOKABLE void setMapVelmap();

    Q_INVOKABLE int getLocationNum(QString type);
    Q_INVOKABLE int getLocGroupNum(int num);
    //---------------------------------------------------Save
    void initLocation();
    Q_INVOKABLE void saveMap();
    Q_INVOKABLE void saveTline();
    Q_INVOKABLE void saveVelmap();
    //---------------------------------------------------Map Scale, Move
    int map_width;
    int map_height;
    int mapping_size;
    float mapping_grid;
    int map_x;
    int map_y;
    float prev_scale;
    float scale = 1;
    Q_INVOKABLE void setMapSize(int width, int height);
    Q_INVOKABLE void zoomIn(int x, int y);
    Q_INVOKABLE void zoomOut(int x, int y);
    Q_INVOKABLE void scaledIn(int x, int y);
    Q_INVOKABLE void scaledOut(int x, int y);
    Q_INVOKABLE void move(int x, int y);
    Q_INVOKABLE int getX(){return map_x;}
    Q_INVOKABLE int getY(){return map_y;}
    Q_INVOKABLE float getScale(){return scale;}
    void setX(int newx);
    void setY(int newy);
    void setCenter(int centerx, int centery);
    void setZoomCenter(int x=0, int y=0);

    int getLocationGroupSize(int num);
    void setSetting(QString name, QString value){
        QString ini_path = QDir::homePath()+"/robot_config.ini";
        QSettings setting(ini_path, QSettings::IniFormat);
        setting.setValue(name,value);
        plog->write("[SETTING] SET "+name+" VALUE TO "+value);
    }
    void setAnnotation(QString filename, QString name, QString value){
        QString ini_path = QDir::homePath()+"/maps/"+filename+"/annotation.ini";
        QSettings setting(ini_path, QSettings::IniFormat);
        setting.setValue(name,value);
        plog->write("[SETTING] SET "+name+" VALUE TO "+value);
    }
    Q_INVOKABLE void saveAnnotation(QString filename);
protected:
    virtual void paint(QPainter *painter) Q_DECL_OVERRIDE;

private:
    PixmapContainer pixmap_map;
    PixmapContainer pixmap_object;
    PixmapContainer pixmap_location;
    PixmapContainer pixmap_tline;
    PixmapContainer pixmap_velmap;
    PixmapContainer pixmap_current;
    cv::Mat map_orin;
    cv::Mat map_tline;
    cv::Mat map_velmap;
    cv::Mat map_cost;
    cv::Mat map_objecting;
    cv::Mat map_map;
    cv::Mat map_drawing;
    cv::Mat map_drawing_mask;
    QPixmap map_object;
    QPixmap map_location;
    QPixmap map_current;

private slots:
    void onTimer();
private:
    QQuickWindow *mMain;
    QTimer *timer;
    QObject *mObject = nullptr;
    //---------------------------------------------------Window
    void setWindow(QQuickWindow* Window);
    QQuickWindow *getWindow();
    void setObject(QObject* object);
    QObject* getObject();
};


#endif // MAPVIEW_H
