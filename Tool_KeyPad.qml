import QtQuick 2.12
import QtQuick.Controls 2.12
import "."

Popup {
    id: tool_keypad
    width: 260
    height: 380
    leftPadding: 0
    rightPadding: 0
    topPadding: 0
    bottomPadding: 0
    y: 400 - height/2 + statusbar.height/2
    x: 880 + width/2

    background:Rectangle{
        anchors.fill: parent
        color: "transparent"
    }

    property bool is_opened: false
    onOpened:{
        is_opened = true;
    }

    onClosed:{
        is_opened = false;
        owner.focus = false;
        owner.select(0,0);
    }



    property var owner

    property bool is_shift: false

    property var keysize: 58
    property var keytopmargin: 15
    property var keyrightmargin: 13

    property var textsize: 25

    property color color_default: "white"
    property color color_highlight: "#12d27c"
    Rectangle{
        id: rect_keypad
        width: parent.width
        height: parent.height
        color: color_dark_navy
        radius: 5
        Column{
            anchors.centerIn: parent
            spacing: keytopmargin
            Text{
                anchors.horizontalCenter: parent.horizontalCenter
                font.family: font_noto_r.name
                font.pixelSize: 16
                color: "white"
                text: "숫자키를 사용해 입력하세요"
            }

            Column{
                spacing: keytopmargin
                anchors.horizontalCenter: parent.horizontalCenter
                Row{
                    anchors.horizontalCenter: parent.horizontalCenter
                    spacing: keyrightmargin
                    Repeater{
                        id: keys_11
                        model: ["7","8","9"]
                        Rectangle{
                            width: keysize
                            height: width
                            radius: 5
                            color: color_default
                            Text{
                                anchors.centerIn: parent
                                text: modelData
                                font.family: font_noto_r.name
                                font.pixelSize: textsize
                            }
                            MouseArea{
                                anchors.fill: parent
                                onClicked:{
                                    emitter.keyPressed(owner,modelData);
                                }
                            }
                        }
                    }
                }
                Row{
                    anchors.horizontalCenter: parent.horizontalCenter
                    spacing: keyrightmargin
                    Repeater{
                        id: keys_22
                        model: ["4","5","6"]
                        Rectangle{
                            width: keysize
                            height: width
                            radius: 5
                            color: color_default
                            Text{
                                anchors.centerIn: parent
                                text: modelData
                                font.family: font_noto_r.name
                                font.pixelSize: textsize
                            }
                            MouseArea{
                                anchors.fill: parent
                                onClicked:{
                                    emitter.keyPressed(owner,modelData);

                                }
                            }
                        }
                    }
                }
                Row{
                    anchors.horizontalCenter: parent.horizontalCenter
                    spacing: keyrightmargin
                    Repeater{
                        id: keys_33
                        model: ["1","2","3"]
                        Rectangle{
                            width: keysize
                            height: width
                            radius: 5
                            color: color_default
                            Text{
                                anchors.centerIn: parent
                                text: modelData
                                font.family: font_noto_r.name
                                font.pixelSize: textsize
                            }
                            MouseArea{
                                anchors.fill: parent
                                onClicked:{
                                    emitter.keyPressed(owner,modelData);
                                }
                            }
                        }
                    }
                }
                Row{
                    anchors.horizontalCenter: parent.horizontalCenter
                    spacing: keyrightmargin
                    Rectangle{
                        id: btn_0
                        width: keysize*2 + keyrightmargin
                        height: keysize
                        radius: 5
                        color: color_default
                        Text{
                            anchors.centerIn: parent
                            text: "0"
                            font.family: font_noto_r.name
                            font.pixelSize: textsize
                        }
                        MouseArea{
                            anchors.fill: parent
                            onClicked:{
                                emitter.keyPressed(owner,"0");

                            }
                        }
                    }
                    Rectangle{
                        width: keysize
                        height: width
                        radius: 5
                        color: color_default
                        Text{
                            anchors.centerIn: parent
                            text: "."
                            font.family: font_noto_r.name
                            font.pixelSize: textsize
                        }
                        MouseArea{
                            anchors.fill: parent
                            onClicked:{
                                emitter.keyPressed(owner,".");
                            }
                        }
                    }
                }
            }
        }
    }
}
