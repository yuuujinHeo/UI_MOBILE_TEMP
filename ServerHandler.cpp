#include "ServerHandler.h"
#include <iostream>
#include <QUrl>
#include <QDataStream>

using namespace std;
ServerHandler::ServerHandler()
{
    // 네트워크 연결 관리
    manager = new QNetworkAccessManager(this);
    goqual_manager = new QNetworkAccessManager(this);

    timer = new QTimer();
    connect(timer, SIGNAL(timeout()),this,SLOT(onTimer()));
    timer->start(TIMER_MS);

    call_server = new QtHttpServer(this);
    connect(call_server, SIGNAL(requestNeedsReply(QtHttpRequest*,QtHttpReply*)), this, SLOT(onCallRequestReply(QtHttpRequest*,QtHttpReply*)));
    call_server->start(8000);
    myID = getSetting("robot","SERVER","my_id");
    checkUpdate();
    startTime = QTime::currentTime();
//    sendRobotConfig();
    sendMaps();
//    uploadRelease(QDir::homePath()+"/RB_MOBILE/release/MAIN_MOBILE","hello..4");
//    uploadRelease(QDir::homePath()+"/RB_MOBILE/release/ExtProcess","hello..4");
//    uploadRelease(QDir::homePath()+"/RB_MOBILE/sh/autostart.sh","hello..4");
//    getGitCommits();



    // goqual_login.client_id = getSetting("setting","GOQUAL","client_id");
    // goqual_login.client_secret = getSetting("setting","GOQUAL","client_secret");
    // goqual_login.app_key = getSetting("setting","GOQUAL","app_key");
    goqual_login.id = getSetting("setting","GOQUAL","user_id");
    goqual_login.passwd = getSetting("setting","GOQUAL","user_passwd");

    goqual_token.access_key = getSetting("setting","GOQUAL","access_key");
    goqual_token.refresh_key = getSetting("setting","GOQUAL","refresh_key");
    goqual_token.expires_in = getSetting("setting","GOQUAL","expires_in").toInt();

}

// 오류를 출력하는 함수
void handleErrors(void) {
    ERR_print_errors_fp(stderr);
    abort();
}

QByteArray ServerHandler::encrypt(const QByteArray &text) {
    EVP_CIPHER_CTX *ctx;
    int len;
    int ciphertext_len;
    QByteArray key = goqual_login.app_key.left(32).toUtf8();
    QByteArray iv = goqual_login.app_key.left(16).toUtf8();

    // 출력 버퍼 초기화
    int ciphertext_buffer_len = text.size() + AES_BLOCK_SIZE;
    unsigned char *ciphertext = new unsigned char[ciphertext_buffer_len];

    // 컨텍스트 초기화
    if(!(ctx = EVP_CIPHER_CTX_new())) handleErrors();

    // 초기화 벡터와 키를 사용하여 암호화 초기화
    if(1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, (unsigned char*)key.data(), (unsigned char*)iv.data()))
        handleErrors();

    // 데이터를 암호화하고 출력 버퍼에 저장
    if(1 != EVP_EncryptUpdate(ctx, ciphertext, &len, (unsigned char*)text.data(), text.size()))
        handleErrors();
    ciphertext_len = len;

    // 암호화 완료
    if(1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len)) handleErrors();
    ciphertext_len += len;

    // 컨텍스트 정리
    EVP_CIPHER_CTX_free(ctx);

    // 결과를 QByteArray로 변환
    QByteArray result((char*)ciphertext, ciphertext_len);
    delete[] ciphertext;
    return result;
}

// Base64url 인코딩 함수
QString base64UrlEncode(const QByteArray &data) {
    QString base64 = data.toBase64();
    base64 = base64.replace("+", "-").replace("/", "_").replace("=", "");
    return base64;
}

void ServerHandler::goqualPost(QByteArray body, QString url){
    QByteArray postDataSize = QByteArray::number(body.size());
    QUrl serviceURL(url);
    QNetworkRequest request(serviceURL);
    request.setRawHeader("Content-Type", "application/json");
    request.setRawHeader("Content-Length", postDataSize);
    request.setRawHeader("Connection", "Keep-Alive");
    request.setRawHeader("AcceptEncoding", "gzip, deflate");
    request.setRawHeader("AcceptLanguage", "ko-KR,en,*");
    if(!url.contains("/token")){
        QString auth = "Bearer "+goqual_token.access_key;
        request.setRawHeader("Authorization",auth.toUtf8());
    }
    qDebug() << "POST===============================";
    qDebug() << body;
    QNetworkReply *reply = goqual_manager->post(request, body);
    connect(reply, &QNetworkReply::finished, [=](){
        parsingReply("GOQUAL",url,reply);
    });
}

void ServerHandler::goqualGet(QString url){
    QUrl serviceURL(url);
    QNetworkRequest request(serviceURL);
    QString auth = "Bearer "+goqual_token.access_key;

    request.setRawHeader("Content-Type","application./json");
    request.setRawHeader("Authorization",auth.toUtf8());

    QNetworkReply *reply = goqual_manager->get(request);
    connect(reply, &QNetworkReply::finished, [=](){
        parsingReply("GOQUAL",url,reply);
    });
}

