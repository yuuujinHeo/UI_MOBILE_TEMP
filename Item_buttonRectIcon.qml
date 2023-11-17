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
    id: item_ButtonRect
    property string icon: ""
    property string name: ""
    property string color: "white"
    property string push_color: color_light_gray
    property string disable_color: color_gray
    property string font_color: color_dark_navy
    property bool selected: false
    signal clicked
    width: 130
    height: 130

    Rectangle{
        id: btn
        width: parent.width
        height: parent.height
        radius: 20
        border.color: color_green
        border.width: selected?3:0
        color: parent.enabled?parent.color:parent.disable_color
        Column{
            anchors.centerIn: parent
            Image{
                visible: icon!==""
                source: icon
                anchors.horizontalCenter: parent.horizontalCenter
                Component.onCompleted: {
                    if(sourceSize.width > 50)
                        sourceSize.width = 50

                    if(sourceSize.height > 50)
                        sourceSize.height = 50
                }
                ColorOverlay{
                    anchors.fill: parent
                    source: parent
                    color: color_dark_navy
                }

            }
            Text{
                text: name
                color: item_ButtonRect.enabled?font_color:"white"
                horizontalAlignment: Text.AlignHCenter
                font.family: font_noto_r.name
                font.pixelSize: 20
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }
        MouseArea{
            anchors.fill: parent
            onPressed:{
                btn.color = push_color;
            }
            onReleased: {
                btn.color = color;
                item_ButtonRect.clicked()
                click_sound.play();
            }
        }
    }

//    SoundEffect{
//        id: click_sound
//        source: "bgm/click.wav"
//    }
}
