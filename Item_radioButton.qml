import QtQuick 2.0
import "."

Item {
    id: item_radiobutton
    width: big
    height: small
    property var big: 100
    property var small: 40
    property var spacing: 5
    property var head_width: small-spacing*2
    property bool onoff: false
    property bool touchEnabled: false
    property bool isVertical: true
    signal turnon
    signal turnoff
    Component.onCompleted: {
        enabledChange();
        verticalChange();
    }
    onIsVerticalChanged: {
        verticalChange();
    }

    onOnoffChanged: {
        if(isVertical){
            if(onoff){
                turnon();
                head.y = height - spacing - head_width;
            }else{
                turnoff();
                head.y = spacing;
            }
        }else{
            if(onoff){
                turnon();
                head.x = width - spacing - head_width;
            }else{
                turnoff();
                head.x = spacing;
            }
        }

        if(onoff && background.color != "#12d27c"){
            background.color = "#12d27c";
        }else if(!onoff && background.color != "#525252"){
            background.color = "#525252";
        }

    }
    function setEnabled(en){
        if(en){
            enabled = true;
        }else{
            enabled = false;
            onoff = false;
        }
    }
    function setOnoff(o){
        onoff = o;
        if(onoff){
            turnon();
            if(isVertical){
                head.y = height - spacing - head_width;
            }else{
                head.x = width - spacing - head_width;
            }
            background.color = "#12d27c";
        }else{
            turnoff();
            if(isVertical){
                head.y = spacing;
            }else{
                head.x = spacing;
            }
            background.color = "#525252";
        }

    }

    function enabledChange(){
        if(enabled){
            onoff = false;
            background.color = "#525252"
        }else{
            onoff = false;
            background.color = "#525252"
        }
    }

    function verticalChange(){
        if(isVertical){
            width = small;
            height = big;
            head.anchors.horizontalCenter = background.horizontalCenter;
            if(onoff){
                head.y = height - head_width - spacing;
            }else{
                head.y = spacing;
            }
        }else{
            width = big;
            height = small;
            head.anchors.verticalCenter = background.verticalCenter;
            if(onoff){
                head.x = height - head_width - spacing;
            }else{
                head.x = spacing;
            }
        }
    }


    Rectangle{
        id: background
        anchors.fill: parent
        radius: 40
        color: "#525252"
        MouseArea{
            anchors.fill: parent
            enabled: touchEnabled && item_radiobutton.enabled
            onClicked: {
                if(onoff){
                    print("click 1: onoff -> off");
                    onoff = false;
                }else{
                    print("click 1: onoff -> on");
                    onoff = true;
                }
            }
        }

        Rectangle{
            visible: !item_radiobutton.enabled
            anchors.fill: parent
            radius: 40
            color: "#525252"
            Text{
                text: qsTr("없음")
                anchors.centerIn: parent
                font.family: font_noto_r.name
                font.pixelSize: 15
                color:"white"
            }
        }

        Rectangle{
            id: head
            width: head_width
            height: width
            radius: width
            visible: item_radiobutton.enabled
            color: "white"

            Behavior on y{
                SpringAnimation{
                    duration: 200
                    spring: 1
                    damping: 0.2
                }
            }
            Behavior on x{
                SpringAnimation{
                    duration: 200
                    spring: 1
                    damping: 0.2
                }
            }
            MouseArea{
                anchors.fill: parent
                enabled: touchEnabled && item_radiobutton.enabled
                property var firstX;
                property var firstY;
                property var width_dis: 0
                onPressed: {
                    if(isVertical){
                        firstY = mouseY;
                    }else{
                        firstX = mouseX;
                    }
                    width_dis = 0;
                }
                onPositionChanged: {
                    if(isVertical){
                        width_dis = mouseY-firstY;
                        if(head.y + width_dis < spacing){
                            head.y = spacing;
                        }else if(head.y + width_dis > background.height - head_width - spacing){
                            head.y = background.height - head_width - spacing;
                        }else{
                            head.y = head.y + width_dis;
                        }
                    }else{
                        width_dis = mouseX-firstX;
                        if(head.x + width_dis < spacing){
                            head.x = spacing;
                        }else if(head.x + width_dis > background.width - head_width - spacing){
                            head.x = background.width - head_width - spacing;
                        }else{
                            head.x = head.x + width_dis;
                        }
                    }

                    if(width_dis > 0){
                        if(background.color != "#525252"){
                            background.color = "#525252";
                        }
                    }else{
                        if(background.color != "#12d27c"){
                            print("2")
                            background.color = "#12d27c";
                        }
                    }


                }
                onReleased: {
                    if(width_dis>0){
                        onoff = true;
                        if(isVertical){
                            head.y = background.height - head_width - spacing;
                        }else{
                            head.x = background.width - head_width - spacing;
                        }

                    }else if(width_dis<0){
                        onoff = false;
                        if(isVertical){
                            head.y = spacing;
                        }else{
                            head.x = spacing;
                        }
                    }else if(width_dis == 0){
                        if(onoff){
                            onoff = false;
                        }else{
                            onoff = true;
                        }
                    }
                }
            }
        }
    }
}
