#include "TTSHandler.h"

TTSHandler::TTSHandler()
{
    // 네트워크 연결 관리
    manager = new QNetworkAccessManager(this);

    readVoiceSetting();
}

void TTSHandler::setVoice(QString name, QString lan){
    curVoice.voice = name;
    curVoice.language = lan;
}

void TTSHandler::setVoiceDetail(int speed, int pitch, int alpha, int emotion, int emotion_strength){
    curVoice.speed = speed;
    curVoice.pitch = pitch;
    curVoice.alpha = alpha;
    curVoice.emotion = emotion;
    curVoice.emotion_strength = emotion_strength;
}

QString TTSHandler::getMentionBasicStr(QString lan, QString text){
    if(lan == "ko"){
        if(text == "move_serving"){return "서빙을 시작합니다";}
        if(text == "move_calling"){return "호출하신 곳으로 이동합니다";}
        if(text == "move_charging"){return "충전위치로 이동합니다";}
        if(text == "move_resting"){return "대기위치로 이동합니다";}
        if(text == "move_cleaning"){return "퇴식위치로 이동합니다";}
        if(text == "move_patrol"){ return "지정순회를 시작합니다";}
        if(text == "move_next"){   return "다음위치로 이동합니다";}

        if(text == "hello"){       return "안녕하세요";}
        if(text == "thanks"){      return "감사합니다";}
        if(text == "sorry"){       return "죄송합니다";}
        if(text == "excuseme"){    return "죄송합니다. 잠시만 지나가겠습니다";}
        if(text == "moving"){      return "로봇이 서빙 중입니다";}

        if(text == "error_no_path"){ "경로를 찾을 수 없습니다";}
        if(text == "error_localization"){
            return "위치를 찾을 수 없습니다";}
        if(text == "error_battery"){return "배터리가 부족합니다";}
        if(text == "error_emo"){   return "비상전원스위치가 눌렸습니다";}

        if(text == "pickup"){      return "트레이의 제품을 픽업하신 후){확인버튼을 눌러주세요";}
        if(text == "callme"){      return "부르셨나요? 이용이 끝나신 후 확인버튼을 눌러주세요";}

        if(text == "start_operation"){
            return "운영을 시작합니다";}

        if(text == "start_charging"){return"충전을 시작합니다";}
        if(text == "stop_charging"){ return"충전이 종료되었습니다";}
        if(text == "charging"){    return "충전 중 입니다";}

        if(text == "start_mapping"){ return"매핑을 시작합니다";}
        if(text == "stop_mapping"){return "매핑을 종료합니다";}

        if(text == "test"){return "테스트 음성입니다";}
    }else if(lan == "en"){
        if(text == "move_serving"){return "I'll start serving";}
        if(text == "move_calling"){return "I'm heading to the requested location";}
        if(text == "move_charging"){return "Moving to the charging station";}
        if(text == "move_resting"){return "Moving to the waiting area";}
        if(text == "move_cleaning"){return "Heading to the dining area";}
        if(text == "move_patrol"){ return "Starting designated patrol";}
        if(text == "move_next"){   return "Moving to the next location";}

        if(text == "hello"){       return "Hello";}
        if(text == "thanks"){      return "Thank you";}
        if(text == "sorry"){       return "I'm sorry";}
        if(text == "excuseme"){    return "sorry){please wait a moment";}
        if(text == "moving"){      return "The robot is currently serving";}

        if(text == "error_no_path"){return"Unable to find the route";}
        if(text == "error_localization"){return"Unable to find my location";}
        if(text == "error_battery"){ return"Low battery";}
        if(text == "error_emo"){   return "Emergency power switch has been pressed";}

        if(text == "pickup"){      return "Please pick up the item from the tray and press the confirm button";}
        if(text == "callme"){      return "Did you call? Please press the confirm button when you're done";}

        if(text == "start_operation"){return "Starting operation";}

        if(text == "start_charging"){return "Starting charging";}
        if(text == "stop_charging"){ return "Charging complete";}
        if(text == "charging"){    return "Currently charging";}

        if(text == "start_mapping"){return "Starting mapping";}
        if(text == "stop_mapping"){return "Mapping complete";}

        if(text == "test"){return "This is a test voice";}
    }else if(lan == "zh-CN"){
        if(text == "move_serving"){return "开始服务";}
        if(text == "move_calling"){return "前往您呼叫的地点";}
        if(text == "move_charging"){return "前往充电位置";}
        if(text == "move_resting"){return "前往等待位置";}
        if(text == "move_cleaning"){return "前往就餐位置";}
        if(text == "move_patrol"){ return "开始指定巡逻";}
        if(text == "move_next"){   return "前往下一个位置";}

        if(text == "hello"){       return "你好";}
        if(text == "thanks"){      return "谢谢";}
        if(text == "sorry"){       return "对不起";}
        if(text == "excuseme"){    return "对不起，请稍等片刻";}
        if(text == "moving"){      return "机器人正在服务中";}

        if(text == "error_no_path"){return "无法找到路径";}
        if(text == "error_localization"){return "无法找到位置";}
        if(text == "error_battery"){return "电池电量不足";}
        if(text == "error_emo"){   return "紧急电源开关已按下";}

        if(text == "pickup"){      return "取走托盘上的物品后，请按下确认按钮";}
        if(text == "callme"){      return "您呼叫了吗？完成后请按下确认按钮";}

        if(text == "start_operation"){return "开始运营";}

        if(text == "start_charging"){return "开始充电";}
        if(text == "stop_charging"){return "充电已完成";}
        if(text == "charging"){    return "正在充电";}

        if(text == "start_mapping"){return "开始地图绘制";}
        if(text == "stop_mapping"){return "地图绘制完成";}
        if(text == "test"){return "这是一个测试音频";}
    }else if(lan == "ja"){
        if(text == "move_serving"){return "サービスを開始します";}
        if(text == "move_calling"){return "お呼びの場所に移動します";}
        if(text == "move_charging"){return "充電場所に移動します";}
        if(text == "move_resting"){return "待機場所に移動します";}
        if(text == "move_cleaning"){return "食事場所に移動します";}
        if(text == "move_patrol"){ return "指定された巡回を開始します";}
        if(text == "move_next"){   return "次の場所に移動します";}

        if(text == "hello"){       return "こんにちは";}
        if(text == "thanks"){      return "ありがとうございます";}
        if(text == "sorry"){       return "申し訳ありません";}
        if(text == "excuseme"){    return "申し訳ありません。少々お待ちください";}
        if(text == "moving"){      return "ロボットがサービス中です";}

        if(text == "error_no_path"){return "経路が見つかりません";}
        if(text == "error_localization"){return "場所が見つかりません";}
        if(text == "error_battery"){return "バッテリーが不足しています";}
        if(text == "error_emo"){   return "緊急電源スイッチが押されました";}

        if(text == "pickup"){      return "トレイの商品を取り出した後、確認ボタンを押してください";}
        if(text == "callme"){      return "呼びましたか？ご利用が終わった後、確認ボタンを押してください";}

        if(text == "start_operation"){ return "運用を開始します";}

        if(text == "start_charging"){return "充電を開始します";}
        if(text == "stop_charging"){return "充電が完了しました";}
        if(text == "charging"){    return "充電中です";}

        if(text == "start_mapping"){return "マッピングを開始します";}
        if(text == "stop_mapping"){return "マッピングが終了しました";}
        if(text == "test"){return "これはテスト音声です";}
    }else if(lan == "es"){
        if(text == "move_serving"){return "Comenzando el servicio";}
        if(text == "move_calling"){return "Dirigiéndome hacia el lugar solicitado";}
        if(text == "move_charging"){return "Dirigiéndome hacia la estación de carga";}
        if(text == "move_resting"){return "Dirigiéndome hacia el área de espera.";}
        if(text == "move_cleaning"){return "Dirigiéndome hacia el área de comida.";}
        if(text == "move_patrol"){ return "Comenzando la patrulla designada.";}
        if(text == "move_next"){   return "Dirigiéndome hacia la próxima ubicación.";}
        if(text == "hello"){       return "Hola.";}
        if(text == "thanks"){      return "Gracias.";}
        if(text == "sorry"){       return "Lo siento.";}
        if(text == "excuseme"){    return "Lo siento){por favor espere un momento.";}
        if(text == "moving"){      return "El robot está sirviendo actualmente.";}
        if(text == "error_no_path"){return "No se puede encontrar la ruta.";}

        if(text == "error_localization"){return "No se puede encontrar la ubicación.";}

        if(text == "error_battery"){return "Batería baja.";}
        if(text == "error_emo"){   return "Se ha presionado el interruptor de emergencia.";}
        if(text == "pickup"){      return "Por favor){recoja el producto de la bandeja y luego presione el botón de confirmación.";}
        if(text == "callme"){      return "¿Me llamaste? Por favor){presiona el botón de confirmación cuando hayas terminado.";}
        if(text == "start_operation"){return "Comenzando la operación.";}
        if(text == "start_charging"){return "Comenzando la carga.";}
        if(text == "stop_charging"){return "La carga ha sido completada.";}
        if(text == "charging"){    return "Cargando actualmente.";}
        if(text == "start_mapping"){return "Comenzando el mapeo.";}
        if(text == "stop_mapping"){return "Mapeo completado.";}
        if(text == "test"){return "Este es un audio de prueba";}
    }else if(lan == "ru"){
        if(text == "move_serving"){    return "Начинаю обслуживание.";}
        if(text == "move_calling"){    return "Перехожу к запрошенному месту.";}
        if(text == "move_charging"){   return "Перехожу к месту зарядки.";}
        if(text == "move_resting"){    return "Перехожу на место ожидания.";}
        if(text == "move_cleaning"){   return "Перехожу на место для приема пищи.";}
        if(text == "move_patrol"){     return "Начинаю заданное обходное движение.";}
        if(text == "move_next"){       return "Перехожу к следующему месту.";}
        if(text == "hello"){           return "Здравствуйте.";}
        if(text == "thanks"){          return "Спасибо.";}
        if(text == "sorry"){           return "Извините.";}
        if(text == "excuseme"){        return "Извините){пожалуйста){подождите немного.";}
        if(text == "moving"){          return "Робот находится в процессе обслуживания.";}
        if(text == "error_no_path"){   return "Не удается найти маршрут.";}
     if(text == "error_localization"){ return "Не удается найти местоположение.";}
        if(text == "error_battery"){   return "Низкий уровень заряда батареи.";}
        if(text == "error_emo"){       return "Был нажат аварийный выключатель питания.";}
        if(text == "pickup"){          return "Пожалуйста){возьмите товар с подноса){затем нажмите кнопку подтверждения.";}
        if(text == "callme"){          return "Вас вызывали? Пожалуйста){нажмите кнопку подтверждения){когда закончите.";}
        if(text == "start_operation"){ return "Начинаю операцию.";}
        if(text == "start_charging"){  return "Начинаю зарядку.";}
        if(text == "stop_charging"){   return "Зарядка завершена.";}
        if(text == "charging"){        return "В процессе зарядки.";}
        if(text == "start_mapping"){   return "Начинаю создание карты.";}
        if(text == "stop_mapping"){    return "Картирование завершено.";}
        if(text == "test"){return "Это тестовый голос";}
    }else if(lan == "de"){
        if(text == "move_serving"){        return "Ich beginne mit dem Servieren.";}
        if(text == "move_calling"){        return "Ich bewege mich zu dem angeforderten Ort.";}
        if(text == "move_charging"){       return "Ich bewege mich zur Ladestation.";}
        if(text == "move_resting"){        return "Ich bewege mich zum Wartebereich.";}
        if(text == "move_cleaning"){       return "Ich bewege mich zum Essbereich.";}
        if(text == "move_patrol"){         return "Ich beginne mit der festgelegten Patrouille.";}
        if(text == "move_next"){           return "Ich bewege mich zur nächsten Position.";}
        if(text == "hello"){               return "Hallo.";}
        if(text == "thanks"){              return "Danke.";}
        if(text == "sorry"){               return "Es tut mir leid.";}
        if(text == "excuseme"){            return "Es tut mir leid){bitte warten Sie einen Moment.";}
        if(text == "moving"){              return "Der Roboter serviert gerade.";}
        if(text == "error_no_path"){       return "Die Route konnte nicht gefunden werden.";}
        if(text == "error_localization"){  return "Der Standort konnte nicht gefunden werden.";}
        if(text == "error_battery"){       return "Batterie ist schwach.";}
        if(text == "error_emo"){           return "Notstromschalter wurde betätigt.";}
        if(text == "pickup"){              return "Bitte nehmen Sie das Produkt aus der Ablage und drücken Sie dann die Bestätigungstaste.";}
        if(text == "callme"){              return "Haben Sie gerufen? Bitte drücken Sie die Bestätigungstaste){wenn Sie fertig sind.";}
        if(text == "start_operation"){     return "Ich beginne mit dem Betrieb.";}
        if(text == "start_charging"){      return "Ich beginne mit dem Laden.";}
        if(text == "stop_charging"){       return "Das Laden ist abgeschlossen.";}
        if(text == "charging"){            return "Es wird gerade geladen.";}
        if(text == "start_mapping"){       return "Ich beginne mit der Kartierung.";}
        if(text == "stop_mapping"){        return "Die Kartierung ist abgeschlossen.";}
        if(text == "test"){return "Dies ist eine Teststimme";}
    }
}

