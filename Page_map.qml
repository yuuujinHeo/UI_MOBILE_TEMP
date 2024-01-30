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
    id: page_map
    objectName: "page_map"
    width: 1280
    height: 800
    property int width_menu: 400

    //slam
    property bool slam_initializing: false
    property bool joystick_connection: false
    property bool joy_init: false
    property var joy_axis_left_ud: 0
    property var joy_axis_right_rl: 0

    property bool edit_flag: false
    property int state_meta: 0
    property int state_annot: 0
    property int state_map: 0

    //mode : 0(mapview) 1:(slam-mapping) 2:(annotation) 3:(patrol) 4: (slam-localization)
    property int map_mode: 0

    property bool is_mapping: false
    property bool is_objecting: false

    //0: location 1: record 2: random
    property int patrol_mode: 2
    property bool recording: false

    property bool is_init_state: false
    property bool is_save_annot: false

    property var last_robot_x: supervisor.getOrigin()[0]
    property var last_robot_y: supervisor.getOrigin()[1]
    property var last_robot_th: 0

    //annotation
    property string select_object_type: "Wall"
    property string select_location_type: "Serving"
    property int select_tline_num: -1
    property int select_tline_category: -1
    property int select_patrol_num: -1
    property var select_preset: 1

    property var cur_group: 0



    function init(){
        statusbar.visible = true;
        if(supervisor.isExistAnnotation(supervisor.getMapname())){
            state_annot = 1;
        }else{
            state_annot = 0;
        }

        if(supervisor.isExistMap(supervisor.getMapname())){
            state_map = 1;
            state_meta = 1;
        }else{
            state_map = 0;
            state_meta = 0;
        }
    }

    Component.onCompleted: {
        init();
    }

    function updatepath(){
        map_current.update_path();
    }

    Rectangle{
        id: rect_menus
        width: 320
        height: parent.height - statusbar.height
        anchors.bottom: parent.bottom
        color: color_dark_navy
        Column{
            spacing: 40
            anchors.centerIn: parent
            Repeater{
                model: [qsTr("맵 새로만들기"),qsTr("현재맵 수정하기"),qsTr("위치 초기화"),qsTr("지정 순회")]
                Rectangle{
                    property int btn_size: 135
                    width: btn_size
                    height: btn_size
                    radius: btn_size
                    color: "white"
                    Rectangle{
                        id: rect_btn
                        width: btn_size
                        height: btn_size
                        radius: 13
                        color: "white"
                        Column{
                            anchors.centerIn: parent
                            spacing: 8
                            Image{
                                anchors.horizontalCenter: parent.horizontalCenter
                                width: 50
                                height: 48
                                sourceSize.width: 50
                                sourceSize.height: 48
                                source: {
                                    if(modelData == qsTr("맵 새로만들기")){
                                        "image/image_slam.png"
                                    }else if(modelData == qsTr("현재맵 수정하기")){
                                        "image/image_annot.png"
                                    }else if(modelData == qsTr("지정 순회")){
                                        "image/image_patrol.png"
                                    }else if(modelData == qsTr("위치 초기화")){
                                        "image/image_localization.png"
                                    }
                                }
                            }
                            Text{
                                anchors.horizontalCenter: parent.horizontalCenter
                                horizontalAlignment: Text.AlignHCenter
                                font.family: font_noto_r.name
                                font.pixelSize: 18
                                color: "#323744"
                                text:modelData
                            }
                        }
                    }
                    MouseArea{
                        anchors.fill: parent
                        onPressed:{
                            rect_btn.color = color_gray;
                        }
                        onReleased:{
                            click_sound.play();
                            rect_btn.color = "white";
                            if(modelData == qsTr("맵 새로만들기")){
                                supervisor.writelog("[UI] MAP : move to Mapping");
                                loadPage(pmapping);
                            }else if(modelData == qsTr("현재맵 수정하기")){
                                supervisor.writelog("[UI] MAP : move to Annotation");
                                loadPage(pannotation);
                                supervisor.setAnnotEditFlag(true);
                            }else if(modelData == qsTr("지정 순회")){
                                supervisor.writelog("[UI] MAP : Show Patrol Popup")
                                popup_patrol_list.open();
                                popup_patrol_list.mode = "sequence";
                            }else if(modelData == qsTr("위치 초기화")){
                                supervisor.writelog("[UI] MAP : move to Localization")
                                debug_mode = false;
                                supervisor.resetLocalization();
//                                loadPage(건너뛰기zation);
                            }
                        }
                    }
                }
            }
        }
    }

    ////////************************ITEM :: MAP **********************************************************
    Item{
        id: map_cur
        objectName: "map_current"
        width: parent.width
        height: parent.height - statusbar.height
        anchors.left: rect_menus.right
        anchors.bottom: parent.bottom

        Component.onCompleted: {
//            map_current.loadmap(supervisor.getMapname(),"EDITED")
            map_current.setEnable(true);
            map_current.setViewer("current");
        }
        Component.onDestruction: {
            map_current.setEnable(false);
        }

        Rectangle{
            id: rect_mapview
            anchors.fill: parent
            color: "#282828"
            MAP_FULL2{
                id: map_current
                objectName: "CURRENT"
                width: height
                height: parent.height
                show_button_following: true
                show_button_lidar: true
            }
        }
    }

    Rectangle{
        id: btn_menu
        width: 120
        height: width
        anchors.right: parent.right
        anchors.rightMargin: 50
        anchors.top: parent.top
        anchors.topMargin: statusbar.height + 50
        color: "white"
        radius: 30
        property bool is_restart: false
        Image{
            source:"icon/btn_menu.png"
            scale: 1-(120-parent.width)/120
            anchors.centerIn: parent
        }
        MouseArea{
            anchors.fill: parent
            onClicked: {
                click_sound.play();;
                supervisor.writelog("[UI] MAP : move to backPage");
                loadPage(pmenu);
//                backPage();
            }
        }
    }

    Popup_patrol{
        id: popup_patrol_list
    }



