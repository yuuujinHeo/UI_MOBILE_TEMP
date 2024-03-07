#include "checker.h"
#include <QTimer>
#include "QtDBus/QDBusInterface"
#include "QtDBus/QDBusConnection"
#include "QtDBus/QDBusReply"
#include "QtDBus/QDBusObjectPath"

void Worker::getWifiInterface(){
    process = new QProcess();
    process->start("iwlist", QStringList() << probot->wifi_interface.name << "scan");

    if(!process->waitForFinished()){
        emit finished(this);
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
//    plog->write("[WORKER - "+name+"] getWifiInterface : ");

    probot->wifi_list.clear();
    probot->wifi_list = wifiList;
    emit finished(this);
}
void Worker::getSystemVolume(){
    process = new QProcess();
    process->start("amixer",QStringList() << "-D" << "pulse" << "sget" << "Master");

    if(!process->waitForFinished()){
        emit finished(this);
        return;
    }

    QByteArray result = process->readAllStandardOutput();
    QList<QByteArray> lines = result.split('\n');

    for(QByteArray line : lines){
        if(line.contains("Front Left:")){
            QString percent = line.split('[')[1].split('%')[0];
            probot->volume_system = percent.toInt();
//            plog->write("[WORKER - "+name+"] Get System Volume : "+ QString::number(probot->volume_system));
            break;
        }
    }
    emit finished(this);
}
void Worker::setSystemVolume(){
    if(argument.size() > 0){
        QString volume = argument[0];
        process = new QProcess();
        if(volume == "0"){
            process->start("amixer",QStringList() << "-D" << "pulse" << "sset" << "Master" << volume+"%");
        }else{
            process->start("amixer",QStringList() << "-D" << "pulse" << "sset" << "Master" << volume+"%" << "unmute");
        }
        if(!process->waitForFinished()){
            emit finished(this);
            return;
        }

        QByteArray result = process->readAllStandardOutput();
        qDebug() << result;
        plog->write("[WORKER - "+name+"] Set System Volume : Done ("+volume+")");
    }
    emit finished(this);
}
void Worker::connectWifi(){
    QString ssid = "";
    QString passwd = "";
    if(argument.size() > 0){
        ssid = argument[0];
        if(argument.size() > 1){
            passwd = argument[1];
        }
    }
    process = new QProcess();
    if(passwd == ""){
        plog->write("[CHECKER] Connect Wifi : "+ssid+" passwd = none");
        process->start("sudo",QStringList()  << "-S" << "nmcli"  << "device" << "wifi" << "connect" << ssid);
    }else{
        plog->write("[CHECKER] Connect Wifi : "+ssid+" passwd = "+passwd);
        process->start("sudo",QStringList() << "-S" << "nmcli" << "device" << "wifi"<< "connect" << ssid << "password" << passwd);
    }

    connect(process,SIGNAL(readyReadStandardError()),this,SLOT(error_connect_wifi()));

    if(!process->waitForFinished()){
        emit connect_wifi_fail(3, argument[0]);
        emit finished(this);
        return;
    }

    QByteArray result = process->readAllStandardOutput();

    if(result.contains("successfully")){
        emit connect_wifi_success(argument[0]);
    }else if(result.contains("Secrets were required")){
        emit connect_wifi_fail(1, argument[0]);
    }else if(result.contains("failed:")){
        emit connect_wifi_fail(2, argument[0]);
    }else{
        emit connect_wifi_fail(0, argument[0]);
    }
    emit finished(this);
}

void Worker::setIP(){
    QString ssid = "";
    QString ip = "";
    QString subnet = "";
    QString gateway = "";
    QString dns1 = "";
    QString dns2 = "";
    if(argument.size() > 5){
        ssid = argument[0];
        ip = argument[1];
        subnet = argument[2];
        gateway = argument[3];
        dns1 = argument[4];
        dns2 = argument[5];
    }

    process = new QProcess();
    plog->write("[CHECKER] Set Wifi "+ssid+" : "+ip+"/"+subnet+" , "+gateway+" , "+dns1+" , "+dns2);
    process->start("nmcli",QStringList()  << "con" << "mod" << ssid << "ipv4.method" << "manual" << "ipv4.address" << ip+"/"+subnet << "ipv4.gateway" << gateway << "ipv4.dns" << dns1+" "+dns2);

    connect(process,SIGNAL(readyReadStandardError()),this,SLOT(error_set_wifi()));

    if(!process->waitForFinished()){
        emit set_wifi_fail(0, argument[0]);
        emit finished(this);
        return;
    }

    QByteArray result = process->readAllStandardOutput();

    process = new QProcess();
    plog->write("[CHECKER] Set Wifi "+ssid+" : Success -> Connection Update");
    process->start("nmcli",QStringList()  << "con" << "up" << ssid);

    if(!process->waitForFinished()){
        emit set_wifi_fail(0, argument[0]);
        emit finished(this);
        return;
    }
    result = process->readAllStandardOutput();
    emit set_wifi_success(argument[0]);
    emit finished(this);
}

void Worker::gitReset(){
    process = new QProcess();
    process->setWorkingDirectory(QDir::homePath()+"/RB_MOBILE/release");
    process->start("git",QStringList() << "reset" << "--hard" << "origin/master");

    connect(process,SIGNAL(readyReadStandardError()),this,SLOT(error_git_reset()));

    if(!process->waitForFinished()){
        emit finished(this);
        return;
    }
    QByteArray result = process->readAllStandardOutput();
    qDebug() << "Result : " << result;
    emit finished(this);
}

QString subnetToNetmask(QString subnetSize) {
    // Calculate netmask from subnet size
    int netmaskInt = (0xFFFFFFFF << (32 - subnetSize.toInt())) & 0xFFFFFFFF;
    return QString("%1.%2.%3.%4")
           .arg((netmaskInt >> 24) & 0xFF)
           .arg((netmaskInt >> 16) & 0xFF)
           .arg((netmaskInt >> 8) & 0xFF)
           .arg(netmaskInt & 0xFF);
}

QString netmaskToSubnet(const QString &netmask) {
    // Convert netmask from string to integer
    QStringList parts = netmask.split('.');
    if (parts.size() != 4) {
        qWarning() << "Invalid netmask format";
        return "0";
    }
    uint netmaskInt = 0;
    for (int i = 0; i < 4; ++i) {
        int octet = parts[i].toInt();
        if (octet < 0 || octet > 255) {
            qWarning() << "Invalid octet in netmask";
            return "0";
        }
        netmaskInt = (netmaskInt << 8) | octet;
    }

    // Calculate subnet size from netmask
    int subnetSize = 0;
    while (netmaskInt & 0x80000000) {
        subnetSize++;
        netmaskInt <<= 1;
    }
    return QString::number(subnetSize);
}

void Worker::getNetworkState(){
    process = new QProcess();
    QString name = "";
    bool all_search = false;
    if(argument.size()>0){
        name = argument[0];
        if(name == ""){
            all_search = true;
        }
    }else{
        all_search = true;
        name = "";
    }

    if(all_search){
        process->start("nmcli",QStringList()<< "device" << "show");
    }else{
        process->start("nmcli",QStringList()<< "device" << "show" << name);
    }

    if(!process->waitForFinished()){
        emit finished(this);
        return;
    }

    QByteArray result = process->readAllStandardOutput();
    QList<QByteArray> lines = result.split('\n');

    QString type;
    for(QByteArray line : lines){
        if(all_search){
            if(line.contains("GENERAL.DEVICE")){
                name = line.split(':')[1].replace(' ',"");
            }else if(line.contains("GENERAL.TYPE")){
                type = line.split(':')[1].replace(' ',"");
            }else if(line.contains("GENERAL.STATE")){
                if(line.contains("disconnected")){
                    continue;
                }else if(line.contains("connected")){

                }else{
                    continue;
                }
            }else if(line.contains("GENERAL.CONNECTION")){
                if(type == "wifi"){
                    probot->wifi_interface.name = name;
                    probot->wifi_interface.ssid = line.split(':')[1].replace(' ',"");
                }else if(type == "ethernet"){
                    probot->ethernet_interface.name = name;
                    probot->ethernet_interface.ssid = line.split(':')[1].replace(' ',"");
                }
            }else if(line.contains("IP4.ADDRESS")){
                if(name == probot->ethernet_interface.name){
                    probot->ethernet_interface.ipv4 = line.split(':')[1].replace(' ',"").split('/')[0];
                    probot->ethernet_interface.subnet = line.split(':')[1].replace(' ',"").split('/')[1];
                    probot->ethernet_interface.netmask = subnetToNetmask(probot->ethernet_interface.subnet);
                }else if(name == probot->wifi_interface.name){
                    probot->wifi_interface.ipv4 = line.split(':')[1].replace(' ',"").split('/')[0];
                    probot->wifi_interface.subnet = line.split(':')[1].replace(' ',"").split('/')[1];
                    probot->wifi_interface.netmask = subnetToNetmask(probot->wifi_interface.subnet);
                }
            }else if(line.contains("IP4.GATEWAY")){
                if(name == probot->ethernet_interface.name){
                    probot->ethernet_interface.gateway = line.split(':')[1].replace(' ',"").split('/')[0];
                }else if(name == probot->wifi_interface.name){
                    probot->wifi_interface.gateway = line.split(':')[1].replace(' ',"").split('/')[0];
                }
            }else if(line.contains("IP4.DNS[1]")){
                if(name == probot->ethernet_interface.name){
                    probot->ethernet_interface.dns1 = line.split(':')[1].replace(' ',"").split('/')[0];
                    probot->ethernet_interface.dns2 = "";
                }else if(name == probot->wifi_interface.name){
                    probot->wifi_interface.dns1 = line.split(':')[1].replace(' ',"").split('/')[0];
                    probot->wifi_interface.dns2 = "";
                }
            }else if(line.contains("IP4.DNS[2]")){
                if(name == probot->ethernet_interface.name){
                    probot->ethernet_interface.dns2 = line.split(':')[1].replace(' ',"").split('/')[0];
                }else if(name == probot->wifi_interface.name){
                    probot->wifi_interface.dns2 = line.split(':')[1].replace(' ',"").split('/')[0];
                }
            }
        }else{
            if(line.contains("IP4.ADDRESS")){
                if(name == probot->ethernet_interface.name){
                    probot->ethernet_interface.ipv4 = line.split(':')[1].replace(' ',"").split('/')[0];
                    probot->ethernet_interface.subnet = line.split(':')[1].replace(' ',"").split('/')[1];
                    probot->ethernet_interface.netmask = subnetToNetmask(probot->ethernet_interface.subnet);
                }else if(name == probot->wifi_interface.name){
                    probot->wifi_interface.ipv4 = line.split(':')[1].replace(' ',"").split('/')[0];
                    probot->wifi_interface.subnet = line.split(':')[1].replace(' ',"").split('/')[1];
                    probot->wifi_interface.netmask = subnetToNetmask(probot->wifi_interface.subnet);
                }
            }else if(line.contains("IP4.GATEWAY")){
                if(name == probot->ethernet_interface.name){
                    probot->ethernet_interface.gateway = line.split(':')[1].replace(' ',"").split('/')[0];
                }else if(name == probot->wifi_interface.name){
                    probot->wifi_interface.gateway = line.split(':')[1].replace(' ',"").split('/')[0];
                }
            }else if(line.contains("IP4.DNS[1]")){
                if(name == probot->ethernet_interface.name){
                    probot->ethernet_interface.dns1 = line.split(':')[1].replace(' ',"").split('/')[0];
                    probot->ethernet_interface.dns2 = "";
                }else if(name == probot->wifi_interface.name){
                    probot->wifi_interface.dns1 = line.split(':')[1].replace(' ',"").split('/')[0];
                    probot->wifi_interface.dns2 = "";
                }
            }else if(line.contains("IP4.DNS[2]")){
                if(name == probot->ethernet_interface.name){
                    probot->ethernet_interface.dns2 = line.split(':')[1].replace(' ',"").split('/')[0];
                }else if(name == probot->wifi_interface.name){
                    probot->wifi_interface.dns2 = line.split(':')[1].replace(' ',"").split('/')[0];
                }
            }
        }
    }

    qDebug() << probot->wifi_interface.ssid << probot->wifi_interface.ipv4 << probot->wifi_interface.dns1 << probot->ethernet_interface.name;

    emit finished(this);
}
void Worker::gitPull(){
    process = new QProcess();
    process->setWorkingDirectory(QDir::homePath()+"/RB_MOBILE");
    plog->write("[UPDATE] Git Pull : Start");
    process->start("git",QStringList()<<"submodule" << "update" <<"--remote");

    connect(process,SIGNAL(readyReadStandardError()),this,SLOT(error_git_pull()));

    if(!process->waitForFinished()){
        emit finished(this);
        return;
    }
    QByteArray result = process->readAllStandardOutput();
    if(result.contains("error:")){
        plog->write("[UPDATE] Git Pull : Failed");
    }else{
        plog->write("[UPDATE] Git Pull : Success");
    }
    qDebug() << "Result : " << result;
    emit finished(this);
}

void Worker::checkPing(){
    QString hostname = "www.google.com";
    if(argument.size() > 0){
        hostname = argument[0];
    }
    process = new QProcess();
    process->start("ping",QStringList()<< "-c" << "1" << hostname);

    connect(process,SIGNAL(readyReadStandardError()),this,SLOT(error_git_pull()));

    if(!process->waitForFinished(1000)){
        probot->con_internet = false;
        emit finished(this);
        return;
    }
    QByteArray result = process->readAllStandardOutput();
    if (result.contains("1 received")) {
        probot->con_internet = true;
    } else {
        probot->con_internet = false;
    }
    emit finished(this);
}

void Worker::startMonitorNetwork(){
    process = new QProcess();
    plog->write("[CHECKER] Start Monitor Network");
    process->start("nmcli",QStringList()<<"m");
    connect(process,SIGNAL(readyReadStandardOutput()),this,SLOT(network_output()));
}

void Worker::network_output(){
    QByteArray output = process->readAllStandardOutput();
    QList<QByteArray> lines = output.split('\n');

    for(QByteArray line : lines){
        if(line.contains(':')){
            QString name = line.split(':')[0];
            QString state = line.split(':')[1];
            if(name == probot->ethernet_interface.name){
                if(state.contains("disconnected") || state.contains("unavailable")){
                    plog->write("[NETWORK] Ethernet ("+name+") : Unavailable or Disconnected");
                    probot->ethernet_interface.state = NET_DISCON;
                }else if(state.contains("connected")){
                    plog->write("[NETWORK] Ethernet ("+name+") : Connected");
                    probot->ethernet_interface.state = NET_CON;
                }else if(state.contains("connecting")){
                    plog->write("[NETWORK] Ethernet ("+name+") : Connecting");
                    probot->ethernet_interface.state = NET_CONNECTING;
                }
            }else if(name == probot->wifi_interface.name){
                if(state.contains("disconnected") || state.contains("unavailable")){
                    plog->write("[NETWORK] Wifi ("+name+") : Unavailable or Disconnected");
                    probot->wifi_interface.state = NET_DISCON;
                }else if(state.contains("connected")){
                    plog->write("[NETWORK] Wifi ("+name+") : Connected");
                    probot->wifi_interface.state = NET_CON;
                }else if(state.contains("connecting")){
                    plog->write("[NETWORK] Wifi ("+name+") : Connecting");
                    probot->wifi_interface.state = NET_CONNECTING;
                }else if(state.contains("using connection")){
                    probot->wifi_interface.ssid = state.split('\'')[1].split('\'')[0];
                    plog->write("[NETWORK] Wifi ("+name+") : Using SSID "+probot->wifi_interface.ssid);
                }
            }
        }

        if(line.contains("Networkmanager is now in")){
            QString state = line.split('\'')[1].split('\'')[0];
            if(state == "connected"){
                plog->write("[NETWORK] Networkmanager : Connected");
                probot->con_internet2 = NET_CON;
            }else if(state == "disconnected"){
                plog->write("[NETWORK] Networkmanager : Disconnected");
                probot->con_internet2 = NET_DISCON;
            }else if(state == "connecting"){
                plog->write("[NETWORK] Networkmanager : Connecting");
                probot->con_internet2 = NET_CONNECTING;
            }
        }
    }
}

Checker::Checker(QObject *parent)
{
    thread_1 = new QThread();
    thread_2 = new QThread();
    thread_3 = new QThread();

    worker_3 = new Worker("PROCESS_3",thread_3);
    worker_3->moveToThread(thread_3);
    QObject::connect(thread_3, &QThread::started, worker_3, &Worker::startMonitorNetwork);
    thread_3->start();
    QObject::connect(worker_3, &Worker::change_network, this, &Checker::change_network);

    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &Checker::onTimer);
    timer->start(100);
}

