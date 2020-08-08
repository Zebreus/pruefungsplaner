#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H

#include <QObject>
#include <security-provider/client.h>

/*
 * The ConnectionManager should handle login and create a authorized connection to the server
*/
class ConnectionManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString username READ getUsername WRITE setUsername NOTIFY usernameChanged)

public:
    explicit ConnectionManager(const QUrl& securityProviderUrl, QObject *parent = nullptr);

    QString getUsername() const;

signals:
    void loginSuccess();
    void loginError(const QString& message);
    void usernameChanged(QString username);

public slots:
    void login(QString username, QString password);
    void setUsername(QString username);

private slots:
    void gotToken(QString token);
    void providerError(securityprovider::Client::Error error);

private:
    QString token;
    QUrl securityProviderUrl;
    securityprovider::Client client;
    QString m_username;
};

#endif // CONNECTIONMANAGER_H
