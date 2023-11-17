#ifndef MAPVIEWER_H
#define MAPVIEWER_H

#include <QTimer>
#include <QObject>
#include <QSettings>
#include "MapHeader.h"
#include "spline.h"
#include "GlobalHeader.h"

class MapViewer : public QQuickPaintedItem
{
    Q_OBJECT
public:
    MapViewer(QQuickItem *parent = nullptr);
    Q_INVOKABLE void setActive(bool onoff){
        active = onoff;
    }
    Q_INVOKABLE void setName(QString name){object_name = name;}
    QString object_name ="";

protected:
    virtual void paint(QPainter *painter) Q_DECL_OVERRIDE;

private slots:
    void onTimer();
private:
    QTimer *timer;
    bool active = false;
    PixmapContainer pixmap_map;
};

#endif // MAPVIEWER_H
