#include "checker.h"
#include <QTimer>
#include "QtDBus/QDBusInterface"
#include "QtDBus/QDBusConnection"
#include "QtDBus/QDBusReply"
#include "QtDBus/QDBusObjectPath"

QString subnetToNetmask(QString subnetSize) {
    // Calculate netmask from subnet size
    int netmaskInt = (0xFFFFFFFF << (32 - subnetSize.toInt())) & 0xFFFFFFFF;
    return QString("%1.%2.%3.%4")
           .arg((netmaskInt >> 24) & 0xFF)
           .arg((netmaskInt >> 16) & 0xFF)
           .arg((netmaskInt >> 8) & 0xFF)
           .arg(netmaskInt & 0xFF);
}

//BJ - edit
QString netmaskToSubnet(const QString &netmask) {
    // Convert netmask from string to integer
    QStringList parts = netmask.split('.');
    if (parts.size() != 4) {
        qWarning() << "Invalid netmask format";
        return "0";
    }
    uint netmaskInt = 0;
    for (int i = 0; i < 4; ++i) {
        bool ok; //BJ
        int octet = parts[i].toInt(&ok);
        //if (!ok || octet < 0 || octet > 255) {
        if (!ok || octet > 255) {
            qWarning() << "Invalid octet in netmask";
            return "0";
        }
        netmaskInt = (netmaskInt << 8) | octet;
    }

    // Calculate subnet size from netmask
    int subnetSize = 0;
    bool zeroSeen = false; // BJ
    //while (netmaskInt & 0x80000000) {
    //    subnetSize++;
    //    netmaskInt <<= 1;
    //}
    for (int i = 0; i < 32; ++i) {
        if (netmaskInt & 0x80000000) {
            if (zeroSeen) {
                qWarning() << "Invalid netmask: non-contiguous bits";
                return "0";
            }
            subnetSize++;
        } else {
            zeroSeen = true;
        }
        netmaskInt <<= 1;
    }
    return QString::number(subnetSize);
}


bool sortWifi2(const ST_WIFI &w1, const ST_WIFI &w2){
    if(w1.ssid == probot->wifi_interface.ssid)
        return true;
    else if(w2.ssid == probot->wifi_interface.ssid)
        return false;
    else{
        return w2.level < w1.level;
    }
}

void Worker::getWifiInterface(){
    process = new QProcess();

    if(argument[0] == "readall"){
        process->start("nmcli", QStringList() << "dev"<< "wifi");
        if(!process->waitForFinished()){
            process->close();
            process->disconnect();
            process->deleteLater();
            // process = nullptr;
            emit finished(this);
            return;
        }
    }

    process->start("iwlist", QStringList() << probot->wifi_interface.name << "scan");

    if(!process->waitForFinished()){
        process->close();
        process->disconnect();
        process->deleteLater();
        // process = nullptr;
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
        }else if(line.contains("ESSID")){
            QByteArray temp = line.split('"')[1];
            if(temp.contains('\\\\x')){
                QByteArray t;
                for (int i = 0; i < temp.size(); ++i) {
                    if (temp[i] == '\\' && temp[i + 1] == 'x') {
                        bool ok;
                        char byte = temp.mid(i + 2, 2).toInt(&ok, 16);
                        if (ok) {
                            t.append(byte);
                            i += 3; // '\xNN'을 건너뜀
                        } else {
                            t.append(temp[i]);
                        }
                    } else {
                        t.append(temp[i]);
                    }
                }
                wifiinfo["ESSID"] = QString::fromUtf8(t);
            }else{
                wifiinfo["ESSID"]=QString::fromUtf8(temp);
            }
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

    std::sort(wifiList.begin(),wifiList.end(),sortWifi2);

    probot->wifi_list.clear();
    probot->wifi_list = wifiList;
    process->close();
    process->disconnect();
    process->deleteLater();
    process = nullptr;
    emit finished(this);
}


void Worker::getSystemVolume(){
    process = new QProcess();
    QString cmd = "pactl";
    QStringList lists = QStringList() << "list" << "sinks";
    process->start(cmd,lists);

    if(!process->waitForFinished()){
        process->close();
        process->disconnect();
        process->deleteLater();
        process = nullptr;
        emit finished(this);
        return;
    }

    QByteArray result = process->readAllStandardOutput();
    QList<QByteArray> lines = result.split('\n');

    QString temp = "Name: "+getSettings("static","SOUND","default_sink");
    bool match=false;
    for(QByteArray line : lines){
        if(line.contains(temp.toUtf8())){
            // qDebug() << line;
            match=true;
        }else if(match && line.contains("Volume: front-left")){
            int num = line.split('/')[1].split('%')[0].toInt();
            // qDebug() << "num is = "<<num;
            probot->volume_system = num;
            break;
        }
    }
    // qDebug() << "---------------------------------------------------------------------------";
    // qDebug() << probot->volume_system << getSettings("static","SOUND","default_sink");

    process->close();
    process->disconnect();
    process->deleteLater();
    process = nullptr;
    emit finished(this);
}
void Worker::setSystemVolume(){
    if(argument.size() > 0){
        QString volume = argument[0];
        process = new QProcess();

        QString cmd = "pactl";
        QStringList lists = QStringList() << "set-sink-volume" << getSettings("static","SOUND","default_sink") << volume+"%";
        // qDebug() << "---------------------------------------------------------------------------";
        // qDebug() << cmd << lists << getSettings("static","SOUND","default_sink");
        process->start(cmd,lists);

        if(!process->waitForFinished()){
            process->close();
            process->disconnect();
            process->deleteLater();
            process = nullptr;
            emit finished(this);
            return;
        }

        QByteArray result = process->readAllStandardOutput();
        // qDebug() << result;
        plog->write("[WORKER - "+name+"] Set System Volume : Done ("+volume+")");
    }

    process->close();
    process->disconnect();
    process->deleteLater();
    process = nullptr;
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
        process->close();
        process->disconnect();
        process->deleteLater();
        // process = nullptr;
        emit finished(this);
        return;
    }

    QByteArray result = process->readAllStandardOutput();

    argument.clear();
    argument << ssid << "pass_finish";;

    if(result.contains("successfully")){
        emit connect_wifi_success(argument[0]);
    }else if(result.contains("Secrets were required")){
        emit connect_wifi_fail(1, argument[0]);
    }else if(result.contains("failed:")){
        emit connect_wifi_fail(2, argument[0]);
    }else{
        emit connect_wifi_fail(0, argument[0]);
    }

    process->close();
    process->disconnect();
    process->deleteLater();
    process = nullptr;

    getNetworkState();
    emit finished(this);
}

