#include "connectionmanager.h"

ConnectionManager::ConnectionManager(const QUrl &securityProviderUrl, QObject *parent):
    QObject(parent), securityProviderUrl(securityProviderUrl)
{
    connect(&client, &securityprovider::Client::gotToken, this, &ConnectionManager::gotToken);
    connect(&client, &securityprovider::Client::error, this, &ConnectionManager::providerError);
    //connect(&client, &securityprovider::Client::onConnected, [](){qDebug() << "connected";});
    client.open(securityProviderUrl);
}

QString ConnectionManager::getUsername() const
{
    return m_username;
}

void ConnectionManager::login(QString username, QString password)
{
    qDebug() << "Login";
    QList<QString> claims{"pruefungsplanerRead", "pruefungsplanerWrite"};
    QString audience = "pruefungsplaner-backend";
    client.getToken(username, password, claims, audience);
}

void ConnectionManager::setUsername(QString username)
{
    if (m_username == username)
        return;

    m_username = username;
    emit usernameChanged(m_username);
}

void ConnectionManager::gotToken(QString token)
{
    //TODO connect to service
    qDebug() << "gotToken";
    emit loginSuccess();
}

void ConnectionManager::providerError(securityprovider::Client::Error error)
{
    QString message;
    switch(error){
        case securityprovider::Client::Error::SOCKET_ERROR:
            message = "Der Authentifizierungsserver ist gerade nicht erreichbar. Versuch es später nochmal.";
        break;
        case securityprovider::Client::Error::SERVER_ERROR:
            message = "Der Authentifizierungsserver hat ein Problem. Am besten schaust du mal nach ihm.";
        break;
        case securityprovider::Client::Error::INVALID_RESPONSE:
            message = "Error: INVALID_RESPONSE";
        break;
        case securityprovider::Client::Error::UNEXPECTED_MESSAGE:
            message = "Der Authentifizierungsserver sendet seltsame Nachrichten. Am besten schaust du mal nach ihm.";
    }
    qDebug() << "Provider Error : " << error;
    emit loginError(message);
}
