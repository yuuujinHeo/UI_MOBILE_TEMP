#ifndef SUPERVISOR_H
#define SUPERVISOR_H

#include <QObject>
#include <QTimer>
#include <QThread>
#include <QQuickWindow>
#include "GlobalHeader.h"
#include <QSoundEffect>
#include "CallbellHandler.h"
#include "ZIPHandler.h"
#include "python_wrapper.h"
#include "IPCHandler.h"
#include "Cmd_checker.h"
#include <QMediaPlaylist>
#include "ServerHandler.h"
#include <QMediaPlayer>
#include "TTSHandler.h"
#include "MapHandler.h"
#include <libusb-1.0/libusb.h>


#define MOTOR_RUN(x)            ((x)&0x01)
#define MOTOR_MOD_ERROR(x)      ((x>>1)&0x01)
#define MOTOR_JAM_ERROR(x)      ((x>>2)&0x01)
#define MOTOR_CUR_ERROR(x)      ((x>>3)&0x01)
#define MOTOR_BIG_ERROR(x)      ((x>>4)&0x01)
#define MOTOR_INP_ERROR(x)      ((x>>5)&0x01)
#define MOTOR_PS_ERROR(x)       ((x>>6)&0x01)
#define MOTOR_COL_ERROR(x)      ((x>>7)&0x01)

enum{
    PATROL_NONE = 0,
    PATROL_RANDOM,
    PATROL_SEQUENCE,
    PATROL_NEW
};

class Supervisor : public QObject
{
    Q_OBJECT
public:
    explicit Supervisor(QObject *parent = nullptr);
    ~Supervisor();
public:
    ////*********************************************  CLASS   ***************************************************////
    ST_MAP map;
    ST_ROBOT robot;
    ST_SETTING setting;

    ServerHandler *server;
    ZIPHandler *zip;
    MapHandler *maph;
    CMD_CHECKER *checker;
    CallbellHandler *call;
    IPCHandler *ipc;
    TTSHandler *tts;
    QProcess *slam_process;


    ////*********************************************  State  *********************************************////
    bool need_init = true;
    bool debug_mode = false;

    //state
    QString curUiState();
    Q_INVOKABLE void passInit();
    Q_INVOKABLE void stateInit();
    Q_INVOKABLE void stateMoving();
    Q_INVOKABLE void setUiState(int state){
        ui_state = state;
    }

    //reset
    Q_INVOKABLE void factoryInit();
    Q_INVOKABLE void clearStatusAll();
    Q_INVOKABLE void clearStatus();
    Q_INVOKABLE void resetLocalization();
    Q_INVOKABLE void resetLocalizationConfirm();
    Q_INVOKABLE void clearSharedMemory();

    //mode
    Q_INVOKABLE bool isDebugMode(){return debug_mode;}

    //status
    Q_INVOKABLE bool isRobotReady(bool print=true);
    Q_INVOKABLE int getBattery();
    Q_INVOKABLE int getMotorState();
    Q_INVOKABLE int getLocalizationState();
    Q_INVOKABLE int getStateMoving();
    Q_INVOKABLE QString getStateMovingStr();

    Q_INVOKABLE bool getIPCConnection();
    Q_INVOKABLE bool getMotorConnection(int id);
    Q_INVOKABLE int getMotorStatus(int id);
    Q_INVOKABLE QString getMotorStatusStr(int id);
    Q_INVOKABLE int getMotorTemperature(int id);
    Q_INVOKABLE int getMotorInsideTemperature(int id);
    Q_INVOKABLE int getMotorWarningTemperature();
    Q_INVOKABLE int getMotorCurrent(int id);
    Q_INVOKABLE int getPowerStatus();
    Q_INVOKABLE int getChargeConnectStatus();
    Q_INVOKABLE int getChargeStatus();
    Q_INVOKABLE int getEmoStatus();
    Q_INVOKABLE int getLockStatus();
    Q_INVOKABLE float getBatteryIn();
    Q_INVOKABLE float getBatteryOut();
    Q_INVOKABLE float getBatteryCurrent();
    Q_INVOKABLE float getPower();
    Q_INVOKABLE float getPowerTotal();
    Q_INVOKABLE int getObsinPath();

    Q_INVOKABLE float getlastRobotx();
    Q_INVOKABLE float getlastRoboty();
    Q_INVOKABLE float getlastRobotth();

    Q_INVOKABLE float getICPRatio();
    Q_INVOKABLE float getICPError();

    ////*********************************************  MAP Load 관련   ***************************************************////
    QList<QString> map_list;
    QList<QString> map_detail_list;

    //load
    Q_INVOKABLE void setMapOrin(QString type){maph->setMapOrin(type);}
    Q_INVOKABLE void loadFile(QString name="", QString type=""){maph->loadFile(name,type);}
    Q_INVOKABLE void loadAnnotation(){maph->loadAnnotation();}
    Q_INVOKABLE void removeMap(QString filename);
    Q_INVOKABLE void loadMap(QString name);
    Q_INVOKABLE bool isLoadMap();
    Q_INVOKABLE bool isExistMap(QString name="");
    Q_INVOKABLE bool isExistRawMap(QString name);
    Q_INVOKABLE bool isExistTlineMap(QString name="");
    Q_INVOKABLE bool isExistAvoidMap(QString name="");
    Q_INVOKABLE bool isExistVelMap(QString name="");
    Q_INVOKABLE bool isExistObjectMap(QString name="");
    Q_INVOKABLE bool isExistTravelMap(QString name);
    Q_INVOKABLE bool isExistAnnotation(QString name);
    Q_INVOKABLE bool isAvailableAnnotation();
    Q_INVOKABLE QString getAnnotModifiedDate(){return pmap->annot_modified_date;}
    Q_INVOKABLE int getAvailableMap();
    Q_INVOKABLE QString getAvailableMapPath(int num);
    Q_INVOKABLE void deleteEditedMap();
    Q_INVOKABLE void deleteAnnotation();
    void CopyPath(QString srcs, QString dst);
    Q_INVOKABLE int copyMap(QString orinname, QString newname);

