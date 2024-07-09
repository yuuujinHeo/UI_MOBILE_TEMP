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
    property int password: 0
    property int obs_in_path : 0
    property int show_face: 0

    function movedone(){
        loadPage(pkitchen);
        popup_notice.close();
    }

    Component.onCompleted: {
        statusbar.visible = false;
    }

    onPos_nameChanged: {
        if(pos_name === qsTr("충전 장소")){
            image_robot.source = "image/robot_move_charge.png"
        }else if(pos_name === qsTr("대기 장소")){
            image_robot.source = "image/robot_move_wait.png"
        }else{
            image_robot.source = "image/robot_moving.png"
        }
    }

    Component.onDestruction:  {
        supervisor.stopBGM();
    }

    function openNotice(errstr){
        popup_notice.init();
        popup_notice.style = "warning";
        if(errstr === "no_path"){
            popup_notice.main_str = qsTr("경로를 찾지 못했습니다");
            popup_notice.sub_str = "";
            popup_notice.open();
        }else if(errstr === "no_location"){
            popup_notice.main_str = qsTr("목적지가 지정되지 않았습니다");
            popup_notice.sub_str = "";
            popup_notice.open();
        }else if(errstr === "localization"){
            popup_notice.main_str = qsTr("로봇의 위치를 찾을 수 없습니다");
            popup_notice.sub_str = qsTr("로봇초기화를 다시 해주세요");
            popup_notice.addButton(qsTr("위치초기화"));
            popup_notice.open();
        }else if(errstr === "emo"){
            popup_notice.main_str = qsTr("비상스위치가 눌려있습니다");
            popup_notice.sub_str = qsTr("비상스위치를 풀어주세요");
            popup_notice.open();
        }else if(errstr === 3){
            popup_notice.main_str = qsTr("경로가 취소되었습니다");
            popup_notice.sub_str = "";
            popup_notice.open();
        }else if(errstr === "motor_lock"){
            popup_notice.style = "warning";
            popup_notice.main_str = qsTr("로봇이 수동모드입니다");
            popup_notice.sub_str = "";
            popup_notice.closemode = false;
            popup_notice.addButton(qsTr("모터초기화"))
            popup_notice.open();
        }else if(errstr === 5){
            popup_notice.main_str = qsTr("모터와 연결되지 않았습니다");
            popup_notice.sub_str = "";
            popup_notice.open();
        }else if(errstr === 6){
            popup_notice.main_str = qsTr("출발할 수 없는 상태입니다");
            popup_notice.sub_str = qsTr("로봇을 다시 초기화해주세요");
            popup_notice.open();
        }else if(errstr === "no_location"){
            popup_notice.style = "warning";
            popup_notice.main_str = qsTr("목적지를 찾을 수 없습니다");
            popup_notice.sub_str = qsTr("");
            popup_notice.open();
        }else if(errstr === "no_patrol"){
            popup_notice.style = "warning";
            popup_notice.main_str = qsTr("없는 지정순회 파일입니다");
            popup_notice.sub_str = qsTr("");
            popup_notice.open();
        }else if(errstr === "motor_notready"){
            popup_notice.style = "warning";
            popup_notice.main_str = qsTr("모터초기화가 필요합니다");
            popup_notice.sub_str = qsTr("비상전원스위치를 눌렀다가 풀어주세요");
            popup_notice.closemode = false;
            popup_notice.addButton(qsTr("모터초기화"))
            popup_notice.open();
        }else if(errstr === "debug"){
            popup_notice.style = "warning";
            popup_notice.main_str = qsTr("디버그 모드입니다")
            popup_notice.sub_str = qsTr("디버그모드에서는 주행할 수 없습니다")
            popup_notice.closemode = false;
            popup_notice.open();
        }else if(errstr === "charging"){
            popup_notice.style = "warning";
            popup_notice.main_str = qsTr("충전 케이블이 연결되어 있습니다")
            popup_notice.sub_str = qsTr("충전케이블이 연결된 상태로 주행할 수 없습니다")
            popup_notice.closemode = false;
            popup_notice.open();
        }else if(errstr === "running"){
            popup_notice.style = "warning";
            popup_notice.main_str = qsTr("로봇이 현재 대기상태가 아닙니다")
            popup_notice.sub_str = qsTr("현재 상태 : ")+supervisor.getStateMovingStr();
            popup_notice.closemode = false;
            popup_notice.open();
        }else if(errstr === "ipc_discon"){
            popup_notice.style = "error";
            popup_notice.main_str = qsTr("SLAMNAV와 연결할 수 없습니다")
            popup_notice.sub_str = "";
            popup_notice.closemode = false;
            popup_notice.open();
        }else if(errstr === "motor"){
            popup_notice.style = "error";
            popup_notice.main_str = qsTr("모터가 현재 대기상태가 아닙니다")
            popup_notice.sub_str = qsTr("현재 상태 : ")+supervisor.getMotorStatusStr(0)+","+supervisor.getMotorStatusStr(1);
            popup_notice.closemode = false;
            popup_notice.open();
        }
    }

    function init(){
        supervisor.writelog("[QML] MOVING PAGE init")
        popup_pause.visible = false;
        if(supervisor.isPatrolPage()){
            if(supervisor.getPatrolMovingMode() === "face1"){
                face_image.play("image/face_normal.gif");
                rect_robot.visible = false;
                show_face = 1;
            }else if(supervisor.getPatrolMovingMode() === "face2"){
                face_image.play("image/face_normal2.gif");
                rect_robot.visible = false;
                show_face = 2;
            }else{
                show_face = false;
                face_image.stop();
                rect_robot.visible = true;
            }
        }else{
            if(supervisor.getSetting("setting","UI","moving_face")==="1"){
                face_image.play("image/face_normal.gif");
                rect_robot.visible = false;
                show_face = 1;
            }else if(supervisor.getSetting("setting","UI","moving_face")==="2"){
                face_image.play("image/face_normal2.gif");
                rect_robot.visible = false;
                show_face = 2;
            }else if(supervisor.getSetting("setting","UI","moving_face")==="3"){
                show_face = 3;
                face_image.stop();
                rect_robot.visible = false;
            }else{
                show_face = 0;
                face_image.stop();
                rect_robot.visible = true;
            }
        }
        robot_paused = false;
        supervisor.playBGM();
    }

    Rectangle{
        id: rect_background
        anchors.fill: parent
        color: "#282828"
    }

    AnimatedImage{
        id: face_image
        visible: false
        cache: true
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
            }
            anchors.centerIn: parent
        }
    }

    Column{
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: rect_robot.right
        anchors.leftMargin: 100
        visible: !show_face
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
                        supervisor.playSound('click');;
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
            sourceSize.width: width
            sourceSize.height: height
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 200
            MouseArea{
                anchors.fill: parent
                z: 99
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
            text: qsTr("일시정지 됨")
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
                    text: qsTr("수동 이동")
                }
                MouseArea{
                    anchors.fill: parent
                    z: 99
                    onClicked:{
                        supervisor.playSound('click');
                        popup_notice.init();
                        popup_notice.closemode = false;
                        popup_notice.style = "warning";
                        popup_notice.main_str = qsTr("로봇을 수동으로 이동하시겠습니까?")
                        popup_notice.sub_str = qsTr("기존의 경로는 취소되며 대기화면으로 넘어갑니다")
                        popup_notice.addButton(qsTr("수동이동"));
                        popup_notice.open();
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
                        supervisor.playSound('click');;
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
                        supervisor.playSound('click');;
                        supervisor.writelog("[USER INPUT] MOVING PAUSED : RESUME");
                        supervisor.moveResume();
                    }
                }
            }
        }
    }

    property bool flag_voice: false
    property int count_voice: 0

    Timer{
        id: update_timer
        interval: 500
        running: true
        repeat: true
        property int prev_state: 0
        onTriggered: {
            if(supervisor.getLockStatus()===0){
                if(motor_lock)
                    supervisor.writelog("[UI] PageMoving : Motor Lock false");

                motor_lock = false;

                popup_notice.init();
                popup_notice.closemode = false;
                popup_notice.style = "warning";
                popup_notice.main_str = qsTr("로봇이 수동이동 중입니다")
                popup_notice.sub_str = ""
                popup_notice.addButton(qsTr("원래대로"));
                popup_notice.open();
            }else{
                if(!motor_lock){
                    supervisor.writelog("[UI] PageMoving : Motor Lock true");
                }
                motor_lock = true;

                if(prev_state !== supervisor.getStateMoving()){
                    if(supervisor.getStateMoving() === 4){
                        robot_paused = true;
                        popup_pause.visible = true;
                        supervisor.writelog("[UI] PageMoving : Check State -> Robot Paused");
                    }else if(supervisor.getStateMoving() === 0){
                        robot_paused = true;
                        popup_pause.visible = true;
                        supervisor.writelog("[UI] PageMoving : Check State -> Robot Not Moving");
                    }else{
                        popup_pause.visible = false;
                        robot_paused = false;
                        supervisor.writelog("[UI] PageMoving : Check State -> "+Number(supervisor.getStateMoving()));
                    }
                }
                prev_state = supervisor.getStateMoving();
            }

            if(supervisor.getMultiState() === 2){
                popup_waiting.visible = true;
            }else{
                popup_waiting.visible = false;
            }

            //DEBUG 230605
            obs_in_path =supervisor.getObsinPath();

            if(show_face == 1){
                if(obs_in_path == 0){
                    if(face_image.cur_source !== "image/face_normal.gif"){
                        supervisor.writelog("[UI] SHOW MOVING FACE : NORMAL");
                        face_image.play("image/face_normal.gif");
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
            }else if(show_face === 2){
                if(obs_in_path == 0){
                    if(face_image.cur_source !== "image/face_normal2.gif"){
                        supervisor.writelog("[UI] SHOW MOVING FACE : NORMAL");
                        face_image.play("image/face_normal2.gif");
                    }
                }else if(obs_in_path == 1){
                    flag_voice = true;
                    if(face_image.cur_source !== "image/face_surprise2.gif"){
                        supervisor.writelog("[UI] SHOW MOVING FACE : SURPRISE");
                        face_image.play("image/face_surprise2.gif");
                    }
                }else if(obs_in_path == 2){
                    flag_voice = true;
                    if(face_image.cur_source !== "image/face_cry2.gif"){
                        supervisor.writelog("[UI] SHOW MOVING FACE : CRY");
                        face_image.play("image/face_cry2.gif");
                    }
                }
            }
        }
    }
    MouseArea{
        id: btn_page
        anchors.fill: parent
        visible: !robot_paused
        onClicked: {
            supervisor.playSound('click');
            if(!robot_paused){
                supervisor.movePause();
            }
        }
    }

    MouseArea{
        id: btn_password_1
        width: 100
        height: 100
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        z: 99
        onClicked: {
            supervisor.playSound('click');
            password++;
            if(password > 4){
                password = 0;
                supervisor.moveStop();
                supervisor.writelog("[UI] PageMoving : debug pass -> PageKitchen");
                loadPage(pkitchen);
            }
        }
        onPressAndHold: {
            supervisor.playSound('click');
            password = 0;
            mainwindow.showMinimized();
        }
    }

    Popup_notice{
        id: popup_notice
        z:99
        onClicked:{
            if(cur_btn === qsTr("수동이동")){
                supervisor.writelog("[UI] PopupNotice : Lock Off");
                supervisor.setMotorLock(false);
            }else if(cur_btn === qsTr("취 소")||cur_btn === qsTr("확 인")){
                popup_notice.close();
            }else if(cur_btn === qsTr("모터초기화")){
                supervisor.writelog("[UI] PopupNotice : Motor Init");
                supervisor.setMotorLock(true);
                supervisor.stateInit();
                if(loader_page.item.objectName === "page_moving" || loader_page.item.objectName === "page_moving_custom"){
                    loadPage(pinit);
                }
                popup_notice.close();
            }else if(cur_btn === qsTr("위치초기화")){
                supervisor.writelog("[UI] PopupNotice : Local Init");
                if(loader_page.item.objectName === "page_annotation"){
                    loader_page.item.setAnnotLocation();
                }else{
                    loadPage(pinit);
                    supervisor.resetLocalization();
                    supervisor.stateInit();
                }
                popup_notice.close();
            }else if(cur_btn === qsTr("원래대로")){
                supervisor.writelog("[UI] PopupNotice : Lock On");
                supervisor.setMotorLock(true);
                supervisor.moveStopFlag();
                loadPage(pkitchen);
                popup_notice.close();
            }
        }
    }

}
