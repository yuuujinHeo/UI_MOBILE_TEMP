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

    property bool setting_patrol_mode: false
    property string setting_patrol_image: "image/robot_moving.png"
    property int setting_patrol_image_width: 300
    property int setting_patrol_image_height: 300

    property bool motor_lock: false
    property string pos_name: ""
    property bool robot_paused: false
    property bool move_fail: false
    property int password: 0
    property int obs_in_path : 0
    property bool show_face: false

    function movedone(){
        loadPage(pkitchen);
    }

    function setNotice(num){
        popup_motor_lock_off.open();
    }

    Component.onCompleted: {
        init();

        if(setting_patrol_mode){
            var ww = parseInt(supervisor.getSetting("setting","UI","patrol_image_width"));
            var hh = parseInt(supervisor.getSetting("setting","UI","patrol_image_heigth"));
            if(ww > 0 && ww < 1280){
                setting_patrol_image_width = ww;
            }else{
                setting_patrol_image_width = 300;
            }
            if(hh > 0 && hh < 1280){
                setting_patrol_image_height = hh;
            }else{
                setting_patrol_image_height = 300;
            }
        }else{
            statusbar.visible = false;
        }
    }

    onSetting_patrol_image_widthChanged: {
        image_robot_set.setSize();
    }
    onSetting_patrol_image_heightChanged: {
        image_robot_set.setSize();
    }

    onPos_nameChanged: {
        if(!setting_patrol_mode){
            if(pos_name === qsTr("충전 장소")){
                image_robot.source = "image/robot_move_charge.png"
            }else if(pos_name === qsTr("대기 장소")){
                image_robot.source = "image/robot_move_wait.png"
            }else{
                image_robot.source = "image/robot_moving.png"
            }
        }
//        image_robot.setsize();
    }

    Component.onDestruction:  {
//        playMusic.stop();
        supervisor.stopBGM();
    }

    function setImageHeight(){
        if(setting_patrol_mode){
            setting_patrol_image_height = (image_robot.sourceSize.height * setting_patrol_image_width / image_robot.sourceSize.width).toFixed(0);
            return setting_patrol_image_height;
        }
    }

    function getImageHeight(ww){
        var hh = image_robot.sourceSize.height * ww / image_robot.sourceSize.width;
        print(ww,hh)
        return hh.toFixed(0);
    }

    function setTempText(t1, t2){
        patrol_text_1.text = t1;
        patrol_text_2.text = t2;
    }

    function init(){
        supervisor.writelog("[QML] MOVING PAGE init")
        popup_pause.visible = false;
        if(setting_patrol_mode){
            show_face = false;
            face_image.stop();
        }else{
            if(supervisor.getSetting("setting","UI","moving_face")==="true"){
                face_image.play("image/temp.gif");
                rect_robot.visible = false;
                show_face = true;
            }else{
                show_face = false;
                face_image.stop();
                rect_robot.visible = true;
            }
            robot_paused = false;
            supervisor.playBGM();
        }
    }

    function checkPaused(){
        timer_check_pause.start();
    }

    function movefail(){
        robot_paused = true;
        move_fail = true;
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

    Rectangle{
        id: rect_robot
        width: 400
        height: 400
        visible: !setting_patrol_mode
        color: "transparent"
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: 100
        Image{
            id: image_robot
            source: "image/robot_moving.png"
            function setsize(){
                if(sourceSize.width > sourceSize.height){
                    width = 400;
                    height = sourceSize.height * 400/sourceSize.width;
                }else{
                    height = 400;
                    width = sourceSize.width * 400/sourceSize.height;
                 }
                print("====>>> ",sourceSize.width, sourceSize.height, width, height)
            }
            anchors.centerIn: parent
        }
    }

    Rectangle{
        id: rect_robot_set
        width: setting_patrol_image_width
        height: setting_patrol_image_height
        visible: setting_patrol_mode
        color: "red"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 160*page_moving.width/1280

        Image{
            id: image_robot_set
            source: {
                if(setting_patrol_mode){
                    setting_patrol_image
                }else{
                    if(pos_name === qsTr("충전 장소")){
                        "image/robot_move_charge.png"
                    }else if(pos_name === qsTr("대기 장소")){
                        "image/robot_move_wait.png"
                    }else{
                        "image/robot_moving.png"
                    }
                }
            }
            function setSize(){
                if(sourceSize.width > sourceSize.height){
                    if(sourceSize.width > setting_patrol_image_width){
                        width = setting_patrol_image_width*page_moving.width/1280;
                        height = sourceSize.height * setting_patrol_image_width*page_moving.width/1280 / sourceSize.width;
                    }else{
                        width = sourceSize.width*page_moving.width/1280;
                        height = sourceSize.height*page_moving.width/1280;
                    }
                }else{
                }
                print("source changed ", sourceSize.width,sourceSize.height,width,height);
            }

            anchors.centerIn: parent
            onSourceChanged: {
                setSize();
            }
        }
    }

    Column{
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: rect_robot_set.bottom
        anchors.topMargin: 50*page_moving.width/1280
        spacing: 20*page_moving.width/1280
        Text{
            id: patrol_text_1
            text: supervisor.getSetting("setting","UI","patrol_text_1");
            visible: setting_patrol_mode
            font.pixelSize: 50*page_moving.width/1280
            font.family: font_noto_b.name
            anchors.horizontalCenter: parent.horizontalCenter
            color: "white"
        }
        Text{
            id: patrol_text_2
            visible: setting_patrol_mode
            text: supervisor.getSetting("setting","UI","patrol_text_2");
            font.pixelSize: 40*page_moving.width/1280
            font.family: font_noto_r.name
            anchors.horizontalCenter: parent.horizontalCenter
            color: "white"
        }

    }

    Column{
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: rect_robot.right
        anchors.leftMargin: 100
        visible: !show_face&& !setting_patrol_mode
        Text{
            id: target_pos
            text: pos_name
            font.pixelSize: 80
            font.family: font_noto_b.name
            color: "#12d27c"
        }
        Text{
            id: text_mention
            text: qsTr("(으)로 이동 중입니다.")
            font.pixelSize: 60
            font.family: font_noto_r.name
            color: "white"
        }
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
                        click_sound.play();;
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
            source: "icon/icon_warning.png"
            width: 160
            height: 160
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 200
            MouseArea{
                anchors.fill: parent
                z: 99
                onClicked:{
                    popup_pause.visible = false;
                }
            }
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
                        click_sound.play();;
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
                        click_sound.play();;
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
                        click_sound.play();;
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
                            click_sound.play();;
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
                            click_sound.play();;
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
                            click_sound.play();;
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
        enabled: !setting_patrol_mode
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        z: 99
        onClicked: {
            click_sound.play();;
            password++;
            supervisor.writelog("[USER INPUT] MOVING PASSWORD "+Number(password));
            if(password > 4){
                password = 0;
                supervisor.writelog("[USER INPUT] ENTER THE MOVEFAIL PAGE "+Number(password));
                loadPage(pkitchen);
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
            if(setting_patrol_mode){

            }else{
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
    }
    Timer{
        id: update_timer
        interval: 500
        running: true
        repeat: true
        onTriggered: {
            if(setting_patrol_mode){

            }else{
                if(supervisor.getLockStatus()===0 || supervisor.getEmoStatus()){
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

            }

//            text_debug_1.text = "Robot Auto State : " + supervisor.getStateMoving().toString();
//            text_debug_2.text = "Robot OBS In Path State : " + supervisor.getObsinPath().toString();
        }
    }

//    Audio{
//        id: voice_serving
//        volume: volume_voice/100
//        source: supervisor.getVoice("serving");
//        property bool isplaying: false
//        onStopped: {
//            isplaying = false;
//        }
//        onPlaying:{
//            isplaying = true;
//        }
//    }

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
            click_sound.play();;
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
