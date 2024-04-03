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
    id: buttons
    width: 180
    height: 60

    property string style: ""
    property string text: ""
    property string source: ""
    property int im_width: 60
    property string btn_color: color_gray
    property string image_color: ""
    property color font_color: "white"
    property color shadow_color: "white"
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
        if(style == "normal"){
            btn_color = color_more_gray
        }else if(style == "green"){
            btn_color = color_mid_green
        }else if(style == "blue"){
            btn_color = color_blue
        }else if(style == "dark_navy"){
            btn_color = color_mid_navy
        }else if(style == "dark"){
            btn_color = "black"
        }else if(style == "keyboard"){
            btn_color = "black"
        }else if(style == "white"){
            btn_color = color_light_gray
        }
    }

    function setStyle(){
        if(active){
            if(style == "normal"){
                btn_color = color_gray
                font_color = color_dark_navy
            }else if(style == "green"){
                btn_color = color_green
            }else if(style == "blue"){
                btn_color = color_blue
            }else if(style == "dark_navy"){
                btn_color = color_dark_navy
            }else if(style == "dark"){
                btn_color = color_navy
            }else if(style == "keyboard"){
                btn_color = color_navy
                width =  50
                height = 50
                im_width = 50
                rect_buttons.radius = 5
                source = "icon/icon_keyboard.png"
            }else if(style == "keyboard_dark"){
                btn_color = color_navy
                width =  50
                height = 50
                im_width = 50
                rect_buttons.radius = 5
                source = "icon/icon_keyboard.png"
            }else if(style == "white"){
                btn_color = "white"
                font_color = color_dark_navy
            }else if(style == "menu_dark"){
                width = 180
                height = 180
                btn_color = color_dark_navy
                show_shadow = true
                shadow_color = color_navy
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
        color: buttons.btn_color
        border.width: buttons.selected?3:0
        border.color: color_green
        Row{
            anchors.fill: parent
            Rectangle{
                id: r1
                anchors.verticalCenter: parent.verticalCenter
                visible: buttons.source!==""
                width: im_width//buttons.height>60?60:buttons.height
                height: buttons.height>60?60:buttons.height
                color: "transparent"
                Image{
                    anchors.centerIn: parent
                    source: buttons.source
                    height: buttons.height>60?60*0.8:buttons.height*0.8
                    width: height
                    sourceSize.width: width
                    sourceSize.height: height
//                    antialiasing: true
                    ColorOverlay{
                        anchors.fill: parent
                        source: parent
                        color: buttons.image_color
                        visible: buttons.image_color!==""
                    }
                }
            }
            Rectangle{
                width: buttons.source===""?buttons.width:(buttons.width - r1.width)
                height: buttons.height
                color: "transparent"
                visible: buttons.text!==""
                Text{
                    anchors.centerIn: parent
                    text: buttons.text
                    font.pixelSize: 20
                    Component.onCompleted: {
                        while(width>parent.width*0.95){
                            font.pixelSize -= 1;
                        }
                    }
                    color: buttons.font_color
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
                click_sound.play();
            }else{
                click_sound_no.play();
            }
        }
        onReleased:{
            if(active){
                setStyle();
                if(containsMouse){
                    buttons.clicked();
                }
            }
        }
    }
}
