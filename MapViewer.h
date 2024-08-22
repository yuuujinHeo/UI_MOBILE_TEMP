#ifndef MAPVIEWER_H
#define MAPVIEWER_H

#include <QTimer>
#include <QObject>
#include <QSettings>
#include "MapHeader.h"
#include "GlobalHeader.h"

class MapViewer : public QQuickPaintedItem
{
    Q_OBJECT
public:
    MapViewer(QQuickItem *parent = nullptr);
    Q_INVOKABLE void setActive(bool onoff)
    {
        if(onoff)
        {
            plog->write("[MapView] "+object_name+" active : true");
        }
        else
        {
            plog->write("[MapView] "+object_name+" active : false");
        }
        active = onoff;
    }
    Q_INVOKABLE void setName(QString name)
    {
        object_name = name;
        plog->write("[MapView] setMapview : "+object_name);
    }
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