    //path
    Q_INVOKABLE QString getMapname();
    Q_INVOKABLE QString getnewMapname();
    Q_INVOKABLE QString getMappath();
    Q_INVOKABLE QString getRawMapPath(QString name);
    Q_INVOKABLE QString getMapPath(QString name);
    Q_INVOKABLE QString getAnnotPath(QString name);
    Q_INVOKABLE QString getMetaPath(QString name);
    Q_INVOKABLE QString getTravelPath(QString name);
    Q_INVOKABLE QString getCostPath(QString name);

    //map info
    Q_INVOKABLE int getMapWidth();
    Q_INVOKABLE int getMapHeight();
    Q_INVOKABLE float getGridWidth();
    Q_INVOKABLE QList<int> getOrigin();
    Q_INVOKABLE int getMappingWidth(){return pmap->mapping_width;}
    Q_INVOKABLE float getMappingGridwidth(){return pmap->mapping_gridwidth;}



    ////*********************************************  MAP Drawing   ***************************************************////
    //view
    Q_INVOKABLE void zoomIn(int x, int y, float dist){maph->zoomIn(x,y,dist);}
    Q_INVOKABLE void zoomOut(int x, int y, float dist){maph->zoomOut(x,y,dist);}
    Q_INVOKABLE void setFullScreen(){maph->setFullScreen();}
    Q_INVOKABLE void move(int x, int y){maph->move(x,y);}
    Q_INVOKABLE void setSize(int x, int y, float width){maph->setSize(x,y,width);}
    Q_INVOKABLE int getFileWidth(){return maph->getFileWidth();}
    Q_INVOKABLE int getX(){return maph->getX();}
    Q_INVOKABLE int getY(){return maph->getY();}
    Q_INVOKABLE float getScale(){return maph->getScale();}

    //mode
    Q_INVOKABLE void setMapDrawing(){maph->setMapDrawing();}
    Q_INVOKABLE void setMode(QString name){maph->setMode(name);}
    Q_INVOKABLE void setEnable(bool en){maph->setEnable(en);}
    Q_INVOKABLE QString getMode(){return maph->getMode();}
    Q_INVOKABLE bool getRobotFollowing(){return maph->getRobotFollowing();}

    //topo
    Q_INVOKABLE bool isExistNode(QString type){return maph->isExistNode(type);}
    Q_INVOKABLE void autoTline(){maph->autoTline();}

    //tool
    Q_INVOKABLE void setTool(QString name){maph->setTool(name);}
    Q_INVOKABLE QString getTool(){return maph->getTool();}
    Q_INVOKABLE void setRulerPoint(int x, int y){maph->setRulerPoint(x,y);}
    Q_INVOKABLE bool getCutBoxFlag(){return maph->getCutBoxFlag();}
    Q_INVOKABLE void setBoxPoint(int num, int x, int y){maph->setBoxPoint(num,x,y);}
    Q_INVOKABLE int getPointBox(int x, int y){return maph->getPointBox(x,y);}
    Q_INVOKABLE void saveRotateMap(){maph->saveRotateMap();}
    Q_INVOKABLE void initRotate(){maph->initRotate();}
    Q_INVOKABLE void rotateMap(int angle){maph->rotateMap(angle);}
    Q_INVOKABLE void rotateMapCW(){maph->rotateMapCW();}
    Q_INVOKABLE void rotateMapCCW(){maph->rotateMapCCW();}

    //show
    Q_INVOKABLE void setShowBrush(bool onoff){maph->setShowBrush(onoff);}
    Q_INVOKABLE void setShowLidar(bool onoff){maph->setShowLidar(onoff);}
    Q_INVOKABLE void setShowLocation(bool onoff){maph->setShowLocation(onoff);}
    Q_INVOKABLE void setRobotFollowing(bool onoff){maph->setRobotFollowing(onoff);}
    Q_INVOKABLE void setShowTravelline(bool onoff){maph->setShowTravelline(onoff);}
    Q_INVOKABLE void setShowVelocitymap(bool onoff){maph->setShowVelocitymap(onoff);}
    Q_INVOKABLE void setShowObject(bool onoff){maph->setShowObject(onoff);}
    Q_INVOKABLE bool getshowLocation(){return maph->getshowLocation();}
    Q_INVOKABLE bool getShowLidar(){return maph->getShowLidar();}
    Q_INVOKABLE void setShowAvoidmap(bool onoff){maph->setShowAvoidMap(onoff);}
    Q_INVOKABLE void setShowTline(bool onoff){maph->setShowTravelline(onoff);}
    Q_INVOKABLE bool getShowTline(){return maph->getShowTline();}
    Q_INVOKABLE void setShowVelmap(bool onoff){maph->setShowVelocitymap(onoff);}
    Q_INVOKABLE bool getShowVelmap(){return maph->getShowVelmap();}
    Q_INVOKABLE void setShowAvoid(bool onoff){maph->setShowAvoidMap(onoff);}
    Q_INVOKABLE bool getShowAvoid(){return maph->getShowAvoid();}
    Q_INVOKABLE bool getShowObject(){return maph->getShowObject();}
    Q_INVOKABLE void setShowEdge(bool onoff){maph->setShowEdge(onoff);}
    Q_INVOKABLE bool getShowEdge(){return maph->getShowEdge();}
    Q_INVOKABLE void setShowNode(bool onoff){maph->setShowNode(onoff);}
    Q_INVOKABLE bool getShowNode(){return maph->getShowNode();}
    Q_INVOKABLE void setShowName(bool onoff){maph->setShowName(onoff);}
    Q_INVOKABLE bool getShowName(){return maph->getShowName();}
    Q_INVOKABLE void setVelmapView(bool onoff);
    Q_INVOKABLE void setTlineView(bool onoff);
    Q_INVOKABLE void setObjectView(bool onoff);
    Q_INVOKABLE void setAvoidmapView(bool onoff);
    Q_INVOKABLE void setLocationView(bool onoff);
    Q_INVOKABLE void setRobotView(bool onoff);