//    Popup{
//        id: popup_save_edited
//        width: parent.width
//        height: parent.height
//        background:Rectangle{
//            anchors.fill: parent
//            color: "#282828"
//            opacity: 0.7
//        }
//        onOpened:{
//            textfield_name.text = supervisor.getMapname();
//        }

//        Rectangle{
//            anchors.centerIn: parent
//            width: 400
//            height: 250
//            color: "white"
//            radius: 10

//            Column{
//                anchors.centerIn: parent
//                spacing: 20
//                Column{
//                    anchors.horizontalCenter: parent.horizontalCenter
//                    Text{
//                        text: qsTr("맵을 <font color=\"#12d27c\">저장</font>하시겠습니까?")
//                        font.family: font_noto_r.name
//                        font.pixelSize: 20
//                        anchors.horizontalCenter: parent.horizontalCenter
//                    }
//                    Text{
//                        text: qsTr("동일한 이름의 맵을 덮어씌워집니다")
//                        font.family: font_noto_r.name
//                        font.pixelSize: 15
//                        anchors.horizontalCenter: parent.horizontalCenter
//                    }
//                }

//                Row{
//                    anchors.horizontalCenter: parent.horizontalCenter
//                    spacing: 10
//                    Text{
//                        text: qsTr("맵 이름 : ")
//                        anchors.verticalCenter: parent.verticalCenter
//                        font.family: font_noto_r.name
//                        font.pixelSize: 20
//                    }
//                    TextField{
//                        id: textfield_name
//                        width: 250
//                        height: 50
//                        text: supervisor.getMapname();
//                        placeholderText: supervisor.getMapname();
//                        onFocusChanged: {
//                            keyboard.owner = textfield_name;
//                            if(focus){
//                                keyboard.open();
//                                textfield_name.selectAll();
//                            }else{
//                                keyboard.close();
//                            }
//                        }
//                    }
//                }
//                Row{
//                    anchors.horizontalCenter: parent.horizontalCenter
//                    spacing: 20
//                    Rectangle{
//                        width: 180
//                        height: 60
//                        radius: 10
//                        color:"transparent"
//                        border.width: 1
//                        border.color: "#7e7e7e"
//                        Text{
//                            anchors.centerIn: parent
//                            text: qsTr("취소")
//                            font.family: font_noto_r.name
//                            font.pixelSize: 25

