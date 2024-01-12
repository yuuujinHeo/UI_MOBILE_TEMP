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


    property bool debug_mode: false
    property var volume_button : parseInt(supervisor.getSetting("setting","UI","volume_button"));
    property var volume_bgm : parseInt(supervisor.getSetting("setting","UI","volume_bgm"));
    property var volume_voice: parseInt(supervisor.getSetting("setting","UI","volume_voice"));

    flags: !testMode?Qt.Window | Qt.FramelessWindowHint | Qt.WindowMinimizeButtonHint |Qt.WindowStaysOnTopHint |Qt.WindowOverridesSystemGestures |Qt.MaximizeUsingFullscreenGeometryHint:Qt.Window
    visibility: !testMode?Window.FullScreen:Window.Windowed
    onVisibilityChanged: {
        if(!testMode){
            if(mainwindow.visibility == Window.Minimized){
                print("minimized");
            }else if(mainwindow.visibility == Window.FullScreen){
                print("fullscreen");
            }else{
                supervisor.writelog("[QML - MAIN] Window show fullscreen");
                mainwindow.visibility = Window.FullScreen;
            }
        }
    }
    property color color_more_gray: "#777777";
    property color color_dark_gray: "#999999";
    property color color_red: "#E7584D"
    property color color_dark_red: "#D6473C"
    property color color_green: "#12d27c"
    property color color_mid_green: "#0FB168"
    property color color_yellow: "#F7DB0D"
    property color color_dark_black: "#282828"
    property color color_mid_black: "#464646"
    property color color_gray: "#d8d8d8"
    property color color_mid_gray: "#e8e8e8"
    property color color_light_gray: "#F4F4F4"
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
    property string pmovefail: "qrc:/Page_MoveFail.qml"
    property string pmoving: "qrc:/Page_moving.qml"
    property string ppickup: "qrc:/Page_pickup.qml"
    property string ppickupCall: "qrc:/Page_pickup_calling.qml"
    property string psetting: "qrc:/Page_setting.qml"
    property string plog: "qrc:/Page_log.qml"
    property string pmapping: "qrc:/Page_mapping.qml"
