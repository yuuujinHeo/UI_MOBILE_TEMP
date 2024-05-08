import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
//import QtQuick.Dialogs 1.2
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
    property bool is_rainbow: false
    property bool skip_local: false
    property var last_robot_x: supervisor.getOrigin()[0]
    property var last_robot_y: supervisor.getOrigin()[1]
    property real last_robot_th: 0
    //0 none 1 moving 2 movefail
    property bool use_callbell : true
    property int test_move_state: 0
    property bool annotation_after_mapping: false
    property bool edit_once: false
    property var page_after_localization

    property int select_location: -1
    property int select_preset: 1
    property int select_object: -1
    property bool is_object: false

    //robot state 체크할지말지
    property bool checkState: true

    property int beforeY: 0

    function setMappingFlag(){
        annotation_after_mapping = true;
        popup_loading.close();
        annot_pages.sourceComponent = page_annot_start;
    }
    onSelect_locationChanged: {
        print("select_location : ",select_location)
    }

    onSelect_objectChanged: {
        supervisor.selectObject(select_object);
        if(select_object > -1){
            annot_pages.item.setObj(true);
        }else{
            annot_pages.item.setObj(false);
        }
    }

    function setAnnotLocation(){
        annot_pages.sourceComponent = page_annot_location;
    }

    function setobjcur(num){
        select_object= num;
    }

    function key_event(key){
        annot_pages.item.key_event(key);
    }

    function init(){
        supervisor.stopBGM();
    }



    function movestart(){
        popup_loading.close();
        var location_name = supervisor.getcurLoc();
        if(location_name === "Charging0"){
            location_name = qsTr("충전위치");
        }else if(location_name === "Resting0"){
            location_name = qsTr("대기위치");
        }else if(location_name === "Cleaning0"){
            location_name = qsTr("퇴식위치");
        }
        popup_moving.location = location_name;
        popup_moving.open();
    }

    function movedone(){
        popup_moving.close();
        popup_notice.close();
    }

    function set_call_done(){
        readSetting();
    }

    Component.onCompleted: {
        if(annotation_after_mapping){
            annot_pages.sourceComponent = page_annot_start;
        }else{
            if(supervisor.getLocalizationState() === 2){
                annot_pages.sourceComponent = page_annot_menu;
            }else{
                page_after_localization = page_annot_menu;
                annot_pages.sourceComponent = page_annot_localization;
            }
        }
    }
    Component.onDestruction: {
        popup_notice.close();
    }

    ListModel{
        id: details
    }
    ListModel{
        id: locations
    }
    ListModel{
        id: groups
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
        if(supervisor.getSetting("setting","ROBOT_TYPE","type") === "CLEANING" && supervisor.getLocationNum("Cleaning") > 0){
            for(var i=0; i<supervisor.getLocationNum("Serving"); i++){
                locations.append({"name": supervisor.getLocationName(i,"Serving"),
                               "group":supervisor.getLocationGroupNum(i),
                                "call_id" : supervisor.getLocationCallID(3+i),
                                "ling_id" : supervisor.getLocationLingID(3+i),
                                 "callerror":false,
                                 "nameerror":false,
                               "error":false});
            }
        }else{
            for(var i=0; i<supervisor.getLocationNum("Serving"); i++){
                locations.append({"name": supervisor.getLocationName(i,"Serving"),
                               "group":supervisor.getLocationGroupNum(i),
                                "call_id" : supervisor.getLocationCallID(2+i),
                                "ling_id" : supervisor.getLocationLingID(2+i),
                                     "callerror":false,
                                     "nameerror":false,
                               "error":false});
            }
        }
        update();
    }

    function update(){
        if(popup_location.mode == "callbell"){
            popup_location.close();
        }

        details.clear();
        print("READ SETTING!!!!!!!!!!!!!!!!!!!!!!");
        details.append({"ltype":"Charging",
                           "name":qsTr("충전위치"),
                           "group":0,
                           "callerror":false,
                           "nameerror":false,
                           "call_id":supervisor.getLocationCallID(0),
                            "ling_id":supervisor.getLocationLingID(0)});
        details.append({"ltype":"Resting",
                           "name":qsTr("대기위치"),
                           "group":0,
                           "callerror":false,
                           "nameerror":false,
                           "call_id":supervisor.getLocationCallID(1),
                           "ling_id":supervisor.getLocationLingID(1)});
        if(supervisor.getRobotType()==="CLEANING"){
            if(supervisor.getLocationNum("Cleaning") > 0){
                details.append({"ltype":"Cleaning",
                                   "name":qsTr("퇴식위치"),
                                   "group":0,
                                   "callerror":false,
                                   "nameerror":false,
                                   "call_id":supervisor.getLocationCallID(2),
                                   "ling_id":supervisor.getLocationLingID(2)});
            }else{
                details.append({"ltype":"Cleaning",
                                   "name":qsTr("퇴식위치"),
                                   "group":0,
                                   "callerror":false,
                                   "nameerror":false,
                                   "call_id":"",
                                   "ling_id":""});
            }

        }
        print("locations count = ",locations.count);
        for(var i=0; i<locations.count; i++){
            print("locations append = ",i,locations.count);
            details.append({"ltype":"Serving",
                            "name":locations.get(i).name,
                           "group":locations.get(i).group,
                            "call_id":locations.get(i).call_id,
                            "ling_id":locations.get(i).ling_id,
                           "callerror":locations.get(i).callerror,
                               "nameerror":locations.get(i).nameerror});
//                        print("detail append : ",i, locations.get(i).group, locations.get(i).number, getgroupsize(locations.get(i).group))
        }
//                print("=================================");
        checkLocationNumber();
        checkLocationName();
//                print("=================================");

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
                if(details.get(i).group === details.get(j).group)
                    if(details.get(i).name === details.get(j).name){
                        details.get(i).nameerror = true;
                        details.get(j).nameerror = true;
                    }
            }
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

    Loader{
        id: annot_pages
        width: 1280
        height: 800 - statusbar.height
        anchors.bottom: parent.bottom
        clip: true
        sourceComponent: page_annot_start
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
            function checkError(){

            }
            Component.onCompleted: {
                supervisor.setMotorLock(true);
                annotation_after_mapping = false;
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
                                        click_sound.play();
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
                                        click_sound.play();
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
                anchors.topMargin: 80
                spacing: 50
                horizontalItemAlignment: Grid.AlignHCenter
                verticalItemAlignment: Grid.AlignVCenter
                rows: 2
                columns: 3
                Button_menu{
                    id: btn_location11
                    style: "navy"
                    text: qsTr("위치 수정")
                    source: "icon/icon_location.png"
                    onClicked: {
                        supervisor.writelog("[ANNOTATION] MENU : Change Location");
                        if(supervisor.isDebugMode()){//Um..Pass
                            annot_pages.sourceComponent = page_annot_location_serving_done;
                        }else{
                            if(supervisor.getIPCConnection()){//Good
                                annot_pages.sourceComponent = page_annot_location_serving_done;
                            }else{//Nope
                                openNotice("ipc_discon")
                            }
                        }
                    }
                }
                Button_menu{
                    style: "navy"
                    source: "icon/icon_pen.png"
                    text: qsTr("맵 세부수정")
                    onClicked: {
                        supervisor.writelog("[ANNOTATION] Enter : Map Editor");
                        annot_pages.sourceComponent = page_annot_map_editor2;
                    }
                }
                Button_menu{
                    style: "navy"
                    source: "icon/icon_pen.png"
                    text: qsTr("맵 세부수정\n(디버깅)")
                    visible: supervisor.isDebugMode()
                    onClicked: {
                        supervisor.writelog("[ANNOTATION] Enter : Map Editor");
                        annot_pages.sourceComponent = page_annot_map_editor3;
                    }
                }
            }

            Buttons{
                style: "dark"
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                anchors.bottomMargin: 120
                anchors.rightMargin: 50
                text: {
                    if(supervisor.getSetting("setting","USE_SLAM","use_multirobot")==="true"){
                        qsTr("맵 보내기/가져오기")
                    }else{
                        qsTr("맵 불러오기")
                    }
                }
                onClicked: {
                    supervisor.writelog("[ANNOTATION] Load Map");

                    if(supervisor.getSetting("setting","USE_SLAM","use_multirobot")==="true"){
                        popup_ask_mapload.open();
                    }else{
                        popup_map_list.open();
                    }
                }
            }
            Buttons{
                style: "dark"
                text: qsTr("종 료")
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                anchors.bottomMargin: 50
                anchors.rightMargin: 50
                onClicked: {
                    supervisor.writelog("[ANNOTATION] All Done");
                    loadPage(pmenu);
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
            function checkError(){

            }
            Component.onCompleted: {
                supervisor.writelog("[UI] PageAnnot : page_annot_start (rotate, cut map) ");
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
                    if(annotation_after_mapping){
                        supervisor.writelog("[UI] PageAnnot : set Map Orin (annotation_after_mapping) ");
                        supervisor.setMapOrin("RAW");
                    }else{
                        supervisor.writelog("[UI] PageAnnot : set Map Edited ");
                        supervisor.setMapOrin("EDITED");
                    }
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

            Image{
                source: "icon/btn_reset.png"
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: map.left
                anchors.rightMargin: 30
                anchors.verticalCenterOffset: -50
                width: 80
                height: 80
                sourceSize.width: width
                sourceSize.height: height
                Text{
                    anchors.centerIn: parent
                    text: "1"
                    font.pixelSize: 20
                    font.family: font_noto_r.name
                    color: "white"
                }
                MouseArea{
                    anchors.fill: parent
                    onPressed: {
                        click_sound.play();
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
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: map.right
                anchors.leftMargin: 30+80
                anchors.verticalCenterOffset: -50
                transform: Scale{xScale:-1}
                Text{
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: parent.width/2+width/2
                    text: "1"
                    font.pixelSize: 20
                    transform: Scale{xScale:-1}
                    font.family: font_noto_r.name
                    color: "white"
                }
                MouseArea{
                    anchors.fill: parent
                    onPressed: {
                        click_sound.play();
                        timer_rotate.cw = true;
                        timer_rotate.start();
                    }
                    onReleased: {
                        timer_rotate.stop();
                    }
                }
            }

            MAP_FULL2{
                id: map
                enabled: false
                show_ratio: false
                objectName: "annot_rotate"
                width: 600
                height: width
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                anchors.topMargin: 120
                Component.onCompleted: {
                    supervisor.setMapSize(objectName,width,height);
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
                    if(map.getCutFlag() && !annotation_after_mapping){
                        popup_location.mode = "save_rotate";
                        popup_location.open();
//                        popup_save_rotate.open();
                    }else{
                        map.save("rotate");
                        if(annotation_after_mapping){
                            supervisor.writelog("[UI] PageAnnot : Save Rotate, Cut Map -> Location");
                            page_after_localization = page_annot_location;
                            annot_pages.sourceComponent = page_annot_localization;
                        }else{
                            supervisor.writelog("[UI] PageAnnot : Save Rotate, Cut Map -> Menu");
                            annot_pages.sourceComponent = page_annot_menu;
                        }
                        supervisor.slam_map_reload(supervisor.getMapname());
                    }
                }
            }
            Item_buttons{
                width: 200
                height: 100
                anchors.left: parent.left
                anchors.leftMargin: 50
                anchors.top: parent.top
                anchors.topMargin: 50
                type: "round_text"
                text: qsTr("맵\n다시그리기")
                onClicked: {
                    supervisor.writelog("[UI] PageAnnot : Mapping restart -> PageMapping");
                    loadPage(pmapping);
                }
            }
            Column{
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.bottomMargin: 50
                anchors.leftMargin: 50
                spacing: 30
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
                    text: qsTr("맵 잘라내기")
                    selected: map.tool==="cut_map"
                    onClicked: {
                        map.setTool("cut_map");
                    }
                }
                Item_buttons{
                    width: 200
                    height: 80
                    type: "round_text"
                    text: qsTr("초기화")
                    onClicked: {
                        map.clear("rotate_cut");
                    }
                }
            }

            /*
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
                                    map.setTool("move");
                                    map.save("rotate");
                                    if(annotation_after_mapping){
                                        page_after_localization = page_annot_location;
                                        annot_pages.sourceComponent = page_annot_localization;
                                    }else
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
                                btncolor: color_green
                                onClicked:{
                                    map.save("rotate");
                                    annotation_after_mapping = true;
                                    page_after_localization = page_annot_location;
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
        */
        }
    }
    Component{
        id: page_annot_localization
        Item_localization{
            function checkError(){

            }
            anchors.fill: parent
            mapping_mode: annotation_after_mapping
            auto_init: annotation_after_mapping
            onConfirmed: {
                if(annotation_after_mapping){
                    supervisor.writelog("[UI] PageAnnot : Confirm Localization (after Mapping)");
                    supervisor.confirmLocalization();
                    annot_pages.sourceComponent = page_after_localization;
                }else{
                    supervisor.writelog("[UI] PageAnnot : Confirm Localization");
                    supervisor.confirmLocalization();
                    annot_pages.sourceComponent = page_after_localization;
                }
            }
            onPassed: {
                supervisor.writelog("[UI] PageAnnot : Pass Localization");
                skip_local = true;
                annot_pages.sourceComponent = page_after_localization;
            }
            Component.onCompleted: {
                supervisor.writelog("[UI] PageAnnot : page_annot_localization");
            }
        }
    }




    Component{
        id: page_annot_location
        Item{
            width: annot_pages.width
            height: annot_pages.height
            property bool show_map: false
            Component.onCompleted: {
                supervisor.writelog("[UI] PageAnnot : page_annot_location) ");
                supervisor.setMotorLock(false);
                map_location_view.setEnable(true);
                map_location_view.setTool("move");
                map_location_view.setViewer("annot_location");
                map_location_view.show_connection = false;
                map_location_view.show_button_lidar = false;
                readSetting();
                checkLocation();
            }
            Component.onDestruction: {
                map_location_view.setEnable(false);
//                if(!annotation_after_mapping){
//                    map_location_view.save("tline");//saveTline, loadfile
//                }
            }

            function checkError(){
                checkLocation();
            }

            function checkLocation(){
                print("checkLocation ",supervisor.getLocationNum("Charging"),supervisor.getLocationNum("Resting"));
                if(supervisor.getLocationNum("Charging") === 0){
                    btn_save_charging.exist = false;
                    btn_save_charging2.exist = false;
                }else{
                    btn_save_charging.exist = true;
                    btn_save_charging2.exist = true;
                }
                if(supervisor.getLocationNum("Resting") === 0){
                    btn_save_resting.exist = false;
                    btn_save_resting2.exist = false;
                }else{
                    btn_save_resting.exist = true;
                    btn_save_resting2.exist = true;
                }
                if(supervisor.getLocationNum("Cleaning") === 0){
                    btn_save_cleaning.exist = false;
                    btn_save_cleaning2.exist = false;
                }else{
                    btn_save_cleaning.exist = true;
                    btn_save_cleaning2.exist = true;
                }
                if(supervisor.getSetting("setting","ROBOT_TYPE","type") === "CLEANING"){
                    btn_save_cleaning2.visible = true;
                    btn_save_cleaning.visible = true;
                }else{
                    btn_save_cleaning2.visible = false;
                    btn_save_cleaning.visible = false;
                }
            }

            Timer{
                running: true
                interval: 500
                onTriggered:{
                    //slam draw start
                    supervisor.drawingRunawayStart();
                }
            }
            Timer{
                running: true
                repeat: true
                interval: 500
                onTriggered:{
                    //중간에 로컬 틀어지면 localization으로
                    if(supervisor.getLocalizationState() !== 2 && !skip_local){
                        supervisor.writelog("[UI] PageAnnot : Localization Failed -> localization");
                        page_after_localization = page_annot_location;
                        annot_pages.sourceComponent = page_annot_localization;
                    }
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
                width: 550
                objectName: "location_map"
                visible: show_map
                enabled: show_map
                height: 550
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                anchors.verticalCenterOffset: 80
                Component.onCompleted: {
                    supervisor.setMapSize(objectName,width,height);
                }
            }
            Column{
                id: col
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                anchors.topMargin: statusbar.height
                Text{
                    text: qsTr("로봇을 각 위치로 이동시켜주신 후\n저장 버튼을 누르세요")
                    color: "white"
                    font.pixelSize: 40
                    horizontalAlignment: Text.AlignHCenter
                    font.family: font_noto_b.name
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                Column{
                    visible: false
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
                Buttons{
                    style: "dark"
                    active: true
                    width: 200
                    height: 80
                    im_width: 80
                    text: show_map?qsTr("맵 끄기"):qsTr("맵 표시")
                    anchors.horizontalCenter: parent.horizontalCenter
                    source: "icon/icon_map.png"
                    onClicked: {
                        if(show_map){
                            show_map = false;
                        }else{
                            show_map = true;
                        }
                    }
                }
                Buttons{
                    style: "dark"
                    active: true
                    width: 200
                    im_width: 80
                    height: 80
                    text: qsTr("목록 보기")
                    anchors.horizontalCenter: parent.horizontalCenter
                    source: "icon/icon_list.png"
                    onClicked: {
                        popup_serving_list.open();
                    }
                }
            }

            Column{
                visible: show_map
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 50
                spacing: 30
                Buttons{
                    style: "dark"
                    active: true
                    width: 230
                    height: 80
                    id: btn_save_charging
                    property bool exist: false
                    font_color: exist?"white":color_red
                    text: qsTr("충전위치로 저장")
                    anchors.horizontalCenter: parent.horizontalCenter
                    source: "icon/icon_save.png"
                    onClicked: {
                        popup_location.mode = "save";
                        popup_location.loc = "Charging";
                        popup_location.open();
                    }
                }
                Buttons{
                    style: "dark"
                    active: true
                    width: 230
                    height: 80
                    id: btn_save_resting
                    property bool exist: false
                    font_color: exist?"white":color_red
                    text: qsTr("대기위치로 저장")
                    anchors.horizontalCenter: parent.horizontalCenter
                    source: "icon/icon_save.png"
                    onClicked: {
                        popup_location.mode = "save";
                        popup_location.loc = "Resting";
                        popup_location.open();
                    }
                }
                Buttons{
                    style: "dark"
                    active: true
                    width: 230
                    height: 80
                    id: btn_save_cleaning
                    visible: false
                    property bool exist: false
                    font_color: exist?"white":color_red
                    text: qsTr("퇴식위치로 저장")
                    anchors.horizontalCenter: parent.horizontalCenter
                    source: "icon/icon_save.png"
                    onClicked: {
                        popup_location.mode = "save";
                        popup_location.loc = "Cleaning";
                        popup_location.open();
                    }
                }
                Buttons{
                    style: "dark"
                    active: true
                    width: 230
                    height: 80
                    text: qsTr("서빙위치로 저장")
                    anchors.horizontalCenter: parent.horizontalCenter
                    source: "icon/icon_save.png"
                    onClicked: {
                        popup_add_serving.open();
                    }
                }
            }

            Row{
                visible: !show_map
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 50
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.horizontalCenterOffset: -150
                spacing: 30
                Buttons{
                    style: "dark"
                    active: true
                    width: 200
                    height: 120
                    im_width: 80
                    id: btn_save_charging2
                    property bool exist: false
                    font_color: exist?"white":color_red
                    onFont_colorChanged: {
                        print("충전위치 color : ",font_color)
                    }

                    text: qsTr("충전위치로\n저 장")
                    source: "icon/icon_save.png"
                    onClicked: {
                        popup_location.mode = "save";
                        popup_location.loc = "Charging";
                        popup_location.open();
                    }
                }
                Buttons{
                    style: "dark"
                    active: true
                    width: 200
                    height: 120
                    im_width: 80
                    id: btn_save_resting2
                    property bool exist: false
                    font_color: exist?"white":color_red
                    text: qsTr("대기위치로\n저 장")
                    source: "icon/icon_save.png"
                    onClicked: {
                        popup_location.mode = "save";
                        popup_location.loc = "Resting";
                        popup_location.open();
                    }
                }
                Buttons{
                    style: "dark"
                    active: true
                    width: 200
                    height: 120
                    im_width: 80
                    id: btn_save_cleaning2
                    property bool exist: false
                    font_color: exist?"white":color_red
                    text: qsTr("퇴식위치로\n저 장")
                    source: "icon/icon_save.png"
                    onClicked: {
                        popup_location.mode = "save";
                        popup_location.loc = "Cleaning";
                        popup_location.open();
                    }
                }
                Buttons{
                    style: "dark"
                    active: true
                    width: 200
                    height: 120
                    im_width: 80
                    text: qsTr("서빙위치로\n저 장")
                    source: "icon/icon_save.png"
                    onClicked: {
                        popup_add_serving.open();
                    }
                }
            }
            Buttons{
                style: "green"
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                anchors.bottomMargin: 50
                anchors.rightMargin: 50
                text: qsTr("전부 완료했습니다")
                onClicked: {
                    if(supervisor.getLocationNum("Charging") === 0){
                        supervisor.writelog("[UI] PageAnnot : Location Add Done but Charging Location nothing");
                        popup_notice.init();
                        popup_notice.sub_str = qsTr("충전위치로 이동하신 후 저장해주세요")
                        popup_notice.main_str = qsTr("충전위치가 지정되지 않았습니다");
                        popup_notice.open();
                    }else if(supervisor.getLocationNum("Resting") === 0){
                        supervisor.writelog("[UI] PageAnnot : Location Add Done but Resting Location nothing");
                        popup_notice.init();
                        popup_notice.sub_str = qsTr("대기위치로 이동하신 후 저장해주세요")
                        popup_notice.main_str = qsTr("대기위치가 지정되지 않았습니다");
                        popup_notice.open();
                    }else if(supervisor.getLocationNum("Cleaning") === 0 && supervisor.getSetting("setting","ROBOT_TYPE","type") === "CLEANING"){
                        supervisor.writelog("[UI] PageAnnot : Location Add Done but Cleaning Location nothing");
                        popup_notice.init();
                        popup_notice.sub_str = qsTr("퇴식위치로 이동하신 후 저장해주세요")
                        popup_notice.main_str = qsTr("퇴식위치가 지정되지 않았습니다");
                        popup_notice.open();
                    }else{
                        supervisor.writelog("[UI] PageAnnot : Location Add Done -> LocationDone");
                        annot_pages.sourceComponent = page_annot_location_serving_done;
                    }
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
                    color: color_light_gray
                    Column{
                        anchors.centerIn: parent
                        spacing:10
                        Text{
                            text: qsTr("저장된 서빙위치 목록")
                            font.family: font_noto_r.name
                            font.pixelSize: 45
//                            color: "white"
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
                            height: 400
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
                color: "white"
                Row{
                    spacing:1
                    Rectangle{
                        width: 199
                        height: 50
                        color: {
                            if(supervisor.getLocationNum(ltype) === 0){
                                color_red
                            }else{
                                color_gray
                            }
                        }
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
                        color: {
                            if(supervisor.getLocationNum(ltype) === 0){
                                color_red
                            }else{
                                color_gray
                            }
                        }
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
            Component.onCompleted: {
                supervisor.setMotorLock(true);
                readSetting();
                list_location_detail.currentIndex = select_location;
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
                    //slam draw stop
                    supervisor.drawingRunawayStop();
                }
            }
            Timer{
                interval: 500
                repeat: true
                running: true
                onTriggered:{
                    if(supervisor.getLocationNum("Resting") > 0){
                        btn_cleaning.active = true;
                    }else{
                        btn_cleaning.active = false;
                    }
                    checkError();
                }
            }

            function checkError(){
                if(isError()){
                    btn_right.active = false;
                }else{
                    btn_right.active = true;
                }
            }

            Rectangle{
                anchors.fill: parent
                color: color_dark_navy
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
                page_annotation.update();
            }

            function setLocInit(){
                map_location_list.init();
                map_location_list.setCurrentLocation(select_location);
            }

            Component{
                id: detaillocCompo
                Item{
                    width: rect_list_column.width
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
                                            beforeY = list_location_detail.contentY - 55
                                            var refY = beforeY - list_location_detail.originY;
                                            var realY = Math.max(0, Math.min(refY, list_location_detail.contentHeight-list_location_detail.height))//+originY

                                            supervisor.setLocationUp(select_location);
                                            select_location--;
                                            readSetting();

                                            list_location_detail.setting = true;
                                            list_location_detail.setContentY(realY);

                                            combo_group.focus = false;
                                            tx_name.focus = false;
                                        }
                                    }else{
                                        if(select_location>2){
                                            beforeY = list_location_detail.contentY - 55
                                            var refY = beforeY - list_location_detail.originY;
                                            var realY = Math.max(0, Math.min(refY, list_location_detail.contentHeight-list_location_detail.height))//+originY

                                            print(select_location)
                                            supervisor.setLocationUp(select_location);
                                            select_location--;
                                            readSetting();
                                            print("up" ,select_location)

                                            list_location_detail.setting = true;
                                            list_location_detail.setContentY(realY);

                                            combo_group.focus = false;
                                            tx_name.focus = false;
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
                                        beforeY = list_location_detail.contentY + 55
                                        var refY = beforeY - list_location_detail.originY;
                                        var realY = Math.max(0, Math.min(refY, list_location_detail.contentHeight-list_location_detail.height))//+originY

                                        supervisor.setLocationDown(select_location);
                                        select_location++;
                                        readSetting();


                                        list_location_detail.setting = true;
                                        list_location_detail.setContentY(realY);


                                        combo_group.focus = false;
                                        tx_name.focus = false;
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
                                text: {
                                    if(supervisor.getRobotType() === "CLEANING"){
                                        if(index > 2){
                                            index-2
                                        }else{
                                            ""
                                        }
                                    }else{
                                        if(index >1 ){
                                            index-1
                                        }else{
                                            ""
                                        }
                                    }
                                }

                                font.family: font_noto_r.name
                            }
                            MouseArea{
                                anchors.fill: parent
                                onClicked:{
                                    click_sound.play();
                                    if(select_location === index){
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
                                    if(select_location === index){
                                        select_location = -1;
                                    }else{
                                        select_location = index;
                                        print("group focus select_location",index);
                                    }
                                    map_location_list.setCurrentLocation(select_location);
                                    if(currentIndex > -1){
                                        groupchange(index,currentIndex);
                                    }

                                }
                            }
                        }

                        Image{
                            id: error_loc
                            visible: supervisor.getLocationNum(ltype) === 0
                            source: "icon/icon_error.png"
                            width: 40
                            height: 38
                            sourceSize.width: width
                            sourceSize.height: height
                            anchors.verticalCenter: parent.verticalCenter
                        }
                        Image{
                            visible: nameerror && ltype ==="Serving"
                            source: "icon/icon_error.png"
                            width: 40
                            height: 38
                            sourceSize.width: width
                            sourceSize.height: height
                            anchors.verticalCenter: parent.verticalCenter
                        }
                        TextField{
                            id: tx_name
                            text: name
                            background: Rectangle{
                                color:select_location === index?color_green:"white"
                            }
                            width : ltype ==="Serving"?nameerror?205:250:error_loc.visible?250+160+5-45:250+160+5
                            height: 50
                            font.family: font_noto_r.name
                            font.pixelSize: 20
                            horizontalAlignment: Text.AlignHCenter
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

                            MouseArea{
                                anchors.fill:parent
                                onClicked: {
                                    click_sound.play();
                                    if(select_location === index){
                                        select_location = -1;
                                    }else{
                                        select_location = index;
                                    }
                                    map_location_list.setCurrentLocation(select_location);
                                }
                                onPressAndHold: {
                                    click_sound.play();
                                    if(ltype === "Serving"){
                                        keyboard.owner = tx_name;
                                        tx_name.selectAll();
//                                        if(select_location == index){
//                                            select_location = -1;
//                                        }else{
//                                            print("name focus select_location",index);
                                        select_location = index;
//                                        }
                                        map_location_list.setCurrentLocation(select_location);
                                        keyboard.open();
                                    }
                                }
                            }
                        }
                        Image{
                            visible: callerror && ltype ==="Serving"
                            source: "icon/icon_error.png"
                            width: 40
                            height: 38
                            sourceSize.width: width
                            sourceSize.height: height
                            anchors.verticalCenter: parent.verticalCenter
                        }
                        Rectangle{
                            width : callerror && ltype ==="Serving"?105:150
                            height: 50
                            color:select_location === index?color_green:"white"
                            Text{
                                anchors.centerIn: parent
                                font.family: font_noto_r.name
                                text: call_id===""?" - ":call_id
                            }
                            Image{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.right
                                anchors.leftMargin: 5
                                source: "icon/icon_callbell.png"
                                width: 35
                                height: 35
                                visible: ling_id!==""
                            }

                            MouseArea{
                                anchors.fill: parent
                                onClicked:{
                                    click_sound.play();
                                    if(select_location === index){
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
                            spacing: 20
                            Buttons{
                                style: "dark"
                                active: select_location>-1
                                text: qsTr("벨 설정")
                                source: "icon/icon_callbell.png"
                                onClicked: {
                                    if(supervisor.getSetting("setting","ROBOT_TYPE","type") === "CLEANING" && select_location === 2){
                                        if(supervisor.getLocationNum("Cleaning") > 0){
                                            if(supervisor.getSetting("setting","CALL","use_lingbell") === "true"){
                                                popup_lingbell.open();
                                            }else{
                                                popup_location.mode = "callbell"
                                                popup_location.loc = details.get(select_location).ltype;
                                                popup_location.open();
                                            }
                                        }else{
                                            click_sound_no.play();
                                        }
                                    }else{
                                        if(supervisor.getSetting("setting","CALL","use_lingbell") === "true"){
                                            popup_lingbell.open();
                                        }else{
                                            popup_location.mode = "callbell"
                                            popup_location.loc = details.get(select_location).ltype;
                                            popup_location.open();
                                        }
                                    }

                                }
                            }
                            Buttons{
                                style: "dark"
                                active: select_location>-1
                                text: qsTr("테스트 주행")
                                source: "icon/icon_testmoving.png"
                                onClicked: {
                                    if(supervisor.isRobotReady()){
                                        click_sound.play();
                                        supervisor.writelog("[ANNOTATION] TEST MOVING : "+details.get(select_location).name);
                                        supervisor.moveToServingTest(details.get(select_location).group, details.get(select_location).name);
                                        popup_loading.open();
                                    }else{
                                        click_sound_no.play();
                                        robotnotready();
                                    }
                                }
                            }
                            Buttons{
                                style: "dark"
                                active: supervisor.getSetting("setting","ROBOT_TYPE","type") === "CLEANING"?select_location>2:select_location>1
                                text: qsTr("삭제")
                                source: "icon/icon_trash_w.png"
                                onClicked: {
                                    popup_location.mode = "remove"
                                    popup_location.open();
                                }
                            }
                            Buttons{
                                style: "dark"
                                active: select_location>-1
                                text: qsTr("위치 수정")
                                source: "icon/icon_location.png"
                                onClicked: {
                                    supervisor.writelog("[ANNOTATION] Location Edit : "+details.get(select_location).name);
                                    popup_location.mode = "edit"
                                    popup_location.open();
                                }
                            }
                        }

                        MAP_FULL2{
                            id: map_location_list
                            width: 300
                            show_ratio: false
                            anchors.horizontalCenter: parent.horizontalCenter
                            height: 300
                            Component.onCompleted: {
                                supervisor.setMapSize(objectName,width,height);
                            }
                        }

                        Row{
                            anchors.horizontalCenter: parent.horizontalCenter
                            spacing: 10
                            Buttons{
                                width: 130
                                style: "dark"
                                active: true
                                text: qsTr("위치추가")
                                source: "icon/icon_add_loc.png"
                                onClicked: {
                                    supervisor.writelog("[ANNOTATION] LOCAION SAVE : Back to SaveLocation");
                                    annot_pages.sourceComponent = page_annot_location;
                                }
                            }
                            Buttons{
                                width: 130
                                style: "dark"
                                active: true
                                text: qsTr("그룹추가")
                                source: "icon/icon_add_group.png"
                                onClicked: {
                                    popup_add_location_group.open();
                                }
                            }
                            Buttons{
                                id: btn_cleaning
                                width: 130
                                style: "dark"
                                active: supervisor.getLocationNum("Resting") > 0
                                text: qsTr("퇴식모드")
                                source: "icon/icon_cleaning.png"
                                onClicked: {
                                    select_location = -1;
                                    popup_notice.init();
                                    popup_notice.main_str = qsTr("퇴식위치를 별도로 사용하십니까?")
                                    popup_notice.sub_str = qsTr("퇴식전용모드로 전환됩니다\n로봇이 테이블을 다녀온 뒤 퇴식위치로 이동하여 대기합니다 추후 세팅에서 모드를 변경하실 수 있습니다\n퇴식위치의 기본값은 대기위치와 동일합니다 변경을 원하시면 위치 수정을 해주세요")
                                    popup_notice.addButton(qsTr("퇴식모드 미사용"))
                                    popup_notice.addButton(qsTr("퇴식모드 사용"))
                                    popup_notice.open();
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

                        ListView{
                            id: list_location_detail
                            width: rect_list_column.width
                            height: 450-35
                            spacing: 5
                            clip: true
                            anchors.horizontalCenter: parent.horizontalCenter
                            delegate: detaillocCompo
                            model:details
                            addDisplaced: Transition{
                                NumberAnimation{properties:"x,y"; duration: 1}
                            }
                            property real lastOrinY:0
                            property real lastY:0
                            property real refY: 0
                            property bool setting: false

                            Component.onCompleted: {
                                print("component completed")
                            }

                            onModelChanged:{
                                print("model changed",originY,contentHeight);
                            }

                            onOriginYChanged: {
                                print("originy changed : " ,originY,contentY);
                                contentY = refY + originY;
                                update();
                            }

                            function setContentY(y){
                                print("setContentY ",contentY,y,originY)
                                refY = y;
                                lastOrinY = originY;
                                contentY = refY + originY;
                                update();
                            }
                        }
                    }
                }
            }

            Buttons{
                id: btn_right
                style: "green"
                active: false
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                anchors.bottomMargin: 50
                anchors.rightMargin: 50
                text: qsTr("저 장")
                onClicked: {
                    print("save location");
                    supervisor.saveAnnotation(supervisor.getMapname());
                    supervisor.drawingRunawayStop();
                    supervisor.writelog("[ANNOTATION] LOCAION SAVE : Check Done ");
                    if(annotation_after_mapping)
                        annot_pages.sourceComponent = page_annot_done;
                    else
                        loadPage(pmap);
//                        annot_pages.sourceComponent = page_annot_menu;
                }
            }
            Buttons{
                style: "normal"
                text: qsTr("취 소")
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                anchors.bottomMargin: 50
                anchors.rightMargin: 280
                onClicked: {
                    annot_pages.sourceComponent = page_annot_menu;
                }
            }
        }
    }
    Component{
        id: page_annot_done
        Item{
            function checkError(){

            }
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
                    supervisor.slam_map_reload(supervisor.getMapname(),1);
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
//                    supervisor.slam_map_reload(supervisor.getMapname());
                    supervisor.writelog("[ANNOTATION] Next to Additional");
                    annot_pages.sourceComponent = page_annot_menu;
                }
            }
        }
    }

    Component{
        id: page_annot_map_editor2
        Item{
            function checkError(){

            }
            width: annot_pages.width
            height: annot_pages.height
            property int select_mode: 1
            property int select_preset: 0
            property bool is_edited: false
            property bool show_tline: false
            property bool show_velmap: false
            property bool show_object: false
            property bool show_robot: false
            property bool robot_following: false
            property bool show_avoid: false
            property bool show_location: false
            property bool show_tline_menu : false
            property int select_tline_issue: -1
            property string cur_mode_str: qsTr("노이즈 제거")
            Rectangle{
                anchors.fill: parent
                color: color_dark_navy
            }
            Component.onCompleted: {
                select_preset = 0;
                popup_loading.close();
                is_edited = false;
                supervisor.setMotorLock(false);
                map.setEnable(true);
                map.clear("all");
                map.setTool("move");
                map.setViewer("annot_drawing");
                if(supervisor.isExistTravelMap(supervisor.getMapname())){
                    supervisor.writelog("[ANNOTATION] Map Editor : load map")
                }
            }
            onSelect_modeChanged: {
                print("select mode changed " , select_mode);
                map.clear("all");
                show_tline_menu =  false;
                if(select_mode === 1){
                    cur_mode_str = qsTr("노이즈 제거")
                    map.setTool("move");
                    map.setViewer("annot_drawing");
                    map.setDrawingColor(127);
                    show_avoid = false;
                    show_object = false;
                    show_tline = false;
                    show_velmap = false;
                    show_robot = false;
                    robot_following = false;
                    show_location = false;
                    slider_brush.value = 5;
                }else if(select_mode === 2){
                    cur_mode_str = qsTr("안전속도 구간")
                    map.setViewer("annot_velmap");
                    map.setTool("move");
                    map.setDrawingColor(127);
                    select_preset = 0;
                    show_avoid = false;
                    show_object = false;
                    show_tline = false;
                    show_robot = true;
                    robot_following = false;
                    show_velmap = true;
                    show_location = true;
                    slider_brush.value = 10;
                }else if(select_mode === 3){
                    cur_mode_str = qsTr("가상벽")
                    supervisor.readSetting(supervisor.getMapname());
                    map.setViewer("annot_object_png");
                    map.setTool("move");
                    select_preset = 0;
                    show_avoid = false;
                    show_object = true;
                    show_robot = true;
                    robot_following = false;
                    show_tline = false;
                    show_velmap = false;
                    show_location = true;
                    slider_brush.value = 5;
                }else if(select_mode === 4){
                    cur_mode_str = qsTr("이동경로")
                    supervisor.readSetting(supervisor.getMapname());
                    map.setViewer("annot_tline");
                    map.setTool("move");
                    select_preset = 0;
                    show_avoid = false;
                    show_object = false;
                    show_tline = true;
                    show_velmap = false;
                    show_robot = true;
                    robot_following = false;
                    show_location = true;
                    slider_brush.value = 1;
                    supervisor.checkTravelline();
                }else if(select_mode === 5){
                    cur_mode_str = qsTr("장애물 회피구역")
                    supervisor.readSetting(supervisor.getMapname());
                    map.setViewer("annot_obs_area");
                    map.setTool("move");
                    select_preset = 0;
                    show_avoid = true;
                    show_robot = false;
                    robot_following = false;
                    show_object = false;
                    show_tline = false;
                    show_location = true;
                    show_velmap = false;
                    slider_brush.value = 10;
                }
                setView();
            }

            Component.onDestruction: {
                map.setEnable(false);
            }

            function checkEdit(){
                if(is_edited){
                    return true;
                }else{
                    if(select_mode === 3){//travelline
                        if(map.getTFlag()){
                            return true;
                        }else{
                            return false;
                        }
                    }else{
                        return false;
                    }
                }

            }
            function prev_mode(){
                if(select_mode === 1){
                    select_mode = 5;
                }else{
                    select_mode--;
                }
            }
            function next_mode(){
                if(select_mode === 5){
                    select_mode = 1;
                }else{
                    select_mode++;
                }
            }
            function clear(){
                is_edited = false;
                supervisor.drawingRunawayStop();
                map.clear("all");
                map.clear("spline");
                map.clear("tline");
                map.clear("object_png");
            }
            function save(){
                is_edited = false;
                //save temp Image
                if(select_mode === 1){
                    supervisor.writelog("[ANNOTATION] Map Editor : Save Map (Noise)");
                    map.save("map_editor");
                }else if(select_mode === 2){
                    supervisor.writelog("[ANNOTATION] Map Editor : Save Map (Velocity Map)");
                    map.save("velmap");
                    supervisor.slam_map_reload(supervisor.getMapname(),1);
                }else if(select_mode === 3){
                    supervisor.writelog("[ANNOTATION] Map Editor : Save Map (Object)");
                    supervisor.setMode("annot_object_png");
                    supervisor.saveObjectPNG();
                }else if(select_mode === 4){
                    supervisor.writelog("[ANNOTATION] Map Editor : Save Map (Travelline)");
//                    supervisor.drawingRunawayStop();
                    map.save("tline");
                    supervisor.slam_map_reload(supervisor.getMapname(),1);
                    timer_check_tline.start();
                }else if(select_mode === 5){
                    supervisor.writelog("[ANNOTATION] Map Editor : Save Map (Avoid Area)");
                    supervisor.setMode("annot_obs_area");
                    supervisor.saveObsAreaPNG();
                }
                supervisor.loadFile();
            }

            function setView(){
                if(show_velmap){
                    supervisor.setVelmapView(true);
                }else{
                    supervisor.setVelmapView(false);
                }
                if(show_avoid){
                    supervisor.setAvoidmapView(true);
                }else{
                    supervisor.setAvoidmapView(false);
                }
                if(show_tline){
                    supervisor.setTlineView(true);
                }else{
                    supervisor.setTlineView(false);
                }
                if(show_object){
                    supervisor.setObjectView(true);
                }else{
                    supervisor.setObjectView(false);
                }
                supervisor.setMap();
            }

            Timer{
                id: timer_check
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

                    if(map.getTFlag()){
                        is_edited = true;
                        btn_view.enabled = false;
                        btn_draw.enabled = false;
                        btn_tline_drawing.running = true;
                        mode_rect.enabled = false;
                    }else{
                        if(btn_tline_drawing.running){
                            btn_tline_drawing.running = false;
//                            timer_check_tline.stop();
                        }
                        btn_view.enabled = true;
                        btn_draw.enabled = true;
                        mode_rect.enabled = true;
                    }

                    if(supervisor.getLocalizationState()===2){
//                        btn_tline_drawing.enabled = true;
                    }else{
                        if(map.getTFlag()){
                            supervisor.writelog("[UI] PageAnnot : Localization Failed -> Stop Travelline Drawing");
                            popup_notice.init();
                            popup_notice.main_str = qsTr("위치를 찾을 수 없습니다.")
                            popup_notice.addButton(qsTr("위치초기화"),color_green,"white")
                            popup_notice.open();
                        }
//                        btn_tline_drawing.enabled = false;
                    }
                    model_tline_error.clear();
                    for(var i=0; i<supervisor.getTravellineIssue(); i++){
                        model_tline_error.append({"group":supervisor.getTravellineIssueGroup(i),
                                                     "name":supervisor.getTravellineIssueName(i),
                                                     "is_far":supervisor.getTravellineIssueFar(i),
                                                     "is_broken":supervisor.getTravellineIssueBroken(i)});
                    }
                }
            }
            Timer{
                id: timer_check_tline
                interval: 500
                onTriggered: {
                    supervisor.checkTravelline();
                }
            }

            Popup{
                id: popup_mode_change
                width: 1280
                height: 800
                bottomPadding: 0
                topPadding: 0
                leftPadding: 0
                rightPadding: 0
                property bool mode_next: false
                background:Rectangle{
                    anchors.fill: parent
                    color: color_dark_black
                    opacity: 0.9
                }

                Rectangle{
                    width: parent.width
                    height: 350
                    anchors.centerIn: parent
                    color: color_dark_navy
                    Column{
                        anchors.fill: parent
                        Rectangle{
                            width: parent.width
                            height: 100
                            color: "transparent"
                            Row{
                                anchors.centerIn: parent
                                spacing: 10
                                Image{
                                    anchors.verticalCenter: parent.verticalCenter
                                    id: image_location
                                    width:60
                                    height:60
                                    sourceSize.width: 60
                                    sourceSize.height: 60
                                    antialiasing: true
                                    source: "icon/icon_error_w.png"
                                    ColorOverlay{
                                        anchors.fill: parent
                                        source: parent
                                        color: "white"
                                    }
                                }
                                Text{
                                    id:text_loc
                                    color: "white"
                                    anchors.verticalCenter: parent.verticalCenter
                                    font.family: font_noto_r.name
                                    font.pixelSize: 40
                                    text: qsTr("모드를 변경하시겠습니까?")
                                    Component.onCompleted: {
                                        while(width > back.width*0.7){
                                            font.pixelSize-=1
                                        }
                                    }
                                }
                            }
                        }
                        Rectangle{
                            width: parent.width
                            height: 160
                            color: "transparent"
                            Column{
                                anchors.centerIn: parent
                                spacing: 10
                                Text{
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    id:text_sub
                                    color: color_light_gray
                                    horizontalAlignment: Text.AlignHCenter
                                    font.family: font_noto_r.name
                                    font.pixelSize: 28
                                    text: qsTr("저장되지 않은 내용은 사라집니다")
                                    Component.onCompleted: {
                                        while(width > parent.width*0.9){
                                            font.pixelSize-=1
                                        }
                                    }
                                }
                            }
                        }
                        Rectangle{
                            width: parent.width
                            height: 100
                            color: "transparent"
                            Row{
                                anchors.centerIn: parent
                                spacing: 15
                                Buttons{
                                    style: "normal"
                                    text: qsTr("취소")
                                    onClicked:{
                                        popup_mode_change.close();
                                    }
                                }
                                Buttons{
                                    style: "normal"
                                    text: qsTr("저장안하고 변경")
                                    onClicked:{
                                        is_edited = false;
                                        if(popup_mode_change.mode_next){
                                            next_mode();
                                        }else{
                                            prev_mode();
                                        }
                                        popup_mode_change.close();
                                    }
                                }
                                Buttons{
                                    style: "green"
                                    text: qsTr("저장하고 변경")
                                    onClicked:{
                                        is_edited = false;
                                        save();
                                        if(popup_mode_change.mode_next){
                                            next_mode();
                                        }else{
                                            prev_mode();
                                        }
                                        popup_mode_change.close();
                                    }
                                }
                            }
                        }
                    }
                }
            }
            Row{
                Rectangle{
                    id: view_category
                    width: 180
                    color: color_dark_navy
                    height: annot_pages.height
                    Column{
                        anchors.centerIn: parent
                        spacing: 30
                        Text{
                            text: qsTr("표시 정보")
                            anchors.horizontalCenter: parent.horizontalCenter
                            font.family: font_noto_b.name
                            font.pixelSize: 30
                            color: "White"
                        }

                        Item_buttonRectIcon{
                            selected: show_velmap
                            icon: "icon/icon_slowarea.png"
                            name: qsTr("안전속도 구간")
                            onClicked: {
                                if(show_velmap){
                                    show_velmap = false;
                                }else{
                                    show_velmap = true;
                                }
                                setView();
                            }
                        }
                        Item_buttonRectIcon{
                            selected: show_object
                            icon: "icon/icon_wall.png"
                            name: qsTr("가상벽 그리기")
                            onClicked: {
                                if(show_object){
                                    show_object = false;
                                }else{
                                    show_object = true;
                                }
                                setView();
                            }
                        }
                        Item_buttonRectIcon{
                            selected: show_tline
                            icon: "icon/icon_auto_init.png"
                            name: qsTr("이동경로")
                            onClicked: {
                                if(show_tline){
                                    show_tline = false;
                                }else{
                                    show_tline = true;
                                }
                                setView();
                            }
                        }
                        Item_buttonRectIcon{
                            selected: show_avoid
                            icon: "icon/icon_avoid.png"
                            name: qsTr("장애물 회피구역")
                            Component.onCompleted: {
                                scale = 1;
                                while(width*scale > width*0.9){
                                    scale=scale-0.01;
                                }
                            }
                            onClicked: {
                                if(show_avoid){
                                    show_avoid = false;
                                }else{
                                    show_avoid = true;
                                }
                                setView();
                            }
                        }
                    }
                }
                Column{
                    Rectangle{
                        id: title_rect
                        width: annot_pages.width - view_category.width
                        height: 80
                        color: "transparent"
                        Row{
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.right: parent.right
                            anchors.rightMargin: 30
                            spacing: 24
                            Buttons{
                                style: "dark"
                                text:qsTr("초기화")
                                width: 150
                                onClicked:{
                                    supervisor.writelog("[ANNOTATION] Map Editor : Clear All");
                                    clear();
                                }
                            }
                            Buttons{
                                style: "green"
                                text:qsTr("저장")
                                width: 150
                                onClicked:{
                                    supervisor.writelog("[MAPPING] Map Editor : Save");
                                    popup_location.mode = "saveall";
                                    popup_location.open();
                                }
                            }
                            Buttons{
                                style: "dark"
                                text:qsTr("종료")
                                width: 150
                                onClicked:{
                                    supervisor.writelog("[MAPPING] Map Editor : Save and Exit");
                                    if(is_edited){
                                        popup_location.mode = "save_exit";
                                        popup_location.open();

                                    }else{
                                        supervisor.slam_map_reload(supervisor.getMapname());
                                        page_after_localization = page_annot_menu;
                                        annot_pages.sourceComponent = page_annot_localization;
                                    }
                                }
                            }
                        }
                    }
                    Row{
                        Rectangle{
                            id: menu_rect
                            width: title_rect.width - map.width
                            height: annot_pages.height - title_rect.height
                            Column{
                                Rectangle{
                                    id: mode_rect
                                    width: menu_rect.width
                                    height: 80
                                    color: color_navy
                                    enabled: true
                                    Row{
                                        anchors.fill: parent
                                        Rectangle{
                                            width: mode_rect.height
                                            height: width
                                            color: "transparent"
                                            Image{
                                                opacity: menu_rect.enabled?1:0.6
                                                anchors.centerIn:  parent
                                                fillMode: Image.PreserveAspectFit
                                                source: "icon/joy_left.png"
                                            }
                                            MouseArea{
                                                anchors.fill: parent
                                                enabled: menu_rect.enabled
                                                onClicked:{
                                                    click_sound.play();
                                                    if(checkEdit()){
                                                        popup_mode_change.open();
                                                        popup_mode_change.mode_next = false;
                                                    }else{
                                                        prev_mode();
                                                    }
                                                }
                                            }
                                        }
                                        Rectangle{
                                            width: mode_rect.width - 2*height
                                            height: mode_rect.height
                                            color: "transparent"
                                            Text{
                                                anchors.centerIn: parent
                                                font.family: font_noto_r.name
                                                font.pixelSize: 30
                                                color: "white"
                                                text: cur_mode_str
                                            }
                                        }
                                        Rectangle{
                                            width: mode_rect.height
                                            height: width
                                            color: "transparent"
                                            Image{
                                                opacity: menu_rect.enabled?1:0.6
                                                anchors.centerIn: parent
                                                fillMode: Image.PreserveAspectFit
                                                source: "icon/joy_right.png"
                                            }
                                            MouseArea{
                                                enabled: menu_rect.enabled
                                                anchors.fill: parent
                                                onClicked:{
                                                    click_sound.play();
                                                    if(checkEdit()){
                                                        popup_mode_change.open();
                                                        popup_mode_change.mode_next = true;
                                                    }else{
                                                        next_mode();
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                                Rectangle{
                                    id: menus
                                    width: menu_rect.width
                                    height: menu_rect.height - mode_rect.height
                                    color: color_light_gray
                                    Column{
                                        id: cols_menu
                                        width: menus.width * 0.8
                                        anchors.top: parent.top
                                        anchors.topMargin: 60
                                        anchors.horizontalCenter: parent.horizontalCenter
                                        spacing: 10
                                        Row{
                                            id: rect_annot_boxs
                                            anchors.horizontalCenter: parent.horizontalCenter
                                            spacing: 20
                                            Item_button{
                                                id: btn_view
                                                shadow_color: color_gray
                                                highlight: !show_tline_menu && map.tool=="move"
                                                icon: "icon/icon_move.png"
                                                overcolor: true

                                                name: qsTr("보기")
                                                MouseArea{
                                                    anchors.fill: parent
                                                    onPressed: {
                                                        click_sound.play();
                                                        parent.pressed();
                                                    }
                                                    onReleased:{
                                                        parent.released();
                                                    }
                                                    onClicked: {
                                                        show_tline_menu =  false;
                                                        supervisor.writelog("[ANNOTATION] Map Editor : Set Tool to move");
                                                        map.setTool("move");
                                                        map.clear("spline");
                                                    }
                                                }
                                            }
                                            Item_button{
                                                id: btn_draw
                                                shadow_color: color_gray
                                                highlight: map.tool !== "move" && map.tool !== "ruler"//map.tool=="draw" || map.tool=="erase" || map.tool=="straight"|| map.tool=="draw_rect"
                                                icon: "icon/icon_draw.png"
                                                name: qsTr("수정")
                                                MouseArea{
                                                    anchors.fill: parent
                                                    onPressed: {
                                                        click_sound.play();
                                                        parent.pressed();
                                                    }
                                                    onReleased:{
                                                        parent.released();
                                                    }
                                                    onClicked: {
                                                        show_tline_menu =  false;
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
                                                        }else if(select_mode === 4){
                                                            supervisor.writelog("[ANNOTATION] Map Editor : Set Tool to draw");
                                                            map.setTool("draw");
                                                            map.setDrawingColor(255);
                                                            map.setDrawingWidth(slider_brush.value);
                                                        }else if(select_mode === 5){
                                                            supervisor.writelog("[ANNOTATION] Map Editor : Set Tool to draw");
                                                            map.setTool("draw");
                                                            map.setDrawingColor(255);
                                                            map.setDrawingWidth(slider_brush.value);
                                                        }
                                                        is_edited = true;
                                                    }
                                                }
                                            }
                                            Item_button{
                                                id: btn_erase
                                                shadow_color: color_gray
                                                icon: "icon/icon_list.png"
                                                highlight: show_tline_menu
                                                name: qsTr("추가메뉴")
                                                overcolor: true
                                                MouseArea{
                                                    anchors.fill: parent
                                                    onPressed: {
                                                        click_sound.play();
                                                        parent.pressed();
                                                    }
                                                    onReleased:{
                                                        parent.released();
                                                    }
                                                    onClicked: {
                                                        supervisor.writelog("[ANNOTATION] Map Editor : Additional Menu")
                                                        map.setTool("move")
                                                        show_tline_menu =  true;
                                                    }
                                                }
                                            }
                                        }

                                        Column{
                                            spacing: 3
                                            Rectangle{
                                                width: cols_menu.width
                                                height: 60
                                                visible: map.tool !== "move" &&  map.tool !== "ruler"//map.tool === "draw" || map.tool == "straight" ||  map.tool === "draw_rect" || map.tool === "erase"
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
                                                            supervisor.writelog("[ANNOTATION] Map Editor : REDO")
                                                            map.drawing_redo();
                                                        }
                                                    }
                                                }
                                            }
                                            Rectangle{
                                                id: rect_tool
                                                width: cols_menu.width
                                                visible: map.tool !== "move" &&  map.tool !== "ruler" && select_mode !== 1
                                                height: 60
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
                                                                    source: "icon/icon_draw_free.png"
                                                                    width: 30
                                                                    height: 30
                                                                    sourceSize.width: width
                                                                    sourceSize.height: height
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
                                                                click_sound.play();
                                                                supervisor.writelog("[ANNOTATION] Map Editor : Set tool to draw");
                                                                map.clear("spline");
                                                                map.setTool("draw");
                                                                is_edited = true;
                                                                if(select_mode === 2){
                                                                    if(select_preset === 1){
                                                                        map.setDrawingColor(100);
                                                                    }else{
                                                                        map.setDrawingColor(200);
                                                                    }
                                                                }else{
                                                                    map.setDrawingColor(255);
                                                                }
                                                                map.setDrawingWidth(slider_brush.value);
                                                            }
                                                        }
                                                    }
                                                    Rectangle{
                                                        width: 100
                                                        height: 50
                                                        visible: select_mode === 2 || select_mode === 5
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
                                                                    source: "icon/icon_draw_rect.png"
                                                                    width: 30
                                                                    height: 30
                                                                    sourceSize.width: width
                                                                    sourceSize.height: height
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
                                                                click_sound.play();
                                                                is_edited = true;
                                                                if(select_mode === 2){
                                                                    if(select_preset === 1){
                                                                        map.setDrawingColor(100);
                                                                    }else{
                                                                        map.setDrawingColor(200);
                                                                    }
                                                                }else{
                                                                    map.setDrawingColor(255);
                                                                }
                                                                map.setDrawingWidth(slider_brush.value);
                                                                map.setTool("draw_rect");
                                                            }
                                                        }
                                                    }
                                                    Rectangle{
                                                        width: 100
                                                        height: 50
                                                        visible: select_mode === 3 || select_mode === 4
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
                                                                    source: "icon/icon_draw_line.png"
                                                                    width: 30
                                                                    sourceSize.width: width
                                                                    sourceSize.height: height
                                                                    height: 30
                                                                    anchors.centerIn: parent
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
                                                                click_sound.play();
                                                                is_edited = true;
                                                                supervisor.writelog("[ANNOTATION] Object : Set tool to straight")
                                                                map.setTool("straight");
                                                                map.setDrawingColor(255);
                                                                map.setDrawingWidth(slider_brush.value);
                                                            }
                                                        }
                                                    }
                                                }
                                            }

                                            Rectangle{
                                                id: rect_tool_erase
                                                width: cols_menu.width
                                                visible: map.tool !== "move" &&  map.tool !== "ruler" && select_mode !== 1
                                                height: 60
                                                color: "white"
                                                Row{
                                                    anchors.centerIn: parent
                                                    spacing: 10
                                                    Rectangle{
                                                        width: 120
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
                                                                            sourceSize.width: width
                                                                            sourceSize.height: height
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
                                                                        click_sound.play();
                                                                        is_edited = true;
                                                                        supervisor.writelog("[ANNOTATION] Map Editor : Set tool to erase");
                                                                        map.clear("spline");
                                                                        map.setDrawingWidth(slider_erase.value);
                                                                        map.setTool("erase");
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                    Rectangle{
                                                        width: 150
                                                        height: 50
                                                        color: "transparent"
                                                        visible:select_mode === 4
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
                                                                        color: map.tool === "erase2"?color_green:color_gray
                                                                        Image{
                                                                            source: "icon/icon_erase.png"
                                                                            width: 30
                                                                            height: 30
                                                                            sourceSize.width: width
                                                                            sourceSize.height: height
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
                                                                        color: map.tool === "erase2"?"black":color_gray
                                                                        text: qsTr("바탕지우개")
                                                                    }
                                                                }

                                                                MouseArea{
                                                                    anchors.fill: parent
                                                                    onClicked:{
                                                                        click_sound.play();
                                                                        is_edited = true;
                                                                        supervisor.writelog("[ANNOTATION] Map Editor : Set tool to erase2");
                                                                        map.clear("spline");
                                                                        map.setDrawingWidth(slider_erase.value);
                                                                        map.setTool("erase2");
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                            Rectangle{
                                                id: rect_drawing_noise
                                                width: cols_menu.width
                                                height: 60
                                                visible: select_mode === 1 && map.tool !== "move" && map.tool !== "ruler"
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
                                                                click_sound.play();
                                                                is_edited = true;
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
                                                                click_sound.play();
                                                                is_edited = true;
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
                                                                click_sound.play();
                                                                is_edited = true;
                                                                map.setDrawingColor(0);
                                                                map.setDrawingWidth(slider_brush.value);
                                                            }
                                                        }
                                                    }
                                                }
                                            }

                                            Rectangle{
                                                id: rect_drawing_velmap
                                                width: cols_menu.width
                                                height: 60
                                                visible: select_mode === 2 && map.tool !== "move" && map.tool !== "ruler"
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
                                                                    sourceSize.width: width
                                                                    sourceSize.height: height
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
                                                                click_sound.play();
                                                                select_preset = 1;
                                                                is_edited = true;
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
                                                                    sourceSize.width: width
                                                                    sourceSize.height: height
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
                                                                click_sound.play();
                                                                is_edited = true;
                                                                select_preset = 2;
                                                                map.setDrawingColor(200);
                                                                map.setDrawingWidth(slider_brush.value);
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                            Rectangle{
                                                id: rect_drawing_tline_spline
                                                width: cols_menu.width
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
                                                            is_edited = false;
                                                            supervisor.writelog("[ANNOTATION] Map Editor : Save dot spline");
                                                            map.save("spline");
                                                            map.setTool("draw");
                                                        }
                                                    }
                                                }
                                            }
                                            Rectangle{
                                                id: rect_brush
                                                width: cols_menu.width
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
                                                id: rect_erase
                                                width: cols_menu.width
                                                height: 60
                                                color: "white"
                                                visible: map.tool === "erase" || map.tool === "erase2"
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
                                                id: rect_tline_add_menu
                                                width: cols_menu.width
                                                height: 500
                                                color: "transparent"
                                                visible: show_tline_menu
                                                Column{
                                                    anchors.horizontalCenter: parent.horizontalCenter
                                                    spacing: 30
                                                    Row{
                                                        anchors.horizontalCenter: parent.horizontalCenter
                                                        spacing: 10
                                                        Buttons{
                                                            style: "dark"
                                                            source: "icon/icon_ruler.png"
                                                            text: qsTr("줄자")
                                                            selected: map.tool === "ruler"
                                                            onClicked:{
                                                                map.setTool("ruler");
                                                            }
                                                        }
                                                        Buttons{
                                                            id: btn_tline_check
                                                            style: "dark"
                                                            visible: select_mode === 4
                                                            image_color: "white"
                                                            source: "icon/icon_cancelpath.png"
                                                            text: qsTr("경로 검사")
                                                            onClicked:{
                                                                map.setTool("move");
                                                                select_tline_issue = -1;
                                                                timer_check_tline.start();
                                                            }
                                                        }
                                                    }
                                                    Item_buttons{
                                                        id: btn_tline_drawing
                                                        type: "start_progress"
                                                        width: 140
                                                        height: 70
                                                        visible: select_mode === 4
                                                        text: running?qsTr("경로 저장"):qsTr("경로 학습 시작")
                                                        onClicked:{
                                                            map.setTool("move");
                                                            if(running){
                                                                is_edited = false;
                                                                supervisor.writelog("[QML] MAP PAGE : SAVE TRAVELLINE ");
                                                                supervisor.drawingRunawayStop();
                                                                is_edited = false;
                                                                map.save("tline");
                                                            }else{
                                                                if(supervisor.getLocalizationState() === 2){
                                                                    is_edited = true;
                                                                    supervisor.writelog("[ANNOTATION] Travel Line : Drawing Start");
                                                                    supervisor.drawingRunawayStart();
                                                                }else{
                                                                    popup_notice.init();
                                                                    popup_notice.main_str = qsTr("위치초기화가 필요합니다");
                                                                    popup_notice.addButton(qsTr("위치초기화"),color_green,"white")
                                                                    popup_notice.open();
                                                                }
                                                            }
                                                        }
                                                    }

                                                    Flickable{
                                                        width: 350
                                                        height: 200
                                                        visible: select_mode === 4
                                                        contentHeight: colll.height
                                                        clip: true
                                                        anchors.horizontalCenter: parent.horizontalCenter
                                                        Column{
                                                            id: colll
                                                            anchors.centerIn: parent
                                                            spacing: 3
                                                            Text{
                                                                visible: model_tline_error.count === 0
                                                                anchors.horizontalCenter: parent.horizontalCenter
                                                                font.family: font_noto_r.name
                                                                font.pixelSize: 30
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
                                                                            click_sound.play();
                                                                            parent.color = color_light_gray
                                                                        }
                                                                        onReleased: {
                                                                            if(select_tline_issue === index){
                                                                                parent.color = "white";
                                                                            }else{
                                                                                click_sound.play();;
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
                                        }
                                    }
                                }
                            }

                            PageIndicator{
                                id: indicator_tt
                                count: 5
                                currentIndex: select_mode-1
                                anchors.bottom: parent.bottom
                                anchors.bottomMargin: 20
                                anchors.horizontalCenter: parent.horizontalCenter
                                delegate: Rectangle{
                                    implicitWidth: 15
                                    implicitHeight: 15
                                    radius: width
                                    color: index===select_mode-1?"#12d27c":"#525252"
                                    Behavior on color{
                                        ColorAnimation {
                                            duration: 200
                                        }
                                    }
                                }
                            }
                        }
                        MAP_FULL2{
                            id: map
                            objectName: "annot_mapeditor"
                            show_ratio: false
                            height: annot_pages.height - 100
                            width: height
                            Component.onCompleted: {
                                supervisor.setMapSize(objectName,width,height);
                            }
                        }
                    }
                }
            }
/*
            Popup{
                id: popup_save_map
                width: parent.width
                height: parent.height
                background:Rectangle{
                    anchors.fill: parent
                    color: "#282828"
                    opacity: 0.7
                }
                property bool back_page : false
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
                                text: popup_save_map.back_page?qsTr("종료"):qsTr("취소")
                                width: 180
                                height: 60
                                onClicked:{
                                    clear();
                                    popup_save_map.close();
                                    if(popup_save_map.back_page)
                                        annot_pages.sourceComponent = page_annot_menu;
                                }
                            }
                            Item_buttons{
                                type: "round_text"
                                text: qsTr("저장")
                                width: 180
                                height: 60
                                btncolor: color_green
                                onClicked:{
                                    save();
                                    if(popup_save_map.back_page){
                                        supervisor.slam_map_reload(supervisor.getMapname());
                                        page_after_localization = page_annot_menu;
                                        annot_pages.sourceComponent = page_annot_localization;
                                    }
                                    popup_save_map.close();
                                }
                            }
                        }
                    }
                }
            }
        */


        }
    }

    Component{
        id: page_annot_map_editor3
        Item{
            id: item_mm
            width: annot_pages.width
            height: annot_pages.height
            property string select_mode: "move"
            property int select_canvas: 0
            property bool is_edited: false
            property string cur_mode_str: qsTr("노이즈 제거")
            Component.onCompleted: {
                print("WHAT :LOL??????????????????????????????");
                item_keyevent.focus = true;
                readSetting();
                supervisor.setShowNode(true);
                supervisor.setShowName(true);
                supervisor.setShowEdge(true);
                supervisor.setShowLocation(false);
                supervisor.setShowAvoid(true);
                supervisor.setShowVelmap(true);
                supervisor.setShowTline(true);
                supervisor.setShowObject(true);

                //supervisor.setShowNode(true);
                //supervisor.setShowName(true);
                //supervisor.setShowEdge(true);
                //supervisor.setShowLocation(false);
                //supervisor.setShowAvoid(false);
                //supervisor.setShowVelmap(false);
                //supervisor.setShowTline(false);
                //supervisor.setShowObject(false);
                update();
            }
            Component.onDestruction: {
                print("WHAT??????????????????????????????");
                item_keyevent.focus = false;
            }

            onSelect_modeChanged: {
                print("select mode changed " , select_mode);
                map.clear("all");
                if(select_mode == "topo"){
                    supervisor.setShowNode(true);
                    supervisor.setShowEdge(true);
                    supervisor.setShowName(true);
                    supervisor.setShowLocation(false);
                }else if(select_mode == "draw"){
                    supervisor.setShowNode(false);
                    supervisor.setShowEdge(false);
                    supervisor.setShowName(false);
                    supervisor.setShowLocation(true);

                }
            }

            onSelect_canvasChanged: {
                map.clear("all");
                map.setTool("draw");
                select_preset = 0;
                if(select_canvas === 1){
                    cur_mode_str = qsTr("노이즈 제거")
                    slider_brush.value = 5;
                    supervisor.setMode("annot_drawing");
                    map.setDrawingColor(127);
                }else if(select_canvas === 2){
                    cur_mode_str = qsTr("안전속도 구간")
                    supervisor.setMode("annot_velmap");
                    slider_brush.value = 10;
                    map.setDrawingColor(100);
                }else if(select_canvas === 3){
                    cur_mode_str = qsTr("가상벽")
                    supervisor.readSetting(supervisor.getMapname());
                    supervisor.setMode("annot_object_png");
                    map.setDrawingColor(255);
                    slider_brush.value = 5;
                }else if(select_canvas === 4){
                    cur_mode_str = qsTr("이동경로")
                    supervisor.readSetting(supervisor.getMapname());
                    supervisor.setMode("annot_tline");
                    slider_brush.value = 1;
                    map.setDrawingColor(255);
                    supervisor.checkTravelline();
                }else if(select_canvas === 5){
                    cur_mode_str = qsTr("장애물 회피구역")
//                    supervisor.readSetting(supervisor.getMapname());
                    supervisor.setMode("annot_obs_area");
                    map.setDrawingColor(255);
                    slider_brush.value = 10;
                }
                map.setDrawingWidth(slider_brush.value);
                update();
            }

            Rectangle{
                anchors.fill: parent
                color: color_dark_navy
            }
            function key_event(key){
                print("KEY EVENT KEY")
                if(key === Qt.Key_N){
                    popup_add_location.open();
                }else if(key === Qt.Key_E){
                    supervisor.editNode();
                }else if(key === Qt.Key_B){
                    supervisor.addNode("","Route");
                }else if(key === Qt.Key_D){
                    supervisor.deleteNode();
                }else if(key === Qt.Key_L){
                    supervisor.linkNode();
                }else if(key === Qt.Key_X){
                    supervisor.alignNode("x");
                }else if(key === Qt.Key_Z){
                    supervisor.alignNode("y");
                }else if(key === Qt.Key_C){
                    supervisor.alignNode("th");
                }
            }

            function checkEdit(){
                if(is_edited){
                    return true;
                }else{
                    if(select_canvas === 4){//travelline
                        if(map.getTFlag()){
                            return true;
                        }else{
                            return false;
                        }
                    }else{
                        return false;
                    }
                }

            }
            function prev_mode(){
                if(select_canvas === 1){
                    select_canvas = 5;
                }else{
                    select_canvas--;
                }
            }
            function next_mode(){
                if(select_canvas === 5){
                    select_canvas = 1;
                }else{
                    select_canvas++;
                }
            }

            function save(){
                is_edited = false;
                if(select_mode == "topo"){
                    supervisor.saveTline();
                    supervisor.saveObsAreaPNG();
                    supervisor.saveNode();
                }else if(select_mode == "draw"){
                    //save temp Image
                    if(select_canvas === 1){
                        supervisor.writelog("[ANNOTATION] Map Editor : Save Map (Noise)");
                        map.save("map_editor");
                    }else if(select_canvas === 2){
                        supervisor.writelog("[ANNOTATION] Map Editor : Save Map (Velocity Map)");
                        map.save("velmap");
                        supervisor.slam_map_reload(supervisor.getMapname(),1);
                    }else if(select_canvas === 3){
                        supervisor.writelog("[ANNOTATION] Map Editor : Save Map (Object)");
                        supervisor.setMode("annot_object_png");
                        supervisor.saveObjectPNG();
                    }else if(select_canvas === 4){
                        supervisor.writelog("[ANNOTATION] Map Editor : Save Map (Travelline)");
//                        supervisor.drawingRunawayStop();
                        map.save("tline");
                        supervisor.slam_map_reload(supervisor.getMapname(),1);
                        timer_check_tline.start();
                    }else if(select_canvas === 5){
                        supervisor.writelog("[ANNOTATION] Map Editor : Save Map (Avoid Area)");
                        supervisor.setMode("annot_obs_area");
                        supervisor.saveObsAreaPNG();
                    }
                }
                supervisor.loadFile();
            }
            function clear(){
                is_edited = false;
                supervisor.drawingRunawayStop();
                map.clear("all");
                map.clear("spline");
                map.clear("tline");
                map.clear("object_png");
            }
            function update(){
                if(supervisor.getShowNode()){
                    show_node.show = true;
                }else{
                    show_node.show = false;
                }
                if(supervisor.getShowName()){
                    show_name.show = true;
                }else{
                    show_name.show = false;
                }
                if(supervisor.getShowEdge()){
                    show_edge.show = true;
                }else{
                    show_edge.show = false;
                }
                if(supervisor.getShowTline()){
                    show_tline.show = true;
                }else{
                    show_tline.show = false;
                }
                if(supervisor.getshowLocation()){
                    show_annot.show = true;
                }else{
                    show_annot.show = false;
                }
                if(supervisor.getShowAvoid()){
                    show_avoid.show = true;
                }else{
                    show_avoid.show = false;
                }
                if(supervisor.getShowVelmap()){
                    show_velmap.show = true;
                }else{
                    show_velmap.show = false;
                }
                if(supervisor.getShowObject()){
                    show_wall.show = true;
                }else{
                    show_wall.show = false;
                }
            }

            Timer{
                id: timer_check_tline
                interval: 500
                onTriggered: {
                    supervisor.checkTravelline();
                }
            }
            Timer{
                id: timer_check
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

                    if(map.getTFlag()){
                        is_edited = true;
                        btn_view.enabled = false;
                        btn_draw.enabled = false;
                        btn_tline_drawing.running = true;
                    }else{
                        if(btn_tline_drawing.running){
                            btn_tline_drawing.running = false;
//                            timer_check_tline.stop();
                        }
                        btn_view.enabled = true;
                        btn_draw.enabled = true;
                    }

                    model_tline_error.clear();
                    for(var i=0; i<supervisor.getTravellineIssue(); i++){
                        model_tline_error.append({"group":supervisor.getTravellineIssueGroup(i),
                                                     "name":supervisor.getTravellineIssueName(i),
                                                     "is_far":supervisor.getTravellineIssueFar(i),
                                                     "is_broken":supervisor.getTravellineIssueBroken(i)});
                    }
                }
            }

            Row{
                MAP_FULL2{
                    id: map
                    enabled: true
                    objectName: "annot_mapedit"
                    width: annot_pages.height
                    height: annot_pages.height
                    tool: "move"
                    show_connection: false
                    show_ratio: false
                    Component.onCompleted: {
                        setEnable(true);
                        supervisor.setMapSize(objectName,width,height);
                        map.setDrawingColor(255);
                        map.setDrawingWidth(10);
                    }
                    onClicked:{
                        item_keyevent.focus = true;
                    }
                }
                Rectangle{
                    id: rect_menus
                    width: annot_pages.width - annot_pages.height
                    height: annot_pages.height
                    color: color_light_gray
                    Column{
                        anchors.fill: parent
                        Rectangle{
                            width:parent.width
                            height: 100
                            Row{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.right: parent.right
                                anchors.rightMargin: 30
                                spacing: 30
                                Buttons{
                                    style: "green"
                                    text: "저 장"
                                    onClicked:{
                                        save();
                                        supervisor.slam_map_reload(supervisor.getMapname());
                                        page_after_localization = page_annot_menu;
                                        annot_pages.sourceComponent = page_annot_localization;
                                    }
                                }
                                Buttons{
                                    style: "dark"
                                    text: "종 료"
                                    onClicked:{
                                        supervisor.writelog("[MAPPING] Map Editor : Save and Exit");
                                        if(is_edited){
                                            popup_location.mode = "save_exit";
                                            popup_location.open();
//                                            popup_save_map.open()
//                                            popup_save_map.back_page = true;
                                        }else{
                                            supervisor.slam_map_reload(supervisor.getMapname());
                                            page_after_localization = page_annot_menu;
                                            annot_pages.sourceComponent = page_annot_localization;
                                        }
                                    }
                                }
                            }
                        }
                        Flickable{
                            width: parent.width
                            height: parent.height - 100
                            clip: true
                            contentHeight: cols_menus.height
                            Column{
                                id: cols_menus
                                spacing: 10
                                width: parent.width
                                Rectangle{
                                    width: parent.width
                                    height: 5
                                    color: color_light_gray
                                }
                                Rectangle{ // 보기
                                    width: parent.width
                                    height: 100
                                    Row{
                                        anchors.centerIn: parent
                                        spacing: 30
                                        Text{
                                            text: qsTr("보기")
                                            font.family: font_noto_b.name
                                            font.bold: true
                                            font.pixelSize: 30
                                            anchors.verticalCenter: parent.verticalCenter
                                        }
                                        Grid{
                                            columns: 4
                                            rows: 2
                                            anchors.verticalCenter: parent.verticalCenter
                                            spacing: 5
                                            horizontalItemAlignment: Grid.AlignHCenter
                                            verticalItemAlignment: Grid.AlignVCenter
                                            Button_show{
                                                id: show_node
                                                text: qsTr("노드")
                                                text_color: color_dark_navy
                                                onShowChanged:{
                                                    supervisor.setShowNode(show);
                                                    //Supervisor.setShowNode(on);
                                                }
                                            }
                                            Button_show{
                                                id: show_edge
                                                text:qsTr("엣지")
                                                text_color: color_dark_navy
                                                onShowChanged:{
                                                    supervisor.setShowEdge(show);
                                                    //Supervisor.setShowEdge(on);
                                                }
                                            }
                                            Button_show{
                                                id: show_name
                                                text: qsTr("이름")
                                                text_color: color_dark_navy
                                                onShowChanged:{
                                                    supervisor.setShowName(show);
                                                }
                                            }
                                            Button_show{
                                                id: show_avoid
                                                text: qsTr("회피구역")
                                                text_color: color_dark_navy
                                                onShowChanged:{
                                                    supervisor.setShowAvoid(show);
                                                }
                                            }
                                            Button_show{
                                                id: show_wall
                                                text: qsTr("가상벽")
                                                text_color: color_dark_navy
                                                onShowChanged:{
                                                    supervisor.setShowObject(show);
                                                }
                                            }
                                            Button_show{
                                                id: show_tline
                                                text: qsTr("경로")
                                                text_color: color_dark_navy
                                                onShowChanged:{
                                                    supervisor.setShowTline(show);
                                                }
                                            }
                                            Button_show{
                                                id: show_annot
                                                text: qsTr("위치")
                                                text_color: color_dark_navy
                                                onShowChanged:{
                                                    supervisor.setShowLocation(show);
                                                    //Supervisor.setshow
                                                }
                                            }
                                            Button_show{
                                                id: show_velmap
                                                text: qsTr("안전구역")
                                                text_color: color_dark_navy
                                                onShowChanged:{
                                                    supervisor.setShowVelmap(show);
                                                }
                                            }
                                        }
                                    }
                                }
                                Rectangle{ ////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                    width: parent.width
                                    height: 150
                                    Row{
                                        anchors.centerIn: parent
                                        spacing: 30
                                        Item_buttons{ // 보기
                                            id: btn_view
                                            width: 100
                                            height: 100
                                            use_shadow: true
                                            type: "circle_all"
                                            selected: select_mode === "move"
                                            source: "icon/icon_move.png"
                                            overColor: true
                                            text: qsTr("보기")
                                            onClicked: {
                                                supervisor.writelog("[ANNOTATION] Map Editor : Set Tool to move");
                                                map.setTool("move");
                                                select_mode = "move";
                                                map.clear("spline");
                                            }
                                        }
                                        Item_buttons{ // 위치
                                            id: btn_draw
                                            width: 100
                                            height: 100
                                            use_shadow: true
                                            type: "circle_all"
                                            selected: select_mode === "topo"
                                            source: "icon/icon_location.png"
                                            overColor: true
                                            text: qsTr("위치")
                                            onClicked: {
                                                supervisor.writelog("[ANNOTATION] Map Editor : Set Tool to topo");
                                                map.setTool("topo");
                                                select_mode = "topo";
                                                supervisor.setMode("none");
                                                supervisor.setShowNode(true);
                                                supervisor.setShowName(true);
                                                supervisor.setShowEdge(true);
                                                supervisor.setShowLocation(false); //false -> true?
                                                supervisor.setShowAvoid(true);
                                                supervisor.setShowVelmap(true);
                                                supervisor.setShowTline(true);
                                                supervisor.setShowObject(true);
                                                item_mm.update();
                                            }
                                        }
                                        Item_buttons{ // 그리기
                                            id: btn_draw2
                                            width: 100
                                            height: 100
                                            use_shadow: true
                                            type: "circle_all"
                                            selected: select_mode === "draw"
                                            source: "icon/icon_draw.png"
                                            text: qsTr("그리기")
                                            onClicked: {
                                                supervisor.writelog("[ANNOTATION] Map Editor : Set Tool to draw");
                                                map.setTool("draw");
                                                select_mode = "draw"
                                                if(select_canvas === 0)
                                                    select_canvas = 1;
                                            }
                                        }
                                        Item_buttons{ // 줄자
                                            id: btn_ruler
                                            width: 100
                                            height: 100
                                            use_shadow: true
                                            type: "circle_all"
                                            selected: select_mode === "ruler"
                                            source: "icon/icon_ruler.png"
                                            overColor: true
                                            text: qsTr("줄자")
                                            onClicked: {
                                                supervisor.writelog("[ANNOTATION] Map Editor : Set Tool to ruler");
                                                map.setTool("ruler");
                                                select_mode = "ruler"
                                            }
                                        }
                                    }
                                }
                                Rectangle{ //draw
                                    width: parent.width
                                    visible: select_mode === "draw"
                                    height: 80
                                    color: color_navy
                                    Row{
                                        anchors.fill: parent
                                        Rectangle{
                                            width: parent.height
                                            height: width
                                            color: "transparent"
                                            Image{
//                                                opacity: menu_rect.enabled?1:0.6
                                                anchors.centerIn:  parent
                                                fillMode: Image.PreserveAspectFit
                                                source: "icon/joy_left.png"
                                            }
                                            MouseArea{
                                                anchors.fill: parent
//                                                enabled: menu_rect.enabled
                                                onClicked:{
                                                    click_sound.play();
                                                    if(checkEdit()){
                                                        popup_mode_change.open();
                                                        popup_mode_change.mode_next = false;
                                                    }else{
                                                        prev_mode();
                                                    }
                                                }
                                            }
                                        }
                                        Rectangle{
                                            width: parent.width - 2*height
                                            height: parent.height
                                            color: "transparent"
                                            Text{
                                                anchors.centerIn: parent
                                                font.family: font_noto_r.name
                                                font.pixelSize: 30
                                                color: "white"
                                                text: cur_mode_str
                                            }
                                        }
                                        Rectangle{
                                            width: parent.height
                                            height: width
                                            color: "transparent"
                                            Image{
//                                                opacity: menu_rect.enabled?1:0.6
                                                anchors.centerIn: parent
                                                fillMode: Image.PreserveAspectFit
                                                source: "icon/joy_right.png"
                                            }
                                            MouseArea{
//                                                enabled: menu_rect.enabled
                                                anchors.fill: parent
                                                onClicked:{
                                                    click_sound.play();
                                                    if(checkEdit()){
                                                        popup_mode_change.open();
                                                        popup_mode_change.mode_next = true;
                                                    }else{
                                                        next_mode();
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                                Rectangle{ // select_mod:topo
                                    visible: select_mode === "topo"
                                    width: parent.width
                                    height: 400
                                    Grid{
                                        columns: 3
                                        rows: 5
                                        anchors.centerIn: parent
                                        spacing: 20
                                        Item_buttons{
                                            width: 130
                                            height: 70
                                            type: "white_btn"
                                            text: qsTr("경로추가\n[B]")
                                            onClicked: {
                                                supervisor.addNode("","Route");
                                            }
                                        }
                                        Item_buttons{
                                            width: 130
                                            height: 70
                                            type: "white_btn"
                                            text: qsTr("위치추가\n[N]")
                                            onClicked: {
                                                popup_add_location.open();
                                            }
                                        }
                                        Item_buttons{
                                            width: 130
                                            height: 70
                                            type: "white_btn"
                                            text: qsTr("가로정렬\n[Z]")
                                            onClicked: {
                                                supervisor.alignNode("y");
                                            }
                                        }
                                        Item_buttons{
                                            width: 130
                                            height: 70
                                            type: "white_btn"
                                            text: qsTr("변경\n[E]")
                                            onClicked: {
                                                supervisor.editNode();
                                            }
                                        }
                                        Item_buttons{
                                            width: 130
                                            height: 70
                                            type: "white_btn"
                                            text: qsTr("삭제\n[D]")
                                            onClicked: {
                                                supervisor.deleteNode();
                                            }
                                        }
                                        Item_buttons{
                                            width: 130
                                            height: 70
                                            type: "white_btn"
                                            text: qsTr("세로정렬\n[X]")
                                            onClicked: {
                                                supervisor.alignNode("x");
                                            }
                                        }
                                        Item_buttons{
                                            width: 130
                                            height: 70
                                            type: "white_btn"
                                            text: qsTr("링크\n[L]")
                                            onClicked: {
                                                supervisor.linkNode();
                                            }
                                        }
                                        Item_buttons{
                                            width: 130
                                            height: 70
                                            type: "white_btn"
                                            text: qsTr("이동경로 생성")
                                            onClicked: {
                                                supervisor.autoTline();
                                            }
                                        }
                                        Item_buttons{
                                            width: 130
                                            height: 70
                                            type: "white_btn"
                                            text: qsTr("방향정렬\n[C]")
                                            onClicked: {
                                                supervisor.alignNode("th");
                                            }
                                        }
                                        Item_buttons{
                                            width: 130
                                            height: 70
                                            type: "white_btn"
                                            text: qsTr("load\nannotation.ini")
                                            onClicked: {
                                                popup_location.mode = "load_annot";
                                                popup_location.open();
                                            }
                                        }
                                        Item_buttons{
                                            width: 130
                                            height: 70
                                            type: "white_btn"
                                            text: qsTr("save\nannotation.ini")
                                            onClicked: {
                                                supervisor.saveTline();
                                                supervisor.saveObsAreaPNG();
                                                supervisor.saveNode();
                                                supervisor.loadFile();
                                            }
                                        }
                                    }
                                }
                                Rectangle{ //select_mod:draw
                                    width: parent.width
                                    height: 500
                                    color: color_light_gray
                                    visible: select_mode === "draw"
                                    Column{
                                        anchors.fill: parent
                                        spacing: 5
                                        Rectangle{
                                            width: parent.width
                                            height: 60
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
                                                        supervisor.writelog("[ANNOTATION] Map Editor : REDO")
                                                        map.drawing_redo();
                                                    }
                                                }
                                            }
                                        }
                                        Rectangle{
                                            id: rect_tool
                                            width: parent.width
                                            height: 60
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
                                                                sourceSize.width: width
                                                                sourceSize.height: height
                                                                anchors.centerIn: parent
                                                            }
                                                        }
                                                        Text{
                                                            anchors.verticalCenter: parent.verticalCenter
                                                            font.family: font_noto_r.name
                                                            color: map.tool === "draw"?"black":color_gray
                                                            text: qsTr("펜")
                                                        }
                                                    }
                                                    MouseArea{
                                                        anchors.fill: parent
                                                        onClicked:{
                                                            click_sound.play();
                                                            supervisor.writelog("[ANNOTATION] Map Editor : Set tool to draw");
                                                            map.clear("spline");
                                                            map.setTool("draw");
                                                            map.setDrawingWidth(slider_brush.value);
                                                            if(select_canvas === 2){
                                                                if(select_preset === 1){
                                                                    map.setDrawingColor(100);
                                                                }else{
                                                                    map.setDrawingColor(200);
                                                                }
                                                            }else{
                                                                map.setDrawingColor(255);
                                                            }
                                                        }
                                                    }
                                                }
                                                Rectangle{
                                                    width: 100
                                                    height: 50
                                                    visible: select_canvas === 2 || select_canvas === 5
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
                                                                sourceSize.width: width
                                                                sourceSize.height: height
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
                                                            click_sound.play();
                                                            is_edited = true;
//                                                            if(select_mode === 2){
//                                                                if(select_preset === 1){
//                                                                    map.setDrawingColor(100);
//                                                                }else{
//                                                                    map.setDrawingColor(200);
//                                                                }
//                                                            }else{
//                                                                map.setDrawingColor(255);
//                                                            }
                                                            map.setDrawingWidth(slider_brush.value);
                                                            map.setTool("draw_rect");
                                                        }
                                                    }
                                                }
                                                Rectangle{
                                                    width: 100
                                                    height: 50
                                                    visible: select_canvas === 4 || select_canvas === 3
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
                                                                sourceSize.width: width
                                                                sourceSize.height: height
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
                                                            click_sound.play();
                                                            is_edited = true;
                                                            supervisor.writelog("[ANNOTATION] Object : Set tool to straight")
                                                            map.setTool("straight");
                                                            map.setDrawingColor(255);
                                                            map.setDrawingWidth(slider_brush.value);
                                                        }
                                                    }
                                                }
                                                Rectangle{
                                                    width: 120
                                                    height: 50
                                                    color: "transparent"
                                                    visible: select_canvas !== 1
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
                                                                        sourceSize.width: width
                                                                        sourceSize.height: height
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
                                                                    click_sound.play();
                                                                    is_edited = true;
                                                                    supervisor.writelog("[ANNOTATION] Map Editor : Set tool to erase");
                                                                    map.clear("spline");
                                                                    map.setDrawingWidth(slider_erase.value);
                                                                    map.setTool("erase");
                                                                }
                                                            }
                                                        }
                                                    }
                                                }

                                                Rectangle{
                                                    width: 150
                                                    height: 50
                                                    color: "transparent"
                                                    visible: select_canvas === 4
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
                                                                    color: map.tool === "erase2"?color_green:color_gray
                                                                    Image{
                                                                        source: "icon/icon_erase.png"
                                                                        width: 30
                                                                        height: 30
                                                                        sourceSize.width: width
                                                                        sourceSize.height: height
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
                                                                    color: map.tool === "erase2"?"black":color_gray
                                                                    text: qsTr("바탕지우개")
                                                                }
                                                            }

                                                            MouseArea{
                                                                anchors.fill: parent
                                                                onClicked:{
                                                                    click_sound.play();
                                                                    is_edited = true;
                                                                    supervisor.writelog("[ANNOTATION] Map Editor : Set tool to erase2");
                                                                    map.clear("spline");
                                                                    map.setDrawingWidth(slider_erase.value);
                                                                    map.setTool("erase2");
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                        Rectangle{
                                            id: rect_noise_pallete
                                            width: parent.width
                                            height: 60
                                            visible: select_canvas === 1
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
                                                            click_sound.play();
                                                            is_edited = true;
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
                                                            click_sound.play();
                                                            is_edited = true;
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
                                                            click_sound.play();
                                                            is_edited = true;
                                                            map.setDrawingColor(0);
                                                            map.setDrawingWidth(slider_brush.value);
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                        Rectangle{
                                            id: rect_velmap_pallete
                                            width: parent.width
                                            height: 60
                                            visible: select_canvas === 2
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
                                                                sourceSize.width: width
                                                                sourceSize.height: height
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
                                                            click_sound.play();
                                                            select_preset = 1;
                                                            is_edited = true;
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
                                                                sourceSize.width: width
                                                                sourceSize.height: height
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
                                                            click_sound.play();
                                                            is_edited = true;
                                                            select_preset = 2;
                                                            map.setDrawingColor(200);
                                                            map.setDrawingWidth(slider_brush.value);
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                        Rectangle{
                                            id: rect_drawing_tline_spline
                                            width: parent.width
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
                                                        is_edited = false;
                                                        supervisor.writelog("[ANNOTATION] Map Editor : Save dot spline");
                                                        map.save("spline");
                                                        map.setTool("draw");
                                                    }
                                                }
                                            }
                                        }
                                        Rectangle{
                                            id: rect_brush
                                            width: parent.width
                                            height: 60
                                            color: "white"
                                            visible: map.tool !== "erase"
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
                                            id: rect_erase
                                            width: parent.width
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
                                            id: rect_tline_add_menu
                                            width: parent.width
                                            height: 500
                                            color: "transparent"
                                            visible: select_mode === "menu"
                                            Column{
                                                anchors.horizontalCenter: parent.horizontalCenter
                                                spacing: 30
                                                Row{
                                                    anchors.horizontalCenter: parent.horizontalCenter
                                                    spacing: 10
                                                    Item_buttons{
                                                        id: btn_tline_drawing
                                                        type: "start_progress"
                                                        width: 140
                                                        height: 70
                                                        visible: select_mode === 4
                                                        text: running?qsTr("경로 저장"):qsTr("경로 학습 시작")
                                                        onClicked:{
                                                            map.setTool("move");
                                                            if(running){
                                                                is_edited = false;
                                                                supervisor.writelog("[UI] PageAnnot : Save Travelline Drawing");
                                                                supervisor.drawingRunawayStop();
                                                                is_edited = false;
                                                                map.save("tline");
                                                            }else{
                                                                if(supervisor.getLocalizationState() === 2){
                                                                    is_edited = true;
                                                                    supervisor.writelog("[UI] PageAnnot : Start Travelline Drawing");
                                                                    supervisor.drawingRunawayStart();
                                                                }else{
                                                                    popup_notice.init();
                                                                    popup_notice.main_str = qsTr("위치초기화가 필요합니다");
                                                                    popup_notice.addButton(qsTr("위치초기화"),color_green,"white")
                                                                    popup_notice.open();
                                                                }
                                                            }
                                                        }
                                                    }

                                                    Item_buttons{
                                                        id: btn_tline_check
                                                        type: "start_progress"
                                                        visible: select_mode === 4
                                                        width: 140
                                                        height: 70
                                                        text: qsTr("경로 검사")
                                                        onClicked:{
                                                            map.setTool("move");
                                                            select_tline_issue = -1;
                                                            timer_check_tline.start();
                                                        }
                                                    }
                                                }

                                                Flickable{
                                                    width: 350
                                                    height: 200
                                                    visible: select_mode === 4
                                                    contentHeight: colll.height
                                                    clip: true
                                                    anchors.horizontalCenter: parent.horizontalCenter
                                                    Column{
                                                        id: colll
                                                        anchors.centerIn: parent
                                                        spacing: 3
                                                        Text{
                                                            visible: model_tline_error.count === 0
                                                            anchors.horizontalCenter: parent.horizontalCenter
                                                            font.family: font_noto_r.name
                                                            font.pixelSize: 30
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
                                                                        click_sound.play();
                                                                        parent.color = color_light_gray
                                                                    }
                                                                    onReleased: {
                                                                        if(select_tline_issue === index){
                                                                            parent.color = "white";
                                                                        }else{
                                                                            click_sound.play();;
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
                                    }
                                }
                            }
                        }
                    }
                }
            }

            Popup{
                id: popup_mode_change
                width: 1280
                height: 800
                bottomPadding: 0
                topPadding: 0
                leftPadding: 0
                rightPadding: 0
                property bool mode_next: false
                background:Rectangle{
                    anchors.fill: parent
                    color: color_dark_black
                    opacity: 0.9
                }

                Rectangle{
                    width: parent.width
                    height: 350
                    anchors.centerIn: parent
                    color: color_dark_navy
                    Column{
                        anchors.fill: parent
                        Rectangle{
                            width: parent.width
                            height: 100
                            color: "transparent"
                            Row{
                                anchors.centerIn: parent
                                spacing: 10
                                Image{
                                    anchors.verticalCenter: parent.verticalCenter
                                    id: image_location
                                    width:60
                                    height:60
                                    sourceSize.width: 60
                                    sourceSize.height: 60
                                    antialiasing: true
                                    source: "icon/icon_error_w.png"
                                    ColorOverlay{
                                        anchors.fill: parent
                                        source: parent
                                        color: "white"
                                    }
                                }
                                Text{
                                    id:text_loc
                                    color: "white"
                                    anchors.verticalCenter: parent.verticalCenter
                                    font.family: font_noto_r.name
                                    font.pixelSize: 40
                                    text: qsTr("모드를 변경하시겠습니까?")
                                    Component.onCompleted: {
                                        while(width > back.width*0.7){
                                            font.pixelSize-=1
                                        }
                                    }
                                }
                            }
                        }
                        Rectangle{
                            width: parent.width
                            height: 160
                            color: "transparent"
                            Column{
                                anchors.centerIn: parent
                                spacing: 10
                                Text{
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    id:text_sub
                                    color: color_light_gray
                                    horizontalAlignment: Text.AlignHCenter
                                    font.family: font_noto_r.name
                                    font.pixelSize: 28
                                    text: qsTr("저장되지 않은 내용은 사라집니다")
                                    Component.onCompleted: {
                                        while(width > parent.width*0.9){
                                            font.pixelSize-=1
                                        }
                                    }
                                }
                            }
                        }
                        Rectangle{
                            width: parent.width
                            height: 100
                            color: "transparent"
                            Row{
                                anchors.centerIn: parent
                                spacing: 15
                                Buttons{
                                    style: "normal"
                                    text: qsTr("취소")
                                    onClicked:{
                                        popup_mode_change.close();
                                    }
                                }
                                Buttons{
                                    style: "normal"
                                    text: qsTr("저장안하고 변경")
                                    onClicked:{
                                        is_edited = false;
                                        if(popup_mode_change.mode_next){
                                            next_mode();
                                        }else{
                                            prev_mode();
                                        }
                                        popup_mode_change.close();
                                    }
                                }
                                Buttons{
                                    style: "green"
                                    text: qsTr("저장하고 변경")
                                    onClicked:{
                                        is_edited = false;
                                        item_mm.save();
                                        if(popup_mode_change.mode_next){
                                            next_mode();
                                        }else{
                                            prev_mode();
                                        }
                                        popup_mode_change.close();
                                    }
                                }
                            }
                        }
                    }
                }
            }
/*
            Popup{
                id: popup_save_map
                width: parent.width
                height: parent.height
                background:Rectangle{
                    anchors.fill: parent
                    color: "#282828"
                    opacity: 0.7
                }
                property bool back_page : false
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
                                text: popup_save_map.back_page?qsTr("종료"):qsTr("취소")
                                width: 180
                                height: 60
                                onClicked:{
                                    clear();
                                    popup_save_map.close();
                                    if(popup_save_map.back_page)
                                        annot_pages.sourceComponent = page_annot_menu;
                                }
                            }
                            Item_buttons{
                                type: "round_text"
                                text: qsTr("저장")
                                width: 180
                                height: 60
                                btncolor: color_green
                                onClicked:{
                                    save();
                                    if(popup_save_map.back_page){
                                        supervisor.slam_map_reload(supervisor.getMapname());
                                        page_after_localization = page_annot_menu;
                                        annot_pages.sourceComponent = page_annot_localization;
                                    }
                                    popup_save_map.close();
                                }
                            }
                        }
                    }

                }
            }
*/
            Popup{
                id: popup_add_location
                anchors.centerIn: parent
                width: 550
                height: 450
                background:Rectangle{
                    anchors.fill: parent
                    color: "transparent"
                }
                onOpened:{
                    cbox_type.currentIndex = 0;
                    cbox_group.currentIndex = 0;
                    tfield_name.text = "";
                }

                Rectangle{
                    width: parent.width
                    height: parent.height
                    radius: 20

                    Column{
                        anchors.fill: parent
                        Rectangle{
                            width: parent.width
                            height: 80
                            radius: 20
                            color: color_navy
                            Rectangle{
                                width: parent.width
                                height: 20
                                color: color_navy
                                anchors.bottom: parent.bottom
                            }
                            Text{
                                anchors.centerIn: parent
                                text: qsTr("추가할 위치의 정보를 입력해주세요")
                                font.family: font_noto_r.name
                                font.pixelSize: 30
                                color: "white"
                            }
                        }
                        Rectangle{
                            width: parent.width
                            height: parent.height - 180
                            color: "transparent"
                            Grid{
                                anchors.centerIn: parent
                                spacing: 20
                                rows:3
                                columns: 2
                                horizontalItemAlignment: Grid.AlignHCenter
                                verticalItemAlignment: Grid.AlignVCenter
                                Text{
                                    text:qsTr("타  입   : ")
                                    font.family: font_noto_r.name
                                    font.pixelSize: 22
                                }
                                ComboBox{
                                    id: cbox_type
                                    width: 300
                                    height: 50
                                    model:["Serving","Charging","Resting","Cleaning"]
                                }
                                Text{
                                    text:qsTr("그  룹   : ")
                                    font.family: font_noto_r.name
                                    font.pixelSize: 22
                                }
                                Row{
                                    spacing: 5
                                    ComboBox{
                                        id: cbox_group
                                        width: 245
                                        height: 50
                                        model:groups
                                        enabled:cbox_type.currentIndex===0
                                    }
                                    Rectangle{
                                        width: 50
                                        height: 50
                                        radius:10
                                        color: enabled?color_dark_navy:color_gray
                                        enabled:cbox_type.currentIndex===0
                                        Image{
                                            anchors.centerIn: parent
                                            width: 30
                                            height: 30
                                            sourceSize.width: width
                                            sourceSize.height: height
                                            source: "icon/icon_add.png"
                                            ColorOverlay{
                                                anchors.fill: parent
                                                source: parent
                                                color: "white"
                                            }
                                        }
                                        MouseArea{
                                            enabled: parent.enabled
                                            anchors.fill: parent
                                            onClicked:{
                                                click_sound.play();
                                                popup_add_location_group.open();
                                            }
                                        }
                                    }
                                }
                                Text{
                                    text:qsTr("이  름   : ")
                                    font.family: font_noto_r.name
                                    font.pixelSize: 22
                                }
                                Row{
                                    spacing: 5
                                    TextField{
                                        id: tfield_name
                                        width: 245
                                        height: 50
                                        enabled:cbox_type.currentIndex===0
                                        placeholderText: qsTr("(이름을 입력하세요)")
                                    }
                                    Rectangle{
                                        width: 50
                                        height: 50
                                        radius:10
                                        color: enabled?color_dark_navy:color_gray
                                        enabled:cbox_type.currentIndex===0
                                        Image{
                                            anchors.centerIn: parent
                                            width: 35
                                            height: 35
                                            sourceSize.width: width
                                            sourceSize.height: height
                                            source: "icon/icon_keyboard.png"
                                            ColorOverlay{
                                                anchors.fill: parent
                                                source: parent
                                                color: "white"
                                            }
                                        }
                                        MouseArea{
                                            enabled: parent.enabled
                                            anchors.fill: parent
                                            onClicked:{
                                                click_sound.play();
                                                keyboard.owner = tfield_name;
                                                tfield_name.selectAll();
                                                keyboard.open();
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        Rectangle{
                            width: parent.width
                            height: 100
                            color: "transparent"
                            Row{
                                anchors.centerIn: parent
                                spacing: 20
                                Item_buttons{
                                    width: 160
                                    height: 60
                                    type: "white_btn"
                                    text: qsTr("추가")
                                    onClicked:{
                                        if(supervisor.isExistNode(cbox_type.currentText)){
                                            popup_overwrite_location.open();
                                        }else{
                                            supervisor.addNode(tfield_name.text,cbox_group.currentText,cbox_type.currentText);
                                            popup_add_location.close();
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }

            Popup{
                id: popup_overwrite_location
                anchors.centerIn: parent
                width: 550
                height: 250
                background: Rectangle{
                    anchors.fill:parent
                    color: "transparent"
                }

                Rectangle{
                    width: parent.width
                    height: parent.height
                    color: color_navy
                    Column{
                        spacing: 50
                        anchors.centerIn: parent
                        Text{
                            anchors.horizontalCenter: parent.horizontalCenter
                            horizontalAlignment: Text.AlignHCenter
                            text: qsTr("이미 존재합니다.\n기존의 위치를 변경하시겠습니까?")
                            font.pixelSize: 25
                            font.family: font_noto_r.name
                            color: "white"
                        }

                        Row{
                            anchors.horizontalCenter: parent.horizontalCenter
                            spacing: 40
                            Item_buttons{
                                width: 140
                                height: 60
                                type: "round_text"
                                text: qsTr("취소")
                                onClicked: {
                                    popup_overwrite_location.close();
                                }
                            }
                            Item_buttons{
                                width: 140
                                height: 60
                                type: "round_text"
                                text: qsTr("확인")
                                onClicked: {
                                    supervisor.editNode(cbox_type.currentText);
                                    popup_add_location.close();
                                    popup_overwrite_location.close();
                                }

                            }
                        }
                    }
                }

            }
        }
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

    Timer{
        id: timer_update
        interval: 500
        running: true
        repeat: true
        onTriggered: {
            if(supervisor.getStateMoving() === 4){
                if(!robot_paused){
                    robot_paused = true;
                    supervisor.writelog("[UI] PageAnnot : Detect MovingState Paused")
                }
            }else{
                if(robot_paused){
                    robot_paused = false;
                    supervisor.writelog("[UI] PageAnnot : Detect MovingState Not Paused")
                }
                if(supervisor.getStateMoving() === 0 || supervisor.getStateMoving() === 1){
                    if(popup_moving.opened){
                        supervisor.writelog("[UI] PageAnnot : Detect MovingState Not Moving -> Close Popup Moving")
                        popup_moving.close();
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
        onOpened:{
            supervisor.playBGM();
        }

        onClosed:{
            supervisor.stopBGM();
        }

        Rectangle{
            anchors.centerIn: parent
            width: parent.width-100
            height: 400
            radius: 10
            color: "transparent"
            border.color: color_blue
            border.width: 5
            Image{
                id: image_moving
                width: 200
                height: 175
                source: "image/robot_moving.png"
                sourceSize.width: width
                sourceSize.height: height
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
                            supervisor.writelog("[ANNOTATION] Test Moving : Resume")
                            supervisor.moveResume();
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
                            supervisor.writelog("[ANNOTATION] Test Moving : Path Cancled")
                            supervisor.moveStop();
                        }
                    }
                }
            }
            MouseArea{
                anchors.fill: parent
                visible: !robot_paused
                onClicked:{
                    if(robot_paused){
                    }else{
                        click_sound.play();
                        supervisor.writelog("[USER INPUT] MOVING PAUSE 2")
                        supervisor.movePause();
                    }
                }
            }
        }
    }

    Popup{
        id: popup_add_location_group
        anchors.centerIn: parent
        width: 550
        height: 400
        background: Rectangle{
            anchors.fill:parent
            color: "transparent"
        }
        onOpened:{
            tfield_group.text = "";
        }

        Rectangle{
            width: parent.width
            height: parent.height
            Rectangle{
                width: parent.width
                height: 80
                color: color_navy
                Text{
                    anchors.centerIn: parent
                    text: qsTr("그룹 추가")
                    font.pixelSize: 35
                    font.family: font_noto_r.name
                    color: "white"
                }
            }
            Row{
                anchors.centerIn: parent
                spacing: 5
                TextField{
                    id: tfield_group
                    width:  300
                    height: 50
                    placeholderText: qsTr("(그룹명을 입력하세요)")
                    font.family: font_noto_r.name
                    horizontalAlignment: Text.AlignHCenter
                    font.pointSize: 20
                }
                Buttons{
                    style: "keyboard"
                    onClicked:{
                        click_sound.play();
                        keyboard.owner = tfield_group;
                        tfield_group.selectAll();
                        keyboard.open();
                    }
                }
            }

            Row{
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 40
                spacing: 30
                Buttons{
                    style: "normal"
                    text: qsTr("취소")
                    onClicked: {
                        popup_add_location_group.close();
                    }
                }
                Buttons{
                    style: "green"
                    text: qsTr("확인")
                    onClicked: {
                        if(tfield_group.text == ""){
                            click_sound_no.play();
                        }else if(!supervisor.checkGroupName(tfield_group.text)){
                            click_sound_no.play();
                            tfield_group.color = color_red;
                        }else{
                            supervisor.addLocationGroup(tfield_group.text);
                            supervisor.writelog("[QML] MAP PAGE : ADD LOCATION GROUP -> "+tfield_group.text);
                            update();
                            readSetting();
                            popup_add_serving.update();
                            popup_add_location_group.close();
                        }
                    }
                }
            }
        }
    }

    Popup{
        id: popup_add_serving
        property int cur_group: 0
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
            map_location.setViewer("add_serving");
            map_location.setEnable(true);
            textfield_loc_name.text = "";
        }
        onClosed:{
            map_location.setEnable(false);
        }


        function update(){
            print("popup_add_serving update")
            model_loc_group.clear();
            if(supervisor.getLocationGroupNum() === 0){
                model_loc_group.append({"name":"Default"});
            }else{
                for(var i=0; i<supervisor.getLocationGroupNum(); i++){
                    model_loc_group.append({"name":supervisor.getLocGroupname(i)});
                }
            }

        }
        Rectangle{
            anchors.centerIn: parent
            width: 1280
            height: 700
            color: color_dark_navy
            Column{
                Rectangle{
                    color: "transparent"
                    width: 1280
                    height: 100
                    Row{
                        anchors.centerIn: parent
                        spacing: 20
                        Image{
                            source: "icon/icon_add_loc.png"
                            width: 45
                            height: 45
                            sourceSize.width: 45
                            sourceSize.height: 45
                            anchors.verticalCenter: parent.verticalCenter
                        }
                        Text{
                            text: qsTr("서빙위치를 추가합니다")
                            font.pixelSize: 45
                            anchors.verticalCenter: parent.verticalCenter
                            color: "white"
                            horizontalAlignment: Text.AlignHCenter
                            font.family: font_noto_r.name
                        }
                    }
                }
                Rectangle{
                    color: color_navy
                    width: 1280
                    height: 500
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            color: "transparent"
                            width: 600
                            height: 500
                            MAP_FULL2{
                                id: map_location
                                width: 460
                                objectName: "annot_add_Serving"
                                height: 460
                                enabled: popup_add_serving.opened
                                anchors.centerIn: parent
                                show_button_following: false
                                show_button_lidar: false
                                show_button_location: false
                                show_connection: false
                                show_ratio: false
                                Component.onCompleted: {
                                    supervisor.setMapSize(objectName,width,height);
                                }
                            }
                        }
                        Rectangle{
                            color: "transparent"
                            width: parent.width - 600
                            height: 500

                            Column{
                                spacing: 70
                                anchors.verticalCenter: parent.verticalCenter
                                Column{
                                    spacing : 20
                                    Rectangle{
                                        width: row_name.width
                                        height: 60
                                        color: "transparent"
                                        Text{
                                            anchors.left: parent.left
                                            text: qsTr("위치 이름")
                                            anchors.verticalCenter: parent.verticalCenter
                                            font.pixelSize: 40
                                            color: "white"
                                            horizontalAlignment: Text.AlignHCenter
                                            font.family: font_noto_r.name
                                        }
                                        Buttons{
                                            anchors.right: parent.right
                                            anchors.verticalCenter: parent.verticalCenter
                                            style: "dark_navy"
                                            width: 120
                                            text: qsTr("임의생성")
                                            onClicked:{
                                                click_sound.play();
                                                textfield_loc_name.text = supervisor.getNewServingName(popup_add_serving.cur_group);
                                            }
                                        }
                                    }

                                    Row{
                                        id: row_name
                                        spacing: 10
                                        TextField{
                                            id: textfield_loc_name
                                            width: 400
                                            height: 60
                                            placeholderText: qsTr("(이름을 입력하세요)")
                                            font.family: font_noto_r.name
                                            horizontalAlignment: Text.AlignHCenter
                                            font.pointSize: 23
                                        }
                                        Buttons{
                                            style:"keyboard_dark"
                                            anchors.verticalCenter: parent.verticalCenter
                                            onClicked:{
                                                click_sound.play();
                                                keyboard.owner = textfield_loc_name;
                                                textfield_loc_name.selectAll();
                                                keyboard.open();
                                            }
                                        }
                                    }
                                    Text{
                                        id: text_loc_check
                                        anchors.horizontalCenter: parent.horizontalCenter
                                        text: qsTr("")
                                        font.pixelSize: 30
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
                                    Flickable{
                                        width: 500
                                        height:100
                                        clip: true
                                        contentWidth: row_group.width
                                        Rectangle{
                                            anchors.fill: parent
                                            color: color_dark_navy
                                        }

                                        Row{
                                            id: row_group
                                            spacing: 20
                                            Item_buttons{
                                                width: 70
                                                height: 70
                                                type: "round_text"
                                                text:  "+"
                                                btncolor: "black"
                                                onClicked:{
                                                    popup_add_location_group.open();
                                                }
                                            }
                                            Repeater{
                                                model:ListModel{id:model_loc_group}
                                                Item_buttons{
                                                    width: 120
                                                    height: 70
                                                    selected:popup_add_serving.cur_group === index
                                                    type: "round_text"
                                                    text: name
                                                    onClicked: {
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
                }
                Rectangle{
                    color: "transparent"
                    width: 1280
                    height: 100
                    Row{
                        anchors.centerIn: parent
                        spacing: 50
                        Buttons{
                            style: "normal"
                            text: qsTr("취소")
                            onClicked: {
                                popup_add_serving.close();
                            }
                        }
                        Buttons{
                            style: "green"
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
                                    supervisor.writelog("[UI] PageAnnot : Location Save Serving "+Number(supervisor.getlastRobotx())+", "+Number(supervisor.getlastRoboty())+", "+Number(supervisor.getlastRobotth()));

                                    last_robot_x = supervisor.getlastRobotx();
                                    last_robot_y = supervisor.getlastRoboty();
                                    last_robot_th = supervisor.getlastRobotth();
                                    supervisor.addLocation(last_robot_x,last_robot_y,last_robot_th);
                                    supervisor.saveLocation("Serving",popup_add_serving.cur_group, textfield_loc_name.text);
                                    supervisor.writelog("[ANNOTATION] LOCAION SAVE : Serving -> "+popup_add_serving.cur_group+", "+textfield_loc_name.text);
                                    supervisor.writelog("[ANNOTATION] LOCAION SAVE : Serving "+Number(supervisor.getlastRobotx())+", "+Number(supervisor.getlastRoboty())+", "+Number(supervisor.getlastRobotth()));
                                    popup_add_serving.close();
                                }
                                readSetting();
                            }
                        }
                    }
                }
            }
        }
    }

    Popup{
        id: popup_lingbell
        width: 1280
        height:800
        bottomPadding: 0
        topPadding: 0
        leftPadding: 0
        rightPadding: 0
        background:Rectangle{
            anchors.fill: parent
            color: color_dark_black
            opacity: 0.9
        }
        property bool ask_mode: true
        onOpened:{
            ask_mode = true;
        }
        onClosed:{

            print("------------------------------");
            readSetting();
        }

        Rectangle{
            width: parent.width
            height: 360
            anchors.centerIn: parent
            color: color_dark_navy
            Column{
                anchors.fill: parent
                Rectangle{
                    width: parent.width
                    height: 100
                    color: "transparent"
                    Row{
                        anchors.centerIn: parent
                        spacing: 10
                        Image{
                            anchors.verticalCenter: parent.verticalCenter
                            id: image_location2
                            width:60
                            height:60
                            sourceSize.width: 60
                            sourceSize.height: 60
                            antialiasing: true
                            source: "icon/icon_callbell.png"
                            ColorOverlay{
                                anchors.fill: parent
                                source: parent
                                color: "white"
                            }
                        }
                        Text{
                            id:text_loc2
                            color: "white"
                            anchors.verticalCenter: parent.verticalCenter
                            font.family: font_noto_r.name
                            font.pixelSize: 40
                            text: qsTr("모드를 선택해주세요")
                            Component.onCompleted: {
                                while(width > back.width*0.7){
                                    font.pixelSize-=1
                                }
                            }
                        }
                    }
                }
                Rectangle{
                    width: parent.width
                    height: 160
                    color: "transparent"
                    Column{
                        anchors.centerIn: parent
                        spacing: 10
                        visible: !popup_lingbell.ask_mode
                        Text{
                            anchors.horizontalCenter: parent.horizontalCenter
                            id:text_sub2
                            color: color_light_gray
                            horizontalAlignment: Text.AlignHCenter
                            font.family: font_noto_r.name
                            font.pixelSize: 28
                            text: qsTr("")
                            Component.onCompleted: {
                                while(width > parent.width*0.9){
                                    font.pixelSize-=1
                                }
                            }
                        }
                        TextField{
                            id: field_lingbell_callnum
                            anchors.horizontalCenter: parent.horizontalCenter
                            font.family: font_noto_r.name
                            horizontalAlignment: Text.AlignHCenter
                            font.pixelSize: 28
                            text: "FF22EEDD"
                            width: 300
                            height: 50
                        }
                    }
                }
                Rectangle{
                    width: parent.width
                    height: 100
                    color: "transparent"
                    Row{
                        anchors.centerIn: parent
                        spacing: 15
                        visible: popup_lingbell.ask_mode
                        Buttons{
                            id: btn_callbell
                            style: "normal"
                            text: qsTr("호출벨")
                            onClicked:{
                                popup_lingbell.close();
                                popup_location.mode = "callbell"
                                popup_location.loc = details.get(select_location).ltype;
                                popup_location.open();
                            }
                        }
                        Buttons{
                            id: btn_lingbell
                            style: "normal"
                            text: qsTr("알림벨")
                            onClicked:{
                                popup_lingbell.ask_mode = false;
                                text_sub2.text = qsTr("위치 : ")+supervisor.getLocationName(select_location)
                                field_lingbell_callnum.text = supervisor.getLingbell(select_location);
                            }
                        }
                        Buttons{
                            style: "normal"
                            text: qsTr("취소")
                            onClicked:{
                                popup_lingbell.close();
                            }
                        }
                    }
                    Row{
                        anchors.centerIn: parent
                        spacing: 15
                        visible: !popup_lingbell.ask_mode
                        Buttons{
                            id: btn_exit
                            style: "normal"
                            text: qsTr("닫기")
                            onClicked:{
                                popup_lingbell.close();
                            }
                        }
                        Buttons{
                            style: "normal"
                            text: qsTr("초기화")
                            onClicked:{
                                field_lingbell_callnum.text = "";
                                supervisor.resetLingbell(select_location);
                                popup_lingbell.close();
                            }
                        }
                        Buttons{
                            id: btn_send
                            style: "green"
                            text: qsTr("설정")
                            onClicked:{
                                supervisor.callCallbell(field_lingbell_callnum.text);
                            }
                        }
                    }
                }
            }
        }
    }


    Popup{
        id: popup_location
        width: 1280
        height:800
        bottomPadding: 0
        topPadding: 0
        leftPadding: 0
        rightPadding: 0
        background:Rectangle{
            anchors.fill: parent
            color: color_dark_black
            opacity: 0.9
        }
        property string mode: "save"
        property string loc: "Charging"
        onOpened:{
            btn_cancel.text = qsTr("취소")
            btn_confirm.text = qsTr("확인")
            btn_cancel2.visible = false;
            if(mode == "save"){
                row_call_force.visible = false;
                if(loc === "Charging"){
                    text_loc.text = qsTr("충전위치");
                    image_location.source = "icon/icon_charge.png"
                    if(supervisor.getLocationNum("Charging") === 0){
                        text_sub.text = qsTr("현재위치를 충전위치로 지정하시겠습니까?");
                    }else{
                        text_sub.text = qsTr("현재위치를 충전위치로 덮어쓰시겠습니까?");
                    }
                }else if(loc === "Resting"){
                    text_loc.text = qsTr("대기위치");
                    image_location.source = "icon/icon_wait.png"
                    if(supervisor.getLocationNum("Resting") === 0){
                        text_sub.text = qsTr("현재위치를 대기위치로 지정하시겠습니까?");
                    }else{
                        text_sub.text = qsTr("현재위치를 대기위치로 덮어쓰시겠습니까?");
                    }
                }else if(loc === "Cleaning"){
                    text_loc.text = qsTr("퇴식위치");
                    image_location.source = "icon/icon_cleaning.png"
                    if(supervisor.getLocationNum("Cleaning") === 0){
                        text_sub.text = qsTr("현재위치를 퇴식위치로 지정하시겠습니까?");
                    }else{
                        text_sub.text = qsTr("현재위치를 퇴식위치로 덮어쓰시겠습니까?");
                    }
                }else{
                    text_loc.text = qsTr("error");
                    text_sub.text = qsTr("");
                }
            }else if(mode == "remove"){
                btn_confirm.text = qsTr("확인")
                row_call_force.visible = false;
                text_loc.text = qsTr("선택하신 위치를 삭제하시겠습니까?");
                image_location.source = "icon/icon_trash_w.png"
                text_sub.text = qsTr("위치 : ")+supervisor.getLocationName(select_location);
            }else if(mode == "edit"){
                btn_confirm.text = qsTr("이동완료했습니다")
                row_call_force.visible = false;
                supervisor.setMotorLock(false);
                if(select_location == 0){
                    image_location.source = "icon/icon_charge.png"
                    text_loc.text = qsTr("수정하실 충전위치로 로봇을 이동시켜 주세요")
                    text_sub.text = ""
                }else if(select_location == 1){
                    image_location.source = "icon/icon_wait.png"
                    text_loc.text = qsTr("수정하실 대기위치로 로봇을 이동시켜 주세요")
                    text_sub.text = ""
                }else{
                    if(supervisor.getRobotType()==="CLEANING"){
                        if(select_location == 2){
                            image_location.source = "icon/icon_cleaning.png"
                            text_loc.text = qsTr("수정하실 퇴식위치로 로봇을 이동시켜 주세요")
                            text_sub.text = ""
                        }else{
                            image_location.source = "icon/icon_add_loc.png"
                            text_loc.text = qsTr("수정하실 서빙위치로 로봇을 이동시켜 주세요")
                            text_sub.text = qsTr("위치이름 : ")+supervisor.getLocationName(select_location)
                        }
                    }else{
                        image_location.source = "icon/icon_add_loc.png"
                        text_loc.text = qsTr("수정하실 서빙위치로 로봇을 이동시켜 주세요")
                        text_sub.text = qsTr("위치이름 : ")+supervisor.getLocationName(select_location)
                    }
                }
            }else if(mode == "callbell"){
                btn_confirm.text = qsTr("초기화")
                image_location.source = "icon/icon_callbell.png"
                supervisor.setCallbell(loc, select_location);
                text_sub.text = qsTr("위치 : ")+supervisor.getLocationName(select_location)
                text_loc.text = qsTr("변경하실 호출벨을 눌러주세요")
                if(loc === "Resting"){
                    row_call_force.visible = true;
                    if(supervisor.getSetting("setting","CALL","force_resting") === "true"){
                        cb_callbell_force.checked = true;
                    }else{
                        cb_callbell_force.checked = false;
                    }
                }else if(loc === "Cleaning"){
                    row_call_force.visible = true;
                    if(supervisor.getSetting("setting","CALL","force_cleaning") === "true"){
                        cb_callbell_force.checked = true;
                    }else{
                        cb_callbell_force.checked = false;
                    }
                }else{
                    row_call_force.visible = false;
                }
            }else if(mode == "lingbell"){

            }else if(mode == "save_exit"){
                row_call_force.visible = false;
                image_location.source = "icon/icon_save.png"
                text_loc.text = qsTr("이대로 <font color=\"#12d27c\">저장</font>하시겠습니까?")
                text_sub.text = qsTr("기존의 파일은 삭제됩니다")
                btn_confirm.text = qsTr("저장")
                btn_cancel.text = qsTr("종료")
                btn_cancel2.visible = true;
            }else if(mode == "saveall"){
                row_call_force.visible = false;
                image_location.source = "icon/icon_save.png"
                text_loc.text = qsTr("이대로 <font color=\"#12d27c\">저장</font>하시겠습니까?")
                text_sub.text = qsTr("기존의 파일은 삭제됩니다")
                btn_confirm.text = qsTr("저장")
            }else if(mode == "save_rotate"){
                row_call_force.visible = false;
                image_location.source = "icon/icon_cut.png"
                text_loc.text = qsTr("맵을 <font color=\"#12d27c\">잘라내기</font>하시겠습니까?")
                text_sub.text = qsTr("맵을 자르면 기존의 설정은 모두 삭제되며 새로 설정하셔야 합니다")
            }else if(mode == "load_annot"){
                row_call_force.visible = false;
                image_location.source = "icon/icon_bookmark.png"
                text_loc.text = qsTr("annotation.ini에 지정된 노드를 불러오시겠습니까?")
                text_sub.text = qsTr("기존에 지정하셨던 노드와 엣지는 <font color=\"#12d27c\">모두 삭제</font>되며 새로 지정하셔야 합니다")
                btn_confirm.text = qsTr("불러오기")
            }
        }

        onClosed:{
            if(mode == "edit"){
                supervisor.setMotorLock(true);
            }else if(mode == "callbell"){
                supervisor.setCallbell("", -1);
                supervisor.setCallbellForce(loc,cb_callbell_force.checked);
            }
        }

        Rectangle{
            id: back
            width: parent.width
            height: 360
            anchors.centerIn: parent
            color: color_dark_navy
            Column{
                anchors.fill: parent
                Rectangle{
                    width: parent.width
                    height: 100
                    color: "transparent"
                    Row{
                        anchors.centerIn: parent
                        spacing: 10
                        Image{
                            anchors.verticalCenter: parent.verticalCenter
                            id: image_location
                            width:60
                            height:60
                            sourceSize.width: 60
                            sourceSize.height: 60
                            antialiasing: true
                            source: "icon/icon_charge.png"
                            ColorOverlay{
                                anchors.fill: parent
                                source: parent
                                color: "white"
                            }
                        }
                        Text{
                            id:text_loc
                            color: "white"
                            anchors.verticalCenter: parent.verticalCenter
                            font.family: font_noto_r.name
                            font.pixelSize: 40
                            text: qsTr("충전위치")
                            Component.onCompleted: {
                                while(width > back.width*0.7){
                                    font.pixelSize-=1
                                }
                            }
                        }
                    }
                }
                Rectangle{
                    width: parent.width
                    height: 160
                    color: "transparent"
                    Column{
                        anchors.centerIn: parent
                        spacing: 10
                        Text{
                            anchors.horizontalCenter: parent.horizontalCenter
                            id:text_sub
                            color: color_light_gray
                            horizontalAlignment: Text.AlignHCenter
                            font.family: font_noto_r.name
                            font.pixelSize: 28
                            text: qsTr("현재위치를 충전위치로 지정하시겠습니까?")
                            Component.onCompleted: {
                                while(width > parent.width*0.9){
                                    font.pixelSize-=1
                                }
                            }
                        }
                        Row{
                            id: row_call_force
                            anchors.horizontalCenter: parent.horizontalCenter
                            spacing: 30
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
                                font.pixelSize: 28
                            }
                        }
                    }

                }
                Rectangle{
                    width: parent.width
                    height: 100
                    color: "transparent"
                    Row{
                        anchors.centerIn: parent
                        spacing: 15
                        Buttons{
                            id: btn_cancel2
                            style: "normal"
                            visible: false
                            text: qsTr("취소")
                            onClicked:{
                                popup_location.close();
                            }
                        }
                        Buttons{
                            id: btn_cancel
                            style: "normal"
                            text: qsTr("취소")
                            onClicked:{
                                if(popup_location.mode == "save_exit"){
                                    annot_pages.sourceComponent = page_annot_menu;
                                }else if(popup_location.mode == "save_rotate"){
                                    map.setTool("move");
                                    map.save("rotate");
                                    if(annotation_after_mapping){
                                        page_after_localization = page_annot_location;
                                        annot_pages.sourceComponent = page_annot_localization;
                                    }else
                                        annot_pages.sourceComponent = page_annot_menu;
                                    supervisor.slam_map_reload(supervisor.getMapname());
                                }
                                popup_location.close();
                            }
                        }
                        Buttons{
                            id: btn_confirm
                            style: "green"
                            text: qsTr("확인")
                            onClicked:{
                                if(popup_location.mode == "save"){
                                    if(popup_location.loc === "Charging"){
                                        supervisor.writelog("[UI] PageAnnot : Location Save Charging "+Number(supervisor.getlastRobotx())+", "+Number(supervisor.getlastRoboty())+", "+Number(supervisor.getlastRobotth()));
                                        last_robot_x = supervisor.getlastRobotx();
                                        last_robot_y = supervisor.getlastRoboty();
                                        last_robot_th = supervisor.getlastRobotth();
                                        supervisor.addLocation(last_robot_x,last_robot_y,last_robot_th);
                                        supervisor.saveLocation("Charging", 0, "Charging0");
                                    }else if(popup_location.loc === "Resting"){
                                        supervisor.writelog("[UI] PageAnnot : Location Save Resting "+Number(supervisor.getlastRobotx())+", "+Number(supervisor.getlastRoboty())+", "+Number(supervisor.getlastRobotth()));
                                        last_robot_x = supervisor.getlastRobotx();
                                        last_robot_y = supervisor.getlastRoboty();
                                        last_robot_th = supervisor.getlastRobotth();
                                        supervisor.addLocation(last_robot_x,last_robot_y,last_robot_th);
                                        supervisor.saveLocation("Resting", 0, "Resting0");
                                    }else if(popup_location.loc === "Cleaning"){
                                        supervisor.writelog("[UI] PageAnnot : Location Save Cleaning "+Number(supervisor.getlastRobotx())+", "+Number(supervisor.getlastRoboty())+", "+Number(supervisor.getlastRobotth()));
                                        last_robot_x = supervisor.getlastRobotx();
                                        last_robot_y = supervisor.getlastRoboty();
                                        last_robot_th = supervisor.getlastRobotth();
                                        supervisor.addLocation(last_robot_x,last_robot_y,last_robot_th);
                                        supervisor.saveLocation("Cleaning", 0, "Cleaning0");
                                    }
                                    annot_pages.item.checkLocation();
                                    readSetting();
                                    popup_location.close();
                                }else if(popup_location.mode == "remove"){
                                    supervisor.removeLocation(select_location);
                                    select_location = -1;
                                    readSetting();
                                    popup_location.close();
                                }else if(popup_location.mode == "edit"){
                                    supervisor.editLocation(select_location);
                                    annot_pages.item.setLocInit();
                                    popup_location.close();
                                }else if(popup_location.mode == "callbell"){
                                    supervisor.clear_call();
                                    popup_location.close();
                                }else if(popup_location.mode == "saveall"){
                                    annot_pages.item.save();
                                    popup_location.close();
                                }else if(popup_location.mode == "save_exit"){
                                    annot_pages.item.save();
                                    supervisor.slam_map_reload(supervisor.getMapname());
                                    page_after_localization = page_annot_menu;
                                    annot_pages.sourceComponent = page_annot_localization;
                                    popup_location.close();
                                }else if(popup_location.mode == "save_rotate"){
                                    map.save("rotate");
                                    annotation_after_mapping = true;
                                    page_after_localization = page_annot_location;
                                    annot_pages.sourceComponent = page_annot_localization;
                                    supervisor.deleteAnnotation();
                                    supervisor.slam_map_reload(supervisor.getMapname());
                                    popup_location.close();
                                }else if(popup_location.mode == "load_annot"){
                                    supervisor.loadAnnotation();
                                    popup_location.close();
                                }
                            }
                        }
                    }
                }
            }
        }
    }


    Popup_help{
        id: popup_annot_help
    }
}
