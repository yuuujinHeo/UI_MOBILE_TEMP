#include "Cmd_checker.h"
#include <QTimer>
#include "QtDBus/QDBusInterface"
#include "QtDBus/QDBusConnection"
#include "QtDBus/QDBusReply"
#include "QtDBus/QDBusObjectPath"

CMD_CHECKER::CMD_CHECKER(QObject *parent)
    : QObject(parent)
{

    cmd_timer = new QTimer();
    connect(cmd_timer, &QTimer::timeout, this, &CMD_CHECKER::cmd_loop);
    cmd_timer->start(100);

    getPing("www.google.com");
}

CMD_CHECKER::~CMD_CHECKER()
{
    cmd_timer->deleteLater();
}

QString subnetToNetmask(QString subnetSize)
{
    // Calculate netmask from subnet size
    int netmaskInt = (0xFFFFFFFF << (32 - subnetSize.toInt())) & 0xFFFFFFFF;
    QString str = QString("%1.%2.%3.%4").arg((netmaskInt >> 24) & 0xFF)
                                        .arg((netmaskInt >> 16) & 0xFF)
                                        .arg(netmaskInt & 0xFF)
                                        .arg((netmaskInt >> 8) & 0xFF);
    return str;
}

QString netmaskToSubnet(const QString &netmask)
{
    // Convert netmask from string to integer
    QStringList parts = netmask.split('.');
    if (parts.size() != 4)
    {
        qWarning() << "Invalid netmask format";
        return "0";
    }

    uint netmaskInt = 0;
    for (int i = 0; i < 4; ++i)
    {
        int octet = parts[i].toInt();
        if (octet < 0 || octet > 255)
        {
            qWarning() << "Invalid octet in netmask";
            return "0";
        }
        netmaskInt = (netmaskInt << 8) | octet;
    }

    // Calculate subnet size from netmask
    int subnetSize = 0;
    while (netmaskInt & 0x80000000)
    {
        subnetSize++;
        netmaskInt <<= 1;
    }
    return QString::number(subnetSize);
}


bool sortWifi2(const ST_WIFI &w1, const ST_WIFI &w2)
{
    if(w1.ssid == probot->wifi_interface.ssid)
    {
        return true;
    }
    else if(w2.ssid == probot->wifi_interface.ssid)
    {
        return false;
    }
    else
    {
        return w2.level < w1.level;
    }
}

