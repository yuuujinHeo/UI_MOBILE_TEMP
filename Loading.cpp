#include "Loading.h"

Loading::Loading()
{
    thread = new workerThread();
}

workerThread::workerThread(QObject *parent):
    QThread(parent)
{

}

void workerThread::run(){
    while(1){
//        num++;
//        qDebug() << num;
    }
}