//                        }
//                        MouseArea{
//                            anchors.fill: parent
//                            onClicked:{
//                                click_sound.play();;
//                                popup_save_edited.close();
//                            }
//                        }
//                    }
//                    Rectangle{
//                        width: 180
//                        height: 60
//                        radius: 10
//                        color: "#12d27c"
//                        border.width: 1
//                        border.color: "#12d27c"
//                        Text{
//                            anchors.centerIn: parent
//                            text: qsTr("확인")
//                            font.family: font_noto_r.name
//                            font.pixelSize: 25
//                            color: "white"
//                        }
//                        MouseArea{
//                            anchors.fill: parent
//                            onClicked:{
//                                if(textfield_name.text == ""){
//                                    click_sound_no.play();
//                                }else{
//                                    click_sound.play();;
//                                    show_loading();
//                                    supervisor.writelog("[QML] MAP PAGE : SAVE EDITED MAP "+textfield_name.text);
//                                    //save temp Image
//                                    map.save("edited");

//                                    //임시 맵 이미지를 해당 폴더 안에 넣음.
////                                    supervisor.rotate_map("map_edited_temp.png",textfield_name.text, 1);
////                                    supervisor.setMap(textfield_name.text);

//                                    //맵 새로 불러오기.
//                                    map.init();
//                                    map.setViewer("annot_objecting");
//                                    loader_menu.sourceComponent = menu_annot_objecting;
//                                    popup_save_edited.close();
//                                    unshow_loading();
//                                }
//                            }
//                        }
//                    }
//                }
//            }
//        }

//    }

    //    Popup{
//        id: popup_save_travelline
//        width: parent.width
//        height: parent.height
//        background:Rectangle{
//            anchors.fill: parent
//            color: "#282828"
//            opacity: 0.7
//        }
//        property string save_mode: "tline"
//        property bool edited_mode: false
//        Rectangle{
//            anchors.centerIn: parent
//            width: 400
//            height: 250
//            color: "white"
//            radius: 10

//            Column{
//                anchors.centerIn: parent
//                spacing: 20
//                Column{
//                    anchors.horizontalCenter: parent.horizontalCenter
//                    Text{
//                        text: qsTr("이대로 <font color=\"#12d27c\">저장</font>하시겠습니까?")
//                        font.family: font_noto_r.name
//                        font.pixelSize: 20
//                        anchors.horizontalCenter: parent.horizontalCenter
//                    }
//                    Text{
//                        text: qsTr("기존의 파일은 삭제됩니다")
//                        font.family: font_noto_r.name
//                        font.pixelSize: 15
//                        anchors.horizontalCenter: parent.horizontalCenter
//                    }
//                }
//                Row{
//                    anchors.horizontalCenter: parent.horizontalCenter
//                    spacing: 20
//                    Rectangle{
//                        width: 180
//                        height: 60
//                        radius: 10
//                        color:"transparent"
//                        border.width: 1
//                        border.color: "#7e7e7e"
//                        Text{
//                            anchors.centerIn: parent
//                            text: qsTr("취소")
//                            font.family: font_noto_r.name
//                            font.pixelSize: 25

//                        }
//                        MouseArea{
//                            anchors.fill: parent
//                            onClicked:{
//                                click_sound.play();;
//                                popup_save_travelline.close();
//                            }
//                        }
//                    }
//                    Rectangle{
//                        width: 180
//                        height: 60
//                        radius: 10
//                        color: "#12d27c"
//                        border.width: 1
//                        border.color: "#12d27c"
//                        Text{
//                            anchors.centerIn: parent
//                            text: qsTr("확인")
//                            font.family: font_noto_r.name
//                            font.pixelSize: 25
//                            color: "white"
//                        }
//                        MouseArea{
//                            anchors.fill: parent
//                            onClicked:{
//                                //save temp Image
//                                if(popup_save_travelline.save_mode === "tline"){
//                                    supervisor.writelog("[QML] MAP PAGE : SAVE TRAVELLINE ");
//                                    map.save("tline");
//                                }else if(popup_save_travelline.save_mode === "velmap"){
//                                    supervisor.writelog("[QML] MAP PAGE : SAVE VELOCITY MAP ");
//                                    map.save("velmap");
//                                }
//                                click_sound.play();;
//                                popup_save_travelline.close();
//                            }
//                        }
//                    }
//                }
//            }
//        }

