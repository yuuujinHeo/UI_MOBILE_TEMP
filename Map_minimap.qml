import QtQuick 2.12
import QtQuick.Controls 2.12
import "."
import io.qt.Supervisor 1.0

Item {
    id: mini_map
    objectName: "mini_map"

    property int _width: 1280
    property int _height: 800
    width: _width
    height: _height
    property int image_width: 1000
    property int image_height: 1000
    property int origin_x: 500
    property int origin_y: 500
    property var robot_radius: 0.25
    property var grid_size: 0.02
    property var map_data

    Image{
        id: map_image
        visible: false
    }

    function set_minimap(){
        var ctx = canvas_mini.getContext('2d');
        ctx.clearRect(0,0,canvas_map.width,canvas_map.height);
        ctx.drawImage(map_image, 0,0,image_width,image_height);
        map_data = ctx.getImageData(0,0,map_image.width, map_image.height);
        ctx.clearRect(0,0,canvas_map.width,canvas_map.height);

        ctx.lineWidth = 0;
        ctx.fillStyle = "red";
        ctx.strokeStyle = "red";

        print("prev set minimap");
        for(var x=0; x<map_data.data.length; x=x+4){
//            print(map_data.data[x]);
            if(map_data.data[x] == 0){

            }else if(map_data.data[x] > 200){
                map_data.data[x] = 255;
                map_data.data[x+1] = 255;
                map_data.data[x+2] = 255;
            }else if(map_data.data[x] == 38){

            }else{
                map_data.data[x] = 38;
                map_data.data[x+1] = 38;
                map_data.data[x+2] = 38;
            }
        }



        print("start set minimap");
        var grid_width =3;
        for(var x=0; x<image_width; x=x+grid_width){
            for(var y=0; y<image_height-1; y=y+grid_width){
                var ave_grid = 0;
                var isoutline = false;
                for(var xx=0; xx<grid_width; xx++){
                    for(var yy=0; yy<grid_width; yy++){
                        if(map_data.data[((y+yy)*image_width+x+xx)*4] == 0){
                            // black(맵의 바깥영역)이 하나라도 있으면 맵의 외각이라고 판단.
                            isoutline = true;
                        }
                        ave_grid += map_data.data[((y+yy)*image_width+x+xx)*4];
                    }
                }
                ave_grid = ave_grid/(grid_width*grid_width);
                if(ave_grid >150){
                    supervisor.setGrid(x/grid_width,y/grid_width,"wall");
                }else if(ave_grid < 100 && !isoutline){//> 10 && !isoutline){
                    supervisor.setGrid(x/grid_width,y/grid_width,"floor");
                }else if(isoutline || ave_grid < 5){//else{
                    supervisor.setGrid(x/grid_width,y/grid_width,"nothing");
                }else{// if(ave_grid > 40 && !isoutline){
                    supervisor.setGrid(x/grid_width,y/grid_width,"unknown");
                }
            }
        }
        for(x=0; x<image_width; x=x+grid_width){
            for(y=0; y<image_height-1; y=y+grid_width){
                isoutline = false;
//                print(x/grid_width,y/grid_width,supervisor.getGrid(x/grid_width,y/grid_width));
                if(supervisor.getGrid(x/grid_width,y/grid_width) == "outline_wall"){
                    ctx.fillStyle = "yellow";
                    ctx.strokeStyle = "yellow";
                    ctx.beginPath();
                    ctx.rect(x,y,grid_width,grid_width);
                    ctx.fill();
                    ctx.stroke();
                }else if(supervisor.getGrid(x/grid_width,y/grid_width) == "wall"){
                    ctx.fillStyle = "yellow";
                    ctx.strokeStyle = "yellow";
                    ctx.beginPath();
                    ctx.rect(x,y,grid_width,grid_width);
                    ctx.fill();
                    ctx.stroke();
                }else if(supervisor.getGrid(x/grid_width,y/grid_width) == "floor"){
                    ctx.fillStyle = "blue";
                    ctx.strokeStyle = "blue";
                    ctx.beginPath();
                    ctx.rect(x,y,grid_width,grid_width);
                    ctx.fill();
                    ctx.stroke();
                }else if(supervisor.getGrid(x/grid_width,y/grid_width) == "unknown"){
//                    ctx.fillStyle = "yellow";
//                    ctx.strokeStyle = "yellow";
//                    ctx.beginPath();
//                    ctx.rect(x,y,grid_width,grid_width);
//                    ctx.fill();
//                    ctx.stroke();
                }else{

                }



//                if(supervisor.getFloor(x/grid_width,y/grid_width)){
//                    ctx.fillStyle = "cyan";
//                    ctx.strokeStyle = "cyan";
//                    ctx.beginPath();
//                    ctx.rect(x,y,grid_width,grid_width);
//                    ctx.fill();
//                    ctx.stroke();
//                }
            }
        }
    }

    Component.onCompleted: {
        print("map downloading..");
        origin_x = supervisor.getOrigin()[0];
        origin_y = supervisor.getOrigin()[1];
        grid_size = supervisor.getGridWidth();
        canvas_mini.requestPaint();
        canvas_map.requestPaint();
    }
    Rectangle{
        id: rect_mini
        width: 600
        height: 600
        clip: true
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right;

        border.width: 3
        border.color:"black"
        color: "black"
        Canvas{
            id: canvas_mini
            x: - origin_x + rect_mini.width/2;
            y: - origin_y + rect_mini.height/2;
            width: image_width
            height: image_height
            antialiasing: true
            onPaint:{
//                set_minimap();
//                var ctx = getContext("2d");
//                ctx.clearRect(0,0,canvas_map.width,canvas_map.height);
//                ctx.drawImage(map_image, 0,0,image_width,image_height);
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
                if(canvas_mini.x  > canvas_mini.width*(canvas_mini.scale - 1)/2){
                    canvas_mini.x = canvas_mini.width*(canvas_mini.scale - 1)/2
                }else if(canvas_mini.x < -(canvas_mini.width*(canvas_mini.scale - 1)/2 + canvas_mini.width - rect_mini.width)){
                    canvas_mini.x = -(canvas_mini.width*(canvas_mini.scale - 1)/2 + canvas_mini.width - rect_mini.width)
                }
            }
            onYChanged: {
                if(canvas_mini.y  > canvas_mini.height*(canvas_mini.scale - 1)/2){
                    canvas_mini.y = canvas_mini.height*(canvas_mini.scale - 1)/2
                }else if(canvas_mini.y < -(canvas_mini.height*(canvas_mini.scale - 1)/2 + canvas_mini.height - rect_mini.height)){
                    canvas_mini.y = -(canvas_mini.height*(canvas_mini.scale - 1)/2 + canvas_mini.height - rect_mini.height)
                }
            }
            onScaleChanged: {
                if(canvas_mini.x  > canvas_mini.width*(canvas_mini.scale - 1)/2){
                    canvas_mini.x = canvas_mini.width*(canvas_mini.scale - 1)/2
                }else if(canvas_mini.x < -(canvas_mini.width*(canvas_mini.scale - 1)/2 + canvas_mini.width - rect_mini.width)){
                    canvas_mini.x = -(canvas_mini.width*(canvas_mini.scale - 1)/2 + canvas_mini.width - rect_mini.width)
                }

                if(canvas_mini.y  > canvas_mini.height*(canvas_mini.scale - 1)/2){
                    canvas_mini.y = canvas_mini.height*(canvas_mini.scale - 1)/2
                }else if(canvas_mini.y < -(canvas_mini.height*(canvas_mini.scale - 1)/2 + canvas_mini.height - rect_mini.height)){
                    canvas_mini.y = -(canvas_mini.height*(canvas_mini.scale - 1)/2 + canvas_mini.height - rect_mini.height)
                }
            }


            MultiPointTouchArea{
                id: area_map_touch
                anchors.fill: parent
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
                    var ctx = canvas_mini.getContext('2d');
                    var dx = Math.abs(point1.x-point2.x);
                    var dy = Math.abs(point1.y-point2.y);
                    var mx = (point1.x+point2.x)/2;
                    var my = (point1.y+point2.y)/2;
                    var dist = Math.sqrt(dx*dx + dy*dy);
                    var dscale = (dist)/startDist;
                    var new_scale = canvas_mini.scale*dscale;
                    if(point1.pressed&&point2.pressed){

                        if(new_scale > 5)   new_scale = 5;

                        if(canvas_mini.width*new_scale < rect_mini.width){
                            new_scale = rect_mini.width/canvas_mini.width;
                        }
                        canvas_mini.scale = new_scale;

                        dmoveX = (mx - startX);
                        dmoveY = (my - startY);
                        canvas_mini.x += dmoveX;
                        canvas_mini.y += dmoveY;

//                        canvas_mini.requestPaint()
                    }else{
                        dmoveX = (point1.x - startX);
                        dmoveY = (point1.y - startY);
                        canvas_mini.x += dmoveX;
                        canvas_mini.y += dmoveY;

//                        canvas_mini.requestPaint()
                    }
                }
            }
        }
    }
    Rectangle{
        id: rect_origin
        width: 600
        height: 600
        clip: true
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left;

        border.width: 3
        border.color:"black"
        color: "black"
        Canvas{
            id: canvas_map
            x: canvas_mini.x
            y: canvas_mini.y
            scale: canvas_mini.scale
            width: image_width
            height: image_height
            antialiasing: true
            onPaint:{
                var ctx = getContext("2d");
                ctx.clearRect(0,0,canvas_map.width,canvas_map.height);
                ctx.drawImage(map_image, 0,0,image_width,image_height);
            }
        }
    }
}
