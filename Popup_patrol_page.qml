import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.0
import io.qt.Supervisor 1.0
import QtMultimedia 5.12
import QtQuick.Dialogs 1.3
import "."

Popup {
    id: popup_setting_patrolpage
    width: 1280
    height: 800
    closePolicy: Popup.NoAutoClose
    leftPadding: 0
    rightPadding: 0
    topPadding: 0
    bottomPadding: 0
    property string page: "moving"
    property int page_num: -1
    background:Rectangle{
        anchors.fill: parent
        color: "#282828"
        opacity: 0.8
    }
    onOpened:{
        loader_movepage.sourceComponent = move_page;
        loader_movepage.item.setEdit(true);
        init();
    }
    onClosed:{
        loader_movepage.item.close();
        loader_movepage.sourceComponent = "";
    }

    function init(){
        print("patrolpage init " +objectName +" " + page + " ");
        model_obj.clear();
        loader_movepage.item.setPage(page);
        if(page == "moving"){
            for(var i=0; i<supervisor.getPatrolObjectSize(); i++){
                model_obj.append({"type":supervisor.getPageObjectType(i),
                                 "ob_source":supervisor.getPageObjectSource(i),
                                 "ob_color":supervisor.getPageObjectColor(i),
                                 "ob_x":supervisor.getPageObjectX(i),
                                 "ob_y":supervisor.getPageObjectY(i),
                                 "ob_width":supervisor.getPageObjectWidth(i),
                                 "ob_height":supervisor.getPageObjectHeight(i),
                                 "fontsize":supervisor.getPageObjectFontsize(i)});
                print("object append : ",supervisor.getPageObjectType(i),supervisor.getPageObjectSource(i))
            }

            loader_movepage.item.background_mode = supervisor.getMovingPageBackground()
            if(supervisor.getMovingPageBackground() === "color"){
                combo_background_mode.currentIndex = 0;
                loader_movepage.item.background_source = supervisor.getMovingPageColor()
                rect_color.color = supervisor.getMovingPageColor()
                text_color.text = supervisor.getMovingPageColor()
            }else if(supervisor.getMovingPageBackground() === "image"){
                combo_background_mode.currentIndex = 1;
                loader_movepage.item.background_source = supervisor.getMovingPageImage();
                text_image.text = supervisor.getMovingPageImage().split("/").pop()
            }else if(supervisor.getMovingPageBackground() === "video"){
                combo_background_mode.currentIndex = 2;
                loader_movepage.item.background_source = supervisor.getMovingPageVideo();
                text_video.text = supervisor.getMovingPageVideo().split("/").pop()
                if(supervisor.getMovingPageVideoAudio() === "video"){
                    combo_video_audio_mode.currentIndex = 0;
                }else if(supervisor.getMovingPageVideoAudio() === "music1"){
                    combo_video_audio_mode.currentIndex = 1;
                }
                print("kk : ",supervisor.getMovingPageVideo(),supervisor.getMovingPageVideoAudio(),text_video.text )
                loader_movepage.item.video_audio = supervisor.getMovingPageVideoAudio();
            }
            loader_movepage.item.setVolume(supervisor.getMovingPageAudio());

        }else if(page == "serving"){
            for(var i=0; i<supervisor.getServingObjectSize(); i++){
                model_obj.append({"type":supervisor.getServingObjectType(i),
                                 "ob_source":supervisor.getServingObjectSource(i),
                                 "ob_color":supervisor.getServingObjectColor(i),
                                 "ob_x":supervisor.getServingObjectX(i),
                                 "ob_y":supervisor.getServingObjectY(i),
                                 "ob_width":supervisor.getServingObjectWidth(i),
                                 "ob_height":supervisor.getServingObjectHeight(i),
                                 "fontsize":supervisor.getServingObjectFontsize(i)});
                print("object append : ",supervisor.getServingObjectType(i),supervisor.getServingObjectSource(i))
            }

            loader_movepage.item.background_mode = supervisor.getServingPageBackground()

            if(supervisor.getServingPageBackground() === "color"){
                combo_background_mode.currentIndex = 0;
                loader_movepage.item.background_source = supervisor.getServingPageColor()
                rect_color.color = supervisor.getServingPageColor()
                text_color.text = supervisor.getServingPageColor()
            }else if(supervisor.getServingPageBackground() === "image"){
                combo_background_mode.currentIndex = 1;
                loader_movepage.item.background_source = supervisor.getServingPageImage();
                text_image.text = supervisor.getServingPageImage().split("/").pop()
            }else if(supervisor.getServingPageBackground() === "video"){
                combo_background_mode.currentIndex = 2;
                loader_movepage.item.background_source = supervisor.getServingPageVideo();
                text_video.text = supervisor.getServingPageVideo().split("/").pop()
                if(supervisor.getServingPageVideoAudio() === "video"){
                    combo_video_audio_mode.currentIndex = 0;
                }else if(supervisor.getServingPageVideoAudio() === "music1"){
                    combo_video_audio_mode.currentIndex = 1;
                }
                loader_movepage.item.video_audio = supervisor.getServingPageVideoAudio();
            }
            loader_movepage.item.setVolume(supervisor.getServingPageAudio());
        }

    }
    function update(){
        model_obj.clear();
        loader_movepage.item.update();
        if(page == "moving"){
            for(var i=0; i<supervisor.getPatrolObjectSize(); i++){
                model_obj.set(i,{"type":supervisor.getPageObjectType(i),
                                 "ob_source":supervisor.getPageObjectSource(i),
                                 "ob_color":supervisor.getPageObjectColor(i),
                                 "ob_x":supervisor.getPageObjectX(i),
                                 "ob_y":supervisor.getPageObjectY(i),
                                 "ob_width":supervisor.getPageObjectWidth(i),
                                 "ob_height":supervisor.getPageObjectHeight(i),
                                 "fontsize":supervisor.getPageObjectFontsize(i)});
                print("object append : ",supervisor.getPageObjectType(i),supervisor.getPageObjectSource(i))
            }
        }else if(page == "serving"){
            for(var i=0; i<supervisor.getServingObjectSize(); i++){
                model_obj.append({"type":supervisor.getServingObjectType(i),
                                 "ob_source":supervisor.getServingObjectSource(i),
                                 "ob_color":supervisor.getServingObjectColor(i),
                                 "ob_x":supervisor.getServingObjectX(i),
                                 "ob_y":supervisor.getServingObjectY(i),
                                 "ob_width":supervisor.getServingObjectWidth(i),
                                 "ob_height":supervisor.getServingObjectHeight(i),
                                 "fontsize":supervisor.getServingObjectFontsize(i)});
                print("object append : ",supervisor.getServingObjectType(i),supervisor.getServingObjectSource(i))
            }
        }
    }

    Rectangle{
        id: parentrect
        width: 1280
        height: 800
        anchors.centerIn: parent
        color:"transparent"
        Column{
            spacing: 5
            Rectangle{
                id: rect_list_top
                height: 150
                width: parentrect.width
                color: color_dark_navy
                Text{
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 50
                    color: "white"
                    font.family: font_noto_b.name
                    font.bold: true
                    text: page==="moving"?qsTr("순회 중 표시화면 설정"):qsTr("이동 중 표시화면 설정")
                    font.pixelSize: 40
                }

                Row{
                    anchors.rightMargin: 30
                    anchors.right: parent.right
                    anchors.verticalCenter: parent.verticalCenter
                    spacing: 20
                    Item_buttons{
                        width: 130
                        height: 60
                        type: "round_text"
                        text: qsTr("저 장")
                        onClicked: {
                            if(page == "serving"){
                                supervisor.saveServingPage();
                            }else if(page == "moving"){
                                loader_movepage.item.saveMovingPage();
                            }

                            popup_setting_patrolpage.close();
                        }
                    }
                    Item_buttons{
                        width: 130
                        height: 60
                        type: "round_text"
                        text: qsTr("초기화")
                        onClicked: {
                            if(page == "moving"){
                                supervisor.clearPatrolPage(popup_setting_patrolpage.page_num);
                            }else if(page == "serving"){
                                supervisor.clearServingPage();
                            }
                            popup_setting_patrolpage.init();
                        }
                    }
                    Item_buttons{
                        width: 140
                        height: 60
                        type: "round_text"
                        text: qsTr("취 소")
                        onClicked: {
                            if(page == "moving"){
//                                supervisor.clearPatrolPage(popup_setting_patrolpage.page_num);
                            }else if(page == "serving"){
//                                supervisor.clearServingPage();
                            }
                            popup_setting_patrolpage.close();
                        }
                    }

                }
            }

            Row{
                anchors.horizontalCenter: parent.horizontalCenter
                Rectangle{
                    width: 850
                    height: width*800/1280
                    anchors.verticalCenter: parent.verticalCenter
                    Loader{
                        id: loader_movepage
                        anchors.fill: parent
                    }

                    Component{
                        id: move_page
                        Page_moving_custom{
                            objectName: "patrolllllllllll"//popup_setting_patrolpage.objectName
                            anchors.fill: parent
                            edit_mode: true
                            page: popup_setting_patrolpage.page
                            onDoubleclicked: {
                                print("double clicked : ",loader_movepage.item.select_obj)
                                popup_edit.obj_num = loader_movepage.item.select_obj;
                                popup_edit.open();
                            }
                        }
                    }

                }

                Rectangle{
                    id: rect_patrol_set
                    width: 1280-850
                    height: 800-150
                    color: color_light_gray
                    Flickable{
                        anchors.fill: parent
                        clip: true
                        contentHeight: cols_me.height
                        Column{
                            id: cols_me
                            spacing: 30
                            anchors.horizontalCenter: parent.horizontalCenter
                            Column{
                                spacing: 10
                                anchors.horizontalCenter: parent.horizontalCenter
                                Rectangle{
                                    color: "black"
                                    width: 450
                                    height: 45
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    Text{
                                        text: qsTr("배경 설정")
                                        color: "white"
                                        font.family: font_noto_r.name
                                        font.pixelSize: 25
                                        anchors.centerIn: parent
                                    }
                                    Image{
                                        width: 35
                                        height: 20
                                        sourceSize.width: width
                                        sourceSize.height: height
                                        source: column_background.visible?"icon/joy_up.png":"icon/joy_down.png"
                                        anchors.verticalCenter: parent.verticalCenter
                                        anchors.right: parent.right
                                        anchors.rightMargin: 10
                                    }

                                    MouseArea{
                                        anchors.fill: parent
                                        onClicked:{
                                            if(column_background.visible){
                                                column_background.visible = false;
                                            }else{
                                                column_background.visible = true;
                                            }
                                        }
                                    }
                                }
                                Column{
                                    id: column_background
                                    spacing: 10
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    Row{
                                        anchors.horizontalCenter: parent.horizontalCenter
                                        Text{
                                            width: 100
                                            text: qsTr("모드 : ")
                                            anchors.verticalCenter: parent.verticalCenter
                                        }
                                        ComboBox{
                                            id: combo_background_mode
                                            model:["color","image","video"]
                                            currentIndex: 0
                                            anchors.verticalCenter: parent.verticalCenter
                                            width: 250
                                            height: 50
                                            onCurrentIndexChanged: {
                                                print("background mode index : ",currentIndex);
                                                if(currentIndex === 0){
                                                    loader_movepage.item.background_mode = "color";
                                                }else if(currentIndex === 1){
                                                    loader_movepage.item.background_mode = "image";
                                                }else if(currentIndex === 2){
                                                    loader_movepage.item.background_mode = "video";
                                                }

                                                if(page == "moving"){
                                                    supervisor.setMovingPageBackground(loader_movepage.item.background_mode);
                                                }else if(page == "serving"){
                                                    supervisor.setServingPageBackground(loader_movepage.item.background_mode);
                                                }

                                            }
                                        }
                                    }
                                    Row{
                                        visible: combo_background_mode.currentIndex === 0
                                        anchors.horizontalCenter: parent.horizontalCenter
                                        Text{
                                            width: 100
                                            text: qsTr("색 상 : ")
                                            anchors.verticalCenter: parent.verticalCenter
                                        }
                                        Rectangle{
                                            id: rect_color
                                            width: 250
                                            clip: true
                                            height: 50
                                            color: {
                                                if(page == "moving"){
                                                    supervisor.getMovingPageColor()===""?"white":supervisor.getMovingPageColor()
                                                }else if(page == "serving"){
                                                    supervisor.getServingPageColor()===""?"white":supervisor.getServingPageColor()
                                                }
                                            }
                                            Text{
                                                id: text_color
                                                anchors.centerIn: parent
                                                text:{
                                                    if(page == "moving"){
                                                        supervisor.getMovingPageImage()===""?qsTr("선택되지 않음"):supervisor.getMovingPageImage().split("/").pop()
                                                    }else if(page == "serving"){
                                                        supervisor.getServingPageImage()===""?qsTr("선택되지 않음"):supervisor.getServingPageImage().split("/").pop()
                                                    }
                                                }
                                            }
                                            MouseArea{
                                                anchors.fill: parent
                                                onClicked:{
                                                    loader_movepage.item.pauseGif();
                                                    color_dialog.open();
                                                }
                                            }
                                            ColorDialog{
                                                id: color_dialog
                                                onSelectionAccepted: {
                                                    if(page == "moving"){
                                                        supervisor.setMovingPageColor(color_dialog.color);
                                                        loader_movepage.item.background_source = supervisor.getMovingPageColor()
                                                        rect_color.color = supervisor.getMovingPageColor()
                                                        text_color.text = supervisor.getMovingPageColor()
                                                    }else if(page == "serving"){
                                                        supervisor.setServingPageColor(color_dialog.color);
                                                        loader_movepage.item.background_source = supervisor.getServingPageColor()
                                                        rect_color.color = supervisor.getServingPageColor()
                                                        text_color.text = supervisor.getServingPageColor()
                                                    }
                                                    loader_movepage.item.resumeGif();

                                                }
                                            }
                                        }
                                    }
                                    Row{
                                        visible: combo_background_mode.currentIndex === 1
                                        anchors.horizontalCenter: parent.horizontalCenter
                                        Text{
                                            width: 100
                                            text: qsTr("이미지 : ")
                                            anchors.verticalCenter: parent.verticalCenter
                                        }
                                        Rectangle{
                                            id: rect_image
                                            width: 250
                                            clip: true
                                            height: 50
                                            Text{
                                                id: text_image
                                                anchors.centerIn: parent
                                                text:{
                                                    if(page == "moving"){
                                                        supervisor.getMovingPageImage()===""?qsTr("선택되지 않음"):supervisor.getMovingPageImage().split("/").pop()
                                                    }else if(page == "serving"){
                                                        supervisor.getServingPageImage()===""?qsTr("선택되지 않음"):supervisor.getServingPageImage().split("/").pop()
                                                    }
                                                }
                                            }
                                            MouseArea{
                                                anchors.fill: parent
                                                onClicked:{
                                                    loader_movepage.item.pauseGif();
                                                    image_dialog.open();
                                                }
                                            }
                                        }
                                    }
                                    Row{
                                        visible: combo_background_mode.currentIndex === 2
                                        anchors.horizontalCenter: parent.horizontalCenter
                                        Text{
                                            width: 100
                                            text: qsTr("비디오 : ")
                                            anchors.verticalCenter: parent.verticalCenter
                                        }
                                        Rectangle{
                                            id: rect_video
                                            width: 250
                                            height: 50
                                            clip: true
                                            Text{
                                                id: text_video
                                                anchors.centerIn: parent
                                                text:{
                                                    if(page == "moving"){
                                                        supervisor.getMovingPageVideo()===""?qsTr("선택되지 않음"):supervisor.getMovingPageVideo().split("/").pop()
                                                    }else if(page == "serving"){
                                                        supervisor.getServingPageVideo()===""?qsTr("선택되지 않음"):supervisor.getServingPageVideo().split("/").pop()
                                                    }
                                                }
                                            }
                                            MouseArea{
                                                anchors.fill: parent
                                                onClicked:{
                                                    loader_movepage.item.pauseGif();
                                                    image_dialog.open();
                                                }
                                            }
                                        }
                                    }
                                    Row{
                                        visible: combo_background_mode.currentIndex === 2
                                        anchors.horizontalCenter: parent.horizontalCenter
                                        Text{
                                            width: 100
                                            text: qsTr("오디오 : ")
                                            anchors.verticalCenter: parent.verticalCenter
                                        }
                                        ComboBox{
                                            id: combo_video_audio_mode
                                            model:[qsTr("영상오디오"),qsTr("음악")]
                                            currentIndex: 0
                                            anchors.verticalCenter: parent.verticalCenter
                                            width: 250
                                            height: 50
                                            onCurrentIndexChanged: {
                                                print("background mode index : ",currentIndex);
                                                if(currentIndex === 0){
                                                    loader_movepage.item.video_audio = "video";
                                                }else if(currentIndex === 1){
                                                    loader_movepage.item.video_audio = "music1";
                                                }

                                            }
                                        }
                                    }
                                    Row{
                                        visible: combo_background_mode.currentIndex === 2
                                        anchors.horizontalCenter: parent.horizontalCenter
                                        Text{
                                            width: 100
                                            text: qsTr("오디오볼륨 : ")
                                            anchors.verticalCenter: parent.verticalCenter
                                        }
                                        Rectangle{
                                            id: rect_audio
                                            width: 250
                                            height: 50
                                            clip: true
                                            color: "transparent"
                                            Row{
                                                anchors.centerIn: parent
                                                spacing: 5
                                                Image{
                                                    id: ttet1
                                                    source: "icon/icon_mute.png"
                                                    anchors.verticalCenter: parent.verticalCenter
                                                    MouseArea{
                                                        anchors.fill: parent
                                                        onClicked: {
                                                            click_sound.play();
                                                            if(slider_audio.value == 0){
                                                                if(page == "moving"){
                                                                    slider_audio.value  = supervisor.getMovingPageAudio();
                                                                }else if(page == "serving"){
                                                                    slider_audio.value  = supervisor.getServingPageAudio();
                                                                }
                                                            }else{
                                                                slider_audio.value  = 0;
                                                            }
                                                        }
                                                    }
                                                }
                                                Slider{
                                                    id: slider_audio
                                                    width: 200
                                                    value : {
                                                        if(page == "moving"){
                                                            supervisor.getMovingPageAudio()
                                                        }else if(page == "serving"){
                                                            supervisor.getServingPageAudio()
                                                        }
                                                    }
                                                    anchors.verticalCenter: parent.verticalCenter
                                                    to: 1
                                                    from: 0
                                                    onPressedChanged: {
                                                        if(pressed){

                                                        }else{
                                                            if(page == "moving"){
                                                                supervisor.setMovingPageAudio(value)
                                                            }else if(page == "serving"){
                                                                supervisor.setServingPageAudio(value)
                                                            }
                                                            loader_movepage.item.setVolume(value);
                                                            print("value : " ,value)
                                                        }
                                                    }
                                                }
                                            }


                                        }
                                    }
                                }
                            }

                            FileDialog{
                                id: image_dialog
                                title: qsTr("파일을 선택해주세요")
                                folder: shortcuts.home
                                onAccepted:{
                                    if(page == "moving"){
                                        if(combo_background_mode.currentIndex === 0){
                                        }else if(combo_background_mode.currentIndex === 1){
                                            supervisor.setMovingPageImage(image_dialog.fileUrl);
                                            loader_movepage.item.background_source = image_dialog.fileUrl;
                                            text_image.text = image_dialog.fileUrl.toString().split("/").pop()
                                        }else if(combo_background_mode.currentIndex === 2){
                                            supervisor.setMovingPageVideo(image_dialog.fileUrl);
                                            loader_movepage.item.background_source = image_dialog.fileUrl;
                                            text_video.text = image_dialog.fileUrl.toString().split("/").pop()
                                        }
                                    }else if(page == "serving"){
                                        if(combo_background_mode.currentIndex === 0){
                                        }else if(combo_background_mode.currentIndex === 1){
                                            supervisor.setServingPageImage(image_dialog.fileUrl);
                                            loader_movepage.item.background_source = image_dialog.fileUrl;
                                            text_image.text = image_dialog.fileUrl.toString().split("/").pop()
                                        }else if(combo_background_mode.currentIndex === 2){
                                            supervisor.setServingPageVideo(image_dialog.fileUrl);
                                            loader_movepage.item.background_source = image_dialog.fileUrl;
                                            text_video.text = image_dialog.fileUrl.toString().split("/").pop()
                                        }
                                    }
                                    loader_movepage.item.resumeGif();

                                }
                            }

                            Column{
                                spacing: 10
                                anchors.horizontalCenter: parent.horizontalCenter
                                Rectangle{
                                    color: "black"
                                    width: 450
                                    height: 45
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    Text{
                                        text: qsTr("요소 설정")
                                        color: "white"
                                        font.family: font_noto_r.name
                                        font.pixelSize: 25
                                        anchors.centerIn: parent
                                    }
                                    Image{
                                        width: 35
                                        height: 20
                                        sourceSize.width: width
                                        sourceSize.height: height
                                        source: column_background.visible?"icon/joy_up.png":"icon/joy_down.png"
                                        anchors.verticalCenter: parent.verticalCenter
                                        anchors.right: parent.right
                                        anchors.rightMargin: 10
                                    }

                                    MouseArea{
                                        anchors.fill: parent
                                        onClicked:{
                                            if(column_obj.visible){
                                                column_obj.visible = false;
                                            }else{
                                                column_obj.visible = true;
                                            }
                                        }
                                    }
                                }
                                Column{
                                    id: column_obj
                                    spacing: 10
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    Row{
                                        spacing: 10
                                        anchors.horizontalCenter: parent.horizontalCenter
                                        Rectangle{
                                            width: 120
                                            height: 50
                                            radius: 5
                                            color: "black"
                                            Text{
                                                anchors.centerIn: parent
                                                color: "white"
                                                text:qsTr("추가")
                                            }
                                            MouseArea{
                                                anchors.fill: parent
                                                onClicked:{
                                                    popup_add.open();
                                                }
                                            }
                                        }
                                        Rectangle{
                                            width: 120
                                            height: 50
                                            radius: 5
                                            color: "black"
                                            Text{
                                                anchors.centerIn: parent
                                                color: "white"
                                                text:qsTr("수정")
                                            }
                                            MouseArea{
                                                anchors.fill: parent
                                                onClicked:{
                                                    if(loader_movepage.item.select_obj>-1){
                                                        click_sound_no.play();
                                                    }else{
                                                        click_sound.play();
                                                        popup_edit.open();
                                                    }
                                                }
                                            }
                                        }
                                        Rectangle{
                                            width: 120
                                            height: 50
                                            radius: 5
                                            color: "black"
                                            Text{
                                                anchors.centerIn: parent
                                                color: "white"
                                                text:qsTr("삭제")
                                            }
                                            MouseArea{
                                                anchors.fill: parent
                                                onClicked:{
                                                    if(loader_movepage.item.select_obj>-1){
                                                        click_sound_no.play();
                                                    }else{
                                                        click_sound.play();
                                                        popup_delete.open();
                                                    }
                                                }
                                            }
                                        }
                                    }
                                    Flickable{
                                        width: 400
                                        anchors.horizontalCenter: parent.horizontalCenter
                                        height: cols_objs.height < 400?cols_objs.height:400
                                        contentHeight: cols_objs.height
                                        Column{
                                            id: cols_objs
                                            anchors.horizontalCenter: parent.horizontalCenter
                                            spacing: 5
                                            Repeater{
                                                model: ListModel{id: model_obj}
                                                Rectangle{
                                                    width: 400
                                                    height: 50
                                                    Row{
                                                        Rectangle{
                                                            width: 50
                                                            height: 50
                                                            color: loader_movepage.item.select_obj===index?color_red:"black"
                                                            Text{
                                                                anchors.centerIn: parent
                                                                color: "white"
                                                                text: index
                                                            }
                                                        }
                                                        Rectangle{
                                                            width: 250
                                                            height: 50
                                                            Text{
                                                                anchors.centerIn: parent
                                                                text: type
                                                            }
                                                        }
                                                        Rectangle{
                                                            width: 100
                                                            height: 50
                                                            radius: 5
                                                            visible: false
                                                            color: "black"
                                                            Text{
                                                                anchors.centerIn: parent
                                                                text: qsTr("상세")
                                                                color: "white"

                                                            }
                                                            MouseArea{
                                                                anchors.fill: parent
                                                                onClicked:{

                                                                }
                                                            }
                                                        }
                                                    }

                                                    MouseArea{
                                                        anchors.fill: parent
                                                        onClicked:{
                                                            click_sound.play();
                                                            loader_movepage.item.select_obj = index;
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }

                            Rectangle{
                                width: 150
                                height: 70
                                anchors.horizontalCenter: parent.horizontalCenter
                                radius: 10
                                color: "black"
                                Text{
                                    anchors.centerIn: parent
                                    color: "white"
                                    font.pixelSize: 25
                                    text: qsTr("적 용")
                                    font.family: font_noto_r.name
                                }
                                MouseArea{
                                    anchors.fill: parent
                                    onClicked:{
                                        click_sound.play();
                                        if(page == "serving"){
                                            supervisor.saveServingPage();
                                        }else if(page == "moving"){
                                            loader_movepage.item.saveMovingPage();//etMovingPageVideoAudio(loader_movepage.item.voice_audio);
                                        }

                                        popup_setting_patrolpage.close();
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        Popup{
            id: popup_add
            anchors.centerIn: parent
            width: 500
            height: 400
            background:Rectangle{
                anchors.fill: parent
                color: "transparent"
            }
            Rectangle{
                width: parent.width
                height: parent.height
                radius: 10

                Column{
                    anchors.centerIn: parent
                    spacing: 50
                    Row{
                        anchors.horizontalCenter: parent.horizontalCenter
                        spacing: 20
                        Rectangle{
                            width: 200
                            height: 250
                            radius: 20
                            color: color_navy
                            Text{
                                anchors.centerIn: parent
                                color: "white"
                                font.family: font_noto_r.name
                                text: qsTr("이미지")
                                font.pixelSize: 40
                            }
                            MouseArea{
                                anchors.fill: parent
                                onClicked:{
                                    click_sound.play();
                                    if(page == "moving"){
                                        supervisor.addPatrolObject(popup_setting_patrolpage.page,"image")
                                    }else if(page == "serving"){
                                        supervisor.addServingObject(popup_setting_patrolpage.page,"image")
                                    }

                                    popup_setting_patrolpage.init();
                                    popup_add.close();
                                }
                            }
                        }
                        Rectangle{
                            width: 200
                            height: 250
                            radius: 20
                            color: color_navy
                            Text{
                                anchors.centerIn: parent
                                color: "white"
                                font.family: font_noto_r.name
                                text: qsTr("텍스트")
                                font.pixelSize: 40
                            }
                            MouseArea{
                                anchors.fill: parent
                                onClicked:{
                                    click_sound.play();
                                    if(page == "moving"){
                                        supervisor.addPatrolObject(popup_setting_patrolpage.page,"text")
                                    }else if(page == "serving"){
                                        supervisor.addServingObject(popup_setting_patrolpage.page,"text")
                                    }
                                    popup_setting_patrolpage.init();
                                    popup_add.close();
                                }
                            }
                        }
                    }
                }
            }
        }

        Popup{
            id: popup_edit
            anchors.centerIn: parent
            width: 600
            height: 350
            background:Rectangle{
                anchors.fill: parent
                color: "transparent"
            }
            property var obj_num: -1
            onOpened:{
                obj_num = loader_movepage.item.select_obj;
                if(page == "moving"){
                    if(supervisor.getPageObjectType(obj_num) === "image"){
                        col_image.visible = true;
                        col_text.visible = false;
                        tfield_image.fullurl = supervisor.getPageObjectSource(obj_num);
                        tfield_image.text = supervisor.getPageObjectSource(obj_num).split("/").pop();
                    }else if(supervisor.getPageObjectType(obj_num) === "text"){
                        col_image.visible = false;
                        col_text.visible = true;
                        tfield_text.text = supervisor.getPageObjectSource(obj_num);
                        color_dialog2.color = supervisor.getPageObjectColor(obj_num);
                    }
                }else if(page == "serving"){
                    if(supervisor.getServingObjectType(obj_num) === "image"){
                        col_image.visible = true;
                        col_text.visible = false;
                        tfield_image.fullurl = supervisor.getServingObjectSource(obj_num);
                        tfield_image.text = supervisor.getServingObjectSource(obj_num).split("/").pop();
                    }else if(supervisor.getServingObjectType(obj_num) === "text"){
                        col_image.visible = false;
                        col_text.visible = true;
                        tfield_text.text = supervisor.getServingObjectSource(obj_num);
                        color_dialog2.color = supervisor.getServingObjectColor(obj_num);
                    }
                }
            }

            Rectangle{
                width: parent.width
                height: parent.height
                radius: 10
                Column{
                    id: col_image
                    anchors.centerIn: parent
                    spacing: 30
                    Text{
                        anchors.horizontalCenter: parent.horizontalCenter
                        font.family: font_noto_r.name
                        font.pixelSize: 45
                        text: qsTr("이미지를 선택해주세요")
                    }

                    Row{
                        anchors.horizontalCenter: parent.horizontalCenter
                        TextField{
                            id: tfield_image
                            width: 350
                            height: 60
                            readOnly: true
                            property string fullurl:""
                            MouseArea{
                                anchors.fill:parent
                                onClicked: {
                                    click_sound.play();
                                    loader_movepage.item.pauseGif();
                                    image_edit_dialog.open();
                                }
                            }
                        }
                    }
                    FileDialog{
                        id: image_edit_dialog
                        title: qsTr("파일을 선택해주세요")
                        folder: shortcuts.home
                        onAccepted:{
                            tfield_image.fullurl = image_edit_dialog.fileUrl
                            tfield_image.text = image_edit_dialog.fileUrl.toString().split("/").pop()

                            loader_movepage.item.resumeGif();
                        }
                    }
                    Row{
                        anchors.horizontalCenter: parent.horizontalCenter
                        spacing: 30
                        Rectangle{
                            width: 160
                            height: 60
                            radius: 10
                            color: color_navy
                            Text{
                                text: qsTr("취소")
                                color: "white"
                                anchors.centerIn: parent
                                font.family: font_noto_r.name
                                font.pixelSize: 30
                            }
                            MouseArea{
                                anchors.fill: parent
                                onClicked:{
                                    popup_edit.obj_num = -1;
                                    popup_edit.close();
                                }
                            }
                        }
                        Rectangle{
                            width: 160
                            height: 60
                            radius: 10
                            color: color_navy
                            Text{
                                text: qsTr("저장")
                                color: "white"
                                anchors.centerIn: parent
                                font.family: font_noto_r.name
                                font.pixelSize: 30
                            }
                            MouseArea{
                                anchors.fill: parent
                                onClicked:{
                                    if(page == "moving"){
                                        supervisor.setPageObjectSource(popup_edit.obj_num,tfield_image.fullurl);
                                    }else if(page == "serving"){
                                        supervisor.setServingObjectSource(popup_edit.obj_num,tfield_image.fullurl);
                                    }

                                    popup_setting_patrolpage.update();
                                    popup_edit.close();
                                }
                            }
                        }
                    }


                }
                Column{
                    id: col_text
                    anchors.centerIn: parent
                    spacing: 30
                    Text{
                        anchors.horizontalCenter: parent.horizontalCenter
                        font.family: font_noto_r.name
                        font.pixelSize: 45
                        text: qsTr("텍스트를 입력해주세요")
                    }

                    Row{
                        spacing: 5
                        anchors.horizontalCenter: parent.horizontalCenter
                        TextField{
                            id: tfield_text
                            width: 350
                            height: 60
                            color: color_dialog2.color
                            MouseArea{
                                anchors.fill:parent
                                onClicked: {
                                    click_sound.play();
                                    if(keyboard.is_opened){
                                        keyboard.owner = tfield_text;
                                        tfield_text.selectAll();
                                    }else{
                                        keyboard.owner = tfield_text;
                                        tfield_text.selectAll();
                                        keyboard.open();
                                    }
                                }
                            }
                        }

                        Rectangle{
                            id: rect_color_text
                            width: 60
                            height: 60
                            radius: 5
                            Image{
                                anchors.centerIn: parent
                                width: 50
                                height: 50
                                sourceSize.width: width
                                sourceSize.height: height
                                source: "icon/icon_colorwheel.png"
                            }
                            MouseArea{
                                anchors.fill: parent
                                onClicked:{
                                    loader_movepage.item.pauseGif();
                                    color_dialog2.open();
                                }
                            }
                            ColorDialog{
                                id: color_dialog2
                                color: "black"
                                onSelectionAccepted: {
                                    print("set color ",color_dialog2.color)
                                    loader_movepage.item.resumeGif();
//                                    rect_color_text.color = color_dialog2.color
                                }
                            }
                        }
                    }

                    Row{
                        anchors.horizontalCenter: parent.horizontalCenter
                        spacing: 30
                        Rectangle{
                            width: 160
                            height: 60
                            radius: 10
                            color: color_navy
                            Text{
                                text: qsTr("취소")
                                color: "white"
                                anchors.centerIn: parent
                                font.family: font_noto_r.name
                                font.pixelSize: 30
                            }
                            MouseArea{
                                anchors.fill: parent
                                onClicked:{
                                    popup_edit.obj_num = -1;
                                    popup_edit.close();
                                }
                            }
                        }
                        Rectangle{
                            width: 160
                            height: 60
                            radius: 10
                            color: color_navy
                            Text{
                                text: qsTr("저장")
                                color: "white"
                                anchors.centerIn: parent
                                font.family: font_noto_r.name
                                font.pixelSize: 30
                            }
                            MouseArea{
                                anchors.fill: parent
                                onClicked:{
                                    if(page == "moving"){
                                        supervisor.setPageObjectColor(popup_edit.obj_num, color_dialog2.color);
                                        supervisor.setPageObjectSource(popup_edit.obj_num, tfield_text.text);
                                    }else if(page == "serving"){
                                        supervisor.setServingObjectColor(popup_edit.obj_num, color_dialog2.color);
                                        supervisor.setServingObjectSource(popup_edit.obj_num, tfield_text.text);
                                    }

                                    popup_setting_patrolpage.update();
                                    popup_edit.close();
                                    loader_movepage.item.resumeGif();
                                    color_dialog2.close();
                                }
                            }
                        }
                    }


                }
            }
        }

        Popup{
            id: popup_delete
            anchors.centerIn: parent
            width: 600
            height: 350
            background:Rectangle{
                anchors.fill: parent
                color: "transparent"
            }
            Rectangle{
                width: parent.width
                height: parent.height
                radius: 10
                Column{
                    anchors.centerIn: parent
                    spacing: 40
                    Text{
                        anchors.horizontalCenter: parent.horizontalCenter
                        font.family: font_noto_r.name
                        font.pixelSize: 35
                        text: qsTr("선택한 요소를 삭제하시겠습니까?")
                    }
                    Row{
                        anchors.horizontalCenter: parent.horizontalCenter
                        spacing: 30
                        Rectangle{
                            width: 160
                            height: 60
                            radius: 10
                            color: color_navy
                            Text{
                                text: qsTr("취소")
                                color: "white"
                                anchors.centerIn: parent
                                font.family: font_noto_r.name
                                font.pixelSize: 30
                            }
                            MouseArea{
                                anchors.fill: parent
                                onClicked:{
                                    popup_delete.close();
                                }
                            }
                        }
                        Rectangle{
                            width: 160
                            height: 60
                            radius: 10
                            color: color_navy
                            Text{
                                text: qsTr("삭제")
                                color: "white"
                                anchors.centerIn: parent
                                font.family: font_noto_r.name
                                font.pixelSize: 30
                            }
                            MouseArea{
                                anchors.fill: parent
                                onClicked:{
                                    if(page == "moving"){
                                        supervisor.deletePatrolObject(loader_movepage.item.obj_num);
                                    }else if(page == "serving"){
                                        supervisor.deleteServingObject(loader_movepage.item.obj_num);
                                    }
                                    popup_setting_patrolpage.init();
                                    popup_delete.close();
                                }
                            }
                        }
                    }
                }

            }
        }
    }
}
