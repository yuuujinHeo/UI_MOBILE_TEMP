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
    property int last_robot_th: 0

    //annotation
    property string select_object_type: "Wall"
    property string select_location_type: "Serving"
    property int select_tline_num: -1
    property int select_tline_category: -1
    property int select_patrol_num: -1
    property int select_preset: 1

    property int cur_group: 0

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
//        init();
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
                model: [qsTr("맵 새로만들기"),qsTr("현재맵 수정하기"),qsTr("현재맵 동기화"),qsTr("위치 초기화")]
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
                                    if(modelData === qsTr("맵 새로만들기"))
                                    {
                                        "image/image_slam.png"
                                    }
                                    else if(modelData === qsTr("현재맵 수정하기"))
                                    {
                                        "image/image_annot.png"
                                    }
                                    //else if(multirobot_state = 1)
                                    else if(modelData === qsTr("현재맵 동기화"))
                                    {
                                        "image/image_localization_reset.png"
                                    }
                                    else if(modelData === qsTr("위치 초기화"))
                                    {
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
                            rect_btn.color = "white";
                            if(modelData === qsTr("맵 새로만들기"))
                            {
                                if(!supervisor.getIPCConnection()){
                                    supervisor.playSound('no');
                                    openNotice("ipc_discon");
                                }else{
                                    supervisor.playSound('click');
                                    supervisor.writelog("[UI] MAP : move to Mapping");
                                    loadPage(pmapping);
                                }
                            }
                            else if(modelData === qsTr("현재맵 수정하기"))
                            {
                                supervisor.playSound('click');
                                supervisor.writelog("[UI] MAP : move to Annotation");
                                loadPage(pannotation);
                                loader_page.item.init();
                                supervisor.setAnnotEditFlag(true);

                            }
                            else if (modelData === qsTr("현재맵 동기화"))
                            {
                                supervisor.playSound('click');
                                supervisor.writelog("[UI] MAP : move to FMS & others")
                                //supervisor.resetLocalization();
                                //loadPage(pinit);
                                supervisor.sendMapSync();
                            }
                            else if(modelData === qsTr("위치 초기화"))
                            {
                                supervisor.playSound('click');
                                supervisor.writelog("[UI] MAP : move to Localization")
                                supervisor.resetLocalization();
                                loadPage(pinit);
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
            map_current.init();
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
                Component.onCompleted: {
                    supervisor.setMapSize(objectName,width,height);
                }
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
                supervisor.playSound('click');;
                supervisor.writelog("[UI] MAP : move to backPage");
                loadPage(pmenu);
            }
        }
    }



    Popup_patrol{
        id: popup_patrol
    }


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
                    supervisor.playSound('click');;
                    list_location2.currentIndex = index;
                    map.update_canvas();
                }
            }
        }
    }



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
        MouseArea{
            anchors.fill: parent
            onClicked:{
                supervisor.playSound('click');
                popup_help.close();
            }
        }
    }
}
