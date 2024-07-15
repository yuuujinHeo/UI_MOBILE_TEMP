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
    property int debug_count: 0
    property int select_version: -1

    property int category_font_size: 25
    property int group_font_size: 30
    property int name_font_size: 25
    property int info_font_size: 20

    property int caterogy_height: 45
    property int group_height: 60
    property int setting_height: 60

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
    }

    Component.onDestruction: {
        supervisor.stopBGM();
    }

    function setVoiceModel(){
        model_voice.clear();
        if(combo_voice_mode.currentIndex === 0){
            set_voice_name.visible = true;
            model_voice.append({"value":qsTr("어린이")});
            model_voice.append({"value":qsTr("여성")});
        }else if(combo_voice_mode.currentIndex === 1){
            if(combo_voice_language.currentIndex === 0){//한국어
                set_voice_name.visible = true;
                model_voice.append({"value":qsTr("여자어린이")});
                model_voice.append({"value":qsTr("여자성인")});
                model_voice.append({"value":qsTr("남자어린이")});
                model_voice.append({"value":qsTr("남자성인")});
                model_voice.append({"value":qsTr("남자성인2")});
                model_voice.append({"value":qsTr("할머니")});
                model_voice.append({"value":qsTr("할아버지")});
                model_voice.append({"value":qsTr("마녀")});
                model_voice.append({"value":qsTr("악마")});
            }else if(combo_voice_language.currentIndex === 1){//영어
                set_voice_name.visible = true;
                model_voice.append({"value":qsTr("여자어린이")});
                model_voice.append({"value":qsTr("여자성인")});
                model_voice.append({"value":qsTr("남자성인")});
            }else if(combo_voice_language.currentIndex === 2){//중국
                set_voice_name.visible = true;
                model_voice.append({"value":qsTr("여자성인")});
                model_voice.append({"value":qsTr("남자성인")});
            }else if(combo_voice_language.currentIndex === 3){//일본
                set_voice_name.visible = true;
                model_voice.append({"value":qsTr("여자어린이")});
                model_voice.append({"value":qsTr("여자성인")});
                model_voice.append({"value":qsTr("남자어린이")});
                model_voice.append({"value":qsTr("남자성인")});
            }else if(combo_voice_language.currentIndex === 4){//스페인
                set_voice_name.visible = true;
                model_voice.append({"value":qsTr("여자성인")});
                model_voice.append({"value":qsTr("남자성인")});
            }else{
                set_voice_name.visible = false;
            }
        }
    }

    function git_failed(){
        popup_loading.close();
        btn_gitreset.visible = true;
        popup_update.failed();
    }
    function git_newest(){
        popup_loading.close();
        btn_gitreset.visible = false;
        popup_update.newest();
    }
    function update_camera(){
        if(popup_camera.opened)
            popup_camera.update();
    }
    function setClear(name,state){
        popup_clear.addClearState(name,state);
    }

    function wifistatein(){
        popup_wifi.connection = supervisor.getWifiConnection(popup_wifi.select_ssd);
    }

    function wifi_set_success(){
        popup_wifi.set_success();
    }
    function wifi_set_failed(){
        popup_wifi.set_fail();
    }
    function wifi_con_failed(){
        popup_wifi.con_fail();
    }
    function wifi_con_success(){
        popup_wifi.con_success();
    }

    function set_category(num){
        select_category = num;
    }
    function set_call_done(){
        popup_change_call.close();
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

        if(combo_show_time.ischanged){
            if(combo_show_time.currentIndex == 0){
                supervisor.setSetting("setting","USE_UI/show_time","false");
            }else{
                supervisor.setSetting("setting","USE_UI/show_time","true");
            }
        }

        supervisor.setPreset(cur_preset);
        if(combo_language.ischanged){
            var str_lan;
            if(combo_language.currentIndex === 0){
                str_lan = "korean";

            }else if(combo_language.currentIndex === 1){
                str_lan = "english";
            }
            supervisor.setSetting("setting","UI/language",str_lan);
            supervisor.setlanguage(str_lan);
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

        if(combo_use_dcrelay.ischanged){
            if(combo_use_dcrelay.currentIndex == 1){
                supervisor.setSetting("setting","USE_UI/use_goqual","true");
            }else{
                supervisor.setSetting("setting","USE_UI/use_goqual","false");
            }
        }

        if(tfield_goqual_id.ischanged){
            supervisor.setSetting("setting","GOQUAL/user_id",tfield_goqual_id.text);
        }
        if(tfield_goqual_passwd.ischanged){
            supervisor.setSetting("setting","GOQUAL/user_passwd",tfield_goqual_passwd.text);
        }

        if(combo_tray_num.ischanged){
            supervisor.setSetting("setting","ROBOT_TYPE/tray_num",combo_tray_num.currentText);
        }

        if(combo_use_lingbell.ischanged){
            if(combo_use_lingbell.currentIndex === 1){
                supervisor.setSetting("setting","CALL/use_lingbell","true");
            }else{
                supervisor.setSetting("setting","CALL/use_lingbell","false");
            }
        }
        // if(combo_use_lingbell_repeat.ischanged){
        //     if(combo_use_lingbell_repeat.currentIndex === 1){
        //         supervisor.setSetting("setting","CALL/use_lingbell_repeat","true");
        //     }else{
        //         supervisor.setSetting("setting","CALL/use_lingbell_repeat","false");
        //     }
        // }
        if(combo_lingbell_time.ischanged){
            supervisor.setSetting("setting","CALL/lingbell_time",combo_lingbell_time.currentText);
        }

        if(slider_volume_bgm.ischanged){
            supervisor.setSetting("setting","UI/volume_bgm",slider_volume_bgm.value);
//            volume_bgm = slider_volume_bgm.value.toFixed(0);
        }

        if(slider_volume_voice.ischanged){
            supervisor.setSetting("setting","UI/volume_voice",slider_volume_voice.value);
//            volume_voice = slider_volume_voice.value.toFixed(0);
        }

        if(slider_volume_button.ischanged){
            supervisor.setSetting("setting","UI/volume_button",slider_volume_button.value);
        }

        if(combo_movingpage.ischanged){
            supervisor.setSetting("setting","UI/moving_face",Number(combo_movingpage.currentIndex));
            combo_movingpage.ischanged = false;
        }

        if(combo_patrolpage.ischanged){
            supervisor.setSetting("setting","UI/patrol_face",combo_patrolpage.currentIndex);
        }

        if(combo_comeback_preset.ischanged){
            supervisor.setSetting("update","DRIVING/comeback_preset",combo_comeback_preset.currentIndex.toString());
        }


        if(combo_use_tray.ischanged){
            if(combo_use_tray.currentIndex == 0)
                supervisor.setSetting("setting","USE_UI/use_tray","false");
            else
                supervisor.setSetting("setting","USE_UI/use_tray","true");
        }

        if(combo_use_calling_notice.ischanged){
            if(combo_use_calling_notice.currentIndex == 0){
                supervisor.setSetting("setting","USE_UI/use_calling_notice","false");
            }else{
                supervisor.setSetting("setting","USE_UI/use_calling_notice","true");
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



        //OBSTACLE
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
        //if(obs_near.ischanged){ //BJ
        //    supervisor.setSetting("setting","OBSTACLE/obs_near",obs_near.text);
        //}
        //if(obs_decel_gain.ischanged){
        //    supervisor.setSetting("setting","OBSTACLE/obs_decel_gain",obs_decel_gain.text);
        //}
        if(obs_early_stop_dist.ischanged){
            supervisor.setSetting("setting","OBSTACLE/obs_early_stop_dist",obs_early_stop_dist.text);
        }
        if(obs_detect_area.ischanged){
            supervisor.setSetting("setting","OBSTACLE/obs_detect_area",obs_detect_area.text);
        }
        if(obs_detect_sensitivity.ischanged){
            supervisor.setSetting("setting","OBSTACLE/obs_detect_sensitivity",obs_detect_sensitivity.text);
        }
        if(obs_preview_time.ischanged){
            supervisor.setSetting("setting","OBSTACLE/obs_preview_time",obs_preview_time.text);
        }
        if(obs_deadzone.ischanged){
            supervisor.setSetting("setting","OBSTACLE/obs_deadzone",obs_deadzone.text);
        }
        if(obs_wait_time.ischanged){
            supervisor.setSetting("setting","OBSTACLE/obs_wait_time",obs_wait_time.text);
        }
        //if(obs_check_range.ischanged){ //BJ
        //    supervisor.setSetting("setting","OBSTACLE/obs_check_range",obs_check_range.text);
        //}
        if(max_range.ischanged){
            supervisor.setSetting("setting","SENSOR/max_range",max_range.text);
        }

        if(cam_exposure.ischanged){
            supervisor.setSetting("setting","SENSOR/cam_exposure",cam_exposure.text);
        }

        if(combo_auto_update.ischanged){
            if(combo_auto_update.currentIndex === 0){
                supervisor.setSetting("setting","USE_UI/auto_update",false);
            }else{
                supervisor.setSetting("setting","USE_UI/auto_update",true);
            }
        }


        //USE_SLAM
        //if(combo_use_avoid.ischanged){ //BJ
        //    if(combo_use_avoid.currentIndex == 0){
        //        supervisor.setSetting("setting","USE_SLAM/use_avoid",false);
        //    }else{
        //        supervisor.setSetting("setting","USE_SLAM/use_avoid",true);
        //    }
        //}
        if(combo_use_earlystop_serving.ischanged){
            if(combo_use_earlystop_serving.currentIndex == 0){
                supervisor.setSetting("setting","USE_SLAM/use_earlystop_serving",false);
            }else{
                supervisor.setSetting("setting","USE_SLAM/use_earlystop_serving",true);
            }
        }
        if(combo_multirobot.ischanged){
            if(combo_multirobot.currentIndex == 0){
                supervisor.setSetting("setting","USE_SLAM/use_multirobot","false");
            }else{
                supervisor.setSetting("setting","USE_SLAM/use_multirobot","true");
            }
        }
        if(combo_use_earlystop_resting.ischanged){
            if(combo_use_earlystop_resting.currentIndex == 0){
                supervisor.setSetting("setting","USE_SLAM/use_earlystop_resting",false);
            }else{
                supervisor.setSetting("setting","USE_SLAM/use_earlystop_resting",true);
            }
        }

        //if(combo_use_obs_near.ischanged){ //BJ
        //    if(combo_use_obs_near.currentIndex == 0){
        //        supervisor.setSetting("setting","USE_SLAM/use_obs_near",false);
        //    }else{
        //        supervisor.setSetting("setting","USE_SLAM/use_obs_near",true);
        //    }
        //}

        if(combo_use_obs_preview.ischanged){
            if(combo_use_obs_preview.currentIndex == 0){
                supervisor.setSetting("setting","USE_SLAM/use_obs_preview",false);
            }else{
                supervisor.setSetting("setting","USE_SLAM/use_obs_preview",true);
            }
        }
        //if(combo_use_pivot_obs.ischanged){ //BJ
        //    if(combo_use_pivot_obs.currentIndex == 0){
        //        supervisor.setSetting("setting","USE_SLAM/use_pivot_obs",false);
        //    }else{
        //        supervisor.setSetting("setting","USE_SLAM/use_pivot_obs",true);
        //    }
        //}
        if(combo_use_ignore_safetyzone_return.ischanged){
            if(combo_use_ignore_safetyzone_return.currentIndex == 0){
                supervisor.setSetting("setting","USE_SLAM/use_ignore_safetyzone_return",false);
            }else{
                supervisor.setSetting("setting","USE_SLAM/use_ignore_safetyzone_return",true);
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
        //if(path_shifting_val.ischanged){ //BJ
        //    supervisor.setSetting("update","DRIVING/path_shifting_val",path_shifting_val.text);
        //}
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

        if(combo_voice_mode.ischanged){
            print("voice mode : ",combo_voice_mode.currentIndex, combo_voice_name.currentIndex)
            if(combo_voice_mode.currentIndex == 0){

                supervisor.setTTSMode("basic");
                supervisor.setTTSVoice(0,combo_voice_name.currentIndex);
            }else{
                supervisor.setTTSMode("tts");
                supervisor.setTTSVoice(combo_voice_language.currentIndex, combo_voice_name.currentIndex);
            }
        }

        if(combo_voice_name.ischanged){
            if(combo_voice_mode.currentIndex == 0){
                supervisor.setTTSMode("basic");
                supervisor.setTTSVoice(0,combo_voice_name.currentIndex);
            }else{
                supervisor.setTTSMode("tts");
                supervisor.setTTSVoice(combo_voice_language.currentIndex, combo_voice_name.currentIndex);
            }
        }


        if(combo_use_motorcurrent.ischanged){
            if(combo_use_motorcurrent.currentIndex == 0){
                supervisor.setSetting("setting","USE_UI/use_current_pause","false");
            }else{
                supervisor.setSetting("setting","USE_UI/use_current_pause","true");
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

        cur_preset = parseInt(supervisor.getSetting("update","DRIVING","cur_preset"));
        combo_comeback_preset.currentIndex = parseInt(supervisor.getSetting("update","DRIVING","comeback_preset"));
        print("setting init ",cur_preset, combo_comeback_preset.currentIndex);
        slider_volume_system.value = supervisor.getSystemVolume();
        platform_name.text = supervisor.getSetting("setting","ROBOT_TYPE","model");
        combo_platform_serial.currentIndex = parseInt(supervisor.getSetting("setting","ROBOT_TYPE","serial_num"))
        radius.text = supervisor.getSetting("static","ROBOT_HW","robot_radius");
        combo_tray_num.currentIndex = supervisor.getSetting("setting","ROBOT_TYPE","tray_num")-1;

        if(supervisor.getSetting("setting","SERVER","use_server_call")==="true"){
            combo_server_calling.currentIndex = 1;
        }else{
            combo_server_calling.currentIndex = 0;
        }

        if(supervisor.getSetting("setting","UI","language") === "korean"){
            combo_language.currentIndex = 0;
        }else if(supervisor.getSetting("setting","UI","language") === "english"){
            combo_language.currentIndex = 1;
        }

        if(supervisor.getSetting("setting","CALL","use_lingbell") === "true"){
            combo_use_lingbell.currentIndex = 1;
        }else{
            combo_use_lingbell.currentIndex = 0;
        }
        if(supervisor.getSetting("setting","USE_UI","show_time") === "true"){
            combo_show_time.currentIndex = 1;
        }else{
            combo_show_time.currentIndex = 0;
        }


        // if(supervisor.getSetting("setting","CALL","use_lingbell_repeat") === "true"){
        //     combo_use_lingbell_repeat.currentIndex = 1;
        // }else{
        //     combo_use_lingbell_repeat.currentIndex = 0;
        // }


        if(supervisor.getSetting("setting","USE_UI","use_goqual") === "true"){
            combo_use_dcrelay.currentIndex = 1;
        }else{
            combo_use_dcrelay.currentIndex = 0;
        }

        tfield_goqual_id.text = supervisor.getSetting("setting","GOQUAL","user_id");
        tfield_goqual_passwd.text = supervisor.getSetting("setting","GOQUAL","user_passwd");



        if(supervisor.getSetting("setting","CALL","lingbell_time") === "3"){
            combo_lingbell_time.currentIndex = 0;
        }else if(supervisor.getSetting("setting","CALL","lingbell_time") === "4"){
            combo_lingbell_time.currentIndex = 1;
        }else if(supervisor.getSetting("setting","CALL","lingbell_time") === "5"){
            combo_lingbell_time.currentIndex = 2;
        }else if(supervisor.getSetting("setting","CALL","lingbell_time") === "6"){
            combo_lingbell_time.currentIndex = 3;
        }else if(supervisor.getSetting("setting","CALL","lingbell_time") === "7"){
            combo_lingbell_time.currentIndex = 4;
        }else if(supervisor.getSetting("setting","CALL","lingbell_time") === "8"){
            combo_lingbell_time.currentIndex = 5;
        }else if(supervisor.getSetting("setting","CALL","lingbell_time") === "9"){
            combo_lingbell_time.currentIndex = 6;
        }else if(supervisor.getSetting("setting","CALL","lingbell_time") === "10"){
            combo_lingbell_time.currentIndex = 7;
        }else if(supervisor.getSetting("setting","CALL","lingbell_time") === "15"){
            combo_lingbell_time.currentIndex = 8;
        }else if(supervisor.getSetting("setting","CALL","lingbell_time") === "20"){
            combo_lingbell_time.currentIndex = 9;
        }else{
            combo_lingbell_time.currentIndex = 2;
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
        //path_shifting_val.text = supervisor.getSetting("update","DRIVING","path_shifting_val"); //BJ


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



        //USE_SLAM
        if(supervisor.getSetting("setting","USE_SLAM","use_obs_preview") === "true"){
            combo_use_obs_preview.currentIndex = 1;
        }else{
            combo_use_obs_preview.currentIndex = 0;
        }
            //BJ
        //if(supervisor.getSetting("setting","USE_SLAM","use_avoid") === "true"){
        //    combo_use_avoid.currentIndex = 1;
        //}else{
        //    combo_use_avoid.currentIndex = 0;
        //}
        //if(supervisor.getSetting("setting","USE_SLAM","use_pivot_obs") === "true"){
        //    combo_use_pivot_obs.currentIndex = 1;
        //}else{
        //    combo_use_pivot_obs.currentIndex = 0;
        //} //BJ
        if(supervisor.getSetting("setting","USE_SLAM","use_multirobot")==="true"){
            combo_multirobot.currentIndex = 1;
        }else{
            combo_multirobot.currentIndex = 0;
        }
        if(supervisor.getSetting("setting","USE_SLAM","use_ignore_safetyzone_return") === "true"){
            combo_use_ignore_safetyzone_return.currentIndex = 1;
        }else{
            combo_use_ignore_safetyzone_return.currentIndex = 0;
        }
            //BJ
        //if(supervisor.getSetting("setting","USE_SLAM","use_obs_near") === "true"){ // 제자리 회전 감지
        //    combo_use_obs_near.currentIndex = 1;
        //}else{
        //    combo_use_obs_near.currentIndex = 0;
        //}
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

        combo_movingpage.currentIndex = parseInt(supervisor.getSetting("setting","UI","moving_face"));


        combo_patrolpage.currentIndex = parseInt(supervisor.getSetting("setting","UI","patrol_face"));




        print(supervisor.getSetting("setting","UI","voice_mode"),supervisor.getSetting("setting","UI","voice_language"),supervisor.getSetting("setting","UI","voice_name"))
        print(supervisor.getTTSLanguageNum(),supervisor.getTTSNameNum())
        if(supervisor.getSetting("setting","UI","voice_mode") === "tts"){
            combo_voice_mode.currentIndex = 1;
        }else{
            combo_voice_mode.currentIndex = 0;
        }
        combo_voice_language.currentIndex = supervisor.getTTSLanguageNum();
        setVoiceModel();
        combo_voice_name.currentIndex = supervisor.getTTSNameNum();
        combo_voice_name_2.currentIndex = supervisor.getTTSNameNum();


        if(supervisor.getSetting("setting","USE_UI","use_tray") === "true"){
            combo_use_tray.currentIndex = 1;
        }else{
            combo_use_tray.currentIndex = 0;
        }

        if(supervisor.getSetting("setting","USE_UI","use_calling_notice") === "true"){
            combo_use_calling_notice.currentIndex = 1;
        }else{
            combo_use_calling_notice.currentIndex = 0;
        }
        if(supervisor.getSetting("setting","USE_UI","use_restinglock") === "true"){
            combo_resting_lock.currentIndex = 1;
        }else{
            combo_resting_lock.currentIndex = 0;
        }


        //OBSTACLE
        //obs_check_range.text = supervisor.getSetting("setting","OBSTACLE","obs_check_range"); //BJ
        obs_preview_time.text = supervisor.getSetting("setting","OBSTACLE","obs_preview_time");
        obs_wait_time.text = supervisor.getSetting("setting","OBSTACLE","obs_wait_time");
        obs_height_max.text = supervisor.getSetting("setting","OBSTACLE","obs_height_max");
        obs_early_stop_dist.text = supervisor.getSetting("setting","OBSTACLE","obs_early_stop_dist");
        //obs_near.text = supervisor.getSetting("setting","OBSTACLE","obs_near"); //BJ
        obs_margin1.text = supervisor.getSetting("setting","OBSTACLE","obs_margin1");
        obs_margin0.text = supervisor.getSetting("setting","OBSTACLE","obs_margin0");
        obs_detect_area.text = supervisor.getSetting("setting","OBSTACLE","obs_detect_area");
        obs_detect_sensitivity.text = supervisor.getSetting("setting","OBSTACLE","obs_detect_sensitivity");
        obs_height_min.text = supervisor.getSetting("setting","OBSTACLE","obs_height_min");
        //obs_decel_gain.text = supervisor.getSetting("setting","OBSTACLE","obs_decel_gain"); //BJ

        tfield_gitbranch.text = supervisor.getSetting("setting","UI","program_branch");

        max_range.text = supervisor.getSetting("setting","SENSOR","max_range");
        right_camera.text = supervisor.getSetting("static","SENSOR","right_camera_serial");
        left_camera.text = supervisor.getSetting("static","SENSOR","left_camera_serial");

        var ip = supervisor.getcurIP().split(".");
        if(ip.length >3){
            ip_1.text = ip[0];
            ip_2.text = ip[1];
            ip_3.text = ip[2];
            ip_4.text = ip[3];
        }
        var netmask = supervisor.getcurNetmask().split(".");
        if(netmask.length >3){
            netmask_1.text = netmask[0];
            netmask_2.text = netmask[1];
            netmask_3.text = netmask[2];
            netmask_4.text = netmask[3];
        }else{
            netmask_1.text = "";
            netmask_2.text = "";
            netmask_3.text = "";
            netmask_4.text = "";
        }
        var gateway = supervisor.getcurGateway().split(".");
        if(gateway.length >3){
            gateway_1.text = gateway[0];
            gateway_2.text = gateway[1];
            gateway_3.text = gateway[2];
            gateway_4.text = gateway[3];
        }else{
            gateway_1.text = "";
            gateway_2.text = "";
            gateway_3.text = "";
            gateway_4.text = "";
        }
        var dns1 = supervisor.getcurDNS().split(".");
        if(dns1.length >3){
            dnsmain_1.text = dns1[0];
            dnsmain_2.text = dns1[1];
            dnsmain_3.text = dns1[2];
            dnsmain_4.text = dns1[3];
        }else{
            dnsmain_1.text = "";
            dnsmain_2.text = "";
            dnsmain_3.text = "";
            dnsmain_4.text = "";
        }
        var dns2 = supervisor.getcurDNS2().split(".");
        if(dns2.length >3){
            dnsserv_1.text = dns2[0];
            dnsserv_2.text = dns2[1];
            dnsserv_3.text = dns2[2];
            dnsserv_4.text = dns2[3];
        }else{
            dnsserv_1.text = "";
            dnsserv_2.text = "";
            dnsserv_3.text = "";
            dnsserv_4.text = "";
        }
        ip_1.ischanged = false;
        ip_2.ischanged = false;
        ip_3.ischanged = false;
        ip_4.ischanged = false;
        netmask_1.ischanged = false;
        netmask_2.ischanged = false;
        netmask_3.ischanged = false;
        netmask_4.ischanged = false;
        gateway_1.ischanged = false;
        gateway_2.ischanged = false;
        gateway_3.ischanged = false;
        gateway_4.ischanged = false;
        dnsmain_1.ischanged = false;
        dnsmain_2.ischanged = false;
        dnsmain_3.ischanged = false;
        dnsmain_4.ischanged = false;
        dnsserv_1.ischanged = false;
        dnsserv_2.ischanged = false;
        dnsserv_3.ischanged = false;
        dnsserv_4.ischanged = false;

        var eip = supervisor.getethernetIP().split(".");
        if(eip.length >3){
            ethernet_ip_1.text = eip[0];
            ethernet_ip_2.text = eip[1];
            ethernet_ip_3.text = eip[2];
            ethernet_ip_4.text = eip[3];
        }
        var ethernet_netmask = supervisor.getethernetNetmask().split(".");
        if(ethernet_netmask.length >3){
            ethernet_netmask_1.text = ethernet_netmask[0];
            ethernet_netmask_2.text = ethernet_netmask[1];
            ethernet_netmask_3.text = ethernet_netmask[2];
            ethernet_netmask_4.text = ethernet_netmask[3];
        }else{
            ethernet_netmask_1.text = "";
            ethernet_netmask_2.text = "";
            ethernet_netmask_3.text = "";
            ethernet_netmask_4.text = "";
        }
        var ethernet_gateway = supervisor.getethernetGateway().split(".");
        if(ethernet_gateway.length >3){
            ethernet_gateway_1.text = ethernet_gateway[0];
            ethernet_gateway_2.text = ethernet_gateway[1];
            ethernet_gateway_3.text = ethernet_gateway[2];
            ethernet_gateway_4.text = ethernet_gateway[3];
        }else{
            ethernet_gateway_1.text = "";
            ethernet_gateway_2.text = "";
            ethernet_gateway_3.text = "";
            ethernet_gateway_4.text = "";
        }
        var ethernet_dns1 = supervisor.getethernetDNS().split(".");
        if(ethernet_dns1.length >3){
            ethernet_dnsmain_1.text = ethernet_dns1[0];
            ethernet_dnsmain_2.text = ethernet_dns1[1];
            ethernet_dnsmain_3.text = ethernet_dns1[2];
            ethernet_dnsmain_4.text = ethernet_dns1[3];
        }else{
            ethernet_dnsmain_1.text = "";
            ethernet_dnsmain_2.text = "";
            ethernet_dnsmain_3.text = "";
            ethernet_dnsmain_4.text = "";
        }
        var ethernet_dns2 = supervisor.getethernetDNS2().split(".");
        if(ethernet_dns2.length >3){
            ethernet_dnsserv_1.text = ethernet_dns2[0];
            ethernet_dnsserv_2.text = ethernet_dns2[1];
            ethernet_dnsserv_3.text = ethernet_dns2[2];
            ethernet_dnsserv_4.text = ethernet_dns2[3];
        }else{
            ethernet_dnsserv_1.text = "";
            ethernet_dnsserv_2.text = "";
            ethernet_dnsserv_3.text = "";
            ethernet_dnsserv_4.text = "";
        }
        ethernet_ip_1.ischanged = false;
        ethernet_ip_2.ischanged = false;
        ethernet_ip_3.ischanged = false;
        ethernet_ip_4.ischanged = false;
        ethernet_netmask_1.ischanged = false;
        ethernet_netmask_2.ischanged = false;
        ethernet_netmask_3.ischanged = false;
        ethernet_netmask_4.ischanged = false;
        ethernet_gateway_1.ischanged = false;
        ethernet_gateway_2.ischanged = false;
        ethernet_gateway_3.ischanged = false;
        ethernet_gateway_4.ischanged = false;
        ethernet_dnsmain_1.ischanged = false;
        ethernet_dnsmain_2.ischanged = false;
        ethernet_dnsmain_3.ischanged = false;
        ethernet_dnsmain_4.ischanged = false;
        ethernet_dnsserv_1.ischanged = false;
        ethernet_dnsserv_2.ischanged = false;
        ethernet_dnsserv_3.ischanged = false;
        ethernet_dnsserv_4.ischanged = false;


        ip = supervisor.getSetting("setting","SERVER","fms_ip").split(".");
        if(ip.length >3){
            server_ip_1.text = ip[0];
            server_ip_2.text = ip[1];
            server_ip_3.text = ip[2];
            server_ip_4.text = ip[3];
        }
        server_ip_1.ischanged = false;
        server_ip_2.ischanged = false;
        server_ip_3.ischanged = false;
        server_ip_4.ischanged = false;


        //변수 초기화
        platform_name.ischanged = false;
        combo_platform_serial.ischanged = false;
        combo_voice_name.ischanged = false;
        combo_platform_type.ischanged = false;
        combo_tray_num.ischanged = false;
        combo_voice_language.ischanged = false;


//        slider_vxy.ischanged = false;
        slider_volume_bgm.ischanged = false;
        slider_volume_voice.ischanged = false;
        slider_volume_button.ischanged = false;

        combo_language.ischanged = false;
        combo_movingpage.ischanged = false;
        combo_patrolpage.ischanged = false;
        combo_comeback_preset.ischanged = false;


        combo_multirobot.ischanged = false;
        combo_server_calling.ischanged = false;
        fms_id.ischanged = false;
        fms_pw.ischanged = false;

        wheel_base.ischanged = false;
        wheel_radius.ischanged = false;
        radius.ischanged = false;


        max_range.ischanged = false;
        cam_exposure.ischanged = false;

        st_v.ischanged = false;

        obs_preview_time.ischanged = false;
        //combo_use_obs_near.ischanged = false; //BJ
        combo_use_earlystop_resting.ischanged = false;
        combo_use_earlystop_serving.ischanged = false;
        //combo_use_avoid.ischanged = false; //BJ
        combo_use_obs_preview.ischanged = false;
        //combo_use_pivot_obs.ischanged = false; //BJ


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
        //path_shifting_val.ischanged = false; //BJ

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


        tfield_gitbranch.ischanged = false;
        //OBSTACLE
        //obs_check_range.ischanged = false; //BJ
        obs_deadzone.ischanged = false;
        obs_preview_time.ischanged = false;
        obs_wait_time.ischanged = false;
        obs_height_max.ischanged = false;
        obs_height_min.ischanged = false;
        //obs_decel_gain.ischanged = false; //BJ
        obs_margin1.ischanged = false;
        obs_margin0.ischanged = false;
        //obs_near.ischanged = false; //BJ
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
        //if(path_shifting_val.ischanged) is_changed = true; //BJ
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
    Rectangle{ // 카테고리 바 :설정, 현재 상태, 로봇, 주행, 인식
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
                height: caterogy_height
                color: "#323744"
                Text{
                    anchors.centerIn: parent
                    font.family: font_noto_r.name
                    color: "white"
                    text: qsTr("설정")
                    font.pixelSize: category_font_size
                }
                MouseArea{
                    anchors.fill: parent
                    onDoubleClicked:{
                        supervisor.playSound('click', slider_volume_button.value);
                        popup_password.open();
                    }
                }
            }
            Rectangle{
                id: rect_category_1
                width: 240
                height: caterogy_height
                color: "#647087"
                Text{
                    anchors.centerIn: parent
                    font.family: font_noto_r.name
                    color: "white"
                    text: qsTr("현재상태")
                    font.pixelSize: category_font_size
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                       supervisor.playSound('click', slider_volume_button.value);
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
                height: caterogy_height
                color: "#647087"
                Text{
                    anchors.centerIn: parent
                    font.family: font_noto_r.name
                    color: "white"
                    text: qsTr("로봇")
                    font.pixelSize: category_font_size
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        supervisor.playSound('click', slider_volume_button.value);
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
                height: caterogy_height
                visible: is_rainbow
                color: "#647087"
                Text{
                    anchors.centerIn: parent
                    font.family: font_noto_r.name
                    color: "white"
                    text: qsTr("주행")
                    font.pixelSize: category_font_size
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        supervisor.playSound('click', slider_volume_button.value);
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
                height: caterogy_height
                color: "#647087"
                visible: is_admin || is_rainbow
                Text{
                    anchors.centerIn: parent
                    font.family: font_noto_r.name
                    color: "white"
                    text: qsTr("인식")
                    font.pixelSize: category_font_size
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        supervisor.playSound('click', slider_volume_button.value);
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
                    height: group_height
                    color: "black"
                    anchors.horizontalCenter: parent.horizontalCenter
                    Text{
                        anchors.centerIn: parent
                        font.family: font_noto_b.name
                        text:qsTr("로봇 기본 정보")
                        color: "white"
                        font.pixelSize: group_font_size
                    }
                }
                Rectangle{
                    id: set_robot_1
                    width: 840
                    height: setting_height
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
                                text:qsTr("플랫폼 이름 (영문)")
                                font.pixelSize: name_font_size
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
                                id: platform_name
                                anchors.fill: parent
                                horizontalAlignment: TextField.AlignHCenter
                                text:supervisor.getSetting("setting","ROBOT_TYPE","model");
                                property bool ischanged: false
                                onTextChanged: {
                                    ischanged = true;
                                }
                                font.pixelSize: info_font_size
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        supervisor.playSound('click', slider_volume_button.value);
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
                    height: setting_height
                    visible: false//use_multirobot
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
                                text:qsTr("플랫폼 넘버 (중복주의)")
                                font.pixelSize: name_font_size
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
                                text:qsTr("?")
                                onClicked:{
                                    popup_help_setting.open();
                                    popup_help_setting.setTitle(qsTr("플랫폼 넘버"));
                                    popup_help_setting.addLine(qsTr("동일한 이름으로 설정된 로봇을 여러대 구동할 때 구분용으로 사용됩니다"));
                                    popup_help_setting.addLine(qsTr("중복에 유의하여 설정해주세요"));
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
                    height: setting_height
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
                                text:qsTr("플랫폼 타입")
                                font.pixelSize: name_font_size
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
                                id: combo_platform_type
                                anchors.fill: parent
                                property bool ischanged: false
                                onCurrentIndexChanged: {
                                    ischanged = true;
                                }
                                font.pixelSize: info_font_size
                                model:[qsTr("서빙용"),qsTr("호출용"),qsTr("서빙+호출용"), qsTr("퇴식전용")]
                            }
                        }
                    }
                }

                Rectangle{
                    width: 1100
                    height: group_height
                    color: "black"
                    visible: false
                    anchors.horizontalCenter: parent.horizontalCenter
                    Text{
                        anchors.centerIn: parent
                        font.family: font_noto_b.name
                        text:qsTr("알림벨 설정")
                        color: "white"
                        font.pixelSize: group_font_size
                    }
                }
                Rectangle{
                    id: use_lingbell
                    width: 840
                    height: setting_height
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
                                text:qsTr("알림벨 사용")
                                font.pixelSize: name_font_size
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                    anchors.leftMargin = 30 - width*(1-scale)/2
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
                                anchors.fill: parent
                                ComboBox{
                                    id: combo_use_lingbell
                                    width: parent.width
                                    height: parent.height
                                    property bool ischanged: false
                                    onCurrentIndexChanged: {
                                        ischanged = true;
                                    }
                                    font.pixelSize: info_font_size
                                    model:[qsTr("사용안함"), qsTr("사용")]
                                }
                            }
                        }
                    }
                }
                Rectangle{
                    id: lingbell_time
                    width: 840
                    height: setting_height
                    visible: false
                    // visible: combo_use_lingbell.currentIndex === 1 && combo_use_lingbell_repeat.currentIndex === 1
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
                                text:qsTr("반복 주기 [초]")
                                font.pixelSize: name_font_size
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                    anchors.leftMargin = 30 - width*(1-scale)/2
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
                                anchors.fill: parent
                                ComboBox{
                                    font.pixelSize: info_font_size
                                    id: combo_lingbell_time
                                    width: parent.width
                                    height: parent.height
                                    property bool ischanged: false
                                    onCurrentIndexChanged: {
                                        ischanged = true;
                                    }
                                    model:[3,4,5,6,7,8,9,10,15,20]
                                }
                            }
                        }
                    }
                }

                Rectangle{
                    width: 1100
                    height: group_height
                    color: "black"
                    anchors.horizontalCenter: parent.horizontalCenter
                    Text{
                        anchors.centerIn: parent
                        font.family: font_noto_b.name
                        text:qsTr("스마트릴레이 설정")
                        color: "white"
                        font.pixelSize: group_font_size
                    }
                }
                Rectangle{
                    id: use_dcrelay
                    width: 840
                    height: setting_height
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
                                text:qsTr("스마트릴레이 사용")
                                font.pixelSize: name_font_size
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                    anchors.leftMargin = 30 - width*(1-scale)/2
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
                                anchors.fill: parent
                                ComboBox{
                                    id: combo_use_dcrelay
                                    width: parent.width
                                    height: parent.height
                                    font.pixelSize: info_font_size
                                    property bool ischanged: false
                                    onCurrentIndexChanged: {
                                        ischanged = true;
                                    }
                                    model:[qsTr("사용안함"), qsTr("사용")]
                                }
                            }
                        }
                    }
                }
                Rectangle{
                    id: goqual_state
                    width: 840
                    height: setting_height
                    visible: combo_use_dcrelay.currentIndex === 1
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
                                text:qsTr("연동 상태")
                                font.pixelSize: name_font_size
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                    anchors.leftMargin = 30 - width*(1-scale)/2
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
                                anchors.fill: parent
                                Rectangle{
                                    width: parent.width - 150
                                    height: parent.height
                                    color: "transparent"
                                    Text{
                                        anchors.verticalCenter: parent.verticalCenter
                                        anchors.left: parent.left
                                        anchors.leftMargin: 30
                                        font.pixelSize: info_font_size
                                        text: qsTr("연동된 디바이스")
                                    }
                                }

                                Item_buttons{
                                    type: "white_btn"
                                    width: 150
                                    height: setting_height
                                    text: qsTr("설정")
                                    onClicked:{
                                        supervisor.playSound('click', slider_volume_button.value);
                                        popup_set_goqual.open();
                                    }
                                }
                            }
                        }
                    }
                }

                Rectangle{
                    id: goqual_id
                    width: 840
                    height: setting_height
                    visible: combo_use_dcrelay.currentIndex === 1
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
                                text:qsTr("ID")
                                font.pixelSize: name_font_size
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                    anchors.leftMargin = 30 - width*(1-scale)/2
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
                                anchors.fill: parent
                                TextField{
                                    id: tfield_goqual_id
                                    width: parent.width
                                    height: parent.height
                                    property bool ischanged: false
                                    font.pixelSize: info_font_size
                                    text:"master"
                                    onTextChanged: {
                                        ischanged = true;
                                    }
                                }
                            }
                        }
                    }
                }
                Rectangle{
                    id: goqual_passwd
                    width: 840
                    height: setting_height
                    visible: combo_use_dcrelay.currentIndex === 1
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
                                text:qsTr("PASSWD")
                                font.pixelSize: name_font_size
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                    anchors.leftMargin = 30 - width*(1-scale)/2
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
                                anchors.fill: parent
                                TextField{
                                    id: tfield_goqual_passwd
                                    width: parent.width
                                    height: parent.height
                                    property bool ischanged: false
                                    font.pixelSize: info_font_size
                                    text:"master"
                                    onTextChanged: {
                                        ischanged = true;
                                    }
                                }
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
                        text:qsTr("기능 설정")
                        color: "white"
                        font.pixelSize: group_font_size
                    }
                }
                Rectangle{
                    id: set_preset
                    width: 840
                    height: setting_height
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
                                text:qsTr("이동 속도")
                                font.pixelSize: name_font_size
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
                                anchors.centerIn: parent
                                spacing: 5
                                Rectangle{
                                    width:70
                                    height: setting_height
                                    anchors.verticalCenter: parent.verticalCenter
                                    radius: 5
                                    Text{
                                        id: text_preset_name_1
                                        anchors.centerIn: parent
                                        text:qsTr("preset 1")
                                        font.family: font_noto_r.name
                                        font.pixelSize: 15
                                        color: cur_preset===1?color_green:color_mid_black
                                    }
                                    MouseArea{
                                        anchors.fill: parent
                                        onClicked:{
                                            supervisor.playSound('click', slider_volume_button.value);
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
                                    height: setting_height
                                    anchors.verticalCenter: parent.verticalCenter
                                    radius: 5
                                    Text{
                                        id: text_preset_name_2
                                        anchors.centerIn: parent
                                        text:qsTr("preset 2")
                                        font.family: font_noto_r.name
                                        font.pixelSize: 15
                                        color: cur_preset===2?color_green:color_mid_black
                                    }
                                    MouseArea{
                                        anchors.fill: parent
                                        onClicked:{
                                            supervisor.playSound('click', slider_volume_button.value);
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
                                        text:qsTr("preset 3")
                                        font.family: font_noto_r.name
                                        font.pixelSize: 15
                                        color: cur_preset===3?color_green:color_mid_black
                                    }
                                    MouseArea{
                                        anchors.fill: parent
                                        onClicked:{
                                            supervisor.playSound('click', slider_volume_button.value);
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
                                        text:qsTr("preset 4")
                                        font.family: font_noto_r.name
                                        font.pixelSize: 15
                                        color: cur_preset===4?color_green:color_mid_black
                                    }
                                    MouseArea{
                                        anchors.fill: parent
                                        onClicked:{
                                            supervisor.playSound('click', slider_volume_button.value);
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
                                    height: setting_height
                                    anchors.verticalCenter: parent.verticalCenter
                                    radius: 5
                                    Text{
                                        id: text_preset_name_5
                                        anchors.centerIn: parent
                                        text:qsTr("preset 5")
                                        font.family: font_noto_r.name
                                        font.pixelSize: 15
                                        color: cur_preset===5?color_green:color_mid_black
                                    }
                                    MouseArea{
                                        anchors.fill: parent
                                        onClicked:{
                                            supervisor.playSound('click', slider_volume_button.value);
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
                                    visible: is_admin //Add
                                    Text{
                                        anchors.centerIn: parent
                                        text: qsTr("변경")
                                        color: "white"
                                        font.family: font_noto_r.name
                                        font.pixelSize: info_font_size
                                    }
                                    MouseArea{
                                        anchors.fill: parent
                                        onClicked:{
                                            supervisor.playSound('click', slider_volume_button.value);
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
                    height: setting_height
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
                                text:qsTr("복귀 속도 지정")
                                font.pixelSize: name_font_size
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
                                text:qsTr("?")
                                onClicked:{
                                    popup_help_setting.open();
                                    popup_help_setting.setTitle(qsTr("복귀 속도 지정"));
                                    popup_help_setting.addLine(qsTr("로봇이 서빙 후 대기위치로 복귀할 때 속도를 지정합니다"));
                                    popup_help_setting.addLine(qsTr("사용하지 않으면 기본속도 그대로 이동합니다"));
                                    popup_help_setting.addLine(qsTr("안전속도 구간에 진입하면 속도가 자동으로 저하됩니다"));
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
                                font.pixelSize: info_font_size
                                property bool ischanged: false
                                onCurrentIndexChanged: {
                                    ischanged = true;
                                }
                                model:[qsTr("사용 안함"), qsTr("매우느리게"),qsTr("느리게"), qsTr("보통"), qsTr("빠르게"), qsTr("매우빠르게")] //아주느리게, 아주빠르게
                            }
                        }
                    }
                }
                Rectangle{
                    id: set_robot_442
                    width: 840
                    height: setting_height
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
                                text:qsTr("최대 호출 횟수")
                                font.pixelSize: name_font_size
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
                                text:qsTr("?")
                                onClicked:{
                                    popup_help_setting.open();
                                    popup_help_setting.setTitle(qsTr("최대 호출 횟수"));
                                    popup_help_setting.addLine(qsTr("호출벨 전용 기능입니다 지원되는 모델인지 확인하세요"));
                                    popup_help_setting.addLine(qsTr("로봇이 한 번 이동에 호출되는 최대 횟수입니다"));
                                    popup_help_setting.addLine(qsTr("대기 위치에서 출발한 뒤 해당 횟수만큼 테이블을 이동하면"));
                                    popup_help_setting.addLine(qsTr("추가적인 호출명령이 있어도 우선 대기위치로 돌아옵니다"));
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
                                font.pixelSize: info_font_size
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
                    height: setting_height
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
                                text:qsTr("호출복귀 후 재정비")
                                font.pixelSize: name_font_size
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                    anchors.leftMargin = 30 - width*(1-scale)/2
                                }
                            }
                            Item_buttons{
                                type: "circle_text"
                                width: parent.height*0.8
                                height: width
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.right: parent.right
                                anchors.rightMargin: 20
                                text:qsTr("?")
                                onClicked:{
                                    popup_help_setting.open();
                                    popup_help_setting.setTitle(qsTr("호출복귀 후 재정비"));
                                    popup_help_setting.addLine(qsTr("호출벨 전용 기능입니다 지원되는 모델인지 확인하세요"));
                                    popup_help_setting.addLine(qsTr("로봇이 복귀 후 재정비가 필요한 지 여부를 선택하세요"));
                                    popup_help_setting.addLine(qsTr("사용 시 복귀 후 사용자 입력이 있을 때 까지 대기하며"));
                                    popup_help_setting.addLine(qsTr("미사용 시 복귀 하자마자 다른 호출이 들어오면 출발할 수 있습니다"));
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
                                font.pixelSize: info_font_size
                                property bool ischanged: false
                                onCurrentIndexChanged: {
                                    ischanged = true;
                                }
                                model:[qsTr("사용안함"), qsTr("사용")]

                            }
                        }
                    }
                }
                Rectangle{
                    id: set_resting_lock
                    width: 840
                    height: setting_height
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
                                text:qsTr("대기장소 모터 락 해제")
                                font.pixelSize: name_font_size
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                    anchors.leftMargin = 30 - width*(1-scale)/2
                                }
                            }
                            Item_buttons{
                                type: "circle_text"
                                width: parent.height*0.8
                                height: width
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.right: parent.right
                                anchors.rightMargin: 20
                                text:qsTr("?")
                                onClicked:{
                                    popup_help_setting.open();
                                    popup_help_setting.setTitle(qsTr("대기장소 모터 락 해제"));
                                    popup_help_setting.addLine(qsTr("로봇이 대기장소에서 대기하고 있을 때 사람이 밀어서 움직일 수 있는지 설정합니다"));
                                    popup_help_setting.addLine(qsTr("매장 바닥 상황에 따라 로봇이 굴러서 저절로 이동할 수 있습니다"));
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
                                font.pixelSize: info_font_size
                                property bool ischanged: false
                                onCurrentIndexChanged: {
                                    ischanged = true;
                                }
                                model:[qsTr("사용안함"), qsTr("사용")]

                            }
                        }
                    }
                }
                Rectangle{
                    id: set_auto_update
                    width: 840
                    visible: false
                    height: setting_height
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
                                text:qsTr("시작시 업데이트 검사")
                                font.pixelSize: name_font_size
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                    anchors.leftMargin = 30 - width*(1-scale)/2
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
                                font.pixelSize: info_font_size
                                property bool ischanged: false
                                onCurrentIndexChanged: {
                                    ischanged = true;
                                }
                                model:[qsTr("사용 안함"), qsTr("사용")]
                            }
                        }
                    }
                }

                Rectangle{
                    width: 1100
                    height: group_height
                    color: "black"
                    anchors.horizontalCenter: parent.horizontalCenter
                    Text{
                        anchors.centerIn: parent
                        font.family: font_noto_b.name
                        text:qsTr("UI 설정")
                        color: "white"
                        font.pixelSize: group_font_size
                    }
                }
                Rectangle{
                    id: set_show_time
                    width: 840
                    height: setting_height
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
                                text:qsTr("시간 표시")
                                font.pixelSize: name_font_size
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                    anchors.leftMargin = 30 - width*(1-scale)/2
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
                                id: combo_show_time
                                anchors.fill: parent
                                font.pixelSize: info_font_size
                                property bool ischanged: false
                                onCurrentIndexChanged: {
                                    ischanged = true;
                                }
                                model:[qsTr("표시안함"), qsTr("표시")]

                            }
                        }
                    }
                }
                Rectangle{
                    id: set_use_tray
                    width: 840
                    height: setting_height
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
                                text:qsTr("트레이 별 서빙")
                                font.pixelSize: name_font_size
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                    anchors.leftMargin = 30 - width*(1-scale)/2
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
                                font.pixelSize: info_font_size
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
                                model:[qsTr("사용안함"), qsTr("사용")]

                            }
                        }
                    }
                }
                Rectangle{
                    id: set_tray_num
                    width: 840
                    height: setting_height
                    visible: use_tray
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
                                text:qsTr("트레이 개수")
                                font.pixelSize: name_font_size
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                    anchors.leftMargin = 30 - width*(1-scale)/2
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
                                font.pixelSize: info_font_size
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
                    height: setting_height
//                    visible: false
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
                                text:qsTr("표시 언어")
                                font.pixelSize: name_font_size
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
                                font.pixelSize: info_font_size
                                anchors.fill: parent
                                property bool ischanged: false
                                onCurrentIndexChanged: {
                                    ischanged = true;
                                }
                                model:[qsTr("한국어"), qsTr("영어")]
                            }
                        }
                    }
                }
                Rectangle{
                    id: set_movingpage
                    width: 840
                    height: setting_height
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
                                text:qsTr("이동 중 화면")
                                font.pixelSize: name_font_size
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
                                ComboBox{
                                    id: combo_movingpage
                                    width: currentIndex===3?409:489
                                    height: setting_height
                                    font.pixelSize: info_font_size
                                    property bool ischanged: false
                                    onCurrentIndexChanged: {
                                        ischanged = true;
                                    }
                                    model:[qsTr("목적지 표시"), qsTr("동그란눈 얼굴"), qsTr("네모눈 얼굴"), qsTr("사용자 지정화면")]
                                }
                                Rectangle{
                                    width: 70
                                    height: setting_height
                                    visible: combo_movingpage.currentIndex === 3
                                    color: color_dark_navy
                                    Text{
                                        anchors.centerIn: parent
                                        font.pixelSize: info_font_size
                                        text: qsTr("설정")
                                        color: "white"
                                    }
                                    MouseArea{
                                        anchors.fill: parent
                                        onClicked:{
                                            supervisor.initServingPage();
                                            popup_set_patrolpage.page = "serving";
                                            popup_set_patrolpage.open();
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                Rectangle{
                    id: set_patrolpage
                    width: 840
                    height: setting_height
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
                                text:qsTr("순회 중 화면")
                                font.pixelSize: name_font_size
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
                                id: combo_patrolpage
                                width: currentIndex === 2?parent.width - 100 : parent.width
                                height: parent.height
                                font.pixelSize: info_font_size
                                property bool ischanged: false
                                onCurrentIndexChanged: {
                                    ischanged = true;
                                }
                                model:[qsTr("목적지 표시"), qsTr("귀여운 얼굴"), qsTr("커스텀 화면")]
                            }
                            Rectangle{
                                width: 100
                                height: parent.height
                                anchors.right: parent.right
                                visible: combo_patrolpage.currentIndex === 2
                                radius: 5
                                color: "black"
                                Text{
                                    anchors.centerIn: parent
                                    color: "white"
                                    text: qsTr("설정")
                                    font.family: font_noto_r.name
                                    font.pixelSize: info_font_size
                                }
                                MouseArea{
                                    anchors.fill: parent
                                    onClicked:{
                                        supervisor.playSound('click', slider_volume_button.value);
                                        popup_set_patrolpage.page = "moving";
                                        popup_set_patrolpage.open();
                                    }
                                }
                            }
                        }
                    }
                }
                Rectangle{
                    id: set_voice_mode
                    width: 840
                    height: setting_height
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
                                text:qsTr("로봇 음성")
                                font.pixelSize: name_font_size
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
                                anchors.fill: parent
                                ComboBox{
                                    id: combo_voice_mode
                                    width: parent.width
                                    font.pixelSize: info_font_size
                                    height: parent.height
                                    property bool ischanged: false
                                    onCurrentIndexChanged: {
                                        ischanged = true;
                                        setVoiceModel();
                                        combo_voice_name.currentIndex = 0;

                                    }
                                    model:[qsTr("기본 음성"), qsTr("음성 설정(인터넷필요)")]
                                }
                            }

                        }
                    }
                }
                Rectangle{
                    id: set_voice_language
                    width: 840
                    height: setting_height
                    visible: combo_voice_mode.currentIndex === 1
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
                                text:qsTr("음성 언어")
                                font.pixelSize: name_font_size
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
                                anchors.fill: parent
                                ComboBox{
                                    id: combo_voice_language
                                    width: parent.width - 100
                                    font.pixelSize: info_font_size
                                    height: parent.height
                                    property bool ischanged: false
                                    onCurrentIndexChanged: {
                                        ischanged = true;
                                        setVoiceModel();
                                        combo_voice_name.currentIndex = 0;
                                    }
                                    model:[qsTr("한국어"), qsTr("영어"), qsTr("중국어"), qsTr("일본어"), qsTr("스페인어")]//, qsTr("러시아어"), qsTr("독일어")]
                                    MouseArea{
                                        anchors.fill: parent
                                        onClicked:{
                                            supervisor.playSound('no', slider_volume_button.value);
                                        }
                                    }
                                }
                                Rectangle{
                                    width: 100
                                    height: parent.height
                                    anchors.verticalCenter: parent.verticalCenter
                                    radius: 5
                                    color: color_dark_navy
                                    Text{
                                        anchors.centerIn: parent
                                        text: qsTr("설정")
                                        color: "white"
                                        font.family: font_noto_r.name
                                        font.pixelSize: info_font_size
                                    }
                                    MouseArea{
                                        anchors.fill: parent
                                        onClicked:{
                                            supervisor.playSound('click', slider_volume_button.value);
                                            popup_mention.open();
                                        }
                                    }
                                }
                            }

                        }
                    }
                }
                Rectangle{
                    id: set_voice_name
                    width: 840
                    height: setting_height
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
                                text:qsTr("음성")
                                font.pixelSize: name_font_size
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
                                anchors.fill: parent
                                ComboBox{
                                    id: combo_voice_name
                                    width: combo_voice_mode.currentIndex === 1?parent.width-100 : parent.width
                                    height: parent.height
                                    property bool ischanged: false
                                    font.pixelSize: info_font_size
                                    onCurrentIndexChanged: {
                                        ischanged = true;
                                    }
                                    model:ListModel{id:model_voice}
                                }
                                Rectangle{
                                    width: 100
                                    visible: combo_voice_mode.currentIndex === 1
                                    height: parent.height
                                    anchors.verticalCenter: parent.verticalCenter
                                    radius: 5
                                    color: color_dark_navy
                                    Text{
                                        anchors.centerIn: parent
                                        text: qsTr("상세설정")
                                        color: "white"
                                        font.family: font_noto_r.name
                                        font.pixelSize: info_font_size
                                    }
                                    MouseArea{
                                        anchors.fill: parent
                                        onClicked:{
                                            supervisor.playSound('click', slider_volume_button.value);
                                            popup_voice.open();
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                Rectangle{
                    id: set_system_volume
                    width: 840
                    height: setting_height
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
                                text:qsTr("시스템 볼륨")
                                font.pixelSize: name_font_size
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
                                            supervisor.playSound('click', slider_volume_button.value);

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
                                    width: tt.width*0.7 + 10 + ttet2132.width
                                    height: setting_height
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
                    height: setting_height
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
                                text:qsTr("음악 볼륨")
                                font.pixelSize: name_font_size
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
                                            supervisor.playSound('click', slider_volume_button.value);
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
                                    width: tt.width*0.7
                                    height: setting_height
                                    stepSize: 1
                                    from: 0
                                    to: 100
                                    property bool ischanged: false
                                    onValueChanged: {
                                        ischanged = true;
                                    }
                                    onPressedChanged: {
                                        if(pressed){

                                        }else{
                                            supervisor.setvolumeBGM(slider_volume_bgm.value);
                                        }
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
                                            supervisor.playSound('click', slider_volume_button.value);
                                            if(supervisor.isplayBGM()){
                                                supervisor.stopBGM();
                                                ttet2132.source = "icon/icon_test_play.png";
                                            }else{
                                                supervisor.playBGM(slider_volume_bgm.value);
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
                    height: setting_height
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
                                text:qsTr("음성 볼륨")
                                font.pixelSize: name_font_size
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
                                            supervisor.playSound('click', slider_volume_button.value);
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
                                    height: setting_height
                                    from: 0
                                    to: 100
                                    stepSize: 1
                                    property bool ischanged: false
                                    onValueChanged: {
                                        ischanged = true;
                                    }
                                    onPressedChanged: {
                                        if(pressed){

                                        }else{
                                            supervisor.playVoice("move_serving","","","",slider_volume_voice.value);
                                        }
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
                                            supervisor.playSound('click', slider_volume_button.value);
                                            supervisor.playVoice("move_serving","","","",slider_volume_voice.value);
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
                    height: setting_height
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
                                text:qsTr("버튼클릭 볼륨")
                                font.pixelSize: name_font_size
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
                                            supervisor.playSound('click', slider_volume_button.value);
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
                                    height: setting_height
                                    from: 0
                                    to: 100
                                    stepSize: 1
                                    property bool ischanged: false
                                    onValueChanged: {
                                        ischanged = true;
                                    }
                                    onPressedChanged: {
                                        if(pressed){

                                        }else{
                                            supervisor.playSound('click', slider_volume_button.value);
                                        }
                                    }
                                    value: supervisor.getSetting("setting","UI","volume_button")
                                }
                                Image{
                                    anchors.verticalCenter: parent.verticalCenter
                                    source: "icon/icon_test_play.png"
                                    MouseArea{
                                        anchors.fill: parent
                                        onClicked: {
                                            supervisor.playSound('click', slider_volume_button.value);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                Rectangle{
                    id: set_branch
                    width: 840
                    height: setting_height
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
                                text:qsTr("깃 브랜치")
                                font.pixelSize: name_font_size
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
                                anchors.fill: parent
                                spacing: 5
                                TextField{
                                    width: parent.width - 160
                                    height: parent.height
                                    font.pixelSize: info_font_size
                                    id: tfield_gitbranch
                                    property bool ischanged: false
                                    text:"master"
                                    onTextChanged: {
                                        ischanged = true;
                                    }
                                }
                                Rectangle{
                                    width: 50
                                    height: setting_height
                                    radius:10
                                    color: color_dark_navy
                                    anchors.verticalCenter: parent.verticalCenter
                                    Image{
                                        anchors.centerIn: parent
                                        width: 35
                                        height: 35
                                        sourceSize.width: width
                                        sourceSize.height: height
                                        source: "icon/icon_keyboard.png"
                                        ColorOverlay{
                                            anchors.fill: parent
                                            source: parent
                                            color: "white"
                                        }
                                    }
                                    MouseArea{
                                        enabled: parent.enabled
                                        anchors.fill: parent
                                        onClicked:{
                                            supervisor.playSound('click', slider_volume_button.value);
                                            keyboard.owner = tfield_gitbranch;
                                            tfield_gitbranch.selectAll();
                                            keyboard.open();
                                        }
                                    }
                                }
                                Item_buttons{
                                    type: "white_btn"
                                    text: qsTr("변경")
                                    width: 100
                                    onClicked:{
                                        supervisor.setSetting("setting","UI/program_branch",tfield_gitbranch.text);
                                        supervisor.playSound('click', slider_volume_button.value);
                                        tfield_gitbranch.ischanged = false;
                                    }
                                    height: parent.height
                                }
                            }

                        }
                    }
                }

                Rectangle{
                    width: 1100
                    height: group_height
                    visible: is_admin
                    color: "black"
                    anchors.horizontalCenter: parent.horizontalCenter
                    Text{
                        anchors.centerIn: parent
                        font.family: font_noto_b.name
                        text:qsTr("멀티로봇")
                        color: "white"
                        font.pixelSize: group_font_size
                    }
                }
                Rectangle{
                    id: set_use_multirobot
                    width: 840
                    visible: is_admin
                    height: setting_height
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
                                text:qsTr("멀티로봇 사용")
                                font.pixelSize: name_font_size
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
                                font.pixelSize: info_font_size
                                onCurrentIndexChanged: {
                                    ischanged = true;
                                    if(currentIndex == 0){
                                        use_multirobot = false;
                                    }else{
                                        use_multirobot = true;
                                    }
                                }
                                model:[qsTr("사용안함"),qsTr("사용")]
                            }
                        }
                    }
                }

                Rectangle{
                    id: set_use_server_call
                    width: 840
                    visible: is_admin && use_multirobot
                    height: setting_height
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
                                text:qsTr("서버 호출 사용")
                                font.pixelSize: name_font_size
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
                                font.pixelSize: info_font_size
                                property bool ischanged: false
                                onCurrentIndexChanged: {
                                    ischanged = true;
                                }
                                model:[qsTr("사용안함"),qsTr("사용")]
                            }
                        }
                    }
                }
                Rectangle{
                    id: set_server_ip
                    width: 840
                    visible: is_admin && use_multirobot
                    height: setting_height
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
                                text:qsTr("서버 IP")
                                font.pixelSize: name_font_size
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
                                    font.pixelSize: info_font_size
                                    height: setting_height
                                    MouseArea{
                                        anchors.fill:parent
                                        onClicked: {
                                            supervisor.playSound('click', slider_volume_button.value);
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
                                    font.pixelSize: info_font_size
                                    height: setting_height
                                    MouseArea{
                                        anchors.fill:parent
                                        onClicked: {
                                            supervisor.playSound('click', slider_volume_button.value);
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
                                    font.pixelSize: info_font_size
                                }
                                TextField{
                                    id: server_ip_3
                                    width: 70
                                    font.pixelSize: info_font_size
                                    height: setting_height
                                    MouseArea{
                                        anchors.fill:parent
                                        onClicked: {
                                            supervisor.playSound('click', slider_volume_button.value);
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
                                    font.pixelSize: info_font_size
                                }
                                TextField{
                                    id: server_ip_4
                                    width: 70
                                    font.pixelSize: info_font_size
                                    height: setting_height
                                    MouseArea{
                                        anchors.fill:parent
                                        onClicked: {
                                            supervisor.playSound('click', slider_volume_button.value);
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
                                        font.pixelSize: info_font_size
                                        color: "white"
                                        font.family: font_noto_r.name
                                        text: qsTr("변경")
                                    }
                                    MouseArea{
                                        anchors.fill: parent
                                        onClicked:{
                                            supervisor.playSound('click', slider_volume_button.value);
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
                    height: setting_height
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
                                text:qsTr("FMS 아이디")
                                font.pixelSize: name_font_size
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
                                font.pixelSize: info_font_size
                                property bool ischanged: false
                                onTextChanged: {
                                    ischanged = true;
                                    is_reset_slam = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        supervisor.playSound('click', slider_volume_button.value);
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
                    height: setting_height
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
                                text:qsTr("FMS 비밀번호")
                                font.pixelSize: name_font_size
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
                                font.pixelSize: info_font_size
                                anchors.fill: parent
                                property bool ischanged: false
                                onTextChanged: {
                                    ischanged = true;
                                    is_reset_slam = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        supervisor.playSound('click', slider_volume_button.value);
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
                    height: group_height
                    visible: is_rainbow
                    color: "black"
                    anchors.horizontalCenter: parent.horizontalCenter
                    Text{
                        anchors.centerIn: parent
                        font.family: font_noto_b.name
                        text:qsTr("로봇 하드웨어 설정")
                        color: "white"
                        font.pixelSize: group_font_size
                    }
                }
                Rectangle{
                    id: set_robot_radius
                    width: 840
                    visible: is_rainbow
                    height: setting_height
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
                                text:qsTr("로봇 반지름 반경 [m]")
                                font.pixelSize: name_font_size
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                    anchors.leftMargin = 30 - width*(1-scale)/2
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
                                font.pixelSize: info_font_size
                                property bool ischanged: false
                                onTextChanged: {
                                    ischanged = true;
                                    is_reset_slam = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        supervisor.playSound('click', slider_volume_button.value);
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
                    visible: is_rainbow
                    height: setting_height
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
                                text:qsTr("로봇 길이 [m]")
                                font.pixelSize: name_font_size
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                    anchors.leftMargin = 30 - width*(1-scale)/2
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
                                font.pixelSize: info_font_size
                                onTextChanged: {
                                    ischanged = true;
                                    is_reset_slam = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        supervisor.playSound('click', slider_volume_button.value);
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
                    visible: is_rainbow
                    height: setting_height
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
                                text:qsTr("휠 베이스 반경 [m]")
                                font.pixelSize: name_font_size
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                    anchors.leftMargin = 30 - width*(1-scale)/2
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
                                font.pixelSize: info_font_size
                                anchors.fill: parent
                                property bool ischanged: false
                                onTextChanged: {
                                    ischanged = true;
                                    is_reset_slam = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        supervisor.playSound('click', slider_volume_button.value);
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
                    height: setting_height
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
                                text:qsTr("휠 반지름 반경 [m]")
                                font.pixelSize: name_font_size
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                    anchors.leftMargin = 30 - width*(1-scale)/2
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
                                font.pixelSize: info_font_size
                                property bool ischanged: false
                                onTextChanged: {
                                    ischanged = true;
                                    is_reset_slam = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        supervisor.playSound('click', slider_volume_button.value);
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
                    height: group_height
                    color: "black"
                    anchors.horizontalCenter: parent.horizontalCenter
                    Text{
                        anchors.centerIn: parent
                        font.family: font_noto_b.name
                        text:qsTr("네트워크 설정")
                        color: "white"
                        font.pixelSize: group_font_size
                    }
                }
                Rectangle{
                    id: set_internet
                    width: 840
                    height: setting_height
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
                                text:qsTr("인터넷 연결상태")
                                font.pixelSize: name_font_size
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                    anchors.leftMargin = 30 - width*(1-scale)/2
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
                                    id: internet_con
                                    width: 500
                                    height: setting_height
                                    property int connection: 0
                                    color: {
                                        if(internet_con.connection === 1){
                                            color_yellow
                                        }else if(internet_con.connection === 2){
                                            color_green
                                        }else{
                                            color_red
                                        }
                                    }
                                    Text{
                                        anchors.centerIn: parent
                                        font.family:font_noto_r.name
                                        font.pixelSize:info_font_size
                                        text:{
                                            if(internet_con.connection === 1){
                                                qsTr("연결중")
                                            }else if(internet_con.connection === 2){
                                                qsTr("연결됨")
                                            }else{
                                                qsTr("연결안됨")
                                            }
                                        }
                                        color: "white"
                                    }
                                }


                            }
                        }


                    }
                }
                Rectangle{
                    id: set_ethernet
                    width: 840
                    height: is_admin?500:setting_height
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
                                text:qsTr("유선 연결상태")
                                font.pixelSize: name_font_size
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                    anchors.leftMargin = 30 - width*(1-scale)/2
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
                                spacing: 6
                                Rectangle{
                                    id: ethernet_con
                                    width: 500
                                    height: setting_height
                                    property int connection: 0
                                    color: {
                                        if(ethernet_con.connection === 1){
                                            color_yellow
                                        }else if(ethernet_con.connection === 2){
                                            color_green
                                        }else{
                                            color_red
                                        }
                                    }
                                    Text{
                                        anchors.centerIn: parent
                                        font.family:font_noto_r.name
                                        font.pixelSize:info_font_size
                                        text:{
                                            if(ethernet_con.connection === 1){
                                                qsTr("연결중")
                                            }else if(ethernet_con.connection === 2){
                                                qsTr("연결됨")
                                            }else{
                                                qsTr("연결안됨")
                                            }
                                        }
                                        color: "white"
                                    }
                                }
                                Row{
                                    visible: is_admin
                                    spacing: 5
                                    Rectangle{
                                        width: 150
                                        height: setting_height
                                        Text{
                                            anchors.verticalCenter: parent.verticalCenter
                                            anchors.left: parent.left
                                            anchors.leftMargin: 30
                                            font.family: font_noto_r.name
                                            text:qsTr("IP")
                                            font.pixelSize: name_font_size
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
                                        height: setting_height
                                        color: "#d0d0d0"
                                    }

                                    Rectangle{
                                        width: 500-161
                                        height: setting_height
                                        Row{
                                            spacing: 10
                                            anchors.centerIn: parent
                                            TextField{
                                                id: ethernet_ip_1
                                                width: 60
                                                height: 40
                                                font.pixelSize: info_font_size
                                                horizontalAlignment: TextField.AlignHCenter
                                                MouseArea{
                                                    anchors.fill:parent
                                                    onClicked: {
                                                        supervisor.playSound('click', slider_volume_button.value);
                                                        if(keypad.is_opened){
                                                            keypad.owner = ethernet_ip_1;
                                                            ethernet_ip_1.selectAll();
                                                        }else{
                                                            keypad.owner = ethernet_ip_1;
                                                            ethernet_ip_1.selectAll();
                                                            keypad.open();
                                                        }
                                                    }
                                                }

                                                color: ischanged?color_red:"black"
                                                property bool ischanged: false
                                                onTextChanged: {
                                                    ischanged = true;
                                                    if(ethernet_ip_1.text.split(".").length > 1){
                                                        ethernet_ip_1.text = ethernet_ip_1.text.split(".")[0];
                                                        ethernet_ip_2.selectAll();
                                                        keypad.owner = ethernet_ip_2;
                                                    }
                                                    if(ethernet_ip_1.text.length == 3){
                                                        ethernet_ip_2.selectAll();
                                                        keypad.owner = ethernet_ip_2;
                                                    }
                                                }
                                            }
                                            Text{
                                                anchors.verticalCenter: parent.verticalCenter
                                                text:"."
                                                font.pixelSize: info_font_size
                                            }

                                            TextField{
                                                id: ethernet_ip_2
                                                width: 60
                                                height: 40
                                                font.pixelSize: info_font_size
                                                horizontalAlignment: TextField.AlignHCenter
                                                MouseArea{
                                                    anchors.fill:parent
                                                    onClicked: {
                                                        supervisor.playSound('click', slider_volume_button.value);
                                                        if(keypad.is_opened){
                                                            keypad.owner = ethernet_ip_2;
                                                            ethernet_ip_2.selectAll();
                                                        }else{
                                                            keypad.owner = ethernet_ip_2;
                                                            ethernet_ip_2.selectAll();
                                                            keypad.open();
                                                        }
                                                    }
                                                }
                                                color: ischanged?color_red:"black"
                                                property bool ischanged: false
                                                onTextChanged: {
                                                    ischanged = true;
                                                    if(ethernet_ip_2.text == "."){
                                                        ethernet_ip_2.text = ethernet_ip_2.text.split(".")[0]
                                                    }

                                                    if(ethernet_ip_2.text.split(".").length > 1){
                                                        ethernet_ip_2.text = ethernet_ip_2.text.split(".")[0];
                                                        ethernet_ip_3.selectAll();
                                                        keypad.owner = ethernet_ip_3;
                                                    }
                                                    if(ethernet_ip_2.text.length == 3){
                                                        ethernet_ip_3.selectAll();
                                                        keypad.owner = ethernet_ip_3;
                                                    }
                                                }
                                            }
                                            Text{
                                                anchors.verticalCenter: parent.verticalCenter
                                                text:"."
                                                font.pixelSize: info_font_size
                                            }
                                            TextField{
                                                id: ethernet_ip_3
                                                width: 60
                                                height: 40
                                                font.pixelSize: info_font_size
                                                horizontalAlignment: TextField.AlignHCenter
                                                MouseArea{
                                                    anchors.fill:parent
                                                    onClicked: {
                                                        supervisor.playSound('click', slider_volume_button.value);
                                                        if(keypad.is_opened){
                                                            keypad.owner = ethernet_ip_3;
                                                            ethernet_ip_3.selectAll();
                                                        }else{
                                                            keypad.owner = ethernet_ip_3;
                                                            ethernet_ip_3.selectAll();
                                                            keypad.open();
                                                        }
                                                    }
                                                }
                                                color: ischanged?color_red:"black"
                                                property bool ischanged: false
                                                onTextChanged: {
                                                    ischanged = true;
                                                    if(ethernet_ip_3.text == "."){
                                                        ethernet_ip_3.text = ethernet_ip_3.text.split(".")[0]
                                                    }

                                                    if(ethernet_ip_3.text.split(".").length > 1){
                                                        ethernet_ip_3.text = ethernet_ip_3.text.split(".")[0];
                                                        ethernet_ip_4.selectAll();
                                                        keypad.owner = ethernet_ip_4;
                                                    }
                                                    if(ethernet_ip_3.text.length == 3){
                                                        ethernet_ip_4.selectAll();
                                                        keypad.owner = ethernet_ip_4;
                                                    }
                                                }
                                            }
                                            Text{
                                                anchors.verticalCenter: parent.verticalCenter
                                                text:"."
                                                font.pixelSize: info_font_size
                                            }
                                            TextField{
                                                id: ethernet_ip_4
                                                width: 60
                                                font.pixelSize: info_font_size
                                                height: 40
                                                horizontalAlignment: TextField.AlignHCenter
                                                MouseArea{
                                                    anchors.fill:parent
                                                    onClicked: {
                                                        supervisor.playSound('click', slider_volume_button.value);
                                                        if(keypad.is_opened){
                                                            keypad.owner = ethernet_ip_4;
                                                            ethernet_ip_4.selectAll();
                                                        }else{
                                                            keypad.owner = ethernet_ip_4;
                                                            ethernet_ip_4.selectAll();
                                                            keypad.open();
                                                        }
                                                    }
                                                }
                                                color: ischanged?color_red:"black"
                                                property bool ischanged: false
                                                onTextChanged: {
                                                    ischanged = true;
                                                    if(ethernet_ip_4.text == "."){
                                                        ethernet_ip_4.text = ethernet_ip_4.text.split(".")[0]
                                                    }

                                                    if(ethernet_ip_4.text.split(".").length > 1){
                                                        ethernet_ip_4.text = ethernet_ip_4.text.split(".")[0];
                                                        keypad.close();
                                                    }
                                                    if(ethernet_ip_4.text.length == 3){
                                                        keypad.close();
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                                Row{
                                    visible: is_admin
                                    spacing: 5
                                    Rectangle{
                                        width: 150
                                        height: setting_height
                                        Text{
                                            anchors.verticalCenter: parent.verticalCenter
                                            anchors.left: parent.left
                                            anchors.leftMargin: 30
                                            font.family: font_noto_r.name
                                            text:qsTr("Netmask")
                                            font.pixelSize: name_font_size
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
                                        height: setting_height
                                        color: "#d0d0d0"
                                    }

                                    Rectangle{
                                        width: 500-161
                                        height: setting_height
                                        Row{
                                            spacing: 10
                                            anchors.centerIn: parent
                                            TextField{
                                                id: ethernet_netmask_1
                                                width: 60
                                                height: 40
                                                font.pixelSize: info_font_size
                                                horizontalAlignment: TextField.AlignHCenter
                                                MouseArea{
                                                    anchors.fill:parent
                                                    onClicked: {
                                                        supervisor.playSound('click', slider_volume_button.value);
                                                        if(keypad.is_opened){
                                                            keypad.owner = ethernet_netmask_1;
                                                            ethernet_netmask_1.selectAll();
                                                        }else{
                                                            keypad.owner = ethernet_netmask_1;
                                                            ethernet_netmask_1.selectAll();
                                                            keypad.open();
                                                        }
                                                    }
                                                }
                                                color: ischanged?color_red:"black"
                                                property bool ischanged: false
                                                onIschangedChanged: {
                                                    color = ischanged?color_red:"black"
                                                }
                                                onTextChanged: {
                                                    ischanged = true;
                                                    if(ethernet_netmask_1.text.split(".").length > 1){
                                                        ethernet_netmask_1.text = ethernet_netmask_1.text.split(".")[0];
                                                        keypad.owner = ethernet_netmask_2;
                                                        ethernet_netmask_2.selectAll();
                                                    }
                                                    if(ethernet_netmask_1.text.length == 3){
                                                        keypad.owner = ethernet_netmask_2;
                                                        ethernet_netmask_2.selectAll();
                                                    }
                                                }
                                            }
                                            Text{
                                                anchors.verticalCenter: parent.verticalCenter
                                                text:"."
                                                font.pixelSize: info_font_size
                                            }

                                            TextField{
                                                id: ethernet_netmask_2
                                                width: 60
                                                height: 40
                                                font.pixelSize: info_font_size
                                                horizontalAlignment: TextField.AlignHCenter
                                                MouseArea{
                                                    anchors.fill:parent
                                                    onClicked: {
                                                        supervisor.playSound('click', slider_volume_button.value);
                                                        if(keypad.is_opened){
                                                            keypad.owner = ethernet_netmask_2;
                                                            ethernet_netmask_2.selectAll();
                                                        }else{
                                                            keypad.owner = ethernet_netmask_2;
                                                            ethernet_netmask_2.selectAll();
                                                            keypad.open();
                                                        }
                                                    }
                                                }
                                                color: ischanged?color_red:"black"
                                                property bool ischanged: false
                                                onIschangedChanged: {
                                                    color = ischanged?color_red:"black"
                                                }
                                                onTextChanged: {
                                                    ischanged = true;
                                                    if(ethernet_netmask_2.text == "."){
                                                        ethernet_netmask_2.text = ethernet_netmask_2.text.split(".")[0]
                                                    }

                                                    if(ethernet_netmask_2.text.split(".").length > 1){
                                                        ethernet_netmask_2.text = ethernet_netmask_2.text.split(".")[0];
                                                        keypad.owner = ethernet_netmask_3;
                                                        ethernet_netmask_3.selectAll();
                                                    }
                                                    if(ethernet_netmask_2.text.length == 3){
                                                        keypad.owner = ethernet_netmask_3;
                                                        ethernet_netmask_3.selectAll();
                                                    }
                                                }
                                            }
                                            Text{
                                                font.pixelSize: info_font_size
                                                anchors.verticalCenter: parent.verticalCenter
                                                text:"."
                                            }
                                            TextField{
                                                id: ethernet_netmask_3
                                                width: 60
                                                font.pixelSize: info_font_size
                                                height: 40
                                                horizontalAlignment: TextField.AlignHCenter
                                                MouseArea{
                                                    anchors.fill:parent
                                                    onClicked: {
                                                        supervisor.playSound('click', slider_volume_button.value);
                                                        if(keypad.is_opened){
                                                            keypad.owner = ethernet_netmask_3;
                                                            ethernet_netmask_3.selectAll();
                                                        }else{
                                                            keypad.owner = ethernet_netmask_3;
                                                            ethernet_netmask_3.selectAll();
                                                            keypad.open();
                                                        }
                                                    }
                                                }
                                                property bool ischanged: false
                                                color: ischanged?color_red:"black"
                                                onColorChanged: {
                                                    print("netmask 3 color : ",color)
                                                }
                                                onIschangedChanged: {
                                                    color = ischanged?color_red:"black"
                                                }
                                                onTextChanged: {
                                                    ischanged = true;
                                                    if(ethernet_netmask_3.text == "."){
                                                        ethernet_netmask_3.text = ethernet_netmask_3.text.split(".")[0]
                                                    }

                                                    if(ethernet_netmask_3.text.split(".").length > 1){
                                                        ethernet_netmask_3.text = ethernet_netmask_3.text.split(".")[0];
                                                        keypad.owner = ethernet_netmask_4;
                                                        ethernet_netmask_4.selectAll();
                                                    }
                                                    if(ethernet_netmask_3.text.length == 3){
                                                        keypad.owner = ethernet_netmask_4;
                                                        ethernet_netmask_4.selectAll();
                                                    }
                                                }
                                            }
                                            Text{
                                                font.pixelSize: info_font_size
                                                anchors.verticalCenter: parent.verticalCenter
                                                text:"."
                                            }
                                            TextField{
                                                id: ethernet_netmask_4
                                                width: 60
                                                height: 40
                                                font.pixelSize: info_font_size
                                                horizontalAlignment: TextField.AlignHCenter
                                                MouseArea{
                                                    anchors.fill:parent
                                                    onClicked: {
                                                        supervisor.playSound('click', slider_volume_button.value);
                                                        if(keypad.is_opened){
                                                            keypad.owner = ethernet_netmask_4;
                                                            ethernet_netmask_4.selectAll();
                                                        }else{
                                                            keypad.owner = ethernet_netmask_4;
                                                            ethernet_netmask_4.selectAll();
                                                            keypad.open();
                                                        }
                                                    }
                                                }
                                                onIschangedChanged: {
                                                    color = ischanged?color_red:"black"
                                                }
                                                color: ischanged?color_red:"black"
                                                property bool ischanged: false
                                                onTextChanged: {
                                                    ischanged = true;
                                                    if(ethernet_netmask_4.text == "."){
                                                        ethernet_netmask_4.text = ethernet_netmask_4.text.split(".")[0]
                                                    }

                                                    if(ethernet_netmask_4.text.split(".").length > 1){
                                                        ethernet_netmask_4.text = ethernet_netmask_4.text.split(".")[0];
                                                        keypad.close();
                                                    }
                                                    if(ethernet_netmask_4.text.length == 3){
                                                        keypad.close();
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                                Row{
                                    visible: is_admin
                                    spacing: 5
                                    Rectangle{
                                        width: 150
                                        height: setting_height
                                        Text{
                                            anchors.verticalCenter: parent.verticalCenter
                                            anchors.left: parent.left
                                            anchors.leftMargin: 30
                                            font.family: font_noto_r.name
                                            text:qsTr("Gateway")
                                            font.pixelSize: name_font_size
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
                                        height: setting_height
                                        color: "#d0d0d0"
                                    }

                                    Rectangle{
                                        width: 500-161
                                        height: setting_height
                                        Row{
                                            spacing: 10
                                            anchors.centerIn: parent
                                            TextField{
                                                id: ethernet_gateway_1
                                                width: 60
                                                height: 40
                                                font.pixelSize: info_font_size
                                                horizontalAlignment: TextField.AlignHCenter
                                                MouseArea{
                                                    anchors.fill:parent
                                                    onClicked: {
                                                        supervisor.playSound('click', slider_volume_button.value);
                                                        if(keypad.is_opened){
                                                            keypad.owner = ethernet_gateway_1;
                                                            ethernet_gateway_1.selectAll();
                                                        }else{
                                                            keypad.owner = ethernet_gateway_1;
                                                            ethernet_gateway_1.selectAll();
                                                            keypad.open();
                                                        }
                                                    }
                                                }
                                                color: ischanged?color_red:"black"
                                                property bool ischanged: false
                                                onTextChanged: {
                                                    ischanged = true;
                                                    if(ethernet_gateway_1.text.split(".").length > 1){
                                                        ethernet_gateway_1.text = ethernet_gateway_1.text.split(".")[0];
                                                        keypad.owner = ethernet_gateway_2;
                                                        ethernet_gateway_2.selectAll();
                                                    }
                                                    if(ethernet_gateway_1.text.length == 3){
                                                        keypad.owner = ethernet_gateway_2;
                                                        ethernet_gateway_2.selectAll();
                                                    }
                                                }
                                            }
                                            Text{
                                                anchors.verticalCenter: parent.verticalCenter
                                                text:"."
                                                font.pixelSize: info_font_size
                                            }

                                            TextField{
                                                id: ethernet_gateway_2
                                                width: 60
                                                height: 40
                                                font.pixelSize: info_font_size
                                                horizontalAlignment: TextField.AlignHCenter
                                                MouseArea{
                                                    anchors.fill:parent
                                                    onClicked: {
                                                        supervisor.playSound('click', slider_volume_button.value);
                                                        if(keypad.is_opened){
                                                            keypad.owner = ethernet_gateway_2;
                                                            ethernet_gateway_2.selectAll();
                                                        }else{
                                                            keypad.owner = ethernet_gateway_2;
                                                            ethernet_gateway_2.selectAll();
                                                            keypad.open();
                                                        }
                                                    }
                                                }
                                                color: ischanged?color_red:"black"
                                                property bool ischanged: false
                                                onTextChanged: {
                                                    ischanged = true;
                                                    if(ethernet_gateway_2.text == "."){
                                                        ethernet_gateway_2.text = ethernet_gateway_2.text.split(".")[0]
                                                    }

                                                    if(ethernet_gateway_2.text.split(".").length > 1){
                                                        ethernet_gateway_2.text = ethernet_gateway_2.text.split(".")[0];
                                                        keypad.owner = ethernet_gateway_3;
                                                        ethernet_gateway_3.selectAll();
                                                    }
                                                    if(ethernet_gateway_2.text.length == 3){
                                                        keypad.owner = ethernet_gateway_3;
                                                        ethernet_gateway_3.selectAll();
                                                    }
                                                }
                                            }
                                            Text{
                                                anchors.verticalCenter: parent.verticalCenter
                                                text:"."
                                                font.pixelSize: info_font_size
                                            }
                                            TextField{
                                                id: ethernet_gateway_3
                                                width: 60
                                                font.pixelSize: info_font_size
                                                height: 40
                                                horizontalAlignment: TextField.AlignHCenter
                                                MouseArea{
                                                    anchors.fill:parent
                                                    onClicked: {
                                                        supervisor.playSound('click', slider_volume_button.value);
                                                        if(keypad.is_opened){
                                                            keypad.owner = ethernet_gateway_3;
                                                            ethernet_gateway_3.selectAll();
                                                        }else{
                                                            keypad.owner = ethernet_gateway_3;
                                                            ethernet_gateway_3.selectAll();
                                                            keypad.open();
                                                        }
                                                    }
                                                }
                                                color: ischanged?color_red:"black"
                                                property bool ischanged: false
                                                onTextChanged: {
                                                    ischanged = true;
                                                    if(ethernet_gateway_3.text == "."){
                                                        ethernet_gateway_3.text = ethernet_gateway_3.text.split(".")[0]
                                                    }

                                                    if(ethernet_gateway_3.text.split(".").length > 1){
                                                        ethernet_gateway_3.text = ethernet_gateway_3.text.split(".")[0];
                                                        keypad.owner = ethernet_gateway_4;
                                                        ethernet_gateway_4.selectAll();
                                                    }
                                                    if(ethernet_gateway_3.text.length == 3){
                                                        keypad.owner = ethernet_gateway_4;
                                                        ethernet_gateway_4.selectAll();
                                                    }
                                                }
                                            }
                                            Text{
                                                anchors.verticalCenter: parent.verticalCenter
                                                text:"."
                                                font.pixelSize: info_font_size
                                            }
                                            TextField{
                                                id: ethernet_gateway_4
                                                width: 60
                                                height: 40
                                                font.pixelSize: info_font_size
                                                horizontalAlignment: TextField.AlignHCenter
                                                MouseArea{
                                                    anchors.fill:parent
                                                    onClicked: {
                                                        supervisor.playSound('click', slider_volume_button.value);
                                                        if(keypad.is_opened){
                                                            keypad.owner = ethernet_gateway_4;
                                                            ethernet_gateway_4.selectAll();
                                                        }else{
                                                            keypad.owner = ethernet_gateway_4;
                                                            ethernet_gateway_4.selectAll();
                                                            keypad.open();
                                                        }
                                                    }
                                                }
                                                color: ischanged?color_red:"black"
                                                property bool ischanged: false
                                                onTextChanged: {
                                                    ischanged = true;
                                                    if(ethernet_gateway_4.text == "."){
                                                        ethernet_gateway_4.text = ethernet_gateway_4.text.split(".")[0]
                                                    }

                                                    if(ethernet_gateway_4.text.split(".").length > 1){
                                                        ethernet_gateway_4.text = ethernet_gateway_4.text.split(".")[0];
                                                        keypad.close();
                                                    }
                                                    if(ethernet_gateway_4.text.length == 3){
                                                        keypad.close();
                                                    }
                                                }
                                            }

                                        }
                                    }
                                }


                                Row{
                                    visible: is_admin
                                    spacing: 5
                                    Rectangle{
                                        width: 150
                                        height: setting_height
                                        Text{
                                            anchors.verticalCenter: parent.verticalCenter
                                            anchors.left: parent.left
                                            anchors.leftMargin: 30
                                            font.family: font_noto_r.name
                                            text:qsTr("DNS 1")
                                            font.pixelSize: name_font_size
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
                                        height: setting_height
                                        color: "#d0d0d0"
                                    }

                                    Rectangle{
                                        width: 500-161
                                        height: setting_height
                                        Row{
                                            spacing: 10
                                            anchors.centerIn: parent
                                            TextField{
                                                id: ethernet_dnsmain_1
                                                width: 60
                                                font.pixelSize: info_font_size
                                                height: 40
                                                horizontalAlignment: TextField.AlignHCenter
                                                MouseArea{
                                                    anchors.fill:parent
                                                    onClicked: {
                                                        supervisor.playSound('click', slider_volume_button.value);
                                                        if(keypad.is_opened){
                                                            keypad.owner = ethernet_dnsmain_1;
                                                            ethernet_dnsmain_1.selectAll();
                                                        }else{
                                                            keypad.owner = ethernet_dnsmain_1;
                                                            ethernet_dnsmain_1.selectAll();
                                                            keypad.open();
                                                        }
                                                    }
                                                }
                                                color: ischanged?color_red:"black"
                                                property bool ischanged: false
                                                onTextChanged: {
                                                    ischanged = true;
                                                    if(ethernet_dnsmain_1.text.split(".").length > 1){
                                                        ethernet_dnsmain_1.text = ethernet_dnsmain_1.text.split(".")[0];
                                                        keypad.owner = ethernet_dnsmain_2;
                                                        ethernet_dnsmain_2.selectAll();
                                                    }
                                                    if(ethernet_dnsmain_1.text.length == 3){
                                                        keypad.owner = ethernet_dnsmain_2;
                                                        ethernet_dnsmain_2.selectAll();
                                                    }
                                                }
                                            }
                                            Text{
                                                anchors.verticalCenter: parent.verticalCenter
                                                text:"."
                                                font.pixelSize: info_font_size
                                            }

                                            TextField{
                                                id: ethernet_dnsmain_2
                                                width: 60
                                                height: 40
                                                font.pixelSize: info_font_size
                                                horizontalAlignment: TextField.AlignHCenter
                                                MouseArea{
                                                    anchors.fill:parent
                                                    onClicked: {
                                                        supervisor.playSound('click', slider_volume_button.value);
                                                        if(keypad.is_opened){
                                                            keypad.owner = ethernet_dnsmain_2;
                                                            ethernet_dnsmain_2.selectAll();
                                                        }else{
                                                            keypad.owner = ethernet_dnsmain_2;
                                                            ethernet_dnsmain_2.selectAll();
                                                            keypad.open();
                                                        }
                                                    }
                                                }
                                                color: ischanged?color_red:"black"
                                                property bool ischanged: false
                                                onTextChanged: {
                                                    ischanged = true;
                                                    if(ethernet_dnsmain_2.text == "."){
                                                        ethernet_dnsmain_2.text = ethernet_dnsmain_2.text.split(".")[0]
                                                    }

                                                    if(ethernet_dnsmain_2.text.split(".").length > 1){
                                                        ethernet_dnsmain_2.text = ethernet_dnsmain_2.text.split(".")[0];
                                                        keypad.owner = ethernet_dnsmain_3;
                                                        ethernet_dnsmain_3.selectAll();
                                                    }
                                                    if(ethernet_dnsmain_2.text.length == 3){
                                                        keypad.owner = ethernet_dnsmain_3;
                                                        ethernet_dnsmain_3.selectAll();
                                                    }
                                                }
                                            }
                                            Text{
                                                anchors.verticalCenter: parent.verticalCenter
                                                text:"."
                                                font.pixelSize: info_font_size
                                            }
                                            TextField{
                                                id: ethernet_dnsmain_3
                                                width: 60
                                                font.pixelSize: info_font_size
                                                height: 40
                                                horizontalAlignment: TextField.AlignHCenter
                                                MouseArea{
                                                    anchors.fill:parent
                                                    onClicked: {
                                                        supervisor.playSound('click', slider_volume_button.value);
                                                        if(keypad.is_opened){
                                                            keypad.owner = ethernet_dnsmain_3;
                                                            ethernet_dnsmain_3.selectAll();
                                                        }else{
                                                            keypad.owner = ethernet_dnsmain_3;
                                                            ethernet_dnsmain_3.selectAll();
                                                            keypad.open();
                                                        }
                                                    }
                                                }
                                                color: ischanged?color_red:"black"
                                                property bool ischanged: false
                                                onTextChanged: {
                                                    ischanged = true;
                                                    if(ethernet_dnsmain_3.text == "."){
                                                        ethernet_dnsmain_3.text = ethernet_dnsmain_3.text.split(".")[0]
                                                    }

                                                    if(ethernet_dnsmain_3.text.split(".").length > 1){
                                                        ethernet_dnsmain_3.text = ethernet_dnsmain_3.text.split(".")[0];
                                                        keypad.owner = ethernet_dnsmain_4;
                                                        ethernet_dnsmain_4.selectAll();
                                                    }
                                                    if(ethernet_dnsmain_3.text.length == 3){
                                                        keypad.owner = ethernet_dnsmain_4;
                                                        ethernet_dnsmain_4.selectAll();
                                                    }
                                                }
                                            }
                                            Text{
                                                anchors.verticalCenter: parent.verticalCenter
                                                text:"."
                                                font.pixelSize: info_font_size
                                            }
                                            TextField{
                                                id: ethernet_dnsmain_4
                                                width: 60
                                                height: 40
                                                font.pixelSize: info_font_size
                                                horizontalAlignment: TextField.AlignHCenter
                                                MouseArea{
                                                    anchors.fill:parent
                                                    onClicked: {
                                                        supervisor.playSound('click', slider_volume_button.value);
                                                        if(keypad.is_opened){
                                                            keypad.owner = ethernet_dnsmain_4;
                                                            ethernet_dnsmain_4.selectAll();
                                                        }else{
                                                            keypad.owner = ethernet_dnsmain_4;
                                                            ethernet_dnsmain_4.selectAll();
                                                            keypad.open();
                                                        }
                                                    }
                                                }
                                                color: ischanged?color_red:"black"
                                                property bool ischanged: false
                                                onTextChanged: {
                                                    ischanged = true;
                                                    if(ethernet_dnsmain_4.text == "."){
                                                        ethernet_dnsmain_4.text = ethernet_dnsmain_4.text.split(".")[0]
                                                    }

                                                    if(ethernet_dnsmain_4.text.split(".").length > 1){
                                                        ethernet_dnsmain_4.text = ethernet_dnsmain_4.text.split(".")[0];
                                                        keypad.close();
                                                    }
                                                    if(ethernet_dnsmain_4.text.length == 3){
                                                        keypad.close();
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }

                                Row{
                                    visible: is_admin
                                    spacing: 5
                                    Rectangle{
                                        width: 150
                                        height: setting_height
                                        Text{
                                            anchors.verticalCenter: parent.verticalCenter
                                            anchors.left: parent.left
                                            anchors.leftMargin: 30
                                            font.family: font_noto_r.name
                                            text:qsTr("DNS 2")
                                            font.pixelSize: name_font_size
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
                                        height: setting_height
                                        color: "#d0d0d0"
                                    }

                                    Rectangle{
                                        width: 500-161
                                        height: setting_height
                                        Row{
                                            spacing: 10
                                            anchors.centerIn: parent
                                            TextField{
                                                id: ethernet_dnsserv_1
                                                width: 60
                                                height: 40
                                                font.pixelSize: info_font_size
                                                horizontalAlignment: TextField.AlignHCenter
                                                MouseArea{
                                                    anchors.fill:parent
                                                    onClicked: {
                                                        supervisor.playSound('click', slider_volume_button.value);
                                                        if(keypad.is_opened){
                                                            keypad.owner = ethernet_dnsserv_1;
                                                            ethernet_dnsserv_1.selectAll();
                                                        }else{
                                                            keypad.owner = ethernet_dnsserv_1;
                                                            ethernet_dnsserv_1.selectAll();
                                                            keypad.open();
                                                        }
                                                    }
                                                }

                                                color: ischanged?color_red:"black"
                                                property bool ischanged: false
                                                onTextChanged: {
                                                    ischanged = true;
                                                    if(ethernet_dnsserv_1.text.split(".").length > 1){
                                                        ethernet_dnsserv_1.text = ethernet_dnsserv_1.text.split(".")[0];
                                                        keypad.owner = ethernet_dnsserv_2;
                                                        ethernet_dnsserv_2.selectAll();
                                                    }
                                                    if(ethernet_dnsserv_1.text.length == 3){
                                                        keypad.owner = ethernet_dnsserv_2;
                                                        ethernet_dnsserv_2.selectAll();
                                                    }
                                                }
                                            }
                                            Text{
                                                anchors.verticalCenter: parent.verticalCenter
                                                text:"."
                                                font.pixelSize: info_font_size
                                            }

                                            TextField{
                                                id: ethernet_dnsserv_2
                                                width: 60
                                                height: 40
                                                font.pixelSize: info_font_size
                                                horizontalAlignment: TextField.AlignHCenter
                                                MouseArea{
                                                    anchors.fill:parent
                                                    onClicked: {
                                                        supervisor.playSound('click', slider_volume_button.value);
                                                        if(keypad.is_opened){
                                                            keypad.owner = ethernet_dnsserv_2;
                                                            ethernet_dnsserv_2.selectAll();
                                                        }else{
                                                            keypad.owner = ethernet_dnsserv_2;
                                                            ethernet_dnsserv_2.selectAll();
                                                            keypad.open();
                                                        }
                                                    }
                                                }
                                                color: ischanged?color_red:"black"
                                                property bool ischanged: false
                                                onTextChanged: {
                                                    ischanged = true;
                                                    if(ethernet_dnsserv_2.text == "."){
                                                        ethernet_dnsserv_2.text = ethernet_dnsserv_2.text.split(".")[0]
                                                    }

                                                    if(ethernet_dnsserv_2.text.split(".").length > 1){
                                                        ethernet_dnsserv_2.text = ethernet_dnsserv_2.text.split(".")[0];
                                                        keypad.owner = ethernet_dnsserv_3;
                                                        ethernet_dnsserv_3.selectAll();
                                                    }
                                                    if(ethernet_dnsserv_2.text.length == 3){
                                                        keypad.owner = ethernet_dnsserv_3;
                                                        ethernet_dnsserv_3.selectAll();
                                                    }
                                                }
                                            }
                                            Text{
                                                anchors.verticalCenter: parent.verticalCenter
                                                text:"."
                                                font.pixelSize: info_font_size
                                            }
                                            TextField{
                                                id: ethernet_dnsserv_3
                                                width: 60
                                                font.pixelSize: info_font_size
                                                height: 40
                                                horizontalAlignment: TextField.AlignHCenter
                                                MouseArea{
                                                    anchors.fill:parent
                                                    onClicked: {
                                                        supervisor.playSound('click', slider_volume_button.value);
                                                        if(keypad.is_opened){
                                                            keypad.owner = ethernet_dnsserv_3;
                                                            ethernet_dnsserv_3.selectAll();
                                                        }else{
                                                            keypad.owner = ethernet_dnsserv_3;
                                                            ethernet_dnsserv_3.selectAll();
                                                            keypad.open();
                                                        }
                                                    }
                                                }
                                                color: ischanged?color_red:"black"
                                                property bool ischanged: false
                                                onTextChanged: {
                                                    ischanged = true;
                                                    if(ethernet_dnsserv_3.text == "."){
                                                        ethernet_dnsserv_3.text = ethernet_dnsserv_3.text.split(".")[0]
                                                    }

                                                    if(ethernet_dnsserv_3.text.split(".").length > 1){
                                                        ethernet_dnsserv_3.text = ethernet_dnsserv_3.text.split(".")[0];
                                                        keypad.owner = ethernet_dnsserv_4;
                                                        ethernet_dnsserv_4.selectAll();
                                                    }
                                                    if(ethernet_dnsserv_3.text.length == 3){
                                                        keypad.owner = ethernet_dnsserv_4;
                                                        ethernet_dnsserv_4.selectAll();
                                                    }
                                                }
                                            }
                                            Text{
                                                anchors.verticalCenter: parent.verticalCenter
                                                text:"."
                                                font.pixelSize: info_font_size
                                            }
                                            TextField{
                                                id: ethernet_dnsserv_4
                                                width: 60
                                                height: 40
                                                font.pixelSize: info_font_size
                                                horizontalAlignment: TextField.AlignHCenter
                                                MouseArea{
                                                    anchors.fill:parent
                                                    onClicked: {
                                                        supervisor.playSound('click', slider_volume_button.value);
                                                        if(keypad.is_opened){
                                                            keypad.owner = ethernet_dnsserv_4;
                                                            ethernet_dnsserv_4.selectAll();
                                                        }else{
                                                            keypad.owner = ethernet_dnsserv_4;
                                                            ethernet_dnsserv_4.selectAll();
                                                            keypad.open();
                                                        }
                                                    }
                                                }
                                                color: ischanged?color_red:"black"
                                                property bool ischanged: false
                                                onTextChanged: {
                                                    ischanged = true;
                                                    if(ethernet_dnsserv_4.text == "."){
                                                        ethernet_dnsserv_4.text = ethernet_dnsserv_4.text.split(".")[0]
                                                    }

                                                    if(ethernet_dnsserv_4.text.split(".").length > 1){
                                                        ethernet_dnsserv_4.text = ethernet_dnsserv_4.text.split(".")[0];
                                                        keypad.close();
                                                    }
                                                    if(ethernet_dnsserv_4.text.length == 3){
                                                        keypad.close();
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }

                                Row{
                                    visible: is_admin
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    spacing: 30
                                    Item_buttons{
                                        type: "white_btn"
                                        text:qsTr("변경값적용")
                                        width: 150
                                        height: 50
                                        function check(str){
                                            var num = parseInt(str);
                                            if(num === 0){
                                                if(str === "0"){
                                                    return true;
                                                }else{
                                                    return false;
                                                }
                                            }else if(num === 128 || num === 192 || num === 224 || num === 240 || num === 248 || num === 252 || num === 254 || num === 255){
                                                return true;
                                            }else{
                                                return false;
                                            }
                                        }

                                        onClicked:{
                                            var success = true;
                                            //check value
                                            if(parseInt(ethernet_ip_1.text)>-1 && parseInt(ethernet_ip_1.text)<256){
                                                if(parseInt(ethernet_ip_2.text)>-1 && parseInt(ethernet_ip_2.text)<256){
                                                    if(parseInt(ethernet_ip_3.text)>-1 && parseInt(ethernet_ip_3.text)<256){
                                                        if(parseInt(ethernet_ip_4.text)>-1 && parseInt(ethernet_ip_4.text)<256){

                                                        }else{
                                                            ethernet_ip_4.color = color_red
                                                            success = false;
                                                        }
                                                    }else{
                                                        ethernet_ip_3.color = color_red
                                                        success = false;
                                                    }
                                                }else{
                                                    ethernet_ip_2.color = color_red
                                                    success = false;
                                                }
                                            }else{
                                                ethernet_ip_1.color = color_red
                                                success = false;
                                            }

                                            if(parseInt(ethernet_gateway_1.text)>-1 && parseInt(ethernet_gateway_1.text)<256){
                                                if(parseInt(ethernet_gateway_2.text)>-1 && parseInt(ethernet_gateway_2.text)<256){
                                                    if(parseInt(ethernet_gateway_3.text)>-1 && parseInt(ethernet_gateway_3.text)<256){
                                                        if(parseInt(ethernet_gateway_4.text)>-1 && parseInt(ethernet_gateway_4.text)<256){

                                                        }else{
                                                            ethernet_gateway_4.color = color_red
                                                            success = false;
                                                        }
                                                    }else{
                                                        ethernet_gateway_3.color = color_red
                                                        success = false;
                                                    }
                                                }else{
                                                    ethernet_gateway_2.color = color_red
                                                    success = false;
                                                }
                                            }else{
                                                ethernet_gateway_1.color = color_red
                                                success = false;
                                            }

                                            if(parseInt(ethernet_dnsmain_1.text)>-1 && parseInt(ethernet_dnsmain_1.text)<256){
                                                if(parseInt(ethernet_dnsmain_2.text)>-1 && parseInt(ethernet_dnsmain_2.text)<256){
                                                    if(parseInt(ethernet_dnsmain_3.text)>-1 && parseInt(ethernet_dnsmain_3.text)<256){
                                                        if(parseInt(ethernet_dnsmain_4.text)>-1 && parseInt(ethernet_dnsmain_4.text)<256){

                                                        }else{
                                                            ethernet_dnsmain_4.color = color_red
                                                            success = false;
                                                        }
                                                    }else{
                                                        ethernet_dnsmain_3.color = color_red
                                                        success = false;
                                                    }
                                                }else{
                                                    ethernet_dnsmain_2.color = color_red
                                                    success = false;
                                                }
                                            }else{
                                                ethernet_dnsmain_1.color = color_red
                                                success = false;
                                            }

                                            if(check(ethernet_netmask_1.text)){
                                                if(ethernet_netmask_1.text == "255"){
                                                    if(check(ethernet_netmask_2.text)){
                                                        if(ethernet_netmask_2.text == "255"){
                                                            if(check(ethernet_netmask_3.text)){
                                                                if(ethernet_netmask_3.text == "255"){
                                                                    if(check(ethernet_netmask_4.text)){

                                                                    }else{
                                                                        ethernet_netmask_4.color = color_red;
                                                                        success = false;
                                                                    }
                                                                }else{
                                                                    if(ethernet_netmask_4.text === "0"){

                                                                    }else{
                                                                        ethernet_netmask_4.color = color_red;
                                                                        success = false;
                                                                    }
                                                                }
                                                            }else{
                                                                ethernet_netmask_3.color = color_red;
                                                                success = false;
                                                            }
                                                        }else{
                                                            if(ethernet_netmask_3.text === "0"){
                                                                if(ethernet_netmask_4.text === "0"){

                                                                }else{
                                                                    ethernet_netmask_4.color = color_red;
                                                                    success = false;
                                                                }
                                                            }else{
                                                                ethernet_netmask_3.color = color_red;
                                                                success = false;
                                                            }
                                                        }
                                                    }else{
                                                        ethernet_netmask_2.color = color_red;
                                                        success = false;
                                                    }
                                                }else{
                                                    if(ethernet_netmask_2.text === "0"){
                                                        if(ethernet_netmask_3.text === "0"){
                                                            if(ethernet_netmask_4.text === "0"){

                                                            }else{
                                                                ethernet_netmask_4.color = color_red;
                                                                success = false;
                                                            }
                                                        }else{
                                                            ethernet_netmask_3.color = color_red;
                                                            success = false;
                                                        }
                                                    }else{
                                                        ethernet_netmask_2.color = color_red;
                                                        success = false;
                                                    }
                                                }
                                            }else{
                                                ethernet_netmask_1.color = color_red
                                                success = false;
                                            }


                                            if(success){
                                                supervisor.playSound('click', slider_volume_button.value);
                                                ethernet_ip_1.ischanged = false;
                                                ethernet_ip_2.ischanged = false;
                                                ethernet_ip_3.ischanged = false;
                                                ethernet_ip_4.ischanged = false;
                                                ethernet_netmask_1.ischanged = false;
                                                ethernet_netmask_2.ischanged = false;
                                                ethernet_netmask_3.ischanged = false;
                                                ethernet_netmask_4.ischanged = false;
                                                ethernet_gateway_1.ischanged = false;
                                                ethernet_gateway_2.ischanged = false;
                                                ethernet_gateway_3.ischanged = false;
                                                ethernet_gateway_4.ischanged = false;
                                                ethernet_dnsmain_1.ischanged = false;
                                                ethernet_dnsmain_2.ischanged = false;
                                                ethernet_dnsmain_3.ischanged = false;
                                                ethernet_dnsmain_4.ischanged = false;
                                                ethernet_dnsserv_1.ischanged = false;
                                                ethernet_dnsserv_2.ischanged = false;
                                                ethernet_dnsserv_3.ischanged = false;
                                                ethernet_dnsserv_4.ischanged = false;
                                                var ip_str = ethernet_ip_1.text + "." + ethernet_ip_2.text + "." + ethernet_ip_3.text + "." + ethernet_ip_4.text;
                                                var netmask_str = ethernet_netmask_1.text + "." + ethernet_netmask_2.text + "." + ethernet_netmask_3.text + "." + ethernet_netmask_4.text;
                                                var gateway_str = ethernet_gateway_1.text + "." + ethernet_gateway_2.text + "." + ethernet_gateway_3.text + "." + ethernet_gateway_4.text;
                                                var dns1_str = ethernet_dnsmain_1.text===""?"":ethernet_dnsmain_1.text + "." + ethernet_dnsmain_2.text + "." + ethernet_dnsmain_3.text + "." + ethernet_dnsmain_4.text;
                                                var dns2_str = ethernet_dnsserv_1.text===""?"":ethernet_dnsserv_1.text + "." + ethernet_dnsserv_2.text + "." + ethernet_dnsserv_3.text + "." + ethernet_dnsserv_4.text;
                                                supervisor.setEthernet(ip_str, netmask_str, gateway_str,dns1_str,dns2_str);
                                            }else{
                                                supervisor.playSound('no', slider_volume_button.value);
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                Rectangle{
                    id: set_wifi
                    width: 840
                    height: is_admin?600:setting_height*2+10
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
                                text:qsTr("무선 연결상태")
                                font.pixelSize: name_font_size
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                    anchors.leftMargin = 30 - width*(1-scale)/2
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
                                spacing: 6
                                Rectangle{
                                    id: wifi_con
                                    width: 500
                                    height: setting_height
                                    property int connection: 0
                                    color: {
                                        if(wifi_con.connection === 1){
                                            color_yellow
                                        }else if(wifi_con.connection === 2){
                                            color_green
                                        }else{
                                            color_red
                                        }
                                    }
                                    Text{
                                        anchors.centerIn: parent
                                        font.family:font_noto_r.name
                                        font.pixelSize:info_font_size
                                        text:{
                                            if(wifi_con.connection === 1){
                                                qsTr("연결중")
                                            }else if(wifi_con.connection === 2){
                                                qsTr("연결됨")
                                            }else{
                                                qsTr("연결안됨")
                                            }
                                        }
                                        color: "white"
                                    }
                                }

                                Row{
                                    spacing: 5
                                    Rectangle{
                                        width: 150
                                        height: setting_height
                                        Text{
                                            anchors.verticalCenter: parent.verticalCenter
                                            anchors.left: parent.left
                                            anchors.leftMargin: 30
                                            font.family: font_noto_r.name
                                            text:qsTr("WIFI SSID")
                                            font.pixelSize: name_font_size
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
                                        height: setting_height
                                        color: "#d0d0d0"
                                    }
                                    Rectangle{
                                        width: 500-161
                                        height: setting_height
                                        Text{
                                            id: wifi_ssid
                                            font.pixelSize: info_font_size
                                            anchors.centerIn: parent
                                            font.family: font_noto_r.name
                                            text:supervisor.getSetting("setting","NETWORK","wifi_ssid");
                                        }
                                    }
                                }
                                Row{
                                    visible: is_admin
                                    spacing: 5
                                    Rectangle{
                                        width: 150
                                        height: setting_height
                                        Text{
                                            anchors.verticalCenter: parent.verticalCenter
                                            anchors.left: parent.left
                                            anchors.leftMargin: 30
                                            font.family: font_noto_r.name
                                            text:qsTr("IP")
                                            font.pixelSize: name_font_size
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
                                        height: setting_height
                                        color: "#d0d0d0"
                                    }

                                    Rectangle{
                                        width: 500-161
                                        height: setting_height
                                        Row{
                                            spacing: 10
                                            anchors.centerIn: parent
                                            TextField{
                                                id: ip_1
                                                width: 60
                                                height: 40
                                                font.pixelSize: info_font_size
                                                horizontalAlignment: TextField.AlignHCenter
                                                MouseArea{
                                                    anchors.fill:parent
                                                    onClicked: {
                                                        supervisor.playSound('click', slider_volume_button.value);
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
                                                font.pixelSize: info_font_size
                                            }

                                            TextField{
                                                id: ip_2
                                                width: 60
                                                font.pixelSize: info_font_size
                                                height: 40
                                                horizontalAlignment: TextField.AlignHCenter
                                                MouseArea{
                                                    anchors.fill:parent
                                                    onClicked: {
                                                        supervisor.playSound('click', slider_volume_button.value);
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
                                                font.pixelSize: info_font_size
                                            }
                                            TextField{
                                                id: ip_3
                                                width: 60
                                                height: 40
                                                font.pixelSize: info_font_size
                                                horizontalAlignment: TextField.AlignHCenter
                                                MouseArea{
                                                    anchors.fill:parent
                                                    onClicked: {
                                                        supervisor.playSound('click', slider_volume_button.value);
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
                                                font.pixelSize: info_font_size
                                            }
                                            TextField{
                                                id: ip_4
                                                width: 60
                                                font.pixelSize: info_font_size
                                                height: 40
                                                horizontalAlignment: TextField.AlignHCenter
                                                MouseArea{
                                                    anchors.fill:parent
                                                    onClicked: {
                                                        supervisor.playSound('click', slider_volume_button.value);
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

                                        }
                                    }
                                }

                                Row{
                                    visible: is_admin
                                    spacing: 5
                                    Rectangle{
                                        width: 150
                                        height: setting_height
                                        Text{
                                            anchors.verticalCenter: parent.verticalCenter
                                            anchors.left: parent.left
                                            anchors.leftMargin: 30
                                            font.family: font_noto_r.name
                                            text:qsTr("Netmask")
                                            font.pixelSize: name_font_size
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
                                        height: setting_height
                                        color: "#d0d0d0"
                                    }

                                    Rectangle{
                                        width: 500-161
                                        height: setting_height
                                        Row{
                                            spacing: 10
                                            anchors.centerIn: parent
                                            TextField{
                                                id: netmask_1
                                                width: 60
                                                height: 40
                                                font.pixelSize: info_font_size
                                                horizontalAlignment: TextField.AlignHCenter
                                                MouseArea{
                                                    anchors.fill:parent
                                                    onClicked: {
                                                        supervisor.playSound('click', slider_volume_button.value);
                                                        if(keypad.is_opened){
                                                            keypad.owner = netmask_1;
                                                            netmask_1.selectAll();
                                                        }else{
                                                            keypad.owner = netmask_1;
                                                            netmask_1.selectAll();
                                                            keypad.open();
                                                        }
                                                    }
                                                }
                                                onIschangedChanged: {
                                                    color = ischanged?color_red:"black"
                                                }
                                                color: ischanged?color_red:"black"
                                                property bool ischanged: false
                                                onTextChanged: {
                                                    ischanged = true;
                                                    if(netmask_1.text.split(".").length > 1){
                                                        netmask_1.text = netmask_1.text.split(".")[0];
                                                        keypad.owner = netmask_2;
                                                        netmask_2.selectAll();
                                                    }
                                                    if(netmask_1.text.length == 3){
                                                        keypad.owner = netmask_2;
                                                        netmask_2.selectAll();
                                                    }
                                                }
                                            }
                                            Text{
                                                font.pixelSize: info_font_size
                                                anchors.verticalCenter: parent.verticalCenter
                                                text:"."
                                            }

                                            TextField{
                                                id: netmask_2
                                                font.pixelSize: info_font_size
                                                width: 60
                                                height: 40
                                                horizontalAlignment: TextField.AlignHCenter
                                                MouseArea{
                                                    anchors.fill:parent
                                                    onClicked: {
                                                        supervisor.playSound('click', slider_volume_button.value);
                                                        if(keypad.is_opened){
                                                            keypad.owner = netmask_2;
                                                            netmask_2.selectAll();
                                                        }else{
                                                            keypad.owner = netmask_2;
                                                            netmask_2.selectAll();
                                                            keypad.open();
                                                        }
                                                    }
                                                }
                                                onIschangedChanged: {
                                                    color = ischanged?color_red:"black"
                                                }
                                                color: ischanged?color_red:"black"
                                                property bool ischanged: false
                                                onTextChanged: {
                                                    ischanged = true;
                                                    if(netmask_2.text == "."){
                                                        netmask_2.text = netmask_2.text.split(".")[0]
                                                    }

                                                    if(netmask_2.text.split(".").length > 1){
                                                        netmask_2.text = netmask_2.text.split(".")[0];
                                                        keypad.owner = netmask_3;
                                                        netmask_3.selectAll();
                                                    }
                                                    if(netmask_2.text.length == 3){
                                                        keypad.owner = netmask_3;
                                                        netmask_3.selectAll();
                                                    }
                                                }
                                            }
                                            Text{
                                                anchors.verticalCenter: parent.verticalCenter
                                                text:"."
                                                font.pixelSize: info_font_size
                                            }
                                            TextField{
                                                id: netmask_3
                                                width: 60
                                                height: 40
                                                font.pixelSize: info_font_size
                                                horizontalAlignment: TextField.AlignHCenter
                                                MouseArea{
                                                    anchors.fill:parent
                                                    onClicked: {
                                                        supervisor.playSound('click', slider_volume_button.value);
                                                        if(keypad.is_opened){
                                                            keypad.owner = netmask_3;
                                                            netmask_3.selectAll();
                                                        }else{
                                                            keypad.owner = netmask_3;
                                                            netmask_3.selectAll();
                                                            keypad.open();
                                                        }
                                                    }
                                                }
                                                color: ischanged?color_red:"black"
                                                property bool ischanged: false
                                                onIschangedChanged: {
                                                    color = ischanged?color_red:"black"
                                                }
                                                onTextChanged: {
                                                    ischanged = true;
                                                    if(netmask_3.text == "."){
                                                        netmask_3.text = netmask_3.text.split(".")[0]
                                                    }

                                                    if(netmask_3.text.split(".").length > 1){
                                                        netmask_3.text = netmask_3.text.split(".")[0];
                                                        keypad.owner = netmask_4;
                                                        netmask_4.selectAll();
                                                    }
                                                    if(netmask_3.text.length == 3){
                                                        keypad.owner = netmask_4;
                                                        netmask_4.selectAll();
                                                    }
                                                }
                                            }
                                            Text{
                                                anchors.verticalCenter: parent.verticalCenter
                                                text:"."
                                                font.pixelSize: info_font_size
                                            }
                                            TextField{
                                                id: netmask_4
                                                width: 60
                                                height: 40
                                                font.pixelSize: info_font_size
                                                horizontalAlignment: TextField.AlignHCenter
                                                MouseArea{
                                                    anchors.fill:parent
                                                    onClicked: {
                                                        supervisor.playSound('click', slider_volume_button.value);
                                                        if(keypad.is_opened){
                                                            keypad.owner = netmask_4;
                                                            netmask_4.selectAll();
                                                        }else{
                                                            keypad.owner = netmask_4;
                                                            netmask_4.selectAll();
                                                            keypad.open();
                                                        }
                                                    }
                                                }
                                                color: ischanged?color_red:"black"
                                                property bool ischanged: false
                                                onIschangedChanged: {
                                                    color = ischanged?color_red:"black"
                                                }
                                                onTextChanged: {
                                                    ischanged = true;
                                                    if(netmask_4.text == "."){
                                                        netmask_4.text = netmask_4.text.split(".")[0]
                                                    }

                                                    if(netmask_4.text.split(".").length > 1){
                                                        netmask_4.text = netmask_4.text.split(".")[0];
                                                        keypad.close();
                                                    }
                                                    if(netmask_4.text.length == 3){
                                                        keypad.close();
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }



                                Row{
                                    spacing: 5
                                    visible: is_admin
                                    Rectangle{
                                        width: 150
                                        height: setting_height
                                        Text{
                                            anchors.verticalCenter: parent.verticalCenter
                                            anchors.left: parent.left
                                            anchors.leftMargin: 30
                                            font.family: font_noto_r.name
                                            text:qsTr("Gateway")
                                            font.pixelSize: name_font_size
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
                                        height: setting_height
                                        color: "#d0d0d0"
                                    }

                                    Rectangle{
                                        width: 500-161
                                        height: setting_height
                                        Row{
                                            spacing: 10
                                            anchors.centerIn: parent
                                            TextField{
                                                id: gateway_1
                                                width: 60
                                                height: 40
                                                font.pixelSize: info_font_size
                                                horizontalAlignment: TextField.AlignHCenter
                                                MouseArea{
                                                    anchors.fill:parent
                                                    onClicked: {
                                                        supervisor.playSound('click', slider_volume_button.value);
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
                                                font.pixelSize: info_font_size
                                            }

                                            TextField{
                                                id: gateway_2
                                                width: 60
                                                font.pixelSize: info_font_size
                                                height: 40
                                                horizontalAlignment: TextField.AlignHCenter
                                                MouseArea{
                                                    anchors.fill:parent
                                                    onClicked: {
                                                        supervisor.playSound('click', slider_volume_button.value);
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
                                                font.pixelSize: info_font_size
                                            }
                                            TextField{
                                                id: gateway_3
                                                width: 60
                                                height: 40
                                                font.pixelSize: info_font_size
                                                horizontalAlignment: TextField.AlignHCenter
                                                MouseArea{
                                                    anchors.fill:parent
                                                    onClicked: {
                                                        supervisor.playSound('click', slider_volume_button.value);
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
                                                font.pixelSize: info_font_size
                                            }
                                            TextField{
                                                id: gateway_4
                                                width: 60
                                                height: 40
                                                font.pixelSize: info_font_size
                                                horizontalAlignment: TextField.AlignHCenter
                                                MouseArea{
                                                    anchors.fill:parent
                                                    onClicked: {
                                                        supervisor.playSound('click', slider_volume_button.value);
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
                                        }
                                    }
                                }


                                Row{
                                    spacing: 5
                                    visible: is_admin
                                    Rectangle{
                                        width: 150
                                        height: setting_height
                                        Text{
                                            anchors.verticalCenter: parent.verticalCenter
                                            anchors.left: parent.left
                                            anchors.leftMargin: 30
                                            font.family: font_noto_r.name
                                            text:qsTr("DNS 1")
                                            font.pixelSize: name_font_size
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
                                        height: setting_height
                                        color: "#d0d0d0"
                                    }

                                    Rectangle{
                                        width: 500-161
                                        height: setting_height
                                        Row{
                                            spacing: 10
                                            anchors.centerIn: parent
                                            TextField{
                                                id: dnsmain_1
                                                width: 60
                                                height: 40
                                                font.pixelSize: info_font_size
                                                horizontalAlignment: TextField.AlignHCenter
                                                MouseArea{
                                                    anchors.fill:parent
                                                    onClicked: {
                                                        supervisor.playSound('click', slider_volume_button.value);
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
                                                font.pixelSize: info_font_size
                                            }

                                            TextField{
                                                id: dnsmain_2
                                                width: 60
                                                font.pixelSize: info_font_size
                                                height: 40
                                                horizontalAlignment: TextField.AlignHCenter
                                                MouseArea{
                                                    anchors.fill:parent
                                                    onClicked: {
                                                        supervisor.playSound('click', slider_volume_button.value);
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
                                                font.pixelSize: info_font_size
                                            }
                                            TextField{
                                                id: dnsmain_3
                                                width: 60
                                                height: 40
                                                font.pixelSize: info_font_size
                                                horizontalAlignment: TextField.AlignHCenter
                                                MouseArea{
                                                    anchors.fill:parent
                                                    onClicked: {
                                                        supervisor.playSound('click', slider_volume_button.value);
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
                                                font.pixelSize: info_font_size
                                            }
                                            TextField{
                                                id: dnsmain_4
                                                width: 60
                                                height: 40
                                                font.pixelSize: info_font_size
                                                horizontalAlignment: TextField.AlignHCenter
                                                MouseArea{
                                                    anchors.fill:parent
                                                    onClicked: {
                                                        supervisor.playSound('click', slider_volume_button.value);
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
                                        }
                                    }
                                }

                                Row{
                                    spacing: 5
                                    visible: is_admin
                                    Rectangle{
                                        width: 150
                                        height: setting_height
                                        Text{
                                            anchors.verticalCenter: parent.verticalCenter
                                            anchors.left: parent.left
                                            anchors.leftMargin: 30
                                            font.family: font_noto_r.name
                                            text:qsTr("DNS 2")
                                            font.pixelSize: name_font_size
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
                                        height: setting_height
                                        color: "#d0d0d0"
                                    }

                                    Rectangle{
                                        width: 500-161
                                        height: setting_height
                                        Row{
                                            spacing: 10
                                            anchors.centerIn: parent
                                            TextField{
                                                id: dnsserv_1
                                                width: 60
                                                height: 40
                                                font.pixelSize: info_font_size
                                                horizontalAlignment: TextField.AlignHCenter
                                                MouseArea{
                                                    anchors.fill:parent
                                                    onClicked: {
                                                        supervisor.playSound('click', slider_volume_button.value);
                                                        if(keypad.is_opened){
                                                            keypad.owner = dnsserv_1;
                                                            dnsserv_1.selectAll();
                                                        }else{
                                                            keypad.owner = dnsserv_1;
                                                            dnsserv_1.selectAll();
                                                            keypad.open();
                                                        }
                                                    }
                                                }
                                                color: ischanged?color_red:"black"
                                                property bool ischanged: false
                                                onTextChanged: {
                                                    ischanged = true;
                                                    if(dnsserv_1.text.split(".").length > 1){
                                                        dnsserv_1.text = dnsserv_1.text.split(".")[0];
                                                        keypad.owner = dnsserv_2;
                                                        dnsserv_2.selectAll();
                                                    }
                                                    if(dnsserv_1.text.length == 3){
                                                        keypad.owner = dnsserv_2;
                                                        dnsserv_2.selectAll();
                                                    }
                                                }
                                            }
                                            Text{
                                                anchors.verticalCenter: parent.verticalCenter
                                                text:"."
                                                font.pixelSize: info_font_size
                                            }

                                            TextField{
                                                id: dnsserv_2
                                                width: 60
                                                height: 40
                                                font.pixelSize: info_font_size
                                                horizontalAlignment: TextField.AlignHCenter
                                                MouseArea{
                                                    anchors.fill:parent
                                                    onClicked: {
                                                        supervisor.playSound('click', slider_volume_button.value);
                                                        if(keypad.is_opened){
                                                            keypad.owner = dnsserv_2;
                                                            dnsserv_2.selectAll();
                                                        }else{
                                                            keypad.owner = dnsserv_2;
                                                            dnsserv_2.selectAll();
                                                            keypad.open();
                                                        }
                                                    }
                                                }
                                                color: ischanged?color_red:"black"
                                                property bool ischanged: false
                                                onTextChanged: {
                                                    ischanged = true;
                                                    if(dnsserv_2.text == "."){
                                                        dnsserv_2.text = dnsserv_2.text.split(".")[0]
                                                    }

                                                    if(dnsserv_2.text.split(".").length > 1){
                                                        dnsserv_2.text = dnsserv_2.text.split(".")[0];
                                                        keypad.owner = dnsserv_3;
                                                        dnsserv_3.selectAll();
                                                    }
                                                    if(dnsserv_2.text.length == 3){
                                                        keypad.owner = dnsserv_3;
                                                        dnsserv_3.selectAll();
                                                    }
                                                }
                                            }
                                            Text{
                                                anchors.verticalCenter: parent.verticalCenter
                                                text:"."
                                                font.pixelSize: info_font_size
                                            }
                                            TextField{
                                                id: dnsserv_3
                                                width: 60
                                                height: 40
                                                font.pixelSize: info_font_size
                                                horizontalAlignment: TextField.AlignHCenter
                                                MouseArea{
                                                    anchors.fill:parent
                                                    onClicked: {
                                                        supervisor.playSound('click', slider_volume_button.value);
                                                        if(keypad.is_opened){
                                                            keypad.owner = dnsserv_3;
                                                            dnsserv_3.selectAll();
                                                        }else{
                                                            keypad.owner = dnsserv_3;
                                                            dnsserv_3.selectAll();
                                                            keypad.open();
                                                        }
                                                    }
                                                }
                                                color: ischanged?color_red:"black"
                                                property bool ischanged: false
                                                onTextChanged: {
                                                    ischanged = true;
                                                    if(dnsserv_3.text == "."){
                                                        dnsserv_3.text = dnsserv_3.text.split(".")[0]
                                                    }

                                                    if(dnsserv_3.text.split(".").length > 1){
                                                        dnsserv_3.text = dnsserv_3.text.split(".")[0];
                                                        keypad.owner = dnsserv_4;
                                                        dnsserv_4.selectAll();
                                                    }
                                                    if(dnsserv_3.text.length == 3){
                                                        keypad.owner = dnsserv_4;
                                                        dnsserv_4.selectAll();
                                                    }
                                                }
                                            }
                                            Text{
                                                anchors.verticalCenter: parent.verticalCenter
                                                text:"."
                                                font.pixelSize: info_font_size
                                            }
                                            TextField{
                                                id: dnsserv_4
                                                width: 60
                                                height: 40
                                                font.pixelSize: info_font_size
                                                horizontalAlignment: TextField.AlignHCenter
                                                MouseArea{
                                                    anchors.fill:parent
                                                    onClicked: {
                                                        supervisor.playSound('click', slider_volume_button.value);
                                                        if(keypad.is_opened){
                                                            keypad.owner = dnsserv_4;
                                                            dnsserv_4.selectAll();
                                                        }else{
                                                            keypad.owner = dnsserv_4;
                                                            dnsserv_4.selectAll();
                                                            keypad.open();
                                                        }
                                                    }
                                                }
                                                color: ischanged?color_red:"black"
                                                property bool ischanged: false
                                                onTextChanged: {
                                                    ischanged = true;
                                                    if(dnsserv_4.text == "."){
                                                        dnsserv_4.text = dnsserv_4.text.split(".")[0]
                                                    }

                                                    if(dnsserv_4.text.split(".").length > 1){
                                                        dnsserv_4.text = dnsserv_4.text.split(".")[0];
                                                        keypad.close();
                                                    }
                                                    if(dnsserv_4.text.length == 3){
                                                        keypad.close();
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }

                                Row{
                                    visible: is_admin
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    spacing: 30
                                    Item_buttons{
                                        type: "white_btn"
                                        text:qsTr("WIFI선택")
                                        width: 150
                                        height: 50
                                        onClicked:{
                                            popup_wifi.open();
                                        }
                                    }
                                    Item_buttons{
                                        type: "white_btn"
                                        text:qsTr("변경값적용")
                                        width: 150
                                        height: 50
                                        function check(str){
                                            var num = parseInt(str);
                                            if(num === 0){
                                                if(str === "0"){
                                                    return true;
                                                }else{
                                                    return false;
                                                }
                                            }else if(num === 128 || num === 192 || num === 224 || num === 240 || num === 248 || num === 252 || num === 254 || num === 255){
                                                return true;
                                            }else{
                                                return false;
                                            }
                                        }

                                        onClicked:{
                                            var success = true;
                                            if(parseInt(ip_1.text)>-1 && parseInt(ip_1.text)<256){
                                                if(parseInt(ip_2.text)>-1 && parseInt(ip_2.text)<256){
                                                    if(parseInt(ip_3.text)>-1 && parseInt(ip_3.text)<256){
                                                        if(parseInt(ip_4.text)>-1 && parseInt(ip_4.text)<256){

                                                        }else{
                                                            ip_4.color = color_red
                                                            success = false;
                                                        }
                                                    }else{
                                                        ip_3.color = color_red
                                                        success = false;
                                                    }
                                                }else{
                                                    ip_2.color = color_red
                                                    success = false;
                                                }
                                            }else{
                                                ip_1.color = color_red
                                                success = false;
                                            }

                                            if(parseInt(gateway_1.text)>-1 && parseInt(gateway_1.text)<256){
                                                if(parseInt(gateway_2.text)>-1 && parseInt(gateway_2.text)<256){
                                                    if(parseInt(gateway_3.text)>-1 && parseInt(gateway_3.text)<256){
                                                        if(parseInt(gateway_4.text)>-1 && parseInt(gateway_4.text)<256){

                                                        }else{
                                                            gateway_4.color = color_red
                                                            success = false;
                                                        }
                                                    }else{
                                                        gateway_3.color = color_red
                                                        success = false;
                                                    }
                                                }else{
                                                    gateway_2.color = color_red
                                                    success = false;
                                                }
                                            }else{
                                                gateway_1.color = color_red
                                                success = false;
                                            }

                                            if(parseInt(dnsmain_1.text)>-1 && parseInt(dnsmain_1.text)<256){
                                                if(parseInt(dnsmain_2.text)>-1 && parseInt(dnsmain_2.text)<256){
                                                    if(parseInt(dnsmain_3.text)>-1 && parseInt(dnsmain_3.text)<256){
                                                        if(parseInt(dnsmain_4.text)>-1 && parseInt(dnsmain_4.text)<256){

                                                        }else{
                                                            dnsmain_4.color = color_red
                                                            success = false;
                                                        }
                                                    }else{
                                                        dnsmain_3.color = color_red
                                                        success = false;
                                                    }
                                                }else{
                                                    dnsmain_2.color = color_red
                                                    success = false;
                                                }
                                            }else{
                                                dnsmain_1.color = color_red
                                                success = false;
                                            }

                                            if(check(netmask_1.text)){
                                                if(netmask_1.text == "255"){
                                                    if(check(netmask_2.text)){
                                                        if(netmask_2.text == "255"){
                                                            if(check(netmask_3.text)){
                                                                if(netmask_3.text == "255"){
                                                                    if(check(netmask_4.text)){

                                                                    }else{
                                                                        netmask_4.color = color_red;
                                                                        success = false;
                                                                    }
                                                                }else{
                                                                    if(netmask_4.text === "0"){

                                                                    }else{
                                                                        netmask_4.color = color_red;
                                                                        success = false;
                                                                    }
                                                                }
                                                            }else{
                                                                netmask_3.color = color_red;
                                                                success = false;
                                                            }
                                                        }else{
                                                            if(netmask_3.text === "0"){
                                                                if(netmask_4.text === "0"){

                                                                }else{
                                                                    netmask_4.color = color_red;
                                                                    success = false;
                                                                }
                                                            }else{
                                                                netmask_3.color = color_red;
                                                                success = false;
                                                            }
                                                        }
                                                    }else{
                                                        netmask_2.color = color_red;
                                                        success = false;
                                                    }
                                                }else{
                                                    if(netmask_2.text === "0"){
                                                        if(netmask_3.text === "0"){
                                                            if(netmask_4.text === "0"){

                                                            }else{
                                                                netmask_4.color = color_red;
                                                                success = false;
                                                            }
                                                        }else{
                                                            netmask_3.color = color_red;
                                                            success = false;
                                                        }
                                                    }else{
                                                        netmask_2.color = color_red;
                                                        success = false;
                                                    }
                                                }
                                            }else{
                                                netmask_1.color = color_red
                                                success = false;
                                            }


                                            if(success){
                                                ip_1.ischanged = false;
                                                ip_2.ischanged = false;
                                                ip_3.ischanged = false;
                                                ip_4.ischanged = false;
                                                netmask_1.ischanged = false;
                                                netmask_2.ischanged = false;
                                                netmask_3.ischanged = false;
                                                netmask_4.ischanged = false;
                                                gateway_1.ischanged = false;
                                                gateway_2.ischanged = false;
                                                gateway_3.ischanged = false;
                                                gateway_4.ischanged = false;
                                                dnsmain_1.ischanged = false;
                                                dnsmain_2.ischanged = false;
                                                dnsmain_3.ischanged = false;
                                                dnsmain_4.ischanged = false;
                                                dnsserv_1.ischanged = false;
                                                dnsserv_2.ischanged = false;
                                                dnsserv_3.ischanged = false;
                                                dnsserv_4.ischanged = false;
                                                var ip_str = ip_1.text + "." + ip_2.text + "." + ip_3.text + "." + ip_4.text;
                                                var netmask_str = netmask_1.text + "." + netmask_2.text + "." + netmask_3.text + "." + netmask_4.text;
                                                var gateway_str = gateway_1.text + "." + gateway_2.text + "." + gateway_3.text + "." + gateway_4.text;
                                                var dns1_str = dnsmain_1.text===""?"":dnsmain_1.text + "." + dnsmain_2.text + "." + dnsmain_3.text + "." + dnsmain_4.text;
                                                var dns2_str = dnsserv_1.text===""?"":dnsserv_1.text + "." + dnsserv_2.text + "." + dnsserv_3.text + "." + dnsserv_4.text;
                                                supervisor.setWifi("", ip_str, netmask_str, gateway_str,dns1_str,dns2_str);
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
                    height: group_height
                    color: "black"
                    visible: is_rainbow
                    anchors.horizontalCenter: parent.horizontalCenter
                    Text{
                        anchors.centerIn: parent
                        font.family: font_noto_b.name
                        text:qsTr("카메라 설정")
                        color: "white"
                        font.pixelSize: group_font_size
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
                    height: setting_height
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
                                text:qsTr("카메라 모델")
                                font.pixelSize: name_font_size
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
                                font.pixelSize: info_font_size
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
                                model:[qsTr("리얼센스"),qsTr("제미니")]
                            }
                        }
                    }
                }
                Rectangle{
                    id: set_cam_exposure
                    width: 840
                    height: setting_height
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
                                text:qsTr("노출 시간 [ms]")
                                font.pixelSize: name_font_size
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
                                font.pixelSize: info_font_size
                                text:supervisor.getSetting("setting","SENSOR","cam_exposure");
                                property bool ischanged: false
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        supervisor.playSound('click', slider_volume_button.value);
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
                    height: setting_height
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
                                text:qsTr("왼쪽 카메라 시리얼")
                                font.pixelSize: name_font_size
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
                                font.pixelSize: info_font_size
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
                                    text:qsTr("viewer")
                                    font.pixelSize: info_font_size
                                    font.family: font_noto_r.name
                                }
                                MouseArea{
                                    anchors.fill: parent
                                    onClicked: {
                                        supervisor.playSound('click', slider_volume_button.value);
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
                    height: setting_height
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
                                text:qsTr("오른쪽 카메라 시리얼")
                                font.pixelSize: name_font_size
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
                                    supervisor.playSound('click', slider_volume_button.value);

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
                                font.pixelSize: info_font_size
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
                                    text:qsTr("viewer")
                                    font.pixelSize: info_font_size
                                    font.family: font_noto_r.name
                                    MouseArea{
                                        anchors.fill: parent
                                        onClicked: {
                                            supervisor.playSound('click', slider_volume_button.value);
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
                    height: setting_height
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
                                text:qsTr("라이다 TF")
                                font.pixelSize: name_font_size
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
                                font.pixelSize: info_font_size
                                height: parent.height
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
                                    text:qsTr("change")
                                    color: "white"
                                    font.pixelSize: info_font_size
                                }
                                MouseArea{
                                    anchors.fill: parent
                                    onClicked:{
                                        supervisor.playSound('click', slider_volume_button.value);
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
                    height: setting_height
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
                                text:qsTr("왼쪽 카메라 TF")
                                font.pixelSize: name_font_size
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                    anchors.leftMargin = 30 - width*(1-scale)/2
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
                                font.pixelSize: info_font_size
                                height: parent.height
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
                                    text:qsTr("change")
                                    font.pixelSize: info_font_size
                                    color: "white"
                                }
                                MouseArea{
                                    anchors.fill: parent
                                    onClicked:{
                                        supervisor.playSound('click', slider_volume_button.value);
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
                    height: setting_height
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
                                text:qsTr("오른쪽 카메라 TF")
                                font.pixelSize: name_font_size
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                    anchors.leftMargin = 30 - width*(1-scale)/2
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
                                height: parent.height
                                font.pixelSize: info_font_size
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
                                    text:qsTr("change")
                                    color: "white"
                                    font.pixelSize: info_font_size
                                }
                                MouseArea{
                                    anchors.fill: parent
                                    onClicked:{
                                        supervisor.playSound('click', slider_volume_button.value);
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
                    height: setting_height
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
                                text:qsTr("3D카메라 감지 최소높이 [m]")
                                font.pixelSize: name_font_size
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                    anchors.leftMargin = 30 - width*(1-scale)/2
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
                                font.pixelSize: info_font_size
                                text:supervisor.getSetting("setting","OBSTACLE","obs_height_min");
                                property bool ischanged: false
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        supervisor.playSound('click', slider_volume_button.value);
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
                    height: setting_height
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
                                text:qsTr("3D카메라 감지 최대높이 [m]")
                                font.pixelSize: name_font_size
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                    anchors.leftMargin = 30 - width*(1-scale)/2
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
                                font.pixelSize: info_font_size
                                color:ischanged?color_red:"black"
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        supervisor.playSound('click', slider_volume_button.value);
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
                    height: setting_height
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
                                text:qsTr("라이다데이터 최대 거리 [m]")
                                font.pixelSize: name_font_size
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                    anchors.leftMargin = 30 - width*(1-scale)/2
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
                                font.pixelSize: info_font_size
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        supervisor.playSound('click', slider_volume_button.value);
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
                    height: setting_height
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
                                text:qsTr("라이다데이터 최소 거리 [m]")
                                font.pixelSize: name_font_size
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                    anchors.leftMargin = 30 - width*(1-scale)/2
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
                                font.pixelSize: info_font_size
                                property bool ischanged: false
                                onTextChanged: {
                                    is_reset_slam = true;
                                    ischanged = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        supervisor.playSound('click', slider_volume_button.value);
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
                    height: group_height
                    color: "black"
                    anchors.horizontalCenter: parent.horizontalCenter
                    Text{
                        anchors.centerIn: parent
                        font.family: font_noto_b.name
                        text:qsTr("주행 중 감지")
                        color: "white"
                        font.pixelSize: group_font_size
                        Component.onCompleted: {
                            scale = 1;
                            while(width*scale > parent.width*0.8){
                                scale=scale-0.01;
                            }
                            anchors.leftMargin = 30 - width*(1-scale)/2
                        }
                    }
                }
                Rectangle{
                    id: set_use_obs_preview
                    width: 840
                    height: setting_height
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
                                text:qsTr("장애물 예측 사용")
                                font.pixelSize: name_font_size
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                    anchors.leftMargin = 30 - width*(1-scale)/2
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
                                font.pixelSize: info_font_size
                                property bool ischanged: false
                                onCurrentIndexChanged: {
                                    is_reset_slam = true;
                                    ischanged = true;
                                }
                                model:[qsTr("사용안함"),qsTr("사용")]
                            }
                        }
                    }
                }
                Rectangle{
                    id: set_obs_preview_time
                    width: 840
                    height: setting_height
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
                                text:qsTr("장애물 예측 시간 [초]")
                                font.pixelSize: name_font_size
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                    anchors.leftMargin = 30 - width*(1-scale)/2
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
                                font.pixelSize: info_font_size
                                property bool ischanged: false
                                onTextChanged: {
                                    is_reset_slam = true;
                                    ischanged = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        supervisor.playSound('click', slider_volume_button.value);
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

                //Rectangle{ // 장애물 회피
                //    id: set_use_avoid
                //    width: 840
                //    height: setting_height
                //    Row{
                //        anchors.fill: parent
                //        Rectangle{
                //            width: 350
                //            height: parent.height
                //            Text{
                //                anchors.verticalCenter: parent.verticalCenter
                //                anchors.left: parent.left
                //                anchors.leftMargin: 30
                //                font.family: font_noto_r.name
                //                text:qsTr("장애물 회피")
                //                font.pixelSize: name_font_size
                //                Component.onCompleted: {
                //                    scale = 1;
                //                    while(width*scale > parent.width*0.8){
                //                        scale=scale-0.01;
                //                    }
                //                    anchors.leftMargin = 30 - width*(1-scale)/2
                //                }
                //            }
                //        }
                //        Rectangle{
                //            width: 1
                //            height: parent.height
                //            color: "#d0d0d0"
                //        }
                //        Rectangle{
                //            width: parent.width - 351
                //            height: parent.height
                //            ComboBox{
                //                id: combo_use_avoid
                //                anchors.fill: parent
                //                property bool ischanged: false
                //                onCurrentIndexChanged: {
                //                    is_reset_slam = true;
                //                    ischanged = true;
                //                }
                //                model:[qsTr("사용안함"),qsTr("사용")]
                //            }
                //        }
                //    }
                //}

                //Rectangle{ // 장애물 회피 - 장애물 감지 너비
                //    id: set_obs_check_range
                //    width: 840
                //    height: setting_height
                //    visible: combo_use_avoid.currentIndex === 1
                //    Row{
                //        anchors.fill: parent
                //        Rectangle{
                //            width: 350
                //            height: parent.height
                //            Text{
                //                anchors.verticalCenter: parent.verticalCenter
                //                anchors.left: parent.left
                //                anchors.leftMargin: 30
                //                font.family: font_noto_r.name
                //                text:qsTr("장애물 감지 너비")
                //                font.pixelSize: name_font_size
                //                Component.onCompleted: {
                //                    scale = 1;
                //                    while(width*scale > parent.width*0.8){
                //                        scale=scale-0.01;
                //                    }
                //                    anchors.leftMargin = 30 - width*(1-scale)/2
                //                }
                //            }
                //        }
                //        Rectangle{
                //            width: 1
                //            height: parent.height
                //            color: "#d0d0d0"
                //        }
                //        Rectangle{
                //            width: parent.width - 351
                //            height: parent.height
                //            TextField{
                //                id: obs_check_range
                //                anchors.fill: parent
                //                objectName: "obs_check_range"
                //                text:supervisor.getSetting("setting","OBSTACLE","obs_check_range");
                //                property bool ischanged: false
                //                MouseArea{
                //                    anchors.fill:parent
                //                    onClicked: {
                //                        supervisor.playSound('click', slider_volume_button.value);
                //                        if(keypad.is_opened){
                //                            keypad.owner = obs_check_range;
                //                            obs_check_range.selectAll();
                //                        }else{
                //                            keypad.owner = obs_check_range;
                //                            obs_check_range.selectAll();
                //                            keypad.open();
                //                        }
                //                    }
                //                }
                //                color:ischanged?color_red:"black"
                //                onTextChanged: {
                //                    ischanged = true;
                //                    is_reset_slam = true;

                //                }
                //            }
                //        }
                //    }
                //}

                //Rectangle{ // 제자리 회전 장애물 감지
                //    id: set_use_pivot_obs
                //    width: 840
                //    height: setting_height
                //    Row{
                //        anchors.fill: parent
                //        Rectangle{
                //            width: 350
                //            height: parent.height
                //            Text{
                //                anchors.verticalCenter: parent.verticalCenter
                //                anchors.left: parent.left
                //                anchors.leftMargin: 30
                //                font.family: font_noto_r.name
                //                text:qsTr("제자리회전 장애물감지")
                //                font.pixelSize: name_font_size
                //                Component.onCompleted: {
                //                    scale = 1;
                //                    while(width*scale > parent.width*0.8){
                //                        scale=scale-0.01;
                //                    }
                //                    anchors.leftMargin = 30 - width*(1-scale)/2
                //                }
                //            }
                //        }
                //        Rectangle{
                //            width: 1
                //            height: parent.height
                //            color: "#d0d0d0"
                //        }
                //        Rectangle{
                //            width: parent.width - 351
                //            height: parent.height
                //            ComboBox{
                //                id: combo_use_pivot_obs
                //                anchors.fill: parent
                //                property bool ischanged: false
                //                onCurrentIndexChanged: {
                //                    is_reset_slam = true;
                //                    ischanged = true;
                //                }
                //                model:[qsTr("사용안함"),qsTr("사용")]
                //            }
                //        }
                //    }
                //}
                //Rectangle{
                //    id: set_use_obs_near
                //    width: 840
                //    height: setting_height
                //    Row{
                //        anchors.fill: parent
                //        Rectangle{
                //            width: 350
                //            height: parent.height
                //            Text{
                //                anchors.verticalCenter: parent.verticalCenter
                //                anchors.left: parent.left
                //                anchors.leftMargin: 30
                //                font.family: font_noto_r.name
                //                text:qsTr("근접 장애물 감속")
                //                font.pixelSize: name_font_size
                //                Component.onCompleted: {
                //                    scale = 1;
                //                    while(width*scale > parent.width*0.8){
                //                        scale=scale-0.01;
                //                    }
                //                    anchors.leftMargin = 30 - width*(1-scale)/2
                //                }
                //            }
                //        }
                //        Rectangle{
                //            width: 1
                //            height: parent.height
                //            color: "#d0d0d0"
                //        }
                //        Rectangle{
                //            width: parent.width - 351
                //            height: parent.height
                //            ComboBox{
                //                id: combo_use_obs_near
                //                anchors.fill: parent
                //                property bool ischanged: false
                //                onCurrentIndexChanged: {
                //                    is_reset_slam = true;
                //                    ischanged = true;
                //                }
                //                model:[qsTr("사용안함"),qsTr("사용")]
                //            }
                //        }
                //    }
                //}
                //Rectangle{
                //    id: set_obs_near
                //    width: 840
                //    height: setting_height
                //    visible: combo_use_obs_near.currentIndex === 1
                //    Row{
                //        anchors.fill: parent
                //        Rectangle{
                //            width: 350
                //            height: parent.height
                //            Text{
                //                anchors.verticalCenter: parent.verticalCenter
                //                anchors.left: parent.left
                //                anchors.leftMargin: 30
                //                font.family: font_noto_r.name
                //                text:qsTr("근접 장애물 거리")
                //                font.pixelSize: name_font_size
                //                Component.onCompleted: {
                //                    scale = 1;
                //                    while(width*scale > parent.width*0.8){
                //                        scale=scale-0.01;
                //                    }
                //                    anchors.leftMargin = 30 - width*(1-scale)/2
                //                }
                //            }
                //        }
                //        Rectangle{
                //            width: 1
                //            height: parent.height
                //            color: "#d0d0d0"
                //        }
                //        Rectangle{
                //            width: parent.width - 351
                //            height: parent.height
                //            TextField{
                //                id: obs_near
                //                anchors.fill: parent
                //                objectName: "obs_near"
                //                text:supervisor.getSetting("setting","OBSTACLE","obs_near");
                //                property bool ischanged: false
                //                MouseArea{
                //                    anchors.fill:parent
                //                    onClicked: {
                //                        supervisor.playSound('click', slider_volume_button.value);
                //                        if(keypad.is_opened){
                //                            keypad.owner = obs_near;
                //                            obs_near.selectAll();
                //                        }else{
                //                            keypad.owner = obs_near;
                //                            obs_near.selectAll();
                //                            keypad.open();
                //                        }
                //                    }
                //                }
                //                color:ischanged?color_red:"black"
                //                onTextChanged: {
                //                    ischanged = true;
                //                    is_reset_slam = true;

                //                }
                //            }
                //        }
                //    }
                //}
                //Rectangle{
                //    id: set_obs_decel_gain
                //    width: 840
                //    height: setting_height
                //    visible: combo_use_obs_near.currentIndex === 1
                //    Row{
                //        anchors.fill: parent
                //        Rectangle{
                //            width: 350
                //            height: parent.height
                //            Text{
                //                anchors.verticalCenter: parent.verticalCenter
                //                anchors.left: parent.left
                //                anchors.leftMargin: 30
                //                font.family: font_noto_r.name
                //                text:qsTr("장애물 감속 게인")
                //                font.pixelSize: name_font_size
                //                Component.onCompleted: {
                //                    scale = 1;
                //                    while(width*scale > parent.width*0.8){
                //                        scale=scale-0.01;
                //                    }
                //                    anchors.leftMargin = 30 - width*(1-scale)/2
                //                }
                //            }
                //        }
                //        Rectangle{
                //            width: 1
                //            height: parent.height
                //            color: "#d0d0d0"
                //        }
                //        Rectangle{
                //            width: parent.width - 351
                //            height: parent.height
                //            TextField{
                //                id: obs_decel_gain
                //                anchors.fill: parent
                //                objectName: "obs_decel_gain"
                //                text:supervisor.getSetting("setting","OBSTACLE","obs_decel_gain");
                //                property bool ischanged: false
                //                MouseArea{
                //                    anchors.fill:parent
                //                    onClicked: {
                //                        supervisor.playSound('click', slider_volume_button.value);
                //                        if(keypad.is_opened){
                //                            keypad.owner = obs_decel_gain;
                //                            obs_decel_gain.selectAll();
                //                        }else{
                //                            keypad.owner = obs_decel_gain;
                //                            obs_decel_gain.selectAll();
                //                            keypad.open();
                //                        }
                //                    }
                //                }
                //                color:ischanged?color_red:"black"
                //                onTextChanged: {
                //                    ischanged = true;
                //                    is_reset_slam = true;

                //                }
                //            }
                //        }
                //    }
                //}

                Rectangle{
                    id: set_use_earlystop_resting
                    width: 840
                    height: setting_height
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
                                text:qsTr("대기위치 근처 장애물 미리 정지")
                                font.pixelSize: name_font_size
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                    anchors.leftMargin = 30 - width*(1-scale)/2
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
                                font.pixelSize: info_font_size
                                id: combo_use_earlystop_resting
                                anchors.fill: parent
                                property bool ischanged: false
                                onCurrentIndexChanged: {
                                    is_reset_slam = true;
                                    ischanged = true;
                                }
                                model:[qsTr("사용안함"),qsTr("사용")]
                            }
                        }
                    }
                }
                Rectangle{
                    id: set_use_earlystop_serving
                    width: 840
                    height: setting_height
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
                                text:qsTr("서빙위치 근처 장애물 미리 정지")
                                font.pixelSize: name_font_size
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                    anchors.leftMargin = 30 - width*(1-scale)/2
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
                                font.pixelSize: info_font_size
                                id: combo_use_earlystop_serving
                                anchors.fill: parent
                                property bool ischanged: false
                                onCurrentIndexChanged: {
                                    is_reset_slam = true;
                                    ischanged = true;
                                }
                                model:[qsTr("사용안함"),qsTr("사용")]
                            }
                        }
                    }
                }
                Rectangle{
                    id: set_obs_early_stop_dist
                    width: 840
                    height: setting_height
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
                                text:qsTr("근처 장애물 정지 거리")
                                font.pixelSize: name_font_size
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                    anchors.leftMargin = 30 - width*(1-scale)/2
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
                                font.pixelSize: info_font_size
                                text:supervisor.getSetting("setting","OBSTACLE","obs_early_stop_dist");
                                property bool ischanged: false
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        supervisor.playSound('click', slider_volume_button.value);
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
                    id: set_use_ignore_safetyzone_return
                    width: 840
                    height: setting_height
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
                                text:qsTr("복귀 시 안전구간 무시")
                                font.pixelSize: name_font_size
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                    anchors.leftMargin = 30 - width*(1-scale)/2
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
                                id: combo_use_ignore_safetyzone_return
                                anchors.fill: parent
                                font.pixelSize: info_font_size
                                property bool ischanged: false
                                onCurrentIndexChanged: {
                                    is_reset_slam = true;
                                    ischanged = true;
                                }
                                model:[qsTr("사용안함"),qsTr("사용")]
                            }
                        }
                    }
                }


                Rectangle{
                    id: set_decmargin
                    width: 840
                    height: setting_height
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
                                text:qsTr("동적 장애물 마진 [m]")
                                font.pixelSize: name_font_size
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                    anchors.leftMargin = 30 - width*(1-scale)/2
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
                                font.pixelSize: info_font_size
                                anchors.fill: parent
                                objectName: "obs_margin1"
                                text:supervisor.getSetting("setting","OBSTACLE","obs_margin1");
                                property bool ischanged: false
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        supervisor.playSound('click', slider_volume_button.value);
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
                    height: setting_height
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
                                text:qsTr("정적 장애물 마진 [m]")
                                font.pixelSize: name_font_size
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                    anchors.leftMargin = 30 - width*(1-scale)/2
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
                                font.pixelSize: info_font_size
                                objectName: "obs_margin0"
                                text:supervisor.getSetting("setting","OBSTACLE","obs_margin0");
                                property bool ischanged: false
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        supervisor.playSound('click', slider_volume_button.value);
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
                    height: setting_height
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
                                text:qsTr("장애물 넓이 [pixel]")
                                font.pixelSize: name_font_size
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                    anchors.leftMargin = 30 - width*(1-scale)/2
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
                                font.pixelSize: info_font_size
                                objectName: "obs_detect_area"
                                text:supervisor.getSetting("setting","OBSTACLE","obs_detect_area");
                                property bool ischanged: false
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        supervisor.playSound('click', slider_volume_button.value);
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
                    height: setting_height
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
                                text:qsTr("장애물 최소검출 누적횟수")
                                font.pixelSize: name_font_size
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                    anchors.leftMargin = 30 - width*(1-scale)/2
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
                                font.pixelSize: info_font_size
                                anchors.fill: parent
                                objectName: "obs_detect_sensitivity"
                                text:supervisor.getSetting("setting","OBSTACLE","obs_detect_sensitivity");
                                property bool ischanged: false
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        supervisor.playSound('click', slider_volume_button.value);
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
                    height: setting_height
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
                                text:qsTr("즉시정지 거리 [m]")
                                font.pixelSize: name_font_size
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                    anchors.leftMargin = 30 - width*(1-scale)/2
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
                                font.pixelSize: info_font_size
                                onTextChanged: {
                                    is_reset_slam = true;
                                    ischanged = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        supervisor.playSound('click', slider_volume_button.value);
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
                    height: setting_height
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
                                text:qsTr("감지 후 대기시간 [sec]")
                                font.pixelSize: name_font_size
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                    anchors.leftMargin = 30 - width*(1-scale)/2
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
                                font.pixelSize: info_font_size
                                onTextChanged: {
                                    is_reset_slam = true;
                                    ischanged = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        supervisor.playSound('click', slider_volume_button.value);
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
                    height: setting_height
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
                                text:qsTr("경로추종 최대거리 [m]")
                                font.pixelSize: name_font_size
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                    anchors.leftMargin = 30 - width*(1-scale)/2
                                }
                            }
                            Item_buttons{
                                type: "circle_text"
                                width: parent.height*0.8
                                height: width
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.right: parent.right
                                anchors.rightMargin: 20
                                text:qsTr("?")
                                onClicked:{
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
                                font.pixelSize: info_font_size
                                onTextChanged: {
                                    is_reset_slam = true;
                                    ischanged = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        supervisor.playSound('click', slider_volume_button.value);
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
                    height: setting_height
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
                                text:qsTr("경로추종 최소거리 [m]")
                                font.pixelSize: name_font_size
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                    anchors.leftMargin = 30 - width*(1-scale)/2
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
                                font.pixelSize: info_font_size
                                anchors.fill: parent
                                property bool ischanged: false
                                onTextChanged: {
                                    is_reset_slam = true;
                                    ischanged = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        supervisor.playSound('click', slider_volume_button.value);
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
                    height: setting_height
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
                                text:qsTr("경로이탈 거리 [m]")
                                font.pixelSize: name_font_size
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                    anchors.leftMargin = 30 - width*(1-scale)/2
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
                                font.pixelSize: info_font_size
                                onTextChanged: {
                                    is_reset_slam = true;
                                    ischanged = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        supervisor.playSound('click', slider_volume_button.value);
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
                    height: group_height
                    color: "black"
                    anchors.horizontalCenter: parent.horizontalCenter
                    Text{
                        anchors.centerIn: parent
                        font.family: font_noto_b.name
                        text:qsTr("위치 추정")
                        color: "white"
                        font.pixelSize: group_font_size
                    }
                }
                Rectangle{
                    id: set_icp_init_ratio
                    width: 840
                    height: setting_height
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
                                text:qsTr("초기화 성공기준 [0~1]")
                                font.pixelSize: name_font_size
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                    anchors.leftMargin = 30 - width*(1-scale)/2
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
                                font.pixelSize: info_font_size
                                property bool ischanged: false
                                onTextChanged: {
                                    is_reset_slam = true;
                                    ischanged = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        supervisor.playSound('click', slider_volume_button.value);
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
                    height: setting_height
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
                                text:qsTr("초기화 에러기준 [0~1]")
                                font.pixelSize: name_font_size
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
                                font.pixelSize: info_font_size
                                property bool ischanged: false
                                onTextChanged: {
                                    is_reset_slam = true;
                                    ischanged = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        supervisor.playSound('click', slider_volume_button.value);
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
                    height: setting_height
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
                                text:qsTr("Inlier 판단거리 [m]")
                                font.pixelSize: name_font_size
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
                                id: icp_dist
                                anchors.fill: parent
                                font.pixelSize: info_font_size
                                property bool ischanged: false
                                onTextChanged: {
                                    is_reset_slam = true;
                                    ischanged = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        supervisor.playSound('click', slider_volume_button.value);
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
                    height: setting_height
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
                                text:qsTr("평균오차 최소값 [m]")
                                font.pixelSize: name_font_size
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
                                id: icp_error
                                anchors.fill: parent
                                font.pixelSize: info_font_size
                                property bool ischanged: false
                                onTextChanged: {
                                    is_reset_slam = true;
                                    ischanged = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        supervisor.playSound('click', slider_volume_button.value);
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
                    height: setting_height
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
                                text:qsTr("Inlier 비율 [%]")
                                font.pixelSize: name_font_size
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
                                id: icp_ratio
                                anchors.fill: parent
                                property bool ischanged: false
                                font.pixelSize: info_font_size
                                onTextChanged: {
                                    is_reset_slam = true;
                                    ischanged = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        supervisor.playSound('click', slider_volume_button.value);
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
                    height: setting_height
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
                                text:qsTr("모터 위치추정 비율 [%]")
                                font.pixelSize: name_font_size
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
                                id: icp_odometry_weight
                                anchors.fill: parent
                                property bool ischanged: false
                                font.pixelSize: info_font_size
                                onTextChanged: {
                                    is_reset_slam = true;
                                    ischanged = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        supervisor.playSound('click', slider_volume_button.value);
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
                    height: setting_height
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
                                text:qsTr("위치추정 최소 거리 [m]")
                                font.pixelSize: name_font_size
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
                                id: icp_repeat_dist
                                anchors.fill: parent
                                font.pixelSize: info_font_size
                                property bool ischanged: false
                                onTextChanged: {
                                    is_reset_slam = true;
                                    ischanged = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        supervisor.playSound('click', slider_volume_button.value);
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
                    height: setting_height
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
                                text:qsTr("위치추정 최소 시간[sec]")
                                font.pixelSize: name_font_size
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
                                id: icp_repeat_time
                                anchors.fill: parent
                                property bool ischanged: false
                                font.pixelSize: info_font_size
                                onTextChanged: {
                                    is_reset_slam = true;
                                    ischanged = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        supervisor.playSound('click', slider_volume_button.value);
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
                    height: group_height
                    color: "black"
                    visible: is_rainbow
                    anchors.horizontalCenter: parent.horizontalCenter
                    Text{
                        anchors.centerIn: parent
                        font.family: font_noto_b.name
                        text:qsTr("도착점 판단")
                        color: "white"
                        font.pixelSize: group_font_size
                    }
                }
                Rectangle{
                    id: set_goal_dist
                    width: 840
                    height: setting_height
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
                                text:qsTr("도착점 허용 오차 [m]")
                                font.pixelSize: name_font_size
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
                                id: goal_dist
                                anchors.fill: parent
                                property bool ischanged: false
                                font.pixelSize: info_font_size
                                onTextChanged: {
                                    is_reset_slam = true;
                                    ischanged = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        supervisor.playSound('click', slider_volume_button.value);
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
                    height: setting_height
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
                                text:qsTr("도착점 허용 오차 [deg]")
                                font.pixelSize: name_font_size
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
                                id: goal_th
                                font.pixelSize: info_font_size
                                anchors.fill: parent
                                property bool ischanged: false
                                onTextChanged: {
                                    is_reset_slam = true;
                                    ischanged = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        supervisor.playSound('click', slider_volume_button.value);
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
                    height: setting_height
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
                                text:qsTr("목적지 미리 도달거리 [m]")
                                font.pixelSize: name_font_size
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
                                id: goal_near_dist
                                anchors.fill: parent
                                font.pixelSize: info_font_size
                                property bool ischanged: false
                                onTextChanged: {
                                    is_reset_slam = true;
                                    ischanged = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        supervisor.playSound('click', slider_volume_button.value);
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
                    height: setting_height
                    visible: false//is_rainbow
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
                                text:qsTr("경로탐색 최소거리 [deg]")
                                font.pixelSize: name_font_size
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
                                id: goal_near_th
                                font.pixelSize: info_font_size
                                anchors.fill: parent
                                property bool ischanged: false
                                onTextChanged: {
                                    is_reset_slam = true;
                                    ischanged = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        supervisor.playSound('click', slider_volume_button.value);
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
                    height: group_height
                    color: "black"
                    visible: is_rainbow
                    anchors.horizontalCenter: parent.horizontalCenter
                    Text{
                        anchors.centerIn: parent
                        font.family: font_noto_b.name
                        text:qsTr("지도 작성")
                        color: "white"
                        font.pixelSize: group_font_size
                    }
                }
                Rectangle{
                    id: set_slam_submap_cnt
                    width: 840
                    height: setting_height
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
                                text:qsTr("서브맵 프레임 개수")
                                font.pixelSize: name_font_size
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
                                id: slam_submap_cnt
                                anchors.fill: parent
                                property bool ischanged: false
                                font.pixelSize: info_font_size
                                onTextChanged: {
                                    is_reset_slam = true;
                                    ischanged = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        supervisor.playSound('click', slider_volume_button.value);
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
                    height: setting_height
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
                                text:qsTr("루프클로징 시도거리")
                                font.pixelSize: name_font_size
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
                                id: slam_lc_dist
                                font.pixelSize: info_font_size
                                anchors.fill: parent
                                property bool ischanged: false
                                onTextChanged: {
                                    is_reset_slam = true;
                                    ischanged = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        supervisor.playSound('click', slider_volume_button.value);
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
                    height: setting_height
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
                                text:qsTr("루프클로징 매칭범위")
                                font.pixelSize: name_font_size
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
                                id: slam_lc_icp_dist
                                font.pixelSize: info_font_size
                                anchors.fill: parent
                                property bool ischanged: false
                                onTextChanged: {
                                    is_reset_slam = true;
                                    ischanged = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        supervisor.playSound('click', slider_volume_button.value);
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
                    height: setting_height
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
                                text:qsTr("지도 기본 크기")
                                font.pixelSize: name_font_size
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
                                id: map_size
                                anchors.fill: parent
                                font.pixelSize: info_font_size
                                property bool ischanged: false
                                onTextChanged: {
                                    is_reset_slam = true;
                                    ischanged = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        supervisor.playSound('click', slider_volume_button.value);
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
                    height: setting_height
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
                                text:qsTr("기본 격자 크기")
                                font.pixelSize: name_font_size
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
                                id: grid_size
                                anchors.fill: parent
                                font.pixelSize: info_font_size
                                property bool ischanged: false
                                onTextChanged: {
                                    is_reset_slam = true;
                                    ischanged = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        supervisor.playSound('click', slider_volume_button.value);
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
                    height: group_height
                    color: "black"
                    visible: is_rainbow
                    anchors.horizontalCenter: parent.horizontalCenter
                    Text{
                        anchors.centerIn: parent
                        font.family: font_noto_b.name
                        text:qsTr("주행 중")
                        color: "white"
                        font.pixelSize: group_font_size
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
                    height: setting_height
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
                                text:qsTr("모터 과전류 시 일시정지")
                                font.pixelSize: name_font_size
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
                                id: combo_use_motorcurrent
                                font.pixelSize: info_font_size
                                anchors.fill: parent
                                property bool ischanged: false
                                onCurrentIndexChanged: {
                                    ischanged = true;
                                }
                                model:[qsTr("사용안함"),qsTr("사용")]
                            }
                        }
                    }
                }
                Rectangle{
                    id: set_motor_current_margin
                    width: 840
                    height: setting_height
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
                                text:qsTr("모터전류 제한값 [mA]")
                                font.pixelSize: name_font_size
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
                                font.pixelSize: info_font_size
                                onTextChanged: {
                                    ischanged = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        supervisor.playSound('click', slider_volume_button.value);
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
                    height: setting_height
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
                                text:qsTr("모터전류 제한시간 [ms]")
                                font.pixelSize: name_font_size
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
                                font.pixelSize: info_font_size
                                property bool ischanged: false
                                onTextChanged: {
                                    ischanged = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        supervisor.playSound('click', slider_volume_button.value);
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
                    height: group_height
                    color: "black"
                    visible: is_rainbow
                    anchors.horizontalCenter: parent.horizontalCenter
                    Text{
                        anchors.centerIn: parent
                        font.family: font_noto_b.name
                        text:qsTr("속도 제한")
                        color: "white"
                        font.pixelSize: group_font_size
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
                    height: setting_height
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
                                text:qsTr("출발 시 처음속도 [m/s]")
                                font.pixelSize: name_font_size
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
                                id: st_v
                                anchors.fill: parent
                                property bool ischanged: false
                                font.pixelSize: info_font_size
                                onTextChanged: {
                                    is_reset_slam = true;
                                    ischanged = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        supervisor.playSound('click', slider_volume_button.value);
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
                    height: setting_height
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
                                text:qsTr("도착지점 속도 [m/s]")
                                font.pixelSize: name_font_size
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
                                id: goal_v
                                anchors.fill: parent
                                property bool ischanged: false
                                font.pixelSize: info_font_size
                                onTextChanged: {
                                    is_reset_slam = true;
                                    ischanged = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        supervisor.playSound('click', slider_volume_button.value);
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

                Rectangle{ // 게인 수정
                    width: 1100
                    height: group_height
                    color: "black"
                    visible: is_rainbow
                    anchors.horizontalCenter: parent.horizontalCenter
                    Text{
                        anchors.centerIn: parent
                        font.family: font_noto_b.name
                        text:qsTr("게인 수정")
                        color: "white"
                        font.pixelSize: group_font_size
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
                    height: setting_height
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
                                text:qsTr("k_curve")
                                font.pixelSize: name_font_size
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
                                font.pixelSize: info_font_size
                                property bool ischanged: false
                                onTextChanged: {
                                    is_reset_slam = true;
                                    ischanged = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        supervisor.playSound('click', slider_volume_button.value);
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
                    height: setting_height
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
                                text:qsTr("k_v")
                                font.pixelSize: name_font_size
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
                                font.pixelSize: info_font_size
                                property bool ischanged: false
                                onTextChanged: {
                                    is_reset_slam = true;
                                    ischanged = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        supervisor.playSound('click', slider_volume_button.value);
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
                    height: setting_height
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
                                text:qsTr("k_w")
                                font.pixelSize: name_font_size
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
                                font.pixelSize: info_font_size
                                onTextChanged: {
                                    is_reset_slam = true;
                                    ischanged = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        supervisor.playSound('click', slider_volume_button.value);
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
                    height: setting_height
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
                                text:qsTr("k_dd")
                                font.pixelSize: name_font_size
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
                                font.pixelSize: info_font_size
                                onTextChanged: {
                                    is_reset_slam = true;
                                    ischanged = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        supervisor.playSound('click', slider_volume_button.value);
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
                    height: setting_height
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
                                text:qsTr("경로 가속 게인")
                                font.pixelSize: name_font_size
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
                                font.pixelSize: info_font_size
                                property bool ischanged: false
                                onTextChanged: {
                                    is_reset_slam = true;
                                    ischanged = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        supervisor.playSound('click', slider_volume_button.value);
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
                    height: setting_height
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
                                text:qsTr("경로 감속 게인")
                                font.pixelSize: name_font_size
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
                                font.pixelSize: info_font_size
                                onTextChanged: {
                                    is_reset_slam = true;
                                    ischanged = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        supervisor.playSound('click', slider_volume_button.value);
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
                    height: setting_height
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
                                text:qsTr("경로 속도 게인")
                                font.pixelSize: name_font_size
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
                                font.pixelSize: info_font_size
                                onTextChanged: {
                                    is_reset_slam = true;
                                    ischanged = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        supervisor.playSound('click', slider_volume_button.value);
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
                //Rectangle{ //경로 시프팅 게인
                //    id: set_path_shifting_val
                //    width: 840
                //    height: setting_height
                //    visible: is_rainbow
                //    Row{
                //        anchors.fill: parent
                //        Rectangle{
                //            width: 350
                //            height: parent.height
                //            Text{
                //                anchors.verticalCenter: parent.verticalCenter
                //                anchors.left: parent.left
                //                anchors.leftMargin: 30
                //                font.family: font_noto_r.name
                //                text:qsTr("경로 시프팅 게인")
                //                font.pixelSize: name_font_size
                //                Component.onCompleted: {
                //                    scale = 1;
                //                    while(width*scale > parent.width*0.8){
                //                        scale=scale-0.01;
                //                    }
                //                }
                //            }
                //        }
                //        Rectangle{
                //            width: 1
                //            height: parent.height
                //            color: "#d0d0d0"
                //        }
                //        Rectangle{
                //            width: parent.width - 351
                //            height: parent.he팅ight
                //            TextField{
                //                id: path_shifting_val
                //                anchors.fill: parent
                //                property bool ischanged: false
                //                onTextChanged: {
                //                    is_reset_slam = true;
                //                    ischanged = true;
                //                }
                //                MouseArea{
                //                    anchors.fill:parent
                //                    onClicked: {
                //                        supervisor.playSound('click', slider_volume_button.value);
                //                        if(keypad.is_opened){
                //                            keypad.owner = path_shifting_val;
                //                            path_shifting_val.selectAll();
                //                        }else{
                //                            keypad.owner = path_shifting_val;
                //                            path_shifting_val.selectAll();
                //                            keypad.open();
                //                        }
                //                    }
                //                }
                //                color:ischanged?color_red:"black"
                //                text:supervisor.getSetting("update","DRIVING","path_shifting_val");
                //            }
                //        }
                //    }
                //}

                Rectangle{
                    width: 1100
                    height: group_height
                    color: "black"
                    visible: is_rainbow
                    anchors.horizontalCenter: parent.horizontalCenter
                    Text{
                        anchors.centerIn: parent
                        font.family: font_noto_b.name
                        text:qsTr("모터 세팅 값")
                        color: "white"
                        font.pixelSize: name_font_size
                    }
                }
                Rectangle{
                    id: set_wheel_dir
                    width: 840
                    height: setting_height
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
                                text:qsTr("바퀴 회전 방향")
                                font.pixelSize: name_font_size
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
                                font.pixelSize: info_font_size
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
                    height: setting_height
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
                                text:qsTr("왼쪽 모터 ID")
                                font.pixelSize: name_font_size
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
                                font.pixelSize: info_font_size
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
                    height: setting_height
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
                                text:qsTr("오른쪽 모터 ID")
                                font.pixelSize: name_font_size
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
                                font.pixelSize: info_font_size
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
                    height: setting_height
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
                                text:qsTr("모터 기어비")
                                font.pixelSize: name_font_size
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
                                font.pixelSize: info_font_size
                                onTextChanged: {
                                    is_reset_slam = true;
                                    ischanged = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        supervisor.playSound('click', slider_volume_button.value);
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
                    height: setting_height
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
                                text:qsTr("모터 P 게인")
                                font.pixelSize: name_font_size
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
                                font.pixelSize: info_font_size
                                onTextChanged: {
                                    is_reset_slam = true;
                                    ischanged = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        supervisor.playSound('click', slider_volume_button.value);
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
                    height: setting_height
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
                                text:qsTr("모터 I 게인")
                                font.pixelSize: name_font_size
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
                                font.pixelSize: info_font_size
                                anchors.fill: parent
                                property bool ischanged: false
                                onTextChanged: {
                                    is_reset_slam = true;
                                    ischanged = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        supervisor.playSound('click', slider_volume_button.value);
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
                    height: setting_height
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
                                text:qsTr("모터 D 게인")
                                font.pixelSize: name_font_size
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
                                font.pixelSize: info_font_size
                                property bool ischanged: false
                                onTextChanged: {
                                    is_reset_slam = true;
                                    ischanged = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        supervisor.playSound('click', slider_volume_button.value);
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
                    height: setting_height
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
                                text:qsTr("최대 속도 [m/s]")
                                font.pixelSize: name_font_size
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
                                font.pixelSize: info_font_size
                                onTextChanged: {
                                    is_reset_slam = true;
                                    ischanged = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        supervisor.playSound('click', slider_volume_button.value);
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
                    height: setting_height
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
                                text:qsTr("최대 가속도 [m/s^2]")
                                font.pixelSize: name_font_size
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
                                font.pixelSize: info_font_size
                                anchors.fill: parent
                                property bool ischanged: false
                                onTextChanged: {
                                    is_reset_slam = true;
                                    ischanged = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        supervisor.playSound('click', slider_volume_button.value);
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
                    height: setting_height
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
                                text:qsTr("최대 각속도 [deg/s]")
                                font.pixelSize: name_font_size
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
                                font.pixelSize: info_font_size
                                property bool ischanged: false
                                onTextChanged: {
                                    is_reset_slam = true;
                                    ischanged = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        supervisor.playSound('click', slider_volume_button.value);
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
                    height: setting_height
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
                                text:qsTr("최대 각가속도 [deg/s^2]")
                                font.pixelSize: name_font_size
                                Component.onCompleted: {
                                    scale = 1;
                                    while(width*scale > parent.width*0.8){
                                        scale=scale-0.01;
                                    }
                                    anchors.leftMargin = 30 - width*(1-scale)/2
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
                                font.pixelSize: info_font_size
                                property bool ischanged: false
                                onTextChanged: {
                                    is_reset_slam = true;
                                    ischanged = true;
                                }
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        supervisor.playSound('click', slider_volume_button.value);
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
                spacing : 50
                anchors.centerIn: parent
                Image{
                    id: state_robot
                    source: "image/robot_bad.png"
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.verticalCenterOffset: 50
                    width: 1204/3
                    height: 1331/3
                    sourceSize.width: width
                    sourceSize.height: height
                    Rectangle{
                        id: state_localization
                        width: 65
                        height: 65
                        radius: 65
                        color: color_icon_gray
                        property int state: 0
                        onStateChanged: {
                            if(state === 0){//disconnected slamnav(NONE)
                                color = color_icon_gray;
                                state_robot.source = "image/robot_bad.png"
                                image_localization.source = "icon/icon_location.png"
                            }else if(state === 1){//localization not ready, failed(ERROR)
                                color = color_red;
                                image_localization.source = "icon/icon_location.png"
                                state_robot.source = "image/robot_bad.png"
                            }else if(state === 2){//localizating(WARNING)
                                color = color_warning;
                                image_localization.source = "icon/icon_location.png"
                                state_robot.source = "image/robot_normal.png"
                            }else if(state === 3){//all good
                                color = color_green;
                                image_localization.source = "icon/icon_check.png"
                                state_robot.source = "image/robot_good.png"
                            }
                        }
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.top: parent.top
                        anchors.topMargin: 15
                        Image{
                            id: image_localization
                            anchors.centerIn: parent
                            width: 50
                            height: 50
                            sourceSize.width: width
                            sourceSize.height: height
                            source: "icon/icon_location.png"
                        }
                    }
                    Rectangle{
                        id: state_network
                        width: 65
                        height: 65
                        radius: 65
                        property int state: 0
                        onStateChanged: {
                            if(state === 0){//disconnected ethernet(NONE)
                                color = color_icon_gray;
                                image_network.source = "icon/icon_ethernet_w.png"
                            }else if(state === 1){//connected ethernet but slamnav disconnected(ERROR)
                                color = color_icon_gray;
                                image_network.source = "icon/icon_ethernet_w.png"
                            }else if(state === 2){//slamnav connected but wifi disconnected(WARNING)
                                color = color_warning;
                                image_network.source = "icon/icon_wifi_w.png"
                            }else if(state === 3){//slamnav, wifi connected but not internet(WARNING)
                                color = color_warning;
                                image_network.source = "icon/icon_wifi_w.png"
                            }else if(state === 4){//all good
                                color = color_green;
                                image_network.source = "icon/icon_check.png"
                            }
                        }
                        color: color_icon_gray
                        anchors.right: parent.right
                        anchors.rightMargin: 15
                        anchors.top: parent.top
                        anchors.topMargin:65
                        Image{
                            id: image_network
                            anchors.centerIn: parent
                            width: 50
                            height: 50
                            sourceSize.width: width
                            sourceSize.height: height
                            source: "icon/icon_ethernet_w.png"
                        }
                    }
                    Rectangle{
                        id: state_battery
                        width: 65
                        height: 65
                        radius: 65
                        color: color_icon_gray
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.verticalCenterOffset: 20
                        anchors.left: parent.left
                        anchors.leftMargin: 15
                        property int state: 0
                        onStateChanged: {
                            if(state === 0){//disconnected slamnav(NONE)
                                color = color_icon_gray;
                                image_battery.source = "icon/icon_power_2.png"
                            }else if(state === 1){//power status 0 (ERROR)
                                color = color_red;
                                image_battery.source = "icon/icon_power_2.png"
                            }else if(state === 2){//charging cable connected(charging or not) (WARNING)
                                color = color_warning;
                                image_battery.source = "icon/icon_plug.png"
                            }else if(state === 3){//battery low (WARNING)
                                color = color_warning;
                                image_battery.source = "icon/icon_power_2.png"
                            }else if(state === 4){//all good
                                color = color_green;
                                image_battery.source = "icon/icon_check.png"
                            }
                        }
                        Image{
                            id: image_battery
                            anchors.centerIn: parent
                            width: 50
                            height: 50
                            sourceSize.width: width
                            sourceSize.height: height
                            source: "icon/icon_power_2.png"
                        }
                    }
                    Rectangle{
                        id: state_motor_1
                        width: 65
                        height: 65
                        radius: 65
                        color: color_icon_gray
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: 11
                        anchors.left: parent.left
                        anchors.leftMargin: 15
                        property int state: 0
                        onStateChanged: {
                            if(state === 0){//disconnected slamnav(NONE)
                                color = color_icon_gray;
                                image_motor_1.source = "icon/icon_no.png"
                            }else if(state === 1){//power state false (ERROR)
                                color = color_red;
                                image_motor_1.source = "icon/icon_power_2.png"
                            }else if(state === 2){//emergency switch pushed (ERROR)
                                color = color_red;
                                image_motor_1.source = "icon/icon_emo.png"
                            }else if(state === 3){//motor disconnected (ERROR)
                                color = color_icon_gray;
                                image_motor_1.source = "icon/icon_no.png"
                            }else if(state === 4){//motor error, not ready (ERROR)
                                color = color_red;
                                image_motor_1.source = "icon/icon_no.png"
                            }else if(state === 5){//motor lock false (WARNING)
                                color = color_warning;
                                image_motor_1.source = "icon/icon_unlock.png"
                            }else if(state === 6){//motor hot (WARNING)
                                color = color_warning;
                                image_motor_1.source = "icon/icon_fire.png"
                            }else if(state === 7){//all good
                                color = color_green;
                                image_motor_1.source = "icon/icon_check.png"
                            }
                        }
                        Image{
                            id: image_motor_1
                            anchors.centerIn: parent
                            width: 50
                            height: 50
                            sourceSize.width: width
                            sourceSize.height: height
                            source: "icon/icon_no.png"
                        }
                    }
                    Rectangle{
                        id: state_motor_2
                        width: 65
                        height: 65
                        radius: 65
                        color: color_icon_gray
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: 15
                        anchors.right: parent.right
                        anchors.rightMargin: 15
                        property int state: 0
                        onStateChanged: {
                            if(state === 0){//disconnected slamnav(NONE)
                                color = color_icon_gray;
                                image_motor_2.source = "icon/icon_no.png"
                            }else if(state === 1){//power state false (ERROR)
                                color = color_red;
                                image_motor_2.source = "icon/icon_power_2.png"
                            }else if(state === 2){//emergency switch pushed (ERROR)
                                color = color_red;
                                image_motor_2.source = "icon/icon_emo.png"
                            }else if(state === 3){//motor disconnected (ERROR)
                                color = color_icon_gray;
                                image_motor_2.source = "icon/icon_no.png"
                            }else if(state === 4){//motor error, not ready (ERROR)
                                color = color_red;
                                image_motor_2.source = "icon/icon_no.png"
                            }else if(state === 5){//motor lock false (WARNING)
                                color = color_warning;
                                image_motor_2.source = "icon/icon_unlock.png"
                            }else if(state === 6){//motor hot (WARNING)
                                color = color_warning;
                                image_motor_2.source = "icon/icon_fire.png"
                            }else if(state === 7){//all good
                                color = color_green;
                                image_motor_2.source = "icon/icon_check.png"
                            }
                        }
                        Image{
                            id: image_motor_2
                            anchors.centerIn: parent
                            width: 50
                            height: 50
                            sourceSize.width: width
                            sourceSize.height: height
                            source: "icon/icon_no.png"
                        }
                    }
                }
                Rectangle{
                    width: 450
                    height: area_setting_motor.height
                    color: "transparent"
                    Column{
                        anchors.verticalCenter: parent.verticalCenter
                        spacing: 10
                        Rectangle{
                            id: rect_robot
                            width: 450
                            height: 100
                            radius: 10
                            property int state: 0
                            onStateChanged: {
                                if(state === 0){
                                    text_robot.text = qsTr("프로그램 연결 안됨")
                                }else if(state === 1){
                                    text_robot.text = qsTr("모터 준비 안됨")
                                }else if(state === 2){
                                    text_robot.text = qsTr("위치 알 수 없음")
                                }else if(state === 3){
                                    text_robot.text = qsTr("비상전원 스위치 눌림")
                                }else if(state === 4){
                                    text_robot.text = qsTr("로봇 운행 중")
                                }else if(state === 5){
                                    text_robot.text = qsTr("충전 중")
                                }
                            }

                            color: "transparent"
                            Text{
                                id: text_robot
                                anchors.centerIn: parent
                                font.family: font_noto_b.name
                                font.pixelSize: 40
                                color: color_dark_navy
                                text:qsTr("프로그램 연결 안됨")
                            }
                        }
                        Rectangle{
                            id: state_power
                            width: 450
                            height: 400
                            radius: 10
                            clip: true
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
                                    Rectangle{
                                        id: rect_network
                                        width: 450
                                        height: 100
                                        radius: 10
                                        property int state: state_network.state
                                        onStateChanged: {
                                            text_network2.text = "";
                                            if(state === 0){//disconnected ethernet(NONE)
                                                text_network.text = qsTr("이더넷이 연결되지 않았습니다")
                                            }else if(state === 1){//connected ethernet but slamnav disconnected(ERROR)
                                                text_network.text = qsTr("프로그램과 연결되지 않았습니다")
                                            }else if(state === 2){//slamnav connected but wifi disconnected(WARNING)
                                                text_network.text = qsTr("프로그램 연결 성공")
                                                text_network2.text = qsTr("(와이파이는 연결되지 않았습니다)")
                                            }else if(state === 3){//slamnav, wifi connected but not internet(WARNING)
                                                text_network.text = qsTr("프로그램 연결 성공")
                                                text_network2.text = qsTr("(인터넷은 연결되지 않았습니다)")
                                            }else if(state === 4){//all good
                                                text_network.text = qsTr("프로그램 연결 성공")
                                            }
                                        }
                                        color: "transparent"
                                        Row{
                                            spacing: 10
                                            Rectangle{
                                                width: 50
                                                height: 50
                                                color: state_network.color
                                                anchors.verticalCenter: parent.verticalCenter
                                                radius: 50
                                                Image{
                                                    anchors.centerIn: parent
                                                    source: image_network.source
                                                    width: 40
                                                    height: 40
                                                    sourceSize.width: width
                                                    sourceSize.height: height
                                                }
                                            }
                                            Rectangle{
                                                width: 450-50-10
                                                height: 100
                                                radius : 10
                                                color: "white"
                                                Column{
                                                    anchors.centerIn: parent
                                                    Text{
                                                        id: text_network
                                                        anchors.horizontalCenter: parent.horizontalCenter
                                                        font.family: font_noto_r.name
                                                        font.pixelSize: 25
                                                        text: qsTr("이더넷이 연결되지 않았습니다")
                                                    }
                                                    Text{
                                                        id: text_network2
                                                        visible: text!==""
                                                        anchors.horizontalCenter: parent.horizontalCenter
                                                        font.family: font_noto_r.name
                                                        font.pixelSize: 20
                                                        text: ""
                                                    }
                                                }

                                            }
                                        }
                                    }
                                    Rectangle{
                                        id: rect_battery
                                        width: 450
                                        height: 100
                                        radius: 10
                                        color: "transparent"
                                        property int state: state_battery.state
                                        onStateChanged: {
                                            text_battery2.text = "";
                                            if(state === 0){
                                                text_battery.text = qsTr("프로그램과 연결되지 않았습니다")
                                            }else if(state === 1){
                                                text_battery.text = qsTr("전원이 OFF 상태입니다")
                                            }else if(state === 2){
                                                text_battery.text = qsTr("충전케이블을 분리해주세요")
                                            }else if(state === 3){
                                                text_battery.text = qsTr("배터리가 부족합니다")
                                            }else if(state === 4){
                                                text_battery.text = qsTr("배터리상태 정상")
                                            }
                                        }
                                        Row{
                                            spacing: 10
                                            Rectangle{
                                                width: 50
                                                height: 50
                                                color: state_battery.color
                                                anchors.verticalCenter: parent.verticalCenter
                                                radius: 50
                                                Image{
                                                    anchors.centerIn: parent
                                                    source: image_battery.source
                                                    width: 40
                                                    height: 40
                                                    sourceSize.width: width
                                                    sourceSize.height: height
                                                }
                                            }
                                            Rectangle{
                                                width: 450-50-10
                                                height: 100
                                                radius : 10
                                                color: "white"
                                                Column{
                                                    anchors.centerIn: parent
                                                    Text{
                                                        id: text_battery
                                                        anchors.horizontalCenter: parent.horizontalCenter
                                                        font.family: font_noto_r.name
                                                        font.pixelSize: 25
                                                        text: qsTr("프로그램과 연결되지 않았습니다")
                                                    }
                                                    Text{
                                                        id: text_battery2
                                                        visible: text!==""
                                                        anchors.horizontalCenter: parent.horizontalCenter
                                                        font.family: font_noto_r.name
                                                        font.pixelSize: 20
                                                        text: ""
                                                    }
                                                }
                                            }
                                        }
                                    }

                                    Rectangle{
                                        id: rect_localization
                                        width: 450
                                        height: 100
                                        radius: 10
                                        color: "transparent"
                                        property int state: state_localization.state
                                        onStateChanged: {
                                            text_localization2.text = "";
                                            if(state === 0){
                                                text_localization.text = qsTr("프로그램과 연결되지 않았습니다")
                                            }else if(state === 1){
                                                text_localization.text = qsTr("위치를 찾을 수 없습니다")
                                            }else if(state === 2){
                                                text_localization.text = qsTr("위치를 찾는 중입니다")
                                            }else if(state === 3){
                                                text_localization.text = qsTr("위치상태 정상")
                                            }
                                        }
                                        Row{
                                            spacing: 10
                                            Rectangle{
                                                width: 50
                                                height: 50
                                                color: state_localization.color
                                                anchors.verticalCenter: parent.verticalCenter
                                                radius: 50
                                                Image{
                                                    anchors.centerIn: parent
                                                    source: image_localization.source
                                                    width: 40
                                                    height: 40
                                                    sourceSize.width: width
                                                    sourceSize.height: height
                                                }
                                            }
                                            Rectangle{
                                                width: 450-50-10
                                                height: 100
                                                radius : 10
                                                color: "white"
                                                Column{
                                                    anchors.centerIn: parent
                                                    Text{
                                                        id: text_localization
                                                        anchors.horizontalCenter: parent.horizontalCenter
                                                        font.family: font_noto_r.name
                                                        font.pixelSize: 25
                                                        text: qsTr("프로그램과 연결되지 않았습니다")
                                                    }
                                                    Text{
                                                        id: text_localization2
                                                        visible: text!==""
                                                        anchors.horizontalCenter: parent.horizontalCenter
                                                        font.family: font_noto_r.name
                                                        font.pixelSize: 20
                                                        text: ""
                                                    }
                                                }
                                            }
                                        }
                                    }
                                    Rectangle{
                                        id: rect_motor_1
                                        width: 450
                                        height:100
                                        radius: 10
                                        color: "transparent"
                                        property int state: state_motor_1.state
                                        onStateChanged: {
                                            text_motor_11.text = "";
                                            if(state === 0){
                                                text_motor_1.text = qsTr("프로그램과 연결되지 않았습니다")
                                            }else if(state === 1){
                                                text_motor_1.text = qsTr("전원이 OFF 상태입니다")
                                            }else if(state === 2){
                                                text_motor_1.text = qsTr("비상스위치가 눌려있습니다")
                                            }else if(state === 3){
                                                text_motor_1.text = qsTr("모터와 연결되지 않았습니다")
                                            }else if(state === 4){
                                                text_motor_1.text = qsTr("모터에 에러가 발생했습니다")
                                                text_motor_11.text = supervisor.getMotorStatusStr(0);
                                            }else if(state === 5){
                                                text_motor_1.text = qsTr("모터락이 해제되었습니다")
                                            }else if(state === 6){
                                                text_motor_1.text = qsTr("모터온도가 기준치 이상입니다")
                                            }else if(state === 7){
                                                text_motor_1.text = qsTr("모터상태 정상")
                                            }
                                        }
                                        Row{
                                            spacing: 10
                                            Rectangle{
                                                width: 50
                                                height: 50
                                                color: state_motor_1.color
                                                anchors.verticalCenter: parent.verticalCenter
                                                radius: 50
                                                Image{
                                                    anchors.centerIn: parent
                                                    source: image_motor_1.source
                                                    width: 40
                                                    height: 40
                                                    sourceSize.width: width
                                                    sourceSize.height: height
                                                }
                                            }
                                            Rectangle{
                                                width: 450-50-10
                                                height: 100
                                                radius : 10
                                                color: "white"
                                                Column{
                                                    anchors.centerIn: parent
                                                    Text{
                                                        id: text_motor_1
                                                        anchors.horizontalCenter: parent.horizontalCenter
                                                        font.family: font_noto_r.name
                                                        font.pixelSize: 25
                                                        text: qsTr("프로그램과 연결되지 않았습니다")
                                                    }
                                                    Text{
                                                        id: text_motor_11
                                                        visible: text!==""
                                                        anchors.horizontalCenter: parent.horizontalCenter
                                                        font.family: font_noto_r.name
                                                        font.pixelSize: 20
                                                        text: ""
                                                    }
                                                }
                                            }
                                        }
                                    }

                                    Rectangle{
                                        id: rect_motor_2
                                        width: 450
                                        height: 100
                                        radius: 10
                                        color: "transparent"
                                        property int state: state_motor_2.state
                                        onStateChanged: {
                                            text_motor_22.text = "";
                                            if(state === 0){
                                                text_motor_2.text = qsTr("프로그램과 연결되지 않았습니다")
                                            }else if(state === 1){
                                                text_motor_2.text = qsTr("전원이 OFF 상태입니다")
                                            }else if(state === 2){
                                                text_motor_2.text = qsTr("비상스위치가 눌려있습니다")
                                            }else if(state === 3){
                                                text_motor_2.text = qsTr("모터와 연결되지 않았습니다")
                                            }else if(state === 4){
                                                text_motor_2.text = qsTr("모터에 에러가 발생했습니다")
                                                text_motor_22.text = supervisor.getMotorStatusStr(1);
                                            }else if(state === 5){
                                                text_motor_2.text = qsTr("모터락이 해제되었습니다")
                                            }else if(state === 6){
                                                text_motor_2.text = qsTr("모터온도가 기준치 이상입니다")
                                            }else if(state === 7){
                                                text_motor_2.text = qsTr("모터상태 정상")
                                            }
                                        }
                                        Row{
                                            spacing: 10
                                            Rectangle{
                                                width: 50
                                                height: 50
                                                anchors.verticalCenter: parent.verticalCenter
                                                color: state_motor_2.color
                                                radius: 50
                                                Image{
                                                    anchors.centerIn: parent
                                                    source: image_motor_2.source
                                                    width: 40
                                                    height: 40
                                                    sourceSize.width: width
                                                    sourceSize.height: height
                                                }
                                            }
                                            Rectangle{
                                                width: 450-50-10
                                                height: 100
                                                radius : 10
                                                color: "white"
                                                Column{
                                                    anchors.centerIn: parent
                                                    Text{
                                                        id: text_motor_2
                                                        anchors.horizontalCenter: parent.horizontalCenter
                                                        font.family: font_noto_r.name
                                                        font.pixelSize: 25
                                                        text: qsTr("프로그램과 연결되지 않았습니다")
                                                    }
                                                    Text{
                                                        id: text_motor_22
                                                        visible: text!==""
                                                        anchors.horizontalCenter: parent.horizontalCenter
                                                        font.family: font_noto_r.name
                                                        font.pixelSize: 20
                                                        text: ""
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
                    supervisor.playSound('click', slider_volume_button.value);
                    if(debug_count++ > 3){
                        debug_count = 0;
                        popup_robot_details.open();
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
            anchors.topMargin: 60
            color: "white"
            radius: 30
            property bool is_restart: false
            Image{
                source:"icon/btn_menu.png"
                scale: 1-(120-parent.width)/120
                anchors.centerIn: parent
            }
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    supervisor.playSound('click', slider_volume_button.value);;
                    supervisor.writelog("[UI] MAP : move to backPage");
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
                //color:"transparent"
                color: color_red
                border.width: 1
                //border.color: "#7e7e7e"
                border.color: color_red
                Text{
                    anchors.centerIn: parent
                    text:qsTr("관리자 메뉴")
                    font.family: font_noto_r.name
                    font.pixelSize: 25
                    color: "white"
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked:{
                        supervisor.playSound('click', slider_volume_button.value);
                        supervisor.writelog("[USER INPUT] SETTING PAGE -> SHOW MANAGER MENU");
                        if(is_admin){
                            popup_manager.open();
                        }else{
                            popup_password.open_menu = true;
                            popup_password.open();
                        }
                    }
                }
            }
            Rectangle{
                id: btn_default
                width: 180
                height: 60
                radius: 10
                visible: is_admin || is_rainbow
                //color:"transparent"
                color:color_navy
                border.width: 1
                //border.color: "#7e7e7e"
                border.color: color_navy
                Text{
                    anchors.centerIn: parent
                    text:qsTr("설정 초기화")
                    font.family: font_noto_r.name
                    font.pixelSize: 25
                    color : "white"
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked:{
                        supervisor.playSound('click', slider_volume_button.value);
                        supervisor.writelog("[USER INPUT] SETTING PAGE -> RESET DEFAULT");
                        init();
                    }
                }
            }
            Rectangle{
                id: btn_manual
                width: 180
                height: 60
                radius: 10
                //visible: is_admin
                //color:"transparent"
                color: color_blue
                border.width: 1
                //border.color: "#7e7e7e"
                border.color: color_blue
                Text{
                    anchors.centerIn: parent
                    text:qsTr("매뉴얼")
                    font.family: font_noto_r.name
                    font.pixelSize: 25
                    color: "white"
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked:{
                        supervisor.playSound('click', slider_volume_button.value);
                        supervisor.writelog("[USER INPUT] SETTING PAGE -> SHOW MANUAL MENU");
                        if(is_admin){
                            popup_manual_detail.open();
                        }else{
                            //popup_password.open_menu = true;
                            //popup_password.open();
                            popup_manual.open();
                        }
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
                    text:qsTr("확인")
                    font.family: font_noto_r.name
                    font.pixelSize: 25
                    color: "white"
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked:{
                        console.log("?????????"+slider_volume_button.value);
                        supervisor.playSound('click', slider_volume_button.value);
                        save();
                    }
                }
            }



            Rectangle{
                id: btn_version
                width: 180
                height: 60
                radius: 10
                color: "transparent"
                Text{
                    anchors.centerIn: parent
                    text:qsTr("Version 1.1.8") // 설정초기화 숨김,
                    font.family: font_noto_r.name
                    font.pixelSize: 25
                    color: "black"
                }
            }
        }
    }

    Timer{
        running: true
        interval: 500
        repeat: true
        triggeredOnStart: true
        onTriggered: {

//            if(supervisor.getusbsize() > 0){
//                btn_usb_download.enabled = true;
//            }else{
//                btn_usb_download.enabled = false;
//            }

            //origin(use ExtProcess)
//            wifi_con.connection = supervisor.getWifiConnection("");
//            wifi_ssid.text = supervisor.getCurWifiSSID();
//            if(wifi_con.connection === 0 && supervisor.getCurWifiSSID() !== "" && supervisor.getcurIP() === ""){
//                supervisor.getWifiIP();
//            }

            //new(use Checker)
            wifi_con.connection = supervisor.getWifiConnection();
            ethernet_con.connection = supervisor.getEthernetConnection();
            internet_con.connection = supervisor.getInternetConnection();
            wifi_ssid.text = supervisor.getCurWifiSSID();

            motor_left_id = parseInt(supervisor.getSetting("update","MOTOR","left_id"));
            motor_right_id = parseInt(supervisor.getSetting("update","MOTOR","right_id"));


            if(supervisor.getEthernetConnection() === 2){
                if(supervisor.getIPCConnection()){
                    if(supervisor.getWifiConnection() === 2){
                        if(supervisor.getInternetConnection() === 2){
                            state_network.state = 4;
                        }else{
                            state_network.state = 3;
                        }
                    }else{
                        state_network.state = 2;
                    }
                }else{
                    state_network.state = 1;
                }
            }else{
                state_network.state = 0;
            }

            //로봇 상태 - 로봇 상태
            if(supervisor.getIPCConnection()){
                //로봇 상태 - 전원
                if(supervisor.getPowerStatus() === 0){
                    state_battery.state = 1;
                    state_motor_1.state = 1;
                    state_motor_2.state = 1;
                }else{

                    if(supervisor.getChargeConnectStatus() === 1){
                        state_battery.state = 2;
                    }else{
                        if(supervisor.getBattery() < 30){
                            state_battery.state = 3;
                        }else{
                            state_battery.state = 4;
                        }
                    }

                    //모터 상태 - 모터 1
                    var motorcon1 = supervisor.getMotorConnection(0);
                    //모터 상태 - 모터 2
                    var motorcon2 = supervisor.getMotorConnection(1);

                    if(motorcon1 && motorcon2){
                        var lstate = supervisor.getLockStatus();
                        if(supervisor.getChargeConnectStatus() !== 0){
                        }else if(lstate === 0){
                        }else{
                            var state1 = supervisor.getMotorStatus(0);
                            if(state1 === 0){
                            }else if(state1 === 1){
                            }else{
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
                            }

                            var state2 = supervisor.getMotorStatus(1);
                            if(state2 === 0){
                            }else if(state2 === 1){
                            }else{
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


                    if(supervisor.getEmoStatus() === 1){
                        state_motor_1.state = 2;
                        state_motor_2.state = 2;
                    }else{
                        if(motorcon1 === 0){
                            state_motor_1.state = 3;
                        }else if(supervisor.getLockStatus() === 0){
                            state_motor_1.state = 5;
                        }else if(supervisor.getMotorStatus(0) === 1){
                            if(supervisor.getMotorTemperature(0) > supervisor.getMotorWarningTemperature()){
                                state_motor_1.state = 6;
                            }else{
                                state_motor_1.state = 7;
                            }
                        }else{
                            state_motor_1.state = 4;
                        }

                        if(motorcon2 === 0){
                            state_motor_2.state = 3;
                        }else if(supervisor.getLockStatus() === 0){
                            state_motor_2.state = 5;
                        }else if(supervisor.getMotorStatus(1) === 1){
                            if(supervisor.getMotorTemperature(1) > supervisor.getMotorWarningTemperature()){
                                state_motor_2.state = 6;
                            }else{
                                state_motor_2.state = 7;
                            }
                        }else{
                            state_motor_2.state = 4;
                        }
                    }

                    bar_temp1.value = supervisor.getMotorTemperature(0);
                    bar_mtemp1.value = supervisor.getMotorInsideTemperature(0);
                    bar_cur1.value = supervisor.getMotorCurrent(0);
                    bar_temp2.value = supervisor.getMotorTemperature(1);
                    bar_mtemp2.value = supervisor.getMotorInsideTemperature(1);
                    bar_cur2.value = supervisor.getMotorCurrent(1);
                }


                if(supervisor.getLocalizationState() === 2 && supervisor.getMotorState(0) === 1 && supervisor.getMotorState(1) === 1){
                    if(supervisor.getChargeStatus() === 1){
                        rect_robot.state = 5;
                    }else{
                        rect_robot.state = 4;
                    }
                }else{
                    if(supervisor.getEmoStatus() === 1){
                        rect_robot.state = 3;
                    }else if(supervisor.getLocalizationState() !== 2){
                        rect_robot.state = 2;
                    }else{
                        rect_robot.state = 1;
                    }
                }

                bar_battery_in.value = supervisor.getBatteryIn().toFixed(2);
                bar_battery_out.value = supervisor.getBatteryOut().toFixed(2);
                bar_battery_cur.value = supervisor.getBatteryCurrent().toFixed(2);

                bar_power.value = supervisor.getPower().toFixed(3);
                bar_powert.value = supervisor.getPowerTotal().toFixed(3);

                var state = supervisor.getLocalizationState();
                if(state === 2){
                    state_localization.state = 3;
                }else if(state === 1){
                    state_localization.state = 2;
                }else{
                    state_localization.state = 1;
                }

            }else{
                rect_robot.state = 0;
                state_localization.state = 0;
                state_power.state = 0;
                state_motor_1.state = 0;
                state_motor_2.state = 0;

                if(supervisor.getEthernetConnection() === 2){
                    state_network.state = 1;
                }else{
                    state_network.state = 0;
                }
                text_robot.text = qsTr("프로그램 연결 안됨")
            }

        }
    }

    Popup_help{
        id: popup_help_setting
    }

    Popup{
        id: popup_set_goqual
        anchors.centerIn: parent
        width: 1000
        height: 700
        background: Rectangle{
            anchors.fill: parent
            color: "transparent"
        }
        onOpened:{
            supervisor.getGoqualDeviceList();
            model_goqual_deivce.clear();
            goqual_timer.start();
        }
        onClosed:{
            goqual_timer.stop();
        }

        Timer{
            id: goqual_timer
            running: false
            repeat: true
            interval: 500
            onTriggered:{
                supervisor.getGoqualDeviceList();
                text_goqual_access_key.text = supervisor.getGoqualAccessKey();
                text_goqual_refresh_key.text = supervisor.getGoqualRefreshKey();
                text_goqual_expires_in.text = supervisor.getGoqualExpiresIn();

                for(var i=0; i<supervisor.getGoqualDeviceSize(); i++){
                    var match = false;
                    for(var j=0; j<model_goqual_deivce.count; j++){
                        if(model_goqual_deivce.get(j).id === supervisor.getGoqualDeviceID(i)){
                            match = true;
                            break;
                        }
                    }
                    if(!match){
                        model_goqual_deivce.append({"id":supervisor.getGoqualDeviceID(i),"type":supervisor.getGoqualDeviceType(i),"name":supervisor.getGoqualDeviceName(i),"online":supervisor.getGoqualDeviceOnline(i),"dev_state":supervisor.getGoqualDeviceState(i)});
                    }else{
                        model_goqual_deivce.set(i,{"id":supervisor.getGoqualDeviceID(i),"type":supervisor.getGoqualDeviceType(i),"name":supervisor.getGoqualDeviceName(i),"online":supervisor.getGoqualDeviceOnline(i),"dev_state":supervisor.getGoqualDeviceState(i)})
                    }
                }
            }
        }

        Rectangle{
            width: parent.width
            height: parent.height
            Column{
                anchors.fill: parent
                spacing: 30
                Rectangle{
                    width: parent.width
                    height: 70
                    color: color_dark_navy
                    Text{
                        anchors.centerIn: parent
                        text: qsTr("Goqual(헤이홈) 연동")
                        color: "white"
                        font.bold: true
                        font.pixelSize: 30
                    }
                }
                Rectangle{
                    width: parent.width
                    height: 200
                    color: color_light_gray
                    Row{
                        anchors.centerIn: parent
                        spacing: 40
                        Grid{
                            anchors.verticalCenter: parent.verticalCenter
                            columns: 3
                            rows: 3
                            horizontalItemAlignment: Grid.AlignHCenter
                            verticalItemAlignment: Grid.AlignVCenter
                            spacing: 10
                            Text{
                                text: "access_key"
                                font.bold: true
                                font.pixelSize: 20
                            }
                            Text{
                                text: " : "
                                font.pixelSize: 20
                            }
                            Text{
                                id: text_goqual_access_key
                                font.pixelSize: 20
                            }
                            Text{
                                text: "refresh_key"
                                font.bold: true
                                font.pixelSize: 20
                            }
                            Text{
                                text: " : "
                                font.pixelSize: 20
                            }
                            Text{
                                id: text_goqual_refresh_key
                                font.pixelSize: 20
                            }
                            Text{
                                text: "expires_in"
                                font.bold: true
                                font.pixelSize: 20
                            }
                            Text{
                                text: " : "
                                font.pixelSize: 20
                            }
                            Text{
                                id: text_goqual_expires_in
                                font.pixelSize: 20
                            }
                        }

                        Column{
                            anchors.verticalCenter: parent.verticalCenter
                            spacing: 20
                            Item_buttons{
                                type: "white_btn"
                                text: qsTr("get Key")
                                width: 160
                                height: 50
                                onClicked:{
                                    supervisor.playSound('click', slider_volume_button.value);
                                    supervisor.getGoqualKey();
                                }
                            }
                            Item_buttons{
                                type: "white_btn"
                                text: qsTr("refresh Key")
                                width: 160
                                height: 50
                                onClicked:{
                                    supervisor.playSound('click', slider_volume_button.value);
                                    supervisor.refreshGoqualKey();
                                }
                            }
                        }
                        Text{
                            id: text_goqual_error
                            color: color_red
                            text: ""
                        }
                    }
                }

                Rectangle{
                    width: parent.width
                    height: 370
                    Column{
                        anchors.horizontalCenter: parent.horizontalCenter
                        spacing: 20
                        Row{
                            anchors.left: parent.left
                            anchors.leftMargin: 50
                            spacing: 20
                            Text{
                                text: qsTr("타입 : ")
                                font.pixelSize: 20
                            }
                            ComboBox{
                                width: 300
                                model:["RelayControllerDc2"]
                            }
                        }

                        Column{
                            anchors.horizontalCenter: parent.horizontalCenter
                            spacing: 4
                            Row{
                                anchors.horizontalCenter: parent.horizontalCenter
                                spacing: 4
                                Rectangle{
                                    width: 96
                                    height: 40
                                    color: color_navy
                                    Text{
                                        anchors.centerIn: parent
                                        text: "State"
                                        color: "white"
                                    }
                                }
                                Rectangle{
                                    width: 210
                                    height: 40
                                    color: color_navy
                                    Text{
                                        anchors.centerIn: parent
                                        text: "Name"
                                        color: "white"
                                    }
                                }
                                Rectangle{
                                    width: 220
                                    height: 40
                                    color: color_navy
                                    Text{
                                        anchors.centerIn: parent
                                        text: "ID"
                                        color: "white"
                                    }
                                }
                                Rectangle{
                                    width: 240
                                    height: 40
                                    color: color_navy
                                    Text{
                                        anchors.centerIn: parent
                                        text: "switch"
                                        color: "white"
                                    }
                                }
                            }

                            Repeater{
                                model: ListModel{id:model_goqual_deivce}
                                Row{
                                    Row{
                                        Rectangle{
                                            width: 100
                                            height: 40
                                            color: "transparent"
                                            Rectangle{
                                                anchors.centerIn: parent
                                                width: 35
                                                height: 35
                                                radius: 35
                                                border.width: 3
                                                border.color: color_navy
                                                color: {
                                                    if(online){
                                                        if(dev_state){
                                                            color_green
                                                        }else{
                                                            color_gray
                                                        }
                                                    }else{
                                                        color_red
                                                    }
                                                }
                                            }
                                        }
                                        Rectangle{
                                            width: 214
                                            height: 40
                                            Text{
                                                anchors.centerIn: parent
                                                text: name
                                                Component.onCompleted: {
                                                    scale = 1;
                                                    while(width*scale > parent.width*0.8){
                                                        scale=scale-0.01;
                                                    }
                                                }
                                            }
                                        }
                                        Rectangle{
                                            width: 224
                                            height: 40
                                            Text{
                                                anchors.centerIn: parent
                                                text: id
                                                Component.onCompleted: {
                                                    scale = 1;
                                                    while(width*scale > parent.width*0.8){
                                                        scale=scale-0.01;
                                                    }
                                                }
                                            }
                                        }
                                        Rectangle{
                                            width: 244
                                            height: 40
                                            Row{
                                                anchors.centerIn: parent
                                                spacing: 20
                                                Buttons{
                                                    style: "dark_navy"
                                                    text: qsTr("on")
                                                    width: 100
                                                    height: 40
                                                    onClicked:{
                                                        supervisor.playSound('click', slider_volume_button.value);
                                                        supervisor.setGoqualDevice(id,true);
                                                    }
                                                }
                                                Buttons{
                                                    style: "dark_navy"
                                                    text: qsTr("off")
                                                    width: 100
                                                    height: 40
                                                    onClicked:{
                                                        supervisor.playSound('click', slider_volume_button.value);
                                                        supervisor.setGoqualDevice(id,false);
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

    Popup{
        id: popup_lingbell
        anchors.centerIn: parent
        width: 400
        height: 400
        background: Rectangle{
            anchors.fill: parent
            color: "transparent"
        }
        Rectangle{
            width: parent.width
            height: parent.height
            color: color_light_gray
            Column{
                anchors.centerIn: parent
                spacing: 20
                TextField{
                    id: field_lingbell_callnum
                    text: "FFEEDD"
                    width: 200
                    height: 50
                }
                Item_buttons{
                    type: "round_text"
                    width: 160
                    height: 50
                    text: "CALL"
                    onClicked:{
                        supervisor.callCallbell(field_lingbell_callnum.text);
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
                            text:qsTr("전  원")
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
                                text:qsTr("입력전원")
                                font.family: font_noto_r.name
                                font.pixelSize: 15
                            }
                            Text{
                                text:qsTr("출력전원")
                                font.family: font_noto_r.name
                                font.pixelSize: 15
                            }
                            Text{
                                text:qsTr("전   류")
                                font.family: font_noto_r.name
                                font.pixelSize: 15
                            }
                            Text{
                                text:qsTr("순간전력")
                                font.family: font_noto_r.name
                                font.pixelSize: 15
                            }
                            Text{
                                text:qsTr("누적전력")
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
                                text:qsTr("충전 상태")
                                font.family: font_noto_r.name
                                font.pixelSize: 15
                            }
                            Text{
                                text:qsTr("전원 공급")
                                font.family: font_noto_r.name
                                font.pixelSize: 15
                            }
                            Text{
                                text:qsTr("비상스위치")
                                font.family: font_noto_r.name
                                font.pixelSize: 15
                            }
                            Text{
                                text:qsTr("원격스위치")
                                font.family: font_noto_r.name
                                font.pixelSize: 15
                            }
                            Text{
                                text:qsTr("모터 락")
                                font.family: font_noto_r.name
                                font.pixelSize: 15
                            }
                            Text{
                                text:qsTr("그리기")
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
                                    text:qsTr("연결 안됨")
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
                                    text:qsTr("공급 안됨")
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
                                    text:qsTr("안 눌림")
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
                                    text:qsTr("안 눌림")
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
                                    text:qsTr("풀림")
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
                                    text:qsTr("멈춤")
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
                            text:qsTr("모터 상태")
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
                                    text:qsTr("모터 1")
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
                                    text:qsTr("연결상태")
                                    font.family: font_noto_r.name
                                    font.pixelSize: 15
                                }
                                Text{
                                    text:qsTr("상 태")
                                    font.family: font_noto_r.name
                                    font.pixelSize: 15
                                }
                                Text{
                                    text:qsTr("제어기 온도")
                                    font.family: font_noto_r.name
                                    font.pixelSize: 15
                                }
                                Text{
                                    text:qsTr("모터 온도")
                                    font.family: font_noto_r.name
                                    font.pixelSize: 15
                                }
                                Text{
                                    text:qsTr("전  류")
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
                                        text:qsTr("연결 안됨")
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
                                        text:qsTr("준비 안됨")
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
                                        text: parent.value + qsTr(" 도")
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
                                        text: parent.value + qsTr(" 도")
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
                                    text:qsTr("모터 2")
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
                                    text:qsTr("연결상태")
                                    font.family: font_noto_r.name
                                    font.pixelSize: 15
                                }
                                Text{
                                    text:qsTr("상 태")
                                    font.family: font_noto_r.name
                                    font.pixelSize: 15
                                }
                                Text{
                                    text:qsTr("제어기 온도")
                                    font.family: font_noto_r.name
                                    font.pixelSize: 15
                                }
                                Text{
                                    text:qsTr("모터 온도")
                                    font.family: font_noto_r.name
                                    font.pixelSize: 15
                                }
                                Text{
                                    text:qsTr("전  류")
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
                                        text:qsTr("연결 안됨")
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
                                        text:qsTr("준비 안됨")
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
                                        text: parent.value + qsTr(" 도")
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
                                        text: parent.value + qsTr(" 도")
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
                            text:qsTr("센서 상태")
                            color: "white"
                            font.pixelSize: 20
                        }
                    }
                    Item_buttons{
                        type: "round_text"
                        text:qsTr("뷰 어")
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
        height: 600
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
            radius: 10
            clip: true
            anchors.centerIn: parent
            width: parent.width*0.99
            height: parent.height*0.99

            Rectangle{
                color: color_red
                radius: 10
                id: rect_prd_top
                width: parent.width
                height: 80
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                Rectangle{
                    color: color_dark_navy
                    width: parent.width
                    height: parent.radius
                    anchors.bottom: parent.bottom
                }
                Text{
                    anchors.centerIn: parent
                    color: "white"
                    font.family: font_noto_b.name
                    font.pixelSize: 40
                    text: qsTr("관리자 메뉴")
                }
            }
            Flickable{
                width: parent.width
                height: parent.height-80
                anchors.bottom: parent.bottom
                contentHeight: grid_manager.height
                clip: false
                Grid{
                    id: grid_manager
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.verticalCenterOffset: 40
                    rows: 3
                    columns: 2
                    spacing: 30
                    Rectangle{
                        id: btn_update
                        width: 170
                        height: 150
                        radius: 20
                        color:color_green
                        Rectangle{
                            anchors.centerIn: parent
                            width: 160
                            height: 140
                            radius: 20
                            color:"transparent"
                            border.width: 1
                            border.color: "white"
                            Column{
                                anchors.centerIn: parent
                                spacing: 15
                                Image{
                                    source: "icon/icon_researching.png"
                                    width: 40
                                    height: 40
                                    sourceSize.width: width
                                    sourceSize.height: height
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    ColorOverlay{
                                        anchors.fill: parent
                                        source: parent
                                        color: "white"
                                    }
                                }

                                Text{
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    text: qsTr("프로그램 업데이트")
                                    color: "white"
                                    font.family: font_noto_r.name
                                    font.pixelSize: 20
                                }
                            }
                        }
                        MouseArea{
                            anchors.fill: parent
                            onClicked:{
                                supervisor.playSound('click', slider_volume_button.value);
                                supervisor.writelog("[USER INPUT] SETTING PAGE -> PROGRAM UPDATE");
                                popup_update.open();
                            }
                        }
                    }

                    Rectangle{
                        id: btn_log
                        width: 170
                        height: 150
                        radius: 20
                        color:color_navy
                        //visible: false
                        visible: false
                        Rectangle{
                            anchors.centerIn: parent
                            width: 160
                            height: 140
                            radius: 20
                            color:"transparent"
                            border.width: 1
                            border.color: "white"
                            Column{
                                anchors.centerIn: parent
                                spacing: 15
                                Image{
                                    source: "icon/icon_bookmark.png"
                                    width: 40
                                    height: 40
                                    sourceSize.width: width
                                    sourceSize.height: height
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    ColorOverlay{
                                        anchors.fill: parent
                                        source: parent
                                        color: "white"
                                    }
                                }

                                Text{
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    text:qsTr("로그 확인")
                                    color: "white"
                                    font.family: font_noto_r.name
                                    font.pixelSize: 20
                                }
                            }

                        }
                        MouseArea{
                            anchors.fill: parent
                            onClicked:{
                                supervisor.playSound('click', slider_volume_button.value);
                                supervisor.writelog("[USER INPUT] SETTING PAGE -> LOG");
                                loader_page.source = plog;
                            }
                        }
                    }


                    Rectangle{
                        id: btn_usb_upload
                        width: 170
                        height: 150
                        radius: 20
                        //visible: false
                        visible: is_admin
                        color: enabled?color_navy:color_light_gray
                        Rectangle{
                            anchors.centerIn: parent
                            width: 160
                            height: 140
                            radius: 20
                            color:"transparent"
                            border.width: 1
                            border.color: "white"
                            Column{
                                anchors.centerIn: parent
                                spacing: 15
                                Image{
                                    source: "icon/save_r.png"
                                    width: 40
                                    height: 40
                                    sourceSize.width: width
                                    sourceSize.height: height
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    ColorOverlay{
                                        anchors.fill: parent
                                        source: parent
                                        color: "white"
                                    }
                                }

                                Text{
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    text: qsTr("USB에 저장하기")
                                    color: "white"
                                    font.family: font_noto_r.name
                                    font.pixelSize: 20
                                }
                            }

                        }
                        MouseArea{
                            anchors.fill: parent
                            onClicked:{
                                supervisor.playSound('click', slider_volume_button.value);
                                supervisor.writelog("[USER INPUT] SETTING PAGE -> SAVE TO USB");
                                popup_usb_select.open();
                            }
                        }
                    }


                    Rectangle{ // USB에서 받아오기
                        id: btn_usb_download
                        width: 170
                        height: 150
                        radius: 20
                        // visible: false
                        visible: is_admin
                        //color: enabled?color_navy:color_light_gray
                        color: color_navy
                        Rectangle{
                            anchors.centerIn: parent
                            width: 160
                            height: 140
                            radius: 20
                            color:"transparent"
                            border.width: 1
                            border.color: "white"
                            Column{
                                anchors.centerIn: parent
                                spacing: 15
                                Image{
                                    source: "icon/load_r.png"
                                    width: 40
                                    height: 40
                                    sourceSize.width: width
                                    sourceSize.height: height
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    ColorOverlay{
                                        anchors.fill: parent
                                        source: parent
                                        color: "white"
                                    }
                                }

                                Text{
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    text: qsTr("USB에서 받아오기")
                                    color: "white"
                                    font.family: font_noto_r.name
                                    font.pixelSize: 20
                                }
                            }

                        }
                        MouseArea{
                            anchors.fill: parent
                            onClicked:{
                                supervisor.playSound('click', slider_volume_button.value);
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
                        width: 170
                        height: 150
                        radius: 20
                        color: color_navy
                        Rectangle{
                            anchors.centerIn: parent
                            width: 160
                            height: 140
                            radius: 20
                            color:"transparent"
                            border.width: 1
                            border.color: "white"
                            Column{
                                anchors.centerIn: parent
                                spacing: 15
                                Image{
                                    source: "icon/icon_run.png"
                                    width: 40
                                    height: 40
                                    sourceSize.width: width
                                    sourceSize.height: height
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    ColorOverlay{
                                        anchors.fill: parent
                                        source: parent
                                        color: "white"
                                    }
                                }

                                Text{
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    text: qsTr("자율주행 재시작") //SLAM 재시작
                                    color: "white"
                                    font.family: font_noto_r.name
                                    font.pixelSize: 20
                                }
                            }

                        }
                        MouseArea{
                            anchors.fill: parent
                            onClicked:{
                                supervisor.playSound('click', slider_volume_button.value);
                                supervisor.writelog("[UI] SETTING PAGE -> KILL SLAM");
                                supervisor.restartSLAM();
                            }
                        }
                    }
                    Rectangle{
                        id: btn_edit_passwd
                        width: 170
                        height: 150
                        radius: 20
                        color: color_navy
                        visible: false
                        Rectangle{
                            anchors.centerIn: parent
                            width: 160
                            height: 140
                            radius: 20
                            color:"transparent"
                            border.width: 1
                            border.color: "white"
                            Column{
                                anchors.centerIn: parent
                                spacing: 15
                                Image{
                                    source: "icon/image_setting.png"
                                    width: 40
                                    height: 40
                                    sourceSize.width: width
                                    sourceSize.height: height
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    ColorOverlay{
                                        anchors.fill: parent
                                        source: parent
                                        color: "white"
                                    }
                                }

                                Text{
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    text: qsTr("비밀번호 변경")
                                    color: "white"
                                    font.family: font_noto_r.name
                                    font.pixelSize: 20
                                }
                            }

                        }
                        MouseArea{
                            anchors.fill: parent
                            onClicked:{
                                supervisor.playSound('click', slider_volume_button.value);
                                supervisor.writelog("[USER INPUT] SETTING PAGE -> SAVE TO USB");
                                popup_password.open();
                                popup_password.is_editmode = true;
                            }
                        }
                    }

                    Rectangle{
                        id: btn_all_init
                        width: 170
                        height: 150
                        radius: 20
                        visible: is_rainbow
                        color: color_red
                        Rectangle{
                            anchors.centerIn: parent
                            width: 160
                            height: 140
                            radius: 20
                            color:"transparent"
                            border.width: 2
                            border.color: "white"
                            Column{
                                anchors.centerIn: parent
                                spacing: 15
                                Image{
                                    source: "icon/icon_researching.png"
                                    width: 40
                                    height: 40
                                    sourceSize.width: width
                                    sourceSize.height: height
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    ColorOverlay{
                                        anchors.fill: parent
                                        source: parent
                                        color: "white"
                                    }
                                }

                                Text{
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    text: qsTr("공장 초기화")
                                    color: "white"
                                    font.family: font_noto_r.name
                                    font.pixelSize: 20
                                }
                            }

                        }
                        MouseArea{
                            anchors.fill: parent
                            onClicked:{
                                supervisor.playSound('click', slider_volume_button.value);
                                supervisor.writelog("[USER INPUT] RESET ALL -> REMOVE ALL");
                                popup_clear.open();
                            }
                        }
                    }

                    Rectangle{
                        id: btn_save_setting
                        width: 170
                        height: 150
                        radius: 20
                        visible: is_rainbow
                        color: color_red
                        Rectangle{
                            anchors.centerIn: parent
                            width: 160
                            height: 140
                            radius: 20
                            color:"transparent"
                            border.width: 2
                            border.color: "white"
                            Column{
                                anchors.centerIn: parent
                                spacing: 15
                                Image{
                                    source: "icon/icon_save.png"
                                    width: 40
                                    height: 40
                                    sourceSize.width: width
                                    sourceSize.height: height
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    ColorOverlay{
                                        anchors.fill: parent
                                        source: parent
                                        color: "white"
                                    }
                                }

                                Text{
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    text: qsTr("세팅 저장")
                                    color: "white"
                                    font.family: font_noto_r.name
                                    font.pixelSize: 20
                                }
                            }

                        }
                        MouseArea{
                            anchors.fill: parent
                            onClicked:{
                                supervisor.playSound('click', slider_volume_button.value);
                                supervisor.writelog("[USER INPUT] save Setting");
                                supervisor.saveSetting();
                                popup_manager.close();
                            }
                        }
                    }

                    Rectangle{
                        id: btn_load_setting
                        width: 170
                        height: 150
                        radius: 20
                        visible: is_admin
                        color: color_red
                        Rectangle{
                            anchors.centerIn: parent
                            width: 160
                            height: 140
                            radius: 20
                            color:"transparent"
                            border.width: 2
                            border.color: "white"
                            Column{
                                anchors.centerIn: parent
                                spacing: 15
                                Image{
                                    source: "icon/icon_save2.png"
                                    width: 40
                                    height: 40
                                    sourceSize.width: width
                                    sourceSize.height: height
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    ColorOverlay{
                                        anchors.fill: parent
                                        source: parent
                                        color: "white"
                                    }
                                }

                                Text{
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    text: qsTr("세팅 불러오기")
                                    color: "white"
                                    font.family: font_noto_r.name
                                    font.pixelSize: 20
                                }
                            }

                        }
                        MouseArea{
                            anchors.fill: parent
                            onClicked:{
                                supervisor.playSound('click', slider_volume_button.value);
                                popup_load_setting.open();
                            }
                        }
                    }
                }
            }
        }
    }

    Popup{
        id: popup_load_setting
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
        Rectangle{
            width: parent.width
            height: parent.height
            color: color_navy
            Column{
                anchors.centerIn: parent
                spacing: 40
                Text{
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.family: font_noto_r.name
                    font.pixelSize: 50
                    color: "white"
                    text: qsTr("저장된 초기세팅을 불러오겠습니까?")
                }
                Row{
                    anchors.horizontalCenter: parent.horizontalCenter
                    spacing: 20
                    Rectangle{
                        width: 180
                        height: 60
                        radius: 10
                        color: "#12d27c"
                        border.width: 1
                        border.color: "#12d27c"
                        Text{
                            anchors.centerIn: parent
                            text: qsTr("불러오기")
                            font.family: font_noto_r.name
                            font.pixelSize: 25
                            color: "white"
                        }
                        MouseArea{
                            anchors.fill: parent
                            onClicked: {
                                supervisor.playSound('click', slider_volume_button.value);
                                supervisor.writelog("[USER INPUT] load Setting");
                                supervisor.loadSetting();
                                popup_load_setting.close();
                                popup_manager.close();
                                init();
                            }
                        }
                    }
                    Rectangle{
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
                                supervisor.playSound('click', slider_volume_button.value);
                                popup_load_setting.close();
                            }
                        }
                    }

                }
            }
        }
    }

    Popup{
        id: popup_manual
        width: 500
        height: 600
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
            radius: 10
            clip: true
            anchors.centerIn: parent
            width: parent.width*0.99
            height: parent.height*0.99
            Rectangle{
                color: color_blue
                radius: 10
                id: rect_prd_top2
                width: parent.width
                height: 80
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                Rectangle{
                    color: color_dark_navy
                    width: parent.width
                    height: parent.radius
                    anchors.bottom: parent.bottom
                }
                Text{
                    anchors.centerIn: parent
                    color: "white"
                    font.family: font_noto_b.name
                    font.pixelSize: 40
                    text: qsTr("서빙로봇 매뉴얼")
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
                    id: btn_QuickGuide
                    width: 170
                    height: 150
                    radius: 20
                    color:color_navy
                    Rectangle{
                        anchors.centerIn: parent
                        width: 160
                        height: 140
                        radius: 20
                        color:"transparent"
                        border.width: 1
                        border.color: "white"
                        Column{
                            anchors.centerIn: parent
                            spacing: 15
                            Image{
                                source: "image/serving_manual_qr.png"
                                width: 90
                                height: 90
                                sourceSize.width: width
                                sourceSize.height: height
                                anchors.horizontalCenter: parent.horizontalCenter

                            }

                            Text{
                                anchors.horizontalCenter: parent.horizontalCenter
                                text: qsTr("퀵 가이드")
                                color: "white"
                                font.family: font_noto_r.name
                                font.pixelSize: 20
                            }
                        }
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked:{
                            supervisor.playSound('click', slider_volume_button.value);
                            supervisor.writelog("[USER INPUT] SETTING PAGE -> PROGRAM UPDATE");
                            popup_update.open();
                        }
                    }
                }




            }
        }
    }

    Popup{
        id: popup_manual_detail
        width: 500
        height: 600
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
            radius: 10
            clip: true
            anchors.centerIn: parent
            width: parent.width*0.99
            height: parent.height*0.99
            Rectangle{
                color: color_blue
                radius: 10
                id: rect_prd_top3
                width: parent.width
                height: 80
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                Rectangle{
                    color: color_blue
                    width: parent.width
                    height: parent.radius
                    anchors.bottom: parent.bottom
                }
                Text{
                    anchors.centerIn: parent
                    color: "white"
                    font.family: font_noto_b.name
                    font.pixelSize: 40
                    text: qsTr("서빙로봇 매뉴얼")
                }
            }
            Grid{
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                anchors.verticalCenterOffset: 40
                rows: 2
                columns: 2
                spacing: 30

                Rectangle{
                    id: btn_QuickGuide2
                    width: 170
                    height: 150
                    radius: 20
                    color:color_navy
                    Rectangle{
                        anchors.centerIn: parent
                        width: 160
                        height: 140
                        radius: 20
                        color:"transparent"
                        border.width: 1
                        border.color: "white"
                        Column{
                            anchors.centerIn: parent
                            spacing: 15
                            Image{
                                source: "image/serving_manual_qr.png"
                                width: 90
                                height: 90
                                sourceSize.width: width
                                sourceSize.height: height
                                anchors.horizontalCenter: parent.horizontalCenter

                            }

                            Text{
                                anchors.horizontalCenter: parent.horizontalCenter
                                text: qsTr("퀵 가이드")
                                color: "white"
                                font.family: font_noto_r.name
                                font.pixelSize: 20
                            }
                        }
                    }
                    //MouseArea{
                    //    anchors.fill: parent
                    //    onClicked:{
                    //        supervisor.playSound('click', slider_volume_button.value);
                    //        supervisor.writelog("[USER INPUT] SETTING PAGE -> PROGRAM UPDATE");
                    //        popup_update.open();
                    //    }
                    //}
                }

                Rectangle{
                    id: btn_Guide
                    width: 170
                    height: 150
                    radius: 20
                    color:color_navy
                    Rectangle{
                        anchors.centerIn: parent
                        width: 160
                        height: 140
                        radius: 20
                        color:"transparent"
                        border.width: 1
                        border.color: "white"
                        Column{
                            anchors.centerIn: parent
                            spacing: 15
                            Image{
                                //source: "icon/icon_bookmark.png"
                                source: "image/serving_manual_qr.png"
                                width: 90
                                height: 90
                                sourceSize.width: width
                                sourceSize.height: height
                                anchors.horizontalCenter: parent.horizontalCenter
                                //ColorOverlay{
                                //    anchors.fill: parent
                                //    source: parent
                                //    color: "white"
                                //}
                            }

                            Text{
                                anchors.horizontalCenter: parent.horizontalCenter
                                text:qsTr("풀 가이드")
                                color: "white"
                                font.family: font_noto_r.name
                                font.pixelSize: 20
                            }
                        }

                    }
                    //MouseArea{
                    //    anchors.fill: parent
                    //    onClicked:{
                    //        supervisor.playSound('click', slider_volume_button.value);
                    //        supervisor.writelog("[USER INPUT] SETTING PAGE -> LOG");
                    //        loader_page.source = plog;
                    //    }
                    //}
                }

                Rectangle{
                    id: btn_maint
                    width: 170
                    height: 150
                    radius: 20
                    color: color_navy
                    Rectangle{
                        anchors.centerIn: parent
                        width: 160
                        height: 140
                        radius: 20
                        color:"transparent"
                        border.width: 1
                        border.color: "white"
                        Column{
                            anchors.centerIn: parent
                            spacing: 15
                            Image{
                                source: "image/serving_manual_qr.png"
                                width: 90
                                height: 90
                                sourceSize.width: width
                                sourceSize.height: height
                                anchors.horizontalCenter: parent.horizontalCenter

                            }

                            Text{
                                anchors.horizontalCenter: parent.horizontalCenter
                                text: qsTr("유지보수 매뉴얼") //
                                color: "white"
                                font.family: font_noto_r.name
                                font.pixelSize: 20
                            }
                        }

                    }
                    //MouseArea{
                    //    anchors.fill: parent
                    //    onClicked:{
                    //        supervisor.playSound('click', slider_volume_button.value);
                    //        supervisor.writelog("[UI] SETTING PAGE -> maint manual kill");
                    //        supervisor.restartSLAM();
                    //    }
                    //}
                }

                Rectangle{
                    id: btn_multi
                    width: 170
                    height: 150
                    radius: 20
                    color: color_navy
                    Rectangle{
                        anchors.centerIn: parent
                        width: 160
                        height: 140
                        radius: 20
                        color:"transparent"
                        border.width: 1
                        border.color: "white"
                        Column{
                            anchors.centerIn: parent
                            spacing: 15
                            Image{
                                source: "image/serving_manual_qr.png"
                                width: 90
                                height: 90
                                sourceSize.width: width
                                sourceSize.height: height
                                anchors.horizontalCenter: parent.horizontalCenter

                            }

                            Text{
                                anchors.horizontalCenter: parent.horizontalCenter
                                text: qsTr("멀티환경 구축")
                                color: "white"
                                font.family: font_noto_r.name
                                font.pixelSize: 20
                            }
                        }

                    }
                    //MouseArea{
                    //    anchors.fill: parent
                    //    onClicked:{
                    //        supervisor.playSound('click', slider_volume_button.value);
                    //        supervisor.writelog("[USER INPUT] SETTING PAGE -> Multi Setting");
                    //        popup_password.open();
                    //        popup_password.is_editmode = true;
                    //    }
                    //}
                }

            }
        }
    }

    //add manual
    Popup{
        id: popup_clear
        anchors.centerIn: parent
        width: 1280
        height: 400
        leftPadding: 0
        topPadding: 0
        bottomPadding: 0
        rightPadding: 0
        background: Rectangle{
            anchors.fill: parent
            color : "transparent"
        }
        property var statenum: 0
        onOpened:{
            statenum = 0;
            model_clear.clear();
        }

        function addClearState(name, prev_state){
            var tt = name.split(" ");
            if(model_clear.count > 0){
                listview_clear.model.set(model_clear.count-1,{"done":prev_state});
            }
            if(tt[tt.length-1] === "done"){
                listview_clear.model.append({"name":name,"done":2});
                btn_clear_done.enabled = true;
            }else{
                listview_clear.model.append({"name":name,"done":1});
            }
            listview_clear.currentIndex = model_clear.count - 1;

        }

        Rectangle{
            id: rect_clear_notice
            visible: popup_clear.statenum === 0
            width: parent.width
            height: parent.height
            color: color_dark_navy
            Column{
                anchors.centerIn: parent
                spacing: 40
                Text{
                    text:qsTr("정말로 공장초기화를 하시겠습니까?")
                    font.family: font_noto_r.name
                    font.pixelSize: 70
                    color: color_blue
                }
                Text{
                    anchors.horizontalCenter: parent.horizontalCenter
                    text:qsTr("저장된 모든 맵, 로그파일이 지워지며 설정이 기본세팅으로 변경됩니다.")
                    font.family: font_noto_r.name
                    font.pixelSize: 30
                    color: "white"
                }
                Row{
                    anchors.horizontalCenter: parent.horizontalCenter
                    spacing: 60
                    Item_buttons{
                        type: "round_text"
                        width: 180
                        height: 80
                        text: qsTr("초기화 시작")
                        fontsize: 30
                        onClicked: {
                            popup_clear.statenum = 1;
                            supervisor.factoryInit();
                        }
                    }
                    Item_buttons{
                        type: "round_text"
                        width: 180
                        height: 80
                        text: qsTr("취소")
                        fontsize: 30
                        onClicked: {
                            popup_clear.close();
                        }
                    }
                }
            }

        }
        Rectangle{
            id: rect_clear_ing
            visible: popup_clear.statenum === 1
            width: parent.width
            height: parent.height
            color: color_dark_navy
            Component{
                id: contactDel
                Item{
                    width: 500
                    height: 40
                    Rectangle{
                        width: 500
                        height: 40
                        color: "transparent"
                        Row{
                            spacing: 20
                            Rectangle{
                                width: 40
                                height: 40
                                color: "transparent"
                                Image{
                                    anchors.fill: parent
                                    sourceSize.width: width
                                    sourceSize.height: height
                                    source: done===2?"icon/icon_yes.png":done===1?"icon/icon_run.png":"icon/icon_error.png"
                                }
                            }
                            Rectangle{
                                width: 500 - 40
                                height: 40
                                color: "transparent"
                                Text{
                                    color: "white"
                                    anchors.verticalCenter: parent.verticalCenter
                                    text: name
                                    font.family: font_noto_r.name
                                    font.pixelSize: 20
                                }
                            }
                        }
                    }
                }
            }

            Column{
                anchors.centerIn: parent
                spacing: 40
                ListView{
                    id: listview_clear
                    width: 500
                    height: 200
                    clip: true
                    spacing: 10
                    model:ListModel{
                        id:model_clear
                        onCountChanged: {
                            print(count);
                        }
                    }
                    delegate: contactDel
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                Row{
                    anchors.horizontalCenter: parent.horizontalCenter
                    spacing: 60
                    Item_buttons{
                        id: btn_clear_done
                        type: "round_text"
                        width: 180
                        enabled: false
                        height: 80
                        text: qsTr("종 료")
                        fontsize: 30
                        onClicked: {
                            supervisor.programRestart();
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
                id: timer_close_popup
                interval: 1500 // 1.5초
                running: false
                repeat: false
                onTriggered: {
                    popup_usb_notice.close();
                }
            }

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
                        text_usb_state.text = qsTr("파일을 압축하여 저장 중..");
                    }else{
                        text_usb_state.text = qsTr("파일을 가져오는 중..");
                    }
                }else if(supervisor.getzipstate() === 2){
                    if(popup_usb_notice.mode== "compress"){
                        text_usb_state.text = qsTr("저장에 성공하였습니다");
                        //popup_usb_notice.close()
                        timer_close_popup.start(); // 1.5초 후에 창 닫기 타이머 시작

                    }else{
                        btn_usb_confirm.visible = true;
                        //text_usb_state.text = qsTr("파일을 성공적으로 가져왔습니다\n확인을 누르시면 업데이트를 진행합니다");
                        text_usb_state.text = qsTr("파일을 성공적으로 가져왔습니다\n확인을 눌러주세요");
                        //btn_usb_confirm.close()

                    }

                }else if(supervisor.getzipstate() === 3){
                    if(popup_usb_notice.mode== "compress"){
                        text_usb_state.text = qsTr("저장에 성공하였지만 일부 과정에서 에러가 발생했습니다");
                        //btn_usb_confirm.close()
                    }else{
                        text_usb_state.text = qsTr("파일을 성공적으로 가져왔습니다만 일부 과정에서 에러가 발생했습니다\n확인을 누르시면 업데이트를 진행합니다");
                        //btn_usb_confirm.close()
                    }
                    model_usb_error.clear();
                    for(var i=0; i<supervisor.getusberrorsize(); i++){
                        model_usb_error.append({"error":supervisor.getusberror(i)});
                    }
                }else if(supervisor.getzipstate() === 4){
                    text_usb_state.color = color_red;
                    if(popup_usb_notice.mode== "compress"){
                        text_usb_state.text = qsTr("저장에 실패했습니다");
                        //btn_usb_confirm.close()
                    }else{
                        text_usb_state.text = qsTr("파일을 가져오지 못했습니다");
                        //btn_usb_confirm.visible = true; // "확 인" 버튼 보이게 하기
                        //btn_usb_confirm.close()
                    }
                    model_usb_error.clear();
                    for(var i=0; i<supervisor.getusberrorsize(); i++){
                        model_usb_error.append({"error":supervisor.getusberror(i)});
                    }
                }else{
                    print(supervisor.getzipstate());
                    text_usb_state.text = qsTr("잠시만 기다려주세요");
                }
            }
        }


        onOpened:{
            timer_usb_check.start();
            model_usb_error.clear();
            btn_usb_confirm.visible = false;
            text_usb_state.text = qsTr("잠시만 기다려주세요");
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
                    text:qsTr("잠시만 기다려주세요")
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
                    //visible: false
                    visible: true
                    anchors.horizontalCenter: parent.horizontalCenter
                    width: 100
                    height: 50
                    radius: 5
                    border.width: 1
                    Text{
                        anchors.centerIn: parent
                        font.family:font_noto_r.name
                        color: color_dark_navy
                        font.pixelSize: 15
                        horizontalAlignment: Text.AlignHCenter
                        text:qsTr("확 인")
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked:{
                            supervisor.playSound('click', slider_volume_button.value);
                            if(popup_usb_notice.mode== "compress"){
                                //창 닫기
                                //popup_usb_notice.visible = false;
                                //popup_usb_download.visible = false;
                                popup_usb_notice.close();
                                popup_usb_download.close();
                            }else{
                                //supervisor.updateUSB();
                                //창 닫기
                                //popup_usb_notice.visible = false;
                                //popup_usb_download.visible = false;
                                popup_usb_notice.close();
                                popup_usb_download.close();
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
            //text_recent_file.text = supervisor.readusbrecentfile();
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
                  id: rect_1
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
                            qsTr("가져오실 파일 목록을 선택해주세요")
                        else if(popup_usb_download.index === 1)
                            qsTr("가져오실 목록을 선택해주세요")
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
                        text:qsTr("가장 최신 파일")
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
                        text:""
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
                        text:qsTr("확인")
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked:{
                            supervisor.playSound('click', slider_volume_button.value);
                            supervisor.writelog("[USER INPUT] GET RECENT USB FILE : "+supervisor.getusbrecentfile());
                            popup_usb_notice.mode = "extract_recent";
                            popup_usb_notice.open();
                              supervisor.readusbrecentfile();
                        }
                    }
                }


                Rectangle{
                    width: 200
                    height: 50
                    color: color_navy
                    anchors.horizontalCenter: parent.horizontalCenter
                    Text{
                        text:qsTr("그 외 발견한 파일 목록")
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
                                supervisor.playSound('click', slider_volume_button.value);
                                  popup_usb_download.index = 1;
                                  popup_usb_download.set_name = name;
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
                    visible: false
                    color: popup_usb_download.is_ui?color_green:color_light_gray
                    Text{
                        anchors.centerIn: parent
                        font.family: font_noto_r.name
                        font.pixelSize: 15
                        text:qsTr("UI")
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            supervisor.playSound('click', slider_volume_button.value);
                            popup_usb_download.is_ui = !popup_usb_download.is_ui;
                        }
                    }
                }
                Rectangle{
                    width: 280
                    radius: 10
                    height: 50
                    visible: false
                    color: popup_usb_download.is_slam?color_green:color_light_gray
                    Text{
                        anchors.centerIn: parent
                        font.family: font_noto_r.name
                        font.pixelSize: 15
                        text:qsTr("SLAMNAV")
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            supervisor.playSound('click', slider_volume_button.value);
                            popup_usb_download.is_slam = !popup_usb_download.is_slam;
                        }
                    }
                }
                Rectangle{
                    width: 280
                    radius: 10
                    height: 50
                    visible: is_rainbow
                    color: popup_usb_download.is_config?color_green:color_light_gray
                    Text{
                        anchors.centerIn: parent
                        font.family: font_noto_r.name
                        font.pixelSize: 15
                        text:qsTr("로봇 설정값")
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            supervisor.playSound('click', slider_volume_button.value);
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
                        text:qsTr("맵")
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            supervisor.playSound('click', slider_volume_button.value);
                            popup_usb_download.is_map = !popup_usb_download.is_map;
                        }
                    }
                }
                Rectangle{
                    width: 280
                    radius: 10
                    height: 50
                    visible: is_rainbow
                    color: popup_usb_download.is_log?color_green:color_light_gray
                    Text{
                        anchors.centerIn: parent
                        font.family: font_noto_r.name
                        font.pixelSize: 15
                        text:qsTr("로그")
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            supervisor.playSound('click', slider_volume_button.value);
                            popup_usb_download.is_log = !popup_usb_download.is_log;
                        }
                    }
                }
            }

            Column{
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: parent.bottom
                spacing: 10
                anchors.bottomMargin: 30
                //bottomMargin: 30
                visible: popup_usb_download.index === 1

                Rectangle{
                    width: 250
                    radius: 10
                    height: 50
                    color: "black"
                    Text{
                        anchors.centerIn: parent
                        font.family: font_noto_r.name
                        font.pixelSize: 15
                        color:"white"
                        text: qsTr("확인")
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            supervisor.playSound('click', slider_volume_button.value);
                            popup_usb_notice.setProperty("compress",popup_usb_download.set_name,popup_usb_download.is_ui,popup_usb_download.is_slam,popup_usb_download.is_config,popup_usb_download.is_map,popup_usb_download.is_log);
                            popup_usb_download.close();
                            popup_usb_notice.open();
                        }
                    }
                }

                Rectangle{
                    width: 250
                    radius: 10
                    height: 50
                    color: "black"
                    Text{
                        anchors.centerIn: parent
                        font.family: font_noto_r.name
                        font.pixelSize: 15
                        color:"white"
                        text: qsTr("취소")
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            supervisor.playSound('click', slider_volume_button.value);
                            popup_usb_download.close();
                        }
                    }
                }
            }
            //Rectangle{
            //    width: 250
            //    radius: 10
            //    height: 50
            //    color: "black"
            //    anchors.bottom: parent.bottom
            //    anchors.horizontalCenter: parent.horizontalCenter
            //    anchors.bottomMargin: 30
            //    visible: popup_usb_download.index === 1
            //    Text{
            //        anchors.centerIn: parent
            //        font.family: font_noto_r.name
            //        font.pixelSize: 15
            //        color:"white"
            //        text:qsTr("확인")
            //    }
            //    MouseArea{
            //        anchors.fill: parent
            //        onClicked: {
            //            supervisor.playSound('click', slider_volume_button.value);
            //            popup_usb_notice.setProperty("compress",popup_usb_download.set_name,popup_usb_download.is_ui,popup_usb_download.is_slam,popup_usb_download.is_config,popup_usb_download.is_map,popup_usb_download.is_log);
            //            popup_usb_download.close();
            //            popup_usb_notice.open();
            //        }
            //    }
            //}

            //Rectangle{
            //    width: 250
            //    radius: 10
            //    height: 50
            //    color: "black"
            //    anchors.bottom: parent.bottom
            //    anchors.horizontalCenter: parent.horizontalCenter
            //    anchors.bottomMargin: 30
            //    visible: popup_usb_download.index === 1
            //    Text{
            //        anchors.centerIn: parent
            //        font.family: font_noto_r.name
            //        font.pixelSize: 15
            //        color:"white"
            //        text:qsTr("취소")
            //    }
            //    MouseArea{
            //        anchors.fill: parent
            //        onClicked: {
            //            supervisor.playSound('click', slider_volume_button.value);
            //            popup_usb_download.close();
            //        }
            //    }
            //}


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
        width: 700
        height: 600
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
            //is_ui = true;
            //is_slam = true;
            is_map = true;
            is_log = false;
            is_config = false;
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
                            qsTr("저장소를 선택해주세요")
                        else if(popup_usb_select.index === 1)
                            qsTr("저장할 목록을 선택해주세요")
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
                    font.pixelSize: 20
                    horizontalAlignment: Text.AlignHCenter
                    color: color_red
                    text:qsTr("** USB를 인식할 수 없습니다 **\nUSB를 뺏다 꼽아주시면 인식될 수 있습니다")
                }
                Column{
                    anchors.centerIn: parent
                    spacing: 10
                    anchors.bottomMargin: 30
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
                                text:qsTr("저장소 목록")
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
                                        supervisor.playSound('click', slider_volume_button.value);
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
                        //anchors.centerIn: parent.anchors
                        spacing: 10
                        visible: popup_usb_select.index === 1
                        Rectangle{
                            width: 280
                            radius: 10
                            height: 50
                            visible: false
                            color: popup_usb_select.is_ui?color_green:color_light_gray
                            Text{
                                anchors.centerIn: parent
                                font.family: font_noto_r.name
                                font.pixelSize: 15
                                text:qsTr("UI 실행파일")
                            }
                            MouseArea{
                                anchors.fill: parent
                                onClicked: {
                                    supervisor.playSound('click', slider_volume_button.value);
                                    popup_usb_select.is_ui = !popup_usb_select.is_ui;
                                }
                            }
                        }
                        Rectangle{
                            width: 280
                            radius: 10
                            height: 50
                            visible: false
                            color: popup_usb_select.is_slam?color_green:color_light_gray
                            Text{
                                anchors.centerIn: parent
                                font.family: font_noto_r.name
                                font.pixelSize: 15
                                text:qsTr("슬램 네비게이션 실행파일")
                            }
                            MouseArea{
                                anchors.fill: parent
                                onClicked: {
                                    supervisor.playSound('click', slider_volume_button.value);
                                    popup_usb_select.is_slam = !popup_usb_select.is_slam;
                                }
                            }
                        }
                        Rectangle{
                            width: 280
                            radius: 10
                            height: 50
                            visible:is_rainbow
                            color: popup_usb_select.is_config?color_green:color_light_gray
                            Text{
                                anchors.centerIn: parent
                                font.family: font_noto_r.name
                                font.pixelSize: 15
                                text:qsTr("로봇 설정값") //설정파일
                            }
                            MouseArea{
                                anchors.fill: parent
                                onClicked: {
                                    supervisor.playSound('click', slider_volume_button.value);
                                    popup_usb_select.is_config = !popup_usb_select.is_config;
                                }
                            }
                        }
                        Rectangle{
                            width: 280
                            radius: 10
                            height: 50
                            visible:true
                            color: popup_usb_select.is_map?color_green:color_light_gray
                            Text{
                                anchors.centerIn: parent
                                font.family: font_noto_r.name
                                font.pixelSize: 15
                                text:qsTr("맵")
                            }
                            MouseArea{
                                anchors.fill: parent
                                onClicked: {
                                    supervisor.playSound('click', slider_volume_button.value);
                                    popup_usb_select.is_map = !popup_usb_select.is_map;
                                }
                            }
                        }
                        Rectangle{
                            width: 280
                            radius: 10
                            height: 50
                            visible:is_rainbow
                            color: popup_usb_select.is_log?color_green:color_light_gray
                            Text{
                                anchors.centerIn: parent
                                font.family: font_noto_r.name
                                font.pixelSize: 15
                                text:qsTr("로그")
                            }
                            MouseArea{
                                anchors.fill: parent
                                onClicked: {
                                    supervisor.playSound('click', slider_volume_button.value);
                                    popup_usb_select.is_log = !popup_usb_select.is_log;
                                }
                            }
                        }
                    }

                    //Column{
                    //    anchors.horizontalCenter: parent.horizontalCenter
                    //    anchors.bottom: parent.bottom
                    //    spacing: 10
                    //    anchors.bottomMargin: 30
                    //    //bottomMargin: 30
                    //    visible: popup_usb_download.index === 1

                    //    Rectangle{
                    //        width: 250
                    //        radius: 10
                    //        height: 50
                    //        color: "black"
                    //        Text{
                    //            anchors.centerIn: parent
                    //            font.family: font_noto_r.name
                    //            font.pixelSize: 15
                    //            color:"white"
                    //            text: qsTr("확인")
                    //        }
                    //        MouseArea{
                    //            anchors.fill: parent
                    //            onClicked: {
                    //                supervisor.playSound('click', slider_volume_button.value);
                    //                popup_usb_notice.setProperty("compress",popup_usb_download.set_name,popup_usb_download.is_ui,popup_usb_download.is_slam,popup_usb_download.is_config,popup_usb_download.is_map,popup_usb_download.is_log);
                    //                popup_usb_download.close();
                    //                popup_usb_notice.open();
                    //            }
                    //        }
                    //    }

                    //    Rectangle{
                    //        width: 250
                    //        radius: 10
                    //        height: 50
                    //        color: "black"
                    //        Text{
                    //            anchors.centerIn: parent
                    //            font.family: font_noto_r.name
                    //            font.pixelSize: 15
                    //            color:"white"
                    //            text: qsTr("취소0")
                    //        }
                    //        MouseArea{
                    //            anchors.fill: parent
                    //            onClicked: {
                    //                supervisor.playSound('click', slider_volume_button.value);
                    //                popup_usb_download.close();
                    //            }
                    //        }
                    //    }
                    //}
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
                            text:qsTr("확인")
                        }
                        MouseArea{
                            anchors.fill: parent
                            onClicked: {
                                supervisor.playSound('click', slider_volume_button.value);
                                popup_usb_notice.setProperty("compress",popup_usb_select.set_name,popup_usb_select.is_ui,popup_usb_select.is_slam,popup_usb_select.is_config,popup_usb_select.is_map,popup_usb_select.is_log);
                                popup_usb_select.close();
                                popup_usb_notice.open();
                            }
                        }
                    }
                    //Rectangle{
                    //    width: 250
                    //    radius: 10
                    //    height: 50
                    //    color: "black"
                    //    anchors.horizontalCenter: parent.horizontalCenter
                    //    visible: popup_usb_select.index === 1
                    //    Text{
                    //        anchors.centerIn: parent
                    //        font.family: font_noto_r.name
                    //        font.pixelSize: 15
                    //        color:"white"
                    //        text:qsTr("취소")
                    //    }
                    //    MouseArea{
                    //        anchors.fill: parent
                    //        onClicked: {
                    //            supervisor.playSound('click', slider_volume_button.value);
                    //            popup_usb_select.close();
                    //        }
                    //    }
                    //}
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
                text:qsTr("변경하실 호출벨을 눌러주세요")
                font.family: font_noto_r.name
                font.pixelSize: 25
            }
        }
    }
    // Popup{
    //     id: popup_update_new
    //     width: 1280
    //     height: 400
    //     leftPadding: 0
    //     rightPadding: 0
    //     topPadding: 0
    //     bottomPadding: 0
    //     anchors.centerIn: parent
    //     background: Rectangle{
    //         anchors.fill: parent
    //         color: "transparent"
    //     }

    //     function newest(){
    //         text_main_update.text = qsTr("프로그램이 이미 최신입니다");
    //         text_serv_update.text = qsTr("");
    //     }

    //     function failed(){
    //         text_main_update.text = qsTr("업데이트에 실패했습니다");
    //         text_serv_update.text = qsTr("");
    //     }

    //     onOpened: {
    //         supervisor.refreshVersion();
    //         timer_update_popup.start();
    //     }
    //     onClosed:{
    //         timer_update_popup.stop();
    //     }

    //     Timer{
    //         id: timer_update_popup
    //         running: false
    //         repeat: true
    //         interval: 1000
    //         onTriggered:{
    //             current_version.text = supervisor.getCurVersion();
    //             new_version.text = supervisor.getNewVersion();
    //             last_date.text = supervisor.getCurVersionDate();
    //         }
    //     }

    //     Rectangle{
    //         width: parent.width
    //         height: parent.height
    //         color: color_navy
    //         Column{
    //             anchors.centerIn: parent
    //             spacing: 40
    //             Column{
    //                 spacing: 10
    //                 anchors.horizontalCenter: parent.horizontalCenter
    //                 Row{
    //                     anchors.horizontalCenter: parent.horizontalCenter
    //                     Text{
    //                         width: 200
    //                         horizontalAlignment: Text.AlignHCenter
    //                         font.family: font_noto_r.name
    //                         font.pixelSize: 25
    //                         color: "white"
    //                         text:qsTr("현재 버전 : ")
    //                     }
    //                     Text{
    //                         id: current_version
    //                         width: 500
    //                         font.family: font_noto_r.name
    //                         font.pixelSize: 25
    //                         color: "white"
    //                         horizontalAlignment: Text.AlignHCenter
    //                         text: supervisor.getCurVersion()
    //                     }
    //                 }
    //                 Row{
    //                     anchors.horizontalCenter: parent.horizontalCenter
    //                     Text{
    //                         width: 200
    //                         horizontalAlignment: Text.AlignHCenter
    //                         font.family: font_noto_r.name
    //                         font.pixelSize: 25
    //                         color: "white"
    //                         text:qsTr("최신 버전 : ")
    //                     }
    //                     Text{
    //                         id: new_version
    //                         width: 500
    //                         font.family: font_noto_r.name
    //                         font.pixelSize: 25
    //                         color: "white"
    //                         horizontalAlignment: Text.AlignHCenter
    //                         text: supervisor.getNewVersion()
    //                     }
    //                 }
    //                 Row{
    //                     anchors.horizontalCenter: parent.horizontalCenter
    //                     Text{
    //                         width: 200
    //                         horizontalAlignment: Text.AlignHCenter
    //                         font.family: font_noto_r.name
    //                         font.pixelSize: 25
    //                         color: "white"
    //                         text:qsTr("마지막 업데이트 날짜 : ")
    //                     }
    //                     Text{
    //                         id: last_date
    //                         width: 500
    //                         font.family: font_noto_r.name
    //                         font.pixelSize: 25
    //                         color: "white"
    //                         horizontalAlignment: Text.AlignHCenter
    //                         text: supervisor.getCurVersionDate()
    //                     }
    //                 }
    //             }
    //             Row{
    //                 anchors.horizontalCenter: parent.horizontalCenter
    //                 spacing: 20
    //                 Buttons{
    //                     id: btn_update_new
    //                     text:qsTr("업데이트")
    //                     style: "green"
    //                     onClicked: {
    //                         supervisor.playSound('click', slider_volume_button.value);
    //                         supervisor.writelog("[USER INPUT] SETTING : Program Update Start");
    //                         supervisor.updateProgram(supervisor.getNewVersion());
    //                         // popup_update_new.close();
    //                     }
    //                 }
    //                 Buttons{
    //                     id: btn_rollback_new
    //                     text:qsTr("롤백")
    //                     style: "green"
    //                     onClicked: {
    //                         supervisor.playSound('click', slider_volume_button.value);
    //                         popup_rollback.open();
    //                         // popup_update_new.close();
    //                     }
    //                 }
    //                 Buttons{
    //                     id: btn_cancel_new
    //                     text:qsTr("닫기")
    //                     style: "normal"
    //                     onClicked: {
    //                         supervisor.playSound('click', slider_volume_button.value);
    //                         popup_update_new.close();
    //                     }
    //                 }
    //             }
    //         }
    //     }
    // }

    Popup{
        id: popup_rollback
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

        onOpened:{
            model_versions.clear();
            for(var i=0; i<supervisor.getNewVersionsSize(); i++){
                model_versions.append({version:supervisor.getNewVersion(i),
                                      date:supervisor.getNewVersionDate(i),
                                      message:supervisor.getNewVersionMessage(i)});
            }
        }

        Rectangle{
            width: parent.width
            height: parent.height
            color: color_navy
            Column{
                anchors.centerIn: parent
                spacing: 40
                Flickable{
                    width: popup_rollback.width
                    height: 200
                    contentHeight: cols_version.height
                    clip: true
                    Column{
                        id: cols_version
                        anchors.centerIn: parent
                        spacing: 10
                        Repeater{
                            model: ListModel{id: model_versions}
                            Rectangle{
                                width: 800
                                height: 80
                                color: select_version===index?color_green:color_light_gray
                                Rectangle{
                                    width: 120
                                    height: 50
                                    radius: 30
                                    color: color_light_gray
                                    anchors.verticalCenter: parent.verticalCenter
                                    anchors.left: parent.left
                                    anchors.leftMargin: 100
                                    Text{
                                        anchors.centerIn: parent
                                        text: version
                                        font.bold: true
                                        font.pixelSize: 20
                                    }
                                }
                                Column{
                                    anchors.verticalCenter: parent.verticalCenter
                                    anchors.left: parent.left
                                    anchors.leftMargin: 400
                                    spacing: 10
                                    Row{
                                        Text{
                                            horizontalAlignment: Text.AlignHCenter
                                            text: qsTr("message : ")
                                            width: 150
                                        }
                                        Text{
                                            text: message
                                        }
                                    }
                                    Row{
                                        Text{
                                            horizontalAlignment: Text.AlignHCenter
                                            text: qsTr("date : ")
                                            width: 150
                                        }
                                        Text{
                                            text: date
                                        }
                                    }
                                }
                                MouseArea{
                                    anchors.fill: parent
                                    onClicked:{
                                        select_version = index;
                                    }
                                }
                            }
                        }
                    }
                }
                Row{
                    anchors.horizontalCenter: parent.horizontalCenter
                    spacing: 20
                    Buttons{
                        text:qsTr("롤백")
                        style: "green"
                        onClicked: {
                            if(select_version > -1 && select_version < model_versions.count){
                                supervisor.playSound('click', slider_volume_button.value);
                                supervisor.writelog("[USER INPUT] SETTING : Program Update Start");
                                supervisor.updateProgram(model_versions.get(select_version).version);
                                popup_rollback.close();
                            }else{
                                supervisor.playSound('no', slider_volume_button.value);
                            }

                        }
                    }
                    Buttons{
                        text:qsTr("닫기")
                        style: "normal"
                        onClicked: {
                            supervisor.playSound('click', slider_volume_button.value);
                            popup_rollback.close();
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
                    btn_gitreset.visible = false;
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
                    btn_gitreset.visible = false;
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
                btn_gitreset.visible = false;
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
                            text:qsTr("현재 버전 : ")
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
                            text:qsTr("최신 버전 : ")
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
                                supervisor.playSound('click', slider_volume_button.value);
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
                                supervisor.playSound('click', slider_volume_button.value);
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
                                supervisor.playSound('click', slider_volume_button.value);
                                popup_loading.open();
                                supervisor.writelog("[USER INPUT] SETTING : Program Update(Git Pull) Start");
                                supervisor.updateProgramGitPull();
//                                popup_update.close();
                            }
                        }
                    }
                    Rectangle{
                        id: btn_gitreset
                        width: 180
                        height: 60
                        radius: 10
                        color: "#12d27c"
                        border.width: 1
                        visible: false
                        border.color: "#12d27c"
                        Text{
                            anchors.centerIn: parent
                            text: qsTr("RESET")
                            font.family: font_noto_r.name
                            font.pixelSize: 25
                            color: "white"
                        }
                        MouseArea{
                            anchors.fill: parent
                            onClicked: {
                                supervisor.playSound('click', slider_volume_button.value);
                                popup_loading.open();
                                supervisor.writelog("[USER INPUT] SETTING : Program Update(Git Reset) Start");
                                supervisor.gitReset();
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
                    supervisor.playSound('click', slider_volume_button.value);
                    if(++count > 4){
                        count = 0;
                        supervisor.writelog("[USER INPUT] SETTING : Show Git Pull Button");
                        btn_gitpull.visible = true;
                        btn_gitreset.visible = false;
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
                    text:qsTr("카메라 정보를 확인한 후, 위치를 지정하여주세요")
                }
                Row{
                    anchors.horizontalCenter: parent.horizontalCenter
                    spacing: 50
                    Column{
                        spacing: 10
                        Text{
                            id: text_left
                            text:qsTr("왼쪽")
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
                            text:qsTr("오른쪽")
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
                            text:qsTr("확인")
                            font.family: font_noto_r.name
                            font.pixelSize: 25
                            color: "white"
                        }
                        MouseArea{
                            anchors.fill: parent
                            onClicked: {
                                supervisor.playSound('click', slider_volume_button.value);
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
                            text:qsTr("위치 바꾸기")
                            color: "white"
                            font.family: font_noto_r.name
                            font.pixelSize: 25
                        }
                        MouseArea{
                            anchors.fill: parent
                            onClicked: {
                                supervisor.playSound('click', slider_volume_button.value);
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
                            text:qsTr("취소")
                            font.family: font_noto_r.name
                            font.pixelSize: 25
                        }
                        MouseArea{
                            anchors.fill: parent
                            onClicked: {
                                supervisor.playSound('click', slider_volume_button.value);
                                popup_camera.close();
                            }
                        }
                    }
                }
            }
        }
    }
    Popup{
        id: popup_change_voice_language
        width: 1280
        height: 800
        background: Rectangle{
            anchors.fill: parent
            color: color_dark_black
            opacity: 0.7
        }
        property bool show_emotion: false
        Rectangle{
            anchors.centerIn: parent
            width: 1280
            height: 350
            Column{
                anchors.centerIn: parent
                spacing: 50
                Text{
                    text: qsTr("음성 언어를 변경하시겠습니까?\n기존에 설정했던 음성이 변경되며 멘트가 기본멘트로 변경됩니다")
                    horizontalAlignment: Text.AlignHCenter
                    font.family: font_noto_r.name
                    font.pixelSize: 40

                }
                Row{
                    anchors.horizontalCenter: parent.horizontalCenter
                    spacing: 50
                    Item_buttons{
                        type: "white_btn"
                        text: qsTr("취소")
                        width: 160
                        height: 60
                        onClicked:{
                            combo_voice_lan_2.currentIndex = combo_voice_language.currentIndex
                            popup_change_voice_language.close();
                        }
                    }
                    Item_buttons{
                        type: "white_btn"
                        text: qsTr("확인")
                        width: 160
                        height: 60
                        onClicked:{
                            combo_voice_language.currentIndex = combo_voice_lan_2.currentIndex
                            supervisor.setTTSVoice(combo_voice_language.currentIndex,0);
                            supervisor.setTTSMentionBasic();
                            popup_mention.update();
                            popup_change_voice_language.close();
                        }
                    }
                }
            }

        }
    }

    Popup{
        id: popup_voice
        width: 1280
        height: 800
        background: Rectangle{
            anchors.fill: parent
            color: color_dark_black
            opacity: 0.7
        }
        onOpened:{
            combo_voice_name_2.currentIndex = combo_voice_name.currentIndex
            slider_speed.value = supervisor.getTTSSpeed();
            slider_pitch.value = supervisor.getTTSPitch();
            slider_alpha.value = supervisor.getTTSAlpha();
            slider_emotion.value = supervisor.getTTSEmotion();
            slider_emotion_strength.value = supervisor.getTTSEmotionStrength();
        }

        property bool show_emotion: false
        Rectangle{
            anchors.centerIn: parent
            width: 1000
            height: 600
            radius: 20
            Row{
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.rightMargin: 50
                anchors.topMargin: 50
                spacing: 30
                Item_buttons{
                    type: "white_btn"
                    width: 150
                    height: 55
                    text: qsTr("이전음성 초기화")
                    onClicked:{
                        supervisor.playSound('click', slider_volume_button.value);
                        supervisor.clearTTSVoice(combo_voice_language.currentIndex, combo_voice_name_2.currentIndex);
                    }
                }
                Item_buttons{
                    type: "white_btn"
                    width: 150
                    height: 55
                    text: qsTr("한꺼번에 만들기")
                    onClicked:{
                        supervisor.playSound('click', slider_volume_button.value);
                        supervisor.setTTSMode("tts");
                        supervisor.setTTSVoice(combo_voice_language.currentIndex,combo_voice_name_2.currentIndex);
                        supervisor.setTTSVoiceDetail(slider_speed.value, slider_pitch.value, slider_alpha.value, slider_emotion.value, slider_emotion_strength.value);
                        supervisor.makeTTSAll();
                    }
                }
                Item_buttons{
                    type: "white_btn"
                    width: 150
                    height: 55
                    text: qsTr("취 소")
                    onClicked:{
                        supervisor.playSound('click', slider_volume_button.value);
                        popup_voice.close();
                    }
                }
                Item_buttons{
                    type: "white_btn"
                    width: 150
                    height: 55
                    text: qsTr("저 장")
                    onClicked:{
                        supervisor.playSound('click', slider_volume_button.value);
                        supervisor.setTTSMode("tts");
                        supervisor.setTTSVoice(combo_voice_language.currentIndex,combo_voice_name_2.currentIndex);
                        supervisor.setTTSVoiceDetail(slider_speed.value, slider_pitch.value, slider_alpha.value, slider_emotion.value, slider_emotion_strength.value);
                        init();
                        popup_voice.close();
                    }
                }
            }
            Column{
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                spacing: 50
                Row{
                    spacing: 50
                    anchors.horizontalCenter: parent.horizontalCenter
                    Text{
                        anchors.verticalCenter: parent.verticalCenter
                        text: qsTr("현재 선택된 음성 : ")
                        font.pixelSize: 20
                        font.family: font_noto_r.name
                    }
                    ComboBox{
                        id: combo_voice_name_2
                        width: 300
                        anchors.verticalCenter: parent.verticalCenter
                        height: 50
                        model: model_voice
                        onCurrentIndexChanged: {
                            popup_voice.show_emotion = false;
                            if(combo_voice_language.currentIndex === 0){
                                if(currentIndex === 0 || currentIndex === 1){
                                    popup_voice.show_emotion = true;
                                }
                            }
                        }
                    }
                    Image{
                        anchors.verticalCenter: parent.verticalCenter
                        source: "icon/icon_test_play.png"
                        MouseArea{
                            anchors.fill: parent
                            onClicked: {
                                supervisor.playSound('click', slider_volume_button.value);
                                supervisor.setTTSMode("tts");
                                supervisor.setTTSVoice(combo_voice_language.currentIndex,combo_voice_name_2.currentIndex);
                                supervisor.setTTSVoiceDetail(slider_speed.value, slider_pitch.value, slider_alpha.value, slider_emotion.value, slider_emotion_strength.value);
                                supervisor.playVoice("test","","","",-1);
                            }
                        }
                    }
                }
                Grid{
                    anchors.horizontalCenter: parent.horizontalCenter
                    spacing: 10
                    columns: 3
                    rows: 5
                    horizontalItemAlignment: Grid.AlignHCenter
                    verticalItemAlignment: Grid.AlignVCenter
                    Text{
                        text: qsTr("속도 : ")
                        font.pixelSize: 20
                        font.family: font_noto_r.name
                    }
                    Slider{
                        id: slider_speed
                        width: 400
                        to: 5
                        from: -5
                        stepSize: 1
                        value: 0
                    }
                    Text{
                        width: 180
                        horizontalAlignment: Text.AlignHCenter
                        text: {
                            if(slider_speed.value > 0){
                                qsTr("느린속도 (")+Number(1.0+slider_speed.value*0.2)+"배)"

                            }else if(slider_speed.value < 0){
                                qsTr("빠른속도 (")+Number(1.0+slider_speed.value*0.1)+"배)"

                            }else{
                                qsTr("기본속도")
                            }
                        }
                        font.pixelSize: 20
                        font.family: font_noto_r.name
                    }
                    Text{
                        text: qsTr("피치 : ")
                        font.pixelSize: 20
                        font.family: font_noto_r.name
                    }
                    Slider{
                        id: slider_pitch
                        width: 400
                        to: 5
                        from: -5
                        stepSize: 1
                        value: 0
                    }
                    Text{
                        text: {
                            if(slider_pitch.value > 0){
                                qsTr("낮은피치 (")+Number(slider_pitch.value)+"단계)"

                            }else if(slider_pitch.value < 0){
                                qsTr("높은피치 (")+Number(-slider_pitch.value)+"단계)"

                            }else{
                                qsTr("기본피치")
                            }
                        }
                        font.pixelSize: 20
                        font.family: font_noto_r.name
                    }
                    Text{
                        visible: popup_voice.show_emotion
                        text: qsTr("감정 : ")
                        font.pixelSize: 20
                        font.family: font_noto_r.name
                    }
                    Slider{
                        visible: popup_voice.show_emotion
                        id: slider_emotion
                        width: 400
                        to: 3
                        from: 0
                        stepSize: 1
                        value: 0
                    }
                    Text{
                        visible: popup_voice.show_emotion
                        text: {
                            if(slider_emotion.value == 0){
                                qsTr("중립")
                            }else if(slider_emotion.value == 1){
                                qsTr("슬픔")
                            }else if(slider_emotion.value == 2){
                                qsTr("기쁨")
                            }else{
                                qsTr("분노")
                            }
                        }
                        font.pixelSize: 20
                        font.family: font_noto_r.name
                    }
                    Text{
                        visible: popup_voice.show_emotion
                        text: qsTr("감정정도 : ")
                        font.pixelSize: 20
                        font.family: font_noto_r.name
                    }
                    Slider{
                        visible: popup_voice.show_emotion
                        id: slider_emotion_strength
                        width: 400
                        to: 2
                        from: 0
                        stepSize: 1
                        value: 1
                    }
                    Text{
                        visible: popup_voice.show_emotion
                        text: {
                            if(slider_emotion_strength.value == 0){
                                qsTr("약하게")
                            }else if(slider_emotion_strength.value == 1){
                                qsTr("기본")
                            }else if(slider_emotion_strength.value == 2){
                                qsTr("강하게")
                            }
                        }
                        font.pixelSize: 20
                        font.family: font_noto_r.name
                    }
                    Text{
                        text: qsTr("음색 : ")
                        font.pixelSize: 20
                        font.family: font_noto_r.name
                    }
                    Slider{
                        id: slider_alpha
                        width: 400
                        to: 5
                        from: -5
                        stepSize: 1
                        value: 0
                    }
                    Text{
                        text: {
                            if(slider_alpha.value > 0){
                                qsTr("높은음색 (")+Number(slider_alpha.value)+")"

                            }else if(slider_alpha.value < 0){
                                qsTr("낮은음색 (")+Number(slider_alpha.value)+")"

                            }else{
                                qsTr("기본음색")
                            }
                        }
                        font.pixelSize: 20
                        font.family: font_noto_r.name
                    }
                }


            }

        }
    }
    Popup{
        id: popup_mention
        width: 1280
        height: 800
        background: Rectangle{
            anchors.fill: parent
            color: color_dark_black
            opacity: 0.7
        }
        onOpened:{
            combo_voice_lan_2.currentIndex = combo_voice_language.currentIndex
            update();
        }

        function update(){
            tfield_text_1.text = supervisor.getTTSMention("move_serving");
            tfield_text_2.text = supervisor.getTTSMention("move_calling");
            tfield_text_3.text = supervisor.getTTSMention("moving");
            tfield_text_4.text = supervisor.getTTSMention("excuseme");
            tfield_text_5.text = supervisor.getTTSMention("pickup");
            tfield_text_6.text = supervisor.getTTSMention("callme");
        }

        Rectangle{
            anchors.centerIn: parent
            width: 1100
            height: 700
            radius: 20
            Row{
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.rightMargin: 50
                anchors.topMargin: 50
                spacing: 30
                Item_buttons{
                    type: "white_btn"
                    width: 150
                    height: 55
                    text: qsTr("닫 기")
                    onClicked:{
                        supervisor.playSound('click', slider_volume_button.value);
                        combo_voice_language.currentIndex = supervisor.getTTSLanguageNum();
                        popup_mention.close();
                    }
                }
                Item_buttons{
                    type: "white_btn"
                    width: 150
                    height: 55
                    text: qsTr("저 장")
                    onClicked:{
                        supervisor.playSound('click', slider_volume_button.value);
                        if(combo_voice_language.currentIndex != combo_voice_lan_2.currentIndex){
                            popup_change_voice_language.open();
                        }else{
                            //save new mention
                            supervisor.setTTSMention("move_serving"  ,tfield_text_1.text);
                            supervisor.setTTSMention("move_calling"  ,tfield_text_2.text);
                            supervisor.setTTSMention("moving"        ,tfield_text_3.text);
                            supervisor.setTTSMention("excuseme"      ,tfield_text_4.text);
                            supervisor.setTTSMention("pickup"        ,tfield_text_5.text);
                            supervisor.setTTSMention("callme"        ,tfield_text_6.text);
                            popup_mention.close();
                        }
                    }
                }
            }
            Column{
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                anchors.verticalCenterOffset: 30
                spacing: 50
                Row{
                    spacing: 50
                    anchors.horizontalCenter: parent.horizontalCenter
                    Text{
                        anchors.verticalCenter: parent.verticalCenter
                        text: qsTr("현재 선택된 음성 : ")
                        font.pixelSize: 20
                        font.family: font_noto_r.name
                    }
                    ComboBox{
                        id: combo_voice_lan_2
                        width: 300
                        anchors.verticalCenter: parent.verticalCenter
                        height: 50
                        model:[qsTr("한국어"), qsTr("영어"), qsTr("중국어"), qsTr("일본어"), qsTr("스페인어")]//, qsTr("러시아어"), qsTr("독일어")]

                    }
                    Rectangle{
                        width: 100
                        height: parent.height
                        anchors.verticalCenter: parent.verticalCenter
                        radius: 5
                        color: color_dark_navy
                        Text{
                            anchors.centerIn: parent
                            text: qsTr("설정")
                            color: "white"
                            font.family: font_noto_r.name
                            font.pixelSize: 15
                        }
                        MouseArea{
                            anchors.fill: parent
                            onClicked:{
                                supervisor.playSound('click', slider_volume_button.value);
                                popup_change_voice_language.open();
                            }
                        }
                    }
                }

                Flickable{
                    clip: true
                    anchors.horizontalCenter: parent.horizontalCenter
                    width: 1100
                    height: 400
                    contentHeight: colssss.height
                    Column{
                        id: colssss
                        anchors.horizontalCenter: parent.horizontalCenter
                        spacing: 10
                        Rectangle{
                            width: 800
                            height: 50
                            color: "black"
                            anchors.horizontalCenter: parent.horizontalCenter
                            radius: 2
                            Text{
                                anchors.centerIn: parent
                                color: "white"
                                text: qsTr("주행 시작")
                                font.pixelSize: 30
                                font.bold: true
                            }
                        }

                        Row{
                            spacing: 10
                            Text{
                                width: 300
                                horizontalAlignment: Text.AlignHCenter
                                text: qsTr("서빙을 시작할 때")
                                font.pixelSize: 20
                                anchors.verticalCenter: parent.verticalCenter
                                font.family: font_noto_r.name
                            }
                            TextField{
                                id: tfield_text_1
                                width: 550
                                height: 50
                            }
                            Rectangle{
                                width: 50
                                height: 50
                                radius:10
                                color: enabled?color_dark_navy:color_gray
                                Image{
                                    anchors.centerIn: parent
                                    width: 35
                                    height: 35
                                    sourceSize.width: width
                                    sourceSize.height: height
                                    source: "icon/icon_keyboard.png"
                                    ColorOverlay{
                                        anchors.fill: parent
                                        source: parent
                                        color: "white"
                                    }
                                }
                                MouseArea{
                                    enabled: parent.enabled
                                    anchors.fill: parent
                                    onClicked:{
                                        supervisor.playSound('click', slider_volume_button.value);
                                        keyboard.owner = tfield_text_1;
                                        tfield_text_1.selectAll();
                                        keyboard.open();
                                    }
                                }
                            }
                        }

                        Row{
                            spacing: 10
                            Text{
                                width: 300
                                horizontalAlignment: Text.AlignHCenter
                                text: qsTr("호출위치로 이동할 때")
                                font.pixelSize: 20
                                anchors.verticalCenter: parent.verticalCenter
                                font.family: font_noto_r.name
                            }
                            TextField{
                                id: tfield_text_2
                                width: 550
                                height: 50
                            }
                            Rectangle{
                                width: 50
                                height: 50
                                radius:10
                                color: enabled?color_dark_navy:color_gray
                                Image{
                                    anchors.centerIn: parent
                                    width: 35
                                    height: 35
                                    sourceSize.width: width
                                    sourceSize.height: height
                                    source: "icon/icon_keyboard.png"
                                    ColorOverlay{
                                        anchors.fill: parent
                                        source: parent
                                        color: "white"
                                    }
                                }
                                MouseArea{
                                    enabled: parent.enabled
                                    anchors.fill: parent
                                    onClicked:{
                                        supervisor.playSound('click', slider_volume_button.value);
                                        keyboard.owner = tfield_text_2;
                                        tfield_text_2.selectAll();
                                        keyboard.open();
                                    }
                                }
                            }
                        }

                        Rectangle{
                            width: 800
                            height: 50
                            color: "black"
                            anchors.horizontalCenter: parent.horizontalCenter
                            radius: 2
                            Text{
                                anchors.centerIn: parent
                                color: "white"
                                text: qsTr("이동 중")
                                font.pixelSize: 30
                                font.bold: true
                            }
                        }

                        Row{
                            spacing: 10
                            Text{
                                width: 300
                                horizontalAlignment: Text.AlignHCenter
                                text: qsTr("이동 중 사람감지")
                                font.pixelSize: 20
                                anchors.verticalCenter: parent.verticalCenter
                                font.family: font_noto_r.name
                            }
                            TextField{
                                id: tfield_text_3
                                width: 550
                                height: 50
                            }
                            Rectangle{
                                width: 50
                                height: 50
                                radius:10
                                color: enabled?color_dark_navy:color_gray
                                Image{
                                    anchors.centerIn: parent
                                    width: 35
                                    height: 35
                                    sourceSize.width: width
                                    sourceSize.height: height
                                    source: "icon/icon_keyboard.png"
                                    ColorOverlay{
                                        anchors.fill: parent
                                        source: parent
                                        color: "white"
                                    }
                                }
                                MouseArea{
                                    enabled: parent.enabled
                                    anchors.fill: parent
                                    onClicked:{
                                        supervisor.playSound('click', slider_volume_button.value);
                                        keyboard.owner = tfield_text_3;
                                        tfield_text_3.selectAll();
                                        keyboard.open();
                                    }
                                }
                            }
                        }


                        Row{
                            spacing: 10
                            Text{
                                width: 300
                                horizontalAlignment: Text.AlignHCenter
                                text: qsTr("장애물 일시정지")
                                font.pixelSize: 20
                                anchors.verticalCenter: parent.verticalCenter
                                font.family: font_noto_r.name
                            }
                            TextField{
                                id: tfield_text_4
                                width: 550
                                height: 50
                            }
                            Rectangle{
                                width: 50
                                height: 50
                                radius:10
                                color: enabled?color_dark_navy:color_gray
                                Image{
                                    anchors.centerIn: parent
                                    width: 35
                                    height: 35
                                    sourceSize.width: width
                                    sourceSize.height: height
                                    source: "icon/icon_keyboard.png"
                                    ColorOverlay{
                                        anchors.fill: parent
                                        source: parent
                                        color: "white"
                                    }
                                }
                                MouseArea{
                                    enabled: parent.enabled
                                    anchors.fill: parent
                                    onClicked:{
                                        supervisor.playSound('click', slider_volume_button.value);
                                        keyboard.owner = tfield_text_4;
                                        tfield_text_4.selectAll();
                                        keyboard.open();
                                    }
                                }
                            }
                        }


                        Rectangle{
                            width: 800
                            height: 50
                            color: "black"
                            anchors.horizontalCenter: parent.horizontalCenter
                            radius: 2
                            Text{
                                anchors.centerIn: parent
                                color: "white"
                                text: qsTr("목적지 도착")
                                font.pixelSize: 30
                                font.bold: true
                            }
                        }

                        Row{
                            spacing: 10
                            Text{
                                width: 300
                                horizontalAlignment: Text.AlignHCenter
                                text: qsTr("서빙위치 도착")
                                font.pixelSize: 20
                                anchors.verticalCenter: parent.verticalCenter
                                font.family: font_noto_r.name
                            }
                            TextField{
                                id: tfield_text_5
                                width: 550
                                height: 50
                            }
                            Rectangle{
                                width: 50
                                height: 50
                                radius:10
                                color: enabled?color_dark_navy:color_gray
                                Image{
                                    anchors.centerIn: parent
                                    width: 35
                                    height: 35
                                    sourceSize.width: width
                                    sourceSize.height: height
                                    source: "icon/icon_keyboard.png"
                                    ColorOverlay{
                                        anchors.fill: parent
                                        source: parent
                                        color: "white"
                                    }
                                }
                                MouseArea{
                                    enabled: parent.enabled
                                    anchors.fill: parent
                                    onClicked:{
                                        supervisor.playSound('click', slider_volume_button.value);
                                        keyboard.owner = tfield_text_5;
                                        tfield_text_5.selectAll();
                                        keyboard.open();
                                    }
                                }
                            }
                        }

                        Row{
                            spacing: 10
                            Text{
                                width: 300
                                horizontalAlignment: Text.AlignHCenter
                                text: qsTr("호출위치 도착")
                                font.pixelSize: 20
                                anchors.verticalCenter: parent.verticalCenter
                                font.family: font_noto_r.name
                            }
                            TextField{
                                id: tfield_text_6
                                width: 550
                                height: 50
                            }
                            Rectangle{
                                width: 50
                                height: 50
                                radius:10
                                color: enabled?color_dark_navy:color_gray
                                Image{
                                    anchors.centerIn: parent
                                    width: 35
                                    height: 35
                                    sourceSize.width: width
                                    sourceSize.height: height
                                    source: "icon/icon_keyboard.png"
                                    ColorOverlay{
                                        anchors.fill: parent
                                        source: parent
                                        color: "white"
                                    }
                                }
                                MouseArea{
                                    enabled: parent.enabled
                                    anchors.fill: parent
                                    onClicked:{
                                        supervisor.playSound('click', slider_volume_button.value);
                                        keyboard.owner = tfield_text_6;
                                        tfield_text_6.selectAll();
                                        keyboard.open();
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
                        text:qsTr("로봇 속도 설정")
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
                                        text:qsTr("초기화")
                                    }
                                    MouseArea{
                                        anchors.fill: parent
                                        onClicked:{
                                            supervisor.playSound('click', slider_volume_button.value);
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
                                        text:qsTr("이름변경")
                                    }
                                    MouseArea{
                                        anchors.fill: parent
                                        onClicked:{
                                            supervisor.playSound('click', slider_volume_button.value);
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
                                    text:qsTr("프리셋 1")
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
                                        supervisor.playSound('click', slider_volume_button.value);
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
                                    text:qsTr("프리셋 2")
                                }
                                MouseArea{
                                    anchors.fill: parent
                                    onClicked:{
                                        supervisor.playSound('click', slider_volume_button.value);
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
                                    text:qsTr("프리셋 3")
                                }
                                MouseArea{
                                    anchors.fill: parent
                                    onClicked:{
                                        supervisor.playSound('click', slider_volume_button.value);
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
                                    text:qsTr("프리셋 4")
                                }
                                MouseArea{
                                    anchors.fill: parent
                                    onClicked:{
                                        supervisor.playSound('click', slider_volume_button.value);
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
                                    text:qsTr("프리셋 5")
                                }
                                MouseArea{
                                    anchors.fill: parent
                                    onClicked:{
                                        supervisor.playSound('click', slider_volume_button.value);
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
                                    text:qsTr("나가기")
                                }
                                MouseArea{
                                    anchors.fill: parent
                                    onClicked:{
                                        supervisor.playSound('click', slider_volume_button.value);
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
                                    text:qsTr("저장")
                                }
                                MouseArea{
                                    anchors.fill: parent
                                    onClicked:{
                                        supervisor.playSound('click', slider_volume_button.value);
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
                                text:qsTr("제자리 회전 속도 [deg/s]")
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
                                        supervisor.playSound('click', slider_volume_button.value);
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
                                text:""
                            }
                            Text{
                                font.family: font_noto_r.name
                                text:qsTr("제자리 회전 가속도 [deg/s^2]")
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
                                text:""
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        supervisor.playSound('click', slider_volume_button.value);
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
                                text:qsTr("주행 속도 [m/s]")
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
                                        supervisor.playSound('click', slider_volume_button.value);
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
                                text:""
                            }
                            Text{
                                font.family: font_noto_r.name
                                text:qsTr("주행 가속도 [m/s^2]")
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
                                        supervisor.playSound('click', slider_volume_button.value);
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
                                text:""
                            }
                            Text{
                                font.family: font_noto_r.name
                                text:qsTr("주행 회전속도 [deg/s]")
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
                                        supervisor.playSound('click', slider_volume_button.value);
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
                                text:""
                            }
                            Text{
                                font.family: font_noto_r.name
                                text:qsTr("주행 회전 가속도 [deg/s^2]")
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
                                text:""
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {
                                        supervisor.playSound('click', slider_volume_button.value);
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
                        supervisor.playSound('click', slider_volume_button.value);
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
                        text:qsTr("취소")
                        font.family: font_noto_r.name
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked:{
                            supervisor.playSound('click', slider_volume_button.value);
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
                        text:qsTr("확인")
                        font.family: font_noto_r.name
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked:{
                            supervisor.playSound('click', slider_volume_button.value);
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
                    text:qsTr("선택하신 프리셋으로 세팅을 변경하시겠습니까?")
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
                            text:qsTr("취소")
                            color: "white"
                        }
                        MouseArea{
                            anchors.fill: parent
                            onClicked:{
                                supervisor.playSound('click', slider_volume_button.value);
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
                            text:qsTr("확인")
                        }
                        MouseArea{
                            anchors.fill: parent
                            onClicked:{
                                supervisor.playSound('click', slider_volume_button.value);
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

    Popup_password{
        id: popup_password
        onEdited: {
            select_category = "status";
            popup_password.close();
            popup_manager.close();
        }
        onClosed:{
            if(open_menu){
                popup_manager.open();
                open_menu = false;
            }
        }
        onLogined:{
            is_admin = true;
            is_rainbow = false;
            if(popup_update.opened){
                supervisor.writelog("[USER INPUT] Program Update : Password Correct -> pull start")
                supervisor.updateProgram();
                popup_update.close();
            }
            popup_password.close();
        }
        onLogin_rainbow: {
            is_admin = true;
            is_rainbow = true;
            if(popup_update.opened){
                supervisor.writelog("[USER INPUT] Program Update : Password Correct -> pull start")
                supervisor.updateProgram();
                popup_update.close();
            }
            popup_password.close();
        }
        onFailed:{
            is_admin = false;
            is_rainbow = false;
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
                    text:qsTr("라이다/카메라 TF 설정")
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
                        text:""
                        width: 100
                        horizontalAlignment: Text.AlignHCenter
                        color: "white"
                        font.family: font_noto_r.name
                        font.pixelSize: 18
                    }
                    Text{
                        text:"X"
                        width: 50
                        horizontalAlignment: Text.AlignHCenter
                        color: "white"
                        font.family: font_noto_r.name
                        font.pixelSize: 20
                    }
                    Text{
                        text:"Y"
                        width: 50
                        horizontalAlignment: Text.AlignHCenter
                        color: "white"
                        font.family: font_noto_r.name
                        font.pixelSize: 20
                    }
                    Text{
                        text:"Z"
                        width: 50
                        horizontalAlignment: Text.AlignHCenter
                        color: "white"
                        font.family: font_noto_r.name
                        font.pixelSize: 20
                    }
                    Text{
                        text:"RX"
                        width: 50
                        horizontalAlignment: Text.AlignHCenter
                        color: "white"
                        font.family: font_noto_r.name
                        font.pixelSize: 20
                    }
                    Text{
                        text:"RY"
                        width: 50
                        horizontalAlignment: Text.AlignHCenter
                        color: "white"
                        font.family: font_noto_r.name
                        font.pixelSize: 20
                    }
                    Text{
                        text:"RZ"
                        width: 50
                        horizontalAlignment: Text.AlignHCenter
                        color: "white"
                        font.family: font_noto_r.name
                        font.pixelSize: 20
                    }

                    Text{
                        text:qsTr("라이다")
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
                                supervisor.playSound('click', slider_volume_button.value);
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
                                supervisor.playSound('click', slider_volume_button.value);
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
                                supervisor.playSound('click', slider_volume_button.value);
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
                        enabled: false
                        font.family: font_noto_r.name
                        font.pixelSize: 15
                        horizontalAlignment: Text.AlignHCenter
                        MouseArea{
                            anchors.fill:parent
                            onClicked: {
                                supervisor.playSound('click', slider_volume_button.value);
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
                        enabled: false
                        font.family: font_noto_r.name
                        font.pixelSize: 15
                        horizontalAlignment: Text.AlignHCenter
                        MouseArea{
                            anchors.fill:parent
                            onClicked: {
                                supervisor.playSound('click', slider_volume_button.value);
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
                        enabled: false
                        font.family: font_noto_r.name
                        font.pixelSize: 15
                        horizontalAlignment: Text.AlignHCenter
                        MouseArea{
                            anchors.fill:parent
                            onClicked: {
                                supervisor.playSound('click', slider_volume_button.value);
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
                        text:qsTr("왼쪽카메라")
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
                                supervisor.playSound('click', slider_volume_button.value);
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
                                supervisor.playSound('click', slider_volume_button.value);
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
                                supervisor.playSound('click', slider_volume_button.value);
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
                                supervisor.playSound('click', slider_volume_button.value);
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
                                supervisor.playSound('click', slider_volume_button.value);
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
                                supervisor.playSound('click', slider_volume_button.value);
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
                        text:qsTr("오른쪽카메라")
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
                                supervisor.playSound('click', slider_volume_button.value);
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
                                supervisor.playSound('click', slider_volume_button.value);
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
                                supervisor.playSound('click', slider_volume_button.value);
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
                                supervisor.playSound('click', slider_volume_button.value);
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
                                supervisor.playSound('click', slider_volume_button.value);
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
                                supervisor.playSound('click', slider_volume_button.value);
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
                            text:qsTr("취소")
                        }
                        MouseArea{
                            anchors.fill: parent
                            onClicked:{
                                supervisor.playSound('click', slider_volume_button.value);
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
                            text:qsTr("확인")
                        }
                        MouseArea{
                            anchors.fill: parent
                            onClicked:{
                                supervisor.playSound('click', slider_volume_button.value);
                                supervisor.writelog("[USER INPUT] SETTING CAMERA TF CHANGED");

                                var lidar_str = tf_lidar_x.text + "," + tf_lidar_y.text + "," + tf_lidar_z.text;
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
    Popup_wifi{
        id: popup_wifi
        onDone: {
            popup_wifi.close();
        }
        onCancel: {
            popup_wifi.close();
        }
        onClosed: {
            console.log("init neeeeeeeeeeeeeeeeeeeeeeed")
            page_setting.init();
        }
    }

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
                    text:qsTr("세팅값 변경 감지")
                    color: "white"
                    font.family: font_noto_r.name
                    font.pixelSize: 30
                }

                Text{
                    anchors.horizontalCenter: parent.horizontalCenter
                    text:qsTr("변경한 값으로 저장하시려면 확인 버튼을 눌러주세요\n취소하시면 저장되지 않습니다")
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
                            text:qsTr("취소")
                            color: "white"
                        }
                        MouseArea{
                            anchors.fill: parent
                            onClicked:{
                                supervisor.playSound('click', slider_volume_button.value);
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
                            text:qsTr("확인")
                        }
                        MouseArea{
                            anchors.fill: parent
                            onClicked:{
                                supervisor.playSound('click', slider_volume_button.value);
                                save();
                                backPage();
                            }
                        }
                    }
                }
            }
        }
    }
    Popup_patrol_page{
        id: popup_set_patrolpage
        objectName: "popup_set_patrolpage"
    }

    Popup_map_list{
        id: popup_maplist
    }
    Popup_loading{
        id: popup_loading
    }

    Tool_Keyboard{
        id: keyboard
    }
    Tool_KeyPad{
        id: keypad
    }

}