void Worker::setIP(){
    QString ssid = "";
    QString ip = "";
    QString subnet = "";
    QString gateway = "";
    QString dns1 = "";
    QString dns2 = "";
    QString method = "dhcp";
    if(argument.size() > 6){
        method = argument[0];
        ssid = argument[1];
        ip = argument[2];
        subnet = netmaskToSubnet(QString(argument[3]));
        gateway = argument[4];
        dns1 = argument[5];
        dns2 = argument[6];
    }



    process = new QProcess();
    plog->write("[CHECKER] Set Wifi "+ssid+" : ("+method+") "+ip+"/"+subnet+" , "+gateway+" , "+dns1+" , "+dns2);
    if(method == "dhcp"){
        process->start("nmcli",QStringList()  << "con" << "mod" << ssid << "ipv4.method" << "auto");
    }else{
        process->start("nmcli",QStringList()  << "con" << "mod" << ssid << "ipv4.method" << "manual" << "ipv4.address" << ip+"/"+subnet << "ipv4.gateway" << gateway << "ipv4.dns" << dns1+" "+dns2);

    }
    connect(process,SIGNAL(readyReadStandardError()),this,SLOT(error_set_wifi()));

    if(!process->waitForFinished()){
        emit set_wifi_fail(0, argument[0]);
        process->close();
        process->disconnect();
        process->deleteLater();
        // process = nullptr;
        emit finished(this);
        return;
    }
    process->close();
    process->disconnect();
    process->deleteLater();
    process = nullptr;

    QByteArray result = process->readAllStandardOutput();

    process = new QProcess();
    plog->write("[CHECKER] Set Wifi "+ssid+" : Success -> Connection Update");
    process->start("nmcli",QStringList()  << "con" << "up" << ssid);

    if(!process->waitForFinished()){
        emit set_wifi_fail(0, argument[0]);
        process->close();
        process->disconnect();
        process->deleteLater();
        // process = nullptr;
        emit finished(this);
    }else{
        argument.clear();
        argument << ssid << "pass_finish";

        process->close();
        process->disconnect();
        process->deleteLater();
        process = nullptr;
        getNetworkState();
        emit set_wifi_success(argument[0]);
        emit finished(this);
    }
}

void Worker::setEthernet(){
    QString ip = "";
    QString subnet = "";
    QString gateway = "";
    QString dns1 = "";
    QString dns2 = "";
    if(argument.size() > 4){
        ip = argument[0];
        subnet = netmaskToSubnet(QString(argument[1]));
        gateway = argument[2];
        dns1 = argument[3];
        dns2 = argument[4];
    }

    process = new QProcess();
    plog->write("[CHECKER] Set Ethernet "+probot->ethernet_interface.ssid+" : "+ip+"/"+subnet+" , "+gateway+" , "+dns1+" , "+dns2);
    process->start("nmcli",QStringList()  << "con" << "mod" << probot->ethernet_interface.ssid << "ipv4.method" << "manual" << "ipv4.address" << ip+"/"+subnet << "ipv4.gateway" << gateway << "ipv4.dns" << dns1+" "+dns2);

    connect(process,SIGNAL(readyReadStandardError()),this,SLOT(error_set_wifi()));

    if(!process->waitForFinished()){
        emit set_wifi_fail(0, argument[0]);
        emit finished(this);
        return;
    }

    process->close();
    process->disconnect();
    process->deleteLater();
    process = nullptr;


    process = new QProcess();
    plog->write("[CHECKER] Set Ethernet "+probot->ethernet_interface.ssid+" : Success -> Connection Update");
    process->start("nmcli",QStringList()  << "con" << "up" << probot->ethernet_interface.ssid);

    if(!process->waitForFinished()){
        emit set_wifi_fail(0, argument[0]);
    }else{
        emit set_wifi_success(argument[0]);
    }

    process->close();
    process->disconnect();
    process->deleteLater();
    process = nullptr;

    emit finished(this);
}
void Worker::gitReset(){
    process = new QProcess();
    process->setWorkingDirectory(QDir::homePath()+"/RB_MOBILE/release");
    process->start("git",QStringList() << "reset" << "--hard" << "origin/"+probot->program_branch);

    connect(process,SIGNAL(readyReadStandardError()),this,SLOT(error_git_reset()));

    if(!process->waitForFinished()){
        process->close();
        process->disconnect();
        process->deleteLater();
        process = nullptr;
        emit finished(this);
        return;
    }
    QByteArray result = process->readAllStandardOutput();
    process->close();
    process->disconnect();
    process->deleteLater();
    process = nullptr;
    gitPull();
}