void ServerHandler::getGoqualKey(){
    goqual_login.id = getSetting("setting","GOQUAL","user_id");
    goqual_login.passwd = getSetting("setting","GOQUAL","user_passwd");

    QString strBody = "{\"client_id\":\""+goqual_login.client_id+"\","+
          "\"client_secret\":\""+goqual_login.client_secret+"\","+
          "\"grant_type\":\"password\","+
          "\"username\":\""+goqual_login.id+"\","+
          "\"password\":\""+goqual_login.passwd+"\"}";

    qDebug() << "-----------------------------------------";
    qDebug() << strBody;
    QByteArray test = encrypt(strBody.toUtf8());
    QJsonObject json;
    json["data"] = base64UrlEncode(test);

    QByteArray json_string = QJsonDocument(json).toJson();
    goqualPost(json_string, goqual_url+"/openapi/token");

}

void ServerHandler::refreshGoqualKey(){
    goqual_login.id = "01020866685";
    goqual_login.passwd = "rainbow2011";

    QString strBody = "{\"client_id\":\""+goqual_login.client_id+"\","+
                      "\"client_secret\":\""+goqual_login.client_secret+"\","+
                      "\"grant_type\":\"refresh_token\","+
                      "\"refresh_token\":\""+goqual_token.refresh_key+"\"}";

    qDebug() << "-----------------------------------------";
    QByteArray test = encrypt(strBody.toUtf8());
    QJsonObject json;
    json["data"] = base64UrlEncode(test);

    QByteArray json_string = QJsonDocument(json).toJson();
    goqualPost(json_string, goqual_url+"/openapi/token/refresh");

}

void ServerHandler::getGoqualDevices(){
    if(goqual_token.access_key != ""){
        goqualGet(goqual_url+"/openapi/devices/state");
    }
}
void ServerHandler::setGoqualRelay(QString id, bool onoff){
    QJsonObject json;
    json["deviceId"] = id;
    QJsonObject requirements;
    requirements["power1"] = onoff;
    json["requirments"] = requirements;

    QByteArray json_string = QJsonDocument(json).toJson();
    goqualPost(json_string, goqual_url+"/openapi/control/"+id);
}

void ServerHandler::onTimer(){
    //주기적으로 서버에게 상태를 보냄.
    // getGoqualDevices();

    //Mobile Server
    if(mobile_connection){
        sendStatus();
    }else{
        static int count=0;
        if(++count%10 == 0){
            sendStatus();
        }
    }


    if(connection){
        postStatus();
//        if(myID == "serving.001.01.test" || myID == ""){
//            getNewID();
//        }else if(!send_config){
//            sendRobotConfig();
//            sendSettingConfig();
//            sendUpdateConfig();
//            sendStaticConfig();
//        }else if(!send_map){
//            sendMaps();
//            TIMER_MS = 60000;
//            timer->start(TIMER_MS);
//        }else{
//            postStatus();
//        }
    }

    QTime currentTime = QTime::currentTime();
    elapsedTime = QTime(0,0).addSecs(startTime.secsTo(currentTime));
}

void ServerHandler::sendStatus(){
    QJsonObject jout;

    jout["battery"] = probot->battery;
    jout["map_name"] = pmap->map_name;

    QByteArray ba = QJsonDocument(jout).toJson();

    serverPost("/status",ba);
}

