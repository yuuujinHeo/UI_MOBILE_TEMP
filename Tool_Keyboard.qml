import QtQuick 2.12
import QtQuick.Controls 2.12
import "."
import QtMultimedia 5.12

Popup {
    id: tool_keyboard
    width: 1280
    height: 800
    leftPadding: 0
    rightPadding: 0
    topPadding: 0
    bottomPadding: 0

    background:Rectangle{
        id: background_rect
        opacity: 0
        anchors.fill: parent
        color: "#653D92"
    }

    property bool is_opened: false
    property var owner
    property string owner_text: ""

    property bool is_ko: true
    property bool is_shift: false
    property bool is_capslock: false
    property bool only_en: false

    property var keysize: 55
    property var keytopmargin: 15
    property var keyrightmargin: 10

    property var textsize: 25

    property bool on_bottom: true

    property var keyboard_height: parent.height - rect_keyboard.height
    property color color_default: "#D0D0D0"
    property color color_highlight: "#12d27c"

    Component.onCompleted: {
        setHanEn();
    }


    onIs_koChanged: {
        setHanEn();
    }

    function setHanEn(){
        if(only_en)
            is_ko = false;

        is_shift = false;
        is_capslock = false;
        if(is_ko){
            text_ko_en.text = "한글";
            keys_2.model = ["ㅂ","ㅈ","ㄷ","ㄱ","ㅅ","ㅛ","ㅕ","ㅑ","ㅐ","ㅔ"];
            keys_3.model = ["ㅁ","ㄴ","ㅇ","ㄹ","ㅎ","ㅗ","ㅓ","ㅏ","ㅣ"];
            keys_4.model = ["ㅋ","ㅌ","ㅊ","ㅍ","ㅠ","ㅜ","ㅡ","_","!"];
        }else{
            text_ko_en.text = "영어";
            keys_2.model = ["q","w","e","r","t","y","u","i","o","p"];
            keys_3.model = ["a","s","d","f","g","h","j","k","l"];
            keys_4.model = ["z","x","c","v","b","n","m","_","!"];
        }
    }

    onIs_shiftChanged: {
        if(only_en)
            is_ko = false;

        if(is_shift){
            btn_shift.color =color_highlight;
//            keys_1.model= ["!","@","#","*","_","-","+","/","&","|"]
            if(is_ko){
                keys_2.model = ["ㅃ","ㅉ","ㄸ","ㄲ","ㅆ","ㅛ","ㅕ","ㅑ","ㅒ","ㅖ"];
                keys_3.model = ["ㅁ","ㄴ","ㅇ","ㄹ","ㅎ","ㅗ","ㅓ","ㅏ","ㅣ"];
                keys_4.model = ["ㅋ","ㅌ","ㅊ","ㅍ","ㅠ","ㅜ","ㅡ","&","|"];
            }else{
                keys_2.model = ["Q","W","E","R","T","Y","U","I","O","P"];
                keys_3.model = ["A","S","D","F","G","H","J","K","L"];
                keys_4.model = ["Z","X","C","V","B","N","M","&","|"];
            }
        }else{
            is_capslock = false;
            btn_shift.color = color_default;
//            keys_1.model= [1,2,3,4,5,6,7,8,9,0]
            if(is_ko){
                keys_2.model = ["ㅂ","ㅈ","ㄷ","ㄱ","ㅅ","ㅛ","ㅕ","ㅑ","ㅐ","ㅔ"];
                keys_3.model = ["ㅁ","ㄴ","ㅇ","ㄹ","ㅎ","ㅗ","ㅓ","ㅏ","ㅣ"];
                keys_4.model = ["ㅋ","ㅌ","ㅊ","ㅍ","ㅠ","ㅜ","ㅡ","_","!"];
            }else{
                keys_2.model = ["q","w","e","r","t","y","u","i","o","p"];
                keys_3.model = ["a","s","d","f","g","h","j","k","l"];
                keys_4.model = ["z","x","c","v","b","n","m","_","!"];
            }
        }
    }
    onOn_bottomChanged: {
        if(on_bottom){
            keyboard_height = parent.height - rect_keyboard.height
            area_cancel.enabled = true;
            area_cancel2.enabled = false;
        }else{
            keyboard_height = 0;
            area_cancel2.enabled = true;
            area_cancel.enabled = false;
        }
    }

    MouseArea{
        id: area_cancel
        width: parent.width
        height: parent.height - rect_keyboard.height
        onClicked: {
            //click.play();
            tool_keyboard.close();
            owner.focus = false;
        }
    }
    onOpened: {
        print("keyboard opened : ",owner_text);
        emitter.initHangul();
        rect_keyboard.height = 300;
        is_opened = true;
    }
    onClosed: {
        rect_keyboard.height = 0;
        is_opened = false;
        owner.select(0,0);
    }

    Rectangle{
        id: rect_keyboard
        width: parent.width
        y: keyboard_height
        Behavior on y{
            NumberAnimation{
                duration: 300
            }
        }
        height: 0
        color: "white"
        Row{
            Rectangle{
                height: 300
                width: 100
                color: "#D0D0D0"
                Image{
                    source: "icon/joy_up.png"
                    width: parent.width*0.8
                    height: 40
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: parent.top
                    anchors.topMargin: 30
                }
                Image{
                    source: "icon/joy_down.png"
                    width: parent.width*0.8
                    height: 40
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 30
                }

                Column{
                    anchors.centerIn: parent
                    spacing: keytopmargin
                    Rectangle{
                        width: 100
                        height: keysize
                        visible: !only_en
                        radius: 5
                        color: "transparent"
                        Text{
                            id: text_ko_en
                            anchors.centerIn: parent
                            color: "white"
                            text: "한글"
                            font.family: font_noto_r.name
                            font.pixelSize: textsize
                        }
                    }
                }
                MouseArea{
                    anchors.fill: parent
                    property var firstHeight: keyboard_height
                    property var firstPos: 0
                    onClicked: {
                        //click.play();
                        if(on_bottom){
                            on_bottom = false;
                        }else{
                            on_bottom = true;
                        }
                    }
                }
            }
            Rectangle{
                id: rect_keys
                height: 300
                width: 1280 - 100
                Row{
                    spacing: 80
                    anchors.centerIn: parent
                    Column{
                        spacing: keytopmargin
                        Row{
                            anchors.horizontalCenter: parent.horizontalCenter
                            spacing: keyrightmargin
                            Repeater{
                                id: keys_2
                                model: ["q","w","e","r","t","y","u","i","o","p"]
                                Rectangle{
                                    width: keysize
                                    height: width
                                    radius: 5
                                    color: "#D0D0D0"
                                    Text{
                                        anchors.centerIn: parent
                                        text: modelData
                                        font.family: font_noto_r.name
                                        font.pixelSize: textsize
                                    }
                                    MouseArea{
                                        anchors.fill: parent
                                        onClicked:{
                                            //click.play();
                                            if(is_ko){
                                                emitter.setHangul(owner, modelData);
                                            }else{
                                                emitter.keyPressed(owner,modelData);
                                            }

                                            if(!is_capslock)
                                                is_shift = false;
                                        }
                                    }
                                }
                            }
                            Rectangle{
                                width: keysize
                                height: width
                                radius: 5
                                color: "#D0D0D0"
                                Text{
                                    anchors.centerIn: parent
                                    text: "←"
                                    font.family: font_noto_r.name
                                    font.pixelSize: textsize
                                }
                                MouseArea{
                                    anchors.fill: parent
                                    onClicked:{
                                        //click.play();
                                        emitter.keyPressed(owner,Qt.Key_Backspace);
                                        if(!is_capslock)
                                            is_shift = false;
                                    }
                                    onPressAndHold: {
                                        //click.play();
                                        timer_backspace.start();
                                    }
                                    onReleased: {
                                        timer_backspace.stop();
                                        if(!is_capslock)
                                            is_shift = false;
                                    }
                                    Timer{
                                        id: timer_backspace
                                        interval: 100
                                        running: false
                                        repeat: true
                                        onTriggered: {
                                            emitter.keyPressed(owner,Qt.Key_Backspace);
                                        }
                                    }
                                }
                            }
                        }
                        Row{
                            anchors.horizontalCenter: parent.horizontalCenter
                            spacing: keyrightmargin
                            Repeater{
                                id: keys_3
                                model: ["a","s","d","f","g","h","j","k","l"]
                                Rectangle{
                                    width: keysize
                                    height: width
                                    radius: 5
                                    color: "#D0D0D0"
                                    Text{
                                        anchors.centerIn: parent
                                        text: modelData
                                        font.family: font_noto_r.name
                                        font.pixelSize: textsize
                                    }
                                    MouseArea{
                                        anchors.fill: parent
                                        onClicked:{
                                            //click.play();
                                            if(is_ko){
                                                emitter.setHangul(owner, modelData);
                                            }else{
                                                emitter.keyPressed(owner,modelData);
                                            }
                                            if(!is_capslock)
                                                is_shift = false;
                                        }
                                    }
                                }
                            }
                            Rectangle{
                                width: keysize*2 + keyrightmargin
                                height: keysize
                                radius: 5
                                color: "#D0D0D0"
                                Text{
                                    anchors.centerIn: parent
                                    text: "Enter"
                                    font.family: font_noto_r.name
                                    font.pixelSize: textsize
                                }
                                MouseArea{
                                    anchors.fill: parent
                                    onClicked:{
                                        //click.play();
                                        owner.focus = false;
                                        tool_keyboard.close();
                                        emitter.initHangul();
                                    }
                                }
                            }
                        }
                        Row{
                            anchors.horizontalCenter: parent.horizontalCenter
                            spacing: keyrightmargin
                            Rectangle{
                                id: btn_shift
                                width: keysize*2 + keyrightmargin
                                height: keysize
                                radius: 5
                                color: "#D0D0D0"
                                Text{
                                    anchors.centerIn: parent
                                    text: "Shift"
                                    font.family: font_noto_r.name
                                    font.pixelSize: textsize
                                }
                                MouseArea{
                                    anchors.fill: parent
                                    onClicked:{
                                        //click.play();
                                        if(is_shift){
                                            is_capslock = false;
                                            is_shift = false;
                                        }else{
                                            is_shift = true;
                                        }
                                    }
                                    onPressAndHold: {
                                        //click.play();
                                        is_shift = true;
                                        is_capslock = true;
                                    }
                                }
                            }
                            Repeater{
                                id: keys_4
                                model: ["z","x","c","v","b","n","m","_","!"]
                                Rectangle{
                                    width: keysize
                                    height: width
                                    radius: 5
                                    color: "#D0D0D0"
                                    Text{
                                        anchors.centerIn: parent
                                        text: modelData
                                        font.family: font_noto_r.name
                                        font.pixelSize: textsize
                                    }
                                    MouseArea{
                                        anchors.fill: parent
                                        onClicked:{
                                            //click.play();
                                            if(is_ko && (modelData != "_" && modelData != "!" && modelData != "&" && modelData != "|")){
                                                emitter.setHangul(owner,modelData);
                                            }else{
                                                emitter.keyPressed(owner,modelData);
                                                emitter.initHangul();
                                            }
                                            if(!is_capslock)
                                                is_shift = false;
                                        }
                                    }
                                }
                            }
                        }
                        Row{
                            anchors.horizontalCenter: parent.horizontalCenter
                            spacing: keyrightmargin
                            Rectangle{
                                id: btn_left
                                width: keysize*2 + keyrightmargin
                                height: keysize
                                radius: 5
                                color: "#D0D0D0"
                                Text{
                                    anchors.centerIn: parent
                                    text: "<-"
                                    font.family: font_noto_r.name
                                    font.pixelSize: textsize
                                }
                                MouseArea{
                                    anchors.fill: parent
                                    onClicked:{
                                        //click.play();
                                        emitter.keyPressed(owner,Qt.Key_Left);
                                        emitter.initHangul();
                                        if(!is_capslock)
                                            is_shift = false;
                                    }
                                    onPressAndHold: {
                                        //click.play();
                                        timer_left.start();
                                    }
                                    onReleased: {
                                        timer_left.stop();
                                        if(!is_capslock)
                                            is_shift = false;
                                    }
                                    Timer{
                                        id: timer_left
                                        interval: 100
                                        running: false
                                        repeat: true
                                        onTriggered: {
                                            emitter.keyPressed(owner,Qt.Key_Left);
                                        }
                                    }
                                }
                            }
                            Rectangle{
                                id: btn_spacebar
                                width: keysize*5 + keyrightmargin*4
                                height: keysize
                                radius: 5
                                color: "#D0D0D0"
                                MouseArea{
                                    anchors.fill: parent
                                    onClicked:{
                                        //click.play();
                                        emitter.keyPressed(owner,Qt.Key_Space);
                                        emitter.initHangul();
                                        if(!is_capslock)
                                            is_shift = false;
                                    }
                                }
                            }
                            Rectangle{
                                id: btn_hangul
                                width: keysize*2 + keyrightmargin*1
                                height: keysize
                                radius: 5
                                color: "#D0D0D0"
                                Text{
                                    anchors.centerIn: parent
                                    text: "한/영"
                                    font.family: font_noto_r.name
                                    font.pixelSize: textsize
                                }
                                MouseArea{
                                    anchors.fill: parent
                                    onClicked:{
                                        //click.play();
                                        if(is_ko)
                                            is_ko = false;
                                        else
                                            is_ko  = true;
                                    }
                                }
                            }
                            Rectangle{
                                id: btn_right
                                width: keysize*2 + keyrightmargin
                                height: keysize
                                radius: 5
                                color: "#D0D0D0"
                                Text{
                                    anchors.centerIn: parent
                                    text: "->"
                                    font.family: font_noto_r.name
                                    font.pixelSize: textsize
                                }
                                MouseArea{
                                    anchors.fill: parent
                                    onClicked:{
                                        //click.play();
                                        emitter.keyPressed(owner,Qt.Key_Right);
                                        emitter.initHangul();
                                        if(!is_capslock)
                                            is_shift = false;
                                    }
                                    onPressAndHold: {
                                        //click.play();
                                        timer_right.start();
                                    }
                                    onReleased: {
                                        timer_right.stop();
                                        if(!is_capslock)
                                            is_shift = false;
                                    }
                                    Timer{
                                        id: timer_right
                                        interval: 100
                                        running: false
                                        repeat: true
                                        onTriggered: {
                                            emitter.keyPressed(owner,Qt.Key_Right);
                                        }
                                    }
                                }
                            }
                        }
                    }

                    Column{
                        spacing: keytopmargin
                        Row{
                            anchors.horizontalCenter: parent.horizontalCenter
                            spacing: keyrightmargin
                            Repeater{
                                id: keys_11
                                model: ["7","8","9"]
                                Rectangle{
                                    width: keysize
                                    height: width
                                    radius: 5
                                    color: "#D0D0D0"
                                    Text{
                                        anchors.centerIn: parent
                                        text: modelData
                                        font.family: font_noto_r.name
                                        font.pixelSize: textsize
                                    }
                                    MouseArea{
                                        anchors.fill: parent
                                        onClicked:{
                                            //click.play();
                                            emitter.keyPressed(owner,modelData);
                                            emitter.initHangul();
                                            if(!is_capslock)
                                                is_shift = false;
                                        }
                                    }
                                }
                            }
                        }
                        Row{
                            anchors.horizontalCenter: parent.horizontalCenter
                            spacing: keyrightmargin
                            Repeater{
                                id: keys_22
                                model: ["4","5","6"]
                                Rectangle{
                                    width: keysize
                                    height: width
                                    radius: 5
                                    color: "#D0D0D0"
                                    Text{
                                        anchors.centerIn: parent
                                        text: modelData
                                        font.family: font_noto_r.name
                                        font.pixelSize: textsize
                                    }
                                    MouseArea{
                                        anchors.fill: parent
                                        onClicked:{
                                            //click.play();
                                            emitter.keyPressed(owner,modelData);
                                            emitter.initHangul();
                                            if(!is_capslock)
                                                is_shift = false;
                                        }
                                    }
                                }
                            }
                        }
                        Row{
                            anchors.horizontalCenter: parent.horizontalCenter
                            spacing: keyrightmargin
                            Repeater{
                                id: keys_33
                                model: ["1","2","3"]
                                Rectangle{
                                    width: keysize
                                    height: width
                                    radius: 5
                                    color: "#D0D0D0"
                                    Text{
                                        anchors.centerIn: parent
                                        text: modelData
                                        font.family: font_noto_r.name
                                        font.pixelSize: textsize
                                    }
                                    MouseArea{
                                        anchors.fill: parent
                                        onClicked:{
                                            //click.play();
                                            emitter.keyPressed(owner,modelData);
                                            emitter.initHangul();
                                            if(!is_capslock)
                                                is_shift = false;
                                        }
                                    }
                                }
                            }
                        }
                        Row{
                            anchors.horizontalCenter: parent.horizontalCenter
                            spacing: keyrightmargin
                            Rectangle{
                                id: btn_0
                                width: keysize*2 + keyrightmargin
                                height: keysize
                                radius: 5
                                color: "#D0D0D0"
                                Text{
                                    anchors.centerIn: parent
                                    text: "0"
                                    font.family: font_noto_r.name
                                    font.pixelSize: textsize
                                }
                                MouseArea{
                                    anchors.fill: parent
                                    onClicked:{
                                        //click.play();
                                        emitter.keyPressed(owner,"0");
                                        emitter.initHangul();
                                        if(!is_capslock)
                                            is_shift = false;
                                    }
                                }
                            }
                            Rectangle{
                                width: keysize
                                height: width
                                radius: 5
                                color: "#D0D0D0"
                                Text{
                                    anchors.centerIn: parent
                                    text: "."
                                    font.family: font_noto_r.name
                                    font.pixelSize: textsize
                                }
                                MouseArea{
                                    anchors.fill: parent
                                    onClicked:{
                                        //click.play();
                                        emitter.keyPressed(owner,".");
                                        emitter.initHangul();
                                        if(!is_capslock)
                                            is_shift = false;
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
        id: area_cancel2
        anchors.bottom: parent.bottom
        width: parent.width
        enabled: false
        height: parent.height - rect_keyboard.height
        onClicked: {
            //click.play();
            tool_keyboard.close();
            owner.focus = false;
        }
    }

//    SoundEffect{
//        id: click
//        source: "bgm/click.wav"
//    }
}