//    }

    Component {
        id: locationCompo1
        Item {
            width: parent.width
            height: 35
            Text {
                id: text_loc
                anchors.centerIn: parent
                text: name
                font.family: font_noto_r.name
                font.pixelSize: 20
                font.bold: iscol
                color: list_location2.currentIndex==index?"black":"white"
            }
            Rectangle//리스트의 구분선
            {
                id:line
                width:parent.width
                anchors.bottom:parent.bottom//현재 객체의 아래 기준점을 부모객체의 아래로 잡아주어서 위치가 아래로가게 설정
                height:1
                color:"#e8e8e8"
            }
            MouseArea{
                id:area_compo
                anchors.fill:parent
                onClicked: {
                    click_sound.play();;
                    map.select_location_show = supervisor.getLocNum(name);
                    list_location2.currentIndex = index;
                    map.update_canvas();
                }
            }
        }
    }
//    Popup{
//        id: popup_add_location
//        width: 500
//        height: 400
//        anchors.centerIn: parent
//        bottomPadding: 0
//        topPadding: 0
//        leftPadding: 0
//        rightPadding: 0
//        property bool curpose_mode: false
//        background: Rectangle{
//            anchors.fill:parent
//            color: "#f4f4f4"
//        }
//        onOpened:{
//            curpose_mode = false;
//            select_location_type = "Serving";
//            tfield_location.text = select_location_type + "_" + Number(supervisor.getLocationSize(select_location_type))
//            if(curpose_mode){
//                btn_next_000.enabled = true;

//            }else{
//                if(map.checkLocCollision()){
//                    btn_next_000.enabled = false;
//                    popup_location_warning.open();
//                    popup_location_warning.set_obs();
//                    supervisor.writelog("[QML] MAP PAGE : SAVE LOCATION -> BUT OBS CLOSE");
//                }else{
//                    btn_next_000.enabled = true;
//                }
//            }

//            update();
//        }
//        function update(){
//            model_loc_group.clear();
//            for(var i=0; i<supervisor.getLocationGroupNum(); i++){
//                model_loc_group.append({"name":supervisor.getLocGroupname(i)});
//            }
//        }

