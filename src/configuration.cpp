#include "configuration.h"

Configuration::Configuration(QObject* parent)
    : QObject(parent) {
}

void Configuration::initialize(const QList<QString> &arguments){
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

    selectConfigurationFile(parser.value(configFileOption));
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

void Configuration::selectConfigurationFile(const QString& preferredFile) {
    if(preferredFile != ""){
        filePaths.append(preferredFile);
    }
    for (auto configFilePath : defaultConfigurationFiles) {
        filePaths.append(configFilePath);
    }

    //If using emscripten, then relative paths are also relative http urls
#ifdef __EMSCRIPTEN__
    char* myUrl = (char*)EM_ASM_INT(
                var location = window.location;
            var myUrl = location.origin + location.pathname.substring(0, location.pathname.lastIndexOf('/')+1);
    return allocate(intArrayFromString(myUrl), 'i8', ALLOC_STACK);
    );
    std::clog << "My c++ url is (" << myUrl << ")" << myUrl << '\n';
    QString qUrl(myUrl);


    for(int i = 0;i<filePaths.size();i++){
        if(!filePaths[i].startsWith("/")){
            filePaths.insert(i+1, QString(myUrl) + filePaths[i]);
            ++i;
        }
    }
#endif

    openNextFile();
}

void Configuration::openNextFile(){
    if(filePaths.size() == 0){
        failConfiguration("No valid configuration found");
    }

    QString filePath = filePaths.takeFirst();

    if(filePath.startsWith("http")){
        QUrl fileUrl(filePath);
        QSharedPointer<QNetworkAccessManager> nam(new QNetworkAccessManager());
        QObject::connect(nam.get(), &QNetworkAccessManager::finished, this, [this, nam](QNetworkReply* reply){
            QString data = reply->readAll();
            reply->deleteLater();
            if(data == ""){
                openNextFile();
            }else{
                loadedFile(data);
            }
        });
        nam->get(QNetworkRequest(fileUrl));
    }else{
        QFile configurationFile(filePath);
        if (configurationFile.exists() && configurationFile.open(QIODevice::ReadOnly)) {
            QString data = configurationFile.readAll();
            if(data == ""){
                openNextFile();
            }else{
                loadedFile(data);
            }
        }else{
            openNextFile();
        }
    }
}

void Configuration::loadedFile(const QString &content)
{
    std::clog << "Loading configuration" << '\n';
    loadConfiguration(content);
    std::clog << "Checking configuration" << '\n';
    checkConfiguration();
    std::clog << "Emitting ready" << '\n';
    emit ready();
}

void Configuration::loadConfiguration(const QString& configurationFileContent) {
    try {
        std::clog << "Configuration:" << configurationFileContent.toStdString() << '\n';
        std::istringstream stringStream(configurationFileContent.toStdString());
        auto config = cpptoml::parser{stringStream}.parse();

        // Try to prevent the throwing of exceptions, because emscripten does not support them in the currently used version
        std::string parseAuthUrl = defaultAuthUrl;
        std::string parseBackendUrl = defaultBackendUrl;
        std::string parseSchedulerUrl = defaultSchedulerUrl;

        if(config->contains("auth")){
            auto auth = config->get_table("auth");
            if(auth->is_table() && auth->contains("url") ){
                parseAuthUrl = auth->get_as<std::string>("url").value_or(defaultAuthUrl);
            }
        }

        if(config->contains("backend")){
            auto backend = config->get_table("backend");
            if(backend->is_table() && backend->contains("url") ){
                parseBackendUrl = backend->get_as<std::string>("url").value_or(defaultBackendUrl);
            }
        }
        if(config->contains("scheduler")){
            auto scheduler = config->get_table("scheduler");
            if(scheduler->is_table() && scheduler->contains("url") ){
                parseSchedulerUrl = scheduler->get_as<std::string>("url").value_or(defaultSchedulerUrl);
            }
        }

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
    std::clog << "Configuration error: " << message.toStdString() << '\n';
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