    //localization
    Q_INVOKABLE void setInitFlag(bool onoff){maph->setInitFlag(onoff);}
    Q_INVOKABLE void setInitPose(int x, int y, float th){maph->setInitPose(x,y,th);}
    Q_INVOKABLE void clearInitPose(){maph->clearInitPose();}

    //travel line
    Q_INVOKABLE void startDrawingTline(){maph->startDrawingTline();}
    Q_INVOKABLE void stopDrawingTline(){maph->stopDrawingTline();}
    Q_INVOKABLE bool getDrawingTline(){return maph->getDrawingTline();}
    Q_INVOKABLE int getTravellineIssue();
    Q_INVOKABLE QString getTravellineIssueGroup(int num);
    Q_INVOKABLE QString getTravellineIssueName(int num);
    Q_INVOKABLE bool getTravellineIssueFar(int num);
    Q_INVOKABLE bool getTravellineIssueBroken(int num);

    //drawing
    Q_INVOKABLE bool getDrawingFlag(){return maph->getDrawingFlag();}
    Q_INVOKABLE bool getDrawingUndoFlag(){return maph->getDrawingUndoFlag();}


    // Q_INVOKABLE void startDrawing(int x, int y){maph->startDrawing(x,y);}
    // Q_INVOKABLE void addLinePoint(int x, int y){maph->addLinePoint(x,y);}
    // Q_INVOKABLE void endDrawing(int x, int y){maph->endDrawing(x,y);}
    // Q_INVOKABLE void startErase2(int x, int y){maph->startErase2(x,y);}
    // Q_INVOKABLE void addErase2(int x, int y){maph->addErase2(x,y);}
    // Q_INVOKABLE void endErase2(int x, int y){maph->endErase2(x,y);}
    // Q_INVOKABLE void startDrawingRect(int x, int y){maph->startDrawingRect(x,y);}
    // Q_INVOKABLE void setDrawingRect(int x, int y){maph->setDrawingRect(x,y);}
    // Q_INVOKABLE void endDrawingRect(){maph->endDrawingRect();}
    Q_INVOKABLE void clearDrawing(){maph->clearDrawing();}
    Q_INVOKABLE void undoLine(){maph->undoLine();}
    Q_INVOKABLE void redoLine(){maph->redoLine();}
    // Q_INVOKABLE void startSpline(int x, int y){maph->startSpline(x,y);}
    // Q_INVOKABLE void addSpline(int x, int y){maph->addSpline(x,y);}
    // Q_INVOKABLE void drawSpline(){maph->drawSpline();}
    Q_INVOKABLE void endSpline(bool save){maph->endSpline(save);}
    // Q_INVOKABLE void startDrawingLine(int x, int y){maph->startDrawingLine(x,y);}
    // Q_INVOKABLE void setDrawingLine(int x, int y){maph->setDrawingLine(x,y);}
    // Q_INVOKABLE void stopDrawingLine(int x, int y){maph->stopDrawingLine(x,y);}
    Q_INVOKABLE void setLineColor(int color){maph->setLineColor(color);}
    Q_INVOKABLE void setLineWidth(int width){maph->setLineWidth(width);}

    //save
    Q_INVOKABLE void saveObjectPNG(){
        maph->saveObjectPNG();
        slam_map_reload(getMapname(),1);
    }
    Q_INVOKABLE void saveObsAreaPNG(){
        maph->saveObsAreaPNG();
        slam_map_reload(getMapname(),1);
    }
    Q_INVOKABLE void saveMap(){maph->saveMap();}
    Q_INVOKABLE void saveEditedMap(){maph->saveEditedMap();}
    Q_INVOKABLE void saveTline(){maph->saveTline();}
    Q_INVOKABLE void saveTlineTemp(){maph->saveTlineTemp();}
    Q_INVOKABLE void saveVelmap(){maph->saveVelmap();}
    Q_INVOKABLE void setMapSize(QString obj, int width, int height){
        maph->setMapSize(width, height);
    }
    Q_INVOKABLE bool rotate_map(QString _src, QString _dst, int mode);
    Q_INVOKABLE bool saveAnnotation(QString filename, bool reload=true);
    Q_INVOKABLE void saveNode();
    Q_INVOKABLE void setMap(){maph->setMap();}

    //interact
    Q_INVOKABLE void pressed(QString tool, int x, int y){maph->pressed(tool, x, y);}
    Q_INVOKABLE void double_pressed(QString tool, int x1, int y1, int x2, int y2){maph->double_pressed(tool, x1, y1, x2, y2);}
    Q_INVOKABLE void moved(QString tool, int x, int y){maph->moved(tool, x, y);}
    Q_INVOKABLE void double_moved(QString tool, int x1, int y1, int x2, int y2){maph->double_moved(tool, x1, y1, x2, y2);}
    Q_INVOKABLE void released(QString tool, int x, int y){maph->released(tool, x, y);}
    Q_INVOKABLE void double_released(QString tool, int x1, int y1, int x2, int y2){maph->double_released(tool, x1, y1, x2, y2);}
    Q_INVOKABLE void releaseShift(){maph->releaseShift();}
    Q_INVOKABLE void pressShift(){maph->pressShift();}

