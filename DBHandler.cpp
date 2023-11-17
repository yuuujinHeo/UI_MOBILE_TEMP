#include "DBHandler.h"
#include <QDebug>

DBHandler::DBHandler()
{
    db = QSqlDatabase::addDatabase("QSQLITE", "DB_MAP");
    db.setDatabaseName(DB_NAME);

    LoadDataBase();
}

DBHandler::~DBHandler(){

}

void DBHandler::editDataBase(QString name, QString value){
    if(!db.open()){
        plog->write("[DB]Load DB Fail : ",db.isValid());
        return;
    }

    QSqlQuery query(db);
    QString update_str = "UPDATE Table_Base SET value = \""+value+"\" WHERE name = \""+name+"\"";
    query.exec(update_str);
    qDebug() << update_str;

    plog->write("[DB]Update DB Table_Base : "+name+" -> "+value);

    LoadDataBase();
}
void DBHandler::LoadDataBase(){
    DBbase.clear();
    if(!db.open()){
        plog->write("[DB]Load DB Fail : ",db.isValid());
        return;
    }

    QSqlQuery query(db);
    if(query.exec("SELECT * FROM Table_Base")){
        while(query.next()){
            DBbase[query.value("name").toString()] = query.value("value").toString();
            plog->write("[DB]Load DB Table_Base : "+query.value("name").toString()+" -> "+query.value("value").toString());
        }
    }else{
        plog->write("[DB]Can't select DB Table_Base -> tables size : ",db.tables().size());
    }
    db.close();
}
