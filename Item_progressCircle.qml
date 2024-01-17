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

Item {
    id: item_progresscircle
    width: 400
    height: 400
    property var value: 0.0
    property var error: 0.0
    property var state: 1
    property var limit: parseFloat(supervisor.getSetting("setting","INITIALIZATION","icp_init_ratio"))
    property var error_limit: parseFloat(supervisor.getSetting("setting","INITIALIZATION","icp_init_error"))
    property bool show_limit: false
    property color back_color: color_gray
    property color main_color: color_blue

    Timer{
        repeat: true
        running: true
        interval: 200
        onTriggered: {
            value = supervisor.getICPRatio();
            error = supervisor.getICPError();
//            print("TEST : ",value,error,limit,error_limit,state);
            if(error > error_limit){
                circle1.progressColor = color_red;
                btn_init_success.enabled = false;
                state = 3;
            }else if(value > limit){
                circle1.progressColor = color_green;
                state = 2;
                btn_init_success.enabled = true;
            }else{
                circle1.progressColor = color_warning;
                btn_init_success.enabled = false;
                state = 1;
            }
        }
    }
    onValueChanged: {
        circle1.value = value;
    }
    onErrorChanged: {
        circle2.value = error;
    }



    Item_CircleP{
        id: circle1
        anchors.fill: parent
        show_limit: true
        value: value
        startAngle: 0
        limit_angle: limit
        endAngle: 270
        rotation : 225
        limiter: Item {
            id: item
            width: 24
            height: 24
            Shape {
                anchors.fill: parent
                rotation: 180
                ShapePath {
                    strokeWidth: 1
                    strokeColor: "#FF5555"
                    fillColor: "#FF5555"
                    startX: item.width/2
                    startY: 0
                    PathLine { x: 0; y: item.height }
                    PathLine { x: item.width; y: item.height }
                    PathLine { x: item.width/2; y: 0 }
                }
            }
            transform: Translate {
                x: (circle1.handleWidth - width) / 2
                y: (circle1.handleHeight - height) / 2
            }
        }
    }
    Item_CircleP{
        id: circle2
        width: parent.width*0.8
        height: parent.height*0.8
        anchors.centerIn: parent
        show_limit: true
        progressColor: color_red
        trackWidth: 10
        progressWidth: 10
        value: error
        startAngle: 0
        endAngle: 270
        rotation : 225
        limit_angle: error_limit
        limiter:Rectangle {
            transform: Translate {
                x: (circle2.handleWidth - width) / 2
                y: circle2.handleHeight / 2
            }
            width: 5
            height: circle2.height / 2
            color: "#FFac89"
            radius: width / 2
            antialiasing: true
        }
    }

    Rectangle{
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: -30
        width: 200
        height: width
        radius: width
        color: color_light_gray
        Column{
            anchors.centerIn: parent
            spacing: -20
            Text{
                id: text_value
                property var textValue: value
                NumberAnimation on textValue{
                    id: ani_textvalue
                    to: value
                    from: text_value.textValue
                    duration: 500
                }
                color: circle1.progressColor//state===1?state===2?color_red:color_green:color_blue
                anchors.horizontalCenter: parent.horizontalCenter
                text: Number(textValue*100).toFixed(0);
                font.pixelSize: 120
                font.family: font_noto_b.name
            }
            Row{
                anchors.horizontalCenter: parent.horizontalCenter
                Text{
                    color: color_dark_black
                    text: qsTr("실패지수 : ")
                    font.pixelSize: 15
                    font.family: font_noto_r.name
                }
                Text{
                    id: text_error
                    property var textError: error
                    NumberAnimation on textError{
                        id: ani_texterror
                        to: error
                        from: text_error.textError
                        duration: 500
                    }
                    color: color_dark_black
                    text: Number(textError*100).toFixed(0) + " %";
                    font.pixelSize: 15
                    font.family: font_noto_r.name
                }
            }

        }

    }

}
