#include "checker.h"
#include <QTimer>


void Worker::runProcess(){
    if(is_print)
        plog->write("["+name+"] RunProcress : "+program);

    process = new QProcess();
    process->start(program, argument);

    connect(process,&QProcess::readyReadStandardOutput,this,&Worker::output);
    connect(process,&QProcess::readyReadStandardError,this,&Worker::error);

    if(!process->waitForFinished()){
        if(is_print)
            plog->write("["+name+"] ProcessFailed : "+program);
        return;
    }
    if(is_print)
        plog->write("["+name+"] ProcessFinished : "+program+" -> "+QString::number(process->exitCode()));
    emit finished();

}

void Worker::getWifiInterface(){
    process = new QProcess();
    process->start("iwlist", QStringList() << probot->wifi_interface.name << "scan");

    if(!process->waitForFinished()){
        emit finished();
        return;
    }

    QByteArray result = process->readAllStandardOutput();
    QList<QByteArray> lines = result.split('\n');

    QList<ST_WIFI> wifiList;

    QMap<QString, QString> wifiinfo;

    for(QByteArray line : lines){
        if(line.contains("Cell") && line.contains("Address")){
            if(wifiinfo.size() > 0){
                ST_WIFI temp_wifi;
                temp_wifi.ssid = wifiinfo["ESSID"];
                temp_wifi.level = wifiinfo["LEVEL"].split(" ")[0].toInt();
                if(wifiinfo["SECURITY"] == "on"){
                    temp_wifi.security = true;
                }else{
                    temp_wifi.security = false;
                }

                bool match = false;
                for(int i=0; i<wifiList.size(); i++){
                    if(wifiList[i].ssid == temp_wifi.ssid){
                        if(temp_wifi.level > wifiList[i].level){
                            wifiList[i].level = temp_wifi.level;
                        }
                        match = true;
                    }
                }
                if(!match){
                    wifiList.append(temp_wifi);
                }
            }
            wifiinfo.clear();
        }
        if(line.contains("ESSID")){
            QString temp = QString::fromUtf8(line.split('"')[1]);
            wifiinfo["ESSID"]=temp;
        }else if(line.contains("Encryption key")){
            QString temp = QString::fromUtf8(line.split(':')[1]);
            wifiinfo["SECURITY"]=temp;
        }else if(line.contains("Signal level")){
            QString temp = QString::fromUtf8(line.split('-')[1].split(' ')[0]);
            int lv = temp.toInt();
            if(lv > 70){
                lv = 0;
            }else if(lv > 60){
                lv = 1;
            }else if(lv > 50){
                lv = 2;
            }else if(lv > 40){
                lv = 3;
            }else{
                lv = 4;
            }
            wifiinfo["LEVEL"]=QString::number(lv);
        }
    }

    probot->wifi_list.clear();
    probot->wifi_list = wifiList;
    emit finished();
}
void Worker::getSystemVolume(){
    process = new QProcess();
    process->start("amixer",QStringList() << "-D" << "pulse" << "sget" << "Master");

    if(!process->waitForFinished()){
        emit finished();
        return;
    }

    QByteArray result = process->readAllStandardOutput();
    QList<QByteArray> lines = result.split('\n');

    for(QByteArray line : lines){
        if(line.contains("Front Left")){
            QString percent = line.split('[')[1].split('%')[0];
            probot->volume_system = percent.toInt();
            plog->write("[RETURN] Get System Volume : "+probot->volume_system);
            break;
        }
    }
    emit finished();
}
Checker::Checker(QObject *parent)
{
    thread_1 = new QThread();
    thread_2 = new QThread();
    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &Checker::onTimer);
    timer->start(100);
}

Checker::~Checker(){
}

