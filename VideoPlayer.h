#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QObject>
#include <QDebug>
#include <QAbstractVideoSurface>
#include <QVideoSurfaceFormat>
#include <QVideoFrame>
#include <QMap>
#include "opencv2/opencv.hpp"

class QAbstractVideoSurface;
class BackendThread;

class VideoPlayer : public QObject
{
private:
    Q_OBJECT
    Q_PROPERTY(QAbstractVideoSurface *videoSurface READ videoSurface WRITE setVideoSurface NOTIFY surfaceChanged)

public:
    Q_INVOKABLE void play();
    Q_INVOKABLE void pause();
    Q_INVOKABLE void stop();

public:
    explicit VideoPlayer(QObject *parent = nullptr);
    ~VideoPlayer() {};
    QAbstractVideoSurface *videoSurface() const;


public slots:
    void setVideoSurface(QAbstractVideoSurface *surface);
    void onVideoFrameReady(cv::Mat curr_frame);

signals:
    void surfaceChanged(QAbstractVideoSurface* surface);

private:
    void setFormat(int width, int height, QVideoFrame::PixelFormat frame_format);

    QThread *thread;
    QAbstractVideoSurface *m_surface = NULL;
    QVideoSurfaceFormat m_format;
    BackendThread *m_backend;

    bool m_isFormatSet;
    QImage m_image;
    int count = 0;
};


class BackendThread : public QObject
{
    private:
        Q_OBJECT

    public:
        explicit BackendThread(QObject *parent = nullptr);
        ~BackendThread() {};

    public slots:
        void opencvStart();
        void opencvStop();

        void finished(QString thread_name);

    signals:
        void uiUnlock();
        void frameReady(cv::Mat frame);

    private:
        QMap<QString, QThread*> threads;
        // QVariantMap == QMap<QString, QVariant>
        QMap<QString, QVariant> workers;
};

#endif // VIDEOPLAYER_H
