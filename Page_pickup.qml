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

    function init(){
        supervisor.writelog("[QML] PICKUP PAGE Init");
        pickup_1 = false;
        pickup_2 = false;
        pickup_3 = false;
        text_mention.visible = true;
        text_mention3.visible = true;
        target_pos.visible = true;
        btn_confirm.visible = true;
        text_hello.visible = false;
        timer_hello.stop();
        voice_pickup.play();
        statusbar.visible = false;
    }

    function play_voice(){
//        if(pickup_1)
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
                font.pixelSize: 45
                font.family: font_noto_b.name
                color: "white"
            }
            Rectangle{
                color:"transparent"
                width: parent.width
                height: 50
            }
            Image{
                id: btn_confirm
                source:"icon/btn_confirm.png"
                anchors.horizontalCenter: parent.horizontalCenter
                width: 320
                height: 120
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        //click_start.play();
                        click_sound.play();
                        supervisor.writelog("[USER INPUT] PICKUP CONFIRM clicked");
                        voice_pickup.stop();
                        voice_thanks.play();
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
        property var password: 0
        onClicked: {
            click_sound2.play();
            password++;
            if(password > 4){
                password = 0;
                supervisor.writelog("[USER INPUT] ENTER THE MOVEFAIL PAGE "+Number(password));
                loadPage(pmovefail);
                loader_page.item.setNotice(3);
            }
        }
    }


    Audio{
        id: voice_pickup
        autoPlay: false
        volume: volume_voice/100
        source: supervisor.getVoice("pickup_confirm");
        property bool isplaying: false
        onStopped: {
            isplaying = false;
        }
        onPlaying:{
            isplaying = true;
        }
    }

    Audio{
        id: voice_tray_1
        autoPlay: false
        volume: volume_voice/100
        source: supervisor.getVoice("pickup_1");
        property bool isplaying: false
        onStopped: {
            isplaying = false;
        }
        onPlaying:{
            isplaying = true;
        }
    }

    Audio{
        id: voice_tray_2
        autoPlay: false
        volume: volume_voice/100
        source: supervisor.getVoice("pickup_2");
        property bool isplaying: false
        onStopped: {
            isplaying = false;
        }
        onPlaying:{
            isplaying = true;
        }
    }

    Audio{
        id: voice_thanks
        autoPlay: false
        volume: volume_voice/100
        source: supervisor.getVoice("thank");
        property bool isplaying: false
        onStopped: {
            isplaying = false;
        }
        onPlaying:{
            isplaying = true;
        }
    }

    Timer{
        id: timer_hello
        interval: 3000
        running: false
        repeat: false
        onTriggered: {
            supervisor.confirmPickup();
            supervisor.writelog("[QML] PICKUP PAGE -> Move to Next");
        }
    }
}
