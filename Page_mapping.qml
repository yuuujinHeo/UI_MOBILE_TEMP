import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
//import QtQu+ick.Dialogs 1.2
import Qt.labs.platform 1.0 as Platform
import QtQuick.Shapes 1.12
import QtGraphicalEffects 1.0
import QtMultimedia 5.12
import "."
import io.qt.Supervisor 1.0


Item {
    id: page_mapping
    objectName: "page_mapping"
    width: 1280
    height: 800
    property bool test: true
    property bool is_mapping: false
    property string map_name : "TEST_1"
    property var grid_width: 3
    property var map_width: 1000
    function init(){
        mapping_pages.sourceComponent = page_mapping_start;
        map_name = "TEST_1";
        grid_width = 3;
    }
    function update_mapping(){
        mapping_pages.item.update();
    }

    Timer{
        id: update_timer
        interval: 100
        running: true
        repeat: true
        onTriggered:{
            if(supervisor.getMappingflag()){
                if(!is_mapping){
                    supervisor.writelog("[UI] Play Voice : start mapping");
                    supervisor.playVoice("start_mapping");
                    is_mapping = true;
                }
            }else{
                if(is_mapping){
                    supervisor.writelog("[UI] Play Voice : stop mapping");
                    supervisor.playVoice("stop_mapping");
                    is_mapping = false;
                }
            }
        }
    }
    Loader{
        id: mapping_pages
        width: 1280
        height: 800 - statusbar.height
        anchors.bottom: parent.bottom
        clip: true
        sourceComponent: page_mapping_start
    }
    Component{
        id: page_mapping_start
        Item{
            width: mapping_pages.width
            height: mapping_pages.height
            Component.onCompleted: {
                supervisor.setMotorLock(false);
            }

            Rectangle{
                anchors.fill: parent
                color: color_dark_navy
            }
            Column{
                id: col
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                anchors.topMargin: 120
                spacing: 30
                Text{
                    text: qsTr("맵 생성을 시작합니다")
                    color: "white"
                    font.pixelSize: 80
                    font.family: font_noto_b.name
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                Text{
                    text: qsTr("매장환경을 정돈하신 후 가급적 테이블의 이동을 삼가 해주시기 바랍니다\n지금부터 로봇을 밀며 이동할 수 있습니다")
                    color: "white"
                    font.pixelSize: 30
                    horizontalAlignment: Text.AlignHCenter
                    font.family: font_noto_r.name
                    anchors.horizontalCenter: parent.horizontalCenter
                }
            }
            Rectangle{
                width: 80
                height: width
                radius: width
                visible: false
                color: "transparent"
                border.width:2
                border.color: "white"
                anchors.right: parent.right
                anchors.rightMargin: 50
                anchors.top: parent.top
                anchors.topMargin: 50
                Text{
                    anchors.centerIn: parent
                    text : "?"
                    font.family: font_noto_b.name
                    color: "white"
                    font.pixelSize: 80
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked:{
                        supervisor.playSound('click');;
                        popup_help.setTitle(qsTr("맵 생성"));
                        popup_help.addTip(qsTr("맵 생성이 무엇인가요?","로봇을 처음 세팅하거나 매장의 환경이 많이 바뀌었을 때 매장의 지도를 다시 그려야 합니다\n맵을 생성하고 저장하면 기존의 데이터는 더 이상 사용하지 않으며 새로 세팅해야 합니다\n맵을 그린 뒤 각각의 서빙, 충전 위치 등을 지정하고 이동경로를 학습하려면 [시작] 버튼을 누르세요"));
                        popup_help.addTip(qsTr("맵 생성을 했다가 다시 되돌릴 수 있나요?","맵을 저장하지 않으면 기존 데이터를 덮어쓰지 않습니다\n만일 맵을 저장했다 하더라도 기존에 저장된 맵과 서빙포인트를 되살리고 싶다면 맵 설정 페이지에서 맵 불러오기를 실행하세요"));
                        popup_help.open();
                    }
                }
            }

            AnimatedImage{
                id: image_robotmoving
                source: "image/robot_manual.gif"
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: parent.bottom
                width: 1280/1.5
                height: 800/1.5
                speed: 0.5
                anchors.bottomMargin: -100
            }

            Rectangle{
                id: btn_right
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                anchors.bottomMargin: 50
                anchors.rightMargin: 50
                width: 200
                height: 80
                radius: 15
                border.width: 2
                border.color: "white"
                color: "transparent"
                Text{
                    Component.onCompleted: {
                        scale = 1;
                        while(width*scale > 180){
                            scale=scale-0.01;
                        }
                    }
                    anchors.centerIn: parent
                    font.family: font_noto_r.name
                    font.pixelSize: 30
                    color: "white"
                    text: qsTr("시 작")
                }
                MouseArea{
                    anchors.fill: parent
                    onPressed:{
                        parent.color = color_mid_navy;
                    }
                    onReleased: {
                        supervisor.playSound('click');;
                        supervisor.writelog("[MAPPING] START Mapping : next page")
                        mapping_pages.sourceComponent = page_mapping_set;
                        parent.color = "transparent";
                    }
                }
            }
            Rectangle{
                id: btn_left
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.bottomMargin: 50
                anchors.leftMargin: 50
                width: 200
                height: 80
                radius: 15
                border.width: 2
                border.color: "white"
                color: "transparent"
                Text{
                    Component.onCompleted: {
                        scale = 1;
                        while(width*scale > 180){
                            scale=scale-0.01;
                        }
                    }
                    anchors.centerIn: parent
                    font.family: font_noto_r.name
                    font.pixelSize: 30
                    color: "white"
                    text: qsTr("취 소")
                }
                MouseArea{
                    anchors.fill: parent
                    onPressed:{
                        parent.color = color_mid_navy;
                    }
                    onReleased: {
                        supervisor.playSound('click');;
                        if(pbefore === pannotation){
                            loadPage(pinit);
                        }else{
                            backPage();
                        }
                        parent.color = "transparent";
                    }
                }
            }
        }
    }
    Component{
        id: page_mapping_set
        Item{
            width: mapping_pages.width
            height: mapping_pages.height
            property var select_grid: 5
            property var available_size: 0
            onSelect_gridChanged: {
                available_size = select_grid*slider_mapsize.value/100;
            }

            Rectangle{
                anchors.fill: parent
                color: color_dark_navy
            }
            Component.onCompleted: {
                textfield_name.text = supervisor.getnewMapname();
                slider_mapsize.value = parseInt(supervisor.getSetting("update","SLAM","map_size"));
            }

            Text{
                text: qsTr("맵의 기본 정보를 설정합니다")
                color: "white"
                font.pixelSize: 60
                font.family: font_noto_b.name
                anchors.top: parent.top
                anchors.topMargin: 30
                anchors.horizontalCenter: parent.horizontalCenter
            }
            Column{
                width: 550
                anchors.centerIn: parent
                spacing: 30
                Column{
                    spacing: 20
                    anchors.horizontalCenter: parent.horizontalCenter
                    Text{
                        font.family: font_noto_r.name
                        font.pixelSize: 30
                        color: "white"
                        text: qsTr("맵의 이름")
                    }
                    TextField{
                        id: textfield_name
                        width: 550
                        height: 70
                        horizontalAlignment: TextField.AlignHCenter
                        font.family: font_noto_r.name
                        font.pixelSize: 20
                        Component.onCompleted: {
                            focus = false;
                        }
                        onFocusChanged: {
                            keyboard.owner = textfield_name;
                            textfield_name.selectAll();
                            if(focus){
                                keyboard.open();
                            }else{
                                keyboard.close();
                                textfield_name.select(0,0);
                            }
                        }
                    }
                }
                Column{
                    spacing: 20
                    width: 550
                    anchors.horizontalCenter: parent.horizontalCenter
                    Column{
                        spacing: 3
                        Rectangle{
                            width: 550
                            height: 40
                            color: "transparent"
                            Text{
                                font.family: font_noto_r.name
                                font.pixelSize: 30
                                color: "white"
                                text: qsTr("맵 크기")
                            }

                            Text{
                                anchors.right: parent.right
                                font.family: font_noto_r.name
                                font.pixelSize: 30
                                color: "white"
                                //text: slider_mapsize.value.toString() + " [pixel]"
                                text:available_size.toString() + " m X " + available_size.toString() + " m";
                            }
                        }
                        Text{
                            anchors.right: parent.right
                            font.family: font_noto_r.name
                            font.pixelSize: 20
                            color: color_green
                            text: qsTr("크기가 커질 수록 이동을 시작할 때나 맵을 그릴 때 느려질 수 있습니다")
                        }
                    }
                    Slider{
                        id: slider_mapsize
                        width: 550
                        from: 1000
                        to: 2500
                        stepSize: 200
                        onValueChanged: {
                            available_size = select_grid*slider_mapsize.value/100;
                        }
                    }
                }
                Column{
                    spacing: 20
                    width: 550
                    anchors.horizontalCenter: parent.horizontalCenter
                    Column{
                        spacing: 3
                        Text{
                            width: 550
                            font.family: font_noto_r.name
                            font.pixelSize: 30
                            color: "white"
                            text: qsTr("맵 해상도") // 맵 픽셀 당 크기
                        }
                        Text{
                            anchors.right: parent.right
                            font.family: font_noto_r.name
                            font.pixelSize: 20
                            color: color_green
                            text: qsTr("해상도가 정밀할 수록 정밀한 로봇 이동이 가능합니다") //픽셀크기가 작을 수록 정밀한 로봇 이동이 가능합니다
                        }
                    }

                    Row{
                        anchors.horizontalCenter: parent.horizontalCenter
                        spacing: 50
                        Rectangle{
                            width: 150
                            height: 80
                            radius: 20
                            border.width: 2
                            border.color: "white"
                            color: select_grid === 3?color_green:"transparent"
                            Text{
                                anchors.centerIn: parent
                                font.family: font_noto_r.name
                                font.pixelSize: 30
                                color: "white"
                                text: "정밀" //3cm
                            }
                            MouseArea{
                                anchors.fill: parent
                                onClicked: {
                                    supervisor.playSound('click');;
                                    select_grid = 3;
                                }
                            }
                        }
                        Rectangle{
                            width: 150
                            height: 80
                            radius: 20
                            border.width: 2
                            border.color: "white"
                            color: select_grid === 5?color_green:"transparent"
                            Text{
                                anchors.centerIn: parent
                                font.family: font_noto_r.name
                                font.pixelSize: 30
                                color: "white"
                                text: "보통" //5cm
                            }
                            MouseArea{
                                anchors.fill: parent
                                onClicked: {
                                    supervisor.playSound('click');;
                                    select_grid = 5;
                                }
                            }
                        }
                        Rectangle{
                            width: 150
                            height: 80
                            radius: 20
                            border.width: 2
                            border.color: "white"
                            color: select_grid === 3||select_grid === 5?"transparent":color_green
                            Text{
                                anchors.centerIn: parent
                                font.family: font_noto_r.name
                                font.pixelSize: 30
                                color: "white"
                                text: select_grid === 3||select_grid === 5?qsTr("그 외"):select_grid.toString()+" cm"
                            }
                            MouseArea{
                                anchors.fill: parent
                                onClicked: {
                                    supervisor.playSound('click');;
                                    popup_select_grid.open();
                                }
                            }
                        }
                    }
                }
            }
            Timer{
                running: true
                interval: 1000
                onTriggered: {
                    btn_right.enabled = true;
                }
            }

            Popup{
                id: popup_select_grid
                anchors.centerIn: parent
                width: 600
                height: 300
                background: Rectangle{
                    anchors.fill: parent
                    color: "transparent"
                }
                Rectangle{
                    width: parent.width
                    height: parent.height
                    radius: 20
                    color: color_navy
                    Column{
                        anchors.centerIn: parent
                        spacing: 50
                        Column{
                            anchors.horizontalCenter: parent.horizontalCenter
                            spacing: 10
                            Text{
                                anchors.horizontalCenter: parent.horizontalCenter
                                font.family: font_noto_r.name
                                font.pixelSize: 30
                                color: "white"
                                text: qsTr("맵 해상도") // 맵 픽셀 당 크기
                            }
                            Text{
                                anchors.horizontalCenter: parent.horizontalCenter
                                font.family: font_noto_r.name
                                font.pixelSize: 30
                                color: "white"
                                text: slider_grid.value.toString()+" cm"
                            }
                        }

                        Slider{
                            id: slider_grid
                            width: 500
                            anchors.horizontalCenter: parent.horizontalCenter
                            from: 1
                            to: 10
                            value: 3
                            stepSize: 1
                            onValueChanged: {
                                select_grid = value;
                            }
                        }
                    }
                }
            }

            Column{
                anchors.horizontalCenter: btn_right.horizontalCenter
                anchors.bottom: btn_right.top
                anchors.bottomMargin: 10
                spacing: 5
                Text{
                    font.pixelSize: 15
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.family: font_noto_r.name
                    color: color_blue
                    text:qsTr("맵 생성 가능한 매장 크기(최대)")
                }
                Text{
                    font.pixelSize: 15
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.family: font_noto_r.name
                    color: color_blue
                    //text:available_size.toString() + " m X " + available_size.toString() + " m";
                    text: slider_mapsize.value.toString() + " [pixel]"
                }
            }


            Rectangle{
                id: btn_right
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                anchors.bottomMargin: 50
                anchors.rightMargin: 50
                width: 200
                height: 80
                radius: 15
                border.width: 2
                border.color: "white"
                enabled: false
                color: enabled?"transparent":color_dark_gray
                Text{
                    Component.onCompleted: {
                        scale = 1;
                        while(width*scale > 180){
                            scale=scale-0.01;
                        }
                    }
                    anchors.centerIn: parent
                    font.family: font_noto_r.name
                    font.pixelSize: 30
                    color: "white"
                    text: qsTr("맵 생성")
                }
                MouseArea{
                    anchors.fill: parent
                    onPressed:{
                        parent.color = color_mid_navy;
                    }
                    onReleased: {
                        supervisor.playSound('click');;
                        map_name = textfield_name.text;
                        map_width = slider_mapsize.value;
                        grid_width = (select_grid/100);
                        supervisor.setSetting("update","SLAM/map_size","1000");
                        supervisor.setSetting("update","SLAM/grid_size",grid_width.toString());
                        supervisor.writelog("[MAPPING] START Mapping : set name("+map_name+") grid("+grid_width.toString()+")");
                        mapping_pages.sourceComponent = page_mapping_view;
                        parent.color = "transparent";
                    }
                }
            }
            Rectangle{
                id: btn_left
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.bottomMargin: 50
                anchors.leftMargin: 50
                width: 200
                height: 80
                radius: 15
                border.width: 2
                border.color: "white"
                color: "transparent"
                Text{
                    Component.onCompleted: {
                        scale = 1;
                        while(width*scale > 180){
                            scale=scale-0.01;
                        }
                    }
                    anchors.centerIn: parent
                    font.family: font_noto_r.name
                    font.pixelSize: 30
                    color: "white"
                    text: qsTr("취 소")
                }
                MouseArea{
                    anchors.fill: parent
                    onPressed:{
                        parent.color = color_mid_navy;
                    }
                    onReleased: {
                        supervisor.playSound('click');;
                        supervisor.writelog("[MAPPING] START Mapping : prev page")
                        mapping_pages.sourceComponent = page_mapping_start;
                        parent.color = "transparent";
                    }
                }
            }

        }

    }
    Component{
        id: page_mapping_view
        Item{
            width: mapping_pages.width
            height: mapping_pages.height
            Component.onCompleted: {
                mapping_view.init();
                mapping_view.setTool("move");
                mapping_view.setViewer("mapping");
                mapping_view.setEnable(true)
                supervisor.startMapping(map_width,grid_width);
            }
            function update(){
//                print("update mapping");
                mapping_view.loadmapping();
            }

            Rectangle{
                anchors.fill: parent
                color: color_dark_navy
            }

            Rectangle{
                width: 80
                height: width
                radius: width
                color: "transparent"
                visible: false
                border.width:2
                border.color: "white"
                anchors.right: parent.right
                anchors.rightMargin: 50
                anchors.top: parent.top
                anchors.topMargin: 50
                Text{
                    anchors.centerIn: parent
                    text : "?"
                    font.family: font_noto_b.name
                    color: "white"
                    font.pixelSize: 80
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked:{
                        supervisor.playSound('click');;
                        popup_help.setTitle(qsTr("맵 생성"));
                        popup_help.addTip(qsTr("맵을 새로 그리고 싶어요","[취소] 버튼을 누르고 새로 시작해 주세요"));
                        popup_help.addTip(qsTr("맵이 틀어진 것 같아요","맵을 그리다보면 간혹 기존 맵과 일치하지 않게 틀어진 맵이 추가로 그려질 수 있습니다\n이때 틀어졌다고 판단되는 구간에서 잠시 정지하여 기다려주세요\n로봇은 주기적으로 맵의 오차를 계산하고 이를 복구하기 위해 노력합니다"));
                        popup_help.addTip(qsTr("맵이 끝에서 잘립니다","맵 생성이 가능한 사이즈는 정해져있습니다\n맵을 그리기 시작할 때 로봇의 위치는 맵의 중심좌표가 됩니다\n로봇을 맵의 중앙에 가깝게 이동시켜주신뒤 새로 그려주세요\n"));
                        popup_help.open();
                    }
                }
            }

            MAP_FULL2{
                id: mapping_view
                enabled: true
                show_ratio: false
                objectName: "mappingview"
                width: parent.height
                height: parent.height
                anchors.centerIn: parent
                Component.onCompleted: {
                    supervisor.setMapSize(objectName,width,height);
                }
            }

            Rectangle{
                id: btn_right2
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                anchors.bottomMargin: 150
                anchors.rightMargin: 50
                width: 200
                height: 80
                radius: 15
                border.width: 2
                border.color: "white"
                enabled: false||test
                color: enabled?"transparent":color_dark_gray
                Text{
                    Component.onCompleted: {
                        scale = 1;
                        while(width*scale > 180){
                            scale=scale-0.01;
                        }
                    }
                    anchors.centerIn: parent
                    font.family: font_noto_r.name
                    font.pixelSize: 30
                    color: "white"
                    text: qsTr("루프클로징")
                }
                MouseArea{
                    anchors.fill: parent
                    onPressed:{
                        parent.color = color_mid_navy;
                    }
                    onReleased: {
                        supervisor.playSound('click');
                        supervisor.writelog("[MAPPING] Mapping : Loop Closing");
                        supervisor.loopClosing();
                        parent.color = "transparent";
                    }
                }
            }

            Rectangle{
                id: btn_right
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                anchors.bottomMargin: 50
                anchors.rightMargin: 50
                width: 200
                height: 80
                radius: 15
                border.width: 2
                border.color: "white"
                enabled: false||test
                color: enabled?"transparent":color_dark_gray
                Text{
                    Component.onCompleted: {
                        scale = 1;
                        while(width*scale > 180){
                            scale=scale-0.01;
                        }
                    }
                    anchors.centerIn: parent
                    font.family: font_noto_r.name
                    font.pixelSize: 30
                    color: "white"
                    text: qsTr("저 장")
                }
                MouseArea{
                    anchors.fill: parent
                    onPressed:{
                        parent.color = color_mid_navy;
                    }
                    onReleased: {
                        supervisor.playSound('click');;
                        popup_loading.open();
                        supervisor.writelog("[MAPPING] Mapping : save mapping");
                        supervisor.saveMapping(map_name);
                        timer_save_mapping.start();
                        parent.color = "transparent";
                    }
                }
            }
            Timer{
                id: timer_save_mapping
                running: false
                interval: 1000
                onTriggered:{
                    supervisor.writelog("[MAPPING] Mapping : save mapping done1");
                    popup_loading.close();
                    supervisor.writelog("[MAPPING] Mapping : save mapping done2");
                    supervisor.loadMap(map_name);
                    supervisor.writelog("[MAPPING] Mapping : save mapping done3");
                    loadPage(pannotation);
                    supervisor.writelog("[MAPPING] Mapping : save mapping done4");
                    loader_page.item.setMappingFlag();
                    supervisor.writelog("[MAPPING] Mapping : save mapping done5");
                }
            }

            Rectangle{
                id: btn_left
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.bottomMargin: 50
                anchors.leftMargin: 50
                width: 200
                height: 80
                radius: 15
                border.width: 2
                border.color: "white"
                color: "transparent"
                Text{
                    Component.onCompleted: {
                        scale = 1;
                        while(width*scale > 180){
                            scale=scale-0.01;
                        }
                    }
                    anchors.centerIn: parent
                    font.family: font_noto_r.name
                    font.pixelSize: 30
                    color: "white"
                    text: qsTr("취 소")
                }
                MouseArea{
                    anchors.fill: parent
                    onPressed:{
                        parent.color = color_mid_navy;
                    }
                    onReleased: {
                        supervisor.playSound('click');;
                        supervisor.writelog("[MAPPING] START Mapping : Stop and canceled")
                        supervisor.stopMapping();
                        mapping_pages.sourceComponent = page_mapping_start;
                        parent.color = "transparent";
                    }
                }
            }
        }
    }





    // Component{
    //     id: page_mapping_done
    //     Item{
    //         width: mapping_pages.width
    //         height: mapping_pages.height
    //         property bool detect_done: false
    //         Rectangle{
    //             anchors.fill: parent
    //             color: color_dark_navy
    //         }
    //         Component.onCompleted: {
    //             popup_loading.open();
    //         }
    //         Timer{
    //             running: true
    //             interval: 1000
    //             onTriggered: {
    //                 if(supervisor.getIPCConnection()){
    //                     popup_loading.close();
    //                     supervisor.loadMap(map_name);
    //                     detect_done = true;
    //                     stop();
    //                 }
    //             }
    //         }
    //         Column{
    //             anchors.centerIn: parent
    //             spacing: 30
    //             opacity: detect_done?1:0
    //             Behavior on opacity {
    //                 NumberAnimation{
    //                     duration : 500
    //                 }
    //             }
    //             Text{
    //                 text: qsTr("맵 생성을 완료하였습니다")
    //                 color: "white"
    //                 font.pixelSize: 60
    //                 font.family: font_noto_b.name
    //                 anchors.horizontalCenter: parent.horizontalCenter
    //             }
    //             Text{
    //                 text: qsTr("다음으로 맵 설정을 진행합니다")
    //                 color: "white"
    //                 font.pixelSize: 60
    //                 font.family: font_noto_b.name
    //                 anchors.horizontalCenter: parent.horizontalCenter
    //             }
    //         }
    //         Rectangle{
    //             id: btn_right
    //             anchors.bottom: parent.bottom
    //             anchors.right: parent.right
    //             anchors.bottomMargin: 50
    //             anchors.rightMargin: 50
    //             opacity: detect_done?1:0
    //             Behavior on opacity {
    //                 NumberAnimation{
    //                     duration : 500
    //                 }
    //             }
    //             width: 200
    //             height: 80
    //             radius: 15
    //             border.width: 2
    //             border.color: "white"
    //             color: "transparent"
    //             Text{
    //                 Component.onCompleted: {
    //                     scale = 1;
    //                     while(width*scale > 180){
    //                         scale=scale-0.01;
    //                     }
    //                 }
    //                 anchors.centerIn: parent
    //                 font.family: font_noto_r.name
    //                 font.pixelSize: 30
    //                 color: "white"
    //                 text: qsTr("맵 설정")
    //             }
    //             MouseArea{
    //                 anchors.fill: parent
    //                 onPressed:{
    //                     parent.color = color_mid_navy;
    //                 }
    //                 onReleased: {
    //                     supervisor.playSound('click');;
    //                     supervisor.writelog("[MAPPING] START Annotation");
    //                     loadPage(pannotation);
    //                     loader_page.item.setMappingFlag();
    //                     parent.color = "transparent";
    //                 }
    //             }
    //         }
    //     }
    // }

    Popup_help{
        id: popup_help
    }

    Tool_Keyboard{
        id: keyboard
    }
    Popup_loading{
        id: popup_loading
    }
}