void CMD_CHECKER::start_get_wifi_interface(QString read_method)
{
    is_busy = true;
    std::unique_ptr<QProcess> get_wifi_interface_process = std::make_unique<QProcess>(this);
    if(read_method == "readall")
    {
        get_wifi_interface_process->start("nmcli", QStringList() << "dev" << "wifi");
        if(!get_wifi_interface_process->waitForFinished())
        {
            get_wifi_interface_process->deleteLater();
            get_wifi_interface_process.release();
            return;
        }
    }

    get_wifi_interface_process->start("iwlist", QStringList() << probot->wifi_interface.name << "scan");
    if(!get_wifi_interface_process->waitForFinished())
    {

        get_wifi_interface_process->deleteLater();
        get_wifi_interface_process.release();
        return;
    }

    QList<ST_WIFI> wifiList;
    QMap<QString, QString> wifiinfo;

    QByteArray result = get_wifi_interface_process->readAllStandardOutput();
    QList<QByteArray> lines = result.split('\n');
    for(QByteArray line : lines)
    {
        if(line.contains("Cell") && line.contains("Address"))
        {
            if(wifiinfo.size() > 0)
            {
                ST_WIFI temp_wifi;
                temp_wifi.ssid = wifiinfo["ESSID"];
                temp_wifi.level = wifiinfo["LEVEL"].split(" ")[0].toInt();
                if(wifiinfo["SECURITY"] == "on")
                {
                    temp_wifi.security = true;
                }
                else
                {
                    temp_wifi.security = false;
                }

                bool match = false;
                for(int i=0; i<wifiList.size(); i++)
                {
                    if(wifiList[i].ssid == temp_wifi.ssid)
                    {
                        if(temp_wifi.level > wifiList[i].level)
                        {
                            wifiList[i].level = temp_wifi.level;
                        }
                        match = true;
                    }
                }
                if(!match)
                {
                    wifiList.append(temp_wifi);
                }
            }
            wifiinfo.clear();
        }
        else if(line.contains("ESSID"))
        {
            QByteArray temp = line.split('"')[1];
            if(temp.contains('\\\\x')){
                QByteArray t;
                for (int i = 0; i < temp.size(); ++i)
                {
                    if (temp[i] == '\\' && temp[i + 1] == 'x')
                    {
                        bool ok;
                        char byte = temp.mid(i + 2, 2).toInt(&ok, 16);
                        if (ok)
                        {
                            t.append(byte);
                            i += 3; // '\xNN'을 건너뜀
                        }
                        else
                        {
                            t.append(temp[i]);
                        }
                    }
                    else
                    {
                        t.append(temp[i]);
                    }
                }
                wifiinfo["ESSID"] = QString::fromUtf8(t);
            }
            else
            {
                wifiinfo["ESSID"]=QString::fromUtf8(temp);
            }
        }
        else if(line.contains("Encryption key"))
        {
            QString temp = QString::fromUtf8(line.split(':')[1]);
            wifiinfo["SECURITY"]=temp;
        }
        else if(line.contains("Signal level"))
        {
            QString temp = QString::fromUtf8(line.split('-')[1].split(' ')[0]);
            int lv = temp.toInt();
            if(lv > 70)
            {
                lv = VERY_LOW;
            }
            else if(lv > 60)
            {
                lv = LOW;
            }
            else if(lv > 50)
            {
                lv = MIDDLE;
            }
            else if(lv > 40)
            {
                lv = HIGH;
            }
            else
            {
                lv = VERY_HIGH;
            }
            wifiinfo["LEVEL"]=QString::number(lv);
        }
    }

    if(wifiinfo.size() > 0)
    {
        ST_WIFI temp_wifi;
        temp_wifi.ssid = wifiinfo["ESSID"];
        temp_wifi.level = wifiinfo["LEVEL"].split(" ")[0].toInt();
        if(wifiinfo["SECURITY"] == "on")
        {
            temp_wifi.security = true;
        }
        else
        {
            temp_wifi.security = false;
        }

        bool match = false;
        for(int i=0; i<wifiList.size(); i++)
        {
            if(wifiList[i].ssid == temp_wifi.ssid)
            {
                if(temp_wifi.level > wifiList[i].level)
                {
                    wifiList[i].level = temp_wifi.level;
                }
                match = true;
            }
        }
        if(!match)
        {
            wifiList.append(temp_wifi);
        }
    }

    std::sort(wifiList.begin(), wifiList.end(), sortWifi2);

    probot->wifi_list.clear();
    probot->wifi_list = wifiList;


    get_wifi_interface_process->deleteLater();
    get_wifi_interface_process.release();
    is_busy = false;
}

void CMD_CHECKER::start_get_system_volume()
{
    is_busy = true;
    std::unique_ptr<QProcess> get_system_volume_process = std::make_unique<QProcess>(this);
    get_system_volume_process->start("pactl", QStringList() << "list" << "sinks");
    if(!get_system_volume_process->waitForFinished())
    {

        get_system_volume_process->deleteLater();
        get_system_volume_process.release();
        return;
    }

    QByteArray result = get_system_volume_process->readAllStandardOutput();
    QList<QByteArray> lines = result.split('\n');

    bool match = false;
    for(QByteArray line : lines)
    {
        if(line.contains(getSettings("static", "SOUND", "default_sink").toUtf8()))
        {
            match = true;
        }
        else if(match && line.contains("Volume: front-left"))
        {
            int num = line.split('/')[1].split('%')[0].toInt();
            if(isfinite(num) && isnan(num) && num > 0)
            {
                probot->volume_system = num;
                break;
            }
        }
    }


    get_system_volume_process->deleteLater();
    get_system_volume_process.release();
    is_busy = false;
}

