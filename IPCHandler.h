#ifndef IPCHANDLER_H
#define IPCHANDLER_H

#include <QObject>
#include <QTimer>
#include <QSharedMemory>
#include "GlobalHeader.h"

class IPCHandler : public QObject
{
    Q_OBJECT
public:
    struct CMD
    {
        uint32_t tick = 0;
        int32_t cmd = 0;
        uint8_t params[255] = {0,};

        CMD()
        {
        }
        CMD(const CMD& p)
        {
            tick = p.tick;
            cmd = p.cmd;
            memcpy(params, p.params, 255);
        }
    };

    struct UI_STATUS{
        uint32_t tick = 0;
        float       ui_map_rotate_angle = 0;
        uint32_t    ui_cut_map_x = 0;
        uint32_t    ui_cut_map_y = 0;

        //uint8_t   ui_state = 0;
        UI_STATUS(){

        }
        UI_STATUS(const UI_STATUS& p){
            tick = p.tick;
            ui_map_rotate_angle = p.ui_map_rotate_angle;
            ui_cut_map_x = p.ui_cut_map_x;
            ui_cut_map_y = p.ui_cut_map_y;
            //ui_state = p.ui_state;
        }
    };

    struct STATUS
    {
        uint32_t   tick = 0;
        int8_t     connection_m0 = 0;
        int8_t     connection_m1 = 0;
        int8_t     status_m0 = 0;
        int8_t     status_m1 = 0;
        int8_t     temp_m0 = 0;
        int8_t     temp_m1 = 0;
        int8_t     temp_ex_m0 = 0;
        int8_t     temp_ex_m1 = 0;
        int8_t     cur_m0 = 0;
        int8_t     cur_m1 = 0;
        int8_t     status_charge = 0;
        int8_t     status_power = 0;
        int8_t     status_emo = 0;
        int8_t     status_remote = 0;
        float      bat_in = 0;
        float      bat_out = 0;
        float      bat_cur = 0;
        float      power = 0;
        float      total_power = 0;
        int8_t     ui_loc_state = 0;
        int8_t     ui_auto_state = 0;
        int8_t     ui_obs_state = 0;
        int8_t     ui_face_state = 0;
        int8_t     ui_cur_velocity_preset = 0;
        int8_t     ui_motor_lock_state = 0;

        float      robot_pose[3] = {0,};
        float      robot_scan[360] = {0,};

        int8_t     ui_draw_state = 0;
        int8_t      ui_multi_state = 0;//ready, moving, wait
        int8_t      ui_fail_state = 0;//kill
        STATUS()
        {
        }
        STATUS(const STATUS& p)
        {
            tick = p.tick;
            connection_m0 = p.connection_m0;
            connection_m1 = p.connection_m1;
            status_m0 = p.status_m0;
            status_m1 = p.status_m1;
            temp_m0 = p.temp_m0;
            temp_m1 = p.temp_m1;
            temp_ex_m0 = p.temp_ex_m0;
            temp_ex_m1 = p.temp_ex_m1;
            cur_m0 = p.cur_m0;
            cur_m1 = p.cur_m1;
            status_charge = p.status_charge;
            status_power = p.status_power;
            status_emo = p.status_emo;
            status_remote = p.status_remote;
            bat_in = p.bat_in;
            bat_out = p.bat_out;
            bat_cur = p.bat_cur;
            power = p.power;
            total_power = p.total_power;
            ui_loc_state = p.ui_loc_state;
            ui_auto_state = p.ui_auto_state;
            ui_obs_state = p.ui_obs_state;
            ui_face_state = p.ui_face_state;
            ui_cur_velocity_preset = p.ui_cur_velocity_preset;
            ui_motor_lock_state = p.ui_motor_lock_state;
            ui_draw_state = p.ui_draw_state;
            ui_multi_state = p.ui_multi_state;
            memcpy(robot_pose, p.robot_pose, sizeof(float)*3);
            memcpy(robot_scan, p.robot_scan, sizeof(float)*360);
            ui_fail_state = p.ui_fail_state;
        }
    };

    struct PATH
    {
        uint32_t tick = 0;
        int32_t num = 0;
        float x[512] = {0,};
        float y[512] = {0,};

        PATH()
        {
        }
        PATH(const PATH& p)
        {
            tick = p.tick;
            num = p.num;
            memcpy(x, p.x, sizeof(float)*512);
            memcpy(y, p.y, sizeof(float)*512);
        }
    };

    struct MAP
    {
        uint32_t tick = 0;
        uint32_t width = 1000;
        uint32_t height = 1000;
        uint8_t buf[1000*1000] = {0,};

        MAP()
        {
        }
        MAP(const MAP& p)
        {
            tick = p.tick;
            width = p.width;
            height = p.height;
            memcpy(buf, p.buf, 1000*1000);
        }
    };

    struct IMG
    {
        uint32_t tick = 0;
        uint8_t serial[255] = {0,};
        uint32_t width = 480;
        uint32_t height = 270;
        uint8_t buf[480*270] = {0,};

