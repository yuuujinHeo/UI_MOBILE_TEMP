import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtGraphicalEffects 1.0
import "."
import io.qt.Supervisor 1.0
import QtMultimedia 5.12

Item {
    id: page_log
    objectName: "page_log"
    width: 1280
    height: 800

    property date currentDate: new Date()
    property string today: ""
    property var year: 2023
    property var month: 40
    property var date: 24
    property string week: ""
    property var date_end: 30
    property var select_category: 1

    function init(){
        setdateToday(supervisor.isOdroid());
    }
    function setdateToday(is_odroid){
        today = currentDate.toLocaleDateString();
        var list = today.split(" ");
        var tempStr = "2023-04-11";
        model_date.clear();
        if(is_odroid){
            week = list[0].split(",")[0];
            date = list[1];
            if(list[2] === "January"){
                date = 1;
            }else if(list[2] === "February"){
                date = 2;
            }else if(list[2] === "March"){
                date = 3;
            }else if(list[2] === "April"){
                date = 4;
            }else if(list[2] === "May"){
                date = 5;
            }else if(list[2] === "June"){
                date = 6;
            }else if(list[2] === "July"){
                date = 7;
            }else if(list[2] === "August"){
                date = 8;
            }else if(list[2] === "September"){
                date = 9;
            }else if(list[2] === "October"){
                date = 10;
            }else if(list[2] === "November"){
                date = 11;
            }else if(list[2] === "December"){
                date = 12;
            }
            month = list[2];
            year = list[3];
            for(var i=1; i<date_end+1; i++){
                tempStr = year+"-0"+month+"-"+Number(i);
                var tempWeek = Date.fromLocaleString(Qt.locale(),tempStr,"yyyy-MM-dd").toLocaleDateString().split(" ")[3];
                model_date.append({"date":month+"월 "+Number(i)+"일 ("+tempWeek+")"});
            }
            date_list.currentIndex = parseInt(date);
        }else{
            year = list[0].split("년")[0];
            month = list[1].split("월")[0];
            date = list[2].split("일")[0];
            week = list[3];
            for(var i=1; i<date_end+1; i++){
                tempStr = year+"-0"+month+"-"+Number(i);
                print(i,tempStr);
                tempWeek = Date.fromLocaleString(Qt.locale(),tempStr,"yyyy-MM-dd").toLocaleDateString().split(" ")[3];
                model_date.append({"date":month+"월 "+Number(i)+"일 ("+tempWeek+")"});
            }
            date_list.currentIndex = parseInt(date);
        }
    }
    function setdate(new_date){
        model_date.clear();
        for(var i=1; i<date_end+1; i++){
            var tempStr = year+"-0"+month+"-"+Number(i);
            print(tempStr,Date.fromLocaleString(Qt.locale(),tempStr,"yyyy-MM-dd").toLocaleDateString())
            var tempWeek = Date.fromLocaleString(Qt.locale(),tempStr,"yyyy-MM-dd").toLocaleDateString().split(" ")[3];
            model_date.append({"date":month+"월 "+Number(i)+"일 ("+tempWeek+")"});
        }
        date_list.currentIndex = parseInt(date);
    }

    Rectangle{
        width: parent.width
        height: parent.height-statusbar.height
        anchors.bottom: parent.bottom
        color: "#f4f4f4"
        Rectangle{
            width: parent.width - 200
            height: parent.height
            color: "#f4f4f4"
            Row{
                id: rows_category
                spacing: 5
                Rectangle{
                    width: 250
                    height: 40
                    color: "#323744"
                    Text{
                        anchors.centerIn: parent
                        font.family: font_noto_r.name
                        color: "white"
                        text: "로그"
                        font.pixelSize: 20
                    }
                }
                Rectangle{
                    width: 240
                    height: 40
                    color: "#647087"
                    Text{
                        anchors.centerIn: parent
                        font.family: font_noto_r.name
                        color: "white"
                        text: "UI"
                        font.pixelSize: 20
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                           select_category = 1;
                        }
                    }
                    Rectangle{
                        width: parent.width
                        height: 7
                        visible: select_category==1?true:false
                        color: "#12d27c"
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.top: parent.bottom
                    }
                }
                Rectangle{
                    id: rect_category_2
                    width: 240
                    height: 40
                    color: "#647087"
                    Text{
                        anchors.centerIn: parent
                        font.family: font_noto_r.name
                        color: "white"
                        text: "SLAM"
                        font.pixelSize: 20
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                           select_category = 2;
                        }
                    }
                    Rectangle{
                        width: parent.width
                        height: 7
                        visible: select_category==2?true:false
                        color: "#12d27c"
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.top: parent.bottom
                    }
                }
            }
            SwipeView{
                id: date_list
                width: 300
                height: 40
                spacing: 30
                clip: false
                anchors.top: rows_category.bottom
                anchors.topMargin: 30
                onCurrentIndexChanged: {
                    if(currentIndex < 0)
                        currentIndex = 0;
                    else if(currentIndex > model_date.count-1){
                        currentIndex = model_date.count-1;
                    }
                }

                anchors.horizontalCenter: parent.horizontalCenter
                Repeater{
                    model : ListModel{id: model_date}
                    Rectangle{
                        width: 100
                        height: 40
                        color: "transparent"
                        Text{
                            text: date
                            font.family: font_noto_b.name
                            font.pixelSize: 30
                            anchors.centerIn: parent
                        }
                    }
                }
            }
            Image{
                source: "icon/joy_left.png"
                anchors.verticalCenter: date_list.verticalCenter
                anchors.right: date_list.left
                width: 12
                height: 20
                sourceSize.width: width
                sourceSize.height: height
                ColorOverlay{
                    source: parent
                    anchors.fill: parent
                    color: color_navy
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        date_list.currentIndex--;
                    }
                }
            }
            Image{
                source: "icon/joy_right.png"
                anchors.verticalCenter: date_list.verticalCenter
                anchors.left: date_list.right
                width: 12
                height: 20
                sourceSize.width: width
                sourceSize.height: height
                ColorOverlay{
                    source: parent
                    anchors.fill: parent
                    color: color_navy
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        date_list.currentIndex++;
                    }
                }
            }
            Rectangle{
                anchors.verticalCenter: date_list.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: 100
                width: 40
                height: 40
                radius: 5
                border.width: 1
                Image{
                    source: "icon/icon_transmit_server.png"
                    anchors.fill: parent
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked:{
                        popup_calendar.open();
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
            anchors.topMargin: 50
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
                    supervisor.writelog("[USER INPUT] LOG PAGE -> BACKPAGE");
                    backPage();
                }
            }
        }
    }

    Popup{
        id: popup_calendar
        anchors.centerIn: parent
        width: 500
        height: 500
        background: Rectangle{
            anchors.fill: parent
            color: "transparent"
        }

        Calendar{
            id: calendar
            anchors.fill: parent
            frameVisible: false
            weekNumbersVisible: false
            selectedDate: currentDate
            minimumDate: new Date(2023, 1, 1)
            maximumDate: new Date()
            onSelectedDateChanged: {

            }
        }
    }
}