void CMD_CHECKER::start_set_system_volume(int volume)
{
    is_busy = true;
    if(volume < 0 || !isfinite(volume) || isnan(volume))
    {
        return;
    }

    std::unique_ptr<QProcess> set_system_volume_process = std::make_unique<QProcess>(this);
    set_system_volume_process->start("pactl", QStringList() << "set-sink-volume" << getSettings("static","SOUND","default_sink") << volume + "%");
    if(set_system_volume_process->waitForFinished())
    {
        QByteArray result = set_system_volume_process->readAllStandardOutput();
        plog->write("[WORKER] Set System Volume : Done (" + QString::number(volume) + ")");
    }

    set_system_volume_process->deleteLater();
    set_system_volume_process.release();
    is_busy = false;

}
void CMD_CHECKER::start_connect_wifi(QString ssid, QString pw)
{
    is_busy = true;
    std::unique_ptr<QProcess> connect_wifi_process = std::make_unique<QProcess>(this);
    connect(connect_wifi_process.get(), &QProcess::readyReadStandardError, [this, _process = connect_wifi_process.get()](){error_connect_wifi(_process);});

    if(pw == "")
    {
        plog->write("[CHECKER] Connect Wifi : " + ssid + " passwd = none");
        connect_wifi_process->start("sudo", QStringList()  << "-S" << "nmcli"  << "device" << "wifi" << "connect" << ssid);
    }
    else
    {
        plog->write("[CHECKER] Connect Wifi : " + ssid + " passwd = "+ pw);
        connect_wifi_process->start("sudo", QStringList() << "-S" << "nmcli" << "device" << "wifi"<< "connect" << ssid << "password" << pw);
    }

    if(!connect_wifi_process->waitForFinished())
    {
        emit connect_wifi_fail(WIFI_CMD_IGNORED, ssid);

        connect_wifi_process->deleteLater();
        connect_wifi_process.release();
        return;
    }
\
    QByteArray result = connect_wifi_process->readAllStandardOutput();
    if(result.contains("successfully"))
    {
        emit connect_wifi_success(ssid);
    }
    else if(result.contains("Secrets were required"))
    {
        emit connect_wifi_fail(WIFI_PW_FAILED, ssid);
    }
    else if(result.contains("failed:"))
    {
        emit connect_wifi_fail(WIFI_CONNECTION_FAILED, ssid);
    }
    else
    {
        emit connect_wifi_fail(-1, ssid);
    }

    getNetworkState();

    connect_wifi_process->deleteLater();
    connect_wifi_process.release();
    is_busy = false;
}

void CMD_CHECKER::start_set_ip(QString method, QString ssid, QString ip, QString subnet, QString gateway, QString dns1, QString dns2)
{
    is_busy = true;
    subnet = netmaskToSubnet(subnet);
    plog->write("[CHECKER] Set Wifi " + ssid + " : (" + method + ") " + ip + "/" + subnet + " , " + gateway + " , " + dns1 + " , " + dns2);

    std::unique_ptr<QProcess> set_ip_process = std::make_unique<QProcess>(this);
    if(method == "dhcp")
    {
        set_ip_process->start("nmcli", QStringList() << "con" << "mod" << ssid << "ipv4.method" << "auto");
    }
    else
    {
        set_ip_process->start("nmcli", QStringList() << "con" << "mod" << ssid << "ipv4.method" << "manual" << "ipv4.address" << ip + "/" + subnet << "ipv4.gateway" << gateway << "ipv4.dns" << dns1 + " " + dns2);
    }

    connect(set_ip_process.get(), SIGNAL(readyReadStandardError()), this, SLOT(error_set_wifi()));
    if(!set_ip_process->waitForFinished())
    {
        emit set_wifi_fail(-1, ssid);

        set_ip_process->deleteLater();
        set_ip_process.release();
        return;
    }
    plog->write("[CHECKER] Set Wifi " + ssid + " : Success -> Connection Update");

    std::unique_ptr<QProcess> set_ip_process2 = std::make_unique<QProcess>(this);
    set_ip_process2->start("nmcli", QStringList()  << "con" << "up" << ssid);
    if(!set_ip_process2->waitForFinished())
    {
        emit set_wifi_fail(-1, ssid);

        set_ip_process2->deleteLater();
        set_ip_process2.release();
    }
    else
    {
        getNetworkState();
        emit set_wifi_success(ssid);

        set_ip_process2->deleteLater();
        set_ip_process2.release();
    }
    is_busy = false;
}

void CMD_CHECKER::start_set_ehternet(QString ip, QString subnet, QString gateway, QString dns1, QString dns2)
{
    is_busy = true;
    subnet = netmaskToSubnet(subnet);
    plog->write("[CHECKER] Set Ethernet " + probot->ethernet_interface.ssid + " : " + ip + "/" + subnet + " , " + gateway + " , " + dns1 + " , " + dns2);

    std::unique_ptr<QProcess> set_ethernet_process = std::make_unique<QProcess>(this);
    connect(set_ethernet_process.get(),SIGNAL(readyReadStandardError()),this,SLOT(error_set_wifi()));

    set_ethernet_process->start("nmcli", QStringList()  << "con" << "mod" << probot->ethernet_interface.ssid << "ipv4.method" << "manual" << "ipv4.address" << ip + "/" + subnet << "ipv4.gateway" << gateway << "ipv4.dns" << dns1 + " " + dns2);
    if(!set_ethernet_process->waitForFinished())
    {
        emit set_wifi_fail(-1, ip);

        set_ethernet_process->deleteLater();
        set_ethernet_process.release();
        return;
    }
    plog->write("[CHECKER] Set Ethernet " + probot->ethernet_interface.ssid + " : Success -> Connection Update");

    std::unique_ptr<QProcess> set_ethernet_process2 = std::make_unique<QProcess>(this);
    set_ethernet_process2->start("nmcli", QStringList() << "con" << "up" << probot->ethernet_interface.ssid);
    if(!set_ethernet_process2->waitForFinished())
    {
        emit set_wifi_fail(-1, ip);
    }
    else
    {
        emit set_wifi_success(ip);
    }

    set_ethernet_process2->deleteLater();
    set_ethernet_process2.release();
    is_busy = false;
}

