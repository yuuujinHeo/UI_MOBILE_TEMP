import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

Popup{
    id: popup_test_tts
    anchors.centerIn: parent
    width: 700
    height: 600
    background:Rectangle{
        anchors.fill: parent
        color: "transparent"
    }

    Rectangle{
        width: parent.width
        height: parent.height
        radius: 20
        color: color_dark_navy

        Column{
            anchors.centerIn: parent
            spacing: 50
            TextField{
                anchors.horizontalCenter: parent.horizontalCenter
                id: tfield_text
                width: 400
                height: 50
            }
            Row{
                anchors.horizontalCenter: parent.horizontalCenter
                Rectangle{
                    width: 160
                    radius: 10
                    height: 60
                    Text{
                        anchors.centerIn: parent
                        text: qsTr(" 즉시재생 ")
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked:{
                            supervisor.makeTTS(tfield_text.text);
                            supervisor.playTTS();
                        }
                    }
                }
            }

        }
    }
}
