#include "schedulerclient.h"

SchedulerClient::SchedulerClient(const QUrl &url, QObject *parent):
    QObject(parent), url(url), started(false)
{
    connect(&webSocket, &QWebSocket::connected, this, &SchedulerClient::onConnected);
    connect(&timer, SIGNAL(timeout()), this, SLOT(requestProgress()));
    connect(&webSocket, QOverload<QAbstractSocket::SocketError>::of(&QWebSocket::error), this, &SchedulerClient::onError);
}

void SchedulerClient::open()
{
    webSocket.open(QUrl(url));
    while (!webSocket.isValid()) {
      qDebug() << "Waiting for websocket";
      QCoreApplication::processEvents(QEventLoop::AllEvents, 50);
    }
}

void SchedulerClient::startScheduling(QJsonObject plan)
{
    QString message = "{\"jsonrpc\":\"2.0\",\"method\":\"startScheduling\",\"params\":[";
    message.append(QJsonDocument(plan).toJson(QJsonDocument::Compact));
    message.append("],\"id\":\"1\"}");
    webSocket.sendTextMessage(message);
    timer.start(50);
}

void SchedulerClient::onError(QAbstractSocket::SocketError onError)
{
    qDebug() << "scheduler socket error";
    emit socketError();
}

void SchedulerClient::onConnected()
{
    qDebug() << "scheduler socket connected";
    connect(&webSocket, &QWebSocket::textMessageReceived, this, &SchedulerClient::onTextMessageReceived);
    connect(&webSocket, &QWebSocket::binaryMessageReceived, this, &SchedulerClient::onTextMessageReceived);
}

void SchedulerClient::onTextMessageReceived(QString message)
{
    QJsonDocument document = QJsonDocument::fromJson(message.toUtf8());
    QJsonObject response = document.object();
    QJsonValue result = response.value("result");
    int id = response.value("id").toString().toInt();
    qDebug() << id << " got message:" << QJsonDocument(response).toJson(QJsonDocument::Compact);
    switch (id){
    case 1:
        if(result.isBool() && result.toBool() == false){
            //TODO stop request and timer
        }
        break;
    case 3:
        if(result.isString()){
            qDebug() << "Scheduling error: " << result.toString();
        }else if(result.isUndefined()){
            qDebug() << "Scheduling error: Scheduling not finished yet";
        }else if(result.isObject()){
            qDebug() << "Scheduling successful";
            emit finishedScheduling(result);
        }else{
            qDebug() << "Scheduling error: Unexpected result";
        }
        break;
    case 2:
        if(result.isDouble()){
        double progress = result.toDouble();

        if(progress == 1.0){
            timer.stop();
            webSocket.sendTextMessage("{\"jsonrpc\":\"2.0\",\"method\":\"getResult\",\"id\":\"3\"}");
            started = false;
        }
        emit progressChanged(progress);
        }
        break;
    default:
        qDebug() << "Unknown id";
    }
}

void SchedulerClient::requestProgress()
{
    webSocket.sendTextMessage("{\"jsonrpc\":\"2.0\",\"method\":\"getProgress\",\"id\":\"2\"}");
    if(started){
        timer.start(50);
    }
}