void TTSHandler::setMentionBasic(QString lan){
    curVoice.language = lan;
    plog->write("[TTS] setMentionBasic : "+lan);
    if(lan == "ko"){
        setMentionStr("move_serving",   "서빙을 시작합니다");
        setMentionStr("move_calling",   "호출하신 곳으로 이동합니다");
        setMentionStr("move_charging",  "충전위치로 이동합니다");
        setMentionStr("move_resting",   "대기위치로 이동합니다");
        setMentionStr("move_cleaning",  "퇴식위치로 이동합니다");
        setMentionStr("move_patrol",    "지정순회를 시작합니다");
        setMentionStr("move_next",      "다음위치로 이동합니다");

        setMentionStr("hello",          "안녕하세요");
        setMentionStr("thanks",         "감사합니다");
        setMentionStr("sorry",          "죄송합니다");
        setMentionStr("excuseme",       "죄송합니다. 잠시만 지나가겠습니다");
        setMentionStr("moving",         "로봇이 서빙 중입니다");

        setMentionStr("error_no_path",  "경로를 찾을 수 없습니다");
        setMentionStr("error_localization","위치를 찾을 수 없습니다");
        setMentionStr("error_battery",  "배터리가 부족합니다");
        setMentionStr("error_emo",      "비상전원스위치가 눌렸습니다");

        setMentionStr("pickup",         "트레이의 제품을 픽업하신 후, 확인버튼을 눌러주세요");
        setMentionStr("callme",         "부르셨나요? 이용이 끝나신 후 확인버튼을 눌러주세요");

        setMentionStr("start_operation","운영을 시작합니다");

        setMentionStr("start_charging", "충전을 시작합니다");
        setMentionStr("stop_charging",  "충전이 종료되었습니다");
        setMentionStr("charging",       "충전 중 입니다");

        setMentionStr("start_mapping",  "매핑을 시작합니다");
        setMentionStr("stop_mapping",   "매핑을 종료합니다");

        setMentionStr("test",   "테스트 음성입니다");
    }else if(lan == "en"){
        setMentionStr("move_serving",   "I'll start serving");
        setMentionStr("move_calling",   "I'm heading to the requested location");
        setMentionStr("move_charging",  "Moving to the charging station");
        setMentionStr("move_resting",   "Moving to the waiting area");
        setMentionStr("move_cleaning",  "Heading to the dining area");
        setMentionStr("move_patrol",    "Starting designated patrol");
        setMentionStr("move_next",      "Moving to the next location");

        setMentionStr("hello",          "Hello");
        setMentionStr("thanks",         "Thank you");
        setMentionStr("sorry",          "I'm sorry");
        setMentionStr("excuseme",       "sorry, please wait a moment");
        setMentionStr("moving",         "The robot is currently serving");

        setMentionStr("error_no_path",  "Unable to find the route");
        setMentionStr("error_localization","Unable to find my location");
        setMentionStr("error_battery",  "Low battery");
        setMentionStr("error_emo",      "Emergency power switch has been pressed");

        setMentionStr("pickup",         "Please pick up the item from the tray and press the confirm button");
        setMentionStr("callme",         "Did you call? Please press the confirm button when you're done");

        setMentionStr("start_operation","Starting operation");

        setMentionStr("start_charging", "Starting charging");
        setMentionStr("stop_charging",  "Charging complete");
        setMentionStr("charging",       "Currently charging");

        setMentionStr("start_mapping",  "Starting mapping");
        setMentionStr("stop_mapping",   "Mapping complete");

        setMentionStr("test",   "This is a test voice");
    }else if(lan == "zh-CN"){
        setMentionStr("move_serving",   "开始服务");
        setMentionStr("move_calling",   "前往您呼叫的地点");
        setMentionStr("move_charging",  "前往充电位置");
        setMentionStr("move_resting",   "前往等待位置");
        setMentionStr("move_cleaning",  "前往就餐位置");
        setMentionStr("move_patrol",    "开始指定巡逻");
        setMentionStr("move_next",      "前往下一个位置");

        setMentionStr("hello",          "你好");
        setMentionStr("thanks",         "谢谢");
        setMentionStr("sorry",          "对不起");
        setMentionStr("excuseme",       "对不起，请稍等片刻");
        setMentionStr("moving",         "机器人正在服务中");

        setMentionStr("error_no_path",  "无法找到路径");
        setMentionStr("error_localization","无法找到位置");
        setMentionStr("error_battery",  "电池电量不足");
        setMentionStr("error_emo",      "紧急电源开关已按下");

        setMentionStr("pickup",         "取走托盘上的物品后，请按下确认按钮");
        setMentionStr("callme",         "您呼叫了吗？完成后请按下确认按钮");

        setMentionStr("start_operation","开始运营");

        setMentionStr("start_charging", "开始充电");
        setMentionStr("stop_charging",  "充电已完成");
        setMentionStr("charging",       "正在充电");

        setMentionStr("start_mapping",  "开始地图绘制");
        setMentionStr("stop_mapping",   "地图绘制完成");
        setMentionStr("test",   "这是一个测试音频");
    }else if(lan == "ja"){
        setMentionStr("move_serving",   "サービスを開始します");
        setMentionStr("move_calling",   "お呼びの場所に移動します");
        setMentionStr("move_charging",  "充電場所に移動します");
        setMentionStr("move_resting",   "待機場所に移動します");
        setMentionStr("move_cleaning",  "食事場所に移動します");
        setMentionStr("move_patrol",    "指定された巡回を開始します");
        setMentionStr("move_next",      "次の場所に移動します");

        setMentionStr("hello",          "こんにちは");
        setMentionStr("thanks",         "ありがとうございます");
        setMentionStr("sorry",          "申し訳ありません");
        setMentionStr("excuseme",       "申し訳ありません。少々お待ちください");
        setMentionStr("moving",         "ロボットがサービス中です");

        setMentionStr("error_no_path",  "経路が見つかりません");
        setMentionStr("error_localization","場所が見つかりません");
        setMentionStr("error_battery",  "バッテリーが不足しています");
        setMentionStr("error_emo",      "緊急電源スイッチが押されました");

        setMentionStr("pickup",         "トレイの商品を取り出した後、確認ボタンを押してください");
        setMentionStr("callme",         "呼びましたか？ご利用が終わった後、確認ボタンを押してください");

        setMentionStr("start_operation","運用を開始します");

        setMentionStr("start_charging", "充電を開始します");
        setMentionStr("stop_charging",  "充電が完了しました");
        setMentionStr("charging",       "充電中です");

        setMentionStr("start_mapping",  "マッピングを開始します");
        setMentionStr("stop_mapping",   "マッピングが終了しました");
        setMentionStr("test",   "これはテスト音声です");
    }else if(lan == "es"){
        setMentionStr("move_serving",   "Comenzando el servicio");
        setMentionStr("move_calling",   "Dirigiéndome hacia el lugar solicitado");
        setMentionStr("move_charging",  "Dirigiéndome hacia la estación de carga");
        setMentionStr("move_resting",   "Dirigiéndome hacia el área de espera.");
        setMentionStr("move_cleaning",  "Dirigiéndome hacia el área de comida.");
        setMentionStr("move_patrol",    "Comenzando la patrulla designada.");
        setMentionStr("move_next",      "Dirigiéndome hacia la próxima ubicación.");
        setMentionStr("hello",          "Hola.");
        setMentionStr("thanks",         "Gracias.");
        setMentionStr("sorry",          "Lo siento.");
        setMentionStr("excuseme",       "Lo siento, por favor espere un momento.");
        setMentionStr("moving",         "El robot está sirviendo actualmente.");
        setMentionStr("error_no_path",  "No se puede encontrar la ruta.");

        setMentionStr("error_localization","No se puede encontrar la ubicación.");

        setMentionStr("error_battery",  "Batería baja.");
        setMentionStr("error_emo",      "Se ha presionado el interruptor de emergencia.");
        setMentionStr("pickup",         "Por favor, recoja el producto de la bandeja y luego presione el botón de confirmación.");
        setMentionStr("callme",         "¿Me llamaste? Por favor, presiona el botón de confirmación cuando hayas terminado.");
        setMentionStr("start_operation","Comenzando la operación.");
        setMentionStr("start_charging", "Comenzando la carga.");
        setMentionStr("stop_charging",  "La carga ha sido completada.");
        setMentionStr("charging",       "Cargando actualmente.");
        setMentionStr("start_mapping",  "Comenzando el mapeo.");
        setMentionStr("stop_mapping",   "Mapeo completado.");
        setMentionStr("test",   "Este es un audio de prueba");
    }else if(lan == "ru"){
        setMentionStr("move_serving",       "Начинаю обслуживание.");
        setMentionStr("move_calling",       "Перехожу к запрошенному месту.");
        setMentionStr("move_charging",      "Перехожу к месту зарядки.");
        setMentionStr("move_resting",       "Перехожу на место ожидания.");
        setMentionStr("move_cleaning",      "Перехожу на место для приема пищи.");
        setMentionStr("move_patrol",        "Начинаю заданное обходное движение.");
        setMentionStr("move_next",          "Перехожу к следующему месту.");
        setMentionStr("hello",              "Здравствуйте.");
        setMentionStr("thanks",             "Спасибо.");
        setMentionStr("sorry",              "Извините.");
        setMentionStr("excuseme",           "Извините, пожалуйста, подождите немного.");
        setMentionStr("moving",             "Робот находится в процессе обслуживания.");
        setMentionStr("error_no_path",      "Не удается найти маршрут.");
     setMentionStr("error_localization",    "Не удается найти местоположение.");
        setMentionStr("error_battery",      "Низкий уровень заряда батареи.");
        setMentionStr("error_emo",          "Был нажат аварийный выключатель питания.");
        setMentionStr("pickup",             "Пожалуйста, возьмите товар с подноса, затем нажмите кнопку подтверждения.");
        setMentionStr("callme",             "Вас вызывали? Пожалуйста, нажмите кнопку подтверждения, когда закончите.");
        setMentionStr("start_operation",    "Начинаю операцию.");
        setMentionStr("start_charging",     "Начинаю зарядку.");
        setMentionStr("stop_charging",      "Зарядка завершена.");
        setMentionStr("charging",           "В процессе зарядки.");
        setMentionStr("start_mapping",      "Начинаю создание карты.");
        setMentionStr("stop_mapping",       "Картирование завершено.");
        setMentionStr("test",   "Это тестовый голос");
    }else if(lan == "de"){
        setMentionStr("move_serving",           "Ich beginne mit dem Servieren.");
        setMentionStr("move_calling",           "Ich bewege mich zu dem angeforderten Ort.");
        setMentionStr("move_charging",          "Ich bewege mich zur Ladestation.");
        setMentionStr("move_resting",           "Ich bewege mich zum Wartebereich.");
        setMentionStr("move_cleaning",          "Ich bewege mich zum Essbereich.");
        setMentionStr("move_patrol",            "Ich beginne mit der festgelegten Patrouille.");
        setMentionStr("move_next",              "Ich bewege mich zur nächsten Position.");
        setMentionStr("hello",                  "Hallo.");
        setMentionStr("thanks",                 "Danke.");
        setMentionStr("sorry",                  "Es tut mir leid.");
        setMentionStr("excuseme",               "Es tut mir leid, bitte warten Sie einen Moment.");
        setMentionStr("moving",                 "Der Roboter serviert gerade.");
        setMentionStr("error_no_path",          "Die Route konnte nicht gefunden werden.");
        setMentionStr("error_localization",     "Der Standort konnte nicht gefunden werden.");
        setMentionStr("error_battery",          "Batterie ist schwach.");
        setMentionStr("error_emo",              "Notstromschalter wurde betätigt.");
        setMentionStr("pickup",                 "Bitte nehmen Sie das Produkt aus der Ablage und drücken Sie dann die Bestätigungstaste.");
        setMentionStr("callme",                 "Haben Sie gerufen? Bitte drücken Sie die Bestätigungstaste, wenn Sie fertig sind.");
        setMentionStr("start_operation",        "Ich beginne mit dem Betrieb.");
        setMentionStr("start_charging",         "Ich beginne mit dem Laden.");
        setMentionStr("stop_charging",          "Das Laden ist abgeschlossen.");
        setMentionStr("charging",               "Es wird gerade geladen.");
        setMentionStr("start_mapping",          "Ich beginne mit der Kartierung.");
        setMentionStr("stop_mapping",           "Die Kartierung ist abgeschlossen.");
        setMentionStr("test",   "Dies ist eine Teststimme");
    }
}

