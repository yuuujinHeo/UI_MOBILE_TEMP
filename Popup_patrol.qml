import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

Popup{
    id: popup_patrol
    property string mode: "sequence"
    property int select_pos_mode: 0
    property int waittime: 0
    property int select_preset: -1
    leftPadding: 0
    rightPadding: 0
    topPadding: 0
    bottomPadding: 0
    anchors.centerIn: parent
    width: 500
    height: 700
    property bool show_menu: false

    background: Rectangle{
        anchors.fill: parent
        color: "transparent"
    }

    onShow_menuChanged: {
        print(show_menu, rect_back.width);
    }

    onOpened:{
        cols_patrol_bigmenu.visible = true;
        update();
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
                                "voice":supervisor.getPatrolVoice(i),
                                "location_size":supervisor.getPatrolLocationSize(i)});

        }



        model_patrols.clear();
        for(var i=0; i<supervisor.getLocationNum(""); i++){
            model_patrols.append({"name":supervisor.getLocationName(i,""),"type":supervisor.getLocationType(i),"select":false});
            print(i,supervisor.getLocationName(i,""))
        }
        select();

        model_voice_temp.clear();
        model_voice_temp.append({"file":"thank"});
        model_voice_temp.append({"file":"hello"});
        model_voice.clear();
        model_voice.append({"value":qsTr("감사합니다")});
        model_voice.append({"value":qsTr("안녕하세요")});
        combo_voice.currentIndex = 0;
        waittime = 0;
        combo_voice_mode.currentIndex = 0;
    }



    ListModel{
        id: model_voice_temp
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

        for(var i=0; i<model_voice.count; i++){
            if(model_voice.get(i).file === supervisor.getPatrolVoice(num)){
                combo_voice.currentIndex = i;
                break;
            }
        }

        popup_patrol.waittime = supervisor.getPatrolWaitTime(num);
        if(supervisor.getPatrolVoiceMode(num) === "child"){
            combo_voice_mode.currentIndex = 1;
        }else{
            combo_voice_mode.currentIndex = 0;
        }

        if(supervisor.getPatrolLocation(num) === "all"){
            popup_patrol.select_pos_mode = 0;
        }else if(supervisor.getPatrolLocation(num) === "serving"){
            popup_patrol.select_pos_mode = 1;
        }else{
            popup_patrol.select_pos_mode = 2;
        }

        print("?????????????",model_patrols.count);
        for(var i=0; i<model_patrols.count; i++){
            model_patrols.get(i).select = false;
            for(var j=0; j<supervisor.getPatrolLocationSize(num); j++){
                print(supervisor.getPatrolLocation(num,j), model_patrols.get(i).name)
                if(supervisor.getPatrolLocation(num,j) === model_patrols.get(i).name){
                    model_patrols.get(i).select = true;
                    break;
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
                supervisor.addPatrolLocation(model_patrols.get(i).name);
            }
        }

        if(combo_movingpage.currentIndex === 1){
            supervisor.setPatrolMovingPage("location");
        }else{
            supervisor.setPatrolMovingPage("face");
        }

        if(combo_arrivepage.currentIndex === 1){
            supervisor.setPatrolArrivePage("pickup");
        }else if(combo_arrivepage.currentIndex === 2){
            supervisor.setPatrolArrivePage("calling");
        }else{
            supervisor.setPatrolArrivePage("pass");
        }

        if(combo_voice_mode.currentIndex === 0){
            supervisor.setPatrolVoice(model_voice_temp.get(combo_voice.currentIndex).file, "woman", "50");
        }else{
            supervisor.setPatrolVoice(model_voice_temp.get(combo_voice.currentIndex).file, "child", "50");
        }

        if(savemode==="save"){
            supervisor.savePatrol(name,mode,parseInt(tfield_waittime.text));
        }else{
            supervisor.setPatrol(popup_patrol.select_preset,name,mode,parseInt(tfield_waittime.text));
        }

        update();
        show_menu = false;
    }

    Rectangle{
        id: rect_back
        width: show_menu?1100:500
        height : popup_patrol.height
        radius: 20
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
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
                height: popup_patrol.height
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
//                            color:
                        }
                    }
                    Rectangle{
                        width: parent.width
                        height: parent.height - 100
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
                                                    click_sound.play();
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
                                                click_sound.play();
                                                show_menu = true;
                                            }
                                        }
                                    }
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
                height: popup_patrol.height
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
                                            click_sound.play();
                                            if(popup_patrol.select_preset === -1){
                                                popup_save.newsave = true;
                                            }else{
                                                popup_save.newsave = false;
                                            }
                                            popup_save.open();
                                        }else{
                                            click_sound_no.play();
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
                                                click_sound.play();
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
                                                click_sound.play();
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
                                                click_sound.play();
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
                            spacing: 5
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
                                                        click_sound.play();
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
                                width: parent.width - 311
                                height: parent.height<grids.height?parent.height:grids.height
//                                anchors.centerIn: parent
                                anchors.verticalCenter: parent.verticalCenter
                                contentHeight: grids.height
                                Grid{
                                    id: grids
                                    anchors.centerIn: parent
                                    rows: 10
                                    columns: 2
                                    spacing: 10
                                    horizontalItemAlignment: Grid.AlignHCenter
                                    verticalItemAlignment: Grid.AlignVCenter
                                    Text{
                                        width: 150
                                        text: qsTr("순회 방식")
                                        horizontalAlignment: Text.AlignHCenter
                                        font.family: font_noto_b.name
                                        font.pixelSize: 16
                                    }
                                    Row{
                                        spacing: 30
                                        Rectangle{
                                            width: 55
                                            height: 55
                                            radius: 10
                                            border.width: 2
                                            border.color:popup_patrol.mode==="sequence"?color_green:color_dark_black
                                            color: popup_patrol.mode==="sequence"?color_green:"transparent"
                                            Image{
                                                width: 40
                                                height: 40
                                                anchors.centerIn: parent
                                                source: "icon/icon_repeat_b.png"
                                            }
                                            MouseArea{
                                                anchors.fill: parent
                                                onClicked:{
                                                    click_sound.play();
                                                    popup_patrol.mode = "sequence";
                                                }
                                            }
                                        }
                                        Rectangle{
                                            width: 55
                                            height: 55
                                            radius: 10
                                            border.width: 2
                                            border.color:popup_patrol.mode==="random"?color_green:color_dark_black
                                            color: popup_patrol.mode==="random"?color_green:"transparent"

                                            Image{
                                                width: 40
                                                height: 40
                                                anchors.centerIn: parent
                                                source: "icon/icon_random_b.png"
                                            }
                                            MouseArea{
                                                anchors.fill: parent
                                                onClicked:{
                                                    click_sound.play();
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
                                    ComboBox{
                                        id: combo_movingpage
                                        width: 250
                                        height: 50
                                        model:[qsTr("귀여운 표정"),qsTr("목적지 표시")]//,qsTr("사용자지정화면"),qsTr("비디오")]
                                    }
                                    Text{
                                        visible: combo_movingpage.currentIndex === 2
                                        text: qsTr("사용자지정화면 설정")
                                        font.family: font_noto_b.name
                                        font.pixelSize: 16
                                    }
                                    Row{
                                        spacing: 10
                                        visible: combo_movingpage.currentIndex === 2
                                        Rectangle{
                                            width: 200
                                            height: 50
                                        }
                                        Rectangle{
                                            width: 50
                                            height: 50
                                        }
                                    }
                                    Text{
                                        visible: combo_movingpage.currentIndex === 3
                                        text: qsTr("비디오 설정")
                                        font.family: font_noto_b.name
                                        font.pixelSize: 16
                                    }
                                    Row{
                                        spacing: 10
                                        visible: combo_movingpage.currentIndex === 3
                                        Rectangle{
                                            width: 200
                                            height: 50
                                        }
                                        Rectangle{
                                            width: 50
                                            height: 50
                                        }
                                    }
                                    Text{
                                        text: qsTr("도착 후 페이지")
                                        font.family: font_noto_b.name
                                        font.pixelSize: 16
                                    }
                                    ComboBox{
                                        id: combo_arrivepage
                                        width: 250
                                        height: 50
                                        model:[qsTr("페이지표시안함"),qsTr("픽업화면"),qsTr("호출화면")]//,qsTr("사용자지정화면")]
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
                                            width: 150
                                            height: 50
                                            text: popup_patrol.waittime
                                            horizontalAlignment: TextField.AlignHCenter
                                            anchors.verticalCenter: parent.verticalCenter
                                            MouseArea{
                                                anchors.fill:parent
                                                onClicked:{
                                                    click_sound_no.play();
                                                }
                                            }
                                        }
                                        Text{
                                            text: qsTr(" 초")
                                            font.family: font_noto_b.name
                                            font.pixelSize: 20
                                            anchors.verticalCenter: parent.verticalCenter
                                        }
                                        Column{
                                            spacing: 3
                                            anchors.verticalCenter: parent.verticalCenter
                                            Rectangle{
                                                width: 35
                                                height: 25
                                                color: color_dark_navy
                                                radius: 5
                                                Image{
                                                    anchors.centerIn: parent
                                                    width: 18
                                                    height: 15
                                                    source: "icon/joy_up.png"
                                                }
                                                MouseArea{
                                                    anchors.fill: parent
                                                    onClicked:{
                                                        click_sound.play();
                                                        popup_patrol.waittime++;
                                                    }
                                                }
                                            }
                                            Rectangle{
                                                width: 35
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
                                                        click_sound.play();
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
                                            width: 200
                                            height: 50
                                            model:[qsTr("여성"),qsTr("어린이")]
                                        }
                                        Rectangle{
                                            width: 40
                                            height: 40
                                            radius: 40
                                            anchors.verticalCenter: parent.verticalCenter
                                            Image{
                                                anchors.centerIn: parent
                                                source: "icon/icon_test_play.png"
                                                width: 40
                                                height: 40
                                            }
                                            MouseArea{
                                                anchors.fill: parent
                                                onClicked:{

                                                }
                                            }
                                        }
                                    }
                                    Text{
                                        text: qsTr("도착 후 멘트")
                                        font.family: font_noto_b.name
                                        font.pixelSize: 16
                                    }
                                    Row{
                                        spacing: 10
                                        ComboBox{
                                            id: combo_voice
                                            width: 250
                                            height: 50
                                            model:ListModel{id: model_voice}
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
                                click_sound.play();
                                if(popup_save.newsave){
                                    save("save",tfield_name.text);
                                }else{
                                    save("edit",tfield_name.text);
                                }
                                popup_patrol.select_preset = -1;
                                popup_save.close();
                            }else{
                                click_sound_no.play();
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
                            click_sound.play();
                            supervisor.startPatrol(popup_patrol.select_preset);
//                            if(popup_patrol.select_pos_mode === 0){
//                                click_sound.play();
//                                supervisor.clearRotateList();
//                                for(var i=0; i<supervisor.getLocationNum("");i++){
//                                    supervisor.setRotateList(supervisor.getLocationName(i,""));
//                                }
//                                supervisor.startPatrol(popup_patrol.mode,false);
//                            }else if(popup_patrol.select_pos_mode === 1){
//                                click_sound.play();
//                                supervisor.clearRotateList();
//                                for(var i=0; i<supervisor.getLocationNum("Serving");i++){
//                                    supervisor.setRotateList(supervisor.getLocationName(i,"Serving"));
//                                }
//                                supervisor.startPatrol(popup_patrol.mode,false);
//                            }else if(popup_patrol.select_pos_mode === 2){
//                                click_sound.play();
//                                supervisor.clearRotateList();
//                                for(var i=0; i<model_patrols.count; i++){
//                                    if(model_patrols.get(i).select){
//                                        supervisor.setRotateList(model_patrols.get(i).name);
//                                    }
//                                }
//                                supervisor.startPatrol(popup_patrol.mode,false);

//                            }else{
//                                click_sound.play();
//                            }

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
}

