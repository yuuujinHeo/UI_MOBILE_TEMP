#ifndef SUPERVISOR_H
#define SUPERVISOR_H

#include <QObject>
#include <QTimer>
#include <QThread>
#include <QQuickWindow>
#include "GlobalHeader.h"
#include "CallbellHandler.h"
#include "ZIPHandler.h"
#include "python_wrapper.h"
#include "IPCHandler.h"
#include <QMediaPlaylist>
#include "ServerHandler.h"
#include <QMediaPlayer>
#include "MapView.h"
#include "MapHandler.h"
#include "ExtProcess.h"
#include "ExtProcess.h"
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
    ////*********************************************  FLAGS   ***************************************************////

    //넘어가기(debug)사용 시 true -> slam auto kill 안함
    bool debug_mode = false;

    //순회 모드, 순회 중 픽업해주세요 화면 띄울건지.
    bool use_cleaning_location = false;
    bool start_clear = false;

    ////*********************************************  STRUCT   ***************************************************////
    ST_MAP map;
    ST_ROBOT robot;
    ST_SETTING setting;
//    ST_PATROLMODE patrol;
    ServerHandler *server;

    ////*********************************************  VARIABLE   ***************************************************////
    QStringList usb_list;
    QStringList usb_file_full_list;
    QStringList usb_file_list;
    QStringList usb_backup_list;
    QList<QString> usb_map_list;
    QList<QString> map_list;
    QList<QString> map_detail_list;

    int setting_call_num = -1;
    int patrol_num = -1;

    int foundCount;
    QNetworkConfiguration netcfg;
    QStringList WiFisList;
    QList<QNetworkConfiguration> netcfgList;
    QNetworkConfiguration defaultWifiConf;

    void initPatrol();

    Q_INVOKABLE void loadMapServer();
    Q_INVOKABLE void sendMapServer();

    Q_INVOKABLE bool checkLocationName(int group, QString name);
    ////*********************************************  IP SETTINGs   *********************************************////

    Q_INVOKABLE void resetClear();
    QString wifi_temp_ssd = "";
    Q_INVOKABLE int getWifiNum();
    Q_INVOKABLE int getWifiConnection(QString ssid);
    void setWifiConnection(QString ssid, int con);
    Q_INVOKABLE QString getCurWifiSSID();
    Q_INVOKABLE QString getWifiSSID(int num);
    Q_INVOKABLE void connectWifi(QString ssid, QString passwd);

    Q_INVOKABLE bool getWifiSecurity(QString ssid);
    Q_INVOKABLE int getWifiLevel(QString ssid);
    Q_INVOKABLE int getWifiRate(QString ssid);
    Q_INVOKABLE bool getWifiInuse(QString ssid);
    Q_INVOKABLE void getAllWifiList();
    Q_INVOKABLE void getWifiIP();
    Q_INVOKABLE void setWifi(QString ip, QString gateway, QString dns);
    Q_INVOKABLE QString getcurIP();
    Q_INVOKABLE QString getcurGateway();
    Q_INVOKABLE QString getcurDNS();
    Q_INVOKABLE void readWifiState(QString ssid);
    Q_INVOKABLE void setWifiSSD(QString ssid);

    Q_INVOKABLE int getSystemVolume(){return probot->volume_system;}
    Q_INVOKABLE void passInit();



    ////*********************************************  Patrol   *********************************************////
    int patrol_mode = PATROL_NONE;
    int patrol_wait_count = 0;
    QList<ST_PATROL> patrols;
    ST_PATROL current_patrol;
    Q_INVOKABLE void readPatrol();
    Q_INVOKABLE int getPatrolSize();
    Q_INVOKABLE QString getPatrolName(int num);
    Q_INVOKABLE QString getPatrolType(int num);
    Q_INVOKABLE QString getPatrolLocation(int num);
    Q_INVOKABLE QString getPatrolMovingPage(int num);
    Q_INVOKABLE QString getPatrolArrivePage(int num);
    Q_INVOKABLE int getPatrolWaitTime(int num);
    Q_INVOKABLE int getPatrolPassTime(int num);
    Q_INVOKABLE QString getPatrolVoice(int num);
    Q_INVOKABLE QString getPatrolVoiceMode(int num);

    Q_INVOKABLE bool isPatrolPage();
    Q_INVOKABLE QString getPatrolMovingMode();
    Q_INVOKABLE QString getPatrolArriveMode();

    Q_INVOKABLE void setCurrentPatrol(int num);
    Q_INVOKABLE int getPatrolLocationSize(int num);
    Q_INVOKABLE QString getPatrolLocation(int num, int loc);

    Q_INVOKABLE void clearPatrolLocation(QString mode);
    Q_INVOKABLE void addPatrolLocation(QString name);
    Q_INVOKABLE void setPatrolMovingPage(QString mode, QString param1="", QString param2="", QString param3="");
    Q_INVOKABLE void setPatrolArrivePage(QString mode, QString param1="", QString param2="", QString param3="");
    Q_INVOKABLE void setPatrolVoice(QString text, QString param1="", QString param2="", QString param3="");

    Q_INVOKABLE void setPatrol(int num, QString name, QString type, int wait_time, int pass_time);
    Q_INVOKABLE void savePatrol(QString name, QString type, int wait_time, int pass_time);
    Q_INVOKABLE void deletePatrol(int num);
    Q_INVOKABLE void startPatrol(int num);



    int count_moveto = 0;


    ////*********************************************  CLASS   ***************************************************////
    ZIPHandler *zip;
    MapHandler *maph;
    ExtProcess *extproc;
    CallbellHandler *call;
    IPCHandler *ipc;
    QProcess *slam_process;


    ////*********************************************  Server   ***************************************************////


    bool checkCallQueue();
    ////*********************************************  MAP HANDLER   ***************************************************////

    Q_INVOKABLE void loadFile(QString name, QString type){maph->loadFile(name,type);}

    //------------draw map--------------//
    Q_INVOKABLE void setMap(){maph->setMap();}
    Q_INVOKABLE void moveMap(){maph->moveMap();}
    Q_INVOKABLE void setFullScreen(){maph->setFullScreen();}
    Q_INVOKABLE void setMapDrawing(){maph->setMapDrawing();}

    QMediaPlayer *click_sound;
    QMediaPlayer *click_no_sound;
    QMediaPlayer *click_2_sound;
    QMediaPlayer *click_start_sound;
    QMediaPlayer *bgm_player;
    QMediaPlayer *voice_player;
    QMediaPlaylist *list_bgm;
    Q_INVOKABLE void clicksound(QString mode, int volume = -1);
    Q_INVOKABLE void playBGM(int volume = -1);
    Q_INVOKABLE void stopBGM();
    Q_INVOKABLE bool isplayBGM();
    Q_INVOKABLE void playVoice(QString voice, int volume=-1);
    Q_INVOKABLE void playVoice(QString voice, QString text, int volume=-1);
    Q_INVOKABLE void playVoiceFile(QString file, int volume=-1);



    Q_INVOKABLE void makeTTS(QString text);
    Q_INVOKABLE void playTTS();
    //------------map variables--------------//
    Q_INVOKABLE void confirmLocalization();//{probot->localization_confirm = LOCAL_READY;}
    Q_INVOKABLE void setName(QString name){maph->setName(name);}
    Q_INVOKABLE void setTool(QString name){maph->setTool(name);}
    Q_INVOKABLE QString getTool(){return maph->getTool();}
    Q_INVOKABLE void setMode(QString name){maph->setMode(name);}
    Q_INVOKABLE void setEnable(bool en){maph->setEnable(en);}
    Q_INVOKABLE QString getMode(){return maph->getMode();}
    Q_INVOKABLE void setShowBrush(bool onoff){maph->setShowBrush(onoff);}
    Q_INVOKABLE void setShowLidar(bool onoff){maph->setShowLidar(onoff);}
    Q_INVOKABLE void setShowLocation(bool onoff){maph->setShowLocation(onoff);}
    Q_INVOKABLE void setRobotFollowing(bool onoff){maph->setRobotFollowing(onoff);}
    Q_INVOKABLE void setShowTravelline(bool onoff){maph->setShowTravelline(onoff);}
    Q_INVOKABLE void setShowVelocitymap(bool onoff){maph->setShowVelocitymap(onoff);}
    Q_INVOKABLE void setShowObject(bool onoff){maph->setShowObject(onoff);}
    Q_INVOKABLE void setInitFlag(bool onoff){maph->setInitFlag(onoff);}
    Q_INVOKABLE bool getshowLocation(){return maph->getshowLocation();}
    Q_INVOKABLE bool getRobotFollowing(){return maph->getRobotFollowing();}
    Q_INVOKABLE bool getShowLidar(){return maph->getShowLidar();}
    Q_INVOKABLE void setShowAvoidmap(bool onoff){maph->setShowAvoidMap(onoff);}

    Q_INVOKABLE void setInitPose(int x, int y, float th){maph->setInitPose(x,y,th);}
    Q_INVOKABLE void clearInitPose(){maph->clearInitPose();}

    Q_INVOKABLE QString getAnnotModifiedDate(){return pmap->annot_modified_date;}

    Q_INVOKABLE void startDrawingTline(){maph->startDrawingTline();}
    Q_INVOKABLE void stopDrawingTline(){maph->stopDrawingTline();}
    Q_INVOKABLE bool getDrawingTline(){return maph->getDrawingTline();}

    Q_INVOKABLE void setBoxPoint(int num, int x, int y){maph->setBoxPoint(num,x,y);}
    Q_INVOKABLE int getPointBox(int x, int y){return maph->getPointBox(x,y);}
    Q_INVOKABLE void saveRotateMap(){maph->saveRotateMap();}
    Q_INVOKABLE void initRotate(){maph->initRotate();}
    Q_INVOKABLE void rotateMap(int angle){maph->rotateMap(angle);}
    Q_INVOKABLE void rotateMapCW(){maph->rotateMapCW();}
    Q_INVOKABLE void rotateMapCCW(){maph->rotateMapCCW();}

    Q_INVOKABLE void saveObjectPNG(){
        maph->saveObjectPNG();
        slam_map_reload(getMapname(),1);
    }
    Q_INVOKABLE void saveObsAreaPNG(){
        maph->saveObsAreaPNG();
        slam_map_reload(getMapname(),1);
    }

    void clearRobot();

    Q_INVOKABLE int getLocalizationConfirm(){return probot->localization_confirm;}
    Q_INVOKABLE bool getDrawingFlag(){return maph->getDrawingFlag();}

    Q_INVOKABLE bool getDrawingUndoFlag(){return maph->getDrawingUndoFlag();}

    Q_INVOKABLE void startDrawing(int x, int y){maph->startDrawing(x,y);}
    Q_INVOKABLE void addLinePoint(int x, int y){maph->addLinePoint(x,y);}
    Q_INVOKABLE void endDrawing(int x, int y){maph->endDrawing(x,y);}


    Q_INVOKABLE void setMapOrin(QString type){maph->setMapOrin(type);}
    Q_INVOKABLE void startDrawingRect(int x, int y){maph->startDrawingRect(x,y);}
    Q_INVOKABLE void setDrawingRect(int x, int y){maph->setDrawingRect(x,y);}
    Q_INVOKABLE void endDrawingRect(){maph->endDrawingRect();}

    Q_INVOKABLE void clearDrawing(){maph->clearDrawing();}
    Q_INVOKABLE void undoLine(){maph->undoLine();}
    Q_INVOKABLE void redoLine(){maph->redoLine();}
    Q_INVOKABLE void startSpline(int x, int y){maph->startSpline(x,y);}
    Q_INVOKABLE void addSpline(int x, int y){maph->addSpline(x,y);}
    Q_INVOKABLE void drawSpline(){maph->drawSpline();}
    Q_INVOKABLE void endSpline(bool save){maph->endSpline(save);}
    Q_INVOKABLE void startDrawingLine(int x, int y){maph->startDrawingLine(x,y);}
    Q_INVOKABLE void setDrawingLine(int x, int y){maph->setDrawingLine(x,y);}
    Q_INVOKABLE void stopDrawingLine(int x, int y){maph->stopDrawingLine(x,y);}
    Q_INVOKABLE void setLineColor(int color){maph->setLineColor(color);}
    Q_INVOKABLE void setLineWidth(int width){maph->setLineWidth(width);}



    Q_INVOKABLE int getLocationNum(QString group, QString name);
    Q_INVOKABLE void saveLocation(QString type, int groupnum, QString name);//{maph->saveLocation(type,groupnum,name);}
    Q_INVOKABLE void clearLocation(){maph->clearLocation();}
    Q_INVOKABLE void addLocation(int x, int y,float th){maph->addLocation(x,y,th);}
    Q_INVOKABLE void addLocationCur(int x, int y,float th){maph->addLocationCur(x,y,th);}
    Q_INVOKABLE void setLocation(int x, int y, float th){maph->setLocation(x,y,th);}
    Q_INVOKABLE void editLocation(int num);//{maph->editLocation(x,y,th);}
    Q_INVOKABLE int getLocationNum(int x, int y){return maph->getLocationNum(x,y);}
    Q_INVOKABLE void removeLocation(int num);//{maph->removeLocation(num);}
    Q_INVOKABLE bool getLocationAvailable(int num);
    Q_INVOKABLE void setTableNumberAuto(){maph->setTableNumberAuto();}
