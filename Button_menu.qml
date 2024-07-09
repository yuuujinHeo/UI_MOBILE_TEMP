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


Item {
    id: button_menu
    width: 200
    height: 200
    property string style: ""
    property string text: ""
    property string source: ""
    property int im_width: 80
    property string btn_color: color_dark_navy
    property color font_color: "white"
    property string image_color: ""
    property color shadow_color: color_light_navy
    property bool active: true
    property bool selected: false
    property bool show_shadow: false
    Component.onCompleted: {
        setStyle();
    }
    onActiveChanged: {
        setStyle();
    }
    function setPressed(){
        if(style == "navy"){
            btn_color = color_mid_navy
        }
    }

    function setStyle(){
        if(active){
            if(style == "navy"){
                btn_color = color_dark_navy
            }
        }else{
            btn_color = color_gray
            font_color = "white"
        }
    }

    signal clicked

    Rectangle{
        id: rect_buttons
        width: parent.width
        height: parent.height
        radius: 10
        color: button_menu.btn_color
        border.width: button_menu.selected?3:0
        border.color: color_green
        layer.enabled: true
        layer.effect: DropShadow{
            color: button_menu.shadow_color
            radius: 10
        }
        Rectangle{
            anchors.fill: parent
            radius: 10
            color: button_menu.btn_color
        }

        Column{
            anchors.fill: parent
            Rectangle{
                id: r1
                anchors.horizontalCenter: parent.horizontalCenter
                visible: button_menu.source!==""
                width: button_menu.width>80?80:button_menu.width
                height: button_menu.im_width
                color: "transparent"
                Image{
                    anchors.centerIn: parent
                    source: button_menu.source
                    height: button_menu.width>80?80*0.8:button_menu.width*0.8
                    width: height
                    sourceSize.width: width
                    sourceSize.height: height
                    ColorOverlay{
                        anchors.fill: parent
                        source: parent
                        color: button_menu.image_color
                        visible: button_menu.image_color!==""
                    }
                }
            }
            Rectangle{
                height: button_menu.source===""?button_menu.height:(button_menu.height - r1.height)
                width: button_menu.width
                color: "transparent"
                visible: button_menu.text!==""
                Text{
                    anchors.centerIn: parent
                    text: button_menu.text
                    font.pixelSize: 25
                    horizontalAlignment: Text.AlignHCenter
                    Component.onCompleted: {
                        while(width>parent.width*0.95){
                            font.pixelSize -= 1;
                        }
                    }
                    color: button_menu.font_color
                    font.family: font_noto_r.name
                }
            }
        }
    }
    MouseArea{
        anchors.fill: parent
        onPressed:{
            if(active){
                setPressed();
                supervisor.playSound('click');
            }else{
                supervisor.playSound('no');
            }
        }
        onReleased:{
            if(active){
                setStyle();
                if(containsMouse){
                    button_menu.clicked();
                }
            }
        }
    }
}