void Worker::getNetworkState() {

    //QMutexLocker locker(&mutex);  // 공유 자원 접근 시 동기화
    QScopedPointer<QProcess> process(new QProcess());  // QScopedPointer로 메모리 자동 관리
    QString ssid = "";
    QString name = "";
    bool all_search = false;

    if (argument.size() > 0) {
        ssid = argument[0];
        if (ssid.isEmpty()) {
            all_search = true;
        }
    } else {
        all_search = true;
        ssid = "";
    }

    if (all_search) {
        process->start("nmcli", QStringList() << "device" << "show");
    } else {
        process->start("nmcli", QStringList() << "con" << "show" << ssid);
    }

    if (!process->waitForFinished()) {
        qWarning() << "Process did not finish correctly";
        emit finished(this);
        return;
    }

    QByteArray result = process->readAllStandardOutput();
    QList<QByteArray> lines = result.split('\n');

    QString type;
    for (QByteArray line : lines) {
        if (all_search) {
            if (line.contains("GENERAL.DEVICE")) {
                name = line.split(':')[1].trimmed();
            } else if (line.contains("GENERAL.TYPE")) {
                type = line.split(':')[1].trimmed();
            } else if (line.contains("GENERAL.STATE")) {
                if (line.contains("disconnected")) {
                    continue;
                } else if (line.contains("connected")) {
                    // 연결된 상태일 때 필요한 추가 작업이 있다면 여기에 추가
                } else {
                    continue;
                }
            } else if (line.contains("GENERAL.CONNECTION")) {
                if (type == "wifi") {
                    probot->wifi_interface.name = name;
                    probot->wifi_interface.ssid = line.split(':')[1].trimmed();
                } else if (type == "ethernet") {
                    probot->ethernet_interface.name = name;
                    probot->ethernet_interface.ssid = line.split(':')[1].trimmed();
                }
            } else if (line.contains("IP4.ADDRESS")) {
                if (name == probot->ethernet_interface.name) {
                    probot->ethernet_interface.ipv4 = line.split(':')[1].trimmed().split('/')[0];
                    probot->ethernet_interface.subnet = line.split(':')[1].trimmed().split('/')[1];
                    probot->ethernet_interface.netmask = subnetToNetmask(probot->ethernet_interface.subnet);
                } else if (name == probot->wifi_interface.name) {
                    probot->wifi_interface.ipv4 = line.split(':')[1].trimmed().split('/')[0];
                    probot->wifi_interface.subnet = line.split(':')[1].trimmed().split('/')[1];
                    probot->wifi_interface.netmask = subnetToNetmask(probot->wifi_interface.subnet);
                }
            } else if (line.contains("IP4.GATEWAY")) {
                if (name == probot->ethernet_interface.name) {
                    probot->ethernet_interface.gateway = line.split(':')[1].trimmed();
                } else if (name == probot->wifi_interface.name) {
                    probot->wifi_interface.gateway = line.split(':')[1].trimmed();
                }
            } else if (line.contains("IP4.DNS[1]")) {
                if (name == probot->ethernet_interface.name) {
                    probot->ethernet_interface.dns1 = line.split(':')[1].trimmed();
                    probot->ethernet_interface.dns2 = "";
                } else if (name == probot->wifi_interface.name) {
                    probot->wifi_interface.dns1 = line.split(':')[1].trimmed();
                    probot->wifi_interface.dns2 = "";
                }
            } else if (line.contains("IP4.DNS[2]")) {
                if (name == probot->ethernet_interface.name) {
                    probot->ethernet_interface.dns2 = line.split(':')[1].trimmed();
                } else if (name == probot->wifi_interface.name) {
                    probot->wifi_interface.dns2 = line.split(':')[1].trimmed();
                }
            }
        } else {
            if (line.contains("IP4.ADDRESS[1]")) {
                if (ssid == probot->ethernet_interface.ssid) {
                    probot->ethernet_interface.ipv4 = line.split(':')[1].trimmed().split('/')[0];
                    probot->ethernet_interface.subnet = line.split(':')[1].trimmed().split('/')[1];
                    probot->ethernet_interface.netmask = subnetToNetmask(probot->ethernet_interface.subnet);
                } else if (ssid == probot->wifi_interface.ssid) {
                    probot->wifi_interface.ipv4 = line.split(':')[1].trimmed().split('/')[0];
                    probot->wifi_interface.subnet = line.split(':')[1].trimmed().split('/')[1];
                    probot->wifi_interface.netmask = subnetToNetmask(probot->wifi_interface.subnet);
                }
            } else if (line.contains("ipv4.method")) {
                probot->wifi_interface.method = line.split(':')[1].trimmed();
            } else if (line.contains("IP4.GATEWAY")) {
                if (ssid == probot->ethernet_interface.ssid) {
                    probot->ethernet_interface.gateway = line.split(':')[1].trimmed();
                } else if (ssid == probot->wifi_interface.ssid) {
                    probot->wifi_interface.gateway = line.split(':')[1].trimmed();
                }
            } else if (line.contains("IP4.DNS[1]")) {
                if (ssid == probot->ethernet_interface.ssid) {
                    probot->ethernet_interface.dns1 = line.split(':')[1].trimmed();
                    probot->ethernet_interface.dns2 = "";
                } else if (ssid == probot->wifi_interface.ssid) {
                    probot->wifi_interface.dns1 = line.split(':')[1].trimmed();
                    probot->wifi_interface.dns2 = "";
                }
            } else if (line.contains("IP4.DNS[2]")) {
                if (ssid == probot->ethernet_interface.ssid) {
                    probot->ethernet_interface.dns2 = line.split(':')[1].trimmed();
                } else if (ssid == probot->wifi_interface.ssid) {
                    probot->wifi_interface.dns2 = line.split(':')[1].trimmed();
                }
            }
        }
    }

    // QScopedPointer가 자동으로 process를 삭제하므로 명시적인 삭제는 필요 없음
    emit finished(this);
}