//    Q_INVOKABLE int getLocationNum(QString type){return maph->getLocationNum(type);}
    Q_INVOKABLE int getLocGroupNum(int num){return maph->getLocGroupNum(num);}
    Q_INVOKABLE void saveMap(){maph->saveMap();}
    Q_INVOKABLE void saveEditedMap(){maph->saveEditedMap();}
    Q_INVOKABLE void saveTline(){maph->saveTline();}
    Q_INVOKABLE void saveTlineTemp(){maph->saveTlineTemp();}
    Q_INVOKABLE void saveVelmap(){maph->saveVelmap();}
    Q_INVOKABLE void setMapSize(int width, int height){maph->setMapSize(width, height);}
    Q_INVOKABLE void zoomIn(int x, int y, float dist){maph->zoomIn(x,y,dist);}
    Q_INVOKABLE void zoomOut(int x, int y, float dist){maph->zoomOut(x,y,dist);}
    Q_INVOKABLE void move(int x, int y){maph->move(x,y);}
    Q_INVOKABLE int getFileWidth(){return maph->getFileWidth();}
    Q_INVOKABLE int getX(){return maph->getX();}
    Q_INVOKABLE int getY(){return maph->getY();}
    Q_INVOKABLE float getScale(){return maph->getScale();}

    Q_INVOKABLE void setVelmapView(bool onoff);
    Q_INVOKABLE void setTlineView(bool onoff);
    Q_INVOKABLE void setObjectView(bool onoff);
    Q_INVOKABLE void setAvoidmapView(bool onoff);
    Q_INVOKABLE void setLocationView(bool onoff);
    Q_INVOKABLE void setRobotView(bool onoff);

    Q_INVOKABLE void setSystemVolume(int volume);
    Q_INVOKABLE void requestSystemVolume();

    Q_INVOKABLE void setSize(int x, int y, float width){maph->setSize(x,y,width);}
    Q_INVOKABLE bool getCutBoxFlag(){return maph->getCutBoxFlag();}