    //node
    Q_INVOKABLE void addNode(QString id, QString attr){maph->addNode(id,attr);}
    Q_INVOKABLE void addNode(QString name, QString group, QString attr){maph->addNode(name,group,attr);}
    Q_INVOKABLE void editNode(){maph->editNode();}
    Q_INVOKABLE void editNode(QString attr){maph->editNode(attr);}
    Q_INVOKABLE void deleteNode(){maph->deleteNode();}
    Q_INVOKABLE void linkNode(){maph->linkNode();}
    Q_INVOKABLE void alignNode(QString n){
        if(n=="x"){
            maph->alignXNode();
        }else if(n=="y"){
            maph->alignYNode();
        }else{
            maph->alignTHNode();
        }
    }


    bool isSameLocation(LOCATION l1, LOCATION l2){
        if(l1.group == l2.group && l1.name == l2.name){
            return true;
        }
        return false;
    }


    ////*********************************************  ANNOTATION 관련   ***************************************************////
    //Location
    // Q_INVOKABLE int getLocationNum(QString group, QString name);
    Q_INVOKABLE void saveLocation(QString type, int groupnum, QString name);
    Q_INVOKABLE void clearLocation(){maph->clearLocation();}
    Q_INVOKABLE void addLocation(int x, int y,float th){
        maph->addLocation(x,y,th);
    }
    // Q_INVOKABLE void addLocationCur(int x, int y,float th){maph->addLocationCur(x,y,th);}
    // Q_INVOKABLE void setLocation(int x, int y, float th){maph->setLocation(x,y,th);}
    Q_INVOKABLE void editLocation(QString type, int num);
    // Q_INVOKABLE int getLocationNum(int x, int y){return maph->getLocationNum(x,y);}
    Q_INVOKABLE void removeLocation(QString type, int num);
    Q_INVOKABLE void setTableNumberAuto(){maph->setTableNumberAuto();}
    // Q_INVOKABLE int getLocGroupNum(int num){return maph->getLocGroupNum(num);}
    Q_INVOKABLE QString getServingName(int group, int num);
    Q_INVOKABLE int getLocationNum(QString type);
    Q_INVOKABLE QString getLocationName(int num, QString type);
    Q_INVOKABLE QString getLocationNameGroup(int num);
    // Q_INVOKABLE int getLocationNumber(int group, int num);
    Q_INVOKABLE QString getLocationGroup(int num);
    Q_INVOKABLE int getLocationGroupNum();
    Q_INVOKABLE int getLocationGroupSize(int num);
    Q_INVOKABLE int getLocationGroupNum(int num);
    Q_INVOKABLE QString getLocationCallID(QString type, int num);
    Q_INVOKABLE QString getLocationLingID(QString type, int num);
    Q_INVOKABLE void setLocationGroup(int num, int group);
    Q_INVOKABLE void removeLocationGroup(int num);
    Q_INVOKABLE void addLocationGroup(QString name);
    Q_INVOKABLE QString getLocGroupname(int num);
    Q_INVOKABLE void setLocation(int num, QString name, int group, int tablenum);
    Q_INVOKABLE float getLocationX(int num, QString type);
    Q_INVOKABLE float getLocationY(int num, QString type);
    Q_INVOKABLE float getLocationTH(int num, QString type);

    //object
    // Q_INVOKABLE void setObjPose();
    Q_INVOKABLE int getObjectNum(int x, int y);
    Q_INVOKABLE int getObjectPointNum(int x, int y);
    Q_INVOKABLE void addObject(int x, int y);
    Q_INVOKABLE void addObjectPoint(int x, int y);
    Q_INVOKABLE void setObject(int x, int y);
    Q_INVOKABLE void editObjectStart(int x, int y);
    Q_INVOKABLE void editObject(int x, int y);
    Q_INVOKABLE void saveObject();
    Q_INVOKABLE void clearObject();
    Q_INVOKABLE void clearObjectAll();
    Q_INVOKABLE void selectObject(int num);
    Q_INVOKABLE bool getObjectflag();
    Q_INVOKABLE void undoObject();
    Q_INVOKABLE int getObjectNum();
    Q_INVOKABLE QString getObjectName(int num);
    Q_INVOKABLE int getObjectPointSize(int num);
    Q_INVOKABLE float getObjectX(int num, int point);
    Q_INVOKABLE float getObjectY(int num, int point);
    Q_INVOKABLE int getObjPointNum(int obj_num, int x, int y);
    Q_INVOKABLE int getObjectSize(QString type);
    Q_INVOKABLE void removeObject(int num);

    //edited
    Q_INVOKABLE bool getAnnotEditFlag();
    Q_INVOKABLE void setAnnotEditFlag(bool flag);




    ////*********************************************  Serving  *********************************************////
    Q_INVOKABLE void setTray(int tray_num, int group, int table);
    Q_INVOKABLE void setPreset(int preset);
    Q_INVOKABLE void cleanTray();
    Q_INVOKABLE void confirmPickup(QString mode);
    Q_INVOKABLE QList<int> getPickuptrays();

