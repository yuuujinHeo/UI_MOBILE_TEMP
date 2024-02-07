import QtQuick 2.12
import QtQuick.Controls 2.12
import "."
import io.qt.Supervisor 1.0
import QtMultimedia 5.12

Item {
    id: page_moving_custom
    objectName: "page_moving_custom"
    width: 1280
    height: 800

    property string background_mode: "none"
    property string background_source: ""
    property real volume: 1
    onVolumeChanged:{
        print("move page volume : ", volume)
    }

    function setVolume(vol){
        loader_background.item.setVol(vol);
    }

    property int select_obj: -1
    onSelect_objChanged: {
        if(select_obj > -1){
            rect_left_top.x = model_obj.get(select_obj).ob_x - 10
            rect_left_top.y = model_obj.get(select_obj).ob_y - 10
            rect_right_bottom.x = model_obj.get(select_obj).ob_x  + model_obj.get(select_obj).ob_width - 10
            rect_right_bottom.y = model_obj.get(select_obj).ob_y  + model_obj.get(select_obj).ob_height - 10

        }
    }
    function close(){
        loader_background.sourceComponent = compo_color;
    }

    signal doubleclicked
    Component.onCompleted: {
        init();
    }
    Component.onDestruction:  {
        supervisor.stopBGM();
    }
    function init(){
        supervisor.writelog("[QML] MOVING CUSTOM PAGE init")

        model_obj.clear();
        page_moving_custom.select_obj = -1;
        for(var i=0; i<supervisor.getPatrolObjectSize(); i++){
            model_obj.append({"type":supervisor.getPageObjectType(i),
                             "ob_source":supervisor.getPageObjectSource(i),
                             "ob_color":supervisor.getPageObjectColor(i),
                             "ob_x":supervisor.getPageObjectX(i),
                             "ob_y":supervisor.getPageObjectY(i),
                             "ob_width":supervisor.getPageObjectWidth(i),
                             "ob_height":supervisor.getPageObjectHeight(i),
                             "fontsize":supervisor.getPageObjectFontsize(i)});
            print("object append : ",supervisor.getPageObjectType(i),supervisor.getPageObjectSource(i),supervisor.getPageObjectX(i),supervisor.getPageObjectY(i),supervisor.getPageObjectWidth(i),supervisor.getPageObjectHeight(i));
        }

        if(background_mode === "none" || background_mode === "color"){
            loader_background.sourceComponent = compo_color;
        }else if(background_mode === "image"){
            loader_background.sourceComponent = compo_gif;
        }else if(background_mode === "video"){
            loader_background.sourceComponent = compo_video;
        }

    }

    function update(){
        for(var i=0; i<model_obj.count; i++){
            model_obj.set(i,{"type":supervisor.getPageObjectType(i),
                             "ob_source":supervisor.getPageObjectSource(i),
                             "ob_color":supervisor.getPageObjectColor(i),
                             "ob_x":supervisor.getPageObjectX(i),
                             "ob_y":supervisor.getPageObjectY(i),
                             "ob_width":supervisor.getPageObjectWidth(i),
                             "ob_height":supervisor.getPageObjectHeight(i),
                             "fontsize":supervisor.getPageObjectFontsize(i)});
//            print("object set : ",supervisor.getPageObjectType(i),supervisor.getPageObjectSource(i))
        }
    }

    onBackground_modeChanged: {
        if(background_mode === "none" || background_mode === "color"){
            background_source = supervisor.getMovingPageColor()
            loader_background.sourceComponent = compo_color;
        }else if(background_mode === "image"){
            background_source = supervisor.getMovingPageImage()
            loader_background.sourceComponent = compo_gif;
        }else if(background_mode === "video"){
            background_source = supervisor.getMovingPageVideo()
            loader_background.sourceComponent = compo_video;
        }
    }

    Loader{
        id: loader_background
        anchors.fill: parent
        sourceComponent: compo_color
    }

    Component{
        id: compo_color
        Rectangle{
            anchors.fill: parent
            color: background_source
        }
    }

    Component{
        id: compo_image
        Image{
            id: image
            anchors.fill: parent
            source: background_source
            fillMode: Image.Stretch
            Text{
                anchors.centerIn: parent
                text:qsTr("이미지를 불러올 수 없습니다")
                color: color_red
                visible: image.status !== Image.Ready
            }
        }
    }
    Component{
        id: compo_gif
        AnimatedImage{
            id: gif
            cache: false
            anchors.fill: parent
            onStatusChanged:{
                print("status: ",status, playing)
                if(status == AnimatedImage.Ready){
                    playing = true;
                }
            }
            source: background_source
            fillMode: AnimatedImage.Stretch
            Text{
                anchors.centerIn: parent
                text:qsTr("이미지를 불러올 수 없습니다")
                color: color_red
                visible: gif.status !== AnimatedImage.Ready
            }
        }
    }

    Component{
        id: compo_video
        Item{
            anchors.fill: parent
            function setVol(vol){
                video.volume = vol;
                print("setVol ",vol);
            }

            Video{
                id: video
                anchors.fill: parent
                fillMode: VideoOutput.Stretch
                source: background_source
                volume: volume
                onVolumeChanged:{
                    print("volume : " , volume)
                }

                autoPlay: true
                loops:MediaPlayer.Infinite
                Text{
                    anchors.centerIn: parent
                    text:qsTr("영상을 불러올 수 없습니다")
                    color: color_red
                    visible: video.status === MediaPlayer.NoMedia || video.status === MediaPlayer.InvalidMedia || video.status === MediaPlayer.UnknownStatus
                }
            }
        }
    }



    Rectangle{
        id: rect_frame
        width: parent.width
        height: parent.height
        color: "transparent"
        Repeater{
            model: ListModel{id: model_obj}
            Rectangle{
                x: ob_x
                y: ob_y
                width: ob_width
                color: "transparent"
                height: ob_height
                border.width: page_moving_custom.select_obj===index?3:0
                border.color: color_red
                AnimatedImage{
                    id: image
                    visible: type === "image"
                    source: ob_source
                    anchors.fill: parent
                    cache: false
                    onStatusChanged:{
                        if(status == AnimatedImage.Ready){
                            playing = true;
                        }
                    }
                    Text{
                        anchors.centerIn: parent
                        text:qsTr("이미지를 불러올 수 없습니다")
                        color: color_red
                        visible: image.status !== AnimatedImage.Ready
                    }
                }
                Text{
                    visible: type === "text"
                    x: ob_x
                    y: ob_y
                    color: ob_color
                    anchors.centerIn: parent
                    text: ob_source
                    font.pixelSize: ob_height/2
                    font.family: font_noto_r.name
                }
            }
        }
        MouseArea{
            anchors.fill: parent
            property int posx: -1
            property int posy: -1
            property int firstx: -1
            property int firsty: -1
            property int firstwidth: -1
            property int firstheight: -1
            property int point: -1
            onPressed:{
                page_moving_custom.select_obj = supervisor.getPageObjectNum(mouseX,mouseY);
                if(page_moving_custom.select_obj > -1){
                    posx = mouseX - model_obj.get(page_moving_custom.select_obj).ob_x;
                    posy = mouseY - model_obj.get(page_moving_custom.select_obj).ob_y;
                    point = -1;

                    if(mouseX > model_obj.get(page_moving_custom.select_obj).ob_x - 10 && mouseX < model_obj.get(page_moving_custom.select_obj).ob_x + 10){
                        if(mouseY > model_obj.get(page_moving_custom.select_obj).ob_y - 10 && mouseY < model_obj.get(page_moving_custom.select_obj).ob_y + 10){
                            point = 0;
                            firstx = model_obj.get(page_moving_custom.select_obj).ob_x
                            firsty = model_obj.get(page_moving_custom.select_obj).ob_y
                            firstwidth = model_obj.get(page_moving_custom.select_obj).ob_width
                            firstheight = model_obj.get(page_moving_custom.select_obj).ob_height
                        }
                    }
                    if(mouseX > model_obj.get(page_moving_custom.select_obj).ob_x + model_obj.get(page_moving_custom.select_obj).ob_width - 10 && mouseX < model_obj.get(page_moving_custom.select_obj).ob_x + model_obj.get(page_moving_custom.select_obj).ob_width+ 10){
                        if(mouseY > model_obj.get(page_moving_custom.select_obj).ob_y+ model_obj.get(page_moving_custom.select_obj).ob_height - 10 && mouseY < model_obj.get(page_moving_custom.select_obj).ob_y+ model_obj.get(page_moving_custom.select_obj).ob_height + 10){
                            point = 1;
                            firstx = model_obj.get(page_moving_custom.select_obj).ob_x + model_obj.get(page_moving_custom.select_obj).ob_width
                            firsty = model_obj.get(page_moving_custom.select_obj).ob_y + model_obj.get(page_moving_custom.select_obj).ob_height
                            firstwidth = model_obj.get(page_moving_custom.select_obj).ob_width
                            firstheight = model_obj.get(page_moving_custom.select_obj).ob_height
                        }
                    }
                }else{
                    posx = -1;
                    posy = -1;
                    point = -1;
                }
            }
            onReleased:{
                if(page_moving_custom.select_obj > -1){
                    supervisor.setPatrolObjectSize(page_moving_custom.select_obj,
                                                   model_obj.get(page_moving_custom.select_obj).ob_x,model_obj.get(page_moving_custom.select_obj).ob_y,
                                                   model_obj.get(page_moving_custom.select_obj).ob_width,model_obj.get(page_moving_custom.select_obj).ob_height);
                }
                posx = -1;
                posy = -1;
                point = -1;
            }
            onPositionChanged: {
                if(page_moving_custom.select_obj > -1){
                    if(point === 0){
                        model_obj.get(page_moving_custom.select_obj).ob_x = mouseX - posx
                        model_obj.get(page_moving_custom.select_obj).ob_y = mouseY - posy
                        model_obj.get(page_moving_custom.select_obj).ob_width = firstwidth - mouseX + firstx
                        model_obj.get(page_moving_custom.select_obj).ob_height = firstheight - mouseY + firsty
                    }else if(point === 1){
                        model_obj.get(page_moving_custom.select_obj).ob_width = firstwidth + mouseX - firstx
                        model_obj.get(page_moving_custom.select_obj).ob_height = firstheight + mouseY - firsty
                    }else{
                        supervisor.movePatrolObject(page_moving_custom.select_obj, mouseX-posx, mouseY-posy);
                        page_moving_custom.update();
                    }
                    rect_left_top.x = model_obj.get(page_moving_custom.select_obj).ob_x - 10
                    rect_left_top.y = model_obj.get(page_moving_custom.select_obj).ob_y - 10
                    rect_right_bottom.x = model_obj.get(page_moving_custom.select_obj).ob_x  + model_obj.get(page_moving_custom.select_obj).ob_width - 10
                    rect_right_bottom.y = model_obj.get(page_moving_custom.select_obj).ob_y  + model_obj.get(page_moving_custom.select_obj).ob_height - 10
                }
            }
            onDoubleClicked: {
                if(page_moving_custom.select_obj > -1){
                    page_moving_custom.doubleclicked();
                }
            }
        }
        Rectangle{
            id: rect_left_top
            visible: page_moving_custom.select_obj > -1
            enabled: visible
            x: typeof(model_obj.get(page_moving_custom.select_obj).ob_x)=="undefined"?0:model_obj.get(page_moving_custom.select_obj).ob_x - 10
            y: typeof(model_obj.get(page_moving_custom.select_obj).ob_y)=="undefined"?0:model_obj.get(page_moving_custom.select_obj).ob_y - 10
            width:  20
            height: 20
            color: color_red
        }
        Rectangle{
            id: rect_right_bottom
            visible: page_moving_custom.select_obj > -1
            x: typeof(model_obj.get(page_moving_custom.select_obj).ob_x)=="undefined"?0:model_obj.get(page_moving_custom.select_obj).ob_x + model_obj.get(page_moving_custom.select_obj).ob_width - 10
            y: typeof(model_obj.get(page_moving_custom.select_obj).ob_y)=="undefined"?0:model_obj.get(page_moving_custom.select_obj).ob_y + model_obj.get(page_moving_custom.select_obj).ob_height - 10
            width:  20
            height: 20
            color: color_red
        }
    }

}