//    Q_INVOKABLE void saveAnnotation(QString filename){maph->saveAnnotation(filename);}

    Q_INVOKABLE void selectLocation(int num);

    Q_INVOKABLE void writelog(QString msg);

    Q_INVOKABLE void startDrawingObject();
    Q_INVOKABLE void stopDrawingObject();
    Q_INVOKABLE void saveDrawingObject();


    Q_INVOKABLE void setLocationUp(int num);
    Q_INVOKABLE void setLocationDown(int num);





    ////*********************************************  SH   ***************************************************////
    Q_INVOKABLE bool checkINI();
    void checkShellFiles();
    void makeKillShell();
    void makeKillSlam();
    void makeStartShell();
    void makeAllKillShell();
    void makeUSBShell();
    void makeExtProcessShell();


    Q_INVOKABLE void killSLAM();
    Q_INVOKABLE void makeRobotINI();
    Q_INVOKABLE void checkRobotINI();
    Q_INVOKABLE void restartSLAM();
    Q_INVOKABLE void startSLAM();

    ////*********************************************  LCM 관련   ***************************************************////
    Q_INVOKABLE bool getIPCConnection();
    Q_INVOKABLE bool getIPCRX();
    Q_INVOKABLE bool getIPCTX();


    ////*********************************************  WINDOW 관련   ***************************************************////
    void setWindow(QQuickWindow* Window);
    QQuickWindow *getWindow();
    void setObject(QObject* object);
    QObject* getObject();
    Q_INVOKABLE void programRestart();
    Q_INVOKABLE void programExit();


    Q_INVOKABLE QString getRawMapPath(QString name);
    Q_INVOKABLE QString getMapPath(QString name);
    Q_INVOKABLE QString getAnnotPath(QString name);
    Q_INVOKABLE QString getMetaPath(QString name);
    Q_INVOKABLE QString getTravelPath(QString name);
    Q_INVOKABLE QString getCostPath(QString name);
    Q_INVOKABLE QString getIniPath(QString file);

    ////*********************************************  SETTING 관련   ***************************************************////
    Q_INVOKABLE void setSetting(QString file, QString name, QString value);
    Q_INVOKABLE void readSetting(QString map_name="");
    Q_INVOKABLE QString getSetting(QString file, QString group, QString name);
    Q_INVOKABLE int getTrayNum();
    Q_INVOKABLE void setTableColNum(int col_num);

    Q_INVOKABLE QString getRobotType();

    Q_INVOKABLE void requestCamera();
    Q_INVOKABLE QString getLeftCamera();
    Q_INVOKABLE QString getRightCamera();
    Q_INVOKABLE void setCamera(QString left, QString right);
    Q_INVOKABLE int getCameraNum();
    Q_INVOKABLE QString getCameraSerial(int num);

    Q_INVOKABLE void setCursorView(bool visible);

    Q_INVOKABLE QString getVoice(QString name, QString mode="");
    Q_INVOKABLE void checkTravelline();
    ////*********************************************  GIT 관련   ***************************************************////
    Q_INVOKABLE void updateProgram();
    Q_INVOKABLE void updateProgramGitPull();
    Q_INVOKABLE void checkVersionAgain();
    Q_INVOKABLE bool isNewVersion();
    Q_INVOKABLE bool isNeedUpdate();
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
//    Q_INVOKABLE QString

    Q_INVOKABLE void setlanguage(QString lan);

    ////*********************************************  MOVING 관련   *************************************************////
    Q_INVOKABLE bool isCallingMode(){return probot->is_calling;}
    Q_INVOKABLE void goServing(int group, int table);
    Q_INVOKABLE LOCATION getLocationbyCall(QString call);
    Q_INVOKABLE LOCATION getLocation(int group, QString name);
    Q_INVOKABLE LOCATION getLocationbyID(int id);
    Q_INVOKABLE LOCATION getLocation(QString name);

    Q_INVOKABLE void setUiState(int state){
        ui_state = state;
    }

    Q_INVOKABLE void resetLocalization();
    ////*********************************************  LOG 관련   ***************************************************////
    QStringList curLog;
    QString log_folder = "ui_log";
    Q_INVOKABLE void setLog(int num){
        if(num==1){
            log_folder = "ui_log";
        }else{
            log_folder = "sn_log";
        }
    }
    Q_INVOKABLE int getLogLineNum();
    Q_INVOKABLE QString getLogLine(int num){return curLog[num];}
    Q_INVOKABLE QString getLogDate(int num);
    Q_INVOKABLE QString getLogAuth(int num);
    Q_INVOKABLE QString getLogMessage(int num);
    Q_INVOKABLE void readLog(QDateTime date);
    Q_INVOKABLE QString getLocaleDate(int year, int month, int date){
        return QString().asprintf("%d-%02d-%02d",year,month,date);
    }

    ////*********************************************  USB 관련   ***************************************************////
    Q_INVOKABLE void updateUSB();
    Q_INVOKABLE int getusbsize();
    Q_INVOKABLE void readusbrecentfile();
    Q_INVOKABLE int getusbfilesize();
    Q_INVOKABLE QString getusbfile(int num);
    Q_INVOKABLE QString getusbrecentfile();
    Q_INVOKABLE QString getusbname(int num);
    Q_INVOKABLE void readusb();

    Q_INVOKABLE void saveMapfromUsb(QString path);

    ////*********************************************  INIT PAGE 관련   ***************************************************////
    Q_INVOKABLE bool isConnectServer();

    Q_INVOKABLE bool isLoadMap();
    Q_INVOKABLE bool isExistMap(QString name="");
    Q_INVOKABLE bool isExistRawMap(QString name);
    Q_INVOKABLE bool isExistTlineMap(QString name="");
    Q_INVOKABLE bool isExistAvoidMap(QString name="");
    Q_INVOKABLE bool isExistVelMap(QString name="");
    Q_INVOKABLE bool isExistObjectMap(QString name="");
    Q_INVOKABLE bool isExistTravelMap(QString name);
    Q_INVOKABLE bool isExistAnnotation(QString name);
    Q_INVOKABLE bool isExistRobotINI();

    Q_INVOKABLE int getAvailableMap();
    Q_INVOKABLE QString getAvailableMapPath(int num);
    Q_INVOKABLE int getMapFileSize(QString name);
    Q_INVOKABLE QString getMapFile(int num);

    Q_INVOKABLE void deleteEditedMap();
    Q_INVOKABLE void deleteAnnotation();

    Q_INVOKABLE void removeMap(QString filename);

    Q_INVOKABLE void loadMap(QString name);

    void CopyPath(QString srcs, QString dst);
    Q_INVOKABLE int copyMap(QString orinname, QString newname);
    Q_INVOKABLE void setMap(QString name);
    Q_INVOKABLE bool rotate_map(QString _src, QString _dst, int mode);


    bool isSameLocation(LOCATION l1, LOCATION l2){
        if(l1.group == l2.group && l1.name == l2.name){
            return true;
        }
        return false;
    }

    ////*********************************************  SLAM(LOCALIZATION) 관련   ***************************************************////
    Q_INVOKABLE void startMapping(int mapsize, float grid);
    Q_INVOKABLE void stopMapping();
    Q_INVOKABLE void setSLAMMode(int mode);
    Q_INVOKABLE void saveMapping(QString name);

    Q_INVOKABLE void setInitCurPos();
    Q_INVOKABLE void setInitPos(int x, int y, float th);
    Q_INVOKABLE float getInitPoseX();
    Q_INVOKABLE float getInitPoseY();
    Q_INVOKABLE float getInitPoseTH();

    Q_INVOKABLE void slam_setInit();
    Q_INVOKABLE void slam_run();
    Q_INVOKABLE void slam_stop();
    Q_INVOKABLE void slam_autoInit();
    Q_INVOKABLE bool is_slam_running();

    Q_INVOKABLE bool getMappingflag();

    Q_INVOKABLE bool getObjectingflag();
    Q_INVOKABLE void setObjectingflag(bool flag);

    Q_INVOKABLE QString getnewMapname();

    ////*********************************************  CALLING 관련   ***************************************************////
    Q_INVOKABLE QString getLastCall(){return call->getBellID();}
    Q_INVOKABLE int getCallSize(){
        int num = 0;
        for(int i=0; i<pmap->locations.size(); i++){
            if(pmap->locations[i].call_id != "")
                num++;
        }
        return num;
    }
    Q_INVOKABLE int getCallQueueSize();
    Q_INVOKABLE void cleanTray();
    Q_INVOKABLE QString getCallName(int id){
        return pmap->call_queue[id];
//        if(id > -1 && id < pmap->call_queue.size()){
//            return getCallLocation(pmap->call_queue[id]).name;
//        }else{
//            return "";
//        }
    }
    Q_INVOKABLE void clearCallQueue(){
        pmap->call_queue.clear();
    }
    Q_INVOKABLE QString getCall(int id){return pmap->locations[id].call_id;}
    Q_INVOKABLE LOCATION getCallLocation(QString id);
    Q_INVOKABLE void setCallbell(QString type, int id);
    Q_INVOKABLE void setCallbellForce(QString type, bool onoff);
    Q_INVOKABLE void acceptCall(bool yes);
    LOCATION getloc(QString name){
        for(int i=0; i<pmap->locations.size(); i++){
            if(pmap->locations[i].name == name)
                return pmap->locations[i];
        }
        return LOCATION();
    }


    ////*********************************************  ANNOTATION 관련   ***************************************************////

    Q_INVOKABLE void setObjPose();
    Q_INVOKABLE QString getServingName(int group, int num);