    Q_INVOKABLE void selectLocation(QString type, int num);
    Q_INVOKABLE bool setLocationUp(int num);
    Q_INVOKABLE bool setLocationDown(int num);
    Q_INVOKABLE bool checkGroupName(QString name);
    Q_INVOKABLE bool checkLocationName(int group, QString name);
    Q_INVOKABLE LOCATION getServingLocation(int group, QString name);
    Q_INVOKABLE LOCATION getServingLocation(QString group, QString name);
    Q_INVOKABLE LOCATION getServingLocation(QString name);
    Q_INVOKABLE LOCATION getChargingLocation(int num);
    Q_INVOKABLE LOCATION getCleaningLocation(int num);
    Q_INVOKABLE LOCATION getInitLocation(int num);
    Q_INVOKABLE LOCATION getRestingLocation(int num);
    Q_INVOKABLE QString getcurLoc();
    Q_INVOKABLE QString getNewServingName(int group);
    Q_INVOKABLE bool isDuplicateName(int group, QString name);


    ////*********************************************  Calling  *********************************************////
    int setting_call_num = -1;
    QString setting_call_type = "";
    //move
    Q_INVOKABLE int getCallQueueSize();

    Q_INVOKABLE QString getCallName(int id){
        return pmap->call_queue[id];
    }
    Q_INVOKABLE void clearCallQueue(){
        pmap->call_queue.clear();
    }
    Q_INVOKABLE bool isCallingMode(){return probot->is_calling;}

    //callbell
    Q_INVOKABLE void clear_call();
    Q_INVOKABLE void setCallbell(QString type, int id);
    Q_INVOKABLE void setCallbellForce(QString type, bool onoff);

    //lingbell
    Q_INVOKABLE void callCallbell(QString id);
    Q_INVOKABLE QString makeLingbell();
    Q_INVOKABLE void resetLingbell(int id);

    ////*********************************************  Patrol - Make   *********************************************////
    ST_PATROL current_patrol;
    ST_PAGE serving_page;

    Q_INVOKABLE void setPatrol(int num, QString name, QString type, int wait_time, int pass_time);
    Q_INVOKABLE void savePatrol(QString name, QString type, int wait_time, int pass_time);
    Q_INVOKABLE void deletePatrol(int num);
    Q_INVOKABLE void clearPatrolLocation(QString mode);
    Q_INVOKABLE void addPatrolLocation(QString type, QString group, QString name);
    Q_INVOKABLE void setPatrolMovingPage(QString mode, QString param1="", QString param2="", QString param3="");
    Q_INVOKABLE void setPatrolArrivePage(QString mode, QString param1="", QString param2="", QString param3="");
    Q_INVOKABLE void setPatrolVoice(QString mode, int language, int voice, int volume, int mention=0);

    Q_INVOKABLE void setServingPageBackground(QString mode);
    Q_INVOKABLE QString getServingPageBackground();
    Q_INVOKABLE void setServingPageMode(QString mode);
    Q_INVOKABLE QString getServingPageMode();
    Q_INVOKABLE void setServingPageColor(QString file);
    Q_INVOKABLE QString getServingPageColor();
    Q_INVOKABLE void setServingPageImage(QString file);
    Q_INVOKABLE QString getServingPageImage();
    Q_INVOKABLE void setServingPageVideo(QString file);
    Q_INVOKABLE QString getServingPageVideo();
    Q_INVOKABLE void setServingPageVideoAudio(QString mode);
    Q_INVOKABLE QString getServingPageVideoAudio();
    Q_INVOKABLE void setServingPageAudio(float volume);
    Q_INVOKABLE float getServingPageAudio();

    Q_INVOKABLE void setMovingPageBackground(QString mode);
    Q_INVOKABLE QString getMovingPageBackground();
    Q_INVOKABLE void setMovingPageMode(QString mode);
    Q_INVOKABLE QString getMovingPageMode();
    Q_INVOKABLE void setMovingPageColor(QString file);
    Q_INVOKABLE QString getMovingPageColor();
    Q_INVOKABLE void setMovingPageImage(QString file);
    Q_INVOKABLE QString getMovingPageImage();
    Q_INVOKABLE void setMovingPageVideo(QString file);
    Q_INVOKABLE QString getMovingPageVideo();
    Q_INVOKABLE void setMovingPageVideoAudio(QString mode);
    Q_INVOKABLE QString getMovingPageVideoAudio();
    Q_INVOKABLE void setMovingPageAudio(float volume);
    Q_INVOKABLE float getMovingPageAudio();

    Q_INVOKABLE void clearPatrolPage(int num);
    Q_INVOKABLE void clearServingPage();

    Q_INVOKABLE void initServingPage();
    Q_INVOKABLE void saveServingPage();
    Q_INVOKABLE void savePatrolPage();
    Q_INVOKABLE int getServingObjectSize();
    Q_INVOKABLE QString getServingObjectType(int num);
    Q_INVOKABLE QString getServingObjectSource(int num);
    Q_INVOKABLE QString getServingObjectColor(int num);
    Q_INVOKABLE int getServingObjectX(int num);
    Q_INVOKABLE int getServingObjectY(int num);
    Q_INVOKABLE int getServingObjectWidth(int num);
    Q_INVOKABLE int getServingObjectHeight(int num);
    Q_INVOKABLE int getServingObjectFontsize(int num);
    Q_INVOKABLE void addServingObject(QString page, QString obj);

    Q_INVOKABLE void setServingObjectSource(int num, QString src);
    Q_INVOKABLE void setServingObjectColor(int num, QString color);

