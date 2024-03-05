#ifndef TTSHANDLER_H
#define TTSHANDLER_H

#include <QObject>
#include <QtNetwork>
#include <QTimer>
#include <QDebug>
#include <QGuiApplication>
// json -----------------------
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>
#include "GlobalHeader.h"
#include <websocket/QtHttpServer.h>
#include <websocket/QtHttpRequest.h>
#include <websocket/QtHttpReply.h>
#include <QApplication>
#include <websocket/QtHttpHeader.h>
#include "python_wrapper.h"

typedef struct{
    //ko, en, zh-CN, ja, es, ru, de,
    QString language = "ko";
    QString mode = "none";
    /*
     *
     * 음성
     * 일본어 : dmio (미오-어린이) ntomoko 토모코(여성) dayumu 남성(아유무-어린이) shinji 신지(남성-청년)
     * 중국어 : meimei 메이메이(여성) liangliang 량량(남성)
     * 스페인어 : carmen 카르멘(여성) jose 호세(남성)
     * 영어 : djoey 조이(여성-어린이) matt 매트(남성) danna 안나(여성)
     * 한국어 : vdain 다인(여성-어린이) nhajun 하준(남성-어린이) vara 아라(여성) njooahn 주안(남성)
     * nkyungtae 경태(할아버지-구수) nsunhee 선희(할머니) nsangdo 상도(남성-사투리느낌) nsabina 마녀사비나, nmammon 악마마몬
     *
     */
    QString voice = "";
    QString file_path = "";
    QString file = "";
    QString mention = "";

    int volume = -1;

    //-5(0.5배) ~ +5(2배) (기본0)
    int speed = 0;
    //-5(0.8배) ~ +5(1.2배) (기본0)
    int pitch = 0;
    //0중립(기본) 1슬픔 2기쁨 3분노
    int emotion = 0;
    //0:약한감정 1:보통감정(기본) 2:강한감정
    int emotion_strength = 1;
    //-5(낮은음색) ~ +5(높은음색) (기본0)
    int alpha = 0;
    //-5(끝을내림) ~ +5(끝을올림) (기본0 - speaker가 'd'로 시작하는 경우에만 적용됨)
    int end_pitch = 0;
}ST_VOICE;

class TTSHandler : public QObject
{
    Q_OBJECT
public:
    TTSHandler();
    void readVoiceSetting();
    void setVoice(QString name, QString lan);
    void setVoiceDetail(int speed, int pitch, int alpha, int emotion, int emotion_strength);
    void makeTTS(ST_VOICE voice, bool play=false);
    void generalReply(ST_VOICE voice, bool play, QNetworkReply *reply);

    QString getMentionStr(QString text);
    void setMentionStr(QString text, QString mention);
    void setMentionBasic(QString lan);
    QString getMentionBasicStr(QString lan, QString text);

    QString getVoiceName(int language, int voice);
    QString getVoiceLanguage(int language);
    void playcurVoice();

    ST_VOICE curVoice;

signals:
    void ready_play(ST_VOICE voice);

private:
    QString clientID = "qviycrtjox";
    QString clientSecret = "fspHYa21cJgB0zkjrKFadLf02aJ84mGHlOdMQw4a";
    QString url = "https://naveropenapi.apigw.ntruss.com/tts-premium/v1/tts";
    QNetworkAccessManager   *manager;
};

//curl -i -X POST \
//-H "Content-Type:application/x-www-form-urlencoded" \
//-H "X-NCP-APIGW-API-KEY-ID:qviycrtjox"  \
//-H "X-NCP-APIGW-API-KEY:fspHYa21cJgB0zkjrKFadLf02aJ84mGHlOdMQw4a" \
//-d 'speaker=vdain&text=hello test&volume=1&speed=1&pitch=0' \
//'https://naveropenapi.apigw.ntruss.com/tts-premium/v1/tts'


#endif // TTSHANDLER_H