void ServerHandler::onCallRequestReply(QtHttpRequest *request, QtHttpReply *reply){
    QByteArray rcvData = request->getRawData();
    QJsonObject jin = QJsonDocument::fromJson(rcvData).object();
    QJsonObject jout;



    if(request->getCommand() == "GET"){
        if(request->getUrl().toString().left(6) == "/state"){

            QStringList temp = request->getUrl().toString().split("/");
            if(temp.size() == 3){
                QString table = temp[2];
                jout["table"] = table;
                jout["robot_name"] = probot->name;
                // cur_reply_state.count = cur_state_request.count;
                // cur_reply_state.table = cur_state_request.table;

                //call_queue에 있는 지 여부 확인
                bool match = false;
                for(int i=0; i<pmap->call_queue.size(); i++){
                    if(pmap->call_queue[i] == table){
                        match = true;
                        break;
                    }
                }

                if(match){
                    //현재 목표가 맞는지 확인
                    //            qDebug() << probot->current_target.name << table << probot->running_state << ui_state;
                    if(probot->current_target.name == table){
                        if(ui_state == UI_STATE_MOVING){
                            if(probot->running_state == ROBOT_MOVING_NOT_READY){
                                jout["state"] = "error";
                                jout["error_state"] = 3;
                            }else if(probot->running_state == ROBOT_MOVING_READY){
                                jout["state"] = "wait";
                                jout["error_state"] = 1;
                            }else{
                                //moving, wait, paused
                                jout["state"] = "moving";
                                jout["error_state"] = 0;
                            }
                        }else if(ui_state == UI_STATE_PICKUP){
                            jout["state"] = "arrived";
                            jout["error_state"] = 0;
                        }else{
                            jout["state"] = "error";
                            jout["error_state"] = 2;
                        }
                    }else{
                        if(pmap->call_queue.size() == 0){
                            jout["state"] = "none";
                            jout["error_state"] = 0;
                        }else{
                            jout["state"] = "wait";
                            jout["error_state"] = 0;
                        }
                    }
                }else{
                    jout["state"] = "none";
                    jout["error_state"] = 0;
                }

                QByteArray json_string = QJsonDocument(jout).toJson();
                generalReply(reply, json_string);
            }else{
                reply->setStatusCode(QtHttpReply::BadRequest);
                emit reply->requestSendHeaders();
                return;
            }
        }else{
            reply->setStatusCode(QtHttpReply::BadRequest);
            emit reply->requestSendHeaders();
            return;
        }
    }else if(request->getCommand() == "POST"){
        // cur_call_request.count++;
        // cur_call_request.table = jin["table"].toString();
        // cur_call_request.purpose = jin["purpose"].toString();
        QString table = jin["table"].toString();

        if(table == ""){
            reply->setStatusCode(QtHttpReply::BadRequest);
            emit reply->requestSendHeaders();
            return;
        }

        if(request->getUrl() == QUrl("/call")){
            //check locations
            jout["table"] = table;
            //check locations
            int num = -1;
            for(int i=0; i<pmap->locations.size(); i++){
                if(pmap->locations[i].name == table){
                    num = i;
                    break;
                }
            }
            // cur_reply_call.count = cur_call_request.count;
            // cur_reply_call.table = cur_call_request.table;

            if(num > -1){
                //Queue 중복 확인
                for(int i=0; i<pmap->call_queue.size(); i++){
                    if(pmap->call_queue[i] == table){
                        //already queue in
                        QJsonObject jout;
                        jout["command"] = jin["command"];
                        jout["table"] = jin["table"];
                        jout["robot_name"] = probot->name;
                        jout["result"] = "duplicate";
                        jout["error_state"] = 0;
                        QByteArray json_string = QJsonDocument(jout).toJson();
                        generalReply(reply, json_string);
                        return;
                    }
                }
                qDebug() << "ui state = " << ui_state;
                //Robot State 확인
                if(ui_state == UI_STATE_CHARGING){
                    QJsonObject jout;
                    jout["command"] = jin["command"];
                    jout["table"] = jin["table"];
                    jout["robot_name"] = "";
                    jout["result"] = "none";
                    jout["error_state"] = 2;
                    QByteArray json_string = QJsonDocument(jout).toJson();
                    generalReply(reply, json_string);
                }else if(ui_state == UI_STATE_NONE || ui_state == UI_STATE_INITAILIZING || ui_state == UI_STATE_MOVEFAIL){
                    QJsonObject jout;
                    jout["command"] = jin["command"];
                    jout["table"] = jin["table"];
                    jout["robot_name"] = "";
                    jout["result"] = "none";
                    jout["error_state"] = 1;
                    QByteArray json_string = QJsonDocument(jout).toJson();
                    generalReply(reply, json_string);
                }else{
                    QJsonObject jout;
                    jout["command"] = jin["command"];
                    jout["table"] = jin["table"];
                    jout["robot_name"] = probot->name;
                    jout["result"] = "confirm";
                    jout["error_state"] = 0;
                    emit newCallOrder(table);
                    QByteArray json_string = QJsonDocument(jout).toJson();
                    generalReply(reply, json_string);
                }
            }else{
                QJsonObject jout;
                jout["command"] = jin["command"];
                jout["table"] = jin["table"];
                jout["robot_name"] = "";
                jout["result"] = "none";
                jout["error_state"] = 3;
                QByteArray json_string = QJsonDocument(jout).toJson();
                generalReply(reply, json_string);
            }
        }else{
            reply->setStatusCode(QtHttpReply::BadRequest);
            emit reply->requestSendHeaders();
            return;
        }
    }else{
        reply->setStatusCode(QtHttpReply::BadRequest);
        emit reply->requestSendHeaders();
        return;
    }
}
void ServerHandler::onCallRequestReply2(QtHttpRequest *request, QtHttpReply *reply){
    QByteArray rcvData = request->getRawData();
    QJsonObject jin = QJsonDocument::fromJson(rcvData).object();
    QString msgType = jin["command"].toString();
    QString table = jin["table"].toString();

    // qDebug() << request->getUrl() << request.g
    if(msgType == "calling"){
        //check locations
        int num = -1;
        for(int i=0; i<pmap->locations.size(); i++){
            if(pmap->locations[i].name == table){
                num = i;
                break;
            }
        }

//        qDebug() << "num " << num;

        if(num > -1){
            //Queue 중복 확인
            for(int i=0; i<pmap->call_queue.size(); i++){
                if(pmap->call_queue[i] == table){
                    //already queue in
                    QJsonObject jout;
                    jout["command"] = jin["command"];
                    jout["table"] = jin["table"];
                    jout["robot_name"] = probot->name;
                    jout["result"] = "duplicate";
                    jout["error_state"] = 0;
                    QByteArray json_string = QJsonDocument(jout).toJson();
                    generalReply(reply, json_string);
                    return;
                }
            }
            qDebug() << "ui state = " << ui_state;
            //Robot State 확인
            if(ui_state == UI_STATE_CHARGING){
                QJsonObject jout;
                jout["command"] = jin["command"];
                jout["table"] = jin["table"];
                jout["robot_name"] = "";
                jout["result"] = "none";
                jout["error_state"] = 2;
                QByteArray json_string = QJsonDocument(jout).toJson();
                generalReply(reply, json_string);
            }else if(ui_state == UI_STATE_NONE || ui_state == UI_STATE_INITAILIZING || ui_state == UI_STATE_MOVEFAIL){
                QJsonObject jout;
                jout["command"] = jin["command"];
                jout["table"] = jin["table"];
                jout["robot_name"] = "";
                jout["result"] = "none";
                jout["error_state"] = 1;
                QByteArray json_string = QJsonDocument(jout).toJson();
                generalReply(reply, json_string);
            }else{
                QJsonObject jout;
                jout["command"] = jin["command"];
                jout["table"] = jin["table"];
                jout["robot_name"] = probot->name;
                jout["result"] = "confirm";
                jout["error_state"] = 0;
                emit newCallOrder(table);
                QByteArray json_string = QJsonDocument(jout).toJson();
                generalReply(reply, json_string);
            }
        }else{
            QJsonObject jout;
            jout["command"] = jin["command"];
            jout["table"] = jin["table"];
            jout["robot_name"] = "";
            jout["result"] = "none";
            jout["error_state"] = 3;
            QByteArray json_string = QJsonDocument(jout).toJson();
            generalReply(reply, json_string);
        }
    }else if(msgType == "state"){
        QJsonObject jout;
        jout["command"] = jin["command"];
        jout["table"] = jin["table"];
        jout["robot_name"] = probot->name;

        //call_queue에 있는 지 여부 확인
        bool match = false;
        for(int i=0; i<pmap->call_queue.size(); i++){
            if(pmap->call_queue[i] == table){
                match = true;
                break;
            }
        }

        if(match){
            //현재 목표가 맞는지 확인
//            qDebug() << probot->current_target.name << table << probot->running_state << ui_state;
            if(probot->current_target.name == table){
                if(ui_state == UI_STATE_MOVING){
                    if(probot->running_state == ROBOT_MOVING_NOT_READY){
                        jout["state"] = "error";
                        jout["error_state"] = 3;
                    }else if(probot->running_state == ROBOT_MOVING_READY){
                        jout["state"] = "wait";
                        jout["error_state"] = 1;
                    }else{
                        //moving, wait, paused
                        jout["state"] = "moving";
                        jout["error_state"] = 0;
                    }
                }else if(ui_state == UI_STATE_PICKUP){
                    jout["state"] = "arrived";
                    jout["error_state"] = 0;
                }else{
                    jout["state"] = "error";
                    jout["error_state"] = 2;
                }
            }else{
                if(pmap->call_queue.size() == 0){
                    jout["state"] = "none";
                    jout["error_state"] = 0;
                }else{
                    jout["state"] = "wait";
                    jout["error_state"] = 0;
                }
            }
        }else{
            jout["state"] = "none";
            jout["error_state"] = 0;
        }
        QByteArray json_string = QJsonDocument(jout).toJson();
        generalReply(reply, json_string);
    }
}

