import QtQuick 2.15
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.0
import "."
import io.qt.Supervisor 1.0
// import Qt.labs.platform 1.0 as Platform
// import QtQuick.Shapes 1.15
// import QtMultimedia 5.12

Item{
    id: item_localization
    width: 1280
    height: 800-statusbar.height

    property int local_find_state: -1
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
        supervisor.resetLocalizationConfirm();
        // supervisor.resetLocalization();
        if(auto_init){
            supervisor.writelog("[INIT] Localization : Auto Init")
            timer_check_localization.start();
            supervisor.slam_autoInit();
        }
        supervisor.writelog("[INIT] Localization : Motor Lock off")
        supervisor.setMotorLock(false);

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
            supervisor.writelog("[INIT] Localization : Retry (auto_init)")
            timer_check_localization.start();
            supervisor.slam_autoInit();
        }else{
            supervisor.writelog("[INIT] Localization : Retry (rest_init)")
            timer_check_localization.start();
            supervisor.slam_restInit();
        }
    }

    Timer{
        id: timer_check_localization
        property int timeout_cnt: 0
        running: auto_init
        repeat: true
        interval: 500
        onTriggered: {
            local_find_state = supervisor.getLocalizationState();
            if(local_find_state===0){//not ready
                text_finding.text = qsTr("로봇이 위치를 찾고 있습니다..") //로봇의 위치를 찾고 있습니다
                timeout_cnt = 0;
                show_success = false;
                show_failed = false;
                show_timeout = false;
                show_restart = false;
            }else if(local_find_state === 1){
                if(timeout_cnt++ > 20){
                    show_timeout = true;
                }
                text_finding.text = qsTr("로봇이 위치를 찾고 있습니다...") //로봇의 위치를 찾고 있습니다
                show_success = false;
                show_failed = false;
            }else if(local_find_state === 2){//success
                timeout_cnt = 0;
                show_timeout = false;
                text_finding.text = qsTr("로봇이 위치를 찾았습니다.\n로봇을 회전시켜도 값이 정상이라면 확인버튼을 눌러주세요") //로봇의 위치를 찾고 있습니다
                show_success = true;
                show_failed = true;
            }else if(local_find_state === 3){//failed
                timeout_cnt = 0;
                show_timeout = false;
                text_finding.text = qsTr("로봇이 위치를 찾지 못했습니다") //로봇의 위치를 찾지 못했습니다
                show_success = false;
                show_failed = true;
            }else if(local_find_state === 5){// success but far away
                timeout_cnt = 0;
                show_timeout = false;
                text_finding.text = qsTr("로봇이 대기위치 상에 있지 않습니다.\n 로봇을 대기위치에 가져다 놓은다음 다시시도해 주세요.") //로봇의 위치를 찾았지만 대기위치와 멀리 떨어져 있어 위치추정이 잘못되어있을 가능성 높음.
                show_success = false;
                show_failed = true;
            }else{
                show_timeout = false;
                text_finding.text = qsTr("주행 준비가 되지 않았습니다") //로봇과 연결이 되지 않았습니다
            }

            if(!supervisor.getIPCConnection()){
                local_find_state = 10;
                show_restart = true;
                show_success = false;
                show_failed = false;
                text_finding.text = qsTr("주행 준비가 되지 않았습니다") //로봇과 연결이 되지 않았습니다
            }
        }
    }

    Rectangle{
        id: initPage_main
        visible: !auto_init && ( local_find_state === -1 || local_find_state === 0)
        anchors.fill: parent
        color: color_light_gray
        Column{
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 200
            Text{
                id: text_notice4
                anchors.horizontalCenter: parent.horizontalCenter
                color: color_dark_gray
                font.family: font_noto_b.name
                text: qsTr("로봇을 <font color=\"#12d27c\">대기위치로 이동</font>시켜 주세요")
                font.pixelSize: 60
            }
            Text{
                anchors.horizontalCenter: parent.horizontalCenter
                color: color_dark_gray
                font.family: font_noto_b.name
                text: qsTr("이동하신 후 시작 버튼을 눌러주세요")
                font.pixelSize: 60
            }
        }

        Rectangle{
            id: btn_slam_do_init
            width: 340
            height: 150
            radius: 70
            opacity: 0
            color: color_green
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 130
            Text{
                id: text_slam_do_init
                anchors.centerIn: parent
                text: qsTr("시    작")
                color: "white"
                font.family: font_noto_r.name
                font.pixelSize: 55
            }
            MouseArea{
                anchors.fill: parent
                onPressed:{
                    supervisor.playSound('click');
                    parent.color = color_mid_green;
                }
                onReleased: {
                    parent.color = color_green;
                }
                onClicked: {
                    show_debug = false;
                    timer_check_localization.start();
                    supervisor.writelog("[INIT] Localization : Do Rest Init")
                    supervisor.slam_restInit();
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
            height: 110
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
                    sourceSize.width: width
                    sourceSize.height: height
                    source:"icon/icon_map.png"
                    anchors.horizontalCenter: parent.horizontalCenter
                    ColorOverlay{
                        source: parent
                        anchors.fill: parent
                        color: color_icon_gray
                    }
                }
                Text{
                    id: text_slam_pass
                    text: qsTr("맵 새로만들기")
                    font.family: font_noto_r.name
                    font.pixelSize: 20
                }
            }
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    supervisor.playSound('click');
                    supervisor.writelog("[INIT] Localization : Make new map")
                    loadPage(pmapping);
                }
            }
        }
        Rectangle{
            id: btn_slam_pass
            width: 188
            height: 110
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
                    source:"icon/icon_testmoving.png"
                    anchors.horizontalCenter: parent.horizontalCenter
                    antialiasing: true
                    sourceSize.width: width
                    sourceSize.height: height
                    ColorOverlay{
                        anchors.fill: parent
                        source: parent
                        color: color_icon_gray
                    }
                }
                Text{
                    text: qsTr("넘어가기")
                    font.family: font_noto_r.name
                    font.pixelSize: 20
                }
            }
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    supervisor.playSound('click');
                    supervisor.writelog("[INIT] Debug Mode On");
                    supervisor.passInit();
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
            text: qsTr("로봇이 위치를 찾고 있습니다") //로봇의 위치를 찾고 있습니다
            color: color_dark_navy
            Behavior on opacity {
                NumberAnimation{
                    duration : 500
                }
            }
            horizontalAlignment:Text.AlignHCenter
            font.pixelSize: 50
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
            Buttons{
                id: btn_init_pass
                style: "normal"
                source: "qrc:/icon/icon_testmoving.png"
                visible: show_debug || show_timeout || show_restart
                text:qsTr("넘어가기")
                onClicked: {
                    supervisor.writelog("[INIT] Localization : Pass");
                    passed();
                }
            }
            Buttons{
                id: btn_init_restart
                style: "green"
                source: "qrc:/icon/icon_power.png"
                visible: show_restart
                text:qsTr("프로그램 재시작")
                onClicked: {
                    supervisor.writelog("[INIT] Localization : Restart");
                    supervisor.programRestart();
                }
            }
            Buttons{
                id: btn_init_remapping
                visible: (show_debug || show_timeout || show_failed) && mapping_mode
                style: "dark"
                source: "icon/icon_map.png"
                text:qsTr("맵 다시생성")
                onClicked: {
                    supervisor.writelog("[INIT] Localization : pass to mapping");
                    loadPage(pmapping);
                }
            }
            Buttons{
                id: btn_init_manual
                visible: show_timeout || show_failed || show_debug
                style: "dark"
                text: qsTr("수동지정(전문가)")
                onClicked: {
                    supervisor.writelog("[INIT] Localization : Failed")
                    popup_init_manual.open();
                }
            }
            Buttons{
                id: btn_init_success
                visible: show_success
                style: "green"
                source: "icon/icon_yes_w.png"
                text:qsTr("확 인")
                onClicked: {
                    supervisor.writelog("[INIT] Localization : Success");
                    confirmed();
                }
            }
        }
        Buttons{
            id: btn_init_retry
            visible: show_timeout || show_debug || show_timeout || show_failed || show_success
            style: "dark"
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
        property int count: 0
        onClicked:{
            supervisor.playSound('click');
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
        topPadding: 0
        bottomPadding: 0
        leftPadding: 0
        rightPadding: 0
        onOpened: {
            map.init();
            map.setViewer("localization");
            map.setEnable(true);

        }
        onClosed:{
            map.setEnable(false);
        }
        background: Rectangle{
            anchors.fill: parent
            color: "transparent"
        }

        Rectangle{
            id: manual_init
            width: parent.width
            height: parent.height
            color: color_navy
            Text{
                text:qsTr("로봇의 위치를 맵 상에서 표시해주세요")
                font.pixelSize: 30
                horizontalAlignment: Text.AlignHCenter
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                anchors.topMargin: 40
                color: "white"
                font.family: font_noto_b.name
            }
            Buttons{
                id: btn_right23
                style: "dark_navy"
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
                Buttons{
                    style: "dark_navy"
                    text: qsTr("이 동")
                    selected: map.tool==="move"
                    onClicked: {
                        map.setTool("move");
                    }
                }
                Buttons{
                    style: "dark_navy"
                    selected: map.tool==="slam_init"
                    text:  qsTr("수동 지정")
                    onClicked: {
                        map.setTool("slam_init");
                        supervisor.setInitCurPos();
                        supervisor.slam_setInit();
                    }
                }
//                    Buttons{
//                        style: "dark_navy"
//                        selected: map.tool==="slam_init"
//                        text:  qsTr("자동위치찾기")
//                        onClicked: {
//                            print("init autoinit");
//                            map.setTool("move");
//                            supervisor.slam_fullautoInit();
//                        }
//                    }
//                    Item_buttons{
//                        id: btn_do_autoinit
//                        width: 200
//                        height: 100
//                        running: false
//                        visible: false
//                        type: "start_progress"
//                        text: qsTr("자동위치찾기\n(1분소요)")
//                        shadowcolor: color_dark_black
//                        onClicked: {
//                            print("init autoinit");
//                            map.setTool("move");
//                            supervisor.slam_fullautoInit();
//                        }
//                    }
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

