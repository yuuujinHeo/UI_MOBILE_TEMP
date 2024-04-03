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

Item {
    id: button_show
    width: horizontal?40+70:70
    height: horizontal?40:70
    property int btn_size: 40
    property bool show: false
    property bool horizontal: true
    property string text: "text"
    property color text_color: "white"

    signal clicked();

    Column{
        Row{
            Rectangle{
                width: button_show.btn_size
                height: button_show.btn_size
                radius: width
                color: show?color_green:color_gray
                Image{
                    width: parent.width*0.8
                    height: parent.height*0.8
                    sourceSize.width: width
                    sourceSize.height: height
                    anchors.centerIn: parent
                    source: show?"icon/icon_eye_open.png":"icon/icon_eye_close.png"
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked:{
                        if(show){
                            show = false;
                        }else{
                            show = true;
                        }
                    }
                }
            }
            Rectangle{
                width: 70
                height: 40
                color: "transparent"
                visible: button_show.text!=="" && horizontal
                Text{
                    anchors.centerIn: parent
                    horizontalAlignment: Text.AlignHCenter
                    text: button_show.text
                    color: button_show.text_color
                    font.pixelSize: 15
                    font.family: font_noto_r.name
                }
            }
        }
        Rectangle{
            width: 70
            height: 30
            color: "transparent"
            visible: button_show.text!=="" && !horizontal
            Text{
                anchors.centerIn: parent
                horizontalAlignment: Text.AlignHCenter
                text: button_show.text
                color: button_show.text_color
                font.pixelSize: 15
                font.family: font_noto_r.name
            }
        }

    }

}