void Checker::change_network(QString line){

}

Checker::~Checker(){
    delete thread_1;
    delete thread_2;
    delete thread_3;
    delete worker_1;
    delete worker_2;
    delete worker_3;
}

void Checker::onTimer(){
    if(cmd_list.size() > 0){
        if(thread_1->isRunning()){
            if(thread_2->isRunning()){
            }else{
                worker_2 = new Worker("PROCESS_2",thread_2);
                worker_2->moveToThread(thread_2);
                worker_2->setWork(cmd_list[0].cmd,cmd_list[0].arg);
                worker_2->setProperties(cmd_list[0].print);

                setWork(cmd_list[0], thread_2, worker_2);
                cmd_list.pop_front();
                thread_2->start();
                QObject::connect(worker_2, &Worker::finished, thread_2, &QThread::quit);
                QObject::connect(worker_2, &Worker::finished, this, &Checker::disWork);
            }
        }else{
            worker_1 = new Worker("PROCESS_1",thread_1);
            worker_1->moveToThread(thread_1);
            worker_1->setWork(cmd_list[0].cmd,cmd_list[0].arg);
            worker_1->setProperties(cmd_list[0].print);
            setWork(cmd_list[0], thread_1, worker_1);
            cmd_list.pop_front();
            thread_1->start();
            QObject::connect(worker_1, &Worker::finished, thread_1, &QThread::quit);
            QObject::connect(worker_1, &Worker::finished, this, &Checker::disWork);

        }
    }
}