//        Rectangle{
//            id: rect_loc_title
//            width: parent.width
//            height: 50
//            color: "#323744"
//            Text{
//                anchors.centerIn: parent
//                text: "위치 추가"
//                font.pixelSize: 20
//                font.family: font_noto_r.name
//                color: "white"
//            }
//        }
//        Rectangle{
//            color: "transparent"
//            width: parent.width
//            height: parent.height - rect_loc_title.height
//            anchors.top: rect_loc_title.bottom
//            Column{
//                anchors.centerIn: parent
//                spacing: 20
//                Column{
//                    id: column_loc
//                    width: 500
//                    anchors.horizontalCenter: parent.horizontalCenter
//                    Row{
//                        width: parent.width
//                        Rectangle{
//                            id: btn_serving
//                            width: parent.width/3
//                            height: 55
//                            color: select_location_type=="Serving"?color_green:"white"
//                            border.width: 1
//                            border.color: color_mid_gray
//                            Text{
//                                text: "서빙위치"
//                                font.pixelSize: 20
//                                anchors.centerIn: parent
//                                font.family: font_noto_r.name
//                                anchors.horizontalCenter: parent.horizontalCenter
//                            }
//                            MouseArea{
//                                anchors.fill: parent
//                                onClicked: {
//                                    click_sound.play();;
//                                    select_location_type = "Serving";
//                                    tfield_location.text = select_location_type + "_" + Number(supervisor.getLocationSize(select_location_type))
//                                }
//                            }
//                        }
//                        Rectangle{
//                            id: btn_charging
//                            width: parent.width/3
//                            height: 55
//                            color: select_location_type=="Charging"?color_green:"white"
//                            border.width: 1
//                            border.color: color_mid_gray
//                            Text{
//                                text: "충전위치"
//                                font.pixelSize: 20
//                                anchors.centerIn: parent
//                                font.family: font_noto_r.name
//                                anchors.horizontalCenter: parent.horizontalCenter
//                            }
//                            MouseArea{
//                                anchors.fill: parent
//                                onClicked: {
//                                    click_sound.play();;
//                                    if(supervisor.getLocationNum("Charging") > 0){
//                                        popup_location_warning.open();
//                                        popup_location_warning.set_overwrite();
//                                    }
//                                    select_location_type = "Charging";
//                                    tfield_location.text = select_location_type
//                                }
//                            }
//                        }
//                        Rectangle{
//                            id: btn_resting
//                            width: parent.width/3
//                            height: 55
//                            color: select_location_type=="Resting"?color_green:"white"
//                            border.width: 1
//                            border.color: color_mid_gray
//                            Text{
//                                text: "대기위치"
//                                font.pixelSize: 20
//                                anchors.centerIn: parent
//                                font.family: font_noto_r.name
//                                anchors.horizontalCenter: parent.horizontalCenter
//                            }
//                            MouseArea{
//                                anchors.fill: parent
//                                onClicked: {
//                                    click_sound.play();;
//                                    if(supervisor.getLocationNum("Resting") > 0){
//                                        popup_location_warning.open();
//                                        popup_location_warning.set_overwrite();
//                                    }
//                                    select_location_type = "Resting";
//                                    tfield_location.text = select_location_type
//                                }
//                            }
//                        }
//                    }


//                    Rectangle{
//                        id: rect_loc_menu2
//                        height: 80
//                        width: parent.width
//                        color: "#e8e8e8"
//                        visible: select_location_type=="Serving"
//                        Rectangle{
//                            id:rect_plus
//                            anchors.verticalCenter: parent.verticalCenter
//                            anchors.left: parent.left
//                            anchors.leftMargin: 30
//                            width: 50
//                            height: 50
//                            radius: 50
//                            color: "black"
//                            Text{
//                                anchors.centerIn: parent
//                                text: "+"
//                                color: "white"
//                                font.family: font_noto_b.name
//                                font.pixelSize: 40
//                                font.bold : true
//                            }
//                            MouseArea{
//                                anchors.fill: parent
//                                onClicked:{
//                                    click_sound.play();;
//                                }
//                            }
//                        }
//                        Flickable{
//                            anchors.verticalCenter: parent.verticalCenter
//                            anchors.left: rect_plus.right
//                            anchors.leftMargin: 20
//                            width: parent.width - 80 - rect_plus.width
//                            height: parent.height
//                            clip: true
//                            contentWidth: row_group.width
//                            Row{
//                                id: row_group
//                                spacing: 20
//                                anchors.verticalCenter: parent.verticalCenter
//                                Repeater{
//                                    model:ListModel{id:model_loc_group}
//                                    Rectangle{
//                                        width: 70
//                                        height: 60
//                                        radius: 10
//                                        anchors.verticalCenter: parent.verticalCenter
//                                        border.width: 1
//                                        color: cur_group === index ? color_green : "white"
//                                        Text{
//                                            anchors.centerIn: parent
//                                            font.family: font_noto_r.name
//                                            font.pixelSize: 15
//                                            text: name
//                                        }
//                                        MouseArea{
//                                            anchors.fill: parent
//                                            onClicked: {
//                                                click_sound.play();;
//                                                cur_group = index
//                                            }
//                                            onDoubleClicked: {
//                                                click_sound.play();;
//                                                cur_group = index
//                                                popup_remove_group.open();
//                                            }
//                                            onPressAndHold: {
//                                                click_sound.play();;
//                                                cur_group = index
//                                                popup_remove_group.open();

