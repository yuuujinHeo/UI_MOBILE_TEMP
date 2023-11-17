import QtQuick 2.12
import QtQuick.Controls 2.12



Popup{
    id: popup_help
    anchors.centerIn: parent
    width: 1000
    height: 500
    property string titlestr: ""
    onOpened:{
        model_lines.clear();
    }
    function setTitle(t){
        titlestr = t;
    }
    function addLine(l){
        model_lines.append({"line":l});
    }
    background: Rectangle{
        anchors.fill:parent
        color: "black"
        opacity: 0.8
    }
    Column{
        anchors.fill: parent
        Rectangle{
            width: parent.width
            color: "transparent"
            height: 100
            Text{
                text: popup_help.titlestr
                font.family: font_noto_b.name
                font.pixelSize: 40
                color: "white"
                anchors.centerIn: parent
            }
        }
        Rectangle{
            width: parent.width*0.6
            anchors.horizontalCenter: parent.horizontalCenter
            color: "white"
            height: 2
        }
        Rectangle{
            width: parent.width
            color: "transparent"
            height: parent.height - 102
            Column{
                anchors.centerIn: parent
                spacing: 5
                Repeater{
                    anchors.horizontalCenter: parent.horizontalCenter
                    model:ListModel{id:model_lines}
                    Text{
                        text: line
                        color: "white"
                        horizontalAlignment: Text.AlignHCenter
                        font.family: font_noto_r.name
                        font.pixelSize: 20
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                }
            }
        }
    }
}
