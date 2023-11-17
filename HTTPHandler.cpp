#include "HTTPHandler.h"
#include <iostream>
#include <QDataStream>

#define TIMER_MS    250


using namespace std;
HTTPHandler::HTTPHandler()
{
    // 네트워크 연결 관리
    manager = new QNetworkAccessManager(this);
//    connect(manager, SIGNAL(finished(QNetworkReply*)), &connection_loop, SLOT(quit()));
//    connection_timer = new QTimer();
//    connect(connection_timer, SIGNAL(timeout()),&connection_loop,SLOT(quit()));

}

// 공통적으로 사용되는 POST 구문 : 출력으로 응답 정보를 보냄
void HTTPHandler::generalPost(QByteArray post_data, QString url){
    QByteArray postDataSize = QByteArray::number(post_data.size());
    QUrl serviceURL(url);
    QNetworkRequest request(serviceURL);
//    qDebug() << serviceURL;
    request.setRawHeader("Content-Type", "application/x-www-form-urlencoded");
    request.setRawHeader("Content-Length", postDataSize);
    request.setRawHeader("Connection", "Keep-Alive");
    request.setRawHeader("AcceptEncoding", "gzip, deflate");
    request.setRawHeader("AcceptLanguage", "ko-KR,en,*");

    QNetworkReply *reply = manager->post(request, post_data);
    connection_timer->start(1000);
    connection_loop.exec();

    reply->waitForReadyRead(200);
    QByteArray ret = reply->readAll();
    reply->deleteLater();
    return ret;
}

void HTTPHandler::generalGet(QString url){
    QUrl serviceURL(url);
    QNetworkRequest request(serviceURL);

    QNetworkReply *reply = manager->get(request);
}


void HTTPHandler::updateGitArray(){
    //Server에서 Git commits 받아와서 gitList에 채움

    QString server = GIT_REPO_COMMIT;
    QByteArray ret = generalGet(server);

    json_in = QJsonDocument::fromJson(ret);
    QJsonArray git_array = json_in.array();

    probot->gitList.clear();

    for(int i=0; i<git_array.size(); i++){

        ST_GIT temp_git;
        temp_git.date = git_array[i].toObject()["commit"].toObject()["author"].toObject()["date"].toString();
        temp_git.commit = git_array[i].toObject()["sha"].toString();
        temp_git.message = git_array[i].toObject()["commit"].toObject()["message"].toString();
        probot->gitList.push_back(temp_git);
    }

    for(int i=0; i<probot->gitList.size(); i++){
        qDebug() << probot->gitList[i].commit << probot->gitList[i].date << probot->gitList[i].message;
    }
}

void HTTPHandler::ClearJson(QJsonObject &json){
    QStringList keys = json.keys();
    for(int i=0; i<keys.size(); i++){
        json.remove(keys[i]);
    }
}
