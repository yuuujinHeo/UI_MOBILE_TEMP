import QtQuick 2.12
import "."

Item {
    property var to: 100
    property var from: 0
    property var value: 0
    property color background_color: color_gray
    property bool leveling: false
    property bool warning: false
    property var value_red: 0
    clip: true
    property var value_yellow: 0
    property var value_margin: 0
    property color color: color_blue
    onWidthChanged: {
        progress.width = calWidth();
    }
    onToChanged: {
        value_red = from + (to-from)*0.2;
        value_yellow = from + (to-from)*0.6;
    }
    onFromChanged: {
        value_red = from + (to-from)*0.2;
        value_yellow = from + (to-from)*0.6;
    }

    onValueChanged: {
        progress.width = calWidth();

    }
    function calWidth(){
        return width*value/(to-from);
    }
    Rectangle{
        id: background
        width: parent.width
        height: parent.height
        radius: 5
        color: background_color
    }
    Rectangle{
        id: progress
        width: 0
        Behavior on width {
            NumberAnimation{
                duration: 500
            }
        }
        height: parent.height
        radius: 5
        color: {
            if(leveling){
                if(value < value_red){
                    color_red
                }else if(value < value_yellow){
                    color_yellow
                }else{
                    color_blue
                }
            }else if(warning){
                if(value > value_margin){
                    color_red
                }else{
                    color_blue
                }
            }else{
                color_blue
            }
        }
    }
}
