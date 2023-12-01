import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.0
import "."
import io.qt.Supervisor 1.0
import io.qt.CameraView 1.0
import QtQuick.Controls.Styles 1.4
import QtMultimedia 5.12

Item {
    id: page_setting
    objectName: "page_setting"
    width: 1280
    height: 800

    property bool debug_use_ip: true
    property bool is_admin: false
    property bool is_rainbow: false
    property string select_category: "status"
    property string platform_name: supervisor.getRobotName()
    property int motor_left_id: 1
    property int motor_right_id: 0
    property int cur_preset: -1
    property bool is_reset_slam: false
    property bool use_tray: false
    property bool use_multirobot: false
    property bool wifi_update_auto: true
    property var debug_count: 0


    function update_camera(){
        if(popup_camera.opened)
            popup_camera.update();
    }
    function wifi_set_failed(){
        popup_loading.close();
        init();
    }
    function git_failed(){
        popup_loading.close();
        popup_update.failed();
    }
    function git_newest(){
        popup_loading.close();
        popup_update.newest();
    }

    function wifistatein(){
        popup_loading.close();
        popup_wifi.connection = supervisor.getWifiConnection(popup_wifi.select_ssd);
    }
    function wifi_con_failed(){
        popup_loading.close();
        popup_wifi.connect_fail();
    }
    function wifi_con_success(){
        popup_loading.close();
        init();
        popup_wifi.connection = supervisor.getWifiConnection(popup_wifi.select_ssd);
        popup_wifi.ip_update();
    }

    onIs_adminChanged: {
        if(is_admin){
            init();
        }
    }

    Component.onCompleted: {
        statusbar.visible = true;
        is_admin = false;
        is_rainbow = false;
        is_reset_slam = false;
        supervisor.getAllWifiList();
        supervisor.getWifiIP();
        supervisor.requestSystemVolume();
        init();
    }

    function set_category(num){
        select_category = num;
    }

    function set_call_done(){
        popup_change_call.close();
    }

    Tool_KeyPad{
        id: keypad
    }

    Tool_Keyboard{
        id: keyboard
    }

    Audio{
        id: voice_test
        autoPlay: false
        volume: slider_volume_voice.value/100
        source: supervisor.getVoice("start_serving");
        property bool isplaying: false
        onStopped: {
            isplaying = false;
        }
        onPlaying:{
            isplaying = true;
        }
    }
    Audio{
        id: bgm_test
        property bool isplaying: false
        autoPlay: false
        volume: slider_volume_bgm.value/100
        source: "bgm/song.mp3"
        onPlaying: {
            isplaying = true;
        }
        onStopped: {
            isplaying = false;
        }
    }


    Rectangle{
        id: dfdfd
        width: parent.width
        height: parent.height-statusbar.height
        anchors.bottom: parent.bottom
        color: "#f4f4f4"
        //카테고리 바
        Row{
            id: row_category
            spacing: 5
            Rectangle{
                width: 250
                height: 50
                color: "#323744"
                Text{
                    anchors.centerIn: parent
                    font.family: font_noto_r.name
                    color: "white"
                    text: "설정"
                    font.pixelSize: 25
                }
                MouseArea{
                    anchors.fill: parent
                    onDoubleClicked:{
                        click_sound.play();
                        popup_password.open();
                    }
                }
            }
            Rectangle{
                id: rect_category_1
                width: 240
                height: 50
                color: "#647087"
                Text{
                    anchors.centerIn: parent
                    font.family: font_noto_r.name
                    color: "white"
                    text: "현재상태"
                    font.pixelSize: 25
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                       click_sound.play();
                       select_category = "status";
                    }
                }
                Rectangle{
                    width: parent.width
                    height: 7
                    visible: select_category==="status" ? true : false
                    color: "#12d27c"
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: parent.bottom
                }
            }
            Rectangle{
                id: rect_category_2
                width: 240
                height: 50
                color: "#647087"
                Text{
                    anchors.centerIn: parent
                    font.family: font_noto_r.name
                    color: "white"
                    text: "로봇"
                    font.pixelSize: 25
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        click_sound.play();
                       select_category = "robot";
                    }
                }
                Rectangle{
                    width: parent.width
                    height: 7
                    visible: select_category === "robot" ? true : false
                    color: "#12d27c"
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: parent.bottom
                }
            }
            Rectangle{
                id: rect_category_3
                width: 264
                height: 50
                visible: is_admin || is_rainbow
                color: "#647087"
                Text{
                    anchors.centerIn: parent
                    font.family: font_noto_r.name
                    color: "white"
                    text: "주행"
                    font.pixelSize: 25
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        click_sound.play();
                       select_category = "moving";
                    }
                }
                Rectangle{
                    width: parent.width
                    height: 7
                    visible: select_category === "moving" ? true : false
                    color: "#12d27c"
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: parent.bottom
                }
            }
            Rectangle{
                id: rect_category_4
                width: 240
                height: 50
                color: "#647087"
                visible: is_admin || is_rainbow
                Text{
                    anchors.centerIn: parent
                    font.family: font_noto_r.name
                    color: "white"
                    text: "인식"
                    font.pixelSize: 25
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        click_sound.play();
                       select_category = "slam";
                    }
                }
                Rectangle{
                    width: parent.width
                    height: 7
                    visible: select_category === "slam" ? true : false
                    color: "#12d27c"
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: parent.bottom
                }
            }
        }

        Flickable{
            id: area_setting_robot
            visible: select_category === "robot" ? true : false
            width: 880
            anchors.left: parent.left
            anchors.leftMargin: 100
            anchors.top: parent.top
            anchors.topMargin: 120
            height: parent.height - 200
            contentHeight: column_setting.height
            clip: true
            ScrollBar.vertical: ScrollBar{
                width: 20
                anchors.right: parent.right
                policy: ScrollBar.AlwaysOn
            }
            Column{
                id:column_setting
                width: parent.width
                spacing:10
                Rectangle{
                    width: 1100
                    height: 40
                    color: "black"
                    anchors.horizontalCenter: parent.horizontalCenter
                    Text{
                        anchors.centerIn: parent
                        font.family: font_noto_b.name
                        text:"로봇 기본 정보"
                        color: "white"
                        font.pixelSize: 20
                    }
                }
                Rectangle{
                    id: set_robot_1
                    width: 840
                    height: 50
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"플랫폼 이름 (영문)"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                            Item_buttons{
                                type: "circle_text"
                                width: parent.height*0.8
                                height: width
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.right: parent.right
                                anchors.rightMargin: 20
                                text: "?"
                                onClicked:{
                                    click_sound.play();
                                    popup_help_setting.open();
                                    popup_help_setting.setTitle("플랫폼 이름");
                                    popup_help_setting.addLine("플랫폼을 지칭하는 이름을 적어주세요");
                                    popup_help_setting.addLine("반드시 영문이어야 합니다");
                                    popup_help_setting.addLine("한글이나 특수문자가 들어가면 로봇이 움직이지 않을 수 있습니다");
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            TextField{
                                id: platform_name
                                anchors.fill: parent
                                horizontalAlignment: TextField.AlignHCenter
                                text:supervisor.getSetting("setting","ROBOT_TYPE","model");
                                property bool ischanged: false
                                onTextChanged: {
                                    ischanged = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        keyboard.owner = platform_name;
                                        keyboard.owner_text = "platform_name";
                                        platform_name.selectAll();

                                        if(!keyboard.opened){
                                            keyboard.open();
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                Rectangle{
                    id: set_robot_1_serial
                    width: 840
                    height: 50
                    visible: use_multirobot
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"플랫폼 넘버 (중복주의)"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                            Item_buttons{
                                type: "circle_text"
                                width: parent.height*0.8
                                height: width
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.right: parent.right
                                anchors.rightMargin: 20
                                text: "?"
                                onClicked:{
                                    click_sound.play();
                                    popup_help_setting.open();
                                    popup_help_setting.setTitle("플랫폼 넘버");
                                    popup_help_setting.addLine("로봇을 여러대 구동하며 동일한 로봇 이름을 사용하는 경우 사용합니다");
                                    popup_help_setting.addLine("로봇을 여러대 구동할 경우 각각 지정해줘야 합니다");
                                    popup_help_setting.addLine("각 로봇의 이름을 다르게 지정한 경우 지정하지 않으셔도 됩니다");
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            ComboBox{
                                id: combo_platform_serial
                                anchors.fill: parent
                                property bool ischanged: false
                                onCurrentIndexChanged: {
                                    ischanged = true;
                                }
                                model:[0,1,2,3,4,5,6,7,8,9,10]
                            }
                        }
                    }
                }

                Rectangle{
                    id: set_robot_2
                    width: 840
                    height: 50
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"플랫폼 타입"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                            Item_buttons{
                                type: "circle_text"
                                width: parent.height*0.8
                                height: width
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.right: parent.right
                                anchors.rightMargin: 20
                                text: "?"
                                onClicked:{
                                    click_sound.play();
                                    popup_help_setting.open();
                                    popup_help_setting.setTitle("플랫폼 타입");
                                    popup_help_setting.addLine("지정하기 전, 지원되는 모델인지 확인하세요");
                                    popup_help_setting.addLine("서빙용 : 호출기능을 사용하지 않고 각 테이블을 서빙만 합니다");
                                    popup_help_setting.addLine("호출용 : 서빙기능을 사용하지 않고 로봇이 대기하다가 호출이 울리면 이동합니다");
                                    popup_help_setting.addLine("서빙+호출용 : 서빙기능과 호출기능을 동시에 사용합니다 서빙을 우선적으로 진행합니다");
                                    popup_help_setting.addLine("퇴식전용 : 서빙+호출용과 동일하지만 서빙(호출)위치를 다녀온 뒤 퇴식위치로 이동합니다");
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            ComboBox{
                                id: combo_platform_type
                                anchors.fill: parent
                                property bool ischanged: false
                                onCurrentIndexChanged: {
                                    ischanged = true;
                                }
                                model:["서빙용","호출용","서빙+호출용", "퇴식전용"]
                            }
                        }
                    }
                }

                Rectangle{
                    width: 1100
                    height: 40
                    color: "black"
                    anchors.horizontalCenter: parent.horizontalCenter
                    Text{
                        anchors.centerIn: parent
                        font.family: font_noto_b.name
                        text:"기능 설정"
                        color: "white"
                        font.pixelSize: 20
                    }
                }
                Rectangle{
                    id: set_preset
                    width: 840
                    height: 50
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"이동 속도"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                            Item_buttons{
                                type: "circle_text"
                                width: parent.height*0.8
                                height: width
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.right: parent.right
                                anchors.rightMargin: 20
                                text: "?"
                                onClicked:{
                                    click_sound.play();
                                    popup_help_setting.open();
                                    popup_help_setting.setTitle("이동 속도 (프리셋)");
                                    popup_help_setting.addLine("이동속도는 5단계로 분류됩니다");
                                    popup_help_setting.addLine("각각의 이동속도와 이름을 변경하실 수도 있습니다");
                                    popup_help_setting.addLine("안전속도맵을 사용하시는 경우, 기본 프리셋 기준 아주느리게, 느리게로 지정됩니다");
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            Row{
                                anchors.centerIn: parent
                                spacing: 5
                                Rectangle{
                                    width:70
                                    height: 50
                                    anchors.verticalCenter: parent.verticalCenter
                                    radius: 5
                                    Text{
                                        id: text_preset_name_1
                                        anchors.centerIn: parent
                                        text: "preset 1"
                                        font.family: font_noto_r.name
                                        font.pixelSize: 13
                                        color: cur_preset===1?color_green:color_mid_black
                                    }
                                    MouseArea{
                                        anchors.fill: parent
                                        onClicked:{
                                            click_sound.play();
                                            cur_preset = 1;
                                        }
                                    }
                                }
                                Rectangle{
                                    width:1
                                    height: 45
                                    radius: 1
                                    anchors.verticalCenter: parent.verticalCenter
                                    color: color_gray
                                }
                                Rectangle{
                                    width:70
                                    height: 50
                                    anchors.verticalCenter: parent.verticalCenter
                                    radius: 5
                                    Text{
                                        id: text_preset_name_2
                                        anchors.centerIn: parent
                                        text: "preset 2"
                                        font.family: font_noto_r.name
                                        font.pixelSize: 13
                                        color: cur_preset===2?color_green:color_mid_black
                                    }
                                    MouseArea{
                                        anchors.fill: parent
                                        onClicked:{
                                            click_sound.play();
                                            cur_preset = 2
                                        }
                                    }
                                }
                                Rectangle{
                                    width:1
                                    height: 45
                                    radius: 1
                                    anchors.verticalCenter: parent.verticalCenter
                                    color: color_gray
                                }
                                Rectangle{
                                    width:70
                                    anchors.verticalCenter: parent.verticalCenter
                                    height: 45
                                    radius: 5
                                    Text{
                                        id: text_preset_name_3
                                        anchors.centerIn: parent
                                        text: "preset 3"
                                        font.family: font_noto_r.name
                                        font.pixelSize: 13
                                        color: cur_preset===3?color_green:color_mid_black
                                    }
                                    MouseArea{
                                        anchors.fill: parent
                                        onClicked:{
                                            click_sound.play();
                                            cur_preset = 3
                                        }
                                    }
                                }
                                Rectangle{
                                    width:1
                                    height: 45
                                    anchors.verticalCenter: parent.verticalCenter
                                    radius: 1
                                    color: color_gray
                                }
                                Rectangle{
                                    width:70
                                    height: 45
                                    anchors.verticalCenter: parent.verticalCenter
                                    radius: 5
                                    Text{
                                        id: text_preset_name_4
                                        anchors.centerIn: parent
                                        text: "preset 4"
                                        font.family: font_noto_r.name
                                        font.pixelSize: 13
                                        color: cur_preset===4?color_green:color_mid_black
                                    }
                                    MouseArea{
                                        anchors.fill: parent
                                        onClicked:{
                                            click_sound.play();
                                            cur_preset = 4

                                        }
                                    }
                                }
                                Rectangle{
                                    width:1
                                    height: 45
                                    radius: 1
                                    anchors.verticalCenter: parent.verticalCenter
                                    color: color_gray
                                }
                                Rectangle{
                                    width:70
                                    height: 50
                                    anchors.verticalCenter: parent.verticalCenter
                                    radius: 5
                                    Text{
                                        id: text_preset_name_5
                                        anchors.centerIn: parent
                                        text: "preset 5"
                                        font.family: font_noto_r.name
                                        font.pixelSize: 13
                                        color: cur_preset===5?color_green:color_mid_black
                                    }
                                    MouseArea{
                                        anchors.fill: parent
                                        onClicked:{
                                            click_sound.play();
                                            cur_preset = 5
                                        }
                                    }
                                }
                                Rectangle{
                                    width:1
                                    height: 45
                                    radius: 1
                                    anchors.verticalCenter: parent.verticalCenter
                                    color: color_gray
                                }
                                Rectangle{
                                    width : 60
                                    height: 45
                                    anchors.verticalCenter: parent.verticalCenter
                                    radius: 5
                                    color: color_dark_navy
                                    Text{
                                        anchors.centerIn: parent
                                        text: "변경"
                                        color: "white"
                                        font.family: font_noto_r.name
                                        font.pixelSize: 13
                                    }
                                    MouseArea{
                                        anchors.fill: parent
                                        onClicked:{
                                            click_sound.play();
                                            popup_preset.select_preset = cur_preset;
                                            popup_preset.open();
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                Rectangle{
                    id: set_comeback_preset
                    width: 840
                    height: 50
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"복귀 속도 지정"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                            Item_buttons{
                                type: "circle_text"
                                width: parent.height*0.8
                                height: width
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.right: parent.right
                                anchors.rightMargin: 20
                                text: "?"
                                onClicked:{
                                    click_sound.play();
                                    popup_help_setting.open();
                                    popup_help_setting.setTitle("복귀 속도 지정");
                                    popup_help_setting.addLine("로봇이 서빙 후 대기위치로 이동할 때 속도를 지정합니다");
                                    popup_help_setting.addLine("사용하지 않으면 서빙 때 지정한 속도 그대로 사용합니다");
                                    popup_help_setting.addLine("안전속도 구간에 진입하면 속도가 자동으로 저하됩니다");
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            ComboBox{
                                id: combo_comeback_preset
                                anchors.fill: parent
                                property bool ischanged: false
                                onCurrentIndexChanged: {
                                    ischanged = true;
                                }
                                model:["사용 안함", "아주느리게","느리게", "보통", "빠르게", "아주빠르게"]
                            }
                        }
                    }
                }
                Rectangle{
                    id: set_robot_442
                    width: 840
                    height: 50
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"최대 호출 횟수"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                            Item_buttons{
                                type: "circle_text"
                                width: parent.height*0.8
                                height: width
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.right: parent.right
                                anchors.rightMargin: 20
                                text: "?"
                                onClicked:{
                                    popup_help_setting.open();
                                    popup_help_setting.setTitle("최대 호출 횟수");
                                    popup_help_setting.addLine("지정하기 전, 지원되는 모델인지 확인하세요");
                                    popup_help_setting.addLine("로봇이 한 번 이동에 호출되는 최대 횟수입니다");
                                    popup_help_setting.addLine("대기 위치에서 출발한 뒤 해당 횟수만큼 테이블을 이동하면");
                                    popup_help_setting.addLine("추가적인 호출명령이 있어도 우선 대기위치로 돌아옵니다");
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            ComboBox{
                                id: combo_max_calling
                                anchors.fill: parent
                                property bool ischanged: false
                                onCurrentIndexChanged: {
                                    ischanged = true;
                                }
                                model:[1,2,3,4,5,6,7,8,9]
                            }
                        }
                    }
                }
                Rectangle{
                    id: set_call_notice
                    width: 840
                    height: 50
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"호출복귀 후 재정비"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            ComboBox{
                                id: combo_use_calling_notice
                                anchors.fill: parent
                                property bool ischanged: false
                                onCurrentIndexChanged: {
                                    ischanged = true;
                                }
                                model:["사용안함", "사용"]

                            }
                        }
                    }
                }
                Rectangle{
                    id: set_resting_lock
                    width: 840
                    height: 50
                    visible: false//is_admin
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"대기장소 모터 락 해제"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                            Item_buttons{
                                type: "circle_text"
                                width: parent.height*0.8
                                height: width
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.right: parent.right
                                anchors.rightMargin: 20
                                text: "?"
                                onClicked:{
                                    click_sound.play();
                                    popup_help_setting.open();
                                    popup_help_setting.setTitle("대기장소 모터 락 해제");
                                    popup_help_setting.addLine("로봇이 대기장소에서 대기하고 있을 때 사람이 밀어서 움직일 수 있는지 설정합니다");
                                    popup_help_setting.addLine("매장 바닥 상황에 따라 로봇이 굴러서 저절로 이동할 수 있으니 기본적으론 사용 안함으로 이용해주세요");
                                    popup_help_setting.addLine("사용 시에도 서빙을 보내기 전 대기장소와 너무 떨어지지 않도록 유의해주세요");
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            ComboBox{
                                id: combo_resting_lock
                                anchors.fill: parent
                                property bool ischanged: false
                                onCurrentIndexChanged: {
                                    ischanged = true;
                                }
                                model:["사용안함", "사용"]

                            }
                        }
                    }
                }
                Rectangle{
                    id: set_auto_update
                    width: 840
                    height: 50
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"시작시 업데이트 검사"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            ComboBox{
                                id: combo_auto_update
                                anchors.fill: parent
                                property bool ischanged: false
                                onCurrentIndexChanged: {
                                    ischanged = true;
                                }
                                model:["사용 안함", "사용"]
                            }
                        }
                    }
                }

                Rectangle{
                    width: 1100
                    height: 40
                    color: "black"
                    anchors.horizontalCenter: parent.horizontalCenter
                    Text{
                        anchors.centerIn: parent
                        font.family: font_noto_b.name
                        text:"UI 설정"
                        color: "white"
                        font.pixelSize: 20
                    }
                }
                Rectangle{
                    id: set_use_tray
                    width: 840
                    height: 50
                    visible: is_admin
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"트레이 별 서빙"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                            Item_buttons{
                                type: "circle_text"
                                width: parent.height*0.8
                                height: width
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.right: parent.right
                                anchors.rightMargin: 20
                                text: "?"
                                onClicked:{
                                    click_sound.play();
                                    popup_help_setting.open();
                                    popup_help_setting.setTitle("트레이 별 서빙");
                                    popup_help_setting.addLine("트레이 별로 각각의 서빙위치를 지정하려면 사용하세요");
                                    popup_help_setting.addLine("사용할 경우 서빙순서는 1번 트레이를 우선으로 이동합니다");
                                    popup_help_setting.addLine("대기화면이 변경되며 그룹을 사용하지 않고 각 테이블 번호로 이동합니다");
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            ComboBox{
                                id: combo_use_tray
                                anchors.fill: parent
                                property bool ischanged: false
                                onCurrentIndexChanged: {
                                    ischanged = true;
                                    if(currentIndex == 0){
                                        use_tray = false;
                                    }else{
                                        use_tray = true;
                                    }
                                }
                                model:["사용안함", "사용"]

                            }
                        }
                    }
                }
                Rectangle{
                    id: set_tray_num
                    width: 840
                    height: 50
                    visible: is_rainbow && use_tray
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"트레이 개수"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            ComboBox{
                                id: combo_tray_num
                                anchors.fill: parent
                                property bool ischanged: false
                                onCurrentIndexChanged: {
                                    ischanged = true;
                                }
                                model:[1,2,3]
                            }
                        }
                    }
                }
                Rectangle{
                    id: set_language
                    width: 840
                    height: 50
                    visible: false
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"언어"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            ComboBox{
                                id: combo_language
                                anchors.fill: parent
                                property bool ischanged: false
                                onCurrentIndexChanged: {
                                    ischanged = true;
                                }
                                model:["한국어", "영어"]
                            }
                        }
                    }
                }
                Rectangle{
                    id: set_movingpage
                    width: 840
                    height: 50
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"이동 중 화면"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                            Item_buttons{
                                type: "circle_text"
                                width: parent.height*0.8
                                height: width
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.right: parent.right
                                anchors.rightMargin: 20
                                text: "?"
                                onClicked:{
                                    click_sound.play();
                                    popup_help_setting.open();
                                    popup_help_setting.setTitle("이동 중 화면");
                                    popup_help_setting.addLine("로봇이 이동 중에 화면에 표시될 것을 고르세요");
                                    popup_help_setting.addLine("목적지 표시 : 목적지가 화면에 표시됩니다");
                                    popup_help_setting.addLine("귀여운 얼굴 : 귀여운 표정이 화면 가득 표시됩니다");
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            ComboBox{
                                id: combo_movingpage
                                anchors.fill: parent
                                property bool ischanged: false
                                onCurrentIndexChanged: {
                                    ischanged = true;
                                }
                                model:["목적지 표시", "귀여운 얼굴"]
                            }
                        }
                    }
                }
                Rectangle{
                    id: set_voice_mode
                    width: 840
                    height: 50
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"음성"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            ComboBox{
                                id: combo_voice_mode
                                anchors.fill: parent
                                property bool ischanged: false
                                onCurrentIndexChanged: {
                                    ischanged = true;
                                    if(currentIndex == 0){
                                        voice_test.source = supervisor.getVoice("start_serving","child");
                                    }else if(currentIndex == 1){
                                        voice_test.source = supervisor.getVoice("start_serving","woman");
                                    }
                                }
                                model:["어린이", "여성"]
                            }
                        }
                    }
                }
                Rectangle{
                    id: set_system_volume
                    width: 840
                    height: 50
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"시스템 볼륨"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            id: tt
                            width: parent.width - 351
                            height: parent.height
                            Row{
                                spacing: 10
                                anchors.centerIn: parent
                                Image{
                                    id: ttet12
                                    source: "icon/icon_mute.png"
                                    anchors.verticalCenter: parent.verticalCenter
                                    MouseArea{
                                        anchors.fill: parent
                                        onClicked: {
                                            click_sound.play();
                                            if(slider_volume_system.value == 0){
                                                slider_volume_system.value  = 50;
                                            }else{
                                                slider_volume_system.value  = 0;
                                            }
                                            supervisor.setSystemVolume(slider_volume_system.value);

                                        }
                                    }
                                }
                                Slider{
                                    anchors.verticalCenter: parent.verticalCenter
                                    id: slider_volume_system
//                                    anchors.centerIn: parent
                                    width: tt.width*0.7 + 10 + ttet2132.width
                                    height: 50
                                    from: 0
                                    to: 100
                                    property bool ischanged: false
                                    onValueChanged: {
                                        ischanged = true;
                                    }
                                    value: supervisor.getSystemVolume()
                                    onPressedChanged: {
                                        if(!pressed){
                                            supervisor.setSystemVolume(slider_volume_system.value);
                                            click_sound.play();
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                Rectangle{
                    id: set_bgm_volume
                    width: 840
                    height: 50
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"음악 볼륨"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            id: tte32
                            width: parent.width - 351
                            height: parent.height
                            Row{
                                spacing: 10
                                anchors.centerIn: parent
                                Image{
                                    id: ttet1
                                    source: "icon/icon_mute.png"
                                    anchors.verticalCenter: parent.verticalCenter
                                    MouseArea{
                                        anchors.fill: parent
                                        onClicked: {
                                            click_sound.play();
                                            if(slider_volume_bgm.value == 0){
                                                slider_volume_bgm.value  = Number(supervisor.getSetting("setting","UI","volume_bgm"));
                                            }else{
                                                slider_volume_bgm.value  = 0;
                                            }

                                        }
                                    }
                                }
                                Slider{
                                    anchors.verticalCenter: parent.verticalCenter
                                    id: slider_volume_bgm
//                                    anchors.centerIn: parent
                                    width: tt.width*0.7
                                    height: 50
                                    from: 0
                                    to: 100
                                    property bool ischanged: false
                                    onValueChanged: {
                                        ischanged = true;
                                    }
                                    value: supervisor.getSetting("setting","UI","volume_bgm")
                                }

                                Image{
                                    id: ttet2132
                                    source: "icon/icon_test_play.png"
                                    anchors.verticalCenter: parent.verticalCenter
                                    MouseArea{
                                        anchors.fill: parent
                                        onClicked: {
                                            click_sound.play();
                                            if(bgm_test.isplaying){
                                                bgm_test.stop();
                                                ttet2132.source = "icon/icon_test_play.png";
                                            }else{
                                                bgm_test.play();
                                                ttet2132.source = "icon/icon_test_stop.png";
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                Rectangle{
                    id: set_voice_volume
                    width: 840
                    height: 50
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"음성 볼륨"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }

                        Rectangle{
                            id: te
                            width: parent.width - 351
                            height: parent.height
                            Row{
                                spacing: 10
                                anchors.centerIn: parent
                                Image{
                                    id: ttet124
                                    anchors.verticalCenter: parent.verticalCenter
                                    source: "icon/icon_mute.png"
                                    MouseArea{
                                        anchors.fill: parent
                                        onClicked: {
                                            click_sound.play();
                                            if(slider_volume_voice.value == 0){
                                                slider_volume_voice.value  = Number(supervisor.getSetting("setting","UI","volume_voice"));
                                            }else{
                                                slider_volume_voice.value  = 0;
                                            }
                                        }
                                    }
                                }
                                Slider{
                                    anchors.verticalCenter: parent.verticalCenter
                                    id: slider_volume_voice
                                    width: te.width*0.7
                                    height: 50
                                    from: 0
                                    to: 100
                                    property bool ischanged: false
                                    onValueChanged: {
                                        ischanged = true;
                                    }
                                    value: supervisor.getSetting("setting","UI","volume_voice")
                                }
                                Image{
                                    id: ttet14
                                    anchors.verticalCenter: parent.verticalCenter
                                    source: "icon/icon_test_play.png"
                                    MouseArea{
                                        anchors.fill: parent
                                        onClicked: {
                                            click_sound.play();
                                            print("test play")
                                            voice_test.play();
                                        }
                                    }
                                }
                            }
                        }
                    }
                }

                Rectangle{
                    id: set_voice_button
                    width: 840
                    height: 50
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"버튼클릭 볼륨"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }

                        Rectangle{
                            id: te3
                            width: parent.width - 351
                            height: parent.height
                            Row{
                                spacing: 10
                                anchors.centerIn: parent
                                Image{
                                    anchors.verticalCenter: parent.verticalCenter
                                    source: "icon/icon_mute.png"
                                    MouseArea{
                                        anchors.fill: parent
                                        onClicked: {
                                            click_sound.play();
                                            if(slider_volume_button.value == 0){
                                                slider_volume_button.value  = Number(supervisor.getSetting("setting","UI","volume_button"));
                                            }else{
                                                slider_volume_button.value  = 0;
                                            }
                                        }
                                    }
                                }
                                Slider{
                                    anchors.verticalCenter: parent.verticalCenter
                                    id: slider_volume_button
                                    width: te.width*0.7
                                    height: 50
                                    from: 0
                                    to: 100
                                    property bool ischanged: false
                                    onValueChanged: {
                                        ischanged = true;
                                        volume_button = value;
                                    }
                                    value: supervisor.getSetting("setting","UI","volume_button")
                                }
                                Image{
                                    anchors.verticalCenter: parent.verticalCenter
                                    source: "icon/icon_test_play.png"
                                    MouseArea{
                                        anchors.fill: parent
                                        onClicked: {
                                            start_sound.play();
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                Rectangle{
                    id: set_tableview
                    width: 840
                    height: 50
                    visible: false
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"테이블 표시"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            ComboBox{
                                id: combo_tableview
                                anchors.fill: parent
                                property bool ischanged: false
                                onCurrentIndexChanged: {
                                    ischanged = true;
                                }
                                model:["테이블 번호로 표시", "테이블 별칭으로 표시", "테이블 맵으로 표시(설정 필요)"]
                            }
                        }
                    }
                }

                Rectangle{
                    width: 1100
                    height: 40
                    visible: is_admin
                    color: "black"
                    anchors.horizontalCenter: parent.horizontalCenter
                    Text{
                        anchors.centerIn: parent
                        font.family: font_noto_b.name
                        text:"멀티로봇"
                        color: "white"
                        font.pixelSize: 20
                    }
                }
                Rectangle{
                    id: set_use_multirobot
                    width: 840
                    visible: is_admin
                    height: 50
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"멀티로봇 사용"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            ComboBox{
                                id: combo_multirobot
                                anchors.fill: parent
                                property bool ischanged: false
                                onCurrentIndexChanged: {
                                    ischanged = true;
                                    if(currentIndex == 0){
                                        use_multirobot = false;
                                    }else{
                                        use_multirobot = true;
                                    }
                                }
                                model:["사용안함","사용"]
                            }
                        }
                    }
                }

                Rectangle{
                    id: set_use_server_call
                    width: 840
                    visible: is_admin && use_multirobot
                    height: 50
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"서버 호출 사용"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            ComboBox{
                                id: combo_server_calling
                                anchors.fill: parent
                                property bool ischanged: false
                                onCurrentIndexChanged: {
                                    ischanged = true;
                                }
                                model:["사용안함","사용"]
                            }
                        }
                    }
                }
                Rectangle{
                    id: set_server_ip
                    width: 840
                    visible: is_admin && use_multirobot
                    height: 50
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"서버 IP"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }

                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            Row{
                                spacing: 10
                                anchors.centerIn: parent
                                TextField{
                                    id: server_ip_1
                                    width: 70
                                    height: 50
                                    MouseArea{
                                        anchors.fill:parent
                                        onClicked: {
                                            if(keypad.is_opened){
                                                keypad.owner = server_ip_1;
                                                server_ip_1.selectAll();
                                            }else{
                                                keypad.owner = server_ip_1;
                                                server_ip_1.selectAll();
                                                keypad.open();
                                            }
                                        }
                                    }
                                    color: ischanged?color_red:"black"
                                    property bool ischanged: false
                                    onTextChanged: {
                                        ischanged = true;
                                        if(server_ip_1.text.split(".").length > 1){
                                            server_ip_1.text = server_ip_1.text.split(".")[0];
                                            server_ip_2.selectAll();
                                            keypad.owner = server_ip_2;
                                        }
                                        if(server_ip_1.text.length == 3){
                                            server_ip_2.selectAll();
                                            keypad.owner = server_ip_2;
                                        }
                                    }
                                }
                                Text{
                                    anchors.verticalCenter: parent.verticalCenter
                                    text:"."
                                }

                                TextField{
                                    id: server_ip_2
                                    width: 70
                                    height: 50
                                    MouseArea{
                                        anchors.fill:parent
                                        onClicked: {
                                            if(keypad.is_opened){
                                                keypad.owner = server_ip_2;
                                                server_ip_2.selectAll();
                                            }else{
                                                keypad.owner = server_ip_2;
                                                server_ip_2.selectAll();
                                                keypad.open();
                                            }
                                        }
                                    }
                                    color: ischanged?color_red:"black"
                                    property bool ischanged: false
                                    onTextChanged: {
                                        ischanged = true;
                                        if(server_ip_2.text == "."){
                                            server_ip_2.text = server_ip_2.text.split(".")[0]
                                        }

                                        if(server_ip_2.text.split(".").length > 1){
                                            server_ip_2.text = server_ip_2.text.split(".")[0];
                                            server_ip_3.selectAll();
                                            keypad.owner = server_ip_3;
                                        }
                                        if(server_ip_2.text.length == 3){
                                            server_ip_3.selectAll();
                                            keypad.owner = server_ip_3;
                                        }
                                    }
                                }
                                Text{
                                    anchors.verticalCenter: parent.verticalCenter
                                    text:"."
                                }
                                TextField{
                                    id: server_ip_3
                                    width: 70
                                    height: 50
                                    MouseArea{
                                        anchors.fill:parent
                                        onClicked: {
                                            if(keypad.is_opened){
                                                keypad.owner = server_ip_3;
                                                server_ip_3.selectAll();
                                            }else{
                                                keypad.owner = server_ip_3;
                                                server_ip_3.selectAll();
                                                keypad.open();
                                            }
                                        }
                                    }
                                    color: ischanged?color_red:"black"
                                    property bool ischanged: false
                                    onTextChanged: {
                                        ischanged = true;
                                        if(server_ip_3.text == "."){
                                            server_ip_3.text = server_ip_3.text.split(".")[0]
                                        }

                                        if(server_ip_3.text.split(".").length > 1){
                                            server_ip_3.text = server_ip_3.text.split(".")[0];
                                            server_ip_4.selectAll();
                                            keypad.owner = server_ip_4;
                                        }
                                        if(server_ip_3.text.length == 3){
                                            server_ip_4.selectAll();
                                            keypad.owner = server_ip_4;
                                        }
                                    }
                                }
                                Text{
                                    anchors.verticalCenter: parent.verticalCenter
                                    text:"."
                                }
                                TextField{
                                    id: server_ip_4
                                    width: 70
                                    height: 50
                                    MouseArea{
                                        anchors.fill:parent
                                        onClicked: {
                                            if(keypad.is_opened){
                                                keypad.owner = server_ip_4;
                                                server_ip_4.selectAll();
                                            }else{
                                                keypad.owner = server_ip_4;
                                                server_ip_4.selectAll();
                                                keypad.open();
                                            }
                                        }
                                    }
                                    color: ischanged?color_red:"black"
                                    property bool ischanged: false
                                    onTextChanged: {
                                        ischanged = true;
                                        if(server_ip_4.text == "."){
                                            server_ip_4.text = server_ip_4.text.split(".")[0]
                                        }

                                        if(server_ip_4.text.split(".").length > 1){
                                            server_ip_4.text = server_ip_4.text.split(".")[0];
                                            keypad.close();
                                        }
                                        if(server_ip_4.text.length == 3){
                                            keypad.close();
                                        }
                                    }
                                }

                                Rectangle{
                                    height: parent.height
                                    width: parent.width*0.2
                                    radius: 5
                                    color: "black"
                                    Text{
                                        anchors.centerIn: parent
                                        color: "white"
                                        font.family: font_noto_r.name
                                        text: "변경"
                                    }
                                    MouseArea{
                                        anchors.fill: parent
                                        onClicked:{
                                            click_sound.play();
                                            server_ip_1.ischanged = false;
                                            server_ip_2.ischanged = false;
                                            server_ip_3.ischanged = false;
                                            server_ip_4.ischanged = false;
                                            var ip_str = server_ip_1.text + "." + server_ip_2.text + "." + server_ip_3.text + "." + server_ip_4.text;
                                            supervisor.setSetting("setting","SERVER/fms_ip",ip_str);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                Rectangle{
                    id: set_server_id
                    width: 840
                    height: 50
                    visible: is_admin && use_multirobot
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"FMS 아이디"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            TextField{
                                id: fms_id
                                anchors.fill: parent
                                property bool ischanged: false
                                onTextChanged: {
                                    ischanged = true;
                                    is_reset_slam = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        if(keyboard.is_opened){
                                            keyboard.owner = fms_id;
                                            fms_id.selectAll();
                                        }else{
                                            keyboard.owner = fms_id;
                                            fms_id.selectAll();
                                            keyboard.open();
                                        }
                                    }
                                }
                                color: ischanged?color_red:"black"
                                text:supervisor.getSetting("setting","SERVER","fms_id");
                            }
                        }
                    }
                }
                Rectangle{
                    id: set_server_pw
                    width: 840
                    height: 50
                    visible: is_admin &&  use_multirobot
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"FMS 비밀번호"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            TextField{
                                id: fms_pw
                                anchors.fill: parent
                                property bool ischanged: false
                                onTextChanged: {
                                    ischanged = true;
                                    is_reset_slam = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        if(keyboard.is_opened){
                                            keyboard.owner = fms_pw;
                                            fms_pw.selectAll();
                                        }else{
                                            keyboard.owner = fms_pw;
                                            fms_pw.selectAll();
                                            keyboard.open();
                                        }
                                    }
                                }
                                color: ischanged?color_red:"black"
                                text:supervisor.getSetting("setting","SERVER","fms_pw");

                            }
                        }
                    }
                }

                Rectangle{
                    width: 1100
                    height: 40
                    visible: is_admin
                    color: "black"
                    anchors.horizontalCenter: parent.horizontalCenter
                    Text{
                        anchors.centerIn: parent
                        font.family: font_noto_b.name
                        text:"로봇 하드웨어 설정"
                        color: "white"
                        font.pixelSize: 20
                    }
                }
                Rectangle{
                    id: set_robot_radius
                    width: 840
                    visible: is_admin
                    height: 50
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"로봇 반지름 반경 [m]"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            TextField{
                                id: radius
                                anchors.fill: parent
                                property bool ischanged: false
                                onTextChanged: {
                                    ischanged = true;
                                    is_reset_slam = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        if(keypad.is_opened){
                                            keypad.owner = radius;
                                            radius.selectAll();
                                        }else{
                                            keypad.owner = radius;
                                            radius.selectAll();
                                            keypad.open();
                                        }
                                    }
                                }
                                color: ischanged?color_red:"black"
                                text:supervisor.getSetting("static","ROBOT_HW","robot_radius");

                            }
                        }
                    }
                }
                Rectangle{
                    id: set_robot_length
                    width: 840
                    visible: is_admin
                    height: 50
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"로봇 길이 [m]"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            TextField{
                                id: robot_length
                                anchors.fill: parent
                                property bool ischanged: false
                                onTextChanged: {
                                    ischanged = true;
                                    is_reset_slam = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        if(keypad.is_opened){
                                            keypad.owner = robot_length;
                                            robot_length.selectAll();
                                        }else{
                                            keypad.owner = robot_length;
                                            robot_length.selectAll();
                                            keypad.open();
                                        }
                                    }
                                }
                                color: ischanged?color_red:"black"
                                text:supervisor.getSetting("static","ROBOT_HW","robot_length");

                            }
                        }
                    }
                }
                Rectangle{
                    id: set_wheelbase
                    width: 840
                    visible: is_admin
                    height: 50
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"휠 베이스 반경 [m]"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            TextField{
                                id: wheel_base
                                anchors.fill: parent
                                property bool ischanged: false
                                onTextChanged: {
                                    ischanged = true;
                                    is_reset_slam = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        if(keypad.is_opened){
                                            keypad.owner = wheel_base;
                                            wheel_base.selectAll();
                                        }else{
                                            keypad.owner = wheel_base;
                                            wheel_base.selectAll();
                                            keypad.open();
                                        }
                                    }
                                }
                                color: ischanged?color_red:"black"
                                text:supervisor.getSetting("static","ROBOT_HW","wheel_base");

                            }
                        }
                    }
                }
                Rectangle{
                    id: set_wheelradius
                    width: 840
                    height: 50
                    visible: is_admin
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"휠 반지름 반경 [m]"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            TextField{
                                id: wheel_radius
                                anchors.fill: parent
                                property bool ischanged: false
                                onTextChanged: {
                                    ischanged = true;
                                    is_reset_slam = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        if(keypad.is_opened){
                                            keypad.owner = wheel_radius;
                                            wheel_radius.selectAll();
                                        }else{
                                            keypad.owner = wheel_radius;
                                            wheel_radius.selectAll();
                                            keypad.open();
                                        }
                                    }
                                }
                                color: ischanged?color_red:"black"
                                text:supervisor.getSetting("setting","ROBOT_HW","wheel_radius");

                            }
                        }
                    }
                }

                Rectangle{
                    width: 1100
                    height: 40
                    visible: is_admin
                    color: "black"
                    anchors.horizontalCenter: parent.horizontalCenter
                    Text{
                        anchors.centerIn: parent
                        font.family: font_noto_b.name
                        text:"무선 와이파이 설정"
                        color: "white"
                        font.pixelSize: 20
                    }
                }
                Rectangle{
                    id: set_wifi
                    width: 840
                    visible: is_admin && debug_use_ip
                    height: 400
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 200
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"WIFI 연결상태"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 201
                            height: parent.height
                            Column{
                                anchors.centerIn: parent
                                spacing: 10
                                Rectangle{
                                    id: wifi_connection
                                    width: 500
                                    height: 50
                                    property int connection: 0
                                    color: {
                                        if(wifi_connection.connection === 1){
                                            color_yellow
                                        }else if(wifi_connection.connection === 2){
                                            color_yellow
                                        }else if(wifi_connection.connection === 3){
                                            color_green
                                        }else{
                                            color_red
                                        }
                                    }
                                    Text{
                                        anchors.centerIn: parent
                                        font.family:font_noto_r.name
                                        font.pixelSize:20
                                        text:{
                                            if(wifi_connection.connection === 1){
                                                "연결중"
                                            }else if(wifi_connection.connection === 2){
                                                "연결됨(인터넷 연결안됨)"
                                            }else if(wifi_connection.connection === 3){
                                                "연결됨"
                                            }else{
                                                "연결안됨"
                                            }
                                        }
                                        color: "white"
                                    }
                                }

                                Row{
                                    spacing: 5
                                    Rectangle{
                                        width: 150
                                        height: 50
                                        Text{
                                            anchors.verticalCenter: parent.verticalCenter
                                            anchors.left: parent.left
                                            anchors.leftMargin: 30
                                            font.family: font_noto_r.name
                                            text:"WIFI SSID"
                                            font.pixelSize: 20
                                            Component.onCompleted: {
                                                scale = 1;
                                                while(width*scale > parent.width*0.8){
                                                    scale=scale-0.01;
                                                }
                                            }
                                        }
                                    }
                                    Rectangle{
                                        width: 1
                                        height: 50
                                        color: "#d0d0d0"
                                    }
                                    Rectangle{
                                        width: 500-161
                                        height: 50
                                        Text{
                                            id: wifi_ssid
                                            anchors.centerIn: parent
                                            font.family: font_noto_r.name
                                            text:supervisor.getSetting("setting","NETWORK","wifi_ssid");
                                        }

                                    }
                                }

                                Row{
                                    spacing: 5
                                    Rectangle{
                                        width: 150
                                        height: 50
                                        Text{
                                            anchors.verticalCenter: parent.verticalCenter
                                            anchors.left: parent.left
                                            anchors.leftMargin: 30
                                            font.family: font_noto_r.name
                                            text:"IP"
                                            font.pixelSize: 20
                                            Component.onCompleted: {
                                                scale = 1;
                                                while(width*scale > parent.width*0.8){
                                                    scale=scale-0.01;
                                                }
                                            }
                                        }
                                    }
                                    Rectangle{
                                        width: 1
                                        height: 50
                                        color: "#d0d0d0"
                                    }

                                    Rectangle{
                                        width: 500-161
                                        height: 50
                                        Row{
                                            spacing: 10
                                            anchors.centerIn: parent
                                            TextField{
                                                id: ip_1
                                                width: 60
                                                height: 40
                                                horizontalAlignment: TextField.AlignHCenter
                                                MouseArea{
                                                    anchors.fill:parent
                                                    onClicked: {
                                                        if(keypad.is_opened){
                                                            keypad.owner = ip_1;
                                                            ip_1.selectAll();
                                                        }else{
                                                            keypad.owner = ip_1;
                                                            ip_1.selectAll();
                                                            keypad.open();
                                                        }
                                                    }
                                                }
                                                color: ischanged?color_red:"black"
                                                property bool ischanged: false
                                                onTextChanged: {
                                                    ischanged = true;
                                                    if(ip_1.text.split(".").length > 1){
                                                        ip_1.text = ip_1.text.split(".")[0];
                                                        ip_2.selectAll();
                                                        keypad.owner = ip_2;
                                                    }
                                                    if(ip_1.text.length == 3){
                                                        ip_2.selectAll();
                                                        keypad.owner = ip_2;
                                                    }
                                                }
                                            }
                                            Text{
                                                anchors.verticalCenter: parent.verticalCenter
                                                text:"."
                                            }

                                            TextField{
                                                id: ip_2
                                                width: 60
                                                height: 40
                                                horizontalAlignment: TextField.AlignHCenter
                                                MouseArea{
                                                    anchors.fill:parent
                                                    onClicked: {
                                                        if(keypad.is_opened){
                                                            keypad.owner = ip_2;
                                                            ip_2.selectAll();
                                                        }else{
                                                            keypad.owner = ip_2;
                                                            ip_2.selectAll();
                                                            keypad.open();
                                                        }
                                                    }
                                                }
                                                color: ischanged?color_red:"black"
                                                property bool ischanged: false
                                                onTextChanged: {
                                                    ischanged = true;
                                                    if(ip_2.text == "."){
                                                        ip_2.text = ip_2.text.split(".")[0]
                                                    }

                                                    if(ip_2.text.split(".").length > 1){
                                                        ip_2.text = ip_2.text.split(".")[0];
                                                        ip_3.selectAll();
                                                        keypad.owner = ip_3;
                                                    }
                                                    if(ip_2.text.length == 3){
                                                        ip_3.selectAll();
                                                        keypad.owner = ip_3;
                                                    }
                                                }
                                            }
                                            Text{
                                                anchors.verticalCenter: parent.verticalCenter
                                                text:"."
                                            }
                                            TextField{
                                                id: ip_3
                                                width: 60
                                                height: 40
                                                horizontalAlignment: TextField.AlignHCenter
                                                MouseArea{
                                                    anchors.fill:parent
                                                    onClicked: {
                                                        if(keypad.is_opened){
                                                            keypad.owner = ip_3;
                                                            ip_3.selectAll();
                                                        }else{
                                                            keypad.owner = ip_3;
                                                            ip_3.selectAll();
                                                            keypad.open();
                                                        }
                                                    }
                                                }
                                                color: ischanged?color_red:"black"
                                                property bool ischanged: false
                                                onTextChanged: {
                                                    ischanged = true;
                                                    if(ip_3.text == "."){
                                                        ip_3.text = ip_3.text.split(".")[0]
                                                    }

                                                    if(ip_3.text.split(".").length > 1){
                                                        ip_3.text = ip_3.text.split(".")[0];
                                                        ip_4.selectAll();
                                                        keypad.owner = ip_4;
                                                    }
                                                    if(ip_3.text.length == 3){
                                                        ip_4.selectAll();
                                                        keypad.owner = ip_4;
                                                    }
                                                }
                                            }
                                            Text{
                                                anchors.verticalCenter: parent.verticalCenter
                                                text:"."
                                            }
                                            TextField{
                                                id: ip_4
                                                width: 60
                                                height: 40
                                                horizontalAlignment: TextField.AlignHCenter
                                                MouseArea{
                                                    anchors.fill:parent
                                                    onClicked: {
                                                        if(keypad.is_opened){
                                                            keypad.owner = ip_4;
                                                            ip_4.selectAll();
                                                        }else{
                                                            keypad.owner = ip_4;
                                                            ip_4.selectAll();
                                                            keypad.open();
                                                        }
                                                    }
                                                }
                                                color: ischanged?color_red:"black"
                                                property bool ischanged: false
                                                onTextChanged: {
                                                    ischanged = true;
                                                    if(ip_4.text == "."){
                                                        ip_4.text = ip_4.text.split(".")[0]
                                                    }

                                                    if(ip_4.text.split(".").length > 1){
                                                        ip_4.text = ip_4.text.split(".")[0];
                                                        keypad.close();
                                                    }
                                                    if(ip_4.text.length == 3){
                                                        keypad.close();
                                                    }
                                                }
                                            }

                                            Rectangle{
                                                height: parent.height
                                                width: parent.width*0.2
                                                radius: 5
                                                visible: false
                                                color: "black"
                                                Text{
                                                    anchors.centerIn: parent
                                                    color: "white"
                                                    font.family: font_noto_r.name
                                                    text: "변경"
                                                }
                                                MouseArea{
                                                    anchors.fill: parent
                                                    onClicked:{
                                                        click_sound.play();
                                                        ip_1.ischanged = false;
                                                        ip_2.ischanged = false;
                                                        ip_3.ischanged = false;
                                                        ip_4.ischanged = false;
                                                        var ip_str = ip_1.text + "." + ip_2.text + "." + ip_3.text + "." + ip_4.text;
                                                        gateway_1.ischanged = false;
                                                        gateway_2.ischanged = false;
                                                        gateway_3.ischanged = false;
                                                        gateway_4.ischanged = false;
                                                        var gateway_str = gateway_1.text + "." + gateway_2.text + "." + gateway_3.text + "." + gateway_4.text;
                                                        dnsmain_1.ischanged = false;
                                                        dnsmain_2.ischanged = false;
                                                        dnsmain_3.ischanged = false;
                                                        dnsmain_4.ischanged = false;
                                                        var dns_str = dnsmain_1.text + "." + dnsmain_2.text + "." + dnsmain_3.text + "." + dnsmain_4.text;
                                                        supervisor.setWifi(ip_str,gateway_str,dns_str);
                                                        supervisor.setSetting("setting","NETWORK/wifi_ip",ip_str);
                                                        supervisor.setSetting("setting","NETWORK/wifi_gateway",gateway_str);
                                                        supervisor.setSetting("setting","NETWORK/wifi_dnsmain",dns_str);
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }


                                Row{
                                    spacing: 5
                                    Rectangle{
                                        width: 150
                                        height: 50
                                        Text{
                                            anchors.verticalCenter: parent.verticalCenter
                                            anchors.left: parent.left
                                            anchors.leftMargin: 30
                                            font.family: font_noto_r.name
                                            text:"Gateway"
                                            font.pixelSize: 20
                                            Component.onCompleted: {
                                                scale = 1;
                                                while(width*scale > parent.width*0.8){
                                                    scale=scale-0.01;
                                                }
                                            }
                                        }
                                    }
                                    Rectangle{
                                        width: 1
                                        height: 50
                                        color: "#d0d0d0"
                                    }

                                    Rectangle{
                                        width: 500-161
                                        height: 50
                                        Row{
                                            spacing: 10
                                            anchors.centerIn: parent
                                            TextField{
                                                id: gateway_1
                                                width: 60
                                                height: 40
                                                horizontalAlignment: TextField.AlignHCenter
                                                MouseArea{
                                                    anchors.fill:parent
                                                    onClicked: {
                                                        if(keypad.is_opened){
                                                            keypad.owner = gateway_1;
                                                            gateway_1.selectAll();
                                                        }else{
                                                            keypad.owner = gateway_1;
                                                            gateway_1.selectAll();
                                                            keypad.open();
                                                        }
                                                    }
                                                }
                                                color: ischanged?color_red:"black"
                                                property bool ischanged: false
                                                onTextChanged: {
                                                    ischanged = true;
                                                    if(gateway_1.text.split(".").length > 1){
                                                        gateway_1.text = gateway_1.text.split(".")[0];
                                                        keypad.owner = gateway_2;
                                                        gateway_2.selectAll();
                                                    }
                                                    if(gateway_1.text.length == 3){
                                                        keypad.owner = gateway_2;
                                                        gateway_2.selectAll();
                                                    }
                                                }
                                            }
                                            Text{
                                                anchors.verticalCenter: parent.verticalCenter
                                                text:"."
                                            }

                                            TextField{
                                                id: gateway_2
                                                width: 60
                                                height: 40
                                                horizontalAlignment: TextField.AlignHCenter
                                                MouseArea{
                                                    anchors.fill:parent
                                                    onClicked: {
                                                        if(keypad.is_opened){
                                                            keypad.owner = gateway_2;
                                                            gateway_2.selectAll();
                                                        }else{
                                                            keypad.owner = gateway_2;
                                                            gateway_2.selectAll();
                                                            keypad.open();
                                                        }
                                                    }
                                                }
                                                color: ischanged?color_red:"black"
                                                property bool ischanged: false
                                                onTextChanged: {
                                                    ischanged = true;
                                                    if(gateway_2.text == "."){
                                                        gateway_2.text = gateway_2.text.split(".")[0]
                                                    }

                                                    if(gateway_2.text.split(".").length > 1){
                                                        gateway_2.text = gateway_2.text.split(".")[0];
                                                        keypad.owner = gateway_3;
                                                        gateway_3.selectAll();
                                                    }
                                                    if(gateway_2.text.length == 3){
                                                        keypad.owner = gateway_3;
                                                        gateway_3.selectAll();
                                                    }
                                                }
                                            }
                                            Text{
                                                anchors.verticalCenter: parent.verticalCenter
                                                text:"."
                                            }
                                            TextField{
                                                id: gateway_3
                                                width: 60
                                                height: 40
                                                horizontalAlignment: TextField.AlignHCenter
                                                MouseArea{
                                                    anchors.fill:parent
                                                    onClicked: {
                                                        if(keypad.is_opened){
                                                            keypad.owner = gateway_3;
                                                            gateway_3.selectAll();
                                                        }else{
                                                            keypad.owner = gateway_3;
                                                            gateway_3.selectAll();
                                                            keypad.open();
                                                        }
                                                    }
                                                }
                                                color: ischanged?color_red:"black"
                                                property bool ischanged: false
                                                onTextChanged: {
                                                    ischanged = true;
                                                    if(gateway_3.text == "."){
                                                        gateway_3.text = gateway_3.text.split(".")[0]
                                                    }

                                                    if(gateway_3.text.split(".").length > 1){
                                                        gateway_3.text = gateway_3.text.split(".")[0];
                                                        keypad.owner = gateway_4;
                                                        gateway_4.selectAll();
                                                    }
                                                    if(gateway_3.text.length == 3){
                                                        keypad.owner = gateway_4;
                                                        gateway_4.selectAll();
                                                    }
                                                }
                                            }
                                            Text{
                                                anchors.verticalCenter: parent.verticalCenter
                                                text:"."
                                            }
                                            TextField{
                                                id: gateway_4
                                                width: 60
                                                height: 40
                                                horizontalAlignment: TextField.AlignHCenter
                                                MouseArea{
                                                    anchors.fill:parent
                                                    onClicked: {
                                                        if(keypad.is_opened){
                                                            keypad.owner = gateway_4;
                                                            gateway_4.selectAll();
                                                        }else{
                                                            keypad.owner = gateway_4;
                                                            gateway_4.selectAll();
                                                            keypad.open();
                                                        }
                                                    }
                                                }
                                                color: ischanged?color_red:"black"
                                                property bool ischanged: false
                                                onTextChanged: {
                                                    ischanged = true;
                                                    if(gateway_4.text == "."){
                                                        gateway_4.text = gateway_4.text.split(".")[0]
                                                    }

                                                    if(gateway_4.text.split(".").length > 1){
                                                        gateway_4.text = gateway_4.text.split(".")[0];
                                                        keypad.close();
                                                    }
                                                    if(gateway_4.text.length == 3){
                                                        keypad.close();
                                                    }
                                                }
                                            }
                                            Rectangle{
                                                height: parent.height
                                                width: parent.width*0.2
                                                radius: 5
                                                visible: false
                                                color: "black"
                                                Text{
                                                    anchors.centerIn: parent
                                                    color: "white"
                                                    font.family: font_noto_r.name
                                                    text: "변경"
                                                }
                                                MouseArea{
                                                    anchors.fill: parent
                                                    onClicked:{
                                                        click_sound.play();
                                                        ip_1.ischanged = false;
                                                        ip_2.ischanged = false;
                                                        ip_3.ischanged = false;
                                                        ip_4.ischanged = false;
                                                        var ip_str = ip_1.text + "." + ip_2.text + "." + ip_3.text + "." + ip_4.text;
                                                        gateway_1.ischanged = false;
                                                        gateway_2.ischanged = false;
                                                        gateway_3.ischanged = false;
                                                        gateway_4.ischanged = false;
                                                        var gateway_str = gateway_1.text + "." + gateway_2.text + "." + gateway_3.text + "." + gateway_4.text;
                                                        dnsmain_1.ischanged = false;
                                                        dnsmain_2.ischanged = false;
                                                        dnsmain_3.ischanged = false;
                                                        dnsmain_4.ischanged = false;
                                                        var dns_str = dnsmain_1.text + "." + dnsmain_2.text + "." + dnsmain_3.text + "." + dnsmain_4.text;
                                                        supervisor.setWifi(ip_str,gateway_str,dns_str);
                                                        supervisor.setSetting("setting","NETWORK/wifi_ip",ip_str);
                                                        supervisor.setSetting("setting","NETWORK/wifi_gateway",gateway_str);
                                                        supervisor.setSetting("setting","NETWORK/wifi_dnsmain",dns_str);
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }


                                Row{
                                    spacing: 5
                                    Rectangle{
                                        width: 150
                                        height: 50
                                        Text{
                                            anchors.verticalCenter: parent.verticalCenter
                                            anchors.left: parent.left
                                            anchors.leftMargin: 30
                                            font.family: font_noto_r.name
                                            text:"DNS"
                                            font.pixelSize: 20
                                            Component.onCompleted: {
                                                scale = 1;
                                                while(width*scale > parent.width*0.8){
                                                    scale=scale-0.01;
                                                }
                                            }
                                        }
                                    }
                                    Rectangle{
                                        width: 1
                                        height: 50
                                        color: "#d0d0d0"
                                    }

                                    Rectangle{
                                        width: 500-161
                                        height: 50
                                        Row{
                                            spacing: 10
                                            anchors.centerIn: parent
                                            TextField{
                                                id: dnsmain_1
                                                width: 60
                                                height: 40
                                                horizontalAlignment: TextField.AlignHCenter
                                                MouseArea{
                                                    anchors.fill:parent
                                                    onClicked: {
                                                        if(keypad.is_opened){
                                                            keypad.owner = dnsmain_1;
                                                            dnsmain_1.selectAll();
                                                        }else{
                                                            keypad.owner = dnsmain_1;
                                                            dnsmain_1.selectAll();
                                                            keypad.open();
                                                        }
                                                    }
                                                }
                                                color: ischanged?color_red:"black"
                                                property bool ischanged: false
                                                onTextChanged: {
                                                    ischanged = true;
                                                    if(dnsmain_1.text.split(".").length > 1){
                                                        dnsmain_1.text = dnsmain_1.text.split(".")[0];
                                                        keypad.owner = dnsmain_2;
                                                        dnsmain_2.selectAll();
                                                    }
                                                    if(dnsmain_1.text.length == 3){
                                                        keypad.owner = dnsmain_2;
                                                        dnsmain_2.selectAll();
                                                    }
                                                }
                                            }
                                            Text{
                                                anchors.verticalCenter: parent.verticalCenter
                                                text:"."
                                            }

                                            TextField{
                                                id: dnsmain_2
                                                width: 60
                                                height: 40
                                                horizontalAlignment: TextField.AlignHCenter
                                                MouseArea{
                                                    anchors.fill:parent
                                                    onClicked: {
                                                        if(keypad.is_opened){
                                                            keypad.owner = dnsmain_2;
                                                            dnsmain_2.selectAll();
                                                        }else{
                                                            keypad.owner = dnsmain_2;
                                                            dnsmain_2.selectAll();
                                                            keypad.open();
                                                        }
                                                    }
                                                }
                                                color: ischanged?color_red:"black"
                                                property bool ischanged: false
                                                onTextChanged: {
                                                    ischanged = true;
                                                    if(dnsmain_2.text == "."){
                                                        dnsmain_2.text = dnsmain_2.text.split(".")[0]
                                                    }

                                                    if(dnsmain_2.text.split(".").length > 1){
                                                        dnsmain_2.text = dnsmain_2.text.split(".")[0];
                                                        keypad.owner = dnsmain_3;
                                                        dnsmain_3.selectAll();
                                                    }
                                                    if(dnsmain_2.text.length == 3){
                                                        keypad.owner = dnsmain_3;
                                                        dnsmain_3.selectAll();
                                                    }
                                                }
                                            }
                                            Text{
                                                anchors.verticalCenter: parent.verticalCenter
                                                text:"."
                                            }
                                            TextField{
                                                id: dnsmain_3
                                                width: 60
                                                height: 40
                                                horizontalAlignment: TextField.AlignHCenter
                                                MouseArea{
                                                    anchors.fill:parent
                                                    onClicked: {
                                                        if(keypad.is_opened){
                                                            keypad.owner = dnsmain_3;
                                                            dnsmain_3.selectAll();
                                                        }else{
                                                            keypad.owner = dnsmain_3;
                                                            dnsmain_3.selectAll();
                                                            keypad.open();
                                                        }
                                                    }
                                                }
                                                color: ischanged?color_red:"black"
                                                property bool ischanged: false
                                                onTextChanged: {
                                                    ischanged = true;
                                                    if(dnsmain_3.text == "."){
                                                        dnsmain_3.text = dnsmain_3.text.split(".")[0]
                                                    }

                                                    if(dnsmain_3.text.split(".").length > 1){
                                                        dnsmain_3.text = dnsmain_3.text.split(".")[0];
                                                        keypad.owner = dnsmain_4;
                                                        dnsmain_4.selectAll();
                                                    }
                                                    if(dnsmain_3.text.length == 3){
                                                        keypad.owner = dnsmain_4;
                                                        dnsmain_4.selectAll();
                                                    }
                                                }
                                            }
                                            Text{
                                                anchors.verticalCenter: parent.verticalCenter
                                                text:"."
                                            }
                                            TextField{
                                                id: dnsmain_4
                                                width: 60
                                                height: 40
                                                horizontalAlignment: TextField.AlignHCenter
                                                MouseArea{
                                                    anchors.fill:parent
                                                    onClicked: {
                                                        if(keypad.is_opened){
                                                            keypad.owner = dnsmain_4;
                                                            dnsmain_4.selectAll();
                                                        }else{
                                                            keypad.owner = dnsmain_4;
                                                            dnsmain_4.selectAll();
                                                            keypad.open();
                                                        }
                                                    }
                                                }
                                                color: ischanged?color_red:"black"
                                                property bool ischanged: false
                                                onTextChanged: {
                                                    ischanged = true;
                                                    if(dnsmain_4.text == "."){
                                                        dnsmain_4.text = dnsmain_4.text.split(".")[0]
                                                    }

                                                    if(dnsmain_4.text.split(".").length > 1){
                                                        dnsmain_4.text = dnsmain_4.text.split(".")[0];
                                                        keypad.close();
                                                    }
                                                    if(dnsmain_4.text.length == 3){
                                                        keypad.close();
                                                    }
                                                }
                                            }
                                            Rectangle{
                                                height: parent.height
                                                width: parent.width*0.2
                                                radius: 5
                                                visible: false
                                                color: "black"
                                                Text{
                                                    anchors.centerIn: parent
                                                    color: "white"
                                                    font.family: font_noto_r.name
                                                    text: "변경"
                                                }
                                                MouseArea{
                                                    anchors.fill: parent
                                                    onClicked:{
                                                        click_sound.play();
                                                        ip_1.ischanged = false;
                                                        ip_2.ischanged = false;
                                                        ip_3.ischanged = false;
                                                        ip_4.ischanged = false;
                                                        var ip_str = ip_1.text + "." + ip_2.text + "." + ip_3.text + "." + ip_4.text;
                                                        gateway_1.ischanged = false;
                                                        gateway_2.ischanged = false;
                                                        gateway_3.ischanged = false;
                                                        gateway_4.ischanged = false;
                                                        var gateway_str = gateway_1.text + "." + gateway_2.text + "." + gateway_3.text + "." + gateway_4.text;
                                                        dnsmain_1.ischanged = false;
                                                        dnsmain_2.ischanged = false;
                                                        dnsmain_3.ischanged = false;
                                                        dnsmain_4.ischanged = false;
                                                        var dns_str = dnsmain_1.text + "." + dnsmain_2.text + "." + dnsmain_3.text + "." + dnsmain_4.text;
                                                        supervisor.setWifi(ip_str,gateway_str,dns_str);
                                                        supervisor.setSetting("setting","NETWORK/wifi_ip",ip_str);
                                                        supervisor.setSetting("setting","NETWORK/wifi_gateway",gateway_str);
                                                        supervisor.setSetting("setting","NETWORK/wifi_dnsmain",dns_str);
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
                                        type: "round_text"
                                        text: "WIFI선택"
                                        width: 120
                                        height: 50
                                        onClicked:{
                                            popup_wifi.open();
                                        }
                                    }
                                    Item_buttons{
                                        type: "round_text"
                                        text: "변경값적용"
                                        width: 120
                                        height: 50
                                        onClicked:{
                                            click_sound.play();
                                            ip_1.ischanged = false;
                                            ip_2.ischanged = false;
                                            ip_3.ischanged = false;
                                            ip_4.ischanged = false;
                                            var ip_str = ip_1.text + "." + ip_2.text + "." + ip_3.text + "." + ip_4.text;
                                            gateway_1.ischanged = false;
                                            gateway_2.ischanged = false;
                                            gateway_3.ischanged = false;
                                            gateway_4.ischanged = false;
                                            var gateway_str = gateway_1.text + "." + gateway_2.text + "." + gateway_3.text + "." + gateway_4.text;
                                            dnsmain_1.ischanged = false;
                                            dnsmain_2.ischanged = false;
                                            dnsmain_3.ischanged = false;
                                            dnsmain_4.ischanged = false;
                                            var dns_str = dnsmain_1.text + "." + dnsmain_2.text + "." + dnsmain_3.text + "." + dnsmain_4.text;
                                            supervisor.setWifi(ip_str,gateway_str,dns_str);
                                            supervisor.setSetting("setting","NETWORK/wifi_ip",ip_str);
                                            supervisor.setSetting("setting","NETWORK/wifi_gateway",gateway_str);
                                            supervisor.setSetting("setting","NETWORK/wifi_dnsmain",dns_str);
                                            popup_loading.open();
                                        }
                                    }
                                }
                            }
                        }


                    }
                }

                Rectangle{
                    id: init_
                    width: 840
                    height: 50
                    visible: false
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"초기화"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            Rectangle{
                                anchors.centerIn: parent
                                width: 300
                                height: 50
                                color: "black"
                                Text{
                                    anchors.centerIn: parent
                                    color: "white"
                                    font.family: font_noto_r.name
                                    font.pixelSize: 15
                                    text: "공용폴더 덮어씌우기"
                                }
                                MouseArea{
                                    anchors.fill: parent
                                    onClicked: {
                                        click_sound.play();
                                        popup_reset.open();
                                    }
                                }
                            }
                        }
                    }
                }
            }

        }

        Flickable{
            id: area_setting_slam
            visible: select_category==="slam"?true:false
            width: 880
            anchors.left: parent.left
            anchors.leftMargin: 100
            anchors.top: parent.top
            anchors.topMargin: 120
            height: parent.height - 200
            contentHeight: column_setting3.height
            clip: true
            ScrollBar.vertical: ScrollBar{
                width: 20
                anchors.right: parent.right
                policy: ScrollBar.AlwaysOn
            }
            Column{
                id:column_setting3
                width: parent.width
                spacing:10
                Rectangle{
                    width: 1100
                    height: 40
                    color: "black"
                    visible: is_rainbow
                    anchors.horizontalCenter: parent.horizontalCenter
                    Text{
                        anchors.centerIn: parent
                        font.family: font_noto_b.name
                        text:"카메라 설정"
                        color: "white"
                        font.pixelSize: 20
                        Component.onCompleted: {
                            scale = 1;
                            while(width*scale > parent.width*0.8){
                                scale=scale-0.01;
                            }
                        }
                    }
                }
                Rectangle{
                    id: set_camera_model
                    width: 840
                    height: 50
                    visible: false
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"카메라 모델"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            ComboBox{
                                id: combo_camera_model
                                anchors.fill: parent
                                property bool ischanged: false
                                onCurrentIndexChanged: {
                                    ischanged = true;
                                    is_reset_slam = true;
                                    if(currentIndex == 0){
//                                        is_realsense = true;
                                    }else{
//                                        is_realsense = false;
                                    }
                                }
                                model:["리얼센스","제미니"]
                            }
                        }
                    }
                }
                Rectangle{
                    id: set_cam_exposure
                    width: 840
                    height: 50
                    visible: is_rainbow
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"노출 시간 [ms]"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            TextField{
                                id: cam_exposure
                                anchors.fill: parent
                                text:supervisor.getSetting("setting","SENSOR","cam_exposure");
                                property bool ischanged: false
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        if(keypad.is_opened){
                                            keypad.owner = cam_exposure;
                                            cam_exposure.selectAll();
                                        }else{
                                            keypad.owner = cam_exposure;
                                            cam_exposure.selectAll();
                                            keypad.open();
                                        }
                                    }
                                }
                                color:ischanged?color_red:"black"
                                onTextChanged: {
                                    ischanged = true;
                                    is_reset_slam = true;
                                }
                            }
                        }
                    }
                }
                Rectangle{
                    id: set_left_camera
                    width: 840
                    height: 50
                    visible: is_rainbow
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"왼쪽 카메라 시리얼"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            TextField{
                                id: left_camera
                                height: parent.height
                                anchors.left: parent.left
                                anchors.right: btn_view_cam.left
                                text:supervisor.getSetting("static","SENSOR","left_camera_serial");
                                readOnly: true
                            }
                            Rectangle{
                                id: btn_view_cam
                                width: 100
                                height: parent.height
                                anchors.right: parent.right
                                radius: 5
                                color: "#d0d0d0"
                                Text{
                                    anchors.centerIn: parent
                                    text: "viewer"
                                    font.pixelSize: 15
                                    font.family: font_noto_r.name
                                }
                                MouseArea{
                                    anchors.fill: parent
                                    onClicked: {
                                        popup_camera.open();
                                    }
                                }
                            }
                        }
                    }
                }
                Rectangle{
                    id: set_right_camera
                    width: 840
                    height: 50
                    visible: is_rainbow
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"오른쪽 카메라 시리얼"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                            MouseArea{
                                anchors.fill: parent
                                onClicked: {

                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            TextField{
                                id: right_camera
                                height: parent.height
                                anchors.left: parent.left
                                anchors.right: btn_view_camr.left
                                text:supervisor.getSetting("static","SENSOR","right_camera_serial");
                                readOnly: true
                            }
                            Rectangle{
                                id: btn_view_camr
                                width: 100
                                height: parent.height
                                anchors.right: parent.right
                                radius: 5
                                color: "#d0d0d0"
                                Text{
                                    anchors.centerIn: parent
                                    text: "viewer"
                                    font.pixelSize: 15
                                    font.family: font_noto_r.name
                                    MouseArea{
                                        anchors.fill: parent
                                        onClicked: {
                                            popup_camera.open();
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                Rectangle{
                    id: set_lidar_offset_tf
                    width: 840
                    height: 50
                    visible: is_rainbow
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"라이다 TF"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            TextField{
                                id: lidar_offset_tf
                                anchors.left: parent.left
                                anchors.right: btn_change_lidar_offset.left
//                                anchors.fill: parent
                                text:supervisor.getSetting("static","SENSOR","lidar_offset_tf");
                            }
                            Rectangle{
                                id: btn_change_lidar_offset
                                width: parent.width*0.2
                                height: parent.height
                                anchors.right: parent.right
                                radius: 5
                                color: "black"
                                Text{
                                    anchors.centerIn: parent
                                    text: "change"
                                    color: "white"
                                }
                                MouseArea{
                                    anchors.fill: parent
                                    onClicked:{
                                        popup_tf.open();
                                    }
                                }
                            }

                        }
                    }
                }
                Rectangle{
                    id: set_left_camera_tf
                    width: 840
                    height: 50
                    visible: is_rainbow
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"좌측 카메라 TF"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            TextField{
                                id: left_camera_tf
                                anchors.left: parent.left
                                anchors.right: btn_change_left_offset.left
//                                anchors.fill: parent
                                text:supervisor.getSetting("static","SENSOR","left_camera_tf");
                            }
                            Rectangle{
                                id: btn_change_left_offset
                                width: parent.width*0.2
                                anchors.right: parent.right
                                height: parent.height
                                radius: 5
                                color: "black"
                                Text{
                                    anchors.centerIn: parent
                                    text: "change"
                                    color: "white"
                                }
                                MouseArea{
                                    anchors.fill: parent
                                    onClicked:{
                                        popup_tf.open();
                                    }
                                }
                            }

                        }
                    }
                }
                Rectangle{
                    id: set_right_camera_tf
                    width: 840
                    height: 50
                    visible: is_rainbow
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"우측 카메라 TF"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            TextField{
                                id: right_camera_tf
                                anchors.left: parent.left
                                anchors.right: btn_change_right_offset.left
//                                anchors.fill: parent
                                text:supervisor.getSetting("static","SENSOR","right_camera_tf");
                            }
                            Rectangle{
                                id:btn_change_right_offset
                                width: parent.width*0.2
                                height: parent.height
                                anchors.right: parent.right
                                radius: 5
                                color: "black"
                                Text{
                                    anchors.centerIn: parent
                                    text: "change"
                                    color: "white"
                                }
                                MouseArea{
                                    anchors.fill: parent
                                    onClicked:{
                                        popup_tf.open();
                                    }
                                }
                            }
                        }
                    }
                }
                Rectangle{
                    id: set_obs_height_min
                    width: 840
                    height: 50
                    visible: is_rainbow
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"3D카메라 감지 최소높이 [m]"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                            Item_buttons{
                                type: "circle_text"
                                width: parent.height*0.8
                                height: width
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.right: parent.right
                                anchors.rightMargin: 20
                                text: "?"
                                onClicked:{
                                    click_sound.play();
                                    popup_help_setting.open();
                                    popup_help_setting.setTitle("최소 인식 높이");
                                    popup_help_setting.addLine("장애물 감지에 사용되는 카메라 3D 데이터값의 최소높이값입니다");
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            TextField{
                                id: obs_height_min
                                anchors.fill: parent
                                objectName: "obs_height_min"
                                text:supervisor.getSetting("setting","OBSTACLE","obs_height_min");
                                property bool ischanged: false
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        if(keypad.is_opened){
                                            keypad.owner = obs_height_min;
                                            obs_height_min.selectAll();
                                        }else{
                                            keypad.owner = obs_height_min;
                                            obs_height_min.selectAll();
                                            keypad.open();
                                        }
                                    }
                                }
                                color:ischanged?color_red:"black"
                                onTextChanged: {
                                    ischanged = true;
                                    is_reset_slam = true;
                                }
                            }
                        }
                    }
                }
                Rectangle{
                    id: set_obsheight_max
                    width: 840
                    height: 50
                    visible: is_rainbow
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"3D카메라 감지 최대높이 [m]"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                            Item_buttons{
                                type: "circle_text"
                                width: parent.height*0.8
                                height: width
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.right: parent.right
                                anchors.rightMargin: 20
                                text: "?"
                                onClicked:{
                                    click_sound.play();
                                    popup_help_setting.open();
                                    popup_help_setting.setTitle("최대 인식 높이");
                                    popup_help_setting.addLine("장애물 감지에 사용되는 카메라 3D 데이터값의 최대높이값입니다");
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            TextField{
                                id: obs_height_max
                                anchors.fill: parent
                                objectName: "obs_height_max"
                                text:supervisor.getSetting("setting","OBSTACLE","obs_height_max");
                                property bool ischanged: false
                                color:ischanged?color_red:"black"
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        if(keypad.is_opened){
                                            keypad.owner = obs_height_max;
                                            obs_height_max.selectAll();
                                        }else{
                                            keypad.owner = obs_height_max;
                                            obs_height_max.selectAll();
                                            keypad.open();
                                        }
                                    }
                                }
                                onTextChanged: {
                                    ischanged = true;
                                    is_reset_slam = true;
                                }
                            }
                        }
                    }
                }
                Rectangle{
                    id: set_max_range
                    width: 840
                    height: 50
                    visible: is_rainbow
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"라이다데이터 최대 거리 [m]"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                            Item_buttons{
                                type: "circle_text"
                                width: parent.height*0.8
                                height: width
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.right: parent.right
                                anchors.rightMargin: 20
                                text: "?"
                                onClicked:{
                                    click_sound.play();
                                    popup_help_setting.open();
                                    popup_help_setting.setTitle("데이터 최대 거리");
                                    popup_help_setting.addLine("연산에 사용되는 라이다 데이터의 최대값입니다");
                                    popup_help_setting.addLine("이 값을 초과하는 라이다 데이터는 무시합니다");
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            TextField{
                                id: max_range
                                anchors.fill: parent
                                text:supervisor.getSetting("setting","SENSOR","max_range");
                                property bool ischanged: false
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        if(keypad.is_opened){
                                            keypad.owner = max_range;
                                            max_range.selectAll();
                                        }else{
                                            keypad.owner = max_range;
                                            max_range.selectAll();
                                            keypad.open();
                                        }
                                    }
                                }
                                color:ischanged?color_red:"black"
                                onTextChanged: {
                                    ischanged = true;
                                    is_reset_slam = true;

                                }
                            }
                        }
                    }
                }
                Rectangle{
                    id: set_icp_near
                    width: 840
                    height: 50
                    visible: is_rainbow
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"라이다데이터 최소 거리 [m]"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                            Item_buttons{
                                type: "circle_text"
                                width: parent.height*0.8
                                height: width
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.right: parent.right
                                anchors.rightMargin: 20
                                text: "?"
                                onClicked:{
                                    click_sound.play();
                                    popup_help_setting.open();
                                    popup_help_setting.setTitle("데이터 최소 거리");
                                    popup_help_setting.addLine("연산에 사용되는 라이다 데이터의 최소값(로봇 중심기준)입니다");
                                    popup_help_setting.addLine("이 값보다 작은 라이다 데이터는 무시합니다");
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            TextField{
                                id: icp_near
                                anchors.fill: parent
                                property bool ischanged: false
                                onTextChanged: {
                                    is_reset_slam = true;
                                    ischanged = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        if(keypad.is_opened){
                                            keypad.owner = icp_near;
                                            icp_near.selectAll();
                                        }else{
                                            keypad.owner = icp_near;
                                            icp_near.selectAll();
                                            keypad.open();
                                        }
                                    }
                                }
                                color:ischanged?color_red:"black"
                                text:supervisor.getSetting("update","LOCALIZATION","icp_near");
                            }
                        }
                    }
                }

                Rectangle{
                    width: 1100
                    height: 40
                    color: "black"
                    anchors.horizontalCenter: parent.horizontalCenter
                    Text{
                        anchors.centerIn: parent
                        font.family: font_noto_b.name
                        text:"주행 중 감지"
                        color: "white"
                        font.pixelSize: 20
                        Component.onCompleted: {
                            scale = 1;
                            while(width*scale > parent.width*0.8){
                                scale=scale-0.01;
                            }
                        }
                    }
                }
                Rectangle{
                    id: set_use_obs_preview
                    width: 840
                    height: 50
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"장애물 예측 사용"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            ComboBox{
                                id: combo_use_obs_preview
                                anchors.fill: parent
                                property bool ischanged: false
                                onCurrentIndexChanged: {
                                    is_reset_slam = true;
                                    ischanged = true;
                                }
                                model:["사용안함","사용"]
                            }
                        }
                    }
                }
                Rectangle{
                    id: set_obs_preview_time
                    width: 840
                    height: 50
                    visible: combo_use_obs_preview.currentIndex === 1
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"장애물 예측 시간 [초]"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                            Item_buttons{
                                type: "circle_text"
                                visible: false
                                width: parent.height*0.8
                                height: width
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.right: parent.right
                                anchors.rightMargin: 20
                                text: "?"
                                onClicked:{
                                    click_sound.play();
                                    popup_help_setting.open();
                                    popup_help_setting.setTitle("경로추종 최대거리");
                                    popup_help_setting.addLine("로봇과 로봇이 추종하는 경로 상 한 점 사이 최대 거리입니다");
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            TextField{
                                id: obs_preview_time
                                anchors.fill: parent
                                property bool ischanged: false
                                onTextChanged: {
                                    is_reset_slam = true;
                                    ischanged = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        if(keypad.is_opened){
                                            keypad.owner = obs_preview_time;
                                            obs_preview_time.selectAll();
                                        }else{
                                            keypad.owner = obs_preview_time;
                                            obs_preview_time.selectAll();
                                            keypad.open();
                                        }
                                    }
                                }
                                color:ischanged?color_red:"black"
                                text:supervisor.getSetting("setting","OBSTACLE","obs_preview_time");
                            }
                        }
                    }
                }

                Rectangle{
                    id: set_use_avoid
                    width: 840
                    height: 50
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"장애물 회피"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            ComboBox{
                                id: combo_use_avoid
                                anchors.fill: parent
                                property bool ischanged: false
                                onCurrentIndexChanged: {
                                    is_reset_slam = true;
                                    ischanged = true;
                                }
                                model:["사용안함","사용"]
                            }
                        }
                    }
                }
                Rectangle{
                    id: set_obs_avoid_v
                    width: 840
                    height: 50
                    visible: combo_use_avoid.currentIndex === 1
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"장애물 회피 속도"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            TextField{
                                id: obs_avoid_v
                                anchors.fill: parent
                                objectName: "obs_detect_area"
                                text:supervisor.getSetting("setting","OBSTACLE","obs_avoid_v");
                                property bool ischanged: false
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        if(keypad.is_opened){
                                            keypad.owner = obs_avoid_v;
                                            obs_avoid_v.selectAll();
                                        }else{
                                            keypad.owner = obs_avoid_v;
                                            obs_avoid_v.selectAll();
                                            keypad.open();
                                        }
                                    }
                                }
                                color:ischanged?color_red:"black"
                                onTextChanged: {
                                    ischanged = true;
                                    is_reset_slam = true;

                                }
                            }
                        }
                    }
                }
                Rectangle{
                    id: set_obs_avoid_width
                    width: 840
                    height: 50
                    visible: combo_use_avoid.currentIndex === 1
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"장애물 회피 너비"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            TextField{
                                id: obs_avoid_width
                                anchors.fill: parent
                                objectName: "obs_detect_area"
                                text:supervisor.getSetting("setting","OBSTACLE","obs_avoid_width");
                                property bool ischanged: false
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        if(keypad.is_opened){
                                            keypad.owner = obs_avoid_width;
                                            obs_avoid_width.selectAll();
                                        }else{
                                            keypad.owner = obs_avoid_width;
                                            obs_avoid_width.selectAll();
                                            keypad.open();
                                        }
                                    }
                                }
                                color:ischanged?color_red:"black"
                                onTextChanged: {
                                    ischanged = true;
                                    is_reset_slam = true;

                                }
                            }
                        }
                    }
                }

                Rectangle{
                    id: set_use_pivot_obs
                    width: 840
                    height: 50
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"제자리회전 장애물감지"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            ComboBox{
                                id: combo_use_pivot_obs
                                anchors.fill: parent
                                property bool ischanged: false
                                onCurrentIndexChanged: {
                                    is_reset_slam = true;
                                    ischanged = true;
                                }
                                model:["사용안함","사용"]
                            }
                        }
                    }
                }
                Rectangle{
                    id: set_use_obs_near
                    width: 840
                    height: 50
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"근접 장애물 감속"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            ComboBox{
                                id: combo_use_obs_near
                                anchors.fill: parent
                                property bool ischanged: false
                                onCurrentIndexChanged: {
                                    is_reset_slam = true;
                                    ischanged = true;
                                }
                                model:["사용안함","사용"]
                            }
                        }
                    }
                }
                Rectangle{
                    id: set_obs_near
                    width: 840
                    height: 50
                    visible: combo_use_obs_near.currentIndex === 1
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"근접 장애물 거리"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                            Item_buttons{
                                type: "circle_text"
                                width: parent.height*0.8
                                height: width
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.right: parent.right
                                anchors.rightMargin: 20
                                text: "?"
                                onClicked:{
                                    click_sound.play();
                                    popup_help_setting.open();
                                    popup_help_setting.setTitle("감지 거리 Level 1");
                                    popup_help_setting.addLine("주행 중 장애물을 감지하는 범위의 level 1 값입니다");
                                    popup_help_setting.addLine("로봇 중심 기준으로 동적장애물로 판단되는 것이 이 범위 안에 들어오면");
                                    popup_help_setting.addLine("감속하고 놀란 표정을 띄웁니다.(바닥의 LED 색은 보라색)");
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            TextField{
                                id: obs_near
                                anchors.fill: parent
                                objectName: "obs_near"
                                text:supervisor.getSetting("setting","OBSTACLE","obs_near");
                                property bool ischanged: false
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        if(keypad.is_opened){
                                            keypad.owner = obs_near;
                                            obs_near.selectAll();
                                        }else{
                                            keypad.owner = obs_near;
                                            obs_near.selectAll();
                                            keypad.open();
                                        }
                                    }
                                }
                                color:ischanged?color_red:"black"
                                onTextChanged: {
                                    ischanged = true;
                                    is_reset_slam = true;

                                }
                            }
                        }
                    }
                }

                Rectangle{
                    id: set_use_earlystop_resting
                    width: 840
                    height: 50
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"대기위치 근처 장애물 미리 정지"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            ComboBox{
                                id: combo_use_earlystop_resting
                                anchors.fill: parent
                                property bool ischanged: false
                                onCurrentIndexChanged: {
                                    is_reset_slam = true;
                                    ischanged = true;
                                }
                                model:["사용안함","사용"]
                            }
                        }
                    }
                }
                Rectangle{
                    id: set_use_earlystop_serving
                    width: 840
                    height: 50
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"서빙위치 근처 장애물 미리 정지"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            ComboBox{
                                id: combo_use_earlystop_serving
                                anchors.fill: parent
                                property bool ischanged: false
                                onCurrentIndexChanged: {
                                    is_reset_slam = true;
                                    ischanged = true;
                                }
                                model:["사용안함","사용"]
                            }
                        }
                    }
                }
                Rectangle{
                    id: set_obs_early_stop_dist
                    width: 840
                    height: 50
                    visible: set_use_earlystop_resting.currentIndex === 1 || set_use_earlystop_serving.currentIndex === 1
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"근처 장애물 정지 거리"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            TextField{
                                id: obs_early_stop_dist
                                anchors.fill: parent
                                objectName: "obs_early_stop_dist"
                                text:supervisor.getSetting("setting","OBSTACLE","obs_early_stop_dist");
                                property bool ischanged: false
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        if(keypad.is_opened){
                                            keypad.owner = obs_early_stop_dist;
                                            obs_early_stop_dist.selectAll();
                                        }else{
                                            keypad.owner = obs_early_stop_dist;
                                            obs_early_stop_dist.selectAll();
                                            keypad.open();
                                        }
                                    }
                                }
                                color:ischanged?color_red:"black"
                                onTextChanged: {
                                    ischanged = true;
                                    is_reset_slam = true;
                                }
                            }
                        }
                    }
                }


                Rectangle{
                    id: set_decmargin
                    width: 840
                    height: 50
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"감지 거리 Level 1 [m]"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                            Item_buttons{
                                type: "circle_text"
                                width: parent.height*0.8
                                height: width
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.right: parent.right
                                anchors.rightMargin: 20
                                text: "?"
                                onClicked:{
                                    click_sound.play();
                                    popup_help_setting.open();
                                    popup_help_setting.setTitle("감지 거리 Level 1");
                                    popup_help_setting.addLine("주행 중 장애물을 감지하는 범위의 level 1 값입니다");
                                    popup_help_setting.addLine("로봇 중심 기준으로 동적장애물로 판단되는 것이 이 범위 안에 들어오면");
                                    popup_help_setting.addLine("감속하고 놀란 표정을 띄웁니다.(바닥의 LED 색은 보라색)");
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            TextField{
                                id: obs_margin1
                                anchors.fill: parent
                                objectName: "obs_margin1"
                                text:supervisor.getSetting("setting","OBSTACLE","obs_margin1");
                                property bool ischanged: false
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        if(keypad.is_opened){
                                            keypad.owner = obs_margin1;
                                            obs_margin1.selectAll();
                                        }else{
                                            keypad.owner = obs_margin1;
                                            obs_margin1.selectAll();
                                            keypad.open();
                                        }
                                    }
                                }
                                color:ischanged?color_red:"black"
                                onTextChanged: {
                                    ischanged = true;
                                    is_reset_slam = true;

                                }
                            }
                        }
                    }
                }
                Rectangle{
                    id: set_decmargin0
                    width: 840
                    height: 50
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"감지 거리 Level 0 [m]"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                            Item_buttons{
                                type: "circle_text"
                                width: parent.height*0.8
                                height: width
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.right: parent.right
                                anchors.rightMargin: 20
                                text: "?"
                                onClicked:{
                                    click_sound.play();
                                    popup_help_setting.open();
                                    popup_help_setting.setTitle("감지 거리 Level 0");
                                    popup_help_setting.addLine("주행 중 장애물을 감지하는 범위의 level 0 값입니다");
                                    popup_help_setting.addLine("로봇 중심 기준으로 동적장애물로 판단되는 것이 이 범위 안에 들어오면");
                                    popup_help_setting.addLine("로봇을 즉시 정지하며 우는 표정을 띄웁니다.(바닥의 LED 색은 붉은색)");
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            TextField{
                                id: obs_margin0
                                anchors.fill: parent
                                objectName: "obs_margin0"
                                text:supervisor.getSetting("setting","OBSTACLE","obs_margin0");
                                property bool ischanged: false
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        if(keypad.is_opened){
                                            keypad.owner = obs_margin0;
                                            obs_margin0.selectAll();
                                        }else{
                                            keypad.owner = obs_margin0;
                                            obs_margin0.selectAll();
                                            keypad.open();
                                        }
                                    }
                                }
                                color:ischanged?color_red:"black"
                                onTextChanged: {
                                    ischanged = true;
                                    is_reset_slam = true;
                                }
                            }
                        }
                    }
                }
                Rectangle{
                    id: set_obs_area
                    width: 840
                    height: 50
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"장애물 넓이 [pixel]"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                            Item_buttons{
                                type: "circle_text"
                                width: parent.height*0.8
                                height: width
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.right: parent.right
                                anchors.rightMargin: 20
                                text: "?"
                                onClicked:{
                                    click_sound.play();
                                    popup_help_setting.open();
                                    popup_help_setting.setTitle("장애물 넓이");
                                    popup_help_setting.addLine("감지되는 동적 센서 데이타가 이 값만큼 뭉쳐있다면 장애물로 판단합니다");
                                    popup_help_setting.addLine("단위는 pixel로 현재 설정된 픽셀 당 크기 값을 참조하세요");
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            TextField{
                                id: obs_detect_area
                                anchors.fill: parent
                                objectName: "obs_detect_area"
                                text:supervisor.getSetting("setting","OBSTACLE","obs_detect_area");
                                property bool ischanged: false
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        if(keypad.is_opened){
                                            keypad.owner = obs_detect_area;
                                            obs_detect_area.selectAll();
                                        }else{
                                            keypad.owner = obs_detect_area;
                                            obs_detect_area.selectAll();
                                            keypad.open();
                                        }
                                    }
                                }
                                color:ischanged?color_red:"black"
                                onTextChanged: {
                                    ischanged = true;
                                    is_reset_slam = true;

                                }
                            }
                        }
                    }
                }
                Rectangle{
                    id: set_obs_sensitivity
                    width: 840
                    height: 50
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"장애물 감지 민감도"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                            Item_buttons{
                                type: "circle_text"
                                width: parent.height*0.8
                                height: width
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.right: parent.right
                                anchors.rightMargin: 20
                                text: "?"
                                onClicked:{
                                    click_sound.play();
                                    popup_help_setting.open();
                                    popup_help_setting.setTitle("장애물 감지 민감도");
                                    popup_help_setting.addLine("동적장애물로 판단하는 픽셀의 민감도 입니다");
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            TextField{
                                id: obs_detect_sensitivity
                                anchors.fill: parent
                                objectName: "obs_detect_sensitivity"
                                text:supervisor.getSetting("setting","OBSTACLE","obs_detect_sensitivity");
                                property bool ischanged: false
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        if(keypad.is_opened){
                                            keypad.owner = obs_detect_sensitivity;
                                            obs_detect_sensitivity.selectAll();
                                        }else{
                                            keypad.owner = obs_detect_sensitivity;
                                            obs_detect_sensitivity.selectAll();
                                            keypad.open();
                                        }
                                    }
                                }
                                color:ischanged?color_red:"black"
                                onTextChanged: {
                                        ischanged = true;
                                        is_reset_slam = true;

                                }
                            }
                        }
                    }
                }
                Rectangle{
                    id: set_obs_deadzone
                    width: 840
                    height: 50
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"즉시정지 거리 [m]"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                            Item_buttons{
                                type: "circle_text"
                                width: parent.height*0.8
                                height: width
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.right: parent.right
                                anchors.rightMargin: 20
                                text: "?"
                                onClicked:{
                                    click_sound.play();
                                    popup_help_setting.open();
                                    popup_help_setting.setTitle("즉시정지 거리");
                                    popup_help_setting.addLine("로봇 중심 기준으로 동적장애물로 판단되는 것이 이 범위 안에 들어오면");
                                    popup_help_setting.addLine("로봇을 즉시 정지하며 우는 표정을 띄웁니다.(바닥의 LED 색은 붉은색)");
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            TextField{
                                id: obs_deadzone
                                anchors.fill: parent
                                property bool ischanged: false
                                onTextChanged: {
                                    is_reset_slam = true;
                                    ischanged = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        if(keypad.is_opened){
                                            keypad.owner = obs_deadzone;
                                            obs_deadzone.selectAll();
                                        }else{
                                            keypad.owner = obs_deadzone;
                                            obs_deadzone.selectAll();
                                            keypad.open();
                                        }
                                    }
                                }
                                color:ischanged?color_red:"black"
                                text:supervisor.getSetting("setting","OBSTACLE","obs_deadzone");
                            }
                        }
                    }
                }
                Rectangle{
                    id: set_obs_wait_time
                    width: 840
                    height: 50
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"감지 후 대기시간 [sec]"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                            Item_buttons{
                                type: "circle_text"
                                width: parent.height*0.8
                                height: width
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.right: parent.right
                                anchors.rightMargin: 20
                                text: "?"
                                onClicked:{
                                    click_sound.play();
                                    popup_help_setting.open();
                                    popup_help_setting.setTitle("감지 후 대기시간");
                                    popup_help_setting.addLine("장애물을 감지 후 로봇이 멈춘 뒤 다시 출발할 때 까지 걸리는 대기시간입니다");
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            TextField{
                                id: obs_wait_time
                                anchors.fill: parent
                                property bool ischanged: false
                                onTextChanged: {
                                    is_reset_slam = true;
                                    ischanged = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        if(keypad.is_opened){
                                            keypad.owner = obs_wait_time;
                                            obs_wait_time.selectAll();
                                        }else{
                                            keypad.owner = obs_wait_time;
                                            obs_wait_time.selectAll();
                                            keypad.open();
                                        }
                                    }
                                }
                                color:ischanged?color_red:"black"
                                text:supervisor.getSetting("setting","OBSTACLE","obs_wait_time");
                            }
                        }
                    }
                }

                Rectangle{
                    id: set_lookaheaddist
                    width: 840
                    height: 50
                    visible: is_rainbow
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"경로추종 최대거리 [m]"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                            Item_buttons{
                                type: "circle_text"
                                width: parent.height*0.8
                                height: width
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.right: parent.right
                                anchors.rightMargin: 20
                                text: "?"
                                onClicked:{
                                    click_sound.play();
                                    popup_help_setting.open();
                                    popup_help_setting.setTitle("경로추종 최대거리");
                                    popup_help_setting.addLine("로봇과 로봇이 추종하는 경로 상 한 점 사이 최대 거리입니다");
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            TextField{
                                id: look_ahead_dist
                                anchors.fill: parent
                                property bool ischanged: false
                                onTextChanged: {
                                    is_reset_slam = true;
                                    ischanged = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        if(keypad.is_opened){
                                            keypad.owner = look_ahead_dist;
                                            look_ahead_dist.selectAll();
                                        }else{
                                            keypad.owner = look_ahead_dist;
                                            look_ahead_dist.selectAll();
                                            keypad.open();
                                        }
                                    }
                                }
                                color:ischanged?color_red:"black"
                                text:supervisor.getSetting("update","DRIVING","look_ahead_dist");
                            }
                        }
                    }
                }
                Rectangle{
                    id: set_minlookaheaddist
                    width: 840
                    height: 50
                    visible: is_rainbow
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"경로추종 최소거리 [m]"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                            Item_buttons{
                                type: "circle_text"
                                width: parent.height*0.8
                                height: width
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.right: parent.right
                                anchors.rightMargin: 20
                                text: "?"
                                onClicked:{
                                    click_sound.play();
                                    popup_help_setting.open();
                                    popup_help_setting.setTitle("경로추종 최대거리");
                                    popup_help_setting.addLine("로봇과 로봇이 추종하는 경로 상 한 점 사이 최소 거리입니다");
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            TextField{
                                id: min_look_ahead_dist
                                anchors.fill: parent
                                property bool ischanged: false
                                onTextChanged: {
                                    is_reset_slam = true;
                                    ischanged = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        if(keypad.is_opened){
                                            keypad.owner = min_look_ahead_dist;
                                            min_look_ahead_dist.selectAll();
                                        }else{
                                            keypad.owner = min_look_ahead_dist;
                                            min_look_ahead_dist.selectAll();
                                            keypad.open();
                                        }
                                    }
                                }
                                color:ischanged?color_red:"black"
                                text:supervisor.getSetting("update","DRIVING","min_look_ahead_dist");
                            }
                        }
                    }
                }

                Rectangle{
                    id: set_path_out_dist
                    width: 840
                    height: 50
                    visible: is_rainbow
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"경로이탈 거리 [m]"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                            Item_buttons{
                                type: "circle_text"
                                width: parent.height*0.8
                                height: width
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.right: parent.right
                                anchors.rightMargin: 20
                                text: "?"
                                onClicked:{
                                    click_sound.play();
                                    popup_help_setting.open();
                                    popup_help_setting.setTitle("경로이탈 거리");
                                    popup_help_setting.addLine("로봇이 경로에서 이 값 이상 떨어지면 경로를 이탈했다고 판단합니다");
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            TextField{
                                id: path_out_dist
                                anchors.fill: parent
                                property bool ischanged: false
                                onTextChanged: {
                                    is_reset_slam = true;
                                    ischanged = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        if(keypad.is_opened){
                                            keypad.owner = path_out_dist;
                                            path_out_dist.selectAll();
                                        }else{
                                            keypad.owner = path_out_dist;
                                            path_out_dist.selectAll();
                                            keypad.open();
                                        }
                                    }
                                }
                                color:ischanged?color_red:"black"
                                text:supervisor.getSetting("update","DRIVING","path_out_dist");
                            }
                        }
                    }
                }

                Rectangle{
                    width: 1100
                    height: 40
                    color: "black"
                    anchors.horizontalCenter: parent.horizontalCenter
                    Text{
                        anchors.centerIn: parent
                        font.family: font_noto_b.name
                        text:"위치 추정"
                        color: "white"
                        font.pixelSize: 20
                    }
                }
                Rectangle{
                    id: set_icp_init_ratio
                    width: 840
                    height: 50
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"초기화 성공기준 [0~1]"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            TextField{
                                id: icp_init_ratio
                                anchors.fill: parent
                                property bool ischanged: false
                                onTextChanged: {
                                    is_reset_slam = true;
                                    ischanged = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        if(keypad.is_opened){
                                            keypad.owner = icp_init_ratio;
                                            icp_init_ratio.selectAll();
                                        }else{
                                            keypad.owner = icp_init_ratio;
                                            icp_init_ratio.selectAll();
                                            keypad.open();
                                        }
                                    }
                                }
                                color:ischanged?color_red:"black"
                                text:supervisor.getSetting("setting","INITIALIZATION","icp_init_ratio");
                            }
                        }
                    }
                }
                Rectangle{
                    id: set_icp_init_error
                    width: 840
                    height: 50
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"초기화 에러기준 [0~1]"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            TextField{
                                id: icp_init_error
                                anchors.fill: parent
                                property bool ischanged: false
                                onTextChanged: {
                                    is_reset_slam = true;
                                    ischanged = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        if(keypad.is_opened){
                                            keypad.owner = icp_init_error;
                                            icp_init_error.selectAll();
                                        }else{
                                            keypad.owner = icp_init_error;
                                            icp_init_error.selectAll();
                                            keypad.open();
                                        }
                                    }
                                }
                                color:ischanged?color_red:"black"
                                text:supervisor.getSetting("setting","INITIALIZATION","icp_init_error");
                            }
                        }
                    }
                }
                Rectangle{
                    id: set_icp_dist
                    width: 840
                    height: 50
                    visible: is_rainbow
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"Inlier 판단거리 [m]"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                            Item_buttons{
                                type: "circle_text"
                                width: parent.height*0.8
                                height: width
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.right: parent.right
                                anchors.rightMargin: 20
                                text: "?"
                                onClicked:
                                {
                                    click_sound.play();
                                    popup_help_setting.open();
                                    popup_help_setting.setTitle("Inlier 판단거리");
                                    popup_help_setting.addLine("로봇이 위치추정할 때, 실제 라이다데이터와 맵상 대응점과의 위치차이가");
                                    popup_help_setting.addLine("이 값보다 작다면 inlier(일치)한다고 판단합니다");
                                    popup_help_setting.addLine("이 값이 작을 수록 위치추정이 정밀하지만 위치추정에 실패할 가능성도 높아집니다");
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            TextField{
                                id: icp_dist
                                anchors.fill: parent
                                property bool ischanged: false
                                onTextChanged: {
                                    is_reset_slam = true;
                                    ischanged = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        if(keypad.is_opened){
                                            keypad.owner = icp_dist;
                                            icp_dist.selectAll();
                                        }else{
                                            keypad.owner = icp_dist;
                                            icp_dist.selectAll();
                                            keypad.open();
                                        }
                                    }
                                }
                                color:ischanged?color_red:"black"
                                text:supervisor.getSetting("update","LOCALIZATION","icp_dist");
                            }
                        }
                    }
                }
                Rectangle{
                    id: set_icp_error
                    width: 840
                    height: 50
                    visible: is_rainbow
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"평균오차 최소값 [m]"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                            Item_buttons{
                                type: "circle_text"
                                width: parent.height*0.8
                                height: width
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.right: parent.right
                                anchors.rightMargin: 20
                                text: "?"
                                onClicked:
                                {
                                    click_sound.play();
                                    popup_help_setting.open();
                                    popup_help_setting.setTitle("평균오차 최소값(icp_error)");
                                    popup_help_setting.addLine("Inlier 판단된 데이터들의 실제 라이다데이터와 맵상 대응점과의 위치차이의 평균이");
                                    popup_help_setting.addLine("이 값보다 작다면 위치추정에 성공했다고 판단합니다");
                                    popup_help_setting.addLine("위치추정은 평균오차의 최소값과 Inlier 비율이 모두 기준에 부합해야 성공으로 간주합니다");
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            TextField{
                                id: icp_error
                                anchors.fill: parent
                                property bool ischanged: false
                                onTextChanged: {
                                    is_reset_slam = true;
                                    ischanged = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        if(keypad.is_opened){
                                            keypad.owner = icp_error;
                                            icp_error.selectAll();
                                        }else{
                                            keypad.owner = icp_error;
                                            icp_error.selectAll();
                                            keypad.open();
                                        }
                                    }
                                }
                                color:ischanged?color_red:"black"
                                text:supervisor.getSetting("update","LOCALIZATION","icp_error");
                            }
                        }
                    }
                }
                Rectangle{
                    id: set_icp_ratio
                    width: 840
                    height: 50
                    visible: is_rainbow
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"Inlier 비율 [%]"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                            Item_buttons{
                                type: "circle_text"
                                width: parent.height*0.8
                                height: width
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.right: parent.right
                                anchors.rightMargin: 20
                                text: "?"
                                onClicked:
                                {
                                    click_sound.play();
                                    popup_help_setting.open();
                                    popup_help_setting.setTitle("Inlier 비율 (icp_ratio)");
                                    popup_help_setting.addLine("전체 라이다데이터 대비 lnlier 판단된 데이터 값의 비율입니다");
                                    popup_help_setting.addLine("실제 값이 이 기준보다 높아야 위치추정에 성공했다고 판단합니다");
                                    popup_help_setting.addLine("위치추정은 평균오차의 최소값과 Inlier 비율이 모두 기준에 부합해야 성공으로 간주합니다");
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            TextField{
                                id: icp_ratio
                                anchors.fill: parent
                                property bool ischanged: false
                                onTextChanged: {
                                    is_reset_slam = true;
                                    ischanged = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        if(keypad.is_opened){
                                            keypad.owner = icp_ratio;
                                            icp_ratio.selectAll();
                                        }else{
                                            keypad.owner = icp_ratio;
                                            icp_ratio.selectAll();
                                            keypad.open();
                                        }
                                    }
                                }
                                color:ischanged?color_red:"black"
                                text:supervisor.getSetting("update","LOCALIZATION","icp_ratio");
                            }
                        }
                    }
                }
                Rectangle{
                    id: set_icp_odometry_weight
                    width: 840
                    height: 50
                    visible: is_rainbow
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text: "모터 위치추정 비율 [%]"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                            Item_buttons{
                                type: "circle_text"
                                width: parent.height*0.8
                                height: width
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.right: parent.right
                                anchors.rightMargin: 20
                                text: "?"
                                onClicked:{
                                    click_sound.play();
                                    popup_help_setting.open();
                                    popup_help_setting.setTitle("모터 위치추정 비율");
                                    popup_help_setting.addLine("모터의 엔코더값으로 계산되는 위치추정 값을 얼마나 사용할지의 비율입니다");
                                    popup_help_setting.addLine("값이 0에 가까울 수록 라이다데이타로 추정하는 ICP를 신뢰하고");
                                    popup_help_setting.addLine("값이 1에 가까울 수록 라이다데이타는 사용하지 않습니다");
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            TextField{
                                id: icp_odometry_weight
                                anchors.fill: parent
                                property bool ischanged: false
                                onTextChanged: {
                                    is_reset_slam = true;
                                    ischanged = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        if(keypad.is_opened){
                                            keypad.owner = icp_odometry_weight;
                                            icp_odometry_weight.selectAll();
                                        }else{
                                            keypad.owner = icp_odometry_weight;
                                            icp_odometry_weight.selectAll();
                                            keypad.open();
                                        }
                                    }
                                }
                                color:ischanged?color_red:"black"
                                text:supervisor.getSetting("update","LOCALIZATION","icp_odometry_weight");
                            }
                        }
                    }
                }
                Rectangle{
                    id: set_icp_repeat_dist
                    width: 840
                    height: 50
                    visible: is_rainbow
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"위치추정 최소 거리 [m]"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                            Item_buttons{
                                type: "circle_text"
                                width: parent.height*0.8
                                height: width
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.right: parent.right
                                anchors.rightMargin: 20
                                text: "?"
                                onClicked:{
                                    click_sound.play();
                                    popup_help_setting.open();
                                    popup_help_setting.setTitle("위치추정 최소 거리");
                                    popup_help_setting.addLine("로봇이 주행하며 이 거리 이상 움직이면 위치추정을 시도합니다");
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            TextField{
                                id: icp_repeat_dist
                                anchors.fill: parent
                                property bool ischanged: false
                                onTextChanged: {
                                    is_reset_slam = true;
                                    ischanged = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        if(keypad.is_opened){
                                            keypad.owner = icp_repeat_dist;
                                            icp_repeat_dist.selectAll();
                                        }else{
                                            keypad.owner = icp_repeat_dist;
                                            icp_repeat_dist.selectAll();
                                            keypad.open();
                                        }
                                    }
                                }
                                color:ischanged?color_red:"black"
                                text:supervisor.getSetting("update","LOCALIZATION","icp_repeat_dist");
                            }
                        }
                    }
                }
                Rectangle{
                    id: set_icp_repeat_time
                    width: 840
                    height: 50
                    visible: is_rainbow
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"위치추정 최소 시간[sec]"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                            Item_buttons{
                                type: "circle_text"
                                width: parent.height*0.8
                                height: width
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.right: parent.right
                                anchors.rightMargin: 20
                                text: "?"
                                onClicked:{
                                    click_sound.play();
                                    popup_help_setting.open();
                                    popup_help_setting.setTitle("위치추정 최소 시간");
                                    popup_help_setting.addLine("로봇은 이 시간 간격으로 자동으로 위치추정을 시도합니다");
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            TextField{
                                id: icp_repeat_time
                                anchors.fill: parent
                                property bool ischanged: false
                                onTextChanged: {
                                    is_reset_slam = true;
                                    ischanged = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        if(keypad.is_opened){
                                            keypad.owner = icp_repeat_time;
                                            icp_repeat_time.selectAll();
                                        }else{
                                            keypad.owner = icp_repeat_time;
                                            icp_repeat_time.selectAll();
                                            keypad.open();
                                        }
                                    }
                                }
                                color:ischanged?color_red:"black"
                                text:supervisor.getSetting("update","LOCALIZATION","icp_repeat_time");
                            }
                        }
                    }
                }




                Rectangle{
                    width: 1100
                    height: 40
                    color: "black"
                    visible: is_rainbow
                    anchors.horizontalCenter: parent.horizontalCenter
                    Text{
                        anchors.centerIn: parent
                        font.family: font_noto_b.name
                        text:"도착점 판단"
                        color: "white"
                        font.pixelSize: 20
                    }
                }
                Rectangle{
                    id: set_goal_dist
                    width: 840
                    height: 50
                    visible: is_rainbow
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"도착점 허용 오차 [m]"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                            Item_buttons{
                                type: "circle_text"
                                width: parent.height*0.8
                                height: width
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.right: parent.right
                                anchors.rightMargin: 20
                                text: "?"
                                onClicked:{
                                    click_sound.play();
                                    popup_help_setting.open();
                                    popup_help_setting.setTitle("도착점 허용 오차");
                                    popup_help_setting.addLine("로봇의 현재 위치와 목적지의 위치차이가 이 값보다 작으면 목적지에 도착했다고 판단합니다");
                                    popup_help_setting.addLine("값이 작을 수록 목작지에 정확하게 도달하지만 조금만 틀어져도 목적지에 도착했다고 판단하지 않아서");
                                    popup_help_setting.addLine("주행실패하거나 이상동작을 할 수 있습니다");
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            TextField{
                                id: goal_dist
                                anchors.fill: parent
                                property bool ischanged: false
                                onTextChanged: {
                                    is_reset_slam = true;
                                    ischanged = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        if(keypad.is_opened){
                                            keypad.owner = goal_dist;
                                            goal_dist.selectAll();
                                        }else{
                                            keypad.owner = goal_dist;
                                            goal_dist.selectAll();
                                            keypad.open();
                                        }
                                    }
                                }
                                color:ischanged?color_red:"black"
                                text:supervisor.getSetting("update","DRIVING","goal_dist");
                            }
                        }
                    }
                }
                Rectangle{
                    id: set_goal_th
                    width: 840
                    height: 50
                    visible: is_rainbow
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"도착점 허용 오차 [deg]"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                            Item_buttons{
                                type: "circle_text"
                                width: parent.height*0.8
                                height: width
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.right: parent.right
                                anchors.rightMargin: 20
                                text: "?"
                                onClicked:{
                                    click_sound.play();
                                    popup_help_setting.open();
                                    popup_help_setting.setTitle("도착점 허용 오차");
                                    popup_help_setting.addLine("로봇의 현재 위치와 목적지의 위치차이가 이 값보다 작으면 목적지에 도착했다고 판단합니다");
                                    popup_help_setting.addLine("값이 작을 수록 목작지에 정확하게 도달하지만 조금만 틀어져도 목적지에 도착했다고 판단하지 않아서");
                                    popup_help_setting.addLine("주행실패하거나 이상동작을 할 수 있습니다");
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            TextField{
                                id: goal_th
                                anchors.fill: parent
                                property bool ischanged: false
                                onTextChanged: {
                                    is_reset_slam = true;
                                    ischanged = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        if(keypad.is_opened){
                                            keypad.owner = goal_th;
                                            goal_th.selectAll();
                                        }else{
                                            keypad.owner = goal_th;
                                            goal_th.selectAll();
                                            keypad.open();
                                        }
                                    }
                                }
                                color:ischanged?color_red:"black"
                                text:supervisor.getSetting("update","DRIVING","goal_th");

                            }
                        }
                    }
                }
                Rectangle{
                    id: set_goal_near_dist
                    width: 840
                    height: 50
                    visible: is_rainbow
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"경로탐색 최소거리 [m]"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                            Item_buttons{
                                type: "circle_text"
                                width: parent.height*0.8
                                height: width
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.right: parent.right
                                anchors.rightMargin: 20
                                text: "?"
                                onClicked:{
                                    click_sound.play();
                                    popup_help_setting.open();
                                    popup_help_setting.setTitle("경로탐색 최소거리");
                                    popup_help_setting.addLine("출발점과 도착점이 이 값보다 작으면 경로를 탐색하지 않고");
                                    popup_help_setting.addLine("point to point 방식으로 이동합니다");
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            TextField{
                                id: goal_near_dist
                                anchors.fill: parent
                                property bool ischanged: false
                                onTextChanged: {
                                    is_reset_slam = true;
                                    ischanged = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        if(keypad.is_opened){
                                            keypad.owner = goal_near_dist;
                                            goal_near_dist.selectAll();
                                        }else{
                                            keypad.owner = goal_near_dist;
                                            goal_near_dist.selectAll();
                                            keypad.open();
                                        }
                                    }
                                }
                                color:ischanged?color_red:"black"
                                text:supervisor.getSetting("update","DRIVING","goal_near_dist");
                            }
                        }
                    }
                }
                Rectangle{
                    id: set_goal_near_th
                    width: 840
                    height: 50
                    visible: is_rainbow
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"경로탐색 최소거리 [deg]"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                            Item_buttons{
                                type: "circle_text"
                                width: parent.height*0.8
                                height: width
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.right: parent.right
                                anchors.rightMargin: 20
                                text: "?"
                                onClicked:{
                                    click_sound.play();
                                    popup_help_setting.open();
                                    popup_help_setting.setTitle("경로탐색 최소거리");
                                    popup_help_setting.addLine("출발점과 도착점이 이 값보다 작으면 경로를 탐색하지 않고");
                                    popup_help_setting.addLine("point to point 방식으로 이동합니다");
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            TextField{
                                id: goal_near_th
                                anchors.fill: parent
                                property bool ischanged: false
                                onTextChanged: {
                                    is_reset_slam = true;
                                    ischanged = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        if(keypad.is_opened){
                                            keypad.owner = goal_near_th;
                                            goal_near_th.selectAll();
                                        }else{
                                            keypad.owner = goal_near_th;
                                            goal_near_th.selectAll();
                                            keypad.open();
                                        }
                                    }
                                }
                                color:ischanged?color_red:"black"
                                text:supervisor.getSetting("update","DRIVING","goal_near_th");
                            }
                        }
                    }
                }

                Rectangle{
                    width: 1100
                    height: 40
                    color: "black"
                    visible: is_rainbow
                    anchors.horizontalCenter: parent.horizontalCenter
                    Text{
                        anchors.centerIn: parent
                        font.family: font_noto_b.name
                        text:"지도 작성"
                        color: "white"
                        font.pixelSize: 20
                    }
                }
                Rectangle{
                    id: set_slam_submap_cnt
                    width: 840
                    height: 50
                    visible: is_rainbow
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"서브맵 프레임 개수"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                            Item_buttons{
                                type: "circle_text"
                                width: parent.height*0.8
                                height: width
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.right: parent.right
                                anchors.rightMargin: 20
                                text: "?"
                                onClicked:{
                                    click_sound.play();
                                    popup_help_setting.open();
                                    popup_help_setting.setTitle("도착점 허용 오차");
                                    popup_help_setting.addLine("로봇의 현재 위치와 목적지의 위치차이가 이 값보다 작으면 목적지에 도착했다고 판단합니다");
                                    popup_help_setting.addLine("값이 작을 수록 목작지에 정확하게 도달하지만 조금만 틀어져도 목적지에 도착했다고 판단하지 않아서");
                                    popup_help_setting.addLine("주행실패하거나 이상동작을 할 수 있습니다");
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            TextField{
                                id: slam_submap_cnt
                                anchors.fill: parent
                                property bool ischanged: false
                                onTextChanged: {
                                    is_reset_slam = true;
                                    ischanged = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        if(keypad.is_opened){
                                            keypad.owner = slam_submap_cnt;
                                            slam_submap_cnt.selectAll();
                                        }else{
                                            keypad.owner = slam_submap_cnt;
                                            slam_submap_cnt.selectAll();
                                            keypad.open();
                                        }
                                    }
                                }
                                color:ischanged?color_red:"black"
                                text:supervisor.getSetting("update","SLAM","slam_submap_cnt");
                            }
                        }
                    }
                }
                Rectangle{
                    id: set_slam_lc_dist
                    width: 840
                    height: 50
                    visible: is_rainbow
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"루프클로징 시도거리"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                            Item_buttons{
                                type: "circle_text"
                                width: parent.height*0.8
                                height: width
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.right: parent.right
                                anchors.rightMargin: 20
                                text: "?"
                                onClicked:{
                                    click_sound.play();
                                    popup_help_setting.open();
                                    popup_help_setting.setTitle("도착점 허용 오차");
                                    popup_help_setting.addLine("로봇의 현재 위치와 목적지의 위치차이가 이 값보다 작으면 목적지에 도착했다고 판단합니다");
                                    popup_help_setting.addLine("값이 작을 수록 목작지에 정확하게 도달하지만 조금만 틀어져도 목적지에 도착했다고 판단하지 않아서");
                                    popup_help_setting.addLine("주행실패하거나 이상동작을 할 수 있습니다");
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            TextField{
                                id: slam_lc_dist
                                anchors.fill: parent
                                property bool ischanged: false
                                onTextChanged: {
                                    is_reset_slam = true;
                                    ischanged = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        if(keypad.is_opened){
                                            keypad.owner = slam_lc_dist;
                                            slam_lc_dist.selectAll();
                                        }else{
                                            keypad.owner = slam_lc_dist;
                                            slam_lc_dist.selectAll();
                                            keypad.open();
                                        }
                                    }
                                }
                                color:ischanged?color_red:"black"
                                text:supervisor.getSetting("update","SLAM","slam_lc_dist");
                            }
                        }
                    }
                }
                Rectangle{
                    id: set_slam_lc_icp_dist
                    width: 840
                    height: 50
                    visible: is_rainbow
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"루프클로징 매칭범위"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                            Item_buttons{
                                type: "circle_text"
                                width: parent.height*0.8
                                height: width
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.right: parent.right
                                anchors.rightMargin: 20
                                text: "?"
                                onClicked:{
                                    click_sound.play();
                                    popup_help_setting.open();
                                    popup_help_setting.setTitle("도착점 허용 오차");
                                    popup_help_setting.addLine("로봇의 현재 위치와 목적지의 위치차이가 이 값보다 작으면 목적지에 도착했다고 판단합니다");
                                    popup_help_setting.addLine("값이 작을 수록 목작지에 정확하게 도달하지만 조금만 틀어져도 목적지에 도착했다고 판단하지 않아서");
                                    popup_help_setting.addLine("주행실패하거나 이상동작을 할 수 있습니다");
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            TextField{
                                id: slam_lc_icp_dist
                                anchors.fill: parent
                                property bool ischanged: false
                                onTextChanged: {
                                    is_reset_slam = true;
                                    ischanged = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        if(keypad.is_opened){
                                            keypad.owner = slam_lc_icp_dist;
                                            slam_lc_icp_dist.selectAll();
                                        }else{
                                            keypad.owner = slam_lc_icp_dist;
                                            slam_lc_icp_dist.selectAll();
                                            keypad.open();
                                        }
                                    }
                                }
                                color:ischanged?color_red:"black"
                                text:supervisor.getSetting("update","SLAM","slam_lc_icp_dist");
                            }
                        }
                    }
                }
                Rectangle{
                    id: set_map_size
                    width: 840
                    height: 50
                    visible: is_rainbow
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"지도 기본 크기"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                            Item_buttons{
                                type: "circle_text"
                                width: parent.height*0.8
                                height: width
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.right: parent.right
                                anchors.rightMargin: 20
                                text: "?"
                                onClicked:{
                                    click_sound.play();
                                    popup_help_setting.open();
                                    popup_help_setting.setTitle("도착점 허용 오차");
                                    popup_help_setting.addLine("로봇의 현재 위치와 목적지의 위치차이가 이 값보다 작으면 목적지에 도착했다고 판단합니다");
                                    popup_help_setting.addLine("값이 작을 수록 목작지에 정확하게 도달하지만 조금만 틀어져도 목적지에 도착했다고 판단하지 않아서");
                                    popup_help_setting.addLine("주행실패하거나 이상동작을 할 수 있습니다");
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            TextField{
                                id: map_size
                                anchors.fill: parent
                                property bool ischanged: false
                                onTextChanged: {
                                    is_reset_slam = true;
                                    ischanged = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        if(keypad.is_opened){
                                            keypad.owner = map_size;
                                            map_size.selectAll();
                                        }else{
                                            keypad.owner = map_size;
                                            map_size.selectAll();
                                            keypad.open();
                                        }
                                    }
                                }
                                color:ischanged?color_red:"black"
                                text:supervisor.getSetting("update","SLAM","map_size");
                            }
                        }
                    }
                }
                Rectangle{
                    id: set_grid_size
                    width: 840
                    height: 50
                    visible: is_rainbow
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"기본 격자 크기"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                            Item_buttons{
                                type: "circle_text"
                                width: parent.height*0.8
                                height: width
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.right: parent.right
                                anchors.rightMargin: 20
                                text: "?"
                                onClicked:{
                                    click_sound.play();
                                    popup_help_setting.open();
                                    popup_help_setting.setTitle("도착점 허용 오차");
                                    popup_help_setting.addLine("로봇의 현재 위치와 목적지의 위치차이가 이 값보다 작으면 목적지에 도착했다고 판단합니다");
                                    popup_help_setting.addLine("값이 작을 수록 목작지에 정확하게 도달하지만 조금만 틀어져도 목적지에 도착했다고 판단하지 않아서");
                                    popup_help_setting.addLine("주행실패하거나 이상동작을 할 수 있습니다");
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            TextField{
                                id: grid_size
                                anchors.fill: parent
                                property bool ischanged: false
                                onTextChanged: {
                                    is_reset_slam = true;
                                    ischanged = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        if(keypad.is_opened){
                                            keypad.owner = grid_size;
                                            grid_size.selectAll();
                                        }else{
                                            keypad.owner = grid_size;
                                            grid_size.selectAll();
                                            keypad.open();
                                        }
                                    }
                                }
                                color:ischanged?color_red:"black"
                                text:supervisor.getSetting("update","SLAM","grid_size");
                            }
                        }
                    }
                }

            }
        }

        Flickable{
            id: area_setting_moving
            visible: select_category==="moving"?true:false
            width: 880
            anchors.left: parent.left
            anchors.leftMargin: 100
            anchors.top: parent.top
            anchors.topMargin: 120
            height: parent.height - 200
            contentHeight: column_setting45.height
            clip: true
            ScrollBar.vertical: ScrollBar{
                width: 20
                anchors.right: parent.right
                policy: ScrollBar.AlwaysOn
            }
            Column{
                id:column_setting45
                width: parent.width
                spacing:10
                Rectangle{
                    width: 1100
                    height: 40
                    color: "black"
                    visible: is_rainbow
                    anchors.horizontalCenter: parent.horizontalCenter
                    Text{
                        anchors.centerIn: parent
                        font.family: font_noto_b.name
                        text:"주행 중"
                        color: "white"
                        font.pixelSize: 20
                        Component.onCompleted: {
                            scale = 1;
                            while(width*scale > parent.width*0.8){
                                scale=scale-0.01;
                            }
                        }
                    }
                }
                Rectangle{
                    id: set_use_current
                    width: 840
                    height: 50
                    visible: is_rainbow
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"모터 과전류 시 일시정지"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                            Item_buttons{
                                type: "circle_text"
                                width: parent.height*0.8
                                height: width
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.right: parent.right
                                anchors.rightMargin: 20
                                text: "?"
                                onClicked:{
                                    click_sound.play();
                                    popup_help_setting.open();
                                    popup_help_setting.setTitle("모터전류 감지");
                                    popup_help_setting.addLine("로봇이 주행 중, 충돌했다고 판단할만큼 모터의 전류가 높다면 자동으로 일시정지합니다");
                                    popup_help_setting.addLine("감도를 올리거나 내리고 싶다면 모터전류 제한값을 변경해 주세요");
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            ComboBox{
                                id: combo_use_motorcurrent
                                anchors.fill: parent
                                property bool ischanged: false
                                onCurrentIndexChanged: {
                                    ischanged = true;
                                }
                                model:["사용안함","사용"]
                            }
                        }
                    }
                }
                Rectangle{
                    id: set_motor_current_margin
                    width: 840
                    height: 50
                    visible: is_rainbow && combo_use_motorcurrent.currentIndex === 1
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"모터전류 제한값 [mA]"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            TextField{
                                id: pause_motor_current
                                anchors.fill: parent
                                property bool ischanged: false
                                onTextChanged: {
                                    ischanged = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        if(keypad.is_opened){
                                            keypad.owner = pause_motor_current;
                                            pause_motor_current.selectAll();
                                        }else{
                                            keypad.owner = pause_motor_current;
                                            pause_motor_current.selectAll();
                                            keypad.open();
                                        }
                                    }
                                }
                                color:ischanged?color_red:"black"
                                text:supervisor.getSetting("update","DRIVING","pause_motor_current");

                            }
                        }
                    }
                }
                Rectangle{
                    width: 840
                    height: 50
                    visible: is_rainbow && combo_use_motorcurrent.currentIndex === 1
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"모터전류 제한시간 [ms]"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            TextField{
                                id: pause_check_ms
                                anchors.fill: parent
                                property bool ischanged: false
                                onTextChanged: {
                                    ischanged = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        if(keypad.is_opened){
                                            keypad.owner = pause_check_ms;
                                            pause_check_ms.selectAll();
                                        }else{
                                            keypad.owner = pause_check_ms;
                                            pause_check_ms.selectAll();
                                            keypad.open();
                                        }
                                    }
                                }
                                color:ischanged?color_red:"black"
                                text:supervisor.getSetting("update","DRIVING","pause_check_ms");
                            }
                        }
                    }
                }

                Rectangle{
                    width: 1100
                    height: 40
                    color: "black"
                    visible: is_rainbow
                    anchors.horizontalCenter: parent.horizontalCenter
                    Text{
                        anchors.centerIn: parent
                        font.family: font_noto_b.name
                        text:"속도 제한"
                        color: "white"
                        font.pixelSize: 20
                        Component.onCompleted: {
                            scale = 1;
                            while(width*scale > parent.width*0.8){
                                scale=scale-0.01;
                            }
                        }
                    }
                }
                Rectangle{
                    id: set_st_v
                    width: 840
                    height: 50
                    visible: is_rainbow
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"출발 시 처음속도 [m/s]"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                            Item_buttons{
                                type: "circle_text"
                                width: parent.height*0.8
                                height: width
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.right: parent.right
                                anchors.rightMargin: 20
                                text: "?"
                                onClicked:{
                                    click_sound.play();
                                    popup_help_setting.open();
                                    popup_help_setting.setTitle("출발 속도(st_v)");
                                    popup_help_setting.addLine("로봇이 출발할 때, 처음으로 주어지는 속도값입니다");
                                    popup_help_setting.addLine("작을 수록 천천히 출발합니다");
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            TextField{
                                id: st_v
                                anchors.fill: parent
                                property bool ischanged: false
                                onTextChanged: {
                                    is_reset_slam = true;
                                    ischanged = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        if(keypad.is_opened){
                                            keypad.owner = st_v;
                                            st_v.selectAll();
                                        }else{
                                            keypad.owner = st_v;
                                            st_v.selectAll();
                                            keypad.open();
                                        }
                                    }
                                }
                                color:ischanged?color_red:"black"
                                text:supervisor.getSetting("update","DRIVING","st_v");
                            }
                        }
                    }
                }
                Rectangle{
                    id: set_goal_v
                    width: 840
                    height: 50
                    visible: is_rainbow
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"도착지점 속도 [m/s]"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                            Item_buttons{
                                type: "circle_text"
                                width: parent.height*0.8
                                height: width
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.right: parent.right
                                anchors.rightMargin: 20
                                text: "?"
                                onClicked:{
                                    click_sound.play();
                                    popup_help_setting.open();
                                    popup_help_setting.setTitle("도착 속도(goal_v)");
                                    popup_help_setting.addLine("로봇이 목적지에 인접했을 때, 감속되는 최종 속도값입니다");
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            TextField{
                                id: goal_v
                                anchors.fill: parent
                                property bool ischanged: false
                                onTextChanged: {
                                    is_reset_slam = true;
                                    ischanged = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        if(keypad.is_opened){
                                            keypad.owner = goal_v;
                                            goal_v.selectAll();
                                        }else{
                                            keypad.owner = goal_v;
                                            goal_v.selectAll();
                                            keypad.open();
                                        }
                                    }
                                }
                                color:ischanged?color_red:"black"
                                text:supervisor.getSetting("update","DRIVING","goal_v");
                            }
                        }
                    }
                }

                Rectangle{
                    width: 1100
                    height: 40
                    color: "black"
                    visible: is_rainbow
                    anchors.horizontalCenter: parent.horizontalCenter
                    Text{
                        anchors.centerIn: parent
                        font.family: font_noto_b.name
                        text:"게인 수정"
                        color: "white"
                        font.pixelSize: 20
                        Component.onCompleted: {
                            scale = 1;
                            while(width*scale > parent.width*0.8){
                                scale=scale-0.01;
                            }
                        }
                    }
                }
                Rectangle{
                    id: set_k_curve
                    width: 840
                    height: 50
                    visible: is_rainbow
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"k_curve"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            TextField{
                                id: k_curve
                                anchors.fill: parent
                                property bool ischanged: false
                                onTextChanged: {
                                    is_reset_slam = true;
                                    ischanged = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        if(keypad.is_opened){
                                            keypad.owner = k_curve;
                                            k_curve.selectAll();
                                        }else{
                                            keypad.owner = k_curve;
                                            k_curve.selectAll();
                                            keypad.open();
                                        }
                                    }
                                }
                                color:ischanged?color_red:"black"
                                text:supervisor.getSetting("update","DRIVING","k_curve");
                            }
                        }
                    }
                }
                Rectangle{
                    id: set_k_v
                    width: 840
                    visible: is_rainbow
                    height: 50
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"k_v"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            TextField{
                                id: k_v
                                anchors.fill: parent
                                property bool ischanged: false
                                onTextChanged: {
                                    is_reset_slam = true;
                                    ischanged = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        if(keypad.is_opened){
                                            keypad.owner = k_v;
                                            k_v.selectAll();
                                        }else{
                                            keypad.owner = k_v;
                                            k_v.selectAll();
                                            keypad.open();
                                        }
                                    }
                                }
                                color:ischanged?color_red:"black"
                                text:supervisor.getSetting("update","DRIVING","k_v");
                            }
                        }
                    }
                }
                Rectangle{
                    id: set_k_w
                    width: 840
                    visible: is_rainbow
                    height: 50
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"k_w"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            TextField{
                                id: k_w
                                anchors.fill: parent
                                property bool ischanged: false
                                onTextChanged: {
                                    is_reset_slam = true;
                                    ischanged = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        if(keypad.is_opened){
                                            keypad.owner = k_w;
                                            k_w.selectAll();
                                        }else{
                                            keypad.owner = k_w;
                                            k_w.selectAll();
                                            keypad.open();
                                        }
                                    }
                                }
                                color:ischanged?color_red:"black"
                                text:supervisor.getSetting("update","DRIVING","k_w");
                            }
                        }
                    }
                }
                Rectangle{
                    id: set_k_dd
                    visible: is_rainbow
                    width: 840
                    height: 50
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"k_dd"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            TextField{
                                id: k_dd
                                anchors.fill: parent
                                property bool ischanged: false
                                onTextChanged: {
                                    is_reset_slam = true;
                                    ischanged = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        if(keypad.is_opened){
                                            keypad.owner = k_dd;
                                            k_dd.selectAll();
                                        }else{
                                            keypad.owner = k_dd;
                                            k_dd.selectAll();
                                            keypad.open();
                                        }
                                    }
                                }
                                color:ischanged?color_red:"black"
                                text:supervisor.getSetting("update","DRIVING","k_dd");
                            }
                        }
                    }
                }
                Rectangle{
                    id: set_path_delta_v_acc_gain
                    width: 840
                    height: 50
                    visible: is_rainbow
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"경로 가속 게인"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            TextField{
                                id: path_delta_v_acc_gain
                                anchors.fill: parent
                                property bool ischanged: false
                                onTextChanged: {
                                    is_reset_slam = true;
                                    ischanged = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        if(keypad.is_opened){
                                            keypad.owner = path_delta_v_acc_gain;
                                            path_delta_v_acc_gain.selectAll();
                                        }else{
                                            keypad.owner = path_delta_v_acc_gain;
                                            path_delta_v_acc_gain.selectAll();
                                            keypad.open();
                                        }
                                    }
                                }
                                color:ischanged?color_red:"black"
                                text:supervisor.getSetting("update","DRIVING","path_delta_v_acc_gain");
                            }
                        }
                    }
                }
                Rectangle{
                    id: set_path_delta_v_dec_gain
                    width: 840
                    height: 50
                    visible: is_rainbow
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"경로 감속 게인"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            TextField{
                                id: path_delta_v_dec_gain
                                anchors.fill: parent
                                property bool ischanged: false
                                onTextChanged: {
                                    is_reset_slam = true;
                                    ischanged = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        if(keypad.is_opened){
                                            keypad.owner = path_delta_v_dec_gain;
                                            path_delta_v_dec_gain.selectAll();
                                        }else{
                                            keypad.owner = path_delta_v_dec_gain;
                                            path_delta_v_dec_gain.selectAll();
                                            keypad.open();
                                        }
                                    }
                                }
                                color:ischanged?color_red:"black"
                                text:supervisor.getSetting("update","DRIVING","path_delta_v_dec_gain");
                            }
                        }
                    }
                }
                Rectangle{
                    id: set_path_ref_v_gain
                    width: 840
                    height: 50
                    visible: is_rainbow
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"경로 속도 게인"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            TextField{
                                id: path_ref_v_gain
                                anchors.fill: parent
                                property bool ischanged: false
                                onTextChanged: {
                                    is_reset_slam = true;
                                    ischanged = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        if(keypad.is_opened){
                                            keypad.owner = path_ref_v_gain;
                                            path_ref_v_gain.selectAll();
                                        }else{
                                            keypad.owner = path_ref_v_gain;
                                            path_ref_v_gain.selectAll();
                                            keypad.open();
                                        }
                                    }
                                }
                                color:ischanged?color_red:"black"
                                text:supervisor.getSetting("update","DRIVING","path_ref_v_gain");
                            }
                        }
                    }
                }
                Rectangle{
                    id: set_path_shifting_val
                    width: 840
                    height: 50
                    visible: is_rainbow
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"경로 시프팅 게인"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            TextField{
                                id: path_shifting_val
                                anchors.fill: parent
                                property bool ischanged: false
                                onTextChanged: {
                                    is_reset_slam = true;
                                    ischanged = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        if(keypad.is_opened){
                                            keypad.owner = path_shifting_val;
                                            path_shifting_val.selectAll();
                                        }else{
                                            keypad.owner = path_shifting_val;
                                            path_shifting_val.selectAll();
                                            keypad.open();
                                        }
                                    }
                                }
                                color:ischanged?color_red:"black"
                                text:supervisor.getSetting("update","DRIVING","path_shifting_val");
                            }
                        }
                    }
                }

                Rectangle{
                    width: 1100
                    height: 40
                    color: "black"
                    visible: is_rainbow
                    anchors.horizontalCenter: parent.horizontalCenter
                    Text{
                        anchors.centerIn: parent
                        font.family: font_noto_b.name
                        text:"모터 세팅 값"
                        color: "white"
                        font.pixelSize: 20
                    }
                }
                Rectangle{
                    id: set_wheel_dir
                    width: 840
                    height: 50
                    visible: is_rainbow
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"바퀴 회전 방향"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            ComboBox{
                                id: combo_wheel_dir
                                property bool ischanged: false
                                onCurrentIndexChanged: {
                                    ischanged = true;
                                    is_reset_slam = true;
                                }
                                anchors.fill: parent
                                model: [-1,1]
                            }
                        }
                    }
                }
                Rectangle{
                    id: set_left_id
                    width: 840
                    height: 50
                    visible: is_rainbow
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"왼쪽 모터 ID"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            ComboBox{
                                id: combo_left_id
                                property bool ischanged: false
                                onCurrentIndexChanged: {
                                    ischanged = true;
                                    is_reset_slam = true;
                                }
                                anchors.fill: parent
                                model:[0,1]
                            }
                        }
                    }
                }
                Rectangle{
                    id: set_right_id
                    width: 840
                    height: 50
                    visible: is_rainbow
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"오른쪽 모터 ID"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            ComboBox{
                                id: combo_right_id
                                property bool ischanged: false
                                onCurrentIndexChanged: {
                                    ischanged = true;
                                    is_reset_slam = true;
                                }
                                anchors.fill: parent
                                model:[0,1]
                            }
                        }
                    }
                }
                Rectangle{
                    id: set_gear_ratio
                    width: 840
                    height: 50
                    visible: is_rainbow
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"모터 기어비"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            TextField{
                                id: gear_ratio
                                anchors.fill: parent
                                property bool ischanged: false
                                onTextChanged: {
                                    is_reset_slam = true;
                                    ischanged = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        if(keypad.is_opened){
                                            keypad.owner = gear_ratio;
                                            gear_ratio.selectAll();
                                        }else{
                                            keypad.owner = gear_ratio;
                                            gear_ratio.selectAll();
                                            keypad.open();
                                        }
                                    }
                                }
                                color:ischanged?color_red:"black"
                                text:supervisor.getSetting("update","MOTOR","gear_ratio");
                            }
                        }
                    }
                }
                Rectangle{
                    id: set_kp
                    width: 840
                    height: 50
                    visible: is_rainbow
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"모터 P 게인"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            TextField{
                                id: k_p
                                anchors.fill: parent
                                property bool ischanged: false
                                onTextChanged: {
                                    is_reset_slam = true;
                                    ischanged = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        if(keypad.is_opened){
                                            keypad.owner = k_p;
                                            k_p.selectAll();
                                        }else{
                                            keypad.owner = k_p;
                                            k_p.selectAll();
                                            keypad.open();
                                        }
                                    }
                                }
                                color:ischanged?color_red:"black"
                                text:supervisor.getSetting("update","MOTOR","k_p");
                            }
                        }
                    }
                }
                Rectangle{
                    id: set_ki
                    width: 840
                    height: 50
                    visible: is_rainbow
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"모터 I 게인"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            TextField{
                                id: k_i
                                anchors.fill: parent
                                property bool ischanged: false
                                onTextChanged: {
                                    is_reset_slam = true;
                                    ischanged = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        if(keypad.is_opened){
                                            keypad.owner = k_i;
                                            k_i.selectAll();
                                        }else{
                                            keypad.owner = k_i;
                                            k_i.selectAll();
                                            keypad.open();
                                        }
                                    }
                                }
                                color:ischanged?color_red:"black"
                                text:supervisor.getSetting("update","MOTOR","k_i");
                            }
                        }
                    }
                }
                Rectangle{
                    id: set_kd
                    width: 840
                    height: 50
                    visible: is_rainbow
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"모터 D 게인"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            TextField{
                                id: k_d
                                anchors.fill: parent
                                property bool ischanged: false
                                onTextChanged: {
                                    is_reset_slam = true;
                                    ischanged = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        if(keypad.is_opened){
                                            keypad.owner = k_d;
                                            k_d.selectAll();
                                        }else{
                                            keypad.owner = k_d;
                                            k_d.selectAll();
                                            keypad.open();
                                        }
                                    }
                                }
                                color:ischanged?color_red:"black"
                                text:supervisor.getSetting("update","MOTOR","k_d");
                            }
                        }
                    }
                }
                Rectangle{
                    id: set_limit_v
                    width: 840
                    visible: is_rainbow
                    height: 50
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"최대 속도 [m/s]"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            TextField{
                                id: motor_limit_v
                                anchors.fill: parent
                                property bool ischanged: false
                                onTextChanged: {
                                    is_reset_slam = true;
                                    ischanged = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        if(keypad.is_opened){
                                            keypad.owner = motor_limit_v;
                                            motor_limit_v.selectAll();
                                        }else{
                                            keypad.owner = motor_limit_v;
                                            motor_limit_v.selectAll();
                                            keypad.open();
                                        }
                                    }
                                }
                                color:ischanged?color_red:"black"
                                text:supervisor.getSetting("update","MOTOR","limit_v");
                            }
                        }
                    }
                }
                Rectangle{
                    id: set_limitv_acc
                    width: 840
                    visible: is_rainbow
                    height: 50
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"최대 가속도 [m/s^2]"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            TextField{
                                id: motor_limit_v_acc
                                anchors.fill: parent
                                property bool ischanged: false
                                onTextChanged: {
                                    is_reset_slam = true;
                                    ischanged = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        if(keypad.is_opened){
                                            keypad.owner = motor_limit_v_acc;
                                            motor_limit_v_acc.selectAll();
                                        }else{
                                            keypad.owner = motor_limit_v_acc;
                                            motor_limit_v_acc.selectAll();
                                            keypad.open();
                                        }
                                    }
                                }
                                color:ischanged?color_red:"black"
                                text:supervisor.getSetting("update","MOTOR","limit_v_acc");
                            }
                        }
                    }
                }
                Rectangle{
                    id: set_limit_w
                    width: 840
                    height: 50
                    visible: is_rainbow
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"최대 각속도 [deg/s]"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            TextField{
                                id: motor_limit_w
                                anchors.fill: parent
                                property bool ischanged: false
                                onTextChanged: {
                                    is_reset_slam = true;
                                    ischanged = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        if(keypad.is_opened){
                                            keypad.owner = motor_limit_w;
                                            motor_limit_w.selectAll();
                                        }else{
                                            keypad.owner = motor_limit_w;
                                            motor_limit_w.selectAll();
                                            keypad.open();
                                        }
                                    }
                                }
                                color:ischanged?color_red:"black"
                                text:supervisor.getSetting("update","MOTOR","limit_w");
                            }
                        }
                    }
                }
                Rectangle{
                    id: set_limit_wacc
                    width: 840
                    height: 50
                    visible: is_rainbow
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"최대 각가속도 [deg/s^2]"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: parent.width - 351
                            height: parent.height
                            TextField{
                                id: motor_limit_w_acc
                                anchors.fill: parent
                                property bool ischanged: false
                                onTextChanged: {
                                    is_reset_slam = true;
                                    ischanged = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        if(keypad.is_opened){
                                            keypad.owner = motor_limit_w_acc;
                                            motor_limit_w_acc.selectAll();
                                        }else{
                                            keypad.owner = motor_limit_w_acc;
                                            motor_limit_w_acc.selectAll();
                                            keypad.open();
                                        }
                                    }
                                }
                                color:ischanged?color_red:"black"
                                text:supervisor.getSetting("update","MOTOR","limit_w_acc");
                            }
                        }
                    }
                }
            }
        }


        Rectangle{
            id: area_setting_motor
            visible: select_category==="status" ? true : false
            width: 1000
            color:"transparent"
            height: parent.height
            Row{
                spacing : 150
                anchors.centerIn: parent
                Image{
                    source: "image/image_robot_temp.png"
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.verticalCenterOffset: 50
                    width: 200
                    height: 460
                    ColorOverlay{
                        anchors.fill: parent
                        source: parent
                        color: color_gray
                    }
                    Image{
                        id: status_motor_left
                        property var state: 2
                        source: state === 0?"icon/icon_error.png":state === 1?"image/warning.png":"icon/btn_yes.png"
                        width: 55
                        height: 50
                        anchors.left: parent.left
                        anchors.leftMargin: 20//60
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: state === 1 ? 20 : 23
                        Rectangle{
                            visible: false
                            width: 130
                            height: 30
                            radius: 5
                            anchors.topMargin: parent.state === 1 ? 0 : 3
                            color: parent.state === 0?color_red:parent.state === 1?color_warning:color_green
                            anchors.top: parent.bottom
                            anchors.left: parent.left
                            Text{
                                anchors.centerIn: parent
                                font.family: font_noto_r.name
                                font.pixelSize: 20
                                color: "white"
                                text: "모터 1"
                            }
                        }
                    }
                    Image{
                        id: status_motor_right
                        property var state: 1
                        source: state === 0?"icon/icon_error.png":state === 1?"image/warning.png":"icon/btn_yes.png"
                        width: 55
                        height: 50
                        anchors.right: parent.right
                        anchors.rightMargin: 20//-60
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: state === 1 ? 20 : 23
                        Rectangle{
                            width: 130
                            visible: false
                            height: 30
                            radius: 5
                            anchors.topMargin: parent.state === 1 ? 0 : 3
                            color: parent.state === 0?color_red:parent.state === 1?color_warning:color_green
                            anchors.top: parent.bottom
                            anchors.right: parent.right
                            Text{
                                anchors.centerIn: parent
                                font.family: font_noto_r.name
                                font.pixelSize: 20
                                color: "white"
                                text: "모터 2"
                            }
                        }
                    }
                    Image{
                        id: status_power
                        property var state: 0
                        source: state === 0?"icon/icon_error.png":state === 1?"image/warning.png":"icon/btn_yes.png"
                        width: 55
                        height: 50
                        anchors.centerIn: parent
                        Rectangle{
                            width: 130
                            height: 30
                            visible: false
                            radius: 5
                            color: parent.state === 0?color_red:parent.state === 1?color_warning:color_green
                            anchors.top: parent.bottom
                            anchors.topMargin: parent.state === 1 ? 0 : 3
                            anchors.horizontalCenter: parent.horizontalCenter
                            Text{
                                anchors.centerIn: parent
                                font.family: font_noto_r.name
                                font.pixelSize: 20
                                color: "white"
                                text: "전원"
                            }
                        }
                        Item_ProgressBar{
                            id: bar_battery
                            width: 180
                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.top: parent.bottom
                            anchors.topMargin: 5
                            height: 40
                            to:100
                            from:0
                            value: supervisor.getBattery();
                            Text{
                                id: text_battery
                                anchors.centerIn: parent
                                font.family: font_noto_r.name
                                font.pixelSize: 20
                                text: parent.value + " %"
                                color: "white"
                            }
                        }
                    }
                    Image{
                        id: status_localization
                        property var state: 0
                        source: state === 0?"icon/icon_error.png":state === 1?"image/warning.png":"icon/btn_yes.png"
                        width: 55
                        height: 50
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.bottom: parent.top
                        anchors.bottomMargin: -20
                    }
                }
                Rectangle{
                    width: 500
                    height: area_setting_motor.height
                    color: "transparent"
                    Column{
                        anchors.verticalCenter: parent.verticalCenter
                        spacing: 10
                        Rectangle{
                            id: state_robot
                            width: 500
                            height: 100
                            radius: 10
                            color: "white"
                            Text{
                                id: text_robot
                                anchors.centerIn: parent
                                font.family: font_noto_b.name
                                font.pixelSize: 40
                                text: "로봇 운영 중"
                            }
                        }
                        Rectangle{
                            id: state_power
                            width: 500
                            height: 500
                            radius: 10
                            clip: true
                            visible: model_power_issue.count > 0
                            color: "transparent"
                            Flickable{
                                width: parent.width*0.9
                                height: parent.height*0.9
                                anchors.centerIn: parent
                                contentHeight: ddddd.height
                                Column{
                                    id: ddddd
                                    anchors.centerIn: parent
                                    spacing: 10
                                    Repeater{
                                        model:ListModel{id:model_power_issue}
                                        Rectangle{
                                            width: 500
                                            height: 50
                                            radius: 10
                                            color: "transparent"
                                            Row{
                                                spacing: 30
                                                Rectangle{
                                                    width: 100
                                                    height: 50
                                                    color: "transparent"
                                                    Image{
                                                        anchors.centerIn: parent
                                                        source: image
                                                        width: 45
                                                        height: 40
                                                    }
                                                }
                                                Rectangle{
                                                    width: 370
                                                    height: 50
                                                    radius : 10
                                                    color: "white"
                                                    Text{
                                                        anchors.centerIn: parent
                                                        font.family: font_noto_r.name
                                                        font.pixelSize: 20
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

                }

            }


            MouseArea{
                anchors.left: parent.left
                anchors.bottom: parent.bottom
                width: 100
                height: 100
                Rectangle{
                    anchors.fill: parent
                    color: "transparent"
                }

                onClicked: {
                    click_sound.play();
                    if(debug_count++ > 3){
                        debug_count = 0;
                        popup_robot_details.open();
                    }
                }
            }

            Column{
                id:column_setting4
                width: parent.width
                visible: false
//                anchors.top: rect_motor_2.bottom
                anchors.topMargin: 2
                spacing:10
                Rectangle{
                    width: 840
                    height: 40
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"모터 연결상태"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: (parent.width - 351)/2
                            height: parent.height
                            color: "transparent"
                            Rectangle{
                                id: rect_connection_0
                                height: parent.height
                                anchors.centerIn: parent
                                width: parent.width*0.8
                                color: supervisor.getMotorConnection(motor_left_id)?color_green:color_red
                                Text{
                                    id: text_connection_0
                                    anchors.centerIn: parent
                                    font.family: font_noto_r.name
                                    text:supervisor.getMotorConnection(motor_left_id)?"연결됨":"연결안됨"
                                    font.pixelSize: 15
                                }
                            }
                        }
                        Rectangle{
                            width: (parent.width - 351)/2
                            height: parent.height
                            color: "transparent"
                            Rectangle{
                                id: rect_connection_1
                                height: parent.height
                                anchors.centerIn: parent
                                width: parent.width*0.8
                                color: supervisor.getMotorConnection(motor_right_id)?color_green:color_red
                                Text{
                                    id: text_connection_1
                                    anchors.centerIn: parent
                                    font.family: font_noto_r.name
                                    text:supervisor.getMotorConnection(motor_right_id)?"연결됨":"연결안됨"
                                    font.pixelSize: 15
                                }
                            }
                        }
                    }
                }
                Rectangle{
                    width: 840
                    height: 50
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"모터 상태"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: (parent.width - 351)/2
                            height: parent.height
                            Text{
                                id: text_status_0
                                anchors.centerIn: parent
                                font.family: font_noto_r.name
                                text:supervisor.getMotorStatus(0).toString()
                                font.pixelSize: 15
                            }
                        }
                        Rectangle{
                            width: (parent.width - 351)/2
                            height: parent.height
                            Text{
                                id: text_status_1
                                anchors.centerIn: parent
                                font.family: font_noto_r.name
                                text:supervisor.getMotorStatus(1).toString()
                                font.pixelSize: 15
                            }
                        }
                    }
                }
                Rectangle{
                    width: 840
                    height: 50
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"모터 온도"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: (parent.width - 351)/2
                            height: parent.height
                            Text{
                                id: text_temp_0
                                anchors.centerIn: parent
                                font.family: font_noto_r.name
                                text:supervisor.getMotorTemperature(0).toString()
                                font.pixelSize: 15
                            }
                        }
                        Rectangle{
                            width: (parent.width - 351)/2
                            height: parent.height
                            Text{
                                id: text_temp_1
                                anchors.centerIn: parent
                                font.family: font_noto_r.name
                                text:supervisor.getMotorTemperature(1).toString()
                                font.pixelSize: 15
                            }
                        }
                    }
                }
                Rectangle{
                    width: 840
                    height: 50
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"모터 내부 온도"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: (parent.width - 351)/2
                            height: parent.height
                            Text{
                                id: text_temp_0_1
                                anchors.centerIn: parent
                                font.family: font_noto_r.name
                                text:supervisor.getMotorInsideTemperature(0).toString()
                                font.pixelSize: 15
                            }
                        }
                        Rectangle{
                            width: (parent.width - 351)/2
                            height: parent.height
                            Text{
                                id: text_temp_1_1
                                anchors.centerIn: parent
                                font.family: font_noto_r.name
                                text:supervisor.getMotorInsideTemperature(1).toString()
                                font.pixelSize: 15
                            }
                        }
                    }
                }
                Rectangle{
                    width: 840
                    height: 50
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"모터 전류"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: (parent.width - 351)/2
                            height: parent.height
                            Text{
                                id: text_cur_0
                                anchors.centerIn: parent
                                font.family: font_noto_r.name
                                text:supervisor.getMotorCurrent(0).toString()
                                font.pixelSize: 15
                            }
                        }
                        Rectangle{
                            width: (parent.width - 351)/2
                            height: parent.height
                            Text{
                                id: text_cur_1
                                anchors.centerIn: parent
                                font.family: font_noto_r.name
                                text:supervisor.getMotorCurrent(1).toString()
                                font.pixelSize: 15
                            }
                        }
                    }
                }

                Rectangle{
                    width: 1100
                    height: 40
                    color: "black"
                    anchors.horizontalCenter: parent.horizontalCenter
                    Text{
                        anchors.centerIn: parent
                        font.family: font_noto_b.name
                        text:"로봇 상태"
                        color: "white"
                        font.pixelSize: 20
                    }
                }

                Rectangle{
                    width: 840
                    height: 50
                    Row{
                        anchors.fill: parent
                        Rectangle{
                            width: 350
                            height: parent.height
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 30
                                font.family: font_noto_r.name
                                text:"상태값"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                        }
                        Rectangle{
                            width: 1
                            height: parent.height
                            color: "#d0d0d0"
                        }
                        Rectangle{
                            width: (parent.width - 351)/4
                            height: parent.height
                            Text{
                                id: text_status_charging
                                anchors.centerIn: parent
                                font.family: font_noto_r.name
                                text:"Charging : "+supervisor.getChargeStatus().toString()
                                font.pixelSize: 15
                            }
                        }
                        Rectangle{
                            width: (parent.width - 351)/4
                            height: parent.height
                            Text{
                                id: text_status_power
                                anchors.centerIn: parent
                                font.family: font_noto_r.name
                                text:"Power : "+supervisor.getPowerStatus().toString()
                                font.pixelSize: 15
                            }
                        }
                        Rectangle{
                            width: (parent.width - 351)/4
                            height: parent.height
                            Text{
                                id: text_status_emo
                                anchors.centerIn: parent
                                font.family: font_noto_r.name
                                text:"Emo : "+supervisor.getEmoStatus().toString()
                                font.pixelSize: 15
                            }
                        }
                        Rectangle{
                            width: (parent.width - 351)/4
                            height: parent.height
                            Text{
                                id: text_status_remote
                                anchors.centerIn: parent
                                font.family: font_noto_r.name
                                text:"Remote : "+supervisor.getRemoteStatus().toString()
                                font.pixelSize: 15
                            }
                        }
                    }
                }
            }
        }

        Rectangle{
            id: btn_menu
            width: 120
            height: width
            anchors.right: parent.right
            anchors.rightMargin: 50
            anchors.top: parent.top
            anchors.topMargin: 50 + row_category.height
            color: "transparent"
            radius: 30
            Behavior on width{
                NumberAnimation{
                    duration: 500;
                }
            }
            Image{
                id: image_btn_menu
                source:"icon/btn_reset2.png"
                scale: 1-(120-parent.width)/120
                anchors.centerIn: parent
            }
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    click_sound.play();
                    supervisor.writelog("[USER INPUT] SETTING PAGE -> BACKPAGE");
                    if(check_update()){
                        popup_changed.open();
                    }else{
                        backPage();
                    }
                }
            }
        }

        Column{
            anchors.bottom: area_setting_robot.bottom
            anchors.right: parent.right
            anchors.rightMargin: (parent.width - area_setting_robot.width - area_setting_robot.x - btn_default.width)/2
            spacing: 30
            Rectangle{
                id: btn_manager
                width: 180
                height: 60
                radius: 10
                visible: is_admin
                color:"transparent"
                border.width: 1
                border.color: "#7e7e7e"
                Text{
                    anchors.centerIn: parent
                    text: "관리자 메뉴"
                    font.family: font_noto_r.name
                    font.pixelSize: 20
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked:{
                        supervisor.writelog("[USER INPUT] SETTING PAGE -> SHOW MANAGER MENU");
                        if(is_admin){
                            popup_manager.open();
                        }else{
                            popup_password.open();
                            popup_password.open_menu = true;
                        }
                    }
                }
            }
            Rectangle{
                id: btn_default
                width: 180
                height: 60
                radius: 10
                color:"transparent"
                border.width: 1
                border.color: "#7e7e7e"
                Text{
                    anchors.centerIn: parent
                    text: "설정 초기화"
                    font.family: font_noto_r.name
                    font.pixelSize: 25
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked:{
                        supervisor.writelog("[USER INPUT] SETTING PAGE -> RESET DEFAULT");
                        init();
                    }
                }
            }
            Rectangle{
                id: btn_confirm
                width: 180
                height: 60
                radius: 10
                color: "#12d27c"
                border.width: 1
                border.color: "#12d27c"
                Text{
                    anchors.centerIn: parent
                    text: "Confirm"
                    font.family: font_noto_r.name
                    font.pixelSize: 25
                    color: "white"
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked:{
                        save();
                    }
                }
            }
        }
    }

    Popup{
        id: popup_robot_details
        anchors.centerIn: parent
        width: 1280
        height : 600
        closePolicy: Popup.NoAutoClose
        background:Rectangle{
            anchors.fill: parent
        }
        Rectangle{
            width: parent.width
            height: parent.height

            Column{
                anchors.centerIn: parent
                Rectangle{
                    width: popup_robot_details.width*0.8
                    height: popup_robot_details.height*0.25
                    color: "transparent"
                    Rectangle{
                        width: 200
                        height: 40
                        color: "black"
                        Text{
                            anchors.centerIn: parent
                            font.family: font_noto_b.name
                            text:"전  원"
                            color: "white"
                            font.pixelSize: 20
                        }
                    }
                    Column{
                        anchors.centerIn: parent
                        Grid{
                            id: grid_power
                            rows: 2
                            columns: 5
                            horizontalItemAlignment: Grid.AlignHCenter
                            verticalItemAlignment: Grid.AlignVCenter
                            spacing: 5
                            Text{
                                text: "입력전원"
                                font.family: font_noto_r.name
                                font.pixelSize: 15
                            }
                            Text{
                                text: "출력전원"
                                font.family: font_noto_r.name
                                font.pixelSize: 15
                            }
                            Text{
                                text: "전   류"
                                font.family: font_noto_r.name
                                font.pixelSize: 15
                            }
                            Text{
                                text: "순간전력"
                                font.family: font_noto_r.name
                                font.pixelSize: 15
                            }
                            Text{
                                text: "누적전력"
                                font.family: font_noto_r.name
                                font.pixelSize: 15
                            }
                            Item_ProgressBar{
                                id: bar_battery_in
                                width: 100
                                height: 25
                                to: 56
                                from: 0
                                value: 0
                                Text{
                                    id: text_battery_in
                                    anchors.centerIn: parent
                                    text: parent.value + " V"
                                    font.family: font_noto_r.name
                                    font.pixelSize: 15
                                }
                            }
                            Item_ProgressBar{
                                id: bar_battery_out
                                width: 100
                                height: 25
                                to: 56
                                from: 0
                                value: 0
                                Text{
                                    id: text_battery_out
                                    anchors.centerIn: parent
                                    text: parent.value + " V"
                                    font.family: font_noto_r.name
                                    font.pixelSize: 15
                                }
                            }
                            Item_ProgressBar{
                                id: bar_battery_cur
                                width: 100
                                height: 25
                                to: 20
                                from: 0
                                value: 0
                                Text{
                                    id: text_battery_cur
                                    anchors.centerIn: parent
                                    text: parent.value + " A"
                                    font.family: font_noto_r.name
                                    font.pixelSize: 15
                                }
                            }
                            Item_ProgressBar{
                                id: bar_power
                                width: 100
                                height: 25
                                to: 1
                                from: 0
                                value: 0
                                Text{
                                    id: text_power
                                    anchors.centerIn: parent
                                    text: parent.value + " W"
                                    font.family: font_noto_r.name
                                    font.pixelSize: 15
                                }
                            }
                            Item_ProgressBar{
                                id: bar_powert
                                width: 100
                                height: 25
                                to: 1
                                from: 0
                                value: 0
                                Text{
                                    id: text_powert
                                    anchors.centerIn: parent
                                    text: parent.value + " Wh"
                                    font.family: font_noto_r.name
                                    font.pixelSize: 15
                                }
                            }
                        }

                        Grid{
                            rows: 2
                            columns: 6
                            horizontalItemAlignment: Grid.AlignHCenter
                            verticalItemAlignment: Grid.AlignVCenter
                            spacing: 5
                            Text{
                                text: "충전 상태"
                                font.family: font_noto_r.name
                                font.pixelSize: 15
                            }
                            Text{
                                text: "전원 공급"
                                font.family: font_noto_r.name
                                font.pixelSize: 15
                            }
                            Text{
                                text: "비상스위치"
                                font.family: font_noto_r.name
                                font.pixelSize: 15
                            }
                            Text{
                                text: "원격스위치"
                                font.family: font_noto_r.name
                                font.pixelSize: 15
                            }
                            Text{
                                text: "모터 락"
                                font.family: font_noto_r.name
                                font.pixelSize: 15
                            }
                            Text{
                                text: "그리기"
                                font.family: font_noto_r.name
                                font.pixelSize: 15
                            }
                            Item_ProgressBar{
                                id: bar_charging
                                width: 100
                                height: 25
                                Text{
                                    id: text_charging
                                    anchors.centerIn: parent
                                    text: "연결 안됨"
                                    font.family: font_noto_r.name
                                    font.pixelSize: 15
                                }
                            }
                            Item_ProgressBar{
                                id: bar_powerstate
                                width: 100
                                height: 25
                                color: color_gray
                                Text{
                                    id: text_powerstate
                                    anchors.centerIn: parent
                                    text: "공급 안됨"
                                    font.family: font_noto_r.name
                                    font.pixelSize: 15
                                }
                            }
                            Item_ProgressBar{
                                id: bar_emo
                                width: 100
                                height: 25
                                color: color_gray
                                Text{
                                    id: text_emo
                                    anchors.centerIn: parent
                                    text: "안 눌림"
                                    font.family: font_noto_r.name
                                    font.pixelSize: 15
                                }
                            }
                            Item_ProgressBar{
                                id: bar_remote
                                width: 100
                                height: 25
                                color: color_gray
                                Text{
                                    id: text_remote
                                    anchors.centerIn: parent
                                    text: "안 눌림"
                                    font.family: font_noto_r.name
                                    font.pixelSize: 15
                                }
                            }
                            Item_ProgressBar{
                                id: bar_motorlock
                                width: 100
                                height: 25
                                color: color_gray
                                Text{
                                    id: text_motorlock
                                    anchors.centerIn: parent
                                    text: "풀림"
                                    font.family: font_noto_r.name
                                    font.pixelSize: 15
                                }
                            }
                            Item_ProgressBar{
                                id: bar_drawing
                                width: 100
                                height: 25
                                color: color_gray
                                Text{
                                    id: text_drawing
                                    anchors.centerIn: parent
                                    text: "멈춤"
                                    font.family: font_noto_r.name
                                    font.pixelSize: 15
                                }
                            }
                        }

                    }
                }
                Rectangle{
                    width: area_setting_motor.width*0.8
                    height: area_setting_motor.height*0.25
                    color: "transparent"
                    Rectangle{
                        width: 200
                        height: 40
                        color: "black"
                        Text{
                            anchors.centerIn: parent
                            font.family: font_noto_b.name
                            text:"모터 상태"
                            color: "white"
                            font.pixelSize: 20
                        }
                    }
                    Column{
                        anchors.centerIn: parent
                        Row{
                            spacing: 10
                            Rectangle{
                                width: 150
                                height: 40
                                color: "transparent"
                                radius: 10
                                anchors.verticalCenter: parent.verticalCenter
                                Text{
                                    text: "모터 1"
                                    anchors.centerIn: parent
                                    font.family: font_noto_r.name
                                    font.pixelSize: 25
                                }
                            }

                            Grid{
                                rows: 2
                                columns: 5
                                horizontalItemAlignment: Grid.AlignHCenter
                                verticalItemAlignment: Grid.AlignVCenter
                                spacing: 5
                                Text{
                                    text: "연결상태"
                                    font.family: font_noto_r.name
                                    font.pixelSize: 15
                                }
                                Text{
                                    text: "상 태"
                                    font.family: font_noto_r.name
                                    font.pixelSize: 15
                                }
                                Text{
                                    text: "제어기 온도"
                                    font.family: font_noto_r.name
                                    font.pixelSize: 15
                                }
                                Text{
                                    text: "모터 온도"
                                    font.family: font_noto_r.name
                                    font.pixelSize: 15
                                }
                                Text{
                                    text: "전  류"
                                    font.family: font_noto_r.name
                                    font.pixelSize: 15
                                }
                                Item_ProgressBar{
                                    id: bar_con1
                                    width: 100
                                    height: 25
                                    color: color_red
                                    Text{
                                        id: text_con1
                                        anchors.centerIn: parent
                                        text: "연결 안됨"
                                        font.family: font_noto_r.name
                                        font.pixelSize: 15
                                    }
                                }
                                Item_ProgressBar{
                                    id: bar_status1
                                    width: 100
                                    height: 25
                                    color: color_gray
                                    Text{
                                        id: text_status1
                                        anchors.centerIn: parent
                                        text: "준비 안됨"
                                        font.family: font_noto_r.name
                                        font.pixelSize: 15
                                    }
                                }
                                Item_ProgressBar{
                                    id: bar_temp1
                                    width: 100
                                    height: 25
                                    from: 20
                                    to: 70
                                    warning: true
                                    value_margin: 60
                                    Text{
                                        id: text_temp1
                                        anchors.centerIn: parent
                                        text: parent.value + " 도"
                                        font.family: font_noto_r.name
                                        font.pixelSize: 15

                                    }
                                }
                                Item_ProgressBar{
                                    id: bar_mtemp1
                                    width: 100
                                    height: 25
                                    from: 20
                                    to: 70
                                    warning: true
                                    value_margin: 60
                                    Text{
                                        id: text_mtemp1
                                        anchors.centerIn: parent
                                        text: parent.value + " 도"
                                        font.family: font_noto_r.name
                                        font.pixelSize: 15

                                    }
                                }
                                Item_ProgressBar{
                                    id: bar_cur1
                                    width: 100
                                    height: 25
                                    warning: true
                                    from: 0
                                    to: 15
                                    value_margin: 6
                                    Text{
                                        id: text_cur1
                                        anchors.centerIn: parent
                                        text: parent.value + " A"
                                        font.family: font_noto_r.name
                                        font.pixelSize: 15
                                    }
                                }
                            }

                        }
                        Row{
                            spacing: 10
                            Rectangle{
                                width: 150
                                height: 40
                                radius: 10
                                anchors.verticalCenter: parent.verticalCenter
                                color: "transparent"

                                Text{
                                    text: "모터 2"
                                    anchors.centerIn: parent
                                    font.family: font_noto_r.name
                                    font.pixelSize: 25
                                }
                            }
                            Grid{
                                rows: 2
                                columns: 5
                                horizontalItemAlignment: Grid.AlignHCenter
                                verticalItemAlignment: Grid.AlignVCenter
                                spacing: 5
                                Text{
                                    text: "연결상태"
                                    font.family: font_noto_r.name
                                    font.pixelSize: 15
                                }
                                Text{
                                    text: "상 태"
                                    font.family: font_noto_r.name
                                    font.pixelSize: 15
                                }
                                Text{
                                    text: "제어기 온도"
                                    font.family: font_noto_r.name
                                    font.pixelSize: 15
                                }
                                Text{
                                    text: "모터 온도"
                                    font.family: font_noto_r.name
                                    font.pixelSize: 15
                                }
                                Text{
                                    text: "전  류"
                                    font.family: font_noto_r.name
                                    font.pixelSize: 15
                                }
                                Item_ProgressBar{
                                    id: bar_con2
                                    width: 100
                                    height: 25
                                    color: color_red
                                    Text{
                                        id: text_con2
                                        anchors.centerIn: parent
                                        text: "연결 안됨"
                                        font.family: font_noto_r.name
                                        font.pixelSize: 15
                                    }
                                }
                                Item_ProgressBar{
                                    id: bar_status2
                                    width: 100
                                    height: 25
                                    color: color_gray
                                    Text{
                                        id: text_status2
                                        anchors.centerIn: parent
                                        text: "준비 안됨"
                                        font.family: font_noto_r.name
                                        font.pixelSize: 15
                                    }
                                }
                                Item_ProgressBar{
                                    id: bar_temp2
                                    width: 100
                                    height: 25
                                    from: 20
                                    to: 70
                                    warning: true
                                    value_margin: 60
                                    Text{
                                        id: text_temp2
                                        anchors.centerIn: parent
                                        text: parent.value + " 도"
                                        font.family: font_noto_r.name
                                        font.pixelSize: 15
                                    }
                                }
                                Item_ProgressBar{
                                    id: bar_mtemp2
                                    width: 100
                                    height: 25
                                    from: 20
                                    to: 70
                                    warning: true
                                    value_margin: 60
                                    Text{
                                        id: text_mtemp2
                                        anchors.centerIn: parent
                                        text: parent.value + " 도"
                                        font.family: font_noto_r.name
                                        font.pixelSize: 15
                                    }
                                }
                                Item_ProgressBar{
                                    id: bar_cur2
                                    width: 100
                                    height: 25
                                    warning: true
                                    from: 0
                                    to: 15
                                    value_margin: 6
                                    Text{
                                        id: text_cur2
                                        anchors.centerIn: parent
                                        text: parent.value + " A"
                                        font.family: font_noto_r.name
                                        font.pixelSize: 15
                                    }
                                }
                            }
                        }
                    }
                }
                Rectangle{
                    width: area_setting_motor.width*0.8
                    height: area_setting_motor.height*0.25
                    color: "transparent"
                    Rectangle{
                        width: 200
                        height: 40
                        color: "black"
                        Text{
                            anchors.centerIn: parent
                            font.family: font_noto_b.name
                            text:"센서 상태"
                            color: "white"
                            font.pixelSize: 20
                        }
                    }
                    Item_buttons{
                        type: "round_text"
                        text:"뷰 어"
                        fontsize: 30
                        anchors.centerIn: parent
                        width: 150
                        height: 80
                        onClicked:{
                            popup_sensorview.open();
                        }
                    }
                }
            }

            Item_buttons{
                type: "circle_image"
                source:"icon/btn_no.png"
                fontsize: 30
                anchors.top: parent.top
                anchors.right: parent.right
                width: 60
                height: 60
                onClicked:{
                    popup_robot_details.close();
                }
            }
        }
    }

    function save(){
        supervisor.writelog("[USER INPUT] SETTING PAGE -> SETTING CHANGE");
        if(platform_name.ischanged){
            supervisor.setSetting("setting","ROBOT_TYPE/model",platform_name.text);
        }

        if(combo_platform_serial.ischanged){
            supervisor.setSetting("setting","ROBOT_TYPE/serial_num",combo_platform_serial.currentText);
        }

        if(combo_max_calling.ischanged){
            supervisor.setSetting("setting","CALL/call_maximum",combo_max_calling.currentText);
        }

        supervisor.setPreset(cur_preset);
        if(combo_language.ischanged){
            var str_lan;
            if(combo_language.currentIndex === 0){
                str_lan = "KR";

            }else if(combo_language.currentIndex === 1){
                str_lan = "US";
            }
            supervisor.setSetting("setting","UI/langauge",str_lan);
            supervisor.setLangauge(str_lan);
        }

        if(combo_multirobot.ischanged){
            if(combo_multirobot.currentIndex == 0){
                supervisor.setSetting("setting","USE_SLAM/use_multirobot","false");
            }else{
                supervisor.setSetting("setting","USE_SLAM/use_multirobot","true");
            }
        }

        if(combo_server_calling.ischanged){
            if(combo_server_calling.currentIndex == 0){
                supervisor.setSetting("setting","SERVER/use_server_call","false");
            }else{
                supervisor.setSetting("setting","SERVER/use_server_call","true");
            }
        }

        if(combo_platform_type.ischanged){
            if(combo_platform_type.currentIndex == 0){
                supervisor.setSetting("setting","ROBOT_TYPE/type","SERVING");
            }else if(combo_platform_type.currentIndex == 1){
                supervisor.setSetting("setting","ROBOT_TYPE/type","CALLING");
            }else if(combo_platform_type.currentIndex == 2){
                supervisor.setSetting("setting","ROBOT_TYPE/type","BOTH");
            }else if(combo_platform_type.currentIndex == 3){
                supervisor.setSetting("setting","ROBOT_TYPE/type","CLEANING");
            }
        }

        if(combo_tray_num.ischanged){
            supervisor.setSetting("setting","ROBOT_TYPE/tray_num",combo_tray_num.currentText);
        }

        if(slider_volume_bgm.ischanged){
            supervisor.setSetting("setting","UI/volume_bgm",slider_volume_bgm.value.toFixed(0));
            volume_bgm = slider_volume_bgm.value.toFixed(0);
        }

        if(slider_volume_voice.ischanged){
            supervisor.setSetting("setting","UI/volume_voice",slider_volume_voice.value.toFixed(0));
            volume_voice = slider_volume_voice.value.toFixed(0);
        }

        if(slider_volume_button.ischanged){
            supervisor.setSetting("setting","UI/volume_button",slider_volume_button.value.toFixed(0));
            volume_button = slider_volume_button.value.toFixed(0);
        }
        if(combo_movingpage.ischanged){
            if(combo_movingpage.currentIndex == 0)
                supervisor.setSetting("setting","UI/moving_face","false");
            else
                supervisor.setSetting("setting","UI/moving_face","true");
        }

        if(combo_comeback_preset.ischanged){
            supervisor.setSetting("setting","UI/comeback_preset",combo_comeback_preset.currentIndex.toString());
        }
        if(combo_voice_mode.ischanged){
            if(combo_voice_mode.currentIndex == 0){
                supervisor.setSetting("setting","UI/voice_mode","child");
            }else if(combo_voice_mode.currentIndex == 1){
                supervisor.setSetting("setting","UI/voice_mode","woman");
            }
            readVoice();
        }

        if(combo_use_tray.ischanged){
            if(combo_use_tray.currentIndex == 0)
                supervisor.setSetting("setting","USE_UI/use_tray","false");
            else
                supervisor.setSetting("setting","USE_UI/use_tray","true");
        }

        if(combo_use_calling_notice.ischanged){
            if(combo_use_calling_notice.currentIndex == 0){
                supervisor.setSetting("setting","USE_UI/combo_use_calling_notice","false");
            }else{
                supervisor.setSetting("setting","USE_UI/combo_use_calling_notice","true");
            }
        }
        if(combo_resting_lock.ischanged){
            if(combo_resting_lock.currentIndex == 0){
                supervisor.setSetting("setting","USE_UI/use_restinglock","false");
            }else{
                supervisor.setSetting("setting","USE_UI/use_restinglock","true");
            }
        }

        if(fms_id.ischanged){
            supervisor.setSetting("setting","SERVER/fms_id",fms_id.text);
        }

        if(fms_pw.ischanged){
            supervisor.setSetting("setting","SERVER/fms_pw",fms_pw.text);
        }

        if(ip_1.ischanged||ip_2.ischanged||ip_3.ischanged||ip_4.ischanged){
            var ip_str = ip_1.text + "." + ip_2.text + "." + ip_3.text + "." + ip_4.text;
            supervisor.setSetting("setting","NETWORK/wifi_ip",ip_str);
        }

        if(gateway_1.ischanged||gateway_2.ischanged||gateway_3.ischanged||gateway_4.ischanged){
            var ip_str = gateway_1.text + "." + gateway_2.text + "." + gateway_3.text + "." + gateway_4.text;
            supervisor.setSetting("setting","NETWORK/wifi_gateway",ip_str);
        }

        if(dnsmain_1.ischanged||dnsmain_2.ischanged||dnsmain_3.ischanged||dnsmain_4.ischanged){
            var ip_str = dnsmain_1.text + "." + dnsmain_2.text + "." + dnsmain_3.text + "." + dnsmain_4.text;
            supervisor.setSetting("setting","NETWORK/wifi_dnsmain",ip_str);
        }


        if(wheel_base.ischanged){
            supervisor.setSetting("static","ROBOT_HW/wheel_base",wheel_base.text);
        }
        if(wheel_radius.ischanged){
            supervisor.setSetting("static","ROBOT_HW/wheel_radius",wheel_radius.text);
        }
        if(radius.ischanged){
            supervisor.setSetting("static","ROBOT_HW/robot_radius",radius.text);
        }
        if(radius.ischanged){
            supervisor.setSetting("static","ROBOT_HW/robot_radius",radius.text);
        }
        if(robot_length.ischanged){
            supervisor.setSetting("static","ROBOT_HW/robot_length",radius.text);
        }

        if(obs_height_min.ischanged){
            supervisor.setSetting("setting","OBSTACLE/obs_height_min",obs_height_min.text);
        }

        if(obs_height_max.ischanged){
            supervisor.setSetting("setting","OBSTACLE/obs_height_max",obs_height_max.text);
        }

        if(obs_margin1.ischanged){
            supervisor.setSetting("setting","OBSTACLE/obs_margin1",obs_margin1.text);
        }
        if(obs_margin0.ischanged){
            supervisor.setSetting("setting","OBSTACLE/obs_margin0",obs_margin0.text);
        }
        if(obs_near.ischanged){
            supervisor.setSetting("setting","OBSTACLE/obs_near",obs_near.text);
        }
        if(obs_early_stop_dist.ischanged){
            supervisor.setSetting("setting","OBSTACLE/obs_early_stop_dist",obs_early_stop_dist.text);
        }

        if(obs_detect_area.ischanged){
            supervisor.setSetting("setting","OBSTACLE/obs_detect_area",obs_detect_area.text);
        }

        if(obs_detect_sensitivity.ischanged){
            supervisor.setSetting("setting","OBSTACLE/obs_detect_sensitivity",obs_detect_sensitivity.text);
        }

        if(max_range.ischanged){
            supervisor.setSetting("setting","SENSOR/max_range",max_range.text);
        }

        if(cam_exposure.ischanged){
            supervisor.setSetting("setting","SENSOR/cam_exposure",cam_exposure.text);
        }

        if(obs_preview_time.ischanged){
            supervisor.setSetting("setting","OBSTACLE/obs_preview_time",obs_preview_time.text);
        }

        if(combo_use_avoid.ischanged){
            if(combo_use_avoid.currentIndex == 0){
                supervisor.setSetting("setting","USE_SLAM/use_avoid",false);
            }else{
                supervisor.setSetting("setting","USE_SLAM/use_avoid",true);
            }
        }
        if(combo_auto_update.ischanged){
            if(combo_auto_update.currentIndex === 0){
                supervisor.setSetting("setting","USE_UI/auto_update",false);
            }else{
                supervisor.setSetting("setting","USE_UI/auto_update",true);
            }
        }

        if(combo_use_earlystop_serving.ischanged){
            if(combo_use_earlystop_serving.currentIndex == 0){
                supervisor.setSetting("setting","USE_SLAM/use_earlystop_serving",false);
            }else{
                supervisor.setSetting("setting","USE_SLAM/use_earlystop_serving",true);
            }
        }

        if(combo_use_earlystop_resting.ischanged){
            if(combo_use_earlystop_resting.currentIndex == 0){
                supervisor.setSetting("setting","USE_SLAM/use_earlystop_resting",false);
            }else{
                supervisor.setSetting("setting","USE_SLAM/use_earlystop_resting",true);
            }
        }

        if(combo_use_obs_near.ischanged){
            if(combo_use_obs_near.currentIndex == 0){
                supervisor.setSetting("setting","USE_SLAM/use_obs_near",false);
            }else{
                supervisor.setSetting("setting","USE_SLAM/use_obs_near",true);
            }
        }

        if(combo_use_obs_preview.ischanged){
            if(combo_use_obs_preview.currentIndex == 0){
                supervisor.setSetting("setting","USE_SLAM/use_obs_preview",false);
            }else{
                supervisor.setSetting("setting","USE_SLAM/use_obs_preview",true);
            }
        }
        if(combo_use_pivot_obs.ischanged){
            if(combo_use_pivot_obs.currentIndex == 0){
                supervisor.setSetting("setting","USE_SLAM/use_pivot_obs",false);
            }else{
                supervisor.setSetting("setting","USE_SLAM/use_pivot_obs",true);
            }
        }

        if(st_v.ischanged){
            supervisor.setSetting("update","DRIVING/st_v",st_v.text);
        }

        if(combo_wheel_dir.ischanged){
            supervisor.setSetting("update","MOTOR/wheel_dir",combo_wheel_dir.currentText);
        }

        if(combo_left_id.ischanged){
            supervisor.setSetting("update","MOTOR/left_id",combo_left_id.currentText);
        }

        if(combo_right_id.ischanged){
            supervisor.setSetting("update","MOTOR/right_id",combo_right_id.currentText);
        }

        if(gear_ratio.ischanged){
            supervisor.setSetting("update","MOTOR/gear_ratio",gear_ratio.text);
        }

        if(goal_near_th.ischanged){
            supervisor.setSetting("update","DRIVING/goal_near_th",goal_near_th.text);
        }
        if(k_curve.ischanged){
            supervisor.setSetting("update","DRIVING/k_curve",k_curve.text);
        }
        if(k_v.ischanged){
            supervisor.setSetting("update","DRIVING/k_v",k_v.text);
        }
        if(k_w.ischanged){
            supervisor.setSetting("update","DRIVING/k_w",k_w.text);
        }
        if(k_dd.ischanged){
            supervisor.setSetting("update","DRIVING/k_dd",k_dd.text);
        }
        if(path_delta_v_acc_gain.ischanged){
            supervisor.setSetting("update","DRIVING/path_delta_v_acc_gain",path_delta_v_acc_gain.text);
        }
        if(path_delta_v_dec_gain.ischanged){
            supervisor.setSetting("update","DRIVING/path_delta_v_dec_gain",path_delta_v_dec_gain.text);
        }
        if(path_ref_v_gain.ischanged){
            supervisor.setSetting("update","DRIVING/path_ref_v_gain",path_ref_v_gain.text);
        }
        if(path_shifting_val.ischanged){
            supervisor.setSetting("update","DRIVING/path_shifting_val",path_shifting_val.text);
        }
        if(slam_submap_cnt.ischanged){
            supervisor.setSetting("update","SLAM/slam_submap_cnt",slam_submap_cnt.text);
        }
        if(slam_lc_dist.ischanged){
            supervisor.setSetting("update","SLAM/slam_lc_dist",slam_lc_dist.text);
        }
        if(icp_init_error.ischanged){
            supervisor.setSetting("setting","INITIALIZATION/icp_init_error",icp_init_error.text);
        }
        if(icp_init_ratio.ischanged){
            supervisor.setSetting("setting","INITIALIZATION/icp_init_ratio",icp_init_ratio.text);
        }

        if(slam_lc_icp_dist.ischanged){
            supervisor.setSetting("update","SLAM/slam_lc_icp_dist",slam_lc_icp_dist.text);
        }
        if(map_size.ischanged){
            supervisor.setSetting("update","SLAM/map_size",map_size.text);
        }
        if(grid_size.ischanged){
            supervisor.setSetting("update","SLAM/grid_size",grid_size.text);
        }


//        if(combo_camera_model.ischanged){
//            supervisor.setSetting("SENSOR/camera_model",Number(combo_camera_model.currentIndex));
//        }

        if(combo_use_motorcurrent.ischanged){
            if(combo_use_motorcurrent.currentIndex == 0){
                supervisor.setSetitng("setting","USE_UI/use_current_pause","false");
            }else{
                supervisor.setSetitng("setting","USE_UI/use_current_pause","true");
            }
        }

        if(pause_check_ms.ischanged){
            supervisor.setSetting("update","DRIVING/pause_check_ms",pause_check_ms.text);
        }
        if(pause_motor_current.ischanged){
            supervisor.setSetting("update","DRIVING/pause_motor_current",pause_motor_current.text);
        }

        if(k_p.ischanged){
            supervisor.setSetting("update","MOTOR/k_p",k_p.text);
        }

        if(k_i.ischanged){
            supervisor.setSetting("update","MOTOR/k_i",k_i.text);
        }

        if(k_d.ischanged){
            supervisor.setSetting("update","MOTOR/k_d",k_d.text);
        }

        if(motor_limit_v.ischanged){
            supervisor.setSetting("update","MOTOR/limit_v",motor_limit_v.text);
        }

        if(motor_limit_v_acc.ischanged){
            supervisor.setSetting("update","MOTOR/limit_v_acc",motor_limit_v_acc.text);
        }

        if(motor_limit_w.ischanged){
            supervisor.setSetting("update","MOTOR/limit_w",motor_limit_w.text);
        }

        if(motor_limit_w_acc.ischanged){
            supervisor.setSetting("update","MOTOR/limit_w_acc",motor_limit_w_acc.text);
        }

        if(look_ahead_dist.ischanged){
            supervisor.setSetting("update","DRIVING/look_ahead_dist"         ,look_ahead_dist.text);
        }

        if(min_look_ahead_dist.ischanged){
            supervisor.setSetting("update","DRIVING/min_look_ahead_dist"    ,min_look_ahead_dist.text);
        }

        if(obs_deadzone.ischanged){
            supervisor.setSetting("setting","OBSTACLE/obs_deadzone"           ,obs_deadzone.text);
        }

        if(obs_wait_time.ischanged){
            supervisor.setSetting("setting","OBSTACLE/obs_wait_time"          ,obs_wait_time.text);
        }

        if(path_out_dist.ischanged){
            supervisor.setSetting("update","DRIVING/path_out_dist"          ,path_out_dist.text);
        }

        if(icp_dist.ischanged){
            supervisor.setSetting("update","LOCALIZATION/icp_dist"               ,icp_dist.text);
        }

        if(icp_error.ischanged){
            supervisor.setSetting("update","LOCALIZATION/icp_error"              ,icp_error.text);
        }

        if(icp_near.ischanged){
            supervisor.setSetting("update","LOCALIZATION/icp_near"               ,icp_near.text);
        }

        if(icp_odometry_weight.ischanged){
            supervisor.setSetting("update","LOCALIZATION/icp_odometry_weight"    ,icp_odometry_weight.text);
        }

        if(icp_ratio.ischanged){
            supervisor.setSetting("update","LOCALIZATION/icp_ratio"              ,icp_ratio.text);
        }

        if(icp_repeat_dist.ischanged){
            supervisor.setSetting("update","LOCALIZATION/icp_repeat_dist"        ,icp_repeat_dist.text);
        }

        if(icp_repeat_time.ischanged){
            supervisor.setSetting("update","LOCALIZATION/icp_repeat_time"        ,icp_repeat_time.text);

        }

        if(goal_dist.ischanged){
            supervisor.setSetting("update","DRIVING/goal_dist"              ,goal_dist.text);
        }

        if(goal_v.ischanged){
            supervisor.setSetting("update","DRIVING/goal_v"                 ,goal_v.text);
        }

        if(goal_th.ischanged){
            supervisor.setSetting("update","DRIVING/goal_th"                ,goal_th.text);
        }

        if(goal_near_dist.ischanged){
            supervisor.setSetting("update","DRIVING/goal_near_dist"         ,goal_near_dist.text);
        }

        supervisor.readSetting();
        if(is_reset_slam)
            supervisor.slam_ini_reload();

        is_reset_slam = false;

        backPage();
    }

    function init(){
        supervisor.writelog("[QML] SETTING PAGE init");
        wifi_check();

        cur_preset = parseInt(supervisor.getSetting("update","DRIVING","cur_preset"));
        slider_volume_system.value = supervisor.getSystemVolume();
        platform_name.text = supervisor.getSetting("setting","ROBOT_TYPE","model");
        combo_platform_serial.currentIndex = parseInt(supervisor.getSetting("setting","ROBOT_TYPE","serial_num"))
        radius.text = supervisor.getSetting("static","ROBOT_HW","robot_radius");

        combo_tray_num.currentIndex = supervisor.getSetting("setting","ROBOT_TYPE","tray_num")-1;

        if(supervisor.getSetting("setting","USE_SLAM","use_multirobot")==="true"){
            combo_multirobot.currentIndex = 1;
        }else{
            combo_multirobot.currentIndex = 0;
        }

        if(supervisor.getSetting("setting","SERVER","use_server_call")==="true"){
            combo_server_calling.currentIndex = 1;
        }else{
            combo_server_calling.currentIndex = 0;
        }

        if(supervisor.getSetting("setting","UI","langauge") === "KR"){
            combo_language.currentIndex = 0;
        }else if(supervisor.getSetting("setting","UI","langauge") === "US"){
            combo_language.currentIndex = 1;
        }

        if(supervisor.getSetting("setting","USE_UI","auto_update") === "true"){
            combo_auto_update.currentIndex = 1;
        }else if(supervisor.getSetting("setting","USE_UI","auto_update") === "false"){
            combo_auto_update.currentIndex = 0;
        }



        if(supervisor.getSetting("setting","ROBOT_TYPE","type") === "SERVING"){
            combo_platform_type.currentIndex = 0;
        }else if(supervisor.getSetting("setting","ROBOT_TYPE","type") === "CALLING"){
            combo_platform_type.currentIndex = 1;
        }else if(supervisor.getSetting("setting","ROBOT_TYPE","type") === "BOTH"){
            combo_platform_type.currentIndex = 2;
        }else if(supervisor.getSetting("setting","ROBOT_TYPE","type") === "CLEANING"){
            combo_platform_type.currentIndex = 3;
        }


        fms_id.text = supervisor.getSetting("setting","SERVER","fms_id");
        fms_pw.text = supervisor.getSetting("setting","SERVER","fms_pw");
        combo_max_calling.currentIndex = parseInt(supervisor.getSetting("setting","CALL","call_maximum")) - 1;
        wheel_base.text = supervisor.getSetting("static","ROBOT_HW","wheel_base");
        wheel_radius.text = supervisor.getSetting("static","ROBOT_HW","wheel_radius");

        left_camera_tf.text = supervisor.getSetting("static","SENSOR","left_camera_tf");
        right_camera_tf.text = supervisor.getSetting("static","SENSOR","right_camera_tf");
        cam_exposure.text = supervisor.getSetting("setting","SENSOR","cam_exposure");

        icp_dist.text = supervisor.getSetting("update","LOCALIZATION","icp_dist");
        icp_error.text = supervisor.getSetting("update","LOCALIZATION","icp_error");
        icp_near.text = supervisor.getSetting("update","LOCALIZATION","icp_near");
        icp_odometry_weight.text = supervisor.getSetting("update","LOCALIZATION","icp_odometry_weight");
        icp_ratio.text = supervisor.getSetting("update","LOCALIZATION","icp_ratio");
        icp_repeat_dist.text = supervisor.getSetting("update","LOCALIZATION","icp_repeat_dist");
        icp_repeat_time.text = supervisor.getSetting("update","LOCALIZATION","icp_repeat_time");

        obs_deadzone.text = supervisor.getSetting("setting","OBSTACLE","obs_deadzone");
        obs_preview_time.text = supervisor.getSetting("setting","OBSTACLE","obs_preview_time");
        obs_wait_time.text = supervisor.getSetting("setting","OBSTACLE","obs_wait_time");
        path_out_dist.text = supervisor.getSetting("update","DRIVING","path_out_dist");
        st_v.text = supervisor.getSetting("update","DRIVING","st_v");
        min_look_ahead_dist.text = supervisor.getSetting("update","DRIVING","min_look_ahead_dist");
        goal_dist.text = supervisor.getSetting("update","DRIVING","goal_dist");
        goal_th.text = supervisor.getSetting("update","DRIVING","goal_th");
        goal_v.text = supervisor.getSetting("update","DRIVING","goal_v");
        goal_near_dist.text = supervisor.getSetting("update","DRIVING","goal_near_dist");
        goal_near_th.text = supervisor.getSetting("update","DRIVING","goal_near_th");
        k_curve.text = supervisor.getSetting("update","DRIVING","k_curve");
        k_v.text = supervisor.getSetting("update","DRIVING","k_v");
        k_w.text = supervisor.getSetting("update","DRIVING","k_w");
        k_dd.text = supervisor.getSetting("update","DRIVING","k_dd");
        path_delta_v_acc_gain.text = supervisor.getSetting("update","DRIVING","path_delta_v_acc_gain");
        path_delta_v_dec_gain.text = supervisor.getSetting("update","DRIVING","path_delta_v_dec_gain");
        path_ref_v_gain.text = supervisor.getSetting("update","DRIVING","path_ref_v_gain");
        path_shifting_val.text = supervisor.getSetting("update","DRIVING","path_shifting_val");


        slam_submap_cnt.text = supervisor.getSetting("update","SLAM","slam_submap_cnt");
        slam_lc_dist.text = supervisor.getSetting("update","SLAM","slam_lc_dist");
        slam_lc_icp_dist.text = supervisor.getSetting("update","SLAM","slam_lc_icp_dist");
        map_size.text = supervisor.getSetting("update","SLAM","map_size");
        grid_size.text = supervisor.getSetting("update","SLAM","grid_size");
        icp_init_ratio.text = supervisor.getSetting("setting","INITIALIZATION","icp_init_ratio");
        icp_init_error.text = supervisor.getSetting("setting","INITIALIZATION","icp_init_error");

        motor_limit_v.text = supervisor.getSetting("update","MOTOR","limit_v");
        motor_limit_v_acc.text = supervisor.getSetting("update","MOTOR","limit_v_acc");
        motor_limit_w.text = supervisor.getSetting("update","MOTOR","limit_w");
        motor_limit_w_acc.text = supervisor.getSetting("update","MOTOR","limit_w_acc");
        look_ahead_dist.text = supervisor.getSetting("update","DRIVING","look_ahead_dist");

        if(supervisor.getSetting("setting","USE_SLAM","use_obs_preview") === "true"){
            combo_use_obs_preview.currentIndex = 1;
        }else{
            combo_use_obs_preview.currentIndex = 0;
        }
        if(supervisor.getSetting("setting","USE_SLAM","use_avoid") === "true"){
            combo_use_avoid.currentIndex = 1;
        }else{
            combo_use_avoid.currentIndex = 0;
        }
        if(supervisor.getSetting("setting","USE_SLAM","use_pivot_obs") === "true"){
            combo_use_pivot_obs.currentIndex = 1;
        }else{
            combo_use_pivot_obs.currentIndex = 0;
        }
        if(supervisor.getSetting("setting","USE_SLAM","use_obs_near") === "true"){
            combo_use_obs_near.currentIndex = 1;
        }else{
            combo_use_obs_near.currentIndex = 0;
        }
        if(supervisor.getSetting("setting","USE_SLAM","use_earlystop_resting") === "true"){
            combo_use_earlystop_resting.currentIndex = 1;
        }else{
            combo_use_earlystop_resting.currentIndex = 0;
        }
        if(supervisor.getSetting("setting","USE_SLAM","use_earlystop_serving") === "true"){
            combo_use_earlystop_serving.currentIndex = 1;
        }else{
            combo_use_earlystop_serving.currentIndex = 0;
        }

        slider_volume_bgm.value = Number(supervisor.getSetting("setting","UI","volume_bgm"));
        slider_volume_voice.value = Number(supervisor.getSetting("setting","UI","volume_voice"));
        slider_volume_button.value = Number(supervisor.getSetting("setting","UI","volume_button"));

        text_preset_name_1.text = supervisor.getSetting("setting","PRESET1","name");
        text_preset_name_2.text = supervisor.getSetting("setting","PRESET2","name");
        text_preset_name_3.text = supervisor.getSetting("setting","PRESET3","name");
        text_preset_name_4.text = supervisor.getSetting("setting","PRESET4","name");
        text_preset_name_5.text = supervisor.getSetting("setting","PRESET5","name");

        gear_ratio.text = supervisor.getSetting("update","MOTOR","gear_ratio");
        k_d.text = supervisor.getSetting("update","MOTOR","k_d");
        k_i.text = supervisor.getSetting("update","MOTOR","k_i");
        k_p.text = supervisor.getSetting("update","MOTOR","k_p");

        wifi_ssid.text = supervisor.getCurWifiSSID();
//        wifi_passwd.text = supervisor.getSetting("setting","NETWORK","wifi_passwd");

        combo_left_id.currentIndex = parseInt(supervisor.getSetting("update","MOTOR","left_id"));
        combo_right_id.currentIndex = parseInt(supervisor.getSetting("update","MOTOR","right_id"));

        if(supervisor.getSetting("update","MOTOR","wheel_dir") === "-1"){
            combo_wheel_dir.currentIndex = 0;
        }else{
            combo_wheel_dir.currentIndex = 1;
        }

        pause_motor_current.text = supervisor.getSetting("update","DRIVING","pause_motor_current");
        pause_check_ms.text = supervisor.getSetting("update","DRIVING","pause_check_ms");
        if(supervisor.getSetting("setting","USE_UI","use_current_pause") === "false"){
            combo_use_motorcurrent.currentIndex = 0;
        }else{
            combo_use_motorcurrent.currentIndex = 1;
        }

//        if(supervisor.getSetting("setting","SENSOR","camera_model") === "0"){
//            combo_camera_model.currentIndex = 0;
//        }else{
//            combo_camera_model.currentIndex = 1;
//        }

        if(supervisor.getSetting("setting","UI","moving_face") === "true"){
            combo_movingpage.currentIndex = 1;
        }else{
            combo_movingpage.currentIndex = 0;
        }

        if(supervisor.getSetting("setting","UI","voice_mode") === "woman"){
            combo_voice_mode.currentIndex = 1;
        }else{
            combo_voice_mode.currentIndex = 0;
        }

        combo_comeback_preset.currentIndex = parseInt(supervisor.getSetting("update","DRIVING","comeback_preset"));

        if(supervisor.getSetting("setting","USE_UI","use_tray") === "true"){
            combo_use_tray.currentIndex = 1;
        }else{
            combo_use_tray.currentIndex = 0;
        }

        if(supervisor.getSetting("setting","USE_UI","combo_use_calling_notice") === "true"){
            combo_use_calling_notice.currentIndex = 1;
        }else{
            combo_use_calling_notice.currentIndex = 0;
        }
        if(supervisor.getSetting("setting","USE_UI","use_restinglock") === "true"){
            combo_resting_lock.currentIndex = 1;
        }else{
            combo_resting_lock.currentIndex = 0;
        }
        obs_early_stop_dist.text = supervisor.getSetting("setting","OBSTACLE","obs_early_stop_dist");
        obs_near.text = supervisor.getSetting("setting","OBSTACLE","obs_near");
        obs_margin1.text = supervisor.getSetting("setting","OBSTACLE","obs_margin1");
        obs_margin0.text = supervisor.getSetting("setting","OBSTACLE","obs_margin0");
        obs_detect_area.text = supervisor.getSetting("setting","OBSTACLE","obs_detect_area");
        obs_detect_sensitivity.text = supervisor.getSetting("setting","OBSTACLE","obs_detect_sensitivity");
        obs_height_min.text = supervisor.getSetting("setting","OBSTACLE","obs_height_min");
        max_range.text = supervisor.getSetting("setting","SENSOR","max_range");
        right_camera.text = supervisor.getSetting("static","SENSOR","right_camera_serial");
        left_camera.text = supervisor.getSetting("static","SENSOR","left_camera_serial");

//        var ip = supervisor.getSetting("setting","NETWORK","wifi_ip").split(".");
        var ip = supervisor.getcurIP().split(".");
        if(ip.length >3){
            ip_1.text = ip[0];
            ip_2.text = ip[1];
            ip_3.text = ip[2];
            ip_4.text = ip[3];
        }
        ip = supervisor.getSetting("setting","SERVER","fms_ip").split(".");
        if(ip.length >3){
            server_ip_1.text = ip[0];
            server_ip_2.text = ip[1];
            server_ip_3.text = ip[2];
            server_ip_4.text = ip[3];
        }
        ip = supervisor.getSetting("setting","NETWORK","wifi_gateway").split(".");
        ip = supervisor.getcurGateway().split(".");
        if(ip.length >3){
            gateway_1.text = ip[0];
            gateway_2.text = ip[1];
            gateway_3.text = ip[2];
            gateway_4.text = ip[3];
        }
        ip = supervisor.getSetting("setting","NETWORK","wifi_dnsmain").split(".");
        ip = supervisor.getcurDNS().split(".");
        if(ip.length >3){
            dnsmain_1.text = ip[0];
            dnsmain_2.text = ip[1];
            dnsmain_3.text = ip[2];
            dnsmain_4.text = ip[3];
        }

        voice_test.source = supervisor.getVoice("start_serving");

        //변수 초기화
        platform_name.ischanged = false;
        combo_platform_serial.ischanged = false;
        combo_voice_mode.ischanged = false;
        combo_platform_type.ischanged = false;
        combo_tray_num.ischanged = false;

//        slider_vxy.ischanged = false;
        slider_volume_bgm.ischanged = false;
        slider_volume_voice.ischanged = false;
        slider_volume_button.ischanged = false;

        combo_language.ischanged = false;
        combo_movingpage.ischanged = false;
        combo_comeback_preset.ischanged = false;
//        wifi_passwd.ischanged = false;
        ip_1.ischanged = false;
        ip_2.ischanged = false;
        ip_3.ischanged = false;
        ip_4.ischanged = false;
        gateway_1.ischanged = false;
        gateway_2.ischanged = false;
        gateway_3.ischanged = false;
        gateway_4.ischanged = false;
        dnsmain_1.ischanged = false;
        dnsmain_2.ischanged = false;
        dnsmain_3.ischanged = false;
        dnsmain_4.ischanged = false;

        combo_multirobot.ischanged = false;
        server_ip_1.ischanged = false;
        server_ip_2.ischanged = false;
        combo_server_calling.ischanged = false;
        server_ip_3.ischanged = false;
        server_ip_4.ischanged = false;
        fms_id.ischanged = false;
        fms_pw.ischanged = false;

        wheel_base.ischanged = false;
        wheel_radius.ischanged = false;
        radius.ischanged = false;


        max_range.ischanged = false;
        cam_exposure.ischanged = false;

        st_v.ischanged = false;

        obs_preview_time.ischanged = false;
        combo_use_obs_near.ischanged = false;
        combo_use_earlystop_resting.ischanged = false;
        combo_use_earlystop_serving.ischanged = false;
        combo_use_avoid.ischanged = false;
        combo_use_obs_preview.ischanged = false;
        combo_use_pivot_obs.ischanged = false;


        combo_wheel_dir.ischanged = false;
        combo_left_id.ischanged = false;
        combo_right_id.ischanged = false;
        gear_ratio.ischanged = false;
        k_p.ischanged = false;
        k_i.ischanged = false;
        k_d.ischanged = false;
        combo_use_motorcurrent.ischanged = false;
        combo_camera_model.ischanged = false;
        motor_limit_v.ischanged = false;
        motor_limit_v_acc.ischanged = false;
        motor_limit_w.ischanged = false;
        motor_limit_w_acc.ischanged = false;
        look_ahead_dist.ischanged = false;
        min_look_ahead_dist.ischanged = false;
        obs_deadzone.ischanged = false;
        obs_wait_time.ischanged = false;
        path_out_dist.ischanged = false;
        icp_dist.ischanged = false;
        icp_error.ischanged = false;
        icp_near.ischanged = false;
        icp_odometry_weight.ischanged = false;
        icp_ratio.ischanged = false;
        icp_repeat_dist.ischanged = false;
        icp_repeat_time.ischanged = false;
        goal_dist.ischanged = false;
        goal_v.ischanged = false;
        goal_th.ischanged = false;
        pause_motor_current.ischanged = false;
        pause_check_ms.ischanged = false;
        goal_near_dist.ischanged = false;


        goal_near_th.ischanged = false;
        k_curve.ischanged = false;
        k_v.ischanged = false;
        k_w.ischanged = false;
        k_dd.ischanged = false;
        path_delta_v_acc_gain.ischanged = false;
        path_delta_v_dec_gain.ischanged = false;
        path_ref_v_gain.ischanged = false;
        path_shifting_val.ischanged = false;

        slam_submap_cnt.ischanged = false;
        slam_lc_dist.ischanged = false;
        slam_lc_icp_dist.ischanged = false;
        icp_init_ratio.ischanged = false;
        icp_init_error.ischanged = false;
        map_size.ischanged = false;
        grid_size.ischanged = false;
        combo_auto_update.ischanged = false;


        combo_max_calling.ischanged = false;
        combo_use_tray.ischanged = false;
        combo_resting_lock.ischanged = false;
        combo_use_calling_notice.ischanged = false;
        obs_height_max.ischanged = false;
        obs_height_min.ischanged = false;
        obs_margin1.ischanged = false;
        obs_margin0.ischanged = false;
        obs_near.ischanged = false;
        obs_early_stop_dist.ischanged = false;
        obs_detect_area.ischanged = false;
        obs_detect_sensitivity.ischanged = false;
        robot_length.ischanged = false;
        is_reset_slam = false;
    }

    function check_update(){
        var is_changed = false;

        if(platform_name.ischanged) is_changed = true;
        if(combo_platform_serial.ischanged) is_changed = true;
        if(combo_platform_type.ischanged) is_changed = true;
        if(combo_tray_num.ischanged) is_changed = true;
//        if(slider_vxy.ischanged) is_changed = true;
        if(slider_volume_bgm.ischanged) is_changed = true;
        if(slider_volume_voice.ischanged) is_changed = true;
        if(slider_volume_button.ischanged) is_changed = true;
        if(ip_1.ischanged) is_changed = true;
        if(ip_2.ischanged) is_changed = true;
        if(ip_3.ischanged) is_changed = true;
        if(ip_4.ischanged) is_changed = true;
        if(combo_use_motorcurrent.ischanged) is_changed = true;
        if(pause_motor_current.ischanged) is_changed = true;
        if(pause_check_ms.ischanged) is_changed = true;
        if(combo_camera_model.ischanged) is_changed = true;
        if(gateway_1.ischanged) is_changed = true;
        if(gateway_2.ischanged) is_changed = true;
        if(gateway_3.ischanged) is_changed = true;
        if(gateway_4.ischanged) is_changed = true;
        if(dnsmain_1.ischanged) is_changed = true;
        if(dnsmain_2.ischanged) is_changed = true;
        if(dnsmain_3.ischanged) is_changed = true;
        if(dnsmain_4.ischanged) is_changed = true;
        if(wheel_base.ischanged) is_changed = true;
        if(wheel_radius.ischanged) is_changed = true;
        if(radius.ischanged) is_changed = true;
        if(max_range.ischanged) is_changed = true;
        if(cam_exposure.ischanged) is_changed = true;
        if(st_v.ischanged) is_changed = true;
        if(combo_wheel_dir.ischanged) is_changed = true;
        if(combo_left_id.ischanged) is_changed = true;
        if(combo_right_id.ischanged) is_changed = true;
        if(gear_ratio.ischanged) is_changed = true;
        if(k_p.ischanged) is_changed = true;
        if(k_i.ischanged) is_changed = true;
        if(k_d.ischanged) is_changed = true;
        if(motor_limit_v.ischanged) is_changed = true;
        if(motor_limit_v_acc.ischanged) is_changed = true;
        if(motor_limit_w.ischanged) is_changed = true;
        if(motor_limit_w_acc.ischanged) is_changed = true;
        if(look_ahead_dist.ischanged) is_changed = true;
        if(min_look_ahead_dist.ischanged) is_changed = true;
        if(obs_deadzone.ischanged) is_changed = true;
        if(obs_wait_time.ischanged) is_changed = true;
        if(path_out_dist.ischanged) is_changed = true;
        if(icp_dist.ischanged) is_changed = true;
        if(icp_error.ischanged) is_changed = true;
        if(icp_near.ischanged) is_changed = true;
        if(icp_odometry_weight.ischanged) is_changed = true;
        if(icp_ratio.ischanged) is_changed = true;
        if(icp_repeat_dist.ischanged) is_changed = true;
        if(icp_repeat_time.ischanged) is_changed = true;
        if(goal_dist.ischanged) is_changed = true;
        if(goal_v.ischanged) is_changed = true;
        if(goal_th.ischanged) is_changed = true;
        if(goal_near_dist.ischanged) is_changed = true;
        if(goal_near_th.ischanged) is_changed = true;
        if(k_curve.ischanged) is_changed = true;
        if(k_v.ischanged) is_changed = true;
        if(k_w.ischanged) is_changed = true;
        if(k_dd.ischanged) is_changed = true;
        if(path_delta_v_acc_gain.ischanged) is_changed = true;
        if(path_delta_v_dec_gain.ischanged) is_changed = true;
        if(path_ref_v_gain.ischanged) is_changed = true;
        if(path_shifting_val.ischanged) is_changed = true;
        if(slam_submap_cnt.ischanged) is_changed = true;
        if(slam_lc_dist.ischanged) is_changed = true;
        if(slam_lc_icp_dist.ischanged) is_changed = true;
        if(icp_init_ratio.ischanged) is_changed = true;
        if(icp_init_error.ischanged) is_changed = true;
        if(map_size.ischanged) is_changed = true;
        if(grid_size.ischanged) is_changed = true;
        if(combo_auto_update.ischanged) is_changed = true;

        return is_changed;
    }

    function wifi_check(){
        supervisor.readWifiState("");
    }

    Timer{
        running: true
        interval: 500
        repeat: true
        triggeredOnStart: true
        onTriggered: {

            if(supervisor.getusbsize() > 0){
                btn_usb_download.enabled = true;
            }else{
                btn_usb_download.enabled = false;
            }

            wifi_connection.connection = supervisor.getWifiConnection("");

            if(wifi_connection.connection === 0 && supervisor.getCurWifiSSID() !== "" && supervisor.getcurIP() === ""){
                supervisor.getWifiIP();
            }
            motor_left_id = parseInt(supervisor.getSetting("update","MOTOR","left_id"));
            motor_right_id = parseInt(supervisor.getSetting("update","MOTOR","right_id"));




            //로봇 상태 - 로봇 상태
            if(supervisor.getIPCConnection()){
                //로봇 상태 - 전원
                status_power.state = 2;
                if(supervisor.getBattery() < 30){
                    status_power.state = 1;
                    model_power_issue.append({"name":"배터리잔량 낮음","image":"image/warning.png"});
                }

                bar_battery_in.value = supervisor.getBatteryIn().toFixed(2);
                bar_battery_out.value = supervisor.getBatteryOut().toFixed(2);
                bar_battery_cur.value = supervisor.getBatteryCurrent().toFixed(2);

                bar_power.value = supervisor.getPower().toFixed(3);
                bar_powert.value = supervisor.getPowerTotal().toFixed(3);

                //로봇 상태 - 상태 값
                model_power_issue.clear();

                if(supervisor.getEmoStatus() !== 0){
                    model_power_issue.append({"name":"비상스위치 눌림","image":"image/warning.png"});
                    status_power.state = 1;
                }else if(supervisor.getRemoteStatus() === 0){
                    model_power_issue.append({"name":"원격비상스위치 눌림","image":"image/warning.png"});
                    status_power.state = 1;
                }else if(supervisor.getPowerStatus() === 0){
                    model_power_issue.append({"name":"전원 공급 안됨","image":"icon/icon_error.png"});
                    status_power.state = 0;
                }

                var state = supervisor.getLocalizationState();
                if(state === 0){
                    model_power_issue.append({"name":"위치초기화 필요","image":"icon/icon_error.png"});
                    text_robot.text = "초기화 안됨";
                    status_localization.state = 0;
                }else if(state === 1){
                    model_power_issue.append({"name":"위치초기화 진행중","image":"image/warning.png"});
                    text_robot.text = "초기화 중";
                    status_localization.state = 1;
                }else if(state === 2){
                    text_robot.text = "초기화 완료";
                    status_localization.state = 2;

                    state = supervisor.getStateMoving();
                    if(state === 0){
                        model_power_issue.append({"name":"로봇주행 준비안됨","image":"image/warning.png"});
                        text_robot.text = "준비 안됨";
                    }else if(state === 1){
                        text_robot.text = "준비";
                    }else if(state === 2){
                        text_robot.text = "이동 중";
                    }else if(state === 3){
                        text_robot.text = "대기 중";
                    }else if(state === 4){
                        text_robot.text = "일시정지 중";
                    }

                }else if(state === 3){
                    status_localization.state = 0;
                    model_power_issue.append({"name":"위치초기화 실패","image":"image/warning.png"});
                    text_robot.text = "초기화 실패";
                }


                if(supervisor.getObsState() === 1){
                    status_localization.state = 0;
                    model_power_issue.append({"name":"장애물 겹침","image":"image/warning.png"});
                }

                //모터 상태 - 모터 1
                var state1 = supervisor.getMotorConnection(0);
                //모터 상태 - 모터 2
                var state2 = supervisor.getMotorConnection(1);


                if(!state1){
                    model_power_issue.append({"name":"모터 1 연결안됨","image":"icon/icon_error.png"});
                    status_motor_left.state = 0;
                }else{
                    status_motor_left.state = 2;
                }

                if(!state2){
                    status_motor_right.state = 0;
                    model_power_issue.append({"name":"모터 2 연결안됨","image":"icon/icon_error.png"});
                }else{
                    status_motor_right.state = 2;
                }

                if(state1 && state2){
                    var lstate = supervisor.getLockStatus();
                    if(supervisor.getChargeStatus() !== 0){
                        status_motor_right.state = 1;
                        status_motor_left.state = 1;
                        model_power_issue.append({"name":"충전케이블 연결됨","image":"image/warning.png"});
                    }else if(lstate === 0){
                        status_motor_right.state = 1;
                        status_motor_left.state = 1;
                        model_power_issue.append({"name":"모터락 풀림","image":"image/warning.png"});
                    }else{
                        state1 = supervisor.getMotorStatus(0);
                        if(state1 === 0){
                            model_power_issue.append({"name":"모터 1 준비안됨","image":"icon/icon_error.png"});
                            status_motor_left.state = 1;
                        }else if(state1 === 1){
                            status_motor_left.state = 2;
                        }else{
                            status_motor_left.state = 0;
                            var str_error = "";
                            if(state1 >= 128){
                                str_error += "Unknown ";
                                state1 -= 128;
                            }
                            if(state1 >= 64){
                                str_error += "PS1,2 ";
                                state1 -= 64;
                            }
                            if(state1 >= 32){
                                str_error += "INPUT ";
                                state1 -= 32;
                            }
                            if(state1 >= 16){
                                str_error += "BIG ";
                                state1 -= 16;
                            }
                            if(state1 >= 8){
                                str_error += "CUR ";
                                state1 -= 8;
                            }
                            if(state1 >= 4){
                                str_error += "JAM ";
                                state1 -= 4;
                            }
                            if(state1 >= 2){
                                str_error += "MOD ";
                                state1 -= 2;
                            }
                            model_power_issue.append({"name":"모터 1 "+str_error,"image":"icon/icon_error.png"});
                        }

                        state2 = supervisor.getMotorStatus(1);
                        if(state2 === 0){
                            status_motor_right.state = 1;
                            model_power_issue.append({"name":"모터 2 준비안됨","image":"icon/icon_error.png"});
                        }else if(state2 === 1){
                            status_motor_right.state = 2;
                        }else{
                            status_motor_right.state = 0;
                            var str_error = "";
                            if(state2 >= 128){
                                str_error += "Unknown ";
                                state2 -= 128;
                            }
                            if(state2 >= 64){
                                str_error += "PS1,2 ";
                                state2 -= 64;
                            }
                            if(state2 >= 32){
                                str_error += "INPUT ";
                                state2 -= 32;
                            }
                            if(state2 >= 16){
                                str_error += "BIG ";
                                state2 -= 16;
                            }
                            if(state2 >= 8){
                                str_error += "CUR ";
                                state2 -= 8;
                            }
                            if(state2 >= 4){
                                str_error += "JAM ";
                                state2 -= 4;
                            }
                            if(state2 >= 2){
                                str_error += "MOD ";
                                state2 -= 2;
                            }
                            model_power_issue.append({"name":"모터 2 "+str_error,"image":"icon/icon_error.png"});

                            bar_status2.background_color = color_red;
                            text_status2.text = str_error;
                        }
                    }

                    bar_temp1.value = supervisor.getMotorTemperature(0);
                    bar_mtemp1.value = supervisor.getMotorInsideTemperature(0);
                    bar_cur1.value = supervisor.getMotorCurrent(0);
                    bar_temp2.value = supervisor.getMotorTemperature(1);
                    bar_mtemp2.value = supervisor.getMotorInsideTemperature(1);
                    bar_cur2.value = supervisor.getMotorCurrent(1);
                }


            }else{
                status_power.state = 0;
                status_motor_left.state = 0;
                status_motor_right.state = 0;
                status_localization.state = 0;
                text_robot.text = "프로그램 연결 안됨"
            }

        }
    }

    Popup_help{
        id: popup_help_setting
    }

    Popup{
        id: popup_sensorview
        anchors.centerIn: parent
        width: 850
        height: 650
        background:Rectangle{
            anchors.fill: parent
            color: "transparent"
        }
        Rectangle{
            width: parent.width
            height: parent.height
            radius: 10
            color: color_dark_navy
        }
    }

    Popup{
        id: popup_manager
        width: 500
        height: 500
        anchors.centerIn: parent
        leftPadding: 0
        topPadding: 0
        bottomPadding: 0
        rightPadding: 0
        background: Rectangle{
            anchors.fill: parent
            color : "transparent"
        }

        Rectangle{
            radius: 20
            clip: true
            anchors.centerIn: parent
            width: parent.width*0.99
            height: parent.height*0.99
            border.width: 3
            border.color: color_dark_navy
            Rectangle{
                radius: 20
                id: rect_prd_top
                width: parent.width
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                Rectangle{
                    width: parent.width
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.bottom: parent.bottom
                    height: 20
                    color: color_dark_navy
                }
                height: 80
                color: color_dark_navy
                Text{
                    anchors.centerIn: parent
                    color: "white"
                    font.family: font_noto_r.name
                    font.pixelSize: 30
                    text: "관리자 메뉴"
                }
            }
            Grid{
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                anchors.verticalCenterOffset: 40
                rows: 3
                columns: 2
                spacing: 30
                Rectangle{
                    id: btn_update
                    width: 180
                    height: 60
                    radius: 10
                    color:"transparent"
                    border.width: 1
                    border.color: "#7e7e7e"
                    Text{
                        anchors.centerIn: parent
                        text: "프로그램 업데이트"
                        font.family: font_noto_r.name
                        font.pixelSize: 20
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked:{
                            supervisor.writelog("[USER INPUT] SETTING PAGE -> PROGRAM UPDATE");
                            popup_update.open();
                        }
                    }
                }
                Rectangle{
                    id: btn_log
                    width: 180
                    height: 60
                    radius: 10
                    visible: false
                    color:"transparent"
                    border.width: 1
                    border.color: "#7e7e7e"
                    Text{
                        anchors.centerIn: parent
                        text: "Log"
                        font.family: font_noto_r.name
                        font.pixelSize: 20
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked:{
                            supervisor.writelog("[USER INPUT] SETTING PAGE -> LOG");
                            loader_page.source = plog;
                        }
                    }
                }
                Rectangle{
                    id: btn_usb_upload
                    width: 180
                    height: 60
                    radius: 10
                    color: enabled?"white":color_light_gray
                    border.width: 1
                    border.color: "#7e7e7e"
                    visible: false
                    Text{
                        anchors.centerIn: parent
                        text: "USB에 저장하기"
                        font.family: font_noto_r.name
                        font.pixelSize: 20
                        color: btn_usb_upload.enabled?"black":color_gray
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked:{
                            supervisor.writelog("[USER INPUT] SETTING PAGE -> SAVE TO USB");
                            popup_usb_select.open();
                        }
                    }
                }
                Rectangle{
                    id: btn_usb_download
                    width: 180
                    height: 60
                    radius: 10
                    enabled: false
                    color:enabled?"white":color_light_gray
                    border.width: 1
                    visible: false
                    border.color: "#7e7e7e"
                    Text{
                        anchors.centerIn: parent
                        text: "USB에서 받아오기"
                        font.family: font_noto_r.name
                        font.pixelSize: 20
                        color: btn_usb_download.enabled?"black":color_gray
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked:{
                            supervisor.writelog("[USER INPUT] SETTING PAGE -> DOWNLOAD FROM USB");
                            if(is_admin){
                                popup_usb_download.open();
                            }else{
                                popup_password.open();
                            }
                        }
                    }
                }
                Rectangle{
                    id: btn_reset_slam
                    width: 180
                    height: 60
                    radius: 10
                    color:"transparent"
                    border.width: 1
                    border.color: "#7e7e7e"
                    Text{
                        anchors.centerIn: parent
                        text: "SLAM restart"
                        font.family: font_noto_r.name
                        font.pixelSize: 20
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked:{
                            supervisor.writelog("[USER INPUT] SETTING PAGE -> KILL SLAM");
                            supervisor.restartSLAM();
                        }
                    }
                }
                Rectangle{
                    id: btn_all_init
                    width: 180
                    height: 60
                    radius: 10
                    color:"transparent"
                    border.width: 1
                    border.color: "#7e7e7e"
                    Text{
                        anchors.centerIn: parent
                        text: "공장 초기화"
                        font.family: font_noto_r.name
                        font.pixelSize: 20
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked:{
                            supervisor.writelog("[USER INPUT] RESET ALL -> REMOVE ALL");
                            supervisor.resetClear();
                        }
                    }
                }
            }
        }
    }
    Popup{
        id: popup_usb_notice
        anchors.centerIn: parent
        width: 500
        height: 500
        leftPadding: 0
        topPadding: 0
        bottomPadding: 0
        rightPadding: 0
        background: Rectangle{
            anchors.fill: parent
            color : "transparent"
        }
        function setProperty(mo,na,ui,slam,config,map,log){
            mode = mo;
            name = na;
            is_ui = ui;
            is_slam = slam;
            is_map = map;
            is_log = log;
            is_config = config;
        }

        property bool is_ui: false
        property bool is_slam: false
        property bool is_map: false
        property bool is_log: false
        property bool is_config: false
        property string name: "Desktop"
        property string mode: "compress";
        property bool is_new: true
        Timer{
            id: timer_usb_check
            running: false
            repeat: true
            interval: 300
            onTriggered: {
                if(popup_usb_notice.is_new){
                    popup_usb_notice.is_new = false;
                    if(popup_usb_notice.mode == "compress"){
                        supervisor.usbsave(popup_usb_notice.name, popup_usb_notice.is_ui, popup_usb_notice.is_slam, popup_usb_notice.is_config, popup_usb_notice.is_map, popup_usb_notice.is_log);
                    }else if(popup_usb_notice.mode == "extract_recent"){
                        supervisor.readusbrecentfile();
                    }else if(popup_usb_notice.mode == "extract"){

                    }
                }
                text_usb_state.color = "white"

                if(supervisor.getzipstate() === 1){
                    if(popup_usb_notice.mode== "compress"){
                        text_usb_state.text = "파일을 압축하여 저장 중..";
                    }else{
                        text_usb_state.text = "파일을 가져오는 중..";
                    }
                }else if(supervisor.getzipstate() === 2){
                    if(popup_usb_notice.mode== "compress"){
                        text_usb_state.text = "저장에 성공하였습니다";
                    }else{
                        btn_usb_confirm.visible = true;
                        text_usb_state.text = "파일을 성공적으로 가져왔습니다\n확인을 누르시면 업데이트를 진행합니다";
                    }

                }else if(supervisor.getzipstate() === 3){
                    if(popup_usb_notice.mode== "compress"){
                        text_usb_state.text = "저장에 성공하였지만 일부 과정에서 에러가 발생했습니다";
                    }else{
                        text_usb_state.text = "파일을 성공적으로 가져왔습니다만 일부 과정에서 에러가 발생했습니다\n확인을 누르시면 업데이트를 진행합니다";
                        btn_usb_confirm.visible = true;
                    }
                    model_usb_error.clear();
                    for(var i=0; i<supervisor.getusberrorsize(); i++){
                        model_usb_error.append({"error":supervisor.getusberror(i)});
                    }
                }else if(supervisor.getzipstate() === 4){
                    text_usb_state.color = color_red;
                    if(popup_usb_notice.mode== "compress"){
                        text_usb_state.text = "저장에 실패했습니다";
                    }else{
                        text_usb_state.text = "파일을 가져오지 못했습니다";
                    }
                    model_usb_error.clear();
                    for(var i=0; i<supervisor.getusberrorsize(); i++){
                        model_usb_error.append({"error":supervisor.getusberror(i)});
                    }
                }else{
                    print(supervisor.getzipstate());
                    text_usb_state.text = "잠시만 기다려주세요";
                }
            }
        }
        onOpened:{
            timer_usb_check.start();
            model_usb_error.clear();
            btn_usb_confirm.visible = false;
            text_usb_state.text = "잠시만 기다려주세요";
            is_new = true;
        }
        onClosed: {
            timer_usb_check.stop();
        }
        Rectangle{
            width: parent.width
            height: parent.height
            radius: 20
            color: color_dark_navy
            Column{
                anchors.centerIn: parent
                spacing: 10
                Text{
                    id: text_usb_state
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.family: font_noto_r.name
                    color: "white"
                    font.pixelSize: 30
                    horizontalAlignment: Text.AlignHCenter
                    text:"잠시만 기다려주세요"
                }
                Repeater{
                    model: ListModel{id:model_usb_error}
                    Rectangle{
                        width: 400
                        height: 30
                        color: color_navy
                        Text{
                            anchors.centerIn: parent
                            font.family: font_noto_r.name
                            font.pixelSize: 12
                            color: "white"
                            horizontalAlignment: Text.AlignHCenter
                            text:error
                        }
                    }

                }

                Rectangle{
                    id: btn_usb_confirm
                    visible: false
                    anchors.horizontalCenter: parent.horizontalCenter
                    width: 100
                    height: 50
                    radius: 5
                    border.width: 1
                    Text{
                        anchors.centerIn: parent
                        font.family:font_noto_r.name
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked:{

                            if(popup_usb_notice.mode== "compress"){

                            }else{
                                supervisor.updateUSB();
                            }
                        }
                    }
                }
            }
        }
    }


    Popup{
        id: popup_usb_download
        anchors.centerIn: parent
        width: 400
        height: 500
        leftPadding: 0
        topPadding: 0
        bottomPadding: 0
        rightPadding: 0
        background: Rectangle{
            color: "transparent"
        }
        property var index: 0
        property bool is_ui: false
        property bool is_slam: false
        property bool is_map: false
        property bool is_log: false
        property bool is_config: false
        property string set_name: ""
        onOpened:{
            timer_usb_new.start();

            model_usb_file_list.clear();
            for(var i=0; i<supervisor.getusbfilesize(); i++){
                model_usb_file_list.append({"name":supervisor.getusbfile(i)});
            }

            text_recent_file.text = supervisor.getusbrecentfile();
            if(text_recent_file.text == ""){
                notice_recent.visible = false;
                btn_recent_confirm.visible = false;
            }else{
                notice_recent.visible = true;
                btn_recent_confirm.visible = true;
            }
        }
        onClosed:{
            timer_usb_new.stop();
        }

        Rectangle{
            anchors.fill: parent
            Rectangle{
//                id: rect_1
                width: parent.width
                height: 50
                color: color_dark_navy
                Text{
                    anchors.centerIn: parent
                    font.family: font_noto_r.name
                    font.pixelSize: 15
                    color: "white"
                    text: {
                        if(popup_usb_download.index === 0)
                            "가져오실 파일 목록을 선택해주세요"
                        else if(popup_usb_download.index === 1)
                            "가져오실 목록을 선택해주세요"
                    }
                }
            }

            Column{
                anchors.centerIn: parent
                visible: popup_usb_download.index === 0
                spacing: 10
                Rectangle{
                    id: notice_recent
                    width: 200
                    height: 50
                    color: color_navy
                    anchors.horizontalCenter: parent.horizontalCenter
                    Text{
                        text: "가장 최신 파일"
                        anchors.centerIn: parent
                        font.family: font_noto_r.name
                        font.pixelSize: 15
                        color: "white"
                    }
                }
                Rectangle{
                    width: 280
                    radius: 10
                    anchors.horizontalCenter: parent.horizontalCenter
                    height: 50
                    color: color_light_gray
                    Text{
                        id: text_recent_file
                        anchors.centerIn: parent
                        font.family: font_noto_r.name
                        font.pixelSize: 15
                        text: ""
                    }
                }
                Rectangle{
                    id: btn_recent_confirm
                    visible: false
                    width: 100
                    radius: 5
                    anchors.horizontalCenter: parent.horizontalCenter
                    height: 50
                    border.width:1
                    color: "white"//color_light_gray
                    Text{
                        anchors.centerIn: parent
                        font.family: font_noto_r.name
                        font.pixelSize: 15
                        text: "확인"
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked:{
                            supervisor.writelog("[USER INPUT] GET RECENT USB FILE : "+supervisor.getusbrecentfile());
                            popup_usb_notice.mode = "extract_recent";
                            popup_usb_notice.open();
//                            supervisor.readusbrecentfile();
                        }
                    }
                }

                Rectangle{
                    width: 200
                    height: 50
                    color: color_navy
                    anchors.horizontalCenter: parent.horizontalCenter
                    Text{
                        text: "그 외 발견한 파일 목록"
                        anchors.centerIn: parent
                        font.family: font_noto_r.name
                        font.pixelSize: 15
                        color: "white"
                    }
                }
                Repeater{
                    model: ListModel{id:model_usb_file_list}
                    Rectangle{
                        width: 280
                        radius: 10
                        height: 50
                        color: color_light_gray
                        Text{
                            anchors.centerIn: parent
                            font.family: font_noto_r.name
                            font.pixelSize: 10
                            text: name
                        }
                        MouseArea{
                            anchors.fill: parent
                            onClicked: {
//                                popup_usb_download.index = 1;
//                                popup_usb_download.set_name = name;
                            }
                        }
                    }
                }
            }
            Column{
                anchors.centerIn: parent
                spacing: 10
                visible: popup_usb_download.index === 1
                Rectangle{
                    width: 280
                    radius: 10
                    height: 50
                    color: popup_usb_download.is_ui?color_green:color_light_gray
                    Text{
                        anchors.centerIn: parent
                        font.family: font_noto_r.name
                        font.pixelSize: 15
                        text: "UI"
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            popup_usb_download.is_ui = !popup_usb_download.is_ui;
                        }
                    }
                }
                Rectangle{
                    width: 280
                    radius: 10
                    height: 50
                    color: popup_usb_download.is_slam?color_green:color_light_gray
                    Text{
                        anchors.centerIn: parent
                        font.family: font_noto_r.name
                        font.pixelSize: 15
                        text: "SLAMNAV"
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            popup_usb_download.is_slam = !popup_usb_download.is_slam;
                        }
                    }
                }
                Rectangle{
                    width: 280
                    radius: 10
                    height: 50
                    color: popup_usb_download.is_config?color_green:color_light_gray
                    Text{
                        anchors.centerIn: parent
                        font.family: font_noto_r.name
                        font.pixelSize: 15
                        text: "robot_config"
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            popup_usb_download.is_config = !popup_usb_download.is_config;
                        }
                    }
                }
                Rectangle{
                    width: 280
                    radius: 10
                    height: 50
                    color: popup_usb_download.is_map?color_green:color_light_gray
                    Text{
                        anchors.centerIn: parent
                        font.family: font_noto_r.name
                        font.pixelSize: 15
                        text: "maps"
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            popup_usb_download.is_map = !popup_usb_download.is_map;
                        }
                    }
                }
                Rectangle{
                    width: 280
                    radius: 10
                    height: 50
                    color: popup_usb_download.is_log?color_green:color_light_gray
                    Text{
                        anchors.centerIn: parent
                        font.family: font_noto_r.name
                        font.pixelSize: 15
                        text: "Log"
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            popup_usb_download.is_log = !popup_usb_download.is_log;
                        }
                    }
                }
            }
            Rectangle{
                width: 250
                radius: 10
                height: 50
                color: "black"
                anchors.bottom: parent.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottomMargin: 30
                visible: popup_usb_download.index === 1
                Text{
                    anchors.centerIn: parent
                    font.family: font_noto_r.name
                    font.pixelSize: 15
                    color:"white"
                    text: "확인"
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        popup_usb_notice.setProperty("compress",popup_usb_download.set_name,popup_usb_download.is_ui,popup_usb_download.is_slam,popup_usb_download.is_config,popup_usb_download.is_map,popup_usb_download.is_log);
                        popup_usb_download.close();
                        popup_usb_notice.open();
                    }
                }
            }

        }
        Timer{
            id: timer_usb_new
            interval: 500
            running: false
            repeat: true
            onTriggered: {
                if(supervisor.getusbsize() > 0){
                }else{
                }
            }
        }
    }

    Popup{
        id: popup_usb_select
        anchors.centerIn: parent
        width: 500
        height: 500
        leftPadding: 0
        topPadding: 0
        bottomPadding: 0
        rightPadding: 0
        property int usb_size: 0
        property int index: 0
        property bool is_ui: false
        property bool is_slam: false
        property bool is_map: false
        property bool is_log: false
        property bool is_config: false
        property string set_name: "Desktop"
        background: Rectangle{
            anchors.fill: parent
            color: "transparent"
        }
        onOpened: {
            if(supervisor.getusbsize() > 0){
                text_no_usb.visible =false;
            }else{
                text_no_usb.visible = true;
            }

            timer_check_usb_new.start();
            index = 0;
            is_ui = true;
            is_slam = true;
            is_map = false;
            is_log = false;
            is_config = true;
            model_usb_list.clear();
            for(var i=0; i<supervisor.getusbsize(); i++){
                print(i, supervisor.getusbname(i));
                model_usb_list.append({"name":supervisor.getusbname(i)});
            }
            model_usb_list.append({"name":"Desktop"});
        }
        onClosed: {
            timer_check_usb_new.stop();
        }

        Timer{
            id: timer_check_usb_new
            interval: 500
            running: false
            repeat: true
            onTriggered: {
                if(supervisor.getusbsize() > 0){
                    text_no_usb.visible =false;
                }else if(popup_usb_select.index === 0){
                    text_no_usb.visible = true;
                }
                model_usb_list.clear();
                for(var i=0; i<supervisor.getusbsize(); i++){
                    model_usb_list.append({"name":supervisor.getusbname(i)});
                }
                model_usb_list.append({"name":"Desktop"});
            }
        }

        Rectangle{
            radius: 20
            clip: true
            anchors.centerIn: parent
            width: parent.width*0.99
            height: parent.height*0.99
            border.width: 3
            border.color: color_dark_navy
            Rectangle{
                radius: 20
                id: rect_ttt
                width: parent.width
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                Rectangle{
                    width: parent.width
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.bottom: parent.bottom
                    height: 20
                    color: color_dark_navy
                }
                height: 80
                color: color_dark_navy
                Text{
                    anchors.centerIn: parent
                    font.family: font_noto_r.name
                    font.pixelSize: 25
                    color: "white"
                    text: {
                        if(popup_usb_select.index === 0)
                            "저장소를 선택해주세요"
                        else if(popup_usb_select.index === 1)
                            "저장할 목록을 선택해주세요"
                    }
                }
            }
            Rectangle{
                width: parent.width
                color: "transparent"
                height: parent.height - rect_ttt.height
                anchors.top: rect_ttt.bottom
                Text{
                    id: text_no_usb
                    visible: false
                    anchors.top: parent.top
                    anchors.topMargin: 20
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.family: font_noto_r.name
                    font.pixelSize: 25
                    horizontalAlignment: Text.AlignHCenter
                    color: color_red
                    text: "** USB를 인식할 수 없습니다 **\nUSB를 뺏다 꼽아주시면 인식될 수 있습니다"
                }
                Column{
                    anchors.centerIn: parent
                    spacing: 30
                    Column{
                        anchors.horizontalCenter: parent.horizontalCenter
                        visible: popup_usb_select.index === 0
                        spacing: 10

                        Rectangle{
                            width: 400
                            height: 40
                            color: "black"
                            Text{
                                color: "white"
                                anchors.centerIn: parent
                                font.family: font_noto_r.name
                                font.pixelSize: 15
                                text: "저장소 목록"
                            }
                        }
                        Repeater{
                            anchors.horizontalCenter: parent.horizontalCenter
                            model: ListModel{id:model_usb_list}
                            Rectangle{
                                anchors.horizontalCenter: parent.horizontalCenter
                                width: 300
                                radius: 10
                                height: 50
                                color: color_light_gray
                                Text{
                                    anchors.centerIn: parent
                                    font.family: font_noto_r.name
                                    font.pixelSize: 15
                                    text: name
                                }
                                MouseArea{
                                    anchors.fill: parent
                                    onClicked: {
                                        text_no_usb.visible = false;
                                        popup_usb_select.index = 1;
                                        popup_usb_select.set_name = name;
                                    }
                                }
                            }
                        }
                    }
                    Column{
                        anchors.horizontalCenter: parent.horizontalCenter
                        spacing: 10
                        visible: popup_usb_select.index === 1
                        Rectangle{
                            width: 280
                            radius: 10
                            height: 50
                            color: popup_usb_select.is_ui?color_green:color_light_gray
                            Text{
                                anchors.centerIn: parent
                                font.family: font_noto_r.name
                                font.pixelSize: 15
                                text: "UI 실행파일"
                            }
                            MouseArea{
                                anchors.fill: parent
                                onClicked: {
                                    popup_usb_select.is_ui = !popup_usb_select.is_ui;
                                }
                            }
                        }
                        Rectangle{
                            width: 280
                            radius: 10
                            height: 50
                            color: popup_usb_select.is_slam?color_green:color_light_gray
                            Text{
                                anchors.centerIn: parent
                                font.family: font_noto_r.name
                                font.pixelSize: 15
                                text: "슬램 네비게이션 실행파일"
                            }
                            MouseArea{
                                anchors.fill: parent
                                onClicked: {
                                    popup_usb_select.is_slam = !popup_usb_select.is_slam;
                                }
                            }
                        }
                        Rectangle{
                            width: 280
                            radius: 10
                            height: 50
                            color: popup_usb_select.is_config?color_green:color_light_gray
                            Text{
                                anchors.centerIn: parent
                                font.family: font_noto_r.name
                                font.pixelSize: 15
                                text: "설정파일"
                            }
                            MouseArea{
                                anchors.fill: parent
                                onClicked: {
                                    popup_usb_select.is_config = !popup_usb_select.is_config;
                                }
                            }
                        }
                        Rectangle{
                            width: 280
                            radius: 10
                            height: 50
                            color: popup_usb_select.is_map?color_green:color_light_gray
                            Text{
                                anchors.centerIn: parent
                                font.family: font_noto_r.name
                                font.pixelSize: 15
                                text: "맵 폴더"
                            }
                            MouseArea{
                                anchors.fill: parent
                                onClicked: {
                                    popup_usb_select.is_map = !popup_usb_select.is_map;
                                }
                            }
                        }
                        Rectangle{
                            width: 280
                            radius: 10
                            height: 50
                            color: popup_usb_select.is_log?color_green:color_light_gray
                            Text{
                                anchors.centerIn: parent
                                font.family: font_noto_r.name
                                font.pixelSize: 15
                                text: "로그"
                            }
                            MouseArea{
                                anchors.fill: parent
                                onClicked: {
                                    popup_usb_select.is_log = !popup_usb_select.is_log;
                                }
                            }
                        }
                    }
                    Rectangle{
                        width: 250
                        radius: 10
                        height: 50
                        color: "black"
                        anchors.horizontalCenter: parent.horizontalCenter
                        visible: popup_usb_select.index === 1
                        Text{
                            anchors.centerIn: parent
                            font.family: font_noto_r.name
                            font.pixelSize: 15
                            color:"white"
                            text: "확인"
                        }
                        MouseArea{
                            anchors.fill: parent
                            onClicked: {
                                popup_usb_notice.setProperty("compress",popup_usb_select.set_name,popup_usb_select.is_ui,popup_usb_select.is_slam,popup_usb_select.is_config,popup_usb_select.is_map,popup_usb_select.is_log);
                                popup_usb_select.close();
                                popup_usb_notice.open();
                            }
                        }
                    }
                }
            }
        }
    }

    Popup{
        id: popup_change_call
        width: 400
        height: 300
        anchors.centerIn: parent
        leftPadding: 0
        topPadding: 0
        bottomPadding: 0
        rightPadding: 0
        property string calltype: ""
        property var callid: 0
        onOpened: {
            supervisor.setCallbell(calltype, callid);
        }
        onClosed: {
            supervisor.setCallbell("", -1);
        }

        Rectangle{
            anchors.fill: parent
            Text{
                anchors.centerIn: parent
                text: "변경하실 호출벨을 눌러주세요"
                font.family: font_noto_r.name
                font.pixelSize: 25
            }
        }
    }

    Popup{
        id: popup_reset
        width: 400
        height: 300
        anchors.centerIn: parent
        leftPadding: 0
        topPadding: 0
        bottomPadding: 0
        rightPadding: 0
        Rectangle{
            anchors.fill: parent
            Column{
                anchors.centerIn: parent
                spacing: 20
                Text{
                    text: "정말 덮어씌우시겠습니까?"
                    font.family: font_noto_b.name
                    font.pixelSize: 20
                }
                Rectangle{
                    width: 100
                    height: 50
                    border.width: 1
                    radius: 5
                    Text{
                        anchors.centerIn: parent
                        text: "확인"
                        font.family: font_noto_r.name
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked:{
                            supervisor.writelog("[USER INPUT] RESET HOME FOLDERS")
                            supervisor.resetHomeFolders();
                            popup_reset.close();
                        }
                    }
                }
            }
        }
    }

    Popup{
        id: popup_update
        width: 1280
        height: 400
        leftPadding: 0
        rightPadding: 0
        topPadding: 0
        bottomPadding: 0
        anchors.centerIn: parent
        background: Rectangle{
            anchors.fill: parent
            color: "transparent"
        }

        function newest(){
            text_main_update.text = qsTr("프로그램이 이미 최신입니다");
            text_serv_update.text = qsTr("");
        }

        function failed(){
            text_main_update.text = qsTr("업데이트에 실패했습니다");
            text_serv_update.text = qsTr("");
        }

        onOpened: {
            area_debug_update.count = 0;
            //서버 연결 체크
            if(supervisor.isConnectServer()){
                //서버 연결 됨 -> 기본 서버업데이트, Git Pull은 선택
                if(supervisor.isNeedUpdate()){
                    //서버 내 업데이트 존재 -> 서버 업데이트 유도. Git Pull숨겨둠
                    supervisor.writelog("[SETTING] UPDATE PROGRAM -> New Server Update Detected")
                    text_main_update.text = qsTr("새로운 업데이트가 있습니다");
                    text_serv_update.text = qsTr("업데이트를 진행하시겠습니까?");
                    btn_gitpull.visible = false;
                    btn_cancel.visible = true;
                    btn_doupdate.visible = true;
                    current_version.visible = true;
                    new_version.visible = true;
                }else{
                    //서버 내 업데이트 없음 -> Git Pull 숨겨둠
                    supervisor.writelog("[SETTING] UPDATE PROGRAM -> No Server Update")
                    text_main_update.text = qsTr("프로그램이 이미 최신입니다");
                    text_serv_update.text = qsTr("");
                    btn_gitpull.visible = false;
                    btn_cancel.visible = true;
                    btn_doupdate.visible = false;
                    current_version.visible = true;
                    new_version.visible = false;
                }
            }else{
                //서버 연결 안됨 -> Git Pull만 가능(숨겨둠)
                supervisor.writelog("[SETTING] UPDATE PROGRAM -> Disconnected Server")
                text_main_update.text = qsTr("서버와 연결되지 않았습니다");
                text_serv_update.text = qsTr("무선 와이파이가 연결되었는지 확인해주세요");
                btn_gitpull.visible = false;
                btn_cancel.visible = true;
                btn_doupdate.visible = false;
                current_version.visible = true;
                new_version.visible = false;
            }
        }
        Rectangle{
            width: parent.width
            height: parent.height
            color: color_navy
            Column{
                anchors.centerIn: parent
                spacing: 40
                Column{
                    anchors.horizontalCenter: parent.horizontalCenter
                    Text{
                        id: text_main_update
                        anchors.horizontalCenter: parent.horizontalCenter
                        font.family: font_noto_r.name
                        font.pixelSize: 50
                        color: "white"
                        text: qsTr("프로그램이 이미 최신입니다")
                    }
                    Text{
                        id: text_serv_update
                        anchors.horizontalCenter: parent.horizontalCenter
                        font.family: font_noto_r.name
                        font.pixelSize: 40
                        color: "white"
                        text: qsTr("프로그램이 이미 최신입니다")
                    }
                }
                Column{
                    spacing: 10
                    anchors.horizontalCenter: parent.horizontalCenter
                    Row{
                        id: current_version
                        anchors.horizontalCenter: parent.horizontalCenter
                        Text{
                            width: 200
                            horizontalAlignment: Text.AlignHCenter
                            font.family: font_noto_r.name
                            font.pixelSize: 25
                            color: "white"
                            text: "현재 버전 : "
                        }
                        Text{
                            width: 500
                            font.family: font_noto_r.name
                            font.pixelSize: 25
                            color: "white"
                            horizontalAlignment: Text.AlignHCenter
                            text: supervisor.getLocalVersion()
                        }
                    }
                    Row{
                        id: new_version
                        anchors.horizontalCenter: parent.horizontalCenter
                        Text{
                            width: 200
                            horizontalAlignment: Text.AlignHCenter
                            font.family: font_noto_r.name
                            font.pixelSize: 25
                            color: "white"
                            text: "최신 버전 : "
                        }
                        Text{
                            width: 500
                            font.family: font_noto_r.name
                            font.pixelSize: 25
                            color: "white"
                            horizontalAlignment: Text.AlignHCenter
                            text: supervisor.getServerVersion()
                        }
                    }
                }
                Row{
                    anchors.horizontalCenter: parent.horizontalCenter
                    spacing: 20
                    Rectangle{
                        id: btn_doupdate
                        width: 180
                        height: 60
                        radius: 10
                        color: "#12d27c"
                        border.width: 1
                        border.color: "#12d27c"
                        Text{
                            anchors.centerIn: parent
                            text: qsTr("업데이트")
                            font.family: font_noto_r.name
                            font.pixelSize: 25
                            color: "white"
                        }
                        MouseArea{
                            anchors.fill: parent
                            onClicked: {
                                supervisor.writelog("[USER INPUT] SETTING : Program Update Start");
                                supervisor.updateProgram();
                                popup_update.close();
                            }
                        }
                    }
                    Rectangle{
                        id: btn_cancel
                        width: 180
                        height: 60
                        radius: 10
                        color: "transparent"
                        border.width: 1
                        border.color: "white"
                        Text{
                            anchors.centerIn: parent
                            text: qsTr("닫기")
                            font.family: font_noto_r.name
                            font.pixelSize: 25
                            color: "white"
                        }
                        MouseArea{
                            anchors.fill: parent
                            onClicked: {
                                popup_update.close();
                            }
                        }
                    }
                    Rectangle{
                        id: btn_gitpull
                        width: 180
                        height: 60
                        radius: 10
                        color: "#12d27c"
                        border.width: 1
                        border.color: "#12d27c"
                        Text{
                            anchors.centerIn: parent
                            text: qsTr("PULL")
                            font.family: font_noto_r.name
                            font.pixelSize: 25
                            color: "white"
                        }
                        MouseArea{
                            anchors.fill: parent
                            onClicked: {
                                popup_loading.open();
                                supervisor.writelog("[USER INPUT] SETTING : Program Update(Git Pull) Start");
                                supervisor.updateProgramGitPull();
//                                popup_update.close();
                            }
                        }
                    }
                }

            }
            MouseArea{
                id: area_debug_update
                width: 100
                height: parent.height
                anchors.right: parent.right
                property var count: 0
                onClicked:{
                    if(++count > 4){
                        count = 0;
                        supervisor.writelog("[USER INPUT] SETTING : Show Git Pull Button");
                        btn_gitpull.visible = true;
                    }
                }
            }
        }
    }
    Popup{
        id: popup_camera
        width: parent.width
        height: parent.height
        background: Rectangle{
            opacity: 0.8
            color: "#282828"
        }
        property bool is_load: false
        property bool is_switched: false
        property var left_id: 0
        property var right_id: 1

        onOpened: {
            timer_load.start();
        }

        onClosed: {
            timer_load.stop();
        }

        function update(){
            //카메라 대수에 따라 UI 업데이트
            if(supervisor.getCameraNum() === 2){
                print(supervisor.getCameraNum(),supervisor.getCameraSerial(left_id));
                is_load = true;
                if(is_switched){
                    cameraview_1.setCamera(left_id);
                    cameraview_2.setCamera(right_id);
                    text_camera_1.text = supervisor.getCameraSerial(left_id);
                    text_camera_2.text = supervisor.getCameraSerial(right_id);
                }else{
                    if(supervisor.getLeftCamera()===supervisor.getCameraSerial(0)){
                        left_id = 0;
                        right_id = 1;
                    }else if(supervisor.getLeftCamera() === supervisor.getCameraSerial(1)){
                        left_id = 1;
                        right_id = 0;
                    }else{
                        if(supervisor.getRightCamera()===supervisor.getCameraSerial(0)){
                            left_id = 1;
                            right_id = 0;
                        }else if(supervisor.getRightCamera() === supervisor.getCameraSerial(1)){
                            left_id = 0;
                            right_id = 1;
                        }else{
                            left_id = 0;
                            right_id = 1;
                        }
                    }
                    cameraview_1.setCamera(left_id);
                    cameraview_2.setCamera(right_id);
                    text_camera_1.text = supervisor.getCameraSerial(left_id);
                    text_camera_2.text = supervisor.getCameraSerial(right_id);
                }
            }else{
                is_load = false;
                text_camera_1.text = "";
                text_camera_2.text = "";
            }
        }

        Timer{
            id: timer_load
            interval: 500
            repeat: true
            running: popup_camera.opened
            onTriggered:{
                //카메라 정보 요청
                supervisor.requestCamera();
                update();
            }
        }
        Rectangle{
            anchors.centerIn: parent
            width: 1280
            height: 650
            color: color_dark_navy
            Column{
                anchors.centerIn: parent
                spacing: 30
                Text{
                    anchors.horizontalCenter: parent.horizontalCenter
                    color: "white"
                    font.family: font_noto_r.name
                    font.pixelSize: 40
                    text: "카메라 정보를 확인한 후, 위치를 지정하여주세요"
                }
                Row{
                    anchors.horizontalCenter: parent.horizontalCenter
                    spacing: 50
                    Column{
                        spacing: 10
                        Text{
                            id: text_left
                            text: "왼쪽"
                            font.family: font_noto_b.name
                            font.pixelSize: 30
                            anchors.horizontalCenter: parent.horizontalCenter
                            Component.onCompleted: {
                                scale = 1;
                                while(width*scale > parent.width*0.8){
                                    scale=scale-0.01;
                                }
                            }
                            color: "white"
                        }
                        Rectangle{
                            width: 350
                            height: 350
                            color: "black"
                            anchors.horizontalCenter: parent.horizontalCenter
                            CameraView{
                                id: cameraview_1
                                anchors.fill: parent
                                Text{
                                    id: text_camera_1
                                    anchors.bottom: parent.bottom
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    text: {
                                        if(supervisor.getCameraNum() > 0&& supervisor.getCameraSerial(0) !== ""){
                                            "Serial : " + supervisor.getCameraSerial(0);
                                        }else{
                                            "Serial : Not connected"
                                        }
                                    }
                                    font.family: font_noto_r.name
                                    color: color_red
                                    font.pixelSize: 20
                                }
                            }
                        }
                    }
                    Column{
                        spacing: 10
                        Text{
                            id: text_right
                            text: "오른쪽"
                            font.family: font_noto_b.name
                            font.pixelSize: 30
                            anchors.horizontalCenter: parent.horizontalCenter
                            Component.onCompleted: {
                                scale = 1;
                                while(width*scale > parent.width*0.8){
                                    scale=scale-0.01;
                                }
                            }
                            color: "white"
                        }
                        Rectangle{
                            width: 350
                            height: 350
                            color: "black"
                            anchors.horizontalCenter: parent.horizontalCenter
                            CameraView{
                               id: cameraview_2
                               anchors.fill: parent
                               Text{
                                   id: text_camera_2
                                   anchors.bottom: parent.bottom
                                   anchors.horizontalCenter: parent.horizontalCenter
                                   text: {
                                       if(supervisor.getCameraNum() > 1 && supervisor.getCameraSerial(1) !== ""){
                                           "Serial : " + supervisor.getCameraSerial(1);
                                       }else{
                                           "Serial : Not connected"
                                       }
                                   }
                                   font.family: font_noto_r.name
                                   color: color_red
                                   font.pixelSize: 20
                               }
                           }
                        }
                    }
                }
                Row{
                    spacing: 50
                    anchors.horizontalCenter: parent.horizontalCenter
                    Rectangle{
                        width: 180
                        height: 60
                        radius: 10
                        color: enabled?"#12d27c":"#e9e9e9"
                        border.width: enabled?2:0
                        border.color: "#12d27c"
                        enabled: popup_camera.is_load
                        Text{
                            anchors.centerIn: parent
                            text: "확인"
                            font.family: font_noto_r.name
                            font.pixelSize: 25
                            color: "white"
                        }
                        MouseArea{
                            anchors.fill: parent
                            onClicked: {
                                if(popup_camera.is_switched){
                                    is_reset_slam = true;
                                    supervisor.writelog("[USER INPUT] SETTING PAGE : CAMERA SWITCH LEFT("+text_camera_1.text+") RIGHT("+text_camera_2.text+")");
                                    supervisor.setCamera(text_camera_1.text,text_camera_2.text);
                                }
                                if(left_camera.text  !== supervisor.getSetting("static","SENSOR","left_camera_serial") || right_camera.text !== supervisor.getSetting("static","SENSOR","right_camera_serial")){
                                    is_reset_slam = true;
                                }

                                left_camera.text = supervisor.getSetting("static","SENSOR","left_camera_serial");
                                right_camera.text = supervisor.getSetting("static","SENSOR","right_camera_serial");
                                popup_camera.close();
                            }
                        }
                    }
                    Rectangle{
                        width: 180
                        height: 60
                        radius: 10
                        color:"transparent"
                        border.width: 2
                        border.color: "#7e7e7e"
                        Text{
                            anchors.centerIn: parent
                            text: "위치 바꾸기"
                            color: "white"
                            font.family: font_noto_r.name
                            font.pixelSize: 25
                        }
                        MouseArea{
                            anchors.fill: parent
                            onClicked: {
                                supervisor.writelog("[USER INPUT] SETTING PAGE : CAMERA Position Switch")
                                popup_camera.is_switched = true;
                                var temp_id = popup_camera.left_id;
                                popup_camera.left_id = popup_camera.right_id;
                                popup_camera.right_id = temp_id;
                            }
                        }
                    }
                    Rectangle{
                        width: 180
                        height: 60
                        radius: 10
                        color:"transparent"
                        border.width: 2
                        border.color: "#7e7e7e"
                        Text{
                            anchors.centerIn: parent
                            color: "white"
                            text: "취소"
                            font.family: font_noto_r.name
                            font.pixelSize: 25
                        }
                        MouseArea{
                            anchors.fill: parent
                            onClicked: {
                                popup_camera.close();
                            }
                        }
                    }
                }
            }
        }
    }

    Popup{
        id: popup_preset
        width: 1280
        height: 800
        background: Rectangle{
            anchors.fill: parent
            color: color_dark_black
            opacity: 0.7
        }
        property var select_preset: 1
        onOpened:{
            update();
        }
        onClosed:{
            init();
        }

        function update(){
            text_preset_1.text = supervisor.getSetting("setting","PRESET1","name");
            text_preset_2.text = supervisor.getSetting("setting","PRESET2","name");
            text_preset_3.text = supervisor.getSetting("setting","PRESET3","name");
            text_preset_4.text = supervisor.getSetting("setting","PRESET4","name");
            text_preset_5.text = supervisor.getSetting("setting","PRESET5","name");
            preset_limit_pivot.text = supervisor.getSetting("setting","PRESET"+Number(select_preset),"limit_pivot");
            preset_limit_pivot_acc.text = supervisor.getSetting("setting","PRESET"+Number(select_preset),"limit_pivot_acc");
            preset_limit_v.text = supervisor.getSetting("setting","PRESET"+Number(select_preset),"limit_v");
            preset_limit_vacc.text = supervisor.getSetting("setting","PRESET"+Number(select_preset),"limit_v_acc");
            preset_limit_w.text = supervisor.getSetting("setting","PRESET"+Number(select_preset),"limit_w");
            preset_limit_wacc.text = supervisor.getSetting("setting","PRESET"+Number(select_preset),"limit_w_acc");
        }

        Rectangle{
            id: rect_preset
            width: 900
            height: 600
            anchors.centerIn: parent
            radius: 20
            Column{
                Rectangle{
                    id: rect_preset_t
                    width: rect_preset.width
                    height: 80
                    radius: 20
                    color: color_dark_navy
                    Text{
                        anchors.centerIn: parent
                        color: "white"
                        font.family: font_noto_r.name
                        font.pixelSize: 30
                        font.bold: true
                        text: "로봇 프리셋 설정"
                    }
                    Rectangle{
                        anchors.bottom: parent.bottom
                        width: parent.width
                        height: parent.radius
                        color: color_dark_navy
                    }
                }
                Row{
                    Rectangle{
                        id: rect_preset_l
                        width: 300
                        radius: 20
                        height: rect_preset.height - rect_preset_t.height
                        color: color_gray
                        Rectangle{
                            anchors.top: parent.top
                            width: parent.width
                            height: parent.radius
                            color: parent.color
                        }
                        Rectangle{
                            anchors.right: parent.right
                            width: parent.radius
                            height: parent.height
                            color: parent.color
                        }
                        Column{
                            anchors.centerIn: parent
                            spacing: 16
                            Row{
                                anchors.horizontalCenter: parent.horizontalCenter
                                spacing: 30
                                Rectangle{
                                    width: 90
                                    height: 50
                                    radius: 10
                                    Text{
                                        anchors.centerIn: parent
                                        font.family: font_noto_r.name
                                        font.pixelSize: 15
                                        text: "초기화"
                                    }
                                    MouseArea{
                                        anchors.fill: parent
                                        onClicked:{
                                            popup_preset.update();
                                        }
                                    }
                                }
                                Rectangle{
                                    width: 90
                                    height: 50
                                    radius: 10
                                    Text{
                                        anchors.centerIn: parent
                                        font.family: font_noto_r.name
                                        font.pixelSize: 15
                                        text: "이름변경"
                                    }
                                    MouseArea{
                                        anchors.fill: parent
                                        onClicked:{
                                            popup_preset_name.open();
                                        }
                                    }
                                }
                            }
                            Rectangle{
                                anchors.horizontalCenter: parent.horizontalCenter
                                width: rect_preset_l.width*0.8
                                height: 70
                                radius: 5
                                border.width: popup_preset.select_preset===1?3:1
                                border.color: popup_preset.select_preset===1?color_green:"black"
                                Text{
                                    id: text_preset_1
                                    anchors.centerIn: parent
                                    font.family: font_noto_r.name
                                    font.pixelSize: 20
                                    font.bold: true
                                    text: "프리셋 1"
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
                                        popup_preset.select_preset = 1;
                                        popup_preset.update();
                                    }
                                }
                            }
                            Rectangle{
                                anchors.horizontalCenter: parent.horizontalCenter
                                width: rect_preset_l.width*0.8
                                height: 70
                                radius: 5
                                border.width: popup_preset.select_preset===2?3:1
                                border.color: popup_preset.select_preset===2?color_green:"black"
                                Text{
                                    id: text_preset_2
                                    anchors.centerIn: parent
                                    font.family: font_noto_r.name
                                    font.pixelSize: 20
                                    Component.onCompleted: {
                                        scale = 1;
                                        while(width*scale > parent.width*0.8){
                                            scale=scale-0.01;
                                        }
                                    }
                                    font.bold: true
                                    text: "프리셋 2"
                                }
                                MouseArea{
                                    anchors.fill: parent
                                    onClicked:{
                                        popup_preset.select_preset = 2;
                                        popup_preset.update();
                                    }
                                }
                            }
                            Rectangle{
                                anchors.horizontalCenter: parent.horizontalCenter
                                width: rect_preset_l.width*0.8
                                height: 70
                                radius: 5
                                border.width: popup_preset.select_preset===3?3:1
                                border.color: popup_preset.select_preset===3?color_green:"black"
                                Text{
                                    id: text_preset_3
                                    anchors.centerIn: parent
                                    font.family: font_noto_r.name
                                    font.pixelSize: 20
                                    Component.onCompleted: {
                                        scale = 1;
                                        while(width*scale > parent.width*0.8){
                                            scale=scale-0.01;
                                        }
                                    }
                                    font.bold: true
                                    text: "프리셋 3"
                                }
                                MouseArea{
                                    anchors.fill: parent
                                    onClicked:{
                                        popup_preset.select_preset = 3;
                                        popup_preset.update();
                                    }
                                }
                            }
                            Rectangle{
                                anchors.horizontalCenter: parent.horizontalCenter
                                width: rect_preset_l.width*0.8
                                height: 70
                                radius: 5
                                border.width: popup_preset.select_preset===4?3:1
                                border.color: popup_preset.select_preset===4?color_green:"black"
                                Text{
                                    id: text_preset_4
                                    anchors.centerIn: parent
                                    font.family: font_noto_r.name
                                    font.pixelSize: 20
                                    Component.onCompleted: {
                                        scale = 1;
                                        while(width*scale > parent.width*0.8){
                                            scale=scale-0.01;
                                        }
                                    }
                                    font.bold: true
                                    text: "프리셋 4"
                                }
                                MouseArea{
                                    anchors.fill: parent
                                    onClicked:{
                                        popup_preset.select_preset = 4;
                                        popup_preset.update();
                                    }
                                }
                            }
                            Rectangle{
                                anchors.horizontalCenter: parent.horizontalCenter
                                width: rect_preset_l.width*0.8
                                height: 70
                                radius: 5
                                border.width: popup_preset.select_preset===5?3:1
                                border.color: popup_preset.select_preset===5?color_green:"black"
                                Text{
                                    id: text_preset_5
                                    anchors.centerIn: parent
                                    font.family: font_noto_r.name
                                    font.pixelSize: 20
                                    Component.onCompleted: {
                                        scale = 1;
                                        while(width*scale > parent.width*0.8){
                                            scale=scale-0.01;
                                        }
                                    }
                                    font.bold: true
                                    text: "프리셋 5"
                                }
                                MouseArea{
                                    anchors.fill: parent
                                    onClicked:{
                                        popup_preset.select_preset = 5;
                                        popup_preset.update();
                                    }
                                }
                            }
                        }

                    }
                    Rectangle{
                        id: rect_preset_r
                        radius: 20
                        width: rect_preset.width - rect_preset_l.width
                        height:rect_preset_l.height
                        Rectangle{
                            anchors.top: parent.top
                            width: parent.width
                            height: parent.radius
                            color: parent.color
                        }
                        Row{
                            spacing: 30
                            anchors.bottom: parent.bottom
                            anchors.right: parent.right
                            anchors.rightMargin: 60
                            anchors.bottomMargin: 50
                            Rectangle{
                                width: 120
                                height: 60
                                radius: 10
                                border.width: 1
                                Text{
                                    anchors.centerIn: parent
                                    font.family: font_noto_r.name
                                    font.pixelSize: 15
                                    text: "나가기"
                                }
                                MouseArea{
                                    anchors.fill: parent
                                    onClicked:{
                                        popup_preset.close();
                                    }
                                }
                            }

                            Rectangle{
                                width: 120
                                height: 60
                                radius: 10
                                border.width: 1
                                Text{
                                    anchors.centerIn: parent
                                    font.family: font_noto_r.name
                                    font.pixelSize: 15
                                    text: "저장"
                                }
                                MouseArea{
                                    anchors.fill: parent
                                    onClicked:{
                                        if(popup_preset.select_preset === 1){
                                            supervisor.setSetting("setting","PRESET1/name",text_preset_1.text);
                                        }else if(popup_preset.select_preset === 2){
                                            supervisor.setSetting("setting","PRESET2/name",text_preset_2.text);
                                        }else if(popup_preset.select_preset === 3){
                                            supervisor.setSetting("setting","PRESET3/name",text_preset_3.text);
                                        }else if(popup_preset.select_preset === 4){
                                            supervisor.setSetting("setting","PRESET4/name",text_preset_4.text);
                                        }else if(popup_preset.select_preset === 5){
                                            supervisor.setSetting("setting","PRESET5/name",text_preset_5.text);
                                        }

                                        supervisor.setSetting("setting","PRESET"+Number(popup_preset.select_preset)+"/limit_pivot",preset_limit_pivot.text);

                                        supervisor.setSetting("setting","PRESET"+Number(popup_preset.select_preset)+"/limit_pivot_acc",preset_limit_pivot_acc.text);
                                        supervisor.setSetting("setting","PRESET"+Number(popup_preset.select_preset)+"/limit_v",preset_limit_v.text);
                                        supervisor.setSetting("setting","PRESET"+Number(popup_preset.select_preset)+"/limit_v_acc",preset_limit_vacc.text);
                                        supervisor.setSetting("setting","PRESET"+Number(popup_preset.select_preset)+"/limit_w",preset_limit_w.text);
                                        supervisor.setSetting("setting","PRESET"+Number(popup_preset.select_preset)+"/limit_w_acc",preset_limit_wacc.text);
                                        popup_preset.close();
                                    }
                                }
                            }
                        }

                        Grid{
                            spacing: 15
                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.verticalCenterOffset: -50
                            rows: 6
                            columns: 3
                            horizontalItemAlignment: Grid.AlignHCenter
                            verticalItemAlignment: Grid.AlignVCenter
                            Text{
                                font.family: font_noto_r.name
                                text:"제자리 회전 속도 [deg/s]"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                            Rectangle{
                                width: 1
                                height: 50
                                color: "#d0d0d0"
                            }
                            TextField{
                                id: preset_limit_pivot
                                width: 200
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        if(keypad.is_opened){
                                            keypad.owner = preset_limit_pivot;
                                            preset_limit_pivot.selectAll();
                                        }else{
                                            keypad.owner = preset_limit_pivot;
                                            preset_limit_pivot.selectAll();
                                            keypad.open();
                                        }
                                    }
                                }
                                height: 50
                                text:"";
                            }
                            Text{
                                font.family: font_noto_r.name
                                text:"제자리 회전 가속도 [deg/s^2]"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                            Rectangle{
                                width: 1
                                height: 50
                                color: "#d0d0d0"
                            }
                            TextField{
                                id: preset_limit_pivot_acc
                                width: 200
                                height: 50
                                text:"";
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        if(keypad.is_opened){
                                            keypad.owner = preset_limit_pivot_acc;
                                            preset_limit_pivot_acc.selectAll();
                                        }else{
                                            keypad.owner = preset_limit_pivot_acc;
                                            preset_limit_pivot_acc.selectAll();
                                            keypad.open();
                                        }
                                    }
                                }
                            }
                            Text{
                                font.family: font_noto_r.name
                                text:"주행 속도 [m/s]"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                            Rectangle{
                                width: 1
                                height: 50
                                color: "#d0d0d0"
                            }
                            TextField{
                                id: preset_limit_v
                                width: 200
                                height: 50
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        if(keypad.is_opened){
                                            keypad.owner = preset_limit_v;
                                            preset_limit_v.selectAll();
                                        }else{
                                            keypad.owner = preset_limit_v;
                                            preset_limit_v.selectAll();
                                            keypad.open();
                                        }
                                    }
                                }
                                text:"";
                            }
                            Text{
                                font.family: font_noto_r.name
                                text:"주행 가속도 [m/s^2]"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                            Rectangle{
                                width: 1
                                height: 50
                                color: "#d0d0d0"
                            }
                            TextField{
                                id: preset_limit_vacc
                                width: 200
                                height: 50
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        if(keypad.is_opened){
                                            keypad.owner = preset_limit_vacc;
                                            preset_limit_vacc.selectAll();
                                        }else{
                                            keypad.owner = preset_limit_vacc;
                                            preset_limit_vacc.selectAll();
                                            keypad.open();
                                        }
                                    }
                                }
                                text:"";
                            }
                            Text{
                                font.family: font_noto_r.name
                                text:"주행 회전속도 [deg/s]"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                            Rectangle{
                                width: 1
                                height: 50
                                color: "#d0d0d0"
                            }
                            TextField{
                                id: preset_limit_w
                                width: 200
                                height: 50
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        if(keypad.is_opened){
                                            keypad.owner = preset_limit_w;
                                            preset_limit_w.selectAll();
                                        }else{
                                            keypad.owner = preset_limit_w;
                                            preset_limit_w.selectAll();
                                            keypad.open();
                                        }
                                    }
                                }
                                text:"";
                            }
                            Text{
                                font.family: font_noto_r.name
                                text:"주행 회전 가속도 [deg/s^2]"
                                font.pixelSize: 20
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                }
                            }
                            Rectangle{
                                width: 1
                                height: 50
                                color: "#d0d0d0"
                            }
                            TextField{
                                id: preset_limit_wacc
                                width: 200
                                height: 50
                                text:"";
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        if(keypad.is_opened){
                                            keypad.owner = preset_limit_wacc;
                                            preset_limit_wacc.selectAll();
                                        }else{
                                            keypad.owner = preset_limit_wacc;
                                            preset_limit_wacc.selectAll();
                                            keypad.open();
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
        id: popup_preset_name
        anchors.centerIn: parent
        width: 300
        height: 200
        background: Rectangle{
            anchors.fill: parent
            color: color_dark_navy
        }
        Column{
            anchors.centerIn: parent
            spacing: 20
            TextField{
                id: preset_name
                width: 200
                height: 70
                horizontalAlignment: Text.AlignHCenter
                anchors.horizontalCenter: parent.horizontalCenter
                text: supervisor.getSetting("setting","PRESET"+Number(popup_preset.select_preset),"name");
                MouseArea{
                    anchors.fill:parent
                    onClicked: {
                        if(keyboard.is_opened){
                            keyboard.owner = preset_name;
                            preset_name.selectAll();
                        }else{
                            keyboard.owner = preset_name;
                            preset_name.selectAll();
                            keyboard.open();
                        }
                    }
                }
            }
            Row{
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: 20
                Rectangle{
                    width: 100
                    height: 50
                    radius: 5
                    Text{
                        anchors.centerIn: parent
                        text: "취소"
                        font.family: font_noto_r.name
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked:{
                            popup_preset_name.close();
                        }
                    }
                }
                Rectangle{
                    width: 100
                    height: 50
                    radius: 5
                    Text{
                        anchors.centerIn: parent
                        text: "확인"
                        font.family: font_noto_r.name
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked:{
                            supervisor.setSetting("setting","PRESET"+Number(popup_preset.select_preset)+"/name",preset_name.text);
                            popup_preset.update();
                            popup_preset_name.close();
                        }
                    }
                }
            }
        }
    }

    Popup{
        id: popup_preset_set
        anchors.centerIn: parent
        leftPadding: 0
        rightPadding: 0
        topPadding: 0
        bottomPadding: 0
        width: 450
        height: 300
        property var preset_num: 0
        background: Rectangle{
            anchors.fill: parent
            color: "transparent"
        }
        onOpened:{
            if(preset_num === 1){
                text_preset_name_set.text = "(  "+supervisor.getSetting("setting","PRESET1","name") + "   )";
            }else if(preset_num === 2){
                text_preset_name_set.text = "(  "+supervisor.getSetting("setting","PRESET2","name") + "   )";
            }else if(preset_num === 3){
                text_preset_name_set.text = "(  "+supervisor.getSetting("setting","PRESET3","name") + "   )";
            }else if(preset_num === 4){
                text_preset_name_set.text = "(  "+supervisor.getSetting("setting","PRESET4","name") + "   )";
            }else if(preset_num === 5){
                text_preset_name_set.text = "(  "+supervisor.getSetting("setting","PRESET5","name") + "   )";
            }
        }
        Rectangle{
            width: parent.width
            height: parent.height
            radius: 10
            color: color_dark_navy
            Column{
                anchors.centerIn: parent
                spacing: 30

                Text{
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: "선택하신 프리셋으로 세팅을 변경하시겠습니까?"
                    color: "white"
                    horizontalAlignment: Text.AlignHCenter
                    font.family: font_noto_r.name
                    font.pixelSize: 15
                }
                Text{
                    id: text_preset_name_set
                    anchors.horizontalCenter: parent.horizontalCenter
                    color: "white"
                    font.family: font_noto_r.name
                    font.pixelSize: 30
                }

                Row{
                    anchors.horizontalCenter: parent.horizontalCenter
                    spacing: 30
                    Rectangle{
                        width: 150
                        height: 50
                        radius: 5
                        color: "transparent"
                        border.width: 2
                        border.color: "white"
                        Text{
                            anchors.centerIn: parent
                            font.family: font_noto_r.name
                            text: "취소"
                            color: "white"
                        }
                        MouseArea{
                            anchors.fill: parent
                            onClicked:{
                                popup_preset_set.close();
                            }
                        }
                    }
                    Rectangle{
                        width: 150
                        height: 50
                        radius: 5
                        color: "white"
                        Text{
                            anchors.centerIn: parent
                            font.family: font_noto_r.name
                            text: "확인"
                        }
                        MouseArea{
                            anchors.fill: parent
                            onClicked:{
                                supervisor.setSetting("update","DRIVING/cur_preset",Number(popup_preset_set.preset_num));
                                is_reset_slam = true;
                                popup_preset_set.close();
                            }
                        }
                    }
                }
            }
        }
    }


    Popup{
        id: popup_password
        anchors.centerIn: parent
        width: 360
        height: 550
        background: Rectangle{
            anchors.fill: parent
            color: "transparent"
        }
        property string passwd: "2011"
        property string answer: ""
        property bool is_fail: false
        property var input_len: 0
        property bool open_menu: false
        onIs_failChanged: {
            if(is_fail){
                setfailed();
            }else{
                setfailclear();
            }
        }

        onOpened:{
            model_passwd.clear();
            is_fail = false
            model_passwd.append({"show":false,"failed":false})
            model_passwd.append({"show":false,"failed":false})
            model_passwd.append({"show":false,"failed":false})
            model_passwd.append({"show":false,"failed":false})

            model_pad.clear();
            model_pad.append({"name":"1"});
            model_pad.append({"name":"2"});
            model_pad.append({"name":"3"});
            model_pad.append({"name":"4"});
            model_pad.append({"name":"5"});
            model_pad.append({"name":"6"});
            model_pad.append({"name":"7"});
            model_pad.append({"name":"8"});
            model_pad.append({"name":"9"});
            model_pad.append({"name":"clear"});
            model_pad.append({"name":"0"});
            model_pad.append({"name":"<-"});
            answer = "";
            input_len = 0;
        }

        function setfailed(){
            for(var i=0; i<model_passwd.count; i++){
                model_passwd.get(i).failed = true;
            }
        }
        function setfailclear(){
            for(var i=0; i<model_passwd.count; i++){
                model_passwd.get(i).failed = false;
            }
        }

        onClosed:{
            if(is_admin && popup_update.opened){
                supervisor.writelog("[USER INPUT] Program Update : Password Correct -> pull start")
                supervisor.updateProgram();
                popup_update.close();
            }
            if(open_menu){
                popup_manager.open();
                open_menu = false;
            }
        }

        Rectangle{
            radius: 40
            clip: true
            anchors.centerIn: parent
            width: parent.width
            height: parent.height
            color: color_dark_navy
            Column{
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenterOffset: -20
                spacing: 50
                Rectangle{
                    width: 260
                    color: color_dark_navy
                    anchors.horizontalCenter: parent.horizontalCenter
                    height: 60
                    Row{
                        anchors.centerIn: parent
                        spacing: 15
                        Repeater{
                            model: ListModel{id: model_passwd}
                            Rectangle{
                                width: 50
                                height: 50
                                radius: 50
                                color: "transparent"
                                Rectangle{
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    visible: show
                                    width: 46
                                    height: width
                                    radius: width
                                    color: failed ? color_red : color_green
                                }
                                Rectangle{
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    anchors.bottom: parent.bottom
                                    anchors.bottomMargin: -10
                                    width: 50
                                    height: 2
                                    color: color_gray
                                }
                            }
                        }
                    }
                }

                Grid{
                    anchors.horizontalCenter: parent.horizontalCenter
                    spacing: 17
                    rows: 4
                    columns: 3
                    Repeater{
                        model: ListModel{id: model_pad}
                        Rectangle{
                            width: 70
                            height: width
                            radius: 70
                            color: color_navy
                            Text{
                                text: name
                                visible:name!=="clear"&&name!=="<-"
                                font.family: font_noto_r.name
                                font.pixelSize: 30
                                anchors.centerIn: parent
                                color: "white"
                            }
                            Image{
                                anchors.centerIn: parent
                                width: {
                                    if(name=="clear"){
                                        50
                                    }else{
                                        50
                                    }
                                }

                                height: width
                                visible:name==="clear"||name==="<-"
                                source:{
                                    if(name=="clear"){
                                        "icon/icon_trashcan.png"
                                    }else{
                                        "icon/btn_reset.png"
                                    }
                                }
                            }

                            MouseArea{
                                anchors.fill: parent
                                onClicked: {
                                    if(name==="clear"){
                                        popup_password.setfailclear();
                                        popup_password.is_fail = false;
                                        popup_password.input_len = 0;
                                        model_passwd.set(0,{"show":false});
                                        model_passwd.set(1,{"show":false});
                                        model_passwd.set(2,{"show":false});
                                        model_passwd.set(3,{"show":false});
                                        popup_password.answer = "";
                                    }else if(name==="<-"){
                                        if(popup_password.input_len === 0){

                                        }else{
                                            popup_password.input_len--;
                                            model_passwd.set(popup_password.input_len,{"show":false});
                                            popup_password.answer = popup_password.answer.slice(0,popup_password.input_len);
                                        }
                                        popup_password.is_fail = false;
                                    }else{
                                        if(popup_password.input_len === 4){
                                            is_admin = false;
                                            popup_password.is_fail = true;
                                            supervisor.writelog("[USER INPUT] SETTING PAGE -> ADMIN LOGIN FAILED "+popup_password.answer);
                                        }else{
                                            popup_password.is_fail = false;
                                            popup_password.answer += name;
                                            model_passwd.set(popup_password.input_len,{"show":true});
                                            popup_password.input_len++;
                                            if(popup_password.answer===popup_password.passwd){
                                                supervisor.writelog("[USER INPUT] SETTING PAGE -> ADMIN LOGIN SUCCESS");
                                                is_admin = true;
                                                popup_password.is_fail = true;
                                                popup_password.close();
                                            }else if(popup_password.input_len === 4){
                                                is_admin = false;
                                                popup_password.is_fail = true;
                                                supervisor.writelog("[USER INPUT] SETTING PAGE -> ADMIN LOGIN FAILED "+popup_password.answer);
                                            }else{
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
        id: popup_tf
        anchors.centerIn: parent
        leftPadding: 0
        rightPadding: 0
        topPadding: 0
        bottomPadding: 0
        background: Rectangle{
            anchors.fill: parent
            color: "transparent"
        }
        onOpened:{
            var left_str = supervisor.getSetting("static","SENSOR","left_camera_tf");
            var left_strs = left_str.split(",");
            tf_left_x.text = left_strs[0];
            tf_left_y.text = left_strs[1];
            tf_left_z.text = left_strs[2];
            tf_left_rx.text = left_strs[3];
            tf_left_ry.text = left_strs[4];
            tf_left_rz.text = left_strs[5];
            var right_str = supervisor.getSetting("static","SENSOR","right_camera_tf");
            var right_strs = right_str.split(",");
            tf_right_x.text = right_strs[0];
            tf_right_y.text = right_strs[1];
            tf_right_z.text = right_strs[2];
            tf_right_rx.text = right_strs[3];
            tf_right_ry.text = right_strs[4];
            tf_right_rz.text = right_strs[5];
            var lidar_str = supervisor.getSetting("static","SENSOR","lidar_offset_tf");
            var lidar_strs = lidar_str.split(",");

            tf_lidar_x.text = lidar_strs[0];
            tf_lidar_y.text = lidar_strs[1];
            tf_lidar_z.text = lidar_strs[2];
            tf_lidar_rx.text = lidar_strs[3];
            tf_lidar_ry.text = lidar_strs[4];
            tf_lidar_rz.text = lidar_strs[5];
        }

        width: 1280
        height: 500
        Rectangle{
            width: parent.width
            height: parent.height
            color: color_dark_navy
            Column{
                anchors.centerIn: parent
                spacing: 30
                Text{
                    id: text_tf
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: "라이다/카메라 TF 설정"
                    color: "white"
                    font.family: font_noto_r.name
                    font.pixelSize: 40
                }

                Grid{
                    id: grid_tf
                    columns: 7
                    rows: 4
                    anchors.horizontalCenter: parent.horizontalCenter
                    horizontalItemAlignment: Grid.AlignHCenter
                    verticalItemAlignment: Grid.AlignVCenter
                    spacing: 15
                    Text{
                        text: ""
                        width: 100
                        horizontalAlignment: Text.AlignHCenter
                        color: "white"
                        font.family: font_noto_r.name
                        font.pixelSize: 18
                    }
                    Text{
                        text: "X"
                        width: 50
                        horizontalAlignment: Text.AlignHCenter
                        color: "white"
                        font.family: font_noto_r.name
                        font.pixelSize: 20
                    }
                    Text{
                        text: "Y"
                        width: 50
                        horizontalAlignment: Text.AlignHCenter
                        color: "white"
                        font.family: font_noto_r.name
                        font.pixelSize: 20
                    }
                    Text{
                        text: "Z"
                        width: 50
                        horizontalAlignment: Text.AlignHCenter
                        color: "white"
                        font.family: font_noto_r.name
                        font.pixelSize: 20
                    }
                    Text{
                        text: "RX"
                        width: 50
                        horizontalAlignment: Text.AlignHCenter
                        color: "white"
                        font.family: font_noto_r.name
                        font.pixelSize: 20
                    }
                    Text{
                        text: "RY"
                        width: 50
                        horizontalAlignment: Text.AlignHCenter
                        color: "white"
                        font.family: font_noto_r.name
                        font.pixelSize: 20
                    }
                    Text{
                        text: "RZ"
                        width: 50
                        horizontalAlignment: Text.AlignHCenter
                        color: "white"
                        font.family: font_noto_r.name
                        font.pixelSize: 20
                    }

                    Text{
                        text: "라이다"
                        width: 150
                        horizontalAlignment: Text.AlignHCenter
                        color: "white"
                        font.family: font_noto_b.name
                        font.pixelSize: 30
                    }
                    TextField{
                        id: tf_lidar_x
                        width: 100
                        height: 50
                        font.family: font_noto_r.name
                        font.pixelSize: 15
                        horizontalAlignment: Text.AlignHCenter
                        MouseArea{
                            anchors.fill:parent
                            onClicked: {
                                if(keypad.is_opened){
                                    keypad.owner = tf_lidar_x;
                                    tf_lidar_x.selectAll();
                                }else{
                                    keypad.owner = tf_lidar_x;
                                    tf_lidar_x.selectAll();
                                    keypad.open();
                                }
                            }
                        }
                    }
                    TextField{
                        id: tf_lidar_y
                        width: 100
                        height: 50
                        font.family: font_noto_r.name
                        font.pixelSize: 15
                        horizontalAlignment: Text.AlignHCenter
                        MouseArea{
                            anchors.fill:parent
                            onClicked: {
                                if(keypad.is_opened){
                                    keypad.owner = tf_lidar_y;
                                    tf_lidar_y.selectAll();
                                }else{
                                    keypad.owner = tf_lidar_y;
                                    tf_lidar_y.selectAll();
                                    keypad.open();
                                }
                            }
                        }
                    }
                    TextField{
                        id: tf_lidar_z
                        width: 100
                        height: 50
                        font.family: font_noto_r.name
                        font.pixelSize: 15
                        horizontalAlignment: Text.AlignHCenter
                        MouseArea{
                            anchors.fill:parent
                            onClicked: {
                                if(keypad.is_opened){
                                    keypad.owner = tf_lidar_z;
                                    tf_lidar_z.selectAll();
                                }else{
                                    keypad.owner = tf_lidar_z;
                                    tf_lidar_z.selectAll();
                                    keypad.open();
                                }
                            }
                        }
                    }
                    TextField{
                        id: tf_lidar_rx
                        width: 100
                        height: 50
                        font.family: font_noto_r.name
                        font.pixelSize: 15
                        horizontalAlignment: Text.AlignHCenter
                        MouseArea{
                            anchors.fill:parent
                            onClicked: {
                                if(keypad.is_opened){
                                    keypad.owner = tf_lidar_rx;
                                    tf_lidar_rx.selectAll();
                                }else{
                                    keypad.owner = tf_lidar_rx;
                                    tf_lidar_rx.selectAll();
                                    keypad.open();
                                }
                            }
                        }
                    }
                    TextField{
                        id: tf_lidar_ry
                        width: 100
                        height: 50
                        font.family: font_noto_r.name
                        font.pixelSize: 15
                        horizontalAlignment: Text.AlignHCenter
                        MouseArea{
                            anchors.fill:parent
                            onClicked: {
                                if(keypad.is_opened){
                                    keypad.owner = tf_lidar_ry;
                                    tf_lidar_ry.selectAll();
                                }else{
                                    keypad.owner = tf_lidar_ry;
                                    tf_lidar_ry.selectAll();
                                    keypad.open();
                                }
                            }
                        }
                    }
                    TextField{
                        id: tf_lidar_rz
                        width: 100
                        height: 50
                        font.family: font_noto_r.name
                        font.pixelSize: 15
                        horizontalAlignment: Text.AlignHCenter
                        MouseArea{
                            anchors.fill:parent
                            onClicked: {
                                if(keypad.is_opened){
                                    keypad.owner = tf_lidar_rz;
                                    tf_lidar_rz.selectAll();
                                }else{
                                    keypad.owner = tf_lidar_rz;
                                    tf_lidar_rz.selectAll();
                                    keypad.open();
                                }
                            }
                        }
                    }
                    Text{
                        text: "왼쪽카메라"
                        width: 150
                        horizontalAlignment: Text.AlignHCenter
                        color: "white"
                        font.family: font_noto_b.name
                        font.pixelSize: 30
                    }
                    TextField{
                        id: tf_left_x
                        width: 100
                        height: 50
                        font.family: font_noto_r.name
                        font.pixelSize: 15
                        horizontalAlignment: Text.AlignHCenter
                        MouseArea{
                            anchors.fill:parent
                            onClicked: {
                                if(keypad.is_opened){
                                    keypad.owner = tf_left_x;
                                    tf_left_x.selectAll();
                                }else{
                                    keypad.owner = tf_left_x;
                                    tf_left_x.selectAll();
                                    keypad.open();
                                }
                            }
                        }
                    }
                    TextField{
                        id: tf_left_y
                        width: 100
                        height: 50
                        font.family: font_noto_r.name
                        font.pixelSize: 15
                        horizontalAlignment: Text.AlignHCenter
                        MouseArea{
                            anchors.fill:parent
                            onClicked: {
                                if(keypad.is_opened){
                                    keypad.owner = tf_left_y;
                                    tf_left_y.selectAll();
                                }else{
                                    keypad.owner = tf_left_y;
                                    tf_left_y.selectAll();
                                    keypad.open();
                                }
                            }
                        }
                    }
                    TextField{
                        id: tf_left_z
                        width: 100
                        height: 50
                        font.family: font_noto_r.name
                        font.pixelSize: 15
                        horizontalAlignment: Text.AlignHCenter
                        MouseArea{
                            anchors.fill:parent
                            onClicked: {
                                if(keypad.is_opened){
                                    keypad.owner = tf_left_z;
                                    tf_left_z.selectAll();
                                }else{
                                    keypad.owner = tf_left_z;
                                    tf_left_z.selectAll();
                                    keypad.open();
                                }
                            }
                        }
                    }
                    TextField{
                        id: tf_left_rx
                        width: 100
                        height: 50
                        font.family: font_noto_r.name
                        font.pixelSize: 15
                        horizontalAlignment: Text.AlignHCenter
                        MouseArea{
                            anchors.fill:parent
                            onClicked: {
                                if(keypad.is_opened){
                                    keypad.owner = tf_left_rx;
                                    tf_left_rx.selectAll();
                                }else{
                                    keypad.owner = tf_left_rx;
                                    tf_left_rx.selectAll();
                                    keypad.open();
                                }
                            }
                        }
                    }
                    TextField{
                        id: tf_left_ry
                        width: 100
                        horizontalAlignment: Text.AlignHCenter
                        height: 50
                        font.family: font_noto_r.name
                        font.pixelSize: 15
                        MouseArea{
                            anchors.fill:parent
                            onClicked: {
                                if(keypad.is_opened){
                                    keypad.owner = tf_left_ry;
                                    tf_left_ry.selectAll();
                                }else{
                                    keypad.owner = tf_left_ry;
                                    tf_left_ry.selectAll();
                                    keypad.open();
                                }
                            }
                        }
                    }
                    TextField{
                        id: tf_left_rz
                        width: 100
                        height: 50
                        font.family: font_noto_r.name
                        font.pixelSize: 15
                        horizontalAlignment: Text.AlignHCenter
                        MouseArea{
                            anchors.fill:parent
                            onClicked: {
                                if(keypad.is_opened){
                                    keypad.owner = tf_left_rz;
                                    tf_left_rz.selectAll();
                                }else{
                                    keypad.owner = tf_left_rz;
                                    tf_left_rz.selectAll();
                                    keypad.open();
                                }
                            }
                        }
                    }


                    Text{
                        text: "오른쪽카메라"
                        width: 150
                        horizontalAlignment: Text.AlignHCenter
                        color: "white"
                        font.family: font_noto_b.name
                        font.pixelSize: 30
                    }
                    TextField{
                        id: tf_right_x
                        width: 100
                        height: 50
                        font.family: font_noto_r.name
                        font.pixelSize: 15
                        horizontalAlignment: Text.AlignHCenter
                        MouseArea{
                            anchors.fill:parent
                            onClicked: {
                                if(keypad.is_opened){
                                    keypad.owner = tf_right_x;
                                    tf_right_x.selectAll();
                                }else{
                                    keypad.owner = tf_right_x;
                                    tf_right_x.selectAll();
                                    keypad.open();
                                }
                            }
                        }
                    }
                    TextField{
                        id: tf_right_y
                        width: 100
                        height: 50
                        font.family: font_noto_r.name
                        font.pixelSize: 15
                        horizontalAlignment: Text.AlignHCenter
                        MouseArea{
                            anchors.fill:parent
                            onClicked: {
                                if(keypad.is_opened){
                                    keypad.owner = tf_right_y;
                                    tf_right_y.selectAll();
                                }else{
                                    keypad.owner = tf_right_y;
                                    tf_right_y.selectAll();
                                    keypad.open();
                                }
                            }
                        }
                    }
                    TextField{
                        id: tf_right_z
                        width: 100
                        height: 50
                        font.family: font_noto_r.name
                        font.pixelSize: 15
                        horizontalAlignment: Text.AlignHCenter
                        MouseArea{
                            anchors.fill:parent
                            onClicked: {
                                if(keypad.is_opened){
                                    keypad.owner = tf_right_z;
                                    tf_right_z.selectAll();
                                }else{
                                    keypad.owner = tf_right_z;
                                    tf_right_z.selectAll();
                                    keypad.open();
                                }
                            }
                        }
                    }
                    TextField{
                        id: tf_right_rx
                        width: 100
                        height: 50
                        font.family: font_noto_r.name
                        font.pixelSize: 15
                        horizontalAlignment: Text.AlignHCenter
                        MouseArea{
                            anchors.fill:parent
                            onClicked: {
                                if(keypad.is_opened){
                                    keypad.owner = tf_right_rx;
                                    tf_right_rx.selectAll();
                                }else{
                                    keypad.owner = tf_right_rx;
                                    tf_right_rx.selectAll();
                                    keypad.open();
                                }
                            }
                        }
                    }
                    TextField{
                        id: tf_right_ry
                        width: 100
                        height: 50
                        font.family: font_noto_r.name
                        font.pixelSize: 15
                        horizontalAlignment: Text.AlignHCenter
                        MouseArea{
                            anchors.fill:parent
                            onClicked: {
                                if(keypad.is_opened){
                                    keypad.owner = tf_right_ry;
                                    tf_right_ry.selectAll();
                                }else{
                                    keypad.owner = tf_right_ry;
                                    tf_right_ry.selectAll();
                                    keypad.open();
                                }
                            }
                        }
                    }
                    TextField{
                        id: tf_right_rz
                        width: 100
                        height: 50
                        horizontalAlignment: Text.AlignHCenter
                        font.family: font_noto_r.name
                        font.pixelSize: 15
                        MouseArea{
                            anchors.fill:parent
                            onClicked: {
                                if(keypad.is_opened){
                                    keypad.owner = tf_right_rz;
                                    tf_right_rz.selectAll();
                                }else{
                                    keypad.owner = tf_right_rz;
                                    tf_right_rz.selectAll();
                                    keypad.open();
                                }
                            }
                        }
                    }
                }

                Row{
                    anchors.horizontalCenter: parent.horizontalCenter
                    spacing: 30
                    Rectangle{
                        width: 130
                        height: 60
                        radius: 5
                        border.width: 1
                        border.color: color_gray
                        Text{
                            anchors.centerIn: parent
                            color: color_dark_navy
                            font.family: font_noto_r.name
                            font.pixelSize: 20
                            text: "취소"
                        }
                        MouseArea{
                            anchors.fill: parent
                            onClicked:{
                                popup_tf.close();
                            }
                        }
                    }
                    Rectangle{
                        width: 130
                        height: 60
                        radius: 5
                        border.width: 1
                        border.color: color_gray
                        Text{
                            anchors.centerIn: parent
                            color: color_dark_navy
                            font.family: font_noto_r.name
                            font.pixelSize: 20
                            text: "확인"
                        }
                        MouseArea{
                            anchors.fill: parent
                            onClicked:{
                                supervisor.writelog("[USER INPUT] SETTING CAMERA TF CHANGED");

                                var lidar_str = tf_lidar_x.text + "," + tf_lidar_y.text + "," + tf_lidar_z.text + "," + tf_lidar_rx.text + "," + tf_lidar_ry.text  + "," + tf_lidar_rz.text;
                                var left_str = tf_left_x.text + "," + tf_left_y.text + "," + tf_left_z.text + "," + tf_left_rx.text + "," + tf_left_ry.text  + "," + tf_left_rz.text;
                                var right_str = tf_right_x.text + "," + tf_right_y.text + "," + tf_right_z.text + "," + tf_right_rx.text + "," + tf_right_ry.text  + "," + tf_right_rz.text;

                                supervisor.setSetting("static","SENSOR/lidar_offset_tf",lidar_str);
                                supervisor.setSetting("static","SENSOR/left_camera_tf",left_str);
                                supervisor.setSetting("static","SENSOR/right_camera_tf",right_str);

                                is_reset_slam = true;
                                popup_tf.close();
                            }
                        }
                    }
                }
            }
        }
    }

    Popup{
        id: popup_wifi
        anchors.centerIn: parent
        leftPadding: 0
        rightPadding: 0
        topPadding: 0
        bottomPadding: 0
        width: 1280
        height: 650
        closePolicy: Popup.NoAutoClose
        background: Rectangle{
            anchors.fill: parent
            color:"transparent"
        }
        function connect_fail(){
            print("wifi connect fail");
            text_wifi76788.visible = true;
        }

        function ip_update(){
            var ip = supervisor.getcurIP().split(".");
            if(ip.length >3){
                ip__1.text = ip[0];
                ip__2.text = ip[1];
                ip__3.text = ip[2];
                ip__4.text = ip[3];
            }else{
                ip__1.text = "";
                ip__2.text = "";
                ip__3.text = "";
                ip__4.text = "";
            }

            ip = supervisor.getcurGateway().split(".");
            if(ip.length >3){
                gateway__1.text = ip[0];
                gateway__2.text = ip[1];
                gateway__3.text = ip[2];
                gateway__4.text = ip[3];
            }else{
                gateway__1.text = "";
                gateway__2.text = "";
                gateway__3.text = "";
                gateway__4.text = "";
            }
            ip = supervisor.getcurGateway().split(".");
            if(ip.length >3){
                dns_1.text = ip[0];
                dns_2.text = ip[1];
                dns_3.text = ip[2];
                dns_4.text = ip[3];
            }else{
                dns_1.text = "";
                dns_2.text = "";
                dns_3.text = "";
                dns_4.text = "";
            }
            ip__1.ischanged = false;
            ip__2.ischanged = false;
            ip__3.ischanged = false;
            ip__4.ischanged = false;
            gateway__1.ischanged = false;
            gateway__2.ischanged = false;
            gateway__3.ischanged = false;
            gateway__4.ischanged = false;
            dns_1.ischanged = false;
            dns_2.ischanged = false;
            dns_3.ischanged = false;
            dns_4.ischanged = false;
        }
        property var connection : 0
        property var setting_step: 0
        property string select_ssd: ""
        property bool select_inuse: false
        property var select_level: 0
        property bool select_security: false
        property bool show_passwd: false
        onSetting_stepChanged: {
            if(setting_step === 0){
                timer_update_wifi.start();
                timer_update_state.stop();
            }
        }
        function init(){
            timer_update_wifi.start();
            setting_step = 0;
        }
        onOpened:{
            init();
//            timer_update_wifi.start();
        }
        onClosed:{
            timer_update_wifi.stop();
            timer_update_state.stop();
            init();
        }
        Timer{
            id: timer_update_wifi
            running: false
            repeat: wifi_update_auto
            interval: 3000
            triggeredOnStart: true
            onTriggered: {
                supervisor.getAllWifiList();
                model_wifis.clear();
                for(var i=0; i<supervisor.getWifiNum(); i++){
                    var ssid = supervisor.getWifiSSID(i);
//                    print(i,ssid);
                    model_wifis.append({"ssid":ssid,"inuse":supervisor.getWifiInuse(ssid),"rate":supervisor.getWifiRate(ssid),"level":supervisor.getWifiLevel(ssid),"security":supervisor.getWifiSecurity(ssid)});
                }
            }
        }
        Timer{
            id: timer_update_state
            running: false
            repeat: true
            interval: 500
            triggeredOnStart: true
            onTriggered: {
//                popup_wifi.connection = supervisor.getWifiConnection(popup_wifi.select_ssd);
            }
        }

        Rectangle{
            anchors.fill: parent
            color: "transparent"
            Rectangle{
                width: 1280
                height: 600
                anchors.bottom: parent.bottom
                Column{
                    anchors.centerIn: parent
                    spacing:30
                    visible: popup_wifi.setting_step === 0
                    Text{
                        id: text_main_wifi
                        anchors.horizontalCenter: parent.horizontalCenter
                        color: color_dark_black
                        font.family: font_noto_r.name
                        font.pixelSize: 40
                        text: "무선 WIFI를 설정해주세요"
                    }
                    Rectangle{
                        width: 1280
                        height: 450
                        Flickable{
                            id: flickable_wifi
                            anchors.fill: parent
                            clip: true
                            contentHeight: col_wifis.height
                            Column{
                                id: col_wifis
                                anchors.centerIn: parent
                                property var select_wifi: -1
                                spacing: 10
                                Repeater{
                                    model : ListModel{id: model_wifis}
                                    Rectangle{
                                        width: 700
                                        height: 50
                                        radius: 20
                                        color:col_wifis.select_wifi===index?color_green:"white"
                                        Rectangle{
                                            width: 600
                                            height: 50
                                            anchors.centerIn: parent
                                            color: "transparent"
                                            Text{
                                                anchors.centerIn: parent
                                                font.family: font_noto_r.name
                                                color:col_wifis.select_wifi===index?"white":"black"
                                                text: ssid
                                            }
                                            Text{
                                                font.family: font_noto_r.name
                                                text: "(사용중)"
                                                color: color_red
                                                visible: inuse
                                                font.pixelSize: 15
                                                anchors.verticalCenter: parent.verticalCenter
                                                anchors.right: parent.right
                                                anchors.rightMargin: 10
                                            }
                                            Image{
                                                visible: !inuse && security
                                                anchors.verticalCenter: parent.verticalCenter
                                                anchors.right: parent.right
                                                source: "icon/icon_lock_2.png"
                                                width: 50
                                                height: 50
                                                ColorOverlay{
                                                    anchors.fill: parent
                                                    source: parent
                                                    color: color_gray
                                                }
                                            }
                                            Rectangle{
                                                width: 30
                                                height: 30
                                                radius: 5
                                                anchors.verticalCenter: parent.verticalCenter
                                                anchors.left: parent.left
                                                anchors.leftMargin: 10
                                                Row{
                                                    spacing: 1
                                                    anchors.centerIn: parent
                                                    Rectangle{
                                                        width: 5
                                                        anchors.bottom: parent.bottom
                                                        height:level<1?2:5
                                                        color:{
                                                            if(level==0){
                                                                color_red
                                                            }else if(level==1){
                                                                color_red
                                                            }else if(level==2){
                                                                color_yellow
                                                            }else if(level==3){
                                                                color_green
                                                            }else if(level==4){
                                                                color_green
                                                            }
                                                        }
                                                    }
                                                    Rectangle{
                                                        width: 5
                                                        anchors.bottom: parent.bottom
                                                        height:level<2?2:10
                                                        color:{
                                                            if(level==0){
                                                                color_red
                                                            }else if(level==1){
                                                                color_red
                                                            }else if(level==2){
                                                                color_yellow
                                                            }else if(level==3){
                                                                color_green
                                                            }else if(level==4){
                                                                color_green
                                                            }
                                                        }
                                                    }
                                                    Rectangle{
                                                        width: 5
                                                        anchors.bottom: parent.bottom
                                                        height:level<3?2:15
                                                        color:{
                                                            if(level==0){
                                                                color_red
                                                            }else if(level==1){
                                                                color_red
                                                            }else if(level==2){
                                                                color_yellow
                                                            }else if(level==3){
                                                                color_green
                                                            }else if(level==4){
                                                                color_green
                                                            }
                                                        }
                                                    }
                                                    Rectangle{
                                                        width: 5
                                                        anchors.bottom: parent.bottom
                                                        height:level<4?2:20
                                                        color:{
                                                            if(level==0){
                                                                color_red
                                                            }else if(level==1){
                                                                color_red
                                                            }else if(level==2){
                                                                color_yellow
                                                            }else if(level==3){
                                                                color_green
                                                            }else if(level==4){
                                                                color_green
                                                            }
                                                        }
                                                    }
                                                }

                                            }
                                        }

                                        MouseArea{
                                            anchors.fill: parent
                                            onClicked:{
                                                click_sound.play();
                                                col_wifis.select_wifi = index;
                                                popup_wifi.select_ssd = ssid;
                                                popup_wifi.select_inuse = inuse;
                                                popup_wifi.select_security = security;
                                                popup_wifi.select_level = level;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                Column{
                    anchors.right: parent.right
                    anchors.rightMargin: 60
                    anchors.top: parent.top
                    anchors.topMargin: 60
                    Grid{
                        columns: 2
                        rows: 2
                        anchors.horizontalCenter: parent.horizontalCenter
                        horizontalItemAlignment: Grid.AlignHCenter
                        verticalItemAlignment: Grid.AlignVCenter
                        spacing: 10
                        RadioButton{
                            id: radio_update_always
                            width: 30
                            height: 30
                            checked: wifi_update_auto
                            onClicked: {
                                print(checked, wifi_update_auto);
                                if(!wifi_update_auto){
                                    timer_update_wifi.start();
                                    wifi_update_auto = true;
                                }
                            }
                        }
                        RadioButton{
                            id: radio_update_once
                            width: 30
                            height: 30
                            checked: !wifi_update_auto
                            onClicked: {
                                if(wifi_update_auto){
                                    wifi_update_auto = false;
                                }
                            }
                        }
                        Text{
                            text:"자동검색"
                            font.family: font_noto_r.name
                        }
                        Text{
                            text:"수동검색"
                            font.family: font_noto_r.name
                        }
                    }

                    Item_buttons{
                        type:"round_text"
                        width: 150
                        height: 50
                        text: "재검색"
                        fontsize: 20
                        anchors.horizontalCenter: parent.horizontalCenter
                        visible: !wifi_update_auto
                        onClicked:{
                            popup_loading.open();
                            timer_update_wifi.start();
                        }
                    }
                }


                Column{
                    anchors.centerIn: parent
                    spacing:30
                    visible: popup_wifi.setting_step ===1
                    Text{
                        anchors.horizontalCenter: parent.horizontalCenter
                        color: color_dark_black
                        font.family: font_noto_r.name
                        font.pixelSize: 40
                        text: "무선 WIFI에 연결합니다."
                    }
                    Rectangle{
                        width: 1280
                        height: 450
                        Rectangle{
                            width: 1280
                            height: 50
                            radius: 20
                            Rectangle{
                                width: 600
                                height: 50
                                anchors.horizontalCenter: parent.horizontalCenter
                                color: "transparent"
                                Text{
                                    anchors.centerIn: parent
                                    font.family: font_noto_r.name
                                    text: popup_wifi.select_ssd
                                }
                                Text{
                                    font.family: font_noto_r.name
                                    text: "(사용중)"
                                    color: color_red
                                    visible: popup_wifi.select_inuse
                                    font.pixelSize: 15
                                    anchors.verticalCenter: parent.verticalCenter
                                    anchors.right: parent.right
                                    anchors.rightMargin: 10
                                }
                                Image{
                                    visible: !popup_wifi.select_inuse && popup_wifi.select_security
                                    anchors.verticalCenter: parent.verticalCenter
                                    anchors.right: parent.right
                                    source: "icon/icon_lock_2.png"
                                    width: 50
                                    height: 50
                                    ColorOverlay{
                                        anchors.fill: parent
                                        source: parent
                                        color: color_gray
                                    }
                                }
                                Rectangle{
                                    width: 30
                                    height: 30
                                    radius: 5
                                    anchors.verticalCenter: parent.verticalCenter
                                    anchors.left: parent.left
                                    anchors.leftMargin: 10
                                    Row{
                                        spacing: 1
                                        anchors.centerIn: parent
                                        Rectangle{
                                            width: 5
                                            anchors.bottom: parent.bottom
                                            height:popup_wifi.select_level<1?2:5
                                            color:{
                                                if(popup_wifi.select_level==0){
                                                    color_red
                                                }else if(popup_wifi.select_level==1){
                                                    color_red
                                                }else if(popup_wifi.select_level==2){
                                                    color_yellow
                                                }else if(popup_wifi.select_level==3){
                                                    color_green
                                                }else if(popup_wifi.select_level==4){
                                                    color_green
                                                }
                                            }
                                        }
                                        Rectangle{
                                            width: 5
                                            anchors.bottom: parent.bottom
                                            height:popup_wifi.select_level<2?2:10
                                            color:{
                                                if(popup_wifi.select_level==0){
                                                    color_red
                                                }else if(popup_wifi.select_level==1){
                                                    color_red
                                                }else if(popup_wifi.select_level==2){
                                                    color_yellow
                                                }else if(popup_wifi.select_level==3){
                                                    color_green
                                                }else if(popup_wifi.select_level==4){
                                                    color_green
                                                }
                                            }
                                        }
                                        Rectangle{
                                            width: 5
                                            anchors.bottom: parent.bottom
                                            height:popup_wifi.select_level<3?2:15
                                            color:{
                                                if(popup_wifi.select_level==0){
                                                    color_red
                                                }else if(popup_wifi.select_level==1){
                                                    color_red
                                                }else if(popup_wifi.select_level==2){
                                                    color_yellow
                                                }else if(popup_wifi.select_level==3){
                                                    color_green
                                                }else if(popup_wifi.select_level==4){
                                                    color_green
                                                }
                                            }
                                        }
                                        Rectangle{
                                            width: 5
                                            anchors.bottom: parent.bottom
                                            height:popup_wifi.select_level<4?2:20
                                            color:{
                                                if(popup_wifi.select_level==0){
                                                    color_red
                                                }else if(popup_wifi.select_level==1){
                                                    color_red
                                                }else if(popup_wifi.select_level==2){
                                                    color_yellow
                                                }else if(popup_wifi.select_level==3){
                                                    color_green
                                                }else if(popup_wifi.select_level==4){
                                                    color_green
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }

                        Column{
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.verticalCenterOffset: 25
                            anchors.horizontalCenter: parent.horizontalCenter
                            spacing: 25
                            Rectangle{
                                anchors.horizontalCenter: parent.horizontalCenter
                                visible:{
                                    if(popup_wifi.select_security){
                                        if(popup_wifi.connection === 1){
                                            false
                                        }else if(popup_wifi.connection === 2 || popup_wifi.connection === 3){
                                            true
                                        }else{
                                            false
                                        }
                                    }else{
                                        true
                                    }
                                }
                                color:popup_wifi.connection===0?color_red:popup_wifi.connection===1?color_yellow:color_green
                                width: 500
                                height: 50
                                radius: 5
                                Text{
                                    anchors.centerIn: parent
                                    font.family: font_noto_r.name
                                    color:popup_wifi.connection===0?"black":"white"
                                    text:popup_wifi.connection===0?"연결 안됨":popup_wifi.connection===1?"연결 중":"연결 성공"
                                    font.pixelSize: 20
                                }
                            }
                            Text{
                                visible: !popup_wifi.connection&&popup_wifi.select_security
                                anchors.horizontalCenter: parent.horizontalCenter
                                text: "비밀번호를 입력해주세요"
                                font.family: font_noto_r.name
                                font.pixelSize: 20
                            }

                            Row{
                                visible: !popup_wifi.connection&&popup_wifi.select_security
                                anchors.horizontalCenter: parent.horizontalCenter
                                anchors.horizontalCenterOffset: 35
                                spacing: 20
                                Column{
                                    anchors.verticalCenter: parent.verticalCenter
                                    Text{
                                        id: text_wifi76788
                                        visible: false
                                        onVisibleChanged: {
                                            print("text wifi visible ",visible);
                                        }

                                        anchors.horizontalCenter: parent.horizontalCenter
                                        text: "비밀번호가 틀렸습니다"
                                        color: color_red
                                        font.family: font_noto_r.name
                                        font.pixelSize: 17
                                    }

                                    TextField{
                                        id: passwd_wifi
                                        width: 400
                                        height: 50
                                        anchors.horizontalCenter: parent.horizontalCenter
                                        horizontalAlignment: Text.AlignHCenter
                                        echoMode: popup_wifi.show_passwd?TextInput.Normal:TextInput.Password
                                        MouseArea{
                                            anchors.fill:parent
                                            onClicked: {
                                                if(keyboard.is_opened){
                                                    keyboard.owner = passwd_wifi;
                                                    passwd_wifi.selectAll();
                                                }else{
                                                    keyboard.owner = passwd_wifi;
                                                    keyboard.is_ko = false;
                                                    passwd_wifi.selectAll();
                                                    keyboard.open();
                                                }
                                            }
                                        }
                                        onTextChanged: {
                                            color = "black"
                                            text_wifi76788.visible = false;
                                        }
                                    }
                                }
                                Rectangle{
                                    anchors.verticalCenter: parent.verticalCenter
                                    width: 50
                                    height: 50
                                    radius: 5
                                    color: color_dark_navy
                                    border.color: "white"
                                    border.width: 1
                                    Image{
                                        anchors.centerIn: parent
                                        width: 35
                                        height: 35
                                        source:popup_wifi.show_passwd?"icon/icon_obj_yes.png":"icon/icon_obj_no.png"
                                    }
                                    MouseArea{
                                        anchors.fill: parent
                                        onClicked:{
                                            click_sound.play();
                                            if(popup_wifi.show_passwd){
                                                popup_wifi.show_passwd = false;
                                            }else{
                                                popup_wifi.show_passwd = true;
                                            }
                                        }
                                    }
                                }
                            }
                            Rectangle{
                                width: 200
                                height: 80
                                radius: 40
                                visible: !popup_wifi.connection
                                anchors.horizontalCenter: parent.horizontalCenter
                                color: "black"
                                Text{
                                    anchors.centerIn: parent
                                    text: "연결"
                                    font.pixelSize: 35
                                    font.family: font_noto_r.name
                                    color: "white"
                                }
                                MouseArea{
                                    anchors.fill: parent
                                    onClicked: {
                                        click_sound.play();
                                        if(popup_wifi.select_security){
                                            if(passwd_wifi.text == ""){
                                                text_wifi76788.visible = true;
                                            }else{
                                                print("check connect", popup_wifi.select_ssd, passwd_wifi.text);
                                                supervisor.connectWifi(popup_wifi.select_ssd, passwd_wifi.text);
                                                popup_loading.open();
                                            }
                                        }else{
                                            print("check connect", popup_wifi.select_ssd, passwd_wifi.text);
                                            supervisor.connectWifi(popup_wifi.select_ssd, passwd_wifi.text);
                                            popup_loading.open();
                                        }
                                    }
                                }
                            }
                        }
                    }
                }

                Column{
                    anchors.centerIn: parent
                    spacing:30
                    visible: popup_wifi.setting_step ===2
                    Text{
                        anchors.horizontalCenter: parent.horizontalCenter
                        color: color_dark_black
                        font.family: font_noto_r.name
                        font.pixelSize: 40
                        text: "무선 WIFI의 IP를 세팅합니다"
                    }
                    Rectangle{
                        width: 1280
                        height: 450
                        radius: 20
                        Column{
                            visible: !popup_loading.visible
                            anchors.centerIn: parent
                            spacing: 30
                            Row{
                                width: 700
                                height: 50
                                Rectangle{
                                    width: 200
                                    height: parent.height
                                    Text{
                                        anchors.verticalCenter: parent.verticalCenter
                                        anchors.left: parent.left
                                        anchors.leftMargin: 50
                                        font.family: font_noto_r.name
                                        text:"IP"
                                        font.pixelSize: 20
                                    }
                                }
                                Rectangle{
                                    width: 1
                                    height: parent.height
                                    color: "#d0d0d0"
                                }
                                Rectangle{
                                    width: parent.width - 201
                                    height: parent.height
                                    Row{
                                        spacing: 10
                                        anchors.centerIn: parent
                                        TextField{
                                            id: ip__1
                                            width: 70
                                            height: 40
                                            MouseArea{
                                                anchors.fill:parent
                                                onClicked: {
                                                    if(keypad.is_opened){
                                                        keypad.owner = ip__1;
                                                        ip__1.selectAll();
                                                    }else{
                                                        keypad.owner = ip__1;
                                                        ip__1.selectAll();
                                                        keypad.open();
                                                    }
                                                }
                                            }
                                            color: ischanged?color_red:"black"
                                            property bool ischanged: false
                                            onTextChanged: {
                                                ischanged = true;
                                                if(ip__1.text.split(".").length > 1){
                                                    ip__1.text = ip__1.text.split(".")[0];
                                                    keypad.owner = ip__2;
                                                    ip__2.selectAll();
                                                }
                                                if(ip__1.text.length == 3){
                                                    keypad.owner = ip__2;
                                                    ip__2.selectAll();
                                                }
                                            }
                                        }
                                        Text{
                                            anchors.verticalCenter: parent.verticalCenter
                                            text:"."
                                        }

                                        TextField{
                                            id: ip__2
                                            width: 70
                                            height: 40
                                            MouseArea{
                                                anchors.fill:parent
                                                onClicked: {
                                                    if(keypad.is_opened){
                                                        keypad.owner = ip__2;
                                                        ip__2.selectAll();
                                                    }else{
                                                        keypad.owner = ip__2;
                                                        ip__2.selectAll();
                                                        keypad.open();
                                                    }
                                                }
                                            }
                                            color: ischanged?color_red:"black"
                                            property bool ischanged: false
                                            onTextChanged: {
                                                ischanged = true;
                                                if(ip__2.text == "."){
                                                    ip__2.text = ip__2.text.split(".")[0]
                                                }

                                                if(ip__2.text.split(".").length > 1){
                                                    ip__2.text = ip__2.text.split(".")[0];
                                                    keypad.owner = ip__3;
                                                    ip__3.selectAll();
                                                }
                                                if(ip__2.text.length == 3){
                                                    keypad.owner = ip__3;
                                                    ip__3.selectAll();
                                                }
                                            }
                                        }
                                        Text{
                                            anchors.verticalCenter: parent.verticalCenter
                                            text:"."
                                        }
                                        TextField{
                                            id: ip__3
                                            width: 70
                                            height: 40
                                            MouseArea{
                                                anchors.fill:parent
                                                onClicked: {
                                                    if(keypad.is_opened){
                                                        keypad.owner = ip__3;
                                                        ip__3.selectAll();
                                                    }else{
                                                        keypad.owner = ip__3;
                                                        ip__3.selectAll();
                                                        keypad.open();
                                                    }
                                                }
                                            }
                                            color: ischanged?color_red:"black"
                                            property bool ischanged: false
                                            onTextChanged: {
                                                ischanged = true;
                                                if(ip__3.text == "."){
                                                    ip__3.text = ip__3.text.split(".")[0]
                                                }

                                                if(ip__3.text.split(".").length > 1){
                                                    ip__3.text = ip__3.text.split(".")[0];
                                                    keypad.owner = ip__4;
                                                    ip__4.selectAll();
                                                }
                                                if(ip__3.text.length == 3){
                                                    keypad.owner = ip__4;
                                                    ip__4.selectAll();
                                                }
                                            }
                                        }
                                        Text{
                                            anchors.verticalCenter: parent.verticalCenter
                                            text:"."
                                        }
                                        TextField{
                                            id: ip__4
                                            width: 70
                                            height: 40
                                            MouseArea{
                                                anchors.fill:parent
                                                onClicked: {
                                                    if(keypad.is_opened){
                                                        keypad.owner = ip__4;
                                                        ip__4.selectAll();
                                                    }else{
                                                        keypad.owner = ip__4;
                                                        ip__4.selectAll();
                                                        keypad.open();
                                                    }
                                                }
                                            }
                                            color: ischanged?color_red:"black"
                                            property bool ischanged: false
                                            onTextChanged: {
                                                ischanged = true;
                                                if(ip__4.text == "."){
                                                    ip__4.text = ip__4.text.split(".")[0]
                                                }

                                                if(ip__4.text.split(".").length > 1){
                                                    ip__4.text = ip__4.text.split(".")[0];
                                                    keypad.close();
                                                }
                                                if(ip__4.text.length == 3){
                                                    keypad.close();
                                                }
                                            }
                                        }
                                    }
                                }
                            }

                            Row{
                                width: 700
                                height: 50
                                Rectangle{
                                    width: 200
                                    height: parent.height
                                    Text{
                                        anchors.verticalCenter: parent.verticalCenter
                                        anchors.left: parent.left
                                        anchors.leftMargin: 50
                                        font.family: font_noto_r.name
                                        text:"Gateway"
                                        font.pixelSize: 20
                                    }
                                }
                                Rectangle{
                                    width: 1
                                    height: parent.height
                                    color: "#d0d0d0"
                                }

                                Rectangle{
                                    width: parent.width - 201
                                    height: parent.height
                                    Row{
                                        spacing: 10
                                        anchors.centerIn: parent
                                        TextField{
                                            id: gateway__1
                                            width: 70
                                            height: 40
                                            MouseArea{
                                                anchors.fill:parent
                                                onClicked: {
                                                    if(keypad.is_opened){
                                                        keypad.owner = gateway__1;
                                                        gateway__1.selectAll();
                                                    }else{
                                                        keypad.owner = gateway__1;
                                                        gateway__1.selectAll();
                                                        keypad.open();
                                                    }
                                                }
                                            }
                                            color: ischanged?color_red:"black"
                                            property bool ischanged: false
                                            onTextChanged: {
                                                ischanged = true;
                                                if(gateway__1.text.split(".").length > 1){
                                                    gateway__1.text = gateway__1.text.split(".")[0];
                                                    keypad.owner = gateway__2;
                                                    gateway__2.selectAll();
                                                }
                                                if(gateway__1.text.length == 3){
                                                    keypad.owner = gateway__2;
                                                    gateway__2.selectAll();
                                                }
                                            }
                                        }
                                        Text{
                                            anchors.verticalCenter: parent.verticalCenter
                                            text:"."
                                        }

                                        TextField{
                                            id: gateway__2
                                            width: 70
                                            height: 40
                                            MouseArea{
                                                anchors.fill:parent
                                                onClicked: {
                                                    if(keypad.is_opened){
                                                        keypad.owner = gateway__2;
                                                        gateway__2.selectAll();
                                                    }else{
                                                        keypad.owner = gateway__2;
                                                        gateway__2.selectAll();
                                                        keypad.open();
                                                    }
                                                }
                                            }
                                            color: ischanged?color_red:"black"
                                            property bool ischanged: false
                                            onTextChanged: {
                                                ischanged = true;
                                                if(gateway__2.text == "."){
                                                    gateway__2.text = gateway__2.text.split(".")[0]
                                                }

                                                if(gateway__2.text.split(".").length > 1){
                                                    gateway__2.text = gateway__2.text.split(".")[0];
                                                    keypad.owner = gateway__3;
                                                    gateway__3.selectAll();
                                                }
                                                if(gateway__2.text.length == 3){
                                                    keypad.owner = gateway__3;
                                                    gateway__3.selectAll();
                                                }
                                            }
                                        }
                                        Text{
                                            anchors.verticalCenter: parent.verticalCenter
                                            text:"."
                                        }
                                        TextField{
                                            id: gateway__3
                                            width: 70
                                            height: 40
                                            MouseArea{
                                                anchors.fill:parent
                                                onClicked: {
                                                    if(keypad.is_opened){
                                                        keypad.owner = gateway__3;
                                                        gateway__3.selectAll();
                                                    }else{
                                                        keypad.owner = gateway__3;
                                                        gateway__3.selectAll();
                                                        keypad.open();
                                                    }
                                                }
                                            }
                                            color: ischanged?color_red:"black"
                                            property bool ischanged: false
                                            onTextChanged: {
                                                ischanged = true;
                                                if(gateway__3.text == "."){
                                                    gateway__3.text = gateway__3.text.split(".")[0]
                                                }

                                                if(gateway__3.text.split(".").length > 1){
                                                    gateway__3.text = gateway__3.text.split(".")[0];
                                                    keypad.owner = gateway__4;
                                                    gateway__4.selectAll();
                                                }
                                                if(gateway__3.text.length == 3){
                                                    keypad.owner = gateway__4;
                                                    gateway__4.selectAll();
                                                }
                                            }
                                        }
                                        Text{
                                            anchors.verticalCenter: parent.verticalCenter
                                            text:"."
                                        }
                                        TextField{
                                            id: gateway__4
                                            width: 70
                                            height: 40
                                            MouseArea{
                                                anchors.fill:parent
                                                onClicked: {
                                                    if(keypad.is_opened){
                                                        keypad.owner = gateway__4;
                                                        gateway__4.selectAll();
                                                    }else{
                                                        keypad.owner = gateway__4;
                                                        gateway__4.selectAll();
                                                        keypad.open();
                                                    }
                                                }
                                            }
                                            color: ischanged?color_red:"black"
                                            property bool ischanged: false
                                            onTextChanged: {
                                                ischanged = true;
                                                if(gateway__4.text == "."){
                                                    gateway__4.text = gateway__4.text.split(".")[0]
                                                }

                                                if(gateway__4.text.split(".").length > 1){
                                                    gateway__4.text = gateway__4.text.split(".")[0];
                                                    keypad.close();
                                                }
                                                if(gateway__4.text.length == 3){
                                                    keypad.close();
                                                }
                                            }
                                        }
                                    }
                                }

                            }

                            Row{
                                width: 700
                                height: 50
                                Rectangle{
                                    width: 200
                                    height: 50
                                    Text{
                                        anchors.verticalCenter: parent.verticalCenter
                                        anchors.left: parent.left
                                        anchors.leftMargin: 50
                                        font.family: font_noto_r.name
                                        text:"DNS"
                                        font.pixelSize: 20
                                    }
                                }
                                Rectangle{
                                    width: 1
                                    height: parent.height
                                    color: "#d0d0d0"
                                }

                                Rectangle{
                                    width: parent.width - 201
                                    height: parent.height
                                    Row{
                                        spacing: 10
                                        anchors.centerIn: parent
                                        TextField{
                                            id: dns_1
                                            width: 70
                                            height: 40
                                            MouseArea{
                                                anchors.fill:parent
                                                onClicked: {
                                                    if(keypad.is_opened){
                                                        keypad.owner = dns_1;
                                                        dns_1.selectAll();
                                                    }else{
                                                        keypad.owner = dns_1;
                                                        dns_1.selectAll();
                                                        keypad.open();
                                                    }
                                                }
                                            }
                                            color: ischanged?color_red:"black"
                                            property bool ischanged: false
                                            onTextChanged: {
                                                ischanged = true;
                                                if(dns_1.text.split(".").length > 1){
                                                    dns_1.text = dns_1.text.split(".")[0];
                                                    keypad.owner = dns_2;
                                                    dns_2.selectAll();
                                                }
                                                if(dns_1.text.length == 3){
                                                    keypad.owner = dns_2;
                                                    dns_2.selectAll();
                                                }
                                            }
                                        }
                                        Text{
                                            anchors.verticalCenter: parent.verticalCenter
                                            text:"."
                                        }

                                        TextField{
                                            id: dns_2
                                            width: 70
                                            height: 40
                                            MouseArea{
                                                anchors.fill:parent
                                                onClicked: {
                                                    if(keypad.is_opened){
                                                        keypad.owner = dns_2;
                                                        dns_2.selectAll();
                                                    }else{
                                                        keypad.owner = dns_2;
                                                        dns_2.selectAll();
                                                        keypad.open();
                                                    }
                                                }
                                            }
                                            color: ischanged?color_red:"black"
                                            property bool ischanged: false
                                            onTextChanged: {
                                                ischanged = true;
                                                if(dns_2.text == "."){
                                                    dns_2.text = dns_2.text.split(".")[0]
                                                }

                                                if(dns_2.text.split(".").length > 1){
                                                    dns_2.text = dns_2.text.split(".")[0];
                                                    keypad.owner = dns_3;
                                                    dns_3.selectAll();
                                                }
                                                if(dns_2.text.length == 3){
                                                    keypad.owner = dns_3;
                                                    dns_3.selectAll();
                                                }
                                            }
                                        }
                                        Text{
                                            anchors.verticalCenter: parent.verticalCenter
                                            text:"."
                                        }
                                        TextField{
                                            id: dns_3
                                            width: 70
                                            height: 40
                                            MouseArea{
                                                anchors.fill:parent
                                                onClicked: {
                                                    if(keypad.is_opened){
                                                        keypad.owner = dns_3;
                                                        dns_3.selectAll();
                                                    }else{
                                                        keypad.owner = dns_3;
                                                        dns_3.selectAll();
                                                        keypad.open();
                                                    }
                                                }
                                            }
                                            color: ischanged?color_red:"black"
                                            property bool ischanged: false
                                            onTextChanged: {
                                                ischanged = true;
                                                if(dns_3.text == "."){
                                                    dns_3.text = dns_3.text.split(".")[0]
                                                }

                                                if(dns_3.text.split(".").length > 1){
                                                    dns_3.text = dns_3.text.split(".")[0];
                                                    keypad.owner = dns_4;
                                                    dns_4.selectAll();
                                                }
                                                if(dns_3.text.length == 3){
                                                    keypad.owner = dns_4;
                                                    dns_4.selectAll();
                                                }
                                            }
                                        }
                                        Text{
                                            anchors.verticalCenter: parent.verticalCenter
                                            text:"."
                                        }
                                        TextField{
                                            id: dns_4
                                            width: 70
                                            height: 40
                                            MouseArea{
                                                anchors.fill:parent
                                                onClicked: {
                                                    if(keypad.is_opened){
                                                        keypad.owner = dns_4;
                                                        dns_4.selectAll();
                                                    }else{
                                                        keypad.owner = dns_4;
                                                        dns_4.selectAll();
                                                        keypad.open();
                                                    }
                                                }
                                            }
                                            color: ischanged?color_red:"black"
                                            property bool ischanged: false
                                            onTextChanged: {
                                                ischanged = true;
                                                if(dns_4.text == "."){
                                                    dns_4.text = dns_4.text.split(".")[0]
                                                }

                                                if(dns_4.text.split(".").length > 1){
                                                    dns_4.text = dns_4.text.split(".")[0];
                                                    keypad.close();
                                                }
                                                if(dns_4.text.length == 3){
                                                    keypad.close();
                                                }
                                            }
                                        }
                                    }
                                }
                            }

                            Row{
                                anchors.horizontalCenter: parent.horizontalCenter
                                spacing: 30
                                Rectangle{
                                    width: 200
                                    height: 80
                                    radius: 40
                                    border.width: 1
                                    Text{
                                        anchors.centerIn: parent
                                        text: "초기화"
                                        font.pixelSize: 35
                                        font.family: font_noto_r.name
                                    }
                                    MouseArea{
                                        anchors.fill: parent
                                        onClicked: {
                                            click_sound.play();
                                            if(supervisor.getcurIP() === "")
                                                supervisor.getWifiIP();

                                            popup_wifi.ip_update();
                                        }
                                    }
                                }

                                Rectangle{
                                    width: 200
                                    height: 80
                                    radius: 40
                                    color: "black"
                                    Text{
                                        anchors.centerIn: parent
                                        text: "변경"
                                        font.pixelSize: 35
                                        font.family: font_noto_r.name
                                        color: "white"
                                    }
                                    MouseArea{
                                        anchors.fill: parent
                                        onClicked: {
                                            click_sound.play();
                                            ip__1.ischanged = false;
                                            ip__2.ischanged = false;
                                            ip__3.ischanged = false;
                                            ip__4.ischanged = false;
                                            var ip_string = ip__1.text + "." + ip__2.text + "." + ip__3.text + "." + ip__4.text;
                                            gateway__1.ischanged = false;
                                            gateway__2.ischanged = false;
                                            gateway__3.ischanged = false;
                                            gateway__4.ischanged = false;
                                            var gateway_string = gateway__1.text + "." + gateway__2.text + "." + gateway__3.text + "." + gateway__4.text;
                                            dns_1.ischanged = false;
                                            dns_2.ischanged = false;
                                            dns_3.ischanged = false;
                                            dns_4.ischanged = false;
                                            var dns_string = dns_1.text + "." + dns_2.text + "." + dns_3.text + "." + dns_4.text;
                                            supervisor.setWifi(ip_string,gateway_string,dns_string);
                                            supervisor.setSetting("setting","NETWORK/wifi_ip",ip_string);
                                            supervisor.setSetting("setting","NETWORK/wifi_gateway",gateway_string);
                                            supervisor.setSetting("setting","NETWORK/wifi_dnsmain",dns_string);
                                            popup_wifi.connection = false;
                                            popup_loading.open();
                                        }
                                    }
                                }

                            }
                        }
                    }
                }

                Rectangle{
                    width: 200
                    height: 80
                    radius: 50
                    color: "transparent"
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 30
                    anchors.left: parent.left
                    anchors.leftMargin: 50
                    border.width: 2
                    border.color: color_green
                    Text{
                        anchors.centerIn: parent
                        text: popup_wifi.setting_step == 0 ?"취소":"이전"
                        font.pixelSize: 35
                        font.family: font_noto_r.name
                        color: color_dark_black
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            click_sound.play();
                            if(popup_wifi.setting_step === 0){
                                popup_wifi.close();
                                init();
                            }else{
                                popup_wifi.setting_step--;
                            }

                        }
                    }
                }
                Rectangle{
                    width: 200
                    height: 80
                    radius: 50
                    enabled:{
                        if(popup_wifi.setting_step === 0){
                            if(col_wifis.select_wifi > -1){
                                true
                            }else{
                                false
                            }
                        }else{
                            popup_wifi.connection
                        }
                    }
                    color: enabled?color_green:color_gray
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 30
                    anchors.right: parent.right
                    anchors.rightMargin: 50
                    Text{
                        anchors.centerIn: parent
                        text: popup_wifi.setting_step < 2 ?"다음":"설정 완료"
                        font.pixelSize: 35
                        font.family: font_noto_r.name
                        color: "white"
                    }
                    MouseArea{
                        anchors.fill: parent
                        onPressed:{
                            click_sound.play();
                            parent.color = color_mid_green;
                        }
                        onReleased: {
                            parent.color = color_green;
                        }
                        onClicked: {
                            if(popup_wifi.setting_step == 0){
                                popup_loading.open();
                                supervisor.writelog("[USER INPUT] INIT PAGE : IP SETTING NEXT 1");
                                popup_wifi.setting_step++;
                                timer_update_wifi.stop();
                                supervisor.readWifiState(popup_wifi.select_ssd);
                                click_sound.play();
        //                                    timer_update_state.start();
                            }else if(popup_wifi.setting_step == 1){
                                if(popup_wifi.connection === 2 || popup_wifi.connection === 3){
                                    supervisor.writelog("[USER INPUT] INIT PAGE : IP SETTING NEXT 2");
                                    supervisor.getWifiIP();
                                    popup_wifi.setting_step++;
                                    click_sound.play();
                                }else{
                                    click_sound_no.play();
                                }
                            }else{
        //                                    supervisor.save
                                click_sound.play();
                                supervisor.writelog("[USER INPUT] INIT PAGE : SETTING DONE");
                                popup_wifi.close();
                            }
                        }
                    }
                }

            }
        }

    }





//    function wifi_con_failed(){
//        print("wifi_con_failed")
//        popup_loading.close();
//        passwd_wifi.color = color_red;
//        text_wifi76788.visible = true;
//    }
//    function wifi_con_success(){
//        print("wifi_con_success")
//        popup_loading.close();
//        popup_wifi_passwd.close();
//        popup_wifi.close();
//        init();
//    }

    Popup{
        id: popup_changed
        anchors.centerIn: parent
        leftPadding: 0
        rightPadding: 0
        topPadding: 0
        bottomPadding: 0
        width: 450
        height: 300
        background: Rectangle{
            anchors.fill: parent
            color: "transparent"
        }
        Rectangle{
            width: parent.width
            height: parent.height
            radius: 10
            color: color_dark_navy
            Column{
                anchors.centerIn: parent
                spacing: 30

                Text{
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: "세팅값 변경 감지"
                    color: "white"
                    font.family: font_noto_r.name
                    font.pixelSize: 30
                }

                Text{
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: "변경한 값으로 저장하시려면 확인 버튼을 눌러주세요\n취소하시면 저장되지 않습니다"
                    color: "white"
                    horizontalAlignment: Text.AlignHCenter
                    font.family: font_noto_r.name
                    font.pixelSize: 15
                }
                Row{
                    anchors.horizontalCenter: parent.horizontalCenter
                    spacing: 30
                    Rectangle{
                        width: 150
                        height: 50
                        radius: 5
                        color: "transparent"
                        border.width: 2
                        border.color: "white"
                        Text{
                            anchors.centerIn: parent
                            font.family: font_noto_r.name
                            text: "취소"
                            color: "white"
                        }
                        MouseArea{
                            anchors.fill: parent
                            onClicked:{
                                backPage();
                            }
                        }
                    }
                    Rectangle{
                        width: 150
                        height: 50
                        radius: 5
                        color: "white"
                        Text{
                            anchors.centerIn: parent
                            font.family: font_noto_r.name
                            text: "확인"
                        }
                        MouseArea{
                            anchors.fill: parent
                            onClicked:{
                                save();
                                backPage();
                            }
                        }
                    }
                }
            }
        }
    }
    Popup_map_list{
        id: popup_maplist
    }
//    SoundEffect{
//        id: click
//        source: "bgm/click.wav"
//    }
}