    Q_INVOKABLE void deleteServingObject(int num);
    Q_INVOKABLE void moveServingObject(int num, int x, int y);
    Q_INVOKABLE void setServingObjectSize(int num, int point, int x, int y);
    Q_INVOKABLE void setServingObjectSize(int num, int x, int y, int width, int height);
    Q_INVOKABLE int getServingObjectNum(int x, int y);
    Q_INVOKABLE void initCurrentPatrol();
    Q_INVOKABLE int getPatrolObjectSize();
    Q_INVOKABLE QString getPageObjectType(int num);
    Q_INVOKABLE QString getPageObjectSource(int num);
    Q_INVOKABLE QString getPageObjectColor(int num);
    Q_INVOKABLE int getPageObjectX(int num);
    Q_INVOKABLE int getPageObjectY(int num);
    Q_INVOKABLE int getPageObjectWidth(int num);
    Q_INVOKABLE int getPageObjectHeight(int num);
    Q_INVOKABLE int getPageObjectFontsize(int num);
    Q_INVOKABLE void addPatrolObject(QString page, QString obj);
    ST_PAGE_OBJECT makeNewObj(QString obj);

    Q_INVOKABLE void setPageObjectSource(int num, QString src);
    Q_INVOKABLE void setPageObjectColor(int num, QString color);

    Q_INVOKABLE void deletePatrolObject(int num);
    Q_INVOKABLE void movePatrolObject(int num, int x, int y);
    Q_INVOKABLE void setPatrolObjectSize(int num, int point, int x, int y);
    Q_INVOKABLE void setPatrolObjectSize(int num, int x, int y, int width, int height);
    Q_INVOKABLE int getPageObjectNum(int x, int y);

    ////*********************************************  Patrol - Move   *********************************************////
    int patrol_mode = PATROL_NONE;
    int patrol_num = -1;
    int patrol_wait_count = 0;
    int count_moveto = 0;
    QList<ST_PATROL> patrols;

    Q_INVOKABLE void startPatrol(int num);

    //load
    Q_INVOKABLE void readPatrol();
    Q_INVOKABLE void setCurrentPatrol(int num);
    Q_INVOKABLE int getPatrolSize();
    Q_INVOKABLE int getPatrolVoiceNameNum(int num);
    Q_INVOKABLE QString getPatrolName(int num);
    Q_INVOKABLE QString getPatrolType(int num);
    Q_INVOKABLE QString getPatrolMovingPage(int num);
    Q_INVOKABLE QString getPatrolArrivePage(int num);
    Q_INVOKABLE int getPatrolWaitTime(int num);
    Q_INVOKABLE int getPatrolPassTime(int num);
    Q_INVOKABLE QString getPatrolVoice(int num);
    Q_INVOKABLE QString getPatrolVoiceMode(int num);
    Q_INVOKABLE QString getPatrolVoiceMention(int num);
    Q_INVOKABLE QString getPatrolVoiceLanguage(int num);
    Q_INVOKABLE bool isPatrolPage();
    Q_INVOKABLE QString getPatrolMovingMode();
    Q_INVOKABLE QString getPatrolArriveMode();

    //location
    Q_INVOKABLE int getPatrolLocationSize(int num);
    Q_INVOKABLE QString getPatrolLocation(int num);
    Q_INVOKABLE QString getPatrolLocation(int num, int loc);
    Q_INVOKABLE QString getPatrolLocationGroup(int num, int loc);

    ////*********************************************  Slam - command  *********************************************////
    bool cmd_accept = false;
    Q_INVOKABLE bool is_slam_running();

    //mapping
    Q_INVOKABLE void startMapping(int mapsize, float grid);
    Q_INVOKABLE void stopMapping();
    Q_INVOKABLE void setSLAMMode(int mode);
    Q_INVOKABLE void saveMapping(QString name);
    Q_INVOKABLE void loopClosing();
    Q_INVOKABLE bool getMappingflag();

    //initialize
    Q_INVOKABLE void setInitCurPos();
    Q_INVOKABLE bool getLocalizationConfirm(){return probot->localization_confirm;}
    Q_INVOKABLE void confirmLocalization();
    Q_INVOKABLE void confirmLocalizationAnnot();
    Q_INVOKABLE void slam_fullautoInit();
    Q_INVOKABLE void slam_setInit();
    Q_INVOKABLE void slam_run();
    Q_INVOKABLE void slam_stop();
    Q_INVOKABLE void slam_autoInit();
    Q_INVOKABLE void slam_restInit();

    //moving
    Q_INVOKABLE void setMotorLock(bool onoff);
    Q_INVOKABLE void startServing();
    Q_INVOKABLE void startServing(int group, int table);
    Q_INVOKABLE void moveToServingTest(int group, QString name);
    Q_INVOKABLE void movePause();
    Q_INVOKABLE void moveResume();
    Q_INVOKABLE void moveStopFlag();
    Q_INVOKABLE void moveStop();
    Q_INVOKABLE void moveToCharge();
    Q_INVOKABLE void moveToWait();
    Q_INVOKABLE void moveToCleaning();
    Q_INVOKABLE bool isFinalLocation();

    //annotation
    Q_INVOKABLE void checkTravelline();
    Q_INVOKABLE void drawingRunawayStart();
    Q_INVOKABLE void drawingRunawayStop();
    Q_INVOKABLE int getRunawayState();

    Q_INVOKABLE void slam_map_reload(QString filename, int mode=0);
    Q_INVOKABLE void slam_ini_reload();

    ////*********************************************  SERVER   ***************************************************////
    Q_INVOKABLE bool isConnectServer();
    Q_INVOKABLE void loadMapServer();
    Q_INVOKABLE void sendMapServer();


////*********************************************  SETTINGs   *********************************************////
    //ini
    Q_INVOKABLE bool isExistRobotINI();
    Q_INVOKABLE void setSetting(QString file, QString name, QString value);
    Q_INVOKABLE void readSetting(QString map_name="");
    Q_INVOKABLE QString getSetting(QString file, QString group, QString name);
    Q_INVOKABLE QString getRobotType();
    Q_INVOKABLE QString getRobotName();
    Q_INVOKABLE int getMultiState();
    Q_INVOKABLE void saveSetting();
    Q_INVOKABLE void loadSetting();

