#include "ZIPHandler.h"

ZIPHandler::ZIPHandler()
{

}

void ZIPHandler::testzip(QString dst, QStringList sources){
    if(zipper.compressFiles(dst,sources)){
        qDebug() << "SUCCESS";
    }else{
        qDebug() << "FAIL";
    }
}

void ZIPHandler::makeMapZip(QString path, QString mapname){
    plog->write("[ZIP] Make Map.zip : "+mapname);
    process = 1;
    errorlist.clear();

    //최종 파일 이름
    QString target = path + "/"+mapname+".zip";
    QString source = QDir::homePath() + "/RB_MOBILE/maps/"+mapname;
    if(zipper.compressDir(target,source,true)){
        plog->write("[ZIP] Compress : "+source);
    }else{
        errorlist.append("maps 압축 실패");
        plog->write("[ZIP] Compress Error : "+source);
    }
    emit zip_done();

}
void ZIPHandler::makeZip(QString path, bool _ui, bool _slam, bool _config, bool _map, bool _log){
    if(_ui || _slam || _config || _map || _log){
        QString log_str = "[ZIP] make Zip :";
        process = 1;
        bool is_clear = true;
        errorlist.clear();

        //최종 파일 이름
        QString outzip = path+"/MobileRobot_Backup_"+QDateTime::currentDateTime().toString("yyyyMMddhhmm");

        //취합 폴더 만들기(추후 삭제할 것)
        QDir directory(outzip);
        if(directory.mkpath(".")){
            plog->write("[ZIP] Make Directory : "+outzip);
        }else{
            is_clear = false;
            errorlist.append("저장 폴더 만들지 못함");
            plog->write("[ZIP] Make Directory Error : "+outzip);
        }

        if(_ui){
            log_str += "UI_release, ";
            QString target = outzip + "/UI_MOBILE_release.zip";
            QString source = QDir::homePath() + "/UI_MOBILE_release";
            if(zipper.compressDir(target,source,true)){
                plog->write("[ZIP] Compress : "+source);
            }else{
                is_clear = false;
                errorlist.append("UI 압축 실패");
                plog->write("[ZIP] Compress Error : "+source);
            }
        }
        if(_slam){
            log_str += "SLAMNAV, ";
            QString target = outzip + "/SLAMNAV.zip";
            QString source = QDir::homePath() + "/code/SLAMNAV";
            if(zipper.compressDir(target,source,true)){
                plog->write("[ZIP] Compress : "+source);
            }else{
                is_clear = false;
                errorlist.append("SLAMNAV 압축 실패");
                plog->write("[ZIP] Compress Error : "+source);
            }
            target = outzip + "/build-SLAMNAV-Desktop-Release.zip";
            source = QDir::homePath() + "/code/build-SLAMNAV-Desktop-Release";
            if(zipper.compressDir(target,source,true)){
                plog->write("[ZIP] Compress : "+source);
            }else{
                is_clear = false;
                errorlist.append("SLAMNAV(Release) 압축 실패");
                plog->write("[ZIP] Compress Error : "+source);
            }
            target = outzip + "/build-SLAMNAV-Desktop-Debug.zip";
            source = QDir::homePath() + "/code/build-SLAMNAV-Desktop-Debug";
            if(zipper.compressDir(target,source,true)){
                plog->write("[ZIP] Compress : "+source);
            }else{
                errorlist.append("SLAMNAV(Debug) 압축 실패");
                plog->write("[ZIP] Compress Error : "+source);
            }

        }
        if(_config){
            log_str += "robot_config, ";
            QString target = outzip + "/config.zip";
            QString source = QDir::homePath() + "/RB_MOBILE/config/robot_config.ini";
            if(zipper.compressFile(target,source)){
                plog->write("[ZIP] Compress : "+source);
            }else{
                is_clear = false;
                errorlist.append("robot_config 압축 실패");
                plog->write("[ZIP] Compress Error : "+source);
            }
        }
        if(_map){
            log_str += "maps, ";
            QString target = outzip + "/maps.zip";
            QString source = QDir::homePath() + "/RB_MOBILE/maps";
            if(zipper.compressDir(target,source,true)){
                plog->write("[ZIP] Compress : "+source);
            }else{
                is_clear = false;
                errorlist.append("maps 압축 실패");
                plog->write("[ZIP] Compress Error : "+source);
            }

        }
        if(_log){
            log_str += "logs, ";
            QString target = outzip + "/ui_log.zip";
            QString source = QDir::homePath() + "/RB_MOBILE/log/ui_log";
            zipper.compressDir(target,source,true);
            target = outzip + "/sn_log.zip";
            source = QDir::homePath() + "/sn_log";
            if(zipper.compressDir(target,source,true)){
                plog->write("[ZIP] Compress : "+source);
            }else{
                is_clear = false;
                errorlist.append("logs 압축 실패");
                plog->write("[ZIP] Compress Error : "+source);
            }
        }

        if(zipper.compressDir(outzip+".zip",outzip,true)){
            if(is_clear){
                process = 2;
                plog->write("[ZIP] Compress Final : "+outzip);
            }else{
                process = 3;
                plog->write("[ZIP] Compress Final (some file missing) : "+outzip);
            }
        }else{
            is_clear = false;
            errorlist.append("최종 압축 실패");
            process = 4;
            plog->write("[ZIP] Compress Final Error : "+outzip);
        }
        plog->write(log_str);
        emit zip_done();

        //만들어진 임시폴더 삭제
        if(directory.removeRecursively()){
            plog->write("[ZIP] Remove directory : "+outzip);
        }else{
            plog->write("[ZIP] Remove directory Error : "+outzip);
        }
    }else{
        process = 4;
        plog->write("[ZIP] make Zip Error : no selected folders");
    }
}

