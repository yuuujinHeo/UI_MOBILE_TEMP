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

    property string background_mode: "none"
    property string background_source: ""
    property bool motor_lock: false
    property bool robot_paused: false
    property string pos_name: ""
    property int password: 0
    property real volume: 1
    onVolumeChanged:{
        print("move page volume : ", volume)
    }

    function movedone(){
        loadPage(pkitchen);
    }

    function setVolume(vol){
        if(loader_background != null){
            if(loader_background.item != null)
                loader_background.item.setVol(vol);
        }
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
        popup_notice.close();
    }
    function init(){
        supervisor.writelog("[QML] MOVING CUSTOM PAGE init")

        popup_pause.visible = false;
        if(!edit_mode){
            statusbar.visible = false;
        }

        model_obj.clear();
        page_moving_custom.select_obj = -1;
        for(var i=0; i<supervisor.getPatrolObjectSize(); i++){
            model_obj.append({"type":supervisor.getPageObjectType(i),
                             "ob_source":supervisor.getPageObjectSource(i),
                             "ob_color":supervisor.getPageObjectColor(i),
                             "ob_x":supervisor.getPageObjectX(i)*width/1280,
                             "ob_y":supervisor.getPageObjectY(i)*height/800,
                             "ob_width":supervisor.getPageObjectWidth(i)*width/1280,
                             "ob_height":supervisor.getPageObjectHeight(i)*height/800,
                             "fontsize":supervisor.getPageObjectFontsize(i)});
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
            loader_background.item.setVol(supervisor.getMovingPageAudio());
        }
    }

    function update(){
        for(var i=0; i<model_obj.count; i++){
            model_obj.set(i,{"type":supervisor.getPageObjectType(i),
                             "ob_source":supervisor.getPageObjectSource(i),
                             "ob_color":supervisor.getPageObjectColor(i),
                             "ob_x":supervisor.getPageObjectX(i)*width/1280,
                             "ob_y":supervisor.getPageObjectY(i)*height/800,
                             "ob_width":supervisor.getPageObjectWidth(i)*width/1280,
                             "ob_height":supervisor.getPageObjectHeight(i)*height/800,
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
            Component.onCompleted: {
                video.volume = supervisor.getMovingPageAudio();
                print("completed volume = ",video.volume)
            }

            function setVol(vol){
                video.volume = vol;
                print("VIDEO VOLUME = ",vol);
            }

            Video{
                id: video
                anchors.fill: parent
                fillMode: VideoOutput.Stretch
                source: background_source
                volume: 1
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
                page_moving_custom.select_obj = supervisor.getPageObjectNum(mouseX*res,mouseY*res);
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
                    supervisor.setPatrolObjectSize(page_moving_custom.select_obj,
                                                   model_obj.get(page_moving_custom.select_obj).ob_x*res,model_obj.get(page_moving_custom.select_obj).ob_y*res,
                                                   model_obj.get(page_moving_custom.select_obj).ob_width*res,model_obj.get(page_moving_custom.select_obj).ob_height*res);
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
                        supervisor.movePatrolObject(page_moving_custom.select_obj, mouseX*res-posx*res, mouseY*res-posy*res);
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


    Item{
        id: popup_pause
        width: parent.width
        height: parent.height
        anchors.centerIn: parent
        onVisibleChanged: {
            if(statusbar != null){
                if(visible){
                    statusbar.visible = true;
                }else{
                    statusbar.visible = false;
                }
            }
        }

        Rectangle{
            anchors.fill: parent
            visible: robot_paused
            color: "#282828"
            opacity: 0.8
        }
        Image{
            id: image_warning
            source: "icon/icon_warning.png"
            width: 160
            height: 160
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 200
            MouseArea{
                anchors.fill: parent
                z: 99
                onClicked:{
                    popup_pause.visible = false;
                }
            }
        }
        Text{
            id: teee
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top:image_warning.bottom
            anchors.topMargin: 30
            font.family: font_noto_b.name
            font.pixelSize: 50
            color: "#e2574c"
            text: qsTr("일시정지 됨")
        }
        Text{
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top:teee.bottom
            anchors.topMargin: 10
            font.family: font_noto_b.name
            font.pixelSize: 40
            color: "#e2574c"
            text: qsTr("( 목적지 : ")+pos_name+" )"
        }
        Row{
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 80
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 100
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
                        popup_notice.addButton(qsTr("취소"));
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
//                        timer_check_pause.start();
                    }
                }
            }
        }
    }
    Timer{
        id: timer_check_pause
        interval: 500
        running: true
        repeat: true
        property int prev_state: 0
        onTriggered: {
        }
    }
    Timer{
        id: update_timer
        interval: 500
        running: !edit_mode
        property int prev_state: 0
        repeat: true
        onTriggered: {
            if(supervisor.getLockStatus()===0){
                if(motor_lock)
                    supervisor.writelog("[UI] PageMovingCustom : Motor Lock false");

                motor_lock = false;

                popup_notice.init();
                popup_notice.closemode = false;
                popup_notice.style = "warning";
                popup_notice.main_str = qsTr("로봇이 수동이동 중입니다")
                popup_notice.sub_str = ""
                popup_notice.addButton(qsTr("원래대로"));
                popup_notice.open();
            }else{
                if(!motor_lock){
                    supervisor.writelog("[UI] PageMovingCustom : Motor Lock true");
                }
                motor_lock = true;

                if(prev_state !== supervisor.getStateMoving()){
                    if(supervisor.getStateMoving() === 4){
                        robot_paused = true;
                        popup_pause.visible = true;
                        supervisor.writelog("[UI] PageMovingCustom : Check State -> Robot Paused");
                    }else if(supervisor.getStateMoving() === 0){
                        robot_paused = true;
                        popup_pause.visible = true;
                        supervisor.writelog("[UI] PageMovingCustom : Check State -> Robot Not Moving");
                    }else{
                        popup_pause.visible = false;
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
//                timer_check_pause.start();

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