    //network
    Q_INVOKABLE int getWifiNum();
    Q_INVOKABLE int getWifiConnection();
    Q_INVOKABLE int getEthernetConnection();
    Q_INVOKABLE int getInternetConnection();
    Q_INVOKABLE void connectWifi(QString ssid, QString passwd);
    Q_INVOKABLE void setWifiDHCP();
    Q_INVOKABLE void setWifi(QString ip, QString gateway, QString dns);
    Q_INVOKABLE void setWifi(QString ssid, QString ip, QString subnet, QString gateway, QString dns1, QString dns2);
    Q_INVOKABLE void setEthernet(QString ip, QString subnet, QString gateway, QString dns1, QString dns2);

    Q_INVOKABLE void getAllWifiList();
    Q_INVOKABLE QString getWifiSSID(int num);
    Q_INVOKABLE bool getWifiSecurity(QString ssid);
    Q_INVOKABLE int getWifiLevel(QString ssid);
    Q_INVOKABLE int getWifiRate(QString ssid);
    Q_INVOKABLE bool getWifiInuse(QString ssid);

    Q_INVOKABLE QString getCurWifiSSID();
    Q_INVOKABLE QString getcurIP();
    Q_INVOKABLE QString getcurGateway();
    Q_INVOKABLE QString getcurNetmask();
    Q_INVOKABLE QString getcurDNS2();
    Q_INVOKABLE QString getcurDNS();
    Q_INVOKABLE int getWifiLevel();

    Q_INVOKABLE QString getethernetIP();
    Q_INVOKABLE QString getethernetGateway();
    Q_INVOKABLE QString getethernetNetmask();
    Q_INVOKABLE QString getethernetDNS2();
    Q_INVOKABLE QString getethernetDNS();
    Q_INVOKABLE QString getcurIPMethod();

    //volume
    Q_INVOKABLE int getSystemVolume(){
        return probot->volume_system;
    }
    Q_INVOKABLE void setSystemVolume(int volume);

    //layout
    Q_INVOKABLE void setlanguage(QString lan);
    Q_INVOKABLE void setCursorView(bool visible);
    Q_INVOKABLE int getTrayNum();
    Q_INVOKABLE void setTableColNum(int col_num);


    //camera
    Q_INVOKABLE void requestCamera();
    Q_INVOKABLE QString getLeftCamera();
    Q_INVOKABLE QString getRightCamera();
    Q_INVOKABLE void setCamera(QString left, QString right);
    Q_INVOKABLE int getCameraNum();
    Q_INVOKABLE QString getCameraSerial(int num);



    ////*********************************************  Sound + TTS   *********************************************////
    QMediaPlayer *bgm_player;
    QMediaPlayer *voice_player;
    QSoundEffect *click_effect;
    QMediaPlaylist *list_bgm;

    Q_INVOKABLE void playBGM(int volume = -1);
    Q_INVOKABLE void stopBGM();
    Q_INVOKABLE bool isplayBGM();
    Q_INVOKABLE void setvolumeBGM(int volume);

    Q_INVOKABLE void playSound(QString name, int volume=-1);Q_INVOKABLE void makeTTSAll();
    Q_INVOKABLE void setTTSMode(QString mode);
    Q_INVOKABLE void setTTSVoice(int lan, int name);
    Q_INVOKABLE void setTTSVoiceDetail(int speed, int pitch, int alpha, int emotion=0, int emostren=1);
    Q_INVOKABLE void clearTTSVoice(int lan, int name);
    Q_INVOKABLE void saveTTSVoice();
    Q_INVOKABLE void makePatrolTTS(int language, int voice, QString text, bool play=true);
    Q_INVOKABLE int getTTSNameNum();
    Q_INVOKABLE int getTTSLanguageNum();
    Q_INVOKABLE int getTTSSpeed(){return tts->curVoice.speed;}
    Q_INVOKABLE int getTTSPitch(){return tts->curVoice.pitch;}
    Q_INVOKABLE int getTTSEmotion(){return tts->curVoice.emotion;}
    Q_INVOKABLE int getTTSEmotionStrength(){return tts->curVoice.emotion_strength;}
    Q_INVOKABLE int getTTSAlpha(){return tts->curVoice.alpha;}
    Q_INVOKABLE int getTTSVolume(){return tts->curVoice.volume;}
    Q_INVOKABLE QString getTTSMention(QString text);
    Q_INVOKABLE void setTTSMentionBasic();
    Q_INVOKABLE void setTTSMention(QString text, QString mention);
    Q_INVOKABLE void playVoice(QString file, QString voice="", QString mode="", QString language="", int volume=-1);

    Q_INVOKABLE QString getTTSVoice(int lan, int name){return tts->getVoiceName("tts",lan,name);}
    Q_INVOKABLE void playTTS(){tts->playcurVoice();}


    ////*********************************************  MAIN   ***************************************************////
    QString curPage = "";
    Q_INVOKABLE void setCurrentPage(QString page){curPage = page;}
    void setWindow(QQuickWindow* Window);
    QQuickWindow *getWindow();
    void setObject(QObject* object);
    QObject* getObject();
    Q_INVOKABLE void programRestart();
    Q_INVOKABLE void programExit();
    Q_INVOKABLE bool isOdroid();

    ////*********************************************  SH   ***************************************************////
    Q_INVOKABLE bool checkINI();
    void checkShellFiles();
    void makeKillShell();
    void makeKillSlam();
    void makeStartShell();
    void makeAllKillShell();

