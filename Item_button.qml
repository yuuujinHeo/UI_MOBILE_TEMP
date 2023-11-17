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
    id: item_Button
    property string icon: ""
    property string name: ""
    property bool highlight: false
    width: 100
    height: width
    property color shadow_color: color_light_gray
    property color btn_color: "white"
    property bool overcolor: false

    function show_ani(){
        ani_radial_shape_once.start();
    }

    property bool running: false
    onRunningChanged: {
        if(running){
            ani_radial_shape.start();
        }else{
            ani_radial_shape.stop();
        }
    }
    function pressed(){
        btn_color = color_light_gray;
    }
    function released(){
        btn_color = "white";
        click_sound.play();
    }

    Rectangle{
        width: parent.width
        height: width
        radius: width
        Rectangle{
            id: btn_rect
            width: parent.width
            height: width
            radius: width
            color: item_Button.enabled?btn_color:color_gray
            border.width: highlight?3:0
            border.color: "#12d27c"
            Column{
                anchors.centerIn: parent
                Image{
                    source: icon
                    Component.onCompleted: {
                        if(sourceSize.width > 40)
                            sourceSize.width = 40

                        if(sourceSize.height > 40)
                            sourceSize.height = 40
                    }
                    ColorOverlay{
                        anchors.fill: parent
                        source: parent
                        visible: overcolor
                        color: color_mid_gray
                    }
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                Text{
                    text: name
                    color: item_Button.enabled?"black":"white"
                    horizontalAlignment: Text.AlignHCenter
                    font.family: font_noto_r.name
                    font.pixelSize: 20
                    anchors.horizontalCenter: parent.horizontalCenter
                }
            }
        }
        DropShadow{
            anchors.fill: parent
            radius: 10
            color: shadow_color
            source: btn_rect
        }
        Shape{
            id: shape_radial
            visible: false
            anchors.fill: parent
            layer.enabled: true
            layer.samples: 4
            ShapePath{
                strokeColor: "#12d27c"
                fillColor: "transparent"
                capStyle: Qt.RoundCap
                strokeWidth: 5
                PathAngleArc{
                    id: path_radial
                    radiusX: btn_rect.width/2 - 2
                    radiusY: radiusX
                    centerX: btn_rect.width/2
                    centerY: centerX
                    startAngle: 0
                    sweepAngle: 180
                }
            }
        }
    }

//    SoundEffect{
//        id: click_sound
//        source: "bgm/click2.wav"
//    }
    SequentialAnimation{
        id: ani_radial_shape
        loops: -1
        onStarted: {
            shape_radial.visible = true;
            path_radial.startAngle = -90;
            path_radial.sweepAngle = 0;
        }
        onStopped: {
            shape_radial.visible = false;
        }

        PropertyAnimation{
            target: path_radial
            property: "sweepAngle"
            from: 0
            to: 360
            duration: 500
        }
        ParallelAnimation{
            PropertyAnimation{
                target: path_radial
                property: "startAngle"
                from: -90
                to: 270
                duration: 500
                easing.type: Easing.InOutQuad
            }
            PropertyAnimation{
                target: path_radial
                property: "sweepAngle"
                from: 360
                to: 0
                duration: 500
                easing.type: Easing.InOutQuad
            }
        }
    }
    SequentialAnimation{
        id: ani_radial_shape_once
        onStarted: {
            shape_radial.visible = true;
            path_radial.startAngle = -90;
            path_radial.sweepAngle = 0;
        }
        PropertyAnimation{
            target: path_radial
            property: "sweepAngle"
            from: 0
            to: 360
            duration: 300
        }
        ParallelAnimation{
            PropertyAnimation{
                target: path_radial
                property: "startAngle"
                from: -90
                to: 270
                duration: 200
                easing.type: Easing.InOutQuad
            }
            PropertyAnimation{
                target: path_radial
                property: "sweepAngle"
                from: 360
                to: 0
                duration: 200
                easing.type: Easing.InOutQuad
            }
        }
        onFinished: {
            print("finish")
        }
    }
    SequentialAnimation{
        id: ani_btn_pushed
        PropertyAnimation{
            target: btn_rect
            property: "color"
            from: 0
            to: 360
            duration: 300
        }
        ParallelAnimation{
            PropertyAnimation{
                target: path_radial
                property: "startAngle"
                from: -90
                to: 270
                duration: 200
                easing.type: Easing.InOutQuad
            }
            PropertyAnimation{
                target: path_radial
                property: "sweepAngle"
                from: 360
                to: 0
                duration: 200
                easing.type: Easing.InOutQuad
            }
        }
        onFinished: {
            print("finish")
        }
    }
}
