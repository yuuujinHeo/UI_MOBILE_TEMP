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
        Rectangle{
            id: rect_map
            width: 301
            height: 301
            radius: 25
            anchors.top: text_menu.bottom
            anchors.topMargin: 50
            anchors.right: parent.horizontalCenter
            anchors.rightMargin: 30
            color: color_dark_black
            border.color: "white"
            border.width: 5
            Column{
                anchors.centerIn: parent
                Image{
                    width: 100
                    height: 110
                    sourceSize.height: 110
                    antialiasing: true
                    sourceSize.width: 100
                    source: "icon/icon_map.png"
                    anchors.horizontalCenter: parent.horizontalCenter
                    ColorOverlay{
                        anchors.fill: parent
                        color: "white"
                        source: parent
                    }
                }
                Text{
                    text: qsTr("맵")
                    color: "white"
                    font.pixelSize: 45
                    font.family: font_noto_b.name
                    anchors.horizontalCenter: parent.horizontalCenter
                }
            }
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    click_sound.play();
                    popup_password.open();
                }
            }

        }
        Rectangle{
            id: rect_setting
            width: 301
            height: 301
            radius: 25
            color: color_dark_black
            border.color: "white"
            border.width: 5
            anchors.top: text_menu.bottom
            anchors.topMargin: 50
            anchors.left: parent.horizontalCenter
            anchors.leftMargin: 30
            Column{
                anchors.centerIn: parent
                Image{
                    width: 100
                    height: 100
                    sourceSize.height: 100
                    antialiasing: true
                    sourceSize.width: 100
                    source: "icon/icon_setting2.png"
                    anchors.horizontalCenter: parent.horizontalCenter
                    ColorOverlay{
                        anchors.fill: parent
                        color: "white"
                        source: parent
                    }
                }
                Text{
                    text: qsTr("설 정")
                    color: "white"
                    font.pixelSize: 45
                    font.family: font_noto_b.name
                    anchors.horizontalCenter: parent.horizontalCenter
                }
            }
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    click_sound.play();
                    loadPage(psetting);
                }
            }

        }

    }


    Item_menubar{
        id: menubar
        anchors.right: parent.right
        anchors.rightMargin: 50
        anchors.top: status_bar.bottom
        anchors.topMargin: 50
        Component.onCompleted: {
            addMenu("","icon/btn_menu.png");
            //addMenu(qsTr("최소화"),"icon/icon_minimize.png");
            //addMenu(qsTr("프로그램 종료"),"icon/icon_power.png");
        }
        onMenu1_clicked: {
            click_sound.play();
            loadPage(pkitchen);
        }
        onMenu2_clicked: {
            click_sound.play();
            supervisor.writelog("[USER INPUT] Screen Minimized.");
            mainwindow.showMinimized();
        }
        onMenu3_clicked: {
            click_sound.play();;
            popup_program_exit.open();
        }
    }

    Popup_password{
        id: popup_password
        onLogined:{
            loadPage(pmap);
            popup_password.close();
        }
        onLogin_rainbow:{
            loadPage(pmap);
            popup_password.close();
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
                        width: 50
                        height: 50
                        sourceSize.width: width
                        sourceSize.height: height
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
                            click_sound.play();;
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
                        source: "icon/icon_yes.png"
                        width: 50
                        height: 50
                        sourceSize.width: width
                        sourceSize.height: height
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
                            click_sound.play();;
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
                        source: "icon/icon_yes.png"
                        width: 50
                        height: 50
                        sourceSize.width: width
                        sourceSize.height: height
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
                            click_sound.play();;
                            supervisor.programRestart();
                            popup_program_exit.close();
                        }
                    }
                }
            }
        }
    }
}
