#include "CameraView.h"


CameraView::CameraView(QQuickItem *parent):
    QQuickPaintedItem(parent)
{
}

void CameraView::setCamera(int num){
    m_pixmapContainer.pixmap = pmap->camera_info[num].pixmap;
    update();
}

void CameraView::paint(QPainter *painter){
//    qDebug() << width() << height();
    painter->drawPixmap(0,0,width(),height(),m_pixmapContainer.pixmap);
}
