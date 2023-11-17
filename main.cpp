#include <QGuiApplication>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <QQmlContext>
#include "CameraView.h"
#include "Supervisor.h"
#include "MapViewer.h"
#include "Keyemitter.h"
#include "Logger.h"

Logger *plog;
QObject *object;
QApplication *app;//(argc, argv);

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    qmlRegisterType<Supervisor>("io.qt.Supervisor",1,0, "Supervisor");
    qmlRegisterType<CameraView>("io.qt.CameraView",1,0, "CameraView");
    qmlRegisterType<KeyEmitter>("io.qt.Keyemitter",1,0, "Keyemitter");
    qmlRegisterType<MapViewer>("io.qt.MapViewer",1,0, "MapViewer");

    app = new QApplication(argc,argv);
    app->setOrganizationName("Mobile");
    app->setOrganizationDomain("Mobile");

//    QTranslator *translator = new QTranslator();
//    QString pahhh = QApplication::applicationDirPath() + "/lang_en.qm";
//    qDebug() << pahhh << translator->load(pahhh);
//    app->installTranslator(translator);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("applicationDirPath", QGuiApplication::applicationDirPath());
    engine.rootContext()->setContextProperty("homePath", QDir::homePath());

    QList<QString> path_home_str = QDir::homePath().split("/");
    if(path_home_str[path_home_str.size()-1] == "odroid")
        QGuiApplication::setOverrideCursor(QCursor(Qt::BlankCursor));
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    object = engine.rootObjects()[0];
    return app->exec();
}
