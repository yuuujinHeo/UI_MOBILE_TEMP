#ifndef DBHANDLER_H
#define DBHANDLER_H

#include <QObject>
#include <QTimer>
#include <QMap>
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include "GlobalHeader.h"
#define DB_NAME "db/map"

class DBHandler : public QObject
{
    Q_OBJECT
public:
    DBHandler();
    ~DBHandler();

    void LoadDataBase();

    void editDataBase(QString name, QString value);

    QMap<QString,QString> DBbase;
private:
    QTimer          timer;
    QSqlDatabase    db;
};

#endif // DBHANDLER_H