void Checker::getPing(QString host){
    for(ST_PROC p : cmd_list){
        if(p.name == "checkPing"){
            return;
        }
    }

    ST_PROC proc;
    proc.name = "checkPing";
    proc.cmd = "checkPing";
    proc.arg = QStringList()<<host;
    proc.print = false;
    cmd_list.append(proc);
}
void Checker::getCurrentInterface(){
    getPing("www.google.com");
    getNetworkState();
}
void Checker::disWork(Worker *worker){
    if(worker->program == "getWifiList"){
        QObject::disconnect(worker->parent_thread, &QThread::started, worker, &Worker::getWifiInterface);
    }else if(worker->program == "getSystemVolume"){
        QObject::disconnect(worker->parent_thread, &QThread::started, worker, &Worker::getSystemVolume);
    }else if(worker->program == "setSystemVolume"){
        QObject::disconnect(worker->parent_thread, &QThread::started, worker, &Worker::setSystemVolume);
    }else if(worker->program == "connectWifi"){
        QObject::disconnect(worker->parent_thread, &QThread::started, worker, &Worker::connectWifi);
        QObject::disconnect(worker, &Worker::connect_wifi_success, this, &Checker::connect_wifi_success);
        QObject::disconnect(worker, &Worker::connect_wifi_fail, this, &Checker::connect_wifi_fail);
    }else if(worker->program == "setIP"){
        QObject::disconnect(worker->parent_thread, &QThread::started, worker, &Worker::setIP);
        QObject::disconnect(worker, &Worker::set_wifi_success, this, &Checker::set_wifi_success);
        QObject::disconnect(worker, &Worker::set_wifi_fail, this, &Checker::set_wifi_fail);
    }else if(worker->program == "getNetworkState"){
        QObject::disconnect(worker->parent_thread, &QThread::started, worker, &Worker::getNetworkState);
    }else if(worker->program == "checkPing"){
        QObject::disconnect(worker->parent_thread, &QThread::started, worker, &Worker::checkPing);
    }else if(worker->program == "gitPull"){
        QObject::disconnect(worker->parent_thread, &QThread::started, worker, &Worker::gitPull);
    }else{

    }
}
void Checker::setWork(ST_PROC cmd, QThread *thread, Worker *worker){
    if(cmd.cmd == "getWifiList"){
        QObject::connect(thread, &QThread::started, worker, &Worker::getWifiInterface);
    }else if(cmd.cmd == "getSystemVolume"){
        QObject::connect(thread, &QThread::started, worker, &Worker::getSystemVolume);
    }else if(cmd.cmd == "setSystemVolume"){
        QObject::connect(thread, &QThread::started, worker, &Worker::setSystemVolume);
    }else if(cmd.cmd == "connectWifi"){
        QObject::connect(thread, &QThread::started, worker, &Worker::connectWifi);
        QObject::connect(worker, &Worker::connect_wifi_success, this, &Checker::connect_wifi_success);
        QObject::connect(worker, &Worker::connect_wifi_fail, this, &Checker::connect_wifi_fail);
    }else if(cmd.cmd == "setIP"){
        QObject::connect(thread, &QThread::started, worker, &Worker::setIP);
        QObject::connect(worker, &Worker::set_wifi_success, this, &Checker::set_wifi_success);
        QObject::connect(worker, &Worker::set_wifi_fail, this, &Checker::set_wifi_fail);

    }else if(cmd.cmd == "checkPing"){
        QObject::connect(thread, &QThread::started, worker, &Worker::checkPing);

    }else if(cmd.cmd == "getNetworkState"){
        QObject::connect(thread, &QThread::started, worker, &Worker::getNetworkState);

    }else if(cmd.cmd == "gitPull"){
        QObject::connect(thread, &QThread::started, worker, &Worker::gitPull);
//        QObject::connect(worker, &Worker::set_wifi_success, this, &Checker::set_wifi_success);
//        QObject::connect(worker, &Worker::set_wifi_fail, this, &Checker::set_wifi_fail);

    }else{
    }
}