void TTSHandler::setMentionStr(QString text, QString mention){
    QString ini_path = QDir::homePath()+"/RB_MOBILE/config/voice_config.ini";
    QSettings setting(ini_path, QSettings::IniFormat);

    setting.setValue("MENTION/"+text, mention);

}

QString TTSHandler::getMentionStr(QString text){
    QString ini_path = QDir::homePath()+"/RB_MOBILE/config/voice_config.ini";
    QSettings setting(ini_path, QSettings::IniFormat);
    setting.beginGroup("MENTION");
    return setting.value(text).toString();
}

QString TTSHandler::getVoiceLanguage(int language){
    QString language_name = "";
    if(language == 0){
        language_name = "ko";
    }else if(language == 1){
        language_name = "en";
    }else if(language == 2){
        language_name = "zh-CN";
    }else if(language == 3){
        language_name = "ja";
    }else if(language == 4){
        language_name = "es";
    }else if(language == 5){
        language_name = "ru";
    }else if(language == 6){
        language_name = "de";
    }else if(language == 7){
        language_name = "la";
    }else if(language == 8){
        language_name = "id";
    }
    return language_name;
}

QString TTSHandler::getVoiceName(int language, int voice){
    QString voice_name = "none";
    if(curVoice.mode == "tts"){
        if(language == 0){
            if(voice == 0){
                voice_name = "vdain";
            }else if(voice == 1){
                voice_name = "vara";
            }else if(voice == 2){
                voice_name = "nhajun";
            }else if(voice == 3){
                voice_name = "njooahn";
            }else if(voice == 4){
                voice_name = "nsangdo";
            }else if(voice == 5){
                voice_name = "nsunhee";
            }else if(voice == 6){
                voice_name = "nkyungtae";
            }else if(voice == 7){
                voice_name = "nsabina";
            }else if(voice == 8){
                voice_name = "nmammon";
            }
        }else if(language == 1){
            if(voice == 0){
                voice_name = "djoey";
            }else if(voice == 1){
                voice_name = "danna";
            }else if(voice == 2){
                voice_name = "matt";
            }
        }else if(language == 2){
            if(voice == 0){
                voice_name = "meimei";
            }else if(voice == 1){
                voice_name = "liangliang";
            }
        }else if(language == 3){
            if(voice == 0){
                voice_name = "dmio";
            }else if(voice == 1){
                voice_name = "ntomoko";
            }else if(voice == 2){
                voice_name = "dayumu";
            }else if(voice == 3){
                voice_name = "shinji";
            }
        }else if(language == 4){
            if(voice == 0){
                voice_name = "carmen";
            }else if(voice == 1){
                voice_name = "jose";
            }
        }else if(language == 5){
            voice_name = "ru";
        }else if(language == 6){
            voice_name = "de";
        }else if(language == 7){
            voice_name = "la";
        }else if(language == 8){
            voice_name = "id";
        }else{
            voice_name = "none";
        }
    }else{
        if(voice == 0){
            voice_name = "child";
        }else{
            voice_name = "woman";
        }
    }
    return voice_name;
}

