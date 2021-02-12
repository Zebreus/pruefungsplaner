#include "configuration.h"

Configuration::Configuration(const QList<QString>& arguments, QObject* parent)
    : QObject(parent) {
    QCommandLineParser parser;
    parser.setApplicationDescription("Pruefungsplaner frontend");
    parser.addHelpOption();
    parser.addVersionOption();

    QCommandLineOption configFileOption(
                "config", "Load configuration from <config>.", "config");
    parser.addOption(configFileOption);

    QCommandLineOption authUrlOption("auth-url",
                                     "The url of the auth server. This should "
                                   "look like \"wss://0.0.0.0:443\".",
                                     "auth-url");
    parser.addOption(authUrlOption);

    QCommandLineOption backendUrlOption("backend-url",
                                        "The url of the backend server. This "
                                      "should look like \"wss://0.0.0.0:443\".",
                                        "backend-url");
    parser.addOption(backendUrlOption);

    QCommandLineOption schedulerUrlOption(
                "scheduler-url",
                "The url of the scheduler server. This should look like "
      "\"wss://0.0.0.0:443\".",
                "scheduler-url");
    parser.addOption(schedulerUrlOption);

    parser.process(arguments);

    authUrl = parser.value(authUrlOption);
    backendUrl = parser.value(backendUrlOption);
    schedulerUrl = parser.value(schedulerUrlOption);

    QString configurationFileContent =
            selectConfigurationFile(parser.value(configFileOption));
    loadConfiguration(configurationFileContent);

    checkConfiguration();
}

QUrl Configuration::getAuthUrl() const {
    return authUrl;
}

QUrl Configuration::getBackendUrl() const {
    return backendUrl;
}

QUrl Configuration::getSchedulerUrl() const {
    return schedulerUrl;
}

QString Configuration::selectConfigurationFile(const QString& preferredFile) {
    if (preferredFile == "") {
        for (auto configFilePath : defaultConfigurationFiles) {
            QSharedPointer<QString> content = openFile(configFilePath);
            if (content != nullptr) {
                return *content;
            }
        }

        QString defaultConfigFilesMessage;
        if (defaultConfigurationFiles.size() > 0) {
            defaultConfigFilesMessage = "create one at ";
            for (uint i = 0; i < defaultConfigurationFiles.size() - 1; i++) {
                defaultConfigFilesMessage += defaultConfigurationFiles[i];
                defaultConfigFilesMessage += ", ";
            }
            defaultConfigFilesMessage +=
                    defaultConfigurationFiles[defaultConfigurationFiles.size() - 1];
            defaultConfigFilesMessage += " or";
        }
        failConfiguration("No valid configuration file found. You can " +
                          defaultConfigFilesMessage +
                          " specify your configuration with the --config option.");
    } else {
        QSharedPointer<QString> content = openFile(preferredFile);
        if (content != nullptr) {
            return *content;
        }
        failConfiguration("Unable to open configuration file " + preferredFile +
                          ".");
    }
}

QSharedPointer<QString> Configuration::openFile(const QString& file) {
    QFile configurationFile(file);
    if (configurationFile.exists()) {
        if (configurationFile.open(QIODevice::ReadOnly)) {
            QString content = configurationFile.readAll();
            return QSharedPointer<QString>::create(content);
        }
    }

    if (file.startsWith("http://") || file.startsWith("https://")) {
        // TODO actually retrieve file
        return QSharedPointer<QString>::create("");
    }

    return nullptr;
}

void Configuration::loadConfiguration(const QString& configurationFileContent) {
    try {
        std::istringstream stringStream(configurationFileContent.toStdString());
        auto config = cpptoml::parser{stringStream}.parse();

        auto parseAuthUrl =
                config->get_table("auth")->get_as<std::string>("url").value_or(
                    defaultAuthUrl);
        auto parseBackendUrl =
                config->get_table("backend")->get_as<std::string>("url").value_or(
                    defaultBackendUrl);
        auto parseSchedulerUrl = config->get_table("scheduler")
                ->get_as<std::string>("url")
                .value_or(defaultSchedulerUrl);

        if (authUrl.isEmpty()) {
            authUrl = QUrl(QString::fromStdString(parseAuthUrl));
        }

        if (backendUrl.isEmpty()) {
            backendUrl = QUrl(QString::fromStdString(parseBackendUrl));
        }

        if (schedulerUrl.isEmpty()) {
            schedulerUrl = QUrl(QString::fromStdString(parseSchedulerUrl));
        }

    } catch (const cpptoml::parse_exception& e) {
        // TODO rewrite whole configuration parsing section
        failConfiguration("Failed to parse configuration file :\n" +
                          QString(e.what()));
    }
}

[[noreturn]] void Configuration::failConfiguration(
        const QString& message) const {
    QTextStream(stderr) << message << Qt::endl;
    exit(1);
}

void Configuration::warnConfiguration(const QString& message) const {
    qDebug() << message;
}

void Configuration::checkConfiguration() {
    if (authUrl.isEmpty()) {
        failConfiguration("No auth URL specified");
    }

    if (backendUrl.isEmpty()) {
        failConfiguration("No backend URL specified");
    }

    if (schedulerUrl.isEmpty()) {
        failConfiguration("No scheduler URL specified");
    }
}
