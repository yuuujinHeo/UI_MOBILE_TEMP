import QtQuick 2.12
import QtQuick.Shapes 1.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.2
import Qt.labs.platform 1.0 as Platform
import QtQuick.Shapes 1.12
import QtGraphicalEffects 1.0
import QtMultimedia 5.12
import "."
import io.qt.Supervisor 1.0

Item {
    id: item_menubar
    width: 120
    height: 120
    clip: true

    signal menu1_clicked
    signal menu2_clicked
    signal menu3_clicked
    signal menu4_clicked
    signal menu5_clicked

    property var menu1_en: true
    property var menu2_en: true
    property var menu3_en: true
    property var menu4_en: true
    property var menu5_en: true

    onMenu1_enChanged: {
        setEnable(0,menu1_en);
    }
    onMenu2_enChanged: {
        setEnable(1,menu2_en);
    }
    onMenu3_enChanged: {
        setEnable(2,menu3_en);
    }
    onMenu4_enChanged: {
        setEnable(3,menu4_en);
    }
    onMenu5_enChanged: {
        setEnable(4,menu5_en);
    }

    Component.onCompleted: {
        model_menu.clear();
    }

    function setclicked(num){
        if(num === 0){
            menu1_clicked();
        }else if(num === 1){
            menu2_clicked();
        }else if(num === 2){
            menu3_clicked();
        }else if(num === 3){
            menu4_clicked();
        }else if(num === 4){
            menu5_clicked();
        }
    }

    function addMenu(name, source){
        model_menu.append({"name":name, "image":source, "en":true});
        height = width * model_menu.count
    }
    function setEnable(num, en){
        model_menu.get(num).en = en;
    }


    Rectangle{
        width: parent.width
        height: parent.height
        radius: 30
        Column{
            Repeater{
                model: ListModel{id: model_menu}
                Rectangle{
                    id: btn
                    color: "transparent"
                    width: item_menubar.width
                    height: width
                    radius: 30
                    Column{
                        anchors.centerIn: parent
                        Rectangle{
                            width: name==""?70:50
                            height: width
                            anchors.horizontalCenter: parent.horizontalCenter
                            Image{
                                source:image
                                anchors.centerIn: parent
                                Component.onCompleted: {
                                    var w;
                                    if(width>height){
                                        w = width;
                                    }else{
                                        w = height;
                                    }

                                    if(w>parent.width){
                                        while(w*scale > parent.width){
                                            scale-=0.1;
                                        }
                                    }else{
                                        while(w*scale < parent.width){
                                            scale+=0.1;
                                        }
                                    }
                                }
                            }
                        }
                        Text{
                            height: 30
                            visible: name!==""
                            text: name
                            anchors.horizontalCenter: parent.horizontalCenter
                            font.family: font_noto_r.name
                            font.pixelSize: 15
                            color: en?color_dark_black:color_red
                        }
                    }
                    MouseArea{
                        anchors.fill: parent
                        onPressed:{
                            btn.color = color_light_gray;
//                            click_sound.play();
                        }
                        onReleased:{
                            btn.color = "transparent";
                            if(containsMouse){
                                setclicked(index);
                            }
                        }
                    }
                }
            }
        }
    }
}
