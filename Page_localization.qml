import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.2
import Qt.labs.platform 1.0 as Platform
import QtQuick.Shapes 1.12
import QtGraphicalEffects 1.0
import QtMultimedia 5.12
import "."
import io.qt.Supervisor 1.0

Item {
    id: page_localization
    objectName: "page_localization"
    width: 1280
    height: 800
    property var local_find_state: 0
//    property bool debug_mode: false
    Component.onCompleted: {
        supervisor.setMotorLock(true);
        show_loading();
        text_finding.opacity = 1;
        map.setEnable(true);
    }
    Component.onDestruction: {
        map.setEnable(false);
    }
    function init(){

    }

    Rectangle{
        anchors.fill: parent
        color: color_dark_navy
    }

    Rectangle{
        id: btn_menu
        width: 120
        height: width
        anchors.right: parent.right
        anchors.rightMargin: 50
        anchors.top: parent.top
        anchors.topMargin: statusbar.height + 50
        color: color_gray
        radius: 120
        property bool is_restart: false
        Image{
            source:"icon/btn_reset2.png"
            scale: 1-(120-parent.width)/120
            anchors.centerIn: parent
        }
        MouseArea{
            anchors.fill: parent
            onClicked: {
                click_sound.play();
                supervisor.writelog("[USER INPUT] Localization PAGE -> BACKPAGE");
                backPage();
            }
        }
    }
    Timer{
        id: timer_check_localization2
        running: false
        repeat: true
        interval: 500
        onTriggered: {
            if(supervisor.getLocalizationState() === 2){//success
                btn_right2.enabled = true;
                btn_do_autoinit.running = false;
            }else if(supervisor.getLocalizationState() === 1){
                btn_do_autoinit.running = true;
            }else{
                btn_do_autoinit.running = false;
                btn_right2.enabled = false;
            }

        }
    }

    Timer{
        id: timer_check_localization
        running: true
        repeat: true
        interval: 500
        onTriggered: {
            local_find_state = supervisor.getLocalizationState();
            print("local state = ",local_find_state);
            if(local_find_state===0){//not ready
                supervisor.slam_autoInit();
            }else if(local_find_state === 2){//success
                unshow_loading();
                map.setViewer("local_view");
                timer_check_localization.stop();
            }else if(local_find_state === 3){//failed
                unshow_loading();
                map.setViewer("localization");
                timer_check_localization2.start();
                timer_check_localization.stop();
            }

            if(!supervisor.getIPCConnection()){
                local_find_state = 10;
                unshow_loading();
                timer_check_localization.stop();
            }

        }
    }

    Text{
        id: text_finding
        visible: local_find_state<2
        text: "로봇의 위치를 찾고 있습니다."
        color: "white"
        opacity: 0
        Behavior on opacity {
            NumberAnimation{
                duration : 500
            }
        }
        font.pixelSize: 60
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 140
        font.family: font_noto_b.name
    }
    Text{
        id: text_failed_connection
        visible: local_find_state===10
        text: "로봇과 연결이 되지 않았습니다"
        color: "white"
        font.pixelSize: 60
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 140
        font.family: font_noto_b.name
    }
    Text{
        id: text_find
        visible: local_find_state===2||local_find_state===3
        text:local_find_state===2?"로봇의 위치를 찾았습니다 로봇의 위치가 정확합니까?":"로봇의 위치를 찾을 수 없습니다 로봇의 위치를 맵 상에서 표시해주세요"
        font.pixelSize: 30
        horizontalAlignment: Text.AlignHCenter
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 30
        color: "white"
        font.family: font_noto_b.name
    }

    Column{
        anchors.right: map.left
        anchors.rightMargin: 30
        anchors.verticalCenter: map.verticalCenter
        spacing: 50
        Item_buttons{
            visible: local_find_state===3
            width: 200
            height: 80
            type: "round_text"
            selected: map.tool==="move"
            text: "이 동"
            onClicked: {
                click_sound.play();
                map.setTool("move");
            }
        }
        Item_buttons{
            visible: local_find_state===3
            width: 200
            height: 80
            type: "round_text"
            selected: map.tool==="slam_init"
            text: "수동 지정"
            onClicked: {
                click_sound.play();
                map.setTool("slam_init");
                supervisor.setInitCurPos();
                supervisor.slam_setInit();
            }
        }
        Item_buttons{
            visible: local_find_state===3
            width: 200
            height: 80
            type: "round_text"
            text:  "다시 시도"
            onClicked: {
                click_sound.play();
                map.setTool("move");
                supervisor.slam_autoInit();
                timer_check_localization2.start();
            }
        }
        Item_buttons{
            id: btn_do_autoinit
            visible: local_find_state===3
            width: 200
            height: 100
            running: false
            type: "start_progress"
            text: "자동위치찾기\n(1분소요)"
            shadowcolor: color_dark_black
            onClicked: {
                click_sound.play();
                map.setTool("move");
                supervisor.slam_fullautoInit();
                timer_check_localization2.start();
            }
        }
    }

    MAP_FULL2{
        id: map
        objectName: "annot_local"
        visible: local_find_state>1 && local_find_state<10
        anchors.top: text_find.bottom
        anchors.topMargin: 30
        anchors.horizontalCenter: parent.horizontalCenter
        width: 600
        height: 600
    }

    Item_buttons{
        type: "circle_text"
        text: "?"
        width: 60
        visible: false
        height: 60
        anchors.top: parent.top
        anchors.topMargin: 50
        anchors.right: parent.right
        anchors.rightMargin: 50
        onClicked:{
            click_sound.play();
            popup_annot_help.open();
            popup_annot_help.setTitle("로봇 위치 초기화");
            if(local_find_state === 2){
                popup_annot_help.addLine("파란색으로 표시된 라이다맵과 실제 맵이 일치하는 지 확인해주세요");
                popup_annot_help.addLine("로봇이 충전, 대기, 서빙 위치 근처에 있으면 보다 정확하고 빠르게 위치를 찾습니다");
                popup_annot_help.addLine("로봇은 위치를 찾았다고 생각하지만 라이다맵이 실제 맵과 일치 하지 않으면\n로봇이 주행 중 이상한 곳으로 가거나 충돌이 날 수 있습니다");
            }else{
                popup_annot_help.addLine("로봇을 충전, 대기, 서빙 위치 근처로 이동시킨 뒤 [다시시도]를 하시면 보다 정확하고 빠르게 위치를 찾습니다");
                popup_annot_help.addLine("아니라면 [수동지정]을 통해 맵 상의 로봇의 위치와 방향을 표시해주세요 그 위치에서 초기화를 시도합니다");
                popup_annot_help.addLine("로봇이 이동할 수 있는 상황이 아니고 수동지정도 어려우면 [자동위치찾기]버튼을 누르세요\n시간이 조금 소요됩니다");
            }

        }
    }
    Item_buttons{
        id: btn_pass
        visible: debug_mode
        width: 200
        height: 80
        type: "round_text"
        text: "넘어 가기"
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.bottomMargin: 150
        anchors.rightMargin: 50
        enabled: false
        onClicked: {
            click_sound.play();
            loadPage(pmap);
        }
    }
    Item_buttons{
        id: btn_right
        visible: local_find_state===2
        width: 200
        height: 80
        type: "round_text"
        text: "일치 합니다"
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.bottomMargin: 50
        anchors.rightMargin: 50
        onClicked: {
            click_sound.play();
            supervisor.writelog("[ANNOTATION] Localization : Success");
            supervisor.confirmLocalization();
//            loadPage(pmap);
            backPage();
//                annot_pages.sourceComponent = page_annot_menu;
        }
    }
    Item_buttons{
        id: btn_right2
        visible: local_find_state===3
        width: 200
        height: 80
        type: "round_text"
        text: "일치 합니다"
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.bottomMargin: 50
        anchors.rightMargin: 50
        enabled: false
        onClicked: {
            click_sound.play();
            supervisor.writelog("[ANNOTATION] Localization : Success");
            supervisor.confirmLocalization();
            backPage();
//            loadPage(pmap);//annot_pages.sourceComponent = page_annot_menu;
        }
    }
    Item_buttons{
        id: btn_right3
        visible: local_find_state===10
        width: 200
        height: 80
        type: "round_text"
        text: "프로그램 다시시작"
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.bottomMargin: 50
        anchors.rightMargin: 50
        onClicked: {
            click_sound.play();
            supervisor.writelog("[ANNOTATION] Localization : Connection Failed. Restart");
            supervisor.programRestart();
        }
    }
    Item_buttons{
        id: btn_left
        visible: local_find_state===2
        width: 200
        height: 80
        type: "round_text"
        text: "틀립니다.\n(수동초기화)"
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.bottomMargin: 50
        anchors.leftMargin: 50
        onClicked: {
            click_sound.play();
            supervisor.writelog("[ANNOTATION] Localization : Failed")
            local_find_state = 3;
            map.setViewer("localization");
            timer_check_localization2.start();
        }
    }
    MouseArea{
        width: 50
        height: 50
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        property var count: 0
        onClicked:{
            print(count);
            if(count++ > 4){
                count = 0;
                debug_mode = true;
            }
        }
    }
}
