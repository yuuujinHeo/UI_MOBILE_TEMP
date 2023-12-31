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
    property bool skip_local: false
    property var last_robot_x: supervisor.getOrigin()[0]
    property var last_robot_y: supervisor.getOrigin()[1]
    property var last_robot_th: 0
    //0 none 1 moving 2 movefail
    property bool use_callbell : true
    property var test_move_state: 0
    property bool annotation_after_mapping: false
    property bool edit_once: false
    property var page_after_localization

    property var select_location: -1
    property var select_preset: 0
    property var select_object: -1
    property bool is_object: false

    property var beforeY: 0
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
//        annot_pages.item.checkError();
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
        id: page_annot_notice
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
                    text:qsTr("맵 회전\n잘라내기")
                    onClicked: {
                        click_sound.play();
                        supervisor.writelog("[ANNOTATION] MENU : Rotate / Cut Map");
                        annot_pages.sourceComponent = page_annot_start;
                    }
                }
                Item_buttons{
                    id: btn_location
                    width: 220
                    height: 150
                    fontsize: 30
                    type: "round_text"
                    text: qsTr("위치 수정")
                    onClicked: {
                        click_sound.play();
                        supervisor.writelog("[ANNOTATION] MENU : Change Location");
                        annot_pages.sourceComponent = page_annot_location_serving_done;
                    }
                }
                Item_buttons{
                    width: 220
                    height: 150
                    fontsize: 30
                    type: "round_text"
                    text: qsTr("맵 세부수정")
                    onClicked: {
                        click_sound.play();
                        supervisor.writelog("[ANNOTATION] Enter : Map Editor");
                        annot_pages.sourceComponent = page_annot_map_editor2;
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

            Image{
                source: "icon/btn_reset.png"
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: map.left
                anchors.rightMargin: 30
                anchors.verticalCenterOffset: -50
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
//                    onClicked: {
//                        map.rotate("ccw");
//                    }
                    onPressed: {
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
//                        anchors.centerIn: parent
                    text: "1"
                    font.pixelSize: 20
                    transform: Scale{xScale:-1}
                    font.family: font_noto_r.name
                    color: "white"
                }
                MouseArea{
                    anchors.fill: parent
//                    onClicked: {
//                        map.rotate("cw");
//                    }
                    onPressed: {
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
                            if(annotation_after_mapping){
                                page_after_localization = page_annot_location;
                                annot_pages.sourceComponent = page_annot_localization;
                            }else{
                                annot_pages.sourceComponent = page_annot_menu;
                            }

                            supervisor.slam_map_reload(supervisor.getMapname());
                        }
                    }else{
                        map.save("rotate");
                        supervisor.writelog("[ANNOTATION] Rotate, Cut : done and save.")
                        if(annotation_after_mapping){
                            page_after_localization = page_annot_location;
                            annot_pages.sourceComponent = page_annot_localization;
                        }else{
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
                    click_sound.play();
                    supervisor.writelog("[ANNOTATION] Mapping Restart");
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
                        map.clear("rotate_cut");
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
                                    click_sound.play();
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
                    annot_pages.sourceComponent = page_after_localization;
                }else{
                    supervisor.confirmLocalization();
                    annot_pages.sourceComponent = page_after_localization;
                }
            }
            onPassed: {
                skip_local = true;
                annot_pages.sourceComponent = page_after_localization;
            }
        }
    }

    Component{
        id: page_annot_location
        Item{
            width: annot_pages.width
            height: annot_pages.height
            property bool show_map: false
//            property
            Component.onCompleted: {
                print("annot location completed!!!!!!!!!!!!!!!!!!!!!!");
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
                if(!annotation_after_mapping){
//                    supervisor.stopDrawingTline();
                    map_location_view.save("tline");
                }
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
                print("checkLocation")
            }

            Timer{
                running: true
                interval: 500
                onTriggered:{
                    supervisor.drawingRunawayStart();
//                    supervisor.startDrawingTline();
                }
            }
            Timer{
                running: true
                repeat: true
                interval: 500
                onTriggered:{
                    if(supervisor.getLocalizationState() !== 2 && !skip_local){
                        supervisor.writelog("[ANNOTATION] LOCALIZATION FAILED : Move to Page Localization");
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

            Column{
                visible: show_map
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 15
                spacing: 30
                Item_buttons{
                    id: btn_save_charging
                    property bool exist: false
                    fontcolor: exist?"white":color_red
                    width: 200
                    height: 120

                    type: "round_text"
                    text: qsTr("충전위치로\n저 장")
                    onClicked: {
                        click_sound.play();
                        supervisor.writelog("[ANNOTATION] LOCAION SAVE : Charging "+Number(supervisor.getlastRobotx())+", "+Number(supervisor.getlastRoboty())+", "+Number(supervisor.getlastRobotth()));
                        popup_save_location.loc = "Charging";
                        popup_save_location.open();
                    }
                }
                Item_buttons{
                    id: btn_save_resting
                    property bool exist: false
                    fontcolor: exist?"white":color_red
                    width: 200
                    height: 120
                    type: "round_text"
                    text: qsTr("대기위치로\n저 장")
                    onClicked: {
                        click_sound.play();
                        supervisor.writelog("[ANNOTATION] LOCAION SAVE : Resting "+Number(supervisor.getlastRobotx())+", "+Number(supervisor.getlastRoboty())+", "+Number(supervisor.getlastRobotth()));
                        popup_save_location.loc = "Resting";
                        popup_save_location.open();
                    }
                }
                Item_buttons{
                    id: btn_save_cleaning
                    property bool exist: false
                    visible: false
                    fontcolor: exist?"white":color_red
                    width: 200
                    height: 120
                    type: "round_text"
                    text: qsTr("퇴식위치로\n저 장")
                    onClicked: {
                        click_sound.play();
                        supervisor.writelog("[ANNOTATION] LOCAION SAVE : Cleaning "+Number(supervisor.getlastRobotx())+", "+Number(supervisor.getlastRoboty())+", "+Number(supervisor.getlastRobotth()));
                        popup_save_location.loc = "Cleaning";
                        popup_save_location.open();
                    }
                }
                Item_buttons{
                    width: 200
                    height: 120
                    type: "round_text"
                    text: qsTr("서빙위치로\n저 장")
                    onClicked: {
                        click_sound.play();
                        supervisor.writelog("[ANNOTATION] LOCAION SAVE : Serving "+Number(supervisor.getlastRobotx())+", "+Number(supervisor.getlastRoboty())+", "+Number(supervisor.getlastRobotth()));
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
                Item_buttons{
                    id: btn_save_charging2
                    property bool exist: false
                    fontcolor: exist?"white":color_red
                    width: 200
                    height: 120

                    type: "round_text"
                    text: qsTr("충전위치로\n저 장")
                    onClicked: {
                        click_sound.play();
                        supervisor.writelog("[ANNOTATION] LOCAION SAVE : Charging "+Number(supervisor.getlastRobotx())+", "+Number(supervisor.getlastRoboty())+", "+Number(supervisor.getlastRobotth()));
                        popup_save_location.loc = "Charging";
                        popup_save_location.open();
                    }
                }
                Item_buttons{
                    id: btn_save_resting2
                    property bool exist: false
                    fontcolor: exist?"white":color_red
                    width: 200
                    height: 120
                    type: "round_text"
                    text: qsTr("대기위치로\n저 장")
                    onClicked: {
                        click_sound.play();
                        supervisor.writelog("[ANNOTATION] LOCAION SAVE : Resting "+Number(supervisor.getlastRobotx())+", "+Number(supervisor.getlastRoboty())+", "+Number(supervisor.getlastRobotth()));
                        popup_save_location.loc = "Resting";
                        popup_save_location.open();
                    }
                }
                Item_buttons{
                    id: btn_save_cleaning2
                    property bool exist: false
                    fontcolor: exist?"white":color_red
                    width: 200
                    height: 120
                    visible: false
                    type: "round_text"
                    text: qsTr("퇴식위치로\n저 장")
                    onClicked: {
                        click_sound.play();
                        supervisor.writelog("[ANNOTATION] LOCAION SAVE : Cleaning "+Number(supervisor.getlastRobotx())+", "+Number(supervisor.getlastRoboty())+", "+Number(supervisor.getlastRobotth()));
                        popup_save_location.loc = "Cleaning";
                        popup_save_location.open();
                    }
                }
                Item_buttons{
                    width: 200
                    height: 120
                    type: "round_text"
                    text: qsTr("서빙위치로\n저 장")
                    onClicked: {
                        click_sound.play();
                        supervisor.writelog("[ANNOTATION] LOCAION SAVE : Serving "+Number(supervisor.getlastRobotx())+", "+Number(supervisor.getlastRoboty())+", "+Number(supervisor.getlastRobotth()));
                        popup_add_serving.open();
                    }
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
                    if(supervisor.getLocationNum("Charging") === 0){
                        popup_notice.open();
                        popup_notice.show_localization = false
                        popup_notice.show_motorinit = false;
                        popup_notice.show_restart = false;
                        popup_notice.sub_str = ""
                        popup_notice.main_str = qsTr("충전위치가 지정되지 않았습니다");
                    }else if(supervisor.getLocationNum("Resting") === 0){
                        popup_notice.open();
                        popup_notice.show_localization = false
                        popup_notice.show_motorinit = false;
                        popup_notice.show_restart = false;
                        popup_notice.sub_str = ""
                        popup_notice.main_str = qsTr("대기위치가 지정되지 않았습니다");
                    }else if(supervisor.getLocationNum("Cleaning") === 0 && supervisor.getSetting("setting","ROBOT_TYPE","type") === "CLEANING"){
                        popup_notice.open();
                        popup_notice.show_localization = false
                        popup_notice.show_motorinit = false;
                        popup_notice.show_restart = false;
                        popup_notice.sub_str = ""
                        popup_notice.main_str = qsTr("퇴식위치가 지정되지 않았습니다");
                    }else{
                        annot_pages.sourceComponent = page_annot_location_serving_done;
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
                                        Flickable{
                                            width: 400
                                            height:100
                                            clip: true
                                            contentWidth: row_group.width
                                            Row{
                                                id: row_group
                                                spacing: 20
//                                                anchors.verticalCenter: parent.verticalCenter
                                                Item_buttons{
                                                    width: 70
                                                    height: 70
                                                    type: "round_text"
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
                                        readSetting();
                                    }
                                }
                            }
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
                id: popup_save_location
                width: 1280
                height:300
                anchors.centerIn: parent
                background:Rectangle{
                    anchors.fill: parent
                    color: "transparent"
                }
                property string loc: "Charging"
                onOpened:{
                    if(loc === "Charging"){
                        if(supervisor.getLocationNum("Charging") === 0){
                            text_loc_save.text = qsTr("현재위치를 충전위치로 지정하시겠습니까?");
                        }else{
                            text_loc_save.text = qsTr("현재위치를 충전위치로 덮어쓰시겠습니까?");
                        }
                    }else if(loc === "Resting"){
                        if(supervisor.getLocationNum("Resting") === 0){
                            text_loc_save.text = qsTr("현재위치를 대기위치로 지정하시겠습니까?");
                        }else{
                            text_loc_save.text = qsTr("현재위치를 대기위치로 덮어쓰시겠습니까?");
                        }
                    }else if(loc === "Cleaning"){
                        if(supervisor.getLocationNum("Cleaning") === 0){
                            text_loc_save.text = qsTr("현재위치를 퇴식위치로 지정하시겠습니까?");
                        }else{
                            text_loc_save.text = qsTr("현재위치를 퇴식위치로 덮어쓰시겠습니까?");
                        }
                    }else{
                        text_loc_save.text = qsTr("error");
                    }
                }

                Rectangle{
                    width: parent.width
                    height: parent.height
                    color:color_navy

                    Text{
                        id: text_loc_save
                        anchors.horizontalCenter: parent.horizontalCenter
                        font.family: font_noto_r.name
                        font.pixelSize: 45
                        anchors.top: parent.top
                        anchors.topMargin: 50
                        color: "white"
                    }
                    Item_buttons{
                        type: "round_text"
                        width: 180
                        height: 80
                        text: qsTr("취소")
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: 50
                        anchors.left: parent.left
                        anchors.leftMargin: 50
                        onClicked:{
                            popup_save_location.close();
                        }
                    }
                    Item_buttons{
                        type: "round_text"
                        width: 180
                        height: 80
                        btncolor: color_green
                        text: qsTr("확인")
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: 50
                        anchors.right: parent.right
                        anchors.rightMargin: 50
                        onClicked:{
                            if(popup_save_location.loc === "Charging"){
                                last_robot_x = supervisor.getlastRobotx();
                                last_robot_y = supervisor.getlastRoboty();
                                last_robot_th = supervisor.getlastRobotth();
                                supervisor.addLocation(last_robot_x,last_robot_y,last_robot_th);
                                supervisor.saveLocation("Charging", 0, "Charging0");
                            }else if(popup_save_location.loc === "Resting"){
                                last_robot_x = supervisor.getlastRobotx();
                                last_robot_y = supervisor.getlastRoboty();
                                last_robot_th = supervisor.getlastRobotth();
                                supervisor.addLocation(last_robot_x,last_robot_y,last_robot_th);
                                supervisor.saveLocation("Resting", 0, "Resting0");
                            }else if(popup_save_location.loc === "Cleaning"){
                                last_robot_x = supervisor.getlastRobotx();
                                last_robot_y = supervisor.getlastRoboty();
                                last_robot_th = supervisor.getlastRobotth();
                                supervisor.addLocation(last_robot_x,last_robot_y,last_robot_th);
                                supervisor.saveLocation("Cleaning", 0, "Cleaning0");
                            }
                            checkLocation();
                            readSetting();
                            popup_save_location.close();
                        }
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
                    radius: 20
                    Column{
                        anchors.centerIn: parent
                        spacing:10
                        Text{
                            text: qsTr("저장된 서빙위치 목록")
                            font.family: font_noto_r.name
                            font.pixelSize: 50
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
                color: color_light_gray
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
                    supervisor.drawingRunawayStop();
//                    supervisor.draw
                }
            }
            Timer{
                interval: 500
                repeat: true
                running: true
                onTriggered:{
                    if(supervisor.getLocationNum("Resting") > 0){
                        btn_cleaning.enabled = true;
                    }else{
                        btn_cleaning.enabled = false;
                    }

                    checkError();
                }
            }

            function checkError(){
                if(isError()){
                    btn_right.enabled = false;
                }else{
                    btn_right.enabled = true;
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
                update();
            }

            function tablechange(number, table){
                    print("table change ",number,table)
                if(number > 1 && number < details.count){
                    locations.get(number-2).number = table;
                }
                update();
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
                                            beforeY = list_location_detail.contentY - 55
                                            list_location_detail.setting = true;
                                            list_location_detail.refY = beforeY - list_location_detail.originY;
                                            combo_group.focus = false;
                                            tx_name.focus = false;
                                            keyboard.close();
                                            supervisor.setLocationUp(select_location);
                                            select_location--;
                                            readSetting();
                                        }
                                    }else{
                                        if(select_location>2){
                                            beforeY = list_location_detail.contentY - 55
                                            list_location_detail.setting = true;
                                            list_location_detail.refY = beforeY - list_location_detail.originY;
                                            combo_group.focus = false;
                                            tx_name.focus = false;
                                            keyboard.close();
                                            supervisor.setLocationUp(select_location);
                                            select_location--;
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
                                        beforeY = list_location_detail.contentY + 55
                                        list_location_detail.setting = true;
                                        list_location_detail.refY = beforeY - list_location_detail.originY;
                                        combo_group.focus = false;
                                        tx_name.focus = false;
                                        keyboard.close();
                                        supervisor.setLocationDown(select_location);
                                        select_location++;
                                        readSetting();
                                        list_location_detail.contentY = beforeY - list_location_detail.originY;
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
                            id: error_loc
                            visible: supervisor.getLocationNum(ltype) === 0
                            source: "icon/icon_error.png"
                            width: 40
                            height: 38
                            anchors.verticalCenter: parent.verticalCenter
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
                                    if(select_location == index){
                                        select_location = -1;
                                    }else{
                                        select_location = index;
                                    }
                                    map_location_list.setCurrentLocation(select_location);
                                }
                                onPressAndHold: {
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
                            spacing: 20
                            Item_buttons{
                                width: 140
                                height: 70
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
                                height: 70
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
                                height: 70
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
                                height: 70
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
                            width: 300
                            show_ratio: false
                            anchors.horizontalCenter: parent.horizontalCenter
                            height: 300
                        }

                        Row{
                            anchors.horizontalCenter: parent.horizontalCenter
                            spacing: 30
                            Item_buttons{
                                width: 120
                                height: 60
                                type: "round_text"
                                text: qsTr("위치추가")
                                onClicked: {
                                    click_sound.play();
                                    supervisor.writelog("[ANNOTATION] LOCAION SAVE : Back to SaveLocation");
                                    annot_pages.sourceComponent = page_annot_location;
                                }
                            }
                            Item_buttons{
                                width: 120
                                height: 60
                                type: "round_text"
                                text: qsTr("그룹추가")
                                onClicked: {
                                    click_sound.play();
                                    popup_add_location_group.open();
                                }
                            }
                            Item_buttons{
                                id: btn_cleaning
                                width: 120
                                height: 60
                                type: "round_text"
                                enabled: supervisor.getLocationNum("Resting") > 0;
                                text: qsTr("퇴식모드")
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
                            property real lastY:0
                            property real refY: 0
                            property bool setting: false
                            onContentYChanged:{
//                                print("contenty : ",contentY, originY, contentHeight);
                                 if(!moving){
                                     if(setting){
                                         contentY = Math.max(0, Math.min(refY, contentHeight-height))+originY
                                         print("setting : " ,contentY);
                                         setting = false;
                                     }else{
                                         contentY = Math.max(0, Math.min(lastY, contentHeight-height))+originY
                                         print("no : " ,contentY);
                                     }
                                 }
                                 lastY = contentY-originY
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
//                    map_hide.stopDrawingT();
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
                        readSetting();
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
                                    supervisor.checkCleaningLocation();
                                    supervisor.setSetting("setting","ROBOT_TYPE/type","CLEANING");
                                    supervisor.readSetting();
                                    readSetting();
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
                                    readSetting();
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
                                    readSetting();
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
                    click_sound.play();
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
            property var select_mode: 1
            property var select_preset: 0
            property bool is_edited: false
            property bool show_tline: false
            property bool show_velmap: false
            property bool show_object: false
            property bool show_robot: false
            property bool robot_following: false
            property bool show_avoid: false
            property bool show_location: false
            property bool show_tline_menu : false
            property var select_tline_issue: -1
            property string cur_mode_str: qsTr("노이즈 제거")
            Rectangle{
                anchors.fill: parent
                color: color_dark_navy
            }
            Component.onCompleted: {
                loading.hide();
                select_preset = 0;
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
                map.stopDrawingT();
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
                    map.stopDrawingT();
                    map.save("tline");
                    supervisor.slam_map_reload(supervisor.getMapname(),1);
                    timer_check_tline.start();
                }else if(select_mode === 5){
                    supervisor.writelog("[ANNOTATION] Map Editor : Save Map (Avoid Area)");
                    supervisor.setMode("annot_obs_area");
                    supervisor.saveObsAreaPNG();
                }
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
//                if(show_robot){
//                    supervisor.setRobotView(true);
//                }else{
//                    supervisor.setRobotView(false);
//                }
//                if(show_location){
//                    supervisor.setLocationView(true);
//                }else{
//                    supervisor.setLocationView(false);
//                }
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

                    if(supervisor.getLocalizationState()){
//                        btn_tline_drawing.enabled = true;
                    }else{
                        if(map.getTFlag()){
                            supervisor.writelog("[ANNOTATION] Map Editor : Localization Failed -> Stop Travelline Drawing");
//                            supervisor.stopDrawingTline();
                            popup_notice.open();
                            popup_notice.main_str = qsTr("위치를 찾을 수 없습니다.")
                            popup_notice.show_localization = true;
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
                anchors.centerIn: parent
                width: 450
                height: 280
                property bool mode_next: false
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
                                text: "저장하고 변경"
                                width: 140
                                height: 60
                                btncolor: color_green
                                fontsize: 20
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
                            Item_buttons{
                                type: "round_text"
                                text: "저장안함"
                                width: 140
                                height: 60
                                fontsize: 20
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
                            text: qsTr("뷰   어")
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
                            Item_buttons{
                                type: "round_text"
                                width: 120
                                height: 60
                                text:qsTr("초기화")
                                onClicked:{
                                    click_sound.play();
                                    supervisor.writelog("[ANNOTATION] Map Editor : Clear All");
                                    clear();
                                }
                            }
                            Item_buttons{
                                type: "round_text"
                                width: 120
                                height: 60
                                text:qsTr("저장")
                                onClicked:{
                                    click_sound.play();
                                    supervisor.writelog("[MAPPING] Map Editor : Save");
                                    popup_save_map.open();
                                    popup_save_map.back_page = false;
                                }
                            }
                            Item_buttons{
                                type: "round_text"
                                width: 120
                                height: 60
                                text:qsTr("종료")
                                onClicked:{
                                    click_sound.play();
                                    supervisor.writelog("[MAPPING] Map Editor : Save and Exit");
                                    if(is_edited){
                                        popup_save_map.open()
                                        popup_save_map.back_page = true;
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
                                                highlight: map.tool=="move"
                                                icon: "icon/icon_move.png"
                                                name: qsTr("보기")
                                                MouseArea{
                                                    anchors.fill: parent
                                                    onPressed: {
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
                                                highlight: map.tool !== "move"//map.tool=="draw" || map.tool=="erase" || map.tool=="straight"|| map.tool=="draw_rect"
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
        //                                            width: 80
                                                visible: select_mode === 4
                                                shadow_color: color_gray
                                                icon: "icon/icon_bookmark.png"
                                                name: qsTr("추가메뉴")
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
                                                visible: map.tool !== "move"//map.tool === "draw" || map.tool == "straight" ||  map.tool === "draw_rect" || map.tool === "erase"
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
                                                id: rect_tool
                                                width: cols_menu.width
                                                visible: map.tool !== "move" && select_mode !== 1
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
                                                                is_edited = true;
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
                                                }
                                            }
                                            Rectangle{
                                                id: rect_drawing_noise
                                                width: cols_menu.width
                                                height: 60
                                                visible: select_mode === 1 && map.tool !== "move"
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
                                                visible: select_mode === 2 && map.tool !== "move"
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
                                                            is_edited = false;
                                                            click_sound.play();
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
                                                        Item_buttons{
                                                            id: btn_tline_drawing
                                                            type: "start_progress"
                                                            width: 150
                                                            height: 80
                                                            text: running?qsTr("경로 저장"):qsTr("경로 학습 시작")
                                                            onClicked:{
                                                                map.setTool("move");
                                                                if(running){
                                                                    click_sound.play();
                                                                    is_edited = false;
                                                                    supervisor.writelog("[QML] MAP PAGE : SAVE TRAVELLINE ");
                                                                    map.stopDrawingT();
                                                                    is_edited = false;
//                                                                    timer_check_tline.stop();
                                                                    map.save("tline");
                                                                }else{
                                                                    if(supervisor.getLocalizationState() === 2){
                                                                        click_sound.play();
                                                                        is_edited = true;
                                                                        supervisor.writelog("[ANNOTATION] Travel Line : Drawing Start");
                                                                        map.startDrawingT();
                                                                        timer_check_drawing.start();
                                                                    }else{
                                                                        popup_notice.open();
                                                                        popup_notice.main_str = qsTr("위치초기화가 필요합니다");
                                                                        popup_notice.show_localization = true;
                                                                    }

                                                                }
                                                            }
                                                        }
                                                        Item_buttons{
                                                            id: btn_tline_check
                                                            type: "start_progress"
                                                            width: 150
                                                            height: 80
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
                            width: height
                            show_ratio: false
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
                                    click_sound.play();
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
                                    click_sound.play();
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
        show_ratio: false
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

    Popup_notice{
        id: popup_notice
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
                        page_after_localization = page_annot_location_serving_done;
                        annot_pages.sourceComponent = page_annot_localization;
                        popup_moving.close();
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
                visible: false//popup_notice.show_motorinit
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
                        popup_notice.close();
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
