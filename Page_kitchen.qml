import QtQuick 2.12
import QtQuick.Controls 2.12
import "."
import QtGraphicalEffects 1.0
import io.qt.Supervisor 1.0
import QtMultimedia 5.12

Item {
    id: page_kitchen
    objectName: "page_kitchen"
    width: 1280
    height: 800

    function init(){
        print("kitchen init");
        statusbar.visible = true;

        cur_table = -1;
        cur_group = 0;
        cur_page = 0;
        cur_preset = parseInt(supervisor.getSetting("update","DRIVING","cur_preset"));

        group_num = supervisor.getLocationGroupNum();
        robot_type = supervisor.getSetting("setting","ROBOT_TYPE","type");
        table_num = 0;

        tray_num = parseInt(supervisor.getSetting("setting","ROBOT_TYPE","tray_num"));

        if(robot_type === "CALLING"){
            show_serving = false;
        }else{
            show_serving = true;
        }
        table_view = "table_name";
        if(supervisor.getSetting("setting","USE_UI","use_tray")==="true"){
            use_tray=true;
        }else{
            use_tray=false;
        }

        if(use_tray){
            col_num = 1;
            row_num = 5;
        }else{
            col_num = parseInt(supervisor.getSetting("setting","UI","group_col_num"));
            row_num = parseInt(supervisor.getSetting("setting","UI","group_row_num"));
        }

        if(table_view === "table_name"){
            max_col = 5
            max_row = 4
        }else{
            max_col = 8
            max_row = 4
        }

        traymodel.clear();
        for(var i=0; i<tray_num; i++){
            traymodel.append({tray_num:i+1,setting:false,group:-1,table:-1});
        }

        update_group();
        if(supervisor.getSetting("setting","USE_UI","use_calling_notice") === "true"){
            if(supervisor.isCallingMode() || supervisor.getCallQueueSize() > 0){
                popup_clean_calling.cleaninglocation = false;
                popup_clean_calling.open();
            }
        }
        supervisor.setMotorLock(true);
    }


    function openNotice(errstr){
        popup_notice.init();
        popup_notice.style = "warning";
        if(errstr === "no_path"){
            popup_notice.main_str = qsTr("경로를 찾지 못했습니다");
            popup_notice.sub_str = "";
            popup_notice.open();
        }else if(errstr === "no_location"){
            popup_notice.main_str = qsTr("목적지가 지정되지 않았습니다");
            popup_notice.sub_str = "";
            popup_notice.open();
        }else if(errstr === "localization"){
            popup_notice.main_str = qsTr("로봇의 위치를 찾을 수 없습니다");
            popup_notice.sub_str = qsTr("로봇초기화를 다시 해주세요");
            popup_notice.addButton(qsTr("위치초기화"));
            popup_notice.open();
        }else if(errstr === "emo"){
            popup_notice.main_str = qsTr("비상스위치가 눌려있습니다");
            popup_notice.sub_str = qsTr("비상스위치를 풀어주세요");
            popup_notice.open();
        }else if(errstr === 3){
            popup_notice.main_str = qsTr("경로가 취소되었습니다");
            popup_notice.sub_str = "";
            popup_notice.open();
        }else if(errstr === "motor_lock"){
            popup_notice.style = "warning";
            popup_notice.main_str = qsTr("로봇이 수동모드입니다");
            popup_notice.sub_str = "";

            popup_notice.addButton(qsTr("모터초기화"))
            popup_notice.open();
        }else if(errstr === 5){
            popup_notice.main_str = qsTr("모터와 연결되지 않았습니다");
            popup_notice.sub_str = "";
            popup_notice.open();
        }else if(errstr === 6){
            popup_notice.main_str = qsTr("출발할 수 없는 상태입니다");
            popup_notice.sub_str = qsTr("로봇을 다시 초기화해주세요");
            popup_notice.open();
        }else if(errstr === "no_location"){
            popup_notice.style = "warning";
            popup_notice.main_str = qsTr("목적지를 찾을 수 없습니다");
            popup_notice.sub_str = qsTr("");
            popup_notice.open();
        }else if(errstr === "no_patrol"){
            popup_notice.style = "warning";
            popup_notice.main_str = qsTr("없는 지정순회 파일입니다");
            popup_notice.sub_str = qsTr("");
            popup_notice.open();
        }else if(errstr === "motor_notready"){
            popup_notice.style = "warning";
            popup_notice.main_str = qsTr("모터초기화가 필요합니다");
            popup_notice.sub_str = qsTr("비상전원스위치를 눌렀다가 풀어주세요");

            popup_notice.addButton(qsTr("모터초기화"))
            popup_notice.open();
        }else if(errstr === "debug"){
            popup_notice.style = "warning";
            popup_notice.main_str = qsTr("디버그 모드입니다")
            popup_notice.sub_str = qsTr("디버그모드에서는 주행할 수 없습니다")

            popup_notice.open();
        }else if(errstr === "charging"){
            popup_notice.style = "warning";
            popup_notice.main_str = qsTr("충전 케이블이 연결되어 있습니다")
            popup_notice.sub_str = qsTr("충전케이블이 연결된 상태로 주행할 수 없습니다")

            popup_notice.open();
        }else if(errstr === "running"){
            popup_notice.style = "warning";
            popup_notice.main_str = qsTr("로봇이 현재 대기상태가 아닙니다")
            popup_notice.sub_str = qsTr("현재 상태 : ")+supervisor.getStateMovingStr();

            popup_notice.open();
        }else if(errstr === "ipc_discon"){
            popup_notice.style = "error";
            popup_notice.main_str = qsTr("SLAMNAV와 연결할 수 없습니다")
            popup_notice.sub_str = "";

            popup_notice.open();
        }else if(errstr === "motor"){
            popup_notice.style = "error";
            popup_notice.main_str = qsTr("모터가 현재 대기상태가 아닙니다")
            popup_notice.sub_str = qsTr("현재 상태 : ")+supervisor.getMotorStatusStr(0)+","+supervisor.getMotorStatusStr(1);

            popup_notice.open();
        }
    }

    function cleaning(){
            popup_clean_calling.cleaninglocation = true;
            popup_clean_calling.open();
    }

    property string table_view: "table_name"
    property int tray_num: 2
    property int table_num: 5
    property int group_num: 1
    property int row_num: 5
    property int col_num: 1

    property int max_row: 5
    property int max_col: 5

    property bool show_serving: true

    property bool use_tray: false

    property int tray_width: 400
    property int tray_height: 80
    property int spacing_tray : 10
    property int rect_size: 70
    property int traybox_margin: 150

    property int cur_table: -1
    property int cur_group: 0
    property int cur_page: 0

    property string move_loc: "None"

    property int cur_preset: 3

    onCur_groupChanged: {
        cur_table = -1;
        update_table();
    }

    Rectangle{
        anchors.fill : parent
        color: "#f4f4f4"
    }

    ListModel{
        id: traymodel
        ListElement{
            tray_num: 1
            table: -1
            group: -1
            setting: false
        }
    }

    ListModel{
        id: patrolmodel
    }

    Timer{
        id: timer_update
        interval : 500
        triggeredOnStart: true
        running: true
        repeat: true
        onTriggered: {
            if(supervisor.isDebugMode()){
                menubar.menu2_en = false;
                menubar.menu3_en = false;
                menubar.menu4_en = false;
                btn_patrol.active = false;
                btn_go.active = false;
                rect_go.color = color_red;
                text_go.color = color_dark_gray;
                text_go.text = qsTr("디버그 모드")
                text_go.font.pixelSize = 25
            }else if(supervisor.getIPCConnection()){
                if(supervisor.getPowerStatus()){
                    if(supervisor.getEmoStatus()){
                        menubar.menu2_en = false;
                        menubar.menu3_en = false;
                        menubar.menu4_en = false;
                        btn_patrol.active = false;
                        btn_go.active = false;
                        rect_go.color = color_red;
                        text_go.color = color_dark_gray;
                        text_go.text = qsTr("비상스위치가 눌려있음")
                        text_go.font.pixelSize = 25
                    }else if(supervisor.getMotorState() === 0){
                        btn_go.active = false;
                        menubar.menu2_en = false;
                        btn_patrol.active = false;
                        menubar.menu3_en = false;
                        menubar.menu4_en = false;
                        rect_go.color = color_red;
                        text_go.color = color_dark_gray;
                        text_go.text = qsTr("모터락해제됨")
                        text_go.font.pixelSize = 25
                    }else if(supervisor.getLocalizationState() === 2){
                        if(supervisor.getSetting("setting","ROBOT_TYPE","type") === "CLEANING"){
                            btn_go.active = true;
                            menubar.menu2_en = true;
                            menubar.menu3_en = true;
                            menubar.menu4_en = true;
                            rect_go.color = color_green;
                            btn_patrol.active = true;
                            text_go.color = "white";
                            text_go.text = qsTr("퇴식 테이블로")
                            text_go.font.pixelSize = 35
                        }

                        else{
                            btn_go.active = true;
                            menubar.menu2_en = true;
                            menubar.menu3_en = true;
                            menubar.menu4_en = true;
                            rect_go.color = color_blue;
                            btn_patrol.active = true;
                            text_go.color = "white";
                            text_go.text = qsTr("서빙 시작")
                            text_go.font.pixelSize = 35
                        }
                    }else{
                        btn_go.active = false;
                        menubar.menu2_en = false;
                        menubar.menu3_en = false;
                        menubar.menu4_en = false;
                        btn_patrol.active = false;
                        rect_go.color = color_red;
                        text_go.color = color_dark_gray;
                        text_go.text = qsTr("위치 초기화필요")
                        text_go.font.pixelSize = 30
                    }
                }else{
                    btn_go.active = false;
                    menubar.menu2_en = false;
                    menubar.menu3_en = false;
                    menubar.menu4_en = false;
                    btn_patrol.active = false;
                    rect_go.color = color_gray;
                    text_go.color = color_dark_gray;
                    text_go.text = qsTr("모터 전원 안켜짐")
                    text_go.font.pixelSize = 35
                }
            }else{
                btn_go.active = false;
                menubar.menu2_en = false;
                menubar.menu3_en = false;
                menubar.menu4_en = false;
                btn_patrol.active = false;
                rect_go.color = color_gray;
                text_go.color = color_dark_gray;
                text_go.text = qsTr("로봇 연결 안됨")
                text_go.font.pixelSize = 35
            }
        }
    }

    function update_group(){
        model_group.clear();
        var groupnum = -1;
        for(var i=0; i<supervisor.getLocationGroupNum(); i++){
            console.log(i,supervisor.getLocGroupname(i),groupnum);
            if(supervisor.getLocGroupname(i) === "DEFAULT" || supervisor.getLocGroupname(i) === "Default"){
                if(supervisor.getLocationGroupSize(i) > 0){
                    if(groupnum == -1){
                        groupnum = i;
                    }
                    model_group.append({"num":i,"name":qsTr("그룹"),"show":true});
                }else{
                    model_group.append({"num":i,"name":qsTr("그룹"),"show":false});
                }
            }else{
                if(supervisor.getLocationGroupSize(i) > 0){
                    if(groupnum == -1){
                        groupnum = i;
                    }
                    model_group.append({"num":i,"name":supervisor.getLocGroupname(i),"show":true});
                }else{
                    model_group.append({"num":i,"name":supervisor.getLocGroupname(i),"show":false});
                }
            }
        }

        if(groupnum == -1){
            cur_group = 0;
        }else{
            cur_group = groupnum;

        }

        if(model_group.count > 0){
            table_num = supervisor.getLocationGroupSize(model_group.get(cur_group).num);
        }else
            table_num = 0;

        update_table();
    }
    function update_table(){
        model_group_table.clear();
        for(var i=col_num*row_num*cur_page; i<col_num*row_num*(cur_page+1); i++){
            if(i>=table_num)
                break;
            model_group_table.append({"num":i,"available":true,"name":supervisor.getServingName(model_group.get(cur_group).num, i)});
        }
    }

    Image{
        id: image_head
        visible: (!show_serving || use_tray)?true:false
        anchors.horizontalCenter: show_serving?rect_tray_box.horizontalCenter:rect_calling_box.horizontalCenter
        anchors.bottom: rect_tray_box.top
        anchors.bottomMargin: 10

        width: 90*1.5
        height: 50*1.5
        sourceSize.width: width
        sourceSize.height: height
        source:"image/robot_head.png"
    }


    //=======================Serving Mode , Use Tray=============================//
    Rectangle{
        id: rect_tray_box
        visible: (show_serving && use_tray)?true:false
        width: 500
        height: tray_num*tray_height + (tray_num - 1)*spacing_tray + 50
        color: "#e8e8e8"
        radius: 30
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: rect_table_box.right
        anchors.leftMargin: (menubar.x-rect_table_box.width - width)/2

        Rectangle{
            width: 60
            height: 110
            radius: 30
            color: parent.color
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.topMargin: -50
            Image{
                anchors.horizontalCenter: parent.horizontalCenter
                width: 40
                height: 40
                source: "qrc:/icon/icon_trash_w.png"
                sourceSize.width: width
                sourceSize.height: height
                anchors.verticalCenter: parent.verticalCenter
                anchors.verticalCenterOffset: -30
                MouseArea{
                    anchors.fill: parent
                    onClicked:{
                        for(var i=0; i<traymodel.count; i++){
                            traymodel.get(i).setting = false;
                        }
                    }
                }
            }

        }
        Column{
            id: column_tray
            anchors.centerIn: parent
            spacing: 20
            Repeater{
                id: repeat_tray
                model: traymodel
                Rectangle{
                    id: rect_tray
                    width: tray_width
                    height: tray_height
                    color: "transparent"
                    radius:50
                    border.color: "#d0d0d0"
                    border.width: 1
                    onYChanged: {
                        model.y = y;
                    }

                    SequentialAnimation{
                        id: ani_tray
                        running: false
                        ParallelAnimation{
                            NumberAnimation{target:rect_tray_fill; property:"scale"; from:1;to:1.2;duration:300;}
                            NumberAnimation{target:rect_tray_fill; property:"scale"; from:1.2;to:1;duration:300;}
                        }
                    }
                    Rectangle{
                        id: rect_tray_fill
                        width: tray_width
                        height: tray_height
                        radius:50
                        color: model.setting?color_green:"white"
                        border.color: model.setting?color_green:"white"
                        border.width: 1
                        onColorChanged: {
                            if(color != "#0000ff"){
                                ani_tray.start()
                            }
                        }
                    }
                    Text{
                        id: text_cancel
                        font.family: font_noto_r.name
                        font.pixelSize: 20
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.right: parent.right
                        anchors.rightMargin: 20
                        color: "#525252"
                        visible: false
                        text:"cancel"
                    }
                    MouseArea{
                        id: tray_mousearea
                        anchors.fill: parent
                        property var firstX;
                        property int width_dis: 0
                        onPressed: {
                            supervisor.playSound('click');
                            firstX = mouseX;
                            width_dis = 0;
                        }
                        onReleased: {
                            if(width_dis > 50){
                                model.setting = false;
                                cur_table = -1;
                            }else{
                                if(cur_table != -1){
                                    model.setting = true;
                                    model.group = cur_group;
                                    model.table = cur_table;
                                }

                            }
                            rect_tray_fill.width = rect_tray.width;
                            text_cancel.visible = false;
                            width_dis = 0;
                        }
                        onPositionChanged: {
                            width_dis = firstX-mouseX;

                            if(width_dis < 0)
                                width_dis = 0;

                            if(model.setting){
                                if(width_dis > 50){
                                    text_cancel.visible = true;
                                }else{
                                    text_cancel.visible = false;
                                }
                                rect_tray_fill.width = rect_tray.width - width_dis
                            }

                        }
                    }
                    Text{
                        id: textTray
                        anchors.centerIn: parent
                        font.family: font_noto_r.name
                        font.pixelSize: (!model.setting)?25:30
                        font.bold: (!model.setting)?false:true
                        color: (!model.setting)?"#d0d0d0":"white"
                        text: (!model.setting)?"Tray "+Number(model.tray_num):supervisor.getServingName(model.group, model.table)
                    }
                }
            }
        }
    }

    Rectangle{
        id: rect_table_box
        visible: (show_serving && use_tray)?true:false
        width: 350
        height: parent.height - statusbar.height
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.topMargin: statusbar.height
        color: "#282828"
        Flickable{
            id: flick_group
            width: parent.width
            height: 100
            clip: true
            contentWidth: row_group.width
            Row{
                id: row_group
                anchors.centerIn: parent
                spacing: 20
                Repeater{
                    id: column_table
                    model: model_group
                    Rectangle{
                        width: 160
                        height: 70
                        visible: show
                        color: "transparent"
                        DropShadow{
                            anchors.fill: textt3
                            source: textt3
                            visible: cur_group===num
                            radius: 3
                            color: color_more_gray
                        }
                        Text{
                            id: textt3
                            anchors.centerIn: parent
                            font.family: font_noto_b.name
                            font.pixelSize: 30
                            text: name
                            color: cur_group===num?color_green:color_dark_gray
                        }
                        Rectangle{
                            anchors.bottom: parent.bottom
                            width: parent.width*0.9
                            anchors.horizontalCenter: parent.horizontalCenter
                            radius: 2
                            height: 3
                            color: cur_group===num?color_green:"transparent"
                        }
                        MouseArea{
                            anchors.fill: parent
                            onClicked:{
                                supervisor.playSound('click');
                                cur_group = num;
                            }
                        }
                    }
                }
            }
        }

        SwipeView{
            id: swipeview_tables
            width: parent.width
            currentIndex: 0
            clip: true
            anchors.top: flick_group.bottom
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 100
            onCurrentIndexChanged: {
                if(currentIndex > -1)
                    cur_page = currentIndex;
                update_table();
            }

            Repeater{
                id: page_table
                model: Math.ceil((table_num/(col_num*row_num)))

                Item{
                    property int cur_page: index
                    Column{
                        spacing: 20
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.verticalCenter: parent.verticalCenter
                        Repeater{
                            id: column_table_group2
                            delegate: {
                                if(table_view === "table_name"){
                                    tableNameCompo
                                }else{
                                    tableNumCompo
                                }
                            }
                            model: model_group_table
                        }
                    }
                }
            }
        }
        PageIndicator{
            id: indicator_tables1
            count: swipeview_tables.count
            currentIndex: swipeview_tables.currentIndex
            anchors.bottom: swipeview_tables.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            delegate: Rectangle{
                implicitWidth: 15
                implicitHeight: 15
                radius: width
                color: index===swipeview_tables.currentIndex?"#12d27c":"#525252"
                Behavior on color{
                    ColorAnimation {
                        duration: 200
                    }
                }
            }
        }
        Rectangle{
            id: btn_lock
            color: "transparent"
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 30
            anchors.horizontalCenter: parent.horizontalCenter
            width: 50
            radius: 50
            height: 50
            visible: table_num>row_num?true:false
            Image{
                anchors.fill: parent
                sourceSize.width: width
                sourceSize.height: height
                source: "icon/btn_lock.png"
            }
            MouseArea{
                anchors.fill: parent
                onPressAndHold: {
                    supervisor.playSound('click');
                    btn_lock.visible = false;
                    btns_table.visible = true;
                }
            }
        }
        Row{
            id: btns_table
            visible: false
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 30
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 10
            Rectangle{
                id: btn_minus
                color: "#282828"
                width: 40
                height: 40
                radius: 40
                enabled: table_num>row_num?true:false
                border.color: "#e8e8e8"
                border.width: 1
                Text{
                    anchors.centerIn: parent
                    text:"-"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.family: font_noto_b.name
                    font.pixelSize: 40
                    color: "#e8e8e8"
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        supervisor.playSound('click');
                        if(col_num > 1)
                            supervisor.setTableColNum(--col_num);
                    }
                }
            }
            Rectangle{
                id: btn_plus
                color: "#282828"
                width: 40
                height: 40
                radius: 40
                enabled: table_num>col_num*row_num?true:false
                border.color: "#e8e8e8"
                border.width: 1
                Text{
                    anchors.centerIn: parent
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    text:"+"
                    font.family: font_noto_b.name
                    font.pixelSize: 40
                    color: "#e8e8e8"
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        supervisor.playSound('click');
                        if(col_num < max_col)
                            supervisor.setTableColNum(++col_num);
                    }
                }
            }
            Rectangle{
                id: btn_confirm_tables
                color: "#282828"
                width: 40
                height: 40
                radius: 40
                border.color: "#e8e8e8"
                border.width: 1
                Image{
                    anchors.fill: parent
                    sourceSize.width: width
                    sourceSize.height: height
                    source: "icon/icon_yes.png"
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        supervisor.playSound('click');
                        btn_lock.visible = true;
                        btns_table.visible = false;
                    }
                }
            }

        }

    }



    //=======================Serving Mode , Not use Tray=============================//
    Rectangle{
        id: rect_table_group
        width: 1280
        height: 580
        anchors.top: parent.top
        anchors.topMargin: statusbar.height;
        anchors.left: parent.left
        color: color_dark_navy
        visible: show_serving && !use_tray
        ListModel{
            id: model_group
        }
        ListModel{
            id: model_group_table
        }
        Component{
            id: tableNumCompo
            Rectangle{
                id: rect_table_groups
                width:80
                height:80
                radius:80
                color: (num === cur_table)?"#12d27c":"#d0d0d0"
                Rectangle{
                    width:68
                    height:68
                    radius:68
                    color: "#f4f4f4"
                    anchors.centerIn: parent
                    Text{
                        anchors.centerIn: parent
                        text: num
                        color: "#525252"
                        font.family: font_noto_r.name
                        font.pixelSize: 25
                    }
                }
                MouseArea{
                    anchors.fill:parent
                    onClicked: {
                        supervisor.playSound('click');
                        if(cur_table === num)
                            cur_table = -1;
                        else
                            cur_table = num;
                    }
                }
            }
        }
        Component{
            id: tableNameCompo
            Rectangle{
                id: rect_table_groups
                width:153
                height:82
                radius:15
                color: (num === cur_table)?"white":color_navy
                enabled: available
                Rectangle{
                    width:153
                    height:75
                    radius:10
                    color: (num === cur_table)?color_blue:color_light_gray
                    Text{
                        anchors.centerIn: parent
                        text: name
                        color: available?num===cur_table?"white":"#525252":color_red
                        font.family: font_noto_r.name
                        font.bold: num===cur_table
                        Component.onCompleted: {
                            scale = 1;
                            while(width*scale > 115){
                                scale=scale-0.01;
                            }
                        }
                        font.pixelSize: 25
                    }
                }
                MouseArea{
                    anchors.fill:parent
                    onClicked: {
                        supervisor.playSound('click');
                        cur_table = num;
                    }
                }
            }
        }

        Rectangle{
            id: rect_group
            width: 1280 - 150 - menubar.width
            height: parent.height
            anchors.left: parent.left
            anchors.leftMargin: 50
            color: "transparent"
            Column{
                Rectangle{
                    id: rect_group_category
                    width: rect_group.width
                    height: 70
                    color: "transparent"
                    anchors.horizontalCenter: parent.horizontalCenter
                    Rectangle{
                        anchors.bottom: parent.bottom
                        width: parent.width
                        height: 3
                        radius: 3
                        color: color_dark_gray
                    }
                    Flickable{
                        height: parent.height
                        clip: true
                        width: parent.width - 185
//                        color: "transparent"
                        contentWidth: efkf.width
                        Row{
                            id: efkf
                            spacing: 5
                            Repeater{
                                model: model_group
                                Rectangle{
                                    width: 180
                                    height: 70
                                    visible: show
                                    color: "transparent"
                                    Text{
                                        id: textt
                                        anchors.centerIn: parent
                                        font.family: font_noto_b.name
                                        font.pixelSize: 30
                                        text: name
                                        horizontalAlignment: Text.AlignHCenter
                                        color: cur_group===num?color_green:color_dark_gray
                                        Component.onCompleted: {
                                            scale = 1;
                                            while(scale*width > 180){
                                                scale -=0.05;
                                            }
                                        }
                                    }
                                    Rectangle{
                                        anchors.bottom: parent.bottom
                                        width: parent.width*0.9
                                        anchors.horizontalCenter: parent.horizontalCenter
                                        radius: 2
                                        height: 3
                                        color: cur_group===num?color_green:"transparent"
                                    }
                                    MouseArea{
                                        anchors.fill: parent
                                        onClicked:{
                                            supervisor.playSound('click');
                                            print("cur group change2 : ",num)
                                            cur_group = num;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    Rectangle{
                        id: btn_patrol
                        width: 180
                        height: 70
                        color: "transparent"
                        anchors.right: parent.right
                        property bool active: true
                        Text{
                            anchors.centerIn: parent
                            font.family: font_noto_b.name
                            font.pixelSize: 30
                            text: qsTr("순회") //Patrol
                            color: color_blue
                        }
                        Rectangle{
                            anchors.bottom: parent.bottom
                            width: parent.width*0.9
                            anchors.horizontalCenter: parent.horizontalCenter
                            radius: 2
                            height: 3
                            color: color_blue
                        }
                        MouseArea{
                            anchors.fill: parent
                            onClicked:{
                                //debug
                                popup_patrol.open();
                            }
                        }
                    }
                }
                Rectangle{
                    width: rect_group.width
                    radius: 10
                    clip: true
                    anchors.horizontalCenter: parent.horizontalCenter
                    height: rect_group.height - rect_group_category.height
                    color: color_dark_navy
                    Row{
                        anchors.left: parent.left
                        anchors.leftMargin: 5
                        spacing: 15
                        Repeater{
                            model:model_group
                            Rectangle{
                                width: 140
                                height: 30
                                visible: show
                                color: color_dark_navy
                                opacity: cur_group === index?1:0
                            }
                        }
                    }
                    SwipeView{
                        id: swipeview_group
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.top: parent.top
                        width: parent.width*0.9
                        height: parent.height*0.96
                        currentIndex: 0
                        clip: true
                        onCurrentIndexChanged: {
                            if(currentIndex > -1)
                                cur_page = currentIndex;
                            update_table();
                        }
                        Repeater{
                            id: page_group
                            model: Math.ceil((table_num/(col_num*row_num)))
                            Item{
                                Grid{
                                    rows: row_num
                                    columns: col_num//table_num-(col_num*row_num*(cur_page+1))>0?col_num:((table_num-(col_num*row_num*cur_page))/row_num + 1).toFixed(0)
                                    spacing: 20
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    anchors.verticalCenter: parent.verticalCenter
                                    Repeater{
                                        id: column_table_group
                                        delegate: {
                                            if(table_view === "table_name"){
                                                tableNameCompo
                                            }else{
                                                tableNumCompo
                                            }
                                        }
                                        model: model_group_table
                                    }

                                }
                            }
                        }
                    }
                    PageIndicator{
                        id: indicator_tables_group
                        count: swipeview_group.count
                        currentIndex: swipeview_group.currentIndex
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: 20
                        anchors.horizontalCenter: parent.horizontalCenter
                        delegate: Rectangle{
                            implicitWidth: 15
                            implicitHeight: 15
                            radius: width
                            color: index===swipeview_group.currentIndex?"#12d27c":"#525252"
                            Behavior on color{
                                ColorAnimation {
                                    duration: 200
                                }
                            }
                        }
                    }
                    Rectangle{
                        id: btn_lock_group
                        color: "transparent"
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: 20
                        anchors.right: parent.right
                        width: 50
                        radius: 50
                        height: 50
                        visible: true;//group_num>row_num?true:false
                        Image{
                            anchors.fill: parent
                            sourceSize.width: width
                            sourceSize.height: height
                            source: "icon/btn_lock.png"
                        }
                        MouseArea{
                            anchors.fill: parent
                            onPressAndHold: {
                                supervisor.playSound('click');
                                btn_lock_group.visible = false;
                                btns_table_group.visible = true;
                            }
                        }
                    }
                    Row{
                        id: btns_table_group
                        visible: false
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: 10
                        anchors.right: parent.right
                        spacing: 10
                        Grid{
                            rows: 2
                            columns: 4
                            horizontalItemAlignment: Grid.AlignHCenter
                            verticalItemAlignment: Grid.AlignVCenter
                            spacing: 5
                            Text{
                                font.family: font_noto_r.name
                                font.pixelSize: 15
                                color: "white"
                                text: qsTr("가로줄개수")
                            }
                            Text{
                                font.family: font_noto_r.name
                                font.pixelSize: 15
                                color: "white"
                                text: ":"
                            }
                            Rectangle{
                                width: 30
                                height: 30
                                radius: 30
                                enabled: row_num > 1
                                color: enabled?color_dark_black:color_dark_gray
                                border.color: "#e8e8e8"
                                border.width: 1

                                Rectangle{
                                    width: 14
                                    radius: 2
                                    height: 2
                                    anchors.centerIn: parent
                                    color: color_mid_gray
                                }
                                MouseArea{
                                    anchors.fill: parent
                                    onClicked: {
                                        supervisor.playSound('click');
                                        supervisor.setSetting("setting","UI/group_row_num",row_num-1);
                                        row_num--;
                                        update_table();
                                    }
                                }
                            }
                            Rectangle{
                                width: 30
                                height: 30
                                radius: 30
                                enabled: row_num < max_row
                                color: enabled?color_dark_black:color_dark_gray
                                border.color: "#e8e8e8"
                                border.width: 1
                                Rectangle{
                                    width: 2
                                    radius: 2
                                    height: 14
                                    anchors.centerIn: parent
                                    color: color_mid_gray
                                }
                                Rectangle{
                                    width: 14
                                    radius: 2
                                    height: 2
                                    anchors.centerIn: parent
                                    color: color_mid_gray
                                }
                                MouseArea{
                                    anchors.fill: parent
                                    onClicked: {
                                        supervisor.playSound('click');
                                        supervisor.setSetting("setting","UI/group_row_num",row_num+1);
                                        row_num++;
                                        update_table();
                                    }
                                }
                            }

                            Text{
                                font.family: font_noto_r.name
                                font.pixelSize: 15
                                color: "white"
                                text: qsTr("세로열개수")
                            }
                            Text{
                                font.family: font_noto_r.name
                                font.pixelSize: 15
                                color: "white"
                                text: ":"
                            }
                            Rectangle{
                                width: 30
                                height: 30
                                radius: 30
                                enabled: col_num > 1
                                color: enabled?color_dark_black:color_dark_gray
                                border.color: "#e8e8e8"
                                border.width: 1

                                Rectangle{
                                    width: 14
                                    radius: 2
                                    height: 2
                                    anchors.centerIn: parent
                                    color: color_mid_gray
                                }

                                MouseArea{
                                    anchors.fill: parent
                                    onClicked: {
                                        supervisor.playSound('click');
                                        supervisor.setSetting("setting","UI/group_col_num",col_num-1);
                                        col_num--;
                                        update_table();
                                    }
                                }
                            }
                            Rectangle{
                                width: 30
                                height: 30
                                radius: 30
                                enabled: col_num < max_col
                                color: enabled?color_dark_black:color_dark_gray
                                border.color: "#e8e8e8"
                                border.width: 1
                                Rectangle{
                                    width: 2
                                    radius: 2
                                    height: 14
                                    anchors.centerIn: parent
                                    color: color_mid_gray
                                }
                                Rectangle{
                                    width: 14
                                    radius: 2
                                    height: 2
                                    anchors.centerIn: parent
                                    color: color_mid_gray
                                }
                                MouseArea{
                                    anchors.fill: parent
                                    onClicked: {
                                        supervisor.playSound('click');
                                        supervisor.setSetting("setting","UI/group_col_num",col_num+1);
                                        col_num++;
                                        update_table();
                                    }
                                }
                            }
                        }
                        Rectangle{
                            id: btn_confirm_tables_group
                            color: "#282828"
                            width: 40
                            height: 40
                            radius: 40
                            anchors.verticalCenter: parent.verticalCenter
                            border.color: "#e8e8e8"
                            border.width: 1
                            Image{
                                anchors.fill: parent
                                sourceSize.width: width
                                sourceSize.height: height
                                source: "icon/icon_yes.png"
                            }
                            MouseArea{
                                anchors.fill: parent
                                onClicked: {
                                    supervisor.playSound('click');
                                    btn_lock_group.visible = true;
                                    btns_table_group.visible = false;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    Rectangle{
        id: rect_go
        width: 300
        visible: show_serving?true:false
        height: 120
        radius: 100
        anchors.horizontalCenter: {
            if(use_tray){
                rect_tray_box.horizontalCenter
            }else{
                rect_table_group.horizontalCenter
            }
        }
        anchors.top: {
            if(use_tray){
                rect_tray_box.bottom
            }else{
                rect_table_group.bottom
            }
        }
        anchors.topMargin: {
            if(use_tray)
                40
            else
                20
        }
        color: "#24a9f7"
        Text{
            id: text_go
            anchors.centerIn: parent
            text: qsTr("서빙 시작")
            font.family: font_noto_r.name
            font.pixelSize: 35
            font.bold: true
            color: "white"
        }
        MouseArea{
            id: btn_go
            property bool active: true
            property bool hold: false
            anchors.fill: parent
            onPressed:{
                if(active){
                    hold = false;
                    if(cur_table==-1){
                        supervisor.playSound('no');
                    }else{
                        supervisor.playSound('click');
                    }
                }else{
                    supervisor.playSound('no');
                    cur_table = -1;
                }
            }
            onPressAndHold: {
                if(active){
                    hold = true;
                    popup_preset_menu.open();
                }
            }

            onReleased:{
                if(active){
                    if(!hold){
                        if(cur_table>-1){
                            supervisor.setMotorLock(true);
                            if(supervisor.getSetting("setting","USE_UI","use_tray") === "true"){
                                for(var i=0; i<tray_num; i++){
//                                    print(i, traymodel.get(i).setting, traymodel.get(i).group, traymodel.get(i).table);
                                    if(traymodel.get(i).setting){
                                        supervisor.setTray(i,traymodel.get(i).group,traymodel.get(i).table);
                                    }
                                }
                                supervisor.writelog("[UI] PageKitchen : start Serving (use tray)");
                                supervisor.startServing();
                            }else{
                                supervisor.writelog("[UI] PageKitchen : start Serving");
                                supervisor.startServing(model_group.get(cur_group).num,cur_table);
                            }
                            cur_table = -1;
                        }else{
                            supervisor.writelog("[UI] PageKitchen : start Serving but cur_table -1");
                        }
                    }
                }else{
                    supervisor.writelog("[UI] PageKitchen : start Serving but not actived");
                    robotnotready();
                }
            }
        }

        Popup{
            id: popup_preset_menu
            width: 600
            height: 120
            leftPadding: 0
            rightPadding: 0
            topPadding: 0
            bottomPadding: 0
            background: Rectangle{
                anchors.fill: parent
                color: "transparent"
            }
            onOpened: {
                ani_open.start();
            }
            ParallelAnimation{
                id: ani_open
                onStarted: {
                    row_preset.opacity = 0;
                }

                SequentialAnimation{
                    ParallelAnimation{
                        NumberAnimation{
                            target: rect_preset
                            duration: 300
                            to: popup_preset_menu.width
                            from: 300
                            property: "width"
                        }
                        NumberAnimation{
                            target: rect_preset
                            duration: 300
                            to: -150
                            from: 0
                            property: "x"
                        }
                    }

                    NumberAnimation{
                        target: row_preset
                        duration: 50
                        to: 1
                        from: 0
                        property: "opacity"
                    }
                }
            }
            Rectangle{
                id: rect_preset
                width: parent.width
                height: parent.height
                radius: 100
                color: color_blue
                Row{
                    id: row_preset
                    opacity: 0
                    anchors.centerIn: parent
                    spacing: 15
                    Text{
                        anchors.verticalCenter: parent.verticalCenter
                        font.family: font_noto_r.name
                        font.pixelSize: 25
                        color: "white"
                        text: qsTr("속도설정")
                    }
                    Rectangle{
                        width: 1
                        height: 70
                        color: color_mid_gray
                    }
                    Rectangle{
                        width: 60
                        height: 60
                        anchors.verticalCenter: parent.verticalCenter
                        color: "transparent"
                        Text{
                            anchors.centerIn: parent
                            font.family: font_noto_r.name
                            font.pixelSize: 50
                            color: cur_preset===1?"white":color_dark_gray
                            text: "1"
                        }
                        MouseArea{
                            anchors.fill: parent
                            onClicked:{
                                supervisor.playSound('click');
                                cur_preset = 1;
                                supervisor.setPreset(cur_preset);
                            }
                        }
                    }
                    Rectangle{
                        width: 1
                        height: 70
                        color: color_mid_gray
                    }
                    Rectangle{
                        width: 60
                        height: 60
                        anchors.verticalCenter: parent.verticalCenter
                        color: "transparent"
                        Text{
                            anchors.centerIn: parent
                            font.family: font_noto_r.name
                            font.pixelSize: 50
                            color: cur_preset===2?"white":color_dark_gray
                            text: "2"
                        }
                        MouseArea{
                            anchors.fill: parent
                            onClicked:{
                                supervisor.playSound('click');
                                cur_preset = 2;
                                supervisor.setPreset(cur_preset);
                            }
                        }
                    }
                    Rectangle{
                        width: 1
                        height: 70
                        color: color_mid_gray
                    }
                    Rectangle{
                        width: 60
                        height: 60
                        anchors.verticalCenter: parent.verticalCenter
                        color: "transparent"
                        Text{
                            anchors.centerIn: parent
                            font.family: font_noto_r.name
                            font.pixelSize: 50
                            color: cur_preset===3?"white":color_dark_gray
                            text: "3"
                        }
                        MouseArea{
                            anchors.fill: parent
                            onClicked:{
                                supervisor.playSound('click');
                                cur_preset = 3;
                                supervisor.setPreset(cur_preset);
                            }
                        }
                    }
                    Rectangle{
                        width: 1
                        height: 70
                        color: color_mid_gray
                    }
                    Rectangle{
                        width: 60
                        height: 60
                        anchors.verticalCenter: parent.verticalCenter
                        color: "transparent"
                        Text{
                            anchors.centerIn: parent
                            font.family: font_noto_r.name
                            font.pixelSize: 50
                            color: cur_preset===4?"white":color_dark_gray
                            text: "4"
                        }
                        MouseArea{
                            anchors.fill: parent
                            onClicked:{
                                supervisor.playSound('click');
                                cur_preset = 4;
                                supervisor.setPreset(cur_preset);
                            }
                        }
                    }
                    Rectangle{
                        width: 1
                        height: 70
                        color: color_mid_gray
                    }
                    Rectangle{
                        width: 60
                        height: 60
                        anchors.verticalCenter: parent.verticalCenter
                        color: "transparent"
                        Text{
                            anchors.centerIn: parent
                            font.family: font_noto_r.name
                            font.pixelSize: 50
                            color: cur_preset===5?"white":color_dark_gray
                            text: "5"
                        }
                        MouseArea{
                            anchors.fill: parent
                            onClicked:{
                                supervisor.playSound('click');
                                cur_preset = 5;
                                supervisor.setPreset(cur_preset);
                            }
                        }
                    }
                }
            }
        }

    }



    //=======================Calling Mode=============================//
    Rectangle{
        id: rect_calling_box
        visible: !show_serving?true:false
        width: 500
        height: tray_num*tray_height + (tray_num - 1)*spacing_tray + 50
        color: "#e8e8e8"
        radius: 30
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        Text{
            color:"white"
            font.bold: true
            font.family: font_noto_b.name
            text: qsTr("호출 대기 중")
            anchors.centerIn: parent
            font.pixelSize: 50
        }
    }

    Rectangle{
        id: rect_go_patrol
        width: 300
        visible: !show_serving?true:false
        height: 100
        radius: 100
        anchors.horizontalCenter: rect_calling_box.horizontalCenter
        anchors.top: rect_calling_box.bottom
        anchors.topMargin: 40
        color: "#24a9f7"
        Text{
            id: text_go2
            anchors.centerIn: parent
            text: qsTr("순회 시작")
            font.family: font_noto_r.name
            font.pixelSize: 35
            font.bold: true
            color: "white"
        }
        MouseArea{
            id: btn_go2
            anchors.fill: parent
            onClicked: {
                supervisor.playSound('click');
                popup_patrol.open();
            }
        }
    }




    //=======================Public=============================//
    Item_menubar{
        id: menubar
        anchors.right: parent.right
        anchors.rightMargin: 50
        anchors.top: parent.top
        anchors.topMargin: statusbar.height + 50
        Component.onCompleted: {
            addMenu("","icon/btn_menu.png");
            addMenu(qsTr("충전위치로"),"icon/icon_charge.png");
            addMenu(qsTr("대기위치로"),"icon/icon_wait.png");
            if(supervisor.getSetting("setting","ROBOT_TYPE","type") === "CLEANING"){
                addMenu(qsTr("퇴식위치로"),"icon/icon_clean.png")
            }
        }
        onMenu1_clicked: {
            supervisor.playSound('click');
            cur_table = -1;
            loadPage(pmenu);
        }
        onMenu2_clicked: {
            cur_table = -1;
            if(menu2_en){
                supervisor.playSound('click');
                move_loc = "Charging";
                popup_question.open();
            }else{
                supervisor.playSound('no');
                robotnotready();
            }
        }
        onMenu3_clicked: {
            cur_table = -1;
            if(menu3_en){
                supervisor.playSound('click');
                move_loc = "Resting";
                popup_question.open();
            }else{
                supervisor.playSound('no');
                robotnotready();
            }
        }
        onMenu4_clicked: {
            cur_table = -1;
            if(menu4_en){
                supervisor.playSound('click');
                move_loc = "Cleaning";
                popup_question.open();
            }else{
                supervisor.playSound('no');
                robotnotready();
            }
        }
    }

    Popup{
        id: popup_question
        width: parent.width
        height: parent.height
        anchors.centerIn: parent
        background:Rectangle{
            anchors.fill: parent
            color: "#282828"
            opacity: 0.8
        }
        Image{
            id: image_location
            source:"image/image_location.png"
            width: 160
            height: 160
            sourceSize.width: width
            sourceSize.height: height
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 200
        }
        Text{
            id: text_quest
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top:image_location.bottom
            anchors.topMargin: 30
            font.family: font_noto_b.name
            font.pixelSize: 40
            color: "#12d27c"
            text: {
                if(move_loc === "Resting"){
                    qsTr("대기 장소로 이동<font color=\"white\">하시겠습니까?</font>")
                }else if(move_loc === "Cleaning"){
                    qsTr("퇴식 장소로 이동<font color=\"white\">하시겠습니까?</font>")
                }else if(move_loc === "Charging"){
                    qsTr("충전기로 이동<font color=\"white\">하시겠습니까?</font>")
                }else{
                    ""
                }
            }
        }
        Rectangle{
            id: btn_no
            width: 250
            height: 90
            radius: 20
            color: "#d0d0d0"
            anchors.top: text_quest.bottom
            anchors.topMargin: 50
            anchors.right: parent.horizontalCenter
            anchors.rightMargin: 20
            Image{
                id: image_no
                source: "icon/btn_no.png"
                width: 50
                height: 50
                sourceSize.width: width
                sourceSize.height: height
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 20
            }
            Text{
                id:text_nono
                text:qsTr("아니오")
                font.family: font_noto_b.name
                font.pixelSize: 30
                color:"#282828"
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: image_no.right
                anchors.leftMargin : (parent.width - image_no.x - image_no.width)/2 - text_nono.width/2
            }
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    supervisor.playSound('click');
                    move_loc = "None";
                    popup_question.close();
                }
            }
        }
        Rectangle{
            id: btn_yes
            width: 250
            height: 90
            radius: 20
            color: "#d0d0d0"
            anchors.top: text_quest.bottom
            anchors.topMargin: 50
            anchors.left: parent.horizontalCenter
            anchors.leftMargin: 20
            Rectangle{
                color:"white"
                width: 240
                height: 80
                radius: 19
                anchors.centerIn: parent
            }
            Image{
                id: image_yes
                source: "icon/icon_yes.png"
                width: 50
                height: 50
                sourceSize.width: width
                sourceSize.height: height
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 20
            }
            Text{
                text:qsTr("네")
                font.family: font_noto_b.name
                font.pixelSize: 30
                color:"#282828"
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: image_yes.right
                anchors.leftMargin : (parent.width - image_yes.x - image_yes.width)/2 - width/2
            }
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    supervisor.playSound('click');
                    supervisor.setMotorLock(true);
                    if(move_loc === "Resting"){
                        supervisor.moveToWait();
                    }else if(move_loc === "Charging"){
                        supervisor.moveToCharge();
                    }else if(move_loc === "Cleaning"){
                        supervisor.moveToCleaning();
                    }
                    move_loc = "None";
                    popup_question.close();
                }
            }
        }
    }

    Popup_patrol{
        id: popup_patrol
    }

    Popup{
        id: popup_clean_calling
        anchors.centerIn: parent
        width: 1280
        height: 800
        property bool cleaninglocation: false
        background: Rectangle{
            anchors.fill: parent
            color: color_dark_black
            opacity: 0.8
        }
        onOpened: {
            update();
            timer_upd.start();
            if(cleaninglocation){
                cleaning_text.text = qsTr("확인버튼을 누르시면 대기위치로 이동합니다\n바로 이동명령을 내리시려면 닫기를 눌러주세요")
            }else{
                cleaning_text.text = qsTr("다음 이동 가능한 상태가 되면 확인 버튼을 눌러주세요")
            }
        }
        onClosed:{
            timer_upd.stop();
        }

        Timer{
            id: timer_upd
            repeat: true
            interval: 1000
            onTriggered:{
                popup_clean_calling.update();
            }
        }

        function update(){
            calls.clear();
            for(var i=0; i<supervisor.getCallQueueSize(); i++){
                calls.append({"loc_name":supervisor.getCallName(i)});
            }
            if(calls.count > 0){
                calling_list.visible = true;
            }else{
                calling_list.visible = false;
            }
        }

        Rectangle{
            anchors.fill: parent
            color: "transparent"
            Column{
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                anchors.topMargin: 80
                Text{
                    color: "white"
                    anchors.horizontalCenter: parent.horizontalCenter
                    horizontalAlignment: Text.AlignHCenter
                    font.family: font_noto_r.name
                    font.pixelSize: 45
                    text: qsTr("다녀왔습니다")
                }
                Text{
                    id: cleaning_text
                    color: "white"
                    horizontalAlignment: Text.AlignHCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.family: font_noto_r.name
                    font.pixelSize: 40
                    text: qsTr("확인버튼을 누르시면 대기위치로 이동합니다\n바로 이동명령을 내리시려면 닫기를 눌러주세요")
                }
            }

            Column{
                id: calling_list
                anchors.centerIn: parent
                spacing: 5
                Text{
                    anchors.horizontalCenter: parent.horizontalCenter
                    color: "white"
                    horizontalAlignment: Text.AlignHCenter
                    font.family: font_noto_r.name
                    font.pixelSize: 30
                    text: qsTr("호출 대기열")
                }
                Flickable{
                    anchors.horizontalCenter: parent.horizontalCenter
                    width: 600
                    height: 100
                    contentWidth: row_calling.width
                    clip: true
                    Row{
                        id: row_calling
                        anchors.centerIn: parent
                        spacing: 10
                        Repeater{
                            id: rep_call
                            model: ListModel{id: calls}
                            Rectangle{
                                color: "transparent"
                                border.width: 2
                                border.color: "white"
                                width: 150
                                radius: 20
                                height: 60
                                Text{
                                    color:"white"
                                    font.family: font_noto_r.name
                                    text: loc_name
                                    anchors.centerIn: parent
                                    font.pixelSize: 20
                                    Component.onCompleted: {
                                        scale = 1;
                                        while(width*scale > parent.width*0.8){
                                            scale=scale-0.01;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }

            }

            Row{
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 100
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: 30
                Rectangle{
                    width: 250
                    height: 90
                    radius: 19
                    color:"#d0d0d0"
                    visible: calling_list.visible
                    Image{
                        id: imm2
                        source: "icon/icon_yes.png"
                        width: 50
                        height: 50
                        sourceSize.width: width
                        sourceSize.height: height
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.leftMargin: 20
                    }
                    Text{
                        text:qsTr("대기열 지우기")
                        font.family: font_noto_b.name
                        font.pixelSize: 25
                        color:"#282828"
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: imm2.right
                        anchors.leftMargin : (parent.width - imm2.x - imm2.width)/2 - width/2
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            supervisor.playSound('click');
                            supervisor.clearCallQueue();
                        }
                    }
                }
                Rectangle{
                    width: 250
                    height: 90
                    radius: 20
                    visible: popup_clean_calling.cleaninglocation && calling_list.visible
                    color: "#d0d0d0"
                    Rectangle{
                        width: 240
                        height: 80
                        anchors.centerIn: parent
                        radius: 19
                        color: "white"
                        Text{
                            text:qsTr("호출위치로")
                            font.family: font_noto_b.name
                            font.pixelSize: 30
                            color:"#282828"
                            anchors.centerIn: parent
                        }
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            supervisor.playSound('click');
                            supervisor.cleanTray();
                        }
                    }
                }
                Rectangle{
                    width: 250
                    height: 90
                    radius: 20
                    visible: popup_clean_calling.cleaninglocation
                    color: "#d0d0d0"
                    Rectangle{
                        width: 240
                        height: 80
                        anchors.centerIn: parent
                        radius: 19
                        color: "white"
                        Text{
                            text:qsTr("확인")
                            font.family: font_noto_b.name
                            font.pixelSize: 30
                            color:"#282828"
                            anchors.centerIn: parent
                        }
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            supervisor.playSound('click');
                            supervisor.moveToWait();
                        }
                    }
                }

                Rectangle{
                    width: 250
                    height: 90
                    radius: 20
                    visible: popup_clean_calling.cleaninglocation
                    color: "#d0d0d0"
                    Rectangle{
                        width: 240
                        height: 80
                        anchors.centerIn: parent
                        radius: 19
                        color: "white"
                        Text{
                            text:qsTr("닫기")
                            font.family: font_noto_b.name
                            font.pixelSize: 30
                            color:"#282828"
                            anchors.centerIn: parent
                        }
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            supervisor.playSound('click');
                            supervisor.stateInit();
                            popup_clean_calling.close();
                        }
                    }
                }
                Rectangle{
                    width: 250
                    height: 90
                    radius: 20
                    visible: !popup_clean_calling.cleaninglocation
                    color: "#d0d0d0"
                    Rectangle{
                        width: 240
                        height: 80
                        anchors.centerIn: parent
                        radius: 19
                        color: "white"
                        Image{
                            id: imm
                            source: "icon/icon_yes.png"
                            width: 50
                            height: 50
                            sourceSize.width: width
                            sourceSize.height: height
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.left: parent.left
                            anchors.leftMargin: 20
                        }
                        Text{
                            text:qsTr("확인")
                            font.family: font_noto_b.name
                            font.pixelSize: 30
                            color:"#282828"
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.left: imm.right
                            anchors.leftMargin : (parent.width - imm.x - imm.width)/2 - width/2
                        }
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            supervisor.playSound('click');
                            supervisor.cleanTray();
                            popup_clean_calling.close();
                        }
                    }
                }

            }
        }
    ListModel{id:model_group_table_temp}
    }

    Popup_notice{
        id: popup_notice
        z:99
        onClicked:{
            if(cur_btn === qsTr("수동이동")){
                supervisor.writelog("[UI] PopupNotice : Lock Off");
                supervisor.setMotorLock(false);
            }else if(cur_btn === qsTr("취 소")||cur_btn === qsTr("확 인")){
                popup_notice.close();
            }else if(cur_btn === qsTr("모터초기화")){
                supervisor.writelog("[UI] PopupNotice : Motor Init");
                supervisor.setMotorLock(true);
                supervisor.stateInit();
                if(loader_page.item.objectName === "page_moving" || loader_page.item.objectName === "page_moving_custom"){
                    loadPage(pinit);
                }
                popup_notice.close();
            }else if(cur_btn === qsTr("위치초기화")){
                supervisor.writelog("[UI] PopupNotice : Local Init");
                if(loader_page.item.objectName === "page_annotation"){
                    loader_page.item.setAnnotLocation();
                }else{
                    loadPage(pinit);
                    supervisor.resetLocalization();
                    supervisor.stateInit();
                }
                popup_notice.close();
            }else if(cur_btn === qsTr("원래대로")){
                supervisor.writelog("[UI] PopupNotice : Lock On");
                supervisor.setMotorLock(true);
                supervisor.moveStopFlag();
                loadPage(pkitchen);
                popup_notice.close();
            }
        }
    }

}