/*
void Worker::getNetworkState(){
    process = new QProcess();
    QString ssid = "";
    QString name = "";
    bool all_search = false;
    if(argument.size()>0){
        ssid = argument[0];
        if(ssid == ""){
            all_search = true;
        }
    }else{
        all_search = true;
        ssid = "";
    }

    if(all_search){
        process->start("nmcli",QStringList()<< "device" << "show");
    }else{
        process->start("nmcli",QStringList()<< "con" << "show" << ssid);
    }

    if(!process->waitForFinished()){
    }else{
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
                        int num = 0;
                        QByteArray temp_line = line.split(':')[1];
                        for(uchar c: temp_line){
                            if(c == ' '){
                                num++;
                            }else{
                                temp_line.remove(0,num);
                                break;
                            }
                        }
                        ssid = temp_line;
                        probot->wifi_interface.ssid = ssid;
                    }else if(type == "ethernet"){
                        probot->ethernet_interface.name = name;
                        int num = 0;
                        QByteArray temp_line = line.split(':')[1];
                        for(uchar c: temp_line){
                            if(c == ' '){
                                num++;
                            }else{
                                temp_line.remove(0,num);
                                break;
                            }
                        }
                        ssid = temp_line;
                        probot->ethernet_interface.ssid = temp_line;
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
                if(line.contains("IP4.ADDRESS[1]")){
                    if(ssid == probot->ethernet_interface.ssid){
                        probot->ethernet_interface.ipv4 = line.split(':')[1].replace(' ',"").split('/')[0];
                        probot->ethernet_interface.subnet = line.split(':')[1].replace(' ',"").split('/')[1];
                        probot->ethernet_interface.netmask = subnetToNetmask(probot->ethernet_interface.subnet);
                    }else if(ssid == probot->wifi_interface.ssid){
                        probot->wifi_interface.ipv4 = line.split(':')[1].replace(' ',"").split('/')[0];
                        probot->wifi_interface.subnet = line.split(':')[1].replace(' ',"").split('/')[1];
                        probot->wifi_interface.netmask = subnetToNetmask(probot->wifi_interface.subnet);
                    }
                    //                qDebug() << "IP4.ADDRESS[1]" << ssid << line;
                }else if(line.contains("ipv4.method")){
                    //                qDebug() << "ipv4.method" << ssid << line;
                    probot->wifi_interface.method = line.split(':')[1].replace(' ',"");
                }else if(line.contains("IP4.GATEWAY")){
                    if(ssid == probot->ethernet_interface.ssid){
                        probot->ethernet_interface.gateway = line.split(':')[1].replace(' ',"").split('/')[0];
                    }else if(ssid == probot->wifi_interface.ssid){
                        probot->wifi_interface.gateway = line.split(':')[1].replace(' ',"").split('/')[0];
                    }
                }else if(line.contains("IP4.DNS[1]")){
                    if(ssid == probot->ethernet_interface.ssid){
                        probot->ethernet_interface.dns1 = line.split(':')[1].replace(' ',"").split('/')[0];
                        probot->ethernet_interface.dns2 = "";
                    }else if(ssid == probot->wifi_interface.ssid){
                        probot->wifi_interface.dns1 = line.split(':')[1].replace(' ',"").split('/')[0];
                        probot->wifi_interface.dns2 = "";
                    }
                }else if(line.contains("IP4.DNS[2]")){
                    if(ssid == probot->ethernet_interface.ssid){
                        probot->ethernet_interface.dns2 = line.split(':')[1].replace(' ',"").split('/')[0];
                    }else if(ssid == probot->wifi_interface.ssid){
                        probot->wifi_interface.dns2 = line.split(':')[1].replace(' ',"").split('/')[0];
                    }
                }
            }
        }

    }


    process->close();
    process->disconnect();
    process->deleteLater();
    // process = nullptr;

    if(argument.size()>1){

    }else{
        emit finished(this);
    }
}
*/

