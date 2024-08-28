import QtQuick 2.12
import QtQuick.Controls 2.12
import "."
import io.qt.Supervisor 1.0
import QtMultimedia 5.12

Item {
    id: page_pickup_calling
    objectName: "page_pickup_calling"
    width: 1280
    height: 800

    property int type: 0
    property int clickCount: 0 // 클릭 횟수 저장

    function init(){
        if(type == 0){//부르셨나요?
            target_pos2.visible = false;
        }else if(type == 1){//다 드신 그릇은
            target_pos2.visible = true;
        }
        text_mention.visible = true;
        target_pos.visible = true;
        btn_confirm.visible = true;
        if(!supervisor.isPatrolPage())
            supervisor.playVoice("callme")
        text_hello.visible = false;
        statusbar.visible = false;
        timer_hello.stop();
    }

    Rectangle{
        id: rect_background
        anchors.fill: parent
        color: "#282828"
    }
    Row{
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: 70
        spacing: 100
        Image{
            id: image_robot
            source: "image/robot_clear.png"
            width: 257
            height: 457
            sourceSize.width: width
            sourceSize.height: height
            anchors.verticalCenter: parent.verticalCenter
        }
        Column{
            id: column_pickup
            //visible: true
            anchors.bottom: parent.bottom
            Text{
                id: target_pos
                text: {
                    if(type == 0){
                        qsTr("고객님, 부르셨나요?")
                    }else if(type == 1){
                        qsTr("<font color=\"#12d27c\">다 드신 그릇</font> 은")
                    }
                }
                font.pixelSize: 70
                font.family: font_noto_b.name
                color: "white"
            }
            Text{
                id: target_pos2
                visible:type==1?true:false
                text: qsTr("저에게 전달해 주세요")
                font.pixelSize: 60
                font.family: font_noto_b.name
                color: "white"
            }
            Rectangle{
                color:"transparent"
                width: parent.width
                height: 10
            }
            Text{
                id: text_mention
                text:  {
                    if(type == 0){
                        qsTr("이용이 끝나시면 <font color=\"#12d27c\">확인버튼</font>을 눌러주세요")
                    }else if(type == 1){
                        qsTr("완료 후 아래 <font color=\"#12d27c\">확인버튼</font>을 눌러주세요")
                    }
                }
                font.pixelSize: 45
                font.family: font_noto_b.name
                color: "white"
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
                height: 80
            }
            Rectangle{
                id: btn_confirm
                width: 320
                height: 120
                radius: 60
                border.color: color_gray
                border.width: 2
                anchors.horizontalCenter: parent.horizontalCenter
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
                        supervisor.writelog("[USER INPUT] PICKUP(CALL) CONFIRM clicked");
                        supervisor.playVoice("thanks");
                        column_pickup.visible = false;
                        text_mention.visible = false;
                        target_pos.visible = false;
                        target_pos2.visible = false;
                        btn_confirm.visible = false;
                        text_hello.visible = true;
                        timer_hello.start();
                    }
                }
            }
            Rectangle{
                id: btn_confirm2
                width: 120
                height: 120
                radius: 100
                visible: supervisor.isFinalLocation() && supervisor.getLocationNum("Cleaning")>0
                border.color: color_gray
                border.width: 2
                Text{
                    anchors.centerIn: parent
                    text: qsTr("퇴식")
                    font.family: font_noto_b.name
                    font.pixelSize: 45
                    color: color_blue
                }
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
        Text{
            id: text_hello
            text:qsTr("감사합니다")
            visible: false
            font.pixelSize: 80
            font.family: font_noto_b.name
            color: "white"
            //anchors.verticalCenter: parent.verticalCenter
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
                supervisor.writelog("[QML-PickupCall] PagePickupCall : Debug Pass -> PageKitchen");
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
            supervisor.writelog("[QML-PickupCall] PICKUP PAGE -> Move to Next");
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
