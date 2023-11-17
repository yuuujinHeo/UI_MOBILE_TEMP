import QtQuick 2.12
import QtQuick.Controls 2.12
import "."
import io.qt.Supervisor 1.0

Item {
    id: current_map
    objectName: "current_map"

    property int _width: 600
    property int _height: 600

    width: _width
    height: _height

    property bool is_enabled: false
    property bool show_meta_data: true
    property bool flag_map: supervisor.getMapState()
    property bool flag_path_changed: false
    property bool flag_map_load: false
    property int image_width: 1000
    property int image_height: 1000
    property int origin_x: 500
    property int origin_y: 500
    property var map_data

    property var robot_radius: 0.25
    property var grid_size: 0.02

    property int location_num: supervisor.getLocationNum();
    property int path_num: supervisor.getPathNum();
    property int object_num: supervisor.getObjectNum();

    property var location_types
    property var location_x
    property var location_y
    property var location_th

    property var path_x
    property var path_y
    property var path_th

    property var robot_x: supervisor.getRobotx()/grid_size;
    property var robot_y: supervisor.getRoboty()/grid_size;
    property var robot_th:-supervisor.getRobotth()-Math.PI/2;
    onRobot_xChanged: {
        canvas_cur_map.requestPaint();
    }
    onRobot_yChanged: {
        canvas_cur_map.requestPaint();
    }
    onRobot_thChanged: {
        canvas_cur_map.requestPaint();
    }
    Behavior on robot_x{
        NumberAnimation{
            duration: 200
        }
    }
    Behavior on robot_y{
        NumberAnimation{
            duration: 200
        }
    }
    Behavior on robot_th{
        NumberAnimation{
            duration: 200
        }
    }

    Timer{
        id: update_map
        running: true
        repeat: true
        interval: 200
        onTriggered: {
            robot_x = supervisor.getRobotx()/grid_size;
            robot_y = supervisor.getRoboty()/grid_size;
            robot_th = -supervisor.getRobotth()-Math.PI/2;
            path_num = supervisor.getPathNum();
        }
    }

    Component.onCompleted: {
        print("map downloading..");
        location_num = supervisor.getLocationNum();
        object_num = supervisor.getObjectNum();
        origin_x = supervisor.getOrigin()[0];
        origin_y = supervisor.getOrigin()[1];
        grid_size = supervisor.getGridWidth();
        canvas_map.requestPaint();
        canvas_cur_map.requestPaint();
    }

    Image{
        id: map_image
        visible: false
        onSourceChanged: {
            print("Map Current source changed: "+source);
            canvas_map.requestPaint();
        }
    }

    function canvas_draw_path(){
        var ctx = canvas_cur_map.getContext('2d');
        path_num = supervisor.getPathNum();
        path_x = robot_x;
        path_y = robot_y;
        path_th = robot_th;
        ctx.lineWidth = 2;
        for(var i=0; i<path_num; i++){
            var path_x_before = path_x;
            var path_y_before = path_y;
            var path_th_before = path_th;
            path_x = supervisor.getPathx(i)/grid_size;
            path_y = supervisor.getPathy(i)/grid_size;
            path_th = -supervisor.getPathth(i)-Math.PI/2;

            ctx.strokeStyle = "yellow";
            ctx.beginPath();
            if(i>0){
                ctx.moveTo(path_x_before+origin_x,path_y_before+origin_y);
                ctx.lineTo(path_x+origin_x,path_y+origin_y);
                ctx.stroke()
            }

        }

        if(path_num > 0){
            //target Pos
            ctx.strokeStyle = "yellow";
            ctx.beginPath();
            ctx.moveTo(path_x+origin_x,path_y+origin_y);
            ctx.arc(path_x+origin_x,path_y+origin_y,robot_radius/grid_size, path_th, path_th+2*Math.PI, true);
            ctx.stroke()
            ctx.fill("black")
            ctx.moveTo(path_x+origin_x,path_y+origin_y);
            ctx.lineTo(path_x+origin_x,path_y+origin_y)
            ctx.stroke()
        }
    }

    function canvas_draw_local_path(){
        var ctx = canvas_cur_map.getContext('2d');
        ctx.lineWidth = 1;
        ctx.strokeStyle = "red";
        ctx.fillStyle = "red";
        if(path_num != 0){
            var localpath_num = supervisor.getLocalPathNum();
            for(var i=0; i<localpath_num; i++){
                ctx.beginPath();
                var local_x = supervisor.getLocalPathx(i)/grid_size +origin_x;
                var local_y = supervisor.getLocalPathy(i)/grid_size +origin_y;
                ctx.moveTo(local_x,local_y);
                ctx.arc(local_x,local_y,2,0, Math.PI*2);
                ctx.closePath();
                ctx.fill();
                ctx.stroke();
            }
        }

    }

    function canvas_draw_robot(){
        var ctx = canvas_cur_map.getContext('2d');
        //Robot Cur Pos
        robot_x = supervisor.getRobotx()/grid_size;
        robot_y = supervisor.getRoboty()/grid_size;
        robot_th = -supervisor.getRobotth()-Math.PI/2;
        ctx.strokeStyle = "cyan";
        ctx.fillStyle = "black";
        ctx.beginPath();
        ctx.moveTo(robot_x+origin_x,robot_y+origin_y);
        ctx.arc(robot_x+origin_x,robot_y+origin_y,robot_radius/grid_size, robot_th, robot_th+2*Math.PI, true);
        ctx.stroke()
        ctx.fill("black")
        ctx.moveTo(robot_x+origin_x,robot_y+origin_y);
        ctx.lineTo(robot_x+origin_x,robot_y+origin_y)
        ctx.stroke()
    }

    function canvas_draw_locations(){
        var ctx = canvas_map.getContext('2d');
        ctx.lineWidth = 1;
        ctx.lineCap = "round"

        //Location Load
        location_num = supervisor.getLocationNum();
        for(var i=0; i<location_num; i++){
            location_types = supervisor.getLocationTypes(i);
            location_x = supervisor.getLocationx(i)/grid_size + origin_x;
            location_y = supervisor.getLocationy(i)/grid_size + origin_y;
            location_th = -supervisor.getLocationth(i)-Math.PI/2;

            if(location_types.slice(0,4) == "Char"){
                ctx.strokeStyle = "green";
            }else if(location_types.slice(0,4) == "Rest"){
                ctx.strokeStyle = "white";
            }else if(location_types.slice(0,4) == "Patr"){
                ctx.strokeStyle = "blue";
            }else if(location_types.slice(0,4) == "Tabl"){
                ctx.strokeStyle = "gray";
            }
            ctx.beginPath();
            ctx.moveTo(location_x,location_y);
            ctx.arc(location_x,location_y,robot_radius/grid_size, location_th, location_th+2*Math.PI, true);
            ctx.moveTo(location_x,location_y);
            ctx.stroke()
        }
    }

    function canvas_draw_object(){
        var ctx = canvas_map.getContext('2d');
        ctx.lineWidth = 1;
        ctx.lineCap = "round";
        ctx.fillStyle = "steelblue";
        ctx.strokeStyle = "blue";

        //Object Load
        object_num = supervisor.getObjectNum()
        for(var i=0; i<object_num; i++){
            var obj_type = supervisor.getObjectName(i);
            var obj_size = supervisor.getObjectPointSize(i);
            var obj_x = supervisor.getObjectX(i,0)/grid_size +origin_x;
            var obj_y = supervisor.getObjectY(i,0)/grid_size +origin_y;
            var obj_x0 = obj_x;
            var obj_y0 = obj_y;

            ctx.beginPath();
            ctx.moveTo(obj_x,obj_y);
            for(var j=1; j<obj_size; j++){
                obj_x = supervisor.getObjectX(i,j)/grid_size + origin_x;
                obj_y = supervisor.getObjectY(i,j)/grid_size + origin_y;
                ctx.lineTo(obj_x,obj_y);
            }
            ctx.lineTo(obj_x0,obj_y0);
            ctx.closePath();
            ctx.fill();
            ctx.stroke();
        }
    }

    Rectangle{
        id: rect_cur_map
        width: parent.width
        height: parent.height
        clip: true
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right;

        border.width: 3
        border.color:"black"
        color: "black"

        Canvas{
            id: canvas_map
            x: canvas_cur_map.x
            y: canvas_cur_map.y
            width: canvas_cur_map.width
            height: canvas_cur_map.height
            scale: canvas_cur_map.scale
            antialiasing: true
            onPaint:{
                if(is_enabled){
                    var ctx = getContext("2d");
                    ctx.clearRect(0,0,canvas_map.width,canvas_map.height);
                    ctx.drawImage(map_image, 0,0,image_width,image_height);

                    if(show_meta_data){
                        canvas_draw_object();
                    }
                }
            }
        }

        Canvas{
            id: canvas_cur_map
            x: - origin_x + rect_cur_map.width/2;
            y: - origin_y + rect_cur_map.height/2;
            width: image_width
            height: image_height
            antialiasing: true
            onPaint:{
                if(is_enabled){
                    var ctx = getContext("2d");
                    ctx.clearRect(0,0,canvas_cur_map.width,canvas_cur_map.height);
                    if(show_meta_data){
                        canvas_draw_path();
                        canvas_draw_local_path();
                        canvas_draw_robot();
                    }
                }
            }
            Behavior on scale{
                NumberAnimation{
                    duration: 300
                }
            }
            Behavior on x{
                NumberAnimation{
                    duration: 100
                }
            }
            Behavior on y{
                NumberAnimation{
                    duration: 100
                }
            }
            onXChanged: {
                if(canvas_cur_map.x  > canvas_cur_map.width*(canvas_cur_map.scale - 1)/2){
                    canvas_cur_map.x = canvas_cur_map.width*(canvas_cur_map.scale - 1)/2
                }else if(canvas_cur_map.x < -(canvas_cur_map.width*(canvas_cur_map.scale - 1)/2 + canvas_cur_map.width - rect_cur_map.width)){
                    canvas_cur_map.x = -(canvas_cur_map.width*(canvas_cur_map.scale - 1)/2 + canvas_cur_map.width - rect_cur_map.width)
                }
                requestPaint();
            }
            onYChanged: {
                if(canvas_cur_map.y  > canvas_cur_map.height*(canvas_cur_map.scale - 1)/2){
                    canvas_cur_map.y = canvas_cur_map.height*(canvas_cur_map.scale - 1)/2
                }else if(canvas_cur_map.y < -(canvas_cur_map.height*(canvas_cur_map.scale - 1)/2 + canvas_cur_map.height - rect_cur_map.height)){
                    canvas_cur_map.y = -(canvas_cur_map.height*(canvas_cur_map.scale - 1)/2 + canvas_cur_map.height - rect_cur_map.height)
                }
                requestPaint();
            }
            onScaleChanged: {
                if(canvas_cur_map.x  > canvas_cur_map.width*(canvas_cur_map.scale - 1)/2){
                    canvas_cur_map.x = canvas_cur_map.width*(canvas_cur_map.scale - 1)/2
                }else if(canvas_cur_map.x < -(canvas_cur_map.width*(canvas_cur_map.scale - 1)/2 + canvas_cur_map.width - rect_cur_map.width)){
                    canvas_cur_map.x = -(canvas_cur_map.width*(canvas_cur_map.scale - 1)/2 + canvas_cur_map.width - rect_cur_map.width)
                }

                if(canvas_cur_map.y  > canvas_cur_map.height*(canvas_cur_map.scale - 1)/2){
                    canvas_cur_map.y = canvas_cur_map.height*(canvas_cur_map.scale - 1)/2
                }else if(canvas_cur_map.y < -(canvas_cur_map.height*(canvas_cur_map.scale - 1)/2 + canvas_cur_map.height - rect_cur_map.height)){
                    canvas_cur_map.y = -(canvas_cur_map.height*(canvas_cur_map.scale - 1)/2 + canvas_cur_map.height - rect_cur_map.height)
                }
                requestPaint();
            }

            MultiPointTouchArea{
                id: area_map_touch
                anchors.fill: parent
                minimumTouchPoints: 1
                maximumTouchPoints: 2
                property var gesture: "none"
                property var dmoveX : 0;
                property var dmoveY : 0;
                property var startX : 0;
                property var startY : 0;
                property var startDist : 0;
                touchPoints: [TouchPoint{id:point1},TouchPoint{id:point2}]
                onPressed: {
                    gesture = "drag";
                    if(point1.pressed && point2.pressed){
                        var dx = Math.abs(point1.x-point2.x);
                        var dy = Math.abs(point1.y-point2.y);
                        var dist = Math.sqrt(dx*dx + dy*dy);
                        area_map_touch.startX = (point1.x+point2.x)/2;
                        area_map_touch.startY = (point1.y+point2.y)/2;
                        area_map_touch.startDist = dist;
                    }else if(point1.pressed){
                        area_map_touch.startX = point1.x;
                        area_map_touch.startY = point1.y;
                    }

                }
                onReleased: {
                    if(!point1.pressed&&!point2.pressed){
                        gesture = "none"
                    }
                }
                onTouchUpdated:{
                    if(is_enabled){
                        var ctx = canvas_cur_map.getContext('2d');
                        var dx = Math.abs(point1.x-point2.x);
                        var dy = Math.abs(point1.y-point2.y);
                        var mx = (point1.x+point2.x)/2;
                        var my = (point1.y+point2.y)/2;
                        var dist = Math.sqrt(dx*dx + dy*dy);
                        var dscale = (dist)/startDist;
                        var new_scale = canvas_cur_map.scale*dscale;
                        if(point1.pressed&&point2.pressed){

                            if(new_scale > 5)   new_scale = 5;

                            if(canvas_cur_map.width*new_scale < rect_cur_map.width){
                                new_scale = rect_cur_map.width/canvas_cur_map.width;
                            }
                            canvas_cur_map.scale = new_scale;

                            dmoveX = (mx - startX);
                            dmoveY = (my - startY);
                            canvas_cur_map.x += dmoveX;
                            canvas_cur_map.y += dmoveY;

                            canvas_cur_map.requestPaint()
                        }else{
                            dmoveX = (point1.x - startX);
                            dmoveY = (point1.y - startY);
                            canvas_cur_map.x += dmoveX;
                            canvas_cur_map.y += dmoveY;

                            canvas_cur_map.requestPaint()
                        }
                    }
                }
            }
        }
    }
}
