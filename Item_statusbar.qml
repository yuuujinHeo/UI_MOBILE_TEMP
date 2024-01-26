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

    Component.onCompleted: {
//        statusbar.visible = true;
    }
    onVisibleChanged: {
        print("statusbar visible ",visible);
    }

    Rectangle{
        id: status_bar
        width: parent.width
        height: 60
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        color: testMode?"red":"white"
        Text{
            id: textName
            width: 300
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
                    popup_menu.open();
                }
            }
        }
//        Timer{
//            running: true
//            interval: 200
//            repeat: true
//            onTriggered: {
//                temp_0.text = supervisor.getMotorTemperature(0).toFixed(0)+"("+supervisor.getMotorInsideTemperature(0).toFixed(0)+")";
//                temp_1.text = supervisor.getMotorTemperature(1).toFixed(0)+"("+supervisor.getMotorInsideTemperature(1).toFixed(0)+")";
//            }
//        }
//        Row{
//            anchors.verticalCenter: parent.verticalCenter
//            anchors.left: textName.right
//            spacing: 20
//            Text{
//                id: temp_0
//                width: 100
//                horizontalAlignment: Text.AlignHCenter
//                font.family: font_noto_r.name
//                font.pixelSize: 20
//                text: "-"
//            }
//            Text{
//                id: temp_1
//                width: 100
//                horizontalAlignment: Text.AlignHCenter
//                font.family: font_noto_r.name
//                font.pixelSize: 20
//                text: "-"
//            }
//        }

        Text{
            id: textTime
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            text: curTime
            font.family: font_noto_b.name
            font.pixelSize: 20
        }
        Image{
            id: image_clock
            source:"icon/clock.png"
            anchors.right: textTime.left
            anchors.rightMargin: 5
            anchors.verticalCenter: textTime.verticalCenter
        }

        Row{
            id: rows_icon
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: 30
            spacing: 5
            Image{
                id: image_joystick
                visible: is_con_joystick
                sourceSize.width: 46
                sourceSize.height: 42
                source: "icon/icon_joy_connect.png"
            }
            Image{
                id: image_server
                visible: is_con_server
                sourceSize.width: 46
                sourceSize.height: 42
                source: "icon/icon_server_connect.png"
            }
            Image{
                id: image_motor_power
                sourceSize.width: 46
                sourceSize.height: 42
                width: 46
                height: 42
                source: is_motor_power?"icon/motor_power_on.png":"icon/motor_power_off.png"
            }
            Image{
                id: image_motor_temperror
                visible: is_motor_hot
                sourceSize.width: 46
                sourceSize.height: 42
                width: 46
                height: 42
                source: "icon/icon_motor_hot.png"
            }
            Image{
                id: image_emergency
                visible: is_emergency
                sourceSize.width: 46
                sourceSize.height: 42
                width: 46
                height: 42
                source: "icon/icon_emergency.png"
            }
            Image{
                id: image_motor_error
                visible: is_motor_error
                sourceSize.width: 46
                sourceSize.height: 42
                width: 46
                height: 42
                source: "icon/icon_motor_error.png"
            }
            Image{
                id: image_local_error
                visible: is_local_not_ready
                sourceSize.width: 46
                sourceSize.height: 42
                width: 46
                height: 42
                source: "icon/icon_local_error.png"
            }
            Image{
                id: image_robot_discon
                visible: !is_con_robot
                width: 46
                height: 42
                sourceSize.width: 46
                sourceSize.height: 42
                source: "icon/icon_lcm_discon.png"
            }
            Rectangle{
                color: "transparent"
                width: 46
                height: 42
                visible: is_con_robot
                anchors.verticalCenter: parent.verticalCenter
                Row{
                    id: image_robot_con
                    anchors.centerIn: parent
                    Image{
                        id: image_tx
                        width: 15
                        height: 28
                        mipmap: true
                        antialiasing: true
                        sourceSize.width: 15
                        sourceSize.height: 28
                        source: robot_tx?"icon/data_green.png":"icon/data_gray.png"
                    }
                    Image{
                        id: image_rx
                        mipmap: true
                        antialiasing: true
                        width: 15
                        height: 28
                        sourceSize.width: 15
                        sourceSize.height: 28
                        anchors.top: image_tx.top
                        anchors.topMargin: 1
                        rotation: 180
                        source: robot_rx?"icon/data_green.png":"icon/data_gray.png"
                    }
                }
            }


            Image{
                id: image_battery
                source: {
                    if(robot_battery > 90){
                        "icon/bat_full.png"
                    }else if(robot_battery > 60){
                        "icon/bat_3.png"
                    }else if(robot_battery > 30){
                        "icon/bat_2.png"
                    }else{
                        "icon/bat_1.png"
                    }
                }
                sourceSize.width: 46
                sourceSize.height: 42
                anchors.verticalCenter: parent.verticalCenter
            }

            Text{
                id: textBattery
                anchors.verticalCenter: parent.verticalCenter
                color: "#7e7e7e"
                font.family: font_noto_r.name
                font.pixelSize: 20
                text: robot_battery.toFixed(0)+' %'
            }

        }
        MouseArea{
            anchors.fill: rows_icon
            onClicked: {
                click_sound.play();
                update_detail();
                popup_status_detail.open();
            }
            onPressAndHold:{
                //debug_mode
                popup_tts.open();
            }
        }
    }

    Popup_test_tts{
        id: popup_tts
    }


    Popup{
        id: popup_terminate
        width: 1280
        height: 800
        background: Rectangle{
            anchors.fill: parent
            color: color_dark_black
            opacity: 0.9
        }
        Column{
            anchors.centerIn: parent
            spacing: 40
            Image{
                source:"image/robot_head_sleep.png"
                scale: 0.8
                anchors.horizontalCenter: parent.horizontalCenter
            }
            Text{
                id: text_quest
                anchors.horizontalCenter: parent.horizontalCenter
                font.family: font_noto_b.name
                font.pixelSize: 50
                color: "#12d27c"
                text: qsTr("프로그램을 종료<font color=\"white\">하시겠습니까?</font>")
            }
            Row{
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: 50
                Rectangle{
                    width: 250
                    height: 90
                    radius: 20
                    color: "#d0d0d0"
                    Row{
                        anchors.verticalCenter: parent.verticalCenter
                        Rectangle{
                            width: 90
                            height: width
                            color: "transparent"
                            Image{
                                source: "icon/btn_no.png"
                                width: 50
                                height: 50
                                anchors.centerIn : parent
                            }
                        }
                        Rectangle{
                            width: 250 - 90
                            height: 90
                            color: "transparent"
                            Text{
                                text:qsTr("취소")
                                font.family: font_noto_b.name
                                font.pixelSize: 30
                                color:"#282828"
                                anchors.centerIn : parent
                            }
                        }
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            click_sound.play();
                            popup_terminate.close();
                            popup_menu.close();
                        }
                    }
                }
                Rectangle{
                    width: 250
                    height: 90
                    radius: 20
                    color: "#d0d0d0"
                    Rectangle{
                        color:"white"
                        width: 240
                        height: 80
                        radius: 19
                        anchors.centerIn: parent
                    }
                    Row{
                        anchors.verticalCenter: parent.verticalCenter
                        Rectangle{
                            width: 90
                            height: width
                            color: "transparent"
                            Image{
                                source: "icon/btn_reset.png"
                                width: 50
                                height: 50
                                anchors.centerIn : parent
                            }
                        }
                        Rectangle{
                            width: 250 - 90
                            height: 90
                            color: "transparent"
                            Text{
                                text:qsTr("다시시작")
                                font.family: font_noto_b.name
                                font.pixelSize: 30
                                color:"#282828"
                                anchors.centerIn : parent
                            }
                        }
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            click_sound.play();
                            supervisor.writelog("[USER INPUT] STATUS BAR : PROGRAM RESTART")
                            supervisor.programRestart();
                        }
                    }
                }
                Rectangle{
                    width: 250
                    height: 90
                    radius: 20
                    color: "#d0d0d0"
                    Rectangle{
                        color:"white"
                        width: 240
                        height: 80
                        radius: 19
                        anchors.centerIn: parent
                    }
                    Row{
                        anchors.verticalCenter: parent.verticalCenter
                        Rectangle{
                            width: 90
                            height: width
                            color: "transparent"
                            Image{
                                source: "icon/btn_yes.png"
                                width: 50
                                height: 50
                                anchors.centerIn : parent
                            }
                        }
                        Rectangle{
                            width: 250 - 90
                            height: 90
                            color: "transparent"
                            Text{
                                text:qsTr("종료")
                                font.family: font_noto_b.name
                                font.pixelSize: 30
                                color:"#282828"
                                anchors.centerIn : parent
                            }
                        }
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            click_sound.play();
                            supervisor.writelog("[USER INPUT] STATUS BAR : PROGRAM EXIT")
                            supervisor.programExit();
                        }
                    }
                }
            }
        }
    }


    Popup{
        id: popup_menu
        width: 280
        height: 100
        bottomPadding: 0
        topPadding: 0
        leftPadding: 0
        rightPadding: 0
        x: textName.x + textName.width/2 - width/2
        y: parent.height
        z: -1
        background: Rectangle{
            anchors.fill: parent
            color: "transparent"
        }

        Rectangle{
            id: rree
            width: parent.width
            height: parent.height
            radius: 25
            color: "white"

            Rectangle{
                width: parent.width
                height: rree.radius
            }
            Row{
                anchors.centerIn: parent
                spacing: 15
                Rectangle{
                    id: btn_cursor
                    width: 78
                    height: 78
                    radius: width
                    color: color_navy
                    Column{
                        anchors.centerIn: parent
                        Image{
                            id: image_cursor
                            source:"icon/cursor.png"
                            width: 30
                            height: 30
                            anchors.horizontalCenter: parent.horizontalCenter
                            ColorOverlay{
                                source: parent
                                anchors.fill: parent
                                color: show_cursor?color_green:"white"
                            }
                        }
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            click_sound.play();
                            if(show_cursor){
                                supervisor.writelog("[USER INPUT] STATUS BAR : CURSOR UNSHOW");
                                supervisor.setCursorView(false);
                                show_cursor = false;
                            }else{
                                supervisor.writelog("[USER INPUT] STATUS BAR : CURSOR SHOW");
                                supervisor.setCursorView(true);
                                show_cursor = true;

                            }
                        }
                    }
                }
                Rectangle{
                    id: btn_minimize
                    width: 78
                    height: 78
                    radius: width
                    color: color_navy
                    Column{
                        anchors.centerIn: parent
                        Image{
                            id: image_charge
                            source:"icon/btn_minimize.png"
                            anchors.horizontalCenter: parent.horizontalCenter
                            ColorOverlay{
                                source: parent
                                anchors.fill: parent
                                color: "white"
                            }
                        }
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            click_sound.play();
                            supervisor.writelog("[USER INPUT] Screen Minimized.");
                            mainwindow.showMinimized();
                        }
                    }
                }
                Rectangle{
                    width: 78
                    height: 78
                    radius: width
                    color: color_navy
                    Column{
                        anchors.centerIn: parent
                        Image{
                            id: image_wait
                            source:"icon/icon_power.png"
                            anchors.horizontalCenter: parent.horizontalCenter
                            ColorOverlay{
                                source: parent
                                anchors.fill: parent
                                color: "white"
                            }
                        }
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            click_sound.play();
                            popup_terminate.open();
                        }
                    }
                }
            }
        }

        DropShadow{
            anchors.fill: parent
            radius: 10
            visible: false
            color: color_gray
            source: rree
        }
        Rectangle{
            width: parent.width+20
            x: -10
            y: -10
            height: 10
        }
    }

    SequentialAnimation{
        id: ani_popup_show
        onStarted: {
            col_details.opacity = 0;
        }
        NumberAnimation{target: popup_status_detail; property: "height"; from: 0; to: model_details.count * 40; duration: 300; easing.type: Easing.OutBack}
        NumberAnimation{target: col_details; property: "opacity"; from: 0; to: 1; duration: 100; easing.type: Easing.OutBack}
    }

    ListModel{
        id: model_details
    }

    function update_detail(){
        model_details.clear();
        if(is_con_joystick){
            model_details.append({"detail":qsTr("조이스틱이 연결되었습니다"),"icon":"icon/icon_joy_connect.png","error":false});
        }
        if(is_con_server){
            model_details.append({"detail":qsTr("서버에 연결되었습니다"),"icon":"icon/icon_server_connect.png","error":false});
        }
        if(!is_con_robot){
            model_details.append({"detail":qsTr("로봇과 연결되지 않았습니다"),"icon":"icon/icon_lcm_discon.png","error":true});
        }
        if(is_motor_error){
            model_details.append({"detail":qsTr("모터락이 풀려있습니다"),"icon":"icon/icon_motor_error.png","error":true});
        }
        if(is_local_not_ready){
            model_details.append({"detail":qsTr("로봇 위치 초기화가 필요합니다"),"icon":"icon/icon_local_error.png","error":true});
        }
        if(is_motor_power){
            model_details.append({"detail":qsTr("모터전원이 정상입니다"),"icon":"icon/motor_power_on.png","error":false});
        }else{
            model_details.append({"detail":qsTr("모터전원을 켜주세요"),"icon":"icon/motor_power_off.png","error":true});
        }

        if(is_emergency){
            model_details.append({"detail":qsTr("비상스위치가 눌렸습니다"),"icon":"icon/icon_emergency.png","error":true});
        }
        if(is_motor_hot){
            model_details.append({"detail":qsTr("모터가 뜨겁습니다"),"icon":"icon/icon_lcm_discon.png","error":true});
        }
        if(robot_battery < 30 && is_con_robot){
            model_details.append({"detail":qsTr("배터리가 부족합니다"),"icon":"icon/bat_1.png","error":true});
        }
    }

    Popup{
        id: popup_status_detail
        width: 300
        height: 0
        x: parent.width - width
        y: parent.height
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
                ani_popup_show.start();
            }
        }

        Rectangle{
            id: rre
            width: parent.width
            height: parent.height
            radius: 25
            color: "white"
            Rectangle{
                width: parent.width
                height: rre.radius
            }
            Column{
                id: col_details
                anchors.centerIn: parent
                spacing: 10
                Repeater{
                    model: model_details
                    Row{
                        spacing: 10
                        Image{
                            source: icon
                            width: 25
                            height: 25
                            anchors.verticalCenter: parent.verticalCenter
                        }
                        Text{
                            text: detail
                            anchors.verticalCenter: parent.verticalCenter
                            font.family: font_noto_r.name
                            font.pixelSize: 15
                            color: error===true?"red":"green"
                        }
                    }
                }
            }
        }

        DropShadow{
            anchors.fill: parent
            radius: 10
            color: color_gray
            visible: false
            source: rre
        }
        Rectangle{
            width: parent.width+20
            x: -10
            y: -10
            height: 10
        }
    }

    Timer{
        id: timer_status_update
        interval: 100
        repeat: true
        running: true
        onTriggered: {
            robot_battery = supervisor.getBattery();
            curTime = Qt.formatTime(new Date(), "hh:mm");

            is_con_robot = supervisor.getIPCConnection();
            robot_rx = supervisor.getIPCRX();
            robot_tx = supervisor.getIPCTX();
            is_con_server = supervisor.isConnectServer();

            is_motor_power = supervisor.getPowerStatus();
            is_emergency = supervisor.getEmoStatus();

            if(is_motor_power && !is_emergency){
                if(supervisor.getMotorTemperature(0) > supervisor.getMotorWarningTemperature()){
                    is_motor_hot = true;
                }else if(supervisor.getMotorTemperature(0) > supervisor.getMotorWarningTemperature()){
                    is_motor_hot = true;
                }else{
                    is_motor_hot = false;
                }
                if(supervisor.getMotorState() === 0){
                    is_motor_error = true;
                }else{
                    is_motor_error = false;
                }
            }else{
                is_motor_hot = false;
                is_motor_error = false;
            }

            if(supervisor.getLocalizationState() === 0 || supervisor.getLocalizationState() === 3){
                is_local_not_ready = true;
            }else{
                is_local_not_ready = false;
            }
        }

    }
}
