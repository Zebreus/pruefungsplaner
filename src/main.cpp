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

    QTranslator translator;
    translator.load(QLocale(), QLatin1String("planner"), QLatin1String("_"), QLatin1String(":/translations"));
    app.installTranslator(&translator);

    ConnectionManager* connectionManagerInstance = new ConnectionManager(QUrl("ws://localhost:9092"), QUrl("ws://localhost:9093"));
    PruefungsplanerManager* planerInstance = PruefungsplanerManager::getInstance();
    qmlRegisterSingletonInstance<ConnectionManager>("org.pruefungsplaner.ConnectionManager", 1, 0, "ConnectionManager", connectionManagerInstance);
    qmlRegisterSingletonInstance<PruefungsplanerManager>("org.pruefungsplaner.Backend", 1, 0, "Backend", planerInstance);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
    engine.load(url);
    return app.exec();

}
