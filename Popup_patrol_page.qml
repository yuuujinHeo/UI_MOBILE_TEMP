import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.0
import io.qt.Supervisor 1.0
import QtMultimedia 5.12
import "."

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
                            supervisor.setSetting("setting","UI/patrol_text_1",tfield_1.text);
                            supervisor.setSetting("setting","UI/patrol_text_2",tfield_2.text);
                            popup_setting_patrolpage.close();
                        }
                    }
                    Item_buttons{
                        width: 130
                        height: 60
                        type: "round_text"
                        text: qsTr("초기화")
                        onClicked: {
                            tfield_1.text = supervisor.getSetting("setting","UI","patrol_text_1");
                            tfield_2.text = supervisor.getSetting("setting","UI","patrol_text_2");
                        }
                    }
                    Item_buttons{
                        width: 140
                        height: 60
                        type: "round_text"
                        text: qsTr("취 소")
                        onClicked: {
                            popup_setting_patrolpage.close();
                        }
                    }

                }
            }

            Row{
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
                    width: 1280-850
                    height: 800-150
                    color: color_light_gray
                    Column{
                        spacing: 20
                        anchors.centerIn: parent
                        Text{
                            text: qsTr("이미지 설정")
                            anchors.horizontalCenter: parent.horizontalCenter
                        }
                        ComboBox{
                            id: combo_image
                            model:["robot1","robot2","robot3","robot4","robot5"]
                            onCurrentIndexChanged: {
                                if(currentIndex == 0){
                                    move_page.setting_patrol_image = "image/robot_moving.png";
                                }else if(currentIndex == 1){
                                    move_page.setting_patrol_image = "image/robot_callme.png";
                                }else if(currentIndex == 2){
                                    move_page.setting_patrol_image = "image/robot_clear.png";
                                }else if(currentIndex == 3){
                                    move_page.setting_patrol_image = "image/robot_head.png";
                                }else if(currentIndex == 4){
                                    move_page.setting_patrol_image = "image/rainbow3.png";

                                }
                            }
                            currentIndex: parseInt(supervisor.getSetting("setting","UI","patrol_image"))

                            anchors.horizontalCenter: parent.horizontalCenter
                            width: 300
                            height: 50
                        }
                        Column{
                            anchors.horizontalCenter: parent.horizontalCenter
                            spacing: 3
                            Row{
                                anchors.horizontalCenter: parent.horizontalCenter
                                spacing: 20
                                CheckBox{
                                    id: cb_resolution
                                    anchors.verticalCenter: parent.verticalCenter
                                    checked: supervisor.getSetting("setting","UI","patrol_image_fix")==="true"
                                    onCheckedChanged: {
                                        if(checked){
                                            tfield_image_height.enabled = false;
                                            tfield_image_height.text = move_page.setImageHeight();
                                        }else{
                                            tfield_image_height.enabled = true;
                                            tfield_image_height.text = move_page.setImageHeight();
                                        }
                                    }
                                }
                                Text{
                                    anchors.verticalCenter: parent.verticalCenter
                                    text: qsTr("원본비율 유지")
                                }
                            }

                            Row{
                                spacing: 10
                                Text{
                                    anchors.verticalCenter: parent.verticalCenter
                                    text:qsTr("이미지 너비")
                                }
                                TextField{
                                    id: tfield_image_width
                                    width: 120
                                    anchors.verticalCenter: parent.verticalCenter
                                    height: 40
                                    horizontalAlignment: TextField.AlignHCenter
                                    text: move_page.setting_patrol_image_width
                                    MouseArea{
                                        anchors.fill: parent
                                        onClicked: {
                                            click_sound.play();
                                            if(keypad.is_opened){
                                                keypad.owner = tfield_image_width;
                                                tfield_image_width.selectAll();
                                            }else{
                                                keypad.owner = tfield_image_width;
                                                tfield_image_width.selectAll();
                                                keypad.open();
                                            }
                                        }
                                    }
                                    onTextChanged: {
                                        var widthvalue = parseInt(text);
                                        if(widthvalue > 0 && widthvalue < 1281){
                                            if(cb_resolution.checked){
                                                tfield_image_height.text = move_page.getImageHeight(widthvalue);
                                            }
                                        }
                                    }
                                }
                                Item_buttons{
                                    width: 70
                                    height: 40
                                    anchors.verticalCenter: parent.verticalCenter
                                    type: "round_text"
                                    text: qsTr("적용")
                                    fontsize: 15
                                    onClicked:{
                                        move_page.setting_patrol_image_width = parseInt(tfield_image_width.text);
                                    }
                                }
                            }
                            Row{
                                spacing: 10
                                Text{
                                    anchors.verticalCenter: parent.verticalCenter
                                    text:qsTr("이미지 높이")
                                }
                                TextField{
                                    id: tfield_image_height
                                    width: 120
                                    horizontalAlignment: TextField.AlignHCenter
                                    enabled: !cb_resolution.checked
                                    anchors.verticalCenter: parent.verticalCenter
                                    height: 45
                                    text: move_page.setting_patrol_image_height
                                    MouseArea{
                                        anchors.fill: parent
                                        onClicked: {
                                            click_sound.play();
                                            if(keypad.is_opened){
                                                keypad.owner = tfield_image_height;
                                                tfield_image_height.selectAll();
                                            }else{
                                                keypad.owner = tfield_image_height;
                                                tfield_image_height.selectAll();
                                                keypad.open();
                                            }
                                        }
                                    }
                                }
                                Item_buttons{
                                    width: 70
                                    height: 40
                                    enabled: !cb_resolution.checked
                                    anchors.verticalCenter: parent.verticalCenter
                                    type: "round_text"
                                    fontsize: 15
                                    text: qsTr("적용")
                                    onClicked:{
                                        move_page.setting_patrol_image_height = parseInt(tfield_image_height.text);
                                    }
                                }
                            }
                        }

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
                                width: 300
                                height: 40
                                text:supervisor.getSetting("setting","UI","patrol_text_1")
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        click_sound.play();
                                        if(keyboard.is_opened){
                                            keyboard.owner = tfield_1;
                                            tfield_1.selectAll();
                                        }else{
                                            keyboard.owner = tfield_1;
                                            tfield_1.selectAll();
                                            keyboard.open();
                                        }
                                    }
                                }
                            }
                            Text{
                                text: qsTr("문구2 : ")
                            }
                            TextField{
                                id: tfield_2
                                width: 300
                                height: 40
                                text:supervisor.getSetting("setting","UI","patrol_text_2")
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        click_sound.play();
                                        if(keyboard.is_opened){
                                            keyboard.owner = tfield_2;
                                            tfield_2.selectAll();
                                        }else{
                                            keyboard.owner = tfield_2;
                                            tfield_2.selectAll();
                                            keyboard.open();
                                        }
                                    }
                                }
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
