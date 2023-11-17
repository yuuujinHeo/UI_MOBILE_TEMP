#ifndef IPC_H
#define IPC_H

#include <QObject>
#include <QSharedMemory>

class IPC : public QObject
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

    struct UI_STATUS
    {
        uint32_t  tick = 0;
        float     ui_map_rotated_angle = 0;
        uint32_t    ui_cut_map_x = 0;
        uint32_t    ui_cut_map_y = 0;

        UI_STATUS()
        {
        }
        UI_STATUS(const UI_STATUS& p)
        {
            tick = p.tick;
            ui_map_rotated_angle = p.ui_map_rotated_angle;
            ui_cut_map_x = p.ui_cut_map_x;
            ui_cut_map_y = p.ui_cut_map_y;
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
            memcpy(robot_pose, p.robot_pose, sizeof(float)*3);
            memcpy(robot_scan, p.robot_scan, sizeof(float)*360);
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


public:
    explicit IPC(QObject *parent = nullptr);
    ~IPC();

    std::atomic<uint32_t> tick;

    QSharedMemory shm_cmd;
    QSharedMemory shm_ui_status;
    QSharedMemory shm_status;
    QSharedMemory shm_path;
    QSharedMemory shm_map;
    QSharedMemory shm_obs;
    QSharedMemory shm_cam0;
    QSharedMemory shm_cam1;
    QSharedMemory shm_cam_color0;
    QSharedMemory shm_cam_color1;

    CMD get_cmd();
    UI_STATUS get_ui_status();
    STATUS get_status();
    PATH get_path();
    MAP get_map();
    MAP get_obs();
    IMG get_cam0();
    IMG get_cam1();
    IMG_COLOR get_cam_color0();
    IMG_COLOR get_cam_color1();

    void set_cmd(IPC::CMD val);
    void set_ui_status(IPC::UI_STATUS val);
    void set_status(IPC::STATUS val);
    void set_path(IPC::PATH val);
    void set_map(IPC::MAP val);
    void set_obs(IPC::MAP val);
    void set_cam0(IPC::IMG val);
    void set_cam1(IPC::IMG val);
    void set_cam_color0(IPC::IMG_COLOR val);
    void set_cam_color1(IPC::IMG_COLOR val);

signals:

};

#endif // IPC_H