void CMD_CHECKER::start_git_reset()
{
    is_busy = true;
    plog->write("[CHECKER] start git reset");
    std::unique_ptr<QProcess> set_git_reset_process = std::make_unique<QProcess>(this);
    connect(set_git_reset_process.get(), SIGNAL(readyReadStandardError()), this, SLOT(error_git_reset()));

    set_git_reset_process->setWorkingDirectory(QDir::homePath() + "/RB_MOBILE/release");
    set_git_reset_process->start("git", QStringList() << "reset" << "--hard" << "origin/" + probot->program_branch);
    if(set_git_reset_process->waitForFinished())
    {
        gitPull();
    }

    set_git_reset_process.release();
    set_git_reset_process->deleteLater();
    is_busy = false;
}

void CMD_CHECKER::start_get_network_state(QString ssid)
{
    is_busy = true;
    QString name = "";
    bool all_search = false;
    if(ssid == "")
    {
        all_search = true;
    }

    std::unique_ptr<QProcess> get_network_state_process = std::make_unique<QProcess>(this);
    if(all_search == true)
    {
        get_network_state_process->start("nmcli", QStringList() << "device" << "show");
    }
    else
    {
        get_network_state_process->start("nmcli",QStringList()<< "con" << "show" << ssid);
    }

    if(get_network_state_process->waitForFinished())
    {
        {
            QString type = "";
            QByteArray result = get_network_state_process->readAllStandardOutput();
            QList<QByteArray> lines = result.split('\n');
            for(QByteArray line : lines)
            {
                if(all_search == true)
                {
                    if(line.contains("GENERAL.DEVICE"))
                    {
                        QByteArrayList _line = line.split(':');
                        if(_line.size() < 2)
                        {
                            continue;
                        }
                        name = _line[1].replace(' ', "");
                    }
                    else if(line.contains("GENERAL.TYPE"))
                    {
                        QByteArrayList _line = line.split(':');
                        if(_line.size() < 2)
                        {
                            continue;
                        }
                        type = _line[1].replace(' ', "");
                    }
                    else if(line.contains("GENERAL.STATE"))
                    {
                        if(!line.contains("connected"))
                        {
                            continue;
                        }
                    }
                    else if(line.contains("GENERAL.CONNECTION"))
                    {
                        if(type == "wifi")
                        {
                            QByteArrayList _line = line.split(':');
                            if(_line.size() < 2)
                            {
                                continue;
                            }

                            int num = 0;
                            probot->wifi_interface.name = name;
                            QByteArray temp_line = _line[1];
                            for(uchar c: temp_line)
                            {
                                if(c == ' ')
                                {
                                    num++;
                                }
                                else
                                {
                                    temp_line.remove(0,num);
                                    break;
                                }
                            }
                            ssid = temp_line;
                            probot->wifi_interface.ssid = ssid;
                        }
                        else if(type == "ethernet")
                        {
                            QByteArrayList _line = line.split(':');
                            if(_line.size() < 2)
                            {
                                continue;
                            }

                            int num = 0;
                            probot->ethernet_interface.name = name;
                            QByteArray temp_line = _line[1];
                            for(uchar c: temp_line)
                            {
                                if(c == ' ')
                                {
                                    num++;
                                }
                                else
                                {
                                    temp_line.remove(0,num);
                                    break;
                                }
                            }
                            ssid = temp_line;
                            probot->ethernet_interface.ssid = temp_line;
                        }
                    }
                    else if(line.contains("IP4.ADDRESS"))
                    {
                        if(name == probot->ethernet_interface.name)
                        {
                            QByteArrayList _line = line.split(':');
                            if(_line.size() < 2)
                            {
                                continue;
                            }

                            QByteArrayList _line2 = _line[1].replace(' ',"").split('/');
                            if(_line2.size() < 2)
                            {
                                continue;
                            }

                            probot->ethernet_interface.ipv4 = _line2[0];
                            probot->ethernet_interface.subnet = _line2[1];
                            probot->ethernet_interface.netmask = subnetToNetmask(probot->ethernet_interface.subnet);
                        }
                        else if(name == probot->wifi_interface.name)
                        {
                            QByteArrayList _line = line.split(':');
                            if(_line.size() < 2)
                            {
                                continue;
                            }

                            QByteArrayList _line2 = _line[1].replace(' ',"").split('/');
                            if(_line2.size() < 2)
                            {
                                continue;
                            }

                            probot->wifi_interface.ipv4 = _line2[0];
                            probot->wifi_interface.subnet = _line2[1];
                            probot->wifi_interface.netmask = subnetToNetmask(probot->wifi_interface.subnet);
                        }
                    }
                    else if(line.contains("IP4.GATEWAY"))
                    {
                        QByteArrayList _line = line.split(':');
                        if(_line.size() < 2)
                        {
                            continue;
                        }

                        QByteArrayList _line2 = _line[1].replace(' ',"").split('/');
                        if(_line2.size() < 1)
                        {
                            continue;
                        }

                        if(name == probot->ethernet_interface.name)
                        {
                            probot->ethernet_interface.gateway = _line2[0];
                        }
                        else if(name == probot->wifi_interface.name)
                        {
                            probot->wifi_interface.gateway = _line2[0];
                        }
                    }
                    else if(line.contains("IP4.DNS[1]"))
                    {
                        QByteArrayList _line = line.split(':');
                        if(_line.size() < 2)
                        {
                            continue;
                        }

                        QByteArrayList _line2 = _line[1].replace(' ',"").split('/');
                        if(_line2.size() < 1)
                        {
                            continue;
                        }

                        if(name == probot->ethernet_interface.name)
                        {
                            probot->ethernet_interface.dns1 = _line2[0];
                            probot->ethernet_interface.dns2 = "";
                        }
                        else if(name == probot->wifi_interface.name)
                        {
                            probot->wifi_interface.dns1 = _line2[0];
                            probot->wifi_interface.dns2 = "";
                        }
                    }
                    else if(line.contains("IP4.DNS[2]"))
                    {
                        QByteArrayList _line = line.split(':');
                        if(_line.size() < 2)
                        {
                            continue;
                        }

                        QByteArrayList _line2 = _line[1].replace(' ',"").split('/');
                        if(_line2.size() < 1)
                        {
                            continue;
                        }

                        if(name == probot->ethernet_interface.name)
                        {
                            probot->ethernet_interface.dns2 = _line2[0];
                        }
                        else if(name == probot->wifi_interface.name)
                        {
                            probot->wifi_interface.dns2 = _line2[0];
                        }
                    }
                }
                else
                {
                    if(line.contains("IP4.ADDRESS[1]"))
                    {
                        QByteArrayList _line = line.split(':');
                        if(_line.size() < 2)
                        {
                            continue;
                        }

                        QByteArrayList _line2 = _line[1].replace(' ',"").split('/');
                        if(_line2.size() < 2)
                        {
                            continue;
                        }

                        if(ssid == probot->ethernet_interface.ssid)
                        {
                            probot->ethernet_interface.ipv4 = _line2[0];
                            probot->ethernet_interface.subnet = _line2[1];
                            probot->ethernet_interface.netmask = subnetToNetmask(probot->ethernet_interface.subnet);
                        }
                        else if(ssid == probot->wifi_interface.ssid)
                        {
                            probot->wifi_interface.ipv4 = _line2[0];
                            probot->wifi_interface.subnet = _line2[1];
                            probot->wifi_interface.netmask = subnetToNetmask(probot->wifi_interface.subnet);
                        }
                        //                qDebug() << "IP4.ADDRESS[1]" << ssid << line;
                    }
                    else if(line.contains("ipv4.method"))
                    {
                        QByteArrayList _line = line.split(':');
                        if(_line.size() < 2)
                        {
                            continue;
                        }

                        probot->wifi_interface.method = _line[1].replace(' ',"");
                    }
                    else if(line.contains("IP4.GATEWAY"))
                    {
                        QByteArrayList _line = line.split(':');
                        if(_line.size() < 2)
                        {
                            continue;
                        }

                        QByteArrayList _line2 = _line[1].replace(' ',"").split('/');
                        if(_line2.size() < 1)
                        {
                            continue;
                        }

                        if(ssid == probot->ethernet_interface.ssid)
                        {
                            probot->ethernet_interface.gateway = _line2[0];
                        }
                        else if(ssid == probot->wifi_interface.ssid)
                        {
                            probot->wifi_interface.gateway = _line2[0];
                        }
                    }
                    else if(line.contains("IP4.DNS[1]"))
                    {
                        QByteArrayList _line = line.split(':');
                        if(_line.size() < 2)
                        {
                            continue;
                        }

                        QByteArrayList _line2 = _line[1].replace(' ',"").split('/');
                        if(_line2.size() < 1)
                        {
                            continue;
                        }

                        if(ssid == probot->ethernet_interface.ssid)
                        {
                            probot->ethernet_interface.dns1 = _line2[0];
                            probot->ethernet_interface.dns2 = "";
                        }
                        else if(ssid == probot->wifi_interface.ssid)
                        {
                            probot->wifi_interface.dns1 = _line2[0];
                            probot->wifi_interface.dns2 = "";
                        }
                    }
                    else if(line.contains("IP4.DNS[2]"))
                    {
                        QByteArrayList _line = line.split(':');
                        if(_line.size() < 2)
                        {
                            continue;
                        }

                        QByteArrayList _line2 = _line[1].replace(' ',"").split('/');
                        if(_line2.size() < 1)
                        {
                            continue;
                        }

                        if(ssid == probot->ethernet_interface.ssid)
                        {
                            probot->ethernet_interface.dns2 = _line2[0];
                        }
                        else if(ssid == probot->wifi_interface.ssid)
                        {
                            probot->wifi_interface.dns2 = _line2[0];
                        }
                    }
                }
            }

        }
    }

    get_network_state_process->deleteLater();
    get_network_state_process.release();
    is_busy = false;
}