void ServerHandler::generalReply(QtHttpReply *reply, QByteArray post_data){
    QByteArray postDataSize = QByteArray::number(post_data.size());

   qDebug() << "REPLY : " << post_data;

    reply->addHeader(QtHttpHeader::ContentType, QByteArrayLiteral("application/json"));
    reply->addHeader(QtHttpHeader::ContentLength, postDataSize);
    reply->addHeader(QtHttpHeader::Connection, QByteArrayLiteral("Keep-Alive"));
    reply->addHeader(QtHttpHeader::AcceptEncoding, QByteArrayLiteral("gzip, deflate"));
    reply->addHeader(QtHttpHeader::AcceptLanguage, QByteArrayLiteral("ko-KR,en,*"));

    reply->appendRawData(post_data);
    emit reply->requestSendHeaders();
    emit reply->requestSendData();
}


void ServerHandler::postStatus(){
    ClearJson(json_out);

    json_out["robot_id"] = "CAPTAIN";

    json_out["wifi_ip"] = probot->wifi_interface.ipv4;
    json_out["battery"] = probot->battery;
    json_out["exec_time"] = elapsedTime.toString("hh:mm:ss");
    json_out["map_name"] = pmap->map_name;

    json_out["state_ui"] = ui_state;
    json_out["state_charge"] = probot->status_charge;
    json_out["state_emo"] = probot->status_emo;
    json_out["state_running"] = probot->running_state;
    json_out["state_localization"] = probot->localization_state;
    json_out["state_motorlock"] = probot->status_lock;

    QByteArray temp_array = QJsonDocument(json_out).toJson();
    newPost(temp_array, serverURL+"/setstatus");
}

void ServerHandler::uploadRelease(QString file, QString message){
//    QString dir = QDir::homePath()+"/UI_MOBILE_release/MAIN_MOBILE";
    QFile exe(file);
    if(exe.open(QIODevice::ReadOnly)){
        plog->write("[SERVER] Upload Release : "+serverURL+"/upload/release/"+myID+"/"+message);
        sendfilePost(file, serverURL+"/release/upload/"+myID+"/"+message);
    }else{
        plog->write("[SERVER] Send UI : Failed (File not open)");
    }
}

void ServerHandler::checkUpdate(){
//    qDebug() << "checkUpdate : "  << getSetting("robot","SERVER","update");
    if(getSetting("robot","SERVER","update") == "true"){
        plog->write("[SERVER] Check Update : "+myID);
        update_list.clear();
        QJsonObject temp_out;
        temp_out["id"] = myID;
        QByteArray temp_array = QJsonDocument(temp_out).toJson();
        generalPost(temp_array, serverURL+"/update/"+myID);
        setSetting("robot","SERVER/update","false");
    }else{
        plog->write("[SERVER] Check Update : "+myID);
        update_list.clear();
        generalGet(serverURL+"/update/mylist/"+myID);
    }
}

