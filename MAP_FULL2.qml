import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.2
import QtGraphicalEffects 1.0
import "."
import io.qt.Supervisor 1.0
import io.qt.MapViewer 1.0


Item {
    id: map_full2
    objectName: "map_full2"
    width: 1000
    height: 1000
    clip: true

    //--------------------------------------- main variables
    property string tool: "move"
    property string map_type: ""
    property string map_name: ""
    property bool map_loaded: false
    property bool touch_on: true
    property bool show_connection: true
    property bool show_button_lidar: false
    property bool show_button_following: false
    property bool show_button_location: false
    property bool show_costmap: false
    property bool show_brush: false
    property bool show_grid: false

    property int obj_sequence: 0

    property var cur_width: 0
    property var cur_color: 0
    //--------------------------------------- SLAM / Localization
    property bool is_slam_running: false

    //0(location patrol) 1:(path patrol)
    property int patrol_mode: 0

    property bool is_edited: false
    property bool is_object_new: false
    property bool is_location_new: false
    property bool is_drawing_undo: false
    property bool is_drawing_redo: false

    onWidthChanged: {
        if(width>0 && height>0){
            supervisor.setMapSize(width, height);
        }
    }

    Component.onCompleted: {
        mapview.setName(objectName);
        supervisor.setName(objectName);
        supervisor.setMapSize(width, height);
    }

    function setEnable(en){
        enabled = en;
        mapview.setActive(en);
        supervisor.setEnable(en);
//        print("set enable ",objectName,en);
    }

    function setViewer(mode){
        supervisor.writelog("[QML MAP] SET Viewer "+objectName+" to "+mode);
        supervisor.setMode(mode);
        show_connection = true;
        show_button_following = true;
        show_button_lidar = true;
        show_button_location = true;
        show_costmap = false;
        show_grid = false;
        if(mode === "annot_drawing"){
            show_connection = false;
            show_button_following = false;
            show_button_lidar = false;
            show_button_location = false;
        }else if(mode === "serving_list"){
            show_connection = false;
            show_button_following = false;
            show_button_lidar = false;
            show_button_location = false;
        }else if(mode === "map_list"){
            show_connection = false;
            show_button_following = false;
            show_button_lidar = false;
            show_button_location = false;
        }else if(mode === "annot_tline"){
            show_connection = false;
            show_button_location = true;
            show_button_following = false;
            show_button_lidar = false;
        }else if(mode === "annot_velmap"){
            show_connection = false;
            show_button_location = true;
            show_button_following = false;
            show_button_lidar = false;
        }else if(mode === "annot_location"){
//            supervisor.setCostMap();
        }else if(mode === "mapping"){
            show_button_following = true;
            show_button_lidar = false;
            show_button_location = false;
        }else if(mode === "local_view"){
            show_connection = false;
            show_button_following = false;
            show_button_lidar = false;
            show_button_location = false;
        }else if(mode === "annot_object"){
            show_connection = true;
            show_button_following = false;
            show_button_lidar = true;
            show_button_location = true;
            show_costmap = true;
        }else if(mode === "current"){

        }else if(mode === "annot_rotate"){
            show_grid = true;
            show_connection = false;
            show_button_following = false;
            show_button_lidar = false;
            show_button_location = false;
        }else if(mode === "localization"){
            show_grid = false;
            show_connection = true;
            show_button_following = false;
            show_button_lidar = false;
            show_button_location = false;
        }else if(mode === "annot_view"){
            show_grid = false;
            show_connection = false;
            show_button_following = false;
            show_button_lidar = false;
            show_button_location = false;
        }
    }

    function reload(){

    }

    function showLocation(onoff){
        supervisor.setShowLocation(onoff);
    }

    function showTravelline(onoff){
        supervisor.setShowTravelline(onoff);
    }

    function showVelocityMap(onoff){
        supervisor.setShowVelocitymap(onoff);
    }

    function checkDrawing(){
        is_drawing_redo = false;
        is_drawing_undo = false;
        if(supervisor.getDrawingFlag()){
            is_drawing_undo = true;
        }
        if(supervisor.getDrawingUndoFlag()){
            is_drawing_redo = true;
        }
    }

    function loadmap(name,type){
        if(typeof(name) === 'undefined'){
            name = supervisor.getMapname();
        }
        if(map_name !== name){
            supervisor.readSetting(name);
            map_name = name;
        }

        print("loadmap "+objectName + " : "+ name,type);
        if(typeof(type) !== 'undefined'){
            map_type = type;
            timer_loadmap.stop();
            map_loaded = true;
            supervisor.loadFile(name,type);
        }else{
            map_loaded = true;
            supervisor.loadFile(name,type);
            if(supervisor.isExistAnnotation(name)){
                map_type = "EDITED";
            }else{
                map_type = "RAW";
            }
        }
        supervisor.setMap();
    }

    function startDrawingT(){
        supervisor.startDrawingTline();
    }

    function stopDrawingT(){
        supervisor.stopDrawingTline();
    }

    function getTFlag(){
        return supervisor.getDrawingTline();
    }

    function loadmapping(){
        supervisor.setMap();
    }

    function setfullscreen(){
        supervisor.setFullScreen();
    }

    function setCurrentLocation(num){
        supervisor.selectLocation(num);
    }

    function setTool(name){
        tool = name;
        supervisor.setTool(name);
    }
    function saveMap(){
        supervisor.saveMap();
        supervisor.slam_map_reload(supervisor.getMapname());
    }
    function drawing_undo(){
        supervisor.undoLine();
    }
    function drawing_redo(){
        supervisor.redoLine();
    }

    function init(){
        clear("all");
        setTool("move");
    }

    function removelocation(num){
        supervisor.removeLocation(num);
    }
    function setTableNumberAuto(){
        supervisor.setTableNumberAuto();
    }
    function getCutFlag(){
        return supervisor.getCutBoxFlag();
    }

    function selectLocation(num){
        map.selectLocation(num);
    }

    function clear(mode){
        if(mode==="obj"){

        }else if(mode === "location"){
            supervisor.clearLocation();
        }else if(mode==="all"){
            supervisor.endSpline(false);
            supervisor.clearDrawing();
            supervisor.clearLocation();
            supervisor.clearObjectAll();
            supervisor.clearInitPose();
        }else if(mode==="tline"){
            supervisor.clearDrawing();

        }else if(mode==="spline"){
            supervisor.endSpline(false);
        }else if(mode ==="rotate"){
            supervisor.initRotate();
        }else if(mode === "object"){
            supervisor.clearObject();
        }
    }
    function rotate(dir){
//        print("rotate map : "+dir)
        if(dir === "cw"){
            supervisor.rotateMapCW();
        }else if(dir === "ccw"){
            supervisor.rotateMapCCW();
        }else if(dir === "clear"){
            supervisor.rotateMap(0);
        }else{
            supervisor.rotateMap(dir);
        }
    }
    function save(mode, type, name){
        if(mode==="obj"){
            supervisor.saveObject();
        }else if(mode==="raw"){

        }else if(mode==="edited"){
            supervisor.saveMap();
            supervisor.setMap(map_name);
            supervisor.slam_map_reload(supervisor.getMapname());
        }else if(mode==="location_cur"){
            last_robot_x = supervisor.getlastRobotx();
            last_robot_y = supervisor.getlastRoboty();
            last_robot_th = supervisor.getlastRobotth();
//            /*print(*/last_robot_x,last_robot_y,last_robot_th);
            supervisor.addLocation(last_robot_x,last_robot_y,last_robot_th);
            supervisor.saveLocation(type,0,name);
        }else if(mode==="edit_location"){
            last_robot_x = supervisor.getlastRobotx();
            last_robot_y = supervisor.getlastRoboty();
            last_robot_th = supervisor.getlastRobotth();
//            /*print(*/last_robot_x,last_robot_y,last_robot_th);
            supervisor.editLocation(last_robot_x,last_robot_y,last_robot_th);
        }else if(mode==="location"){
            supervisor.saveLocation(type,0,name);
        }else if(mode==="map_editor"){
            supervisor.saveEditedMap();
        }else if(mode==="tline"){
            supervisor.saveTline();
            supervisor.slam_map_reload(supervisor.getMapname());
        }else if(mode==="tline_temp"){
            supervisor.saveTlineTemp();
        }else if(mode==="spline"){
            supervisor.endSpline(true);
        }else if(mode==="velmap"){
            supervisor.saveVelmap();
            supervisor.slam_map_reload(supervisor.getMapname());
        }else if(mode==="rotate"){
            supervisor.saveRotateMap();
            supervisor.slam_map_reload(supervisor.getMapname());
        }else if(mode==="location_all"){
            supervisor.saveAnnotation(map_name);
//            supervisor.slam_map_reload(supervisor.getMapname());
        }
    }

    function savelocation(mode, type, group, name){
        if(mode==="location_cur"){
           last_robot_x = supervisor.getlastRobotx();
           last_robot_y = supervisor.getlastRoboty();
           last_robot_th = supervisor.getlastRobotth();
//           /*print(*/last_robot_x,last_robot_y,last_robot_th);
           supervisor.addLocation(last_robot_x,last_robot_y,last_robot_th);
           supervisor.saveLocation(type,group, name);
       }else if(mode==="location"){
           supervisor.saveLocation(type,group, name);
       }
    }



//    function savelocation(mode, type, name){
//        if(mode==="cur_pose"){
//            print(last_robot_x,last_robot_y,last_robot_th);
//            supervisor.addLocation(last_robot_x,last_robot_y,last_robot_th);
//            supervisor.saveLocation(type,name);
//        }else if(mode==="new_target"){
//            supervisor.saveLocation(type,name);
//        }
//    }

    function setDrawingColor(color){
        supervisor.setLineColor(color);
        cur_color = color;
    }

    function setDrawingWidth(width){
        supervisor.setLineWidth(width);
        cur_width = width*map_full2.width/supervisor.getFileWidth()/supervisor.getScale() + 2;
    }

    function setAutoInit(x,y,th){
//        print(objectName+" ?:",x,y,th);
        supervisor.setInitPose(x,y,th);
        supervisor.setInitPos(x,y,th);
    }


    MapViewer{
        id: mapview
        width: parent.width
        height: parent.height
        Component.onCompleted: {
        }
        clip: true

        Rectangle{
            id: rect_notice
            anchors.horizontalCenter: parent.horizontalCenter
            width: 300
            height: 60
            y: -10
            radius: 5
            color: color_red
            function show_connect(){
                show_ani.start();
            }
            function unshow_connect(){
                unshow_ani.start();
            }
            NumberAnimation{
                id: show_ani
                target: rect_notice
                property: "y"
                from: -height
                to: -10
                duration: 500
                onStarted: {
                    rect_notice.visible = true;
                }
                onFinished: {

                }
            }
            NumberAnimation{
                id: unshow_ani
                target: rect_notice
                property: "y"
                from: -10
                to: -height
                duration: 500
                onStarted: {
                }
                onFinished: {
                    rect_notice.visible = false;
                }
            }
            visible: false
            onVisibleChanged: {
                if(visible){
                    show_ani.start();
                }
            }
            property string msg: ""
            property bool show_icon: false
            Row{
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                anchors.verticalCenterOffset: 5
                spacing: 10
                Image{
                    width: 30
                    height: 30
                    visible: rect_notice.show_icon
                    anchors.verticalCenter: parent.verticalCenter
                    source: "icon/icon_warning.png"
                    ColorOverlay{
                        source: parent
                        anchors.fill: parent
                        color: "white"
                    }
                }
                Text{
                    text: rect_notice.msg
                    anchors.verticalCenter: parent.verticalCenter
                    font.family: font_noto_b.name
                    font.pixelSize: 20
                    color: "white"
                }
            }
        }

        Canvas{
            anchors.fill: parent
            property int wgrid: 20
            visible: show_grid
            onPaint: {
                var ctx = getContext("2d");
                ctx.lineWidth = 0.5;
                ctx.strokeStyle = "white"
                ctx.beginPath();
                var nrows = height/wgrid;
                ctx.setLineDash([2,5])

                for(var i=0; i<nrows+1; i++){
                    ctx.moveTo(0,wgrid*i);
                    ctx.lineTo(width, wgrid*i);
                }
                var ncols = width/wgrid;
                for(var j=0; j<ncols+1; j++){
                    ctx.moveTo(wgrid*j,0);
                    ctx.lineTo(wgrid*j,height);
                }
                ctx.closePath();
                ctx.stroke();
            }
        }
    }
    MouseArea{
        anchors.fill: parent
        hoverEnabled: true
        enabled: touch_on
        onWheel: {
            if(wheel.angleDelta.y > 0){
                supervisor.zoomIn(mouseX, mouseY);
            }else{
                supervisor.zoomOut(mouseX, mouseY);
            }
        }
    }

    MultiPointTouchArea{
        enabled: touch_on
        anchors.fill: parent
        minimumTouchPoints: 1
        maximumTouchPoints: 2
        property var firstX;
        property var firstY;
        property var firstDist;
        property bool double_touch: false
        property var select_point;
        touchPoints: [TouchPoint{id:point1},TouchPoint{id:point2}]
        onPressed:{
            double_touch = false;
            supervisor.setRobotFollowing(false);
            if(point1.pressed && point2.pressed){
                double_touch = true;
            }else if(point1.pressed){
                firstX = supervisor.getX() + point1.x*supervisor.getScale()*supervisor.getFileWidth()/width;
                firstY = supervisor.getY() + point1.y*supervisor.getScale()*supervisor.getFileWidth()/width;
            }else if(point2.pressed){
                firstX = supervisor.getX() + point2.x*supervisor.getScale()*supervisor.getFileWidth()/width;
                firstY = supervisor.getY() + point2.y*supervisor.getScale()*supervisor.getFileWidth()/width;
            }
            if(tool == "move"){
                if(double_touch){
                    firstX = supervisor.getX() + (point1.x+point2.x)*supervisor.getScale()*supervisor.getFileWidth()/width/2;
                    firstY = supervisor.getY() + (point1.y+point2.y)*supervisor.getScale()*supervisor.getFileWidth()/width/2;
                    var dx = Math.abs(point1.x-point2.x);
                    var dy = Math.abs(point1.y-point2.y);
                    firstDist = Math.sqrt(dx*dx + dy*dy);
                }
            }else if(tool == "draw"){
                supervisor.setShowBrush(true);
                supervisor.startDrawing(firstX, firstY);
            }else if(tool == "draw_rect"){
                supervisor.setShowBrush(false);
                supervisor.startDrawingRect(firstX,firstY);
            }else if(tool == "straight"){
                supervisor.setShowBrush(true);
                supervisor.startDrawingLine(firstX, firstY);
            }else if(tool == "dot_spline"){
//                supervisor.startSpline(firstX, firstY);
                supervisor.addSpline(firstX,firstY);
            }else if(tool == "add_object"){
                supervisor.addObject(firstX,firstY);
            }else if(tool == "edit_object"){
                supervisor.editObjectStart(firstX,firstY);
            }else if(tool == "add_point"){
                supervisor.addObjectPoint(firstX,firstY);
            }else if(tool == "erase"){
                supervisor.setShowBrush(true);
                supervisor.setLineColor(-1);
                supervisor.startDrawing(firstX, firstY);
            }else if( tool === "add_location"){
                supervisor.addLocation(firstX, firstY,0);
            }else if( tool === "edit_location"){
                supervisor.editLocation(firstX, firstY,0);
            }else if(tool === "edit_location_new"){
                supervisor.addLocation(firstX, firstY,0);
            }else if( tool === "slam_init"){
                supervisor.setInitFlag(true);
//                print("Pressed : ",firstX,firstY,0);
                supervisor.setInitPose(firstX,firstY,0);
            }else if(tool === "cut_map"){
                select_point = supervisor.getPointBox(firstX,firstY);
//                if(select_point === -1){
//                    if(double_touch){
//                        firstX = supervisor.getX() + (point1.x+point2.x)*supervisor.getScale()*supervisor.getFileWidth()/width/2;
//                        firstY = supervisor.getY() + (point1.y+point2.y)*supervisor.getScale()*supervisor.getFileWidth()/width/2;
//                        var dx = Math.abs(point1.x-point2.x);
//                        var dy = Math.abs(point1.y-point2.y);
//                        firstDist = Math.sqrt(dx*dx + dy*dy);
//                    }
//                }
            }
        }
        onReleased: {
            supervisor.setShowBrush(false);
            var newX = supervisor.getX() + point1.x*supervisor.getScale()*supervisor.getFileWidth()/width;
            var newY = supervisor.getY() + point1.y*supervisor.getScale()*supervisor.getFileWidth()/width;
            if(!point1.pressed && !point2.pressed){
                if(tool == "move"){
                    if(supervisor.getMode() === "annot_object"){
                        var objnum = supervisor.getObjectNum(newX, newY);
                        if(objnum > -1){
                            loader_page.item.setobjcur(objnum);
                        }else{
                            loader_page.item.setobjcur(-1);
                        }
                    }
                }else if(tool == "draw"){
                    supervisor.endDrawing(newX, newY);
                }else if(tool == "draw_rect"){
                    supervisor.endDrawingRect();
                }else if(tool == "straight"){
                    supervisor.stopDrawingLine(newX, newY);
                }else if(tool == "erase"){
                    supervisor.endDrawing(newX, newY);
                }else if( tool === "edit_location"){
//                    var angle = Math.atan2((newX-firstX),(newY-firstY));
//                    supervisor.editLocation(firstX, firstY,angle);
                }else if(tool == "add_object"){
//                    supervisor
                }else if(tool == "edit_object"){
                    supervisor.setObjPose();
                }else if(tool == "add_point"){

                }else if( tool === "add_location"){

                }else if( tool === "slam_init"){
                    supervisor.setInitFlag(false);
                    var angle = Math.atan2((newY-firstY),(newX-firstX));
//                    print("Released : ",firstX,firstY,angle);
                    supervisor.setInitPos(firstX, firstY, angle);
                    supervisor.slam_setInit();
                }
            }
        }
        onTouchUpdated: {
//            print(point1.pressed,point2.pressed,tool);
            if(point1.pressed || point2.pressed){
                var newX = supervisor.getX() + point1.x*supervisor.getScale()*supervisor.getFileWidth()/width;
                var newY = supervisor.getY() + point1.y*supervisor.getScale()*supervisor.getFileWidth()/width;
                if(tool == "move"){
                    if(double_touch){
                        if(point1.pressed && point2.pressed){
                            newX = (point1.x + point2.x)*supervisor.getScale()/2;
                            newY = (point1.y + point2.y)*supervisor.getScale()/2;

                            var dx = Math.abs(point1.x - point2.x)
                            var dy = Math.abs(point1.y - point2.y)
                            var dist = Math.sqrt(dx*dx + dy*dy);
                            var thres = 10;

                            for(var i=0; i<(firstDist-dist)/thres; i++){
//                                supervisor.scaledOut(1,1);
                                supervisor.zoomOut(newX,newY);
                            }
                            for(var i=0; i<(dist-firstDist)/thres; i++){
//                                supervisor.scaledIn(1,1);
                                supervisor.zoomIn(newX,newY);
                            }
                            firstDist = dist;

//                            print("UPDATE : ",newX,newY,dist);
                            supervisor.setRobotFollowing(false);
                            supervisor.move(firstX-newX, firstY-newY);
                        }else{
                            double_touch = false;
                        }
                    }else{
                        if(point1.pressed){
                            newX = point1.x*supervisor.getScale()*supervisor.getFileWidth()/width;
                            newY = point1.y*supervisor.getScale()*supervisor.getFileWidth()/width;
                        }else if(point2.pressed){
                            newX = point2.x*supervisor.getScale()*supervisor.getFileWidth()/width;
                            newY = point2.y*supervisor.getScale()*supervisor.getFileWidth()/width;
                        }
                        supervisor.setRobotFollowing(false);
                        supervisor.move(firstX-newX, firstY-newY);
                    }
                }else if(tool == "draw"){
                    supervisor.addLinePoint(newX, newY);
                }else if(tool == "draw_rect"){
                    supervisor.setDrawingRect(newX, newY);
                }else if(tool == "cut_map"){
                    supervisor.setBoxPoint(select_point,newX,newY);
                }else if(tool == "straight"){
                    supervisor.setDrawingLine(newX, newY);
                }else if(tool == "erase"){
                    supervisor.addLinePoint(newX, newY);
                }else if(tool == "add_object"){
                    supervisor.setObject(newX,newY);
                }else if(tool == "edit_object"){
                    supervisor.editObject(newX,newY);
                }else if(tool == "add_point"){
                    supervisor.setObject(newX,newY);
                }else if( tool === "edit_location_new"){
                    var angle = Math.atan2((newY-firstY),(newX-firstX));
                    supervisor.addLocation(firstX, firstY,angle);
                }else if( tool === "add_location"){
                    angle = Math.atan2((newY-firstY),(newX-firstX));
                    supervisor.addLocation(firstX, firstY,angle);
                }else if( tool === "edit_location"){
                    angle = Math.atan2((newY-firstY),(newX-firstX));
//                    print(angle, newX-firstX, newY-firstY);
                    supervisor.editLocation(firstX, firstY,angle);
                }else if( tool === "slam_init"){
                    angle = Math.atan2((newY-firstY),(newX-firstX));
//                    print("Update : ",firstX,firstY,angle);
                    supervisor.setInitPose(firstX,firstY,angle);
                }
            }
        }
    }

    //Buttons

    Column{
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.leftMargin: 5
        anchors.topMargin: 5
        spacing: 10

        Rectangle{
            id: btn_robot_following
            width: 40
            height: 40
            radius: 40
            visible: show_button_following
            property bool active: false
            color: active?"#12d27c":"#e8e8e8"
            Image{
                anchors.centerIn: parent
                source: "icon/icon_cur.png"
            }
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    supervisor.setRobotFollowing(true);
                }
            }
        }

        Rectangle{
            id: btn_show_lidar
            width: 40
            height: 40
            radius: 40
            visible: show_button_lidar
            property bool active: false
            color:active?"#12d27c":"#e8e8e8"
            Image{
                anchors.centerIn: parent
                source: "icon/icon_lidar.png"
            }
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    if(parent.active){
                        supervisor.setShowLidar(false);
                    }else{
                        supervisor.setShowLidar(true);
                    }
                }
            }
        }
        Rectangle{
            id: btn_show_location
            width: 40
            height: 40
            radius: 40
            visible: show_button_location
            property bool active: false
            color:  active?"#12d27c":"#e8e8e8"
            Image{
                anchors.centerIn: parent
                width: 32
                height: 30
                source: "icon/icon_location.png"
            }
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    if(parent.active){
                        supervisor.setShowLocation(false);
                    }else{
                        supervisor.setShowLocation(true);
                    }
                }
            }
        }
    }
    Rectangle{
        id: brushview
        visible: show_brush
        width: cur_width
        height: width
        radius: width
        border.width: 1
        border.color: "black"
        anchors.centerIn: parent
    }

    //최초 실행 후 맵 파일을 받아올 수 있을 때까지 1회 수행
    Timer{
        id: timer_loadmap
        running: false//parent.enabled
        repeat: true
        interval: 500
        onTriggered: {
            //맵을 로딩할 수 있을 때
            if(supervisor.isloadMap()){
                //맵 정보 받아옴(경로, 이름)
                map_name = supervisor.getMapname();
                if(supervisor.isExistMap(map_name)){
                    loadmap(map_name,"EDITED");
                }else{
                    loadmap(map_name,"RAW");
                }
                setfullscreen();

                //타이머 종료
                timer_loadmap.stop();
                supervisor.writelog("[QML] Load Map(AUTO) "+parent.objectName+": "+map_name);
            }
        }
    }

    //로봇 연결되면 주기적 수행
    Timer{
        id: update_map
        running: true
        repeat: true
        interval: 500
        onTriggered: {
            btn_show_location.active = supervisor.getshowLocation();
            btn_robot_following.active = supervisor.getRobotFollowing();
            btn_show_lidar.active = supervisor.getShowLidar();
            if(supervisor.getIPCConnection()){
                is_slam_running = supervisor.is_slam_running();
                if(show_connection){
                    if(supervisor.getMappingflag()){
                        rect_notice.visible = true;
                        rect_notice.msg =  qsTr("맵 생성 중");
                        rect_notice.color = color_navy;
                        rect_notice.show_icon = false;
                    }else if(supervisor.getObjectflag()){
                        rect_notice.visible = true;
                        rect_notice.msg =  qsTr("오브젝트 생성 중");
                        rect_notice.color = color_navy;
                        rect_notice.show_icon = false;
                    }else if(supervisor.getLocalizationState()===1){
                        rect_notice.visible = true;
                        rect_notice.msg =  qsTr("위치 초기화 중");
                        rect_notice.color = color_navy;
                        rect_notice.show_icon = false;
                    }else if(!is_slam_running && supervisor.getMode() !== "mapping"){
                        rect_notice.visible = true;
                        rect_notice.msg =  qsTr("주행 활성화 안됨");
                        rect_notice.color = color_red;
                        rect_notice.show_icon = true;
                    }else{
                        rect_notice.visible = false;
                    }
                }else{
                    rect_notice.visible = false;
                }
            }else{
                if(show_connection){

                    rect_notice.visible = true;
                    rect_notice.msg =  qsTr("로봇 연결 안됨");
                    rect_notice.color = color_red;
                    rect_notice.show_icon = true;
                }

            }

        }
    }
}
