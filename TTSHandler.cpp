#include "TTSHandler.h"

TTSHandler::TTSHandler()
{
    // 네트워크 연결 관리
    manager = new QNetworkAccessManager(this);

    readVoiceSetting();
}

void TTSHandler::setVoice(QString name, QString lan, QString mode){
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
            voice_name = "nmamon";
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
    }else{
        voice_name = "none";
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
    if(voice.voice == "none"){
        QString all = "from gtts import gTTS\n"
                      "tts = gTTS(text=\""+voice.mention+"\", lang='"+voice.language+"')\n"
                      "tts.save('"+voice.file_path+"')";
        plog->write("[TTS] makeTTS : "+voice.mention + " -> "+ voice.file_path);
        PyRun_SimpleString(all.toStdString().data());
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
        connect(reply, &QNetworkReply::finished, [=](){
            generalReply(voice, play, reply);
        });
    }
}
void TTSHandler::generalReply(ST_VOICE voice, bool play, QNetworkReply *reply){
    if(reply->error() == QNetworkReply::NoError){
        QByteArray response = reply->readAll();

        QFile tempvoice(voice.file_path);
        if(tempvoice.open(QIODevice::ReadWrite)){
            tempvoice.write(response);
            tempvoice.close();
            plog->write("[TTS] makeTTS (CLOVA) : Save Voice file -> "+voice.file_path);
        }

        if(play){
            emit ready_play(voice);
        }
    }else{
        QString err = reply->errorString();
        qDebug() << err;
    }
    delete reply;
}