void Checker::connect_wifi_success(QString ssid){
    plog->write("[CHECKER] Connect Wifi Success : "+ssid);
}

void Checker::connect_wifi_fail(int reason,QString ssid){
    if(reason == 1){
        plog->write("[CHECKER] Connect Wifi Failed : Password Failed "+ssid);
    }else if(reason == 2){
        plog->write("[CHECKER] Connect Wifi Failed : Connection Failed "+ssid);
    }else if(reason == 3){
        plog->write("[CHECKER] Connect Wifi Failed : Command ignored "+ssid);
    }else if(reason == 4){
        plog->write("[CHECKER] Connect Wifi Failed : Can't found SSID "+ssid);
    }else{
        plog->write("[CHECKER] Connect Wifi Failed : Unknown "+QString::number(reason)+"  "+ssid);
    }
}

void Checker::set_wifi_success(QString ssid){
    plog->write("[CHECKER] Set Wifi Success : "+ssid);
}

void Checker::set_wifi_fail(int reason,QString ssid){
    if(reason == 1){
        plog->write("[CHECKER] Set Wifi Failed : Error "+ssid);
    }else{
        plog->write("[CHECKER] Set Wifi Failed : Unknown "+ssid);
    }
}

void Checker::setSystemVolume(int volume){
    for(ST_PROC p : cmd_list){
        if(p.name == "setSystemVolume"){
            return;
        }
    }

    ST_PROC proc;
    proc.name = "setSystemVolume";
    proc.cmd = "setSystemVolume";
    proc.arg = QStringList() << QString::number(volume);
    proc.print = false;
    cmd_list.append(proc);
}

