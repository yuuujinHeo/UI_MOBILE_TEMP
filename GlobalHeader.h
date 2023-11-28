#ifndef GLOBALHEADER_H
#define GLOBALHEADER_H

#include "Logger.h"
#include <opencv2/opencv.hpp>
#include <QDir>
#include <QPixmap>
#include "MapHeader.h"
#include "cv_to_qt.h"


extern Logger *plog;
extern int ui_state;
extern bool is_debug;
extern QApplication *app;


typedef struct{
    QString serial;
    int imageSize = 0;
//    QList<int> data;
    cv::Mat data;
    QPixmap pixmap;
    int width;
    int height;
}ST_CAMERA;

typedef struct{
    QString commit;
    QString message;
    QString date;
}ST_GIT;

float setAxis(float _angle);
float setAxisBack(float _angle);
cv::Point2f setAxis(cv::Point2f _point);
cv::Point2f setAxisMapping(cv::Point2f _point);
cv::Point2f setAxisObject(cv::Point2f _point);
cv::Point2f setAxisBack(cv::Point2f _point);
POSE setAxis(POSE _pose);
POSE setAxisBack(POSE _pose);
POSE setAxis(cv::Point2f _point, float _angle);
POSE setAxisBack(cv::Point2f _point, float _angle);

bool sortLocation2(const LOCATION &l1, const LOCATION &l2);
bool sortWifi(const QString &w1, const QString &w2);

typedef struct{
    QString group;
    QString name;
    bool is_far;
    bool is_broken;
}ST_TLINE_CHECK;
enum{
    WIFI_NONE = 0,
    WIFI_CONNECTING,
    WIFI_CONNECT_NO_INTERNET,
    WIFI_CONNECT,
    WIFI_UNKNOWN
};
typedef struct{
    int chunkSize = 0;
    int imageSize = 0;
    QVector<int> data;
    QVector<int> data_objecting;
    QPixmap test_mapping;
    cv::Mat map_mapping;
    cv::Mat map_objecting;
    QPixmap test_objecting;

    QVector<ST_CAMERA> camera_info;
    QString left_camera;
    QString right_camera;

    QString map_name = "";
    QString map_path = "";
    int width = 1000;
    int height = 1000;
    float gridwidth = 0;
    int origin[2] = {0,};
    int edited_width = 1000;
    int edited_height = 1000;
    int edited_origin[2] = {0,};
    float robot_radius = 0.3;

    float map_rotate_angle = 0;
    int cut_map[4];
    int mapping_width = 1000;
    float mapping_gridwidth = 0.3;

    QStringList location_groups;
    QList<LOCATION> locations;
    QVector<QVector<cv::Point2f>> tlines;
    QVector<OBJECT> objects;

    QVector<cv::Point2f> list_obj_uL;
    QVector<cv::Point2f> list_obj_dR;

    float margin;
    bool use_uicmd;
    bool map_loaded;

    POSE init_pose;

    bool annotation_edited;
    bool annot_edit_object;
    bool annot_edit_drawing;
    bool annot_edit_location;
    bool annot_edit_tline;

    QPixmap map;

    int tline_issue = 0;
    ST_TLINE_CHECK tline_issues[5];
}ST_MAP;
extern ST_MAP *pmap;

typedef struct{
    bool connection = false;
    int status = 0;
    int temperature = 0;
    int motor_temp = 0;
    float current = 0;
}ST_MOTOR;
typedef struct{

    bool empty=true;
    LOCATION location;
}ST_TRAY;

typedef struct{
    bool inuse;
    QString ssid;
    int rate;
    int level;
    bool security;
    int discon_count;
    int state = 0;
    int prev_state=0;
}ST_WIFI;

typedef struct{
    bool ipc_use = false;
    //from Robot
    ST_MOTOR motor[2];

    int status_power = 0;
    int status_emo = 0;
    int status_remote = 0;
    int status_charge = 0;
    int status_lock = 0;

    QVector<float> bat_list;
    int battery_percent = 0;
    float battery = 0.;
    float battery_in = 0;
    float battery_out = 0;
    float battery_cur = 0;
    float power = 0;
    float total_power = 0;

    int multirobot_state = 0;
    int localization_state = 0;
    int running_state = 0;
    int obs_state = 0;
    int ui_fail_state = 0;
    int obs_in_path_state = 0;
    int robot_preset = 0;
    int drawing_state = 0;
    float map_rotate_angle = 0;

    int localization_confirm = 0;


    int err_code = 0;

    POSE curPose;
    POSE lastPose;
    QVector<int> pickupTrays;
    POSE curTarget;

    int pathSize =0;
    QVector<POSE> curPath;
    int localpathSize =0;
    POSE localPath[4];

    //mine
    QString name = "";
    QString model = "";
    int serial_num;
    QString name_debug = "";
    QString type = "SERVING";
    float velocity = 1.0;

    QVector<ST_TRAY> trays;
    bool is_calling=false;
    bool is_patrol = false;
    LOCATION curLocation;
    int cur_preset=3;
    int comeback_preset=3;
//    QVector<QString> call_list;

    int call_moving_count=0;
    int max_moving_count;
    float joystick[2];
    float lidar_data[360];
    float radius;

    int server_call_size=0;
    int server_call_location=-1;

    int volume_system = 50;
    QString program_version;
    QString program_date;
    QString program_message;
    QVector<ST_GIT> gitList;

    QMap<QString, ST_WIFI> wifi_map;
    int wifi_connection = 0;
    QString wifi_ssid = "";
    QString wifi_passwd = "";
    QString wifi_ip = "";
    QString wifi_gateway = "";
    QString wifi_dns = "";
    QString cur_ip="";
    QString cur_gateway="";
    QString cur_dns="";
}ST_ROBOT;
extern ST_ROBOT *probot;

