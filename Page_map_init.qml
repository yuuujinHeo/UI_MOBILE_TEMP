import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.2
import Qt.labs.platform 1.0 as Platform
import QtGraphicalEffects 1.0
import "."
import io.qt.Supervisor 1.0

Item {
    id: page_map_init
    objectName: "page_map_init"
    width: 1280
    height: 800

    property int width_menu: 400

    //slam
    property bool slam_initializing: false
    property bool joystick_connection: false
    property var joy_axis_left_ud: 0
    property var joy_axis_right_rl: 0


    //mode : 1:(slam) 2:(annotation)
    property int map_mode: 1

    Component.onCompleted: {
        init();
    }

    Component.onDestruction:  {
        if(supervisor.getJoyXY() !== 0){
            supervisor.joyMoveXY(0);
        }
        if(supervisor.getJoyR() !== 0){
            supervisor.joyMoveR(0);
        }
    }

    function updatecanvas(){
        map.update_canvas_all();
    }
    Item{
        focus: true
        Keys.onReleased: {
            if(map_mode == 1){
                if(event.key === Qt.Key_Up){
                    loader_menu.item.setKeyUp(false);
                    if(!loader_menu.item.getKeyDown())
                        supervisor.joyMoveXY(0);
                }
                if(event.key === Qt.Key_Down){
                    loader_menu.item.setKeyDown(false);
                    if(!loader_menu.item.getKeyUp())
                        supervisor.joyMoveXY(0);
                }
                if(event.key === Qt.Key_Left){
                    loader_menu.item.setKeyLeft(false);
                    if(!loader_menu.item.getKeyRight())
                        supervisor.joyMoveR(0);
                }
                if(event.key === Qt.Key_Right){
                    loader_menu.item.setKeyRight(false);
                    if(!loader_menu.item.getKeyLeft())
                        supervisor.joyMoveR(0);
                }
            }
        }
        Keys.onPressed: {
            if(map_mode == 1){
                if(event.key === Qt.Key_Up){
                    loader_menu.item.setKeyUp(true);
                    supervisor.joyMoveXY(-1);
                }
                if(event.key === Qt.Key_Down){
                    loader_menu.item.setKeyDown(true);
                    supervisor.joyMoveXY(1);
                }
                if(event.key === Qt.Key_Left){
                    loader_menu.item.setKeyLeft(true);
                    supervisor.joyMoveR(-1);
                }
                if(event.key === Qt.Key_Right){
                    loader_menu.item.setKeyRight(true);
                    supervisor.joyMoveR(1);
                }
            }
        }
    }

    Rectangle{
        id: status_bar
        width: parent.width
        height: 60
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        color: "white"
    }

    Rectangle{
        id: rect_menus
        width: width_menu
        height: parent.height - status_bar.height
        anchors.left: parent.left
        anchors.top: status_bar.bottom
        color: "#282828"
        property int menu_height: 30
        Loader{
            id: loader_menu
            anchors.fill: parent
            sourceComponent: menu_slam
        }
   }

    Item{
        id: map_annot
        width: parent.width - rect_menus.width
        height: parent.height - status_bar.height
        anchors.left: rect_menus.right
        anchors.top: status_bar.bottom
        Rectangle{
            anchors.fill: parent
            color: "#282828"
            Map_full{
                id: map
                height: parent.height
                width: height
                anchors.left: parent.left
                anchors.verticalCenter: parent.verticalCenter
                clip: true
                just_show_map: true
            }
            Rectangle{
                id: rect_init_notice
                width: 400
                height: 100
                visible: slam_initializing
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                color: "gray"
                Text{
                    anchors.centerIn: parent
                    text:"초기화 중...시간이 조금 소요됩니다."
                    color: "white"
                }
            }
        }
    }

    Rectangle{
        id: btn_menu
        width: 60
        height: width
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.top: status_bar.bottom
        anchors.topMargin: 20
        color: "white"
        radius: 30
        Image{
            source:"icon/btn_reset.png"
            scale: 1-(120-parent.width)/120
            anchors.centerIn: parent
        }
        MouseArea{
            anchors.fill: parent
            onClicked: {
                backPage();
            }
        }
    }

    ////////************************ITEM :: MENU**********************************************************

    Component{
        id: menu_slam
        Item{
            anchors.fill: parent
            function remote_input_xy(value1,value2){
                if(value1 == 0 && value2 == 0){
                    joy_xy.remote_stop();
                }else{
                    joy_xy.remote_input(value1,value2);
                }
            }
            function remote_input_th(value1,value2){
                if(value1 == 0 && value2 == 0){
                    joy_th.remote_stop();
                }else{
                    joy_th.remote_input(value1,value2);
                }
            }
            function setKeyUp(pressed){
                keyboard.pressed_up = pressed;
            }
            function setKeyDown(pressed){
                keyboard.pressed_down = pressed;
            }
            function setKeyLeft(pressed){
                keyboard.pressed_left = pressed;
            }
            function setKeyRight(pressed){
                keyboard.pressed_right = pressed;
            }
            function getKeyUp(){
                return keyboard.pressed_up
            }
            function getKeyDown(){
                return keyboard.pressed_down
            }
            function getKeyLeft(){
                return keyboard.pressed_left
            }
            function getKeyRight(){
                return keyboard.pressed_right
            }

            Column{
                id: column_slam_menus
                spacing: 30
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                anchors.topMargin: 50
                Rectangle{
                    id: btn_slam_save
                    width: 150
                    height: 70
                    radius: 15
                    anchors.horizontalCenter: parent.horizontalCenter
                    color: "#D0D0D0"
                    Text{
                        anchors.centerIn: parent
                        text: "save"
                        font.family: font_noto_b.name
                        font.pixelSize: 20
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            map.save_map("image/raw_map.png");
                            supervisor.writelog("[USER INPUT] Save Mapping Image -> image/raw_map.png");
                        }
                    }
                }
                Row{
                    id: row_slam_menu
                    spacing: 30
                    anchors.horizontalCenter: parent.horizontalCenter
                    Repeater{
                        model: ["run","stop"]
                        Rectangle{
                            width: 150
                            height: 70
                            radius: 15
                            color: "#D0D0D0"
                            Text{
                                anchors.centerIn: parent
                                text: modelData
                                font.family: font_noto_b.name
                                font.pixelSize: 20
                            }
                            MouseArea{
                                anchors.fill: parent
                                onClicked: {
                                    if(modelData == "run"){
                                        supervisor.startMapping();
                                        timer_mapping.start();
                                    }else if(modelData == "stop"){
                                        supervisor.stopMapping();
                                        timer_mapping.stop();
                                    }
                                }
                            }
                        }
                    }
                }
            }

            Image{
                id: image_joy_up
                source: "icon/joy_up.png"
                width: 13
                height: 8
                anchors.horizontalCenter: joy_xy.horizontalCenter
                anchors.bottom: joy_xy.top
                anchors.bottomMargin: 8
            }
            Image{
                id: image_joy_down
                source: "icon/joy_down.png"
                width: 13
                height: 8
                anchors.horizontalCenter: joy_xy.horizontalCenter
                anchors.top: joy_xy.bottom
                anchors.topMargin: 8
            }
            Image{
                id: image_joy_left
                source: "icon/joy_left.png"
                width: 8
                height: 13
                anchors.verticalCenter: joy_th.verticalCenter
                anchors.right: joy_th.left
                anchors.rightMargin: 8
            }
            Image{
                id: image_joy_right
                source: "icon/joy_right.png"
                width: 8
                height: 13
                anchors.verticalCenter: joy_th.verticalCenter
                anchors.left: joy_th.right
                anchors.leftMargin: 8
            }

            Item_joystick{
                id: joy_xy
                anchors.top: column_slam_menus.bottom
                anchors.topMargin: 100
                anchors.right: parent.horizontalCenter
                anchors.rightMargin: 30
                verticalOnly: true
                onUpdate_cntChanged: {
                    if(update_cnt == 0 && supervisor.getJoyXY() != 0){
                        supervisor.joyMoveXY(0, 0);
                    }else{
                        if(fingerInBounds) {
                            supervisor.joyMoveXY(Math.sin(angle) * Math.sqrt(fingerDistance2) / distanceBound);
                        }else{
                            supervisor.joyMoveXY(Math.sin(angle));
                        }
                    }
                }
            }
            Item_joystick{
                id: joy_th
                anchors.top: column_slam_menus.bottom
                anchors.topMargin: 100
                anchors.left: parent.horizontalCenter
                anchors.leftMargin: 30
                horizontalOnly: true
                onUpdate_cntChanged: {
                    if(update_cnt == 0 && supervisor.getJoyR() != 0){
                        supervisor.joyMoveR(0, 0);
                    }else{
                        if(fingerInBounds) {
                            supervisor.joyMoveR(-Math.cos(angle) * Math.sqrt(fingerDistance2) / distanceBound);
                        } else {
                            supervisor.joyMoveR(-Math.cos(angle));
                        }
                    }
                }
            }
            Item_keyboard{
                id: keyboard
                focus: true
                anchors.top: joy_th.bottom
                anchors.topMargin: 100
                anchors.horizontalCenter: parent.horizontalCenter

            }
        }
    }

    Component{
        id: menu_annot
        Item{
            StackView{
                id: stackview_annot_menu
                width: rect_menus.width
                height: rect_menus.height
                initialItem: menu_state
            }
        }
    }

    //Annotation Menu ITEM===================================================
    Component{
        id: menu_annot_state
        Item{
            id: menu_state
            objectName: "menu_init"
            anchors.fill: parent
            Rectangle{
                anchors.fill: parent
                color: "#f4f4f4"
                Column{
                    anchors.top: parent.top
                    anchors.topMargin: 25
                    spacing: 25
                    Rectangle{
                        y: 20
                        width: menu_state.width
                        height: rect_menus.menu_height
                        color: "yellow"
                        radius: 10
                        Text{
                            id: text_name
                            anchors.left: parent.left
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.leftMargin: 15
                            text: "Map : "
                        }
                    }
                    Rectangle{
                        width: menu_state.width
                        height: rect_menus.menu_height
                        color: "yellow"
                        radius: 10
                    }
                    Rectangle{
                        width: menu_state.width
                        height: rect_menus.menu_height
                        color: "yellow"
                        radius: 10
                    }
                    Rectangle{
                        width: menu_state.width
                        height: rect_menus.menu_height
                        color: "yellow"
                        radius: 10
                    }
                }

                //prev, next button
                Rectangle{
                    id: btn_prev_0
                    width: width_menu/2
                    height: 60
                    anchors.bottom: parent.bottom
                    radius: 10
                    border.width: 2
                    border.color: "gray"
                    Text{
                        anchors.centerIn: parent
                        text: "Previous"
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked:{
                            backPage();
                        }
                    }
                }
                Rectangle{
                    id: btn_next_0
                    width: width_menu/2
                    height: 60
                    anchors.bottom: parent.bottom
                    anchors.right: parent.right
                    radius: 10
                    border.width: 2
                    border.color: "gray"
                    Text{
                        anchors.centerIn: parent
                        text: "Next"
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked:{
                            map.state_annotation = "DRAWING";
                            loader_menu.sourceComponent = menu_annot_draw;
                        }
                    }
                }
            }
        }

    }
    Component{
        id: menu_annot_draw
        Item{
            id: menu_load_edit
            objectName: "menu_load_edit"
            anchors.fill: parent
            Rectangle{
                width: parent.width
                height: parent.height
                anchors.fill: parent
                color: "transparent"
                Text{
                    id: text_main_1
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.pixelSize: 20
                    text: "Step 1. Map annotation and edit location"
                }

                //map load
                Rectangle{
                    id: text_cur_name
                    anchors.top: text_main_1.bottom
                    anchors.topMargin: 30
                    width: parent.width
                    height: rect_menus.menu_height
                    color: "yellow"
                    radius: 10
                    Text{
                        id: text_name2
                        anchors.left: parent.left
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.leftMargin: 15
                        text: " Current Map : "
                    }
                    Text{
                        id: text_name3
                        anchors.right: parent.right
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.rightMargin: 15
                        text: "/image/"+map_name + ".png";
                    }
                }
                Rectangle{
                    id: btn_load_map
                    width: parent.width/2
                    height: 60
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: text_cur_name.bottom
                    anchors.topMargin: 30

                    radius: 10
                    border.width: 2
                    border.color: "gray"

                    Text{
                        anchors.centerIn: parent
                        text: "Load"
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked:{
                            fileload.open();
                        }
                    }
                }


                //draw Menu
                Row{
                    id: menubar_drawing
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: btn_load_map.bottom
                    anchors.topMargin: 30
                    spacing: 25
                    Repeater{
                        model: ["move","draw","clear","undo","redo"]
                        Rectangle{
                            id: btn
                            width: 60
                            height: 60
                            color: {
                                if(map.tool == "MOVE"){
                                    if(modelData == "move"){
                                        "blue"
                                    }else{
                                        "gray"
                                    }
                                }else if(map.tool == "BRUSH"){
                                    if(modelData == "draw"){
                                        "blue"
                                    }else{
                                        "gray"
                                    }
                                }else{
                                    "gray"
                                }
                            }
                            radius: 10
                            Image{
                                anchors.centerIn:  parent
                                antialiasing: true
                                mipmap: true
                                scale: {(height>width?parent.width/height:parent.width/width)*0.8}
                                source:{
                                    if(modelData == "move"){
                                        "icon/btn_minimize.png"
                                    }else if(modelData == "draw"){
                                        "icon/play_r.png"
                                    }else if(modelData == "clear"){
                                        "icon/btn_reset.png"
                                    }else if(modelData == "undo"){
                                        "icon/btn_no.png"
                                    }else if(modelData == "redo"){
                                        "icon/btn_yes.png"
                                    }
                                }
                            }
                            MouseArea{
                                anchors.fill: parent
                                onClicked: {
                                    if(modelData == "move"){
                                        map.tool = "MOVE";
                                    }else if(modelData == "draw"){
                                        map.tool = "BRUSH";
                                    }else if(modelData == "clear"){
                                        supervisor.clear_all();
                                        map.update_canvas_all();
                                    }else if(modelData == "undo"){
                                        supervisor.undo();
                                        map.update_canvas_all();
                                    }else if(modelData == "redo"){
                                        supervisor.redo();
                                        map.update_canvas_all();
                                    }
                                }
                            }
                        }
                    }
                }

                Row{
                    id: colorbar
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: menubar_drawing.bottom
                    anchors.topMargin: 30
                    spacing: 25
                    property color paintColor: "black"
                    Repeater{
                        model: ["black", "#262626", "white"]
                        Rectangle {
                            id: red
                            width: 60
                            height: 60
                            color: modelData
                            border.color: "gray"
                            border.width: 2
                            radius: 60

                            MouseArea{
                                anchors.fill: parent
                                onClicked: {
                                    map.brush_color = color
                                    map.tool = "BRUSH";
                                }
                            }
                        }
                    }
                }

                Slider {
                    id: slider_brush
                    x: 300
                    y: 330
                    value: 15
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: colorbar.bottom
                    anchors.topMargin: 20
                    width: parent.width/1.5
                    height: 30
                    from: 0.1
                    to : 50
    //                orientation: Qt.Vertical
                    onValueChanged: {
                        map.brush_size = value;
                        print("slider : " +map.brush_size);
                    }
                    onPressedChanged: {
                        if(slider_brush.pressed){
                            brushview.visible = true;
                        }else{
                            brushview.visible =false;
                        }
                    }
                }



                //prev, next button
                Rectangle{
                    id: btn_prev_1
                    width: parent.width/2
                    height: 60
                    anchors.bottom: parent.bottom
                    radius: 10
                    border.width: 2
                    border.color: "gray"
                    Text{
                        anchors.centerIn: parent
                        text: "Previous"
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked:{
                            map.init_mode();
                            map.state_annotation = "NONE";
                            loader_menu.sourceComponent = menu_annot_state;
                        }
                    }
                }
                Rectangle{
                    id: btn_next_1
                    width: parent.width/2
                    height: 60
                    anchors.bottom: parent.bottom
                    anchors.right: parent.right
                    radius: 10
                    border.width: 2
                    border.color: "gray"
                    Text{
                        anchors.centerIn: parent
                        text: "Next"
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked:{
                            //save temp Image
                            map.save_canvas_temp();
                            map.loadmap("file://"+applicationDirPath+"/image/map_edited.png");
                            supervisor.clear_all();
                            map.state_annotation = "OBJECT";
                            loader_menu.sourceComponent = menu_annot_object;
                        }
                    }
                }
            }
        }

    }
    Component{
        id: menu_annot_object
        Item{
            id: menu_object
            objectName: "menu_object"
            anchors.fill: parent
            Component.onCompleted: {
                var ob_num = supervisor.getObjectNum();
                list_object.model.clear();
                for(var i=0; i<ob_num; i++){
                    list_object.model.append({"name":supervisor.getObjectName(i)});
                }
                map.update_canvas_all();
            }
            function update(){
                var ob_num = supervisor.getObjectNum();
                list_object.model.clear();
                for(var i=0; i<ob_num; i++){
                    list_object.model.append({"name":supervisor.getObjectName(i)});
                }
                list_object.currentIndex = ob_num-1;
                map.update_canvas_all();
            }

            function getcur(){
                return list_object.currentIndex;
            }
            function setcur(index){
                list_object.currentIndex = index;
            }
            Rectangle{
                anchors.fill: parent
                color: "transparent"
                Text{
                    id: text_main_2
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.pixelSize: 20
                    text: "Step 2. Add Object"
                }
                Row{
                    id: menubar_object
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: text_main_2.bottom
                    anchors.topMargin: 30
                    spacing: 25
                    Repeater{
                        model: ["move","rect","add","clear","undo"]
                        Rectangle{
                            id: btn2
                            width: 60
                            height: 60
                            color: {
                                if(map.tool == "MOVE"){
                                    if(modelData == "move"){
                                        "blue"
                                    }else{
                                        "gray"
                                    }
                                }else if(map.tool == "ADD_POINT"){
                                    if(modelData == "add"){
                                        "blue"
                                    }else{
                                        "gray"
                                    }
                                }else if(map.tool == "ADD_OBJECT"){
                                    if(modelData == "rect"){
                                        "blue"
                                    }else{
                                        "gray"
                                    }
                                }else{
                                    "gray"
                                }
                            }
                            radius: 10
                            Text{
                                anchors.centerIn:  parent
                                text: modelData
                            }
                            MouseArea{
                                anchors.fill: parent
                                onClicked: {
                                    if(modelData == "move"){
                                        map.tool = "MOVE";
                                    }else if(modelData == "add"){
                                        map.tool = "ADD_POINT";
                                    }else if(modelData == "clear"){
                                        supervisor.clearObjectPoints();
                                        map.update_canvas_all();
                                    }else if(modelData == "undo"){
                                        supervisor.removeObjectPointLast();
                                        map.update_canvas_all();
                                    }else if(modelData == "rect"){
                                        map.tool = "ADD_OBJECT";
                                    }
                                }
                            }
                        }
                    }
                }

                //List Object
                Component {
                    id: objectCompo
                    Item {
                        width: 250; height: 30
                        Text {
                            anchors.centerIn: parent
                            text: name
                        }
                        Rectangle//리스트의 구분선
                        {
                            id:line
                            width:parent.width
                            anchors.bottom:parent.bottom//현재 객체의 아래 기준점을 부모객체의 아래로 잡아주어서 위치가 아래로가게 설정
                            height:1
                            color:"black"
                        }
                        MouseArea{
                            id:area_compo
                            anchors.fill:parent
                            onClicked: {
                                map.select_object = supervisor.getObjNum(name);
                                print("select object = "+map.select_object);
                                list_object.currentIndex = index;
                                map.update_canvas_all();
                            }
                        }
                    }
                }
                ListView {
                    id: list_object
                    width: 250
                    height: 400
                    anchors.top: menubar_object.bottom
                    anchors.topMargin: 30
                    anchors.left: parent.left
                    anchors.leftMargin: 30
                    clip: true
                    model: ListModel{}
                    delegate: objectCompo
                    highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
                    focus: true
                }

                Column{
                    id: menubar_object2
                    anchors.verticalCenter: list_object.verticalCenter
                    anchors.left: list_object.right
                    anchors.leftMargin: 40
                    spacing: 30
                    Repeater{
                        model: ["add","edit","remove"]
                        Rectangle{
                            id: btn3
                            width: 60
                            height: 60
                            color: "gray"
                            radius: 10
                            Text{
                                anchors.centerIn: parent
                                text: modelData
                            }

                            MouseArea{
                                anchors.fill: parent
                                onClicked: {
                                    if(modelData == "edit"){
                                        map.tool = "EDIT_OBJECT";
    //                                    map.tool = "EDIT_POINT";
                                    }else if(modelData == "remove"){
                                        supervisor.removeObject(list_object.model.get(list_object.currentIndex).name);
                                        map.update_canvas_all();
                                    }else if(modelData == "add"){
                                        popup_add_object.open();
                                    }
                                }
                            }
                        }
                    }
                }

                Rectangle{
                    width: parent.width/2
                    height: 60
                    anchors.bottom: parent.bottom
                    radius: 10
                    border.width: 2
                    border.color: "gray"
                    Text{
                        anchors.centerIn: parent
                        text: "Previous"
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked:{
                            map.init_mode();
                            map.state_annotation = "DRAWING";
                            loader_menu.sourceComponent = menu_annot_draw;
                        }
                    }
                }
                Rectangle{
                    width: parent.width/2
                    height: 60
                    anchors.bottom: parent.bottom
                    anchors.right: parent.right
                    radius: 10
                    border.width: 2
                    border.color: "gray"
                    Text{
                        anchors.centerIn: parent
                        text: "Next"
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked:{
                            map.init_mode();
                            map.state_annotation = "LOCATION";
                            map.update_canvas_all();
                            loader_menu.sourceComponent = menu_annot_location;
                        }
                    }
                }
            }
        }
    }
    Component{
        id: menu_annot_location
        Item{
            id: menu_location
            objectName: "menu_location"
            anchors.fill: parent
            Component.onCompleted: {
                var loc_num = supervisor.getLocationNum();
                list_location.model.clear();
                for(var i=0; i<loc_num; i++){
                    list_location.model.append({"name":supervisor.getLocationTypes(i),"iscol":false});
                }
                map.update_canvas_all();
            }
            function getcur(){
                return list_location.currentIndex;
            }
            function setcur(index){
                list_location.currentIndex = index;
            }
            function getslider(){
                return slider_margin.value;
            }
            function update(){
                for(var i=0; i<list_location.model.count; i++){
                    if(map.is_Col_loc(supervisor.getLocationx(i)/map.grid_size + map.origin_x,supervisor.getLocationy(i)/map.grid_size + map.origin_y)){
                        list_location.model.get(i).iscol = true;
                    }else{
                        list_location.model.get(i).iscol = false;
                    }
                }
                var loc_num = supervisor.getLocationNum();
                list_location.model.clear();
                for(var i=0; i<loc_num; i++){
                    list_location.model.append({"name":supervisor.getLocationTypes(i),"iscol":false});
                }
                list_location.currentIndex = loc_num-1;
            }

            Rectangle{
                anchors.fill: parent
                color: "transparent"
                Text{
                    id: text_main_3
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.pixelSize: 20
                    text: "Step 3. Set Margin"
                }
                Slider{
                    id: slider_margin
                    anchors.top: text_main_3.bottom
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.topMargin: 50
                    from: 0
                    to: 1
                    value: supervisor.getMargin()
                    onValueChanged: {
                        map.update_margin();
                    }
                }
                Text{
                    id: text_margin
                    anchors.top: slider_margin.bottom
                    anchors.topMargin: 20
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.pixelSize: 20
                    text: "Margin [m] = " + slider_margin.value
                }

                //List Object
                Component {
                    id: locationCompo
                    Item {
                        width: 250; height: 30
                        Text {
                            id: text_loc
                            anchors.centerIn: parent
                            text: name
                            font.bold: iscol
                            color: iscol?"red":"black"
                        }
                        Rectangle//리스트의 구분선
                        {
                            id:line
                            width:parent.width
                            anchors.bottom:parent.bottom//현재 객체의 아래 기준점을 부모객체의 아래로 잡아주어서 위치가 아래로가게 설정
                            height:1
                            color:"black"
                        }
                        MouseArea{
                            id:area_compo
                            anchors.fill:parent
                            onClicked: {
                                map.select_location = supervisor.getLocNum(name);
                                print("select location = "+map.select_location);
                                list_location.currentIndex = index;
                                map.update_canvas_all();
                            }
                        }
                    }
                }
                ListView {
                    id: list_location
                    width: 250
                    height: 400
                    anchors.top: text_margin.bottom
                    anchors.topMargin: 30
                    anchors.left: parent.left
                    anchors.leftMargin: 30
                    clip: true
                    model: ListModel{}
                    delegate: locationCompo
                    highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
                    focus: true
                }

                Column{
                    id: menubar_location
                    anchors.verticalCenter: list_location.verticalCenter
                    anchors.left: list_location.right
                    anchors.leftMargin: 40
                    spacing: 30
                    Repeater{
                        model: ["move","add","edit","remove"]
                        Rectangle{
                            id: btn4
                            width: 60
                            height: 60
                            color: {
                                if(map.tool == "ADD_LOCATION" && modelData == "add")
                                    "blue"
                                else if(map.tool == "EDIT_LOCATION" && modelData == "edit")
                                    "blue"
                                else
                                    "gray"


                            }
                            radius: 10
                            Image{
                                anchors.centerIn:  parent
                                antialiasing: true
                                mipmap: true
                                scale: {(height>width?parent.width/height:parent.width/width)*0.8}
                                source:{
                                    if(modelData == "edit"){
                                        "icon/btn_wait.png"
                                    }else if(modelData == "remove"){
                                        "icon/btn_no.png"
                                    }else if(modelData == "add"){
                                        "icon/btn_yes.png"
                                    }else if(modelData == "move"){
                                        "icon/btn_minimize.png"
                                    }
                                }
                            }
                            Text{
                                anchors.centerIn: parent
                                text: modelData
                            }
                            MouseArea{
                                anchors.fill: parent
                                onClicked: {
                                    if(modelData == "edit"){
                                        map.tool = "EDIT_LOCATION";
                                    }else if(modelData == "remove"){
                                        if(list_location.currentIndex > 0){
                                            supervisor.removeLocation(list_location.model.get(list_location.currentIndex).name);
                                            map.map.select_location = -1;
                                            map.update_canvas_all();
                                        }
                                    }else if(modelData == "add"){
                                        if(map.tool == "ADD_LOCATION"){
                                            if(map.new_loc_available){
                                                popup_add_location.open();
                                            }else{

                                            }
                                        }else{
                                            map.tool = "ADD_LOCATION";
                                        }
                                    }else if(modelData == "move"){
                                        map.tool = "MOVE";
                                    }
                                }
                            }
                        }
                    }
                }

                Rectangle{
                    width: parent.width/2
                    height: 60
                    anchors.bottom: parent.bottom
                    radius: 10
                    border.width: 2
                    border.color: "gray"
                    Text{
                        anchors.centerIn: parent
                        text: "Previous"
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked:{
                            map.init_mode();
                            map.state_annotation = "OBJECT";
                            loader_menu.sourceComponent = menu_annot_object;
                        }
                    }
                }
                Rectangle{
                    width: parent.width/2
                    height: 60
                    anchors.bottom: parent.bottom
                    anchors.right: parent.right
                    radius: 10
                    border.width: 2
                    border.color: "gray"
                    Text{
                        anchors.centerIn: parent
                        text: "Next"
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked:{
                            map.init_mode();
                            map.state_annotation = "TRAVELLINE";
                            loader_menu.sourceComponent = menu_annot_tline;
                        }
                    }
                }
            }
        }

    }
    Component{
        id: menu_annot_tline
        Item{
            id: menu_travelline
            objectName: "menu_travelline"
            anchors.fill: parent
            Component.onCompleted: {
                var travel_num = supervisor.getTlineSize();
                list_travel_line.model.clear();
                for(var i=0; i<travel_num; i++){
                    list_travel_line.model.append({"name":supervisor.getTlineName(i)});
                }
                map.select_travel_line = 0;

                var line_num = supervisor.getTlineSize(map.select_travel_line);
                list_line.model.clear();
                for(i=0; i<line_num; i=i+2){
                    list_line.model.append({"name":"line_" + Number(i/2)});
                }
                map.update_canvas_all();
            }
            function getcur(){
                return list_line.currentIndex;
            }
            function setcur(index){
                list_line.currentIndex = index;
            }
            function update(){
                var travel_num = supervisor.getTlineSize();
                list_travel_line.model.clear();
                for(var i=0; i<travel_num; i++){
                    list_travel_line.model.append({"name":supervisor.getTlineName(i)});
                }

                var line_num = supervisor.getTlineSize(map.select_travel_line);
                print(line_num);
                list_line.model.clear();
                for(i=0; i<line_num; i=i+2){
                    list_line.model.append({"name":"line_" + Number(i/2)});
                }
                list_line.currentIndex = line_num-1;

                var line_num = supervisor.getTlineSize(map.select_travel_line);
                print(line_num);
                list_line.model.clear();
                for(var i=0; i<line_num; i=i+2){
                    list_line.model.append({"name":"line_" + Number(i/2)});
                }
            }

            Rectangle{
                anchors.fill: parent
                color: "transparent"
                Text{
                    id: text_main_4
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.pixelSize: 20
                    text: "Step 4. Travel Line"
                }
                //List Object
                Component {
                    id: lineCompo
                    Item {
                        width: 250; height: 30
                        Text {
                            anchors.centerIn: parent
                            text: name
                        }
                        Rectangle//리스트의 구분선
                        {
                            id:line
                            width:parent.width
                            anchors.bottom:parent.bottom//현재 객체의 아래 기준점을 부모객체의 아래로 잡아주어서 위치가 아래로가게 설정
                            height:1
                            color:"black"
                        }
                        MouseArea{
                            id:area_compo
                            anchors.fill:parent
                            onClicked: {
                                map.select_line = index;
                                print("select line = "+map.select_line);
                                list_line.currentIndex = index;
                                map.update_canvas_all();
                            }
                        }
                    }
                }
                Component {
                    id: travellineCompo
                    Item {
                        width: 250; height: 30
                        Text {
                            anchors.centerIn: parent
                            text: name
                        }
                        Rectangle//리스트의 구분선
                        {
                            id:line
                            width:parent.width
                            anchors.bottom:parent.bottom//현재 객체의 아래 기준점을 부모객체의 아래로 잡아주어서 위치가 아래로가게 설정
                            height:1
                            color:"black"
                        }
                        MouseArea{
                            id:area_compo
                            anchors.fill:parent
                            onClicked: {
                                map.select_travel_line = index;
                                print("select travel line = "+map.select_travel_line);
                                list_travel_line.currentIndex = index;
                                updatelistline();
                                map.update_canvas_all();
                            }
                        }
                    }
                }
                ListView{
                    id: list_travel_line
                    width: 250
                    height: 100
                    anchors.top: text_main_4.bottom
                    anchors.topMargin: 30
                    anchors.left: parent.left
                    anchors.leftMargin: 30
                    clip: true
                    model: ListModel{}
                    delegate: travellineCompo
                    highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
                    focus: true
                }

                ListView {
                    id: list_line
                    width: 250
                    height: 200
                    anchors.top: list_travel_line.bottom
                    anchors.topMargin: 30
                    anchors.left: parent.left
                    anchors.leftMargin: 30
                    clip: true
                    model: ListModel{}
                    delegate: lineCompo
                    highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
                    focus: true
                }

                Column{
                    id: menubar_line
                    anchors.verticalCenter: list_line.verticalCenter
                    anchors.left: list_line.right
                    anchors.leftMargin: 40
                    spacing: 30
                    Repeater{
                        model: ["add","remove"]
                        Rectangle{
                            id: btn5
                            width: 60
                            height: 60
                            color: {
                                if(map.tool == "ADD_LINE" && modelData == "add")
                                    "blue"
                                else
                                    "gray"
                            }
                            radius: 10
                            Image{
                                anchors.centerIn:  parent
                                antialiasing: true
                                mipmap: true
                                scale: {(height>width?parent.width/height:parent.width/width)*0.8}
                                source:{
                                    if(modelData == "remove"){
                                        "icon/btn_no.png"
                                    }else if(modelData == "add"){
                                        "icon/btn_yes.png"
                                    }
                                }
                            }
                            Text{
                                anchors.centerIn: parent
                                text: modelData
                            }

                            MouseArea{
                                anchors.fill: parent
                                onClicked: {
                                    if(modelData == "remove"){
                                        supervisor.removeTline(0,list_line.currentIndex);
                                        map.update_canvas_all();
                                    }else if(modelData == "add"){
                                        if(map.tool == "ADD_LINE"){
                                            if(map.new_line_point1 && map.new_line_point2){
                                                supervisor.addTline(0,map.new_line_x1,map.new_line_y1,map.new_line_x2,map.new_line_y2);
                                            }
                                            //cancel
                                            map.new_line_point1 = false;
                                            map.new_line_point2 = false;
                                            map.tool = "MOVE";

                                        }else{
                                            map.tool = "ADD_LINE";
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                Rectangle{
                    width: parent.width/2
                    height: 60
                    anchors.bottom: parent.bottom
                    radius: 10
                    border.width: 2
                    border.color: "gray"
                    Text{
                        anchors.centerIn: parent
                        text: "Previous"
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked:{
                            map.init_mode();
                            map.state_annotation = "LOCATION";
                            loader_menu.sourceComponent = menu_annot_location;
                        }
                    }
                }
                Rectangle{
                    width: parent.width/2
                    height: 60
                    anchors.bottom: parent.bottom
                    anchors.right: parent.right
                    radius: 10
                    border.width: 2
                    border.color: "gray"
                    Text{
                        anchors.centerIn: parent
                        text: "Next"
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked:{
                            map.init_mode();
                            map.state_annotation = "SAVE";
                            loader_menu.sourceComponent = menu_annot_save;
                        }
                    }
                }
            }
        }

    }
    Component{
        id: menu_annot_save
        Item{
            id: menu_save
            objectName: "menu_save"
            anchors.fill: parent
            Rectangle{
                anchors.fill: parent
                color: "transparent"
                Text{
                    id: text_main_5
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.pixelSize: 20
                    text: "Save"
                }
                //현재 어노테이션 상태 체크 화면

                //저장
                Rectangle{
                    id: btn_save_meta
                    width: 100
                    height: 60
                    anchors.top: text_main_5.bottom
                    anchors.topMargin: 50
                    anchors.right: parent.horizontalCenter
                    anchors.rightMargin: 30
                    radius: 10
                    border.width: 2
                    border.color: "gray"
                    Text{
                        anchors.centerIn: parent
                        text: "Meta 저장"
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked:{
                            supervisor.saveMetaData("setting/map_meta.ini");
                        }
                    }
                }
                Rectangle{
                    id:btn_save_annot
                    width: 100
                    height: 60
                    anchors.top: text_main_5.bottom
                    anchors.topMargin: 50
                    anchors.left: parent.horizontalCenter
                    anchors.leftMargin: 30
                    radius: 10
                    border.width: 2
                    border.color: "gray"
                    Text{
                        anchors.centerIn: parent
                        text: "Annot 저장"
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked:{
                            supervisor.saveAnnotation("setting/annotation.ini");
                        }
                    }
                }
                //서버에 전송
                Rectangle{
                    width: 100
                    height: 60
                    anchors.top: btn_save_annot.bottom
                    anchors.topMargin: 50
                    anchors.horizontalCenter: parent.horizontalCenter
                    radius: 10
                    border.width: 2
                    border.color: "gray"
                    Text{
                        anchors.centerIn: parent
                        text: "서버에 전송"
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked:{
                            supervisor.sendMaptoServer();
                        }
                    }
                }

                //뒤로가기
                Rectangle{
                    width: parent.width/2
                    height: 60
                    anchors.bottom: parent.bottom
                    anchors.left: parent.left
                    radius: 10
                    border.width: 2
                    border.color: "gray"
                    Text{
                        anchors.centerIn: parent
                        text: "Previous"
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked:{
                            map.state_annotation = "TRAVELLINE";
                            loader_menu.sourceComponent = menu_annot_tline;
                            map.update_canvas_all();
                        }
                    }
                }
                Rectangle{
                    width: parent.width/2
                    height: 60
                    anchors.bottom: parent.bottom
                    anchors.right: parent.right
                    radius: 10
                    border.width: 2
                    border.color: "gray"
                    Text{
                        anchors.centerIn: parent
                        text: "Confirm"
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked:{
                            backPage();
                        }
                    }
                }
            }
        }

    }

    function updatemap(){
        map.update_map_variable();
        map.update_canvas_all();
    }

    ////////*********************Timer********************************************************
    Timer{
        id: timer_get_joy
        interval: 100
        running: false
        repeat: true
        onTriggered: {
            joystick_connection = supervisor.isconnectJoy();
            if(joystick_connection){
                if(joy_axis_left_ud == supervisor.getJoyAxis(1) && joy_axis_right_rl == supervisor.getJoyAxis(2)){

                }else{
                    joy_axis_left_ud = supervisor.getJoyAxis(1);
                    joy_axis_right_rl = supervisor.getJoyAxis(2);
                    if(joy_axis_left_ud != 0){
                        loader_menu.item.remote_input_xy(joy_axis_left_ud,0);
                    }else{
                        loader_menu.item.remote_input_xy(0,0);
                    }

                    if(joy_axis_right_rl != 0){
                        loader_menu.item.remote_input_th(0,joy_axis_right_rl);
                    }else{
                        loader_menu.item.remote_input_th(0,0);
                    }
                }
            }else{
                joy_axis_left_ud = 0;
                joy_axis_right_rl = 0;
                loader_menu.item.remote_input_xy(0,0);
                loader_menu.item.remote_input_th(0,0);
            }
        }
    }
    Timer{
        id: timer_mapping
        interval: 500
        running: false
        repeat: true
        onTriggered: {

            if(supervisor.getMappingflag()){
                //Mapping update
                map.loadmapping();
                supervisor.setMappingflag(false);
            }
        }
    }
    Timer{
        id: check_slam_init_timer
        interval: 1000
        running: false
        repeat: true
        property int trigger_cnt: 0
        onTriggered: {
            if(supervisor.getRobotState() == 7){
                if(slam_initializing == false){
                    slam_initializing = true;
                }
            }else{
                if(slam_initializing){
                    slam_initializing = false;
                    check_slam_init_timer.stop();
                }else{
                    if(trigger_cnt++ > 10){
                        print("slam auto init fail");
                        check_slam_init_timer.stop();
                    }
                }
            }
        }
    }

    //Dialog(Popup) ================================================================
    Popup{
        id: popup_add_object
//        visible: false
        width: 400
        height: 300
        anchors.centerIn: parent
        background: Rectangle{
            anchors.fill:parent
            color: "white"
        }

        Text{
            anchors.horizontalCenter: parent.horizontalCenter
            text: "Add Object"
            font.pixelSize: 20
            font.bold: true
        }
        TextField{
            id: textfield_name
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 100
            width: 200
            height: 60
            placeholderText: "(obj_name)"
            font.pointSize: 20
        }
        Rectangle{
            id: btn_add_object_confirm
            width: 60
            height: 50
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 50
            anchors.right: parent.horizontalCenter
            anchors.rightMargin: 20
            color: "gray"
            Text{
                anchors.centerIn: parent
                text: "확인"
            }
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    if(textfield_name.text == ""){
                        textfield_name.color = "red";
                    }else{
                        supervisor.addObject(textfield_name.text);
                        map.update_canvas_all();
                        map.tool = "MOVE";
                        popup_add_object.close();

                    }
                }
            }
        }
        Rectangle{
            id: btn_add_object_cancel
            width: 60
            height: 50
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 50
            anchors.left: parent.horizontalCenter
            anchors.leftMargin: 20
            color: "gray"
            Text{
                anchors.centerIn: parent
                text: "취소"
            }
            MouseArea{
                anchors.fill: parent
                onClicked: {
//                    popup_add_object.visible = false;
                    popup_add_object.close();
                }
            }
        }
    }

    Popup{
        id: popup_add_location
//        visible: false
        width: 400
        height: 300
        anchors.centerIn: parent
        background: Rectangle{
            anchors.fill:parent
            color: "white"
        }

        Text{
            anchors.horizontalCenter: parent.horizontalCenter
            text: "Add Location"
            font.pixelSize: 20
            font.bold: true
        }
        TextField{
            id: textfield_name2
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 100
            width: 200
            height: 60
            placeholderText: "(loc_name)"
            font.pointSize: 20
        }
        Rectangle{
            id: btn_add_loc_confirm
            width: 60
            height: 50
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 50
            anchors.right: parent.horizontalCenter
            anchors.rightMargin: 20
            color: "gray"
            Text{
                anchors.centerIn: parent
                text: "확인"
            }
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    if(textfield_name2.text == ""){
                        textfield_name2.color = "red";
                    }else{
                        supervisor.addLocation(textfield_name2.text, map.new_loc_x, map.new_loc_y, map.new_loc_th);

                        map.tool = "MOVE";
                        map.new_location = false;
                        map.new_loc_x = 0;
                        map.new_loc_y = 0;
                        map.new_loc_th = 0;
                        map.new_loc_available = false;
                        popup_add_location.close();
                        map.update_canvas_all();
                    }
                }
            }
        }
        Rectangle{
            id: btn_add_loc_cancel
            width: 60
            height: 50
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 50
            anchors.left: parent.horizontalCenter
            anchors.leftMargin: 20
            color: "gray"
            Text{
                anchors.centerIn: parent
                text: "취소"
            }
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    popup_add_location.close();
                }
            }
        }
    }

    Popup{
        id: popup_add_travelline
        width: 400
        height: 300
        anchors.centerIn: parent
        background: Rectangle{
            anchors.fill:parent
            color: "white"
        }

        Text{
            anchors.horizontalCenter: parent.horizontalCenter
            text: "Add Location"
            font.pixelSize: 20
            font.bold: true
        }
        TextField{
            id: textfield_name3
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 100
            width: 200
            height: 60
            placeholderText: "(line_name)"
            font.pointSize: 20
        }
        Rectangle{
            id: btn_add_line_confirm
            width: 60
            height: 50
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 50
            anchors.right: parent.horizontalCenter
            anchors.rightMargin: 20
            color: "gray"
            Text{
                anchors.centerIn: parent
                text: "확인"
            }
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    if(textfield_name3.text == ""){
                        textfield_name3.color = "red";
                    }else if(map.isnewline){
                        supervisor.addTline(textfield_name3.text, map.new_line_x1, map.new_line_y1, map.new_line_x2, map.new_line_y2);
                        map.isnewline = false;
                        map.new_line_x1 = 0;
                        map.new_line_x2 = 0;
                        map.new_line_y1 = 0;
                        map.new_line_y2 = 0;
                        map.tool = "MOVE";
                        popup_add_travelline.close();
                        map.update_canvas_all();
                    }else{
                        popup_add_travelline.close();
                    }
                }
            }
        }
        Rectangle{
            id: btn_add_line_cancel
            width: 60
            height: 50
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 50
            anchors.left: parent.horizontalCenter
            anchors.leftMargin: 20
            color: "gray"
            Text{
                anchors.centerIn: parent
                text: "취소"
            }
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    popup_add_travelline.close();
                }
            }
        }
    }

    function loadmap(path){
        map.loadmap(path);
        updatemap();
        map.update_canvas_all();
    }

    function init(){
        if(map_mode == 1){
            map.mapping_mode = true;
            map.just_show_map = true;
            loader_menu.sourceComponent = menu_slam;
            timer_get_joy.start();
        }else if(map_mode == 2){
            timer_get_joy.stop();
            loader_menu.sourceComponent = menu_annot_state;
            map.state_annotation = "NONE";
        }
        map.init();
        loadmap(map_path);
    }

    function updateobject(){
        loader_menu.item.update();
    }
    function updatelocation(){
        loader_menu.item.update();
    }
    function updatetravelline(){
        loader_menu.item.update();
    }
    function updatelistline(){
        loader_menu.item.update();
    }

}
