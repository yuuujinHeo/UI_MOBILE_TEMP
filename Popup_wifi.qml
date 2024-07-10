import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.0
import "."
import io.qt.Supervisor 1.0
import QtQuick.Controls.Styles 1.4

Popup{
    id: popup_wifi
    anchors.centerIn: parent
    leftPadding: 0
    rightPadding: 0
    topPadding: 0
    bottomPadding: 0
    width: 1280
    height: 650
    closePolicy: Popup.NoAutoClose
    background: Rectangle{
        anchors.fill: parent
        color:"transparent"
    }
    signal cancel;
    signal done;
    function ip_update(){
        var ip = supervisor.getcurIP().split(".");
        print("ip update ",supervisor.getcurIP());
        if(ip.length >3){
            ip__1.text = ip[0];
            ip__2.text = ip[1];
            ip__3.text = ip[2];
            ip__4.text = ip[3];
        }else{
            ip__1.text = "";
            ip__2.text = "";
            ip__3.text = "";
            ip__4.text = "";
        }

        var netmask = supervisor.getcurNetmask().split(".");
        if(netmask.length >3){
            netmask__1.text = netmask[0];
            netmask__2.text = netmask[1];
            netmask__3.text = netmask[2];
            netmask__4.text = netmask[3];
        }else{
            netmask__1.text = "";
            netmask__2.text = "";
            netmask__3.text = "";
            netmask__4.text = "";
        }

        ip = supervisor.getcurGateway().split(".");
        if(ip.length >3){
            gateway__1.text = ip[0];
            gateway__2.text = ip[1];
            gateway__3.text = ip[2];
            gateway__4.text = ip[3];
        }else{
            gateway__1.text = "";
            gateway__2.text = "";
            gateway__3.text = "";
            gateway__4.text = "";
        }

        ip = supervisor.getcurDNS().split(".");
        if(ip.length >3){
            dns_1.text = ip[0];
            dns_2.text = ip[1];
            dns_3.text = ip[2];
            dns_4.text = ip[3];
        }else{
            dns_1.text = "";
            dns_2.text = "";
            dns_3.text = "";
            dns_4.text = "";
        }

        var dnsserv = supervisor.getcurDNS2().split(".");
        if(dnsserv.length >3){
            dnsserv_1.text = dnsserv[0];
            dnsserv_2.text = dnsserv[1];
            dnsserv_3.text = dnsserv[2];
            dnsserv_4.text = dnsserv[3];
        }else{
            dnsserv_1.text = "";
            dnsserv_2.text = "";
            dnsserv_3.text = "";
            dnsserv_4.text = "";
        }

        if(supervisor.getcurIPMethod() === "auto"){
            rb_dhcp.checked = true;
            rb_manual.checked = false;
        }else{
            rb_dhcp.checked = false;
            rb_manual.checked = true;
        }


        ip__1.ischanged = false;
        ip__2.ischanged = false;
        ip__3.ischanged = false;
        ip__4.ischanged = false;
        netmask__1.ischanged = false;
        netmask__2.ischanged = false;
        netmask__3.ischanged = false;
        netmask__4.ischanged = false;
        gateway__1.ischanged = false;
        gateway__2.ischanged = false;
        gateway__3.ischanged = false;
        gateway__4.ischanged = false;
        dns_1.ischanged = false;
        dns_2.ischanged = false;
        dns_3.ischanged = false;
        dns_4.ischanged = false;
        dnsserv_1.ischanged = false;
        dnsserv_2.ischanged = false;
        dnsserv_3.ischanged = false;
        dnsserv_4.ischanged = false;
    }
    property int connection : 0
    property int setting_step: 0
    property bool show_passwd: false
    property bool auto_repeat: true
    property int select_wifi: -1

    property string select_ssid: ""
    property int select_level: 0
    property bool select_security: false
    property bool select_inuse: false

    onSetting_stepChanged: {
        if(setting_step === 0){
            connection = 0;
            timer_update_wifi.start();
            select_wifi = -1
            select_inuse = false;
            select_security = false;
            select_ssid = "";
            select_level = 0;
        }else{
            timer_update_wifi.stop();
        }
    }
    function init(){
        timer_update_wifi.start();
        setting_step = 0;
    }
    onOpened:{
        init();
    }
    onClosed:{
        timer_update_wifi.stop();
        init();
    }
    function con_success(){
        connection = 2;
        ip_update();
    }
    function con_fail(){
        connection = 0;
        popup_fail_con.open();
    }
    function set_success(){
        ip_update();
    }
    function set_fail(){
        ip_update();
    }

    Timer{
        id: timer_update_wifi
        running: false
        repeat: auto_repeat
        interval: 1000
        triggeredOnStart: true
        onTriggered: {
            supervisor.getAllWifiList();
            model_wifis.clear();
            for(var i=0; i<supervisor.getWifiNum(); i++){
                var ssid = supervisor.getWifiSSID(i);
                if(ssid !== "unknown" && ssid !== ""){
                    model_wifis.append({"ssid":ssid,"inuse":supervisor.getWifiInuse(ssid),"level":supervisor.getWifiLevel(ssid),"security":supervisor.getWifiSecurity(ssid)});
                }
            }
        }
    }

    Rectangle{
        anchors.fill: parent
        color: "transparent"
        Rectangle{
            width: 1280
            height: 600
            anchors.bottom: parent.bottom
            Column{
                anchors.centerIn: parent
                spacing:30
                visible: popup_wifi.setting_step === 0
                Text{
                    id: text_main_wifi
                    anchors.horizontalCenter: parent.horizontalCenter
                    color: color_dark_black
                    font.family: font_noto_r.name
                    font.pixelSize: 40
                    text:qsTr("무선 WIFI를 검색중입니다..")
                }
                Rectangle{
                    width: 1280
                    height: 450
                    Flickable{
                        id: flickable_wifi
                        anchors.fill: parent
                        clip: true
                        contentHeight: col_wifis.height
                        Column{
                            id: col_wifis
                            anchors.centerIn: parent
                            spacing: 10
                            Repeater{
                                model : ListModel{id: model_wifis}
                                Rectangle{
                                    width: 700
                                    height: 50
                                    radius: 20
                                    color:popup_wifi.select_wifi===index?color_green:"white"
                                    Rectangle{
                                        width: 600
                                        height: 50
                                        anchors.centerIn: parent
                                        color: "transparent"
                                        Text{
                                            anchors.centerIn: parent
                                            font.family: font_noto_r.name
                                            color:popup_wifi.select_wifi===index?"white":"black"
                                            text: ssid
                                        }
                                        Rectangle{
                                            width: 100
                                            height: 50
                                            anchors.verticalCenter: parent.verticalCenter
                                            anchors.right: parent.right
                                            anchors.rightMargin: 10
                                            color: "transparent"
                                            Text{
                                                anchors.centerIn: parent
                                                font.family: font_noto_r.name
                                                text:qsTr("(사용중)")
                                                color: color_red
                                                visible: inuse
                                                font.pixelSize: 15
                                            }
                                        }
                                        Rectangle{
                                            width: 100
                                            height: 50
                                            anchors.verticalCenter: parent.verticalCenter
                                            anchors.right: parent.right
                                            anchors.rightMargin: 10
                                            color: "transparent"
                                            Image{
                                                visible: !inuse && security
                                                anchors.centerIn: parent
                                                source: "icon/icon_lock_2.png"
                                                width: 50
                                                height: 50
                                                sourceSize.width: width
                                                sourceSize.height: height
                                                ColorOverlay{
                                                    anchors.fill: parent
                                                    source: parent
                                                    color: color_gray
                                                }
                                            }
                                        }

                                        Rectangle{
                                            width: 30
                                            height: 30
                                            radius: 5
                                            anchors.verticalCenter: parent.verticalCenter
                                            anchors.left: parent.left
                                            anchors.leftMargin: 10
                                            Row{
                                                spacing: 1
                                                anchors.centerIn: parent
                                                Rectangle{
                                                    width: 5
                                                    anchors.bottom: parent.bottom
                                                    height:level<1?2:5
                                                    color:{
                                                        if(level===0){
                                                            color_red
                                                        }else if(level===1){
                                                            color_red
                                                        }else if(level===2){
                                                            color_yellow
                                                        }else if(level===3){
                                                            color_green
                                                        }else if(level==4){
                                                            color_green
                                                        }
                                                    }
                                                }
                                                Rectangle{
                                                    width: 5
                                                    anchors.bottom: parent.bottom
                                                    height:level<2?2:10
                                                    color:{
                                                        if(level===0){
                                                            color_red
                                                        }else if(level===1){
                                                            color_red
                                                        }else if(level===2){
                                                            color_yellow
                                                        }else if(level===3){
                                                            color_green
                                                        }else if(level===4){
                                                            color_green
                                                        }
                                                    }
                                                }
                                                Rectangle{
                                                    width: 5
                                                    anchors.bottom: parent.bottom
                                                    height:level<3?2:15
                                                    color:{
                                                        if(level===0){
                                                            color_red
                                                        }else if(level===1){
                                                            color_red
                                                        }else if(level===2){
                                                            color_yellow
                                                        }else if(level===3){
                                                            color_green
                                                        }else if(level===4){
                                                            color_green
                                                        }
                                                    }
                                                }
                                                Rectangle{
                                                    width: 5
                                                    anchors.bottom: parent.bottom
                                                    height:level<4?2:20
                                                    color:{
                                                        if(level===0){
                                                            color_red
                                                        }else if(level===1){
                                                            color_red
                                                        }else if(level===2){
                                                            color_yellow
                                                        }else if(level===3){
                                                            color_green
                                                        }else if(level===4){
                                                            color_green
                                                        }
                                                    }
                                                }
                                            }

                                        }
                                    }

                                    MouseArea{
                                        anchors.fill: parent
                                        onClicked:{
                                            supervisor.playSound('click');
                                            select_wifi = index;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            Column{
                anchors.right: parent.right
                anchors.rightMargin: 60
                anchors.top: parent.top
                anchors.topMargin: 60
                visible: popup_wifi.setting_step ===0
                Grid{
                    columns: 2
                    rows: 2
                    anchors.horizontalCenter: parent.horizontalCenter
                    horizontalItemAlignment: Grid.AlignHCenter
                    verticalItemAlignment: Grid.AlignVCenter
                    spacing: 10
                    RadioButton{
                        id: radio_update_always
                        width: 30
                        height: 30
                        checked: auto_repeat
                        onClicked: {
                            if(!auto_repeat){
                                timer_update_wifi.start();
                                auto_repeat = true;
                            }
                        }
                    }
                    RadioButton{
                        id: radio_update_once
                        width: 30
                        height: 30
                        checked: !auto_repeat
                        onClicked: {
                            if(auto_repeat){
                                auto_repeat = false;
                                timer_update_wifi.stop();
                            }
                        }
                    }
                    Text{
                        text:qsTr("자동검색")
                        font.family: font_noto_r.name
                    }
                    Text{
                        text:qsTr("수동검색")
                        font.family: font_noto_r.name
                    }
                }

                Item_buttons{
                    type:"round_text"
                    width: 150
                    height: 50
                    text:qsTr("재검색")
                    fontsize: 20
                    anchors.horizontalCenter: parent.horizontalCenter
                    visible: !auto_repeat
                    onClicked:{
                        timer_update_wifi.start();
                    }
                }
            }


            Column{
                anchors.centerIn: parent
                spacing:30
                visible: popup_wifi.setting_step ===1
                enabled: visible
                Text{
                    anchors.horizontalCenter: parent.horizontalCenter
                    color: color_dark_black
                    font.family: font_noto_r.name
                    font.pixelSize: 40
                    text:qsTr("무선 WIFI에 연결합니다.")
                }

                Rectangle{
                    width: 1280
                    height: 450
                    Rectangle{
                        width: 1280
                        height: 50
                        radius: 20
                        Rectangle{
                            width: 600
                            height: 50
                            anchors.horizontalCenter: parent.horizontalCenter
                            color: "transparent"
                            Text{
                                anchors.centerIn: parent
                                font.family: font_noto_r.name
                                text: select_ssid
                            }
                            Text{
                                font.family: font_noto_r.name
                                text:qsTr("(사용중)")
                                color: color_red
                                visible: select_inuse
                                font.pixelSize: 15
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.right: parent.right
                                anchors.rightMargin: 10
                            }
                            Image{
                                visible: !select_inuse && select_security
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.right: parent.right
                                source: "icon/icon_lock_2.png"
                                width: 50
                                height: 50
                                sourceSize.width: width
                                sourceSize.height: height
                                ColorOverlay{
                                    anchors.fill: parent
                                    source: parent
                                    color: color_gray
                                }
                            }
                            Rectangle{
                                width: 30
                                height: 30
                                radius: 5
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 10
                                Row{
                                    spacing: 1
                                    anchors.centerIn: parent
                                    Rectangle{
                                        width: 5
                                        anchors.bottom: parent.bottom
                                        height:select_level<1?2:5
                                        color:{
                                            if(select_level==0){
                                                color_red
                                            }else if(select_level==1){
                                                color_red
                                            }else if(select_level==2){
                                                color_yellow
                                            }else if(select_level==3){
                                                color_green
                                            }else if(select_level==4){
                                                color_green
                                            }
                                        }
                                    }
                                    Rectangle{
                                        width: 5
                                        anchors.bottom: parent.bottom
                                        height:select_level<2?2:10
                                        color:{
                                            if(select_level==0){
                                                color_red
                                            }else if(select_level==1){
                                                color_red
                                            }else if(select_level==2){
                                                color_yellow
                                            }else if(select_level==3){
                                                color_green
                                            }else if(select_level==4){
                                                color_green
                                            }
                                        }
                                    }
                                    Rectangle{
                                        width: 5
                                        anchors.bottom: parent.bottom
                                        height:select_level<3?2:15
                                        color:{
                                            if(select_level==0){
                                                color_red
                                            }else if(select_level==1){
                                                color_red
                                            }else if(select_level==2){
                                                color_yellow
                                            }else if(select_level==3){
                                                color_green
                                            }else if(select_level==4){
                                                color_green
                                            }
                                        }
                                    }
                                    Rectangle{
                                        width: 5
                                        anchors.bottom: parent.bottom
                                        height:select_level<4?2:20
                                        color:{
                                            if(select_level==0){
                                                color_red
                                            }else if(select_level==1){
                                                color_red
                                            }else if(select_level==2){
                                                color_yellow
                                            }else if(select_level==3){
                                                color_green
                                            }else if(select_level==4){
                                                color_green
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }

                    Column{
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.verticalCenterOffset: 25
                        anchors.horizontalCenter: parent.horizontalCenter
                        spacing: 25
                        Rectangle{
                            anchors.horizontalCenter: parent.horizontalCenter
                            visible:{
                                if(select_security){
                                    if(popup_wifi.connection === 1){
                                        false
                                    }else if(popup_wifi.connection === 2){
                                        true
                                    }else{
                                        false
                                    }
                                }else{
                                    true
                                }
                            }
                            color:popup_wifi.connection===0?color_red:popup_wifi.connection===1?color_yellow:color_green
                            width: 500
                            height: 50
                            radius: 5
                            Text{
                                anchors.centerIn: parent
                                font.family: font_noto_r.name
                                color:popup_wifi.connection===0?"black":"white"
                                text:popup_wifi.connection===0?qsTr("연결 안됨"):popup_wifi.connection===1?qsTr("연결 중"):qsTr("연결 성공")
                                font.pixelSize: 20
                            }
                        }
                        Text{
                            visible: !popup_wifi.connection&&select_security
                            anchors.horizontalCenter: parent.horizontalCenter
                            text:qsTr("비밀번호를 입력해주세요")
                            font.family: font_noto_r.name
                            font.pixelSize: 20
                        }

                        Row{
                            visible: !popup_wifi.connection&&select_security
                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.horizontalCenterOffset: 35
                            spacing: 20
                            Column{
                                anchors.verticalCenter: parent.verticalCenter
                                TextField{
                                    id: passwd_wifi
                                    width: 400
                                    height: 50
                                    enabled: popup_wifi.connection === 0
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    horizontalAlignment: Text.AlignHCenter
                                    echoMode: popup_wifi.show_passwd?TextInput.Normal:TextInput.Password
                                    onTextChanged: {
                                        color = "black"
                                    }
                                }
                            }
                            Rectangle{
                                width: 50
                                height: 50
                                radius:10
                                color: color_dark_navy
                                enabled: popup_wifi.connection === 0
                                anchors.verticalCenter: parent.verticalCenter
                                Image{
                                    anchors.centerIn: parent
                                    width: 35
                                    height: 35
                                    sourceSize.width: width
                                    sourceSize.height: height
                                    source: "icon/icon_keyboard.png"
                                    ColorOverlay{
                                        anchors.fill: parent
                                        source: parent
                                        color: "white"
                                    }
                                }
                                MouseArea{
                                    enabled: parent.enabled
                                    anchors.fill: parent
                                    onClicked:{
                                        supervisor.playSound('click');
                                        keyboard.owner = passwd_wifi;
                                        passwd_wifi.selectAll();
                                        keyboard.open();
                                    }
                                }
                            }
                            Rectangle{
                                anchors.verticalCenter: parent.verticalCenter
                                width: 50
                                height: 50
                                radius: 10
                                enabled: popup_wifi.connection === 0
                                color: color_dark_navy
                                Image{
                                    anchors.centerIn: parent
                                    width: 35
                                    height: 35
                                    sourceSize.width: width
                                    sourceSize.height: height
                                    source:popup_wifi.show_passwd?"icon/icon_eye_open.png":"icon/icon_eye_close.png"
                                }
                                MouseArea{
                                    anchors.fill: parent
                                    onClicked:{
                                        supervisor.playSound('click');
                                        if(popup_wifi.show_passwd){
                                            popup_wifi.show_passwd = false;
                                        }else{
                                            popup_wifi.show_passwd = true;
                                        }
                                    }
                                }
                            }
                        }
                        Rectangle{
                            width: 200
                            height: 80
                            radius: 40
                            visible: popup_wifi.connection===0
                            anchors.horizontalCenter: parent.horizontalCenter
                            color: "black"
                            Text{
                                anchors.centerIn: parent
                                text:qsTr("연결")
                                font.pixelSize: 35
                                font.family: font_noto_r.name
                                color: "white"
                            }
                            MouseArea{
                                anchors.fill: parent
                                onClicked: {
                                    if(select_security){
                                        if(passwd_wifi.text == ""){
                                            supervisor.playSound('no');
                                        }else{
                                            supervisor.playSound('click');
                                            print("check connect", select_ssid, passwd_wifi.text);
                                            supervisor.connectWifi(select_ssid, passwd_wifi.text);
                                            popup_wifi.connection = 1;
                                            popup_loading.open();
                                        }
                                    }else{
                                        supervisor.playSound('click');
                                        print("check connect", select_ssid, passwd_wifi.text);
                                        supervisor.connectWifi(select_ssid, "");
                                        popup_wifi.connection = 1;
                                        popup_loading.open();
                                    }
                                }
                            }
                        }
                    }
                }
            }

            Column{
                anchors.centerIn: parent
                spacing:30
                visible: popup_wifi.setting_step ===2
                Text{
                    anchors.horizontalCenter: parent.horizontalCenter
                    color: color_dark_black
                    font.family: font_noto_r.name
                    font.pixelSize: 40
                    text:qsTr("무선 WIFI의 IP를 세팅합니다")
                }
                Rectangle{
                    width: 1280
                    height: 450
                    radius: 20
                    Column{
                        visible: !popup_loading.visible
                        anchors.centerIn: parent
                        spacing: 50

                        Column{
                            anchors.horizontalCenter: parent.horizontalCenter
                            spacing: 20
                            Rectangle{
                                width: 1280
                                height: 50
                                anchors.horizontalCenter: parent.horizontalCenter
                                Row{
                                    anchors.centerIn: parent
                                    spacing: 50
                                    Row{
                                        RadioButton{
                                            id: rb_dhcp
                                            checked: true
                                            anchors.verticalCenter: parent.verticalCenter
                                            onCheckedChanged: {
                                                if(checked){
                                                    rb_manual.checked = false;
                                                }else{
                                                    rb_manual.checked = true;
                                                }
                                            }
                                        }
                                        Text{
                                            text: "DHCP"
                                            font.family: font_noto_r.name
                                            font.pixelSize: 25
                                            anchors.verticalCenter: parent.verticalCenter
                                        }
                                    }
                                    Row{
                                        RadioButton{
                                            id: rb_manual
                                            checked: false
                                            anchors.verticalCenter: parent.verticalCenter
                                            onCheckedChanged: {
                                                if(checked){
                                                    rb_dhcp.checked = false;
                                                }else{
                                                    rb_dhcp.checked = true;
                                                }
                                            }
                                        }
                                        Text{
                                            text: "MANUAL"
                                            font.family: font_noto_r.name
                                            font.pixelSize: 25
                                            anchors.verticalCenter: parent.verticalCenter
                                        }
                                    }
                                }
                            }


                            Column{
                                enabled: rb_manual.checked
                                anchors.horizontalCenter: parent.horizontalCenter
                                spacing: 10

                                Row{
                                    width: 700
                                    height: 50
                                    Rectangle{
                                        width: 200
                                        height: parent.height
                                        Text{
                                            anchors.verticalCenter: parent.verticalCenter
                                            anchors.left: parent.left
                                            anchors.leftMargin: 50
                                            font.family: font_noto_r.name
                                            text:qsTr("IP")
                                            font.pixelSize: 20
                                        }
                                    }
                                    Rectangle{
                                        width: 1
                                        height: parent.height
                                        color: "#d0d0d0"
                                    }
                                    Rectangle{
                                        width: parent.width - 201
                                        height: parent.height
                                        Row{
                                            spacing: 10
                                            anchors.centerIn: parent
                                            TextField{
                                                id: ip__1
                                                width: 70
                                                height: 40
                                                MouseArea{
                                                    anchors.fill:parent
                                                    onClicked: {
                                                        supervisor.playSound('click');
                                                        if(keypad.is_opened){
                                                            keypad.owner = ip__1;
                                                            ip__1.selectAll();
                                                        }else{
                                                            keypad.owner = ip__1;
                                                            ip__1.selectAll();
                                                            keypad.open();
                                                        }
                                                    }
                                                }
                                                color: ischanged?color_red:"black"
                                                property bool ischanged: false
                                                onTextChanged: {
                                                    ischanged = true;
                                                    if(ip__1.text.split(".").length > 1){
                                                        ip__1.text = ip__1.text.split(".")[0];
                                                        keypad.owner = ip__2;
                                                        ip__2.selectAll();
                                                    }
                                                    if(ip__1.text.length == 3){
                                                        keypad.owner = ip__2;
                                                        ip__2.selectAll();
                                                    }
                                                }
                                            }
                                            Text{
                                                anchors.verticalCenter: parent.verticalCenter
                                                text:"."
                                            }

                                            TextField{
                                                id: ip__2
                                                width: 70
                                                height: 40
                                                MouseArea{
                                                    anchors.fill:parent
                                                    onClicked: {
                                                        supervisor.playSound('click');
                                                        if(keypad.is_opened){
                                                            keypad.owner = ip__2;
                                                            ip__2.selectAll();
                                                        }else{
                                                            keypad.owner = ip__2;
                                                            ip__2.selectAll();
                                                            keypad.open();
                                                        }
                                                    }
                                                }
                                                color: ischanged?color_red:"black"
                                                property bool ischanged: false
                                                onTextChanged: {
                                                    ischanged = true;
                                                    if(ip__2.text == "."){
                                                        ip__2.text = ip__2.text.split(".")[0]
                                                    }

                                                    if(ip__2.text.split(".").length > 1){
                                                        ip__2.text = ip__2.text.split(".")[0];
                                                        keypad.owner = ip__3;
                                                        ip__3.selectAll();
                                                    }
                                                    if(ip__2.text.length == 3){
                                                        keypad.owner = ip__3;
                                                        ip__3.selectAll();
                                                    }
                                                }
                                            }
                                            Text{
                                                anchors.verticalCenter: parent.verticalCenter
                                                text:"."
                                            }
                                            TextField{
                                                id: ip__3
                                                width: 70
                                                height: 40
                                                MouseArea{
                                                    anchors.fill:parent
                                                    onClicked: {
                                                        supervisor.playSound('click');
                                                        if(keypad.is_opened){
                                                            keypad.owner = ip__3;
                                                            ip__3.selectAll();
                                                        }else{
                                                            keypad.owner = ip__3;
                                                            ip__3.selectAll();
                                                            keypad.open();
                                                        }
                                                    }
                                                }

                                                color: ischanged?color_red:"black"
                                                property bool ischanged: false
                                                onTextChanged: {
                                                    ischanged = true;
                                                    if(ip__3.text == "."){
                                                        ip__3.text = ip__3.text.split(".")[0]
                                                    }

                                                    if(ip__3.text.split(".").length > 1){
                                                        ip__3.text = ip__3.text.split(".")[0];
                                                        keypad.owner = ip__4;
                                                        ip__4.selectAll();
                                                    }
                                                    if(ip__3.text.length == 3){
                                                        keypad.owner = ip__4;
                                                        ip__4.selectAll();
                                                    }
                                                }
                                            }
                                            Text{
                                                anchors.verticalCenter: parent.verticalCenter
                                                text:"."
                                            }
                                            TextField{
                                                id: ip__4
                                                width: 70
                                                height: 40
                                                MouseArea{
                                                    anchors.fill:parent
                                                    onClicked: {
                                                        supervisor.playSound('click');
                                                        if(keypad.is_opened){
                                                            keypad.owner = ip__4;
                                                            ip__4.selectAll();
                                                        }else{
                                                            keypad.owner = ip__4;
                                                            ip__4.selectAll();
                                                            keypad.open();
                                                        }
                                                    }
                                                }
                                                color: ischanged?color_red:"black"
                                                property bool ischanged: false
                                                onTextChanged: {
                                                    ischanged = true;
                                                    if(ip__4.text == "."){
                                                        ip__4.text = ip__4.text.split(".")[0]
                                                    }

                                                    if(ip__4.text.split(".").length > 1){
                                                        ip__4.text = ip__4.text.split(".")[0];
                                                        keypad.close();
                                                    }
                                                    if(ip__4.text.length == 3){
                                                        keypad.close();
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }

                                Row{
                                    width: 700
                                    height: 50
                                    Rectangle{
                                        width: 200
                                        height: parent.height
                                        Text{
                                            anchors.verticalCenter: parent.verticalCenter
                                            anchors.left: parent.left
                                            anchors.leftMargin: 50
                                            font.family: font_noto_r.name
                                            text:"Netmask"
                                            font.pixelSize: 20
                                        }
                                    }
                                    Rectangle{
                                        width: 1
                                        height: parent.height
                                        color: "#d0d0d0"
                                    }

                                    Rectangle{
                                        width: parent.width - 201
                                        height: parent.height
                                        Row{
                                            spacing: 10
                                            anchors.centerIn: parent
                                            TextField{
                                                id: netmask__1
                                                width: 70
                                                height: 40
                                                MouseArea{
                                                    anchors.fill:parent
                                                    onClicked: {
                                                        supervisor.playSound('click');
                                                        if(keypad.is_opened){
                                                            keypad.owner = netmask__1;
                                                            netmask__1.selectAll();
                                                        }else{
                                                            keypad.owner = netmask__1;
                                                            netmask__1.selectAll();
                                                            keypad.open();
                                                        }
                                                    }
                                                }
                                                color: ischanged?color_red:"black"
                                                property bool ischanged: false
                                                onTextChanged: {
                                                    ischanged = true;
                                                    if(netmask__1.text.split(".").length > 1){
                                                        netmask__1.text = netmask__1.text.split(".")[0];
                                                        keypad.owner = netmask__2;
                                                        netmask__2.selectAll();
                                                    }
                                                    if(netmask__1.text.length == 3){
                                                        keypad.owner = netmask__2;
                                                        netmask__2.selectAll();
                                                    }
                                                }
                                            }
                                            Text{
                                                anchors.verticalCenter: parent.verticalCenter
                                                text:"."
                                            }

                                            TextField{
                                                id: netmask__2
                                                width: 70
                                                height: 40
                                                MouseArea{
                                                    anchors.fill:parent
                                                    onClicked: {
                                                        supervisor.playSound('click');
                                                        if(keypad.is_opened){
                                                            keypad.owner = netmask__2;
                                                            netmask__2.selectAll();
                                                        }else{
                                                            keypad.owner = netmask__2;
                                                            netmask__2.selectAll();
                                                            keypad.open();
                                                        }
                                                    }
                                                }
                                                color: ischanged?color_red:"black"
                                                property bool ischanged: false
                                                onTextChanged: {
                                                    ischanged = true;
                                                    if(netmask__2.text == "."){
                                                        netmask__2.text = netmask__2.text.split(".")[0]
                                                    }

                                                    if(netmask__2.text.split(".").length > 1){
                                                        netmask__2.text = netmask__2.text.split(".")[0];
                                                        keypad.owner = netmask__3;
                                                        netmask__3.selectAll();
                                                    }
                                                    if(netmask__2.text.length == 3){
                                                        keypad.owner = netmask__3;
                                                        netmask__3.selectAll();
                                                    }
                                                }
                                            }
                                            Text{
                                                anchors.verticalCenter: parent.verticalCenter
                                                text:"."
                                            }
                                            TextField{
                                                id: netmask__3
                                                width: 70
                                                height: 40
                                                MouseArea{
                                                    anchors.fill:parent
                                                    onClicked: {
                                                        supervisor.playSound('click');
                                                        if(keypad.is_opened){
                                                            keypad.owner = netmask__3;
                                                            netmask__3.selectAll();
                                                        }else{
                                                            keypad.owner = netmask__3;
                                                            netmask__3.selectAll();
                                                            keypad.open();
                                                        }
                                                    }
                                                }
                                                color: ischanged?color_red:"black"
                                                property bool ischanged: false
                                                onTextChanged: {
                                                    ischanged = true;
                                                    if(netmask__3.text == "."){
                                                        netmask__3.text = netmask__3.text.split(".")[0]
                                                    }

                                                    if(netmask__3.text.split(".").length > 1){
                                                        netmask__3.text = netmask__3.text.split(".")[0];
                                                        keypad.owner = netmask__4;
                                                        netmask__4.selectAll();
                                                    }
                                                    if(netmask__3.text.length == 3){
                                                        keypad.owner = netmask__4;
                                                        netmask__4.selectAll();
                                                    }
                                                }
                                            }
                                            Text{
                                                anchors.verticalCenter: parent.verticalCenter
                                                text:"."
                                            }
                                            TextField{
                                                id: netmask__4
                                                width: 70
                                                height: 40
                                                MouseArea{
                                                    anchors.fill:parent
                                                    onClicked: {
                                                        supervisor.playSound('click');
                                                        if(keypad.is_opened){
                                                            keypad.owner = netmask__4;
                                                            netmask__4.selectAll();
                                                        }else{
                                                            keypad.owner = netmask__4;
                                                            netmask__4.selectAll();
                                                            keypad.open();
                                                        }
                                                    }
                                                }
                                                color: ischanged?color_red:"black"
                                                property bool ischanged: false
                                                onTextChanged: {
                                                    ischanged = true;
                                                    if(netmask__4.text == "."){
                                                        netmask__4.text = netmask__4.text.split(".")[0]
                                                    }

                                                    if(netmask__4.text.split(".").length > 1){
                                                        netmask__4.text = netmask__4.text.split(".")[0];
                                                        keypad.close();
                                                    }
                                                    if(netmask__4.text.length == 3){
                                                        keypad.close();
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }

                                Row{
                                    width: 700
                                    height: 50
                                    Rectangle{
                                        width: 200
                                        height: parent.height
                                        Text{
                                            anchors.verticalCenter: parent.verticalCenter
                                            anchors.left: parent.left
                                            anchors.leftMargin: 50
                                            font.family: font_noto_r.name
                                            text:"Gateway"
                                            font.pixelSize: 20
                                        }
                                    }
                                    Rectangle{
                                        width: 1
                                        height: parent.height
                                        color: "#d0d0d0"
                                    }

                                    Rectangle{
                                        width: parent.width - 201
                                        height: parent.height
                                        Row{
                                            spacing: 10
                                            anchors.centerIn: parent
                                            TextField{
                                                id: gateway__1
                                                width: 70
                                                height: 40
                                                MouseArea{
                                                    anchors.fill:parent
                                                    onClicked: {
                                                        supervisor.playSound('click');
                                                        if(keypad.is_opened){
                                                            keypad.owner = gateway__1;
                                                            gateway__1.selectAll();
                                                        }else{
                                                            keypad.owner = gateway__1;
                                                            gateway__1.selectAll();
                                                            keypad.open();
                                                        }
                                                    }
                                                }
                                                color: ischanged?color_red:"black"
                                                property bool ischanged: false
                                                onTextChanged: {
                                                    ischanged = true;
                                                    if(gateway__1.text.split(".").length > 1){
                                                        gateway__1.text = gateway__1.text.split(".")[0];
                                                        keypad.owner = gateway__2;
                                                        gateway__2.selectAll();
                                                    }
                                                    if(gateway__1.text.length == 3){
                                                        keypad.owner = gateway__2;
                                                        gateway__2.selectAll();
                                                    }
                                                }
                                            }
                                            Text{
                                                anchors.verticalCenter: parent.verticalCenter
                                                text:"."
                                            }

                                            TextField{
                                                id: gateway__2
                                                width: 70
                                                height: 40
                                                MouseArea{
                                                    anchors.fill:parent
                                                    onClicked: {
                                                        supervisor.playSound('click');
                                                        if(keypad.is_opened){
                                                            keypad.owner = gateway__2;
                                                            gateway__2.selectAll();
                                                        }else{
                                                            keypad.owner = gateway__2;
                                                            gateway__2.selectAll();
                                                            keypad.open();
                                                        }
                                                    }
                                                }
                                                color: ischanged?color_red:"black"
                                                property bool ischanged: false
                                                onTextChanged: {
                                                    ischanged = true;
                                                    if(gateway__2.text == "."){
                                                        gateway__2.text = gateway__2.text.split(".")[0]
                                                    }

                                                    if(gateway__2.text.split(".").length > 1){
                                                        gateway__2.text = gateway__2.text.split(".")[0];
                                                        keypad.owner = gateway__3;
                                                        gateway__3.selectAll();
                                                    }
                                                    if(gateway__2.text.length == 3){
                                                        keypad.owner = gateway__3;
                                                        gateway__3.selectAll();
                                                    }
                                                }
                                            }
                                            Text{
                                                anchors.verticalCenter: parent.verticalCenter
                                                text:"."
                                            }
                                            TextField{
                                                id: gateway__3
                                                width: 70
                                                height: 40
                                                MouseArea{
                                                    anchors.fill:parent
                                                    onClicked: {
                                                        supervisor.playSound('click');
                                                        if(keypad.is_opened){
                                                            keypad.owner = gateway__3;
                                                            gateway__3.selectAll();
                                                        }else{
                                                            keypad.owner = gateway__3;
                                                            gateway__3.selectAll();
                                                            keypad.open();
                                                        }
                                                    }
                                                }
                                                color: ischanged?color_red:"black"
                                                property bool ischanged: false
                                                onTextChanged: {
                                                    ischanged = true;
                                                    if(gateway__3.text == "."){
                                                        gateway__3.text = gateway__3.text.split(".")[0]
                                                    }

                                                    if(gateway__3.text.split(".").length > 1){
                                                        gateway__3.text = gateway__3.text.split(".")[0];
                                                        keypad.owner = gateway__4;
                                                        gateway__4.selectAll();
                                                    }
                                                    if(gateway__3.text.length == 3){
                                                        keypad.owner = gateway__4;
                                                        gateway__4.selectAll();
                                                    }
                                                }
                                            }
                                            Text{
                                                anchors.verticalCenter: parent.verticalCenter
                                                text:"."
                                            }
                                            TextField{
                                                id: gateway__4
                                                width: 70
                                                height: 40
                                                MouseArea{
                                                    anchors.fill:parent
                                                    onClicked: {
                                                        supervisor.playSound('click');
                                                        if(keypad.is_opened){
                                                            keypad.owner = gateway__4;
                                                            gateway__4.selectAll();
                                                        }else{
                                                            keypad.owner = gateway__4;
                                                            gateway__4.selectAll();
                                                            keypad.open();
                                                        }
                                                    }
                                                }
                                                color: ischanged?color_red:"black"
                                                property bool ischanged: false
                                                onTextChanged: {
                                                    ischanged = true;
                                                    if(gateway__4.text == "."){
                                                        gateway__4.text = gateway__4.text.split(".")[0]
                                                    }

                                                    if(gateway__4.text.split(".").length > 1){
                                                        gateway__4.text = gateway__4.text.split(".")[0];
                                                        keypad.close();
                                                    }
                                                    if(gateway__4.text.length == 3){
                                                        keypad.close();
                                                    }
                                                }
                                            }
                                        }
                                    }

                                }

                                Row{
                                    width: 700
                                    height: 50
                                    Rectangle{
                                        width: 200
                                        height: 50
                                        Text{
                                            anchors.verticalCenter: parent.verticalCenter
                                            anchors.left: parent.left
                                            anchors.leftMargin: 50
                                            font.family: font_noto_r.name
                                            text:"DNS1"
                                            font.pixelSize: 20
                                        }
                                    }
                                    Rectangle{
                                        width: 1
                                        height: parent.height
                                        color: "#d0d0d0"
                                    }

                                    Rectangle{
                                        width: parent.width - 201
                                        height: parent.height
                                        Row{
                                            spacing: 10
                                            anchors.centerIn: parent
                                            TextField{
                                                id: dns_1
                                                width: 70
                                                height: 40
                                                MouseArea{
                                                    anchors.fill:parent
                                                    onClicked: {
                                                        supervisor.playSound('click');
                                                        if(keypad.is_opened){
                                                            keypad.owner = dns_1;
                                                            dns_1.selectAll();
                                                        }else{
                                                            keypad.owner = dns_1;
                                                            dns_1.selectAll();
                                                            keypad.open();
                                                        }
                                                    }
                                                }
                                                color: ischanged?color_red:"black"
                                                property bool ischanged: false
                                                onTextChanged: {
                                                    ischanged = true;
                                                    if(dns_1.text.split(".").length > 1){
                                                        dns_1.text = dns_1.text.split(".")[0];
                                                        keypad.owner = dns_2;
                                                        dns_2.selectAll();
                                                    }
                                                    if(dns_1.text.length == 3){
                                                        keypad.owner = dns_2;
                                                        dns_2.selectAll();
                                                    }
                                                }
                                            }
                                            Text{
                                                anchors.verticalCenter: parent.verticalCenter
                                                text:"."
                                            }

                                            TextField{
                                                id: dns_2
                                                width: 70
                                                height: 40
                                                MouseArea{
                                                    anchors.fill:parent
                                                    onClicked: {
                                                        supervisor.playSound('click');
                                                        if(keypad.is_opened){
                                                            keypad.owner = dns_2;
                                                            dns_2.selectAll();
                                                        }else{
                                                            keypad.owner = dns_2;
                                                            dns_2.selectAll();
                                                            keypad.open();
                                                        }
                                                    }
                                                }
                                                color: ischanged?color_red:"black"
                                                property bool ischanged: false
                                                onTextChanged: {
                                                    ischanged = true;
                                                    if(dns_2.text == "."){
                                                        dns_2.text = dns_2.text.split(".")[0]
                                                    }

                                                    if(dns_2.text.split(".").length > 1){
                                                        dns_2.text = dns_2.text.split(".")[0];
                                                        keypad.owner = dns_3;
                                                        dns_3.selectAll();
                                                    }
                                                    if(dns_2.text.length == 3){
                                                        keypad.owner = dns_3;
                                                        dns_3.selectAll();
                                                    }
                                                }
                                            }
                                            Text{
                                                anchors.verticalCenter: parent.verticalCenter
                                                text:"."
                                            }
                                            TextField{
                                                id: dns_3
                                                width: 70
                                                height: 40
                                                MouseArea{
                                                    anchors.fill:parent
                                                    onClicked: {
                                                        supervisor.playSound('click');
                                                        if(keypad.is_opened){
                                                            keypad.owner = dns_3;
                                                            dns_3.selectAll();
                                                        }else{
                                                            keypad.owner = dns_3;
                                                            dns_3.selectAll();
                                                            keypad.open();
                                                        }
                                                    }
                                                }
                                                color: ischanged?color_red:"black"
                                                property bool ischanged: false
                                                onTextChanged: {
                                                    ischanged = true;
                                                    if(dns_3.text == "."){
                                                        dns_3.text = dns_3.text.split(".")[0]
                                                    }

                                                    if(dns_3.text.split(".").length > 1){
                                                        dns_3.text = dns_3.text.split(".")[0];
                                                        keypad.owner = dns_4;
                                                        dns_4.selectAll();
                                                    }
                                                    if(dns_3.text.length == 3){
                                                        keypad.owner = dns_4;
                                                        dns_4.selectAll();
                                                    }
                                                }
                                            }
                                            Text{
                                                anchors.verticalCenter: parent.verticalCenter
                                                text:"."
                                            }
                                            TextField{
                                                id: dns_4
                                                width: 70
                                                height: 40
                                                MouseArea{
                                                    anchors.fill:parent
                                                    onClicked: {
                                                        supervisor.playSound('click');
                                                        if(keypad.is_opened){
                                                            keypad.owner = dns_4;
                                                            dns_4.selectAll();
                                                        }else{
                                                            keypad.owner = dns_4;
                                                            dns_4.selectAll();
                                                            keypad.open();
                                                        }
                                                    }
                                                }
                                                color: ischanged?color_red:"black"
                                                property bool ischanged: false
                                                onTextChanged: {
                                                    ischanged = true;
                                                    if(dns_4.text == "."){
                                                        dns_4.text = dns_4.text.split(".")[0]
                                                    }

                                                    if(dns_4.text.split(".").length > 1){
                                                        dns_4.text = dns_4.text.split(".")[0];
                                                        keypad.close();
                                                    }
                                                    if(dns_4.text.length == 3){
                                                        keypad.close();
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }

                                Row{
                                    width: 700
                                    height: 50
                                    Rectangle{
                                        width: 200
                                        height: 50
                                        Text{
                                            anchors.verticalCenter: parent.verticalCenter
                                            anchors.left: parent.left
                                            anchors.leftMargin: 50
                                            font.family: font_noto_r.name
                                            text:"DNS2"
                                            font.pixelSize: 20
                                        }
                                    }
                                    Rectangle{
                                        width: 1
                                        height: parent.height
                                        color: "#d0d0d0"
                                    }

                                    Rectangle{
                                        width: parent.width - 201
                                        height: parent.height
                                        Row{
                                            spacing: 10
                                            anchors.centerIn: parent
                                            TextField{
                                                id: dnsserv_1
                                                width: 70
                                                height: 40
                                                MouseArea{
                                                    anchors.fill:parent
                                                    onClicked: {
                                                        supervisor.playSound('click');
                                                        if(keypad.is_opened){
                                                            keypad.owner = dnsserv_1;
                                                            dnsserv_1.selectAll();
                                                        }else{
                                                            keypad.owner = dnsserv_1;
                                                            dnsserv_1.selectAll();
                                                            keypad.open();
                                                        }
                                                    }
                                                }
                                                color: ischanged?color_red:"black"
                                                property bool ischanged: false
                                                onTextChanged: {
                                                    ischanged = true;
                                                    if(dnsserv_1.text.split(".").length > 1){
                                                        dnsserv_1.text = dnsserv_1.text.split(".")[0];
                                                        keypad.owner = dnsserv_2;
                                                        dnsserv_2.selectAll();
                                                    }
                                                    if(dnsserv_1.text.length == 3){
                                                        keypad.owner = dnsserv_2;
                                                        dnsserv_2.selectAll();
                                                    }
                                                }
                                            }
                                            Text{
                                                anchors.verticalCenter: parent.verticalCenter
                                                text:"."
                                            }

                                            TextField{
                                                id: dnsserv_2
                                                width: 70
                                                height: 40
                                                MouseArea{
                                                    anchors.fill:parent
                                                    onClicked: {
                                                        supervisor.playSound('click');
                                                        if(keypad.is_opened){
                                                            keypad.owner = dnsserv_2;
                                                            dnsserv_2.selectAll();
                                                        }else{
                                                            keypad.owner = dnsserv_2;
                                                            dnsserv_2.selectAll();
                                                            keypad.open();
                                                        }
                                                    }
                                                }
                                                color: ischanged?color_red:"black"
                                                property bool ischanged: false
                                                onTextChanged: {
                                                    ischanged = true;
                                                    if(dnsserv_2.text == "."){
                                                        dnsserv_2.text = dnsserv_2.text.split(".")[0]
                                                    }

                                                    if(dnsserv_2.text.split(".").length > 1){
                                                        dnsserv_2.text = dnsserv_2.text.split(".")[0];
                                                        keypad.owner = dnsserv_3;
                                                        dnsserv_3.selectAll();
                                                    }
                                                    if(dnsserv_2.text.length == 3){
                                                        keypad.owner = dnsserv_3;
                                                        dnsserv_3.selectAll();
                                                    }
                                                }
                                            }
                                            Text{
                                                anchors.verticalCenter: parent.verticalCenter
                                                text:"."
                                            }
                                            TextField{
                                                id: dnsserv_3
                                                width: 70
                                                height: 40
                                                MouseArea{
                                                    anchors.fill:parent
                                                    onClicked: {
                                                        supervisor.playSound('click');
                                                        if(keypad.is_opened){
                                                            keypad.owner = dnsserv_3;
                                                            dnsserv_3.selectAll();
                                                        }else{
                                                            keypad.owner = dnsserv_3;
                                                            dnsserv_3.selectAll();
                                                            keypad.open();
                                                        }
                                                    }
                                                }
                                                color: ischanged?color_red:"black"
                                                property bool ischanged: false
                                                onTextChanged: {
                                                    ischanged = true;
                                                    if(dnsserv_3.text == "."){
                                                        dnsserv_3.text = dnsserv_3.text.split(".")[0]
                                                    }

                                                    if(dnsserv_3.text.split(".").length > 1){
                                                        dnsserv_3.text = dnsserv_3.text.split(".")[0];
                                                        keypad.owner = dnsserv_4;
                                                        dnsserv_4.selectAll();
                                                    }
                                                    if(dnsserv_3.text.length == 3){
                                                        keypad.owner = dnsserv_4;
                                                        dnsserv_4.selectAll();
                                                    }
                                                }
                                            }
                                            Text{
                                                anchors.verticalCenter: parent.verticalCenter
                                                text:"."
                                            }
                                            TextField{
                                                id: dnsserv_4
                                                width: 70
                                                height: 40
                                                MouseArea{
                                                    anchors.fill:parent
                                                    onClicked: {
                                                        supervisor.playSound('click');
                                                        if(keypad.is_opened){
                                                            keypad.owner = dnsserv_4;
                                                            dnsserv_4.selectAll();
                                                        }else{
                                                            keypad.owner = dnsserv_4;
                                                            dnsserv_4.selectAll();
                                                            keypad.open();
                                                        }
                                                    }
                                                }
                                                color: ischanged?color_red:"black"
                                                property bool ischanged: false
                                                onTextChanged: {
                                                    ischanged = true;
                                                    if(dnsserv_4.text == "."){
                                                        dnsserv_4.text = dnsserv_4.text.split(".")[0]
                                                    }

                                                    if(dnsserv_4.text.split(".").length > 1){
                                                        dnsserv_4.text = dnsserv_4.text.split(".")[0];
                                                        keypad.close();
                                                    }
                                                    if(dnsserv_4.text.length == 3){
                                                        keypad.close();
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }

                            }

                        }

                        Row{
                            anchors.horizontalCenter: parent.horizontalCenter
                            spacing: 30
                            Rectangle{
                                width: 200
                                height: 80
                                radius: 40
                                border.width: 1
                                Text{
                                    anchors.centerIn: parent
                                    text:qsTr("초기화")
                                    font.pixelSize: 35
                                    font.family: font_noto_r.name
                                }
                                MouseArea{
                                    anchors.fill: parent
                                    onClicked: {
                                        supervisor.playSound('click');
                                        if(supervisor.getcurIP() === "")
                                            ip_update();

                                        popup_wifi.ip_update();
                                    }
                                }
                            }
                            Rectangle{
                                width: 200
                                height: 80
                                radius: 40
                                border.width: 1
                                Text{
                                    anchors.centerIn: parent
                                    text:qsTr("변 경")
                                    font.pixelSize: 35
                                    font.family: font_noto_r.name
                                }

                                MouseArea{
                                    anchors.fill: parent
                                    function check(str){
                                        var num = parseInt(str);
                                        if(num === 0){
                                            if(str === "0"){
                                                return true;
                                            }else{
                                                return false;
                                            }
                                        }else if(num === 128 || num === 192 || num === 224 || num === 240 || num === 248 || num === 252 || num === 254 || num === 255){
                                            return true;
                                        }else{
                                            return false;
                                        }
                                    }
                                    onClicked: {
                                        var success = true;
                                        //check value
                                        if(rb_dhcp.checked){
                                            supervisor.playSound('click');
                                            popup_loading.open();
                                            supervisor.setWifiDHCP();
                                        }else{
                                            if(parseInt(ip__1.text)>-1 && parseInt(ip__1.text)<256){
                                                if(parseInt(ip__2.text)>-1 && parseInt(ip__2.text)<256){
                                                    if(parseInt(ip__3.text)>-1 && parseInt(ip__3.text)<256){
                                                        if(parseInt(ip__4.text)>-1 && parseInt(ip__4.text)<256){

                                                        }else{
                                                            ip__4.color = color_red
                                                            success = false;
                                                        }
                                                    }else{
                                                        ip__3.color = color_red
                                                        success = false;
                                                    }
                                                }else{
                                                    ip__2.color = color_red
                                                    success = false;
                                                }
                                            }else{
                                                ip__1.color = color_red
                                                success = false;
                                            }

                                            if(parseInt(gateway__1.text)>-1 && parseInt(gateway__1.text)<256){
                                                if(parseInt(gateway__2.text)>-1 && parseInt(gateway__2.text)<256){
                                                    if(parseInt(gateway__3.text)>-1 && parseInt(gateway__3.text)<256){
                                                        if(parseInt(gateway__4.text)>-1 && parseInt(gateway__4.text)<256){

                                                        }else{
                                                            gateway__4.color = color_red
                                                            success = false;
                                                        }
                                                    }else{
                                                        gateway__3.color = color_red
                                                        success = false;
                                                    }
                                                }else{
                                                    gateway__2.color = color_red
                                                    success = false;
                                                }
                                            }else{
                                                gateway__1.color = color_red
                                                success = false;
                                            }

                                            if(parseInt(dns_1.text)>-1 && parseInt(dns_1.text)<256){
                                                if(parseInt(dns_2.text)>-1 && parseInt(dns_2.text)<256){
                                                    if(parseInt(dns_3.text)>-1 && parseInt(dns_3.text)<256){
                                                        if(parseInt(dns_4.text)>-1 && parseInt(dns_4.text)<256){

                                                        }else{
                                                            dns_4.color = color_red
                                                            success = false;
                                                        }
                                                    }else{
                                                        dns_3.color = color_red
                                                        success = false;
                                                    }
                                                }else{
                                                    dns_2.color = color_red
                                                    success = false;
                                                }
                                            }else{
                                                dns_1.color = color_red
                                                success = false;
                                            }

                                            if(check(netmask__1.text)){
                                                if(netmask__1.text == "255"){
                                                    if(check(netmask__2.text)){
                                                        if(netmask__2.text == "255"){
                                                            if(check(netmask__3.text)){
                                                                if(netmask__3.text == "255"){
                                                                    if(check(netmask__4.text)){

                                                                    }else{
                                                                        netmask__4.color = color_red;
                                                                        success = false;
                                                                    }
                                                                }else{
                                                                    if(netmask__4.text === "0"){

                                                                    }else{
                                                                        netmask__4.color = color_red;
                                                                        success = false;
                                                                    }
                                                                }
                                                            }else{
                                                                netmask__3.color = color_red;
                                                                success = false;
                                                            }
                                                        }else{
                                                            if(netmask__3.text === "0"){
                                                                if(netmask__4.text === "0"){

                                                                }else{
                                                                    netmask__4.color = color_red;
                                                                    success = false;
                                                                }
                                                            }else{
                                                                netmask__3.color = color_red;
                                                                success = false;
                                                            }
                                                        }
                                                    }else{
                                                        netmask__2.color = color_red;
                                                        success = false;
                                                    }
                                                }else{
                                                    if(netmask__2.text === "0"){
                                                        if(netmask__3.text === "0"){
                                                            if(netmask__4.text === "0"){

                                                            }else{
                                                                netmask__4.color = color_red;
                                                                success = false;
                                                            }
                                                        }else{
                                                            netmask__3.color = color_red;
                                                            success = false;
                                                        }
                                                    }else{
                                                        netmask__2.color = color_red;
                                                        success = false;
                                                    }
                                                }
                                            }else{
                                                netmask__1.color = color_red
                                                success = false;
                                            }

                                            keypad.close();

                                            if(success){
                                                supervisor.playSound('click');
                                                popup_loading.open();
                                                ip__1.ischanged = false;
                                                ip__2.ischanged = false;
                                                ip__3.ischanged = false;
                                                ip__4.ischanged = false;
                                                netmask__1.ischanged = false;
                                                netmask__2.ischanged = false;
                                                netmask__3.ischanged = false;
                                                netmask__4.ischanged = false;
                                                gateway__1.ischanged = false;
                                                gateway__2.ischanged = false;
                                                gateway__3.ischanged = false;
                                                gateway__4.ischanged = false;
                                                dns_1.ischanged = false;
                                                dns_2.ischanged = false;
                                                dns_3.ischanged = false;
                                                dns_4.ischanged = false;
                                                dnsserv_1.ischanged = false;
                                                dnsserv_2.ischanged = false;
                                                dnsserv_3.ischanged = false;
                                                dnsserv_4.ischanged = false;
                                                var ip_str = ip__1.text + "." + ip__2.text + "." + ip__3.text + "." + ip__4.text;
                                                var netmask_str = netmask__1.text + "." + netmask__2.text + "." + netmask__3.text + "." + netmask__4.text;
                                                var gateway_str = gateway__1.text + "." + gateway__2.text + "." + gateway__3.text + "." + gateway__4.text;
                                                var dns1_str = dns_1.text===""?"":dns_1.text + "." + dns_2.text + "." + dns_3.text + "." + dns_4.text;
                                                var dns2_str = dnsserv_1.text===""?"":dnsserv_1.text + "." + dnsserv_2.text + "." + dnsserv_3.text + "." + dnsserv_4.text;
                                                supervisor.setWifi("", ip_str, netmask_str, gateway_str,dns1_str,dns2_str);
                                            }else{
                                                supervisor.playSound('no');
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }

            Rectangle{
                width: 200
                height: 80
                radius: 50
                color: "transparent"
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 30
                anchors.left: parent.left
                anchors.leftMargin: 50
                border.width: 2
                border.color: color_green
                Text{
                    anchors.centerIn: parent
                    text: popup_wifi.setting_step == 0 ?qsTr("취소"):qsTr("이전")
                    font.pixelSize: 35
                    font.family: font_noto_r.name
                    color: color_dark_black
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        supervisor.playSound('click');
                        if(popup_wifi.setting_step === 0){
                            cancel();
                        }else{
                            popup_wifi.setting_step--;
                        }

                    }
                }
            }
            Rectangle{
                width: 200
                height: 80
                radius: 50
                enabled:{
                    if(popup_wifi.setting_step === 0){
                        if(popup_wifi.select_wifi > -1){
                            true
                        }else{
                            false
                        }
                    }else{
                        popup_wifi.connection === 2
                    }
                }
                color: enabled?color_green:color_gray
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 30
                anchors.right: parent.right
                anchors.rightMargin: 50
                Text{
                    anchors.centerIn: parent
                    text: popup_wifi.setting_step < 2 ?qsTr("다음"):qsTr("설정 완료")
                    font.pixelSize: 35
                    font.family: font_noto_r.name
                    color: "white"
                }
                MouseArea{
                    anchors.fill: parent
                    onPressed:{
                        supervisor.playSound('click');
                        parent.color = color_mid_green;
                    }
                    onReleased: {
                        parent.color = color_green;
                    }
                    onClicked: {
                        if(popup_wifi.setting_step == 0){
                            if(select_wifi>-1 && select_wifi < model_wifis.count){
                                supervisor.playSound('click');
                                select_ssid = model_wifis.get(select_wifi).ssid;
                                select_inuse = model_wifis.get(select_wifi).inuse;
                                select_security = model_wifis.get(select_wifi).security;
                                select_level = model_wifis.get(select_wifi).level;
                                supervisor.writelog("[SETTING] PopupWifi : 1. Select Wifi -> "+select_ssid);
                                if(select_inuse){
                                    popup_wifi.connection = 2;
                                    popup_wifi.setting_step = 1;
                                }else{
                                    popup_wifi.setting_step++;
                                }

                            }else{
                                supervisor.playSound('no');
                            }


                        }else if(popup_wifi.setting_step == 1){
                            if(popup_wifi.connection === 2){
                                supervisor.playSound('click');
                                supervisor.writelog("[SETTING] PopupWifi : 2. Ip Setting");
                                ip_update();
                                popup_wifi.setting_step++;
                            }else{
                                supervisor.playSound('no');
                            }
                        }else{
                            supervisor.playSound('click');
                            supervisor.writelog("[SETTING] PopupWifi : Setting Done");
                            done();
                        }
                    }
                }
            }

        }
    }

    Popup{
        id: popup_fail_con
        anchors.centerIn: parent
        width: 1280
        height: 200
        background:Rectangle{
            anchors.fill: parent
            color: "transparent"
        }
        Rectangle{
            width: parent.width
            height: parent.height
            color: color_red
            Text{
                anchors.centerIn: parent
                text: qsTr("연결에 실패했습니다\n비밀번호를 다시 확인해주세요")
                horizontalAlignment: Text.AlignHCenter
                color: "white"
                font.family: font_noto_b.name
                font.pixelSize: 50
            }
        }
        MouseArea{
            anchors.fill: parent
            onClicked:{
                popup_fail_con.close();
            }
        }

    }

    Popup_loading{
        id: popup_loading
    }
    Tool_Keyboard{
        id: keyboard
    }
    Tool_KeyPad{
        id: keypad
    }
}