void ServerHandler::doUpdateUI(QString version){
    plog->write("[SERVER] Do Update");
    // generalGet(serverURL+"/update/"+myID);
    QJsonObject body;
    QJsonObject auth;
    auth["name"] = "rainbow";
    body["program"] = "MAIN_MOBILE";
    body["new_version"] = version;
    body["cur_version"] = ui_version.version;
    body["auth"] = auth;
    body["path"] = QDir::homePath()+"/RB_MOBILE/release/MAIN_MOBILE";
    QByteArray temp_array = QJsonDocument(body).toJson();
    generalPost(temp_array,serverURL+"/update");
}

void ServerHandler::doUpdate(){
    plog->write("[SERVER] Do Update"+myID);
    generalGet(serverURL+"/update/"+myID);
}

void ServerHandler::getNewID(){
    ClearJson(json_out);
    json_out["server_group"] = getSetting("robot","SERVER","group");
    json_out["server_name"] = getSetting("robot","SERVER","name");
    json_out["id"] = myID;
    json_out["platform_name"] = getSetting("setting","ROBOT_TYPE","model");

    QByteArray temp_array = QJsonDocument(json_out).toJson();
//    qDebug() << temp_array;

    generalPost(temp_array,serverURL+"/setting/getname");
}

bool ServerHandler::need_update(){
    if(connection){
        return new_update;
    }else{
        return new_update_local;
    }
}

void ServerHandler::getNewVersion(QString filename){
    generalGet(fileserverURL+"/versions/"+filename);
}

void ServerHandler::getCurVersion(QString filename){
    generalGet(serverURL+"/versions/"+filename);
}

void ServerHandler::getNewVersions(QString filename){
    generalGet(fileserverURL+"/versions/all/"+filename);
}

void ServerHandler::getGitCommits(){
    plog->write("[SERVER] CMD : Get Git Commits");
    generalGet("https://api.github.com/repos/yuuujinHeo/release/commits");
//    generalGet("https://api.github.com/repos/yuuujinHeo/UI_MOBILE_release/commits");
}

void ServerHandler::sendRobotConfig(){
    QString dir = QDir::homePath()+"/RB_MOBILE/config/robot_config.ini";
    QFile config(dir);
    send_config = true;
    if(config.open(QIODevice::ReadOnly)){
        sendfilePost(dir, serverURL+"/upload/config/"+myID);
    }else{
        plog->write("[SERVER] Send Robot Config : Failed (File not open)");
    }
}

void ServerHandler::sendSettingConfig(){
    QString dir = QDir::homePath()+"/RB_MOBILE/config/setting_config.ini";
    QFile config(dir);
    send_config = true;
    if(config.open(QIODevice::ReadOnly)){
        sendfilePost(dir, serverURL+"/upload/config/"+myID);
    }else{
        plog->write("[SERVER] Send Setting Config : Failed (File not open)");
    }
}

void ServerHandler::sendStaticConfig(){
    QString dir = QDir::homePath()+"/RB_MOBILE/config/static_config.ini";
    QFile config(dir);
    send_config = true;
    if(config.open(QIODevice::ReadOnly)){
        sendfilePost(dir, serverURL+"/upload/config/"+myID);
    }else{
        plog->write("[SERVER] Send Static Config : Failed (File not open)");
    }
}

void ServerHandler::sendUpdateConfig(){
    QString dir = QDir::homePath()+"/RB_MOBILE/config/update_config.ini";
    QFile config(dir);
    send_config = true;
    if(config.open(QIODevice::ReadOnly)){
        sendfilePost(dir, serverURL+"/upload/config/"+myID);
    }else{
        plog->write("[SERVER] Send Update Config : Failed (File not open)");
    }
}

void ServerHandler::sendMaps(){
    ZIPHandler zip;
    send_map = true;
    zip.makeMapZip(QDir::homePath(),getSetting("setting","MAP","map_name"));
    QString dir = QDir::homePath()+"/"+getSetting("setting","MAP","map_name")+".zip";
    QFile config(dir);
    if(config.open(QIODevice::ReadOnly)){
        newPostFile(dir, fileserverURL+"/upload/map");
    }else{
        plog->write("[SERVER] Send Map : Failed (File not open)");
    }
}

void ServerHandler::setSetting(QString file, QString name, QString value){
    QString ini_path = QDir::homePath()+"/RB_MOBILE/config/"+file+"_config.ini";
    QSettings setting(ini_path, QSettings::IniFormat);
    setting.setValue(name,value);
    plog->write("[SETTING] SET "+name+" VALUE TO "+value);
}


QString ServerHandler::getSetting(QString file, QString group, QString name){
    QString ini_path = QDir::homePath()+"/RB_MOBILE/config/"+file+"_config.ini";
    QSettings setting_robot(ini_path, QSettings::IniFormat);
    setting_robot.beginGroup(group);
    return setting_robot.value(name).toString();
}

