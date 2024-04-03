import QtQuick 2.12
import QtQuick.Controls 2.12
import "."
import io.qt.Supervisor 1.0
import QtMultimedia 5.12

Item {
    id: page_moving_custom
    objectName: "page_moving_custom"
    property bool edit_mode: false
    width: 1280
    height: 800

    property string page: "moving"
    property string background_mode: "none"
    property string background_source: ""
    property string video_audio: "video"
    property bool motor_lock: false
    property bool robot_paused: false
    property string pos_name: ""
    property int password: 0
    property real volume: 1
    onVolumeChanged:{
        print("move page volume : ", volume)
    }
    onVideo_audioChanged: {
        print("video audio changed : ",video_audio)
        loader_background.item.init();
    }

    function pauseGif(){
        if(background_mode === "image"){
            loader_background.item.pause();
        }
    }

    function resumeGif(){
        if(background_mode === "image")
            loader_background.item.resume();
    }

    function setPage(name){
        page = name;
        init();
    }

    function movedone(){
        loadPage(pkitchen);
    }

    function setVolume(vol){
        if(loader_background.item.objectName == "compo_video")
            loader_background.item.setVol(vol);
    }
    function close(){
        loader_background.sourceComponent = compo_black;
        supervisor.stopBGM();
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

    signal doubleclicked
    Component.onCompleted: {
        init();
    }

    Component.onDestruction:  {
        supervisor.stopBGM();
        popup_notice.close();
    }

    function saveMovingPage(){
        supervisor.setMovingPageBackground(background_mode);
        if(background_mode === "color"){
        }else if(background_mode === "image"){

        }else if(background_mode === "video"){
            supervisor.setMovingPageVideoAudio(video_audio);
//            supervisor.setMovingPageAudio(volume);
        }
    }

    function saveServingPage(){
        supervisor.setServingPageBackground(background_mode);
        if(background_mode === "color"){
        }else if(background_mode === "image"){

        }else if(background_mode === "video"){
            supervisor.setServingPageVideoAudio(video_audio);
            supervisor.setServingPageAudio(volume);
        }

    }

    function setEdit(tt){
        edit_mode = tt;
        init();
    }

    function init(){
        supervisor.writelog("[QML] MOVING CUSTOM PAGE init "+page+" : "+objectName+", "+edit_mode);

        supervisor.stopBGM();
        popup_pause.close();
        if(!edit_mode){
            statusbar.visible = false;
        }else{
            statusbar.visible = true;
        }

        model_obj.clear();
        if(page == "moving"){
            page_moving_custom.select_obj = -1;
            for(var i=0; i<supervisor.getPatrolObjectSize(); i++){
                if(supervisor.getPageObjectType(i)==="image"){
                    model_obj.append({"type":supervisor.getPageObjectType(i),
                                     "ob_source":supervisor.getPageObjectSource(i),
                                     "ob_text":"",
                                     "ob_color":supervisor.getPageObjectColor(i),
                                     "ob_x":supervisor.getPageObjectX(i)*width/1280,
                                     "ob_y":supervisor.getPageObjectY(i)*height/800,
                                     "ob_width":supervisor.getPageObjectWidth(i)*width/1280,
                                     "ob_height":supervisor.getPageObjectHeight(i)*height/800,
                                     "fontsize":supervisor.getPageObjectFontsize(i)});
                }else{
                    model_obj.append({"type":supervisor.getPageObjectType(i),
                                     "ob_source":"",
                                     "ob_text":supervisor.getPageObjectSource(i),
                                     "ob_color":supervisor.getPageObjectColor(i),
                                     "ob_x":supervisor.getPageObjectX(i)*width/1280,
                                     "ob_y":supervisor.getPageObjectY(i)*height/800,
                                     "ob_width":supervisor.getPageObjectWidth(i)*width/1280,
                                     "ob_height":supervisor.getPageObjectHeight(i)*height/800,
                                     "fontsize":supervisor.getPageObjectFontsize(i)});
                }
                print("object append : ",supervisor.getPageObjectType(i),supervisor.getPageObjectSource(i),supervisor.getPageObjectX(i),supervisor.getPageObjectY(i),supervisor.getPageObjectWidth(i),supervisor.getPageObjectHeight(i));
            }

            background_mode = supervisor.getMovingPageBackground();
            print("background mode = ",background_mode);
            if(background_mode === "none" || background_mode === "color"){
                background_source = supervisor.getMovingPageColor();
                loader_background.sourceComponent = compo_color;
            }else if(background_mode === "image"){
                background_source = supervisor.getMovingPageImage();
                loader_background.sourceComponent = compo_gif;
            }else if(background_mode === "video"){
                background_source = supervisor.getMovingPageVideo();
                loader_background.sourceComponent = compo_video;
                loader_background.item.init();
                loader_background.item.setVol(supervisor.getMovingPageAudio());
                video_audio = supervisor.getMovingPageVideoAudio();
                print("video_audio mode = ",video_audio);
            }
        }else if(page == "serving"){
            page_moving_custom.select_obj = -1;

            print(supervisor.getServingObjectSize())
            for(var i=0; i<supervisor.getServingObjectSize(); i++){
                if(supervisor.getServingObjectType(i)==="image"){
                    model_obj.append({"type":supervisor.getServingObjectType(i),
                                     "ob_source":supervisor.getServingObjectSource(i),
                                     "ob_text":"",
                                     "ob_color":supervisor.getServingObjectColor(i),
                                     "ob_x":supervisor.getServingObjectX(i)*width/1280,
                                     "ob_y":supervisor.getServingObjectY(i)*height/800,
                                     "ob_width":supervisor.getServingObjectWidth(i)*width/1280,
                                     "ob_height":supervisor.getServingObjectHeight(i)*height/800,
                                     "fontsize":supervisor.getServingObjectFontsize(i)});
                }else{
                    model_obj.append({"type":supervisor.getServingObjectType(i),
                                     "ob_source":"",
                                     "ob_text":supervisor.getServingObjectSource(i),
                                     "ob_color":supervisor.getServingObjectColor(i),
                                     "ob_x":supervisor.getServingObjectX(i)*width/1280,
                                     "ob_y":supervisor.getServingObjectY(i)*height/800,
                                     "ob_width":supervisor.getServingObjectWidth(i)*width/1280,
                                     "ob_height":supervisor.getServingObjectHeight(i)*height/800,
                                     "fontsize":supervisor.getServingObjectFontsize(i)});
                }
                print("object append : ",supervisor.getServingObjectType(i),supervisor.getServingObjectSource(i),supervisor.getServingObjectX(i),supervisor.getServingObjectY(i),supervisor.getServingObjectWidth(i),supervisor.getServingObjectHeight(i));
            }

            background_mode = supervisor.getServingPageBackground();
            print("background mode = ",background_mode);
            if(background_mode === "none" || background_mode === "color"){
                background_source = supervisor.getServingPageColor();
                loader_background.sourceComponent = compo_color;
            }else if(background_mode === "image"){
                background_source = supervisor.getServingPageImage();
                loader_background.sourceComponent = compo_gif;
            }else if(background_mode === "video"){
                background_source = supervisor.getServingPageVideo();
                loader_background.sourceComponent = compo_video;
                loader_background.item.init();
                loader_background.item.setVol(supervisor.getServingPageAudio());
                video_audio = supervisor.getServingPageVideoAudio();
                print("video_audio mode = ",video_audio);
            }
        }

        if(background_mode !== "video" && !edit_mode){
            supervisor.playBGM();
        }

    }

    function update(){
        if(page == "moving"){
            for(var i=0; i<model_obj.count; i++){
                if(supervisor.getPageObjectType(i)==="image"){
                    model_obj.set(i,{"type":supervisor.getPageObjectType(i),
                                     "ob_source":supervisor.getPageObjectSource(i),
                                     "ob_text":"",
                                     "ob_color":supervisor.getPageObjectColor(i),
                                     "ob_x":supervisor.getPageObjectX(i)*width/1280,
                                     "ob_y":supervisor.getPageObjectY(i)*height/800,
                                     "ob_width":supervisor.getPageObjectWidth(i)*width/1280,
                                     "ob_height":supervisor.getPageObjectHeight(i)*height/800,
                                     "fontsize":supervisor.getPageObjectFontsize(i)});
                }else{
                    model_obj.set(i,{"type":supervisor.getPageObjectType(i),
                                     "ob_source":"",
                                     "ob_text":supervisor.getPageObjectSource(i),
                                     "ob_color":supervisor.getPageObjectColor(i),
                                     "ob_x":supervisor.getPageObjectX(i)*width/1280,
                                     "ob_y":supervisor.getPageObjectY(i)*height/800,
                                     "ob_width":supervisor.getPageObjectWidth(i)*width/1280,
                                     "ob_height":supervisor.getPageObjectHeight(i)*height/800,
                                     "fontsize":supervisor.getPageObjectFontsize(i)});
                }
    //            print("object set : ",supervisor.getPageObjectType(i),supervisor.getPageObjectSource(i))
            }
        }else if(page == "serving"){
            for(var i=0; i<model_obj.count; i++){
                if(supervisor.getServingObjectType(i)==="image"){
                    model_obj.set(i,{"type":supervisor.getServingObjectType(i),
                                     "ob_source":supervisor.getServingObjectSource(i),
                                     "ob_text":"",
                                     "ob_color":supervisor.getServingObjectColor(i),
                                     "ob_x":supervisor.getServingObjectX(i)*width/1280,
                                     "ob_y":supervisor.getServingObjectY(i)*height/800,
                                     "ob_width":supervisor.getServingObjectWidth(i)*width/1280,
                                     "ob_height":supervisor.getServingObjectHeight(i)*height/800,
                                     "fontsize":supervisor.getServingObjectFontsize(i)});
                }else{
                    model_obj.set(i,{"type":supervisor.getServingObjectType(i),
                                     "ob_source":"",
                                     "ob_text":supervisor.getServingObjectSource(i),
                                     "ob_color":supervisor.getServingObjectColor(i),
                                     "ob_x":supervisor.getServingObjectX(i)*width/1280,
                                     "ob_y":supervisor.getServingObjectY(i)*height/800,
                                     "ob_width":supervisor.getServingObjectWidth(i)*width/1280,
                                     "ob_height":supervisor.getServingObjectHeight(i)*height/800,
                                     "fontsize":supervisor.getServingObjectFontsize(i)});
                }
    //            print("object set : ",supervisor.getPageObjectType(i),supervisor.getPageObjectSource(i))
            }
        }

    }

    onBackground_modeChanged: {
        supervisor.stopBGM();
        if(page == "moving"){
            if(background_mode === "none" || background_mode === "color"){
                background_source = supervisor.getMovingPageColor()
                loader_background.sourceComponent = compo_color;
            }else if(background_mode === "image"){
                background_source = supervisor.getMovingPageImage()
                loader_background.sourceComponent = compo_gif;
            }else if(background_mode === "video"){
                background_source = supervisor.getMovingPageVideo()
                loader_background.sourceComponent = compo_video;
                loader_background.item.init();
                video_audio = supervisor.getMovingPageVideoAudio();
                print("background change , ",video_audio);
            }
        }else if(page == "serving"){
            if(background_mode === "none" || background_mode === "color"){
                background_source = supervisor.getServingPageColor()
                loader_background.sourceComponent = compo_color;
            }else if(background_mode === "image"){
                background_source = supervisor.getServingPageImage()
                loader_background.sourceComponent = compo_gif;
            }else if(background_mode === "video"){
                background_source = supervisor.getServingPageVideo()
                loader_background.sourceComponent = compo_video;
                loader_background.item.init();
                video_audio = supervisor.getServingPageVideoAudio();
                print("background changes , ",video_audio);
            }
        }

    }

    Loader{
        id: loader_background
        anchors.fill: parent
        sourceComponent: compo_black
    }

    Component{
        id: compo_black
        Item{
            anchors.fill: parent
            Rectangle{
                anchors.fill: parent
                color: "black"
            }
        }
    }

    Component{
        id: compo_color
        Item{
            Rectangle{
                anchors.fill: parent
                color: background_source
            }
        }
    }
    Component{
        id: compo_image
        Item{
            Image{
                id: image
                anchors.fill: parent
                sourceSize.width: width
                sourceSize.height: height
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

    }
    Component{
        id: compo_gif
        Item{
            anchors.fill: parent
            function pause(){
                gif.paused = true;
            }
            function resume(){
                print("gif resume")
                gif.paused = false;
            }
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
    }
    Component{
        id: compo_video
        Item{
            objectName: "compo_video"
            anchors.fill: parent
            Component.onCompleted: {
                init();
            }
            Component.onDestruction: {
                supervisor.stopBGM();
            }
            function init(){
                print("video init ",video_audio);
                if(video_audio == "music1"){
                    video.volume = 0;
                    if(page == "moving"){
                        supervisor.playBGM(supervisor.getMovingPageAudio()*100);
                    }else if(page == "serving"){
                        supervisor.playBGM(supervisor.getServingPageAudio()*100);
                    }
                }else{
                    supervisor.stopBGM();
                    if(page == "moving"){
                        video.volume = supervisor.getVolume(supervisor.getMovingPageAudio());
                    }else if(page == "serving"){
                        video.volume = supervisor.getVolume(supervisor.getServingPageAudio());
                    }
                }
            }

            function setVol(vol){
                print("video set vol ",vol,video_audio)
                if(video_audio == "video"){
                    video.volume = supervisor.getVolume(vol);
                }else if(video_audio == "music1"){
                    supervisor.setvolumeBGM(vol*100);
                }
            }
            function pause(){
                video.pause();
            }
            function resume(){
                print("video resume")
                video.play();
            }

            Video{
                id: video
                anchors.fill: parent
                fillMode: VideoOutput.Stretch
                source: background_source
                volume: supervisor.getVolume(0.5)
                flushMode: VideoOutput.FirstFrame
                autoPlay: true
                loops:MediaPlayer.Infinite
                property var lastPos
                property int zero_count: 0
                onStatusChanged: {
                    print("status : ",status)
                    if(status === MediaPlayer.Loaded){
                        video.play();
                    }
                }
                function reset(){
                    source = "";
                    source = background_source;
                }

                onPlaybackStateChanged: {
                    print("playback state : ",playbackState)
                }
                onPlaybackRateChanged: {
                    print("playback rate : ",playbackRate);
                }

                onPositionChanged:{
                    if(duration > 0){
//                        print("position changed ",position,duration)
                        if(position != 0){
                            lastPos = position;
                            zero_count = 0;
                        }else{
                            if(zero_count++>3){
                                zero_count = 0;
//                                print("need source reset");
                                reset();
                            }
                        }
                        if(position>duration-500){
//                            print("source reset")
                            reset();
                        }
                    }
                }

                Text{
                    anchors.centerIn: parent
                    text:qsTr("영상을 불러올 수 없습니다")
                    color: color_red
                    visible: video.status === MediaPlayer.NoMedia || video.status === MediaPlayer.InvalidMedia || video.status === MediaPlayer.UnknownStatus
                }
            }
        }
    }

//    Timer{
//        id: test_timer
//        interval: 1000
//        running: true
//        repeat: true
//        property int nn: 0
//        onTriggered:{
//            if(loader_background.item.objectName == "compo_video"){
//                if(nn === 0){
//                    loader_background.item.pause();
//                    nn++;
//                }else{
//                    loader_background.item.resume();
//                    nn = 0;
//                }
//            }
//        }
//    }

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
                    text: ob_text
                    font.pixelSize: ob_height/2
                    font.family: font_noto_r.name
                }
            }
        }
        MouseArea{
            anchors.fill: parent
            visible: edit_mode
            property int posx: -1
            property int posy: -1
            property int firstx: -1
            property int firsty: -1
            property int firstwidth: -1
            property int firstheight: -1
            property int point: -1
            property real res: 1280/width
            onPressed:{
                if(page == "moving"){
                    page_moving_custom.select_obj = supervisor.getPageObjectNum(mouseX*res,mouseY*res);
                }else if(page == "serving"){
                    page_moving_custom.select_obj = supervisor.getServingObjectNum(mouseX*res,mouseY*res);
                }

                if(page_moving_custom.select_obj > -1){
                    posx = mouseX - model_obj.get(page_moving_custom.select_obj).ob_x;
                    posy = mouseY - model_obj.get(page_moving_custom.select_obj).ob_y;
                    point = -1;

                    print(mouseX, mouseY, res, model_obj.get(page_moving_custom.select_obj).ob_x ,model_obj.get(page_moving_custom.select_obj).ob_width, model_obj.get(page_moving_custom.select_obj).ob_y, model_obj.get(page_moving_custom.select_obj).ob_height)
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
                    if(page == "moving"){
                        supervisor.setPatrolObjectSize(page_moving_custom.select_obj,
                                                       model_obj.get(page_moving_custom.select_obj).ob_x*res,model_obj.get(page_moving_custom.select_obj).ob_y*res,
                                                       model_obj.get(page_moving_custom.select_obj).ob_width*res,model_obj.get(page_moving_custom.select_obj).ob_height*res);

                    }else if(page == "serving"){
                        supervisor.setServingObjectSize(page_moving_custom.select_obj,
                                                       model_obj.get(page_moving_custom.select_obj).ob_x*res,model_obj.get(page_moving_custom.select_obj).ob_y*res,
                                                       model_obj.get(page_moving_custom.select_obj).ob_width*res,model_obj.get(page_moving_custom.select_obj).ob_height*res);

                    }
                }
                posx = -1;
                posy = -1;
                point = -1;
            }
            onPositionChanged: {
                if(page_moving_custom.select_obj > -1){
                    if(point === 0){
                        if(firstwidth - mouseX + firstx > 0){
                            model_obj.get(page_moving_custom.select_obj).ob_x = mouseX - posx
                            model_obj.get(page_moving_custom.select_obj).ob_width = firstwidth - mouseX + firstx
                        }
                        if(firstheight - mouseY + firsty > 0){
                            model_obj.get(page_moving_custom.select_obj).ob_y = mouseY - posy
                            model_obj.get(page_moving_custom.select_obj).ob_height = firstheight - mouseY + firsty
                        }
                    }else if(point === 1){
                        if(firstwidth + mouseX - firstx > 0){
                            model_obj.get(page_moving_custom.select_obj).ob_width = firstwidth + mouseX - firstx
                        }
                        if(firstheight + mouseY - firsty > 0){
                            model_obj.get(page_moving_custom.select_obj).ob_height = firstheight + mouseY - firsty
                        }
                    }else{
                        if(page == "moving"){
                            supervisor.movePatrolObject(page_moving_custom.select_obj, mouseX*res-posx*res, mouseY*res-posy*res);
                        }else if(page == "serving"){
                            supervisor.moveServingObject(page_moving_custom.select_obj, mouseX*res-posx*res, mouseY*res-posy*res);
                        }
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
            visible: edit_mode && page_moving_custom.select_obj > -1
            enabled: visible
            x: !visible?0:model_obj.get(page_moving_custom.select_obj).ob_x - 10
            y: !visible?0:model_obj.get(page_moving_custom.select_obj).ob_y - 10
            width:  20
            height: 20
            color: color_red
        }
        Rectangle{
            id: rect_right_bottom
            visible: edit_mode && page_moving_custom.select_obj > -1
            x: !visible?0:model_obj.get(page_moving_custom.select_obj).ob_x + model_obj.get(page_moving_custom.select_obj).ob_width - 10
            y: !visible?0:model_obj.get(page_moving_custom.select_obj).ob_y + model_obj.get(page_moving_custom.select_obj).ob_height - 10
            width:  20
            height: 20
            color: color_red
        }
    }


    Popup{
        id: popup_pause
        width: parent.width
        height: parent.height
        closePolicy: Popup.NoAutoClose
        onOpened:{
            statusbar.visible = true;
            loader_background.item.pause();
            if(popup_notice.opened){
                print("재오픈")
//                popup_notice.close();
//                popup_notice.open();
            }
        }
        onClosed:{
            if(!edit_mode){
                statusbar.visible = false;
            }
            loader_background.item.resume();
        }
        background:Rectangle{
            anchors.fill: parent
            color: color_dark_black
            opacity: 0.9
        }
        Column{
            anchors.centerIn: parent
            spacing: 50
            Image{
                id: image_warning
                source: "icon/icon_warning.png"
                width: 160
                height: 160
                anchors.horizontalCenter: parent.horizontalCenter
                sourceSize.width: width
                sourceSize.height: height
            }
            Column{
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: 10
                Text{
                    id: teee
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.family: font_noto_b.name
                    font.pixelSize: 50
                    color: "#e2574c"
                    text: qsTr("일시정지 됨")
                }
                Text{
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.family: font_noto_b.name
                    font.pixelSize: 40
                    color: "#e2574c"
                    text: qsTr("( 목적지 : ")+pos_name+" )"
                }
            }
            Row{
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: 80
                Rectangle{
                    width: 180
                    height: 120
                    radius: 20
                    color: "transparent"
                    border.color: color_red
                    border.width: 6
                    Text{
                        anchors.centerIn: parent
                        color: color_red
                        font.family: font_noto_r.name
                        font.pixelSize: 30
                        text: qsTr("수동 이동")
                    }
                    MouseArea{
                        anchors.fill: parent
                        z: 99
                        onClicked:{
                            click_sound.play();
                            popup_notice.init();
                            popup_notice.closemode = false;
                            popup_notice.style = "warning";
                            popup_notice.main_str = qsTr("로봇을 수동으로 이동하시겠습니까?")
                            popup_notice.sub_str = qsTr("기존의 경로는 취소되며 대기화면으로 넘어갑니다")
                            popup_notice.addButton(qsTr("수동이동"));
                            popup_notice.open();
                        }
                    }
                }
                Rectangle{
                    width: 180
                    height: 120
                    radius: 20
                    color: "transparent"
                    enabled: motor_lock
                    border.color: motor_lock?color_red:color_gray
                    border.width: 6
                    Text{
                        anchors.centerIn: parent
                        color: color_red
                        font.family: font_noto_r.name
                        font.pixelSize: 30
                        text: qsTr("경로 취소")
                    }
                    MouseArea{
                        anchors.fill: parent
                        z: 99
                        propagateComposedEvents: true
                        onPressed:{
                            click_sound.play();;
                            parent.color = color_dark_navy
                        }
                        onReleased:{
                            parent.color = "transparent"
                        }
                        onClicked:{
                            supervisor.writelog("[UI] PageMovingCustom : Path Cancle");
                            supervisor.moveStop();
                        }
                    }
                }
                Rectangle{
                    width: 180
                    height: 120
                    radius: 20
                    color: "transparent"
                    enabled: motor_lock
                    border.color: motor_lock?color_red:color_gray
                    border.width: 6
                    Text{
                        anchors.centerIn: parent
                        color: color_red
                        font.family: font_noto_r.name
                        font.pixelSize: 30
                        text: qsTr("경로 재개")
                    }
                    MouseArea{
                        anchors.fill: parent
                        z: 99
                        onClicked:{
                            click_sound.play();;
                            supervisor.writelog("[UI] PageMovingCustom : Path Resume");
                            supervisor.moveResume();
                        }
                    }
                }
            }
        }
    }

    Timer{
        id: update_timer
        interval: 500
        running: !edit_mode
        property int prev_state: 0
        property bool lock_notice: false
        repeat: true
        onTriggered: {
            if(supervisor.getLockStatus()===0){
                if(motor_lock)
                    supervisor.writelog("[UI] PageMovingCustom : Motor Lock false");

                motor_lock = false;

                if(!lock_notice){
                    popup_notice.init();
                    popup_notice.closemode = false;
                    popup_notice.style = "warning";
                    popup_notice.main_str = qsTr("로봇이 수동이동 중입니다")
                    popup_notice.sub_str = ""
                    popup_notice.addButton(qsTr("원래대로"));
                    popup_notice.open();
                    lock_notice = true;
                }

            }else{
                if(!motor_lock){
                    supervisor.writelog("[UI] PageMovingCustom : Motor Lock true");
                }
                motor_lock = true;

                if(lock_notice){
                    lock_notice = false;
                    popup_notice.close();
                }

                if(prev_state !== supervisor.getStateMoving()){
                    if(supervisor.getStateMoving() === 4){
                        robot_paused = true;
                        popup_pause.open();
                        supervisor.writelog("[UI] PageMovingCustom : Check State -> Robot Paused");
                    }else if(supervisor.getStateMoving() === 0){
                        robot_paused = true;
                        popup_pause.open();
                        supervisor.writelog("[UI] PageMovingCustom : Check State -> Robot Not Moving");
                    }else if(supervisor.getStateMoving() === 2){
                        popup_pause.close();
                        robot_paused = false;
                        supervisor.writelog("[UI] PageMovingCustom : Check State -> Robot Moving");
                    }else{
                        popup_pause.close();
                        robot_paused = false;
                        supervisor.writelog("[UI] PageMovingCustom : Check State -> "+Number(supervisor.getStateMoving()));
                    }
                }
                prev_state = supervisor.getStateMoving();
            }
        }
    }
    MouseArea{
        id: btn_page
        anchors.fill: parent
        visible: !edit_mode && !robot_paused
        onClicked: {
            click_sound.play();
            if(!robot_paused){
                supervisor.writelog("[UI] PageMovingCustom : Move Pause")
                supervisor.movePause();
            }
        }
    }
    MouseArea{
        id: btn_password_1
        width: 100
        height: 100
        visible: !edit_mode
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        z: 99
        onClicked: {
            click_sound.play();
            password++;
            if(password > 4){
                password = 0;
                supervisor.moveStop();
                supervisor.writelog("[UI] PageMovingCustom : Debug Pass -> PageKitchen");
                loadPage(pkitchen);
            }
        }
        onPressAndHold: {
            password = 0;
            mainwindow.showMinimized();
        }
    }
}