void Checker::getSystemVolume(){
    for(ST_PROC p : cmd_list){
        if(p.name == "getSystemVolume"){
            return;
        }
    }

    ST_PROC proc;
    proc.name = "getSystemVolume";
    proc.cmd = "getSystemVolume";
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

            probot->ethernet_interface.ipv4 = "";
            probot->ethernet_interface.netmask = "";

            foreach (const QNetworkAddressEntry &entry, addressEntries) {
                if(entry.ip().protocol() == QAbstractSocket::IPv4Protocol){
                    probot->ethernet_interface.state = NET_CON;
                    probot->ethernet_interface.ipv4 = entry.ip().toString();
                    probot->ethernet_interface.netmask = entry.netmask().toString();
                }
            }
        }else if(interface.type() == QNetworkInterface::Wifi){
            probot->wifi_interface.name = interface.name();
            probot->wifi_interface.type = interface.type();

            // 이 인터페이스의 IP 주소 목록을 가져옴
            QList<QNetworkAddressEntry> addressEntries = interface.addressEntries();

            probot->wifi_interface.ipv4 = "";
            probot->wifi_interface.netmask = "";

            foreach (const QNetworkAddressEntry &entry, addressEntries) {
                if(entry.ip().protocol() == QAbstractSocket::IPv4Protocol){
                    probot->wifi_interface.state = NET_CON;
                    probot->wifi_interface.ipv4 = entry.ip().toString();
                    probot->wifi_interface.netmask = entry.netmask().toString();
                }
            }
        }
    }