//void Worker::gitPull(){
//    process = new QProcess(this);
//
//    process->setWorkingDirectory(QDir::homePath()+"/RB_MOBILE");
//    plog->write("[UPDATE] Git Pull : Start");
//    process->start("git",QStringList()<<"submodule" << "update" <<"--remote");
//
//    connect(process,SIGNAL(readyReadStandardError()),this,SLOT(error_git_pull()));
//
//    if(!process->waitForFinished()){
//    }else{
//        QByteArray result = process->readAllStandardOutput();
//
//        if(result == "" && !is_error){
//            plog->write("[UPDATE] Git Pull : Already");
//            emit git_pull_nothing();
//        }else if(result.contains("error:") || is_error){
//            plog->write("[UPDATE] Git Pull : Failed");
//            emit git_pull_failed();
//        }else{
//            plog->write("[UPDATE] Git Pull : Success");
//            emit git_pull_success();
//        }
//    }
//
//    process->close();
//    process->disconnect();
//    process->deleteLater();
//    process = nullptr;
//
//    emit finished(this);
//}

//0725-BJ
void Worker::gitPull() {
    process = new QProcess(this);
    process->setWorkingDirectory(QDir::homePath() + "/RB_MOBILE");
    plog->write("[UPDATE] Git Pull : Start");

    connect(process, &QProcess::readyReadStandardError, this, &Worker::error_git_pull);

    process->start("git", QStringList() << "submodule" << "update" << "--remote");

    if (!process->waitForFinished()) {
        plog->write("[UPDATE] Git Pull : Timeout or Error");
    } else {
        QByteArray result = process->readAllStandardOutput();
        if (result.isEmpty() && !is_error) {
            plog->write("[UPDATE] Git Pull : Already up-to-date");
            emit git_pull_nothing();
        } else if (result.contains("error:") || is_error) {
            plog->write("[UPDATE] Git Pull : Failed");
            emit git_pull_failed();
        } else {
            plog->write("[UPDATE] Git Pull : Success");
            emit git_pull_success();
        }
    }

    process->close();
    process->deleteLater();
    process = nullptr;

    emit finished(this);
}

/*
void Worker::checkPing(){
    QString hostname = "www.google.com";
    if(argument.size() > 0){
        hostname = argument[0];
    }

    process = new QProcess(this);
    process->start("ping",QStringList()<< "-c" << "1" << hostname);

    if(!process->waitForFinished(1000)){
        probot->con_internet = false;
    }else{
        QByteArray result = process->readAllStandardOutput();
        //    qDebug() << "PING : " << result;
        if (result.contains("1 received")) {
            probot->con_internet = true;
        } else {
            probot->con_internet = false;
        }
    }
    process->close();
    process->deleteLater();
    // process = nullptr;
    emit finished(this);
}
*/

void Worker::checkPing() {
    QString hostname = "www.google.com";
    plog ->write("[CHECKER]checkping");
    if (argument.size() > 0) {
        hostname = argument[0];
    }

    // QScopedPointer를 사용하여 QProcess 객체를 관리
    QScopedPointer<QProcess> process(new QProcess(this));
    process->start("ping", QStringList() << "-c" << "1" << hostname);

    try {
        if (!process->waitForFinished(1000)) {
            probot->con_internet = false;
            plog->write("[CHECKER]checkping : con_internet-wait false");
        } else {
            QByteArray result = process->readAllStandardOutput();
            // qDebug() << "PING : " << result;
            if (result.contains("1 received")) {
                probot->con_internet = true;
                plog->write("[CHECKER]checkping : con_internet-true");
            } else {
                probot->con_internet = false;
                plog->write("[CHECKER]checkping : con_internet-false");
            }
        }
    } catch (const std::exception &e) {
        qWarning() << "An error occurred during checkPing: " << e.what();
        probot->con_internet = false;  // 에러 발생 시 인터넷 연결을 false로 설정
    } catch (...) {
        qWarning() << "An unexpected error occurred during checkPing";
        probot->con_internet = false;  // 에러 발생 시 인터넷 연결을 false로 설정
    }

    // QScopedPointer가 자동으로 process를 삭제하므로 명시적인 삭제는 필요 없음
    emit finished(this);
}

//0725-BJ
void Worker::outputAvailable() {
    QByteArray result = process->readAllStandardOutput();
    QString output(result);
    // 네트워크 상태를 처리하는 로직 추가
    plog->write("[CHECKER] Network Output: " + output);
    // 필요한 추가 작업 수행
}
//0725-BJ
void Worker::processFinished(int exitCode, QProcess::ExitStatus exitStatus) {
    if (exitCode == 0) {
        plog->write("[CHECKER] Network Monitor Finished Successfully");
    } else {
        plog->write("[CHECKER] Network Monitor Finished with Errors");
    }
    process->deleteLater();
    emit finished(this);
}

//void Worker::startMonitorNetwork(){
//    process = new QProcess();
//    plog->write("[CHECKER] Start Monitor Network");
//    process->start("nmcli",QStringList()<<"m");
//    connect(process,SIGNAL(readyReadStandardOutput()),this,SLOT(network_output()));
//}

//0725-BJ
void Worker::startMonitorNetwork() {
    process = new QProcess(this);
    plog->write("[CHECKER] Start Monitor Network");

    connect(process, &QProcess::readyReadStandardOutput, this, &Worker::outputAvailable);
    connect(process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this, &Worker::processFinished);

    process->start("nmcli", QStringList() << "m");
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
                probot->con_internet = false;
            }else if(state == "connecting"){
                plog->write("[NETWORK] Networkmanager : Connecting");
                probot->con_internet2 = NET_CONNECTING;
                probot->con_internet = false;
            }
        }
    }
}

