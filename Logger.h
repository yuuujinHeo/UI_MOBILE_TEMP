#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QDateTime>

class Logger : QObject
{
    Q_OBJECT

    static Logger instance;

public:
    Logger();

    void write(const QString str, bool print=true);
    static void write_space();

private:
    QFile *file;
    QString prev_str;

    QString filename;

    QString getFileName();
};

#endif // LOGGER_H
