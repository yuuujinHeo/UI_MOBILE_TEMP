import QtQuick 2.12
import QtQuick.Controls 2.12
import "."
import io.qt.Supervisor 1.0
import QtMultimedia 5.12

Item {
    id: page_pickup
    objectName: "page_pickup"
    width: 1280
    height: 800

    property string pos: "1번"
    property bool pickup_1: false
    property bool pickup_2: false
    property bool pickup_3: false
    property bool blink_1: false
    property bool blink_2: false
    property bool blink_3: false
    property var tray_num: parseInt(supervisor.getSetting("setting","ROBOT_TYPE","tray_num"))
    property int clickCount: 0 // 클릭 횟수 저장

    function init(){
        supervisor.writelog("[QML-Pickup] PICKUP PAGE Init");
        pickup_1 = false;
        pickup_2 = false;
        pickup_3 = false;
        text_mention.visible = true;
        text_mention3.visible = true;
        target_pos.visible = true;
        btn_confirm.visible = true;
        text_hello.visible = false;
        timer_hello.stop();

        if(!supervisor.isPatrolPage())
            supervisor.playVoice("pickup");

        statusbar.visible = false;
        tray_num = parseInt(supervisor.getSetting("setting","ROBOT_TYPE","tray_num"));
        if(tray_num === 1){
            rect_tray_1.visible = true;
            rect_tray_2.visible = false;
            rect_tray_3.visible = false;
        }else if(tray_num === 2){
            rect_tray_1.visible = true;
            rect_tray_2.visible = true;
            rect_tray_3.visible = false;
        }else{
            rect_tray_1.visible = true;
            rect_tray_2.visible = true;
            rect_tray_3.visible = true;
        }
    }

    function show_all(){
        pos = "";
        pickup_1 = true;
        pickup_2 = true;
        pickup_3 = true;
    }

    function set_tray(){
        var trays = supervisor.getPickuptrays();
        if(trays.length === parseInt(supervisor.getSetting("setting","ROBOT_TYPE","tray_num"))){
            pos = "";
            pickup_1 = true;
            pickup_2 = true;
            pickup_3 = true;
        }else{
            var tempstr = "";
            for(var i=0; i<trays.length; i++){
                if(tempstr === ""){
                    tempstr = Number(trays[i])+qsTr("번");
                }else{
                    tempstr += qsTr("과 ") + Number(trays[i])+qsTr("번");
                }

                if(trays[i] === 1){
                    pickup_1 = true;
                }else if(trays[i] === 2){
                    pickup_2 = true;
                }else if(trays[i] === 3){
                    pickup_3 = true;
                }
            }
            pos = tempstr;
        }
    }

    Timer{
        repeat: true
        interval: 1000
        running: true
        onTriggered: {
            if(pickup_1){
                if(blink_1) blink_1 = false;
                else blink_1 = true;
            }else{
                blink_1 = false;
            }

            if(pickup_2){
                if(blink_2) blink_2 = false;
                else blink_2 = true;
            }else{
                blink_2 = false;
            }

            if(pickup_3){
                if(blink_3) blink_3 = false;
                else blink_3 = true;
            }else{
                blink_3 = false;
            }
        }
    }

    Rectangle{
        id: rect_background
        anchors.fill: parent
        color: "#282828"
    }

    Row{
        id: row_ee
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: 100
        spacing: 100
        Image{
            id: image_robot
            source: "image/robot_pickup.png"
            width: 221
            height: 452
            sourceSize.width: width
            sourceSize.height: height
            anchors.verticalCenter: parent.verticalCenter

            Rectangle{
                id: rect_tray_1
                color: blink_1?"#12d27c":"#525252"
                width: 187
                height: 50
                anchors.top: parent.top
                anchors.topMargin: 339-row_ee.y-parent.y
                anchors.horizontalCenter: image_robot.horizontalCenter
                Text{
                    anchors.centerIn: parent
                    color:"white"
                    text:"1"
                    font.family: font_noto_r.name
                    font.pixelSize: 15
                }
            }
            Rectangle{
                id: rect_tray_2
                color: blink_2?"#12d27c":"#525252"
                width: 187
                height: 50
                anchors.top: rect_tray_1.bottom
                anchors.topMargin: 45
                anchors.horizontalCenter: image_robot.horizontalCenter
                Text{
                    anchors.centerIn: parent
                    color:"white"
                    text:"2"
                    font.family: font_noto_r.name
                    font.pixelSize: 15
                }
            }
            Rectangle{
                id: rect_tray_3
                color: blink_3?"#12d27c":"#525252"
                width: 187
                height: 50
                anchors.top: rect_tray_2.bottom
                anchors.topMargin: 43
                anchors.horizontalCenter: image_robot.horizontalCenter
                Text{
                    anchors.centerIn: parent
                    color:"white"
                    text:"3"
                    font.family: font_noto_r.name
                    font.pixelSize: 15
                }
            }
            Rectangle{
                id: btn_confirm2 // 퇴식 버튼
                width: 200
                height: 50
                radius: 5
                visible: supervisor.isFinalLocation() && supervisor.getLocationNum("Cleaning")>0
                //opacity: 0 // 투명하게 설정하여 보이지 않도록 함
                border.color: color_gray
                border.width: 2
                anchors.top: rect_tray_3.bottom
                anchors.topMargin: 10
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: parent.anchors
                color:color_green

                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        clickCount += 1;
                        if (clickCount == 2) {
                            supervisor.playSound('click');
                            supervisor.writelog("[USER INPUT] PICKUP CONFIRM2 clicked");
                            supervisor.playVoice("thanks");
                            column_pickup.visible = false;
                            text_mention.visible = false;
                            text_mention3.visible = false;
                            target_pos.visible = false;
                            btn_confirm.visible = false;
                            text_hello.visible = true;
                            timer_hello2.start();
                        }
                    }
                }

            }

        }
        Column{
            id: column_pickup
            anchors.top: parent.top
            Text{
                id: target_pos
                text: pos + qsTr(" 트레이 <font color=\"white\">의</font>")
                font.pixelSize: 70
                font.bold: true
                font.family: font_noto_b.name
                color: "#12d27c"
            }
            Text{
                id: text_mention
                text: qsTr("제품을 수령해주세요")
                font.pixelSize: 70
                font.family: font_noto_b.name
                color: "white"
            }
            Rectangle{
                color:"transparent"
                width: parent.width
                height: 10
            }
            Text{
                id: text_mention3
                text: qsTr("수령 후 아래 <font color=\"#12d27c\">확인버튼</font>을 눌러주세요")
                font.pixelSize: 40
                font.family: font_noto_b.name
                color: "white"
            }
            Rectangle{
                color:"transparent"
                width: parent.width
                height: 50
            }
            Row{
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: 50

                Rectangle{
                    id: btn_confirm
                    width: 320
                    height: 120
                    radius: 60
                    border.color: color_gray
                    border.width: 2
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 120
                            height: 120
                            color: "transparent"
                            Image{
                                anchors.centerIn: parent
                                source:"icon/icon_yes.png"
                                width: 80
                                height: 80
                                sourceSize.width: width
                                sourceSize.height: height
                            }
                        }
                        Rectangle{
                            width: 200
                            height: 120
                            color: "transparent"
                            Text{
                                anchors.centerIn: parent
                                text: qsTr("확인")
                                font.family: font_noto_b.name
                                font.pixelSize: 45
                                color: color_green
                            }
                        }
                    }

                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            supervisor.playSound('click');
                            supervisor.writelog("[USER INPUT] PICKUP CONFIRM clicked");
                            supervisor.playVoice("thanks");
                            column_pickup.visible = false;
                            text_mention.visible = false;
                            text_mention3.visible = false;
                            target_pos.visible = false;
                            btn_confirm.visible = false;
                            text_hello.visible = true;
                            timer_hello.start();
                        }
                    }
                }


            }
        }
        Text{
            id: text_hello
            text:qsTr("감사합니다")
            visible: false
            font.pixelSize: 80
            font.family: font_noto_b.name
            color: "white"
            anchors.verticalCenter: image_robot.verticalCenter
        }
    }
    MouseArea{
        id: area_debug
        width: 150
        height: 150
        anchors.right: parent.right
        anchors.bottom : parent.bottom
        z: 99
        property int password: 0
        onClicked: {
            supervisor.playSound('click');
            password++;
            if(password > 4){
                password = 0;
                supervisor.moveStop();
                supervisor.writelog("[QML-Pickup] PagePickup : Debug Pass -> PageKitchen");
                loadPage(pkitchen);
            }
        }
    }


    Timer{
        id: timer_hello
        interval: 1500
        running: false
        repeat: false
        onTriggered: {
            supervisor.confirmPickup("");
            supervisor.writelog("[QML-Pickup] PICKUP PAGE -> Move to Next");
        }
    }
    Timer{
        id: timer_hello2
        interval: 1500
        //running: false
        running: clickCount > 0
        repeat: false
        onTriggered: {
            supervisor.confirmPickup("Cleaning");
            supervisor.writelog("[QML-Pickup] PICKUP PAGE2222222 -> Move to Next");
            clickCount = 0; // 시간 내에 두 번 클릭하지 않으면 클릭 횟수 초기화
        }
    }
}