Checker::Checker(QObject *parent)
{
    thread_1 = new QThread(this);
    thread_2 = new QThread(this);
    thread_3 = new QThread(this);

    worker_3 = new Worker("PROCESS_3",thread_3);
    worker_3->moveToThread(thread_3);
    QObject::connect(thread_3, &QThread::started, worker_3, &Worker::startMonitorNetwork);
    thread_3->start();
    QObject::connect(worker_3, &Worker::change_network, this, &Checker::change_network);

    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &Checker::onTimer);
    timer->start(100);

    getPing("www.goog3le.com");
}

void Checker::change_network(QString line){

}

Checker::~Checker(){
    timer->deleteLater();
    thread_1->quit();
    thread_1->wait();
    delete thread_1;

    thread_2->quit();
    thread_2->wait();
    delete thread_2;

    thread_3->quit();
    thread_3->wait();
    delete thread_3;

    delete worker_1;
    delete worker_2;
    delete worker_3;
}

/*
void Checker::onTimer(){
    if(cmd_list.size() > 0){
        if(thread_1->isRunning()){
            if(thread_2->isRunning()){
            }else{
                worker_2 = new Worker("PROCESS_2",thread_2);
                worker_2->moveToThread(thread_2);
                QObject::connect(worker_2, &Worker::finished, thread_2, &QThread::quit);
                QObject::connect(worker_2, &Worker::finished, this, &Checker::disWork);
                //qDebug() << "setWork 2" << cmd_list[0].cmd << cmd_list[0].arg;
                worker_2->setWork( cmd_list[0].cmd, cmd_list[0].arg);
                worker_2->setProperties(cmd_list[0].print);

                setWork(cmd_list[0], thread_2, worker_2);
                // cmd_list.pop_front();
                thread_2->start();
            }
        }else{
            worker_1 = new Worker("PROCESS_1",thread_1);
            worker_1->moveToThread(thread_1);
            QObject::connect(worker_1, &Worker::finished, thread_1, &QThread::quit);
            QObject::connect(worker_1, &Worker::finished, this, &Checker::disWork);
            //qDebug() << "setWork 1" << cmd_list[0].cmd << cmd_list[0].arg;
            worker_1->setWork(cmd_list[0].cmd,cmd_list[0].arg);
            worker_1->setProperties(cmd_list[0].print);
            setWork(cmd_list[0], thread_1, worker_1);

            // cmd_list.pop_front();
            thread_1->start();
        }
    }
}
*/

