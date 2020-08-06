#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include "pruefungsplanermanager.h"
#include <QtCore>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    //PruefungsplanerBackend::getInstance();

    //qmlRegisterType<PruefungsplanerBackend>("examples.backend", 1, 0, "BackEnd");
    qmlRegisterSingletonType<PruefungsplanerManager>("org.pruefungsplaner.Backend", 1, 0, "Backend", &PruefungsplanerManager::getQmlInstance);
    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);
    return app.exec();

}
