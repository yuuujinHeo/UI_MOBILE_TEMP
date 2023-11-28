import QtQuick 2.12
import QtQuick.Controls 2.12
import "."
import io.qt.Supervisor 1.0
import QtMultimedia 5.12

Item {
    id: page_moving
    objectName: "page_moving"
    width: 1280
    height: 800

    property bool motor_lock: false
    property string pos_name: ""
    property bool robot_paused: false
    property bool move_fail: false
    property int password: 0
    property int obs_in_path : 0
    property bool show_face: false

    Component.onCompleted: {
        init();
        statusbar.visible = false;
    }

    Component.onDestruction:  {
        playMusic.stop();
    }

    function init(){
        supervisor.writelog("[QML] MOVING PAGE init")

        popup_pause.visible = false;
        if(supervisor.getSetting("setting","UI","moving_face")==="true"){

            face_image.play("image/temp.gif");
            image_robot.visible = false;
            show_face = true;
        }else{
            show_face = false;
            face_image.stop();
            image_robot.visible = true;
        }

        robot_paused = false;
        playMusic.play();
    }
    function checkPaused(){
        timer_check_pause.start();
    }

    function movefail(){
        robot_paused = true;
        move_fail = true;
    }

    Audio{
        id: playMusic
        autoPlay: false
        volume: volume_bgm/100
        source: "bgm/song.mp3"
        loops: 99
        property bool isplaying: false
        onStopped: {
            isplaying = false;
        }
        onPlaying:{
            isplaying = true;
        }
    }

    Rectangle{
        id: rect_background
        anchors.fill: parent
        color: "#282828"
    }
    AnimatedImage{
        id: face_image
        visible: false
        cache: false
        property string cur_source: ""
        function play(name){
            source = name;
            cur_source = name;
            visible = true;
        }
        function stop(){
            visible = false;
            cur_source = "";
            source = "";
        }
        source:  ""
        anchors.fill: parent
    }
    Image{
        id: image_robot
        source: {
            if(pos_name == qsTr("충전 장소")){
                "image/robot_move_charge.png"
            }else if(pos_name == qsTr("대기 장소")){
                "image/robot_move_wait.png"
            }else{
                "image/robot_moving.png"
            }
        }
        width: 300
        height: 270
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 200
    }

    Text{
        id: target_pos
        text: pos_name
        visible: !show_face
        font.pixelSize: 40
        font.family: font_noto_b.name
        anchors.right: parent.horizontalCenter
        anchors.top: image_robot.bottom
        anchors.topMargin: 80
        anchors.rightMargin: 40
        color: "#12d27c"
    }
    Text{
        id: text_mention
        visible: !show_face
        text: qsTr("(으)로 이동 중입니다.")
        font.pixelSize: 40
        font.family: font_noto_r.name
        anchors.left: parent.horizontalCenter
        anchors.top: image_robot.bottom
        anchors.topMargin: 80
        anchors.leftMargin: 40
        color: "white"
    }
    Text{
        id: target_posname
        text: pos_name
        visible: false//!show_face
        font.pixelSize: 40
        font.family: font_noto_b.name
        color: "#12d27c"
        anchors.horizontalCenter: target_pos.horizontalCenter
        anchors.top: target_pos.bottom
        anchors.topMargin: 10
    }

    Item{
        id: popup_waiting
        width: parent.width
        height: parent.height
        anchors.centerIn: parent
        visible: false
        onVisibleChanged: {
            if(visible){
                statusbar.visible = true;
            }else{
                statusbar.visible = false;
            }
        }
        Rectangle{
            anchors.fill: parent
            color: "#282828"
            opacity: 0.8
        }
        Text{
            id: teeeq34e
            anchors.centerIn: parent
            font.family: font_noto_b.name
            font.pixelSize: 50
            color: "#e2574c"
            text: qsTr("다른 로봇의 이동을 기다리고 있습니다")
        }
        Text{
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top:teeeq34e.bottom
            anchors.topMargin: 10
            font.family: font_noto_b.name
            font.pixelSize: 40
            color: "#e2574c"
            text: qsTr("( 목적지 : ")+pos_name+" )"
        }
        Row{
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 80
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 100
            Rectangle{
                width: 180
                height: 120
                radius: 20
                color: "transparent"
                enabled: motor_lock
                border.color: motor_lock?color_red:color_gray
                border.width: 6
                Text{
                    anchors.centerIn: parent
                    color: color_red
                    font.family: font_noto_r.name
                    font.pixelSize: 30
                    text: qsTr("경로 취소")
                }
                MouseArea{
                    anchors.fill: parent
                    z: 99
                    propagateComposedEvents: true
                    onPressed:{
                        click_sound.play();
                        parent.color = color_dark_navy
                    }
                    onReleased:{
                        parent.color = "transparent"
                    }

                    onClicked:{
                        supervisor.writelog("[USER INPUT] MOVING PAUSED : PATH CANCELED");
                        supervisor.moveStop();
                    }
                }
            }
        }
    }

    Item{
        id: popup_pause
        width: parent.width
        height: parent.height
        anchors.centerIn: parent
        onVisibleChanged: {
            if(visible){
                statusbar.visible = true;
            }else{
                statusbar.visible = false;
            }
        }

        Rectangle{
            anchors.fill: parent
            visible: robot_paused
            color: "#282828"
            opacity: 0.8
        }
        Image{
            id: image_warning
            source: "icon/warning.png"
            width: 160
            height: 160
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 200
        }
        Text{
            id: teee
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top:image_warning.bottom
            anchors.topMargin: 30
            font.family: font_noto_b.name
            font.pixelSize: 50
            color: "#e2574c"
            text: move_fail?qsTr("경로를 찾을 수 없습니다"):qsTr("일시정지 됨")
        }
        Text{
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top:teee.bottom
            anchors.topMargin: 10
            font.family: font_noto_b.name
            font.pixelSize: 40
            color: "#e2574c"
            text: qsTr("( 목적지 : ")+pos_name+" )"
        }
        Row{
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 80
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 100
            Rectangle{
                width: 180
                height: 120
                radius: 20
                color: "transparent"
                border.color: color_red
                border.width: 6
                Text{
                    anchors.centerIn: parent
                    color: color_red
                    font.family: font_noto_r.name
                    font.pixelSize: 30
//                    text: motor_lock?"수동 이동":"원래대로"
                    text: qsTr("수동 이동")
                }
                MouseArea{
                    anchors.fill: parent
                    z: 99
                    onClicked:{
                        click_sound.play();
                        popup_motor_lock.open();

//                        if(!motor_lock){
//                        }
                    }
                }
            }
            Rectangle{
                width: 180
                height: 120
                radius: 20
                color: "transparent"
                enabled: motor_lock
                border.color: motor_lock?color_red:color_gray
                border.width: 6
                Text{
                    anchors.centerIn: parent
                    color: color_red
                    font.family: font_noto_r.name
                    font.pixelSize: 30
                    text: qsTr("경로 취소")
                }
                MouseArea{
                    anchors.fill: parent
                    z: 99
                    propagateComposedEvents: true
                    onPressed:{
                        click_sound.play();
                        parent.color = color_dark_navy
                    }
                    onReleased:{
                        parent.color = "transparent"
                    }
                    onClicked:{
                        supervisor.writelog("[USER INPUT] MOVING PAUSED : PATH CANCELED");
                        supervisor.moveStop();
                    }
                }
            }
            Rectangle{
                width: 180
                height: 120
                radius: 20
                color: "transparent"
                enabled: motor_lock
                border.color: motor_lock?color_red:color_gray
                border.width: 6
                Text{
                    anchors.centerIn: parent
                    color: color_red
                    font.family: font_noto_r.name
                    font.pixelSize: 30
                    text: qsTr("경로 재개")
                }
                MouseArea{
                    anchors.fill: parent
                    z: 99
                    onClicked:{
                        click_sound.play();
                        supervisor.writelog("[USER INPUT] MOVING PAUSED : RESUME");
                        supervisor.moveResume();
                        timer_check_pause.start();
                    }
                }
            }
        }
    }
    Popup{
        id: popup_motor_lock
        anchors.centerIn: parent
        width: parent.width
        height: parent.height
        background:Rectangle{
            anchors.fill: parent
            color: color_dark_black
            opacity: 0.8
        }
        Rectangle{
            width: parent.width
            height: 300
            anchors.centerIn: parent
            color: color_dark_black
            Image{
                id: image_warn
                source: "image/warning.png"
                width: 120
                height: 120
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 50
            }
            Column{
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: image_warn.right
                anchors.leftMargin: 50
                spacing: 5
                Text{
                    color: color_red
                    font.family: font_noto_r.name
                    font.pixelSize: 35
                    text: qsTr("로봇을 수동으로 이동하시겠습니까?")
                }
                Text{
                    color: color_red
                    font.family: font_noto_r.name
                    font.pixelSize: 30
                    text: qsTr("기존의 경로는 취소되며 대기화면으로 넘어갑니다")
                }
            }
            Row{
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 30
                anchors.right: parent.right
                anchors.rightMargin: 30
                spacing: 50
                Rectangle{
                    width: 140
                    height: 70
                    radius: 10
                    color: "transparent"
                    border.color: color_red
                    border.width: 3
                    Text{
                        anchors.centerIn: parent
                        font.family: font_noto_r.name
                        font.pixelSize: 25
                        color: color_red
                        text: qsTr("수동이동")
                    }
                    MouseArea{
                        anchors.fill: parent
                        onPressed:{
                            click_sound.play();
                            parent.color = color_dark_black;
                        }
                        onReleased:{
                            parent.color = "transparent";
                            supervisor.setMotorLock(!motor_lock);
                            supervisor.writelog("[USER INPUT] MOVING PAUSED : MOTOR LOCK DISABLE");
                        }
                    }
                }
                Rectangle{
                    width: 140
                    height: 70
                    radius: 10
                    color: "transparent"
                    border.color: color_red
                    border.width: 3
                    Text{
                        anchors.centerIn: parent
                        font.family: font_noto_r.name
                        font.pixelSize: 25
                        color: color_red
                        text: qsTr("취 소")
                    }
                    MouseArea{
                        anchors.fill: parent
                        onPressed:{
                            click_sound.play();
                            parent.color = color_dark_black;
                        }
                        onReleased:{
                            parent.color = "transparent";
                            popup_motor_lock.close();
//                            supervisor.writelog("[USER INPUT] MOVING PAUSED : MOTOR LOCK DISABLE");
                        }
                    }
                }
            }

        }

    }

    Popup{
        id: popup_motor_lock_off
        anchors.centerIn: parent
        width: parent.width
        height: parent.height
        background:Rectangle{
            anchors.fill: parent
            color: color_dark_black
            opacity: 0.8
        }
        Rectangle{
            width: parent.width
            height: 300
            anchors.centerIn: parent
            color: color_dark_black
            Image{
                id: image_warn2
                source: "image/warning.png"
                width: 120
                height: 120
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 50
            }
            Column{
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.horizontalCenterOffset: 50
                spacing: 50
                Text{
                    color: color_red
                    font.family: font_noto_r.name
                    font.pixelSize: 35
                    text: qsTr("로봇이 수동이동 중입니다")
                }
                Rectangle{
                    width: 140
                    height: 70
                    radius: 10
                    color: "transparent"
                    border.color: color_red
                    border.width: 3
                    Text{
                        anchors.centerIn: parent
                        font.family: font_noto_r.name
                        font.pixelSize: 25
                        color: color_red
                        text: qsTr("원래대로")
                    }
                    MouseArea{
                        anchors.fill: parent
                        onPressed:{
                            click_sound.play();
                            parent.color = color_dark_black;
                        }
                        onReleased:{
                            parent.color = "transparent";
                            supervisor.setMotorLock(!motor_lock);
                            supervisor.moveStopFlag();
                            supervisor.writelog("[USER INPUT] MOVING PAUSED : MOTOR LOCK EANBLE");
                        }
                    }
                }
            }

        }

    }


    MouseArea{
        id: btn_password_1
        width: 100
        height: 100
//        enabled: robot_paused
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        z: 99
        onClicked: {
            click_sound2.play();
            password++;
            supervisor.writelog("[USER INPUT] MOVING PASSWORD "+Number(password));
            if(password > 4){
                password = 0;
                supervisor.writelog("[USER INPUT] ENTER THE MOVEFAIL PAGE "+Number(password));
                loadPage(pmovefail);
                loader_page.item.setNotice(3);
            }
        }
        onPressAndHold: {
            password = 0;
            mainwindow.showMinimized();
        }
    }

    property bool flag_voice: false
    property var count_voice: 0
    Timer{
        id: timer_check_pause
        interval: 500
        running: false
        repeat: true
        onTriggered: {
            if(supervisor.getStateMoving() === 4){
                robot_paused = true;
                popup_pause.visible = true;
                supervisor.writelog("[QML] CHECK MOVING STATE : PAUSED")
                timer_check_pause.stop();
            }else if(supervisor.getStateMoving() === 0){
                robot_paused = true;
                popup_pause.visible = true;
                supervisor.writelog("[QML] CHECK MOVING STATE : NOT READY")
                move_fail = true;
                timer_check_pause.stop();
            }else{
                popup_pause.visible = false;
                robot_paused = false;
                supervisor.writelog("[QML] CHECK MOVING STATE : "+Number(supervisor.getStateMoving()));
                timer_check_pause.stop();
            }
        }
    }
    Timer{
        id: update_timer
        interval: 500
        running: true
        repeat: true
        onTriggered: {
            if(supervisor.getLockStatus()===0){
                if(motor_lock)
                    supervisor.writelog("[QML] Motor Lock : false");
                motor_lock = false;
                popup_motor_lock.close();
                popup_motor_lock_off.open();
            }else{
                if(!motor_lock){
                    supervisor.writelog("[QML] Motor Lock : true");
                }
                motor_lock = true;
                popup_motor_lock_off.close();
                if(supervisor.getStateMoving() === 4){
                    robot_paused = true;
                    popup_pause.visible = true;
                }else{
                    robot_paused = false;
                }
            }

            if(supervisor.getMultiState() === 2){
                popup_waiting.visible = true;
            }else{
                popup_waiting.visible = false;
            }

            //DEBUG 230605
            obs_in_path =supervisor.getObsinPath();

            if(show_face){
                if(obs_in_path == 0){
                    if(face_image.cur_source !== "image/temp.gif"){
                        supervisor.writelog("[UI] SHOW MOVING FACE : NORMAL");
                        face_image.play("image/temp.gif");
                    }
                }else if(obs_in_path == 1){
                    flag_voice = true;
                    if(face_image.cur_source !== "image/face_surprise.gif"){
                        supervisor.writelog("[UI] SHOW MOVING FACE : SURPRISE");
                        face_image.play("image/face_surprise.gif");
                    }
                }else if(obs_in_path == 2){
                    flag_voice = true;
                    if(face_image.cur_source !== "image/face_cry.gif"){
                        supervisor.writelog("[UI] SHOW MOVING FACE : CRY");
                        face_image.play("image/face_cry.gif");
                    }
                }
            }

            text_debug_1.text = supervisor.getSetting("update","DRIVING","pause_motor_current");
            text_debug_2.text = supervisor.getMotorCurrent(0).toString() + ", " + supervisor.getMotorCurrent(1).toString();

//            text_debug_1.text = "Robot Auto State : " + supervisor.getStateMoving().toString();
//            text_debug_2.text = "Robot OBS In Path State : " + supervisor.getObsinPath().toString();
        }
    }

    Audio{
        id: voice_serving
        volume: volume_voice/100
        source: supervisor.getVoice("serving");
        property bool isplaying: false
        onStopped: {
            isplaying = false;
        }
        onPlaying:{
            isplaying = true;
        }
    }

    Column{
        visible: false
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        spacing: 20
        anchors.leftMargin: 50
        anchors.bottomMargin: 50
        Text{
            id: text_debug_1
            color: "white"
            text: "Robot Auto State : "
            font.pixelSize: 20
        }
        Text{
            id: text_debug_2
            color: "white"
            text: "Robot OBS In Path State : "
            font.pixelSize: 20
        }
    }


    MouseArea{
        id: btn_page
        anchors.fill: parent
        visible: !robot_paused
        onClicked: {
            click_sound.play();
            if(robot_paused){
//                supervisor.writelog("[USER INPUT] MOVING RESUME 2")
//                supervisor.moveResume();
//                timer_check_pause.start();
            }else{
                supervisor.writelog("[USER INPUT] MOVING PAUSE 2")
                supervisor.movePause();
                timer_check_pause.start();

            }
        }
    }
//    SoundEffect{
//        id: click
//        source: "bgm/click.wav"
//    }
}