//    property string 건너뛰기zation: "qrc:/Page_localization.qml"
    property string pannotation: "qrc:/Page_annotation.qml"

    property string robot_type: supervisor.getRobotType()
    property string robot_name: supervisor.getRobotName()
    property var robot_battery: 0
    property var count_resting: 0
    property string cur_location;

    property bool playingSound: false
    property string cur_sound: ""
    property string next_sound: ""
    property string prev_sound: ""

    function setClear(name, state){
        print("setClear" , name, state);
        loader_page.item.setClear(name,state);
    }

    function gitfailed(){
        loader_page.item.git_failed();
    }
    function gitnewest(){
        loader_page.item.git_newest();
    }

    function movefail_wake(){
        if(loader_page.item.objectName == "page_annotation"){
            loader_page.item.movedone();
        }
    }

    function movefail(){
        if(loader_page.item.objectName == "page_annotation" || loader_page.item.objectName == "page_kitchen"){
            if(supervisor.getIPCConnection() === false){
//                supervisor.playVoice("sorry");
                supervisor.playVoice("sorry");
                loader_page.item.movefail(5);
            }if(supervisor.getEmoStatus()){
                supervisor.playVoice("error_emo");
                loader_page.item.movefail(2);
            }else if(supervisor.getLocalizationState() === 0 || supervisor.getLocalizationState() === 3){

                supervisor.playVoice("error_localization");
                loader_page.item.movefail(1);
            }else if(supervisor.getMotorState() === 0){
//                supervisor.playVoice("error_");
                supervisor.playVoice("sorry");
                loader_page.item.movefail(4);
            }else if(supervisor.getStateMoving() === 0){
//                supervisor.playVoice("sorry");
                supervisor.playVoice("sorry");
                loader_page.item.movefail(0);
            }else{
                supervisor.playVoice("sorry");
                loader_page.item.movefail(6);
                supervisor.writelog("[MOVEFAIL] WEIRED MOVEFAIL : "+supervisor.getStateMoving().toString()+","+supervisor.getLocalizationState().toString()+","+supervisor.getMotorState().toString())
            }
        }else if(loader_page.item.objectName == "page_mapping" || loader_page.item.objectName == "page_init" || loader_page.item.objectName == "page_movefail" || loader_page.item.objectName == "page_map" || loader_page.item.objectName == "page_setting"){

        }else{
//            //*/0: no path /1: local fail /2: emergency /3: user stop /4: motor error
//            if(supervisor.getEmoStatus()){
//                supervisor.writelog("[UI] Force Page Change MoveFail : Emergency Switch");
//                loadPage(pmovefail);
//                loader_page.item.setNotice(2);
//                supervisor.playVoice("error_emo");
//            }else if(supervisor.getMotorState() === 0){
//                supervisor.writelog("[UI] Force Page Change MoveFail : Motor not ready");
//                loadPage(pmovefail);
//                loader_page.item.setNotice(4);
////                stopVoice();
//            }else if(supervisor.getLocalizationState() === 0 || supervisor.getLocalizationState() === 3){
//                supervisor.writelog("[UI] Force Page Change MoveFail : Localization not ready");
//                loadPage(pmovefail);
//                loader_page.item.setNotice(1);
//                supervisor.playVoice("error_localization");
//            }else if(supervisor.getStateMoving() === 0){
//                supervisor.writelog("[UI] Force Page Change MoveFail : Robot not running");
//                loadPage(pmovefail);
//                loader_page.item.setNotice(0);
//                supervisor.playVoice("error_no_path");
//            }else{
//                supervisor.writelog("[UI] Force Page Change MoveFail : Unknown state ("+supervisor.getStateMoving().toString()+","+supervisor.getLocalizationState().toString()+","+supervisor.getMotorState().toString()+")");
//            }*/
        }
    }

    Component.onCompleted: {
//        popup_patrol.open();
    }

    function lessbattery(){
        supervisor.writelog("[UI] Play Voice : less battery");
        supervisor.playVoice("low_battery");
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
            supervisor.playVoice("start_move_charge");
        }else if(cur_location == "Resting0"){
            cur_location = qsTr("대기 장소");
            supervisor.playVoice("start_move_resting");
        }else if(cur_location == "Cleaning0"){
            cur_location = qsTr("퇴식 장소");
            supervisor.playVoice("start_move_resting");
        }else{
            if(supervisor.isCallingMode() || supervisor.getSetting("setting","ROBOT_TYPE","type") === "CLEANING"){
                supervisor.playVoice("start_calling");
            }else{
                supervisor.playVoice("start_serving");
            }
        }

        if(loader_page.item.objectName == "page_annotation"){
            supervisor.writelog("[UI] Annotation Check : Moving Start "+cur_location);
            loader_page.item.movestart();
        }else{
            loadPage(pmoving)
            supervisor.writelog("[UI] Force Page Change Moving : "+cur_location);
            loader_page.item.pos_name = cur_location;
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

    function need_init(){
        print("need_init");
        if(!debug_mode){
            if(loader_page.item.objectName != "page_annotation" && loader_page.item.objectName != "page_mapping"&& loader_page.item.objectName != "page_init"){
                supervisor.writelog("[UI] Force Page Change : Robot disconnected");
                loadPage(pinit);
            }
        }
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
        supervisor.playVoice("serving");
        print("excuseme");
    }
    function movewait(){
        //죄송합니다 잠시만 지나가겠습니다
        supervisor.playVoice("wait");
    }

    function pull_success(){
        if(loader_page.item.objectName == "page_init" || loader_page.item.objectName == "page_setting"){
            loader_page.item.pull_success();
        }
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
        print("loadpage start");
        pbefore = loader_page.source;
        loader_page.source = page;
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

//    Popup_patrol_page{
//        id: popup_patrol
//        width: parent.width
//        height: parent.height
//    }

    Page_moving{
        anchors.fill: parent
        pos_name : qsTr("대기위치")
    }

    Loader{
        visible: false
        id: loader_page
        focus: true
        anchors.fill: parent
        onLoaded: {
            timer_update.start();
            loader_page.item.init();
        }
        source: pinit
    }

    Timer{
        id: timer_update
        interval: 3000
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
                count_resting =0;
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
                property var password: 0
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
        onVolumeChanged:{
            print("volume : ",volume);
        }
        onStatusChanged: {
            print(status);
        }
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

}