void ServerHandler::serverPost(QString url, QByteArray body){
    QUrl _url(SERVER_URL+url);
    QNetworkRequest request(_url);
    QByteArray postDataSize = QByteArray::number(body.size());
    request.setRawHeader("Content-Type", "application/json");
    request.setRawHeader("Content-Length", postDataSize);
    request.setRawHeader("Connection", "Keep-Alive");
    request.setRawHeader("AcceptEncoding", "gzip, deflate");
    request.setRawHeader("AcceptLanguage", "ko-KR,en,*");

    QNetworkReply *reply = manager->post(request, body);
    connect(reply, &QNetworkReply::finished, [=](){
        parsingServer(url,reply);
    });
}

void ServerHandler::newPost(QByteArray post_data, QString url){
    QByteArray postDataSize = QByteArray::number(post_data.size());
    QUrl serviceURL(url);
    QNetworkRequest request(serviceURL);
    request.setRawHeader("Content-Type", "application/json");
    request.setRawHeader("Content-Length", postDataSize);
    request.setRawHeader("Connection", "Keep-Alive");
    request.setRawHeader("AcceptEncoding", "gzip, deflate");
    request.setRawHeader("AcceptLanguage", "ko-KR,en,*");

    QNetworkReply *reply = manager->post(request, post_data);
    connect(reply, &QNetworkReply::finished, [=](){
        parsingReply("POST",url,reply);
    });
}
void ServerHandler::newPostFile(QString file_dir, QString url){
    QUrl serviceURL(url);
    QNetworkRequest request(serviceURL);

    QHttpMultiPart *files = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    QStringList file_dirs = file_dir.split("/");
    QString filename = file_dirs[file_dirs.size()-1];

    QHttpPart filepart;
    filepart.setHeader(QNetworkRequest::ContentDispositionHeader,QVariant("form-data; name=\"file\"; filename=\""+filename+"\""));
    QFile *file = new QFile(file_dir);
    file->open(QIODevice::ReadOnly);
    filepart.setBody(file->readAll());
    file->setParent(files);

    files->append(filepart);

    quint32 random[6];
    QRandomGenerator::global()->fillRange(random);
    QByteArray boundary = "--boundary_zyl_"+ QByteArray::fromRawData(reinterpret_cast<char *>(random),sizeof(random)).toBase64();

    QByteArray contentType;
    contentType += "multipart/";
    contentType += "form-data";
    contentType += "; boundary=";
    contentType += boundary;
    files->setBoundary(boundary);
    request.setHeader(QNetworkRequest::ContentTypeHeader, contentType);

    QNetworkReply *reply = manager->post(request, files);
    connect(reply, &QNetworkReply::finished, [=](){
        files->setParent(reply);
        parsingReply("POST",url,reply);
    });
}
void ServerHandler::sendfilePost(QString file_dir, QString url){
//    QUrl serviceURL(url);
//    QNetworkRequest request(serviceURL);

//    QHttpMultiPart *files = new QHttpMultiPart(QHttpMultiPart::FormDataType);

//    QStringList file_dirs = file_dir.split("/");
//    QString filename = file_dirs[file_dirs.size()-1];

//    QHttpPart filepart;
//    filepart.setHeader(QNetworkRequest::ContentDispositionHeader,QVariant("form-data; name=\"file\"; filename=\""+filename+"\""));
//    QFile *file = new QFile(file_dir);
//    file->open(QIODevice::ReadOnly);
//    filepart.setBody(file->readAll());
//    file->setParent(files);

//    files->append(filepart);

//    quint32 random[6];
//    QRandomGenerator::global()->fillRange(random);
//    QByteArray boundary = "--boundary_zyl_"+ QByteArray::fromRawData(reinterpret_cast<char *>(random),sizeof(random)).toBase64();

//    QByteArray contentType;
//    contentType += "multipart/";
//    contentType += "form-data";
//    contentType += "; boundary=";
//    contentType += boundary;
//    files->setBoundary(boundary);
//    request.setHeader(QNetworkRequest::ContentTypeHeader, contentType);

//    QNetworkReply *reply = manager->post(request, files);
//    connect(reply, &QNetworkReply::finished, [=](){
//        files->setParent(reply);
//        parsingReply("POST",url,reply);
//    });
}
// 공통적으로 사용되는 POST 구문 : 출력으로 응답 정보를 보냄
void ServerHandler::generalPost(QByteArray post_data, QString url){
   QByteArray postDataSize = QByteArray::number(post_data.size());
   QUrl serviceURL(url);
   QNetworkRequest request(serviceURL);
   request.setRawHeader("Content-Type", "application/json");
   request.setRawHeader("Content-Length", postDataSize);
   request.setRawHeader("Connection", "Keep-Alive");
   request.setRawHeader("AcceptEncoding", "gzip, deflate");
   request.setRawHeader("AcceptLanguage", "ko-KR,en,*");

   QNetworkReply *reply = manager->post(request, post_data);
   connect(reply, &QNetworkReply::finished, [=](){
       parsingReply("POST",url,reply);
   });
}

void ServerHandler::parsingServer(QString url, QNetworkReply *reply){
    if(reply->error() == QNetworkReply::NoError){
        QByteArray response = reply->readAll();
        mobile_connection = true;

        if(url.contains("/versions/MAIN_MOBILE")){
            QJsonObject temp = QJsonDocument::fromJson(response).object();
            ui_version.version = temp["data"].toObject()["version"].toString();
            ui_version.prev_version = temp["data"].toObject()["prev_version"].toString();
            ui_version.date = temp["data"].toObject()["date"].toString();
            qDebug() << "version get " << ui_version.version << ui_version.date;
        }

    }else{
        QString err = reply->errorString();
        qDebug() << "ERROR==========================" << err;
        if(reply->error()>0 && reply->error()<100){
            mobile_connection = false;
        }
    }
}