void Checker::onTimer() {
    // 스레드가 실행 중인지 확인하는 부분에 동기화 적용
    QMutexLocker locker(&mutex); // 스레드 간 동기화를 위한 뮤텍스 사용

    if (cmd_list.isEmpty()) {
        return; // cmd_list가 비어 있으면 작업을 수행하지 않고 종료
    }

    // QScopedPointer를 사용하여 Worker 객체를 안전하게 관리
    QScopedPointer<Worker> worker_1;
    QScopedPointer<Worker> worker_2;

    // 스레드 1이 실행 중인지 확인
    if (thread_1->isRunning()) {
        // 스레드 2가 실행 중이지 않은 경우
        if (!thread_2->isRunning()) {
            try {
                worker_2.reset(new Worker("PROCESS_2", thread_2));
                worker_2->moveToThread(thread_2);

                QObject::connect(worker_2.data(), &Worker::finished, thread_2, &QThread::quit);
                QObject::connect(worker_2.data(), &Worker::finished, this, &Checker::disWork);

                worker_2->setWork(cmd_list[0].cmd, cmd_list[0].arg);
                worker_2->setProperties(cmd_list[0].print);
                setWork(cmd_list[0], thread_2, worker_2.data());

                thread_2->start();
                //QObject::connect(thread_2, &QThread::started, worker_2.data(), &Worker::checkPing);  // 스레드 시작 후 checkPing 호출



                cmd_list.pop_front();
            } catch (std::bad_alloc& e) {
                qWarning() << "Memory allocation failed for worker_2: " << e.what();
                return; // 메모리 할당 실패 시 안전하게 종료
            } catch (...) {
                qWarning() << "An unexpected error occurred while creating worker_2";
                return; // 다른 예외 발생 시도 안전하게 종료
            }
        }
    } else { // 스레드 1이 실행 중이지 않은 경우
        try {
            worker_1.reset(new Worker("PROCESS_1", thread_1));
            worker_1->moveToThread(thread_1);
            QObject::connect(worker_1.data(), &Worker::finished, thread_1, &QThread::quit);
            QObject::connect(worker_1.data(), &Worker::finished, this, &Checker::disWork);

            worker_1->setWork(cmd_list[0].cmd, cmd_list[0].arg);
            worker_1->setProperties(cmd_list[0].print);
            setWork(cmd_list[0], thread_1, worker_1.data());

            thread_1->start();
            //QObject::connect(thread_1, &QThread::started, worker_1.data(), &Worker::checkPing);  // 스레드 시작 후 checkPing 호출



            cmd_list.pop_front();
        } catch (std::bad_alloc& e) {
            qWarning() << "Memory allocation failed for worker_1: " << e.what();
            return; // 메모리 할당 실패 시 안전하게 종료
        } catch (...) {
            qWarning() << "An unexpected error occurred while creating worker_1";
            return; // 다른 예외 발생 시도 안전하게 종료
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
    //qDebug() << "diswork";
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
    }else if(worker->program == "setEthernet"){
        QObject::disconnect(worker->parent_thread, &QThread::started, worker, &Worker::setEthernet);
        QObject::disconnect(worker, &Worker::set_wifi_success, this, &Checker::set_wifi_success);
        QObject::disconnect(worker, &Worker::set_wifi_fail, this, &Checker::set_wifi_fail);
    }else if(worker->program == "getNetworkState"){
        QObject::disconnect(worker->parent_thread, &QThread::started, worker, &Worker::getNetworkState);
    }else if(worker->program == "checkPing"){
        QObject::disconnect(worker->parent_thread, &QThread::started, worker, &Worker::checkPing);
    }else if(worker->program == "gitReset"){
        QObject::disconnect(worker->parent_thread, &QThread::started, worker, &Worker::gitReset);
        QObject::disconnect(worker, &Worker::git_pull_success, this, &Checker::gitpull_success);
        QObject::disconnect(worker, &Worker::git_pull_failed, this, &Checker::gitpull_fail);
        QObject::disconnect(worker, &Worker::git_pull_nothing, this, &Checker::gitpull_nothing);
    }else if(worker->program == "gitPull"){
        QObject::disconnect(worker->parent_thread, &QThread::started, worker, &Worker::gitPull);
        QObject::disconnect(worker, &Worker::git_pull_success, this, &Checker::gitpull_success);
        QObject::disconnect(worker, &Worker::git_pull_failed, this, &Checker::gitpull_fail);
        QObject::disconnect(worker, &Worker::git_pull_nothing, this, &Checker::gitpull_nothing);
    }else{

    }

    //cmd_list pop
    for(int i=0; i<cmd_list.size(); i++){
        if(cmd_list[i].cmd == worker->program){
            cmd_list.removeAt(i);
            break;
        }
    }

    if(worker == worker_1){
        //qDebug() << "disWork 1";
        worker_1->disconnect();
        worker_1->deleteLater();
        worker_1 = nullptr;
    }else if(worker == worker_2){
        //qDebug() << "disWork 2";
        worker_2->disconnect();
        worker_2->deleteLater();
        worker_2 = nullptr;
    }
    //qDebug() << "disWork done";
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

    }else if(cmd.cmd == "setEthernet"){
        QObject::connect(thread, &QThread::started, worker, &Worker::setEthernet);
        QObject::connect(worker, &Worker::set_wifi_success, this, &Checker::set_wifi_success);
        QObject::connect(worker, &Worker::set_wifi_fail, this, &Checker::set_wifi_fail);

    }else if(cmd.cmd == "checkPing"){
        QObject::connect(thread, &QThread::started, worker, &Worker::checkPing);

    }else if(cmd.cmd == "getNetworkState"){
        QObject::connect(thread, &QThread::started, worker, &Worker::getNetworkState);

    }else if(cmd.cmd == "gitReset"){
        QObject::connect(thread, &QThread::started, worker, &Worker::gitReset);
        QObject::connect(worker, &Worker::git_pull_success, this, &Checker::gitpull_success);
        QObject::connect(worker, &Worker::git_pull_failed, this, &Checker::gitpull_fail);
        QObject::connect(worker, &Worker::git_pull_nothing, this, &Checker::gitpull_nothing);
    }else if(cmd.cmd == "gitPull"){
        QObject::connect(thread, &QThread::started, worker, &Worker::gitPull);
        QObject::connect(worker, &Worker::git_pull_success, this, &Checker::gitpull_success);
        QObject::connect(worker, &Worker::git_pull_failed, this, &Checker::gitpull_fail);
        QObject::connect(worker, &Worker::git_pull_nothing, this, &Checker::gitpull_nothing);
    }else{
    }
}

void Checker::gitpull_success(){
    emit sig_gitpull_success();
}
void Checker::gitpull_fail(){
    emit sig_gitpull_fail(0);
}
void Checker::gitpull_nothing(){
    emit sig_gitpull_fail(1);
}
void Checker::connect_wifi_success(QString ssid){
    plog->write("[CHECKER] Connect Wifi Success : "+ssid);
    emit sig_con_wifi_success(ssid);
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
    emit sig_con_wifi_fail(reason, ssid);
}

void Checker::set_wifi_success(QString ssid){
    plog->write("[CHECKER] Set Wifi Success : "+ssid);
    emit sig_set_wifi_success(ssid);
}