void TTSHandler::playcurVoice(){
    emit ready_play(curVoice);
}

void TTSHandler::readVoiceSetting(){
    QString ini_path = QDir::homePath()+"/RB_MOBILE/config/setting_config.ini";
    QSettings setting(ini_path, QSettings::IniFormat);
    setting.beginGroup("UI");
    curVoice.language = setting.value("voice_language").toString();
    curVoice.mode = setting.value("voice_mode").toString();
    curVoice.voice = setting.value("voice_name").toString();
    qDebug() << "readVoice : " << curVoice.voice;
    curVoice.speed = setting.value("voice_speed").toInt();
    curVoice.pitch = setting.value("voice_pitch").toInt();
    curVoice.alpha = setting.value("voice_alpha").toInt();
    curVoice.emotion = setting.value("voice_emotion").toInt();
    curVoice.emotion_strength = setting.value("voice_emotion_strength").toInt();
    curVoice.volume = setting.value("volume_voice").toInt();
}
void TTSHandler::makeTTS(ST_VOICE voice, bool play){
    if(voice.voice == "none" || voice.voice == "ru" || voice.voice == "de" || voice.voice == "la" || voice.voice == "id"){
        QString all = "from gtts import gTTS\n"
                      "tts = gTTS(text=\""+voice.mention.toUtf8()+"\", lang='"+voice.language.toUtf8()+"')\n"
                      "tts.save('"+voice.file.toUtf8()+"')";
        plog->write("[TTS] makeTTS : "+voice.mention + " -> "+ voice.file_path);
        PyRun_SimpleString(all.toUtf8().data());
    }else{
        QString post_str = "speaker="+voice.voice+"&speed="+QString::number(curVoice.speed)+"&pitch="+QString::number(curVoice.pitch)+"&emotion="+QString::number(curVoice.emotion)+"&emotion_strength="+QString::number(curVoice.emotion_strength)+"&format=mp3&text="+voice.mention;
        plog->write("[TTS] makeTTS (CLOVA) : "+post_str);

        QByteArray postDataSize = QByteArray::number(post_str.toUtf8().size());
        QUrl serviceURL(url);
        QNetworkRequest request(serviceURL);
        request.setRawHeader("Content-Type", "application/x-www-form-urlencoded");
        request.setRawHeader("X-NCP-APIGW-API-KEY-ID", clientID.toUtf8());
        request.setRawHeader("X-NCP-APIGW-API-KEY", clientSecret.toUtf8());

        QNetworkReply *reply = manager->post(request, post_str.toUtf8());
        qDebug() << reply->isOpen();
        connect(reply, &QNetworkReply::finished, [=](){
            generalReply(voice, play, reply);
        });
    }
}
void TTSHandler::generalReply(ST_VOICE voice, bool play, QNetworkReply *reply){
    if(reply->error() == QNetworkReply::NoError){
        QByteArray response = reply->readAll();

        QString path = QDir::homePath() + "/RB_MOBILE/voice";
        if(!QFile::exists(path)){
            QDir().mkdir(path);
        }

        QFile tempvoice(voice.file_path);
        if(tempvoice.open(QIODevice::ReadWrite)){
            tempvoice.write(response);
            tempvoice.close();
            plog->write("[TTS] makeTTS (CLOVA) : Save Voice file -> "+voice.file_path);
        }else{
            plog->write("[TTS] makeTTS (CLOVA) : Open voice file failed -> "+voice.file_path);
        }

        if(play){
            emit ready_play(voice);
        }
    }else{
        QString err = reply->errorString();
        plog->write("[TTS] makeTTS (CLOVA) : Reply Error -> "+err);
    }
    delete reply;
}
