import QtQuick 2.12
import QtQuick.Controls 2.12

Popup{
    id: popup_notice
    anchors.centerIn: parent
    width: 1280
    height: 800
    property string main_str: ""
    property string sub_str: ""
    property string style: "warning"

    property bool closemode: true
    leftPadding: 0
    rightPadding: 0
    topPadding: 0
    bottomPadding: 0
    background:Rectangle{
        anchors.fill: parent
        color: color_dark_black
        opacity: 0.7
    }

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


    onOpened:{
        if(style == "notice"){
            image_warn.source = "icon/icon_bookmark.png"
            text_main.color = "white";
            text_sub.color = "white";
        }else if(style == "error"){
            image_warn.source = "image/icon_warning.png"
            text_main.color = color_red;
            text_sub.color = color_red;
        }else if(style == "warning"){
            image_warn.source = "image/warning.png"
            text_main.color = color_red;
            text_sub.color = color_red;
        }else if(style == "check"){
            image_warn.source = "image/robot_callme.png"
            text_main.color = color_blue;
            text_sub.color = "white";
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
    Rectangle{
        id: back
        width: parent.width
        height: 400
        anchors.centerIn: parent
        color: "transparent"

        Column{
            anchors.fill: parent
            Rectangle{
                width: parent.width
                height: 15
                color: text_main.color
            }
            Rectangle{
                id: rect_border
                width: parent.width
                height: parent.height - 30
                color: "transparent"
                Rectangle{
                    anchors.fill: parent
                    color: color_dark_black
                    opacity: 0.7
                }
                Row{
                    anchors.fill: parent
                    Rectangle{
                        width:  parent.height
                        height: parent.height
                        color: "transparent"
                        Image{
                            anchors.centerIn: parent
                            id: image_warn
                            width:220
                            height:220
                            source: "image/warning.png"
                        }
                    }
                    Rectangle{
                        id: rect_dd
                        width: parent.width -  parent.height
                        height: parent.height
                        color: "transparent"
                        Column{
                            spacing: 40
                            anchors.verticalCenter: parent.verticalCenter
                            Column{
                                Text{
                                    id:text_main
                                    color: color_red
                                    font.family: font_noto_r.name
                                    font.pixelSize: 50
                                    text: popup_notice.main_str
                                    Component.onCompleted: {
                                        while(width > rect_dd.width*0.9){
                                            font.pixelSize-=1
                                        }
                                    }
                                }
                                Text{
                                    id:text_sub
                                    color: color_red
                                    font.family: font_noto_r.name
                                    font.pixelSize: 35
                                    text: popup_notice.sub_str
                                    Component.onCompleted: {
                                        while(width > rect_dd.width*0.9){
                                            font.pixelSize-=1
                                        }
                                    }
                                }
                            }
                            Rectangle{
                                width: rect_dd.width*0.8
                                color: "transparent"
                                height: 80
                                anchors.horizontalCenter: parent.horizontalCenter
                                visible: model_btn.count>0
                                Row{
                                    anchors.centerIn: parent
                                    spacing: 40
                                    Repeater{
                                        model : model_btn
                                        Rectangle{
                                            width:  160
                                            height: 60
                                            color: color_gray
                                            radius: 10
                                            Text{
                                                anchors.centerIn: parent
                                                color: color_dark_black
                                                font.family: font_noto_r.name
                                                font.pixelSize: 25
                                                text: name
                                                Component.onCompleted: {
                                                    while(width > 160*0.9){
                                                        font.pixelSize-=1
                                                    }
                                                }
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
                                                    popup_notice.clicked();
                                                }
                                            }
                                        }
                                    }
                                }

                            }
                        }
                    }
                }
            }
            Rectangle{
                width: parent.width
                height: 15
                color: text_main.color
            }
        }
    }
}