//    Q_INVOKABLE int getLocation
    Q_INVOKABLE int getLocationNum(QString type="");
    Q_INVOKABLE QString getLocationName(int num, QString type="");
    Q_INVOKABLE QString getLocationType(int num);
    Q_INVOKABLE int getLocationNumber(int group, int num);
    Q_INVOKABLE void setLocationNumber(QString name, int num);
    Q_INVOKABLE int getLocationSize(QString type);
    Q_INVOKABLE QString getLocationGroup(int num);
    Q_INVOKABLE int getLocationID(int group, int num);
    Q_INVOKABLE int getLocationGroupNum();
    Q_INVOKABLE int getLocationGroupSize(int num);
    Q_INVOKABLE int getLocationGroupNum(int num);
    Q_INVOKABLE QString getLocationCallID(int num);

    Q_INVOKABLE void setLocationGroup(int num, int group);
    Q_INVOKABLE void removeLocationGroup(int num);
    Q_INVOKABLE void addLocationGroup(QString name);
    Q_INVOKABLE QString getLocGroupname(int num);
    Q_INVOKABLE void setLocation(int num, QString name, int group, int tablenum);

    Q_INVOKABLE float getLocationX(int num, QString type="");
    Q_INVOKABLE float getLocationY(int num, QString type="");
    Q_INVOKABLE float getLocationTH(int num, QString type="");

    Q_INVOKABLE bool isExistLocation(int group, int num);
    Q_INVOKABLE float getLidar(int num);

    Q_INVOKABLE bool getAnnotEditFlag();
    Q_INVOKABLE void setAnnotEditFlag(bool flag);

    Q_INVOKABLE void clearSharedMemory();

    //***********************************************************************Object(INI)..
    Q_INVOKABLE int getObjectNum();
    Q_INVOKABLE QString getObjectName(int num);
    Q_INVOKABLE int getObjectPointSize(int num);
    Q_INVOKABLE float getObjectX(int num, int point);
    Q_INVOKABLE float getObjectY(int num, int point);


    //***********************************************************************Object(NEW)..
    Q_INVOKABLE int getObjPointNum(int obj_num, int x, int y);
    Q_INVOKABLE int getLocNum(QString name);
    Q_INVOKABLE int getLocNum(int x, int y);

    Q_INVOKABLE void saveLocations();
    Q_INVOKABLE int getObjectSize(QString type);
    Q_INVOKABLE void removeObject(int num);