typedef struct{
    QString message;
    QString commit;
    QString date;
    QString extension;
    bool file_exist = false;
}ST_UPDATE;

typedef struct{
    QString type;
    QString location;
    POSE pose;
}ST_PATROL;

typedef struct{
    QVector<ST_PATROL> path;
    QString filename;
    int mode;
}ST_PATROLMODE;

typedef struct{
    int tray_num;
    int travelline;
    int table_num;
    int table_col_num;

    int volumeSystem;
    int volumeBGM;
    int volumeVoice;
    bool useAvoid;
    bool useAutoInit;
    bool useVoice;
    bool useBGM;
    bool useTravelline;
    bool useServerCMD;
}ST_SETTING;

enum ROBOT_CMD{
    ROBOT_CMD_NONE = 0,
    ROBOT_CMD_MOVE_TARGET_EX,
    ROBOT_CMD_MOVE_TARGET,
    ROBOT_CMD_MOVE_JOG,
    ROBOT_CMD_MOVE_MANUAL,

    ROBOT_CMD_MOVE_STOP,//=5
    ROBOT_CMD_MOVE_PAUSE,
    ROBOT_CMD_MOVE_RESUME,
    ROBOT_CMD_SET_VELOCITY,
    ROBOT_CMD_RESTART,

    ROBOT_CMD_SET_INIT,//=10
    ROBOT_CMD_SLAM_RUN,
    ROBOT_CMD_SLAM_STOP,
    ROBOT_CMD_SLAM_AUTO,
    ROBOT_CMD_SLAM_FULL_AUTO,

    ROBOT_CMD_MAPPING_START,//=15
    ROBOT_CMD_MAPPING_STOP,
    ROBOT_CMD_REQ_CAMERA,
    ROBOT_CMD_MAPPING_SAVE,
    ROBOT_CMD_OBJECTING_START,

    ROBOT_CMD_OBJECTING_STOP,//20
    ROBOT_CMD_OBJECTING_SAVE,
    ROBOT_CMD_MOTOR_LOCK_OFF,
    ROBOT_CMD_MOTOR_LOCK_ON,
    ROBOT_CMD_DRAW_LINE_START,

    ROBOT_CMD_DRAW_LINE_SAVE,//25
    ROBOT_CMD_MAP_RELOAD,
    ROBOT_CMD_SETTING_RELOAD,
    ROBOT_CMD_SERVER_MAP_UPDATE,
    ROBOT_CMD_CHECK_TRAVEL_LINE

};

enum UI_CMD{
    UI_CMD_NONE = 0,
    UI_CMD_MOVE_SERVING,
    UI_CMD_PAUSE,
    UI_CMD_RESUME,
    UI_CMD_MOVE_RESTING,
    UI_CMD_MOVE_CHARGING//5
};

enum UI_STATE{
    UI_STATE_NONE = 0,
    UI_STATE_INITAILIZING,
    UI_STATE_SETTING,
    UI_STATE_RESTING,
    UI_STATE_CHARGING,

    UI_STATE_MOVING,//5
    UI_STATE_PICKUP,
    UI_STATE_MOVEFAIL,
    UI_STATE_CLEANING,
    UI_STATE_HANDS_UP
};

enum LOCALIZATION_STATE{
    LOCAL_NOT_READY = 0,
    LOCAL_START,
    LOCAL_READY,
    LOCAL_FAILED
};

enum{
    NOT_READY = 0,
    READY
};

enum ROBOT_MOVING_STATE{
    ROBOT_MOVING_NOT_READY = 0,
    ROBOT_MOVING_READY,
    ROBOT_MOVING_MOVING,
    ROBOT_MOVING_WAIT,
    ROBOT_MOVING_PAUSED
};

enum ROBOT_MULTI_STATE{
    MULTI_READY = 0,
    MULTI_MOVING,
    MULTI_WAIT
};

enum ROBOT_ERROR{
    ROBOT_ERROR_NONE = 0,
    ROBOT_ERROR_WAIT,
    ROBOT_ERROR_NO_PATH,
    ROBOT_ERROR_LOCALIZATION_FAILED
};

#endif // GLOBALHEADER_H