//    qDebug() << "getNetworkState " << probot->ethernet_interface.name << probot->wifi_interface.name;
}

void Checker::getNetworkState(QString name){
    for(ST_PROC p : cmd_list){
        if(p.name == "getNetworkState"){
            return;
        }
    }

    ST_PROC proc;
    proc.name = "getNetworkState";
    proc.cmd = "getNetworkState";
    proc.arg = QStringList() << name;
    cmd_list.append(proc);
}

void Checker::getWifiList(){
    for(ST_PROC p : cmd_list){
        if(p.name == "getWifiList"){
            return;
        }
    }

    ST_PROC proc;
    proc.name = "getWifiList";
    proc.cmd = "getWifiList";
    proc.arg = QStringList();// << "grep" << "-o" << "'^[z-zA-Z0-9]*'";
    cmd_list.append(proc);
}

void Checker::connectWifi(QString ssid, QString passwd){
    for(ST_PROC p : cmd_list){
        if(p.name == "connectWifi"){
            return;
        }
    }

    ST_PROC proc;
    proc.cmd = "connectWifi";
    proc.arg = QStringList() << ssid << passwd;
    proc.print = false;
    cmd_list.append(proc);
}

void Checker::setIP(QString ssid, QString ip, QString subnet, QString gateway, QString dns1, QString dns2){
    for(ST_PROC p : cmd_list){
        if(p.name == "setIP"){
            return;
        }
    }

    ST_PROC proc;
    proc.cmd = "setIP";
    proc.arg = QStringList() << ssid << ip << subnet << gateway << dns1 << dns2;
    proc.print = false;
    cmd_list.append(proc);
}

void Checker::gitPull(){
    for(ST_PROC p : cmd_list){
        if(p.name == "gitPull"){
            return;
        }
    }
    ST_PROC proc;
    proc.cmd = "gitPull";
    proc.arg = QStringList();
    proc.print = false;
    cmd_list.append(proc);

}
