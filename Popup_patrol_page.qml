import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.0
import io.qt.Supervisor 1.0
import QtMultimedia 5.12

Popup {
    id: popup_setting_patrolpage
    width: 1280
    height: 800
    closePolicy: Popup.NoAutoClose
    leftPadding: 0
    rightPadding: 0
    topPadding: 0
    bottomPadding: 0
    background:Rectangle{
        anchors.fill: parent
        color: "#282828"
        opacity: 0.8
    }
    onOpened:{

    }
    onClosed:{

    }
    Rectangle{
        id: parentrect
        width: 1280
        height: 800
        anchors.centerIn: parent
        color:"transparent"
        Column{
            spacing: 5
            Rectangle{
                id: rect_list_top
                height: 150
                width: parentrect.width
                color: color_dark_navy
                Text{
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 50
                    color: "white"
                    font.family: font_noto_b.name
                    font.bold: true
                    text: qsTr("순회 중 표시화면 설정")
                    font.pixelSize: 40
                }

                Row{
                    anchors.rightMargin: 30
                    anchors.right: parent.right
                    anchors.verticalCenter: parent.verticalCenter
                    spacing: 20
                    Item_buttons{
                        width: 130
                        height: 60
                        type: "round_text"
                        text: qsTr("저 장")
                        onClicked: {
                            click_sound.play();;
                            popup_setting_patrolpage.close();
                        }
                    }
                    Item_buttons{
                        width: 130
                        height: 60
                        type: "round_text"
//                            visible: false
                        text: qsTr("초기화")
                        onClicked: {
                            click_sound.play();;
                        }
                    }
                    Item_buttons{
                        width: 140
                        height: 60
                        type: "round_text"
                        text: "취 소"
                        onClicked: {
                            click_sound.play();;
                            popup_setting_patrolpage.close();
                        }
                    }

                }
            }

            Row{
                spacing: 50
                anchors.horizontalCenter: parent.horizontalCenter
                Rectangle{
                    width: 850
                    height: width*800/1280
                    anchors.verticalCenter: parent.verticalCenter
                    Page_moving{
                        id: move_page
                        anchors.fill: parent
                        setting_patrol_mode: true
                    }
                }

                Rectangle{
                    id: rect_patrol_set
                    width: 1280-800
                    height: 800-150
                    color: color_light_gray
                    Column{
                        spacing: 20
                        anchors.centerIn: parent
                        Text{
                            text: qsTr("텍스트 설정")
                            anchors.horizontalCenter: parent.horizontalCenter
                        }
                        Grid{
                            columns: 2
                            rows: 2
                            spacing: 5
                            horizontalItemAlignment: Grid.AlignHCenter
                            verticalItemAlignment: Grid.AlignVCenter
                            Text{
                                text: qsTr("문구1 : ")
                            }
                            TextField{
                                id: tfield_1
                                width: 220
                                height: 40
                            }
                            Text{
                                text: qsTr("문구2 : ")
                            }
                            TextField{
                                id: tfield_2
                                width: 220
                                height: 40
                            }
                        }
                        Rectangle{
                            width: 150
                            height: 70
                            radius: 10
                            color: "black"
                            Text{
                                anchors.centerIn: parent
                                color: "white"
                                font.pixelSize: 25
                                text: qsTr("적 용")
                                font.family: font_noto_r.name
                            }
                            MouseArea{
                                anchors.fill: parent
                                onClicked:{
                                    click_sound.play();;
                                    move_page.setTempText(tfield_1.text, tfield_2.text);
                                }
                            }
                        }
                    }
                }
            }
        }
    }

}
