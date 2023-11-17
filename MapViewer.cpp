#include "MapViewer.h"

PixmapContainer::PixmapContainer(QObject *parent){

}
MapViewer::MapViewer(QQuickItem *parent):
    QQuickPaintedItem(parent)
{
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(onTimer()));
    timer->start(100);
}

void MapViewer::onTimer(){
    if(active){
        update();
    }
}
void MapViewer::paint(QPainter *painter){
    QPixmap temp = pmap->map;
//    temp.scaled(width(),height(),Qt::IgnoreAspectRatio,Qt::FastTransformation);
//    painter->drawPixmap(0,0,width(),height(),temp);
    painter->drawPixmap(0,0,width(),height(),temp.scaled(width(),height(),Qt::IgnoreAspectRatio,Qt::FastTransformation));
}
