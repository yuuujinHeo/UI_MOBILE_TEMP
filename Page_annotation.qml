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
    id: page_annotation
    objectName: "page_annotation"
    width: 1280
    height: 800
    property bool test: false
    property bool robot_paused: false
    property var last_robot_x: supervisor.getOrigin()[0]
    property var last_robot_y: supervisor.getOrigin()[1]
    property var last_robot_th: 0
    //0 none 1 moving 2 movefail
    property var test_move_state: 0
    property bool annotation_after_mapping: false
    property bool edit_once: false

    property var select_location: -1
    property var select_preset: 0
    property var select_object: -1
    property bool is_object: false

    function setMappingFlag(){
        annotation_after_mapping = true;
        annot_pages.sourceComponent = page_annot_start;
        loading.hide();
    }
    onSelect_locationChanged: {
    }

    onSelect_objectChanged: {
        supervisor.selectObject(select_object);
        if(select_object > -1){
            annot_pages.item.setObj(true);
        }else{
            annot_pages.item.setObj(false);
        }
    }

    function setobjcur(num){
        select_object= num;
    }

    function init(){
        test_move_state = 0;
        playMusic.stop();
    }
    function movestart(){
        test_move_state = 1;
        var location_name = supervisor.getcurLoc();
        if(location_name === "Charging0"){
            location_name = qsTr("충전위치");
        }else if(location_name === "Resting0"){
            location_name = qsTr("대기위치");
        }else if(location_name === "Cleaning0"){
            location_name = qsTr("퇴식위치");
        }
        playMusic.play();
        popup_moving.location = location_name;
        popup_moving.open();
    }
    function movedone(){
        playMusic.stop();
        test_move_state = 0;
        popup_moving.close();
        popup_notice.close();
    }
    function movefail(errnum){
        playMusic.stop();
        popup_notice.show_localization = false;
        popup_notice.show_motorinit = false;
        popup_moving.close();
        if(errnum === 0){
            popup_notice.main_str = qsTr("경로를 찾지 못했습니다");
            popup_notice.sub_str = "";
        }else if(errnum === 1){
            popup_notice.main_str = qsTr("로봇의 위치를 찾을 수 없습니다");
            popup_notice.sub_str = qsTr("로봇초기화를 다시 해주세요");
            popup_notice.show_localization = true;
            popup_notice.show_motorinit = false;
        }else if(errnum === 2){
            popup_notice.main_str = qsTr("비상스위치가 눌려있습니다");
            popup_notice.sub_str = qsTr("비상스위치를 풀어주세요");
        }else if(errnum === 3){
            popup_notice.main_str = qsTr("경로가 취소되었습니다");
            popup_notice.sub_str = "";
        }else if(errnum === 4){
            popup_notice.main_str = qsTr("모터가 초기화 되지 않았습니다");
            popup_notice.sub_str = qsTr("비상스위치를 눌렀다 풀어주세요");
        }else if(errnum === 5){
            popup_notice.main_str = qsTr("모터와 연결되지 않았습니다");
            popup_notice.sub_str = "";
        }
        popup_notice.open();
        print("annotation move fail : ",errnum);
    }

    function set_call_done(){
        annot_pages.item.readSetting();
    }

    Component.onCompleted: {
//        annot_pages.sourceComponent = page_annot_main_travelline;
        if(annotation_after_mapping){
            annot_pages.sourceComponent = page_annot_start;
        }else{
            if(supervisor.getLocalizationState() === 2){
                annot_pages.sourceComponent = page_annot_menu;
            }else{
                annot_pages.sourceComponent = page_annot_localization;
            }
        }
    }

    ListModel{
        id: details
    }

    Loader{
        id: annot_pages
        width: 1280
        height: 800 - statusbar.height
        anchors.bottom: parent.bottom
        clip: true
        sourceComponent: page_annot_start
    }

    Component{
        id: page_annot_notice
        Item{
            width: annot_pages.width
            height: annot_pages.height
            property var local_find_state: 0
            Rectangle{
                anchors.fill: parent
                color: color_dark_navy
            }
            Column{
                anchors.centerIn: parent
                Text{
                    id: text_title1
                    text: qsTr("로봇에 충전케이블이 연결되어 있습니다")
                    color: "white"
                    horizontalAlignment: Text.AlignHCenter
                    font.pixelSize: 60
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.family: font_noto_b.name
                }
                Text{
                    id: text_title12
                    text: qsTr("충전 중에는 맵설정을 할 수 없습니다")
                    color: "white"
                    horizontalAlignment: Text.AlignHCenter
                    font.pixelSize: 40
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.family: font_noto_b.name
                }
            }
            Item_buttons{
                width: 200
                height: 80
                type: "round_text"
                text: qsTr("넘어가기")
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                anchors.bottomMargin: 150
                anchors.rightMargin: 50
                onClicked: {
                    click_sound.play();
                    supervisor.writelog("[ANNOTATION] Charging pass");
                    annot_pages.sourceComponent = page_annot_menu;
                }
            }
            Item_buttons{
                width: 200
                height: 80
                type: "round_text"
                text: qsTr("종 료")
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                anchors.bottomMargin: 50
                anchors.rightMargin: 50
                onClicked: {
                    click_sound.play();
                    supervisor.writelog("[ANNOTATION] Charging Exit");
                    backPage();
                }
            }
        }
    }

    Component{
        id: page_annot_menu
        Item{
            width: annot_pages.width
            height: annot_pages.height
            property var local_find_state: 0
            Rectangle{
                anchors.fill: parent
                color: color_dark_navy
            }
            Component.onCompleted: {
                supervisor.setMotorLock(true);
                if(supervisor.getLocalizationState() === 2 && supervisor.getChargeStatus() === 0){

                    btn_charge.enabled = true;
                    btn_resting.enabled = true;
                    btn_serving.enabled = true;
                }else{
                    btn_charge.enabled = false;
                    btn_resting.enabled = false;
                    btn_serving.enabled = false;
                }
            }
            Popup{
                id: popup_ask_reset
                anchors.centerIn: parent
                background: Rectangle{
                    anchors.fill: parent
                    color: "transparent"
                }
                width: 700
                height: 300
                Rectangle{
                    width : parent.width
                    height: parent.height
                    radius: 10
                    color: color_navy
                    Column{
                        anchors.centerIn: parent
                        spacing: 30
                        Column{
                            anchors.horizontalCenter: parent.horizontalCenter
                            Text{
                                text: qsTr("정말로 초기화하고 다시 세팅하시겠습니까?")
                                anchors.horizontalCenter: parent.horizontalCenter
                                font.family: font_noto_r.name
                                font.pixelSize: 30
                                color: "white"
                            }
                            Text{
                                text: qsTr("(이전 세팅이 모두 사라지며 복구가 불가능합니다)")
                                anchors.horizontalCenter: parent.horizontalCenter
                                font.family: font_noto_r.name
                                font.pixelSize: 20
                                color: color_red
                            }
                        }
                        Row{
                            anchors.horizontalCenter: parent.horizontalCenter
                            spacing: 50
                            Rectangle{
                                width: 150
                                height: 60
                                radius: 10
                                color: color_green
                                Text{
                                    anchors.centerIn: parent
                                    text: qsTr("확인")
                                    font.family: font_noto_r.name
                                    font.pixelSize: 20
                                    color: "white"
                                }
                                MouseArea{
                                    anchors.fill: parent
                                    onClicked:{
                                        supervisor.writelog("[ANNOTATION] MENU : Clear and New Annotation");
                                        annot_pages.sourceComponent = page_annot_start;
                                        supervisor.deleteEditedMap();
                                        supervisor.deleteAnnotation();
                                        annotation_after_mapping = true;
                                        popup_ask_reset.close();
                                    }
                                }
                            }
                            Rectangle{
                                width: 150
                                height: 60
                                radius: 10
                                color: color_light_gray
                                Text{
                                    anchors.centerIn: parent
                                    text: qsTr("취소")
                                    font.family: font_noto_r.name
                                    font.pixelSize: 20
                                }
                                MouseArea{
                                    anchors.fill: parent
                                    onClicked:{
                                        popup_ask_reset.close();
                                    }
                                }
                            }
                        }

                    }
                }
            }

            Text{
                id: text_title1
                text: qsTr("맵을 수정합니다")
                color: "white"
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 60
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                anchors.topMargin: 50
                font.family: font_noto_b.name
            }
            Text{
                id: text_title12
                text: qsTr("수정하실 단계를 선택하여 진행해주세요")
                color: "white"
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 40
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: text_title1.bottom
                font.family: font_noto_b.name
            }
            Grid{
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: text_title12.bottom
                anchors.topMargin: 50
                spacing: 30
                horizontalItemAlignment: Grid.AlignHCenter
                verticalItemAlignment: Grid.AlignVCenter
                rows: 2
                columns: 3
                Item_buttons{
                    width: 220
                    height: 150
                    fontsize: 30
                    visible: false
                    type: "round_text"
                    text:qsTr("이전세팅 초기화\n다시 세팅")
                    onClicked: {
                        click_sound.play();
                        popup_ask_reset.open();
                    }
                }
                Item_buttons{
                    width: 220
                    height: 150
                    fontsize: 30
                    visible: false
                    type: "round_text"
                    text:qsTr("맵 회전\n잘라내기")
                    onClicked: {
                        click_sound.play();
                        supervisor.writelog("[ANNOTATION] MENU : Rotate / Cut Map");
                        annot_pages.sourceComponent = page_annot_start;
                    }
                }
                Item_buttons{
                    id: btn_charge
                    width: 220
                    height: 150
                    fontsize: 30
                    type: "round_text"
                    text: qsTr("충전위치 변경")
                    onClicked: {
                        click_sound.play();
                        supervisor.writelog("[ANNOTATION] MENU : Change Charging Location");
                        annot_pages.sourceComponent = page_annot_location_charging;
                    }
                }
                Item_buttons{
                    id: btn_resting
                    width: 220
                    height: 150
                    fontsize: 30
                    type: "round_text"
                    text: qsTr("대기위치 변경")
                    onClicked: {
                        click_sound.play();
                        supervisor.writelog("[ANNOTATION] MENU : Change Resting Location");
                        annot_pages.sourceComponent = page_annot_location_resting;
                    }
                }
                Item_buttons{
                    id: btn_serving
                    width: 220
                    height: 150
                    fontsize: 30
                    type: "round_text"
                    text: qsTr("서빙위치 변경")
                    onClicked: {
                        click_sound.play();
                        supervisor.writelog("[ANNOTATION] MENU : Change Serving Location");
                        annot_pages.sourceComponent = page_annot_location_serving_done;
                    }
                }
                Item_buttons{
                    width: 220
                    height: 150
                    fontsize: 30
                    type: "round_text"
                    text: qsTr("추가 설정")
                    onClicked: {
                        click_sound.play();
                        supervisor.writelog("[ANNOTATION] MENU : Additional menu");
                        annot_pages.sourceComponent = page_annot_additional_menu;
                    }
                }
            }

            Item_buttons{
                width: 200
                height: 80
                type: "round_text"
                text: {
                    if(supervisor.getSetting("setting","USE_SLAM","use_multirobot")==="true"){
                        qsTr("맵 보내기/가져오기")
                    }else{
                        qsTr("맵 불러오기")
                    }
                }

                anchors.bottom: parent.bottom
                anchors.right: parent.right
                anchors.bottomMargin: 150
                anchors.rightMargin: 50
                onClicked: {
                    click_sound.play();
                    supervisor.writelog("[ANNOTATION] Load Map");

                    if(supervisor.getSetting("setting","USE_SLAM","use_multirobot")==="true"){
                        popup_ask_mapload.open();
                    }else{
                        popup_map_list.open();
                    }
                }
            }
            Item_buttons{
                width: 200
                height: 80
                type: "round_text"
                text: qsTr("종 료")
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                anchors.bottomMargin: 50
                anchors.rightMargin: 50
                onClicked: {
                    click_sound.play();
                    supervisor.writelog("[ANNOTATION] All Done");
                    backPage();
                }
            }
        }
    }
    Component{
        id: page_annot_start
        Item{
            width: annot_pages.width
            height: annot_pages.height
            Rectangle{
                anchors.fill: parent
                color: color_dark_navy
            }
            Component.onCompleted: {
                map.setEnable(true);
                supervisor.setMotorLock(true);
            }
            Component.onDestruction: {
                map.setEnable(false);
            }

            Timer{
                interval: 500
                running: true
                onTriggered:{
                    if(annotation_after_mapping)
                        supervisor.setMapOrin("RAW");
                    else
                        supervisor.setMapOrin("EDITED");

                    map.setEnable(true);
                    map.setViewer("annot_rotate");
                    map.setTool("move");
                    map.clear("rotate")
                }
            }

            Timer{
                id: timer_rotate
                interval: 50
                running: false
                repeat: true
                property bool cw: true
                onTriggered: {
                    if(cw){
                        map.rotate("cw");
                    }else{
                        map.rotate("ccw");
                    }
                }
            }

            Text{
                text: qsTr("맵을 회전하고 맵의 영역만큼 지정해주세요")
                color: "white"
                font.pixelSize: 40
                font.family: font_noto_b.name
                anchors.top: parent.top
                anchors.topMargin: 30
                anchors.horizontalCenter: parent.horizontalCenter
            }

            Item_buttons{
                type: "circle_text"
                text: "?"
                width: 60
                height: 60
                anchors.top: parent.top
                anchors.topMargin: 50
                anchors.right: parent.right
                anchors.rightMargin: 50
                onClicked:{
                    click_sound.play();
                    popup_annot_help.open();
                    popup_annot_help.setTitle(qsTr("맵 회전 / 잘라내기"));
                    popup_annot_help.addLine(qsTr("매장에 대한 로봇의 방향을 직관적으로 알 수 있도록 맵을 회전시켜주세요\n맵을 회전하지 않아도 로봇 주행에는 문제가 없습니다\n이미 사용중인 맵을 회전시키면 기존에 설정한 위치들이 전부 삭제되므로 신중하게 결정해주세요"));
                    popup_annot_help.addLine(qsTr("맵 생성을 한 뒤 맵의 여백이 너무 많은 경우 잘라내기를 할 수 있습니다\n로봇이 이동해야할 부분을 잘라내기 하지 않도록 주의해주세요"));
                }
            }
            Row{
                spacing: 20
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: map.left
                anchors.rightMargin: 30
                anchors.verticalCenterOffset: -50
                Image{
                    source: "icon/btn_reset.png"
                    width: 80
                    height: 80
                    MouseArea{
                        anchors.fill: parent
                        onPressed:{
                            timer_rotate.cw = false;
                            timer_rotate.start();
                        }
                        onReleased: {
                            timer_rotate.stop();
                        }
                    }
                }
                Image{
                    source: "icon/btn_reset.png"
                    width: 80
                    height: 80
                    Text{
                        anchors.centerIn: parent
                        text: "1"
                        font.pixelSize: 20
                        font.family: font_noto_r.name
                        color: "white"
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            map.rotate("ccw");
                        }
                        onPressAndHold: {
                            timer_rotate.cw = false;
                            timer_rotate.start();
                        }
                        onReleased: {
                            timer_rotate.stop();
                        }
                    }
                }
            }

            Row{
                spacing: 20
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: map.right
                anchors.leftMargin: 30+80
                anchors.verticalCenterOffset: -50
                Image{
                    source: "icon/btn_reset.png"
                    width: 80
                    height: 80
                    transform: Scale{xScale:-1}
                    Text{
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.leftMargin: parent.width/2+width/2
//                        anchors.centerIn: parent
                        text: "1"
                        font.pixelSize: 20
                        transform: Scale{xScale:-1}
                        font.family: font_noto_r.name
                        color: "white"
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            map.rotate("cw");
                        }
                        onPressAndHold: {
                            timer_rotate.cw = true;
                            timer_rotate.start();
                        }
                        onReleased: {
                            timer_rotate.stop();
                        }
                    }
                }
                Image{
                    source: "icon/btn_reset.png"
                    width: 80
                    height: 80
                    transform: Scale{xScale:-1}
                    MouseArea{
                        anchors.fill: parent
                        onPressed:{
                            timer_rotate.cw = true;
                            timer_rotate.start();
                        }
                        onReleased: {
                            timer_rotate.stop();
                        }
                    }
                }

            }

            MAP_FULL2{
                id: map
                enabled: false
                objectName: "annot_rotate"
                width: 600
                height: width
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                anchors.topMargin: 120
                onToolChanged: {
                    print(tool)
                }
            }


            Item_buttons{
                width: 200
                height: 80
                type: "round_text"
                text: qsTr("저 장")
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                anchors.bottomMargin: 50
                anchors.rightMargin: 50
                onClicked: {
                    click_sound.play();
                    if(map.tool == "cut_map"){
                        if(map.getCutFlag() && !annotation_after_mapping){

                            popup_save_rotate.open();
                        }else{
                            map.save("rotate");
                            supervisor.writelog("[ANNOTATION] Rotate, Cut : done and save.")
                            if(annotation_after_mapping)
                                annot_pages.sourceComponent = page_annot_localization;
                            else
                                annot_pages.sourceComponent = page_annot_menu;

                            supervisor.slam_map_reload(supervisor.getMapname());
                        }
                    }else{
                        map.save("rotate");
                        supervisor.writelog("[ANNOTATION] Rotate, Cut : done and save.")
                        if(annotation_after_mapping)
                            annot_pages.sourceComponent = page_annot_localization;
                        else
                            annot_pages.sourceComponent = page_annot_menu;

                        supervisor.slam_map_reload(supervisor.getMapname());
                    }

                }
            }

            Column{
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.bottomMargin: 50
                anchors.leftMargin: 50
                spacing: 20

                Item_buttons{
                    width: 200
                    height: 80
                    type: "round_text"
                    selected: map.tool==="move"
                    text: qsTr("이 동")
                    onClicked: {
                        click_sound.play();
                        map.setTool("move");
                    }
                }
                Item_buttons{
                    width: 200
                    height: 80
                    type: "round_text"
                    text: qsTr("맵 잘라내기")
                    selected: map.tool==="cut_map"
                    onClicked: {
                        click_sound.play();
                        map.setTool("cut_map");
                    }
                }
                Item_buttons{
                    width: 200
                    height: 80
                    type: "round_text"
                    text: qsTr("초기화")
                    onClicked: {
                        click_sound.play();
                        map.clear("rotate");
                    }
                }
            }

            Popup{
                id : popup_save_rotate
                width: parent.width
                height: parent.height
                background:Rectangle{
                    anchors.fill: parent
                    color: "#282828"
                    opacity: 0.7
                }
                Rectangle{
                    anchors.centerIn: parent
                    width: 500
                    height: 250
                    color: "white"
                    radius: 20
                    Column{
                        anchors.centerIn: parent
                        spacing: 20
                        Column{
                            anchors.horizontalCenter: parent.horizontalCenter
                            Text{
                                text: qsTr("맵을 <font color=\"#12d27c\">잘라내기</font>하시겠습니까?")
                                font.family: font_noto_r.name
                                font.pixelSize: 30
                                anchors.horizontalCenter: parent.horizontalCenter
                            }
                            Text{
                                text: qsTr("맵을 자르면 기존의 설정은 모두 삭제되며 새로 설정하셔야 합니다")
                                font.family: font_noto_r.name
                                font.pixelSize: 15
                                color: color_red
                                anchors.horizontalCenter: parent.horizontalCenter
                            }
                        }
                        Row{
                            anchors.horizontalCenter: parent.horizontalCenter
                            spacing: 20
                            Item_buttons{
                                type: "round_text"
                                text: qsTr("잘라내지 않음")
                                width: 180
                                height: 100
                                onClicked:{
                                    click_sound.play();
                                    map.setTool("move");
                                    map.save("rotate");
                                    if(annotation_after_mapping)
                                        annot_pages.sourceComponent = page_annot_localization;
                                    else
                                        annot_pages.sourceComponent = page_annot_menu;

                                    supervisor.slam_map_reload(supervisor.getMapname());
                                    popup_save_rotate.close();
                                }
                            }
                            Item_buttons{
                                type: "round_text"
                                text: qsTr("확인")
                                width: 180
                                height: 100
                                onClicked:{
                                    click_sound.play();
                                    map.save("rotate");
                                    annotation_after_mapping = true;
                                    annot_pages.sourceComponent = page_annot_localization;
                                    supervisor.deleteAnnotation();
                                    supervisor.slam_map_reload(supervisor.getMapname());
                                    popup_save_rotate.close();
                                }
                            }
                        }
                    }

                }

            }
        }
    }
    Component{
        id: page_annot_localization
        Item{
            width: annot_pages.width
            height: annot_pages.height
            property var local_find_state: -1
            property bool show_debug: false
            Component.onCompleted: {

            }
            Component.onDestruction: {
                map.setEnable(false);
            }

            Rectangle{
                anchors.fill: parent
                color: color_light_gray
            }

            Timer{
                running: true
                interval: 500
                onTriggered:{
                    if(annotation_after_mapping){
                        timer_check_localization.start();
                        supervisor.writelog("[ANNOTATION] INIT PAGE : DO LOCALIZATION")
                        supervisor.slam_autoInit();
                    }
                }
            }
            Timer{
                running: true
                interval: 1000
                onTriggered:{
                    supervisor.setMotorLock(false);
                }
            }

            Timer{
                id: timer_check_localization
                running: false
                repeat: true
                interval: 500
                onTriggered: {
                    local_find_state = supervisor.getLocalizationState();
//                    print(local_find_state);
                    if(local_find_state===0){//not ready
                        if(!popup_loading.opened)
                            popup_loading.open();
                    }else if(local_find_state === 1){
                        text_finding.text = qsTr("로봇의 위치를 찾고 있습니다")
                        popup_loading.close();
                        btn_init_success.visible = false;
                        btn_init_manual.visible = false;
                        btn_init_retry.visible = false;
                    }else if(local_find_state === 2){//success
                        text_finding.text = qsTr("로봇의 위치를 찾았습니다.\n로봇을 회전시켜도 값이 정상이라면 확인버튼을 눌러주세요")
                        popup_loading.close();
                        btn_init_success.visible = true;
                        btn_init_retry.visible = true;
                        btn_init_manual.visible = true;
//                        timer_check_localization.stop();
                    }else if(local_find_state === 3){//failed
                        text_finding.text = qsTr("로봇의 위치를 찾지 못했습니다")
                        popup_loading.close();
                        btn_init_success.visible = false;
                        btn_init_manual.visible = true;
                        btn_init_retry.visible = true;
                        timer_check_localization2.start();
//                        timer_check_localization.stop();
                    }else{
                        text_finding.text = qsTr("로봇과 연결이 되지 않았습니다")
                    }

                    if(!supervisor.getIPCConnection()){
                        local_find_state = 10;
                        popup_loading.close();
                        btn_init_reboot.visible = true;
                        timer_check_localization.stop();
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
//                        btn_right2.enabled = true;
                        btn_do_autoinit.running = false;
                    }else if(supervisor.getLocalizationState() === 1){
                        btn_do_autoinit.running = true;
//                        btn_right2.enabled = false;
                    }else{
                        btn_do_autoinit.running = false;
//                        btn_right2.enabled = false;
                    }
                }
            }

            Rectangle{
                id: initPage_main
                visible: !annotation_after_mapping && (local_find_state === -1 || local_find_state === 0)
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
                    text: qsTr("로봇을 지정된 대기위치로 이동시켜 주세요\n이동하신 후 아래 버튼을 눌러주세요")
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
                        text: qsTr("대기위치입니다")
                        color: "white"
                        font.family: font_noto_r.name
                        font.pixelSize: 40
                    }
                    MouseArea{
                        anchors.fill: parent
                        onPressed:{
                            start_sound.play();
                            parent.color = color_mid_green;
                        }
                        onReleased: {
                            parent.color = color_green;
                        }
                        onClicked: {
                            timer_check_localization.start();
                            supervisor.writelog("[USER INPUT] INIT PAGE : DO LOCALIZATION")
                            supervisor.slam_autoInit();
                            update_timer.stop();
                        }
                    }
                }
                DropShadow{
                    anchors.fill: btn_slam_do_init
                    radius: 10
                    color: color_dark_gray
                    source: btn_slam_do_init
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
                    spacing: 20
                    Item_buttons{
                        id: btn_init_pass
                        visible: show_debug
                        width: 200
                        height: 80
                        type: "round_text"
                        text:qsTr("넘어가기")
                        onClicked: {
                            click_sound.play();
                            supervisor.writelog("[ANNOTATION] Localization : Pass");
                            annot_pages.sourceComponent = page_annot_menu;
                        }
                    }
                    Item_buttons{
                        id: btn_init_remapping
                        visible: show_debug
                        width: 200
                        height: 80
                        type: "round_text"
                        text:qsTr("맵 다시생성")
                        onClicked: {
                            click_sound.play();
                            supervisor.writelog("[ANNOTATION] Localization : pass to mapping");
                            loadPage(pmapping);
                        }
                    }
                    Item_buttons{
                        id: btn_init_manual
                        visible: false
                        width: 200
                        height: 80
                        type: "round_text"
                        text: qsTr("수동지정(전문가)")
                        onClicked: {
                            click_sound.play();
                            supervisor.writelog("[ANNOTATION] Localization : Failed")
                            popup_init_manual.open();
                        }
                    }
                    Item_buttons{
                        id: btn_init_success
                        visible: false
                        width: 200
                        height: 80
                        type: "round_text"
                        text:qsTr("확 인")
                        onClicked: {
                            click_sound.play();
                            supervisor.writelog("[ANNOTATION] Localization : Success");
                            if(annotation_after_mapping){
                                annot_pages.sourceComponent = page_annot_location_charging;
                            }else{
                                supervisor.confirmLocalization();
                                annot_pages.sourceComponent = page_annot_menu;
                            }

                        }
                    }
                }
                Item_buttons{
                    id: btn_init_retry
                    visible: false
                    width: 200
                    height: 80
                    type: "round_text"
                    text: qsTr("다시시도")
                    anchors.bottom: parent.bottom
                    anchors.left: parent.left
                    anchors.bottomMargin: 50
                    anchors.leftMargin: 50
                    onClicked: {
                        click_sound.play();
                        if(annotation_after_mapping){
                            timer_check_localization.start();
                            supervisor.writelog("[ANNOTATION] INIT PAGE : DO LOCALIZATION")
                            supervisor.slam_autoInit();
                        }else{
                            timer_check_localization.stop();
                            local_find_state = -1;
                            supervisor.writelog("[ANNOTATION] Localization : Retry");
    //                        timer_check_localization2.start();
                        }

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
                    print(count);
                    if(count++ > 4){
                        count = 0;
                        if(annotation_after_mapping){
                            btn_init_remapping.visible = true;
                        }else{
                            show_debug = true;
                        }
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
                            click_sound.play();
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
                                click_sound.play();
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
                                click_sound.play();
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
                                click_sound.play();
                                map.setTool("move");
                                supervisor.slam_autoInit();
                                timer_check_localization2.start();
                            }
                        }
                        Item_buttons{
                            id: btn_do_autoinit
                            width: 200
                            height: 100
                            running: false
                            type: "start_progress"
                            text: qsTr("자동위치찾기\n(1분소요)")
                            shadowcolor: color_dark_black
                            onClicked: {
                                click_sound.play();
                                print("init autoinit");
                                map.setTool("move");
                                supervisor.slam_fullautoInit();
                                timer_check_localization2.start();
                            }
                        }
                    }
                }
                MAP_FULL2{
                    id: map
                    enabled: false
                    objectName: "annot_local"
//                    visible: local_find_state>1 && local_find_state<10
//                    onVisibleChanged: {
//                        print("map visible changed",visible,x,y,width,height);
//                    }
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 50
                    anchors.horizontalCenter: parent.horizontalCenter
                    width: 600
                    height: 600
                }

            }

        }
    }
    Component{
        id: page_annot_location_charging
        Item{
            width: annot_pages.width
            height: annot_pages.height
            Component.onCompleted: {
                supervisor.setMotorLock(false);
            }

            Timer{
                running: true
                interval: 500
                onTriggered:{
                    supervisor.drawingRunawayStart();
                }
            }

            Rectangle{
                anchors.fill: parent
                color: color_dark_navy
            }
            Column{
                id: col
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                anchors.topMargin: 80
                spacing: 30
                Text{
                    text: qsTr("로봇을 충전 위치로 이동시켜주세요")
                    color: "white"
                    font.pixelSize: 80
                    font.family: font_noto_b.name
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                Column{
                    Text{
                        text: qsTr("* 충전 위치란?")
                        color: color_green
                        font.bold: true
                        font.pixelSize: 20
                        horizontalAlignment: Text.AlignHCenter
                        font.family: font_noto_r.name
                    }
                    Text{
                        text: qsTr("로봇이 비 운영 중에 충전을 위해 서 있는 장소입니다")
                        color: "white"
                        font.pixelSize: 20
                        horizontalAlignment: Text.AlignHCenter
                        font.family: font_noto_r.name
                    }
                    Text{
                        text: qsTr("충전기가 꼽혀있는 콘센트 주변으로 지정해주세요")
                        color: "white"
                        font.pixelSize: 20
                        horizontalAlignment: Text.AlignHCenter
                        font.family: font_noto_r.name
                    }
                }
            }

            AnimatedImage{
                id: image_robotmoving
                source: "image/robot_manual.gif"
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: parent.bottom
                width: 1280/1.5
                height: 800/1.5
                speed: 0.5
                anchors.bottomMargin: -100
            }

            Item_buttons{
                id: btn_left
                width: 200
                height: 80
                type: "round_text"
                text: qsTr("위치 초기화")
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.bottomMargin: 50
                anchors.leftMargin: 50
                onClicked: {
                    click_sound.play();
                    supervisor.writelog("[ANNOTATION] BACK TO Localization  ");
                    annot_pages.sourceComponent = page_annot_localization;
                }
            }

            Item_buttons{
                id: btn_right2
                width: 200
                height: 80
                visible: !annotation_after_mapping
                type: "round_text"
                text: qsTr("취 소")
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                anchors.bottomMargin: 150
                anchors.rightMargin: 50
                onClicked: {
                    click_sound.play();
                    annot_pages.sourceComponent = page_annot_menu;
                }
            }
            Item_buttons{
                id: btn_right
                width: 200
                height: 80
                type: "round_text"
                text: qsTr("이동했습니다")
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                anchors.bottomMargin: 50
                anchors.rightMargin: 50
                onClicked: {
                    click_sound.play();
                    supervisor.writelog("[ANNOTATION] LOCAION SAVE : Charging "+Number(supervisor.getlastRobotx())+", "+Number(supervisor.getlastRoboty())+", "+Number(supervisor.getlastRobotth()));
                    annot_pages.sourceComponent = page_annot_location_charging_done;
                }
            }
        }
    }
    Component{
        id: page_annot_location_charging_done
        Item{
            width: annot_pages.width
            height: annot_pages.height
            Component.onCompleted: {
                supervisor.setMotorLock(false);
//                if(annotation_after_mapping || supervisor.getLocationNum("Charging") === 0){
                    last_robot_x = supervisor.getlastRobotx();
                    last_robot_y = supervisor.getlastRoboty();
                    last_robot_th = supervisor.getlastRobotth();
                    supervisor.addLocation(last_robot_x,last_robot_y,last_robot_th);
                    supervisor.saveLocation("Charging", 0, "Charging0");
                    text_save_done.visible = true;
                    column_another_save.visible = false;
                    btn_right.enabled = true;
//                }else{
//                    column_another_save.visible = true;
//                    text_save_done.visible = false;
//                    model_chargings.clear();
//                    for(var i=0; i<supervisor.getLocationNum("Charging"); i++){
//                        model_chargings.append({"name":qsTr("충전위치")+Number(i)});
//                    }
//                }
            }
            property int select_charging: 0
            Rectangle{
                anchors.fill: parent
                color: color_dark_navy
            }
            Text{
                id: text_save_done
                text: qsTr("로봇의 충전 위치를 저장했습니다")
                color: "white"
                visible: false
                font.pixelSize: 80
                font.family: font_noto_b.name
                anchors.centerIn: parent
            }
            Column{
                id: column_another_save
                visible: false
                anchors.centerIn: parent
                spacing: 50
                Text{
                    text: qsTr("이미 세팅된 충전위치가 있습니다")
                    color: "white"
                    font.pixelSize: 80
                    font.family: font_noto_b.name
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                Flickable{
                    width: rows_charging.width
                    height: 100
                    clip: true
                    anchors.horizontalCenter: parent.horizontalCenter
                    contentWidth: rows_charging.width
                    Row{
                        id: rows_charging
                        spacing: 20
                        anchors.horizontalCenter: parent.horizontalCenter
                        Repeater{
                            model: ListModel{id: model_chargings}
                            Item_buttons{
                                width: 200
                                height: 100
                                type: "round_text"
                                selected: select_charging===index
                                text: name
                                onClicked:{
                                    select_charging = index;
                                }
                            }
                        }
                    }
                }

                Row{
                    anchors.horizontalCenter: parent.horizontalCenter
                    spacing: 50
                    Item_buttons{
                        width: 200
                        height: 80
                        type: "round_text"
                        text: qsTr("덮어쓰기")
                        onClicked:{
                            last_robot_x = supervisor.getlastRobotx();
                            last_robot_y = supervisor.getlastRoboty();
                            last_robot_th = supervisor.getlastRobotth();
                            supervisor.addLocation(last_robot_x,last_robot_y,last_robot_th);
                            supervisor.saveLocation("Charging", 0, "Charging"+Number(select_charging));
                            text_save_done.visible = true;
                            column_another_save.visible = false;
                            btn_right.enabled = true;
                        }
                    }
                    Item_buttons{
                        width: 200
                        height: 80
                        type: "round_text"
                        text: qsTr("새로추가")
                        onClicked:{
                            last_robot_x = supervisor.getlastRobotx();
                            last_robot_y = supervisor.getlastRoboty();
                            last_robot_th = supervisor.getlastRobotth();
                            supervisor.addLocation(last_robot_x,last_robot_y,last_robot_th);
                            supervisor.saveLocation("Charging", 0, "Charging"+Number(supervisor.getLocationNum("Charging")));
                            text_save_done.visible = true;
                            column_another_save.visible = false;
                            btn_right.enabled = true;
                        }
                    }
                    Item_buttons{
                        width: 200
                        height: 80
                        type: "round_text"
                        text: qsTr("취 소")
                        onClicked:{
                            btn_right.enabled = true;
                            supervisor.writelog("[Annotation] Location Save : Charging -> Done");
                            if(annotation_after_mapping)
                                annot_pages.sourceComponent = page_annot_location_resting;
                            else
                                annot_pages.sourceComponent = page_annot_location_test_1;
                        }
                    }

                }
            }

            Item_buttons{
                id: btn_left
                width: 200
                height: 80
                type: "round_text"
                text: qsTr("다시 지정")
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.bottomMargin: 50
                anchors.leftMargin: 50
                onClicked: {
                    click_sound.play();
                    supervisor.writelog("[Annotation] Location Save : Charging -> Canceled");
                    annot_pages.sourceComponent = page_annot_location_charging;

                }
            }
            Item_buttons{
                id: btn_right
                width: 200
                height: 80
                type: "round_text"
                text: qsTr("다음으로")
                enabled: false
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                anchors.bottomMargin: 50
                anchors.rightMargin: 50
                onClicked: {
                    click_sound.play();
                    supervisor.writelog("[Annotation] Location Save : Charging -> Done");
                    if(annotation_after_mapping)
                        if(edit_once){
                            annot_pages.sourceComponent = page_annot_location_test_1;
                            edit_once = false;
                        }else
                            annot_pages.sourceComponent = page_annot_location_resting;
                    else
                        annot_pages.sourceComponent = page_annot_location_test_1;
                }
            }
        }
    }
    Component{
        id: page_annot_location_resting
        Item{
            width: annot_pages.width
            height: annot_pages.height
            Component.onCompleted: {
                supervisor.setMotorLock(false);
            }

            Timer{
                running: true
                interval: 500
                onTriggered:{
                    supervisor.drawingRunawayStart();
                }
            }

            Rectangle{
                anchors.fill: parent
                color: color_dark_navy
            }
            Column{
                id: col
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                anchors.topMargin: 80
                spacing: 30
                Text{
                    text: qsTr("로봇을 대기위치로 이동시켜주세요")
                    color: "white"
                    font.pixelSize: 80
                    font.family: font_noto_b.name
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                Column{
                    Text{
                        text: qsTr("* 대기위치란?")
                        color: color_green
                        font.bold: true
                        font.pixelSize: 20
                        horizontalAlignment: Text.AlignHCenter
                        font.family: font_noto_r.name
                    }
                    Text{
                        text: qsTr("로봇이 서빙을 시작하기 전, 음식을 받기 위해 기다리는 장소입니다")
                        color: "white"
                        font.pixelSize: 20
                        horizontalAlignment: Text.AlignHCenter
                        font.family: font_noto_r.name
                    }
                    Text{
                        text: qsTr("주방에서 음식을 올리기 편한 위치로 지정해주세요")
                        color: "white"
                        font.pixelSize: 20
                        horizontalAlignment: Text.AlignHCenter
                        font.family: font_noto_r.name
                    }
                }
            }

            AnimatedImage{
                id: image_robotmoving
                source: "image/robot_manual.gif"
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: parent.bottom
                width: 1280/1.5
                height: 800/1.5
                speed: 0.5
                anchors.bottomMargin: -100
            }
            Item_buttons{
                id: btn_right2
                width: 200
                height: 80
                visible: !annotation_after_mapping
                type: "round_text"
                text: qsTr("취 소")
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                anchors.bottomMargin: 150
                anchors.rightMargin: 50
                onClicked: {
                    click_sound.play();
                    annot_pages.sourceComponent = page_annot_menu;
                }
            }
            Item_buttons{
                id: btn_right
                width: 200
                height: 80
                type: "round_text"
                text: qsTr("이동했습니다")
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                anchors.bottomMargin: 50
                anchors.rightMargin: 50
                onClicked: {
                    click_sound.play();
                    supervisor.writelog("[ANNOTATION] LOCAION SAVE : Resting "+Number(supervisor.getlastRobotx())+", "+Number(supervisor.getlastRoboty())+", "+Number(supervisor.getlastRobotth()));
                    annot_pages.sourceComponent = page_annot_location_resting_done;
                }
            }
        }
    }
    Component{
        id: page_annot_location_resting_done
        Item{
            width: annot_pages.width
            height: annot_pages.height
            Component.onCompleted: {
                supervisor.setMotorLock(false);
//                if(annotation_after_mapping || supervisor.getLocationNum("Resting") === 0){
                    last_robot_x = supervisor.getlastRobotx();
                    last_robot_y = supervisor.getlastRoboty();
                    last_robot_th = supervisor.getlastRobotth();
                    supervisor.addLocation(last_robot_x,last_robot_y,last_robot_th);
                    supervisor.saveLocation("Resting", 0, "Resting0");
                    text_save_done.visible = true;
                    column_another_save.visible = false;
                    btn_right.enabled = true;
//                }else{
//                    column_another_save.visible = true;
//                    text_save_done.visible = false;
//                    model_resting.clear();
//                    for(var i=0; i<supervisor.getLocationNum("Resting"); i++){
//                        model_resting.append({"name":qsTr("대기위치")+Number(i)});
//                    }
//                }
//                loading.show();
            }
            property int select_resting: 0
            Rectangle{
                anchors.fill: parent
                color: color_dark_navy
            }
            Text{
                id: text_save_done
                text: qsTr("로봇의 대기위치를 저장했습니다")
                color: "white"
                visible: false
                font.pixelSize: 80
                font.family: font_noto_b.name
                anchors.centerIn: parent
            }
            Column{
                id: column_another_save
                visible: false
                anchors.centerIn: parent
                spacing: 50
                Text{
                    text: qsTr("이미 세팅된 대기위치가 있습니다")
                    color: "white"
                    font.pixelSize: 80
                    font.family: font_noto_b.name
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                Flickable{
                    width: rows_resting.width
                    height: 100
                    clip: true
                    anchors.horizontalCenter: parent.horizontalCenter
                    contentWidth: rows_resting.width
                    Row{
                        id: rows_resting
                        spacing: 20
                        anchors.horizontalCenter: parent.horizontalCenter
                        Repeater{
                            model: ListModel{id: model_resting}
                            Item_buttons{
                                width: 200
                                height: 100
                                type: "round_text"
                                selected: select_resting===index
                                text: name
                                onClicked:{
                                    select_resting = index;
                                }
                            }
                        }
                    }
                }

                Row{
                    anchors.horizontalCenter: parent.horizontalCenter
                    spacing: 50
                    Item_buttons{
                        width: 200
                        height: 80
                        type: "round_text"
                        text: qsTr("덮어쓰기")
                        onClicked:{
                            last_robot_x = supervisor.getlastRobotx();
                            last_robot_y = supervisor.getlastRoboty();
                            last_robot_th = supervisor.getlastRobotth();
                            supervisor.addLocation(last_robot_x,last_robot_y,last_robot_th);
                            supervisor.saveLocation("Resting", 0, "Resting"+Number(select_resting));
                            text_save_done.visible = true;
                            column_another_save.visible = false;
                            btn_right.enabled = true;
                        }
                    }
                    Item_buttons{
                        width: 200
                        height: 80
                        type: "round_text"
                        text: qsTr("새로추가")
                        onClicked:{
                            last_robot_x = supervisor.getlastRobotx();
                            last_robot_y = supervisor.getlastRoboty();
                            last_robot_th = supervisor.getlastRobotth();
                            supervisor.addLocation(last_robot_x,last_robot_y,last_robot_th);
                            supervisor.saveLocation("Resting", 0, "Resting"+Number(supervisor.getLocationNum("Resting")));
                            text_save_done.visible = true;
                            column_another_save.visible = false;
                            btn_right.enabled = true;
                        }
                    }
                    Item_buttons{
                        width: 200
                        height: 80
                        type: "round_text"
                        text: qsTr("취 소")
                        onClicked:{
                            btn_right.enabled = true;
                        }
                    }
                }
            }

            Item_buttons{
                id: btn_left
                width: 200
                height: 80
                type: "round_text"
                text: qsTr("다시 지정")
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.bottomMargin: 50
                anchors.leftMargin: 50
                onClicked: {
                    click_sound.play();
                    supervisor.writelog("[Annotation] Location Save : Resting -> Canceled");
                    annot_pages.sourceComponent = page_annot_location_resting;

                }
            }
            Item_buttons{
                id: btn_right
                width: 200
                height: 80
                type: "round_text"
                text: qsTr("다음으로")
                enabled: false
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                anchors.bottomMargin: 50
                anchors.rightMargin: 50
                onClicked: {
                    click_sound.play();
                    supervisor.writelog("[Annotation] Location Save : Resting -> Done");
                    annot_pages.sourceComponent = page_annot_location_test_1;
                }
            }
        }
    }
    Component{
        id: page_annot_location_test_1
        Item{
            width: annot_pages.width
            height: annot_pages.height
            Component.onCompleted: {
                supervisor.setMotorLock(true);
//                supervisor.checkMoveFail();
            }
            Timer{
                running: true
                interval: 500
                onTriggered: {
                    supervisor.drawingRunawayStop();
                }
            }

            Rectangle{
                anchors.fill: parent
                color: color_dark_navy
            }
            Text{
                text: qsTr("충전 위치와 대기 위치 사이의 이동을 확인합니다")
                color: "white"
                font.pixelSize:60
                font.family: font_noto_b.name
                anchors.top: parent.top
                anchors.topMargin: 80
                anchors.horizontalCenter: parent.horizontalCenter
            }
            Item_buttons{
                type: "circle_text"
                text: "?"
                width: 60
                height: 60
                anchors.top: parent.top
                anchors.topMargin: 50
                anchors.right: parent.right
                anchors.rightMargin: 50
                onClicked:{
                    click_sound.play();
                    popup_annot_help.open();
                    popup_annot_help.setTitle(qsTr("충전위치/대기위치"));
                    popup_annot_help.addLine(qsTr("충전위치와 대기위치를 지정하고 그 경로주행을 확인합니다\n도착위치를 변경하고 싶으면 각 위치를 [다시지정]해주세요"));
                    popup_annot_help.addLine(qsTr("로봇이 주행하거나 끌고 이동하는 모든 경로는 기억됩니다"));
                }
            }
            Row{
                anchors.centerIn: parent
                spacing: 100
                Item_buttons{
                    width: 220
                    height: 120
                    type: "round_text"
                    text: qsTr("충전 위치로")
                    onClicked: {
                        click_sound.play();
                        supervisor.writelog("[Annotation] Location Test : go Charging");
                        supervisor.moveToServingTest(0,"Charging0");
                    }
                }
                Item_buttons{
                    width: 220
                    height: 120
                    type: "round_text"
                    text: qsTr("대기 위치로")
                    onClicked: {
                        click_sound.play();
                        supervisor.writelog("[Annotation] Location Test : go Resting");
                        supervisor.moveToServingTest(0,"Resting0");
                    }
                }
            }


            Item_buttons{
                id: btn_left
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.bottomMargin: 50
                anchors.leftMargin: 50
                width: 200
                height: 80
                type: "round_text"
                text: qsTr("대기위치 다시 지정")
                onClicked: {
                    click_sound.play();
                    supervisor.writelog("[Annotation] Location Save : Resting -> Canceled");
                    annot_pages.sourceComponent = page_annot_location_resting;
                    edit_once = false;
                }
            }
            Item_buttons{
                anchors.bottom: btn_left.top
                anchors.left: parent.left
                anchors.bottomMargin: 20
                anchors.leftMargin: 50
                width: 200
                height: 80
                type: "round_text"
                text: qsTr("충전위치 다시 지정")
                onClicked: {
                    click_sound.play();
                    supervisor.writelog("[Annotation] Location Save : Charging -> Canceled");
                    edit_once = true;
                    annot_pages.sourceComponent = page_annot_location_charging;
                }
            }
            Item_buttons{
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                anchors.bottomMargin: 50
                anchors.rightMargin: 50
                width: 200
                height: 80
                type: "round_text"
                text: annotation_after_mapping?qsTr("다음으로"):qsTr("확 인")
                onClicked: {
                    click_sound.play();
                    supervisor.writelog("[Annotation] Location Test : Done");
                    if(annotation_after_mapping)
                        annot_pages.sourceComponent = page_annot_main_travelline;
                    else
                        annot_pages.sourceComponent = page_annot_menu;
                }
            }
        }
    }
    Component{
        id: page_annot_location_go_resting
        Item{
            width: annot_pages.width
            height: annot_pages.height
            Component.onCompleted: {
                supervisor.setMotorLock(true);
                supervisor.checkMoveFail();
            }

            Timer{
                running: true
                interval: 500
                onTriggered:{
                    supervisor.drawingRunawayStop();
                }
            }
            Rectangle{
                anchors.fill: parent
                color: color_dark_navy
            }
            Text{
                text: qsTr("지금부터 서빙위치를 지정하겠습니다\n로봇을 대기위치로 이동시켜주세요")
                color: "white"
                font.pixelSize:60
                horizontalAlignment: Text.AlignHCenter
                font.family: font_noto_b.name
                anchors.top: parent.top
                anchors.topMargin: 80
                anchors.horizontalCenter: parent.horizontalCenter
            }

            Item_buttons{
                type: "circle_text"
                text: "?"
                width: 60
                height: 60
                anchors.top: parent.top
                anchors.topMargin: 50
                anchors.right: parent.right
                anchors.rightMargin: 50
                onClicked:{
                    click_sound.play();
                    popup_annot_help.open();
                    popup_annot_help.setTitle(qsTr("대기위치로 이동"));
                    popup_annot_help.addLine(qsTr("로봇이 주행하거나 끌고 이동하는 모든 경로는 기억됩니다"));
                    popup_annot_help.addLine(qsTr("이 단계가 필요한 이유는 서빙위치와 대기위치는 서로 경로로 연결되어야하기 때문입니다"));
                    popup_annot_help.addLine(qsTr("대기위치에서 서빙위치로 출발하는 경로를 기억하기 위해서 대기위치로 이동한 뒤 서빙위치를 설정합니다"));
                }
            }
            Item_buttons{
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 100
                width: 240
                height: 140
                type: "round_text"
                text: qsTr("대기 위치로")
                onClicked: {
                    click_sound.play();
                    supervisor.writelog("[Annotation] Location Test : go Resting");

                    supervisor.moveToServingTest(0,"Resting0");
                }
            }

            Item_buttons{
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                anchors.bottomMargin: 50
                anchors.rightMargin: 50
                width: 200
                height: 80
                type: "round_text"
                text: qsTr("로봇이 대기위치입니다")
                onClicked: {
                    click_sound.play();
                    supervisor.writelog("[Annotation] Location Test : Resting -> Done");
                    annot_pages.sourceComponent = page_annot_location_serving;
                }
            }
        }
    }
    Component{
        id: page_annot_main_travelline
        Item{
            width: annot_pages.width
            height: annot_pages.height
            property bool show_map: false
            Component.onCompleted: {
                supervisor.setMotorLock(false);
                map_travel_view.setEnable(true);
                map_travel_view.setViewer("annot_location");
                map_travel_view.show_connection = false;
                map_travel_view.show_button_lidar = false;
                if(!annotation_after_mapping){
                    map_travel_view.startDrawingT();
                }
            }
            Component.onDestruction: {
                map_travel_view.setEnable(false);
                if(!annotation_after_mapping){
                    map_travel_view.stopDrawingT();
                    map_travel_view.save("tline");
                }
            }

            Timer{
                running: true
                interval: 500
                onTriggered:{
                    supervisor.drawingRunawayStart();
                    map_travel_view.startDrawingT();
                }
            }
            Rectangle{
                anchors.fill: parent
                color: color_dark_navy
            }
            AnimatedImage{
                id: image_robotmoving
                visible: !show_map
                source: "image/robot_manual.gif"
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                anchors.verticalCenterOffset: 60
                width: 1280/1.5
                height: 800/1.5
                speed: 0.5
                anchors.bottomMargin: -100
            }
            MAP_FULL2{
                id: map_travel_view
                width: 500
                objectName: "main_travelline_map"
                enabled: true
                height: 500
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                anchors.verticalCenterOffset: 85
            }
            Column{
                id: col
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                anchors.topMargin: 30
                Text{
                    text: qsTr("로봇을 주 이동경로를 따라 끌고 이동해주세요")
                    color: "white"
                    font.pixelSize: 50
                    horizontalAlignment: Text.AlignHCenter
                    font.family: font_noto_b.name
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                Column{
                    Text{
                        text: qsTr("* 주 이동경로란?")
                        color: color_green
                        font.bold: true
                        font.pixelSize:15
                        horizontalAlignment: Text.AlignHCenter
                        font.family: font_noto_r.name
                    }
                    Text{
                        text: qsTr("로봇이 이동할 때 사용하는 경로입니다 매장내부를 여러번 이동하면서 경로를 그려주세요")
                        color: "white"
                        font.pixelSize: 15
                        horizontalAlignment: Text.AlignHCenter
                        font.family: font_noto_r.name
                    }
                    Text{
                        text: qsTr("테이블의 의자가 빠지는 것을 생각해서 통로의 중앙을 통하며 경로를 그려줘야합니다")
                        color: "white"
                        font.pixelSize: 15
                        horizontalAlignment: Text.AlignHCenter
                        font.family: font_noto_r.name
                    }
                    Text{
                        text: qsTr("각 테이블의 서빙위치는 뒷 단계에서 진행하니 매장의 통로를 따라서만 진행하시면 됩니다")
                        color: "white"
                        font.pixelSize: 15
                        horizontalAlignment: Text.AlignHCenter
                        font.family: font_noto_r.name
                    }
                    Text{
                        text: qsTr("로봇이 접근하지 말아야 하는 장소는 제외해주세요 추가 설정에서 수정가능합니다")
                        color: "white"
                        font.pixelSize: 15
                        horizontalAlignment: Text.AlignHCenter
                        font.family: font_noto_r.name
                    }
                }
            }
            Item_buttons{
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                anchors.bottomMargin: 150
                anchors.rightMargin: 50
                width: 200
                height: 80
                type: "round_text"
                text: qsTr("초기화")
                visible: false
                onClicked: {
                    click_sound.play();
//                    supervisor.stop
                }
            }
            Item_buttons{
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                anchors.bottomMargin: 50
                anchors.rightMargin: 50
                width: 200
                height: 80
                type: "round_text"
                text: qsTr("전부 완료했습니다")
                onClicked: {
                    click_sound.play();
                    supervisor.writelog("[Annotation] Main Travelline : Done");
                    annot_pages.sourceComponent = page_annot_location_serving;

                }
            }
        }
    }
    Component{
        id: page_annot_location_serving
        Item{
            width: annot_pages.width
            height: annot_pages.height
            property bool show_map: false
            Component.onCompleted: {
                supervisor.setMotorLock(false);
                map_location_view.setEnable(true);
                map_location_view.setViewer("annot_location");
                map_location_view.show_connection = false;
                map_location_view.show_button_lidar = false;
                if(!annotation_after_mapping){
                    map_location_view.startDrawingT();
                }
            }

            Component.onDestruction: {
                map_location_view.setEnable(false);
                if(!annotation_after_mapping){
                    map_location_view.stopDrawingT();
                    map_location_view.save("tline");
                }
            }

            Timer{
                running: true
                interval: 500
                onTriggered:{
                    supervisor.drawingRunawayStart();
                    map_location_view.startDrawingT();
                }
            }

            Rectangle{
                anchors.fill: parent
                color: color_dark_navy
            }
            AnimatedImage{
                id: image_robotmoving
                visible: !show_map
                source: "image/robot_manual.gif"
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                anchors.verticalCenterOffset: 60
                width: 1280/1.5
                height: 800/1.5
                speed: 0.5
                anchors.bottomMargin: -100
            }
            MAP_FULL2{
                id: map_location_view
                width: 600
                objectName: "serving_map"
                visible: show_map
                enabled: show_map
                onEnabledChanged: {
                    print("location view enable",enabled);
                }
                height: 600
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                anchors.verticalCenterOffset: 60
            }
            Column{
                id: col
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                anchors.topMargin: 30
                Text{
                    text: qsTr("로봇을 각 테이블의 서빙위치로 이동시켜주신 후 저장 버튼을 누르세요")
                    color: "white"
                    font.pixelSize: 40
                    horizontalAlignment: Text.AlignHCenter
                    font.family: font_noto_b.name
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                Column{
                    Text{
                        text: qsTr("* 서빙위치란?")
                        color: color_green
                        font.bold: true
                        font.pixelSize:15
                        horizontalAlignment: Text.AlignHCenter
                        font.family: font_noto_r.name
                    }
                    Text{
                        text: qsTr("로봇이 각 테이블에 음식을 서빙하기위해 서는 장소입니다")
                        color: "white"
                        font.pixelSize: 15
                        horizontalAlignment: Text.AlignHCenter
                        font.family: font_noto_r.name
                    }
                    Text{
                        text: qsTr("로봇이 도착 후 회전할 수 있을 만큼은 테이블로부터 떨어트려주세요")
                        color: "white"
                        font.pixelSize: 15
                        horizontalAlignment: Text.AlignHCenter
                        font.family: font_noto_r.name
                    }
                }
            }
            Column{
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: 50
                spacing: 30
                Item_buttons{
                    anchors.horizontalCenter: parent.horizontalCenter
                    width: 200
                    height: 80
                    type: "round_text"
                    text: show_map?qsTr("맵 끄기"):qsTr("맵 표시")
                    onClicked: {
                        click_sound.play();
                        if(show_map){
                            show_map = false;
                        }else{
                            show_map = true;
                        }
                    }
                }
                Item_buttons{
                    anchors.horizontalCenter: parent.horizontalCenter
                    width: 200
                    height: 80
                    type: "round_text"
                    text: qsTr("목록 보기")
                    onClicked: {
                        click_sound.play();
                        popup_serving_list.open();
                    }
                }
            }

            Item_buttons{
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 50
                width: 220
                height: 120
                type: "round_text"
                text: qsTr("저 장")
                onClicked: {
                    click_sound.play();
                    supervisor.writelog("[ANNOTATION] LOCAION SAVE : Serving "+Number(supervisor.getlastRobotx())+", "+Number(supervisor.getlastRoboty())+", "+Number(supervisor.getlastRobotth()));
                    popup_add_serving.open();
                }
            }
            Item_buttons{
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                anchors.bottomMargin: 50
                anchors.rightMargin: 50
                width: 200
                height: 80
                type: "round_text"
                text: qsTr("전부 완료했습니다")
                onClicked: {
                    click_sound.play();
//                    annot_pages.sourceComponent = page_annot_location_serving;
                    annot_pages.sourceComponent = page_annot_location_serving_done;
//                    popup_drawing_notice.open();
                }
            }
            Popup{
                id: popup_drawing_notice
                width: 1280
                height:800
                y:-statusbar.height
                background:Rectangle{
                    anchors.fill: parent
                    color: color_dark_black
                    opacity: 0.8
                }
                onOpened:{
                    map_location_view.save("tline_temp");
                    map_tline.setViewer("annot_location");
                    map_tline.show_connection = false;
                    map_tline.show_button_lidar = false;
                    map_tline.setEnable(true);
                    map_tline.startDrawingT();
                }
                onClosed: {
                    map_tline.setEnable(false);
                }

                Rectangle{
                    anchors.centerIn: parent
                    width: 1280
                    height: 600
                    radius: 20
                    Row{
                        anchors.centerIn: parent
                        spacing: 100
                        Column{
                            spacing: 50
                            anchors.verticalCenter: parent.verticalCenter
                            Text{
                                anchors.horizontalCenter: parent.horizontalCenter
                                font.family: font_noto_r.name
                                font.pixelSize: 20
                                horizontalAlignment: Text.AlignHCenter
                                text: qsTr("로봇을 끌고 움직이는 대로 이동경로를 학습합니다\n로봇이 주행가능한 길을\n대기위치와 각 서빙위치 별로\n가능한 여러번 학습시켜주세요")
                            }
                            Row{
                                anchors.horizontalCenter: parent.horizontalCenter
                                spacing: 50
                                Item_buttons{
                                    width: 200
                                    height: 80
                                    type: "round_text"
                                    text: qsTr("창 닫기\n(학습된 기록은 유지)")
                                    onClicked: {
                                        click_sound.play();
                                        popup_drawing_notice.close();
                                    }
                                }
                                Item_buttons{
                                    width: 200
                                    height: 80
                                    type: "round_text"
                                    text: qsTr("완 료")
                                    onClicked: {
                                        click_sound.play();
                                        supervisor.writelog("[ANNOTATION] LOCAION SAVE : Serving Done ");
                                        annot_pages.sourceComponent = page_annot_location_serving_done;
                                        popup_drawing_notice.close();
                                    }
                                }
                            }
                        }

                        MAP_FULL2{
                            id: map_tline
                            width: 550
                            objectName: "serving_map"
                            visible: show_map
                            enabled: false
                            height: 550
                            anchors.verticalCenter: parent.verticalCenter
                        }
                    }

                }
            }

            Popup{
                id: popup_add_serving
                property var cur_group: 0
                width: 1280
                height:800
                y:-statusbar.height
                background:Rectangle{
                    anchors.fill: parent
                    color: color_dark_black
                    opacity: 0.8
                }
                onOpened:{
                    update();
                    map_location.setViewer("annot_location");
                    map_location.setEnable(true);

                    textfield_loc_name.text = "";
                }
                onClosed:{
                    map_location.setEnable(false);
                    map_location_view.setEnable(true);
                }

                Timer{
                    running: true
                    interval: 500
                    onTriggered:{
                        map_location.setfullscreen();
//                        map_location.move(0,0);
                    }
                }

                function update(){
                    model_loc_group.clear();
                    for(var i=0; i<supervisor.getLocationGroupNum(); i++){
                        model_loc_group.append({"name":supervisor.getLocGroupname(i)});
                    }
                }
                Rectangle{
                    anchors.centerIn: parent
                    width: 1280
                    height: 700
                    Column{
                        Rectangle{

                            color: "transparent"
                            width: 1280
                            height: 100
                            Text{
                                text: qsTr("서빙위치를 추가합니다")
                                anchors.centerIn: parent
                                font.pixelSize: 50
                                horizontalAlignment: Text.AlignHCenter
                                font.family: font_noto_r.name
                            }
                        }
                        Rectangle{
                            color: color_navy
                            width: 1280
                            height: 500
                            Row{
                                anchors.centerIn: parent
                                spacing: 100
                                MAP_FULL2{
                                    id: map_location
                                    width: 460
                                    objectName: "annot_add_Serving"
                                    height: 460
                                    enabled: popup_add_serving.opened
                                    anchors.verticalCenter: parent.verticalCenter
                                }
                                Column{
                                    spacing: 70
                                    anchors.verticalCenter: parent.verticalCenter
                                    Column{
                                        spacing : 20
                                        Text{
                                            text: qsTr("위치 이름")
                                            font.pixelSize: 40
                                            color: "white"
                                            horizontalAlignment: Text.AlignHCenter
                                            font.family: font_noto_r.name
                                        }
                                        TextField{
                                            id: textfield_loc_name
                                            width: 400
                                            height: 80
                                            anchors.horizontalCenter: parent.horizontalCenter
                                            placeholderText: qsTr("(이름을 입력하세요)")
                                            font.family: font_noto_r.name
                                            horizontalAlignment: Text.AlignHCenter
                                            font.pointSize: 30
                                            onFocusChanged: {
                                                keyboard.owner = textfield_loc_name;
                                                textfield_loc_name.selectAll();
                                                text_loc_check.text = "";
                                                if(focus){
                                                    keyboard.open();
                                                }else{
                                                    textfield_loc_name.select(0,0)
                                                    keyboard.close();
                                                }
                                            }
                                        }
                                        Text{
                                            id: text_loc_check
                                            anchors.horizontalCenter: parent.horizontalCenter
                                            text: qsTr("")
                                            font.pixelSize: 20
                                            color: color_red
                                            horizontalAlignment: Text.AlignHCenter
                                            font.family: font_noto_r.name
                                        }
                                    }
                                    Column{
                                        spacing: 20
                                        Text{
                                            text: qsTr("그룹 지정")
                                            font.pixelSize: 40
                                            color: "white"
                                            horizontalAlignment: Text.AlignHCenter
                                            font.family: font_noto_r.name
                                        }
//                                        Row{
//                                            anchors.horizontalCenter: parent.horizontalCenter
//                                            spacing: 30
//                                            visible: !popup_add_serving.use_group
//                                            Item_buttons{
//                                                width: 180
//                                                height: 80
//                                                type: "round_text"
//                                                text: qsTr("지정 안함")
//                                            }
//                                            Item_buttons{
//                                                width: 180
//                                                height: 80
//                                                type: "round_text"
//                                                text:  qsTr("그룹 사용")
//                                                onClicked: {
//                                                    click_sound.play();
//                                                    popup_add_serving.use_group = true;
//                                                }
//                                            }
//                                        }

                                        Flickable{
                                            width: 400
                                            height:100
                                            clip: true
                                            contentWidth: row_group.width
                                            Row{
                                                id: row_group
                                                spacing: 20
                                                anchors.verticalCenter: parent.verticalCenter
                                                Item_buttons{
                                                    width: 70
                                                    height: 70
                                                    type: "circle_text"
                                                    text:  "+"
                                                    btncolor: "black"
                                                    onClicked: {
                                                        click_sound.play();
                                                        popup_add_location_group.open();
                                                    }
                                                }
                                                Repeater{
                                                    model:ListModel{id:model_loc_group}
                                                    Item_buttons{
                                                        width: 100
                                                        height: 70
                                                        selected:popup_add_serving.cur_group === index
                                                        type: "round_text"
                                                        text: name
                                                        onClicked: {
                                                            click_sound.play();
                                                            popup_add_serving.cur_group = index
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        Rectangle{
                            color: "transparent"
                            width: 1280
                            height: 100
                            Row{
                                anchors.centerIn: parent
                                spacing: 50
                                Item_buttons{
                                    width: 180
                                    height: 80
                                    type: "round_text"
                                    text: qsTr("취소")
                                    onClicked: {
                                        click_sound.play();
                                        popup_add_serving.close();
                                    }
                                }
                                Item_buttons{
                                    width: 180
                                    height: 80
                                    type: "round_text"
                                    text: qsTr("확인")
                                    onClicked: {
                                        if(textfield_loc_name.text == ""){
                                            click_sound_no.play();
                                            textfield_loc_name.color = color_red;
                                        }else if(!supervisor.checkLocationName(popup_add_serving.cur_group, textfield_loc_name.text)){
                                            click_sound_no.play();
                                            textfield_loc_name.color = color_red;
                                            text_loc_check.text = qsTr("이미 중복되는 이름이 있습니다");
                                        }else{

                                            click_sound.play();
                                            map_hide.savelocation("location_cur","Serving", popup_add_serving.cur_group, textfield_loc_name.text);
                                            supervisor.writelog("[ANNOTATION] LOCAION SAVE : Serving -> "+popup_add_serving.cur_group+", "+textfield_loc_name.text);
                                            supervisor.writelog("[ANNOTATION] LOCAION SAVE : Serving "+Number(supervisor.getlastRobotx())+", "+Number(supervisor.getlastRoboty())+", "+Number(supervisor.getlastRobotth()));
                                            popup_add_serving.close();
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            Popup{
                id: popup_add_callbell
                anchors.centerIn: parent
                background: Rectangle{
                    anchors.fill: parent
                    color: "transparent"
                }
                width : 500
                height: 200
                property string calltype: ""
                property var callid: 0
                onOpened: {
                    supervisor.setCallbell(calltype, callid);
                }
                onClosed: {
                    supervisor.setCallbell("", -1);
                }

                Rectangle{
                    width: parent.width
                    height: parent.height
                    radius: 20
                    color: color_dark_navy
                    Text{
                        anchors.centerIn: parent
                        text: qsTr("변경하실 호출벨을 눌러주세요")
                        font.family: font_noto_r.name
                        font.pixelSize: 25
                        color: "white"
                    }
                    Item_buttons{
                        width: 100
                        height: 60
                        type: "round_text"
                        text: qsTr("사용안함")
                        onClicked: {
                            supervisor.clear_call();
                        }
                    }
                }
            }
            Popup{
                id: popup_add_location_group
                anchors.centerIn: parent
                width: 400
                height: 300
                bottomPadding: 0
                topPadding: 0
                leftPadding: 0
                rightPadding: 0
                background: Rectangle{
                    anchors.fill:parent
                    color: "white"
                }
                onOpened:{
                    tfield_group.text = "";
                }

                Rectangle{
                    id: rect_add_loc_group_1
                    width: parent.width
                    height: 55
                    color: "#323744"
                    Text{
                        anchors.centerIn: parent
                        text: qsTr("그룹 추가")
                        font.pixelSize: 40
                        font.family: font_noto_r.name
                        color: "white"
                    }
                }
                Rectangle{
                    color: "transparent"
                    width: parent.width
                    height: 250 - rect_add_loc_group_1.height
                    anchors.bottom: parent.bottom
                    Column{
                        anchors.centerIn: parent
                        spacing: 20

                        TextField{
                            id: tfield_group
                            anchors.horizontalCenter: parent.horizontalCenter
                            width: popup_add_location_group.width*0.9
                            height: 70
                            placeholderText: "(group_name)"
                            font.family: font_noto_r.name
                            horizontalAlignment: Text.AlignHCenter
                            font.pointSize: 20
                            onFocusChanged: {
                                keyboard.owner = tfield_group;
                                tfield_group.selectAll();
                                if(focus){
                                    keyboard.open();
                                }else{
                                    tfield_group.select(0,0)
                                    keyboard.close();
                                }
                            }
                        }
                        Row{
                            anchors.horizontalCenter: parent.horizontalCenter
                            spacing: 20
                            Item_buttons{
                                width: 150
                                height: 60
                                type: "round_text"
                                text: qsTr("취소")
                                onClicked: {
                                    click_sound.play();
                                    popup_add_location_group.close();
                                }
                            }
                            Item_buttons{
                                width: 150
                                height: 60
                                type: "round_text"
                                text: qsTr("확인")
                                onClicked: {
                                    if(tfield_group.text == ""){
                                        click_sound_no.play();
                                    }else{
                                        click_sound.play();
                                        supervisor.addLocationGroup(tfield_group.text);
                                        supervisor.writelog("[QML] MAP PAGE : ADD LOCATION GROUP -> "+tfield_group.text);
                                        popup_add_serving.update();
                                        readSetting();
                                        popup_add_serving.cur_group = supervisor.getLocationGroupNum()-1;
                                        popup_add_location_group.close();
                                    }
                                }
                            }
                        }
                    }
                }
                Rectangle{
                    anchors.fill:parent
                    color: "transparent"
                    border.width: 3
                    border.color: "#323744"
                }
            }

            Popup{
                id: popup_serving_list
                anchors.centerIn: parent
                width: 800
                height: 600
                background: Rectangle{
                    anchors.fill: parent
                    color: "transparent"
                }

                Rectangle{
                    width: parent.width
                    height: parent.height
                    radius: 10
                    Column{
                        anchors.centerIn: parent
                        spacing:1
                        Text{
                            text: qsTr("저장된 서빙위치 목록")
                            font.family: font_noto_r.name
                            font.pixelSize: 50
                            anchors.horizontalCenter: parent.horizontalCenter
                        }
                        Row{
                            spacing: 1
                            Rectangle{
                                width: 199
                                height: 40
                                color: color_navy
                                Text{
                                    text: qsTr("그 룹")
                                    color: "white"
                                    anchors.centerIn: parent
                                    font.family: font_noto_r.name
                                    font.pixelSize: 20
                                }
                            }
                            Rectangle{
                                width: 500
                                height: 40
                                color: color_navy
                                Text{
                                    text: qsTr("이 름")
                                    color: "white"
                                    anchors.centerIn: parent
                                    font.family: font_noto_r.name
                                    font.pixelSize: 20
                                }
                            }
                        }
                        ListView{
                            clip: true
                            model:details
                            spacing: 2
                            delegate: servings_delegate
                            anchors.horizontalCenter: parent.horizontalCenter
                            width: 700
                            height: 350
                        }
                    }
                }
            }

        }
    }
    Component{
        id: servings_delegate
        Item{
            width: 700
            height: 50
            Rectangle{
                anchors.fill: parent
                color: color_light_gray
                Row{
                    spacing:1
                    Rectangle{
                        width: 199
                        height: 50
                        color: color_yellow_rect
                        visible:ltype==="Serving"
                        Text{
                            text: supervisor.getLocGroupname(group)
                            anchors.centerIn: parent
                            font.family: font_noto_r.name
                            font.pixelSize: 20
                        }
                    }
                    Rectangle{
                        width: ltype==="Serving"?500:700
                        height: 50
                        color: color_yellow_rect
                        Text{
                            text: name
                            anchors.centerIn: parent
                            font.family: font_noto_r.name
                            font.pixelSize: 20
                        }
                    }
                }
            }
        }
    }

    Component{
        id: page_annot_location_serving_done
        Item{
            width: annot_pages.width
            height: annot_pages.height
            property bool use_callbell : true
            Component.onCompleted: {
                supervisor.setMotorLock(true);
                readSetting();
                map_location_list.init();
                map_location_list.setViewer("serving_list");
                map_location_list.setEnable(true);
                map_location_list.setTool("none");
            }
            Component.onDestruction: {
                map_location_list.setEnable(false);
                map_location_list.setCurrentLocation(-1);

            }

            Timer{
                interval: 500
                running: true
                onTriggered:{
                    supervisor.drawingRunawayStop();
                }
            }

            Rectangle{
                anchors.fill: parent
                color: color_dark_navy
            }


            function readSetting(){
                groups.clear();
                for(var i=0; i<supervisor.getLocationGroupNum(); i++){
                    groups.append({"value":supervisor.getLocGroupname(i)});
                }

                if(supervisor.getSetting("setting","USE_UI","use_callbell")==="true"){
                    use_callbell = true;
                }else{
                    use_callbell = false;
                }

                locations.clear();
                print(supervisor.getLocationNum("Serving"));
                if(supervisor.getSetting("setting","ROBOT_TYPE","type") === "CLEANING"){
                    for(var i=0; i<supervisor.getLocationNum("Serving"); i++){
                        locations.append({"name": supervisor.getLocationName(i,"Serving"),
                                       "group":supervisor.getLocationGroupNum(i),
                                        "call_id" : supervisor.getLocationCallID(3+i),
                                       "error":false});
                    }
                }else{
                    for(var i=0; i<supervisor.getLocationNum("Serving"); i++){
                        locations.append({"name": supervisor.getLocationName(i,"Serving"),
                                       "group":supervisor.getLocationGroupNum(i),
                                        "call_id" : supervisor.getLocationCallID(2+i),
                                       "error":false});
                    }
                }

                update();
            }

            function update(){
                popup_add_callbell.close();

                details.clear();
                print("READ SETTING!!!!!!!!!!!!!!!!!!!!!!");
                details.append({"ltype":"Charging",
                                   "name":qsTr("충전위치"),
                                   "group":0,
                                   "callerror":false,
                                   "nameerror":false,
                                   "call_id":supervisor.getLocationCallID(0)});
                details.append({"ltype":"Resting",
                                   "name":qsTr("대기위치"),
                                   "group":0,
                                   "callerror":false,
                                   "nameerror":false,
                                   "call_id":supervisor.getLocationCallID(1)});
                if(supervisor.getRobotType()==="CLEANING"){
                    details.append({"ltype":"Cleaning",
                                       "name":qsTr("퇴식위치"),
                                       "group":0,
                                       "callerror":false,
                                       "nameerror":false,
                                       "call_id":supervisor.getLocationCallID(2)});
                }
                for(var i=0; i<locations.count; i++){
                    details.append({"ltype":"Serving",
                                    "name":locations.get(i).name,
                                   "group":locations.get(i).group,
                                    "call_id":locations.get(i).call_id,
                                   "callerror":locations.get(i).callerror,
                                       "nameerror":locations.get(i).nameerror});
//                        print("detail append : ",i, locations.get(i).group, locations.get(i).number, getgroupsize(locations.get(i).group))
                }
//                print("=================================");
                checkLocationNumber();
                checkLocationName();
//                print("=================================");

                list_location_detail.currentIndex = select_location;

                if(isError()){
                    btn_right.enabled = false;
                }else{
                    btn_right.enabled = true;
                }
            }

            function isError(){
                for(var i=0; i<details.count; i++){
                    if(details.get(i).ltype === "Serving")
                        if(details.get(i).callerror || details.get(i).nameerror)
                            return true;
                }
                return false;
            }

            function groupchange(number, group){
                print(" group change ",number,group,details.count);
                if(supervisor.getSetting("setting","ROBOT_TYPE","type") === "CLEANING"){
                    if(number > 2 && number < details.count){
                        supervisor.setLocationGroup(number,group);
                        locations.get(number-3).group = group;
                        locations.get(number-3).number = 0;
                    }

                }else{
                    if(number > 1 && number < details.count){
                        supervisor.setLocationGroup(number,group);
                        locations.get(number-2).group = group;
                        locations.get(number-2).number = 0;
                    }
                }
                update();
            }

            function tablechange(number, table){
                    print("table change ",number,table)
                if(number > 1 && number < details.count){
                    locations.get(number-2).number = table;
                }
                update();
            }

            function update_callbell(){
                details.get(0).call_id = supervisor.getLocationCallID("Charging",0);
                details.get(1).call_id = supervisor.getLocationCallID("Resting",0);
                if(supervisor.getRobotType()==="CLEANING"){
                    details.get(2).call_id = supervisor.getLocationCallID("Cleaning",0);

                    for(var i=3; i<details.count; i++){
                        details.get(i).call_id = supervisor.getLocationCallID("Serving",i-3);
                        print(i,details.get(i).call_id);
                    }
                }else{
                    for(var i=2; i<details.count; i++){
                        details.get(i).call_id = supervisor.getLocationCallID("Serving",i-2);
                        print(i,details.get(i).call_id);
                    }
                }

            }

            function checkLocationNumber(){
                for(var i=0; i<details.count; i++){
                    for(var j=i+1; j<details.count; j++){
                        if(details.get(i).call_id === "" || details.get(i).call_id === "-")
                            continue;
                        else if(details.get(i).call_id === details.get(j).call_id){
                            details.get(i).callerror = true;
                            details.get(j).callerror = true;
                        }
                    }
                }
            }
            function clearLocationName(){
                for(var i=0; i<details.count; i++){
                    details.get(i).nameerror = false;
                }

            }

            function checkLocationName(){
                for(var i=0; i<details.count; i++){
                    for(var j=i+1; j<details.count; j++){
                        if(details.get(i).group === details.get(i).group)
                            if(details.get(i).name === details.get(j).name){
                                details.get(i).nameerror = true;
                                details.get(j).nameerror = true;
                            }
                    }
                }
                if(isError()){
                    btn_right.enabled = false;
                }else{
                    btn_right.enabled = true;
                }
            }

            ListModel{
                id: locations
            }

            ListModel{
                id: groups
            }
            Component{
                id: detaillocCompo
                Item{
                    width: parent.width
                    height: 50
                    Column{
                        anchors.right: rowsss.left
                        anchors.verticalCenter: rowsss.verticalCenter
                        anchors.rightMargin: 5
                        spacing: 5
                        visible: select_location === index && ltype === "Serving"
                        Rectangle{
                            width: 30
                            height: 30
                            Image{
                                anchors.centerIn: parent
                                source:"icon/keyboard_up.png"
                            }
                            MouseArea{
                                anchors.fill: parent
                                onClicked:{
                                    click_sound.play();
                                    if(supervisor.getRobotType() === "CLEANING"){
                                        if(select_location>3){
                                            combo_group.focus = false;
                                            tx_name.focus = false;
                                            keyboard.close();
                                            supervisor.setLocationUp(select_location);
                                            select_location--;
                                            print("up select_location ",select_location);
                                            readSetting();
                                        }
                                    }else{
                                        if(select_location>2){
                                            combo_group.focus = false;
                                            tx_name.focus = false;
                                            keyboard.close();
                                            supervisor.setLocationUp(select_location);
                                            select_location--;
                                            print("up select_location ",select_location);
                                            readSetting();
                                        }
                                    }
                                }
                            }
                        }
                        Rectangle{
                            width: 30
                            height: 30
                            Image{
                                anchors.centerIn: parent
                                source:"icon/keyboard_down.png"
                            }
                            MouseArea{
                                anchors.fill: parent
                                onClicked:{
                                    click_sound.play();
                                    if(select_location<details.count-1){
                                        combo_group.focus = false;
                                        tx_name.focus = false;
                                        keyboard.close();
                                        supervisor.setLocationDown(select_location);
                                        select_location++;
                                        readSetting();
                                    }
                                }
                            }
                        }
                    }

                    Row{
                        id: rowsss
                        anchors.horizontalCenter: parent.horizontalCenter
                        spacing: 5
                        Rectangle{
                            width: 50
                            height: 50
                            color:select_location === index?color_green:"white"
                            Text{
                                anchors.centerIn: parent
                                text: index
                                font.family: font_noto_r.name
                            }
                            MouseArea{
                                anchors.fill: parent
                                onClicked:{
                                    if(select_location == index){
                                        select_location = -1;
                                    }else{
                                        select_location = index;
                                    }
                                    map_location_list.setCurrentLocation(select_location);
                                }
                            }
                        }

                        ComboBox{
                            id: combo_group
                            visible: ltype === "Serving"
                            width: 160
                            height: 50
                            model: groups
                            background: Rectangle{
                                color:select_location === index?color_green:"white"
                            }
                            onFocusChanged: {
                                if(focus){
                                    select_location = index;
                                    print("combo focus on select_location ",index);
                                }
                            }

//                            style
                            currentIndex: group
                            onCurrentIndexChanged: {
                                if(focus){
                                    if(select_location == index){
                                        select_location = -1;
                                    }else{
                                        select_location = index;
                                        print("group focus select_location",index);
                                    }
                                    map_location_list.setCurrentLocation(select_location);
                                    groupchange(index,currentIndex);
                                }
                            }
                        }
                        Image{
                            visible: nameerror && ltype ==="Serving"
                            source: "icon/icon_error.png"
                            width: 40
                            height: 38
                            anchors.verticalCenter: parent.verticalCenter
                        }
                        TextField{
                            id: tx_name
                            text: name
                            background: Rectangle{
                                color:select_location === index?color_green:"white"
                            }
                            width : ltype ==="Serving"?nameerror?205:250:250+160+5
                            height: 50
                            font.family: font_noto_r.name
                            font.pixelSize: 20
                            horizontalAlignment: Text.AlignHCenter
                            onFocusChanged: {
                                keyboard.owner = tx_name;
                                tx_name.selectAll();
                                if(focus){
                                    if(select_location == index){
                                        select_location = -1;
                                    }else{
                                        print("name focus select_location",index);
                                        select_location = index;
                                    }
                                    map_location_list.setCurrentLocation(select_location);
                                    keyboard.open();
                                }else{
                                    keyboard.close();
                                    tx_name.select(0,0);
                                }
                            }
                            onTextChanged: {
                                name = text;
                                if(locations.count > index){
                                    if(supervisor.getRobotType() === "CLEANING"){
                                        if(index > 2){
                                            locations.get(index-3).name = name;
                                        }

                                    }else{
                                        if(index > 1){
                                            locations.get(index-2).name = name;
                                        }
                                    }
                                }
                                clearLocationName();
                                checkLocationName();
                            }
                        }
                        Image{
                            visible: callerror && ltype ==="Serving"
                            source: "icon/icon_error.png"
                            width: 40
                            height: 38
                            anchors.verticalCenter: parent.verticalCenter
                        }
                        Rectangle{
                            width : callerror && ltype ==="Serving"?105:150
                            height: 50
                            color:select_location === index?color_green:"white"
                            Text{
                                anchors.centerIn: parent
                                font.family: font_noto_r.name
                                text: call_id==""?" - ":call_id
                            }
                            MouseArea{
                                anchors.fill: parent
                                onClicked:{
                                    if(select_location == index){
                                        select_location = -1;
                                    }else{
                                        select_location = index;
                                    }
                                    map_location_list.setCurrentLocation(select_location);
                                }
                            }
                        }
                    }
                }
            }

            Text{
                id: teeeeee
                text: annotation_after_mapping?qsTr("서빙 위치를 다시한번 확인해주세요"):qsTr("서빙위치를 수정합니다")
                color: "white"
                font.pixelSize: 60
                horizontalAlignment: Text.AlignHCenter
                font.family: font_noto_b.name
                anchors.top: parent.top
                anchors.topMargin: 30
                anchors.horizontalCenter: parent.horizontalCenter
            }

            Row{
                anchors.top: teeeeee.bottom
                anchors.topMargin: 20
                Rectangle{
                    width: 450
                    height: 630
                    color:"transparent"
                    Column{
                        anchors.horizontalCenter: parent.horizontalCenter
                        spacing: 20
                        Grid{
                            columns:2
                            rows:2
                            anchors.horizontalCenter: parent.horizontalCenter
                            spacing: 10
                            Item_buttons{
                                width: 140
                                height: 60
                                enabled: select_location>-1
                                type: "round_text"
                                text: qsTr("호출벨 설정")
                                fontsize: 20
                                onClicked: {
                                    click_sound.play();
                                    popup_add_callbell.calltype = details.get(select_location).ltype;
                                    popup_add_callbell.callid = select_location;
                                    popup_add_callbell.open();
                                }
                            }
                            Item_buttons{
                                width: 140
                                height: 60
                                enabled: select_location>-1
                                type: "round_text"
                                text: qsTr("테스트 주행")
                                fontsize: 20
                                onClicked: {
                                    click_sound.play();
                                    supervisor.writelog("[ANNOTATION] TEST MOVING : "+details.get(select_location).name);
                                    supervisor.moveToServingTest(details.get(select_location).group, details.get(select_location).name);
                                }
                            }
                            Item_buttons{
                                width: 140
                                height: 60
                                enabled: select_location>1
                                type: "round_text"
                                text: qsTr("삭제")
                                fontsize: 20
                                onClicked: {
                                    click_sound.play();
                                    popup_remove_location.open();
                                }
                            }
                            Item_buttons{
                                width: 140
                                height: 60
                                enabled: select_location>-1
                                type: "round_text"
                                text: qsTr("위치 수정")
                                fontsize: 20
                                onClicked: {
                                    click_sound.play();
                                    supervisor.writelog("[ANNOTATION] Location Edit : "+details.get(select_location).name);
                                    popup_edit_serving.open();

                                }
                            }

                        }
                        MAP_FULL2{
                            id: map_location_list
                            width: 350
                            anchors.horizontalCenter: parent.horizontalCenter
                            height: 350
                        }
                        Row{
                            anchors.horizontalCenter: parent.horizontalCenter
                            spacing: 10
                            Item_buttons{
                                width: 140
                                height: 60
                                type: "round_text"
                                text: qsTr("서빙위치 추가")
                                onClicked: {
                                    click_sound.play();
                                    supervisor.writelog("[ANNOTATION] LOCAION SAVE : Back to Serving");
                                    annot_pages.sourceComponent = page_annot_location_serving;
                                }
                            }
                            Item_buttons{
                                width: 140
                                height: 60
                                type: "round_text"
                                text: qsTr("그룹 추가")
                                fontsize: 20
                                onClicked: {
                                    click_sound.play();
                                    popup_add_location_group.open();
                                }
                            }
                            Item_buttons{
                                width: 140
                                height: 60
                                type: "round_text"
                                text: qsTr("퇴식위치 추가")
                                onClicked: {
                                    click_sound.play();
                                    select_location = -1;
                                    popup_cleaning.open();
                                }
                            }
                        }
                    }
                }
                Rectangle{
                    width: 1
                    height: 600
                }

                Rectangle{
                    id: rect_list_column
                    color: "transparent"
                    width: 1280-491
                    height: 500
                    Column{
                        id: cooo
                        spacing: 5
                        Row{
                            anchors.horizontalCenter: parent.horizontalCenter
                            id: ddddd
                            spacing: 5
                            Rectangle{
                                width: 50
                                height: 30
                                color: color_navy
                                Text{
                                    anchors.centerIn: parent
                                    text: qsTr("번호")
                                    font.family: font_noto_r.name
                                    color: "white"
                                }
                            }
                            Rectangle{
                                width: 160
                                height: 30
                                color: color_navy
                                Text{
                                    anchors.centerIn: parent
                                    text: qsTr("그룹")
                                    font.family: font_noto_r.name
                                    color: "white"
                                }
                            }
                            Rectangle{
                                width: 250
                                height: 30
                                color: color_navy
                                Text{
                                    anchors.centerIn: parent
                                    text: qsTr("이름")
                                    font.family: font_noto_r.name
                                    color: "white"
                                }
                            }
                            Rectangle{
                                width: 150
                                height: 30
                                color: color_navy
                                Text{
                                    anchors.centerIn: parent
                                    text: qsTr("호출벨")
                                    font.family: font_noto_r.name
                                    color: "white"
                                }
                            }
                        }

                        Flickable{
                            width: rect_list_column.width
                            height: 450-35
                            clip: true
                            anchors.horizontalCenter: parent.horizontalCenter
                            contentHeight: list_location_detail.height
                            ScrollBar.vertical: ScrollBar{
                                width: 25
                                anchors.right: parent.right
                                anchors.rightMargin: 10
                                policy: ScrollBar.AlwaysOn
                            }
                            ListView{
                                id: list_location_detail
                                width: ddddd.width
                                height: parent.height
                                spacing: 5
                                anchors.horizontalCenter: parent.horizontalCenter
                                delegate: detaillocCompo
                                model:details
                            }
                        }
                    }
                }
            }


            Item_buttons{
                id: btn_right
                width: 200
                height: 80
                type: "round_text"
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                anchors.bottomMargin: 50
                anchors.rightMargin: 50
                enabled: false
                text: qsTr("저 장")
                onClicked: {
                    click_sound.play();
                    print("save location");
                    supervisor.saveAnnotation(supervisor.getMapname());
                    supervisor.drawingRunawayStop();
                    map_hide.stopDrawingT();
                    supervisor.writelog("[ANNOTATION] LOCAION SAVE : Check Done ");
                    if(annotation_after_mapping)
                        annot_pages.sourceComponent = page_annot_done;
                    else
                        loadPage(pmap);
//                        annot_pages.sourceComponent = page_annot_menu;
                }
            }

            Item_buttons{
                id: btn_right22
                width: 200
                height: 80
                type: "round_text"
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                anchors.bottomMargin: 50
                anchors.rightMargin: 280
                enabled: false
                text: qsTr("취 소")
                onClicked: {
                    click_sound.play();
                    annot_pages.sourceComponent = page_annot_menu;
                }
            }
            Row{
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.bottomMargin: 50
                anchors.leftMargin: 50
                spacing: 20
                Item_buttons{
                    width: 180
                    height: 80
                    type: "round_text"
                    text: qsTr("번호 자동세팅")
                    visible: false
                    onClicked: {
                        for(var i=0; i<details.count-2; i++){
                            supervisor.setLocation(i,details.get(i+2).name,details.get(i+2).group,details.get(i+2).number);
                        }
                        click_sound.play();
                        map_hide.setTableNumberAuto();
                        annot_pages.item.readSetting();
                    }
                }
            }
            Popup{
                id: popup_cleaning
                anchors.centerIn: parent
                width: 1280
                height: 400
                background: Rectangle{
                    anchors.fill: parent
                    color: "transparent"
                }
                Rectangle{
                    width: parent.width
                    height: parent.height
                    color: color_dark_navy
                    Column{
                        anchors.centerIn: parent
                        spacing: 30
                        Text{
                            anchors.horizontalCenter: parent.horizontalCenter
                            text: qsTr("퇴식위치를 별도로 사용하십니까?")
                            font.pixelSize: 50
                            font.family: font_noto_r.name
                            color: "white"
                        }
                        Column{
                            anchors.horizontalCenter: parent.horizontalCenter
                            Text{
                                anchors.horizontalCenter: parent.horizontalCenter
                                text: qsTr("퇴식전용모드로 전환됩니다")
                                font.pixelSize: 20
                                font.family: font_noto_r.name
                                color: "white"
                            }
                            Text{
                                anchors.horizontalCenter: parent.horizontalCenter
                                text: qsTr("로봇이 테이블을 다녀온 뒤 퇴식위치로 이동하여 대기합니다 추후 세팅에서 모드를 변경하실 수 있습니다")
                                font.pixelSize: 20
                                font.family: font_noto_r.name
                                color: "white"
                            }
                            Text{
                                anchors.horizontalCenter: parent.horizontalCenter
                                text: qsTr("퇴식위치의 기본값은 대기위치와 동일합니다 변경을 원하시면 위치 수정을 해주세요")
                                font.pixelSize: 20
                                font.family: font_noto_r.name
                                color: "white"
                            }
                        }
                        Row{
                            anchors.horizontalCenter: parent.horizontalCenter
                            spacing: 50
                            Item_buttons{
                                width: 150
                                height: 60
                                type: "round_text"
                                text: qsTr("예")
                                onClicked: {
                                    click_sound.play();
                                    supervisor.setSetting("setting","ROBOT_TYPE/type","CLEANING");
                                    supervisor.readSetting();
                                    annot_pages.item.readSetting();
                                    popup_cleaning.close();
                                }
                            }
                            Item_buttons{
                                width: 150
                                height: 60
                                type: "round_text"
                                text: qsTr("아니오")
                                onClicked: {
                                    click_sound.play();
                                    supervisor.setSetting("setting","ROBOT_TYPE/type","BOTH");
                                    supervisor.readSetting();
                                    annot_pages.item.readSetting();
                                    popup_cleaning.close();
                                }
                            }
                        }

                    }
                }
            }

            Popup{
                id: popup_remove_location
                anchors.centerIn: parent
                property string name : ""
                background: Rectangle{
                    anchors.fill: parent
                    color: "transparent"
                }
                onOpened:{
                    name = supervisor.getLocationName(select_location);
                }
                width: 1280
                height: 350

                Rectangle{
                    width: parent.width
                    height: parent.height
                    color: color_dark_black
                    Column{
                        anchors.centerIn: parent
                        spacing: 40
                        Column{
                            anchors.horizontalCenter: parent.horizontalCenter
                            spacing: 10
                            Text{
                                anchors.horizontalCenter: parent.horizontalCenter
                                text: qsTr("삭제하시겠습니까?")
                                font.pixelSize: 40
                                font.family: font_noto_r.name
                                color: "white"
                            }
                            Text{
                                anchors.horizontalCenter: parent.horizontalCenter
                                text: qsTr("위치 : ")+popup_remove_location.name
                                font.pixelSize: 35
                                font.family: font_noto_r.name
                                color: "white"
                            }
                        }

                        Row{
                            anchors.horizontalCenter: parent.horizontalCenter
                            spacing: 50
                            Item_buttons{
                                width: 150
                                height: 60
                                type: "round_text"
                                text: qsTr("예")
                                onClicked: {
                                    click_sound.play();
                                    supervisor.removeLocation(select_location);
                                    select_location = -1;
                                    annot_pages.item.readSetting();
                                    popup_remove_location.close();
                                }
                            }
                            Item_buttons{
                                width: 150
                                height: 60
                                type: "round_text"
                                text: qsTr("아니오")
                                onClicked: {
                                    click_sound.play();
                                    popup_remove_location.close();
                                }
                            }
                        }
                    }
                }
            }

            Popup{
                id: popup_edit_serving
                width: 1280
                height: 800-statusbar.height
                background: Rectangle{
                    anchors.fill: parent
                    color: "transparent"
                }
                property string location_name: ""
                onOpened:{
                    supervisor.setMotorLock(false);
                    if(select_location == 0){
                        text_men.text = qsTr("수정하실 충전위치로 로봇을 이동시켜 주세요")
                        text_loc.text = ""
                    }else if(select_location == 1){
                        text_men.text = qsTr("수정하실 대기위치로 로봇을 이동시켜 주세요")
                        text_loc.text = ""
                    }else{
                        if(supervisor.getRobotType()==="CLEANING"){
                            if(select_location == 2){
                                text_men.text = qsTr("수정하실 퇴식위치로 로봇을 이동시켜 주세요")
                                text_loc.text = ""
                            }else{
                                text_men.text = qsTr("수정하실 서빙위치로 로봇을 이동시켜 주세요")
                                text_loc.text = qsTr("( 이름 : ")+details.get(select_location).name+" )"
                            }
                        }else{
                            text_men.text = qsTr("수정하실 서빙위치로 로봇을 이동시켜 주세요")
                            text_loc.text = qsTr("( 이름 : ")+details.get(select_location).name+" )"
                        }
                    }
                }
                onClosed:{
                    supervisor.setMotorLock(true);
                }
                Rectangle{
                    width: parent.width
                    height: parent.height
                    color: color_dark_navy
                    Column{
                        anchors.centerIn: parent
                        Text{
                            id: text_men
                            anchors.horizontalCenter: parent.horizontalCenter
                            font.family:font_noto_r.name
                            font.pixelSize: 60
                            color: "white"
                            text:qsTr("수정하실 서빙위치로 로봇을 이동시켜 주세요")
                        }
                        Text{
                            id: text_loc
                            anchors.horizontalCenter: parent.horizontalCenter
                            font.family:font_noto_r.name
                            font.pixelSize: 40
                            color: "white"
                            text:popup_edit_serving.location_name
                        }
                        AnimatedImage{
                            id: image_robotmoving
                            source: "image/robot_manual.gif"
                            anchors.horizontalCenter: parent.horizontalCenter
                            width: 1280/1.5
                            height: 800/1.5
                            speed: 0.5
                        }
                    }
                    Item_buttons{
                        type:"round_text"
                        width: 200
                        height: 80
                        text:qsTr("이동했습니다")
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: 50
                        anchors.right: parent.right
                        anchors.rightMargin: 50
                        onClicked:{
                            supervisor.editLocation(select_location);
    //                                supervisor.setLocation(select_location,details.get(select_location).name,details.get(select_location).group,0)
                            map_location_list.init();
                            map_location_list.setCurrentLocation(select_location);
                            popup_edit_serving.close();
                        }
                    }
                    Item_buttons{
                        type:"round_text"
                        width: 200
                        height: 80
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: 50
                        anchors.left: parent.left
                        anchors.leftMargin: 50
                        text:qsTr("취소")
                        onClicked:{
                            popup_edit_serving.close();
                        }
                    }

                }
            }

            Popup{
                id: popup_add_callbell
                anchors.centerIn: parent
                background: Rectangle{
                    anchors.fill: parent
                    color: "transparent"
                }
                width : 1280
                height: 400
                property string calltype: ""
                property var callid: 0
                onOpened: {
                    supervisor.setCallbell(calltype, callid);
                    cb_callbell_force.checked = false;
                    if(calltype === "Resting" || calltype === "Cleaning"){
                        row_call_force.visible = true;
                    }else{
                        row_call_force.visible = false;
                    }
                }
                onClosed: {
                    supervisor.setCallbell("", -1);
                    supervisor.setCallbellForce(calltype,cb_callbell_force.checked);
                }


                Rectangle{
                    width: parent.width
                    height: parent.height
                    color: color_dark_navy
                    Column{
                        anchors.centerIn: parent
                        spacing: 30
                        Text{
                            anchors.horizontalCenter: parent.horizontalCenter
                            text: qsTr("변경하실 호출벨을 눌러주세요")
                            font.family: font_noto_r.name
                            font.pixelSize: 50
                            color: "white"
                        }
                        Row{
                            id: row_call_force
                            anchors.horizontalCenter: parent.horizontalCenter
                            spacing: 50
                            CheckBox{
                                id: cb_callbell_force
                                anchors.verticalCenter: parent.verticalCenter
                                width:40
                                height:40
                            }
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                text: qsTr("강제 귀환")
                                color: "white"
                                font.family: font_noto_r.name
                                font.pixelSize: 30
                            }
                        }
                        Item_buttons{
                            width: 180
                            height: 60
                            anchors.horizontalCenter: parent.horizontalCenter
                            type: "round_text"
                            text: qsTr("사용안함")
                            onClicked: {
                                click_sound.play();
                                supervisor.clear_call();
                                popup_add_callbell.close();
                            }
                        }
                    }

                }
            }
            Popup{
                id: popup_add_location_group
                anchors.centerIn: parent
                width: 400
                height: 250
                bottomPadding: 0
                topPadding: 0
                leftPadding: 0
                rightPadding: 0
                background: Rectangle{
                    anchors.fill:parent
                    color: "white"
                }
                onOpened:{
                    tfield_group.text = "";
                }

                Rectangle{
                    id: rect_add_loc_group_1
                    width: parent.width
                    height: 45
                    color: "#323744"
                    Text{
                        anchors.centerIn: parent
                        text: qsTr("그룹 추가")
                        font.pixelSize: 20
                        font.family: font_noto_r.name
                        color: "white"
                    }
                }
                Rectangle{
                    color: "transparent"
                    width: parent.width
                    height: 250 - rect_add_loc_group_1.height
                    anchors.bottom: parent.bottom
                    Column{
                        anchors.centerIn: parent
                        spacing: 20

                        TextField{
                            id: tfield_group
                            anchors.horizontalCenter: parent.horizontalCenter
                            width: popup_add_location_group.width*0.9
                            height: 50
                            placeholderText: "(group_name)"
                            font.family: font_noto_r.name
                            horizontalAlignment: Text.AlignHCenter
                            font.pointSize: 20
                            onFocusChanged: {
                                keyboard.owner = tfield_group;
                                tfield_group.selectAll();
                                if(focus){
                                    keyboard.open();
                                }else{
                                    tfield_group.select(0,0)
                                    keyboard.close();
                                }
                            }
                        }
                        Row{
                            anchors.horizontalCenter: parent.horizontalCenter
                            spacing: 20
                            Item_buttons{
                                width: 130
                                height: 50
                                type: "round_text"
                                text: qsTr("취소")
                                onClicked: {
                                    click_sound.play();
                                    popup_add_location_group.close();
                                }
                            }
                            Item_buttons{
                                width: 130
                                height: 50
                                type: "round_text"
                                text: qsTr("확인")
                                onClicked: {
                                    if(tfield_group.text == ""){
                                        click_sound_no.play();
                                    }else{
                                        click_sound.play();
                                        supervisor.addLocationGroup(tfield_group.text);
                                        supervisor.writelog("[QML] MAP PAGE : ADD LOCATION GROUP -> "+tfield_group.text);
                                        update();
                                        readSetting();
                                        popup_add_location_group.close();
                                    }
                                }
                            }
                        }
                    }
                }
                Rectangle{
                    anchors.fill:parent
                    color: "transparent"
                    border.width: 3
                    border.color: "#323744"
                }
            }
        }
    }
    Component{
        id: page_annot_done
        Item{
            width: annot_pages.width
            height: annot_pages.height
            property var local_find_state: 0
            Rectangle{
                anchors.fill: parent
                color: color_dark_navy
            }
            Component.onCompleted: {
                supervisor.setMotorLock(true);
                text_title1.opacity = 1;
                text_title12.opacity = 1;
                text_title2.opacity = 1;
                btn_right.opacity = 1;
                btn_right2.opacity = 1;

            }

            Timer{
                running: true
                interval: 500
                onTriggered:{
                    supervisor.drawingRunawayStop();
                    map_hide.stopDrawingT();
                }
            }
            Text{
                id: text_title1
                text: qsTr("수고하셨습니다")
                color: "white"
                opacity: 0
                Behavior on opacity {
                    NumberAnimation{
                        duration : 1000
                    }
                }
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 80
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                anchors.topMargin: 140
                font.family: font_noto_b.name
            }
            Text{
                id: text_title12
                text: qsTr("맵 설정이 저장되었습니다")
                color: "white"
                opacity: 0
                Behavior on opacity {
                    NumberAnimation{
                        duration : 1000
                    }
                }
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 60
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: text_title1.bottom
                anchors.topMargin: 3
                font.family: font_noto_b.name
            }

            Text{
                id: text_title2
                text: qsTr("추가로 맵의 안전속도 구간과 이동경로를 수정하실 수 있습니다.\n설정을 여기서 완료하시거나 추가 설정을 원하신다면 아래 버튼을 눌러주세요")
                color: "white"
                opacity: 0
                Behavior on opacity {
                    NumberAnimation{
                        duration : 1200
                    }
                }
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 25
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: text_title12.bottom
                anchors.topMargin: 20
                font.family: font_noto_r.name
            }
            Item_buttons{
                id: btn_right
                width: 200
                height: 80
                type: "round_text"
                text: qsTr("종 료")
                opacity: 0
                Behavior on opacity {
                    NumberAnimation{
                        duration : 1500
                    }
                }
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                anchors.bottomMargin: 150
                anchors.rightMargin: 50
                onClicked: {
                    click_sound.play();
                    supervisor.slam_map_reload(supervisor.getMapname());
                    supervisor.writelog("[ANNOTATION] Early Done");
                    loadPage(pinit);
                }
            }
            Item_buttons{
                id: btn_right2
                width: 200
                height: 80
                type: "round_text"
                text: qsTr("추가 설정")
                opacity: 0
                Behavior on opacity {
                    NumberAnimation{
                        duration : 1500
                    }
                }
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                anchors.bottomMargin: 50
                anchors.rightMargin: 50
                onClicked: {
                    click_sound.play();
//                    supervisor.slam_map_reload(supervisor.getMapname());
                    supervisor.writelog("[ANNOTATION] Next to Additional");
                    annot_pages.sourceComponent = page_annot_additional_menu;
                }
            }
        }
    }
    Component{
        id: page_annot_additional_menu
        Item{
            width: annot_pages.width
            height: annot_pages.height
            property var local_find_state: 0
            Rectangle{
                anchors.fill: parent
                color: color_dark_navy
            }
            Component.onCompleted: {
                supervisor.setMotorLock(true);
            }

            Text{
                id: text_title1
                text: qsTr("맵의 추가설정을 합니다")
                color: "white"
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 60
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                anchors.topMargin: 80
                font.family: font_noto_b.name
            }
            Text{
                id: text_title12
                text: qsTr("이 부분은 로봇 운영에 있어 필수는 아닙니다")
                color: "white"
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 40
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: text_title1.bottom
                font.family: font_noto_b.name
            }
            Row{
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: text_title12.bottom
                anchors.topMargin: 100
                spacing: 50
//                Item_buttons{
//                    width: 220
//                    height: 180
//                    type: "round_text"
//                    text: qsTr("안전속도\n구간설정")
//                    onClicked: {
//                        click_sound.play();
//                        supervisor.writelog("[ANNOTATION] Enter : Velocity Map");
//                        annot_pages.sourceComponent = page_annot_velmap;
//                    }
//                }
                Item_buttons{
                    width: 220
                    height: 180
                    type: "round_text"
                    text: qsTr("이동경로\n설정")
                    onClicked: {
                        click_sound.play();
                        supervisor.loadFile(supervisor.getMapname(),"");
                        supervisor.writelog("[ANNOTATION] Enter : Travelline Map");
                        annot_pages.sourceComponent = page_annot_travelline;
                    }
                }
                Item_buttons{
                    width: 220
                    height: 180
                    type: "round_text"
                    text: qsTr("맵 세부수정")
                    onClicked: {
                        click_sound.play();
                        supervisor.writelog("[ANNOTATION] Enter : Map Editor");
                        annot_pages.sourceComponent = page_annot_map_editor;
                    }
                }
//                Item_buttons{
//                    width: 220
//                    height: 180
//                    type: "round_text"
//                    text: qsTr("고정장애물 인식")
////                    visible:
//                    onClicked: {
//                        click_sound.play();
//                        supervisor.writelog("[ANNOTATION] Enter : Object Map");
//                        annot_pages.sourceComponent = page_annot_object;
//                    }
//                }
//                Item_buttons{
//                    width: 220
//                    height: 180
//                    type: "round_text"
//                    text: qsTr("맵\n예쁘게그리기")
//                    visible: false
//                    onClicked: {
//                        click_sound.play();
//                        supervisor.writelog("[ANNOTATION] Enter : Map Drawing");
//                        annot_pages.sourceComponent = page_annot_drawmap;
//                    }
//                }
            }
            Item_buttons{
                id: btn_right
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                anchors.bottomMargin: 50
                anchors.rightMargin: 50
                width: 220
                height: 90
                type: "round_text"
                text: qsTr("종 료")
                onClicked: {
                    click_sound.play();
                    supervisor.writelog("[ANNOTATION] All Done");
                    if(annotation_after_mapping)
                        loadPage(pinit);
                    else
                        annot_pages.sourceComponent = page_annot_menu;
                }
            }
        }
    }
    Component{
        id: page_annot_object
        Item{
            width: annot_pages.width
            height: annot_pages.height
            property bool is_drawing: false
            property var select_mode: 0
            property bool mode_drawing: true
            Rectangle{
                anchors.fill: parent
                color: color_dark_navy
            }

            Component.onCompleted: {
                loading.hide();
                select_preset = 0;
                supervisor.readSetting(supervisor.getMapname());
                supervisor.setMotorLock(false);
                map.setEnable(true);
                if(mode_drawing){
                    map.setViewer("annot_object_png");
                }else{
                    map.setViewer("annot_object");
                    update_object();
                }
            }
            Component.onDestruction: {
                map.setEnable(false);
                if(supervisor.getLockStatus())
                    supervisor.setMotorLock(true);

                if(supervisor.getObjectflag())
                    supervisor.stopDrawObject();
            }

            function update_object(){
                model_objs.clear();
                for(var i=0; i<supervisor.getObjectNum(); i++){
                    model_objs.append({"n":"d"});
                }
            }

            Timer{
                running: true
                repeat: true
                interval: 500
                triggeredOnStart: true
                onTriggered: {
                    map.checkDrawing();
                    if(map.is_drawing_undo)
                        btn_undo.enabled = true;
                    else
                            btn_undo.enabled = false;

                        if(supervisor.getObjectflag()){
                            is_object = true;
                            btn_undo.enabled = true;
                            btn_clear.enabled = true;
                        }else{
                            is_object = false;
                            btn_undo.enabled = false;
                            btn_clear.enabled = false;
                        }
                    }
                }

                Timer{
                    id: timer_check_drawing
                    interval: 500
                    repeat: true
                    onTriggered:{
                        if(supervisor.getObjectflag()){
                            btn_do_drawing.running = true;
                        }else{
                            if(btn_do_drawing.running){
                                btn_do_drawing.running = false;
                                timer_check_drawing.stop();
                            }
                        }
                    }
                }

                Row{
                    Rectangle{
                        width: 200
                        color: color_dark_navy
                        height: annot_pages.height
                        Column{
                            anchors.centerIn: parent
                            spacing: 50
                            Item_buttonRectIcon{
                                visible: false
                                selected: select_mode===0
                                icon: "icon/icon_mapping_start.png"
                                name: qsTr("오브젝트")
                                onClicked: {
                                    select_mode = 0;
                                    map.setTool("move");
                                }
                            }
                            Item_buttonRectIcon{
                                visible: false
                                selected: select_mode===1
                                icon: "icon/icon_lidar.png"
                                name: qsTr("카메라 인식")
                                onClicked: {
                                    select_mode = 1;
                                    map.setTool("move");
                                }
                            }
                            Item_buttonRectIcon{
                                selected: select_mode===2
                                visible: !mode_drawing
                                icon: "icon/icon_edit.png"
                                name: qsTr("직접 그리기")
                                onClicked: {
                                    select_mode = 2;
                                    map.setTool("move");
                                }
                            }
                            Item_buttonRectIcon{
                                selected: select_mode===3
                                visible: mode_drawing
                                icon: "icon/icon_edit.png"
                                name: qsTr("직접 그리기")
                                onClicked: {
                                    select_mode = 3;
                                    map.setTool("move");
                                }
                            }
                        }
                    }

                    Column{
                        Rectangle{
                            width: annot_pages.width - 200
                            height: 100
                            color: "transparent"
                            Text{
                                text: qsTr("고정장애물 인식")
                                color: "white"
                                horizontalAlignment: Text.AlignHCenter
                                font.pixelSize: 40
                                anchors.horizontalCenter: parent.horizontalCenter
                                anchors.horizontalCenterOffset: -100
                                font.family: font_noto_b.name
                                anchors.centerIn: parent
                            }
                            Row{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.right: parent.right
                                anchors.rightMargin: 30
                                spacing: 20
                                Item_buttons{
                                    type: "circle_text"
                                    text: "?"
                                    width: 60
                                    height: 60
                                    onClicked:{
                                        click_sound.play();
                                        popup_annot_help.open();
                                        popup_annot_help.setTitle(qsTr("고정장애물 인식"));
                                        popup_annot_help.addLine(qsTr("로봇은 주행 중 장애물을 마주치면 감속하거나 멈춰 대기합니다"));
                                        popup_annot_help.addLine(qsTr("이동경로가 장애물에 너무 가깝게 지나가거나 장애물이 튀어"));
                                    }
                                }
                                Item_buttons{
                                    type: "round_text"
                                    width: 120
                                    height: 60
                                    text:qsTr("종료")
                                    onClicked:{
                                        click_sound.play();
                                        supervisor.writelog("[MAPPING] Object : Save and Exit");
                                        popup_save_object.open()
                                    }
                                }
                            }
                        }
                        Row{
                            Rectangle{
                                width: (annot_pages.width - map.width)/2 - 200
                                height: map.height
                                visible: select_mode===0
                                color: color_dark_navy
                            }
                            Rectangle{
                                visible: select_mode===1
                                width: annot_pages.width - map.width - 200
                                height: map.height
                                color: color_light_gray

                                Item_buttons{
                                    type: "start_progress"
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    anchors.verticalCenter: parent.verticalCenter
                                    anchors.verticalCenterOffset: -50
                                    width: 220
                                    height: 180
                                    running: is_object
                                    id: btn_do_drawing
                                    text: qsTr("인식 시작")
                                    onClicked:{
                                        map.setTool("move");
                                        if(running){
                                            click_sound.play();
                                            supervisor.writelog("[ANNOTATION] Object : Drawing Stop");
                                            supervisor.stopDrawObject();
                                        }else{
                                            click_sound.play();
                                            supervisor.writelog("[ANNOTATION] Object : Drawing Start");
                                            supervisor.startDrawObject();
                                            timer_check_drawing.start();
                                        }
                                    }
                                }
                                Item_buttons{
                                    type: "round_text"
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    anchors.bottom: parent.bottom
                                    anchors.bottomMargin : 50
                                    text : qsTr("저 장")
                                    width: 200
                                    height: 100
                                    onClicked:{
                                        click_sound.play();
                                        supervisor.writelog("[ANNOTATION] Object : Drawing Save");
                                        popup_save_object.open();
                                    }
                                }
                            }
                            Rectangle{
                                width: annot_pages.width - map.width - 200
                                height: map.height
                                visible: select_mode===2
                                color: color_light_gray
                                Column{
                                    anchors.top: parent.top
                                    anchors.topMargin: 60
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    spacing: 30
                                    Row{
                                        id: rect_annot_boxs
                                        anchors.horizontalCenter: parent.horizontalCenter
                                        spacing: 20
                                        Item_button{
                                            id: btn_move
                                            width: 80
                                            shadow_color: color_gray
                                            highlight: map.tool=="move"
                                            icon: "icon/icon_move.png"
                                            name: qsTr("이동")
                                            MouseArea{
                                                anchors.fill: parent
                                                onPressed: {
                                                    parent.pressed();
                                                }
                                                onReleased:{
                                                    parent.released();
                                                }
                                                onClicked: {
    //                                                supervisor.writelog("[ANNOTATION] Object : Set Tool to move");
                                                    map.setTool("move");
                                                    map.clear("all");
                                                }
                                            }
                                        }
                                        Item_button{
                                            id: btn_add
                                            width: 80
                                            shadow_color: color_gray
                                            highlight: map.tool=="add_object" || map.tool=="add_point"
                                            icon: "icon/icon_add.png"
                                            name: qsTr("추가")
                                            MouseArea{
                                                anchors.fill: parent
                                                onPressed: {
                                                    parent.pressed();
                                                }
                                                onReleased:{
                                                    parent.released();
                                                }
                                                onClicked: {
    //                                                supervisor.writelog("[ANNOTATION] Object : Set Tool to add Object");
                                                    map.setTool("add_object");
                                                    map.clear("all");
                                                }
                                            }
                                        }
                                        Item_button{
                                            id: btn_edit
                                             width: 80
                                             enabled: false
                                             btn_color: enabled?"white":color_gray
                                            shadow_color: color_gray
                                            highlight: map.tool=="edit_object"
                                            icon: "icon/icon_draw.png"
                                            name: qsTr("수정")
                                            MouseArea{
                                                anchors.fill: parent
                                                onPressed: {
                                                    parent.pressed();
                                                }
                                                onReleased:{
                                                    parent.released();
                                                }
                                                onClicked: {
                                                    map.clear("object");
    //                                                supervisor.writelog("[ANNOTATION] Object : Set Tool to add Object");
                                                    map.setTool("edit_object");
                                                }
                                            }
                                        }
                                        Item_button{
                                            id: btn_erase
                                            width: 80
                                            enabled: false
                                            shadow_color: color_gray
                                            btn_color: enabled?"white":color_gray
                                            icon: "icon/icon_remove.png"
                                            name: qsTr("삭제")
                                            overcolor: true
                                            MouseArea{
                                                anchors.fill: parent
                                                onPressed: {
                                                    parent.pressed();
                                                }
                                                onReleased:{
                                                    parent.released();
                                                }
                                                onClicked: {
                                                    supervisor.removeObject(select_object);
                                                    select_object = -1;
                                                    update_object();
                                                    supervisor.writelog("[ANNOTATION] Object : Remove "+Number(select_object));
                                                }
                                            }
                                        }
                                    }

                                    Column{
                                        spacing: 3
                                        Rectangle{
                                            id: rect_annot_tline_2
                                            width: rect_annot_boxs.width
                                            height: 60
                                            visible: map.tool === "add_object" || map.tool === "add_point"
                                            color: "white"
                                            Row{
                                                anchors.centerIn: parent
                                                spacing: 20
                                                Rectangle{
                                                    width: 100
                                                    height: 50
                                                    color: "transparent"
                                                    Row{
                                                        anchors.centerIn: parent
                                                        spacing: 10
                                                        Rectangle{
                                                            width: 50
                                                            height: width
                                                            radius: width
                                                            color: map.tool === "add_object"?color_green:color_gray
                                                            Image{
                                                                source: "icon/icon-drawing-square.png"
                                                                width: 30
                                                                height: 30
                                                                anchors.centerIn: parent
                                                            }
                                                        }
                                                        Text{
                                                            anchors.verticalCenter: parent.verticalCenter
                                                            font.family: font_noto_r.name
                                                            color: map.tool === "add_object"?"black":color_gray
                                                            text: qsTr("사각형")
                                                        }
                                                    }
                                                    MouseArea{
                                                        anchors.fill: parent
                                                        onClicked:{
    //                                                        supervisor.writelog("[ANNOTATION] ㅒㅠㅓ");
                                                            map.clear("object");
                                                            map.setTool("add_object");
                                                        }
                                                    }
                                                }
                                                Rectangle{
                                                    width: 100
                                                    height: 50
                                                    color: "transparent"
                                                    Row{
                                                        anchors.centerIn: parent
                                                        spacing: 10
                                                        Rectangle{
                                                            width: 50
                                                            height: width
                                                            radius: width
                                                            color: map.tool === "add_point"?color_green:color_gray
                                                            Image{
                                                                source: "icon/icon-drawing-polygon.png"
                                                                width: 30
                                                                height: 30
                                                                anchors.centerIn: parent
                                                            }
                                                        }
                                                        Text{
                                                            anchors.verticalCenter: parent.verticalCenter
                                                            font.family: font_noto_r.name
                                                            color: map.tool === "add_point"?"black":color_gray
                                                            text: qsTr("다각형")
                                                        }
                                                    }

                                                    MouseArea{
                                                        anchors.fill: parent
                                                        onClicked:{
    //                                                        supervisor.writelog("[ANNOTATION] Travel line : Set tool to straight");
                                                            map.clear("object");
                                                            map.setTool("add_point");
                                                        }
                                                    }
                                                }

                                            }
                                        }

                                        Rectangle{
                                            width: rect_annot_boxs.width
                                            height: 60
                                            visible: map.tool === "add_object" || map.tool === "add_point"
                                            color: "white"
                                            Row{
                                                id: row_redo
                                                spacing: 20
                                                anchors.centerIn: parent

                                                Rectangle{
                                                    width: 80
                                                    height: 40
                                                    radius: 5
                                                    color: "transparent"
                                                    border.width: 2
                                                    border.color: color_dark_navy
                                                    Text{
                                                        anchors.centerIn: parent
                                                        text: qsTr("저 장")
                                                        font.family: font_noto_r.name
                                                    }
                                                    MouseArea{
                                                        anchors.fill: parent
                                                        onClicked:{
                                                            map.setTool("move");
                                                            supervisor.saveObject();
                                                            update_object();
                                                        }
                                                    }
                                                }
                                                Rectangle{
                                                    width: 80
                                                    height: 40
                                                    radius: 5
                                                    color: "transparent"
                                                    border.width: 2
                                                    border.color: color_dark_navy
                                                    Text{
                                                        anchors.centerIn: parent
                                                        text: qsTr("취 소")
                                                        font.family: font_noto_r.name
                                                    }
                                                    MouseArea{
                                                        anchors.fill: parent
                                                        onClicked:{
                                                            supervisor.clearObjectAll();
                                                            map.setTool("move");
                                                        }
                                                    }
                                                }
                                                Item_buttons{
                                                    id: btn_undo
                                                    type: "circle_image"
                                                    enabled: false
                                                    source: "icon/icon_undo.png"
                                                    width: 40
                                                    height: 40
                                                    onClicked:{
                                                        click_sound.play();
                                                        supervisor.writelog("[ANNOTATION] Object : UNDO")
                                                        supervisor.undoObject();
                                                    }
                                                }
                                                Item_buttons{
                                                    id: btn_clear
                                                    type: "circle_image"
                                                    enabled: false
                                                    source: "icon/icon_trashcan.png"
                                                    width: 40
                                                    height: 40
                                                    onClicked:{
                                                        click_sound.play();
                                                        supervisor.writelog("[ANNOTATION] Object : Clear");
                                                        map.clear("all");
                                                    }
                                                }
                                            }
                                        }

                                    }
                                    Flickable{
                                        anchors.horizontalCenter: parent.horizontalCenter
                                        width: rect_annot_boxs.width
                                        height: 300
                                        clip: true
                                        contentHeight: col_objs.height
                                        Column{
                                            id: col_objs
                                            anchors.horizontalCenter: parent.horizontalCenter
                                            spacing: 10
                                            Repeater{
                                                model:ListModel{id:model_objs}
                                                Rectangle{
                                                    width: rect_annot_boxs.width
                                                    height: 40
                                                    color: select_object === index?color_green:"white"
                                                    Text{
                                                        anchors.centerIn: parent
                                                        text: index
                                                    }
                                                    MouseArea{
                                                        anchors.fill: parent
                                                        onClicked:{
                                                            if(select_object == index){
                                                                select_object = -1;
                                                            }else{
                                                                select_object = index;
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }

                                }

                                Item_buttons{
                                    type: "round_text"
                                    visible: select_mode===1 || (select_mode ===2 && map.tool ==="move")
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    anchors.bottom: parent.bottom
                                    anchors.bottomMargin : 50
                                    text : qsTr("저 장")
                                    width: 200
                                    height: 100
                                    onClicked:{
                                        click_sound.play();
                                        popup_save_object.open();
                                    }
                                }
                            }

//                            Rectangle{
//                                width: annot_pages.width - map.width - 200
//                                height: map.height
//                                visible: select_mode===3
//                                color: color_light_gray
//                                Column{
//                                    anchors.top: parent.top
//                                    anchors.topMargin: 60
//                                    anchors.horizontalCenter: parent.horizontalCenter
//                                    spacing: 10
//                                    Row{
//                                        id: rect_annot_boxs33
//                                        anchors.horizontalCenter: parent.horizontalCenter
//                                        spacing: 20
//                                        Item_button{
//                                            id: btn_move33
//    //                                            width: 80
//                                            shadow_color: color_gray
//                                            highlight: map.tool=="move"
//                                            icon: "icon/icon_move.png"
//                                            name: qsTr("이동")
//                                            MouseArea{
//                                                anchors.fill: parent
//                                                onPressed: {
//                                                    parent.pressed();
//                                                }
//                                                onReleased:{
//                                                    parent.released();
//                                                }

//                                                onClicked: {
//                                                    supervisor.writelog("[ANNOTATION] Travel Line : Set Tool to move");
//                                                    map.setTool("move");
//                                                }
//                                            }
//                                        }
//                                        Item_button{
//                                            id: btn_draw
//    //                                            width: 80
//                                            shadow_color: color_gray
//                                            highlight: map.tool=="draw" || map.tool=="erase" || map.tool=="draw_rect"
//                                            icon: "icon/icon_draw.png"
//                                            name: qsTr("수정")
//                                            MouseArea{
//                                                anchors.fill: parent
//                                                onPressed: {
//                                                    parent.pressed();
//                                                }
//                                                onReleased:{
//                                                    parent.released();
//                                                }
//                                                onClicked: {
//                                                    supervisor.writelog("[ANNOTATION] Object : Set Tool to draw");
//                                                    map.setTool("draw");
//                                                    map.setDrawingColor(255);
//                                                    map.setDrawingWidth(slider_brush.value);
//                                                }
//                                            }
//                                        }
//                                        Item_button{
//                                            id: btn_erase33
//    //                                            width: 80
//                                            shadow_color: color_gray
//                                            icon: "icon/icon_trashcan.png"
//                                            name: qsTr("초기화")
//                                            overcolor: true
//                                            MouseArea{
//                                                anchors.fill: parent
//                                                onPressed: {
//                                                    parent.pressed();
//                                                }
//                                                onReleased:{
//                                                    parent.released();
//                                                }
//                                                onClicked: {
//                                                    map.clear("spline");
//                                                    map.clear("object_png");
//                                                    map.clear("all");
//                                                    supervisor.writelog("[ANNOTATION] Object : Clear")
//                                                }
//                                            }
//                                        }
//                                    }

//                                    Column{
//                                        spacing: 3
//                                        Rectangle{
//                                            width: rect_annot_boxs.width
//                                            height: 60
//                                            visible: map.tool === "draw" || map.tool === "draw_rect" || map.tool === "erase"
//                                            color: "white"
//                                            Row{
//                                                id: row_redo33
//                                                spacing: 30
//                                                anchors.right: parent.right
//                                                anchors.verticalCenter: parent.verticalCenter
//                                                anchors.rightMargin: 30
//                                                Item_buttons{
//                                                    id: btn_undo33
//                                                    type: "circle_image"
//                                                    enabled: false
//                                                    source: "icon/icon_undo.png"
//                                                    width: 40
//                                                    height: 40
//                                                    onClicked:{
//                                                        click_sound.play();
//                                                        supervisor.writelog("[ANNOTATION] Object : UNDO")
//                                                        map.drawing_undo();
//                                                    }
//                                                }
//                                                Item_buttons{
//                                                    id: btn_redo
//                                                    type: "circle_image"
//                                                    enabled: false
//                                                    source: "icon/icon_redo.png"
//                                                    width: 40
//                                                    height: 40
//                                                    onClicked:{
//                                                        click_sound.play();
//                                                        supervisor.writelog("[ANNOTATION] Object : REDO")
//                                                        map.drawing_redo();
//                                                    }
//                                                }
//                                            }
//                                        }
//                                        Rectangle{
//                                            id: rect_annot_obj
//                                            width: rect_annot_boxs.width
//                                            height: 60
//                                            visible: map.tool === "draw" || map.tool === "draw_rect" || map.tool === "erase"
//                                            color: "white"
//                                            Row{
//                                                anchors.centerIn: parent
//                                                spacing: 20
//                                                Rectangle{
//                                                    width: 100
//                                                    height: 50
//                                                    color: "transparent"
//                                                    Row{
//                                                        anchors.centerIn: parent
//                                                        spacing: 10
//                                                        Rectangle{
//                                                            width: 50
//                                                            height: width
//                                                            radius: width
//                                                            color: map.tool === "draw"?color_green:color_gray
//                                                            Image{
//                                                                source: "icon/icon-drawing-free drawing.png"
//                                                                width: 30
//                                                                height: 30
//                                                                anchors.centerIn: parent
//                                                            }
//                                                        }
//                                                        Text{
//                                                            anchors.verticalCenter: parent.verticalCenter
//                                                            font.family: font_noto_r.name
//                                                            color: map.tool === "draw"?"black":color_gray
//                                                            text: qsTr("그리기")
//                                                        }
//                                                    }
//                                                    MouseArea{
//                                                        anchors.fill: parent
//                                                        onClicked:{
//                                                            supervisor.writelog("[ANNOTATION] Object : Set tool to draw");
//                                                            map.setTool("draw");
//                                                            map.setDrawingColor(255);
//                                                            map.setDrawingWidth(slider_brush.value);
//                                                        }
//                                                    }
//                                                }
//                                                Rectangle{
//                                                    width: 100
//                                                    height: 50
//                                                    color: "transparent"
//                                                    Row{
//                                                        anchors.centerIn: parent
//                                                        spacing: 10
//                                                        Rectangle{
//                                                            width: 50
//                                                            height: width
//                                                            radius: width
//                                                            color: map.tool==="draw_rect"? color_green: color_gray
//                                                            Image{
//                                                                source: "icon/icon-drawing-square.png"
//                                                                width: 30
//                                                                height: 30
//                                                                anchors.centerIn: parent
//                                                            }
//                                                        }
//                                                        Text{
//                                                            anchors.verticalCenter: parent.verticalCenter
//                                                            font.family: font_noto_r.name
//                                                            color: map.tool === "draw_rect"?"black":color_gray
//                                                            text: qsTr("사각형")
//                                                        }
//                                                    }

//                                                    MouseArea{
//                                                        anchors.fill: parent
//                                                        onClicked:{
//                                                            supervisor.writelog("[ANNOTATION] Object : Set tool to Rectangle")
//                                                            map.setTool("draw_rect");
//                                                            map.setDrawingColor(255);
//                                                            map.setDrawingWidth(slider_brush.value);
//                                                        }
//                                                    }
//                                                }
//                                                Rectangle{
//                                                    width: 100
//                                                    height: 50
//                                                    color: "transparent"
//                                                    Row{
//                                                        anchors.centerIn: parent
//                                                        spacing: 10
//                                                        Rectangle{
//                                                            width: 50
//                                                            height: width
//                                                            radius: width
//                                                            color: map.tool === "erase"?color_green:color_gray
//                                                            Image{
//                                                                source: "icon/icon_erase.png"
//                                                                width: 30
//                                                                height: 30
//                                                                anchors.centerIn: parent
//                                                                ColorOverlay{
//                                                                    source: parent
//                                                                    anchors.fill: parent
//                                                                    color: "white"
//                                                                }
//                                                            }
//                                                        }
//                                                        Text{
//                                                            anchors.verticalCenter: parent.verticalCenter
//                                                            font.family: font_noto_r.name
//                                                            color: map.tool === "erase"?"black":color_gray
//                                                            text: qsTr("지우개")
//                                                        }
//                                                    }

//                                                    MouseArea{
//                                                        anchors.fill: parent
//                                                        onClicked:{
//                                                            supervisor.writelog("[ANNOTATION] Object : Set tool to erase");
//                                                            map.setDrawingWidth(slider_erase.value);
//                                                            map.setTool("erase");
//                                                        }
//                                                    }
//                                                }
//                                            }
//                                        }

//                                        Rectangle{
//                                            id: rect_annot_box3
//                                            width: rect_annot_boxs.width
//                                            height: 60
//                                            color: "white"
//                                            visible: map.tool === "draw"
//                                            Text{
//                                                text: qsTr("브러시 사이즈")
//                                                font.family: font_noto_r.name
//                                                font.pixelSize: 15
//                                                anchors.verticalCenter: parent.verticalCenter
//                                                anchors.left: parent.left
//                                                anchors.leftMargin: 30
//                                            }
//                                            Slider {
//                                                id: slider_brush
//                                                x: 300
//                                                y: 330
//                                                value: 10
//                                                anchors.verticalCenter: parent.verticalCenter
//                                                anchors.right: parent.right
//                                                anchors.rightMargin: 30
//                                                width: 170
//                                                height: 18
//                                                from: 0
//                                                stepSize: 5
//                                                to : 50
//                                                onValueChanged: {
//                                                    map.setDrawingWidth(value)
//                                                }
//                                                onPressedChanged: {
//                                                    if(slider_brush.pressed){
//                                                        map.show_brush = true;
//                                                    }else{
//                                                        map.show_brush = false;
//                                                    }
//                                                }
//                                            }
//                                        }
//                                        Rectangle{
//                                            width: rect_annot_boxs.width
//                                            height: 60
//                                            color: "white"
//                                            visible: map.tool === "erase"
//                                            Text{
//                                                text: qsTr("브러시 사이즈")
//                                                font.family: font_noto_r.name
//                                                font.pixelSize: 15
//                                                anchors.verticalCenter: parent.verticalCenter
//                                                anchors.left: parent.left
//                                                anchors.leftMargin: 30
//                                            }
//                                            Slider {
//                                                id: slider_erase
//                                                x: 300
//                                                y: 330
//                                                value: 30
//                                                anchors.verticalCenter: parent.verticalCenter
//                                                anchors.right: parent.right
//                                                anchors.rightMargin: 30
//                                                width: 170
//                                                height: 18
//                                                from: 10
//                                                to : 100
//                                                onValueChanged: {
//                                                    map.setDrawingWidth(value);
//                                                }
//                                                onPressedChanged: {
//                                                    if(slider_erase.pressed){
//                                                        map.show_brush = true;
//                    //                                    map.brushchanged();
//                                                    }else{
//                                                        map.show_brush = false;
//                    //                                    map.brushdisappear();
//                                                    }
//                                                }
//                                            }
//                                        }

//                                    }

//                                }
//                                Item_buttons{
//                                    type: "round_text"
//                                    anchors.horizontalCenter: parent.horizontalCenter
//                                    anchors.bottom: parent.bottom
//                                    anchors.bottomMargin : 50
//                                    text : qsTr("저 장")
//                                    width: 200
//                                    height: 100
//                                    onClicked:{
//                                        click_sound.play();
//                                        popup_save_object.open();
//                                    }
//                                }
//                            }
                            MAP_FULL2{
                                id: map
                                objectName: "annot_object"
                                width: height
                                height: annot_pages.height - 100
                            }
                        }
                    }

                }
            }
    }


    Component{
        id: page_annot_map_editor
        Item{
            width: annot_pages.width
            height: annot_pages.height
            property var select_mode: 1
            property var select_preset: 0
            Rectangle{
                anchors.fill: parent
                color: color_dark_navy
            }
            Component.onCompleted: {
                loading.hide();
                select_preset = 0;
                supervisor.setMotorLock(true);
                map.setEnable(true);
                map.clear("all");
                map.setTool("move");
                map.setViewer("annot_drawing");
                if(supervisor.isExistTravelMap(supervisor.getMapname())){
                    supervisor.writelog("[ANNOTATION] Map Editor : load map")
                }
            }
            onSelect_modeChanged: {
                map.clear("all");
                if(select_mode === 0){
                    text_detail.text = qsTr("맵 세부수정");
                    map.setTool("move");
                }else if(select_mode === 1){
                    text_detail.text = qsTr("맵 세부수정");
                    map.setViewer("annot_drawing");
                    map.setTool("move");
                    map.setDrawingColor(127);
                }else if(select_mode === 2){
                    text_detail.text = qsTr("안전속도 구간 설정");
                    supervisor.readSetting(supervisor.getMapname());
                    map.setViewer("annot_velmap");
                    map.setTool("move");
                    map.setDrawingColor(127);
                    select_preset = 0;
                }else if(select_mode === 3){
                    text_detail.text = qsTr("가상벽 설정");
                    supervisor.readSetting(supervisor.getMapname());
                    map.setViewer("annot_object_png");
                    map.setTool("move");
                    select_preset = 0;
                }
            }

            Component.onDestruction: {
                map.setEnable(false);
            }

            Timer{
                running: true
                repeat: true
                interval: 500
                triggeredOnStart: true
                onTriggered: {
                    map.checkDrawing();
                    if(map.is_drawing_undo)
                        btn_undo.enabled = true;
                    else
                        btn_undo.enabled = false;

                    if(map.is_drawing_redo)
                        btn_redo.enabled = true;
                    else
                        btn_redo.enabled = false;
                }
            }

            Popup{
                id: popup_ask_mode_change
                anchors.centerIn: parent
                width: 450
                height: 280
                property var next_mode: 0
                background: Rectangle{
                    anchors.fill: parent
                    color: "transparent"
                }

                Rectangle{
                    width: parent.width
                    height: parent.height
                    radius: 25
                    color: color_dark_navy
                    Column{
                        spacing: 30
                        anchors.centerIn: parent
                        Column{
                            anchors.horizontalCenter: parent.horizontalCenter
                            Text{
                                anchors.horizontalCenter: parent.horizontalCenter
                                font.family: font_noto_r.name
                                text: "모드를 변경하시겠습니까?"
                                font.pixelSize: 20
                                color: "white"
                            }
                            Text{
                                anchors.horizontalCenter: parent.horizontalCenter
                                font.family: font_noto_r.name
                                text: "저장되지 않은 내용은 사라집니다"
                                font.pixelSize: 20
                                color: "white"
                            }
                        }
                        Row{
                            anchors.horizontalCenter: parent.horizontalCenter
                            spacing: 30
                            Item_buttons{
                                type: "round_text"
                                text: "변경"
                                width: 140
                                height: 60
                                fontsize: 20
                                onClicked:{
                                    select_mode = popup_ask_mode_change.next_mode;
                                    popup_ask_mode_change.close();
                                }
                            }
                            Item_buttons{
                                type: "round_text"
                                text: "취소"
                                width: 140
                                height: 60
                                fontsize: 20
                                onClicked: {
                                    popup_ask_mode_change.close();
                                }
                            }
                        }
                    }
                }
            }
            Timer{
                running: true
                repeat: true
                interval: 500
                triggeredOnStart: true
                onTriggered: {
                    map.checkDrawing();
                    if(map.is_drawing_undo)
                        btn_undo.enabled = true;
                    else
                        btn_undo.enabled = false;

                    if(map.is_drawing_redo)
                        btn_redo.enabled = true;
                    else
                        btn_redo.enabled = false;
                }
            }

            Row{
                Rectangle{
                    width: 200
                    color: color_dark_navy
                    height: annot_pages.height
                    Column{
                        anchors.centerIn: parent
                        spacing: 50
                        Item_buttonRectIcon{
                            selected: select_mode===1
                            icon: "icon/icon-drawing-free drawing.png"
                            name: qsTr("노이즈 제거")
                            onClicked: {
                                if(select_mode !== 1){
                                    popup_ask_mode_change.next_mode = 1;
                                    popup_ask_mode_change.open();
                                }
                            }
                        }
                        Item_buttonRectIcon{
                            selected: select_mode===2
                            icon: "icon/icon-drawing-free drawing.png"
                            name: qsTr("안전속도 구간")
                            onClicked: {
                                if(select_mode !== 2){
                                    popup_ask_mode_change.next_mode = 2;
                                    popup_ask_mode_change.open();
                                }
                            }
                        }
                        Item_buttonRectIcon{
                            selected: select_mode===3
                            icon: "icon/icon-drawing-free drawing.png"
                            name: qsTr("가상벽 그리기")
                            onClicked: {
                                if(select_mode !== 3){
                                    popup_ask_mode_change.next_mode = 3;
                                    popup_ask_mode_change.open();
                                }
                            }
                        }
                    }
                }

                Column{
                    Rectangle{
                        width: annot_pages.width - 200
                        height: 100
                        color: "transparent"
                        Text{
                            id: text_detail
                            text: qsTr("맵을 세부수정합니다")
                            color: "white"
                            horizontalAlignment: Text.AlignHCenter
                            font.pixelSize: 40
                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.horizontalCenterOffset: -100
                            font.family: font_noto_b.name
                            anchors.centerIn: parent
                        }
                        Row{
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.right: parent.right
                            anchors.rightMargin: 30
                            spacing: 20
                            Item_buttons{
                                type: "round_text"
                                width: 120
                                height: 60
                                text:qsTr("종료")
                                onClicked:{
                                    click_sound.play();
                                    supervisor.writelog("[MAPPING] Map Editor : Save and Exit");
                                    popup_save_map.open()
                                }
                            }
                        }
                    }
                    Row{
                        Rectangle{
                            width: (annot_pages.width - map.width)/2 - 200
                            height: map.height
                            visible: select_mode===0
                            color: color_dark_navy
                        }
                        Rectangle{
                            width: annot_pages.width - map.width - 200
                            height: map.height
                            color: color_light_gray
                            Column{
                                anchors.top: parent.top
                                anchors.topMargin: 60
                                anchors.horizontalCenter: parent.horizontalCenter
                                spacing: 10
                                Row{
                                    id: rect_annot_boxs
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    spacing: 20
                                    Item_button{
//                                            width: 80
                                        shadow_color: color_gray
                                        highlight: map.tool=="move"
                                        icon: "icon/icon_move.png"
                                        name: qsTr("이동")
                                        MouseArea{
                                            anchors.fill: parent
                                            onPressed: {
                                                parent.pressed();
                                            }
                                            onReleased:{
                                                parent.released();
                                            }

                                            onClicked: {
                                                supervisor.writelog("[ANNOTATION] Map Editor : Set Tool to move");
                                                map.setTool("move");
                                                map.clear("spline");
                                            }
                                        }
                                    }
                                    Item_button{
                                        id: btn_draw
//                                            width: 80
                                        shadow_color: color_gray
                                        highlight: map.tool=="draw" || map.tool=="erase" || map.tool=="straight"|| map.tool=="draw_rect"
                                        icon: "icon/icon_draw.png"
                                        name: qsTr("수정")
                                        MouseArea{
                                            anchors.fill: parent
                                            onPressed: {
                                                parent.pressed();
                                            }
                                            onReleased:{
                                                parent.released();
                                            }
                                            onClicked: {
                                                if(select_mode === 1){
                                                    supervisor.writelog("[ANNOTATION] Map Editor : Set Tool to move");
                                                    map.setTool("draw");
                                                    map.clear("spline");
                                                    map.setDrawingColor(127);
                                                    map.setDrawingWidth(slider_brush.value);
                                                    select_preset = 1;
                                                }else if(select_mode === 2){
                                                    supervisor.writelog("[USER INPUT] MAP PAGE (ANNOT) : VelMap -> BRUSH")
                                                    map.setTool("draw");
                                                    select_preset = 1;
                                                    map.setDrawingColor(100);
                                                    map.setDrawingWidth(slider_brush.value);
                                                }else if(select_mode === 3){
                                                    supervisor.writelog("[ANNOTATION] Object : Set Tool to draw");
                                                    map.setTool("draw");
                                                    map.setDrawingColor(255);
                                                    map.setDrawingWidth(slider_brush.value);
                                                }

                                            }
                                        }
                                    }
                                    Item_button{
                                        id: btn_erase
//                                            width: 80
                                        shadow_color: color_gray
                                        icon: "icon/icon_trashcan.png"
                                        name: qsTr("초기화")
                                        overcolor: true
                                        MouseArea{
                                            anchors.fill: parent
                                            onPressed: {
                                                parent.pressed();
                                            }
                                            onReleased:{
                                                parent.released();
                                            }
                                            onClicked: {
                                                map.clear("spline");
                                                map.clear("tline");
                                                map.clear("all");
                                                map.clear("object_png");
                                                supervisor.writelog("[ANNOTATION] Map Editor : Clear")
                                            }
                                        }
                                    }
                                }

                                Column{
                                    spacing: 3
                                    Rectangle{
                                        width: rect_annot_boxs.width
                                        height: 60
                                        visible: map.tool === "draw" || map.tool == "straight" ||  map.tool === "draw_rect" || map.tool === "erase"
                                        color: "white"
                                        Row{
                                            id: row_redo
                                            spacing: 30
                                            anchors.right: parent.right
                                            anchors.verticalCenter: parent.verticalCenter
                                            anchors.rightMargin: 30
                                            Item_buttons{
                                                id: btn_undo
                                                type: "circle_image"
                                                enabled: false
                                                source: "icon/icon_undo.png"
                                                width: 40
                                                height: 40
                                                onClicked:{
                                                    click_sound.play();
                                                    supervisor.writelog("[ANNOTATION] Map Editor : UNDO")
                                                    map.drawing_undo();
                                                }
                                            }
                                            Item_buttons{
                                                id: btn_redo
                                                type: "circle_image"
                                                enabled: false
                                                source: "icon/icon_redo.png"
                                                width: 40
                                                height: 40
                                                onClicked:{
                                                    click_sound.play();
                                                    supervisor.writelog("[ANNOTATION] Map Editor : REDO")
                                                    map.drawing_redo();
                                                }
                                            }
                                        }
                                    }
                                    Rectangle{
                                        id: rect_drawing_1
                                        width: rect_annot_boxs.width
                                        visible: select_mode === 0
                                        height: 60
                                        color: "white"
                                        Row{
                                            visible: false//map.tool === "draw" || map.tool === "erase"
                                            anchors.centerIn: parent
                                            spacing: 10
                                            Rectangle{
                                                width: 100
                                                height: 50
                                                color: "transparent"
                                                Row{
                                                    anchors.centerIn: parent
                                                    spacing: 10
                                                    Rectangle{
                                                        width: 50
                                                        height: width
                                                        radius: width
                                                        color: map.tool === "draw"?color_green:color_gray
                                                        Image{
                                                            source: "icon/icon-drawing-free drawing.png"
                                                            width: 30
                                                            height: 30
                                                            anchors.centerIn: parent
                                                        }
                                                    }
                                                    Text{
                                                        anchors.verticalCenter: parent.verticalCenter
                                                        font.family: font_noto_r.name
                                                        color: map.tool === "draw"?"black":color_gray
                                                        text: qsTr("그리기")
                                                    }
                                                }
                                                MouseArea{
                                                    anchors.fill: parent
                                                    onClicked:{
                                                        supervisor.writelog("[ANNOTATION] Map Editor : Set tool to draw");
                                                        map.clear("spline");
                                                        map.setTool("draw");
                                                        map.setDrawingColor(255);
                                                        map.setDrawingWidth(slider_brush.value);
                                                    }
                                                }
                                            }
                                            Rectangle{
                                                width: 100
                                                height: 50
                                                color: "transparent"
                                                Row{
                                                    anchors.centerIn: parent
                                                    spacing: 10

                                                    Rectangle{
                                                        width: 100
                                                        height: 50
                                                        color: "transparent"
                                                        Row{
                                                            anchors.centerIn: parent
                                                            spacing: 10
                                                            Rectangle{
                                                                width: 50
                                                                height: width
                                                                radius: width
                                                                color: map.tool === "erase"?color_green:color_gray
                                                                Image{
                                                                    source: "icon/icon_erase.png"
                                                                    width: 30
                                                                    height: 30
                                                                    anchors.centerIn: parent
                                                                    ColorOverlay{
                                                                        source: parent
                                                                        anchors.fill: parent
                                                                        color: "white"
                                                                    }
                                                                }
                                                            }
                                                            Text{
                                                                anchors.verticalCenter: parent.verticalCenter
                                                                font.family: font_noto_r.name
                                                                color: map.tool === "erase"?"black":color_gray
                                                                text: qsTr("지우개")
                                                            }
                                                        }

                                                        MouseArea{
                                                            anchors.fill: parent
                                                            onClicked:{
                                                                supervisor.writelog("[ANNOTATION] Map Editor : Set tool to erase");
                                                                map.clear("spline");
                                                                map.setDrawingWidth(slider_erase.value);
                                                                map.setTool("erase");
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                    Rectangle{
                                        id: rect_drawing
                                        width: rect_annot_boxs.width
                                        height: 60
                                        visible: select_mode === 1 && map.tool === "draw"
                                        color: "white"
                                        Row{
                                            anchors.centerIn: parent
                                            spacing: 10
                                            Rectangle{
                                                width: 100
                                                height: 50
                                                color: "transparent"
                                                Row{
                                                    anchors.centerIn: parent
                                                    spacing: 10
                                                    Rectangle{
                                                        width: 50
                                                        height: width
                                                        radius: width
                                                        border.width: map.cur_color === 255?3:1
                                                        border.color: map.cur_color === 255?color_green:color_gray
                                                        color: "white"
                                                    }
                                                    Text{
                                                        anchors.verticalCenter: parent.verticalCenter
                                                        font.family: font_noto_r.name
                                                        color: map.cur_color === 255?"black":color_gray
                                                        text: qsTr("장애물")
                                                    }
                                                }
                                                MouseArea{
                                                    anchors.fill: parent
                                                    onClicked:{
                                                        map.setDrawingColor(255);
                                                        map.setDrawingWidth(slider_brush.value);
                                                    }
                                                }
                                            }
                                            Rectangle{
                                                width: 100
                                                height: 50
                                                color: "transparent"
                                                Row{
                                                    anchors.centerIn: parent
                                                    spacing: 10
                                                    Rectangle{
                                                        width: 50
                                                        height: width
                                                        radius: width
                                                        border.width: map.cur_color === 127?3:0
                                                        border.color: color_green
                                                        color: color_gray
                                                    }
                                                    Text{
                                                        anchors.verticalCenter: parent.verticalCenter
                                                        font.family: font_noto_r.name
                                                        color: map.cur_color === 127?"black":color_gray
                                                        text: qsTr("바닥")
                                                    }
                                                }
                                                MouseArea{
                                                    anchors.fill: parent
                                                    onClicked:{
                                                        map.setDrawingColor(127);
                                                        map.setDrawingWidth(slider_brush.value);
                                                    }
                                                }
                                            }

                                            Rectangle{
                                                width: 100
                                                height: 50
                                                color: "transparent"
                                                Row{
                                                    anchors.centerIn: parent
                                                    spacing: 10
                                                    Rectangle{
                                                        width: 50
                                                        height: width
                                                        radius: width
                                                        border.width: map.cur_color === 0?3:0
                                                        border.color: color_green
                                                        color: "black"
                                                    }
                                                    Text{
                                                        anchors.verticalCenter: parent.verticalCenter
                                                        font.family: font_noto_r.name
                                                        color: map.cur_color === 0?"black":color_gray
                                                        text: qsTr("외부")
                                                    }
                                                }
                                                MouseArea{
                                                    anchors.fill: parent
                                                    onClicked:{
                                                        map.setDrawingColor(0);
                                                        map.setDrawingWidth(slider_brush.value);
                                                    }
                                                }
                                            }
                                        }
                                    }
                                    Rectangle{
                                        width: rect_annot_boxs.width
                                        height: 60
                                        visible: select_mode === 2 && (map.tool === "draw" || map.tool == "straight" || map.tool === "draw_rect" || map.tool === "erase")
                                        color: "white"
                                        Row{
                                            anchors.centerIn: parent
                                            spacing: 10

                                            Rectangle{
                                                width: 100
                                                height: 50
                                                color: "transparent"
                                                Row{
                                                    anchors.centerIn: parent
                                                    spacing: 10
                                                    Rectangle{
                                                        width: 50
                                                        height: width
                                                        radius: width
                                                        color: map.tool === "draw"?color_green:color_gray
                                                        Image{
                                                            source: "icon/icon-drawing-free drawing.png"
                                                            width: 30
                                                            height: 30
                                                            anchors.centerIn: parent
                                                        }
                                                    }
                                                    Text{
                                                        anchors.verticalCenter: parent.verticalCenter
                                                        font.family: font_noto_r.name
                                                        color: map.tool === "draw"?"black":color_gray
                                                        text: qsTr("그리기")
                                                    }
                                                }

                                                MouseArea{
                                                    anchors.fill: parent
                                                    onClicked:{
                                                        map.setTool("draw");
                                                    }
                                                }
                                            }

                                            Rectangle{
                                                width: 100
                                                height: 50
                                                color: "transparent"
                                                Row{
                                                    anchors.centerIn: parent
                                                    spacing: 10
                                                    Rectangle{
                                                        width: 50
                                                        height: width
                                                        radius: width
                                                        color: map.tool==="draw_rect"? color_green: color_gray
                                                        Image{
                                                            source: "icon/icon-drawing-square.png"
                                                            width: 30
                                                            height: 30
                                                            anchors.centerIn: parent
                                                        }
                                                    }
                                                    Text{
                                                        anchors.verticalCenter: parent.verticalCenter
                                                        font.family: font_noto_r.name
                                                        color: map.tool === "draw_rect"?"black":color_gray
                                                        text: qsTr("사각형")
                                                    }
                                                }

                                                MouseArea{
                                                    anchors.fill: parent
                                                    onClicked:{
                                                        map.setTool("draw_rect");
                                                    }
                                                }
                                            }
                                            Rectangle{
                                                width: 100
                                                height: 50
                                                color: "transparent"
                                                Row{
                                                    anchors.centerIn: parent
                                                    spacing: 10
                                                    Rectangle{
                                                        width: 50
                                                        height: width
                                                        radius: width
                                                        color: map.tool === "erase"?color_green:color_gray
                                                        Image{
                                                            source: "icon/icon_erase.png"
                                                            width: 30
                                                            height: 30
                                                            anchors.centerIn: parent
                                                            ColorOverlay{
                                                                source: parent
                                                                anchors.fill: parent
                                                                color: "white"
                                                            }
                                                        }
                                                    }
                                                    Text{
                                                        anchors.verticalCenter: parent.verticalCenter
                                                        font.family: font_noto_r.name
                                                        color: map.tool === "erase"?"black":color_gray
                                                        text: qsTr("지우개")
                                                    }
                                                }

                                                MouseArea{
                                                    anchors.fill: parent
                                                    onClicked:{
                                                        map.setTool("erase");
                                                    }
                                                }
                                            }

                                        }
                                    }
                                    Rectangle{
                                        width: rect_annot_boxs.width
                                        height: 60
                                        visible: select_mode === 2 && (map.tool === "draw" || map.tool === "draw_rect")
                                        color: "white"
                                        Row{
                                            anchors.centerIn: parent
                                            spacing: 20
                                            Rectangle{
                                                width: 130
                                                height: 50
                                                color: "transparent"
                                                Row{
                                                    anchors.centerIn: parent
                                                    spacing: 10
                                                    Rectangle{
                                                        width: 50
                                                        height: width
                                                        radius: width
                                                        color: select_preset===1?color_yellow_rect:color_gray
                                                        Image{
                                                            source: "icon/icon_connect_error.png"
                                                            width: 28
                                                            height: 25
                                                            anchors.centerIn: parent
                                                            ColorOverlay{
                                                                source: parent
                                                                anchors.fill: parent
                                                                color: "white"
                                                            }
                                                        }
                                                    }
                                                    Text{
                                                        anchors.verticalCenter: parent.verticalCenter
                                                        font.family: font_noto_r.name
                                                        color: select_preset===1?"black":color_gray
                                                        text: qsTr("느리게")
                                                    }
                                                }

                                                MouseArea{
                                                    anchors.fill: parent
                                                    onClicked:{
                                                        select_preset = 1;
                                                        map.setDrawingColor(100);
                                                        map.setDrawingWidth(slider_brush.value);
                                                    }
                                                }
                                            }
                                            Rectangle{
                                                width: 130
                                                height: 50
                                                color: "transparent"
                                                Row{
                                                    anchors.centerIn: parent
                                                    spacing: 10
                                                    Rectangle{
                                                        width: 50
                                                        height: width
                                                        radius: width
                                                        color: select_preset===2?color_red:color_gray
                                                        Image{
                                                            source: "icon/icon_error.png"
                                                            width: 30
                                                            height: 30
                                                            anchors.centerIn: parent
                                                            ColorOverlay{
                                                                source: parent
                                                                anchors.fill: parent
                                                                color: "white"
                                                            }
                                                        }
                                                    }
                                                    Text{
                                                        anchors.verticalCenter: parent.verticalCenter
                                                        font.family: font_noto_r.name
                                                        color: select_preset===2?"black":color_gray
                                                        text: qsTr("매우 느리게")
                                                    }
                                                }

                                                MouseArea{
                                                    anchors.fill: parent
                                                    onClicked:{
                                                        select_preset = 2;
                                                        map.setDrawingColor(200);
                                                        map.setDrawingWidth(slider_brush.value);
                                                    }
                                                }
                                            }
                                        }
                                    }

                                    Rectangle{
                                        id: rect_annot_tline_1
                                        width: rect_annot_boxs.width
                                        height: 60
                                        visible: map.tool === "dot_spline"
                                        color: "white"
                                        Row{
                                            anchors.centerIn: parent
                                            spacing: 10
                                            Item_buttons{
                                                type: "round_text"
                                                width: 120
                                                height: 40
                                                text: qsTr("취소")
                                                fontsize: 20
                                                onClicked:{
                                                    click_sound.play();
                                                    supervisor.writelog("[ANNOTATION] Map Editor : Cancel dot spline");
                                                    map.clear("spline");
                                                    map.setTool("draw");
                                                }
                                            }
                                            Item_buttons{
                                                type: "round_text"
                                                width: 120
                                                height: 40
                                                fontsize: 20
                                                text: qsTr("저장")
                                                onClicked:{
                                                    click_sound.play();
                                                    supervisor.writelog("[ANNOTATION] Map Editor : Save dot spline");
                                                    map.save("spline");
                                                    map.setTool("draw");
                                                }
                                            }
                                        }
                                    }
                                    Rectangle{
                                        id: rect_annot_box3
                                        width: rect_annot_boxs.width
                                        height: 60
                                        color: "white"
                                        visible: map.tool === "draw" || map.tool === "straight" || map.tool === "dot_spline"
                                        Text{
                                            text: qsTr("브러시 사이즈")
                                            font.family: font_noto_r.name
                                            font.pixelSize: 15
                                            anchors.verticalCenter: parent.verticalCenter
                                            anchors.left: parent.left
                                            anchors.leftMargin: 30
                                        }
                                        Slider {
                                            id: slider_brush
                                            x: 300
                                            y: 330
                                            value: 5
                                            anchors.verticalCenter: parent.verticalCenter
                                            anchors.right: parent.right
                                            anchors.rightMargin: 30
                                            width: 170
                                            height: 18
                                            from: 1
                                            stepSize: 1
                                            to : 30
                                            onValueChanged: {
                                                map.setDrawingWidth(value)
                                            }
                                            onPressedChanged: {
                                                if(slider_brush.pressed){
                                                    map.show_brush = true;
                                                }else{
                                                    map.show_brush = false;
                                                }
                                            }
                                        }
                                    }
                                    Rectangle{
                                        width: rect_annot_boxs.width
                                        height: 60
                                        color: "white"
                                        visible: map.tool === "erase"
                                        Text{
                                            text: qsTr("브러시 사이즈")
                                            font.family: font_noto_r.name
                                            font.pixelSize: 15
                                            anchors.verticalCenter: parent.verticalCenter
                                            anchors.left: parent.left
                                            anchors.leftMargin: 30
                                        }
                                        Slider {
                                            id: slider_erase
                                            x: 300
                                            y: 330
                                            value: 30
                                            anchors.verticalCenter: parent.verticalCenter
                                            anchors.right: parent.right
                                            anchors.rightMargin: 30
                                            width: 170
                                            height: 18
                                            from: 10
                                            to : 100
                                            onValueChanged: {
                                                map.setDrawingWidth(value);
                                            }
                                            onPressedChanged: {
                                                if(slider_erase.pressed){
                                                    map.show_brush = true;
                //                                    map.brushchanged();
                                                }else{
                                                    map.show_brush = false;
                //                                    map.brushdisappear();
                                                }
                                            }
                                        }
                                    }
                                    Rectangle{
                                        id: rect_annot_obj
                                        width: rect_annot_boxs.width
                                        height: 60
                                        visible: select_mode===3 && (map.tool === "draw" || map.tool === "straight" || map.tool === "erase")
                                        color: "white"
                                        Row{
                                            anchors.centerIn: parent
                                            spacing: 10
                                            Rectangle{
                                                width: 100
                                                height: 50
                                                color: "transparent"
                                                Row{
                                                    anchors.centerIn: parent
                                                    spacing: 10
                                                    Rectangle{
                                                        width: 50
                                                        height: width
                                                        radius: width
                                                        color: map.tool === "draw"?color_green:color_gray
                                                        Image{
                                                            source: "icon/icon-drawing-free drawing.png"
                                                            width: 30
                                                            height: 30
                                                            anchors.centerIn: parent
                                                        }
                                                    }
                                                    Text{
                                                        anchors.verticalCenter: parent.verticalCenter
                                                        font.family: font_noto_r.name
                                                        color: map.tool === "draw"?"black":color_gray
                                                        text: qsTr("그리기")
                                                    }
                                                }
                                                MouseArea{
                                                    anchors.fill: parent
                                                    onClicked:{
                                                        supervisor.writelog("[ANNOTATION] Object : Set tool to draw");
                                                        map.setTool("draw");
                                                        map.setDrawingColor(255);
                                                        map.setDrawingWidth(slider_brush.value);
                                                    }
                                                }
                                            }
                                            Rectangle{
                                                width: 100
                                                height: 50
                                                color: "transparent"
                                                Row{
                                                    anchors.centerIn: parent
                                                    spacing: 10
                                                    Rectangle{
                                                        width: 50
                                                        height: width
                                                        radius: width
                                                        color: map.tool==="straight"? color_green: color_gray
                                                        Image{
                                                            source: "icon/icon_draw.png"
                                                            width: 30
                                                            height: 30
                                                            anchors.centerIn: parent
                                                            ColorOverlay{
                                                                source: parent
                                                                anchors.fill: parent
                                                                color: "white"
                                                            }
                                                        }
                                                    }
                                                    Text{
                                                        anchors.verticalCenter: parent.verticalCenter
                                                        font.family: font_noto_r.name
                                                        color: map.tool === "straight"?"black":color_gray
                                                        text: qsTr("직선")
                                                    }
                                                }

                                                MouseArea{
                                                    anchors.fill: parent
                                                    onClicked:{
                                                        supervisor.writelog("[ANNOTATION] Object : Set tool to straight")
                                                        map.setTool("straight");
                                                        map.setDrawingColor(255);
                                                        map.setDrawingWidth(slider_brush.value);
                                                    }
                                                }
                                            }
                                            Rectangle{
                                                width: 100
                                                height: 50
                                                color: "transparent"
                                                Row{
                                                    anchors.centerIn: parent
                                                    spacing: 10
                                                    Rectangle{
                                                        width: 50
                                                        height: width
                                                        radius: width
                                                        color: map.tool === "erase"?color_green:color_gray
                                                        Image{
                                                            source: "icon/icon_erase.png"
                                                            width: 30
                                                            height: 30
                                                            anchors.centerIn: parent
                                                            ColorOverlay{
                                                                source: parent
                                                                anchors.fill: parent
                                                                color: "white"
                                                            }
                                                        }
                                                    }
                                                    Text{
                                                        anchors.verticalCenter: parent.verticalCenter
                                                        font.family: font_noto_r.name
                                                        color: map.tool === "erase"?"black":color_gray
                                                        text: qsTr("지우개")
                                                    }
                                                }

                                                MouseArea{
                                                    anchors.fill: parent
                                                    onClicked:{
                                                        supervisor.writelog("[ANNOTATION] Object : Set tool to erase");
                                                        map.setDrawingWidth(slider_erase.value);
                                                        map.setTool("erase");
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }

                            Item_buttons{
                                type: "round_text"
                                anchors.horizontalCenter: parent.horizontalCenter
                                anchors.bottom: parent.bottom
                                anchors.bottomMargin : 50
                                text : qsTr("저 장")
                                width: 200
                                height: 100
                                onClicked:{
                                    click_sound.play();
                                    popup_save_map.open();
                                }
                            }
                        }
                        MAP_FULL2{
                            id: map
                            objectName: "annot_mapeditor"
                            width: height
                            height: annot_pages.height - 100
                        }

                    }
                }

            }


            Popup{
                id: popup_save_map
                width: parent.width
                height: parent.height
                background:Rectangle{
                    anchors.fill: parent
                    color: "#282828"
                    opacity: 0.7
                }
                Rectangle{
                    anchors.centerIn: parent
                    width: 450
                    height: 230
                    color: "white"
                    radius: 20

                    Column{
                        anchors.centerIn: parent
                        spacing: 20
                        Column{
                            anchors.horizontalCenter: parent.horizontalCenter
                            Text{
                                text: qsTr("이대로 <font color=\"#12d27c\">저장</font>하시겠습니까?")
                                font.family: font_noto_r.name
                                font.pixelSize: 30
                                anchors.horizontalCenter: parent.horizontalCenter
                            }
                            Text{
                                text: qsTr("기존의 파일은 삭제됩니다")
                                font.family: font_noto_r.name
                                font.pixelSize: 20
                                anchors.horizontalCenter: parent.horizontalCenter
                            }
                        }
                        Row{
                            anchors.horizontalCenter: parent.horizontalCenter
                            spacing: 20
                            Item_buttons{
                                type: "round_text"
                                text: qsTr("저장 안하고 종료")
                                width: 180
                                height: 60
                                onClicked:{
                                    click_sound.play();
                                    map.clear("all");
                                    popup_save_map.close();
                                    annot_pages.sourceComponent = page_annot_additional_menu;
                                }
                            }
                            Item_buttons{
                                type: "round_text"
                                text: qsTr("확인")
                                width: 180
                                height: 60
                                onClicked:{
                                    //save temp Image
                                    if(select_mode === 1){
                                        supervisor.writelog("[QML] MAP PAGE : SAVE MAP EDITOR ");
                                        map.save("map_editor");
                                    }else if(select_mode === 2){
                                        supervisor.writelog("[QML] MAP PAGE : SAVE VELOCITY MAP ");
                                        map.save("velmap");
                                    }else if(select_mode === 3){
                                        supervisor.writelog("[QML] MAP PAGE : SAVE Object ");
                                        print(supervisor.getObjectflag())
                                        supervisor.saveDrawObject();
                                        supervisor.setMode("annot_object_png");
                                        supervisor.saveObjectPNG();


//                                        update_object();
                                    }
                                    click_sound.play();
                                    popup_save_map.close();
                                    annot_pages.sourceComponent = page_annot_additional_menu;
                                }
                            }
                        }
                    }

                }

            }


        }
    }
    Component{
        id: page_annot_travelline
        Item{
            width: annot_pages.width
            height: annot_pages.height
            property var select_mode: 0
            property bool is_drawing: false
            property var select_tline_issue: -1
            Rectangle{
                anchors.fill: parent
                color: color_dark_navy
            }
            Component.onCompleted: {
                loading.hide();
                select_preset = 0;
                supervisor.setMotorLock(true);
                map.setEnable(true);
                supervisor.checkTravelline();
                map.init();
                if(supervisor.isExistTravelMap(supervisor.getMapname())){
//                    supervisor.loadfile
                    supervisor.writelog("[ANNOTATION] Travel Line : load map")
                }
            }
            Component.onDestruction: {
                map.setEnable(false);
                if(map.getTFlag()){
                    supervisor.setMotorLock(true);
                    map.stopDrawingT();
                }
            }

            Timer{
                interval: 500
                running: true
                onTriggered:{
                    map.setViewer("annot_tline");
                }
            }
            Timer{
                running: true
                repeat: true
                interval: 500
                triggeredOnStart: true
                onTriggered: {
                    map.checkDrawing();
                    if(map.is_drawing_undo)
                        btn_undo.enabled = true;
                    else
                        btn_undo.enabled = false;

                    if(map.is_drawing_redo)
                        btn_redo.enabled = true;
                    else
                        btn_redo.enabled = false;
                }
            }
            Timer{
                id: timer_check_drawing
                interval: 500
                repeat: true
                onTriggered:{
                    if(map.getTFlag()){
                        btn_do_drawing.running = true;
                    }else{
                        if(btn_do_drawing.running){
                            btn_do_drawing.running = false;
                            timer_check_drawing.stop();
                        }
                    }
                }
            }

            Row{
                Rectangle{
                    width: 200
                    color: color_dark_navy
                    height: annot_pages.height
                    Column{
                        anchors.centerIn: parent
                        spacing: 50
                        Item_buttonRectIcon{
                            selected: select_mode===0
                            icon: "icon/icon_mapping_start.png"
                            name: qsTr("경로 보기")
                            onClicked: {
                                select_mode = 0;
                                map.setTool("move");
                            }
                        }
                        Item_buttonRectIcon{
                            selected: select_mode===1
                            icon: "icon/icon_local_error.png"
                            name: qsTr("경로 학습")
                            onClicked: {
                                select_mode = 1;
                                map.setTool("move");
                            }
                        }
                        Item_buttonRectIcon{
                            selected: select_mode===2
                            icon: "icon/icon-drawing-free drawing.png"
                            name: qsTr("경로 수정")
                            onClicked: {
                                select_mode = 2;
                                map.setTool("move");
                            }
                        }
                        Item_buttonRectIcon{
                            selected: select_mode===3
                            icon: "image/image_slam.png"
                            name: qsTr("경로 검사")
                            onClicked: {
                                select_mode = 3;
                                map.setTool("move");
                                supervisor.checkTravelline();
                            }
                        }
                    }
                }

                Column{
                    Rectangle{
                        width: annot_pages.width - 200
                        height: 100
                        color: "transparent"
                        Text{
                            text: qsTr("이동경로를 수정합니다")
                            color: "white"
                            horizontalAlignment: Text.AlignHCenter
                            font.pixelSize: 40
                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.horizontalCenterOffset: -100
                            font.family: font_noto_b.name
                            anchors.centerIn: parent
                        }
                        Row{
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.right: parent.right
                            anchors.rightMargin: 30
                            spacing: 20
                            Item_buttons{
                                type: "circle_text"
                                text: "?"
                                width: 60
                                height: 60
                                onClicked:{
                                    click_sound.play();
                                    popup_annot_help.open();
                                    popup_annot_help.setTitle(qsTr("이동 경로"));
                                    popup_annot_help.addLine(qsTr("이동경로는 로봇이 목적지로 이동할 때 사용하는 경로의 집합입니다\n보다 많은 경로를 학습시킬 수록 최적의 경로를 찾을 수 있습니다"));
                                    popup_annot_help.addLine(qsTr("로봇을 끌고 학습시킬 때 최대한 직진성을 유지해주세요\n경로가 구불구불해도 최대한 부드럽게 이동하려고 하겠지만 보기에 다소 어색할 수 있습니다"));
                                    popup_annot_help.addLine(qsTr("대기, 충전 위치와 각 서빙위치 사이를 여러번 왕복시켜주세요"));
                                }
                            }
                            Item_buttons{
                                type: "round_text"
                                width: 120
                                height: 60
                                text:qsTr("종료")
                                onClicked:{
                                    click_sound.play();
                                    supervisor.writelog("[MAPPING] Travel line : Save and Exit");
                                    popup_save_travelline.open()
                                }
                            }
                        }
                    }
                    Row{
                        Rectangle{
                            width: (annot_pages.width - map.width)/2 - 200
                            height: map.height
                            visible: select_mode===0
                            color: color_dark_navy
                        }
                        Rectangle{
                            visible: select_mode===1
                            width: annot_pages.width - map.width - 200
                            height: map.height
                            color: color_light_gray

                            Item_buttons{
                                type: "start_progress"
                                anchors.horizontalCenter: parent.horizontalCenter
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.verticalCenterOffset: -50
                                width: 220
                                height: 180
                                id: btn_do_drawing
                                text: qsTr("경로 학습 시작")
                                onClicked:{
                                    map.setTool("move");
                                    if(running){
                                        click_sound.play();
                                        supervisor.writelog("[ANNOTATION] Travel Line : Drawing Stop");
                                        map.stopDrawingT();
                                        supervisor.setMotorLock(true);
                                    }else{
                                        click_sound.play();
                                        supervisor.writelog("[ANNOTATION] Travel Line : Drawing Start");
                                        map.startDrawingT();
                                        supervisor.setMotorLock(false);
                                        timer_check_drawing.start();
                                    }
                                }
                            }
                            Item_buttons{
                                type: "round_text"
                                anchors.horizontalCenter: parent.horizontalCenter
                                anchors.bottom: parent.bottom
                                anchors.bottomMargin : 50
                                text : qsTr("저 장")
                                width: 200
                                height: 100
                                onClicked:{
                                    click_sound.play();
                                    supervisor.writelog("[ANNOTATION] Travel Line : Drawing Stop");
                                    map.stopDrawingT();
                                    supervisor.setMotorLock(true);
                                    popup_save_travelline.save_mode = "tline";
                                    popup_save_travelline.open();
                                }
                            }
                        }
                        Rectangle{
                            width: annot_pages.width - map.width - 200
                            height: map.height
                            visible: select_mode===2
                            color: color_light_gray
                            Column{
                                anchors.top: parent.top
                                anchors.topMargin: 60
                                anchors.horizontalCenter: parent.horizontalCenter
                                spacing: 10
                                Row{
                                    id: rect_annot_boxs
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    spacing: 20
                                    Item_button{
                                        id: btn_move
//                                            width: 80
                                        shadow_color: color_gray
                                        highlight: map.tool=="move"
                                        icon: "icon/icon_move.png"
                                        name: qsTr("이동")
                                        MouseArea{
                                            anchors.fill: parent
                                            onPressed: {
                                                parent.pressed();
                                            }
                                            onReleased:{
                                                parent.released();
                                            }

                                            onClicked: {
                                                supervisor.writelog("[ANNOTATION] Travel Line : Set Tool to move");
                                                map.setTool("move");
                                                map.clear("spline");
                                            }
                                        }
                                    }
                                    Item_button{
                                        id: btn_draw
//                                            width: 80
                                        shadow_color: color_gray
                                        highlight: map.tool=="draw" || map.tool=="erase" || map.tool=="straight"
                                        icon: "icon/icon_draw.png"
                                        name: qsTr("수정")
                                        MouseArea{
                                            anchors.fill: parent
                                            onPressed: {
                                                parent.pressed();
                                            }
                                            onReleased:{
                                                parent.released();
                                            }
                                            onClicked: {
                                                supervisor.writelog("[ANNOTATION] Travel Line : Set Tool to move");
                                                map.setTool("draw");
                                                map.clear("spline");
                                                map.setDrawingColor(255);
                                                map.setDrawingWidth(slider_brush.value);
                                                select_preset = 1;
                                            }
                                        }
                                    }
                                    Item_button{
                                        id: btn_erase
//                                            width: 80
                                        shadow_color: color_gray
                                        icon: "icon/icon_trashcan.png"
                                        name: qsTr("초기화")
                                        overcolor: true
                                        MouseArea{
                                            anchors.fill: parent
                                            onPressed: {
                                                parent.pressed();
                                            }
                                            onReleased:{
                                                parent.released();
                                            }
                                            onClicked: {
                                                map.clear("spline");
                                                map.clear("tline");
                                                map.clear("all");
                                                supervisor.writelog("[ANNOTATION] Travel line : Clear")
                                            }
                                        }
                                    }
                                }

                                Column{
                                    spacing: 3
                                    Rectangle{
                                        width: rect_annot_boxs.width
                                        height: 60
                                        visible: map.tool === "draw" || map.tool === "straight" || map.tool === "dot_spline" || map.tool === "erase"
                                        color: "white"
                                        Row{
                                            id: row_redo
                                            spacing: 30
                                            anchors.right: parent.right
                                            anchors.verticalCenter: parent.verticalCenter
                                            anchors.rightMargin: 30
                                            Item_buttons{
                                                id: btn_undo
                                                type: "circle_image"
                                                enabled: false
                                                source: "icon/icon_undo.png"
                                                width: 40
                                                height: 40
                                                onClicked:{
                                                    click_sound.play();
                                                    supervisor.writelog("[ANNOTATION] Travel Line : UNDO")
                                                    map.drawing_undo();
                                                }
                                            }
                                            Item_buttons{
                                                id: btn_redo
                                                type: "circle_image"
                                                enabled: false
                                                source: "icon/icon_redo.png"
                                                width: 40
                                                height: 40
                                                onClicked:{
                                                    click_sound.play();
                                                    supervisor.writelog("[ANNOTATION] Travel Line : REDO")
                                                    map.drawing_redo();
                                                }
                                            }
                                        }
                                    }
                                    Rectangle{
                                        id: rect_annot_tline_2
                                        width: rect_annot_boxs.width
                                        height: 60
                                        visible: map.tool === "draw" || map.tool === "straight" || map.tool === "dot_spline" || map.tool === "erase"
                                        color: "white"
                                        Row{
                                            anchors.centerIn: parent
                                            spacing: 20
                                            Rectangle{
                                                width: 100
                                                height: 50
                                                color: "transparent"
                                                Row{
                                                    anchors.centerIn: parent
                                                    spacing: 10
                                                    Rectangle{
                                                        width: 50
                                                        height: width
                                                        radius: width
                                                        color: map.tool === "draw"?color_green:color_gray
                                                        Image{
                                                            source: "icon/icon-drawing-free drawing.png"
                                                            width: 30
                                                            height: 30
                                                            anchors.centerIn: parent
                                                        }
                                                    }
                                                    Text{
                                                        anchors.verticalCenter: parent.verticalCenter
                                                        font.family: font_noto_r.name
                                                        color: map.tool === "draw"?"black":color_gray
                                                        text: qsTr("그리기")
                                                    }
                                                }
                                                MouseArea{
                                                    anchors.fill: parent
                                                    onClicked:{
                                                        supervisor.writelog("[ANNOTATION] Travel line : Set tool to draw");
                                                        map.clear("spline");
                                                        map.setTool("draw");
                                                        map.setDrawingColor(255);
                                                        map.setDrawingWidth(slider_brush.value);
                                                    }
                                                }
                                            }
                                            Rectangle{
                                                width: 100
                                                height: 50
                                                color: "transparent"
                                                Row{
                                                    anchors.centerIn: parent
                                                    spacing: 10
                                                    Rectangle{
                                                        width: 50
                                                        height: width
                                                        radius: width
                                                        color: map.tool==="straight"? color_green: color_gray
                                                        Shape{
                                                            width: 30
                                                            height: 30
                                                            anchors.centerIn: parent
                                                            ShapePath{
                                                                strokeColor: "white"
                                                                fillColor: "white"
                                                                capStyle: Qt.RoundCap
                                                                strokeWidth:4
                                                                startX: 30
                                                                startY:0
                                                                PathLine{
                                                                    x: 0
                                                                    y: 30
                                                                }
                                                            }
                                                        }
                                                    }
                                                    Text{
                                                        anchors.verticalCenter: parent.verticalCenter
                                                        font.family: font_noto_r.name
                                                        color: map.tool === "straight"?"black":color_gray
                                                        text: qsTr("직선")
                                                    }
                                                }

                                                MouseArea{
                                                    anchors.fill: parent
                                                    onClicked:{
                                                        supervisor.writelog("[ANNOTATION] Travel line : Set tool to straight");
                                                        map.clear("spline");
                                                        map.setTool("straight");
                                                        map.setDrawingColor(255);
                                                        map.setDrawingWidth(slider_brush.value);
                                                    }
                                                }
                                            }

                                        }
                                    }

                                    Rectangle{
                                        width: rect_annot_boxs.width
                                        height: 60
                                        visible: map.tool === "draw" || map.tool === "straight" || map.tool === "dot_spline" || map.tool === "erase"
                                        color: "white"
                                        Row{
                                            anchors.centerIn: parent
                                            spacing: 20
                                            Rectangle{
                                                width: 100
                                                height: 50
                                                color: "transparent"
                                                Row{
                                                    anchors.centerIn: parent
                                                    spacing: 10
                                                    Rectangle{
                                                        width: 50
                                                        height: width
                                                        radius: width
                                                        color: map.tool === "dot_spline"?color_green:color_gray
                                                        Image{
                                                            source: "icon/icon-drawing-curve.png"
                                                            width: 30
                                                            height: 30
                                                            anchors.centerIn: parent
                                                            ColorOverlay{
                                                                source: parent
                                                                anchors.fill: parent
                                                                color: "white"
                                                            }
                                                        }
                                                    }
                                                    Text{
                                                        anchors.verticalCenter: parent.verticalCenter
                                                        font.family: font_noto_r.name
                                                        color: map.tool === "dot_spline"?"black":color_gray
                                                        text: qsTr("곡선")
                                                    }
                                                }

                                                MouseArea{
                                                    anchors.fill: parent
                                                    onClicked:{
                                                        supervisor.writelog("[ANNOTATION] Travel line : Set tool to dot_spline");
                                                        map.clear("spline");
                                                        map.setTool("dot_spline");
                                                        map.setDrawingColor(255);
                                                        map.setDrawingWidth(slider_brush.value);
                                                    }
                                                }
                                            }
                                            Rectangle{
                                                width: 100
                                                height: 50
                                                color: "transparent"
                                                Row{
                                                    anchors.centerIn: parent
                                                    spacing: 10
                                                    Rectangle{
                                                        width: 50
                                                        height: width
                                                        radius: width
                                                        color: map.tool === "erase"?color_green:color_gray
                                                        Image{
                                                            source: "icon/icon_erase.png"
                                                            width: 30
                                                            height: 30
                                                            anchors.centerIn: parent
                                                            ColorOverlay{
                                                                source: parent
                                                                anchors.fill: parent
                                                                color: "white"
                                                            }
                                                        }
                                                    }
                                                    Text{
                                                        anchors.verticalCenter: parent.verticalCenter
                                                        font.family: font_noto_r.name
                                                        color: map.tool === "erase"?"black":color_gray
                                                        text: qsTr("지우개")
                                                    }
                                                }

                                                MouseArea{
                                                    anchors.fill: parent
                                                    onClicked:{
                                                        supervisor.writelog("[ANNOTATION] Travel line : Set tool to erase");
                                                        map.clear("spline");
                                                        map.setDrawingWidth(slider_erase.value);
                                                        map.setTool("erase");
                                                    }
                                                }
                                            }
                                        }
                                    }
                                    Rectangle{
                                        id: rect_annot_tline_1
                                        width: rect_annot_boxs.width
                                        height: 60
                                        visible: map.tool === "dot_spline"
                                        color: "white"
                                        Row{
                                            anchors.centerIn: parent
                                            spacing: 20
                                            Item_buttons{
                                                type: "round_text"
                                                width: 120
                                                height: 40
                                                text: qsTr("취소")
                                                fontsize: 20
                                                onClicked:{
                                                    click_sound.play();
                                                    supervisor.writelog("[ANNOTATION] Travel line : Cancel dot spline");
                                                    map.clear("spline");
                                                    map.setTool("draw");
                                                }
                                            }
                                            Item_buttons{
                                                type: "round_text"
                                                width: 120
                                                height: 40
                                                fontsize: 20
                                                text: qsTr("저장")
                                                onClicked:{
                                                    click_sound.play();
                                                    supervisor.writelog("[ANNOTATION] Travel line : Save dot spline");
                                                    map.save("spline");
                                                    map.setTool("draw");
                                                }
                                            }
                                        }
                                    }
                                    Rectangle{
                                        id: rect_annot_box3
                                        width: rect_annot_boxs.width
                                        height: 60
                                        color: "white"
                                        visible: map.tool === "draw" || map.tool === "straight" || map.tool === "dot_spline"
                                        Text{
                                            text: qsTr("브러시 사이즈")
                                            font.family: font_noto_r.name
                                            font.pixelSize: 15
                                            anchors.verticalCenter: parent.verticalCenter
                                            anchors.left: parent.left
                                            anchors.leftMargin: 30
                                        }
                                        Slider {
                                            id: slider_brush
                                            x: 300
                                            y: 330
                                            value: 1
                                            anchors.verticalCenter: parent.verticalCenter
                                            anchors.right: parent.right
                                            anchors.rightMargin: 30
                                            width: 170
                                            height: 18
                                            from: 1
                                            stepSize: 1
                                            to : 10
                                            onValueChanged: {
                                                map.setDrawingWidth(value)
                                            }
                                            onPressedChanged: {
                                                if(slider_brush.pressed){
                                                    map.show_brush = true;
                                                }else{
                                                    map.show_brush = false;
                                                }
                                            }
                                        }
                                    }
                                    Rectangle{
                                        width: rect_annot_boxs.width
                                        height: 60
                                        color: "white"
                                        visible: map.tool === "erase"
                                        Text{
                                            text: qsTr("브러시 사이즈")
                                            font.family: font_noto_r.name
                                            font.pixelSize: 15
                                            anchors.verticalCenter: parent.verticalCenter
                                            anchors.left: parent.left
                                            anchors.leftMargin: 30
                                        }
                                        Slider {
                                            id: slider_erase
                                            x: 300
                                            y: 330
                                            value: 30
                                            anchors.verticalCenter: parent.verticalCenter
                                            anchors.right: parent.right
                                            anchors.rightMargin: 30
                                            width: 170
                                            height: 18
                                            from: 10
                                            to : 100
                                            onValueChanged: {
                                                map.setDrawingWidth(value);
                                            }
                                            onPressedChanged: {
                                                if(slider_erase.pressed){
                                                    map.show_brush = true;
                //                                    map.brushchanged();
                                                }else{
                                                    map.show_brush = false;
                //                                    map.brushdisappear();
                                                }
                                            }
                                        }
                                    }

                                }

                            }

                            Item_buttons{
                                type: "round_text"
                                anchors.horizontalCenter: parent.horizontalCenter
                                anchors.bottom: parent.bottom
                                anchors.bottomMargin : 50
                                text : qsTr("저 장")
                                width: 200
                                height: 100
                                onClicked:{
                                    click_sound.play();
                                    popup_save_travelline.save_mode = "tline";
                                    popup_save_travelline.open();
                                }
                            }
                        }
                        Rectangle{
                            visible: select_mode===3
                            width: annot_pages.width - map.width - 200
                            height: map.height
                            color: color_light_gray
                            Timer{
                                id: timer_check_tline
                                running: true
                                repeat: true
                                interval: 1000
                                onTriggered: {
                                    model_tline_error.clear();
                                    for(var i=0; i<supervisor.getTravellineIssue(); i++){
                                        model_tline_error.append({"group":supervisor.getTravellineIssueGroup(i),
                                                                     "name":supervisor.getTravellineIssueName(i),
                                                                     "is_far":supervisor.getTravellineIssueFar(i),
                                                                     "is_broken":supervisor.getTravellineIssueBroken(i)});
                                    }
                                }
                            }
                            Column{
                                anchors.centerIn: parent
                                spacing: 30
                                Item_buttons{
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    type: "start_progress"
                                    width: 180
                                    height: 60
                                    id: btn_recheck_tline
                                    text: qsTr("다시 검색")
                                    fontsize: 25
                                    onClicked:{
                                        select_tline_issue = -1;
                                        supervisor.checkTravelline();
                                        timer_check_tline.start();
                                    }
                                }
                                Rectangle{
                                    width: 350
                                    height: 450
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    Column{
                                        anchors.centerIn: parent
                                        spacing: 3
                                        Text{
                                            visible: model_tline_error.count === 0
                                            anchors.horizontalCenter: parent.horizontalCenter
                                            font.family: font_noto_r.name
                                            font.pixelSize: 40
                                            horizontalAlignment: Text.AlignHCenter
                                            text: "모든 경로가\n정상입니다"
                                        }

                                        Repeater{
                                            anchors.horizontalCenter: parent.horizontalCenter
                                            model:ListModel{id:model_tline_error}
                                            Rectangle{
                                                width: 250
                                                height: is_far?is_broken?80:50:50
                                                Column{
                                                    anchors.centerIn: parent
                                                    Text{
                                                        anchors.horizontalCenter: parent.horizontalCenter
                                                        font.family: font_noto_b.name
                                                        font.pixelSize: 20
                                                        text: "["+group + "] " + name
                                                    }
                                                    Text{
                                                        visible: is_broken
                                                        anchors.horizontalCenter: parent.horizontalCenter
                                                        font.family: font_noto_r.name
                                                        font.pixelSize: 15
                                                        color: color_red
                                                        text: "대기 위치와 경로가 연결되지 않습니다"
                                                    }
                                                    Text{
                                                        anchors.horizontalCenter: parent.horizontalCenter
                                                        font.family: font_noto_r.name
                                                        font.pixelSize: 15
                                                        color: color_warning
                                                        visible: is_far
                                                        text: "경로와 너무 멀리 떨어져있습니다"
                                                    }
                                                }
                                                MouseArea{
                                                    anchors.fill: parent
                                                    onPressed:{
                                                        parent.color = color_light_gray
                                                    }
                                                    onReleased: {
                                                        if(select_tline_issue === index){
                                                            parent.color = "white";
                                                        }else{
                                                            click_sound.play();
                                                            parent.color = color_warning;
                                                            select_tline_issue = index;
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        MAP_FULL2{
                            id: map
                            objectName: "annot_tline"
                            width: height
                            height: annot_pages.height - 100
                        }

                    }
                    }

            }
            Popup{
                id: popup_save_travelline
                width: parent.width
                height: parent.height
                background:Rectangle{
                    anchors.fill: parent
                    color: "#282828"
                    opacity: 0.7
                }
                property string save_mode: "tline"
                property bool edited_mode: false
                Rectangle{
                    anchors.centerIn: parent
                    width: 450
                    height: 230
                    color: "white"
                    radius: 20

                    Column{
                        anchors.centerIn: parent
                        spacing: 20
                        Column{
                            anchors.horizontalCenter: parent.horizontalCenter
                            Text{
                                text: qsTr("이대로 <font color=\"#12d27c\">저장</font>하시겠습니까?")
                                font.family: font_noto_r.name
                                font.pixelSize: 30
                                anchors.horizontalCenter: parent.horizontalCenter
                            }
                            Text{
                                text: qsTr("기존의 파일은 삭제됩니다")
                                font.family: font_noto_r.name
                                font.pixelSize: 20
                                anchors.horizontalCenter: parent.horizontalCenter
                            }
                        }
                        Row{
                            anchors.horizontalCenter: parent.horizontalCenter
                            spacing: 20
                            Item_buttons{
                                type: "round_text"
                                text: qsTr("저장 안하고 종료")
                                width: 180
                                height: 60
                                onClicked:{
                                    click_sound.play();
                                    timer_check_tline.stop();
                                    map.clear("all");
                                    popup_save_travelline.close();
                                    annot_pages.sourceComponent = page_annot_additional_menu;
                                }
                            }
                            Item_buttons{
                                type: "round_text"
                                text: qsTr("확인")
                                width: 180
                                height: 60
                                onClicked:{
                                    //save temp Image
                                    timer_check_tline.stop();
                                    if(popup_save_travelline.save_mode === "tline"){
                                        supervisor.writelog("[QML] MAP PAGE : SAVE TRAVELLINE ");
                                        map.save("tline");
                                        click_sound.play();
                                    }else if(popup_save_travelline.save_mode === "velmap"){
                                        supervisor.writelog("[QML] MAP PAGE : SAVE VELOCITY MAP ");
                                        map.save("velmap");
                                        click_sound.play();
                                    }else{
                                        click_sound_no.play();
                                    }

                                    popup_save_travelline.close();
                                    annot_pages.sourceComponent = page_annot_additional_menu;
                                }
                            }
                        }
                    }

                }

            }

        }
    }
    Component{
        id: page_annot_velmap
        Item{
            width: annot_pages.width
            height: annot_pages.height
            Rectangle{
                anchors.fill: parent
                color: color_dark_navy
            }
            Component.onCompleted: {
                map.setEnable(true);
                select_preset = 0;
                supervisor.setMotorLock(true);
            }
            Component.onDestruction: {
                map.setEnable(false);
            }

            Timer{
                interval: 500
                running: true
                onTriggered:{
                    map.setViewer("annot_velmap");
                }
            }
            Row{
                Rectangle{
                    width: 150
                    color: color_dark_navy
                    height: annot_pages.height
                }
                Column{
                    Rectangle{
                        width: annot_pages.width - 150
                        height: 100
                        color: "transparent"
                        Text{
                            text: qsTr("안전속도 구간을 설정합니다")
                            color: "white"
                            horizontalAlignment: Text.AlignHCenter
                            font.pixelSize: 40
                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.horizontalCenterOffset: -100
                            font.family: font_noto_b.name
                            anchors.centerIn: parent
                        }
                        Row{
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.right: parent.right
                            anchors.rightMargin: 30
                            spacing: 20
                            Item_buttons{
                                type: "circle_text"
                                text: "?"
                                width: 60
                                height: 60
                                onClicked:{
                                    click_sound.play();
                                    popup_annot_help.open();
                                    popup_annot_help.setTitle(qsTr("안전속도 구간"));
                                    popup_annot_help.addLine(qsTr("사람이 붐비거나 통로가 비좁아서 로봇이 천천히 움직여야 하는 구간을 표시해주세요"));
                                    popup_annot_help.addLine(qsTr("로봇이 주행 중 해당 구간에 진입하면 자동으로 속도를 1,2단계로 낮춥니다"));
                                    popup_annot_help.addLine(qsTr("각 속도 구간의 상세 속도를 지정하고 싶으시다면 세팅 페이지의 프리셋 수정을 이용하세요"))
                                }
                            }
                            Item_buttons{
                                type: "round_text"
                                text: qsTr("저장 후 종료")
                                width: 120
                                height: 60
                                onClicked:{
                                    click_sound.play();
                                    supervisor.writelog("[MAPPING] Velocity Map : Save and Exit");
                                    popup_save_velmap.open();
                                }
                            }
                        }
                    }
                    Row{
                        MAP_FULL2{
                            id: map
                            width: height
                            objectName: "annot_velmap"
                            height: annot_pages.height - 100
                        }
                    }

                }

            }
            Popup{
                id: popup_mapping_help
                anchors.centerIn: parent
                width: 800
                height: 600
                background: Rectangle{
                    width: popup_mapping_help.width
                    height: popup_mapping_help.height
                    radius: 30
                    color: color_dark_black
                    opacity: 0.9
                }
                Column{
                    Rectangle{
                        width: popup_mapping_help.width
                        height: 100
                        color: "transparent"
                        Text{
                            anchors.centerIn: parent
                            text: qsTr("도움말")
                            font.family: font_noto_r.name
                            font.pixelSize: 50
                            color:"white"
                        }
                    }
                    Rectangle{
                        width: popup_mapping_help.width
                        height: popup_mapping_help.height - 100
                        color: "transparent"
                        Column{
                            anchors.centerIn: parent
                            spacing: 50
                            Column{
                                spacing: 10
                                width: 550
                                Text{
                                    text: qsTr("Q. 안전속도 구간이란?")
                                    font.family: font_noto_r.name
                                    font.pixelSize: 25
                                    color:"white"
                                }
                                Text{
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    text: qsTr("로봇이 이동 중 해당 구간에 진입하면 '느리게', '아주 느리게' 속도로 이동합니다\n각 속도의 설정 값은 세팅화면에서 변경 가능합니다")
                                    font.family: font_noto_r.name
                                    font.pixelSize: 20
                                    color:"white"
                                }
                            }
                       }

                    }
                }
            }
        }
    }
    AnimatedImage{
        id: loading
        width: parent.width
        height: parent.height
        anchors.top: parent.top
        anchors.topMargin: statusbar.height
        function show(){
            source = "image/loading_rb.gif"
        }
        function hide(){
            source = "";
        }
        source: ""
    }

    MAP_FULL2{
        id: map_hide
        visible:false
        objectName: "annot_hide"
        enabled:false
    }

    Popup{
        id : popup_ask_mapload
        anchors.centerIn: parent
        width: 500
        height: 450
        background: Rectangle{
            anchors.fill: parent
            color: "transparent"
        }
        Rectangle{
            width : parent.width
            height: parent.height
            radius: 10
            Column{
                anchors.centerIn: parent
                spacing: 20
                Text{
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.family: font_noto_r.name
                    font.pixelSize: 40
                    color: color_dark_navy
                    text : qsTr("맵 보내기/가져오기")
                }
                Rectangle{
                    width: 300
                    height: 80
                    radius: 15
                    anchors.horizontalCenter: parent.horizontalCenter
                    color : "transparent"
                    border.width: 3
                    border.color:color_dark_navy
                    Text{
                        anchors.centerIn: parent
                        font.family: font_noto_r.name
                        font.pixelSize: 25
                        color: color_dark_navy
                        text : qsTr("서버로 보내기")
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked:{
                            click_sound.play();
                            supervisor.sendMapServer();
                            popup_ask_mapload.close();
                        }
                    }
                }
                Rectangle{
                    width: 300
                    visible: false
                    height: 80
                    anchors.horizontalCenter: parent.horizontalCenter
                    radius: 15
                    color : "transparent"
                    border.width: 3
                    border.color: color_dark_navy
                    Text{
                        font.family: font_noto_r.name
                        font.pixelSize: 20
                        anchors.centerIn: parent
                        color: color_dark_navy
                        text : qsTr("서버로부터 가져오기")
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked:{
                            click_sound.play();
                            supervisor.loadMapServer();
                            popup_ask_mapload.close();
                        }
                    }
                }
                Rectangle{
                    width: 300
                    anchors.horizontalCenter: parent.horizontalCenter
                    height: 80
                    radius: 15
                    color : "transparent"
                    border.width: 3
                    border.color:color_dark_navy
                    Text{
                        anchors.centerIn: parent
                        font.family: font_noto_r.name
                        font.pixelSize: 20
                        color: color_dark_navy
                        text : qsTr("로컬로부터 불러오기")
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked:{
                            click_sound.play();
                            popup_ask_mapload.close();
                            popup_map_list.open();
                        }
                    }
                }
            }
        }

    }

    Popup_map_list{
        id: popup_map_list
    }

    Popup{
        id: popup_notice
        anchors.centerIn: parent
        width: 800
        height: 300
        property string main_str: ""
        property string sub_str: ""
        property bool show_localization: false
        property bool show_motorinit: false
        background:Rectangle{
            anchors.fill: parent
            color: "transparent"
        }
        Rectangle{
            width: parent.width
            height: parent.height
            opacity: 0.9
            radius: 10
            color: color_dark_black
        }
        Rectangle{
            anchors.centerIn: parent
            width: parent.width-20
            height: parent.height-20
//            opacity: 0.8
            radius: 10
            color: "transparent"
            border.color: color_red
            border.width: 5
            Image{
                id: image_warn
                width: 120
                height: 120
                source: "image/warning.png"
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 50
            }
            Column{
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: image_warn.right
                anchors.leftMargin: 50
                Text{
                    color: color_red
                    font.family: font_noto_r.name
                    font.pixelSize: 40
                    text: popup_notice.main_str
                }
                Text{
                    color: color_red
                    font.family: font_noto_r.name
                    font.pixelSize: 30
                    text: popup_notice.sub_str
                }
            }
            MouseArea{
                anchors.fill: parent
                onClicked:{
                    popup_notice.close();
                }
            }
            Rectangle{
                width:  120
                height: 60
                anchors.right: parent.right
                anchors.rightMargin: 20
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 20
                color: "transparent"
                border.color: color_red
                border.width: 3
                radius: 10
                visible: popup_notice.show_localization
                Text{
                    anchors.centerIn: parent
                    color: color_red
                    font.family: font_noto_r.name
                    font.pixelSize: 20
                    text: qsTr("위치초기화")
                }
                MouseArea{
                    anchors.fill: parent
                    onPressed:{
                        parent.color = color_dark_black
                        click_sound.play()
                    }
                    onReleased:{
                        parent.color = "transparent"
                        loadPage(plocalization);
                    }
                }
            }
            Rectangle{
                width:  120
                height: 60
                color: "transparent"
                border.color: color_red
                border.width: 3
                anchors.right: parent.right
                anchors.rightMargin: 20
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 20
                radius: 10
                visible: popup_notice.show_motorinit
                Text{
                    anchors.centerIn: parent
                    color: color_red
                    font.family: font_noto_r.name
                    font.pixelSize: 20
                    text: qsTr("모터초기화")
                }
                MouseArea{
                    anchors.fill: parent
                    onPressed:{
                        parent.color = color_dark_black
                        click_sound.play()
                    }
                    onReleased:{
                        parent.color = "transparent"
                        supervisor.setMotorLock(true);

                    }
                }
            }
        }
    }

    Popup{
        id: popup_moving
        anchors.centerIn: parent
        width: 1280
        height: 800
        property string location: ""
        background:Rectangle{
            anchors.fill: parent
            color: color_dark_black
            opacity: 0.9
        }
        Rectangle{
            anchors.centerIn: parent
            width: parent.width-100
            height: 400
//            opacity: 0.8
            radius: 10
            color: "transparent"
            border.color: color_blue
            border.width: 5
            Image{
                id: image_moving
                width: 200
                height: 175
                source: "image/robot_moving.png"
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 100
            }
            Column{
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: image_moving.right
                anchors.leftMargin: 50
                spacing: 10
                Text{
                    visible: !robot_paused
                    color: color_blue
                    font.family: font_noto_r.name
                    font.pixelSize: 45
                    text: popup_moving.location===""?qsTr("로봇이 이동 중입니다"):qsTr("로봇이 ")+popup_moving.location+qsTr("로")
                }
                Text{
                    visible: !robot_paused && popup_moving.location !==""
                    color: color_blue
                    font.family: font_noto_r.name
                    font.pixelSize: 45
                    text: qsTr("이동 중입니다")
                }
                Text{
                    visible: robot_paused
                    color: color_blue
                    font.family: font_noto_r.name
                    font.pixelSize: 50
                    text: qsTr("로봇이 일시정지 되었습니다")
                }
                Row{
                    visible: robot_paused
                    anchors.horizontalCenter: parent.horizontalCenter
                    spacing: 60
                    Item_buttons{
                        type: "round_text"
                        width: 140
                        height: 80
                        fontcolor: color_blue
                        btncolor: color_dark_black
                        bordercolor: color_blue
                        text: qsTr("경로 재개")
                        onClicked:{
                            click_sound.play();
                            supervisor.writelog("[ANNOTATION] Test Moving : Resume")
                            supervisor.moveResume();
                            timer_check_pause.start();
                        }
                    }
                    Item_buttons{
                        type: "round_text"
                        width: 140
                        height: 80
                        fontcolor: color_blue
                        btncolor: color_dark_black
                        bordercolor: color_blue
                        text: qsTr("경로 취소")
                        onClicked:{
                            click_sound.play();
                            supervisor.writelog("[ANNOTATION] Test Moving : Path Cancled")
                            supervisor.moveStop();
                            playMusic.stop();
                            timer_check_pause.start();
                        }
                    }
                }
            }
            MouseArea{
                anchors.fill: parent
                visible: !robot_paused
                onClicked:{
                    click_sound.play();
                    if(robot_paused){
//                        supervisor.writelog("[USER INPUT] MOVING RESUME 2")
//                        supervisor.moveResume();
//                        timer_check_pause.start();
                    }else{
                        supervisor.writelog("[USER INPUT] MOVING PAUSE 2")
                        supervisor.movePause();
                        timer_check_pause.start();
                    }
                }
            }
            Rectangle{
                width:  120
                height: 60
                anchors.right: parent.right
                anchors.rightMargin: 20
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 20
                color: "transparent"
                border.color: color_red
                border.width: 3
                radius: 10
                visible: popup_notice.show_localization
                Text{
                    anchors.centerIn: parent
                    color: color_red
                    font.family: font_noto_r.name
                    font.pixelSize: 20
                    text: qsTr("위치초기화")
                }
                MouseArea{
                    anchors.fill: parent
                    onPressed:{
                        parent.color = color_dark_black
                        click_sound.play()
                    }
                    onReleased:{
                        parent.color = "transparent"
                        loadPage(plocalization);
                    }
                }
            }
            Rectangle{
                width:  120
                height: 60
                color: "transparent"
                border.color: color_red
                border.width: 3
                anchors.right: parent.right
                anchors.rightMargin: 20
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 20
                radius: 10
                visible: popup_notice.show_motorinit
                Text{
                    anchors.centerIn: parent
                    color: color_red
                    font.family: font_noto_r.name
                    font.pixelSize: 20
                    text: qsTr("모터초기화")
                }
                MouseArea{
                    anchors.fill: parent
                    onPressed:{
                        parent.color = color_dark_black
                        click_sound.play()
                    }
                    onReleased:{
                        parent.color = "transparent"

                    }
                }
            }
        }
    }
    Timer{
        id: timer_check_pause
        interval: 500
        running: false
        repeat: true
        onTriggered: {
            if(supervisor.getStateMoving() === 4){
                robot_paused = true;
                supervisor.writelog("[QML] CHECK MOVING STATE : PAUSED")
                timer_check_pause.stop();
            }else if(supervisor.getStateMoving() === 0){
                robot_paused = false;
                test_move_state = 0;
                supervisor.writelog("[QML] CHECK MOVING STATE : NOT READY")
                movefail(4);
                popup_moving.close();
                timer_check_pause.stop();
            }else if(supervisor.getStateMoving() === 1){
                supervisor.writelog("[QML] CHECK MOVING STATE : READY")
                robot_paused = false;
                test_move_state = 0;
                timer_check_pause.stop();
                popup_moving.close();
            }else{
                robot_paused = false;
                supervisor.writelog("[QML] CHECK MOVING STATE : "+Number(supervisor.getStateMoving()));
                timer_check_pause.stop();
            }
        }
    }
    Popup_help{
        id: popup_annot_help
    }
    Tool_Keyboard{
        id: keyboard
    }
    Audio{
        id: playMusic
        autoPlay: false
        volume: volume_bgm/100
        source: "bgm/song.mp3"
        loops: 99
        property bool isplaying: false
        onStopped: {
            isplaying = false;
        }
        onPlaying:{
            isplaying = true;
        }
    }
}
