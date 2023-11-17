#ifndef LCMHANDLER_H
#define LCMHANDLER_H

#include <QObject>
#include <QThread>
#include <chrono>
#include <thread>
#include <QTimer>
#include <QDir>
#include <lcm/lcm-cpp.hpp>

#include "../lcm_types/command.hpp"
#include "../lcm_types/robot_status.hpp"
#include "../lcm_types/map_data.hpp"
#include "../lcm_types/robot_path.hpp"
#include "../lcm_types/camera_data.hpp"
#include "GlobalHeader.h"

class LCMHandler : public QObject
{
    Q_OBJECT
public:
    LCMHandler();
    ~LCMHandler();

    //LCM 관련
    lcm::LCM lcm;
    std::atomic<bool> bFlag;
    std::thread* bThread = NULL;
    lcm::Subscription *sub_status;
    lcm::Subscription *sub_path;
    lcm::Subscription *sub_localpath;
    lcm::Subscription *sub_mapping;
    lcm::Subscription *sub_objecting;
    lcm::Subscription *sub_camera;
    lcm::Subscription *sub_test_cmd;

    ////*********************************************  FLAGS   ***************************************************////
    //LCM 연결상태
    bool isconnect = false;
    int connect_count = 0;
    bool flag_tx = false;
    bool flag_rx = false;

    //맵 리퀘스트(프로그램 실행 시 1번 보냄)
    bool map_updated = false;

    //매핑 맵 저장 플래그
    bool flagMapping = false;
    bool is_mapping = false;

    //매핑 맵 저장 플래그
    bool flagObjecting = false;
    bool is_objecting = false;

    //조이스틱 명령 플래그
    bool flagJoystick = false;

    //Path 덮어쓰기 플래그
    bool flagPath = false;
    bool flagLocalPath = false;

    //로봇 이름이 달라졌을 때 subscribe 다시
    void subscribe();

    //mapping width
    int mapping_width;
    ////*********************************************  COMMAND FUNCTIONS   ***************************************************////
    void sendCommand(command cmd, QString msg, bool force=false);
    void sendCommand(int cmd, QString msg);
    void programStart();
    void moveToLast();
    void moveTo(QString target_loc);
    void moveTo(float x, float y, float th);
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
    void startMapping(float grid_size);
    void restartSLAM();
    void saveObjecting();
    void startObjecting();

    ////*********************************************  CALLBACK FUNCTIONS   ***************************************************////
    void robot_status_callback(const lcm::ReceiveBuffer *rbuf, const std::string &chan, const robot_status *msg);
    void robot_path_callback(const lcm::ReceiveBuffer *rbuf, const std::string &chan, const robot_path *msg);
    void robot_local_path_callback(const lcm::ReceiveBuffer *rbuf, const std::string &chan, const robot_path *msg);
    void robot_mapping_callback(const lcm::ReceiveBuffer *rbuf, const std::string &chan, const map_data *msg);
    void robot_objecting_callback(const lcm::ReceiveBuffer *rbuf, const std::string &chan, const map_data *msg);
    void robot_camera_callback(const lcm::ReceiveBuffer *rbuf, const std::string &chan, const camera_data *msg);
    void robot_command_callback(const lcm::ReceiveBuffer *rbuf, const std::string &chan, const command*msg);
    ////***********************************************   THREADS  ********************************************************////
    void bLoop();

signals:
    void pathchanged();
    void cameraupdate();
    void mappingin();
    void objectingin();

public slots:
    void onTimer();

private:
    QTimer  *timer;
};

#endif // LCMHANDLER_H
