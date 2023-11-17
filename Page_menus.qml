import QtQuick 2.12
import QtGraphicalEffects 1.0
import QtQuick.Controls 2.12
import "."
import io.qt.Supervisor 1.0

Item {
    id: page_menus
    objectName: "page_menus"
    width: 1280
    height: 800


    function init(){

    }


    Rectangle{
        id: status_bar
        width: parent.width
        height: 60
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        color: "white"
    }

    Rectangle{
        id: rect_background
        width: parent.width
        height: parent.height - status_bar.height
        anchors.top: status_bar.bottom
        color: "#282828"
        Text{
            id: text_menu
            text: qsTr("메뉴")
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 150
            font.family: font_noto_r.name
            font.pixelSize: 40
            color:"white"
        }
        Image{
            id: rect_map
            width: 301
            height: 301
            anchors.top: text_menu.bottom
            anchors.topMargin: 50
            anchors.right: parent.horizontalCenter
            anchors.rightMargin: 30
            source: "icon/btn_map.png"
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    click_sound.play();
                    loadPage(pmap);
                }
            }
        }
        Image{
            id: rect_setting
            width: 301
            height: 301
            anchors.top: text_menu.bottom
            anchors.topMargin: 50
            anchors.left: parent.horizontalCenter
            anchors.leftMargin: 30
            source: "icon/btn_setting.png"
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    click_sound.play();
                    loadPage(psetting);
                }
            }
        }
    }

    property var size_menu: 100
    Rectangle{
        id: rect_menu_box
        width: 120
        height: width*3
        anchors.right: parent.right
        anchors.rightMargin: 50
        anchors.top: status_bar.bottom
        anchors.topMargin: 50
        color: "white"
        radius: 30
        Column{
            spacing: 10
            anchors.top: parent.top
            anchors.topMargin: 10
            anchors.horizontalCenter: parent.horizontalCenter
            Rectangle{
                id: btn_menu
                width: size_menu
                height: size_menu
                color: "transparent"
                anchors.horizontalCenter: parent.horizontalCenter
                Image{
                    source:"icon/btn_menu.png"
                    anchors.centerIn: parent
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            click_sound.play();
                            loadPage(pkitchen);
                        }
                    }
                }
            }
            Rectangle{// 구분바
                width: rect_menu_box.width
                height: 3
                color: "#f4f4f4"
            }
            Rectangle{
                id: btn_minimize
                width: size_menu
                height: size_menu
                color: "transparent"
                anchors.horizontalCenter: parent.horizontalCenter
                Rectangle{
                    width: size_menu
                    color: "transparent"
                    height: image_charge.height+text_charge.height
                    anchors.centerIn: parent
                    Image{
                        id: image_charge
                        scale: 1.2
                        source:"icon/btn_minimize.png"
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                    Text{
                        id: text_charge
                        text:qsTr("최소화")
                        font.family: font_noto_r.name
                        font.pixelSize: 15
                        horizontalAlignment: Text.AlignHCenter
                        color: "#525252"
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.top: image_charge.bottom
                        anchors.topMargin: 10
                    }
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        click_sound.play();
                        supervisor.writelog("[USER INPUT] Screen Minimized.");
                        mainwindow.showMinimized();
                    }
                }
            }
            Rectangle{// 구분바
                width: rect_menu_box.width
                height: 3
                color: "#f4f4f4"
            }
            Rectangle{
                width: size_menu
                height: size_menu
                color: "transparent"
                anchors.horizontalCenter: parent.horizontalCenter
                Rectangle{
                    width: size_menu
                    color: "transparent"
                    height: image_wait.height+text_wait.height
                    anchors.centerIn: parent
                    Image{
                        id: image_wait
                        scale: 1.2
                        source:"icon/icon_power.png"
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                    Text{
                        id: text_wait
                        text:qsTr("프로그램 종료")
                        font.family: font_noto_r.name
                        font.pixelSize: 15
                        color: "#525252"
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.top: image_wait.bottom
                        anchors.topMargin: 10
                    }
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        click_sound.play();
                        popup_program_exit.open();
//                        supervisor.programExit();
                    }
                }
            }
        }
    }

    Popup{
        id: popup_program_exit
        width: parent.width
        height: parent.height
        anchors.centerIn: parent
        visible: false

        background:Rectangle{
            anchors.fill: parent
            color: "#282828"
            opacity: 0.8
        }
//        Image{
//            id: image_location
//            source:"image/image_location.png"
//            width: 160
//            height: 160
//            anchors.horizontalCenter: parent.horizontalCenter
//            anchors.top: parent.top
//            anchors.topMargin: 200
//        }
        Column{
            spacing: 50
            anchors.centerIn: parent
            Text{
                anchors.horizontalCenter: parent.horizontalCenter
                font.family: font_noto_b.name
                font.pixelSize: 40
                color: "#12d27c"
                text: qsTr("프로그램을 종료<font color=\"white\">하시겠습니까?</font>")
            }
            Row{
                anchors.horizontalCenter: parent.horizontalCenter

                spacing: 30
                Rectangle{
                    width: 200
                    height: 90
                    radius: 20
                    color: "#d0d0d0"
                    Image{
                        id: image_no
                        source: "icon/btn_no.png"
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.leftMargin: 20
                    }
                    Text{
                        id:text_nono
                        text:qsTr("취소")
                        font.family: font_noto_b.name
                        font.pixelSize: 30
                        color:"#282828"
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: image_no.right
                        anchors.leftMargin : (parent.width - image_no.x - image_no.width)/2 - text_nono.width/2
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            click_sound.play();
                            popup_program_exit.close();
                        }
                    }
                }
                Rectangle{
                    width: 200
                    height: 90
                    radius: 20
                    color: "#d0d0d0"
                    Rectangle{
                        color:"white"
                        width: 190
                        height: 80
                        radius: 19
                        anchors.centerIn: parent
                    }
                    Image{
                        id: image_yes
                        source: "icon/btn_yes.png"
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.leftMargin: 20
                    }
                    Text{
                        text:qsTr("종료")
                        font.family: font_noto_b.name
                        font.pixelSize: 30
                        color:"#282828"
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: image_yes.right
                        anchors.leftMargin : (parent.width - image_yes.x - image_yes.width)/2 - width/2
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            click_sound.play();
                            supervisor.programExit();
                            popup_program_exit.close();
                        }
                    }
                }
                Rectangle{
                    width: 200
                    height: 90
                    radius: 20
                    color: "#d0d0d0"
                    Rectangle{
                        color:"white"
                        width: 190
                        height: 80
                        radius: 19
                        anchors.centerIn: parent
                    }
                    Image{
                        id: image_yes2
                        source: "icon/btn_yes.png"
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.leftMargin: 20
                    }
                    Text{
                        text:qsTr("다시시작")
                        font.family: font_noto_b.name
                        font.pixelSize: 30
                        color:"#282828"
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: image_yes2.right
                        anchors.leftMargin : (parent.width - image_yes2.x - image_yes2.width)/2 - width/2
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            click_sound.play();
                            supervisor.programRestart();
                            popup_program_exit.close();
                        }
                    }
                }
            }
        }
    }
}