void Checker::set_wifi_fail(int reason,QString ssid){
    if(reason == 1){
        plog->write("[CHECKER] Set Wifi Failed : Error "+ssid);
    }else{
        plog->write("[CHECKER] Set Wifi Failed : Unknown "+ssid);
    }

    emit sig_set_wifi_fail(reason, ssid);
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
            if(interface.name().left(1) == "e"){
                probot->ethernet_interface.name = interface.name();
                probot->ethernet_interface.type = interface.type();
                probot->ethernet_interface.mac = interface.hardwareAddress();

            // 이 인터페이스의 IP 주소 목록을 가져옴
            QList<QNetworkAddressEntry> addressEntries = interface.addressEntries();
                foreach (const QNetworkAddressEntry &entry, addressEntries) {
                if(entry.ip().protocol() == QAbstractSocket::IPv4Protocol){
                    probot->ethernet_interface.state = NET_CON;
                    }
                }
            }
        }else if(interface.type() == QNetworkInterface::Wifi){
            probot->wifi_interface.name = interface.name();
            probot->wifi_interface.type = interface.type();

            // 이 인터페이스의 IP 주소 목록을 가져옴
            QList<QNetworkAddressEntry> addressEntries = interface.addressEntries();

            foreach (const QNetworkAddressEntry &entry, addressEntries) {
                if(entry.ip().protocol() == QAbstractSocket::IPv4Protocol){
                    probot->wifi_interface.state = NET_CON;
                }
            }
        }
    }

    getNetworkState(probot->wifi_interface.ssid);
//    qDebug() << "getNetworkState " << probot->wifi_interface.ipv4 << probot->wifi_interface.name;
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

void Checker::getWifiList(bool readall){
    for(ST_PROC p : cmd_list){
        if(p.name == "getWifiList"){
            return;
        }
    }

    ST_PROC proc;
    proc.name = "getWifiList";
    proc.cmd = "getWifiList";
    if(readall){
        proc.arg = QStringList() << "readall";//"grep" << "-o" << "'^[z-zA-Z0-9]*'";
    }else{
        proc.arg = QStringList() << "no";//"grep" << "-o" << "'^[z-zA-Z0-9]*'";
    }
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

    //0725-BJ
    process = new QProcess(this);
    QStringList arguments;
    arguments << "dev" << "wifi" << "connect" << ssid << "password" << passwd;

    connect(process, &QProcess::readyReadStandardOutput, this, [this, ssid]() {
        QByteArray result = process->readAllStandardOutput();
        if (result.contains("successfully activated")) {
            plog->write("[WiFi] Connection successful to " + ssid);
            emit wifi_connect_success();
        } else {
            plog->write("[WiFi] Connection failed to " + ssid);
            emit wifi_connect_failed();
        }
    });

    connect(process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this, [this]() {
        process->deleteLater();
    });

    process->start("nmcli", arguments);
}

void Checker::setEthernet(QString ip, QString subnet, QString gateway, QString dns1, QString dns2){
    for(ST_PROC p : cmd_list){
        if(p.name == "setEthernet"){
            return;
        }
    }

    ST_PROC proc;
    proc.cmd = "setEthernet";
    proc.arg = QStringList() << ip << subnet << gateway << dns1 << dns2;
    proc.print = false;
    cmd_list.append(proc);

    // 0725-BJ
    process = new QProcess(this);
    QStringList arguments;
    arguments << "connection" << "modify" << "ethernet"
              << "ipv4.addresses" << ip + "/" + subnet
              << "ipv4.gateway" << gateway
              << "ipv4.dns" << dns1
              << "ipv4.dns" << dns2
              << "ipv4.method" << "manual";

    connect(process, &QProcess::readyReadStandardOutput, this, [this]() {
        QByteArray result = process->readAllStandardOutput();
        if (result.contains("successfully")) {
            plog->write("[Ethernet] Configuration successful");
            emit ethernet_config_success();
        } else {
            plog->write("[Ethernet] Configuration failed");
            emit ethernet_config_failed();
        }
    });

    connect(process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this, [this]() {
        process->deleteLater();
    });

    process->start("nmcli", arguments);
}
void Checker::setIP(bool is_manual, QString ssid, QString ip, QString subnet, QString gateway, QString dns1, QString dns2){
    for(ST_PROC p : cmd_list){
        if(p.name == "setIP"){
            return;
        }
    }

    ST_PROC proc;
    proc.cmd = "setIP";
    if(is_manual){
        proc.arg = QStringList() << "manual" << ssid << ip << subnet << gateway << dns1 << dns2;
    }else{
        proc.arg = QStringList() << "dhcp" << ssid << ip << subnet << gateway << dns1 << dns2;
    }
    proc.print = false;
    cmd_list.append(proc);

    // 0725-BJ
    process = new QProcess(this);
    QStringList arguments;
    if (is_manual) {
        arguments << "connection" << "modify" << ssid
                  << "ipv4.addresses" << ip + "/" + subnet
                  << "ipv4.gateway" << gateway
                  << "ipv4.dns" << dns1
                  << "ipv4.dns" << dns2
                  << "ipv4.method" << "manual";
    } else {
        arguments << "connection" << "modify" << ssid << "ipv4.method" << "auto";
    }

    connect(process, &QProcess::readyReadStandardOutput, this, [this]() {
        QByteArray result = process->readAllStandardOutput();
        if (result.contains("successfully")) {
            plog->write("[IP] Configuration successful");
            emit ip_config_success();
        } else {
            plog->write("[IP] Configuration failed");
            emit ip_config_failed();
        }
    });

    connect(process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this, [this]() {
        process->deleteLater();
    });

    process->start("nmcli", arguments);
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
void Checker::gitReset(){
    for(ST_PROC p : cmd_list){
        if(p.name == "gitReset"){
            return;
        }
    }
    ST_PROC proc;
    proc.cmd = "gitReset";
    proc.arg = QStringList();
    proc.print = false;
    cmd_list.append(proc);
}
