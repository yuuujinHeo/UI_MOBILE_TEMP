#ifndef ZIPHANDLER_H
#define ZIPHANDLER_H

#include "GlobalHeader.h"
#include "zlib.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <fcntl.h>
#include <QObject>
#include "quazip/quazip.h"
#include "quazip/JlCompress.h"
//#include

#define CHUNK 16384
class ZIPHandler : public QObject
{
    Q_OBJECT
public:
    ZIPHandler();
    void unZipandRead(QString path);
    QStringList showentry(){return filelist;}

    void makeMapZip(QString path, QString mapname);

    void makeZip(QString path, bool _ui, bool _slam, bool _config, bool _map, bool _log);
    void getZip(QString path);
    void testzip(QString dst, QStringList sources);
    JlCompress zipper;
    QStringList filelist;
    int process = 0;
    QStringList errorlist;
signals:
    void zip_done();
    void unzip_done();
    void zip_fail();
    void unzip_fail();
};

#endif // ZIPHANDLER_H
