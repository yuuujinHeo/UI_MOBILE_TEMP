import QtQuick 2.12
import QtQuick.Controls 2.12
import "."
import io.qt.Supervisor 1.0
import QtMultimedia 5.12
Item {
    id: page_charge
    objectName: "page_charge"
    width: 1280
    height: 800

    property bool is_init: false
    property int password: 0
    property bool is_charging: false
    property double battery: 0
    property string robotName: "test"
    property date curDate: new Date()
    property string curTime: curDate.toLocaleTimeString()
    onBatteryChanged: {
        if(battery == 100){
            timer_bat.stop();
            text_mention.text = qsTr("충전이 완료되었습니다")
            image_battery.source =  "image/image_battery_4.png"
        }else if(!timer_bat.running){
            if(supervisor.getChargeConnectStatus()){
                text_mention.text = qsTr("충전 케이블이 연결되었습니다")
            }else if(supervisor.getChargeStatus() === 0){
                text_mention.text = qsTr("충전 케이블을 연결해 주세요")
            }else{
                text_mention.text = qsTr("충전 중입니다")
                timer_bat.start();
            }
        }
    }

    Component.onCompleted: {
        statusbar.visible = true;
//        init();
    }

    function setInit(){
        is_init = true;
    }

    function init(){
        is_charging = false;
        battery = supervisor.getBattery().toFixed(0);
        if(robot_battery > 90){
            image_battery.source = "image/image_battery_4.png"
        }else if(robot_battery > 60){
            image_battery.source = "image/image_battery_3.png"
        }else if(robot_battery > 30){
            image_battery.source = "image/image_battery_2.png"
        }else{
            image_battery.source = "image/image_battery_1.png"
        }
        timer_bat.stop();
        text_mention.text = qsTr("충전 케이블을 연결해 주세요")
    }

    Rectangle{
        id: rect_background
        anchors.fill: parent
        color: "#282828"
    }
    Image{
        id: image_battery
        source: "image/image_battery_1.png"
        width: 1398/3
        height: 916/3.5
        sourceSize.width: width
        sourceSize.height: height
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 250
    }
    Text{
        id: text_bat
        visible: false
        text: battery + " %"
        font.pixelSize: 50
        color: "white"
        font.family: font_noto_b.name
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top : image_battery.bottom
    }

    Timer{
        repeat: true
        interval: 500
        running: true
        onTriggered: {
            if(supervisor.getChargeStatus()){
                if(!is_charging){
                    timer_bat.start();
                    supervisor.playVoice("charging");
                    is_charging = true;
                }
                text_mention.text = qsTr("충전 중입니다")
            }else if(supervisor.getChargeConnectStatus()){
                text_mention.text = qsTr("충전 케이블이 연결되었습니다")
            }else{
                if(is_charging){
                    init();
                    supervisor.playVoice("stop_charging");
//                    if(is_init){
//                        is_init = false;
//                        loadPage(pinit);
//                    }
                }
            }

            battery = supervisor.getBattery().toFixed(2);

            if(popup_question.visible){
                if(supervisor.getIPCConnection() && supervisor.getStateMoving() !== 0){
                    text_quest.text = qsTr("대기 장소로 이동<font color=\"white\">하시겠습니까?</font>")
                    btn_yes.visible = true;
                    btn_no.visible = true;
                    area_cancel3.enabled = false;
                }else if(supervisor.getChargeConnectStatus()){
                    text_quest.text = qsTr("충전 케이블을 분리해주세요");
                    btn_yes.visible = false;
                    btn_no.visible = false;
                    area_cancel3.enabled = true;
                }else if(supervisor.getEmoStatus()){
                    text_quest.text = qsTr("비상스위치를 풀어주세요");
                    btn_yes.visible = false;
                    btn_no.visible = false;
                    area_cancel3.enabled = true;
                }else{
                    text_quest.text = qsTr("로봇이 준비상태가 아닙니다");
                    btn_yes.visible = false;
                    btn_no.visible = false;
                    area_cancel3.enabled = true;
                }
            }
        }
    }
    Text{
        id: text_mention
        text: qsTr("충전 중 입니다")
        font.pixelSize: 50
        color: "white"
        font.family: font_noto_b.name
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top : text_bat.bottom
        anchors.topMargin: 30
    }
    Text{
        id: text_debug
        text: battery
        visible:false
        font.pixelSize: 20
        color: "white"
        font.family: font_noto_b.name
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top : text_mention.bottom
        anchors.topMargin: 20
    }
    Timer{
        id: timer_bat
        running: true
        interval: 1000
        repeat: true
        onTriggered: {
            if(image_battery.source == "qrc:/image/image_battery_1.png"){
                image_battery.source = "qrc:/image/image_battery_2.png";
            }else if(image_battery.source == "qrc:/image/image_battery_2.png"){
                image_battery.source = "qrc:/image/image_battery_3.png";
            }else if(image_battery.source == "qrc:/image/image_battery_3.png"){
                image_battery.source = "qrc:/image/image_battery_4.png";
            }else{
                image_battery.source = "qrc:/image/image_battery_1.png";
            }
        }
    }

    MouseArea{
        anchors.fill: parent
        onClicked: {
            supervisor.playSound('click');
            timer_bat.stop();
            popup_question.visible = true;
        }
    }



    Item{
        id: popup_question
        width: parent.width
        height: parent.height
        anchors.centerIn: parent
        visible: false
        Component.onCompleted: {
            if(supervisor.getIPCConnection() && supervisor.getStateMoving() !== 0){
                text_quest.text = qsTr("대기 장소로 이동<font color=\"white\">하시겠습니까?</font>");
                btn_yes.visible = true;
                btn_no.visible = true;
                area_cancel3.enabled = false;
            }else if(supervisor.getChargeConnectStatus()){
                text_quest.text = qsTr("충전 케이블을 분리해주세요");
                btn_yes.visible = false;
                btn_no.visible = false;
                area_cancel3.enabled = true;
            }else if(supervisor.getEmoStatus()){
                text_quest.text = qsTr("비상스위치를 풀어주세요");
                btn_yes.visible = false;
                btn_no.visible = false;
                area_cancel3.enabled = true;
            }else{
                supervisor.stateInit();
                loadPage(pkitchen);
//                text_quest.text = "로봇이 준비상태가 아닙니다";
//                btn_yes.visible = false;
//                btn_no.visible = false;
//                area_cancel3.enabled = true;
            }
        }

        Rectangle{
            anchors.fill: parent
            color: "#282828"
            opacity: 0.8
        }
        Column{
            anchors.centerIn: parent
            spacing: 50
            Image{
                id: image_location
                source:"icon/icon_plug.png"
                width: 160
                height: 160
                sourceSize.width: width
                sourceSize.height: height
                anchors.horizontalCenter: parent.horizontalCenter
            }
            Text{
                id: text_quest
                anchors.horizontalCenter: parent.horizontalCenter
                font.family: font_noto_b.name
                font.pixelSize: 40
                color: "#12d27c"
                text: qsTr("대기 장소로 이동<font color=\"white\">하시겠습니까?</font>")
            }
            Row{
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: 50
                Rectangle{
                    id: btn_no
                    width: 250
                    height: 90
                    radius: 20
                    color: "#d0d0d0"
                    Image{
                        id: image_no
                        width: 50
                        height: 50
                        sourceSize.width: width
                        sourceSize.height: height
                        source: "icon/btn_no.png"
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.leftMargin: 20
                    }
                    Text{
                        id:text_nono
                        text:qsTr("아니오")
                        font.family: font_noto_b.name
                        font.pixelSize: 30
                        color:"#282828"
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: image_no.right
                        anchors.leftMargin : (parent.width - image_no.x - image_no.width)/2 - text_nono.width/2
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            supervisor.playSound('click');;
                            timer_bat.start();
                            popup_question.visible = false;
                        }
                    }
                }
                Rectangle{
                    id: btn_yes
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
                    Image{
                        id: image_yes
                        width: 50
                        height: 50
                        sourceSize.width: width
                        sourceSize.height: height
                        source: "icon/icon_yes.png"
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.leftMargin: 20
                    }
                    Text{
                        text:qsTr("네")
                        font.family: font_noto_b.name
                        font.pixelSize: 30
                        color:"#282828"
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: image_yes.right
                        anchors.leftMargin : (parent.width - image_yes.x - image_yes.width)/2 - width/2
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            supervisor.playSound('click');;
                            supervisor.moveToWait();
                            popup_question.visible = false;
                        }
                    }
                }

            }

        }
        MouseArea{
            id: area_cancel3
            anchors.fill: parent
            enabled: false
            onClicked: {
                supervisor.playSound('click');
                timer_bat.start();
                popup_question.visible = false;

            }
        }
        MouseArea{
            id: area_debug
            width: 100
            height: 100
            anchors.right: parent.right
            anchors.bottom : parent.bottom
            z: 99
            onClicked: {
                supervisor.playSound('click');
                password++;
                print(password);
                if(password > 4){
                    password = 0;
                    supervisor.writelog("[UI] PageCharge : Debug Pass -> PageKitchen");
                    supervisor.passInit();
                    loadPage(pkitchen);
                }
            }
        }
    }
}
