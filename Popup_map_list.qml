import QtQuick 2.12
import QtQuick.Controls 2.12
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
    property bool show_location: false
    property bool show_travelline: false
    property bool show_velocitymap: false
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
            show_velocitymap = false;
            supervisor.setShowLocation(false);
            supervisor.setShowTravelline(false);
            supervisor.setShowVelocitymap(false);
            show_location = false;
            show_travelline = false;

            model_details.append({"name1":"맵 사이즈","name2":supervisor.getMapWidth().toString()+" px","show":false});
            model_details.append({"name1":"픽셀 단위","name2":supervisor.getGridWidth().toFixed(2).toString()+" m","show":false});
            model_details.append({"name1":"서빙 위치","name2":supervisor.getLocationNum("Serving").toString(),"show":true});
            model_details.append({"name1":"대기 위치","name2":supervisor.getLocationNum("Resting").toString(),"show":false});
            model_details.append({"name1":"충전 위치","name2":supervisor.getLocationNum("Charging").toString(),"show":false});
            model_details.append({"name1":"이동 경로","name2":"","show":true});
            model_details.append({"name1":"안전 속도","name2":"","show":true});
        }
    }

    Rectangle{
        id: parentrect
        width: 1280
        height: 800
        anchors.centerIn: parent
        color:"transparent"
        Column{
            anchors.centerIn: parent
            spacing: 5
            Rectangle{
                id: rect_list_top
                height: 120
                width: parentrect.width
                color: color_dark_navy
                Column{
                    anchors.centerIn: parent
                    spacing: 5
                    Text{
                        id: text_list_title
                        anchors.horizontalCenter: parent.horizontalCenter
                        color: "white"
                        font.family: font_noto_b.name
                        font.bold: true
                        text: "확인된 맵 목록"
                        font.pixelSize: 40
                    }
                    Text{
                        id: text_list_title2
                        anchors.horizontalCenter: parent.horizontalCenter
                        color: "white"
                        font.family: font_noto_r.name
                        text: "사용 가능한 맵 파일을 모두 찾았습니다"
                        font.pixelSize: 20
                    }
                }
                Item_buttons{
                    width: 60
                    height: 60
                    type: "circle_text"
                    anchors.right: parent.right
                    anchors.rightMargin: 200
                    anchors.verticalCenter: parent.verticalCenter
                    text: "?"
                    onClicked: {
                        click_sound.play();
                        popup_maplist_help.setTitle("맵 불러오기");
                        popup_maplist_help.open();
                        popup_maplist_help.addLine("맵 불러오기란 무엇인가요?","현재 저장된 모든 맵 파일을 불러올 수 있습니다\n맵은 맵 이미지, 위치정보, 이동경로 맵으로 구성됩니다\n기존에 저장했던 맵 설정 정보를 불러오고 싶다면 맵 이름을 클릭한 뒤 사용 버튼을 누르세요");
                        popup_maplist_help.addLine("잘못 불러오기를 했을 시 어떻게 하나요?","다시 이 페이지로 돌아와서 맵을 새로 불러오기하면 됩니다");
                        popup_maplist_help.addLine("잘못해서 기존 맵을 삭제해버렸어요.","삭제된 맵 파일을 복구하는 방법은 없습니다.\n부디 삭제를 하실 때에는 신중하게 고려해주세요");
                        popup_maplist_help.addLine("사용과 수정의 차이는 뭔가요?","맵 설정정보를 기존 그대로 사용하려면 [사용]을 누르세요\n추후 맵 수정하기 페이지에서 변경하실 수도 있습니다\n맵 설정정보가 없다면 [수정]버튼이 활성화 됩니다 맵 이미지 파일만 사용하고 맵은 처음부터 수정하셔야 합니다");
                    }
                }
                Item_buttons{
                    width: 140
                    height: 60
                    type: "round_text"
                    anchors.rightMargin: 30
                    anchors.right: parent.right
                    anchors.verticalCenter: parent.verticalCenter
                    text: "취 소"
                    onClicked: {
                        click_sound.play();
                        popup_map_list.close();
                    }
                }
            }
            Row{
                anchors.horizontalCenter: parent.horizontalCenter
                Column{
                    spacing: 20
                    Rectangle{
                        color: "transparent"
                        width: 500
                        height: 500
                        Row{
                            anchors.centerIn: parent
                            Flickable{
                                width: 200
                                clip: true
                                height: 500
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
                                width: 300
                                height: 500
                                visible: select_map_list > -1
                                color: "transparent"
                                Column{
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


                    Row{
                        anchors.horizontalCenter: parent.horizontalCenter
                        spacing: 30
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
                            text: "복사본만들기"
                            onClicked: {
                                click_sound.play();
                                if(select_map_list > -1){
                                    supervisor.writelog("[USER INPUT] Map used copied : " + model_maps.get(select_map_list).name);
                                    popup_copymap.open();


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
                                    print(name);
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
                    }
                }
                MAP_FULL2{
                    id: map_list_view
                    enabled: false
                    objectName: "POPUP"
                    width: 600
                    height: 600
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
                    id: textfield_new_map
                    width: 200
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
                        width: 160
                        height: 40
                        text:"취소"
                        onClicked:{
                            popup_copymap.close();
                        }
                    }
                    Item_buttons{
                        width: 160
                        height: 40
                        text:"확인"
                        onClicked:{
                            if(textfield_new_map.text != ""){
                                supervisor.copyMap(orin_name, textfield_new_map.text);
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


