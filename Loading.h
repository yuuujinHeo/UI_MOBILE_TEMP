#ifndef LOADING_H
#define LOADING_H

#include <QThread>
#include <QMovie>
#include <QObject>
#include "GlobalHeader.h"

class workerThread;
class Loading : public QQuickItem
{
    Q_OBJECT
public:
    Loading();
    workerThread *thread;
};

class workerThread : public QThread
{
    Q_OBJECT
public:
    explicit workerThread(QObject *parent=0);
    int num = 0;
private:
    void run();
};
#endif // LOADING_H
