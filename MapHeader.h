#ifndef MAPHEADER_H
#define MAPHEADER_H

#include <QPainter>
#include <QObject>
#include <QPixmap>
#include <QQuickPaintedItem>
#include <opencv2/opencv.hpp>
#include "cv_to_qt.h"
#include <QQmlEngine>
#include <QQuickWindow>

#define color_black2    cv::Scalar(0,0,0,100)
#define color_white     cv::Scalar(255,255,255,255)
#define color_black     cv::Scalar(0,0,0,255)
#define color_green     cv::Scalar(18,210,124,255)
#define color_red       cv::Scalar(77,88,231,255)
#define color_navy      cv::Scalar(79,86,102,255)
#define color_gray      cv::Scalar(127,127,127,255)
#define color_blue      cv::Scalar(131,184,249,255)
#define color_pink      cv::Scalar(255,217,255,255)
#define color_yellow    cv::Scalar(80,200,255,255)

#define hex_color_green     "#12d27c"
#define hex_color_red       "#e7584d"
#define hex_color_navy      "#4f5666"
#define hex_color_gray      "#d8d8d8"
#define hex_color_blue      "#83B8F9"
#define hex_color_pink      "#FFD9FF"
#define hex_color_yellow    "#ffc850"

typedef struct{
    cv::Point2f point;
    float angle;
}POSE;

typedef struct{
    QVector<cv::Point2f> points;
    int color;
    int width;
    int type=0;
}LINE;

typedef struct{
    QString type;
    bool is_rect;
    QVector<cv::Point2f> points;
}OBJECT;

typedef struct{
    int group;
    QString type;
    QString name;
    cv::Point2f point;
    float angle;
    QString call_id;
    bool available;
}LOCATION;


class PixmapContainer : public QObject
{
    Q_OBJECT
public:
    explicit PixmapContainer(QObject *parent = 0);
    QPixmap pixmap;
};

#endif // MAPHEADER_H