    Q_INVOKABLE void killSLAM();
    Q_INVOKABLE void makeRobotINI();
    Q_INVOKABLE void checkRobotINI();
    Q_INVOKABLE void restartSLAM();
    Q_INVOKABLE void startSLAM();



    ////*********************************************  Update 관련   ***************************************************////
    Q_INVOKABLE void updateProgram();
    Q_INVOKABLE void updateProgram(QString _v);
    Q_INVOKABLE void gitReset();
    Q_INVOKABLE void updateProgramGitPull();
    Q_INVOKABLE void checkVersionAgain();
    Q_INVOKABLE bool isNewVersion();
    Q_INVOKABLE bool isNeedUpdate();
    Q_INVOKABLE void restartUpdate();
    Q_INVOKABLE void startUpdate();

    Q_INVOKABLE void refreshVersion();
    Q_INVOKABLE QString getNewVersion();
    Q_INVOKABLE QString getCurVersion();
    Q_INVOKABLE QString getCurVersionDate();
    Q_INVOKABLE int getNewVersionsSize();
    Q_INVOKABLE QString getNewVersion(int i);
    Q_INVOKABLE QString getNewVersionDate(int i);
    Q_INVOKABLE QString getNewVersionMessage(int i);

    Q_INVOKABLE QString getLocalVersion();
    Q_INVOKABLE QString getServerVersion();
    Q_INVOKABLE QString getLocalVersionDate();
    Q_INVOKABLE QString getLocalVersionMessage();
    Q_INVOKABLE QString getServerVersionMessage();

    Q_INVOKABLE QString getUpdateDate();
    Q_INVOKABLE int getUpdateSize();
    Q_INVOKABLE QString getUpdateFileName(int num);
    Q_INVOKABLE QString getUpdateCommit(QString name);
    Q_INVOKABLE QString getCurrentCommit(QString name);
    Q_INVOKABLE QString getUpdateMessage(QString name);
    Q_INVOKABLE QString getLastUpdateDate(QString name);

    Q_INVOKABLE void checkCleaningLocation();

    Q_INVOKABLE void checkUpdate();
    Q_INVOKABLE bool checkNewUpdateProgram();


    ////*********************************************  USB 관련   ***************************************************////
    QStringList usb_list;
    QStringList usb_file_full_list;
    QStringList usb_file_list;

    Q_INVOKABLE int getusbsize();
    Q_INVOKABLE void readusbrecentfile();
    Q_INVOKABLE int getusbfilesize();
    Q_INVOKABLE QString getusbfile(int num);
    Q_INVOKABLE QString getusbrecentfile();
    Q_INVOKABLE QString getusbname(int num);
    Q_INVOKABLE void readusb();

    Q_INVOKABLE void saveMapfromUsb(QString path);
    Q_INVOKABLE int getusberrorsize();
    Q_INVOKABLE QString getusberror(int num);
    Q_INVOKABLE void usbsave(QString usb="", bool _ui=true, bool _slam=true, bool _config=true, bool _map=true, bool _log=true);


    ////*********************************************  ZIP 관련   ***************************************************////
    Q_INVOKABLE int getzipstate();

    ////*********************************************  LOG 관련   ***************************************************////
    QStringList curLog;
    QString log_folder = "ui_log";

    Q_INVOKABLE void writelog(QString msg);
    Q_INVOKABLE void setLog(int num){
        if(num==1){
            log_folder = "ui_log";
        }else{
            log_folder = "sn_log";
        }
    }

    ////*********************************************  goqual 관련   ***************************************************////
    Q_INVOKABLE QString getGoqualID();
    Q_INVOKABLE QString getGoqualPassword();
    Q_INVOKABLE QString getGoqualClientID();
    Q_INVOKABLE QString getGoqualClientSecret();
    Q_INVOKABLE QString getGoqualAccessKey();
    Q_INVOKABLE QString getGoqualRefreshKey();
    Q_INVOKABLE QString getGoqualExpiresIn();

    Q_INVOKABLE void getGoqualKey();
    Q_INVOKABLE void refreshGoqualKey();
    Q_INVOKABLE void getGoqualDeviceList();
    Q_INVOKABLE void setGoqualDevice(QString id, bool onoff);

    Q_INVOKABLE int getGoqualDeviceSize();
    Q_INVOKABLE QString getGoqualDeviceID(int num);
    Q_INVOKABLE QString getGoqualDeviceType(int num);
    Q_INVOKABLE bool getGoqualDeviceState(int num);
    Q_INVOKABLE bool getGoqualDeviceOnline(int num);
    Q_INVOKABLE QString getGoqualDeviceName(int num);

    Q_INVOKABLE void log_advanced(const QString& str);
    Q_INVOKABLE void start_folder_clear();

public slots:
    void onTimer();
    void path_changed();
    void camera_update();
    void mapping_update();
    void usb_detect();
    void git_pull_fail(int reason);
    void git_pull_success();
    void new_call();
    void process_accept(int cmd);
    void process_done(int cmd);
    void process_error(int cmd,int param);
    void process_timeout(int cmd);
    void update_success();
    void update_fail();
    void map_reset();
    void new_call_order(QString name);
    void play_voice(ST_VOICE voice);
    void emo_state_changed();
    void connect_wifi_fail(int reason, QString ssid);
    void connect_wifi_success(QString ssid);
    void set_wifi_success(QString ssid);
    void set_wifi_fail(int reason,QString ssid);
    void got_message(QString msg);

private:
    QTimer *timer;
    QTimer *folder_clear_timer;
    QTimer *wifiTimer;
    QQuickWindow *mMain;
    QObject *mObject = nullptr;
    QTranslator *translator;
};

#endif // SUPERVISOR_H
