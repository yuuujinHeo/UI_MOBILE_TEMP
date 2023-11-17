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

    function init(){
        if(type == 0){//부르셨나요?
            target_pos2.visible = false;
        }else if(type == 1){//다 드신 그릇은
            target_pos2.visible = true;
        }
        text_mention.visible = true;
        target_pos.visible = true;
        btn_confirm.visible = true;
        voice_pickup.play();
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
            anchors.verticalCenter: parent.verticalCenter
        }
        Column{
            id: column_pickup
            visible: true
            anchors.bottom: parent.bottom
//            anchors.verticalCenter: image_robot.verticalCenter

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
            Rectangle{
                color:"transparent"
                width: parent.width
                height: 80
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
                        click_sound.play();
                        console.log("UI : CONFIRM");
                        voice_pickup.stop();
                        voice_thanks.play();
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

        }
        Text{
            id: text_hello
            text:qsTr("감사합니다")
            visible: false
            font.pixelSize: 80
            font.family: font_noto_b.name
            color: "white"
            anchors.verticalCenter: parent.verticalCenter
        }
    }
    Audio{
        id: voice_pickup
        autoPlay: false
        volume: volume_voice/100
        source: supervisor.getVoice("pickup_calling");
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
    Timer{
        id: timer_hello
        interval: 3000
        running: false
        repeat: false
        onTriggered: {
            supervisor.confirmPickup();
            console.log("UI : MOVE NEXT");
        }
    }
}
