import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Styles 1.4
import QtMultimedia 5.12
import QtGraphicalEffects 1.0
import "."

Popup{
    id: popup_patrol
    property string mode: "sequence"
    property int select_pos_mode: 0
    property int waittime: 0
    property int passtime: 0
    property int select_preset: -1
    leftPadding: 0
    rightPadding: 0
    topPadding: 0
    bottomPadding: 0
    anchors.centerIn: parent
    width: 1280
    height: 800
    property bool show_menu: false

    background: Rectangle{
        anchors.fill: parent
        opacity: 0.9
        color: color_dark_black
    }

    onOpened:{
        update();
        show_menu = false;
    }

    onSelect_pos_modeChanged: {
        select();
    }

    function update(){
        supervisor.readPatrol();

        model_preset.clear();
        for(var i=0; i<supervisor.getPatrolSize(); i++){
            model_preset.append({"name":supervisor.getPatrolName(i),
                                "type":supervisor.getPatrolType(i),
                                "location":supervisor.getPatrolLocation(i),
                                "moving":supervisor.getPatrolMovingPage(i),
                                "arrive":supervisor.getPatrolArrivePage(i),
                                "wait_time":supervisor.getPatrolWaitTime(i),
                                "pass_time":supervisor.getPatrolPassTime(i),
                                "voice":supervisor.getPatrolVoice(i),
                                "location_size":supervisor.getPatrolLocationSize(i)});

        }



        model_patrols.clear();
        for(var i=0; i<supervisor.getLocationNum(""); i++){
            model_patrols.append({"name":supervisor.getLocationName(i,""),"group":supervisor.getLocationNameGroup(i,""),"type":supervisor.getLocationType(i),"select":false});
        }
        select();

        model_voice_mention.clear();
        model_voice_mention.append({"value":qsTr("감사합니다")});
        model_voice_mention.append({"value":qsTr("안녕하세요")});
        model_voice_mention.append({"value":qsTr("로봇은 열심히 일하는중")});
        model_voice_mention.append({"value":qsTr("안녕하세요(레인보우)")});
        model_voice_mention.append({"value":qsTr("위치를 찾는 중")});
        model_voice_mention.append({"value":qsTr("레인보우화이팅")});
        model_voice_mention.append({"value":qsTr("서빙중입니다")});
        model_voice_mention.append({"value":qsTr("죄송합니다")});
        model_voice_mention.append({"value":qsTr("다음위치로이동")});
        model_voice_mention.append({"value":qsTr("순회를시작합니다")});
        model_voice_mention.append({"value":qsTr("위치를 찾는 중")});
        model_voice_mention.append({"value":qsTr("맛있게드세요")});
        combo_voice_mention.currentIndex = 0;
        waittime = 0;
        combo_voice_name.currentIndex = 0;
        combo_voice_lan.currentIndex = 0;
    }

    function select(){
        for(var i=0; i<model_patrols.count; i++){
            if(popup_patrol.select_pos_mode === 0){
                if(model_patrols.get(i).type === "Serving"){
                    model_patrols.get(i).select = true;
                }else{
                    model_patrols.get(i).select = true;
                }
            }else if(popup_patrol.select_pos_mode === 1){
                if(model_patrols.get(i).type === "Serving"){
                    model_patrols.get(i).select = true;
                }else{
                    model_patrols.get(i).select = false;
                }
            }
        }
    }

    function selectpreset(num){
        popup_patrol.mode = supervisor.getPatrolType(num);

        if(supervisor.getPatrolMovingPage(num) === "location"){
            combo_movingpage.currentIndex = 2;
        }else if(supervisor.getPatrolMovingPage(num) === "custom"){
            combo_movingpage.currentIndex = 3;
        }else if(supervisor.getPatrolMovingPage(num) === "face2"){
            combo_movingpage.currentIndex = 1;
        }else{
            combo_movingpage.currentIndex = 0;
        }

        if(supervisor.getPatrolArrivePage(num) === "pickup"){
            combo_arrivepage.currentIndex = 1;
        }else if(supervisor.getPatrolArrivePage(num) === "calling"){
            combo_arrivepage.currentIndex = 2;
        }else{
            combo_arrivepage.currentIndex = 0;
        }

        if(supervisor.getPatrolVoiceMode(num) === "basic"){
            combo_voice_mode.currentIndex = 1;

            combo_voice_name.currentIndex = supervisor.getPatrolVoiceNameNum(num);

            if(supervisor.getPatrolVoiceMention(num) === "hello"){
                combo_voice_mention.currentIndex = 1;
            }else if(supervisor.getPatrolVoiceMention(num) === "funny_working_hard"){
                combo_voice_mention.currentIndex = 2;
            }else if(supervisor.getPatrolVoiceMention(num) === "hello_rb"){
                combo_voice_mention.currentIndex = 3;
            }else if(supervisor.getPatrolVoiceMention(num) === "path_finding"){
                combo_voice_mention.currentIndex = 4;
            }else if(supervisor.getPatrolVoiceMention(num) === "rb_fighting"){
                combo_voice_mention.currentIndex = 5;
            }else if(supervisor.getPatrolVoiceMention(num) === "moving"){
                combo_voice_mention.currentIndex = 6;
            }else if(supervisor.getPatrolVoiceMention(num) === "sorry"){
                combo_voice_mention.currentIndex = 7;
            }else if(supervisor.getPatrolVoiceMention(num) === "move_next"){
                combo_voice_mention.currentIndex = 8;
            }else if(supervisor.getPatrolVoiceMention(num) === "move_patrol"){
                combo_voice_mention.currentIndex = 9;
            }else if(supervisor.getPatrolVoiceMention(num) === "wait_path"){
                combo_voice_mention.currentIndex = 10;
            }else if(supervisor.getPatrolVoiceMention(num) === "thank_enjoy"){
                combo_voice_mention.currentIndex = 11;
            }else{
                combo_voice_mention.currentIndex = 0;
            }
        }else if(supervisor.getPatrolVoiceMode(num) === "tts"){
            combo_voice_mode.currentIndex = 2;
            tfield_tts_text.text = supervisor.getPatrolVoiceMention(num);
            if(supervisor.getPatrolVoiceLanguage(num) === "en-us"){
                combo_voice_lan.currentIndex = 1;
            }else if(supervisor.getPatrolVoiceLanguage(num) === "en-uk"){
                combo_voice_lan.currentIndex = 2;
            }else if(supervisor.getPatrolVoiceLanguage(num) === "zh-CN"){
                combo_voice_lan.currentIndex = 3;
            }else if(supervisor.getPatrolVoiceLanguage(num) === "ru"){
                combo_voice_lan.currentIndex = 4;
            }else if(supervisor.getPatrolVoiceLanguage(num) === "fr"){
                combo_voice_lan.currentIndex = 5;
            }else if(supervisor.getPatrolVoiceLanguage(num) === "ja"){
                combo_voice_lan.currentIndex = 6;
            }else if(supervisor.getPatrolVoiceLanguage(num) === "id"){
                combo_voice_lan.currentIndex = 7;
            }else if(supervisor.getPatrolVoiceLanguage(num) === "es"){
                combo_voice_lan.currentIndex = 8;
            }else if(supervisor.getPatrolVoiceLanguage(num) === "de"){
                combo_voice_lan.currentIndex = 9;
            }else if(supervisor.getPatrolVoiceLanguage(num) === "la"){
                combo_voice_lan.currentIndex = 10;
            }else{
                combo_voice_lan.currentIndex = 0;
            }
            combo_voice_name.currentIndex = supervisor.getPatrolVoiceNameNum(num);
        }else{
            combo_voice_mode.currentIndex = 0;
        }

        popup_patrol.waittime = supervisor.getPatrolWaitTime(num);


        if(supervisor.getPatrolLocation(num) === "all"){
            popup_patrol.select_pos_mode = 0;
        }else if(supervisor.getPatrolLocation(num) === "serving"){
            popup_patrol.select_pos_mode = 1;
        }else{
            popup_patrol.select_pos_mode = 2;
        }

        for(var i=0; i<model_patrols.count; i++){
            model_patrols.get(i).select = false;
            for(var j=0; j<supervisor.getPatrolLocationSize(num); j++){
                if(supervisor.getPatrolLocation(num,j) === model_patrols.get(i).name){
                    if(supervisor.getPatrolLocationGroup(num,j) === model_patrols.get(i).group){
                        model_patrols.get(i).select = true;
                        break;
                    }

                }
            }
        }
    }

    function save(savemode,name){
        if(select_pos_mode === 0){
            supervisor.clearPatrolLocation("all");
        }else if(select_pos_mode === 1){
            supervisor.clearPatrolLocation("serving");
        }else{
            supervisor.clearPatrolLocation("custom");
        }

        for(var i=0; i<model_patrols.count; i++){
            if(model_patrols.get(i).select){
                supervisor.addPatrolLocation(model_patrols.get(i).group, model_patrols.get(i).name);
            }
        }

        if(combo_movingpage.currentIndex === 1){
            supervisor.setPatrolMovingPage("face2");
        }else if(combo_movingpage.currentIndex === 0){
            supervisor.setPatrolMovingPage("face1");
        }else if(combo_movingpage.currentIndex === 2){
            supervisor.setPatrolMovingPage("location");
        }else if(combo_movingpage.currentIndex === 3){
            supervisor.setPatrolMovingPage("custom");
        }

        if(combo_arrivepage.currentIndex === 1){
            supervisor.setPatrolArrivePage("pickup");
        }else if(combo_arrivepage.currentIndex === 2){
            supervisor.setPatrolArrivePage("calling");
        }else{
            supervisor.setPatrolArrivePage("pass");
        }

        if(combo_voice_mode.currentIndex === 0){//no use
            supervisor.setPatrolVoice("none", 0, 0, 0);
        }else if(combo_voice_mode.currentIndex === 1){//basic
            supervisor.setPatrolVoice("basic", 0, combo_voice_name.currentIndex, slider_voice_volume.value, combo_voice_mention.currentIndex);
        }else if(combo_voice_mode.currentIndex === 2){//tts
            supervisor.makePatrolTTS(combo_voice_lan.currentIndex,combo_voice_name.currentIndex,tfield_tts_text.text);
            supervisor.setPatrolVoice("tts",combo_voice_lan.currentIndex, combo_voice_name.currentIndex, slider_voice_volume.value);
        }


        if(savemode==="save"){
            supervisor.savePatrol(name,mode,popup_patrol.waittime,popup_patrol.passtime);
        }else{
            supervisor.setPatrol(popup_patrol.select_preset,name,mode,popup_patrol.waittime,popup_patrol.passtime);
        }

        update();
        show_menu = false;
    }

    Rectangle{
        id: rect_back
        width: show_menu?1100:500
        height : 700
        radius: 20
        anchors.centerIn: parent
        Behavior on width{
            NumberAnimation{
                duration: 400
            }
        }
        Row{
            anchors.centerIn: parent
            Rectangle{
                id: rect_main
                width: show_menu?300:500
                height: rect_back.height
                color: "transparent"
                Behavior on width{
                    NumberAnimation{
                        duration: 400
                    }
                }
                Column{
                    anchors.fill: parent
                    Rectangle{
                        width: parent.width
                        height: 100
                        color: "transparent"
                        Text{
                            anchors.centerIn : parent
                            text: qsTr("지정 순회")
                            font.family: font_noto_b.name
                            font.pixelSize: 30
                        }
                    }
                    Rectangle{
                        width: parent.width
                        height: parent.height - 200
                        color: "transparent"
                        clip: true
                        Column{
                            anchors.fill: parent
                            Flickable{
                                width: parent.width
                                height: parent.height - 70
                                contentHeight: colss.height
                                Column{
                                    id: colss
                                    spacing: 10
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    Repeater{
                                        model: ListModel{id: model_preset}
                                        Rectangle{
                                            anchors.horizontalCenter: parent.horizontalCenter
                                            width: rect_main.width*0.8
                                            height: 120
                                            radius: 20
                                            color: "transparent"
                                            Rectangle{
                                                width: rect_main.width*0.8
                                                radius: 20
                                                height: 100
                                                color: color_light_gray
                                                anchors.bottom: parent.bottom
                                            }

                                            Column{
                                                anchors.centerIn: parent
                                                spacing: 10
                                                Rectangle{
                                                    anchors.horizontalCenter: parent.horizontalCenter
                                                    width: rect_main.width*0.6
                                                    radius: 10
                                                    color: select_preset === index ? color_green: color_blue
                                                    height: 40
                                                    Text{
                                                        anchors.centerIn: parent
                                                        text: name
                                                        font.family: font_noto_r.name
                                                        color: "white"
                                                        font.pixelSize: 20
                                                        Component.onCompleted: {
                                                            while(scale*width > rect_main.width*0.55){
                                                                scale -=0.05;
                                                            }
                                                        }
                                                        horizontalAlignment: Text.AlignHCenter
                                                    }
                                                }
                                                Rectangle{
                                                    width: rect_main.width*0.8
                                                    radius: 10
                                                    height: 25
                                                    color: "transparent"
                                                    Row{
                                                        anchors.centerIn: parent
                                                        spacing: 5
                                                        Text{
                                                            anchors.verticalCenter: parent.verticalCenter
                                                            text:{
                                                                if(location === "all"){
                                                                    qsTr("전체")
                                                                }else if(location === "serving"){
                                                                    qsTr("서빙")
                                                                }else{
                                                                    qsTr("사용자")
                                                                }
                                                            }
                                                            horizontalAlignment: Text.AlignHCenter
                                                            width : 150
                                                            font.family: font_noto_r.name
                                                            font.pixelSize: 15
                                                        }
                                                        Image{
                                                            width: 25
                                                            height: 25
                                                            sourceSize.width: width
                                                            sourceSize.height: height
                                                            source:{
                                                                type==="random"?"icon/icon_random_b.png":"icon/icon_repeat_b.png"
                                                            }
                                                        }
                                                    }
                                                }
                                                Rectangle{
                                                    width: rect_main.width*0.8
                                                    radius: 10
                                                    height: 25
                                                    color: "transparent"
                                                    Row{
                                                        anchors.centerIn: parent
                                                        Text{
                                                            font.family: font_noto_r.name
                                                            font.pixelSize: 15
                                                            text:{
                                                                if(moving === "location"){
                                                                    qsTr("목적지 / ")
                                                                }else{
                                                                    qsTr("표정 / ")
                                                                }
                                                            }
                                                        }
                                                        Text{
                                                            font.family: font_noto_r.name
                                                            font.pixelSize: 15
                                                            text:{
                                                                if(arrive === "pass"){
                                                                    qsTr("패스 / ")
                                                                }else if(arrive === "calling"){
                                                                    qsTr("호출 / ")
                                                                }else if(arrive === "pickup"){
                                                                    qsTr("픽업 / ")
                                                                }else{
                                                                    qsTr("ㅡㅡ / ")
                                                                }
                                                            }
                                                        }
                                                        Text{
                                                            font.family: font_noto_r.name
                                                            font.pixelSize: 15
                                                            text:wait_time+qsTr(" 초")
                                                        }
                                                    }

                                                }

                                            }

                                            MouseArea{
                                                anchors.fill: parent
                                                onClicked:{
                                                    supervisor.playSound('click');
                                                    if(show_menu){
                                                        popup_change.open();
                                                        popup_change.index = index;
                                                    }else{
                                                        select_preset = index;
                                                        popup_start.open();
                                                    }
                                                }
                                            }
                                        }
                                    }
                                    Rectangle{
                                        width:  rect_main.width*0.8
                                        height: 100
                                        radius: 20
                                        color: color_blue
                                        anchors.horizontalCenter: parent.horizontalCenter
                                        Text{
                                            anchors.centerIn: parent
                                            text: "+"
                                            font.family: font_noto_b.name
                                            font.pixelSize: 40
                                            color: "white"
                                        }
                                        MouseArea{
                                            anchors.fill: parent
                                            onClicked:{
                                                select_preset = -1;
                                                supervisor.playSound('click');
                                                supervisor.initCurrentPatrol();
                                                show_menu = true;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                    Rectangle{
                        width:parent.width
                        height: 100
                        color: "transparent"
                        Rectangle{
                            width:  rect_main.width*0.8
                            height: 80
                            radius: 20
                            color: color_blue
                            anchors.centerIn: parent
                            Text{
                                anchors.centerIn: parent
                                text: qsTr("닫기")
                                font.family: font_noto_b.name
                                font.pixelSize: 30
                                color: "white"
                            }
                            MouseArea{
                                anchors.fill: parent
                                onClicked:{
                                    popup_patrol.close();
                                }
                            }
                        }
                    }
                }
            }
            Rectangle{
                id: rect_menu
                opacity: rect_back.width === 1100?1:0
                width: show_menu?800:0
                height: rect_back.height
                color: "transparent"
                Behavior on width{
                    NumberAnimation{
                        duration: 400
                    }
                }
                Column{
                    visible: rect_menu.opacity === 1
                    anchors.centerIn: parent
                    spacing: 10
                    Rectangle{
                        width: rect_menu.width
                        height: 100
                        color: "transparent"
                        Row{
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.right: parent.right
                            anchors.rightMargin: 50
                            spacing: 50
                            Rectangle{
                                width: 150
                                height: 60
                                radius: 10
                                color: color_blue
                                Text{
                                    anchors.centerIn: parent
                                    text: qsTr("저장")
                                    font.family: font_noto_r.name
                                    font.pixelSize: 20
                                    color: "white"
                                }
                                MouseArea{
                                    anchors.fill: parent
                                    onClicked:{
                                        var select_num = 0;
                                        for(var i=0; i<model_patrols.count; i++){
                                            if(model_patrols.get(i).select)
                                                select_num++;
                                        }

                                        if(select_num > 1){
                                            supervisor.playSound('click');
                                            if(popup_patrol.select_preset === -1){
                                                popup_save.newsave = true;
                                            }else{
                                                popup_save.newsave = false;
                                            }
                                            popup_save.open();
                                        }else{
                                            supervisor.playSound('no');
                                            popup_save_notice.open();
                                            popup_save_notice.textstr = qsTr("순회 위치는 2곳 이상 지정하셔야 합니다")
                                        }

                                    }
                                }
                            }
                            Rectangle{
                                width: 150
                                height: 60
                                radius: 10
                                visible: select_preset > -1
                                color: color_blue
                                Text{
                                    anchors.centerIn: parent
                                    text: qsTr("삭제")
                                    font.family: font_noto_r.name
                                    font.pixelSize: 20
                                    color: "white"
                                }
                                MouseArea{
                                    anchors.fill: parent
                                    onClicked:{
                                        popup_delete.open();
                                    }
                                }
                            }
                            Rectangle{
                                width: 150
                                height: 60
                                radius: 10
                                color: color_blue
                                Text{
                                    anchors.centerIn: parent
                                    text: qsTr("취소")
                                    font.family: font_noto_r.name
                                    font.pixelSize: 20
                                    color: "white"
                                }
                                MouseArea{
                                    anchors.fill: parent
                                    onClicked:{
                                        show_menu = false;
                                    }
                                }
                            }
                        }
                    }
                    Rectangle{
                        width: rect_menu.width
                        height: 100
                        color: color_light_gray
                        Column{
                            anchors.centerIn: parent
                            Rectangle{
                                width: rect_menu.width*0.9
                                height: 80
                                color: "transparent"
                                Row{
                                    anchors.centerIn: parent
                                    spacing: 20
                                    Rectangle{
                                        width: 180
                                        height: 60
                                        radius: 10
                                        color: "transparent"
                                        Text{
                                            anchors.centerIn: parent
                                            text: qsTr("전체위치")
                                            font.family: font_noto_r.name
                                            font.pixelSize: 30
                                            font.bold: popup_patrol.select_pos_mode === 0
                                            color:popup_patrol.select_pos_mode === 0?color_green:color_dark_black
                                        }
                                        MouseArea{
                                            anchors.fill: parent
                                            onClicked:{
                                                supervisor.playSound('click');
                                                popup_patrol.select_pos_mode = 0;
                                            }
                                        }
                                    }
                                    Rectangle{
                                        width: 1
                                        height: 55
                                        anchors.verticalCenter: parent.verticalCenter
                                        color: color_gray
                                    }
                                    Rectangle{
                                        width: 180
                                        height: 60
                                        radius: 10
                                        color: "transparent"
                                        Text{
                                            anchors.centerIn: parent
                                            text: qsTr("서빙위치")
                                            font.family: font_noto_r.name
                                            font.pixelSize: 30
                                            font.bold: popup_patrol.select_pos_mode === 1
                                            color:popup_patrol.select_pos_mode === 1?color_green:color_dark_black
                                        }
                                        MouseArea{
                                            anchors.fill: parent
                                            onClicked:{
                                                supervisor.playSound('click');
                                                popup_patrol.select_pos_mode = 1;
                                            }
                                        }
                                    }
                                    Rectangle{
                                        width: 1
                                        height: 55
                                        anchors.verticalCenter: parent.verticalCenter
                                        color: color_gray
                                    }
                                    Rectangle{
                                        width: 180
                                        height: 60
                                        radius: 10
                                        color: "transparent"
                                        Text{
                                            anchors.centerIn: parent
                                            text: qsTr("사용자 지정")
                                            font.family: font_noto_r.name
                                            font.pixelSize: 30
                                            font.bold: popup_patrol.select_pos_mode === 2
                                            color:popup_patrol.select_pos_mode === 2?color_green:color_dark_black
                                        }
                                        MouseArea{
                                            anchors.fill: parent
                                            onClicked:{
                                                supervisor.playSound('click');
                                                popup_patrol.select_pos_mode = 2;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                    Rectangle{
                        width: rect_menu.width
                        height: rect_menu.height - 220
                        color: "transparent"
                        Row{
                            anchors.fill: parent
                            Rectangle{
                                width: 300
                                height: parent.height
                                color: "transparent"
                                Flickable{
                                    id: flickable_patrol
                                    anchors.fill: parent
                                    clip: true
                                    contentHeight: col_patlist.height
                                    Column{
                                        id: col_patlist
                                        spacing: 10
                                        anchors.centerIn: parent
                                        Repeater{
                                            model: ListModel{id:model_patrols}
                                            Rectangle{
                                                width: 280
                                                height: 50
                                                radius: 5
                                                anchors.horizontalCenter: parent.horizontalCenter
                                                color: select?color_green:"white"
                                                Text{
                                                    anchors.centerIn: parent
                                                    font.family: font_noto_r.name
                                                    text: name
                                                    font.pixelSize: 20
                                                }
                                                MouseArea{
                                                    anchors.fill: parent
                                                    onClicked:{
                                                        supervisor.playSound('click');
                                                        if(select)
                                                            select = false;
                                                        else
                                                            select = true;

                                                        popup_patrol.select_pos_mode = 2;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                            Rectangle{
                                width: 1
                                height: parent.height*0.95
                                anchors.verticalCenter: parent.verticalCenter
                                color: color_gray
                            }
                            Flickable{
                                width: parent.width - 301
                                clip: true
                                height: parent.height<grids.height?parent.height:grids.height
                                anchors.verticalCenter: parent.verticalCenter
                                contentHeight: grids.height
                                Grid{
                                    id: grids
                                    anchors.centerIn: parent
                                    rows: 10
                                    columns: 2
                                    clip: true
                                    spacing: 10
                                    horizontalItemAlignment: Grid.AlignHCenter
                                    verticalItemAlignment: Grid.AlignVCenter
                                    Text{
                                        width: 120
                                        text: qsTr("순회 방식")
                                        horizontalAlignment: Text.AlignHCenter
                                        font.family: font_noto_b.name
                                        font.pixelSize: 16
                                    }
                                    Row{
                                        spacing: 30
                                        Rectangle{
                                            width: 50
                                            height: 50
                                            radius: 10
                                            border.width: 2
                                            border.color:popup_patrol.mode==="sequence"?color_green:color_dark_black
                                            color: popup_patrol.mode==="sequence"?color_green:"transparent"
                                            Image{
                                                width: 40
                                                height: 40
                                                sourceSize.width: width
                                                sourceSize.height: height
                                                anchors.centerIn: parent
                                                source: "icon/icon_repeat_b.png"
                                            }
                                            MouseArea{
                                                anchors.fill: parent
                                                onClicked:{
                                                    supervisor.playSound('click');
                                                    popup_patrol.mode = "sequence";
                                                }
                                            }
                                        }
                                        Rectangle{
                                            width: 50
                                            height: 50
                                            radius: 10
                                            border.width: 2
                                            border.color:popup_patrol.mode==="random"?color_green:color_dark_black
                                            color: popup_patrol.mode==="random"?color_green:"transparent"

                                            Image{
                                                width: 40
                                                height: 40
                                                sourceSize.width: width
                                                sourceSize.height: height
                                                anchors.centerIn: parent
                                                source: "icon/icon_random_b.png"
                                            }
                                            MouseArea{
                                                anchors.fill: parent
                                                onClicked:{
                                                    supervisor.playSound('click');
                                                    popup_patrol.mode = "random";
                                                }
                                            }
                                        }
                                    }
                                    Text{
                                        text: qsTr("이동 중 페이지")
                                        font.family: font_noto_b.name
                                        font.pixelSize: 16
                                    }
                                    Row{
                                        spacing: 10
                                        ComboBox{
                                            id: combo_movingpage
                                            width: currentIndex===2?240:300
                                            height: 50
                                            model:[qsTr("동그란 눈"),qsTr("네모난 눈"),qsTr("목적지 표시"),qsTr("사용자지정화면")]
                                        }
                                        Rectangle{
                                            width: 50
                                            height: 50
                                            radius: 10
                                            visible: combo_movingpage.currentIndex === 3
                                            color: color_dark_navy
                                            Text{
                                                anchors.centerIn: parent
                                                text: qsTr("설정")
                                                color: "white"
                                            }
                                            MouseArea{
                                                anchors.fill: parent
                                                onClicked:{
                                                    popup_patrol_page_main.page = "moving";
                                                    popup_patrol_page_main.page_num = popup_patrol.select_preset;
                                                    popup_patrol_page_main.open();
                                                }
                                            }
                                        }
                                    }

                                    Text{
                                        text: qsTr("도착 후 페이지")
                                        font.family: font_noto_b.name
                                        font.pixelSize: 16
                                    }
                                    ComboBox{
                                        id: combo_arrivepage
                                        width: 300
                                        height: 50
                                        model:[qsTr("페이지표시안함"),qsTr("픽업화면"),qsTr("호출화면")]//,qsTr("사용자지정화면")]
                                    }
                                    Text{
                                        visible: combo_arrivepage.currentIndex === 3
                                        text: qsTr("사용자지정화면 설정")
                                        font.family: font_noto_b.name
                                        font.pixelSize: 16
                                    }
                                    Row{
                                        spacing: 10
                                        visible: combo_arrivepage.currentIndex === 3
                                        Rectangle{
                                            width: 240
                                            height: 50
                                            Text{
                                                anchors.centerIn: parent
                                                text: qsTr("설정되지 않음")
                                            }
                                        }
                                        Rectangle{
                                            width: 50
                                            height: 50
                                            Text{
                                                anchors.centerIn: parent
                                                text: qsTr("설정")
                                            }
                                            MouseArea{
                                                anchors.fill: parent
                                                onClicked:{
                                                    popup_patrol_page_main.page = "arrive";
                                                    popup_patrol_page_main.open();
                                                }
                                            }
                                        }
                                    }
                                    Text{
                                        visible: combo_arrivepage.currentIndex !== 0
                                        text: qsTr("페이지 자동넘김 시간")
                                        font.family: font_noto_b.name
                                        font.pixelSize: 16
                                    }
                                    Row{
                                        visible: combo_arrivepage.currentIndex !== 0
                                        spacing: 10
                                        TextField{
                                            id: tfield_passtime
                                            width: 190
                                            height: 50
                                            text: popup_patrol.passtime
                                            horizontalAlignment: TextField.AlignHCenter
                                            anchors.verticalCenter: parent.verticalCenter
                                            MouseArea{
                                                anchors.fill:parent
                                                onClicked:{
                                                    supervisor.playSound('no');
                                                }
                                            }
                                        }
                                        Text{
                                            width: 40
                                            horizontalAlignment: Text.AlignHCenter
                                            text: qsTr(" 초")
                                            font.family: font_noto_b.name
                                            font.pixelSize: 20
                                            anchors.verticalCenter: parent.verticalCenter
                                        }
                                        Column{
                                            spacing: 3
                                            anchors.verticalCenter: parent.verticalCenter
                                            Rectangle{
                                                width: 50
                                                height: 25
                                                color: color_dark_navy
                                                radius: 5
                                                Image{
                                                    anchors.centerIn: parent
                                                    width: 18
                                                    height: 15
                                                    sourceSize.width: width
                                                    sourceSize.height: height
                                                    source: "icon/joy_up.png"
                                                }
                                                MouseArea{
                                                    anchors.fill: parent
                                                    onClicked:{
                                                        supervisor.playSound('click');
                                                        popup_patrol.passtime++;
                                                    }
                                                }
                                            }
                                            Rectangle{
                                                width: 50
                                                height: 25
                                                color: color_dark_navy
                                                radius: 5
                                                Image{
                                                    anchors.centerIn: parent
                                                    width: 18
                                                    height: 12
                                                    sourceSize.width: width
                                                    sourceSize.height: height
                                                    source: "icon/joy_down.png"
                                                }
                                                MouseArea{
                                                    anchors.fill: parent
                                                    onClicked:{
                                                        supervisor.playSound('click');
                                                        popup_patrol.passtime--;
                                                        if(popup_patrol.passtime < 0)
                                                            popup_patrol.passtime = 0;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                    Text{
                                        text: qsTr("도착 후 대기시간")
                                        font.family: font_noto_b.name
                                        font.pixelSize: 16
                                    }
                                    Row{
                                        spacing: 10
                                        TextField{
                                            id: tfield_waittime
                                            width: 190
                                            height: 50
                                            text: popup_patrol.waittime
                                            horizontalAlignment: TextField.AlignHCenter
                                            anchors.verticalCenter: parent.verticalCenter
                                            MouseArea{
                                                anchors.fill:parent
                                                onClicked:{
                                                    supervisor.playSound('no');
                                                }
                                            }
                                        }
                                        Text{
                                            width: 40
                                            horizontalAlignment: Text.AlignHCenter
                                            text: qsTr(" 초")
                                            font.family: font_noto_b.name
                                            font.pixelSize: 20
                                            anchors.verticalCenter: parent.verticalCenter
                                        }
                                        Column{
                                            spacing: 3
                                            anchors.verticalCenter: parent.verticalCenter
                                            Rectangle{
                                                width: 50
                                                height: 25
                                                color: color_dark_navy
                                                radius: 5
                                                Image{
                                                    anchors.centerIn: parent
                                                    width: 18
                                                    height: 15
                                                    sourceSize.width: width
                                                    sourceSize.height: height
                                                    source: "icon/joy_up.png"
                                                }
                                                MouseArea{
                                                    anchors.fill: parent
                                                    onClicked:{
                                                        supervisor.playSound('click');
                                                        popup_patrol.waittime++;
                                                    }
                                                }
                                            }
                                            Rectangle{
                                                width: 50
                                                height: 25
                                                color: color_dark_navy
                                                radius: 5
                                                Image{
                                                    anchors.centerIn: parent
                                                    width: 18
                                                    height: 12
                                                    source: "icon/joy_down.png"
                                                }
                                                MouseArea{
                                                    anchors.fill: parent
                                                    onClicked:{
                                                        supervisor.playSound('click');
                                                        popup_patrol.waittime--;
                                                        if(popup_patrol.waittime < 0)
                                                            popup_patrol.waittime = 0;
                                                    }
                                                }
                                            }
                                        }
                                    }

                                    Text{
                                        text: qsTr("도착 후 음성")
                                        font.family: font_noto_b.name
                                        font.pixelSize: 16
                                    }
                                    Row{
                                        spacing: 10
                                        ComboBox{
                                            id: combo_voice_mode
                                            width: 300
                                            height: 50
                                            model:[qsTr("사용안함"),qsTr("지정된음성"),qsTr("만들기")]
                                            onCurrentIndexChanged: {
                                                model_voice_name.clear();
                                                if(currentIndex === 1){
                                                    model_voice_name.append({"value":qsTr("여성")});
                                                    model_voice_name.append({"value":qsTr("어린이")});
                                                }else if(currentIndex === 2){
                                                    model_voice_name.clear();
                                                    if(combo_voice_lan.currentIndex === 0){
                                                        model_voice_name.append({"value":qsTr("여자어린이")});
                                                        model_voice_name.append({"value":qsTr("여자성인")});
                                                        model_voice_name.append({"value":qsTr("남자어린이")});
                                                        model_voice_name.append({"value":qsTr("남자성인")});
                                                        model_voice_name.append({"value":qsTr("남자성인2")});
                                                        model_voice_name.append({"value":qsTr("할머니")});
                                                        model_voice_name.append({"value":qsTr("할아버지")});
                                                        model_voice_name.append({"value":qsTr("마녀")});
                                                        model_voice_name.append({"value":qsTr("악마")});
                                                    }else if(combo_voice_lan.currentIndex === 1){
                                                        model_voice_name.append({"value":qsTr("여자어린이")});
                                                        model_voice_name.append({"value":qsTr("여자성인")});
                                                        model_voice_name.append({"value":qsTr("남자성인")});
                                                    }else if(combo_voice_lan.currentIndex === 2){
                                                        model_voice_name.append({"value":qsTr("여자성인")});
                                                        model_voice_name.append({"value":qsTr("남자성인")});
                                                    }else if(combo_voice_lan.currentIndex === 3){
                                                        model_voice_name.append({"value":qsTr("여자어린이")});
                                                        model_voice_name.append({"value":qsTr("여자성인")});
                                                        model_voice_name.append({"value":qsTr("남자어린이")});
                                                        model_voice_name.append({"value":qsTr("남자성인")});
                                                    }else if(combo_voice_lan.currentIndex === 4){
                                                        model_voice_name.append({"value":qsTr("여자성인")});
                                                        model_voice_name.append({"value":qsTr("남자성인")});
                                                    }else{

                                                    }
                                                }
                                            }
                                        }
                                    }
                                    Text{
                                        text: qsTr("멘트")
                                        visible: combo_voice_mode.currentIndex !== 0
                                        font.family: font_noto_b.name
                                        font.pixelSize: 16
                                    }
                                    Row{
                                        spacing: 10
                                        visible: combo_voice_mode.currentIndex === 1
                                        ComboBox{
                                            id: combo_voice_mention
                                            width: 240
                                            height: 50
                                            model:ListModel{id: model_voice_mention}
                                        }
                                        Rectangle{
                                            width: 50
                                            height: 40
                                            radius: 40
                                            anchors.verticalCenter: parent.verticalCenter
                                            Image{
                                                anchors.centerIn: parent
                                                source: "icon/icon_test_play.png"
                                                width: 40
                                                height: 40
                                                sourceSize.width: width
                                                sourceSize.height: height
                                            }
                                            MouseArea{
                                                anchors.fill: parent
                                                onClicked:{
                                                    var mention = combo_voice_mention.currentIndex;
                                                    var file;
                                                    if(mention == 0){
                                                        file = "thanks";
                                                    }else if(mention == 1){
                                                        file = "hello";
                                                    }else if(mention == 2){
                                                        file = "funny_working_hard";
                                                    }else if(mention == 3){
                                                        file = "hello_rb";
                                                    }else if(mention == 4){
                                                        file = "path_finding";
                                                    }else if(mention == 5){
                                                        file = "rb_fighting";
                                                    }else if(mention == 6){
                                                        file = "moving";
                                                    }else if(mention == 7){
                                                        file = "sorry";
                                                    }else if(mention == 8){
                                                        file = "move_next";
                                                    }else if(mention == 9){
                                                        file = "move_patrol";
                                                    }else if(mention == 10){
                                                        file = "wait_path";
                                                    }else{
                                                        file = "thank_enjoy";
                                                    }
                                                    supervisor.playVoice(file,"woman","basic","",slider_voice_volume.value);
                                                }
                                            }
                                        }
                                    }
                                    Row{
                                        spacing: 10
                                        visible: combo_voice_mode.currentIndex === 2
                                        TextField{
                                            id: tfield_tts_text
                                            width: 240
                                            height: 50
                                        }
                                        Rectangle{
                                            width: 50
                                            height: 50
                                            radius:10
                                            color: enabled?color_dark_navy:color_gray
                                            Image{
                                                anchors.centerIn: parent
                                                width: 35
                                                height: 35
                                                sourceSize.width: width
                                                sourceSize.height: height
                                                source: "icon/icon_keyboard.png"
                                                ColorOverlay{
                                                    anchors.fill: parent
                                                    source: parent
                                                    color: "white"
                                                }
                                            }
                                            MouseArea{
                                                enabled: parent.enabled
                                                anchors.fill: parent
                                                onClicked:{
                                                    supervisor.playSound('click');
                                                    keyboard.owner = tfield_tts_text;
                                                    tfield_tts_text.selectAll();
                                                    keyboard.open();
                                                }
                                            }
                                        }
                                    }
                                    Text{
                                        text: qsTr("언어")
                                        visible: combo_voice_mode.currentIndex === 2
                                        font.family: font_noto_b.name
                                        font.pixelSize: 16
                                    }
                                    Row{
                                        spacing: 10
                                        visible: combo_voice_mode.currentIndex === 2
                                        ComboBox{
                                            id: combo_voice_lan
                                            width: 300
                                            height: 50
                                            model:[qsTr("한국어"),qsTr("영어"),qsTr("중국어"),qsTr("일본어"),qsTr("스페인어"),qsTr("러시아어"),qsTr("독일어")]
                                            onCurrentIndexChanged: {
                                                model_voice_name.clear();
                                                if(currentIndex === 0){
                                                    model_voice_name.append({"value":qsTr("여자어린이")});
                                                    model_voice_name.append({"value":qsTr("여자성인")});
                                                    model_voice_name.append({"value":qsTr("남자어린이")});
                                                    model_voice_name.append({"value":qsTr("남자성인")});
                                                    model_voice_name.append({"value":qsTr("남자성인2")});
                                                    model_voice_name.append({"value":qsTr("할머니")});
                                                    model_voice_name.append({"value":qsTr("할아버지")});
                                                    model_voice_name.append({"value":qsTr("마녀")});
                                                    model_voice_name.append({"value":qsTr("악마")});
                                                }else if(currentIndex === 1){
                                                    model_voice_name.append({"value":qsTr("여자어린이")});
                                                    model_voice_name.append({"value":qsTr("여자성인")});
                                                    model_voice_name.append({"value":qsTr("남자성인")});
                                                }else if(currentIndex === 2){
                                                    model_voice_name.append({"value":qsTr("여자성인")});
                                                    model_voice_name.append({"value":qsTr("남자성인")});
                                                }else if(currentIndex === 3){
                                                    model_voice_name.append({"value":qsTr("여자어린이")});
                                                    model_voice_name.append({"value":qsTr("여자성인")});
                                                    model_voice_name.append({"value":qsTr("남자어린이")});
                                                    model_voice_name.append({"value":qsTr("남자성인")});
                                                }else if(currentIndex === 4){
                                                    model_voice_name.append({"value":qsTr("여자성인")});
                                                    model_voice_name.append({"value":qsTr("남자성인")});
                                                }
                                            }
                                        }
                                    }
                                    Text{
                                        text: qsTr("음성볼륨")
                                        visible: combo_voice_mode.currentIndex !== 0
                                        font.family: font_noto_b.name
                                        font.pixelSize: 16
                                    }
                                    Slider{
                                        visible: combo_voice_mode.currentIndex !== 0
                                        id: slider_voice_volume
//                                        anchors.verticalCenter: parent.verticalCenter
                                        width: 300
                                        height: 50
                                        from: 0
                                        to: 100
                                        property bool ischanged: false
                                        value: 100
                                    }

                                    Text{
                                        text: qsTr("음성")
                                        visible: combo_voice_mode.currentIndex === 2
                                        font.family: font_noto_b.name
                                        font.pixelSize: 16
                                    }
                                    Row{
                                        spacing: 10
                                        visible: combo_voice_mode.currentIndex === 2 && combo_voice_lan.currentIndex < 5
                                        ComboBox{
                                            id: combo_voice_name
                                            width: 240
                                            height: 50
                                            model:ListModel{id:model_voice_name}
                                        }
                                        Rectangle{
                                            width: 50
                                            height: 40
                                            radius: 40
                                            anchors.verticalCenter: parent.verticalCenter
                                            Image{
                                                anchors.centerIn: parent
                                                source: "icon/icon_test_play.png"
                                                width: 40
                                                height: 40
                                                sourceSize.width: width
                                                sourceSize.height: height
                                            }
                                            MouseArea{
                                                anchors.fill: parent
                                                onClicked:{
                                                    supervisor.makePatrolTTS(combo_voice_lan.currentIndex,combo_voice_name.currentIndex,tfield_tts_text.text);
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    Popup{
        id: popup_change
        anchors.centerIn: parent
        width: 1000
        height: 300
        property int index: -1
        background: Rectangle{
            anchors.fill: parent
            color: "transparent"
        }
        Rectangle{
            width: parent.width
            height: parent.height
            radius: 20
            Column{
                anchors.centerIn: parent
                spacing: 50
                Text{
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: qsTr("선택하신 순회옵션을 불러오시겠습니까?\n저장되지 않은 변경사항은 전부 사라집니다")
                    font.family: font_noto_r.name
                    font.pixelSize: 20
                    horizontalAlignment: Text.AlignHCenter
                }
                Row{
                    anchors.horizontalCenter: parent.horizontalCenter
                    spacing: 50
                    Item_buttons{
                        type: "round_text"
                        text: qsTr("확인")
                        width: 160
                        height: 70
                        onClicked:{
                            popup_patrol.select_preset = popup_change.index;
                            supervisor.setCurrentPatrol(popup_patrol.select_preset);
                            selectpreset(popup_patrol.select_preset);
                            popup_change.close();
                        }
                    }
                    Item_buttons{
                        type: "round_text"
                        text: qsTr("취소")
                        width: 160
                        height: 70
                        onClicked:{
                            popup_patrol.select_preset = -1;
                            popup_change.close();
                        }
                    }
                }
            }
        }
    }

    Popup{
        id: popup_save_notice
        anchors.centerIn: parent
        width: 1000
        height: 400
        property string textstr: ""
        background: Rectangle{
            anchors.fill: parent
            color: "transparent"
        }
        Rectangle{
            width: parent.width
            height: parent.height
            radius: 20
            color: color_red
            Column{
                anchors.centerIn: parent
                Image{
                    anchors.horizontalCenter: parent.horizontalCenter
                    source: "image/warning.png"
                    width: 150
                    height: 150
                    sourceSize.width: width
                    sourceSize.height: height
                }
                Text{
                    anchors.horizontalCenter: parent.horizontalCenter
                    text:popup_save_notice.textstr
                    color: "white"
                    font.bold: true
                    font.family: font_noto_b.name
                    font.pixelSize: 40
                }
            }

            MouseArea{
                anchors.fill: parent
                onClicked:{
                    popup_save_notice.close();
                }
            }
        }
    }
    Popup{
        id: popup_save
        anchors.centerIn: parent
        width: 1000
        height: 350
        background: Rectangle{
            anchors.fill: parent
            color: "transparent"
        }
        property bool newsave: true
        onOpened:{
            if(newsave){
                tfield_name.text = "";
            }else{
                tfield_name.text = model_preset.get(popup_patrol.select_preset).name;
            }
        }

        Rectangle{
            width: parent.width
            height: parent.height
            radius: 20
            color: color_light_gray
            Column{
                anchors.centerIn: parent
                spacing: 20
                Text{
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: qsTr("저장하시겠습니까?")
                    font.family: font_noto_r.name
                    font.pixelSize: 35
                    horizontalAlignment: Text.AlignHCenter
                }
                TextField{
                    id: tfield_name
                    width: 500
                    height: 60
                    text: ""
                    placeholderText: qsTr("옵션 이름을 입력해주세요")
                    placeholderTextColor: color_red
                    font.pixelSize: 20
                    font.family: font_noto_r.name
                    anchors.horizontalCenter: parent.horizontalCenter
                    onTextChanged: {
                        color = "black";
                    }
                    MouseArea{
                        anchors.fill:parent
                        onClicked:{
                            supervisor.playSound('click');
                            keyboard.owner = tfield_name;
                            keyboard.owner_text = "tfield_name";
                            tfield_name.selectAll();

                            keyboard.open();

                        }
                    }
                }
                Row{
                    anchors.horizontalCenter: parent.horizontalCenter
                    spacing: 50
                    Item_buttons{
                        type: "round_text"
                        text: qsTr("확인")
                        width: 160
                        height: 70
                        onClicked:{
                            if(tfield_name.text !== ""){
                                supervisor.playSound('click');
                                if(popup_save.newsave){
                                    save("save",tfield_name.text);
                                }else{
                                    save("edit",tfield_name.text);
                                }
                                popup_patrol.select_preset = -1;
                                popup_save.close();
                            }else{
                                supervisor.playSound('no');
                                tfield_name.color = color_red;
                            }
                        }
                    }
                    Item_buttons{
                        type: "round_text"
                        text: qsTr("취소")
                        width: 160
                        height: 70
                        onClicked:{
                            popup_save.close();
                        }
                    }
                }
            }
        }
    }
    Popup{
        id: popup_delete
        anchors.centerIn: parent
        width: 1000
        height: 350
        background: Rectangle{
            anchors.fill: parent
            color: "transparent"
        }
        Rectangle{
            width: parent.width
            height: parent.height
            radius: 20
            color: color_light_gray
            Column{
                anchors.centerIn: parent
                spacing: 20
                Text{
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: qsTr("선택하신 옵션을 삭제하시겠습니까?")
                    font.family: font_noto_r.name
                    font.pixelSize: 35
                    horizontalAlignment: Text.AlignHCenter
                }
                Row{
                    anchors.horizontalCenter: parent.horizontalCenter
                    spacing: 50
                    Item_buttons{
                        type: "round_text"
                        text: qsTr("확인")
                        width: 160
                        height: 70
                        onClicked:{
                            supervisor.deletePatrol(popup_patrol.select_preset);
                            popup_patrol.select_preset = -1;
                            popup_patrol.update();
                            popup_delete.close();
                        }
                    }
                    Item_buttons{
                        type: "round_text"
                        text: qsTr("취소")
                        width: 160
                        height: 70
                        onClicked:{
                            popup_delete.close();
                        }
                    }
                }
            }
        }
    }

    Popup{
        id: popup_start
        anchors.centerIn: parent
        width: 1000
        height: 350
        background: Rectangle{
            anchors.fill: parent
            color: "transparent"
        }
        Rectangle{
            width: parent.width
            height: parent.height
            radius: 20
            Column{
                anchors.centerIn: parent
                spacing: 20
                Text{
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: qsTr("선택하신 옵션으로 순회를 시작하시겠습니까?")
                    font.family: font_noto_r.name
                    font.pixelSize: 20
                }
                Rectangle{
                    anchors.horizontalCenter: parent.horizontalCenter
                    width: 500
                    height: 120
                    radius: 10
                    color: "transparent"
                    Rectangle{
                        anchors.horizontalCenter: parent.horizontalCenter
                        width: 500
                        height: 100
                        radius: 10
                        color: color_light_gray
                        anchors.bottom: parent.bottom
                    }
                    Column{
                        anchors.centerIn: parent
                        spacing: 10
                        Rectangle{
                            anchors.horizontalCenter: parent.horizontalCenter
                            width: rect_main.width*0.6
                            radius: 10
                            color: color_green
                            height: 40
                            Text{
                                anchors.centerIn: parent
                                text: select_preset>-1&&select_preset<model_preset.count?model_preset.get(select_preset).name:""
                                font.family: font_noto_r.name
                                color: "white"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    while(scale*width > rect_main.width*0.55){
                                        scale -=0.05;
                                    }
                                }
                                horizontalAlignment: Text.AlignHCenter
                            }
                        }
                        Rectangle{
                            width: rect_main.width*0.8
                            radius: 10
                            height: 25
                            color: "transparent"
                            Row{
                                anchors.centerIn: parent
                                spacing: 5
                                Text{
                                    anchors.verticalCenter: parent.verticalCenter
                                    text:{
                                        if(select_preset>-1&&select_preset<model_preset.count){
                                            if(model_preset.get(select_preset).location === "all"){
                                                qsTr("전체")
                                            }else if(model_preset.get(select_preset).location === "serving"){
                                                qsTr("서빙")
                                            }else{
                                                qsTr("사용자")
                                            }
                                        }else{
                                            ""
                                        }
                                    }
                                    horizontalAlignment: Text.AlignHCenter
                                    width : 150
                                    font.family: font_noto_r.name
                                    font.pixelSize: 15
                                }
                                Image{
                                    width: 25
                                    height: 25
                                    sourceSize.width: width
                                    sourceSize.height: height
                                    source:{
                                        select_preset>-1&&select_preset<model_preset.count?model_preset.get(select_preset).type==="random"?"icon/icon_random_b.png":"icon/icon_repeat_b.png":"icon/icon_repeat_b.png"
                                    }
                                }
                            }
                        }
                        Rectangle{
                            width: rect_main.width*0.8
                            radius: 10
                            height: 25
                            color: "transparent"
                            Row{
                                anchors.centerIn: parent
                                Text{
                                    font.family: font_noto_r.name
                                    font.pixelSize: 15
                                    text:{
                                        if(select_preset>-1&&select_preset<model_preset.count){
                                            if(model_preset.get(select_preset).moving === "location"){
                                                qsTr("목적지 / ")
                                            }else{
                                                qsTr("표정 / ")
                                            }
                                        }else{
                                            ""
                                        }

                                    }
                                }
                                Text{
                                    font.family: font_noto_r.name
                                    font.pixelSize: 15
                                    text:{
                                        if(select_preset>-1&&select_preset<model_preset.count){
                                            if(model_preset.get(select_preset).arrive === "pass"){
                                                qsTr("패스 / ")
                                            }else if(model_preset.get(select_preset).arrive === "calling"){
                                                qsTr("호출 / ")
                                            }else if(model_preset.get(select_preset).arrive === "pickup"){
                                                qsTr("픽업 / ")
                                            }else{
                                                qsTr("ㅡㅡ / ")
                                            }
                                        }else{
                                            qsTr("ㅡㅡ / ")
                                        }

                                    }
                                }
                                Text{
                                    font.family: font_noto_r.name
                                    font.pixelSize: 15
                                    text:select_preset>-1&&select_preset<model_preset.count?model_preset.get(select_preset).wait_time:"0"+qsTr(" 초")
                                }
                            }

                        }

                    }


                }

                Row{
                    anchors.horizontalCenter: parent.horizontalCenter
                    spacing: 50
                    Item_buttons{
                        type: "round_text"
                        text: qsTr("확인")
                        width: 160
                        height: 70
                        onClicked:{
                            supervisor.playSound('click');
                            supervisor.startPatrol(popup_patrol.select_preset);
                            popup_start.close();
                        }
                    }
                    Item_buttons{
                        type: "round_text"
                        text: qsTr("취소")
                        width: 160
                        height: 70
                        onClicked:{
                            popup_start.close();
                        }
                    }
                }
            }
        }
    }

    Rectangle{
        width: parent.width
        height: parent.height
        visible: false
        radius: 10
        color: color_dark_navy
        Column{
            anchors.fill: parent
            Rectangle{
                width: parent.width
                height: parent.height-90
                color: "transparent"
                Column{
                    anchors.centerIn: parent
                    spacing: 20
                    Rectangle{
                        width: 200
                        height: 80
                        radius: 30
                        anchors.horizontalCenter: parent.horizontalCenter
                        color: color_green
                        Text{
                            anchors.centerIn: parent
                            text: qsTr("순회 시작")
                            font.pixelSize: 40
                            color: "white"
                            font.family: font_noto_b.name
                        }
                        MouseArea{
                            anchors.fill: parent
                            onClicked: {
                                popup_patrol.close();
                            }
                        }
                    }

                }

            }
        }

    }
    Tool_Keyboard{
        id: keyboard
    }
    Tool_KeyPad{
        id: keypad
    }
}