//                                            }
//                                        }
//                                    }
//                                }
//                            }
//                        }
//                    }
//                }
//                Popup{
//                    id: popup_remove_group
//                    anchors.centerIn: parent
//                    width: 500
//                    height: 250
//                    background: Rectangle{
//                        anchors.fill: parent
//                        color: "transparent"
//                    }
//                    property bool alright: true
//                    onOpened: {
//                        if(supervisor.getLocationGroupSize(cur_group) > 0){
//                            alright = false;
//                        }else{
//                            alright = true;
//                        }
//                    }

//                    Rectangle{
//                        width: parent.width
//                        height: parent.height
//                        radius: 20
//                        color: color_dark_navy
//                        Column{
//                            anchors.centerIn: parent
//                            spacing: 10
//                            Text{
//                                anchors.horizontalCenter: parent.horizontalCenter
//                                font.family: font_noto_b.name
//                                font.pixelSize: 30
//                                visible: popup_remove_group.alright
//                                text: "선택하신 그룹을 삭제하시겠습니까?"
//                                color: "white"
//                            }
//                            Text{
//                                visible: !popup_remove_group.alright
//                                anchors.horizontalCenter: parent.horizontalCenter
//                                font.family: font_noto_r.name
//                                font.pixelSize: 20
//                                color: color_red
//                                horizontalAlignment: Text.AlignHCenter
//                                text: "그룹 지정된 위치가 존재합니다\n삭제하려면 그룹을 전부 비워주세요"
//                            }
//                            Text{
//                                anchors.horizontalCenter: parent.horizontalCenter
//                                font.family: font_noto_r.name
//                                font.pixelSize: 18
//                                color: "white"
//                                text: "( " + supervisor.getLocGroupname(cur_group) + " )"
//                            }
//                            Row{
//                                anchors.horizontalCenter: parent.horizontalCenter
//                                spacing: 30
//                                Rectangle{
//                                    width: 120
//                                    height: 50
//                                    radius: 10
//                                    border.width: 1
//                                    Text{
//                                        anchors.centerIn: parent
//                                        font.family: font_noto_r.name
//                                        font.pixelSize: 15
//                                        text: "취소"
//                                    }
//                                    MouseArea{
//                                        anchors.fill: parent
//                                        onClicked:{
//                                            click_sound.play();;
//                                            popup_remove_group.close();
//                                        }
//                                    }
//                                }
//                                Rectangle{
//                                    width: 120
//                                    height: 50
//                                    radius: 10
//                                    enabled: popup_remove_group.alright
//                                    border.width: 1
//                                    color: popup_remove_group.alright?"white":color_dark_gray
//                                    Text{
//                                        anchors.centerIn: parent
//                                        font.family: font_noto_r.name
//                                        font.pixelSize: 15
//                                        text: "삭제"
//                                        color: popup_remove_group.alright?"black":"white"
//                                    }
//                                    MouseArea{
//                                        anchors.fill: parent
//                                        onClicked:{
//                                            click_sound.play();;
//                                            supervisor.removeLocationGroup(cur_group);
//                                            popup_remove_group.close();
//                                            cur_group = 0;
//                                            popup_add_location.update();
//                                        }
//                                    }
//                                }
//                            }
//                        }
//                    }

//                }

//                TextField{
//                    id: tfield_location
//                    anchors.horizontalCenter: parent.horizontalCenter
//                    width: parent.width*0.9
//                    height: 50
//                    placeholderText: "(loc_name)"
//                    font.family: font_noto_r.name
//                    horizontalAlignment: Text.AlignHCenter
//                    font.pointSize: 20
//                    onFocusChanged: {
//                        keyboard.owner = tfield_location;
//                        tfield_location.selectAll();
//                        if(focus){
//                            keyboard.open();
//                        }else{
//                            tfield_location.select(0,0)
//                            keyboard.close();
//                        }
//                    }
//                }
//                Row{
//                    anchors.horizontalCenter: tfield_location.horizontalCenter
//                    spacing: 20
//                    Rectangle{
//                        id: btn_prev_000
//                        width: 180
//                        height: 60
//                        radius: 10
//                        color:"transparent"
//                        border.width: 1
//                        border.color: "#7e7e7e"
//                        Text{
//                            anchors.centerIn: parent
//                            text: "취소"
//                            font.family: font_noto_r.name
//                            font.pixelSize: 25

