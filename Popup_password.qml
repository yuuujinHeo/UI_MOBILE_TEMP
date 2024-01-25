import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.0
import "."

Popup{
    id: popup_password
    anchors.centerIn: parent
    width: 360
    height: 550
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
                                click_sound.play();
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