void ServerHandler::parsingReply(QString type, QString url, QNetworkReply *reply){

    if(reply->error() == QNetworkReply::NoError){
        if(url.left(22) == "https://api.github.com"){
            QByteArray response = reply->readAll();
            ClearJson(json_in);
            QJsonArray git_array = QJsonDocument::fromJson(response).array();
            probot->gitList.clear();

            for(int i=0; i<git_array.size(); i++){
                ST_GIT temp_git;
                QString temdate = git_array[i].toObject()["commit"].toObject()["author"].toObject()["date"].toString();
                temp_git.date = QDateTime::fromString(temdate,"yyyy-MM-ddThh:mm:ssZ").addSecs(3600*9).toString("yyyy-MM-dd hh:mm");

                temp_git.commit = git_array[i].toObject()["sha"].toString();
                temp_git.message = git_array[i].toObject()["commit"].toObject()["message"].toString();
                probot->gitList.push_back(temp_git);
            }

            for(int i=0; i<probot->gitList.size(); i++){
                if(i==0){
                    plog->write("[SERVER] GET GIT RECENT COMMIT : "+probot->gitList[i].commit+", "+probot->gitList[i].date+", "+probot->gitList[i].message);
                }else{
                    qDebug() << probot->gitList[i].commit << probot->gitList[i].date << probot->gitList[i].message;
                }
            }

            if(probot->gitList.size() > 0){
                if(probot->gitList[0].date == probot->program_date){
                    new_update_local = false;
                    plog->write("[SERVER] PROGRAM ALREADY UPDATED "+probot->gitList[0].date);
                }else{
                    new_update_local = true;
                    plog->write("[SERVER] PROGRAM NEED UPDATE "+probot->program_date);
                }
            }
        }else if(url.contains(":11334")){
        }else if(url.contains(":11335")){
            QByteArray response = reply->readAll();

            if(url.contains("/versions/MAIN_MOBILE")){
                QJsonObject temp = QJsonDocument::fromJson(response).object();
                ui_version_new.version = temp["version"].toString();
                ui_version_new.date = temp["date"].toString();
                ui_version_new.message = temp["message"].toString();
                qDebug() << "version (new) get " << ui_version.version << ui_version.date;
            }else if(url.contains("/versions/all/MAIN_MOBILE")){
                QJsonArray temp = QJsonDocument::fromJson(response).array();
                ui_new_versions.clear();
                for(int i=0; i<temp.size(); i++){
                    ST_VERSION temp_version;
                    temp_version.version = temp[i].toObject()["version"].toString();
                    temp_version.date = temp[i].toObject()["date"].toString();
                    temp_version.message = temp[i].toObject()["message"].toString();
                    ui_new_versions.append(temp_version);
                }
            }
        }else if(type == "GOQUAL"){
            QByteArray response = reply->readAll();

            if(url.contains("/token")){
                QJsonObject json = QJsonDocument::fromJson(response).object();
                qDebug() << "REPLY===============================";
                qDebug() << "goqual response : " << json;
                goqual_token.access_key = json["access_token"].toString();
                goqual_token.refresh_key = json["refresh_token"].toString();
                goqual_token.expires_in = json["expires_in"].toInt();

                setSetting("setting","GOQUAL/access_key",goqual_token.access_key);
                setSetting("setting","GOQUAL/refresh_key",goqual_token.refresh_key);
                setSetting("setting","GOQUAL/expires_in",QString::number(goqual_token.expires_in));

            }else if(url.contains("/devices/state")){
                QJsonArray json = QJsonDocument::fromJson(response).array();
                goqual_relays.clear();
                for(int i=0; i<json.size(); i++){
                    QJsonObject device = json[i].toObject();
                    if(device["deviceType"].toString().contains("RelayController")){
                        ST_GOQUAL_RELAY temp;
                        temp.id = device["id"].toString();
                        temp.type = device["deviceType"].toString();
                        temp.state = device["deviceState"].toObject()["power1"].toBool();
                        goqual_relays.append(temp);
                    }

                }
            }
        }else{
            first_response = true;
            QString cmd = url.remove(0,23);
            QByteArray response = reply->readAll();
            if(type == "POST"){
                if(cmd == "/setting/getname"){
                    if(response.contains("status")){

                    }else{
                        ClearJson(json_in);
                        json_in = QJsonDocument::fromJson(response).object();
                        myID = json_in["id"].toString();
                        if(myID != "" || getSetting("robot","SERVER","my_id") != ""){
                            plog->write("[SERVER] Get New Name : "+myID);
                            setSetting("robot","SERVER/my_id",myID);
                        }
                    }
                }else if(cmd == "/setstatus"){
                    if(response == ""){
                        if(connection){
                            plog->write("[SERVER] Post Status : Failed");
                            connection = false;
                        }
                    }
                    ClearJson(json_in);
                    json_in = QJsonDocument::fromJson(response).object();
                    if(json_in["id"].toString() == myID){
                        TIMER_MS = json_in["activate_level"].toString().toInt();

                        if(json_in["server_group"].toString() != ""){
                            if(getSetting("robot","SERVER","group") != json_in["server_group"].toString()){
                                setSetting("robot","SERVER/group",json_in["server_group"].toString());
                            }
                        }

                        if(json_in["server_name"].toString() != ""){
                            if(getSetting("robot","SERVER","name") != json_in["server_name"].toString()){
                                setSetting("robot","SERVER/name",json_in["server_name"].toString());
                            }
                        }
                //        qDebug() << "timer ms = " << TIMER_MS << json_in["activate_level"].toString() << json_in["activate_level"].toString().toInt();
                        timer->start(TIMER_MS);
                    }

                }else if(cmd == "/upload/config/"+myID){
                    plog->write("[SERVER] Upload Config : Done");
                }else if(cmd == "/upload/map/"+myID){
                    plog->write("[SERVER] Upload Map : Done");
                }
            }else if(type == "GET"){
                if(cmd == "/update/mylist/"+myID){
                    //checkUpdate()
                    update_list.clear();
                    QJsonObject temp = QJsonDocument::fromJson(response).object();
                    if(temp.size() > 0){
                        if(temp["id"].toString() == myID){
                            if(temp["update"].toString() == "true"){
                                QString keys = temp["keys"].toString();
                                QStringList keyss = keys.split(",");
                                last_update_date = temp["date"].toString();
                                for(QString key : keyss){
                                    ST_UPDATE t;
                                    t.commit = temp[key+"_commit"].toString();
                                    t.message = temp[key+"_message"].toString();
                                    t.extension = temp[key+"_extension"].toString();
                                    update_list[key] = t;
                                    plog->write("[SERVER] Update Check : Need Update "+key+" ("+t.message+")");
                                }
                            }else{
                                plog->write("[SERVER] Update Check : No Update");
                            }

                        }else{
                            new_update  = false;
                        }
                    }else{
                        new_update  = false;
                    }


                }else if(cmd == "/update/"+myID){
                    plog->write("[SERVER] Update : Get File ...");
                    if(response.contains("Internal Server Error")){
                        plog->write("[SERVER] Update : internal server error");
                        emit updatefail();
                    }else if(response.contains("Not Found")){
                        plog->write("[SERVER] Update : 404 Not Found error");
                        emit updatefail();
                    }else if(response.size() > 0){
                        QString path(QDir::homePath() + "/RB_MOBILE/temp");
                        QDir dir;
                        if(!dir.exists(path))
                            dir.mkpath(path);

                        QDir dir_folder(path+"/update");
                        dir_folder.removeRecursively();

                        QFile newFile(path+"/update.zip");
                        newFile.open(QIODevice::WriteOnly);
                        newFile.write(response);
                        newFile.close();
                        plog->write("[SERVER] Update : Download Done " + QString::number(response.size()));
                        emit updatesuccess();
                    }else{
                        plog->write("[SERVER] Update : Download Done but size 0");
                        emit updatefail();
                    }
                }
            }
        }
    }else{
        QString err = reply->errorString();
        qDebug() << "ERROR==========================" << err;
        if(err == "Socket operation timed out"){
            if(connection){
                plog->write("[Server] Time out : disconnected");
                connection = false;
            }
        }
    }
    delete reply;
}

