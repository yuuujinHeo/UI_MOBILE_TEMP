import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
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

    flags: !testMode?Qt.Window | Qt.FramelessWindowHint | Qt.WindowOverridesSystemGestures | Qt.WindowStaysOnTopHint : Qt.Window
//    flags: !testMode?Qt.Window | Qt.FramelessWindowHint | Qt.WindowMinimizeButtonHint |Qt.WindowStaysOnTopHint |Qt.WindowOverridesSystemGestures |Qt.MaximizeUsingFullscreenGeometryHint:Qt.Window
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
    property color color_light_navy: "#778095"
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

    function new_message(msg){
        popup_notice_main.init();
        popup_notice_main.main_str = msg;
        popup_notice_main.open();
    }

    function git_pull_fail(){
        loader_page.item.git_failed();
    }
    function git_pull_already(){
        loader_page.item.git_newest();
    }

    //MoveFail 상태에서 회복됨
    //Popup떠있는것 자동 닫고 이동중이었으면 movedone 처리
    function movefail_wake(){
        if(loader_page.item.objectName == "page_annotation" || loader_page.item.objectName == "page_moving"){
            loader_page.item.movedone();
        }
    }

    //Moving상태에서 위치설정했는데 저장된 location목록에 존재하지 않을 시
    function nolocation(){
        supervisor.writelog("[UI] No Location : "+supervisor.getcurLoc());
        supervisor.playVoice("error_no_path");
        setNotice("no_location");
    }

    function setNotice(errnum){
        supervisor.writelog("[UI] Set Notice : "+errnum+" (cur Page : "+loader_page.item.objectName+")")
        if(loader_page.item.objectName === "page_init" || loader_page.item.objectName === "page_mapping"){

        }else{
            supervisor.stopBGM();
            openNotice(errnum);
        }
    }

    function openNotice(errstr){
        loader_page.item.openNotice(errstr);
    }

    function robotnotready(){
        //240401 아래내용 전부 주석처리되어서 해제 + isRobotReady 걸리는 것들 모두 체크해서 표시 + 기존 showNotice를 대체
        supervisor.playVoice("sorry");
        if(supervisor.isDebugMode()){
            supervisor.writelog("[UI] Robot not Ready : Debug Mode");
            setNotice("debug");
        }else if(supervisor.getChargeConnectStatus()){
            supervisor.writelog("[UI] Robot not Ready : Charge Cable Connected");
            setNotice("charging");
        }else if(supervisor.getStateMoving() !== 2){
            supervisor.writelog("[UI] Robot not Ready : Robot Moving State -> "+Number(supervisor.getStateMoving()));
            setNotice("running");
        }else if(supervisor.getEmoStatus()){
            supervisor.writelog("[UI] Robot not Ready : Emergency Switch");
            setNotice("emo");
        }else if(supervisor.getLocalizationState() === 0 || supervisor.getLocalizationState() === 3){
            supervisor.writelog("[UI] Robot not Ready : Localization not ready");
            setNotice("localization");
        }else if(supervisor.getMotorStatus(0) !== 1 || supervisor.getMotorStatus(1) !== 1){
            supervisor.writelog("[UI] Robot not Ready : Motor State -> "+supervisor.getMotorStatusStr(0)+", "+supervisor.getMotorStatusStr(1));
            setNotice("motor");
        }else{
            supervisor.writelog("[UI] Robot not Ready : Unknown State");
        }
    }

    function notfoundlocation(){
        supervisor.playVoice("sorry");
        setNotice("no_location");
    }

    function notfoundpatrol(){
        supervisor.playVoice("sorry");
        setNotice("no_patrol");
    }


    //MoveFail -> Moving 중 lock이 걸린채로 MotorState not ready
    //Move 명령 5번 연속 씹힘
    //Moving 중 running state가 not ready
    //Pickup 상태에서 lock 걸린채로 MotorState not ready
    //MoveFail상태에서 localiazation, motor, charge state가 바뀌면서 에러발생
    //need_init 함수에서 annotation 페이지인 경우 실행
    function movefail(){
        supervisor.stopBGM();
        if(supervisor.getIPCConnection() === false){
            supervisor.playVoice("sorry");
            supervisor.writelog("[UI] IPC Disconnected");
            setNotice("ipc_discon");
        }else if(supervisor.getChargeConnectStatus()){
            supervisor.writelog("[UI] Charge Cable Connected");
            setNotice("charging");
        }else if(supervisor.getEmoStatus()){
            supervisor.playVoice("error_emo");
            supervisor.writelog("[UI] Emergency Switch");
            setNotice("emo");
        }else if(supervisor.getLocalizationState() === 0 || supervisor.getLocalizationState() === 3){
            supervisor.playVoice("error_localization");
            supervisor.writelog("[UI] Localization not ready");
            setNotice("localization");
        }else if(supervisor.getLockStatus() === 0){
            supervisor.writelog("[UI] Motor lock off");
            setNotice("motor_lock");
        }else if(supervisor.getMotorState() === 0){
            supervisor.writelog("[UI] Motor not ready");
            setNotice("motor_notready");
        }else if(supervisor.getStateMoving() === 0){
            supervisor.playVoice("error_no_path");
            supervisor.writelog("[UI] Robot not running");
            setNotice("no_path");
        }
    }

    function checkwifidone(){
        if(loader_page.item.objectName == "page_init" || loader_page.item.objectName == "page_setting"){
            loader_page.item.wifistatein();
        }
    }

    //Moving 상태에서 로봇이 Moving 시작했을 때
    function movestart(){
        cur_location = supervisor.getcurLoc();

        //패트롤 중일때 제외하고 각 위치에 맞는 보이스 출력
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
            }else{
                if(supervisor.isCallingMode()){
                    supervisor.playVoice("move_calling");
                }else{
                    supervisor.playVoice("move_serving");
                }
            }
        }

        //Annotation페이지의 경우 테스트 주행이므로 페이지 전환 없이 movestart 처리
        //Custom 페이지 설정한경우 moving_custom 페이지로, 아니면 그냥 moving페이지로 전환
        if(loader_page.item.objectName == "page_annotation"){
            supervisor.writelog("[UI] Move Start : Annotation Move -> "+cur_location);
            loader_page.item.movestart();
        }else{
            if(supervisor.isPatrolPage() && supervisor.getMovingPageMode() === "custom"){
                supervisor.writelog("[UI] Move Start : Patrol Custom -> "+cur_location);
                loadPage(pmovingcustom)
                loader_page.item.setPage("moving");
                loader_page.item.pos_name = cur_location;
            }else if(!supervisor.isPatrolPage() && supervisor.getSetting("setting","UI","moving_face") === "3"){
                supervisor.writelog("[UI] Move Start : Moving Custom -> "+cur_location);
                loadPage(pmovingcustom)
                loader_page.item.setPage("serving");
                loader_page.item.pos_name = cur_location;
            }else{
                supervisor.writelog("[UI] Move Start : Moving -> "+cur_location);
                loadPage(pmoving)
                loader_page.item.pos_name = cur_location;
            }
        }
    }

    //Charging 상태
    function charging(){
        if(loader_page.item.objectName == "page_annotation"){
            supervisor.writelog("[UI] Charging : Annotation -> movedone");
            loader_page.item.movedone();
        }else{
            loadPage(pcharging)
            supervisor.writelog("[UI] Charging");
        }
    }

    //moving 상태일때, 대기위치 move done하고 페이지 전환
    //patrol은 표시 안함. annotation은 페이지 전환 안하고 movedone 처리
    function waitkitchen(){
        if(loader_page.item.objectName == "page_annotation"){
            supervisor.writelog("[UI] Wait Kitchen : Moving Done (Resting0) ");
            loader_page.item.movedone();
        }else{
            loadPage(pkitchen)
            supervisor.writelog("[UI] Wait Kitchen");
        }
    }

    //moving 상태일때, 퇴식위치 move done하고 페이지 전환
    //patrol은 표시 안함. annotation은 페이지 전환 안하고 movedone 처리
    function clearkitchen(){
        if(loader_page.item.objectName == "page_annotation"){
            supervisor.writelog("[UI] Clear Kitchen : Moving Done (Cleaning0) ");
            loader_page.item.movedone();
        }else{
            loadPage(pkitchen)
            loader_page.item.cleaning();
            supervisor.writelog("[UI] Clear Kitchen");
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

    //moveStop 함수 호출되었을 때
    function movestopped(){
        if(loader_page.item.objectName == "page_annotation"){
            supervisor.writelog("[UI] Move Stopped : Move Done");
            loader_page.item.movedone();
        }else{
            supervisor.writelog("[UI] Move Stopped : Page Kitchen");
            loadPage(pkitchen);
        }
    }

    //Pickup 상태에서 이상없을 때(Call강제귀환없음)
    //패트롤중인경우 서빙위치에서 표시하기 체크된 경우에만 표시(시간지나면 자동넘김 됨)
    function showpickup(){
        //Annotation에서는 테스트 주행이므로 페이지 전환 없이 movedone 처리
        if(loader_page.item.objectName == "page_annotation"){
            supervisor.writelog("[UI] Show Pickup : Annotation Test Move Done");
            loader_page.item.movedone();
        }else{
            if(supervisor.isPatrolPage()){
                //패트롤 모드인경우 표시모드에 따라 페이지 전환
                if(supervisor.getPatrolArriveMode() === "pickup"){
                    supervisor.writelog("[UI] Show Pickup : Patrol Pickup mode -> "+ loader_page.item.pos_name);
                    loadPage(ppickup);
                    loader_page.item.show_all();
                }else if(supervisor.getPatrolArriveMode() === "calling"){
                    supervisor.writelog("[UI] Show Pickup : Patrol Calling mode -> "+ loader_page.item.pos_name);
                    loadPage(ppickupCall);
                }
            }else{
                //세팅정의된 표시모드에 따라 페이지 전환
                //로봇이 퇴식전용이거나 호출모드로 움직인 경우 -> calling 페이지
                //그 외 -> pickup 페이지
                if(supervisor.isCallingMode()){
                    supervisor.writelog("[UI] Show Pickup : Calling mode -> "+ loader_page.item.pos_name);
                    loadPage(ppickupCall);
                }else{
                    supervisor.writelog("[UI] Show Pickup : Pickup mode -> "+ loader_page.item.pos_name);
                    loadPage(ppickup);
                    loader_page.item.set_tray();
                }
            }
        }
    }

    //None 상태에서 IPC 연결안되고 debug모드 아니면서 init페이지 아님
    //Initalizing상태에서 localization은 좋지만 Motor가 not ready일때(lock on)
    //Initalizing상태에서 localization confirm이 false일 때
    //Charging상태에서 charging 케이블 연결해제됬을 때
    //위 상태에서 init페이지면 실행 안함, annotation페이지면 1회만 실행 -> movefail
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

    //로봇 연결이 끊어졌을 때
    //무조건 Init Page로 이동
    function disconnected(){
        supervisor.writelog("[UI] Disconnected : Page Init");
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
        if(loader_page.item.objectName == "page_setting" || loader_page.item.objectName == "page_init")
            loader_page.item.wifi_con_success();
    }

    function wifi_set_success(){
        if(loader_page.item.objectName == "page_setting" || loader_page.item.objectName == "page_init")
            loader_page.item.wifi_set_success();
    }

    function wifi_con_fail(){
        if(loader_page.item.objectName == "page_setting" || loader_page.item.objectName == "page_init")
            loader_page.item.wifi_con_failed();
    }

    function wifi_set_fail(){
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
        pbefore = loader_page.source;
        loader_page.source = page;
    }

    function backPage(){
        print("backpage start -> ",pbefore);
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
            supervisor.writelog("[LoaderQML] Load "+item.objectName);
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
            loader_page.item.key_event(event.key);
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

    Item_statusbar{
        id: statusbar
        visible: true
    }


    // Tool_KeyPad{
    //     id: keypad
    // }

    // Tool_Keyboard{
    //     id: keyboard
    // }

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
        id: popup_notice_main
        z:99
        onClicked:{
            if(cur_btn === qsTr("수동이동")){
                supervisor.writelog("[UI] PopupNotice : Lock Off");
                supervisor.setMotorLock(false);
            }else if(cur_btn === qsTr("취 소")||cur_btn === qsTr("확 인")){
                popup_notice_main.close();
            }else if(cur_btn === qsTr("위치초기화")){
                supervisor.writelog("[UI] PopupNotice : Local Init");
                if(loader_page.item.objectName == "page_annotation"){
                    loader_page.item.setAnnotLocation();
                }else{
                    loadPage(pinit);
                    supervisor.resetLocalization();
                    supervisor.stateInit();
                }
                popup_notice_main.close();
            }else if(cur_btn === qsTr("원래대로")){
                supervisor.writelog("[UI] PopupNotice : Lock On");
                supervisor.setMotorLock(true);
                supervisor.moveStopFlag();
                loadPage(pkitchen);
                popup_notice_main.close();
            }else if(cur_btn === qsTr("재시작")){
                supervisor.writelog("[UI] PopupNotice : Restart");
                supervisor.programRestart();
                popup_notice_main.close();
            }else if(cur_btn === qsTr("종 료")){
                supervisor.writelog("[UI] PopupNotice : Terminate");
                supervisor.programExit();
                popup_notice_main.close();
            }else if(cur_btn === qsTr("디버그모드 해제")){
                supervisor.writelog("[UI] PopupNotice : Debug Mode off");
                loadPage(pinit);
                supervisor.resetLocalization();
                supervisor.stateInit();
                popup_notice_main.close();
            }else if(cur_btn === qsTr("건너뛰기")){
                supervisor.writelog("[INIT] Debug Mode On");
                supervisor.passInit();
                loadPage(pkitchen);
                popup_notice_main.close();
            }
        }
    }

}
