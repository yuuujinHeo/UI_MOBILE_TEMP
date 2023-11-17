#ifndef MAPEDITOR_H
#define MAPEDITOR_H

#include <QObject>
#include <QTimer>
#include <QThread>
#include <QQuickWindow>

class MapEditor : public QObject
{
    Q_OBJECT
public:
    explicit MapEditor(QObject *parent = nullptr);
    void setWindow(QQuickWindow *Window);
};

#endif // MAPEDITOR_H
