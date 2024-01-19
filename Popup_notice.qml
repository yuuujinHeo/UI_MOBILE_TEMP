import QtQuick 2.12
import QtQuick.Controls 2.12

Popup{
    id: popup_notice
    anchors.centerIn: parent
    width: 1000
    height: 300
    property string main_str: ""
    property string sub_str: ""
    property string style: "warning"

    property bool closemode: true


    property string cur_btn: ""
    signal clicked

    function init(){
        closemode = true;
        model_btn.clear();
    }

    function addButton(text){
        model_btn.append({"name":text});
    }

    ListModel{
        id: model_btn
    }

    background:Rectangle{
        anchors.fill: parent
        color: "transparent"
    }
    onOpened:{
        if(style == "notice"){
            rect_border.border.color = "white";
            image_warn.source = "icon/icon_bookmark.png"
            text_main.color = "white";
            text_sub.color = "white";
        }else if(style == "error"){
            rect_border.border.color = color_red;
            image_warn.source = "image/icon_warning.png"
            text_main.color = color_red;
            text_sub.color = color_red;
        }else if(style == "warning"){
            rect_border.border.color = color_red;
            image_warn.source = "image/warning.png"
            text_main.color = color_red;
            text_sub.color = color_red;
        }else if(style == "check"){
            rect_border.border.color = color_blue;
            image_warn.source = "image/robot_callme.png"
            text_main.color = color_blue;
            text_sub.color = "white";
        }
    }

    Rectangle{
        id: back
        width: parent.width
        height: parent.height
        opacity: 0.9
        radius: 10
        color: color_dark_black
    }
    Rectangle{
        id: rect_border
        anchors.centerIn: parent
        width: parent.width-20
        height: parent.height-20
        radius: 10
        color: "transparent"
        border.color: color_red
        border.width: 5
        Image{
            id: image_warn
            width: 120
            height: 120
            source: "image/warning.png"
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 50
        }
        Column{
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: image_warn.right
            anchors.leftMargin: 50
            Text{
                id:text_main
                color: color_red
                font.family: font_noto_r.name
                font.pixelSize: 35
                text: popup_notice.main_str
            }
            Text{
                id:text_sub
                color: color_red
                font.family: font_noto_r.name
                font.pixelSize: 30
                text: popup_notice.sub_str
            }
        }
        MouseArea{
            anchors.fill: parent
            enabled: closemode
            onClicked:{
                click_sound.play();
                popup_notice.close();
            }
        }
        Row{
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20
            Repeater{
                model : model_btns

                Rectangle{
                    width:  120
                    height: 60
                    color: "transparent"
                    border.color: color_red
                    border.width: 3
                    radius: 10
                    Text{
                        anchors.centerIn: parent
                        color: color_red
                        font.family: font_noto_r.name
                        font.pixelSize: 20
                        text: name
                    }
                    MouseArea{
                        anchors.fill: parent
                        onPressed:{
                            parent.color = color_dark_black
                            click_sound.play();
                        }
                        onReleased:{
                            parent.color = "transparent"
                            cur_btn = name;
                            clicked();
                        }
                    }
                }
            }
        }
    }
}