void Checker::onTimer(){
    if(cmd_list.size() > 0){
        if(thread_1->isRunning()){
            if(thread_2->isRunning()){
            }else{
                worker_2 = new Worker("PROCESS_2");
                worker_2->moveToThread(thread_2);
                worker_2->setWork(cmd_list[0].cmd,cmd_list[0].arg);
                worker_2->setProperties(cmd_list[0].print);
                if(cmd_list[0].name == "getWifiList"){
                    QObject::connect(thread_2, &QThread::started, worker_2, &Worker::getWifiInterface);
                }else{
                    QObject::connect(thread_2, &QThread::started, worker_2, &Worker::runProcess);
                }
                cmd_list.pop_front();
                QObject::connect(worker_2, &Worker::finished, thread_2, &QThread::quit);
                thread_2->start();
            }
        }else{
            worker_1 = new Worker("PROCESS_1");
            worker_1->moveToThread(thread_1);
            worker_1->setWork(cmd_list[0].cmd,cmd_list[0].arg);
            worker_1->setProperties(cmd_list[0].print);
            if(cmd_list[0].name == "getWifiList"){
                QObject::connect(thread_1, &QThread::started, worker_1, &Worker::getWifiInterface);
            }else{
                QObject::connect(thread_1, &QThread::started, worker_1, &Worker::runProcess);
            }
            cmd_list.pop_front();
            QObject::connect(worker_1, &Worker::finished, thread_1, &QThread::quit);
            thread_1->start();
        }
    }
}

void Checker::getSystemVolume(){
    for(ST_PROC p : cmd_list){
        if(p.name == "getSystemVolume"){
            return;
        }
    }

    ST_PROC proc;
    proc.name = "getSystemVolume";
    proc.cmd = "amixer";
    proc.arg = QStringList() << "-D" << "pulse" << "sget" << "Master";
    proc.print = false;
    cmd_list.append(proc);
}

void Checker::getNetworkState(){
    QList<QNetworkInterface> interfaces = QNetworkInterface::allInterfaces();
    foreach (const QNetworkInterface &interface, interfaces) {
        if(interface.type() == QNetworkInterface::Ethernet){
            probot->ethernet_interface.name = interface.name();
            probot->ethernet_interface.type = interface.type();

            // 이 인터페이스의 IP 주소 목록을 가져옴
            QList<QNetworkAddressEntry> addressEntries = interface.addressEntries();

            probot->ethernet_interface.connect = false;
            probot->ethernet_interface.ipv4 = "";
            probot->ethernet_interface.netmask = "";

            foreach (const QNetworkAddressEntry &entry, addressEntries) {
                if(entry.ip().protocol() == QAbstractSocket::IPv4Protocol){
                    probot->ethernet_interface.connect = true;
                    probot->ethernet_interface.ipv4 = entry.ip().toString();
                    probot->ethernet_interface.netmask = entry.netmask().toString();
                }
            }
        }else if(interface.type() == QNetworkInterface::Wifi){
            probot->ethernet_interface.name = interface.name();
            probot->ethernet_interface.type = interface.type();

            // 이 인터페이스의 IP 주소 목록을 가져옴
            QList<QNetworkAddressEntry> addressEntries = interface.addressEntries();

            probot->wifi_interface.connect = false;
            probot->wifi_interface.ipv4 = "";
            probot->wifi_interface.netmask = "";

            foreach (const QNetworkAddressEntry &entry, addressEntries) {
                if(entry.ip().protocol() == QAbstractSocket::IPv4Protocol){
                    probot->wifi_interface.connect = true;
                    probot->wifi_interface.ipv4 = entry.ip().toString();
                    probot->wifi_interface.netmask = entry.netmask().toString();
                }
            }
        }
    }
}

void Checker::getWifiList(){
    for(ST_PROC p : cmd_list){
        if(p.name == "getWifiList"){
            return;
        }
    }

    ST_PROC proc;
    proc.name = "getWifiList";
    proc.cmd = "iwconfig";
    proc.arg = QStringList();// << "grep" << "-o" << "'^[z-zA-Z0-9]*'";
    cmd_list.append(proc);
}