void ZIPHandler::getZip(QString path){
    plog->write("[ZIP] get Zip : "+path);
    process = 1;
    bool is_clear = true;
    errorlist.clear();

    // Remove orin tempBackup Folder
    QDir dirfolder(QDir::homePath() + "/RB_MOBILE/maps");
    dirfolder.removeRecursively();

    // Create tempBackup Folder
    if (!dirfolder.exists()) {
        if (!dirfolder.mkpath(".")) {
            process = 4;
            plog->write("[ZIP] GET ZIP ERROR : TEMPBACKUP FOLDER CREATION FAILED");
            errorlist.append("임시 백업 폴더 생성 실패");
            is_clear = false;
        }
    }

    // Copy File
    std::string user = getenv("USER");
    std::string paths = "/media/" + user;
    QString file = paths.c_str();
    file = file + "/" + path;
    QString file_dst = QDir::homePath()+"/RB_MOBILE/tempBackup.zip";
    QFile file_src(file);
    if(!file_src.exists()){
        process = 4;
        plog->write("[ZIP] GET ZIP ERROR : NO FILE FOUND "+file);
        errorlist.append("복사 실패 : 파일을 찾을 수 없음");
        is_clear = false;
    }else{
        if(file_src.copy(file_dst)){

        }else if(QFile::exists(file_dst)){
            errorlist.append("복사 실패 : 파일이 이미 존재함");
        }else{
            is_clear = false;
            plog->write("[ZIP] GET ZIP ERROR : COPY FAILED "+file_dst);
            errorlist.append("복사 실패 : 그 외 이유");
        }
    }

    // Unzip
    if(is_clear){
        QStringList files = zipper.extractDir(file_dst, QDir::homePath() + "/RB_MOBILE");
        if(files.size() > 0){
            // Unzip middlepath
            foreach(QString ex_file, files){
                qDebug() << ex_file;
                zipper.extractDir(ex_file, ex_file.split(".")[0]);
            }
        }else{
            is_clear = false;
            plog->write("[ZIP] GET ZIP ERROR : EXTRACT FAILED "+QString::number(files.size()));
            errorlist.append("파일 압축해제 실패");
        }
    }

    if(is_clear){
        process = 2;
        plog->write("[ZIP] GET ZIP : SUCCESS");
    }else{
        process = 4;
        plog->write("[ZIP] GET ZIP ERROR");
    }
    qDebug() << errorlist;
}

void ZIPHandler::unZipandRead(QString path){
//    zipper.
}