//    Q_INVOKABLE void removeLocation(QString name);

    //******************************************************************Travel line
    Q_INVOKABLE bool saveAnnotation(QString filename);

    Q_INVOKABLE bool isOdroid();


    Q_INVOKABLE int getMultiState();
    Q_INVOKABLE void drawingRunawayStart();
    Q_INVOKABLE void drawingRunawayStop();
    Q_INVOKABLE int getRunawayState();

    Q_INVOKABLE void slam_map_reload(QString filename, int mode=0);
    Q_INVOKABLE void slam_ini_reload();



    ////*********************************************  SCHEDULER(SERVING) 관련   ***************************************************////
    Q_INVOKABLE void setTray(int tray_num, int group, int table);
    Q_INVOKABLE void startServing();
    Q_INVOKABLE void setPreset(int preset);
    Q_INVOKABLE void confirmPickup();
    Q_INVOKABLE QList<int> getPickuptrays();



    ////*********************************************  ROBOT MOVE 관련   ***************************************************////
//    Q_INVOKABLE void moveTo(QString target_num);
    Q_INVOKABLE void movePause();
    Q_INVOKABLE void moveResume();
    Q_INVOKABLE void moveStopFlag();
    Q_INVOKABLE void moveStop();
    Q_INVOKABLE void moveToCharge();
    Q_INVOKABLE void moveToWait();
    Q_INVOKABLE void moveToCleaning();
    Q_INVOKABLE QString getcurLoc();
    Q_INVOKABLE QString getcurTable();

    Q_INVOKABLE void resetHomeFolders();

    Q_INVOKABLE bool issetLocation(int number);

    Q_INVOKABLE int getObsState(){return probot->obs_state;}
    ////*********************************************  ROBOT STATUS 관련   ***************************************************////
    Q_INVOKABLE int getBattery();
    Q_INVOKABLE int getMotorState();
    Q_INVOKABLE int getLocalizationState();
    Q_INVOKABLE int getStateMoving();
    Q_INVOKABLE int getErrcode();
    Q_INVOKABLE QString getRobotName();

    Q_INVOKABLE bool getMotorConnection(int id);
    Q_INVOKABLE int getMotorStatus(int id);
    Q_INVOKABLE QString getMotorStatusStr(int id);
    Q_INVOKABLE int getMotorTemperature(int id);
    Q_INVOKABLE int getMotorInsideTemperature(int id);
    Q_INVOKABLE int getMotorWarningTemperature();
    Q_INVOKABLE int getMotorCurrent(int id);
    Q_INVOKABLE int getPowerStatus();
    Q_INVOKABLE int getRemoteStatus();
    Q_INVOKABLE int getChargeStatus();
    Q_INVOKABLE int getEmoStatus();
    Q_INVOKABLE int getLockStatus();
    Q_INVOKABLE float getBatteryIn();
    Q_INVOKABLE float getBatteryOut();
    Q_INVOKABLE float getBatteryCurrent();
    Q_INVOKABLE float getPower();
    Q_INVOKABLE float getPowerTotal();
    Q_INVOKABLE int getObsinPath();
    Q_INVOKABLE int getRobotcurPreset();

    Q_INVOKABLE void setMotorLock(bool onoff);
    Q_INVOKABLE float getRobotRadius();
    Q_INVOKABLE float getRobotx();
    Q_INVOKABLE float getRoboty();
    Q_INVOKABLE float getRobotth();
    Q_INVOKABLE float getlastRobotx();
    Q_INVOKABLE float getlastRoboty();
    Q_INVOKABLE float getlastRobotth();

    Q_INVOKABLE int getPathNum();
    Q_INVOKABLE float getPathx(int num);
    Q_INVOKABLE float getPathy(int num);
    Q_INVOKABLE float getPathth(int num);
    Q_INVOKABLE int getLocalPathNum();
    Q_INVOKABLE float getLocalPathx(int num);
    Q_INVOKABLE float getLocalPathy(int num);

    Q_INVOKABLE int getuistate();

    ////*********************************************  MAP IMAGE 관련   ***************************************************////
    Q_INVOKABLE QString getMapname();
    Q_INVOKABLE QString getMappath();
    Q_INVOKABLE int getMapWidth();
    Q_INVOKABLE int getMapHeight();
    Q_INVOKABLE float getGridWidth();
    Q_INVOKABLE QList<int> getOrigin();
    Q_INVOKABLE int getMappingWidth(){return pmap->mapping_width;}
    Q_INVOKABLE float getMappingGridwidth(){return pmap->mapping_gridwidth;}

    ////*********************************************  OBJECTING 관련   ***************************************************////
    Q_INVOKABLE void startDrawObject();
    Q_INVOKABLE void stopDrawObject();
    Q_INVOKABLE void saveDrawObject();
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
    ////*********************************************  PATROL 관련   ***************************************************////
    QStringList patrol_list;
    Q_INVOKABLE void clearRotateList();
    Q_INVOKABLE void setRotateList(QString name);
    Q_INVOKABLE void startPatrol(QString mode, bool pickup);

    Q_INVOKABLE float getICPRatio();
    Q_INVOKABLE float getICPError();

    Q_INVOKABLE void clearFlagStop();
    Q_INVOKABLE void slam_fullautoInit();
    Q_INVOKABLE void moveToServingTest(int group, QString name);
    Q_INVOKABLE int getusberrorsize();
    Q_INVOKABLE QString getusberror(int num);
    Q_INVOKABLE int getzipstate();
    Q_INVOKABLE void clear_call();
    Q_INVOKABLE void usbsave(QString usb="", bool _ui=true, bool _slam=true, bool _config=true, bool _map=true, bool _log=true);

    Q_INVOKABLE void restartUpdate();
    Q_INVOKABLE void startUpdate();

    Q_INVOKABLE int getTravellineIssue();
    Q_INVOKABLE QString getTravellineIssueGroup(int num);
    Q_INVOKABLE QString getTravellineIssueName(int num);
    Q_INVOKABLE bool getTravellineIssueFar(int num);
    Q_INVOKABLE bool getTravellineIssueBroken(int num);
public slots:
    void onTimer();
    void path_changed();
    void camera_update();
    void mapping_update();
    void usb_detect();
    void git_pull_failed();
    void git_pull_success();
    void new_call();
    void process_accept(int cmd);
    void process_done(int cmd);
    void process_error(int cmd,int param);
    void process_timeout(int cmd);
    void update_success();
    void update_fail();
    void clear_all();
    void map_reset();
    void new_call_order(QString name);

private:
    QTimer *timer;
    QTimer *timer2;
    QTimer *wifiTimer;
    QNetworkSession *session;
    QQuickWindow *mMain;
    QObject *mObject = nullptr;
    QTranslator *translator;
};


#endif // SUPERVISOR_H
