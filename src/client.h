#ifndef CLIENT_H
#define CLIENT_H

#include <QString>
#include <QObject>
#include <QWebSocket>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QTimer>

class Client : public QObject
{
    Q_OBJECT

    QUrl url;
    QWebSocket webSocket;
    QTimer timer;
    bool planning;

public:
    explicit Client(const QUrl &url, QObject *parent = nullptr);
    void updatePlan();
    void save(QJsonValue semesters);
    void startPlanning(QJsonValue plan);

    void login(const QString &token);
    void open();
signals:
    void gotResult(QJsonValue result);
    void finishedPlanning(QJsonValue result);
    void setProgress(int progress);
    void socketError();
    void loginFailed();
    void loginSuccess();

private Q_SLOTS:
    void onError(QAbstractSocket::SocketError onError);
    void onConnected();
    void onTextMessageReceived(QString message);
    void requestProgress();
};

#endif // CLIENT_H
