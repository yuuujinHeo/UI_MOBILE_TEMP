import QtQuick 2.12
import QtQuick.Shapes 1.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.2
import Qt.labs.platform 1.0 as Platform
import QtQuick.Shapes 1.12
import QtGraphicalEffects 1.0
import QtMultimedia 5.12
import "."
import io.qt.Supervisor 1.0

Item {
    id: page_movefail
    objectName: "page_movefail"
    width: 1280
    height: 800
    property bool need_emo: false
    property bool joystick_connection: false
    property var joy_axis_left_ud: 0
    property var joy_axis_right_rl: 0

    function setNotice(num){
        notice_num = num;
    }

    //0: no path /1: local fail /2: emergency /3: user stop /4: motor error
    property int notice_num: 0
    onNotice_numChanged: {
        if(notice_num === 0){
            text.text = "목적지로 이동하는데 실패하였습니다\로봇을 수동으로 이동시켜주세요"
        }else if(notice_num === 1){
            text.text = "로봇의 초기화가 필요합니다\n위치초기화를 다시 수행해주세요"
        }else if(notice_num === 2){
            text.text = "비상스위치가 눌렸습니다\n로봇을 수동으로 이동시켜주세요"
        }else if(notice_num === 3){
            text.text = "사용자에 의해 정지되었습니다"
        }else if(notice_num === 4){
            text.text = "목적지로 이동하는데 실패하였습니다\n로봇을 수동으로 이동시켜주세요"
        }
    }

    property bool select_localmode: false
    onSelect_localmodeChanged: {
        map.init();
        if(select_localmode){
            map.setViewer("localization");
        }else{
            map.setViewer("current");
        }
        map.setfullscreen();
    }

    Component.onCompleted: {
        init();
        map.enabled = true;
        supervisor.setMotorLock(false);
    }
    Component.onDestruction: {
        map.enabled = false;
        supervisor.setMotorLock(true);
    }

    function init(){
        supervisor.writelog("[QML] MOVEFAIL PAGE init")
        notice_num = 0;
        statusbar.visible = true;
        popup_notice.open();
        map.init();
        map.setViewer("current");
        map.setfullscreen();
    }

    Rectangle{
        anchors.fill: parent
        color:"#282828"
    }
    Rectangle{
        id: rect_state
        height: parent.height
        width: parent.width - rect_menu1.width - map.width
        anchors.top: parent.top
        anchors.topMargin: statusbar.height
        color: color_dark_navy
        Column{
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 50
            spacing: 30
            Rectangle{
                id: btn_reset
                width: 90
                height: 80
                radius: 5
                enabled: false
                color: enabled?"white":color_gray
                Column{
                    anchors.centerIn: parent
                    spacing: 5
                    Image{
                        source: "icon/icon_run.png"
                        sourceSize.width: 40
                        sourceSize.height: 40
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                    Text{
                        text: "다시 시작"
                        color:btn_reset.enabled?"black":"white"
                        font.family: font_noto_r.name
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                }
                DropShadow{
                    anchors.fill: parent
                    radius: 5
                    color: color_navy
                    source: parent
                    visible:btn_reset.enabled?true:false
                    z: -1
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        supervisor.writelog("[USER INPUT] MOVEFAIL PAGE : RESTART")
                        supervisor.moveStop();
                    }
                }
            }
            Rectangle{
                width: 90
                height: 80
                radius: 5
                border.width: select_localmode?3:0
                border.color: color_green
                Column{
                    anchors.centerIn: parent
                    spacing: 5
                    Image{
                        source: "image/image_localization.png"
                        sourceSize.width: 40
                        sourceSize.height: 40
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                    Text{
                        font.pixelSize: 15
                        text: "Localization"
                        font.family: font_noto_r.name
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                }
                DropShadow{
                    anchors.fill: parent
                    radius: 3
                    color: color_navy
                    source: parent
                    z: -1
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        if(select_localmode){
                            supervisor.writelog("[USER INPUT] MOVEFAIL PAGE : LOCALIZATION STOP")
                            select_localmode = false;
                        }else{
                            supervisor.writelog("[USER INPUT] MOVEFAIL PAGE : LOCALIZATION START")
                            select_localmode = true;
                        }
                    }
                }
            }
            Rectangle{
                width: 90
                height: 80
                radius: 5
                Column{
                    anchors.centerIn: parent
                    spacing: 5
                    Image{
                        source: "icon/icon_power.png"
                        sourceSize.width: 40
                        sourceSize.height: 40
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                    Text{
                        text: "SLAM 재부팅"
                        font.family: font_noto_r.name
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                }
                DropShadow{
                    anchors.fill: parent
                    z: -1
                    radius: 5
                    color: color_navy
                    source: parent
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        supervisor.writelog("[USER INPUT] MOVEFAIL PAGE : RESTART SLAM")
                        supervisor.restartSLAM();
                    }
                }
            }
        }
    }
    Rectangle{
        id: rect_menu1
        width: 400
        height: parent.height - statusbar.height
        anchors.left: rect_state.right
        anchors.topMargin: statusbar.height
        anchors.top: parent.top
        color: "#f4f4f4"
        visible: select_localmode?false:true
        Column{
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            spacing: 30
            Rectangle{
                width: rect_menu1.width
                height: 80
                color: color_dark_navy
                Text{
                    id: text_obs
                    anchors.centerIn : parent
                    font.family: font_noto_b.name
                    font.pixelSize: 30
                    color: "white"
                    text:"현재 상태"
                }
            }
            Column{
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: 10
                Rectangle{
                    id: state_emo
                    width: 300
                    height: 70
                    radius: 20
                    color: "transparent"
                    enabled: supervisor.getEmoStatus()
                    visible: enabled
                    border.color:color_red
                    border.width: 2
                    Row{
                        spacing: 20
                        anchors.centerIn: parent
                        Image{
                            source: "icon/image_emergency.png"
                            anchors.verticalCenter: parent.verticalCenter
                            Component.onCompleted: {
                                if(sourceSize.width > 40)
                                    sourceSize.width = 40

                                if(sourceSize.height > 40)
                                    sourceSize.height = 40
                            }
                            ColorOverlay{
                                id: emo_light
                                anchors.fill: parent
                                source: parent
                                color: color_red
                            }
                        }
                        Text{
                            font.family: font_noto_r.name
                            font.pixelSize: 25
                            color: color_red
                            text: "비상스위치 눌림"
                            anchors.verticalCenter: parent.verticalCenter
                            horizontalAlignment: Text.AlignHCenter
                        }
                    }
                }

                Rectangle{
                    id: state_charging
                    width: 300
                    height: 70
                    radius: 20
                    color: "transparent"
                    enabled: supervisor.getChargeStatus()
                    visible: enabled
                    border.color:color_red
                    border.width: 2
                    Row{
                        spacing: 20
                        anchors.centerIn: parent
                        Image{
                            source: "icon/icon_charge_2.png"
                            anchors.verticalCenter: parent.verticalCenter
                            Component.onCompleted: {
                                if(sourceSize.width > 40)
                                    sourceSize.width = 40

                                if(sourceSize.height > 40)
                                    sourceSize.height = 40
                            }
                            ColorOverlay{
                                anchors.fill: parent
                                source: parent
                                color: color_red
                            }
                        }
                        Text{
                            font.family: font_noto_r.name
                            font.pixelSize: 25
                            color: color_red
                            text: "충전 중"
                            anchors.verticalCenter: parent.verticalCenter
                            horizontalAlignment: Text.AlignHCenter
                        }
                    }
                }

                Rectangle{
                    id: state_localization
                    width: 300
                    height: 70
                    radius: 20
                    color: "transparent"
                    enabled: supervisor.getChargeStatus()
                    border.color:enabled?color_red:color_green
                    border.width: 3
                    Row{
                        spacing: 20
                        anchors.centerIn: parent
                        Image{
                            source: "icon/icon_lidar.png"
                            anchors.verticalCenter: parent.verticalCenter
                            width: 40
                            height: 40
                            Component.onCompleted: {
                                if(sourceSize.width > 50)
                                    sourceSize.width = 50

                                if(sourceSize.height > 50)
                                    sourceSize.height = 50
                            }
                            ColorOverlay{
                                anchors.fill: parent
                                source: parent
                                color: state_localization.enabled?color_red:color_green
                            }
                        }
                        Text{
                            font.family: font_noto_r.name
                            font.pixelSize: 25
                            color: state_localization.enabled?color_red:color_green
                            text: state_localization.enabled?"위치를 알 수 없음":"위치추정중"
                            anchors.verticalCenter: parent.verticalCenter
                            horizontalAlignment: Text.AlignHCenter
                        }
                    }
                }

                Rectangle{
                    id: state_motor_1
                    width: 300
                    height: 70
                    radius: 20
                    color: "transparent"
                    enabled: false
                    border.color:enabled?color_red:color_green
                    border.width: 3
                    Row{
                        spacing: 20
                        anchors.centerIn: parent
                        Image{
                            source: state_motor_1.enabled?"icon/icon_error.png":"icon/icon_charge_2.png"
                            anchors.verticalCenter: parent.verticalCenter
                            Component.onCompleted: {
                                if(sourceSize.width > 40)
                                    sourceSize.width = 40

                                if(sourceSize.height > 40)
                                    sourceSize.height = 40
                            }
                            ColorOverlay{
                                anchors.fill: parent
                                source: parent
                                color: color_green
                                visible: !state_motor_1.enabled
                            }
                        }
                        Text{
                            font.family: font_noto_r.name
                            font.pixelSize: 25
                            color: state_motor_1.enabled?color_red:color_green
                            text: state_motor_1.enabled?"모터 1 에러":"모터 1 정상"
                            anchors.verticalCenter: parent.verticalCenter
                            horizontalAlignment: Text.AlignHCenter
                        }
                    }
                }
                Rectangle{
                    id: state_motor_2
                    width: 300
                    height: 70
                    radius: 20
                    color: "transparent"
                    enabled: false
                    border.color:enabled?color_red:color_green
                    border.width: 3
                    Row{
                        spacing: 20
                        anchors.centerIn: parent
                        Image{
                            source: state_motor_2.enabled?"icon/icon_error.png":"icon/icon_charge_2.png"
                            anchors.verticalCenter: parent.verticalCenter
                            Component.onCompleted: {
                                if(sourceSize.width > 40)
                                    sourceSize.width = 40

                                if(sourceSize.height > 40)
                                    sourceSize.height = 40
                            }
                            ColorOverlay{
                                anchors.fill: parent
                                source: parent
                                color: color_green
                                visible: !state_motor_2.enabled
                            }
                        }
                        Text{
                            font.family: font_noto_r.name
                            font.pixelSize: 25
                            color: state_motor_2.enabled?color_red:color_green
                            text: state_motor_2.enabled?"모터 2 에러":"모터 2 정상"
                            anchors.verticalCenter: parent.verticalCenter
                            horizontalAlignment: Text.AlignHCenter
                        }
                    }
                }

            }
        }

        Column{
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            Rectangle{
                width: 400
                height: 60
                color: color_navy
                Row{
                    Rectangle{
                        color: "transparent"
                        width: 100
                        height: 60
                        Text{
                            anchors.centerIn: parent
                            text: "모터\n1"
                            horizontalAlignment: Text.AlignHCenter
                            color: "white"
                            font.family: font_noto_r.name
                        }
                    }
                    Column{
                        Rectangle{
                            color: "transparent"
                            width: 300
                            height: 30
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                text: "온도"
                                horizontalAlignment: Text.AlignHCenter
                                color: "white"
                                font.family: font_noto_r.name
                            }
                            Text{
                                id: text_motor_temp1
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.right: parent.right
                                anchors.rightMargin: 100
                                text: "0"
                                color: "white"
                                font.family: font_noto_r.name
                            }
                        }
                        Rectangle{
                            height: 1
                            width: 300
                            color: "white"
                        }
                        Rectangle{
                            color: "transparent"
                            width: 300
                            height: 30
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                text: "상태"
                                color: "white"
                                font.family: font_noto_r.name
                            }
                            Text{
                                id: text_motor_stat1
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.right: parent.right
                                anchors.rightMargin: 100
                                text: "이상 없음"
                                color: "white"
                                font.family: font_noto_r.name
                            }
                        }
                    }
                }
            }
            Rectangle{
                height: 1
                width: 400
                color: "white"
            }
            Rectangle{
                width: 400
                height: 60
                color: color_navy
                Row{
                    Rectangle{
                        color: "transparent"
                        width: 100
                        height: 60
                        Text{
                            anchors.centerIn: parent
                            text: "모터\n2"
                            horizontalAlignment: Text.AlignHCenter
                            color: "white"
                            font.family: font_noto_r.name
                        }
                    }
                    Column{
                        Rectangle{
                            color: "transparent"
                            width: 300
                            height: 30
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                text: "온도"
                                horizontalAlignment: Text.AlignHCenter
                                color: "white"
                                font.family: font_noto_r.name
                            }
                            Text{
                                id: text_motor_temp2
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.right: parent.right
                                anchors.rightMargin: 100
                                text: "0"
                                color: "white"
                                font.family: font_noto_r.name
                            }
                        }
                        Rectangle{
                            height: 1
                            width: 300
                            color: "white"
                        }
                        Rectangle{
                            color: "transparent"
                            width: 300
                            height: 30
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                text: "상태"
                                color: "white"
                                font.family: font_noto_r.name
                            }
                            Text{
                                id: text_motor_stat2
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.right: parent.right
                                anchors.rightMargin: 100
                                text: "이상 없음"
                                color: "white"
                                font.family: font_noto_r.name
                            }
                        }
                    }
                }
            }
            Rectangle{
                height: 1
                width: 400
                color: "white"
            }

            Rectangle{
                width: 400
                height: 100
                color: color_navy
                Row{
                    Rectangle{
                        id: bat_in
                        width: 80
                        height: 100
                        color: color_navy
                        Column{
                            Rectangle{
                                width: 60
                                height: 50
                                color: "transparent"
                                Text{
                                    font.family: font_noto_r.name
                                    font.pixelSize: 12
                                    text: "전압\n(IN)"
                                    color: "white"
                                    anchors.centerIn: parent
                                    horizontalAlignment: Text.AlignHCenter
                                }
                            }
                            Rectangle{
                                width: 60
                                height: 50
                                color: "transparent"
                                Text{
                                    id: text_battery_in
                                    font.pixelSize: 12
                                    text: "0V"
                                    anchors.centerIn: parent
                                    color: "white"
                                    horizontalAlignment: Text.AlignHCenter
                                }
                            }
                        }
                    }
                    Rectangle{
                        id: bat_out
                        width: 80
                        height: 100
                        color: color_navy
                        Column{
                            Rectangle{
                                width: 60
                                height: 50
                                color: "transparent"
                                Text{
                                    font.family: font_noto_r.name
                                    font.pixelSize: 12
                                    text: "배터리\n(OUT)"
                                    color: "white"
                                    anchors.centerIn: parent
                                    horizontalAlignment: Text.AlignHCenter
                                }
                            }
                            Rectangle{
                                width: 60
                                height: 50
                                color: "transparent"
                                Text{
                                    id: text_battery_out
                                    font.pixelSize: 12
                                    text: "0V"
                                    color: "white"
                                    anchors.centerIn: parent
                                    horizontalAlignment: Text.AlignHCenter
                                }
                            }
                        }
                    }
                    Rectangle{
                        id: current
                        width: 80
                        height: 100
                        color: color_navy
                        Column{
                            Rectangle{
                                width: 60
                                height: 50
                                color: "transparent"
                                Text{
                                    font.family: font_noto_r.name
                                    font.pixelSize: 12
                                    text: "전류"
                                    color: "white"
                                    anchors.centerIn: parent
                                    horizontalAlignment: Text.AlignHCenter
                                }
                            }
                            Rectangle{
                                width: 60
                                height: 50
                                color: "transparent"
                                Text{
                                    id: text_current
                                    font.pixelSize: 12
                                    text: "0A"
                                    anchors.centerIn: parent
                                    color: "white"
                                    horizontalAlignment: Text.AlignHCenter
                                }
                            }
                        }
                    }
                    Rectangle{
                        id: power
                        width: 80
                        height: 100
                        color: color_navy
                        Column{
                            Rectangle{
                                width: 60
                                height: 50
                                color: "transparent"
                                Text{
                                    font.family: font_noto_r.name
                                    font.pixelSize: 12
                                    text: "전력"
                                    anchors.centerIn: parent
                                    color: "white"
                                    horizontalAlignment: Text.AlignHCenter
                                }
                            }
                            Rectangle{
                                width: 60
                                height: 50
                                color: "transparent"
                                Text{
                                    id: text_power
                                    font.pixelSize: 12
                                    anchors.centerIn: parent
                                    text: "0W"
                                    color: "white"
                                    horizontalAlignment: Text.AlignHCenter
                                }
                            }
                        }
                    }
                    Rectangle{
                        id: power_total
                        width: 80
                        height: 100
                        color: color_navy
                        Column{
                            Rectangle{
                                width: 60
                                height: 50
                                color: "transparent"
                                Text{
                                    font.family: font_noto_r.name
                                    font.pixelSize: 12
                                    text: "전력\n(Total)"
                                    anchors.centerIn: parent
                                    color: "white"
                                    horizontalAlignment: Text.AlignHCenter
                                }
                            }
                            Rectangle{
                                width: 60
                                height: 50
                                color: "transparent"
                                Text{
                                    id: text_power_total
                                    font.pixelSize: 12
                                    text: "0W"
                                    color: "white"
                                    anchors.centerIn: parent
                                    horizontalAlignment: Text.AlignHCenter
                                }
                            }
                        }
                    }
                }
            }
        }

    }
    Timer{
        id: timer_check_localization
        running: false
        repeat: true
        interval: 500
        onTriggered:{
            if(supervisor.is_slam_running()){
                supervisor.writelog("[QML] CHECK LOCALIZATION : STARTED")
                btn_auto_init.running = false;
                timer_check_localization.stop();
            }else if(supervisor.getLocalizationState() === 0 || supervisor.getLocalizationState() === 3){
                supervisor.writelog("[QML] CHECK LOCALIZATION : FAILED OR NOT READY "+Number(supervisor.getLocalizationState()));
                timer_check_localization.stop();
                btn_auto_init.running = false;
            }
        }
    }

    Rectangle{
        id: rect_menu2
        width: 400
        height: parent.height - statusbar.height
        anchors.left: rect_state.right
        anchors.topMargin: statusbar.height
        anchors.top: parent.top
        visible: select_localmode?true:false
        color: "#f4f4f4"
        Timer{
            id: timer_check_localization2
            running: false
            repeat: true
            interval: 500
            onTriggered: {
                if(test){
                    btn_right2.enabled = true;
                }else{
                    if(supervisor.getLocalizationState() === 2){//success
                        btn_do_autoinit.running = false;
                    }else if(supervisor.getLocalizationState() === 1){
                        btn_do_autoinit.running = true;
                    }else{
                        btn_do_autoinit.running = false;
                    }
                }
            }
        }
        Column{
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            spacing: 30
            Rectangle{
                width: rect_menu1.width
                height: 80
                color: color_dark_navy
                Text{
                    anchors.centerIn : parent
                    font.family: font_noto_b.name
                    font.pixelSize: 30
                    color: "white"
                    text:"위치 초기화"
                }
            }
            Rectangle{
                color: "transparent"
                width: rect_menu1.width
                height: rect_menu2.height - 80
                Column{
                    anchors.centerIn: parent
                    spacing: 50
                    Item_buttons{
                        width: 200
                        height: 80
                        type: "round_text"
                        selected: map.tool==="move"
                        text: "이 동"
                        onClicked: {
                            click_sound.play();
                            map.setTool("move");
                        }
                    }
                    Item_buttons{
                        width: 200
                        height: 80
                        type: "round_text"
                        selected: map.tool==="slam_init"
                        text: "수동 지정"
                        onClicked: {
                            click_sound.play();
                            map.setTool("slam_init");
                            supervisor.setInitCurPos();
                            supervisor.slam_setInit();
                        }
                    }
                    Item_buttons{
                        width: 200
                        height: 80
                        type: "round_text"
                        text:  "다시 시도"
                        onClicked: {
                            click_sound.play();
                            map.setTool("move");
                            supervisor.slam_autoInit();
                            timer_check_localization2.start();
                        }
                    }
                    Item_buttons{
                        id: btn_do_autoinit
                        width: 200
                        height: 100
                        running: false
                        type: "start_progress"
                        text: "자동위치찾기\n(1분소요)"
                        shadowcolor: color_dark_black
                        onClicked: {
                            click_sound.play();
                            map.setTool("move");
                            supervisor.slam_fullautoInit();
                            timer_check_localization2.start();
                        }
                    }
                }

            }
        }
    }

    MAP_FULL2{
        id: map
        objectName: "MOVEFAIL"
        width: 740
        height: width
        show_button_following: true
        show_button_lidar: true
        show_connection: true
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.topMargin: statusbar.height
    }

    Popup{
        id: popup_notice
        width: 1280
        height: 400
        anchors.centerIn: parent
        background: Rectangle{
            anchors.fill: parent
            color:"transparent"
        }
        Rectangle{
            width: 1280
            height: 400
            color:color_dark_navy
            Text{
                id: text
                text:"목적지로 이동하는데 실패하였습니다\n로봇을 수동으로 이동시켜주세요"
                anchors.centerIn: parent
                horizontalAlignment: Text.AlignHCenter
                font.family: font_noto_b.name
                font.pixelSize: 40
                color: "white"
            }
            MouseArea{
                anchors.fill: parent
                onClicked:{
                    popup_notice.close();
                }
            }
        }
    }

    Timer{
        id: timer_update
        interval: 300
        running: true
        repeat: true
        onTriggered: {
            //0: no path /1: local fail /2: emergency /3: user stop /4: motor error
            if(supervisor.getEmoStatus()){
                state_emo.enabled = true;
            }else{
                state_emo.enabled = false;
            }
            if(supervisor.getChargeStatus()){
                state_charging.enabled = true;
            }else{
                state_charging.enabled = false;
            }

            if(supervisor.getLockStatus() === 1){
                if(supervisor.getMotorConnection(0)){
                    if(supervisor.getMotorStatus(0) === 1){
                        state_motor_1.enabled = false;
                    }else{
                        state_motor_1.enabled = true;
                    }
                }else{
                    state_motor_1.enabled = true;
                }
                if(supervisor.getMotorConnection(1)){
                    if(supervisor.getMotorStatus(1) === 1){
                        state_motor_2.enabled            = false;
                    }else{
                        state_motor_2.enabled = true;
                    }
                }else{
                    state_motor_2.enabled = true;
                }
            }else{
                state_motor_1.enabled = false;
                state_motor_2.enabled = false;
            }



            if(supervisor.getLocalizationState() === 2){
                state_localization.enabled = false;
            }else{
                state_localization.enabled = true;
            }

            if(state_localization.enabled == false && state_motor_1.enabled == false && state_motor_2.enabled == false){
                btn_reset.enabled = true;
            }else{
                btn_reset.enabled = false;
            }

            if(supervisor.getMotorStatus(0)===0){
                text_motor_stat1.color = color_light_gray;
                text_motor_stat1.text = supervisor.getMotorStatusStr(0);
            }else if(supervisor.getMotorStatus(0)===1){
                text_motor_stat1.color = color_green;
                text_motor_stat1.text = supervisor.getMotorStatusStr(0);
            }else{
                text_motor_stat1.color = color_red;
                text_motor_stat1.text = supervisor.getMotorStatusStr(0);
            }
            if(supervisor.getMotorStatus(1)===0){
                text_motor_stat2.color = color_light_gray;
                text_motor_stat2.text = supervisor.getMotorStatusStr(1);
            }else if(supervisor.getMotorStatus(1)===1){
                text_motor_stat2.color = color_green;
                text_motor_stat2.text = supervisor.getMotorStatusStr(1);
            }else{
                text_motor_stat2.color = color_red;
                text_motor_stat2.text = supervisor.getMotorStatusStr(1);
            }

            if(supervisor.getMotorTemperature(0) > supervisor.getMotorWarningTemperature()){
                text_motor_temp1.color = color_red;
            }else{
                text_motor_temp1.color = "white";
            }
            if(supervisor.getMotorTemperature(1) > supervisor.getMotorWarningTemperature()){
                text_motor_temp2.color = color_red;
            }else{
                text_motor_temp2.color = "white";
            }

            text_motor_temp1.text = supervisor.getMotorTemperature(0).toFixed(0).toString();
            text_motor_temp2.text = supervisor.getMotorTemperature(1).toFixed(0).toString();

            text_battery_in.text = supervisor.getBatteryIn().toFixed(1).toString() + "V";
            text_battery_out.text = supervisor.getBatteryOut().toFixed(1).toString() + "V";
            text_current.text = supervisor.getBatteryCurrent().toFixed(1).toString() + "A";

            text_power.text = supervisor.getPower(0).toFixed(0).toString() + "W";
            text_power_total.text = supervisor.getPowerTotal(1).toFixed(0).toString() + "W";
        }
    }
}
