import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.0
import "."

Popup{
    id: popup_loading
    y: statusbar.height
    leftPadding: 0
    rightPadding: 0
    topPadding: 0
    bottomPadding: 0
    width: 1280
    height: 800 - statusbar.height
    closePolicy: Popup.NoAutoClose
    background: Rectangle{
        anchors.fill: parent
        color: "transparent"
    }
    onOpened:{
        loadi.play("image/loading_rb.gif");
    }
    onClosed:{
        loadi.stop();
    }

    AnimatedImage{
        id: loadi
        cache: false
        function play(name){
            source = name;
            visible = true;
        }
        function stop(){
            visible = false;
            source = "";
        }
        source:  ""
        MouseArea{
            width: 100
            height: 100
            anchors.right: parent.right
            anchors.bottom : parent.bottom
            z: 99
            property int password: 0
            onClicked: {
                supervisor.playSound('click');
                password++;
                if(password > 4){
                    password = 0;
                    popup_loading.close();
                }
            }
        }
    }
}
