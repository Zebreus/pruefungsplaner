#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <cpptoml.h>
#include <QCommandLineOption>
#include <QCommandLineParser>
#include <QDir>
#include <QFile>
#include <QHostAddress>
#include <QJsonValue>
#include <QObject>
#include <QString>
#include <QTemporaryDir>
#include <QTextStream>
#include <array>
#include <string>
#include <vector>
#include "plan.h"
#include "plancsvhelper.h"

#ifndef DEFAULT_CONFIG_PATH
#define DEFAULT_CONFIG_PATH "/etc/pruefungsplaner-frontend"
#endif

class Configuration : public QObject {
    Q_OBJECT
private:
    static constexpr std::array defaultConfigurationFiles{
        DEFAULT_CONFIG_PATH "/config.toml", "./config.toml", "/dev/null"};
    static constexpr auto defaultAuthUrl = "ws://127.0.0.1:9092";
    static constexpr auto defaultBackendUrl = "ws://127.0.0.1:9093";
    static constexpr auto defaultSchedulerUrl = "ws://127.0.0.1:9094";
    QUrl authUrl;
    QUrl backendUrl;
    QUrl schedulerUrl;

    // These are only used internally
    QScopedPointer<bool> check;
    QScopedPointer<bool> retrieve;

public:
    explicit Configuration(const QList<QString>& args, QObject* parent = nullptr);
    QUrl getAuthUrl() const;
    QUrl getBackendUrl() const;
    QUrl getSchedulerUrl() const;

private:
    void loadConfiguration(const QString& configurationFileContent);
    void retrieveSettings(const QString& authServerUrl);
    void checkConfiguration();
    [[noreturn]] void failConfiguration(const QString& message) const;
    void warnConfiguration(const QString& message) const;
    // Retrieved the contents of a configurationFile
    // If preferredFile does not exist, other a default configuration file is used
    // If there is no valid configuration file found, this function will NOT
    // return
    QString selectConfigurationFile(const QString& preferredFile);
    // Try to open a configuration file.
    // url can be either a local path or a http(s) url
    // Returns nullptr, if there is no file at url
    QSharedPointer<QString> openFile(const QString& url);

signals:
};

#endif  // CONFIGURATION_H
