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
        opacity: 0.9
    }

    property string cur_btn: ""
    signal clicked

    function init(){
        closemode = true;
        model_btn.clear();
        style = "warning";
        main_str = "";
        sub_str = "";
    }

    function addButton(text){
        if(text === qsTr("취 소")){
            model_btn.append({"name":text,"mode":0});
        }else{
            model_btn.append({"name":text,"mode":1});
        }
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
            text_sub.color = "white";
        }else if(style == "warning"){
            image_warn.source = "image/warning.png"
            text_main.color = "white";
            text_sub.color = "white";
        }else if(style == "check"){
            image_warn.source = "image/robot_callme.png"
            text_main.color = "white";
            text_sub.color = "white";
        }else if(style == "info"){
            image_warn.source = "icon/icon_info.png";
            text_main.color = "white";
            text_sub.color = "white";
        }

        if(model_btn.count > 0){
            model_btn.insert(0,{"name":qsTr("취 소"),"mode":0})
        }else{
            addButton(qsTr("확 인"));
        }
    }

    Rectangle{
        id: back
        width: parent.width
        height: 360
        anchors.centerIn: parent
        color: color_dark_navy

        Column{
            anchors.fill: parent
            Rectangle{
                width: parent.width
                height: 100
                color: "transparent"
                Row{
                    anchors.centerIn: parent
                    spacing: 10
                    Image{
                        anchors.verticalCenter: parent.verticalCenter
                        id: image_warn
                        width:60
                        height:60
                        sourceSize.width: 60
                        sourceSize.height: 60
                        antialiasing: true
                        source: "image/warning.png"
                    }
                    Text{
                        id:text_main
                        color: "white"
                        anchors.verticalCenter: parent.verticalCenter
                        font.family: font_noto_r.name
                        font.pixelSize: 40
                        text: popup_notice.main_str
                        Component.onCompleted: {
                            while(width > back.width*0.7){
                                font.pixelSize-=1
                            }
                        }
                    }
                }
            }
            Rectangle{
                width: parent.width
                height: 160
                color: "transparent"
                Text{
                    anchors.centerIn: parent
                    id:text_sub
                    color: color_light_gray
                    horizontalAlignment: Text.AlignHCenter
                    font.family: font_noto_r.name
                    font.pixelSize: 28
                    text: popup_notice.sub_str
                    Component.onCompleted: {
                        while(width > back.width*0.9){
                            font.pixelSize-=1
                        }
                    }
                }
            }
            Rectangle{
                width: parent.width
                height: 100
                color: "transparent"
                Row{
                    anchors.centerIn: parent
                    spacing: 15
                    Repeater{
                        model : model_btn
                        Rectangle{
                            width:  180
                            height: 60
                            color: mode===0?color_dark_gray:color_green
                            Text{
                                anchors.centerIn: parent
                                color: mode===0?"white":color_dark_navy
                                font.family: font_noto_r.name
                                font.pixelSize: 20
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
                                    parent.color = mode===0?color_more_gray:color_dark_green
                                    click_sound.play();
                                }
                                onReleased:{
                                    parent.color = mode===0?color_dark_gray:color_green
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