void CMD_CHECKER::start_git_pull()
{
    is_busy = true;
    plog->write("[UPDATE][git_pull] start git pull");

    std::unique_ptr<QProcess> git_pull_process = std::make_unique<QProcess>(this);\
    connect(git_pull_process.get(), &QProcess::readyReadStandardError, [this, _process = git_pull_process.get()](){error_git_pull(_process);});

    git_pull_process->setWorkingDirectory(QDir::homePath() + "/RB_MOBILE");
    git_pull_process->start("git", QStringList() << "submodule" << "update" << "--remote");
    if (!git_pull_process->waitForFinished())
    {
        plog->write("[UPDATE][git_pull] git pull error, Timeout or Error");
    }
    else
    {
        QByteArray result = git_pull_process->readAllStandardOutput();
        if (result.isEmpty() && !is_error)
        {
            plog->write("[UPDATE][git_pull] Error: already newest");
            emit sig_gitpull_fail(ALREADY_NEWEWST);
        }
        else if (result.contains("error:") || is_error)
        {
            plog->write("[UPDATE][git_pull] Error: need reset");
            emit sig_gitpull_fail(NEED_RESET);
        }
        else
        {
            plog->write("[UPDATE][git_pull] Success");
            emit sig_gitpull_success();
        }
    }

    git_pull_process->deleteLater();
    git_pull_process.release();
    is_busy = false;
}

