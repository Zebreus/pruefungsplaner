#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <cpptoml.h>
#include <QCommandLineOption>
#include <QCommandLineParser>
#include <QFile>
#include <QObject>
#include <QString>
#include <array>
#include <string>
#include <QSharedPointer>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <iostream>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#ifndef DEFAULT_CONFIG_PATH
#define DEFAULT_CONFIG_PATH "/etc/pruefungsplaner-frontend"
#endif

class Configuration : public QObject {
    Q_OBJECT
private:
    static constexpr std::array defaultConfigurationFiles{
        DEFAULT_CONFIG_PATH "/config.toml", "config.toml", "/dev/null"};
    static constexpr auto defaultAuthUrl = "ws://127.0.0.1:9092";
    static constexpr auto defaultBackendUrl = "ws://127.0.0.1:9093";
    static constexpr auto defaultSchedulerUrl = "ws://127.0.0.1:9094";
    QUrl authUrl;
    QUrl backendUrl;
    QUrl schedulerUrl;

    // These are only used internally
    QScopedPointer<bool> check;
    QScopedPointer<bool> retrieve;
    QList<QString> filePaths;
    QNetworkAccessManager networkAccessManager;

public:
    explicit Configuration(QObject* parent = nullptr);
    void initialize(const QList<QString>& args);
    QUrl getAuthUrl() const;
    QUrl getBackendUrl() const;
    QUrl getSchedulerUrl() const;

signals:
    void ready();

private:
    void loadConfiguration(const QString& configurationFileContent);
    void retrieveSettings(const QString& authServerUrl);
    void checkConfiguration();
    [[noreturn]] void failConfiguration(const QString& message) const;
    void warnConfiguration(const QString& message) const;
    void selectConfigurationFile(const QString& preferredFile);
    void openNextFile();
private slots:
    void loadedFile(const QString& content);

signals:
};

#endif  // CONFIGURATION_H