        IMG()
        {
        }
        IMG(const IMG& p)
        {
            tick = p.tick;
            width = p.width;
            height = p.height;
            memcpy(serial, p.serial, 255);
            memcpy(buf, p.buf, 480*270);
        }
    };

    struct IMG_COLOR
    {
        uint32_t tick = 0;
        uint8_t serial[255] = {0,};
        uint32_t width = 480;
        uint32_t height = 270;
        uint8_t buf[480*270*3] = {0,};

        IMG_COLOR()
        {
        }
        IMG_COLOR(const IMG_COLOR& p)
        {
            tick = p.tick;
            width = p.width;
            height = p.height;
            memcpy(serial, p.serial, 255);
            memcpy(buf, p.buf, 480*270*3);
        }
    };

    struct LOC_STATUS
    {
        uint32_t tick = 0;
        uint8_t serving[255] = {0,}; // array index means unique number of serving loc. occupied is 1

        LOC_STATUS()
        {
        }
        LOC_STATUS(const LOC_STATUS& p)
        {
            tick = p.tick;
            memcpy(serving, p.serving, 255);
        }
    };
    struct CALL_STATUS
    {
        uint32_t  tick = 0;
        uint8_t call_acceptable = 0;

        CALL_STATUS()
        {
        }
        CALL_STATUS(const CALL_STATUS& p)
        {
            tick = p.tick;
            call_acceptable = p.call_acceptable;
        }
    };
    struct CALL_LOC
    {
        uint32_t  tick = 0;
        int32_t loc_id = 0;

        CALL_LOC()
        {
        }
        CALL_LOC(const CALL_LOC& p)
        {
            tick = p.tick;
            loc_id = p.loc_id;
        }
    };
public:
    explicit IPCHandler(QObject *parent = nullptr);
    ~IPCHandler();

    void updateSharedMemory(QSharedMemory &mem, QString name, int size);
    void detachSharedMemory(QSharedMemory &mem, QString name);
    void clearSharedMemory(QSharedMemory &mem);
    void update();

    std::atomic<uint32_t> tick;
    bool flag_tx = false;
    bool flag_rx = false;
    bool flag_path = false;
    bool is_mapping = false;
    bool is_objecting = false;
    bool flag_mapping = false;
    bool flag_objecting = false;
    bool flag_joystick = false;

    QSharedMemory shm_cmd;
    QSharedMemory shm_status;
    QSharedMemory shm_path;
    QSharedMemory shm_map;
    QSharedMemory shm_obs;
    QSharedMemory shm_cam0;
    QSharedMemory shm_cam1;
    QSharedMemory shm_ui_status;
    QSharedMemory shm_cam_color0;
    QSharedMemory shm_cam_color1;
    QSharedMemory shm_loc_status;
    QSharedMemory shm_call_loc;
    QSharedMemory shm_call_status;

    CMD get_cmd();
    STATUS get_status();
    PATH get_path();
    MAP get_map();
    MAP get_obs();
    IMG get_cam0();
    IMG get_cam1();
    IMG_COLOR get_cam_color0();
    IMG_COLOR get_cam_color1();
    LOC_STATUS get_loc_status();
    CALL_LOC get_call_loc();


    bool getConnection(){
        if(read_count > 30){
            return false;
        }else{
            return true;
        }
    }

    void startObject();
    void stopObject();
    void saveObject();

    void set_cmd(IPCHandler::CMD val, QString log="");
    void set_cmd(int cmd, QString log="");
    void set_status_ui();

    void handsup();
    void handsdown();

    ////*********************************************  COMMAND FUNCTIONS   ***************************************************////
    void moveToLocation(LOCATION target_loc, int preset);
    void moveToLocationTest(LOCATION target_loc, int preset);
    void moveToResting(int preset);
    void moveToCharging(int preset);
    void moveToServing(QString target_loc, int preset);
    void moveTo(float x, float y, float th, int preset);
    void moveToTest(float x, float y, float th, int preset);
    void movePause();
    void moveResume();
    void moveJog();
    void moveStop();
    void moveManual();
    void setInitPose(float x, float y, float th);
    void sendCommand(int cmd);
    void setVelocity(float vel, float velth);
    void setVelocity(float vel);
    void sendMapPath(QString path);
    void saveMapping(QString name);
    void startMapping(int map_size, float grid_size);
    void stopMapping();
    void restartSLAM();
    void set_velocity(float vel);

    QString tempstr = "";
    int read_count = 50;
    unsigned int prev_tick_status = 0;
    unsigned int prev_tick_path = 0;
    unsigned int prev_tick_map = 0;
    unsigned int prev_tick_obs = 0;
    unsigned int prev_tick_cam0 = 0;
    unsigned int prev_tick_cam1 = 0;
    unsigned int prev_tick_cam_color0 = 0;
    unsigned int prev_tick_cam_color1 = 0;
    unsigned int prev_tick_loc_status = 0;
    unsigned int prev_tick_call_loc = 0;

signals:
    void pathchanged();
    void mappingin();
    void objectingin();
    void cameraupdate();

private slots:
    void onTimer();

private:
    QTimer *timer;

};

#endif // IPCHANDLER_H