void CMD_CHECKER::start_check_ping(QString host)
{
    is_busy = true;
    QString hostname = "www.google.com";
    if(!host.isEmpty() || host != "")
    {
        hostname = host;
    }

    plog->write("[CHECKER][start_check_ping] Start ping check");

    std::unique_ptr<QProcess> check_ping_process = std::make_unique<QProcess>(new QProcess);
    check_ping_process->start("ping", QStringList() << "-c" << "1" << hostname);
    if(!check_ping_process->waitForFinished(1000))
    {
        probot->con_internet = false;
    }
    else
    {
        QByteArray result = check_ping_process->readAllStandardOutput();
        if(result.contains("1 received"))
        {
            probot->con_internet = true;
            std::cout << "[CHECKER][start_check_ping] internet connected." << std::endl;
        }
        else
        {
            probot->con_internet = false;
            std::cout << "[CHECKER][start_check_ping] internet not connected." << std::endl;
        }
    }

    check_ping_process.release();
    is_busy = false;
}

void CMD_CHECKER::cmd_loop()
{
    try
    {
        if(is_busy == false && !cmd_list.isEmpty())
        {
            set_work(cmd_list.first());
            cmd_list.pop_front();
        }
    }
    catch(const std::exception &e)
    {
        QString err_str = "[CMD_CHECKER][cmd_loop] Exception occurred, err: "  + QString(e.what());
        std::cerr << err_str.toStdString() << std::endl;
        plog->write(err_str);
    }
    catch(...)
    {
        QString err_str = "[CMD_CHECKER][cmd_loop] Exception occurred, err: unknown.";
        std::cerr << err_str.toStdString() << std::endl;
        plog->write(err_str);
    }
}

