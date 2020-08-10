#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include "pruefungsplanermanager.h"
#include "connectionmanager.h"
#include <QtCore>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    //PruefungsplanerBackend::getInstance();

    //qmlRegisterType<PruefungsplanerBackend>("examples.backend", 1, 0, "BackEnd");
    ConnectionManager* connectionManagerInstance = new ConnectionManager(QUrl("ws://localhost:9092"), QUrl("ws://localhost:9093"));
    PruefungsplanerManager* planerInstance = PruefungsplanerManager::getInstance();
    qmlRegisterSingletonInstance<ConnectionManager>("org.pruefungsplaner.ConnectionManager", 1, 0, "ConnectionManager", connectionManagerInstance);
    qmlRegisterSingletonInstance<PruefungsplanerManager>("org.pruefungsplaner.Backend", 1, 0, "Backend", planerInstance);
    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);
    return app.exec();

}
