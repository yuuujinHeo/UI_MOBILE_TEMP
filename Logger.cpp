#include "Logger.h"
#include <iostream>
#include <QDir>
#include <QDebug>

using namespace std;

// Logger Logger::instance;

Logger::Logger()
{
    filename = getFileName();
    file = new QFile;
    file->setFileName(filename);

    if(file->open(QIODevice::Append | QIODevice::Text)){
        write("[LOGGER] file opened");
    }else{

    }
    prev_str = "";
}

void Logger::reset(){
    QString path = QDir::homePath()+"/RB_MOBILE/log/ui_log";
    QDir directory(path);
    if(!directory.exists()){
        directory.mkpath(".");
        qDebug() << "[LOGGER] ui_log directory not found. make new";
    }
    filename = getFileName();
    file->deleteLater();
    file = new QFile;
    file->setFileName(filename);
    if(file->open(QIODevice::Append | QIODevice::Text)){
        write("[LOGGER] file opened");
    }else{

    }
    prev_str = "";
}
void Logger::write(const QString str, bool print){
    QString text = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss") + " " + str + "\n";
    QString text1 = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss") + " " + str;

    QString tempname = getFileName();
    if(tempname != filename){
        // date changed
        if(file->isOpen()){
            file->close();
            delete file;
        }
        filename = tempname;
        file->deleteLater();
        file = new QFile;
        file->setFileName(filename);
        file->open(QIODevice::Append | QIODevice::Text);
        write("[LOGGER] file re-opened");
    }

    if(print == true){
        std::cout << text1.toStdString() << std::endl;
    }

    QTextStream out(file);
    out.setCodec("UTF-8");

    if(file != nullptr){
        out << text;
    }
}

QString Logger::getFileName(){
    QString tempname = QDir::homePath()+"/RB_MOBILE/log/ui_log"+QDateTime::currentDateTime().toString("/yyyy_MM_dd") + ".txt";
    return tempname;
}