void CMD_CHECKER::getPing(QString host)
{
    for(ST_PROC p : cmd_list)
    {
        if(p.name == "checkPing")
        {
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

void CMD_CHECKER::getCurrentInterface()
{
    getPing("www.google.com");
    getNetworkState();
}

void CMD_CHECKER::set_work(ST_PROC cmd)
{
    QString command = cmd.cmd;
    QStringList params = cmd.arg;

    if(command == "getWifiList")
    {
        if(params.size() != 1)
        {
            return;
        }

        QString method = params[0];
        start_get_wifi_interface(method);
    }
    else if(cmd.cmd == "getSystemVolume")
    {
        start_get_system_volume();
    }
    else if(command == "setSystemVolume")
    {
        if(params.size() != 1)
        {
            return;
        }

        int volume = params[0].toInt();
        start_set_system_volume(volume);
    }
    else if(cmd.cmd == "connectWifi")
    {
        if(params.size() != 2)
        {
            return;
        }

        QString ssid = params[0];
        QString pw = params[1];
        start_connect_wifi(ssid, pw);
    }
    else if(cmd.cmd == "setIP")
    {
        if(params.size() != 7)
        {
            return;
        }

        QString manual = params[0];
        QString ssid = params[1];
        QString ip = params[2];
        QString subnet = params[3];
        QString gateway = params[4];
        QString dns1 = params[5];
        QString dns2 = params[6];

        start_set_ip(manual, ssid, ip, subnet, gateway, dns1, dns2);
    }
    else if(cmd.cmd == "setEthernet")
    {
        if(params.size() != 5)
        {
            return;
        }

        QString ip = params[0];
        QString subnet = params[1];
        QString gateway = params[2];
        QString dns1 = params[3];
        QString dns2 = params[4];

        start_set_ehternet(ip, subnet, gateway, dns1, dns2);
    }
    else if(cmd.cmd == "checkPing")
    {
        if(params.size() != 1)
        {
            return;
        }

        QString host = params[0];

        start_check_ping(host);
    }
    else if(cmd.cmd == "getNetworkState")
    {
        if(params.size() != 1)
        {
            return;
        }

        QString host = params[0];
        start_get_network_state(host);
    }
    else if(cmd.cmd == "gitReset")
    {
        start_git_reset();
    }
    else if(cmd.cmd == "gitPull")
    {
        start_git_pull();
    }
    else
    {

    }
}

void CMD_CHECKER::connect_wifi_success(QString ssid)
{
    plog->write("[CHECKER] Connect Wifi Success : "+ssid);
    emit sig_con_wifi_success(ssid);
}

void CMD_CHECKER::connect_wifi_fail(int reason,QString ssid)
{
    if(reason == WIFI_PW_FAILED)
    {
        plog->write("[CHECKER] Connect Wifi Failed : Password Failed " + ssid);
    }
    else if(reason == WIFI_CONNECTION_FAILED)
    {
        plog->write("[CHECKER] Connect Wifi Failed : Connection Failed " + ssid);
    }
    else if(reason == WIFI_CMD_IGNORED)
    {
        plog->write("[CHECKER] Connect Wifi Failed : Command ignored " + ssid);
    }
    else if(reason == WIFI_NOT_FOUND_SSID)
    {
        plog->write("[CHECKER] Connect Wifi Failed : Can't found SSID " + ssid);
    }
    else
    {
        plog->write("[CHECKER] Connect Wifi Failed : Unknown " + QString::number(reason) + "  " + ssid);
    }
    emit sig_con_wifi_fail(reason, ssid);
}

void CMD_CHECKER::set_wifi_success(QString ssid)
{
    plog->write("[CHECKER] Set Wifi Success : "+ssid);
    emit sig_set_wifi_success(ssid);
}

void CMD_CHECKER::set_wifi_fail(int reason, QString ssid)
{
    if(reason == WIFI_SET_FAILED_ERROR)
    {
        plog->write("[CHECKER] Set Wifi Failed : Error "+ssid);
    }
    else
    {
        plog->write("[CHECKER] Set Wifi Failed : Unknown "+ssid);
    }

    emit sig_set_wifi_fail(reason, ssid);
}

void CMD_CHECKER::setSystemVolume(int volume)
{
    for(ST_PROC p : cmd_list)
    {
        if(p.name == "setSystemVolume")
        {
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

void CMD_CHECKER::getSystemVolume()
{
    for(ST_PROC p : cmd_list)
    {
        if(p.name == "getSystemVolume")
        {
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

void CMD_CHECKER::getNetworkState()
{
    QList<QNetworkInterface> interfaces = QNetworkInterface::allInterfaces();
    foreach (const QNetworkInterface &interface, interfaces)
    {
        if(interface.type() == QNetworkInterface::Ethernet)
        {
            if(interface.name().left(1) == "e")
            {
                probot->ethernet_interface.name = interface.name();
                probot->ethernet_interface.type = interface.type();
                probot->ethernet_interface.mac = interface.hardwareAddress();

                QList<QNetworkAddressEntry> addressEntries = interface.addressEntries();
                foreach (const QNetworkAddressEntry &entry, addressEntries)
                {
                   if(entry.ip().protocol() == QAbstractSocket::IPv4Protocol)
                   {
                       probot->ethernet_interface.state = NET_CON;
                   }
                }
            }
        }
        else if(interface.type() == QNetworkInterface::Wifi)
        {
            probot->wifi_interface.name = interface.name();
            probot->wifi_interface.type = interface.type();

            QList<QNetworkAddressEntry> addressEntries = interface.addressEntries();
            foreach (const QNetworkAddressEntry &entry, addressEntries)
            {
                if(entry.ip().protocol() == QAbstractSocket::IPv4Protocol)
                {
                    probot->wifi_interface.state = NET_CON;
                }
            }
        }
    }

    QString ssid = probot->wifi_interface.ssid;
    ST_PROC proc;
    proc.name = "getNetworkState";
    proc.cmd = "getNetworkState";
    proc.arg = QStringList() << ssid;
    cmd_list.append(proc);
}

void CMD_CHECKER::getWifiList(bool readall)
{
    for(ST_PROC p : cmd_list)
    {
        if(p.name == "getWifiList")
        {
            return;
        }
    }

    ST_PROC proc;
    proc.name = "getWifiList";
    proc.cmd = "getWifiList";
    if(readall == true)
    {
        proc.arg = QStringList() << "readall";//"grep" << "-o" << "'^[z-zA-Z0-9]*'";
    }
    else
    {
        proc.arg = QStringList() << "no";//"grep" << "-o" << "'^[z-zA-Z0-9]*'";
    }
    cmd_list.append(proc);
}

void CMD_CHECKER::connectWifi(QString ssid, QString passwd)
{
    for(ST_PROC p : cmd_list)
    {
        if(p.name == "connectWifi")
        {
            return;
        }
    }

    ST_PROC proc;
    proc.cmd = "connectWifi";
    proc.arg = QStringList() << ssid << passwd;
    proc.print = false;
    cmd_list.append(proc);
}

void CMD_CHECKER::setEthernet(QString ip, QString subnet, QString gateway, QString dns1, QString dns2)
{
    for(ST_PROC p : cmd_list)
    {
        if(p.name == "setEthernet")
        {
            return;
        }
    }

    ST_PROC proc;
    proc.cmd = "setEthernet";
    proc.arg = QStringList() << ip << subnet << gateway << dns1 << dns2;
    proc.print = false;
    cmd_list.append(proc);

}

void CMD_CHECKER::setIP(bool is_manual, QString ssid, QString ip, QString subnet, QString gateway, QString dns1, QString dns2)
{
    for(ST_PROC p : cmd_list)
    {
        if(p.name == "setIP")
        {
            return;
        }
    }

    ST_PROC proc;
    proc.cmd = "setIP";
    if(is_manual == true)
    {
        proc.arg = QStringList() << "manual" << ssid << ip << subnet << gateway << dns1 << dns2;
    }
    else
    {
        proc.arg = QStringList() << "dhcp" << ssid << ip << subnet << gateway << dns1 << dns2;
    }

    proc.print = false;
    cmd_list.append(proc);
}

void CMD_CHECKER::gitPull()
{
    for(ST_PROC p : cmd_list)
    {
        if(p.name == "gitPull")
        {
            return;
        }
    }
    ST_PROC proc;
    proc.cmd = "gitPull";
    proc.arg = QStringList();
    proc.print = false;
    cmd_list.append(proc);
}

void CMD_CHECKER::gitReset()
{
    for(ST_PROC p : cmd_list)
    {
        if(p.name == "gitReset")
        {
            return;
        }
    }

    ST_PROC proc;
    proc.cmd = "gitReset";
    proc.arg = QStringList();
    proc.print = false;
    cmd_list.append(proc);
}

