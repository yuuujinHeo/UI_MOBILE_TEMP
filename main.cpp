#include <QGuiApplication>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <QQmlContext>
#include "CameraView.h"
#include "Supervisor.h"
#include "MapViewer.h"
#include "Keyemitter.h"
#include "checker.h"
#include "Logger.h"

Logger *plog;
QObject *object;
QApplication *app;//(argc, argv);

int main(int argc, char *argv[])
{
    bool test_mode = false;
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    qmlRegisterType<Supervisor>("io.qt.Supervisor",1,0, "Supervisor");
    qmlRegisterType<CameraView>("io.qt.CameraView",1,0, "CameraView");
    qmlRegisterType<KeyEmitter>("io.qt.Keyemitter",1,0, "Keyemitter");
    qmlRegisterType<MapViewer>("io.qt.MapViewer",1,0, "MapViewer");

    app = new QApplication(argc,argv);
    app->setOrganizationName("Mobile");
    app->setOrganizationDomain("Mobile");


    QString ini_path = QDir::homePath()+"/RB_MOBILE/config/setting_config.ini";
    QSettings setting_robot(ini_path, QSettings::IniFormat);
    setting_robot.beginGroup("UI");
    if(setting_robot.value("language").toString() == "english"){
        QTranslator *translator = new QTranslator();
        QString pahhh = QApplication::applicationDirPath() + "/lang_eddn.qm";
        app->installTranslator(translator);
    }else{

    }


    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("applicationDirPath", QGuiApplication::applicationDirPath());
    engine.rootContext()->setContextProperty("homePath", QDir::homePath());
    engine.rootContext()->setContextProperty("testMode",test_mode);

    QList<QString> path_home_str = QDir::homePath().split("/");
    if(!test_mode)
        QGuiApplication::setOverrideCursor(QCursor(Qt::BlankCursor));


    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    object = engine.rootObjects()[0];
    return app->exec();
}