//                        }
//                        MouseArea{
//                            anchors.fill: parent
//                            onClicked:{
//                                click_sound.play();;
//                                popup_add_location.close();
//                            }
//                        }
//                    }
//                    Rectangle{
//                        id: btn_next_000
//                        width: 180
//                        height: 60
//                        radius: 10
//                        enabled: false
//                        color: enabled?"black":color_gray
//                        border.width: 1
//                        border.color: "#7e7e7e"
//                        Text{
//                            anchors.centerIn: parent
//                            text: "확인"
//                            font.family: font_noto_r.name
//                            font.pixelSize: 25
//                            color: "white"
//                        }
//                        MouseArea{
//                            anchors.fill: parent
//                            onClicked:{
//                                if(tfield_location.text == ""){
//                                    click_sound_no.play();
//                                }else{
//                                    click_sound.play();;
//                                    if(popup_add_location.curpose_mode){
//                                        supervisor.savelocation("location_cur",select_location_type, cur_group, tfield_location.text);
//                                    }else{
//                                        supervisor.savelocation("location",select_location_type,cur_group, tfield_location.text)
//                                    }
//                                    supervisor.writelog("[QML] MAP PAGE : SAVE LOCATION -> "+select_location_type + ", "+cur_group+", "+tfield_location.text);
//                                    map.setTool("move");
//                                    map.init();
//                                    popup_add_location.close();
//                                }
//                            }
//                        }
//                    }
//                }
//            }
//        }

//        Rectangle{
//            anchors.fill:parent
//            color: "transparent"
//            border.width: 3
//            border.color: "#323744"
//        }
//    }

//    Popup{
//        id: popup_add_location_group
//        anchors.centerIn: parent
//        width: 400
//        height: 250
//        bottomPadding: 0
//        topPadding: 0
//        leftPadding: 0
//        rightPadding: 0
//        background: Rectangle{
//            anchors.fill:parent
//            color: "white"
//        }
//        onOpened:{
//            tfield_group.text = "";
//        }

//        Rectangle{
//            id: rect_add_loc_group_1
//            width: parent.width
//            height: 45
//            color: "#323744"
//            Text{
//                anchors.centerIn: parent
//                text: "그룹 추가"
//                font.pixelSize: 20
//                font.family: font_noto_r.name
//                color: "white"
//            }
//        }
//        Rectangle{
//            color: "transparent"
//            width: parent.width
//            height: 250 - rect_add_loc_group_1.height
//            anchors.bottom: parent.bottom
//            Column{
//                anchors.centerIn: parent
//                spacing: 20

//                TextField{
//                    id: tfield_group
//                    anchors.horizontalCenter: parent.horizontalCenter
//                    width: popup_add_location_group.width*0.9
//                    height: 50
//                    placeholderText: "(group_name)"
//                    font.family: font_noto_r.name
//                    horizontalAlignment: Text.AlignHCenter
//                    font.pointSize: 20
//                    onFocusChanged: {
//                        keyboard.owner = tfield_group;
//                        tfield_group.selectAll();
//                        if(focus){
//                            keyboard.open();
//                        }else{
//                            tfield_group.select(0,0)
//                            keyboard.close();
//                        }
//                    }
//                }
//                Row{
//                    anchors.horizontalCenter: parent.horizontalCenter
//                    spacing: 20
//                    Rectangle{
//                        width: 150
//                        height: 60
//                        radius: 10
//                        color:"transparent"
//                        border.width: 1
//                        border.color: "#7e7e7e"
//                        Text{
//                            anchors.centerIn: parent
//                            text: "취소"
//                            font.family: font_noto_r.name
//                            font.pixelSize: 25

