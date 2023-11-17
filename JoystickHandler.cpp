#include "JoystickHandler.h"
#include <QDebug>
#include <iostream>
#include "Logger.h"
extern Logger *plog;

int		numAxis;
int		numButton;
char	nameJoy[80];

inline float max(float a, float b) {return (a>=b ? a : b);}
inline float min(float a, float b) {return (a>=b ? b : a);}

JoystickHandler::JoystickHandler(){
    connection = false;
    fdJoy = 0;

    for(int i=0; i<8; i++){
        JoyAxis[i] = 1;
    }
    for(int i=0; i<12; i++){
        JoyButton[i] = 0;
    }

    timer = new QTimer();
    connect(timer, SIGNAL(timeout()),this, SLOT(updatejoy()));
    timer->start(50);
}

JoystickHandler::~JoystickHandler(){
    close(fdJoy);
}

void JoystickHandler::CheckJoy(){
    if(connection){
        struct stat buf;
        if(stat(devName.toStdString().c_str(),&buf) == -1){
            plog->write("[JOYSTICK] DISCONNECTED");
            connection = false;
            close(fdJoy);
        }
    }
}

void JoystickHandler::ConnectJoy(const QString _devName){
    for(int i=0; i<8; i++){
        JoyAxis[i] = 0;
    }
    for(int i=0; i<12; i++){
        JoyButton[i] = 0;
    }
    devName = _devName;
    if((fdJoy = open(devName.toStdString().c_str(), O_RDONLY)) == -1){
        connection = false;
    }else if(!connection){
        int version;
        ioctl(fdJoy, JSIOCGVERSION, &version);
        ioctl(fdJoy, JSIOCGAXES, &numAxis);
        ioctl(fdJoy, JSIOCGBUTTONS, &numButton);
        ioctl(fdJoy, JSIOCGNAME(80), &nameJoy);

        plog->write("[JOYSTICK] CONNECTED : "+ QString(nameJoy) + QString().sprintf(" (%d, %d, %d)",version,numAxis,numButton));

        for(int i=0; i<8; i++){
            JoyAxis[i] = 1;
        }
        fcntl(fdJoy, F_SETFL, O_NONBLOCK);	// use non-blocking methods
        connection = true;
    }
}

int JoystickHandler::DisconnectJoy(){
    connection = false;
    close(fdJoy);
    return true;
}

float calc_joy(float in)
{
    float thres = 500;
    float MaxA = 30000;
    float td;
    if(in>thres)
    {
        td = min(1.0,(in-thres)/(MaxA-thres));
    }
    else if(in<-thres)
    {
        td = max(-1.0,(in+thres)/(MaxA-thres));
    }
    else
    {
        td = 0;
    }
    return td;
}

void JoystickHandler::updatejoy(){
    static int connect_count = 0;
    static int init_count = 0;
    if(connection == true){
        // read the joystick
        while((read(fdJoy, &(JoyEvent),sizeof(struct js_event))) > 0){
            qDebug() << JoyEvent.number << JoyEvent.value;
            switch(JoyEvent.type & ~JS_EVENT_INIT){
            case JS_EVENT_AXIS:
                if(JoyEvent.number < 8)
                {
                    (JoyAxis)[JoyEvent.number] = JoyEvent.value;
                }
                break;
            case JS_EVENT_BUTTON:
                if(JoyEvent.number < 12)
                {
                    (JoyButton)[JoyEvent.number] = JoyEvent.value;
                }
                break;
            }
        }
    }else{
        init_count = 0;
        if(connect_count%100 == 0){
            ConnectJoy("/dev/input/js0");
        }
    }

    if(connect_count++%100 == 0){
        CheckJoy();
    }
}
