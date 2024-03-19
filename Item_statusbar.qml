import QtQuick 2.12
import QtQuick.Controls 2.12
import "."
import io.qt.Supervisor 1.0
import QtMultimedia 5.12
import QtQuick.Shapes 1.12
import QtQuick.Dialogs 1.3
import QtGraphicalEffects 1.0

Item {
    id: item_statusbar
    width: parent.width
    height: 60

    property bool debug_mode: false
    property bool show_cursor: false
    property date curDate: new Date()
    property string curTime: curDate.toLocaleTimeString()

    property bool is_con_joystick: false
    property bool is_con_server: false
    property bool is_con_robot: false
    property bool is_motor_error: false
    property bool is_local_not_ready: false
    property bool is_motor_power: false
    property bool is_emergency: false
    property bool is_motor_hot: false
    property bool robot_tx: false
    property bool robot_rx: false

    Rectangle{
        id: status_bar
        width: parent.width
        height: 60
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        color: debug_mode?color_red:"white"
        Text{
            id: textName
            width: 300
            color: color_mid_black
            horizontalAlignment: Text.AlignHCenter
            anchors.verticalCenter: parent.verticalCenter
            font.family: font_noto_r.name
            font.pixelSize: 20
            text: robot_name
            MouseArea{
                anchors.fill: parent
                onPressAndHold: {
                    click_sound.play();
                    supervisor.writelog("[USER INPUT] Screen Minimized.");
                    mainwindow.showMinimized()
                }
                onDoubleClicked: {
                    click_sound.play();
//                    popup_menu.open();
                }
            }
        }
        Text{
            anchors.right: image_clock.left
            anchors.rightMargin: 100
            horizontalAlignment: Text.AlignHCenter
            anchors.verticalCenter: parent.verticalCenter
            font.family: font_noto_r.name
            font.pixelSize: 30
            text: qsTr("디버그모드")
            color: "white"
            visible: debug_mode
            font.bold: true
            MouseArea{
                anchors.fill: parent
                onDoubleClicked: {
                    click_sound.play();
                    popup_notice.init();
                    popup_notice.main_str = qsTr("디버그 모드를 해제하시겠습니까?")
                    popup_notice.sub_str = qsTr("초기화면으로 이동되며 저장되지 않은 내용은 사라집니다")
                    popup_notice.addButton(qsTr("디버그모드 해제"))
                    popup_notice.open();
                }
            }
        }
        Text{
            anchors.left: textTime.right
            anchors.leftMargin:100
            horizontalAlignment: Text.AlignHCenter
            anchors.verticalCenter: parent.verticalCenter
            font.family: font_noto_r.name
            font.pixelSize: 30
            text: qsTr("디버그모드")
            color: "white"
            visible: debug_mode
            font.bold: true
            MouseArea{
                anchors.fill: parent
                onDoubleClicked: {
                    click_sound.play();
                    popup_notice.init();
                    popup_notice.main_str = qsTr("디버그 모드를 해제하시겠습니까?")
                    popup_notice.sub_str = qsTr("초기화면으로 이동되며 저장되지 않은 내용은 사라집니다")
                    popup_notice.addButton(qsTr("디버그모드 해제"),color_green,"white")
                    popup_notice.open();
                }
            }
        }
        Text{
            id: textTime
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            text: curTime
            color: color_mid_black
            font.family: font_noto_b.name
            font.pixelSize: 20
        }
        Image{
            id: image_clock
            source:"icon/icon_clock.png"
            anchors.right: textTime.left
            width: 40
            height: 40
            sourceSize.width: 40
            sourceSize.height: 40
            anchors.rightMargin: 5
            anchors.verticalCenter: textTime.verticalCenter

        }

        Row{
            id: rows_icon
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: 15
            spacing: 5
            Image{
                id: image_server
                visible: is_con_server
                sourceSize.width: 46
                sourceSize.height: 46
                source: "icon/icon_server_good.png"
            }
            Image{
                id: image_motor_power
                sourceSize.width: 46
                sourceSize.height: 46
                width: 46
                height: 46
                source: "icon/icon_motor_discon.png"
            }
            Image{
                id: image_emergency
                visible: false
                sourceSize.width: 46
                sourceSize.height: 46
                width: 46
                height: 46
                source: "icon/icon_emergency.png"
            }
            Image{
                id: image_motor_unlock
                visible: false
                sourceSize.width: 46
                sourceSize.height: 46
                width: 46
                height: 46
                source: "icon/icon_motor_unlock.png"
            }
            Image{
                id: image_local_error
                visible: false
                sourceSize.width: 46
                sourceSize.height: 46
                width: 46
                height: 46
                source: "icon/icon_local_error.png"
            }
            Image{
                id: image_wifi
                width: 46
                height: 46
                visible: false
                sourceSize.width: 46
                sourceSize.height: 46
                source: "icon/icon_wifi_discon.png"
            }
            Image{
                id: image_ethernet
                width: 46
                height: 46
                sourceSize.width: 46
                sourceSize.height: 46
                source: "icon/icon_ethernet_discon.png"
            }
            Image{
                id: image_volume
                width: 46
                height: 46
                sourceSize.width: 46
                sourceSize.height: 46
                source: "icon/icon_volume_3.png"
            }

            Image{
                id: image_battery
                source: "icon/icon_battery_1.png"
                sourceSize.width: 46
                sourceSize.height: 46
                anchors.verticalCenter: parent.verticalCenter
            }
        }
        MouseArea{
            anchors.fill: rows_icon
            onClicked: {
                click_sound.play();
                update_init();
                update_detail();
                popup_status_detail.open();
            }
            onPressAndHold:{
                //debug_mode
                popup_tts.open();
            }
        }
    }

    ListModel{
        id: model_details
    }

    function update_init(){
        rect_back.sound = supervisor.getSystemVolume();

    }

    function update_detail(){
        model_details.clear();


        if(supervisor.isConnectServer()){
            model_details.append({"detail":qsTr("서버에 연결되었습니다"),"detail2":"","icon":"icon/icon_server_good.png","error":false});
        }

        if(supervisor.getEthernetConnection()===2){
            if(supervisor.getIPCConnection()){
                model_details.append({"detail":qsTr("로봇과 연결되었습니다"),"detail2":supervisor.getethernetIP(),"icon":"icon/icon_ethernet_good.png","error":false});
            }else{
                model_details.append({"detail":qsTr("로봇과 연결할 수 없습니다"),"detail2":qsTr("프로그램이 실행되지 않았습니다"),"icon":"icon/icon_ethernet_no.png","error":true});
            }
        }else{
            model_details.append({"detail":qsTr("로봇과 연결할 수 없습니다"),"detail2":qsTr("이더넷연결을 확인하세요"),"icon":"icon/icon_ethernet_discon.png","error":true});
        }

        if(supervisor.getWifiConnection()===2){
            if(supervisor.getInternetConnection()===2){
                model_details.append({"detail":"SSID : "+supervisor.getCurWifiSSID(),"detail2":"IP : "+supervisor.getcurIP(),"icon":image_wifi.source.toString(),"error":false});
            }else{
                model_details.append({"detail":"SSID : "+supervisor.getCurWifiSSID(),"detail2":"IP (인터넷X) : "+supervisor.getcurIP(),"icon":image_wifi.source.toString(),"error":false});
            }
        }else{
            model_details.append({"detail":"무선인터넷이 연결되지 않았습니다","detail2":"","icon":image_wifi.source.toString(),"error":true});
        }


        if(supervisor.getPowerStatus() === 1){
            if(supervisor.getMotorStatus(0) === 1 && supervisor.getMotorStatus(1) === 1){
                if(supervisor.getMotorTemperature(0) > supervisor.getMotorWarningTemperature() || supervisor.getMotorTemperature(1) > supervisor.getMotorWarningTemperature()){
                    model_details.append({"detail":qsTr("모터전원이 정상입니다"),"detail2":"모터가 뜨겁습니다","icon":"icon/icon_motor_hot.png","error":false});
                }else{
                    model_details.append({"detail":qsTr("모터전원이 정상입니다"),"detail2":"","icon":"icon/icon_motor_good.png","error":false});
                }
            }else{
                if(supervisor.getLockStatus() === 0){
                    model_details.append({"detail":qsTr("모터락이 풀려있습니다"),"detail2":"","icon":"icon/icon_motor_unlock.png","error":true});
                }else{
                    model_details.append({"detail":qsTr("모터에러 발생"),"detail2":supervisor.getMotorStatusStr(0)+"|"+supervisor.getMotorStatusStr(1),"icon":"icon/icon_motor_unlock.png","error":true});
                }
            }
        }else{
            model_details.append({"detail":qsTr("모터전원을 꺼져있습니다"),"detail2":"","icon":"icon/icon_motor_discon.png","error":true});
        }


        if(supervisor.getLocalizationState() !== 2){
            model_details.append({"detail":qsTr("로봇 위치초기화가 필요합니다"),"detail2":"","icon":"icon/icon_local_error.png","error":true});
        }

        if(supervisor.getEmoStatus()===1){
            model_details.append({"detail":qsTr("비상스위치가 눌렸습니다"),"detail2":"","icon":"icon/icon_emergency.png","error":true});
        }

        if(supervisor.getChargeConnectStatus() === 1){
            model_details.append({"detail":qsTr("충전케이블이 연결되었습니다"),"detail2":"","icon":"icon/icon_charge.png","error":false});
        }

        if(robot_battery < 30 && supervisor.getIPCConnection()){
            model_details.append({"detail":qsTr("배터리가 부족합니다"),"detail2":Number(supervisor.getBatteryOut())+" V","icon":"icon/icon_battery_1.png","error":true});
        }

    }

    Popup{
        id: popup_status_detail
        width: 350
        height: 450
        x: parent.width - width - 5
        y: parent.height+5
        bottomPadding: 0
        topPadding: 0
        leftPadding: 0
        rightPadding: 0
        background: Rectangle{
            anchors.fill: parent
            color: "transparent"
        }

        onOpened: {
            if(model_details.count == 0){
                popup_status_detail.close();
            }else{
//                ani_popup_show.start();
            }
        }

        Rectangle{
            id: rre
            width: parent.width
            height: parent.height
            radius: 10
            color: color_mid_black
            Column{
                id: col_details
                width: parent.width
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                anchors.topMargin: 10
                spacing: 15
                Row{
                    anchors.right: parent.right
                    anchors.rightMargin: 10
                    spacing: 20
                    Image{
                        width: 30
                        height: 30
                        sourceSize.width: 30
                        sourceSize.height: 30
                        source: "icon/icon_power.png"
                        antialiasing: true
                        MouseArea{
                            anchors.fill: parent
                            onClicked:{
                                click_sound.play();
                                popup_notice.init();
                                popup_notice.main_str = qsTr("프로그램을 종료<font color=\"white\">하시겠습니까?</font>")
                                popup_notice.addButton(qsTr("재시작"))
                                popup_notice.addButton(qsTr("종 료"))
                                popup_notice.open();
                            }
                        }
                    }
                    Image{
                        width: 30
                        height: 30
                        sourceSize.width: 30
                        sourceSize.height: 30
                        source: "icon/icon_setting.png"
                        antialiasing: true
                        MouseArea{
                            anchors.fill: parent
                            onClicked:{
                                if(loader_page.item.objectName != "page_init" || loader_page.item.objectName != "page_setting"){
                                    click_sound.play();
                                    loadPage(psetting);
                                    popup_status_detail.close();
                                }else{
                                    click_sound_no.play();
                                }
                            }
                        }
                    }
                }
                Row{
                    anchors.horizontalCenter: parent.horizontalCenter
                    spacing: 25
                    Rectangle{
                        id: btn_motorlock
                        width: 55
                        height: 55
                        radius: 55
                        color: color_light_gray
                        Image{
                            id: image_motorlock
                            anchors.centerIn: parent
                            source: "icon/icon_motor_unlock.png"
                            width: 38
                            height: 38
                            sourceSize.width: 38
                            sourceSize.height: 38
                            antialiasing: true
                        }
                        MouseArea{
                            anchors.fill: parent
                            onClicked:{
                                click_sound.play();
                                if(supervisor.getLockStatus() === 1){
                                    supervisor.setMotorLock(false);
                                }else{
                                    supervisor.setMotorLock(true);
                                }
                            }
                        }
                    }
                    Rectangle{
                        id: btn_cursor
                        width: 55
                        height: 55
                        radius: 55
                        property bool view: false
                        color: view?color_green:color_light_gray
                        Image{
                            anchors.centerIn: parent
                            source: "icon/icon_cursor.png"
                            width: 38
                            height: 38
                            sourceSize.width: 38
                            sourceSize.height: 38
                            antialiasing: true
                            ColorOverlay{
                                anchors.fill: parent
                                color: "white"
                                source: parent
                                visible: btn_cursor.view
                            }
                        }
                        MouseArea{
                            anchors.fill: parent
                            onClicked:{
                                click_sound.play();
                                if(btn_cursor.view){
                                    supervisor.setCursorView(false);
                                    btn_cursor.view = false;
                                }else{
                                    supervisor.setCursorView(true);
                                    btn_cursor.view = true;
                                }
                            }
                        }
                    }
                    Rectangle{
                        id: btn_localization
                        width: 55
                        height: 55
                        radius: 55
                        color: color_light_gray
                        Image{
                            anchors.centerIn: parent
                            source: "icon/icon_init.png"
                            width: 38
                            height: 38
                            sourceSize.width: 38
                            sourceSize.height: 38
                            antialiasing: true
                        }
                        MouseArea{
                            anchors.fill: parent
                            onClicked:{
                                click_sound.play();
                                popup_notice.init();
                                popup_notice.style = "info";
                                popup_notice.main_str = qsTr("위치초기화를 다시 하시겠습니까?")
                                popup_notice.sub_str = qsTr("위치초기화 페이지로 이동합니다")
                                popup_notice.addButton(qsTr("위치초기화"),color_green,"white")
                                popup_notice.open();
                            }
                        }
                    }
                    Rectangle{
                        width: 55
                        height: 55
                        radius: 55
                        color: color_light_gray
                        Image{
                            anchors.centerIn: parent
                            source: "icon/icon_minimize.png"
                            width: 38
                            height: 38
                            sourceSize.width: 38
                            sourceSize.height: 38
                            antialiasing: true
                        }
                        MouseArea{
                            anchors.fill: parent
                            onClicked:{
                                click_sound.play();
                                supervisor.writelog("[USER INPUT] Screen Minimized.");
//                                if(debug_mode){
//                                    mainwindow.showMinimized();
//                                }else{
                                    popup_password_minimize.open();
//                                }
                            }
                        }
                    }
                }


                Rectangle{
                    id: rect_back
                    width: parent.width*0.85
                    height: 35
                    anchors.horizontalCenter: parent.horizontalCenter
                    color: color_dark_black
                    radius: 20
                    property int sound : 0
                    clip: true
                    Rectangle{
                        id: rect_sound
                        width: rect_back.width*rect_back.sound/100
                        height: 35
                        Behavior on width {
                            NumberAnimation{
                                duration: 50
                            }
                        }

                        color: color_green
                        radius: 20
                    }
                    Image{
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.leftMargin: 15
                        width: 20
                        height: 20
                        sourceSize.width: 20
                        sourceSize.height: 20
                        antialiasing: true
                        source:{
                            if(rect_back.sound>80){
                                "qrc:/icon/icon_volume_3.png"
                            }else if(rect_back.sound>40){
                                "qrc:/icon/icon_volume_2.png"
                            }else if(rect_back.sound>0){
                                "qrc:/icon/icon_volume_1.png"
                            }else if(rect_back.sound === 0){
                                "qrc:/icon/icon_volume_0.png"
                            }
                        }
                        ColorOverlay{
                            anchors.fill: parent
                            color: color_light_gray
                            source: parent
                        }
                    }

                    MouseArea{
                        anchors.fill: parent
                        onPressed: {
                            rect_back.sound = ((mouseX/width)*100).toFixed(0);
                        }
                        onReleased:{
                            supervisor.setSystemVolume(rect_back.sound);
                        }
                        onPositionChanged: {
                            if(mouseX<0){
                                rect_back.sound = 0;
                            }else if(mouseX>width){
                                rect_back.sound = 100;
                            }else{
                                rect_back.sound = ((mouseX/width)*100).toFixed(0);
                            }
                        }
                    }

                }

                Rectangle{
                    width: parent.width*0.9
                    anchors.horizontalCenter: parent.horizontalCenter
                    height: 1
                    color: color_gray
                }

                Flickable{
                    width: rre.width*0.9
                    anchors.horizontalCenter: parent.horizontalCenter
                    clip: true
                    height: 250
                    contentHeight: col_detail.height
                    Column{
                        id: col_detail
                        anchors.horizontalCenter: parent.horizontalCenter
                        spacing: 10
                        Repeater{
                            model: model_details
                            Rectangle{
                                width: rre.width*0.9
                                anchors.horizontalCenter: parent.horizontalCenter
                                height: 70
                                radius: 5
                                color: color_dark_black
                                Row{
                                    spacing: 10
                                    anchors.verticalCenter: parent.verticalCenter
                                    anchors.left: parent.left
                                    anchors.leftMargin: 10
                                    Rectangle{
                                        width: 45
                                        height: 45
                                        radius: 45
                                        color: "white"
                                        anchors.verticalCenter: parent.verticalCenter
                                        Image{
                                            source: icon
                                            width: 30
                                            height: 30
                                            sourceSize.width: 30
                                            sourceSize.height: 30
                                            antialiasing: true
                                            anchors.centerIn: parent
                                        }
                                    }

                                    Rectangle{
                                        width: rre.width*0.9-65
                                        height: 70
                                        color: "transparent"
                                        Column{
                                            anchors.centerIn: parent
                                            Text{
                                                text: detail
                                                anchors.horizontalCenter: parent.horizontalCenter
                                                font.family: font_noto_r.name
                                                font.pixelSize: 18
                                                color: error===true?"red":"green"
                                            }
                                            Text{
                                                text: detail2
                                                visible: text !== ""
                                                anchors.horizontalCenter: parent.horizontalCenter
                                                font.family: font_noto_r.name
                                                font.pixelSize: 15
                                                color: color_gray
                                            }
                                        }
                                    }

                                }
                            }
                        }
                    }
                }
            }
        }
    }



    Timer{
        id: timer_status_update
        interval: 100
        repeat: true
        running: true
        onTriggered: {
            debug_mode = supervisor.isDebugMode();
            robot_battery = supervisor.getBattery();
            curTime = Qt.formatTime(new Date(), "hh:mm");

            if(supervisor.getEthernetConnection()===1){
                image_ethernet.source = "qrc:/icon/icon_ethernet_connecting.png";
            }else if(supervisor.getEthernetConnection()===2){
                if(supervisor.getIPCConnection()){
                    image_ethernet.source = "qrc:/icon/icon_ethernet_good.png";
                }else{
                    image_ethernet.source = "qrc:/icon/icon_ethernet_no.png";
                }
            }else{
                image_ethernet.source = "qrc:/icon/icon_ethernet_discon.png";
            }

            if(supervisor.getLockStatus() === 1){
                image_motorlock.source = "qrc:/icon/icon_motor_locked.png"
            }else{
                image_motorlock.source = "qrc:/icon/icon_motor_unlock.png"
            }

            if(supervisor.getWifiConnection()===1){
                image_wifi.visible = true;
                image_wifi.source = "qrc:/icon/icon_wifi_connecting.png";
            }else if(supervisor.getWifiConnection()===2){
                image_wifi.visible = true;
                if(supervisor.getInternetConnection()===2){
                    if(supervisor.getWifiLevel() === 4){
                        image_wifi.source = "qrc:/icon/icon_wifi_4.png";
                    }else if(supervisor.getWifiLevel() === 3){
                        image_wifi.source = "qrc:/icon/icon_wifi_3.png";
                    }else if(supervisor.getWifiLevel() === 2){
                        image_wifi.source = "qrc:/icon/icon_wifi_2.png";
                    }else{
                        image_wifi.source = "qrc:/icon/icon_wifi_1.png";
                    }
                }else{
                    if(supervisor.getWifiLevel() === 4){
                        image_wifi.source = "qrc:/icon/icon_wifibad_4.png";
                    }else if(supervisor.getWifiLevel() === 3){
                        image_wifi.source = "qrc:/icon/icon_wifibad_3.png";
                    }else if(supervisor.getWifiLevel() === 2){
                        image_wifi.source = "qrc:/icon/icon_wifibad_2.png";
                    }else{
                        image_wifi.source = "qrc:/icon/icon_wifibad_1.png";
                    }
                }
            }else{
                image_wifi.visible = false;
            }

            if(supervisor.getSystemVolume()>80){
                image_volume.source = "qrc:/icon/icon_volume_3.png";
            }else if(supervisor.getSystemVolume()>40){
                image_volume.source = "qrc:/icon/icon_volume_2.png";
            }else if(supervisor.getSystemVolume()>0){
                image_volume.source = "qrc:/icon/icon_volume_1.png";
            }else if(supervisor.getSystemVolume() === 0){
                image_volume.source = "qrc:/icon/icon_volume_0.png";
            }

            if(supervisor.getPowerStatus() === 1){
                if(supervisor.getMotorStatus(0) === 1 && supervisor.getMotorStatus(1) === 1){
                    if(supervisor.getMotorTemperature(0) > supervisor.getMotorWarningTemperature() || supervisor.getMotorTemperature(1) > supervisor.getMotorWarningTemperature()){
                        image_motor_power.source = "icon/icon_motor_hot.png"
                    }else{
                        image_motor_power.source = "icon/icon_motor_good.png"
                    }
                }else{
                    //error
                    image_motor_power.source = "icon/icon_motor_error.png"
                }
            }else{
                image_motor_power.source = "icon/icon_motor_discon.png"
            }

            if(supervisor.getChargeConnectStatus()===1){
                image_battery.source = "icon/icon_battery_charging.png"
            }else if(robot_battery > 90){
                image_battery.source = "icon/icon_battery_4.png"
            }else if(robot_battery > 60){
                image_battery.source = "icon/icon_battery_3.png"
            }else if(robot_battery > 30){
                image_battery.source = "icon/icon_battery_2.png"
            }else{
                image_battery.source = "icon/icon_battery_1.png"
            }

            if(supervisor.getLockStatus() === 1){
                image_motor_unlock.visible = false;
            }else{
                image_motor_unlock.visible = true;
            }

            if(supervisor.getEmoStatus() === 1){
                image_emergency.visible = true;
            }else{
                image_emergency.visible = false;
            }

            if(supervisor.getLocalizationState() === 2){
                image_local_error.visible = false;
            }else{
                image_local_error.visible = true;
            }

            update_detail();
        }
    }
}