//                        }
//                        MouseArea{
//                            anchors.fill: parent
//                            onClicked:{
//                                click_sound.play();;
//                                popup_add_location_group.close();
//                            }
//                        }
//                    }
//                    Rectangle{
//                        width: 150
//                        height: 60
//                        radius: 10
//                        color: "black"
//                        border.width: 1
//                        border.color: "#7e7e7e"
//                        Text{
//                            anchors.centerIn: parent
//                            text: "확인"
//                            font.family: font_noto_r.name
//                            font.pixelSize: 25
//                            color: "white"
//                        }
//                        MouseArea{
//                            anchors.fill: parent
//                            onClicked:{
//                                if(tfield_group.text == ""){
//                                    click_sound_no.play();
//                                }else{
//                                    click_sound.play();;
//                                    supervisor.addLocationGroup(tfield_group.text);
//                                    supervisor.writelog("[QML] MAP PAGE : ADD LOCATION GROUP -> "+tfield_group.text);
//                                    popup_add_location.update();
//                                    popup_location_number.readSetting();
//                                    cur_group = supervisor.getLocationGroupNum()-1;
//                                    popup_add_location_group.close();
//                                }
//                            }
//                        }
//                    }
//                }
//            }
//        }
//        Rectangle{
//            anchors.fill:parent
//            color: "transparent"
//            border.width: 3
//            border.color: "#323744"
//        }
//    }

//    Popup{
//        id: popup_location_warning
//        anchors.centerIn: parent
//        width: 500
//        height: 200
//        bottomPadding: 0
//        topPadding: 0
//        leftPadding: 0
//        rightPadding: 0
//        function set_overwrite(){
//            text_msg.text = "이미 설정한 위치가 존재합니다 \n저장하시면 설정된 위치를 덮어씁니다";
//        }
//        function set_obs(){
//            text_msg.text = "장애물과 너무 가깝습니다 \n위치를 저장할 수 없습니다"
//        }

//        background: Rectangle{
//            anchors.fill:parent
//            color: "transparent"
//        }
//        Rectangle{
//            color: color_dark_navy
//            anchors.fill: parent
//            Column{
//                anchors.centerIn: parent
//                spacing: 20
//                Image{
//                    source:"icon/icon_error.png"
//                    anchors.horizontalCenter: parent.horizontalCenter
//                }

//                Text{
//                    id: text_msg
//                    anchors.horizontalCenter: parent.horizontalCenter
//                    font.family: font_noto_r.name
//                    font.pixelSize: 20
//                    horizontalAlignment: Text.AlignHCenter
//                    color: color_red
//                    text: "이미 설정한 위치가 존재합니다 \n저장하시면 설정된 위치를 덮어씁니다"
//                }
//            }
//            MouseArea{
//                anchors.fill: parent
//                onClicked:{
//                    click_sound.play();;
//                    popup_location_warning.close();
//                }
//            }

//        }

//    }


    function loadmap(name,type){
        print("map loadmap ",name,type);
//        check_slam_init_timer.stop();
        map.loadmap(name,type);
    }

    Popup{
        id: popup_help
        anchors.centerIn: parent
        width: parent.width
        height: parent.height
        background: Rectangle{
            anchors.fill: parent
            color: color_dark_black
            opacity: 0.7
        }
        onOpened: {
            help_image.play("video/slam_help.gif")
        }
        onClosed:{
            help_image.stop();
        }

        AnimatedImage{
            id: help_image
            enabled: supervisor.getSetting("setting","USE_UI","use_help")==="true"
            anchors.centerIn : parent
            function play(name){
                source = name;
                visible = true;
            }
            function stop(){
                visible = false;
                source = "";
            }
            source:  ""
            cache: false
        }
//        Rectangle{
//            width: parent.width
//            height: parent.height
//            radius: 20
//            Column{
//                spacing: 10
//                anchors.centerIn : parent
//                Text{
//                    anchors.horizontalCenter: parent.horizontalCenter
//                    font.family: font_noto_r.name
//                    font.pixelSize: 30
//                    text: "방법"
//                }
//            }
//        }
        MouseArea{
            anchors.fill: parent
            onClicked:{
                click_sound.play();;
                popup_help.close();
            }
        }
    }
}