void ServerHandler::rename_all(){
    QStringList keys = update_list.keys();
    QString dir = QDir::homePath()+"/RB_MOBILE/temp/update/";
    for(QString key : keys){
        if(update_list[key].file_exist){
            if(QFile::rename(dir+update_list[key].commit+update_list[key].extension, dir+key+update_list[key].extension)){
                plog->write("[UPDATE] Temp file rename : "+update_list[key].commit+update_list[key].extension+" -> "+key+update_list[key].extension);
            }else{
                plog->write("[UPDATE] Temp file rename Fail : "+update_list[key].commit+update_list[key].extension+" -> "+key+update_list[key].extension);
            }
        }else{
            if(QFile::remove(dir+update_list[key].commit+update_list[key].extension)){
                plog->write("[UPDATE] Temp file remove : " +update_list[key].commit+update_list[key].extension);
            }
        }
    }
    if(QFile::remove(dir+"update.json")){
        plog->write("[UPDATE] Update.json remove");
    }
}

void ServerHandler::generalGet(QString url){
   QUrl serviceURL(url);
   QNetworkRequest request(serviceURL);
   request.setRawHeader("Content-Type","application./json");

   QNetworkReply *reply = manager->get(request);
   connect(reply, &QNetworkReply::finished, [=](){
       parsingReply("GET",url,reply);
   });
}
void ServerHandler::generalPut(QString url, QByteArray put_data){
//    QUrl serviceURL(url);
//    QNetworkRequest request(serviceURL);

//    QNetworkReply *reply = manager->put(request, put_data);
//    connect(reply, &QNetworkReply::finished, [=](){
//        parsingReply("PUT",url,reply);
//    });
}

void ServerHandler::generalDelete(QString url){
//    QUrl serviceURL(url);
//    QNetworkRequest request(serviceURL);

//    QNetworkReply *reply = manager->deleteResource(request);
//    connect(reply, &QNetworkReply::finished, [=](){
//        parsingReply("DELETE",url,reply);
//    });
}

void ServerHandler::ClearJson(QJsonObject &json){
    QStringList keys = json.keys();
    for(int i=0; i<keys.size(); i++){
        json.remove(keys[i]);
    }
}
