#ifndef SCHEDULERCLIENT_H
#define SCHEDULERCLIENT_H

#include <QObject>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonDocument>
#include <QWebSocket>
#include <QString>
#include <QTimer>
#include <QCoreApplication>
#include <QEventLoop>

class SchedulerClient : public QObject
{
    Q_OBJECT

    QUrl url;
    QWebSocket webSocket;
    QTimer timer;
    bool started;

public:
    //TODO pass socket in constructor
    explicit SchedulerClient(const QUrl &url, QObject *parent = nullptr);
    void open();
    void startScheduling(QJsonObject plan);

signals:
    void finishedScheduling(QJsonValue result);
    void progressChanged(double progress);
    void socketError();

private Q_SLOTS:
    void onError(QAbstractSocket::SocketError onError);
    void onConnected();
    void onTextMessageReceived(QString message);
    void requestProgress();
signals:

};

#endif // SCHEDULERCLIENT_H
