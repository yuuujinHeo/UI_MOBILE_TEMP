import QtQuick 2.12
import QtQuick.Shapes 1.15
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.3
import Qt.labs.platform 1.0 as Platform
//import QtQuick.Shapes 1.12
import QtGraphicalEffects 1.0
import QtMultimedia 5.12
import "."
import io.qt.Supervisor 1.0

Item{
    id: item_Buttons
    visible: type!==""
    property string text: ""
    property string type: ""
    property string source: ""
    property bool pressed: false
    property bool selected: false
    property bool running: false
    property bool use_shadow: false
    signal clicked

    onRunningChanged: {
        if(running)
            timer.start();
        else
            timer.stop();
    }
    property string btncolor: color_dark_navy
    property string pushcolor: color_dark_black
    property string selectcolor: color_green
    property string bordercolor: "white"
    property string shadowcolor: color_gray
    property string fontcolor: "white"
    property bool overColor: false

    property int fontsize: 30

    property var cur_rect
    onTypeChanged: {
        if(type == "start_progress"){
            cur_rect = start_progress
            use_shadow = true;
            btncolor = "white"
            pushcolor = color_light_gray
            fontcolor = color_dark_navy;
        }else if(type == "circle_text"){
            cur_rect = circle_text
            visible=false;
        }else if(type == "round_text"){
            cur_rect = round_text
        }else if(type == "circle_image"){
            cur_rect = circle_image
        }else if(type == "round_image"){
            cur_rect = round_image
        }else if(type == "white_btn"){
            cur_rect = round_text
            fontsize = 20
            use_shadow = true;
            btncolor = "white"
            bordercolor = color_light_gray
            pushcolor = color_light_gray
            fontcolor = color_dark_navy
        }else if(type == "green_btn"){
            cur_rect = round_text
            fontsize = 20
            use_shadow = true
            btncolor = color_green
            bordercolor = color_light_gray
            pushcolor = color_dark_green
            fontcolor = "white"
        }else if(type == "circle_all"){
            cur_rect = circle_all
            fontcolor = "black"
            btncolor = "white"
            bordercolor = color_green
            pushcolor = color_light_gray
            fontsize = 25
        }
    }

    Rectangle{
        width : parent.width
        height: parent.height
        color: "transparent"

        Rectangle{
            id: start_progress
            visible : type === "start_progress"
            width : parent.width
            height: parent.height
            radius: 20
            color: selected?selectcolor:pressed?pushcolor:btncolor
            Text{
//                visible : !running
                Component.onCompleted: {
                    scale = 1;
                    while(width*scale > parent.width*0.8){
                        scale=scale-0.01;
                    }
                }
                horizontalAlignment: Text.AlignHCenter
//                anchors.centerIn: parent
                anchors.verticalCenter: parent.verticalCenter
                anchors.verticalCenterOffset: running?10:0
                anchors.horizontalCenter: parent.horizontalCenter
                text : item_Buttons.text
                font.family: font_noto_b.name
                color: fontcolor
                font.pixelSize: fontsize
            }
            Rectangle{
                width: parent.width*0.8
                height: 20
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                anchors.verticalCenterOffset: -10
                color: "transparent"
                Rectangle{
                    id: progress
                    width: 30
                    radius: 5
                    property string pos : "left"
                    onPosChanged: {
                        if(pos == "left")
                            x=0;
                        else
                            x=parent.width-width
                    }
                    height: parent.height
                    color: running?selectcolor:"transparent"
                    x: 0
                    Behavior on x{
                        SpringAnimation{
                            duration: 300
                            spring: 2.5
                            damping: 0.6
                        }
                    }
                }
                Timer{
                    id: timer
                    running: running
                    interval: 1100
                    repeat: true
                    onTriggered: {
                        if(progress.pos === "left"){
                            progress.pos = "right";
                        }else{
                            progress.pos = "left";
                        }
                    }
                }
            }
        }
        Rectangle{
            id: circle_all
            visible : type === "circle_all"
            width : parent.width
            height: width
            radius: width
            color: pressed?pushcolor:btncolor
            border.width: selected?3:0
            border.color: bordercolor
            Column{
                anchors.centerIn: parent
                Image{
                    source: item_Buttons.source
                    Component.onCompleted: {
                        if(sourceSize.width > 40)
                            sourceSize.width = 40

                        if(sourceSize.height > 40)
                            sourceSize.height = 40
                    }
                    anchors.horizontalCenter: parent.horizontalCenter
                    ColorOverlay{
                        source: parent
                        color: color_icon_gray
                        anchors.fill: parent
                        visible: item_Buttons.overColor
                    }
                }
                Text{
                    text: item_Buttons.text
                    color: item_Buttons.enabled?fontcolor:"white"
                    horizontalAlignment: Text.AlignHCenter
                    font.family: font_noto_b.name
                    font.pixelSize: fontsize
                    Component.onCompleted: {
                        scale = 1;
                        while(width*scale > parent.width*0.8){
                            scale=scale-0.01;
                        }
                    }
                    anchors.horizontalCenter: parent.horizontalCenter
                }
            }
        }
        Rectangle{
            id: circle_text
            visible : type === "circle_text"
            width : parent.width
            height: width
            radius: width
            color: selected?selectcolor:pressed?pushcolor:btncolor
            border.width: 2
            border.color: bordercolor
            Text{
                horizontalAlignment: Text.AlignHCenter
                Component.onCompleted: {
                    scale = 1;
                    while(width*scale > parent.width*0.8){
                        scale=scale-0.01;
                    }
                }
                anchors.centerIn: parent
                text : item_Buttons.text
                font.family: font_noto_b.name
                color: fontcolor
                font.pixelSize: fontsize
            }
        }
        Rectangle{
            id: round_text
            visible : type === "round_text" || type === "white_btn"
            width : parent.width
            height: parent.height
            radius: 20
            color: item_Buttons.enabled?selected?selectcolor:pressed?pushcolor:btncolor:color_gray
            border.width: 2
            border.color: bordercolor
            Row{

            }

            Text{
                horizontalAlignment: Text.AlignHCenter
                Component.onCompleted: {
                    scale = 1;
                    while(width*scale> parent.width*0.8){
                        scale=scale-0.01;
                    }
                }
                anchors.centerIn: parent
                text : item_Buttons.text
                font.family: font_noto_b.name
                color: fontcolor
                font.pixelSize:fontsize
            }
        }

        Rectangle{
            id: round_image
            visible : type === "round_image"
            width : parent.width
            height: parent.height
            radius: 20
            color: item_Buttons.enabled?selected?selectcolor:pressed?pushcolor:btncolor:color_gray
            border.width: 2
            border.color: bordercolor
            Column{
                anchors.centerIn: parent
                Image{
                    source: item_Buttons.source
                    Component.onCompleted: {
                        while(width > item_Buttons.width*0.8){
                            width = width*0.95;
                            height = height*0.95;
                        }
                        while(height > item_Buttons.height*0.8){
                            width = width*0.95;
                            height = height*0.95;
                        }
                        sourceSize.width= width
                        sourceSize.height= height
                    }
                    sourceSize.width: width
                    sourceSize.height: height
                    anchors.horizontalCenter: parent.horizontalCenter
                    ColorOverlay{
                        source: parent
                        color: color_icon_gray
                        anchors.fill: parent
                        visible: item_Buttons.overColor
                    }
                }
                Text{
                    horizontalAlignment: Text.AlignHCenter
                    Component.onCompleted: {
                        scale = 1;
                        while(width*scale> parent.width*0.8){
                            scale=scale-0.01;
                        }
                    }
                    anchors.horizontalCenter: parent.horizontalCenter
                    text : item_Buttons.text
                    font.family: font_noto_b.name
                    color: fontcolor
                    font.pixelSize:fontsize
                }
            }
        }
        Rectangle{
            id: circle_image
            visible : type === "circle_image"
            width : parent.width
            height: width
            radius: width
            color: enabled?selected?selectcolor:pressed?pushcolor:btncolor:color_gray
            border.width: 2
            border.color: bordercolor
            Image{
                source: item_Buttons.source
                Component.onCompleted: {
                    while(width > item_Buttons.width*0.8){
                        width = width*0.95;
                        height = height*0.95;
                    }
                    while(height > item_Buttons.height*0.8){
                        width = width*0.95;
                        height = height*0.95;
                    }
                }
                anchors.centerIn: parent
                ColorOverlay{
                    source: parent
                    color: color_icon_gray
                    anchors.fill: parent
                    visible: item_Buttons.overColor
                }

            }

            Text{
                horizontalAlignment: Text.AlignHCenter
                anchors.centerIn: parent
                text : item_Buttons.text
                font.family: font_noto_b.name
                color: fontcolor
                font.pixelSize: fontsize
            }
        }
        DropShadow{
            anchors.fill: parent
            radius: 10
            visible: use_shadow
            color: shadowcolor
            source: cur_rect
        }
    }
    MouseArea{
        enabled: item_Buttons.enabled
        anchors.fill: parent
        onPressed:{
            supervisor.playSound('click');
            item_Buttons.pressed = true;
        }
        onReleased:{
            item_Buttons.pressed = false;
            if(containsMouse){
                item_Buttons.clicked();
            }
        }
    }
}
