#ifndef CAMERAVIEW_H
#define CAMERAVIEW_H

#include <QTimer>
#include <QObject>
#include "MapHeader.h"
#include "GlobalHeader.h"

class CameraView : public QQuickPaintedItem
{
    Q_OBJECT
public:
    CameraView(QQuickItem *parent = Q_NULLPTR);
    Q_INVOKABLE void setCamera(int num);
protected:
    virtual void paint(QPainter *painter) Q_DECL_OVERRIDE;

private:
    PixmapContainer m_pixmapContainer;
};
#endif // CAMERAVIEW_H
