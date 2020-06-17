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
    void startPlanning(QJsonValue plan);

signals:
    void gotResult(QJsonValue result);
    void finishedPlanning(QJsonValue result);
    void setProgress(int progress);

private Q_SLOTS:
    void onConnected();
    void onTextMessageReceived(QString message);
    void requestProgress();
};

#endif // CLIENT_H
