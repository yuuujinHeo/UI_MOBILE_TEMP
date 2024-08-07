import QtQuick 2.12
import QtQuick.Controls 2.12
import "."
import io.qt.Supervisor 1.0
import io.qt.MapViewer 1.0
import QtGraphicalEffects 1.0
import io.qt.CameraView 1.0
import QtMultimedia 5.12

Item {
    id: page_init
    objectName: "page_init"
    width: 1280
    height: 800

    //0:inifile, 1:mapfile, 2:connection, 3:slam, 4:done
    property int init_mode: 0

    property bool show_debug: false

    Component.onCompleted: {
        init_mode = 0;
        supervisor.clearSharedMemory();
        supervisor.setUiState(1);
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

            popup_notice.addButton(qsTr("모터초기화"))
            popup_notice.open();
        }else if(errstr === "debug"){
            popup_notice.style = "warning";
            popup_notice.main_str = qsTr("디버그 모드입니다")
            popup_notice.sub_str = qsTr("디버그모드에서는 주행할 수 없습니다")

            popup_notice.open();
        }else if(errstr === "charging"){
            popup_notice.style = "warning";
            popup_notice.main_str = qsTr("충전 케이블이 연결되어 있습니다")
            popup_notice.sub_str = qsTr("충전케이블이 연결된 상태로 주행할 수 없습니다")

            popup_notice.open();
        }else if(errstr === "running"){
            popup_notice.style = "warning";
            popup_notice.main_str = qsTr("로봇이 현재 대기상태가 아닙니다")
            popup_notice.sub_str = qsTr("현재 상태 : ")+supervisor.getStateMovingStr();

            popup_notice.open();
        }else if(errstr === "motor"){
            popup_notice.style = "error";
            popup_notice.main_str = qsTr("모터가 현재 대기상태가 아닙니다")
            popup_notice.sub_str = qsTr("현재 상태 : ")+supervisor.getMotorStatusStr(0)+","+supervisor.getMotorStatusStr(1);

            popup_notice.open();
        }
    }

    function init(){
        if(loader_init.item.objectName == "init_init"){
            loader_init.item.ip_update();
        }
    }

    function wifistatein(){
        loader_init.item.updatewifiState();
    }
    function wifi_con_failed(){
        loader_init.item.connect_fail();
    }
    function wifi_con_success(){
//        popup_wifi.con_success();
//        loader_init.item.updatewifiState();
       loader_init.item.ip_update();
    }

    //init page main window
    Loader{
        id: loader_init
        anchors.fill: parent
        sourceComponent: page_loading
    }

    //로딩화면
    Component{
        id: page_loading
        Item {
            objectName: "page_logo"
            anchors.fill: parent
            Rectangle{
                anchors.fill: parent
                color: "#f4f4f4"
                OpacityAnimator{
                    target: image_logo1;
                    from: 0;
                    to: 1;
                    duration: 1000
                    running: true
                }
                Image{
                    id: image_logo1
                    width: 2245/4
                    height: 1004/4
                    sourceSize.width: width
                    sourceSize.height: height
                    source: Qt.resolvedUrl("qrc:/image/rainbow3.png")
                    anchors.horizontalCenter:  parent.horizontalCenter
                    y: 220
                }
                Text{
                    id: text_copyright
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 130
                    text: "Copyrights Rainbow Robotics Inc. All rights reserved."
                    color: "#7e7e7e"
                    font.family: font_noto_b.name
                    font.pixelSize: 20
                }
            }
        }
    }

    //1. 로봇과 연결 되지 않을 때
    Component{
        id: item_ipc
        Item{
            objectName: "item_ipc"
            anchors.fill: parent
            Component.onCompleted: {
                statusbar.visible = true;
            }

            Rectangle{
                anchors.fill: parent
                color: "#f4f4f4"
            }

            Text{
                font.family: font_noto_r.name
                color: "#7e7e7e"
                horizontalAlignment: Text.AlignHCenter
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenterOffset: -100
                text: qsTr("로봇과 연결이 되지 않습니다\n재시작 후에도 연결이 되지 않으면 로봇을 재부팅해주세요")
                font.pixelSize: 50
            }

            Row{
                spacing: 40
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 140
                anchors.horizontalCenter: parent.horizontalCenter
                Rectangle{
                    id: btn_minimize
                    width: 230
                    height: 130
                    radius: 30
                    color: color_navy
                    Row{
                        spacing: 15
                        anchors.centerIn: parent
                        Image{
                            id: image_charge
                            width: 40
                            height: 40
                            sourceSize.width: width
                            sourceSize.height: height
                            source:"icon/icon_minimize.png"
                            anchors.verticalCenter: parent.verticalCenter
                            ColorOverlay{
                                source: parent
                                anchors.fill: parent
                                color: "white"
                            }
                        }
                        Text{
                            text: qsTr("재시작")
                            anchors.verticalCenter: parent.verticalCenter
                            color: "white"
                            font.family: font_noto_r.name
                            font.pixelSize: 30
                            horizontalAlignment: Text.AlignHCenter
                        }
                    }
                    MouseArea{
                        anchors.fill: parent
                        onPressed:{
                            parent.color = color_mid_navy;
                        }
                        onReleased: {
                            supervisor.playSound('start');
                            supervisor.writelog("[INIT] Program Restart")
                            supervisor.programRestart();
                            parent.color = color_navy;
                        }
                    }
                }
                Rectangle{
                    id: btn_lcm_pass
                    width: 230
                    height: 130
                    radius: 30
                    color: "transparent"
                    border.width: 2
                    border.color: color_navy
                    visible: show_debug
                    Row{
                        spacing: 15
                        anchors.centerIn: parent
                        Text{
                            id: text_slam_pass
                            text: qsTr("건너뛰기")
                            color: color_navy
                            horizontalAlignment: Text.AlignHCenter
                            font.family: font_noto_r.name
                            font.pixelSize: 30
                        }
                    }
                    MouseArea{
                        anchors.fill: parent
                        onPressed:{
                            parent.color = color_gray;
                        }
                        onReleased: {
                            supervisor.playSound('click');
                            supervisor.writelog("[INIT] PASS IPC Connection")

                            popup_notice.init();
                            popup_notice.style = "warning";
                            popup_notice.main_str = qsTr("초기화를 건너뛰겠습니까?")
                            popup_notice.sub_str = qsTr("초기화를 건너뜁니다 로봇이 제대로 동작하지 않을 수 있습니다\n맵 메뉴에서 위치초기화를 누르면 다시 처음 세팅화면으로 돌아옵니다")
                            popup_notice.addButton(qsTr("건너뛰기"));
                            popup_notice.open();
                            parent.color = "transparent";
                        }
                    }
                }

            }

            MouseArea{
                id: area_debug
                width: 100
                height: 100
                anchors.right: parent.right
                anchors.bottom : parent.bottom
                z: 99
                property var password: 0
                onClicked: {
                    supervisor.playSound('click');
                    password++;
                    if(password > 4){
                        password = 0;
                        show_debug = true;
                    }
                }
            }
        }
    }

    //2. robot_config 확인 안될 때
    Component{
        id: item_robot_config
        Item{
            objectName: "item_robot_config"
            anchors.fill: parent
            Rectangle{
                anchors.fill: parent
                color: "#f4f4f4"
            }
            Component.onCompleted: {
                statusbar.visible = true;
                supervisor.makeRobotINI();
            }
            function updatewifiState(){
                wizard_ip.connection = supervisor.getWifiConnection(wizard_ip.select_ssd);
//                print("update wifi state = ",wizard_ip.select_ssd, wizard_ip.connection);

            }
            function connect_fail(){
                text_wifi76788.visible = true;
            }

            function ip_update(){
                var ip = supervisor.getcurIP().split(".");
                if(ip.length >3){
                    ip_1.text = ip[0];
                    ip_2.text = ip[1];
                    ip_3.text = ip[2];
                    ip_4.text = ip[3];
                }else{
                    ip_1.text = "";
                    ip_2.text = "";
                    ip_3.text = "";
                    ip_4.text = "";
                }

                ip = supervisor.getcurGateway().split(".");
                if(ip.length >3){
                    gateway_1.text = ip[0];
                    gateway_2.text = ip[1];
                    gateway_3.text = ip[2];
                    gateway_4.text = ip[3];
                }else{
                    gateway_1.text = "";
                    gateway_2.text = "";
                    gateway_3.text = "";
                    gateway_4.text = "";
                }
                ip = supervisor.getcurGateway().split(".");
                if(ip.length >3){
                    dnsmain_1.text = ip[0];
                    dnsmain_2.text = ip[1];
                    dnsmain_3.text = ip[2];
                    dnsmain_4.text = ip[3];
                }else{
                    dnsmain_1.text = "";
                    dnsmain_2.text = "";
                    dnsmain_3.text = "";
                    dnsmain_4.text = "";
                }
                ip_1.ischanged = false;
                ip_2.ischanged = false;
                ip_3.ischanged = false;
                ip_4.ischanged = false;
                gateway_1.ischanged = false;
                gateway_2.ischanged = false;
                gateway_3.ischanged = false;
                gateway_4.ischanged = false;
                dnsmain_1.ischanged = false;
                dnsmain_2.ischanged = false;
                dnsmain_3.ischanged = false;
                dnsmain_4.ischanged = false;
                ip_1.focus = false;
                ip_2.focus = false;
                ip_3.focus = false;
                ip_4.focus = false;
                gateway_1.focus = false;
                gateway_2.focus = false;
                gateway_3.focus = false;
                gateway_4.focus = false;
                dnsmain_1.focus = false;
                dnsmain_2.focus = false;
                dnsmain_3.focus = false;
                dnsmain_4.focus = false;
            }

            SwipeView{
                id: swipeview_wizard
                anchors.fill: parent
                currentIndex: 0
                interactive: false
                onCurrentIndexChanged: {
                    currentItem.init();
                }
                clip: true
                Item{
                    id: wizard_intro
                    function init(){
                    }
                    Column{
                        anchors.top: parent.top
                        anchors.topMargin: 200
                        anchors.horizontalCenter: parent.horizontalCenter
                        spacing:80
                        Row{
                            spacing: 60
                            anchors.horizontalCenter: parent.horizontalCenter
                            Image{
                                width: 150
                                height: 220
                                sourceSize.width: width
                                sourceSize.height: height
                                source: "image/robot_callme.png"
                            }
                            Column{
                                anchors.bottom: parent.bottom
                                anchors.bottomMargin: 30
                                Text{
                                    text: qsTr("로봇이 처음 시작된 것 같습니다")
                                    color: color_dark_black
                                    font.pixelSize: 40
                                    font.family: font_noto_b.name
                                }
                                Text{
                                    text: qsTr("<font color=\"#12d27c\">첫 실행 마법사</font>를 시작할까요?");
                                    color: color_dark_black
                                    font.pixelSize: 50
                                    font.family: font_noto_b.name
                                }
                            }
                        }
                        Row{
                            spacing: 50
                            anchors.horizontalCenter: parent.horizontalCenter
                            Rectangle{
                                id: btn_usb_load
                                width: 230
                                height: 100
                                radius: 60
                                border.width: 3
                                border.color: enabled?color_green:color_gray
                                enabled: supervisor.getusbsize()>0?true:false
                                color: "transparent"
                                Text{
                                    text: qsTr("USB에서 가져오기")
                                    font.pixelSize: 23
                                    font.family: font_noto_r.name
                                    color:btn_usb_load.enabled?color_dark_black:color_gray
                                    anchors.centerIn: parent
                                }
                                MouseArea{
                                    anchors.fill: parent
                                    onClicked: {
                                        supervisor.playSound('click');
                                        supervisor.writelog("[USER INPUT] INIT PAGE : LOAD MAP FROM USB")
                                        popup_usb_download.open();
                                    }
                                }
                            }
                            Rectangle{
                                id: btn_yes
                                width: 230
                                height: 100
                                radius: 60
                                color: color_green
                                Text{
                                    anchors.centerIn: parent
                                    text: qsTr("시작")
                                    font.pixelSize: 35
                                    font.family: font_noto_r.name
                                    color: "white"
                                }
                                MouseArea{
                                    anchors.fill: parent
                                    onClicked: {
                                        supervisor.playSound('start');
                                        supervisor.writelog("[USER INPUT] INIT PAGE : NEXT")
                                        swipeview_wizard.currentIndex++;
                                    }
                                }
                            }
                            Rectangle{
                                id: btn_lcm_pass
                                width: 188
                                height: 100
                                radius: 60
                                color: "transparent"
                                border.width: 3
                                border.color: "#e5e5e5"
                                visible: show_debug
                                Column{
                                    spacing: 5
                                    anchors.centerIn: parent
                                    Text{
                                        id: text_slam_pass
                                        text: qsTr("건너뛰기")
                                        font.family: font_noto_r.name
                                        font.pixelSize: 15
                                    }
                                }
                                MouseArea{
                                    anchors.fill: parent
                                    onClicked: {
                                        supervisor.playSound('click');

                                        popup_notice.init();
                                        popup_notice.style = "warning";
                                        popup_notice.main_str = qsTr("초기화를 건너뛰겠습니까?")
                                        popup_notice.sub_str = qsTr("초기화를 건너뜁니다 로봇이 제대로 동작하지 않을 수 있습니다\n맵 메뉴에서 위치초기화를 누르면 다시 처음 세팅화면으로 돌아옵니다")
                                        popup_notice.addButton(qsTr("건너뛰기"));
                                        popup_notice.open();
                                        supervisor.writelog("[USER INPUT] INIT PAGE : PASS CONNECTION")
                                        update_timer.stop();
                                    }
                                }
                            }
                        }
                    }
                }
                Item{
                    id: wizard_type
                    function init(){
                    }
                    Column{
                        anchors.centerIn: parent
                        spacing:80
                        Text{
                            text: qsTr("이 로봇은 어떤 목적으로 사용됩니까?");
                            color: color_dark_black
                            anchors.horizontalCenter: parent.horizontalCenter
                            font.pixelSize: 50
                            font.family: font_noto_b.name
                        }
                        Row{
                            spacing: 80
                            anchors.horizontalCenter: parent.horizontalCenter

                            Rectangle{
                                width: 230
                                height: 110
                                radius: 60
                                color: "transparent"
                                border.width: 3
                                border.color : color_green
                                Text{
                                    anchors.centerIn: parent
                                    text: qsTr("서빙+호출용")
                                    font.pixelSize: 35
                                    font.family: font_noto_r.name
                                    color: color_dark_black
                                }
                                MouseArea{
                                    anchors.fill: parent
                                    onClicked: {
                                        supervisor.playSound('click');
                                        supervisor.writelog("[USER INPUT] INIT PAGE : SET ROBOT TYPE TO BOTH")
                                        supervisor.setSetting("setting","ROBOT_TYPE/type","BOTH");
                                        swipeview_wizard.currentIndex++;
                                    }
                                }
                            }

                            Rectangle{
                                width: 230
                                height: 110
                                radius: 60
                                color: "transparent"
                                border.width: 3
                                border.color : color_green
                                Text{
                                    anchors.centerIn: parent
                                    text: qsTr("서빙전용")
                                    font.pixelSize: 35
                                    font.family: font_noto_r.name
                                    color: color_dark_black
                                }
                                MouseArea{
                                    anchors.fill: parent
                                    onClicked: {
                                        supervisor.playSound('click');
                                        supervisor.writelog("[USER INPUT] INIT PAGE : SET ROBOT TYPE TO Serving")
                                        supervisor.setSetting("setting","ROBOT_TYPE/type","SERVING");
                                        swipeview_wizard.currentIndex++;
                                    }
                                }
                            }
                            Rectangle{
                                width: 230
                                height: 110
                                radius: 60
                                color: "transparent"
                                border.width: 3
                                border.color : color_green
                                Text{
                                    anchors.centerIn: parent
                                    text: qsTr("호출전용")
                                    font.pixelSize: 35
                                    font.family: font_noto_r.name
                                    color: color_dark_black
                                }
                                MouseArea{
                                    anchors.fill: parent
                                    onClicked: {
                                        supervisor.playSound('click');
                                        supervisor.writelog("[USER INPUT] INIT PAGE : SET ROBOT TYPE TO CALLING")
                                        supervisor.setSetting("setting","ROBOT_TYPE/type","CALLING");
                                        swipeview_wizard.currentIndex++;
                                    }
                                }
                            }
                            Rectangle{
                                width: 230
                                height: 110
                                radius: 60
                                color: "transparent"
                                border.width: 3
                                border.color : color_green
                                Text{
                                    anchors.centerIn: parent
                                    text: qsTr("퇴식전용")
                                    font.pixelSize: 35
                                    font.family: font_noto_r.name
                                    color: color_dark_black
                                }
                                MouseArea{
                                    anchors.fill: parent
                                    onClicked: {
                                        supervisor.playSound('click');
                                        supervisor.writelog("[USER INPUT] INIT PAGE : SET ROBOT TYPE TO CLEANING")
                                        supervisor.setSetting("setting","ROBOT_TYPE/type","CLEANING");
                                        swipeview_wizard.currentIndex++;
                                    }
                                }
                            }
                        }
                    }

                }

                Item{
                    id: wizard_name
                    function init(){

                    }
                    Column{
                        anchors.centerIn: parent
                        spacing:80
                        Grid{
                            columns:3
                            rows:3
                            horizontalItemAlignment: Grid.AlignHCenter
                            verticalItemAlignment: Grid.AlignVCenter
                            spacing: 40
                            anchors.horizontalCenter: parent.horizontalCenter
                            Text{
                                text: qsTr("로봇의 이름")
                                color: color_dark_black
                                font.pixelSize: 30
                                font.family: font_noto_b.name
                            }
                            Rectangle{
                                width: 2
                                height: 80
                                radius: 2
                                color: color_dark_black
                            }
                            TextField{
                                id: textfield_name
                                width: 400
                                height: 80
                                font.family: font_noto_r.name
                                font.pixelSize: 25
                                horizontalAlignment: TextField.AlignHCenter
                                text: supervisor.getSetting("setting","ROBOT_TYPE","model")
                                background: Rectangle{
                                    radius: 10
                                    border.width: 2
                                    border.color: color_dark_black
                                }

                                onFocusChanged: {
                                    keyboard.owner = textfield_name;
                                    textfield_name.selectAll();
                                    if(focus){
                                        keyboard.open();
                                    }else{
                                        textfield_name.select(0,0)
                                        keyboard.close();
                                    }
                                }
                            }
                            Text{
                                text: qsTr("로봇의 번호")
                                color: color_dark_black
                                font.pixelSize: 30
                                font.family: font_noto_b.name
                            }
                            Rectangle{
                                width: 2
                                height: 80
                                radius: 2
                                color: color_dark_black
                            }
                            ComboBox{
                                width: 400
                                height: 80
                                id: combobox_serialnum

                                background: Rectangle{
                                    radius: 10
                                    border.width: 2
                                    border.color: color_dark_black
                                }
                                contentItem: Text{
                                    anchors.centerIn: parent
                                    font.family: font_noto_r.name
                                    font.pixelSize: 25
                                    text:combobox_serialnum.displayText
                                    horizontalAlignment: Text.AlignHCenter
                                    verticalAlignment: Text.AlignVCenter
                                }
                                delegate: ItemDelegate{
                                    contentItem: Rectangle{
                                        width: parent.implicitWidth
                                        height: 60
                                        Text{
                                            anchors.centerIn: parent
                                            font.family: font_noto_r.name
                                            font.pixelSize: 20
                                            text:modelData
                                            horizontalAlignment: Text.AlignHCenter
                                            verticalAlignment: Text.AlignVCenter
                                        }
                                    }
                                }

                                currentIndex: parseInt(supervisor.getSetting("setting","ROBOT_TYPE","serial_num"))-1
                                model:[1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20]
                            }
                        }

                    }

                    Rectangle{
                        width: 230
                        height: 100
                        radius: 60
                        color: "transparent"
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: 50
                        anchors.left: parent.left
                        anchors.leftMargin: 50
                        border.width: 2
                        border.color: color_green
                        Text{
                            anchors.centerIn: parent
                            text: qsTr("이전")
                            font.pixelSize: 35
                            font.family: font_noto_r.name
                            color: color_dark_black
                        }
                        MouseArea{
                            anchors.fill: parent
                            onClicked: {
                                supervisor.playSound('click');
                                supervisor.writelog("[USER INPUT] INIT PAGE : PREV")
                                swipeview_wizard.currentIndex--;
                            }
                        }
                    }
                    Rectangle{
                        width: 230
                        height: 100
                        radius: 60
                        color: color_green
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: 50
                        anchors.right: parent.right
                        anchors.rightMargin: 50
                        Text{
                            anchors.centerIn: parent
                            text: qsTr("다음")
                            font.pixelSize: 35
                            font.family: font_noto_r.name
                            color: "white"
                        }
                        MouseArea{
                            anchors.fill: parent
                            onClicked: {
                                supervisor.playSound('click');
                                supervisor.setSetting("setting","ROBOT_TYPE/model",textfield_name.text);
                                supervisor.setSetting("setting","ROBOT_TYPE/serial_num",combobox_serialnum.currentText);
                                supervisor.writelog("[USER INPUT] INIT PAGE : NEXT")
                                swipeview_wizard.currentIndex++;
                            }
                        }
                    }
                }

                Item{
                    id: wizard_camera
                    function update(){
                        //카메라 대수에 따라 UI 업데이트
                        if(supervisor.getCameraNum() === 2){
                            print(supervisor.getCameraNum(),supervisor.getCameraSerial(left_id));
                            is_load = true;
                            if(is_switched){
                                cameraview_1.setCamera(left_id);
                                cameraview_2.setCamera(right_id);
                                text_camera_1.text = supervisor.getCameraSerial(left_id);
                                text_camera_2.text = supervisor.getCameraSerial(right_id);
                            }else{
                                if(supervisor.getLeftCamera()===supervisor.getCameraSerial(0)){
                                    left_id = 0;
                                    right_id = 1;
                                }else if(supervisor.getLeftCamera() === supervisor.getCameraSerial(1)){
                                    left_id = 1;
                                    right_id = 0;
                                }else{
                                    if(supervisor.getRightCamera()===supervisor.getCameraSerial(0)){
                                        left_id = 1;
                                        right_id = 0;
                                    }else if(supervisor.getRightCamera() === supervisor.getCameraSerial(1)){
                                        left_id = 0;
                                        right_id = 1;
                                    }else{
                                        left_id = 0;
                                        right_id = 1;
                                    }
                                }
                                cameraview_1.setCamera(left_id);
                                cameraview_2.setCamera(right_id);
                                text_camera_1.text = supervisor.getCameraSerial(left_id);
                                text_camera_2.text = supervisor.getCameraSerial(right_id);
                            }
                        }else{
                            is_load = false;
                            text_camera_1.text = "";
                            text_camera_2.text = "";
                            rect_no_camera.visible = true;
                        }
                    }
                    function init(){
//                        timer_load.start();
                    }
                    Component.onCompleted: {
//                        timer_load.start();
                    }
                    Component.onDestruction: {
                        timer_load.stop();
                    }

                    property bool is_load: false
                    property bool is_switched: false
                    property var left_id: 0
                    property var right_id: 1
                    Timer{
                        id: timer_load
                        interval: 500
                        repeat: true
                        running: swipeview_wizard.currentIndex === 3
                        onTriggered:{
                            //카메라 정보 요청
                            supervisor.requestCamera();
                            wizard_camera.update();
                        }
                    }
                    Column{
                        spacing: 10
                        anchors.top: parent.top
                        anchors.topMargin: 50 + statusbar.height
                        Text{
                            anchors.horizontalCenter: parent.horizontalCenter
                            color: color_dark_black
                            font.family: font_noto_r.name
                            font.pixelSize: 40
                            text: qsTr("카메라의 왼/오른쪽(로봇 기준)이 일치하도록 위치를 지정해주세요")
                        }
                        Rectangle{
                            width: 1280
                            height: 450
                            color: color_dark_navy
                            Row{
                                anchors.centerIn: parent
                                spacing: 20
                                Column{
                                    anchors.verticalCenter: parent.verticalCenter
                                    spacing: 30
                                    Text{
                                        id: text_left
                                        text: qsTr("왼쪽")
                                        color: "white"
                                        anchors.horizontalCenter: parent.horizontalCenter
                                        font.family: font_noto_b.name
                                        font.pixelSize: 30
//                                        color: color_dark_black
                                    }
                                    CameraView{
                                        id: cameraview_1
                                        width: 250
                                        height: 250
                                        anchors.horizontalCenter: parent.horizontalCenter
                                    }
                                    Rectangle{
                                        width: 350
                                        height: 50
                                        color: "white"
        //                                radius: 5
                                        Row{
                                            spacing: 10
                                            anchors.centerIn: parent
                                            Text{
                                                text: "Serial : "
                                                font.family: font_noto_r.name

                                            }
                                            Text{
                                                id: text_camera_1
                                                text: {
                                                    if(supervisor.getCameraNum() > 0){
                                                        supervisor.getCameraSerial(0);
                                                    }else{
                                                        ""
                                                    }
                                                }
                                                font.family: font_noto_r.name
                                            }
                                        }
                                    }
                                }
                                Rectangle{
                                    width: 150
                                    height: 100
                                    radius: 10
                                    anchors.verticalCenter: parent.verticalCenter
                                    color:"transparent"
                                    Row{
                                        spacing: 20
                                        anchors.centerIn: parent
                                        Image{
                                            source: "icon/joy_left.png"
                                            anchors.verticalCenter: parent.verticalCenter
                                            ColorOverlay{
                                                anchors.fill: parent
                                                source: parent
                                                color: "white"
                                            }
                                        }
                                        Text{
                                            anchors.verticalCenter: parent.verticalCenter
                                            text: qsTr("위치\n바꾸기")
                                            color: "white"
                                            horizontalAlignment: Text.AlignHCenter
                                            font.family: font_noto_r.name
                                            font.pixelSize: 25
                                        }
                                        Image{
                                            source: "icon/joy_right.png"
                                            anchors.verticalCenter: parent.verticalCenter
//                                            ColorOverlay{
//                                                anchors.fill: parent
//                                                source: parent
//                                                color: "white"
//                                            }
                                        }
                                    }

                                    MouseArea{
                                        anchors.fill: parent
                                        onClicked: {
                                            supervisor.playSound('click');
                                            supervisor.writelog("[USER INPUT] SETTING PAGE : CAMERA Position Switch")
                                            wizard_camera.is_switched = true;
                                            var temp_id = wizard_camera.left_id;
                                            wizard_camera.left_id = wizard_camera.right_id;
                                            wizard_camera.right_id = temp_id;
                                        }
                                    }
                                }
                                Column{
                                    anchors.verticalCenter: parent.verticalCenter
                                    spacing: 20
                                    Text{
                                        id: text_right
                                        text: qsTr("오른쪽")
                                        color: "white"
                                        anchors.horizontalCenter: parent.horizontalCenter
                                        font.family: font_noto_b.name
                                        font.pixelSize: 30
//                                        color: color_dark_black
                                    }
                                    CameraView{
                                        id: cameraview_2
                                        width: 250
                                        anchors.horizontalCenter: parent.horizontalCenter
                                        height: 250
                                    }
                                    Rectangle{
                                        width: 350
                                        height: 50
                                        color: "white"
                                        Row{
                                            spacing: 10
                                            anchors.centerIn: parent
                                            Text{
                                                text: "Serial : "
                                                font.family: font_noto_r.name
                                            }
                                            Text{
                                                id: text_camera_2
                                                text: {
                                                    if(supervisor.getCameraNum() > 0){
                                                        supervisor.getCameraSerial(1);
                                                    }else{
                                                        ""
                                                    }
                                                }
                                                font.family: font_noto_r.name
                                            }
                                        }
                                    }
                                }
                            }

                        }
                    }

                    Rectangle{
                        id: rect_no_camera
                        visible: false
                        anchors.centerIn: parent
                        width: 1280
                        height: 300
                        color: color_red
                        Text{
                            anchors.top: parent.top
                            anchors.topMargin: 30
                            font.pixelSize: 30
                            color: "white"
                            horizontalAlignment: Text.AlignHCenter
                            font.family: font_noto_b.name
                            text: qsTr("카메라를 찾을 수 없습니다\n건너뛰기를 누르시면 로봇이 제대로 동작하지 않습니다")
                            anchors.horizontalCenter: parent.horizontalCenter
                        }
                        Row{
                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.bottom: parent.bottom
                            anchors.bottomMargin: 30
                            spacing: 30
                            Rectangle{
                                width: 150
                                height: 80
                                radius: 20
                                Text{
                                    anchors.centerIn: parent
                                    font.family: font_noto_r.name
                                    font.pixelSize: 20
                                    text: qsTr("건너뛰기")

                                }
                                MouseArea{
                                    anchors.fill: parent
                                    onClicked:{
                                        supervisor.playSound('click');
                                        supervisor.writelog("[USER INPUT] INIT PAGE : PASS SETTING CAMERA");
                                        swipeview_wizard.currentIndex++;
                                    }
                                }
                            }
                        }
                    }

                    Rectangle{
                        width: 230
                        height: 100
                        radius: 60
                        color: "transparent"
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: 50
                        anchors.left: parent.left
                        anchors.leftMargin: 50
                        border.width: 2
                        border.color: color_green
                        Text{
                            anchors.centerIn: parent
                            text: qsTr("이전")
                            font.pixelSize: 35
                            font.family: font_noto_r.name
                            color: color_dark_black
                        }
                        MouseArea{
                            anchors.fill: parent
                            onClicked: {
                                supervisor.playSound('click');
                                supervisor.writelog("[USER INPUT] INIT PAGE : PREV")
                                swipeview_wizard.currentIndex--;
                            }
                        }
                    }
                    Rectangle{
                        width: 230
                        height: 100
                        radius: 60
                        color: color_green
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: 50
                        anchors.right: parent.right
                        anchors.rightMargin: 50
                        Text{
                            anchors.centerIn: parent
                            text: qsTr("다음")
                            font.pixelSize: 35
                            font.family: font_noto_r.name
                            color: "white"
                        }
                        MouseArea{
                            anchors.fill: parent
                            onClicked: {
                                supervisor.playSound('click');
                                if(!rect_no_camera.visible){
                                    supervisor.writelog("[USER INPUT] INIT PAGE : NEXT")
                                    supervisor.setCamera(text_camera_1.text,text_camera_2.text);
                                    swipeview_wizard.currentIndex++;
                                }
                            }
                        }
                    }
                }

                Item{
                    id: wizard_ip
                    Popup_wifi{
                        id: popup_wifi
                        closePolicy: Popup.NoAutoClose
                        onCancel:{
                            popup_wifi_pass.open();
                        }
                        onDone:{
                            popup_wifi.close();
                            swipeview_wizard.currentIndex++;
                            wizard_final.init();
                        }
                    }
                    Component.onCompleted: {
                        popup_wifi.open();
                    }

                    Popup{
                        id: popup_wifi_pass
                        anchors.centerIn: parent
                        width: 1280
                        height: 250
                        Rectangle{
                            anchors.fill: parent
                            Column{
                                anchors.centerIn: parent
                                spacing : 40
                                Text{
                                    text: qsTr("무선 네트워크가 설정되지 않았습니다")
                                    font.pixelSize: 40
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    font.family: font_noto_r.name
                                }
                                Row{
                                    spacing: 40
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    Item_buttons{
                                        type: "white_btn"
                                        width: 150
                                        height: 60
                                        text: qsTr("이전으로")
                                        onClicked:{
                                            supervisor.writelog("[USER INPUT] INIT PAGE : PREV")
                                            popup_wifi_pass.close();
                                            swipeview_wizard.currentIndex--;
                                        }
                                    }
                                    Item_buttons{
                                        type: "white_btn"
                                        width: 150
                                        height: 60
                                        text: qsTr("건너뛰기")
                                        onClicked:{
                                            supervisor.playSound('click');
                                            popup_wifi_pass.close();
                                            supervisor.writelog("[USER INPUT] INIT PAGE : SKIP WIFI SETTING");
                                            swipeview_wizard.currentIndex++;
                                        }
                                    }
                                }
                            }
                        }
                    }

                }


                Item{
                    id: wizard_final
                    function init(){
                        ani_wizard_final.start();
                        timer_2sec.start();
                    }

                    SequentialAnimation{
                        id:ani_wizard_final
                        NumberAnimation{
                            target: tnke
                            property: "opacity"
                            to: 1
                            from: 0
                            duration: 500
                        }
                    }

                    Timer{
                        id: timer_2sec
                        running: false
                        interval: 2000
                        onTriggered: {
                            init_mode = 3;
                            print("init mode = 3");
                        }
                    }

                    Text{
                        id: tnke
                        text: qsTr("초기 세팅이 완료되었습니다")
                        anchors.centerIn: parent
                        color: color_dark_black
                        font.pixelSize: 50
                        opacity: 0
                        font.family: font_noto_b.name
                    }
                }
            }
            MouseArea{
                id: area_debug
                width: 100
                height: 100
                anchors.right: parent.right
                anchors.bottom : parent.bottom
                z: 99
                property var password: 0
                onClicked: {
                    supervisor.playSound('click');
                    password++;
                    if(password > 4){
                        password = 0;
                        show_debug = true;
                    }
                }
            }
        }
    }

    //3. 맵을 찾을 수 없을 때
    Component{
        id: item_map
        Item{
            objectName: "item_map"
            anchors.fill: parent
            Component.onCompleted: {
                statusbar.visible = true;
                supervisor.setMotorLock(false);
            }
            function enable_usb(){
                btn_usb_load.enabled = true;
            }
            function disable_usb(){
                btn_usb_load.enabled = false;
            }
            Rectangle{
                anchors.fill: parent
                color: "#f4f4f4"
            }
            Timer{
                running: true
                interval: 500
                repeat: true
                onTriggered:{
                    if(supervisor.getIPCConnection()){
                        btn_slam_start.enabled = true;
                    }else{
                        btn_slam_start.enabled = false;
                    }
                }
            }

            Text{
                font.family: font_noto_r.name
                color: "#7e7e7e"
                horizontalAlignment: Text.AlignHCenter
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenterOffset: -100
                text: qsTr("맵 파일을 찾을 수 없습니다")
                font.pixelSize: 40
            }

            Row{
                spacing: 40
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 140
                anchors.horizontalCenter: parent.horizontalCenter
                Rectangle{
                    id: btn_slam_start
                    width: 230
                    height: 130
                    radius: 40
                    color: enabled?color_navy:color_mid_gray
                    Column{
                        spacing: 15
                        anchors.centerIn: parent
                        Image{
                            width: 40
                            height: 40
                            sourceSize.width: width
                            sourceSize.height: height
                            source:"icon/icon_add.png"
                            anchors.horizontalCenter: parent.horizontalCenter
                            ColorOverlay{
                                source: parent
                                anchors.fill: parent
                                color: "white"
                            }
                        }
                        Text{
                            text: qsTr("맵 새로만들기")
                            Component.onCompleted: {
                                scale = 1;
                                while(width*scale > 200){
                                    scale=scale-0.01;
                                }
                            }
                            anchors.horizontalCenter: parent.horizontalCenter
                            color: "white"
                            font.family: font_noto_r.name
                            font.pixelSize: 30
                            horizontalAlignment: Text.AlignHCenter
                        }
                    }
                    MouseArea{
                        anchors.fill: parent
                        onPressed:{
                            supervisor.playSound('click');
                            parent.color = color_mid_navy;
                        }
                        onReleased: {
                            supervisor.writelog("[INIT] MAPPING")
                            loadPage(pmapping);
                            parent.color = color_navy;
                        }
                    }
                }
                Rectangle{
                    width: 230
                    height: 130
                    radius: 40
                    color: enabled?color_navy:color_mid_gray
                    Column{
                        spacing: 15
                        anchors.centerIn: parent
                        Image{
                            width: 40
                            height: 40
                            sourceSize.width: width
                            sourceSize.height: height
                            source:"icon/icon_folder.png"
                            anchors.horizontalCenter: parent.horizontalCenter
                            ColorOverlay{
                                source: parent
                                anchors.fill: parent
                                color: "white"
                            }
                        }
                        Text{
                            text: qsTr("맵 불러오기")
                            Component.onCompleted: {
                                scale = 1;
                                while(width*scale > 200){
                                    scale=scale-0.01;
                                }
                            }
                            anchors.horizontalCenter: parent.horizontalCenter
                            color: "white"
                            font.family: font_noto_r.name
                            font.pixelSize: 30
                            horizontalAlignment: Text.AlignHCenter
                        }
                    }
                    MouseArea{
                        anchors.fill: parent
                        onPressed:{
                            supervisor.playSound('start');
                            parent.color = color_mid_navy;
                        }
                        onReleased: {
                            supervisor.writelog("[INIT] LOAD MAP LOCAL")
                            popup_map_list.open();
                            parent.color = color_navy;
                        }
                    }
                }
                Rectangle{
                    id: btn_usb_load
                    width: 230
                    height: 130
                    radius: 40
                    color: enabled?color_navy:color_mid_gray
                    enabled: supervisor.getusbsize()>0?true:false
                    Column{
                        spacing: 15
                        anchors.centerIn: parent
                        Image{
                            width: 40
                            height: 40
                            sourceSize.width: width
                            sourceSize.height: height
                            source:"icon/icon_usb.png"
                            anchors.horizontalCenter: parent.horizontalCenter
                            ColorOverlay{
                                source: parent
                                anchors.fill: parent
                                color: "white"
                            }
                        }
                        Text{
                            id: text_slam_pass
                            Component.onCompleted: {
                                scale = 1;
                                while(width*scale > 200){
                                    scale=scale-0.01;
                                }
                            }
                            color: "white"
                            anchors.horizontalCenter: parent.horizontalCenter
                            text: qsTr("USB에서 가져오기")
                            font.family: font_noto_r.name
                            font.pixelSize: 30
                        }
                    }
                    MouseArea{
                        anchors.fill: parent
                        onPressed:{
                            supervisor.playSound('click');
                            parent.color = color_gray;
                        }
                        onReleased: {
                            supervisor.writelog("[INIT] USB GET")
                            popup_usb_download.open();
                            parent.color = "transparent";
                        }
                    }
                }
                Rectangle{
                    id: btn_lcm_pass
                    width: 230
                    height: 130
                    radius: 30
                    color: "transparent"
                    border.width: 2
                    border.color: color_navy
                    visible: show_debug
                    Column{
                        spacing: 15
                        anchors.centerIn: parent
                        Image{
                            id: image_charge1
                            width: 40
                            height: 40
                            sourceSize.width: width
                            sourceSize.height: height
                            source:"icon/icon_remove.png"
                            anchors.horizontalCenter: parent.horizontalCenter
                            ColorOverlay{
                                source: parent
                                anchors.fill: parent
                                color: color_navy
                            }
                        }
                        Text{
                            text: qsTr("건너뛰기")
                            horizontalAlignment: Text.AlignHCenter
                            color: color_navy
                            anchors.horizontalCenter: parent.horizontalCenter
                            font.family: font_noto_r.name
                            font.pixelSize: 30
                        }
                    }
                    MouseArea{
                        anchors.fill: parent
                        onPressed:{
                            supervisor.playSound('click');
                            parent.color = color_gray;
                        }
                        onReleased: {

                            popup_notice.init();
                            popup_notice.style = "warning";
                            popup_notice.main_str = qsTr("초기화를 건너뛰겠습니까?")
                            popup_notice.sub_str = qsTr("초기화를 건너뜁니다 로봇이 제대로 동작하지 않을 수 있습니다\n맵 메뉴에서 위치초기화를 누르면 다시 처음 세팅화면으로 돌아옵니다")
                            popup_notice.addButton(qsTr("건너뛰기"));
                            popup_notice.open();
                            supervisor.writelog("[INIT] PASS IPC Connection")
                            parent.color = "transparent";
                        }
                    }
                }

            }

            MouseArea{
                id: area_debug
                width: 100
                height: 100
                anchors.right: parent.right
                anchors.bottom : parent.bottom
                z: 99
                property var password: 0
                onClicked: {
                    supervisor.playSound('click');
                    password++;
                    if(password > 4){
                        password = 0;
                        show_debug = true;
                    }
                }
            }
        }
    }

    //4. 로봇과 연결은 되었으나 init되지 않을 때
    Component{
        id: item_slam_init
        Item{
            objectName: "init_slam"
            anchors.fill: parent
            property int local_find_state: -1
            Component.onCompleted: {
                statusbar.visible = true;
            }
            Item_localization{
                anchors.fill: parent
                start_mode: true
                auto_init: false
                onConfirmed: {
                    supervisor.confirmLocalization();
                    update_timer.start();
                }
                onPassed: {
                    popup_notice.init();
                    popup_notice.style = "warning";
                    popup_notice.main_str = qsTr("초기화를 건너뛰겠습니까?")
                    popup_notice.sub_str = qsTr("초기화를 건너뜁니다 로봇이 제대로 동작하지 않을 수 있습니다\n맵 메뉴에서 위치초기화를 누르면 다시 처음 세팅화면으로 돌아옵니다")
                    popup_notice.addButton(qsTr("건너뛰기"));
                    popup_notice.open();
                }
            }
        }
    }

    //5. 로봇과 연결은 되었으나 init되지 않을 때
    Component{
        id: item_motor_init
        Item{
            objectName: "init_motor"
            anchors.fill: parent
            Component.onCompleted: {
                statusbar.visible = true;
                supervisor.setMotorLock(true);
            }
            Rectangle{
                anchors.fill: parent
                color: "#f4f4f4"
            }

            SequentialAnimation{
                id: ani_logo_up
                running: true
                ParallelAnimation{
                    NumberAnimation{
                        target: image_logo4;
                        property: "anchors.topMargin";
                        to: 100
                        duration: 500
                        easing.type: Easing.InCurve
                    }
                }
                ParallelAnimation{
                    NumberAnimation{
                        target: text_notice4;
                        property: "opacity";
                        to: 1
                        duration: 500
                        easing.type: Easing.InCurve
                    }
                }
            }

            Image{
                id: image_logo4
                width: 2245/6
                height: 1004/6
                sourceSize.width: 2245/6
                sourceSize.height: 1004/6
                anchors.top: parent.top
                anchors.topMargin: 200
                anchors.horizontalCenter: parent.horizontalCenter
                source: Qt.resolvedUrl("qrc:/image/rainbow3.png")
            }
            Text{
                id: text_notice4
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: image_logo4.bottom
                anchors.topMargin: 80
                opacity: 0
                horizontalAlignment: Text.AlignHCenter
                color: color_dark_gray
                font.family: font_noto_b.name
                text: qsTr("모터가 초기화되지 않았습니다.\n비상 스위치를 눌렀다가 풀어주세요.")
                font.pixelSize: 50
            }
            Rectangle{
                id: btn_slam_pass
                width: 188
                height: 100
                radius: 60
                color: "transparent"
                border.width: 3
                visible: show_debug
                border.color: "#e5e5e5"
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: text_notice4.bottom
                anchors.topMargin: 80
                Column{
                    spacing: 5
                    anchors.centerIn: parent
                    Image{
                        id: image_charge1
                        width: 30
                        height: 30
                        source:"icon/icon_testmoving.png"
                        anchors.horizontalCenter: parent.horizontalCenter
                        antialiasing: true
                        sourceSize.width: width
                        sourceSize.height: height
                        ColorOverlay{
                            anchors.fill: parent
                            source: parent
                            color: color_icon_gray
                        }
                    }
                    Text{
                        id: text_slam_pass
                        text: qsTr("넘어가기")
                        font.family: font_noto_r.name
                        font.pixelSize: 15
                    }
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        supervisor.playSound('click');
                        popup_notice.init();
                        popup_notice.style = "warning";
                        popup_notice.main_str = qsTr("초기화를 건너뛰겠습니까?")
                        popup_notice.sub_str = qsTr("초기화를 건너뜁니다 로봇이 제대로 동작하지 않을 수 있습니다\n맵 메뉴에서 위치초기화를 누르면 다시 처음 세팅화면으로 돌아옵니다")
                        popup_notice.addButton(qsTr("건너뛰기"));
                        popup_notice.open();
                    }
                }
            }
            MouseArea{
                id: area_debug
                width: 100
                height: 100
                anchors.right: parent.right
                anchors.bottom : parent.bottom
                z: 99
                property var password: 0
                onClicked: {
                    supervisor.playSound('click');
                    password++;
                    if(password > 4){
                        password = 0;
                        show_debug = true;
                    }
                }
            }
        }
    }

    Popup{
        id: popup_usb_download
        anchors.centerIn: parent
        width: 400
        height: 500
        leftPadding: 0
        topPadding: 0
        bottomPadding: 0
        rightPadding: 0
        background: Rectangle{
            color: "transparent"
        }
        property var index: 0
        property bool is_ui: false
        property bool is_slam: false
        property bool is_map: false
        property bool is_log: false
        property bool is_config: false
        property string set_name: ""
        onOpened:{
            timer_usb_new.start();

            model_usb_file_list.clear();
            for(var i=0; i<supervisor.getusbfilesize(); i++){
                model_usb_file_list.append({"name":supervisor.getusbfile(i)});
            }

            text_recent_file.text = supervisor.getusbrecentfile();
            if(text_recent_file.text == ""){
                notice_recent.visible = false;
                btn_recent_confirm.visible = false;
            }else{
                notice_recent.visible = true;
                btn_recent_confirm.visible = true;
            }
        }
        onClosed:{
            timer_usb_new.stop();
        }

        Rectangle{
            anchors.fill: parent
            Rectangle{
//                id: rect_1
                width: parent.width
                height: 50
                color: color_dark_navy
                Text{
                    anchors.centerIn: parent
                    font.family: font_noto_r.name
                    font.pixelSize: 15
                    color: "white"
                    text: {
                        if(popup_usb_download.index === 0)
                            qsTr("가져오실 파일 목록을 선택해주세요")
                        else if(popup_usb_download.index === 1)
                            qsTr("가져오실 목록을 선택해주세요")
                    }
                }
            }

            Column{
                anchors.centerIn: parent
                visible: popup_usb_download.index === 0
                spacing: 10
                Rectangle{
                    id: notice_recent
                    width: 200
                    height: 40
                    color: color_navy
                    anchors.horizontalCenter: parent.horizontalCenter
                    Text{
                        text: qsTr("가장 최신 파일")
                        anchors.centerIn: parent
                        font.family: font_noto_r.name
                        font.pixelSize: 15
                        color: "white"
                    }
                }
                Rectangle{
                    width: 280
                    radius: 10
                    anchors.horizontalCenter: parent.horizontalCenter
                    height: 50
                    color: color_light_gray
                    Text{
                        id: text_recent_file
                        anchors.centerIn: parent
                        font.family: font_noto_r.name
                        font.pixelSize: 15
                        text: ""
                    }
                }
                Rectangle{
                    id: btn_recent_confirm
                    visible: false
                    width: 100
                    radius: 5
                    anchors.horizontalCenter: parent.horizontalCenter
                    height: 40
                    border.width:1
                    color: "white"//color_light_gray
                    Text{
                        anchors.centerIn: parent
                        font.family: font_noto_r.name
                        font.pixelSize: 15
                        text: qsTr("확인")
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked:{
                            supervisor.playSound('click');
                            supervisor.writelog("[USER INPUT] GET RECENT USB FILE : "+supervisor.getusbrecentfile());
                            popup_usb_notice.mode = "extract_recent";
                            popup_usb_notice.open();
                        }
                    }
                }

                Rectangle{
                    width: 200
                    height: 40
                    color: color_navy
                    anchors.horizontalCenter: parent.horizontalCenter
                    Text{
                        text: qsTr("그 외 발견한 파일 목록")
                        anchors.centerIn: parent
                        font.family: font_noto_r.name
                        font.pixelSize: 15
                        color: "white"
                    }
                }
                Repeater{
                    model: ListModel{id:model_usb_file_list}
                    Rectangle{
                        width: 280
                        radius: 10
                        height: 50
                        color: color_light_gray
                        Text{
                            anchors.centerIn: parent
                            font.family: font_noto_r.name
                            font.pixelSize: 10
                            text: name
                        }
                        MouseArea{
                            anchors.fill: parent
                            onClicked: {
                                supervisor.playSound('click');
//                                popup_usb_download.index = 1;
//                                popup_usb_download.set_name = name;
                            }
                        }
                    }
                }
            }
            Column{
                anchors.centerIn: parent
                spacing: 10
                visible: popup_usb_download.index === 1
                Rectangle{
                    width: 280
                    radius: 10
                    height: 50
                    visible: false
                    color: popup_usb_download.is_ui?color_green:color_light_gray
                    Text{
                        anchors.centerIn: parent
                        font.family: font_noto_r.name
                        font.pixelSize: 15
                        text: "UI"
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            supervisor.playSound('click');
                            popup_usb_download.is_ui = !popup_usb_download.is_ui;
                        }
                    }
                }
                Rectangle{
                    width: 280
                    radius: 10
                    height: 50
                    visible: false
                    color: popup_usb_download.is_slam?color_green:color_light_gray
                    Text{
                        anchors.centerIn: parent
                        font.family: font_noto_r.name
                        font.pixelSize: 15
                        text: "SLAMNAV"
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            supervisor.playSound('click');
                            popup_usb_download.is_slam = !popup_usb_download.is_slam;
                        }
                    }
                }
                Rectangle{
                    width: 280
                    radius: 10
                    height: 50
                    color: popup_usb_download.is_config?color_green:color_light_gray
                    Text{
                        anchors.centerIn: parent
                        font.family: font_noto_r.name
                        font.pixelSize: 15
                        text: "robot_config"
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            supervisor.playSound('click');
                            popup_usb_download.is_config = !popup_usb_download.is_config;
                        }
                    }
                }
                Rectangle{
                    width: 280
                    radius: 10
                    height: 50
                    color: popup_usb_download.is_map?color_green:color_light_gray
                    Text{
                        anchors.centerIn: parent
                        font.family: font_noto_r.name
                        font.pixelSize: 15
                        text: "maps"
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            supervisor.playSound('click');
                            popup_usb_download.is_map = !popup_usb_download.is_map;
                        }
                    }
                }
                Rectangle{
                    width: 280
                    radius: 10
                    height: 50
                    color: popup_usb_download.is_log?color_green:color_light_gray
                    Text{
                        anchors.centerIn: parent
                        font.family: font_noto_r.name
                        font.pixelSize: 15
                        text: "Log"
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            supervisor.playSound('click');
                            popup_usb_download.is_log = !popup_usb_download.is_log;
                        }
                    }
                }
            }
            Rectangle{
                width: 250
                radius: 10
                height: 50
                color: "black"
                anchors.bottom: parent.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottomMargin: 30
                visible: popup_usb_download.index === 1
                Text{
                    anchors.centerIn: parent
                    font.family: font_noto_r.name
                    font.pixelSize: 15
                    color:"white"
                    text: qsTr("확인")
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        supervisor.playSound('click');
                        popup_usb_notice.setProperty("compress",popup_usb_download.set_name,popup_usb_download.is_ui,popup_usb_download.is_slam,popup_usb_download.is_config,popup_usb_download.is_map,popup_usb_download.is_log);
                        popup_usb_download.close();
                        popup_usb_notice.open();
                    }
                }
            }

        }
        Timer{
            id: timer_usb_new
            interval: 500
            running: false
            repeat: true
            onTriggered: {
                if(supervisor.getusbsize() > 0){
                }else{
                }
            }
        }
    }

    Popup{
        id: popup_usb_notice
        anchors.centerIn: parent
        width: 400
        height: 300
        leftPadding: 0
        topPadding: 0
        bottomPadding: 0
        rightPadding: 0
        background: Rectangle{
            anchors.fill: parent
            color : "transparent"
        }
        function setProperty(mo,na,ui,slam,config,map,log){
            mode = mo;
            name = na;
            is_ui = ui;
            is_slam = slam;
            is_map = map;
            is_log = log;
            is_config = config;
        }

        property bool is_ui: false
        property bool is_slam: false
        property bool is_map: false
        property bool is_log: false
        property bool is_config: false
        property string name: "Desktop"
        property string mode: "compress";
        property bool is_new: true
        Timer{
            id: timer_usb_check
            running: false
            repeat: true
            interval: 300
            onTriggered: {
                if(popup_usb_notice.is_new){
                    popup_usb_notice.is_new = false;
                    if(popup_usb_notice.mode == "compress"){
                        supervisor.usbsave(popup_usb_notice.name, popup_usb_notice.is_ui, popup_usb_notice.is_slam, popup_usb_notice.is_config, popup_usb_notice.is_map, popup_usb_notice.is_log);
                    }else if(popup_usb_notice.mode == "extract_recent"){
                        supervisor.readusbrecentfile();
                    }else if(popup_usb_notice.mode == "extract"){

                    }
                }
                if(supervisor.getzipstate() === 1){
                    if(popup_usb_notice.mode== "compress"){
                        text_usb_state.text = qsTr("파일을 압축하여 저장 중..");
                    }else{
                        text_usb_state.text = qsTr("파일을 가져오는 중..");
                    }
                }else if(supervisor.getzipstate() === 2){
                    if(popup_usb_notice.mode== "compress"){
                        text_usb_state.text = qsTr("저장에 성공하였습니다");
                    }else{
                        btn_usb_confirm.visible = true;
                        //text_usb_state.text = qsTr("파일을 성공적으로 가져왔습니다\n확인을 누르시면 업데이트를 진행합니다");
                        text_usb_state.text = qsTr("파일을 성공적으로 가져왔습니다\n확인을 눌러주세요");
                    }

                }else if(supervisor.getzipstate() === 3){
                    if(popup_usb_notice.mode== "compress"){
                        text_usb_state.text = qsTr("저장에 성공하였지만 일부 과정에서 에러가 발생했습니다");
                    }else{
                        text_usb_state.text = qsTr("파일을 성공적으로 가져왔습니다만 일부 과정에서 에러가 발생했습니다\n확인을 누르시면 업데이트를 진행합니다");
                        btn_usb_confirm.visible = true;
                    }
                    model_usb_error.clear();
                    for(var i=0; i<supervisor.getusberrorsize(); i++){
                        model_usb_error.append({"error":supervisor.getusberror(i)});
                    }
                }else if(supervisor.getzipstate() === 4){
                    if(popup_usb_notice.mode== "compress"){
                        text_usb_state.text = qsTr("저장에 실패했습니다");
                    }else{
                        text_usb_state.text = qsTr("파일을 가져오지 못했습니다");
                    }
                    model_usb_error.clear();
                    for(var i=0; i<supervisor.getusberrorsize(); i++){
                        model_usb_error.append({"error":supervisor.getusberror(i)});
                    }
                }else{
                    print(supervisor.getzipstate());
                    text_usb_state.text = qsTr("잠시만 기다려주세요");
                }
            }
        }
        onOpened:{
            timer_usb_check.start();
            model_usb_error.clear();
            btn_usb_confirm.visible = false;
            text_usb_state.text = qsTr("잠시만 기다려주세요");
            is_new = true;
        }
        onClosed: {
            timer_usb_check.stop();
        }
        Rectangle{
            width: parent.width
            height: parent.height
            radius: 10
            color: color_dark_navy
            Column{
                anchors.centerIn: parent
                spacing: 10
                Text{
                    id: text_usb_state
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.family: font_noto_r.name
                    color: "white"
                    font.pixelSize: 20
                    horizontalAlignment: Text.AlignHCenter
                    text:qsTr("잠시만 기다려주세요")
                }
                Repeater{
                    model: ListModel{id:model_usb_error}
                    Text{
                        anchors.horizontalCenter: parent.horizontalCenter
                        font.family: font_noto_r.name
                        font.pixelSize: 10
                        color: color_red
                        horizontalAlignment: Text.AlignHCenter
                        text:error
                    }
                }

                Rectangle{
                    id: btn_usb_confirm
                    //visible: false
                    visible: true
                    anchors.horizontalCenter: parent.horizontalCenter
                    width: 100
                    height: 50
                    radius: 5
                    border.width: 1
                    Text{
                        anchors.centerIn: parent
                        font.family:font_noto_r.name
                        color: color_dark_navy
                        font.pixelSize: 15
                        horizontalAlignment: Text.AlignHCenter
                        text:qsTr("확 인")
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked:{
                            supervisor.playSound('click');
                            if(popup_usb_notice.mode== "compress"){
                                //창 닫기
                                //popup_usb_notice.visible = false;
                                //popup_usb_download.visible = false;
                                popup_usb_notice.close();
                                popup_usb_download.close();
                            }else{
                                //supervisor.updateUSB();
                                //popup_usb_notice.visible = false;
                                //popup_usb_download.visible = false;
                                popup_usb_notice.close();
                                popup_usb_download.close();
                            }
                        }
                    }
                }
            }
        }
    }

    Popup_map_list{
        id: popup_map_list
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Timer{
        id:timer_motor_init
        running: false
        interval: 500
        onTriggered: {
            supervisor.writelog("[UI] PageInit : Motor Failed -> motorInit")
            loader_init.sourceComponent = item_motor_init;
        }
    }

    Timer{
        id: update_timer
        interval: 500
        running: start
        repeat: true
        onTriggered: {
            if(init_mode == 0){
                init_mode = 1;
            }else if(init_mode == 1){
                //=============================== Init Check 1 : IPC ==============================//
                if(testMode){
                    supervisor.writelog("[INIT] IPC Connection Check : Success(DEBUG)");
                    init_mode = 2;
                }else{
                    if(supervisor.getIPCConnection()){
                        supervisor.writelog("[INIT] IPC Connection Check : Success");
                        init_mode = 2;
                    }else if(loader_init.item.objectName != "item_ipc"){
                        loader_init.sourceComponent = item_ipc;
                        supervisor.writelog("[INIT] IPC Connection Check : Failed");
                    }
                }
            }
            if(init_mode == 2){
                //========================== Init Check 2 : Robot Config ==============================//
                if(supervisor.checkINI() && loader_init.item.objectName != "item_robot_config"){
                    supervisor.writelog("[INIT] Robot_config Check : Success");
                    init_mode = 3;
                }else{
                    if(loader_init.item.objectName != "item_robot_config"){
                        loader_init.sourceComponent = item_robot_config
                        supervisor.writelog("[INIT] Robot_config Check : Failed");
                    }
                }
            }
            if(init_mode == 3){
                //=============================== Init Check 3 : 맵 확인 ==============================//
                var map_name = supervisor.getMapname();
                //annotation과 map 존재여부 확인
                if(supervisor.isAvailableAnnotation() && supervisor.isLoadMap()){
                    //이미 설정확인된 맵이 존재한다면 다음으로 넘어감
                    supervisor.writelog("[INIT] Map Check : Success");
                    init_mode = 4;
                }else{
                    //annotation, map 둘 중 하나라도 없으면 안내페이지 표시
                    if(loader_init.item.objectName != "item_map"){
                        supervisor.writelog("[INIT] Map Check : Failed (" + map_name+")");
                        loader_init.sourceComponent = item_map
                    }else{
                        //USB연결 확인
                        if(supervisor.getusbsize() > 0){
                            loader_init.item.enable_usb();
                        }else{
                            loader_init.item.disable_usb();
                        }

                    }
                }
            }
            if(init_mode == 4){
                //======================= Init Check 4 : 로봇 상태 확인(Charging. Localization) =========================//
                if(supervisor.getChargeConnectStatus() === 1){
                    supervisor.writelog("[INIT] Charging Detected");
                }else if(loader_init.item.objectName != "init_slam"){
                    supervisor.writelog("[INIT] Localization Check : Failed");
                    loader_init.sourceComponent = item_slam_init
                }else if(supervisor.getIPCConnection() && supervisor.getLocalizationConfirm()){
                    init_mode = 5;
                    supervisor.writelog("[INIT] Localization Check : Success");
                }else{
//                    print("check localization",supervisor.getLocalizationConfirm());
                }
            }
            if(init_mode == 5){
                //=============================== Init Check 5 : 로봇 상태 확인(Motor) ==============================//

                if(supervisor.getChargeConnectStatus() === 1){
                    supervisor.writelog("[INIT] Charging Detected");
                }else if(supervisor.getIPCConnection() && supervisor.getMotorState() === 1){
                    timer_motor_init.stop();
                    supervisor.writelog("[INIT] Motor Check : Success");
                    init_mode = 6;
                    update_timer.stop();
                    supervisor.stateInit();
                    loadPage(pkitchen);
                }else{
                    if(loader_init.item.objectName != "init_motor"){
                        timer_motor_init.start();
                    }
                }
            }
        }
    }
    Tool_Keyboard{
        id: keyboard
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
                if(loader_page.item.objectName == "page_moving" || loader_page.item.objectName == "page_moving_custom"){
                    loadPage(pinit);
                }

                popup_notice.close();
            }else if(cur_btn === qsTr("위치초기화")){
                supervisor.writelog("[UI] PopupNotice : Local Init");
                if(loader_page.item.objectName == "page_annotation"){
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
            }else if(cur_btn === qsTr("재시작")){
                supervisor.writelog("[UI] PopupNotice : Restart");
                supervisor.programRestart();
                popup_notice.close();
            }else if(cur_btn === qsTr("종 료")){
                supervisor.writelog("[UI] PopupNotice : Terminate");
                supervisor.programExit();
                popup_notice.close();
            }else if(cur_btn === qsTr("디버그모드 해제")){
                supervisor.writelog("[UI] PopupNotice : Debug Mode off");
                loadPage(pinit);
                supervisor.resetLocalization();
                supervisor.stateInit();
                popup_notice.close();
            }else if(cur_btn === qsTr("건너뛰기")){
                supervisor.writelog("[INIT] Debug Mode On");
                supervisor.passInit();
                loadPage(pkitchen);
                popup_notice.close();
            }else if(cur_btn === qsTr("퇴식모드 사용")){
                supervisor.saveAnnotation(supervisor.getMapname());
                supervisor.setSetting("setting","ROBOT_TYPE/type","CLEANING");
                supervisor.readSetting();
                loader_page.item.readSetting();
                loader_page.item.setAnnotLocation();
                popup_notice.close();
            }else if(cur_btn === qsTr("퇴식모드 미사용")){
                supervisor.setSetting("setting","ROBOT_TYPE/type","BOTH");
                supervisor.readSetting();
                loader_page.item.readSetting();
                popup_notice.close();
            }
        }
    }

}
