import QtQuick 2.15
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
//import QtQuick.Dialogs 1.2
import Qt.labs.platform 1.0 as Platform
import QtQuick.Shapes 1.15
//import QtQuick.Shapes 1.12
import QtGraphicalEffects 1.0
import QtMultimedia 5.12
import "."
import io.qt.Supervisor 1.0

Item{
    id: item_localization
    width: 1280
    height: 800-statusbar.height

    property var local_find_state: -1
    property bool show_restart: false
    property bool show_timeout: false
    property bool show_debug: false
    property bool show_success: false
    property bool show_failed: false

    property bool start_mode: false
    property bool mapping_mode: false
    property bool auto_init: false


    signal passed;
    signal confirmed;
    signal backed;

    Component.onCompleted: {
        popup_loading.close();
    }

    Component.onDestruction: {
        map.setEnable(false);
    }

    Rectangle{
        id: background
        anchors.fill: parent
        color: color_light_gray
    }

    function retry(){
        if(auto_init){
            supervisor.writelog("[UI-LOCALIZATION] Retry Localization (auto_init)")
            timer_check_localization.start();
            supervisor.slam_autoInit();
        }else{
            supervisor.writelog("[UI-LOCALIZATION] Retry Localization")
            timer_check_localization.start();
//            supervisor.slam_autoInit();
            supervisor.slam_restInit();
        }
    }

    Timer{
        running: auto_init
        interval: 500
        onTriggered:{
            supervisor.writelog("[UI-LOCALIZATION] Auto Localization")
            timer_check_localization.start();
            supervisor.slam_autoInit();
        }
    }
    Timer{
        running: true
        interval: 1000
        onTriggered:{
            supervisor.writelog("[UI-LOCALIZATION] Set Motor Lock : False")
            supervisor.setMotorLock(false);
        }
    }

    Timer{
        id: timer_check_localization
        running: auto_init
        repeat: true
        interval: 500
        property int timeout_cnt: 0
        onTriggered: {
            local_find_state = supervisor.getLocalizationState();
            if(local_find_state===0){//not ready
                text_finding.text = qsTr("로봇의 위치를 찾고 있습니다.")
                timeout_cnt = 0;
                show_success = false;
                show_failed = false;
                show_timeout = false;
                btn_do_autoinit.running = false;
                show_restart = false;
            }else if(local_find_state === 1){
                if(timeout_cnt++ > 20){
                    show_timeout = true;
                }
                btn_do_autoinit.running = true;
                text_finding.text = qsTr("로봇의 위치를 찾고 있습니다..")
                show_success = false;
                show_failed = false;
            }else if(local_find_state === 2){//success
                timeout_cnt = 0;
                show_timeout = false;
                text_finding.text = qsTr("로봇의 위치를 찾았습니다.\n로봇을 회전시켜도 값이 정상이라면 확인버튼을 눌러주세요")
                show_success = true;
                show_failed = true;
                btn_do_autoinit.running = false;
            }else if(local_find_state === 3){//failed
                timeout_cnt = 0;
                show_timeout = false;
                text_finding.text = qsTr("로봇의 위치를 찾지 못했습니다")
                show_success = false;
                show_failed = true;
                btn_do_autoinit.running = false;
            }else{
                show_timeout = false;
                text_finding.text = qsTr("로봇과 연결이 되지 않았습니다")
            }

            if(!supervisor.getIPCConnection()){
                local_find_state = 10;
                show_restart = true;
                show_success = false;
                show_failed = false;
                text_finding.text = qsTr("로봇과 연결이 되지 않았습니다")
//                timer_check_localization.stop();
            }
        }
    }

    Rectangle{
        id: initPage_main
        visible: !auto_init && ( local_find_state === -1 || local_find_state === 0)
        anchors.fill: parent
        color: color_light_gray
        Text{
            id: text_notice4
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 200
            horizontalAlignment: Text.AlignHCenter
            color: color_dark_gray
            font.family: font_noto_b.name
            text: qsTr("로봇을 대기위치로 이동시켜 주세요\n이동하신 후 아래 버튼을 눌러주세요")
            font.pixelSize: 50
        }
        Rectangle{
            id: btn_slam_do_init
            width: 300
            height: 120
            radius: 60
            opacity: 0
            color: color_green
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 100
            Text{
                id: text_slam_do_init
                anchors.centerIn: parent
                text: qsTr("시   작")
                color: "white"
                font.family: font_noto_r.name
                font.pixelSize: 40
            }
            MouseArea{
                anchors.fill: parent
                onPressed:{
                    click_sound.play();
                    parent.color = color_mid_green;
                }
                onReleased: {
                    parent.color = color_green;
                }
                onClicked: {
                    timer_check_localization.start();
                    supervisor.writelog("[USER INPUT] INIT PAGE : DO LOCALIZATION")
//                    supervisor.slam_autoInit();

                    supervisor.slam_restInit();
//                            update_timer.stop();
                }
            }
        }
        DropShadow{
            anchors.fill: btn_slam_do_init
            radius: 10
            color: color_dark_gray
            source: btn_slam_do_init
        }
        Rectangle{
            id: btn_slam_manual_init
            width: 188
            height: 100
            radius: 60
            color: "transparent"
            border.width: 3
            visible: show_debug && start_mode
            border.color: "#e5e5e5"
            anchors.left: btn_slam_do_init.right
            anchors.leftMargin: 30
            anchors.verticalCenter: btn_slam_do_init.verticalCenter
            Column{
                spacing: 5
                anchors.centerIn: parent
                Image{
                    width: 30
                    height: 30
                    source:"icon/btn_wait.png"
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                Text{
                    id: text_slam_pass
                    text: qsTr("맵 새로만들기")
                    font.family: font_noto_r.name
                    font.pixelSize: 15
                }
            }
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    click_sound.play();
                    supervisor.writelog("[USER INPUT] INIT PAGE : NEW MAPPING")
                    loadPage(pmapping);
                }
            }
        }
        Rectangle{
            id: btn_slam_pass
            width: 188
            height: 100
            radius: 60
            color: "transparent"
            border.width: 3
            visible: show_debug
            border.color: "#e5e5e5"
            anchors.left: btn_slam_manual_init.right
            anchors.leftMargin: 30
            anchors.verticalCenter: btn_slam_do_init.verticalCenter
            Column{
                spacing: 5
                anchors.centerIn: parent
                Image{
                    id: image_charge1
                    width: 30
                    height: 30
                    source:"icon/icon_remove.png"
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                Text{
                    text: qsTr("넘어가기")
                    font.family: font_noto_r.name
                    font.pixelSize: 15
                }
            }
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    click_sound.play();
                    passed();
                }
            }
        }
    }

    Rectangle{
        id: iniPage_localization
        visible: !initPage_main.visible
        width: parent.width
        height: parent.height - statusbar.height
        anchors.bottom: parent.bottom
        color: color_light_gray
        Text{
            id: text_finding
            text: qsTr("로봇의 위치를 찾고 있습니다")
            color: color_dark_navy
            Behavior on opacity {
                NumberAnimation{
                    duration : 500
                }
            }
            horizontalAlignment:Text.AlignHCenter
            font.pixelSize: 40
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 50
            font.family: font_noto_b.name
        }
        Item_progressCircle{
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            anchors.verticalCenterOffset: 50
        }
        Column{
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            anchors.bottomMargin: 50
            anchors.rightMargin: 50
            spacing: 30
            Item_buttons{
                id: btn_init_pass
                visible: show_debug || show_timeout || show_restart
                width: 200
                height: 80
                type: "round_text"
                text:qsTr("넘어가기")
                onClicked: {
                    supervisor.writelog("[ANNOTATION] Localization : Pass");
                    passed();
                }
            }
            Item_buttons{
                id: btn_init_restart
                visible: show_restart
                width: 200
                height: 80
                type: "round_text"
                text:qsTr("프로그램 재시작")
                onClicked: {
                    supervisor.writelog("[ANNOTATION] Localization : Restart");
                    supervisor.programRestart();
                }
            }
            Item_buttons{
                id: btn_init_remapping
                visible: (show_debug || show_timeout || show_failed) && mapping_mode
                width: 200
                height: 80
                type: "round_text"
                text:qsTr("맵 다시생성")
                onClicked: {
                    supervisor.writelog("[ANNOTATION] Localization : pass to mapping");
                    loadPage(pmapping);
                }
            }
            Item_buttons{
                id: btn_init_manual
                visible: show_timeout || show_failed || show_debug
                width: 200
                height: 80
                type: "round_text"
                text: qsTr("수동지정(전문가)")
                onClicked: {
                    supervisor.writelog("[ANNOTATION] Localization : Failed")
                    popup_init_manual.open();
                }
            }
            Item_buttons{
                id: btn_init_success
                visible: show_success //|| show_failed
                width: 200
                height: 80
                type: "round_text"
                text:qsTr("확 인")
                onClicked: {
                    supervisor.writelog("[UI] PageLocalization : Success");
                    confirmed();

                }
            }
        }
        Item_buttons{
            id: btn_init_retry
            visible: show_timeout || show_debug || show_timeout || show_failed || show_success
            width: 200
            height: 80
            type: "round_text"
            text: qsTr("다시시도")
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.bottomMargin: 50
            anchors.leftMargin: 50
            onClicked: {
                retry();
            }
        }
    }

    MouseArea{
        width: 50
        height: 50
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        property var count: 0
        onClicked:{
            click_sound.play();
            if(count++ > 4){
                count = 0;
                show_debug = true;
            }
        }
    }
    Popup{
        id: popup_init_manual
        width: parent.width
        height: parent.height
        onOpened: {
            map.setViewer("localization");
            map.setEnable(true);

        }
        onClosed:{
            map.setEnable(false);
        }

        Rectangle{
            id: manual_init
            width: parent.width
            height: parent.height// - statusbar.height
            anchors.bottom: parent.bottom
            color: color_navy
            Text{
                text:qsTr("로봇의 위치를 맵 상에서 표시해주세요")
                font.pixelSize: 30
                horizontalAlignment: Text.AlignHCenter
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                anchors.topMargin: 30
                color: "white"
                font.family: font_noto_b.name
            }
            Item_buttons{
                id: btn_right23
                width: 200
                height: 80
                type: "round_text"
                text: qsTr("종 료")
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                anchors.bottomMargin: 50
                anchors.rightMargin: 50
                onClicked: {
                    popup_init_manual.close();
                }
            }
            Column{
                anchors.left: parent.left
                anchors.leftMargin: 30
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 100
                spacing: 50
                Item_buttons{
                    width: 200
                    height: 80
                    type: "round_text"
                    selected: map.tool==="move"
                    text: qsTr("이 동")
                    onClicked: {
                        map.setTool("move");
                    }
                }
                Item_buttons{
                    width: 200
                    height: 80
                    type: "round_text"
                    selected: map.tool==="slam_init"
                    text:  qsTr("수동 지정")
                    onClicked: {
                        map.setTool("slam_init");
                        supervisor.setInitCurPos();
                        supervisor.slam_setInit();
                    }
                }
                Item_buttons{
                    width: 200
                    height: 80
                    visible: false
                    type: "round_text"
                    text:  qsTr("다시 시도")
                    onClicked: {
                        map.setTool("move");
                        retry();
                    }
                }
                Item_buttons{
                    id: btn_do_autoinit
                    width: 200
                    height: 100
                    running: false
                    visible: false
                    type: "start_progress"
                    text: qsTr("자동위치찾기\n(1분소요)")
                    shadowcolor: color_dark_black
                    onClicked: {
                        print("init autoinit");
                        map.setTool("move");
                        supervisor.slam_fullautoInit();
                    }
                }
            }
        }
        MAP_FULL2{
            id: map
            enabled: false
            objectName: "annot_local"
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 50
            anchors.horizontalCenter: parent.horizontalCenter
            width: 600
            height: 600
            Component.onCompleted: {
                supervisor.setMapSize(objectName,width,height);
            }
        }

    }

}

