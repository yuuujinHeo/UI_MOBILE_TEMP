import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.0
import io.qt.Supervisor 1.0
import QtMultimedia 5.12
// 가능한 모든 맵 리스트 보여주기
Popup{
    id: popup_map_list
    width: 1280
    height: 800
    closePolicy: Popup.NoAutoClose
    leftPadding: 0
    rightPadding: 0
    topPadding: 0
    bottomPadding: 0
    property string temp_name: ""
    property int select_map_list: -1
    property int cur_group: 0
    property int table_num: 0
    property string modify_date_str: ""
    property string map_size_str: ""
    property string grid_width_str: ""
    background:Rectangle{
        anchors.fill: parent
        color: "#282828"
        opacity: 0.8
    }
    onOpened: {
        update_list();
        var mapname = supervisor.getMapname();
        map_list_view.setEnable(true);
        map_list_view.setViewer("map_list");
    }
    onClosed:{
        map_list_view.enabled = false;
    }
    onCur_groupChanged: {
        update_group();
    }

    function update_group(){
        model_group.clear();
        print("update group ",supervisor.getLocationGroupNum());
        for(var i=0; i<supervisor.getLocationGroupNum(); i++){
            if(supervisor.getLocationGroupSize(i) > 0){
                if(supervisor.getLocGroupname(i) === "DEFAULT" || supervisor.getLocGroupname(i) === "Default"){
                    model_group.append({"num":i,"name":"그룹"});
                }else{
                    model_group.append({"num":i,"name":supervisor.getLocGroupname(i)});
                }
            }
        }
        if(model_group.count > 0){
            table_num = supervisor.getLocationGroupSize(model_group.get(cur_group).num);
            print("table_num : " +table_num);
        }else
            table_num = 0;
        update_table();
    }
    function update_table(){
        servings.clear();
        for(var i=0; i<table_num; i++){
            servings.append({"num":i,"available":true,"name":supervisor.getServingName(model_group.get(cur_group).num, i)});
        }
    }


    function update_list(){
        model_maps.clear();
        var num = supervisor.getAvailableMap();
        for(var i=0; i<num; i++){
            model_maps.append({"name":supervisor.getAvailableMapPath(i)});
        }
        select_map_list = -1;
        map_list_view.loadmap("");
    }
    onSelect_map_listChanged: {
        if(select_map_list > -1){
            supervisor.readSetting(model_maps.get(select_map_list).name);
            model_details.clear();
            supervisor.setShowLocation(false);
            supervisor.setShowTravelline(false);
            supervisor.setShowVelocitymap(false);

            print("71");
            map_size_str = supervisor.getMapWidth().toString()+" px";
            grid_width_str = supervisor.getGridWidth().toFixed(2).toString()+" m";
            modify_date_str = supervisor.getAnnotModifiedDate();

            print("16");
            if(supervisor.isExistMap(model_maps.get(select_map_list).name)){
                radio_editmap.setEnabled(true);
                radio_editmap.setOnoff(true);
                radio_avoidmap.setOnoff(true);
                radio_objectmap.setOnoff(true);
                radio_tline.setOnoff(true);
                radio_velmap.setOnoff(true);
            }else if(supervisor.isExistRawMap(model_maps.get(select_map_list).name)){
                radio_editmap.setEnabled(false);
                radio_editmap.setOnoff(false);
                radio_rawmap.setOnoff(true);
                radio_avoidmap.setOnoff(false);
                radio_objectmap.setOnoff(false);
                radio_tline.setOnoff(false);
                radio_velmap.setOnoff(false);
            }else{
                radio_editmap.setEnabled(false);
                radio_editmap.setOnoff(false);
                radio_rawmap.setOnoff(false);
                radio_avoidmap.setOnoff(false);
                radio_objectmap.setOnoff(false);
                radio_tline.setOnoff(false);
                radio_velmap.setOnoff(false);
            }

            print("15");
            if(supervisor.isExistAvoidMap(model_maps.get(select_map_list).name)){
                radio_avoidmap.setEnabled(true);
            }else{
                radio_avoidmap.setEnabled(false);
            }
            if(supervisor.isExistObjectMap(model_maps.get(select_map_list).name)){
                radio_objectmap.setEnabled(true);
            }else{
                radio_objectmap.setEnabled(false);
            }
            if(supervisor.isExistTlineMap(model_maps.get(select_map_list).name)){
                radio_tline.setEnabled(true);
            }else{
                radio_tline.setEnabled(false);
            }
            if(supervisor.isExistVelMap(model_maps.get(select_map_list).name)){
                radio_velmap.setEnabled(true);
            }else{
                radio_velmap.setEnabled(false);
            }

            print("14");
            if(supervisor.getLocationNum("Charging") === 0){
                state_charging.enabled = false;
            }else{
                state_charging.enabled = true;
            }
            if(supervisor.getLocationNum("Resting") === 0){
                state_resting.enabled = false;
            }else{
                state_resting.enabled = true;
            }
            if(supervisor.getLocationNum("Cleaning") === 0){
                state_cleaning.enabled = false;
            }else{
                state_cleaning.enabled = true;
            }
            print("12");
            update_group();
            supervisor.setMap();
            print("13");
        }
    }

    Rectangle{
        id: parentrect
        width: 1280
        height: 800
        anchors.centerIn: parent
        color:"transparent"
        Column{
            anchors.bottom: parent.bottom
            spacing: 5
            Rectangle{
                id: rect_list_top
                height: 150
                width: parentrect.width
                color: color_dark_navy
                Column{
                    anchors.left: parent.left
                    anchors.leftMargin: 50
                    anchors.verticalCenter: parent.verticalCenter
                    spacing: 5
                    Text{
                        id: text_list_title
                        color: "white"
                        font.family: font_noto_b.name
                        font.bold: true
                        text: "확인된 맵 목록"
                        font.pixelSize: 40
                    }
                    Text{
                        id: text_list_title2
                        color: "white"
                        font.family: font_noto_r.name
                        text: "사용 가능한 맵 파일을 모두 찾았습니다"
                        font.pixelSize: 20
                    }
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
                        text: "사 용"
                        onClicked: {
                            click_sound.play();
                            if(select_map_list > -1){
                                supervisor.writelog("[USER INPUT] Map used changed : " + model_maps.get(select_map_list).name);
                                supervisor.setMap(model_maps.get(select_map_list).name);
                                loader_page.item.init();
                                popup_map_list.close();
                            }
                        }
                    }
                    Item_buttons{
                        width: 130
                        height: 60
                        type: "round_text"
//                            visible: false
                        text: "복 사"
                        onClicked: {
                            click_sound.play();
                            if(select_map_list > -1){
                                supervisor.writelog("[USER INPUT] Map used copied : " + model_maps.get(select_map_list).name);
                                popup_copymap.open();
                                popup_copymap.orin_name = model_maps.get(select_map_list).name;


//                                    supervisor.setMap(model_maps.get(select_map_list).name);
//                                    loader_page.item.init();
//                                    popup_map_list.close();
                            }
                        }
                    }
                    Item_buttons{
                        width: 130
                        height: 60
                        type: "round_text"
                        visible: false
                        text: "수 정"
                        onClicked: {
                            click_sound.play();
                            if(select_map_list > -1){
                                var name = model_maps.get(select_map_list).name;
                                popup_map_list.close();
                                loadPage(pannotation);
                                loader_page.item.setMappingFlag();
                            }
                        }
                    }
                    Item_buttons{
                        width: 130
                        height: 60
                        type: "round_text"
                        text: "삭 제"
                        onClicked: {
                            click_sound.play();
                            if(select_map_list > -1){
                                supervisor.removeMap(model_maps.get(select_map_list).name);
                                popup_map_list.update_list();
                            }
                        }
                    }
                    Item_buttons{
                        width: 140
                        height: 60
                        type: "round_text"
                        text: "취 소"
                        onClicked: {
                            click_sound.play();
                            popup_map_list.close();
                        }
                    }

                }
            }
            Row{
                anchors.horizontalCenter: parent.horizontalCenter
                Column{
                    anchors.verticalCenter: parent.verticalCenter
                    spacing: 20
                    Rectangle{
                        id: rect_ddd
                        color: "transparent"
                        width: 600
                        height: 800-150
                        Row{
                            anchors.centerIn: parent
                            spacing: 20
                            Flickable{
                                width: 200
                                clip: true
                                height: rect_ddd.height*0.8
                                anchors.verticalCenter: parent.verticalCenter
                                contentHeight: column_maps.height
                                Column{
                                    id: column_maps
                                    anchors.centerIn: parent
                                    spacing: 5
                                    Repeater{
                                        model: ListModel{id:model_maps}
                                        Rectangle{
                                            width: 200
                                            height: 50
                                            radius: 10
                                            color: select_map_list===index?color_green:"transparent"
                                            border.width: 2
                                            border.color: "white"
                                            Text{
                                                anchors.centerIn: parent
                                                font.family: font_noto_r.name
                                                font.pixelSize: 20
                                                color: "white"
                                                text: name
                                                Component.onCompleted: {
                                                    scale = 1;
                                                    while(width*scale > parent.width*0.8){
                                                        scale=scale-0.01;
                                                    }
                                                }
                                            }
                                            MouseArea{
                                                anchors.fill: parent
                                                onClicked:{
                                                    if(select_map_list === index){
                                                        select_map_list = -1;
                                                    }else{
                                                        select_map_list = index;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                            Rectangle{
                                id: rect_df
                                width: 350
                                height: rect_ddd.height
                                visible: select_map_list > -1
                                color: "transparent"
                                Column{
                                    anchors.centerIn: parent
                                    spacing: 10
                                    Rectangle{
                                        id: area_map_view
                                        color: "green"
                                        width: rect_df.width
                                        height: 180
                                        Grid{
                                            anchors.centerIn: parent
                                            spacing: 20
                                            columns: 2
                                            rows: 3
                                            Row{
                                                spacing: 3
                                                Text{
                                                    text: "맵원본"
                                                    font.family: font_noto_r.name
                                                    color:"white"
                                                    width: 60
                                                }
                                                Item_radioButton{
                                                    id: radio_rawmap
                                                    touchEnabled: true
                                                    enabled: false
                                                    isVertical: false
                                                    small: 30
                                                    big: 80
                                                    onTurnon: {
                                                        print("raw turn on")
                                                        radio_editmap.setOnoff(false);
                                                        radio_objectmap.setOnoff(false);
                                                        radio_avoidmap.setOnoff(false);
                                                        radio_velmap.setOnoff(false);
                                                        radio_tline.setOnoff(false);
                                                        supervisor.setShowLocation(false);
                                                        print("?")
                                                        supervisor.setMapOrin("RAW");
                                                        print("!")
                                                    }
                                                }
                                            }
                                            Row{
                                                spacing: 3
                                                Text{
                                                    text: "맵수정본"
                                                    width: 60
                                                    font.family: font_noto_r.name
                                                    color:"white"
                                                }
                                                Item_radioButton{
                                                    id: radio_editmap
                                                    touchEnabled: true
                                                    isVertical: false
                                                    small: 30
                                                    big: 80
                                                    onTurnon: {
                                                        print("edit turn on")
                                                        radio_rawmap.setOnoff(false);
                                                        print("???")
                                                        radio_objectmap.setOnoff(true);
                                                        print("???")
                                                        radio_avoidmap.setOnoff(true);
                                                        print("???")
                                                        radio_velmap.setOnoff(true);
                                                        print("???")
                                                        radio_tline.setOnoff(true);
                                                        print("???")
                                                        supervisor.setShowLocation(true);
                                                        print("???")
                                                        supervisor.setMapOrin("EDITED");
                                                        print("!!!")
                                                    }
                                                }
                                            }
                                            Row{
                                                spacing: 3
                                                Text{
                                                    text: "이동경로"
                                                    width: 60
                                                    font.family: font_noto_r.name
                                                    color:"white"
                                                }
                                                Item_radioButton{
                                                    id: radio_tline
                                                    touchEnabled: true
                                                    isVertical: false
                                                    small: 30
                                                    big: 80
                                                    onTurnon: {
                                                        supervisor.setShowTravelline(true);
                                                        supervisor.setMap();
                                                    }
                                                    onTurnoff: {
                                                        supervisor.setShowTravelline(false);
                                                        supervisor.setMap();
                                                    }
                                                }
                                            }
                                            Row{
                                                spacing: 3
                                                Text{
                                                    text: "안전속도"
                                                    width: 60
                                                    font.family: font_noto_r.name
                                                    color:"white"
                                                }
                                                Item_radioButton{
                                                    id: radio_velmap
                                                    touchEnabled: true
                                                    isVertical: false
                                                    small: 30
                                                    big: 80
                                                    onTurnon: {
                                                        supervisor.setShowVelocitymap(true);
                                                        supervisor.setMap();
                                                    }
                                                    onTurnoff: {
                                                        supervisor.setShowVelocitymap(false);
                                                        supervisor.setMap();
                                                    }
                                                }
                                            }
                                            Row{
                                                spacing: 3
                                                Text{
                                                    text: "가상벽"
                                                    width: 60
                                                    font.family: font_noto_r.name
                                                    color:"white"
                                                }
                                                Item_radioButton{
                                                    id: radio_objectmap
                                                    touchEnabled: true
                                                    isVertical: false
                                                    small: 30
                                                    big: 80
                                                    onTurnon: {
                                                        supervisor.setShowObject(true);
                                                        supervisor.setMap();
                                                    }
                                                    onTurnoff: {
                                                        supervisor.setShowObject(false);
                                                        supervisor.setMap();
                                                    }
                                                }
                                            }
                                            Row{
                                                spacing: 3
                                                Text{
                                                    text: "회피구역"
                                                    width: 60
                                                    font.family: font_noto_r.name
                                                    color:"white"
                                                }
                                                Item_radioButton{
                                                    id: radio_avoidmap
                                                    touchEnabled: true
                                                    isVertical: false
                                                    small: 30
                                                    big: 80
                                                    onTurnon: {
                                                        supervisor.setShowAvoidmap(true);
                                                        supervisor.setMap();
                                                    }
                                                    onTurnoff: {
                                                        supervisor.setShowAvoidmap(false);
                                                        supervisor.setMap();
                                                    }
                                                }
                                            }
                                        }
                                    }
                                    Column{
                                        anchors.horizontalCenter: parent.horizontalCenter
                                        spacing: 3
                                        Rectangle{
                                            id: area_loc_1
                                            color: "transparent"
                                            width: rect_df.width
                                            height: 70
                                            radius: 10
                                            Rectangle{
                                                radius: 10
                                                anchors.fill: parent
                                                color: color_dark_black
                                                opacity: 0.7
                                            }
                                            Row{
                                                anchors.centerIn: parent
                                                spacing: 30
                                                Rectangle{
                                                    id: state_charging
                                                    width:55
                                                    height: width
                                                    radius: width
                                                    color: enabled?color_green:color_gray
                                                    Text{
                                                        anchors.centerIn: parent
                                                        text: qsTr("충전\n위치")
                                                        font.family: font_noto_r.name
                                                        color: color_dark_black
                                                    }
                                                }
                                                Rectangle{
                                                    id: state_resting
                                                    width:55
                                                    height: width
                                                    radius: width
                                                    color: enabled?color_green:color_gray
                                                    Text{
                                                        anchors.centerIn: parent
                                                        text: qsTr("대기\n위치")
                                                        font.family: font_noto_r.name
                                                        color: color_dark_black
                                                    }
                                                }
                                                Rectangle{
                                                    id: state_cleaning
                                                    width:55
                                                    height: width
                                                    radius: width
                                                    color: enabled?color_green:color_gray
                                                    Text{
                                                        anchors.centerIn: parent
                                                        text: qsTr("퇴식\n위치")
                                                        font.family: font_noto_r.name
                                                        color: color_dark_black
                                                    }
                                                }
                                            }
                                        }

                                        Rectangle{
                                            id: area_group
                                            color: "transparent"
                                            width: rect_df.width
                                            height: 60

                                            Flickable{
                                                id: flick_group
                                                width: parent.width
                                                height: parent.height
                                                clip: true
                                                contentWidth: row_group.width
                                                Row{
                                                    id: row_group
                                                    anchors.centerIn: parent
                                                    spacing: 10
                                                    Repeater{
                                                        id: column_table
                                                        model: ListModel{id:model_group}
                                                        Rectangle{
                                                            width: 100
                                                            height: 60
                                                            color: "transparent"
                                                            Text{
                                                                id: textt3
                                                                anchors.centerIn: parent
                                                                font.family: font_noto_b.name
                                                                font.pixelSize: 20
                                                                text: name
                                                                color: cur_group==index?color_green:color_dark_gray
                                                            }
                                                            Rectangle{
                                                                anchors.bottom: parent.bottom
                                                                width: parent.width*0.9
                                                                anchors.horizontalCenter: parent.horizontalCenter
                                                                radius: 2
                                                                height: 3
                                                                color: cur_group==index?color_green:"transparent"
                                                            }
                                                            MouseArea{
                                                                anchors.fill: parent
                                                                onClicked:{
                                                                    click_sound.play();
                                                                    cur_group = index;
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                        Rectangle{
                                            id: area_loclist
                                            color: "transparent"
                                            width: rect_df.width
                                            height: 220
                                            Flickable{
                                                anchors.horizontalCenter: parent.horizontalCenter
                                                anchors.fill: parent
                                                clip: true
                                                Column{
                                                    id: cols_locations
                                                    anchors.horizontalCenter: parent.horizontalCenter
                                                    spacing: 1
                                                    Repeater{
                                                        model:ListModel{id:servings}
                                                        Rectangle{
                                                            anchors.horizontalCenter: parent.horizontalCenter
                                                            width: 320
                                                            radius: 10
                                                            height: 40
                                                            Row{
                                                                anchors.centerIn: parent
                                                                Rectangle{
                                                                    width: 40
                                                                    anchors.verticalCenter: parent.verticalCenter
                                                                    height: 40
                                                                    radius: 10
                                                                    color: color_dark_black
                                                                    Text{
                                                                        anchors.centerIn: parent
                                                                        font.family: font_noto_r.name
                                                                        text: index
                                                                        color: "white"
                                                                    }
                                                                }
                                                                Rectangle{
                                                                    width: 280
                                                                    height: 40
                                                                    color: "transparent"
                                                                    Text{
                                                                        anchors.centerIn: parent
                                                                        font.family: font_noto_r.name
                                                                        text: name
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
                                        id: area_map_detail
                                        color: "transparent"
                                        width: rect_df.width
                                        height: 100
                                        Grid{
                                            anchors.horizontalCenter: parent.horizontalCenter
                                            columns: 3
                                            rows: 3
                                            spacing: 5
                                            horizontalItemAlignment: Grid.AlignHCenter
                                            verticalItemAlignment: Grid.AlignVCenter
                                            Text{
                                                font.family: font_noto_b.name
                                                text: qsTr("맵 사이즈")
                                                color: "white"
                                            }
                                            Text{
                                                font.family: font_noto_b.name
                                                text: ":"
                                                color: "white"
                                            }
                                            Text{
                                                font.family: font_noto_b.name
                                                text: map_size_str
                                                color: "white"
                                            }
                                            Text{
                                                font.family: font_noto_b.name
                                                text: qsTr("픽셀 단위")
                                                color: "white"
                                            }
                                            Text{
                                                font.family: font_noto_b.name
                                                text: ":"
                                                color: "white"
                                            }
                                            Text{
                                                font.family: font_noto_b.name
                                                text: grid_width_str
                                                color: "white"
                                            }
                                            Text{
                                                font.family: font_noto_b.name
                                                text: qsTr("수정날짜")
                                                color: "white"
                                            }
                                            Text{
                                                font.family: font_noto_b.name
                                                text: ":"
                                                color: "white"
                                            }
                                            Text{
                                                font.family: font_noto_b.name
                                                text: modify_date_str
                                                color: "white"
                                            }
                                        }
                                    }
                                }

                                Column{
                                    visible: false
                                    anchors.centerIn: parent
                                    spacing: 10
                                    Repeater{
                                        model: ListModel{
                                            id: model_details
                                        }
                                        Rectangle{
                                            width: 260
                                            height: 40
                                            color: "transparent"
                                            Row{
                                                Rectangle{
                                                    width: 80
                                                    height: 40
                                                    color: "transparent"
                                                    Text{
                                                        anchors.centerIn: parent
                                                        font.family: font_noto_r.name
                                                        font.pixelSize: 20
                                                        color: "white"
                                                        text: name1
                                                    }
                                                }
                                                Text{
                                                    anchors.verticalCenter: parent.verticalCenter
                                                    font.family: font_noto_r.name
                                                    font.pixelSize: 20
                                                    color: "white"
                                                    text: ":"
                                                }
                                                Rectangle{
                                                    width: 120
                                                    height: 40
                                                    color: "transparent"
                                                    Text{
                                                        anchors.centerIn: parent
                                                        font.family: font_noto_r.name
                                                        font.pixelSize: 20
                                                        color: "white"
                                                        text: name2
                                                    }

                                                }
                                                Rectangle{
                                                    width: 60
                                                    height: 40
                                                    radius: 5
                                                    color: "black"
                                                    visible: show
                                                    Text{
                                                        anchors.centerIn: parent
                                                        font.family: font_noto_r.name
                                                        font.pixelSize: 20
                                                        color: "white"
                                                        text: "보기"
                                                    }
                                                    MouseArea{
                                                        anchors.fill: parent
                                                        onClicked:{
                                                            if(index == 2){
                                                                if(show_location){
                                                                    parent.color = "black";
                                                                    show_location = false;
                                                                    map_list_view.showLocation(false);
                                                                }else{
                                                                    parent.color = color_green;
                                                                    show_location = true;
                                                                    map_list_view.showLocation(true);
                                                                }
                                                            }else if(index == 5){
                                                                if(show_travelline){
                                                                    parent.color = "black";
                                                                    show_travelline = false;
                                                                    map_list_view.showTravelline(false);
                                                                }else{
                                                                    parent.color = color_green;
                                                                    show_travelline = true;
                                                                    map_list_view.showTravelline(true);
                                                                }
                                                            }else if(index == 6){
                                                                if(show_velocitymap){
                                                                    parent.color = "black";
                                                                    show_velocitymap = false;
                                                                    map_list_view.showVelocityMap(false);
                                                                }else{
                                                                    parent.color = color_green;
                                                                    show_velocitymap = true;
                                                                    map_list_view.showVelocityMap(true);
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
                }
                MAP_FULL2{
                    id: map_list_view
                    enabled: false
                    objectName: "POPUP"
                    width: height
                    height: 800-150
                    show_connection: false
                    Component.onCompleted: {
                        setfullscreen();
                        setViewer("annot_view")
                    }
                }
            }
        }
    }
    Popup{
        id: popup_copymap
        anchors.centerIn: parent
        width: 500
        height: 300
        background:Rectangle{
            anchors.fill: parent
            color: "transparent"
        }
        property string orin_name : ""
        Rectangle{
            width: parent.width
            height: parent.height
            radius: 20
            Column{
                anchors.centerIn: parent
                spacing: 20
                Text{
                    anchors.horizontalCenter: parent.horizontalCenter
                    text:qsTr("새로운 맵의 이름을 입력해주세요")
                    font.family: font_noto_r.name
                    font.pixelSize: 25
                }
                TextField{
                    anchors.horizontalCenter: parent.horizontalCenter
                    id: textfield_new_map
                    width: 250
                    height: 40
                    horizontalAlignment: TextField.AlignHCenter
                    text: popup_copymap.orin_name
                    MouseArea{
                        anchors.fill:parent
                        onClicked: {
                            keyboard.owner = textfield_new_map;
                            keyboard.owner_text = "textfield_new_map";
                            textfield_new_map.selectAll();

                            if(!keyboard.opened){
                                keyboard.open();
                            }
                        }
                    }
                }
                Row{
                    anchors.horizontalCenter: parent.horizontalCenter
                    spacing: 30
                    Item_buttons{
                        type: "round_text"
                        width: 160
                        height: 40
                        text:"취소"
                        onClicked:{
                            popup_copymap.close();
                        }
                    }
                    Item_buttons{
                        type: "round_text"
                        width: 160
                        height: 40
                        text:"확인"
                        onClicked:{
                            if(textfield_new_map.text != ""){
                                if(supervisor.copyMap(popup_copymap.orin_name, textfield_new_map.text) === 0){
                                    update_list();
                                }else{

                                }
                                popup_copymap.close();
                            }
                        }
                    }
                }
            }
        }
    }

    Popup{
        id: popup_annotation_delete
        width: parent.width
        height: parent.height
        background:Rectangle{
            anchors.fill: parent
            color: "#282828"
            opacity: 0.7
        }
        property string name: ""
        Rectangle{
            anchors.centerIn: parent
            width: 400
            height: 250
            color: "white"
            radius: 10

            Column{
                anchors.centerIn: parent
                spacing: 40
                Column{
                    anchors.horizontalCenter: parent.horizontalCenter
                    Text{
                        text: "기존 맵 설정이 삭제됩니다"
                        font.family: font_noto_r.name
                        font.pixelSize: 20
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                }
                Row{
                    anchors.horizontalCenter: parent.horizontalCenter
                    spacing: 20
                    Rectangle{
                        id: btn_prev_00
                        width: 180
                        height: 60
                        radius: 10
                        color:"transparent"
                        border.width: 1
                        border.color: "#7e7e7e"
                        Text{
                            anchors.centerIn: parent
                            text: "취소"
                            font.family: font_noto_r.name
                            font.pixelSize: 25

                        }
                        MouseArea{
                            anchors.fill: parent
                            onClicked:{
                                click_sound.play();
                                popup_annotation_delete.close();
                            }
                        }
                    }
                    Rectangle{
                        id: btn_next_00
                        width: 180
                        height: 60
                        radius: 10
                        color: "#12d27c"
                        border.width: 1
                        border.color: "#12d27c"
                        Text{
                            anchors.centerIn: parent
                            text: "확인"
                            font.family: font_noto_r.name
                            font.pixelSize: 25
                            color: "white"
                        }
                        MouseArea{
                            anchors.fill: parent
                            onClicked:{
                                click_sound.play();
                                supervisor.deleteAnnotation();
                                supervisor.setMap(name);
                                loadPage(pmap);
                                loader_page.item.loadmap(popup_annotation_delete.name,"RAW");
                                loader_page.item.is_init_state = true;
                                loader_page.item.map_mode = 2;
                                popup_annotation_delete.close();
                                popup_map_list.close();
                            }
                        }
                    }
                }
            }
        }
        Popup_help{
            id: popup_maplist_help
        }
    }
}


