import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.0
import "."

Popup{
    id: popup_password
    anchors.centerIn: parent
    width: 450
    height: 620
    background: Rectangle{
        anchors.fill: parent
        color: "transparent"
    }
    property bool is_editmode: false
    property string passwd: "2011"
    property string answer: ""
    property int input_len: 0
    property bool open_menu: false


    signal logined
    signal login_rainbow
    signal edited
    signal failed

    onOpened:{
        is_editmode = false;
        model_passwd.clear();
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


    Rectangle{
        clip: true
        anchors.centerIn: parent
        width: parent.width
        height: parent.height
        color: color_dark_navy
        Column{
            anchors.fill: parent
            Rectangle{
                width: parent.width
                height: parent.height*0.4
                color: "white"
                Column{
                    anchors.centerIn: parent
                    spacing: 25
                    Text{
                        text: qsTr("비밀번호를 입력해주세요")
                        font.pixelSize: 30
                        font.family: font_noto_r.name
                        anchors.horizontalCenter: parent.horizontalCenter
                    }

                    Row{
                        anchors.horizontalCenter: parent.horizontalCenter
                        spacing: 23
                        Repeater{
                            model: ListModel{id: model_passwd}
                            Rectangle{
                                width: 60
                                height: 60
                                radius: 60
                                color: show?failed?color_red:color_green:color_gray
                            }
                        }
                    }
                }
            }
            Rectangle{
                width: parent.width
                height: parent.height*0.6
                color: color_dark_navy
                Grid{
                    anchors.centerIn: parent
                    spacing: 5
                    rows: 4
                    columns: 3
                    Repeater{
                        model: ListModel{id: model_pad}
                        Rectangle{
                            width: 120
                            height: 80
                            color: "transparent"
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
                                    if(name==="clear"){
                                        50
                                    }else{
                                        45
                                    }
                                }
                                height: 50
                                sourceSize.width: width
                                sourceSize.height: height
                                visible:name==="clear"||name==="<-"
                                source:{
                                    if(name==="clear"){
                                        "icon/icon_trash.png"
                                    }else{
                                        "icon/icon_backspace.png"
                                    }
                                }
                                ColorOverlay{
                                    anchors.fill: parent
                                    color: "white"
                                    source: parent
                                    visible: name==="clear"
                                }
                            }
                            MouseArea{
                                anchors.fill: parent
                                onClicked: {
                                    supervisor.playSound('click');
                                    if(name==="clear"){
                                        popup_password.setfailclear();
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
                                        popup_password.setfailclear();
                                    }else{
                                        if(popup_password.is_editmode){
                                            popup_password.setfailclear();
                                            popup_password.answer += name;
                                            model_passwd.set(popup_password.input_len,{"show":true});
                                            popup_password.input_len++;
                                            if(popup_password.input_len === 4){
                                                supervisor.writelog("[SETTING] Change User : "+supervisor.getSetting("setting","UI","user_passwd")+" -> "+popup_password.answer)
                                                supervisor.setSetting("setting","UI/user_passwd",popup_password.answer);
                                                popup_password.edited();
                                            }
                                        }else{
                                            if(popup_password.input_len === 4){
                                                popup_password.setfailclear();
                                                popup_password.input_len = 0;
                                                model_passwd.set(0,{"show":false});
                                                model_passwd.set(1,{"show":false});
                                                model_passwd.set(2,{"show":false});
                                                model_passwd.set(3,{"show":false});
                                                popup_password.answer = "";
                                                popup_password.answer += name;
                                                model_passwd.set(popup_password.input_len,{"show":true});
                                                popup_password.input_len++;
                                            }else{
                                                popup_password.setfailclear();
                                                popup_password.answer += name;
                                                model_passwd.set(popup_password.input_len,{"show":true});
                                                popup_password.input_len++;
                                                if(popup_password.answer===popup_password.passwd){
                                                    supervisor.writelog("[USER INPUT] SETTING PAGE -> ADMIN LOGIN SUCCESS");
                                                    popup_password.login_rainbow();
                                                }else if(popup_password.answer===supervisor.getSetting("setting","UI","user_passwd")){
                                                    supervisor.writelog("[USER INPUT] SETTING PAGE -> ADMIN LOGIN SUCCESS");
                                                    popup_password.logined();
                                                }else if(popup_password.input_len === 4){
                                                    popup_password.setfailed();
                                                    popup_password.failed();
                                                    supervisor.writelog("[USER INPUT] SETTING PAGE -> ADMIN LOGIN FAILED "+popup_password.answer);
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

