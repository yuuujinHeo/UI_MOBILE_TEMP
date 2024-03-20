import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
//import QtQuick.Dialogs
import Qt.labs.platform 1.0
import QtGraphicalEffects 1.0
import "."
import io.qt.Supervisor 1.0
import io.qt.Keyemitter 1.0
import io.qt.MapViewer 1.0
import QtMultimedia 5.12

Window {
    id: mainwindow
    visible: true
    width: 1280
    height: 800

    property var volume_button : parseInt(supervisor.getSetting("setting","UI","volume_button"));
//    property var volume_bgm : parseInt(supervisor.getSetting("setting","UI","volume_bgm"));
//    property var volume_voice: parseInt(supervisor.getSetting("setting","UI","volume_voice"));

    flags: !testMode?Qt.Window | Qt.FramelessWindowHint | Qt.WindowMinimizeButtonHint |Qt.WindowStaysOnTopHint |Qt.WindowOverridesSystemGestures |Qt.MaximizeUsingFullscreenGeometryHint:Qt.Window
    visibility: !testMode?Window.FullScreen:Window.Windowed
    onVisibilityChanged: {
        if(!testMode){
            if(mainwindow.visibility == Window.Minimized){
                supervisor.writelog("[UI] Window : minimized");
            }else if(mainwindow.visibility == Window.FullScreen){
                supervisor.writelog("[UI] Window : fullscreen");
            }else{
                supervisor.writelog("[UI] Window : "+Number(mainwindow.visibility)+" -> fullscreen");
                mainwindow.visibility = Window.FullScreen;
            }
        }
    }
    property color color_icon_gray: "#7f7f7f"
    property color color_more_gray: "#777777";
    property color color_dark_gray: "#999999";
    property color color_red: "#E7584D"
    property color color_dark_red: "#D6473C"
    property color color_green: "#12d27c"
    property color color_dark_green: "#148753"
    property color color_mid_green: "#0FB168"
    property color color_yellow: "#F7DB0D"
    property color color_dark_black: "#282828"
    property color color_mid_black: "#464646"
    property color color_gray: "#d8d8d8"
    property color color_mid_gray: "#e8e8e8"
    property color color_light_gray: "#F4F4F4"
    property color color_pink: "#ffd9ff"
    property color color_navy: "#4f5666"
    property color color_dark_navy: "#323744"
    property color color_mid_navy: "#242535"
    property color color_warning: "#fad271"
    property color color_blue: "#24a9f7"
    property color color_yellow_rect: "#ffc850"

    property string pbefore: pinit
    property string ploading: "qrc:/Page_loading.qml"
    property string pkitchen: "qrc:/Page_kitchen.qml"
    property string pinit: "qrc:/Page_init.qml"
    property string pcharging: "qrc:/Page_charge.qml"
    property string pmap: "qrc:/Page_map.qml"
    property string pmenu: "qrc:/Page_menus.qml"
    property string pmoving: "qrc:/Page_moving.qml"
    property string pmovingcustom: "qrc:/Page_moving_custom.qml"
    property string ppickup: "qrc:/Page_pickup.qml"
    property string ppickupCall: "qrc:/Page_pickup_calling.qml"
    property string psetting: "qrc:/Page_setting.qml"
    property string plog: "qrc:/Page_log.qml"
    property string pmapping: "qrc:/Page_mapping.qml"
//    property string 건너뛰기zation: "qrc:/Page_localization.qml"
    property string pannotation: "qrc:/Page_annotation.qml"

    property string robot_type: supervisor.getRobotType()
    property string robot_name: supervisor.getRobotName()
    property int robot_battery: 0
    property int count_resting: 0
    property string cur_location;

    property bool playingSound: false
    property string cur_sound: ""
    property string next_sound: ""
    property string prev_sound: ""

    function setClear(name, state){
        loader_page.item.setClear(name,state);
    }

    function git_pull_fail(){
        loader_page.item.git_failed();
    }
    function git_pull_already(){
        loader_page.item.git_newest();
    }

    function movefail_wake(){
        if(loader_page.item.objectName == "page_annotation" || loader_page.item.objectName == "page_moving"){
            loader_page.item.movedone();
        }
    }

    function movefailnopath(){
        supervisor.playVoice("error_no_path");
        supervisor.writelog("[UI] Robot not running");
        setNotice(0);
    }

    function setNotice(errnum){
        if(loader_page.item.objectName === "page_init" || loader_page.item.objectName === "page_mapping"){

        }else{
        //        loader_page.item.movedone();
            supervisor.stopBGM();
//            supervisor.moveStopFlag();
            popup_notice.init();
            popup_notice.style = "warning";
            if(errnum === 0){
                popup_notice.main_str = qsTr("경로를 찾지 못했습니다");
                popup_notice.sub_str = "";
                popup_notice.open();
            }else if(errnum === 1){
                popup_notice.main_str = qsTr("로봇의 위치를 찾을 수 없습니다");
                popup_notice.sub_str = qsTr("로봇초기화를 다시 해주세요");
                popup_notice.addButton(qsTr("위치초기화"));
                popup_notice.open();
            }else if(errnum === 2){
                popup_notice.main_str = qsTr("비상스위치가 눌려있습니다");
                popup_notice.sub_str = qsTr("비상스위치를 풀어주세요");
                popup_notice.open();
            }else if(errnum === 3){
                popup_notice.main_str = qsTr("경로가 취소되었습니다");
                popup_notice.sub_str = "";
                popup_notice.open();
            }else if(errnum === 4){
                popup_notice.style = "warning";
                popup_notice.main_str = qsTr("로봇이 수동모드입니다");
                popup_notice.sub_str = "";
                popup_notice.closemode = false;
                popup_notice.addButton(qsTr("모터초기화"))
                popup_notice.open();
            }else if(errnum === 5){
                popup_notice.main_str = qsTr("모터와 연결되지 않았습니다");
                popup_notice.sub_str = "";
                popup_notice.open();
            }else if(errnum === 6){
                popup_notice.main_str = qsTr("출발할 수 없는 상태입니다");
                popup_notice.sub_str = qsTr("로봇을 다시 초기화해주세요");
                popup_notice.open();
            }else if(errnum === 7){
                popup_notice.style = "warning";
                popup_notice.main_str = qsTr("목적지를 찾을 수 없습니다");
                popup_notice.sub_str = qsTr("");
                popup_notice.open();
            }else if(errnum === 8){
                popup_notice.style = "warning";
                popup_notice.main_str = qsTr("없는 지정순회 파일입니다");
                popup_notice.sub_str = qsTr("");
                popup_notice.open();
            }
        }

        print("move fail : ",errnum);
    }

    function robotnotready(){
//        if(supervisor.getEmoStatus()){
//            supervisor.playVoice("error_emo");
//            supervisor.writelog("[UI] Emergency Switch");
//            setNotice(2);
//        }else if(supervisor.getLocalizationState() === 0 || supervisor.getLocalizationState() === 3){
//            supervisor.playVoice("error_localization");
//            supervisor.writelog("[UI] Localization not ready");
//            setNotice(1);
//        }else{
//            supervisor.playVoice("sorry");
//            supervisor.writelog("[UI] Robot not ready to move");
//            setNotice(6);
//        }
    }

    function notfoundlocation(){
        supervisor.playVoice("sorry");
        setNotice(7);
    }

    function notfoundpatrol(){
        supervisor.playVoice("sorry");
        setNotice(8);

    }

    function movefail(){
        supervisor.stopBGM();
        if(supervisor.getIPCConnection() === false){
            supervisor.playVoice("sorry");
            supervisor.writelog("[UI] IPC Disconnected");
            setNotice(5);
        }else if(supervisor.getEmoStatus()){
            supervisor.playVoice("error_emo");
            supervisor.writelog("[UI] Emergency Switch");
            setNotice(2);
        }else if(supervisor.getLocalizationState() === 0 || supervisor.getLocalizationState() === 3){
            supervisor.playVoice("error_localization");
            supervisor.writelog("[UI] Localization not ready");
            setNotice(1);
        }else if(supervisor.getMotorState() === 0){
            supervisor.writelog("[UI] Motor not ready");
            setNotice(4);
        }else if(supervisor.getStateMoving() === 0){
            supervisor.playVoice("error_no_path");
            supervisor.writelog("[UI] Robot not running");
            setNotice(0);
        }

        if(loader_page.item.objectName == "page_annotation" || loader_page.item.objectName == "page_kitchen"){

        }else if(loader_page.item.objectName == "page_mapping" || loader_page.item.objectName == "page_init" || loader_page.item.objectName == "page_map" || loader_page.item.objectName == "page_setting"){

        }else if(loader_page.item.objectName == "page_moving"){

        }
    }

    Component.onCompleted: {
//        popup_patrol_page.page = "moving";
//        popup_patrol_page.open();
//        temp_popup_wifi.open();
    }


    function checkwifidone(){
        if(loader_page.item.objectName == "page_init" || loader_page.item.objectName == "page_setting"){
            loader_page.item.wifistatein();
        }
    }
    function movelocation(){
        cur_location = supervisor.getcurLoc();
        if(cur_location == "Charging0"){
            cur_location = qsTr("충전 장소");
            if(!supervisor.isPatrolPage()){
                supervisor.playVoice("move_charging");
            }
        }else if(cur_location == "Resting0"){
            cur_location = qsTr("대기 장소");
            if(!supervisor.isPatrolPage()){
                supervisor.playVoice("move_resting");
            }
        }else if(cur_location == "Cleaning0"){
            cur_location = qsTr("퇴식 장소");
            if(!supervisor.isPatrolPage()){
                supervisor.playVoice("move_cleaning");
            }
        }else{
            if(supervisor.isPatrolPage()){
//                supervisor.playVoice("start_serving");
            }else{
                if(supervisor.isCallingMode() || supervisor.getSetting("setting","ROBOT_TYPE","type") === "CLEANING"){
                    supervisor.playVoice("move_calling");
                }else{
                    supervisor.playVoice("move_serving");
                }
            }
        }

        if(loader_page.item.objectName == "page_annotation"){
            supervisor.writelog("[UI] Annotation Check : Moving Start "+cur_location);
            loader_page.item.movestart();
        }else{
            print(supervisor.isPatrolPage(), supervisor.getMovingPageMode())
            if(supervisor.isPatrolPage() && supervisor.getMovingPageMode() === "custom"){
                print("loadpage custom");
                if(loader_page.item.objectName !== "page_moving_custom"){
                    loadPage(pmovingcustom)
                    loader_page.item.setPage("moving");
                }
                loader_page.item.pos_name = cur_location;
            }else if(!supervisor.isPatrolPage() && supervisor.getSetting("setting","UI","moving_face") === "3"){
                print("loadpage custom");
                if(loader_page.item.objectName !== "page_moving_custom"){
                    loadPage(pmovingcustom)
                    loader_page.item.setPage("serving");
                }

                loader_page.item.pos_name = cur_location;
            }else{
                print("loadpage moving");
                loadPage(pmoving)
                supervisor.writelog("[UI] Force Page Change Moving : "+cur_location);
                loader_page.item.pos_name = cur_location;
            }

        }
    }

    function docharge(){
        if(loader_page.item.objectName == "page_annotation"){
            supervisor.writelog("[UI] Annotation Check : Moving Done (Charge) ");
            loader_page.item.movedone();
        }else{
            loadPage(pcharging)
            supervisor.writelog("[UI] Force Page Change Charging");
        }
    }
    function dochargeininit(){
        loadPage(pcharging)
        supervisor.writelog("[UI] Force Page Change Charging : Init State");
        loader_page.item.setInit();
    }

    function waitkitchen(){
        if(loader_page.item.objectName == "page_annotation"){
            supervisor.writelog("[UI] Annotation Check : Moving Done (Resting) ");
            loader_page.item.movedone();
        }else{
            loadPage(pkitchen)
            supervisor.writelog("[UI] Force Page Change Kitchen");
        }
    }

    function clearkitchen(){
        if(loader_page.item.objectName == "page_annotation"){
            supervisor.writelog("[UI] Annotation Check : Moving Done (Cleaning) ");
            loader_page.item.movedone();
        }else{
            loadPage(pkitchen)
            loader_page.item.cleaning();
            supervisor.writelog("[UI] Force Page Cleaning Location");
        }
    }

    function updatecamera(){
        if(loader_page.item.objectName == "page_setting"){
            loader_page.item.update_camera();
        }
    }

    function updatemapping(){
        if(loader_page.item.objectName == "page_mapping"){
            loader_page.item.update_mapping();
        }
    }

    function movestopped(){
        if(loader_page.item.objectName == "page_annotation"){
            supervisor.writelog("[UI] Annotation Check : Moving Done (Stopped) ");
        }else{
            supervisor.writelog("[UI] Force Page Change Kitchen : move stopped");
            loadPage(pkitchen);
        }
    }

    function showpickup(){
        if(loader_page.item.objectName == "page_annotation"){
            supervisor.writelog("[UI] Annotation Check : Moving Done (Serving Pickup) ");
            loader_page.item.movedone();
        }else{

            if(supervisor.isPatrolPage()){
                if(supervisor.getPatrolArriveMode() === "pickup"){
                    supervisor.writelog("[UI] Force Page Change Pickup(Patrol) : "+ loader_page.item.pos_name);
                    loadPage(ppickup);
                    loader_page.item.init();
                    loader_page.item.pos = "";
                    loader_page.item.pickup_1 = true;
                    loader_page.item.pickup_2 = true;
                    loader_page.item.pickup_3 = true;
                }else if(supervisor.getPatrolArriveMode() === "calling"){
                    supervisor.writelog("[UI] Force Page Change CallPickup(Patrol) : "+ loader_page.item.pos_name);
                    loadPage(ppickupCall);
                    loader_page.item.init();
                }
            }else{
                if(supervisor.isCallingMode() || supervisor.getSetting("setting","ROBOT_TYPE","type") === "CLEANING"){
                    supervisor.writelog("[UI] Force Page Change Pickup(Calling) : "+ loader_page.item.pos_name);
                    loadPage(ppickupCall);
                    loader_page.item.init();
                }else{
                    supervisor.writelog("[UI] Force Page Change Pickup : "+ loader_page.item.pos_name);
                    loadPage(ppickup);
                    loader_page.item.init();

                    var trays = supervisor.getPickuptrays();
                    if(trays.length === parseInt(supervisor.getSetting("setting","ROBOT_TYPE","tray_num"))){
                        loader_page.item.pos = "";
                        loader_page.item.pickup_1 = true;
                        loader_page.item.pickup_2 = true;
                        loader_page.item.pickup_3 = true;
                    }else{
                        var tempstr = "";
                        for(var i=0; i<trays.length; i++){
                            if(tempstr === ""){
                                tempstr = Number(trays[i])+qsTr("번");
                            }else{
                                tempstr += qsTr("과 ") + Number(trays[i])+qsTr("번");
                            }
                            if(trays[i] === 1){
                                loader_page.item.pickup_1 = true;
                            }else if(trays[i] === 2){
                                loader_page.item.pickup_2 = true;
                            }else if(trays[i] === 3){
                                loader_page.item.pickup_3 = true;
                            }
                        }
                        loader_page.item.pos = tempstr;
                    }
                }
            }


        }
    }

    function need_init(){
        if(!supervisor.isDebugMode()){
            if(loader_page.item.objectName != "page_annotation" && loader_page.item.objectName != "page_mapping"&& loader_page.item.objectName != "page_init"){
                supervisor.writelog("[UI] Force Page Change : Need Init");
                loadPage(pinit);
            }else if(loader_page.item.objectName == "page_annotation"){
                movefail();
            }
        }
    }
    function disconnected(){
        supervisor.writelog("[UI] Force Page Change : Robot disconnected");
        loadPage("");
        loadPage(pinit);
    }

    function unzip_done(){
        loader_page.item.update_unzip_done();
    }
    function unzip_failed(){
        loader_page.item.update_unzip_failed();

    }

    function show_loading(){
        rect_loading.open();
    }
    function unshow_loading(){
        rect_loading.close();
    }
    function show_resting(){
        rect_resting.open();
    }
    function unshow_resting(){
        rect_resting.close();
    }

    function call_setting(){
        loader_page.item.set_call_done();
    }

    function updatepath(){
        if(loader_page.item.objectName == "page_map")
            loader_page.item.updatepath();
    }

    function excuseme(){
        //로봇이 서빙중입니다
        supervisor.playVoice("moving");
    }
    function movewait(){
        //죄송합니다 잠시만 지나가겠습니다
        supervisor.playVoice("excuseme");
    }

    function pull_success(){
        if(loader_page.item.objectName == "page_init" || loader_page.item.objectName == "page_setting"){
            loader_page.item.pull_success();
        }
    }

    function wifi_con_success(){
        popup_loading.close();
        if(loader_page.item.objectName == "page_setting" || loader_page.item.objectName == "page_init")
            loader_page.item.wifi_con_success();
    }
    function wifi_set_success(){
        popup_loading.close();
        if(loader_page.item.objectName == "page_setting" || loader_page.item.objectName == "page_init")
            loader_page.item.wifi_set_success();
    }
    function wifi_con_fail(){
        popup_loading.close();
        if(loader_page.item.objectName == "page_setting" || loader_page.item.objectName == "page_init")
            loader_page.item.wifi_con_failed();
    }
    function wifi_set_fail(){
        popup_loading.close();
        if(loader_page.item.objectName == "page_setting" || loader_page.item.objectName == "page_init")
            loader_page.item.wifi_set_failed();
    }






    function wififailed(){
        if(loader_page.item.objectName == "page_setting" || loader_page.item.objectName == "page_init")
            loader_page.item.wifi_con_failed();
    }

    function wifisuccess(){
        if(loader_page.item.objectName == "page_setting" || loader_page.item.objectName == "page_init")
            loader_page.item.wifi_con_success();
    }

    function setip_fail(){
        if(loader_page.item.objectName == "page_setting" || loader_page.item.objectName == "page_init")
            loader_page.item.wifi_set_failed();

    }

    function wifireset(){
        if(loader_page.item.objectName == "page_setting" || loader_page.item.objectName == "page_init")
            loader_page.item.init();
    }

    function loadPage(page){
        print("loadpage start ",page);
        pbefore = loader_page.source;
        loader_page.source = page;
        if(page !== ""){
            if(loader_page.item.objectName == "page_kitchen")
                loader_page.item.init();
        }
        popup_notice.close();
        print("loadpage done");
    }

    function backPage(){
        print("backpage start");
        print(pbefore);
        loader_page.source = pbefore;
    }

    function update_fail(){
        if(loader_page.item.objectName == "page_init"){
            loader_page.item.update_fail();
        }
    }
    function update_success(){
        if(loader_page.item.objectName == "page_init"){
            loader_page.item.update_success();
        }
    }

    function update_ini(){
        robot_type = supervisor.getRobotType()
        robot_name = supervisor.getRobotName()
    }

    Supervisor{
        id:supervisor
    }

    Keyemitter{
        id: emitter
    }

    Popup_patrol_page{
        id: popup_patrol_page_main
        width: parent.width
        height: parent.height
        objectName: "popup_patrol_page_main"
    }

    Loader{
        id: loader_page
        focus: true
        anchors.fill: parent
        onLoaded: {
            supervisor.setCurrentPage(item.objectName);
            timer_update.start();
            loader_page.item.init();
        }
        source: pinit
    }

    Item{
        id: item_keyevent
        focus: true
        property bool shift_hold: false
        Keys.onPressed: (event) => {
            tt.key_event(event.key);
            if(event.key === Qt.Key_Shift){
                shift_hold = true;
                supervisor.pressShift();
            }
        }
        Keys.onReleased: (event) => {
            if(event.key === Qt.Key_Shift){
                shift_hold = false;
                supervisor.releaseShift();
            }
        }
    }

    Timer{
        id: timer_update
        interval: 1000
        triggeredOnStart: true
        running: true
        repeat: true
        onTriggered: {
            statusbar.curTime = Qt.formatTime(new Date(), "hh:mm")
            if(loader_page.item.objectName == "page_kitchen"){
                if(count_resting++ > 100){
//                    show_resting();
                }
            }else{
                count_resting = 0;
            }
        }
    }

    FontLoader{
        id: font_noto_b
        source: "font/NotoSansKR-Medium.otf"
    }
    FontLoader{
        id: font_noto_r
        source: "font/NotoSansKR-Light.otf"
    }

    Popup{
        id: popup_loading
        y: statusbar.height
        leftPadding: 0
        rightPadding: 0
        topPadding: 0
        bottomPadding: 0
        width: 1280
        height: 800 - statusbar.height
        closePolicy: Popup.NoAutoClose
        background: Rectangle{
            anchors.fill: parent
            color: "transparent"
        }
        onOpened:{
            print("popup_loading open")
            loadi.play("image/loading_rb.gif");
        }
        onClosed:{
            print("popup_loading close")
            loadi.stop();
        }

        AnimatedImage{
            id: loadi
            cache: false
            function play(name){
                source = name;
                visible = true;
            }
            function stop(){
                visible = false;
                source = "";
            }
            source:  ""
            MouseArea{
                width: 100
                height: 100
                anchors.right: parent.right
                anchors.bottom : parent.bottom
                z: 99
                property int password: 0
                onClicked: {
                    click_sound.play();
                    password++;
                    if(password > 4){
                        password = 0;
                        popup_loading.close();
                    }
                }
            }
        }
    }

    Popup{
        id: rect_resting
        width: parent.width

        height: parent.height
        onOpened:{
            resting_image.play("image/loading_rb.gif");
        }
        onClosed:{
            resting_image.stop();
        }

        background:Rectangle{
            anchors.fill: parent
            color: color_dark_black
        }
        AnimatedImage{
            id: resting_image
            source: ""
            cache: false
            function play(name){
                source = name;
                visible = true;
            }
            function stop(){
                visible = false;
                source = "";
            }
            anchors.fill: parent
        }
        MouseArea{
            anchors.fill: parent
            onClicked: {
                click_sound.play();
                rect_resting.close();
                count_resting = 0;
            }
        }
    }

    Item_statusbar{
        id: statusbar
        visible: true
    }

    SoundEffect{
        id: click_sound
        source: "bgm/click_start.wav"
        volume: volume_button/100
    }
    SoundEffect{
        id: click_sound_no
        source: "bgm/click_error.wav"
        volume: volume_button/100
    }
    SoundEffect{
        id: click_sound2
        source: "bgm/click2.wav"
        volume: volume_button/100
    }
    SoundEffect{
        id: start_sound
        source: "bgm/click_start.wav"
        volume: volume_button/100
    }
    Tool_KeyPad{
        id: keypad
    }

    Tool_Keyboard{
        id: keyboard
    }

    function showNotice(){
        popup_notice.init();
        if(supervisor.getIPCConnection()){
            if(supervisor.isDebugMode()){
                popup_notice.main_str = qsTr("디버그 모드입니다")
                popup_notice.sub_str = qsTr("디버그모드에서는 주행할 수 없습니다")
            }else if(supervisor.getPowerStatus()){
                if(supervisor.getEmoStatus()){
                    popup_notice.main_str = qsTr("비상스위치가 눌려있습니다")
                    popup_notice.sub_str = qsTr("비상스위치를 풀어주세요")
                }else if(supervisor.getMotorState() === 0){
                    popup_notice.main_str = qsTr("모터 락이 해제되었습니다.")
                    popup_notice.sub_str = qsTr("비상전원스위치를 눌렀다가 풀어주세요")
                    popup_notice.addButton(qsTr("모터초기화"));
                }else if(supervisor.getChargeConnectStatus() === 1){
                    popup_notice.main_str = qsTr("충전 케이블이 연결되어 있습니다")
                    popup_notice.sub_str = qsTr("충전케이블이 연결된 상태로 주행할 수 없습니다")
                }else{
                    popup_notice.main_str = qsTr("위치를 찾을 수 없습니다")
                    popup_notice.sub_str = qsTr("위치 초기화를 다시 해주세요")
                    popup_notice.addButton(qsTr("위치초기화"));
                }
            }else{
                popup_notice.main_str = qsTr("모터 전원이 꺼져있습니다")
                popup_notice.sub_str = qsTr("로봇을 재부팅해주세요")
            }
        }else{
            popup_notice.main_str = qsTr("로봇이 연결되지 않았습니다")
            popup_notice.sub_str = qsTr("프로그램을 재시작 해주세요")
            popup_notice.addButton(qsTr("재시작"));
        }
        popup_notice.open();
    }

    Popup_password{
        id: popup_password_minimize
        anchors.centerIn: parent
        onLogined:{
            mainwindow.showMinimized();
            popup_status_detail.close();
            popup_password.close();
        }
    }
    Popup_notice{
        id: popup_notice
        onClicked:{
            if(cur_btn === qsTr("수동이동")){
                supervisor.writelog("[UI] PopupNotice : Lock Off");
                supervisor.setMotorLock(false);
            }else if(cur_btn === qsTr("취 소")||cur_btn === qsTr("확 인")){
                popup_notice.close();
            }else if(cur_btn === qsTr("모터초기화")){
                supervisor.writelog("[UI] PopupNotice : Motor Init");
                supervisor.setMotorLock(true);
                supervisor.stateInit();
                popup_notice.close();
            }else if(cur_btn === qsTr("위치초기화")){
                supervisor.writelog("[UI] PopupNotice : Local Init");
                if(loader_page.item.objectName == "page_annotation"){
                    annot_pages.sourceComponent = page_annot_localization;
                }else{
                    loadPage(pinit);
                    supervisor.resetLocalization();
                    supervisor.stateInit();
                }
                popup_notice.close();
            }else if(cur_btn === qsTr("원래대로")){
                supervisor.writelog("[UI] PopupNotice : Lock On");
                supervisor.setMotorLock(true);
                supervisor.moveStopFlag();
                loadPage(pkitchen);
                popup_notice.close();
            }else if(cur_btn === qsTr("재시작")){
                supervisor.writelog("[UI] PopupNotice : Restart");
                supervisor.programRestart();
                popup_notice.close();
            }else if(cur_btn === qsTr("종 료")){
                supervisor.writelog("[UI] PopupNotice : Terminate");
                supervisor.programExit();
                popup_notice.close();
            }else if(cur_btn === qsTr("디버그모드 해제")){
                supervisor.writelog("[UI] PopupNotice : Debug Mode off");
                loadPage(pinit);
                supervisor.resetLocalization();
                supervisor.stateInit();
                popup_notice.close();
            }else if(cur_btn === qsTr("건너뛰기")){
                supervisor.writelog("[INIT] Debug Mode On");
                supervisor.passInit();
                loadPage(pkitchen);
                popup_notice.close();
            }else if(cur_btn === qsTr("퇴식모드 사용")){
                supervisor.saveAnnotation(supervisor.getMapname());
                supervisor.setSetting("setting","ROBOT_TYPE/type","CLEANING");
                supervisor.readSetting();
                loader_page.item.readSetting();
                loader_page.item.setAnnotLocation();
                popup_notice.close();
            }else if(cur_btn === qsTr("퇴식모드 미사용")){
                supervisor.setSetting("setting","ROBOT_TYPE/type","BOTH");
                supervisor.readSetting();
                loader_page.item.readSetting();
                popup_notice.close();
            }
        }
    }
}
