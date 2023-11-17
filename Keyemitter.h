#ifndef KEYEMITTER_H
#define KEYEMITTER_H
#include <QObject>
#include <QTimer>
#include <QDebug>
#include <QCoreApplication>
#include <QKeyEvent>
#include "automata.h"
class KeyEmitter : public QObject
{
    Q_OBJECT
public:
    KeyEmitter(QObject* parent=nullptr) : QObject(parent) {}
    Q_INVOKABLE void keyPressed(QObject* tf, Qt::Key k) {
        QKeyEvent keyPressEvent = QKeyEvent(QEvent::Type::KeyPress, k, Qt::NoModifier, QKeySequence(k).toString());
        if(k == Qt::Key_Space){
            keyPressEvent = QKeyEvent(QEvent::Type::KeyPress, k, Qt::NoModifier, " ");
        }
        QCoreApplication::sendEvent(tf, &keyPressEvent);
    }
    Q_INVOKABLE void keyPressed(QObject* tf, QString k) {
        QKeyEvent keyPressEvent = QKeyEvent(QEvent::Type::KeyPress, QKeySequence(k).count(), Qt::NoModifier, k);
        QCoreApplication::sendEvent(tf, &keyPressEvent);
    }
    Q_INVOKABLE void setHangul(QObject* tf, QString k){
        hangul.InputString(k);
        if(hangul.changed == 1){
            QKeyEvent keyPressEvent = QKeyEvent(QEvent::Type::KeyPress, 0x01000003, Qt::NoModifier, QKeySequence(0x01000003).toString());
            QCoreApplication::sendEvent(tf, &keyPressEvent);
        }
        QKeyEvent keyPressEvent = QKeyEvent(QEvent::Type::KeyPress, QKeySequence(hangul.outString).count(), Qt::NoModifier, hangul.outString);
        QCoreApplication::sendEvent(tf, &keyPressEvent);
    }
    Q_INVOKABLE void initHangul(){
        hangul.Reset();
    }

    Automata hangul;

};


#endif // KEYEMITTER_H

