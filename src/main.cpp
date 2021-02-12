#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include "pruefungsplanermanager.h"
#include "connectionmanager.h"
#include "configuration.h"
#include <QtCore>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QSharedPointer<Configuration> configuration(new Configuration(app.arguments()));

    std::clog << "Auth url" << configuration->getAuthUrl().toString().toStdString() << '\n';
    std::clog << "Backend url" << configuration->getBackendUrl().toString().toStdString() << '\n';
    std::clog << "Scheduler url" << configuration->getSchedulerUrl().toString().toStdString() << '\n';

    QTranslator translator;
    translator.load(QLocale(), QLatin1String("planner"), QLatin1String("_"), QLatin1String(":/translations"));
    app.installTranslator(&translator);

    ConnectionManager* connectionManagerInstance = new ConnectionManager(configuration->getAuthUrl(), configuration->getBackendUrl());
    PruefungsplanerManager* planerInstance = PruefungsplanerManager::getInstance();
    planerInstance->setConfiguration(configuration);
    qmlRegisterSingletonInstance<ConnectionManager>("org.pruefungsplaner.ConnectionManager", 1, 0, "ConnectionManager", connectionManagerInstance);
    qmlRegisterSingletonInstance<PruefungsplanerManager>("org.pruefungsplaner.Backend", 1, 0, "Backend", planerInstance);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
    engine.load(url);
    return app.exec();

}
