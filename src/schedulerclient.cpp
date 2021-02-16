#include "schedulerclient.h"

float SchedulerClient::getProgress() const
{
    return progress;
}

QSharedPointer<QJsonObject> SchedulerClient::getResult() const
{
    return result;
}

SchedulerClient::SchedulerClient(const QUrl &url, QObject *parent):
    QObject(parent), started(false), finished(false), schedulerUrl(url), progress(0.0)
{
    connect(&schedulerSocket, &QWebSocket::connected, this, &SchedulerClient::onConnected);
    connect(&updateRequestTimer, SIGNAL(timeout()), this, SLOT(onUpdateRequestTimer()));
    connect(&schedulerSocket, QOverload<QAbstractSocket::SocketError>::of(&QWebSocket::error), this, &SchedulerClient::onSocketError);
}

SchedulerClient::SchedulerClient(const QUrl &url, const QJsonObject& plan, SchedulingMode mode, QObject *parent):
    SchedulerClient(url, parent)
{
    initialMessage = generateStartSchedulingMessage(plan, mode);
}

SchedulerClient::SchedulerClient(const QUrl &url, QUuid jobId, QObject *parent):
    SchedulerClient(url, parent)
{
    this->jobId = jobId;
    initialMessage = generateAttachSchedulingMessage(jobId);
}

void SchedulerClient::startScheduling()
{
    started = true;
    schedulerSocket.open(QUrl(schedulerUrl));
}

void SchedulerClient::onSocketError(QAbstractSocket::SocketError)
{
    finished = true;
    qDebug() << "Failed to connect to scheduler:" + schedulerSocket.errorString();
    emit connectionFailed("Failed to connect to scheduler:" + schedulerSocket.errorString());
}

void SchedulerClient::onConnected()
{
    qDebug() << "Connected to scheduler.";
    connect(&schedulerSocket, &QWebSocket::textMessageReceived, this, &SchedulerClient::onTextMessageReceived);
    connect(&schedulerSocket, &QWebSocket::binaryMessageReceived, this, &SchedulerClient::onTextMessageReceived);

    schedulerSocket.sendTextMessage(initialMessage);
    updateRequestTimer.start(PROGRESS_UPDATE_FREQUENCY);
}

void SchedulerClient::onTextMessageReceived(QString message)
{
    QJsonDocument document = QJsonDocument::fromJson(message.toUtf8());
    const QJsonObject& response = document.object();
    processMessage(response);
}

void SchedulerClient::onUpdateRequestTimer()
{
    schedulerSocket.sendTextMessage(generateRequestProgressMessage());
    if(started && !finished){
        updateRequestTimer.start(PROGRESS_UPDATE_FREQUENCY);
    }
}

QString SchedulerClient::generateStartSchedulingMessage(const QJsonObject &plan, SchedulerClient::SchedulingMode)
{
    //TODO add mode, when modes are implemented on serverside
    return "{\"jsonrpc\":\"2.0\",\"method\":\"startScheduling\",\"params\":["
    + QJsonDocument(plan).toJson(QJsonDocument::Compact) +
                   "],\"id\":\"" + QString::number(StartScheduling) + "\"}";
}

QString SchedulerClient::generateAttachSchedulingMessage(QUuid)
{
    //TODO Replace mock, when jobIds are implemented on serverside
    return "{\"jsonrpc\":\"2.0\",\"method\":\"invalideName\",\"id\":\"" + QString::number(StartScheduling) + "\"}";
}

QString SchedulerClient::generateRequestProgressMessage()
{
    return "{\"jsonrpc\":\"2.0\",\"method\":\"getProgress\",\"id\":\"" + QString::number(RequestProgress) + "\"}";
}

QString SchedulerClient::generateRequestResultMessage()
{
    return "{\"jsonrpc\":\"2.0\",\"method\":\"getResult\",\"id\":\"" + QString::number(GetResult) + "\"}";
}

void SchedulerClient::processMessage(const QJsonObject &message)
{
    QJsonValue result = message.value("result");
    int id = message.value("id").toString().toInt();
    qDebug() << "Message from scheduler:" << QJsonDocument(message).toJson(QJsonDocument::Compact);
    switch (id){
    case StartScheduling:
        if(!result.isBool() || result.toBool() == false){
            stopScheduling();
            if(!jobId.isNull()){
                emit jobNotFound();
            }
            emit schedulingFailed("Failed to start scheduling");
        }else{
            if(jobId.isNull()){
                //TODO replace placeholder uuid
                jobId = QUuid::createUuid();
            }
            emit schedulingStarted(jobId);
        }
        break;
    case GetResult:
        if(result.isString()){
            stopScheduling();
            QString message = "Scheduling error: " + result.toString();
            qDebug() << message;
            emit schedulingFailed(message);
        }else if(result.isUndefined()){
            //TODO Maybe count the number of these and abort after x times
            QString message = "Scheduling not finished yet";
            qDebug() << message;
        }else if(result.isObject()){
            stopScheduling();
            qDebug() << "Scheduling successful";
            emit schedulingComplete(result.toObject());
        }else{
            stopScheduling();
            qDebug() << "Scheduler returned unexpected result";
            emit schedulingFailed("Scheduling failed");
        }
        break;
    case RequestProgress:
        if(result.isDouble()){
        double progress = result.toDouble();

        if(progress == 1.0){
            updateRequestTimer.stop();
            schedulerSocket.sendTextMessage(generateRequestResultMessage());
            started = false;
        }
        emit progressChanged(progress);
        }else{
            qDebug() << "Scheduler getProgress returned something unexpected";
        }
        break;
    default:
        qDebug() << "Unknown id";
    }
}

void SchedulerClient::stopScheduling()
{
    updateRequestTimer.stop();
    finished = true;
}
