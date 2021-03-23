#include "schedulerclient.h"

float SchedulerClient::getProgress() const { return progress; }

QSharedPointer<QJsonObject> SchedulerClient::getResult() const {
  return result;
}

SchedulerClient::SchedulerClient(const QUrl &url, QObject *parent)
    : QObject(parent), started(false), finished(false), schedulerUrl(url),
      progress(0.0) {
  connect(&schedulerSocket, &QWebSocket::connected, this,
          &SchedulerClient::onConnected);
  connect(&updateRequestTimer, SIGNAL(timeout()), this,
          SLOT(onUpdateRequestTimer()));
  connect(&schedulerSocket,
          QOverload<QAbstractSocket::SocketError>::of(&QWebSocket::error), this,
          &SchedulerClient::onSocketError);

  initialMessages += generateActivateSignalsMessage();
}

SchedulerClient::SchedulerClient(const QUrl &url, const QJsonObject &plan,
                                 SchedulingMode mode, QObject *parent)
    : SchedulerClient(url, parent) {

  initialMessages += generateSetAlgorithmMessage(mode);
  initialMessages += generateStartSchedulingMessage(plan, mode);
}

SchedulerClient::SchedulerClient(const QUrl &url, QUuid jobId, QObject *parent)
    : SchedulerClient(url, parent) {
  this->jobId = jobId;
  initialMessages += generateAttachSchedulingMessage(jobId);
}

void SchedulerClient::startScheduling() {
  started = true;
  schedulerSocket.open(QUrl(schedulerUrl));
}

void SchedulerClient::abortScheduling()
{
    if(started == true && finished == false && schedulerSocket.isValid()){
        QString message = generateStopSchedulingMessage();
        schedulerSocket.sendTextMessage(message);
    }
}

void SchedulerClient::onSocketError(QAbstractSocket::SocketError) {
  finished = true;
  qDebug() << "Failed to connect to scheduler:" + schedulerSocket.errorString();
  emit connectionFailed("Failed to connect to scheduler:" +
                        schedulerSocket.errorString());
}

void SchedulerClient::onConnected() {
  qDebug() << "Connected to scheduler.";
  connect(&schedulerSocket, &QWebSocket::textMessageReceived, this,
          &SchedulerClient::onTextMessageReceived);
  connect(&schedulerSocket, &QWebSocket::binaryMessageReceived, this,
          &SchedulerClient::onTextMessageReceived);

  for (const QString &message : initialMessages) {
    schedulerSocket.sendTextMessage(message);
    QCoreApplication::processEvents(QEventLoop::AllEvents, 20);
  }
}

void SchedulerClient::onTextMessageReceived(QString message) {
  QJsonDocument document = QJsonDocument::fromJson(message.toUtf8());
  const QJsonObject &response = document.object();
  processMessage(response);
}

void SchedulerClient::onUpdateRequestTimer() {
  schedulerSocket.sendTextMessage(generateRequestProgressMessage());
  if (started && !finished) {
    updateRequestTimer.start(PROGRESS_UPDATE_FREQUENCY);
  }
}

QString SchedulerClient::generateStopSchedulingMessage() {
  return "{\"jsonrpc\":\"2.0\",\"method\":\"stopScheduling\",\"params\":[]}";
}

QString SchedulerClient::generateActivateSignalsMessage() {
  return "{\"jsonrpc\":\"2.0\",\"method\":\"rpc.qt.activate\",\"params\":[],"
         "\"id\":\"" +
         QString::number(ActivateSignals) + "\"}";
}

QString SchedulerClient::generateSetAlgorithmMessage(
    SchedulerClient::SchedulingMode mode) {
  QString algorithmName;
  switch (mode) {
  case Good:
    algorithmName = "legacy-good";
    break;
  case Fast:
    algorithmName = "legacy-fast";
    break;
  }
  return "{\"jsonrpc\":\"2.0\",\"method\":\"startScheduling\",\"params\":[\"" +
         algorithmName + "\"]}";
}

QString SchedulerClient::generateStartSchedulingMessage(
    const QJsonObject &plan, SchedulerClient::SchedulingMode) {
  // TODO add mode, when modes are implemented on serverside
  return "{\"jsonrpc\":\"2.0\",\"method\":\"startScheduling\",\"params\":[" +
         QJsonDocument(plan).toJson(QJsonDocument::Compact) + "],\"id\":\"" +
         QString::number(StartScheduling) + "\"}";
}

QString SchedulerClient::generateAttachSchedulingMessage(QUuid) {
  // TODO Replace mock, when jobIds are implemented on serverside
  return "{\"jsonrpc\":\"2.0\",\"method\":\"invalideName\",\"id\":\"" +
         QString::number(StartScheduling) + "\"}";
}

QString SchedulerClient::generateRequestProgressMessage() {
  return "{\"jsonrpc\":\"2.0\",\"method\":\"getProgress\",\"id\":\"" +
         QString::number(RequestProgress) + "\"}";
}

QString SchedulerClient::generateRequestResultMessage() {
  return "{\"jsonrpc\":\"2.0\",\"method\":\"getResult\",\"id\":\"" +
         QString::number(GetResult) + "\"}";
}

void SchedulerClient::processMessage(const QJsonObject &message) {
  if (message.contains("result")) {
    processResult(message);
    return;
  }
  if (message.contains("method")) {
    processRequest(message);
    return;
  }
  if (message.contains("error")) {
    processError(message);
    return;
  }
  return;
}

void SchedulerClient::processResult(const QJsonObject &message) {
  QJsonValue result = message.value("result");
  int id = message.value("id").toString().toInt();
  qDebug() << "Message from scheduler:"
           << QJsonDocument(message).toJson(QJsonDocument::Compact);
  switch (id) {
  case StartScheduling:
    if (!result.isBool() || result.toBool() == false) {
      stopScheduling();
      if (!jobId.isNull()) {
        emit jobNotFound();
      }
      emit schedulingFailed("Failed to start scheduling");
    } else {
      if (jobId.isNull()) {
        // TODO replace placeholder uuid
        jobId = QUuid::createUuid();
      }
      emit schedulingStarted(jobId);
    }
    break;
  case GetResult:
    if (result.isString()) {
      stopScheduling();
      QString message = "Scheduling error: " + result.toString();
      qDebug() << message;
      emit schedulingFailed(message);
    } else if (result.isUndefined()) {
      // TODO Maybe count the number of these and abort after x times
      QString message = "Scheduling not finished yet";
      qDebug() << message;
    } else if (result.isObject()) {
      stopScheduling();
      qDebug() << "Scheduling successful";
      emit schedulingComplete(result.toObject());
    } else {
      stopScheduling();
      qDebug() << "Scheduler returned unexpected result";
      emit schedulingFailed("Scheduling failed");
    }
    break;
  case RequestProgress:
    if (result.isDouble()) {
      double progress = result.toDouble();

      if (progress == 1.0) {
        updateRequestTimer.stop();
        schedulerSocket.sendTextMessage(generateRequestResultMessage());
        started = false;
      }
      emit progressChanged(progress);
    } else {
      qDebug() << "Scheduler getProgress returned something unexpected";
    }
    break;
  case ActivateSignals:
    qDebug() << "Activated signals on scheduler service";
    break;
  default:
    qDebug() << "Unknown id";
  }
}

void SchedulerClient::processError(const QJsonObject &message) {
  int id = message.value("id").toString().toInt();
  QString errorMessage =
      message.value("error").toObject().value("message").toString();
  qDebug() << "Errormessage from scheduler: " << errorMessage;
  switch (id) {
  case StartScheduling:
    qDebug() << "There was a problem with startScheduling";
    break;
  case GetResult:
    qDebug() << "There was a problem with getResult";
    break;
  case RequestProgress:
    qDebug() << "There was a problem with requestProgress";
    break;
  case ActivateSignals:
    qDebug() << "Scheduler service does not support signals. This means you "
                "will get no messages about scheduling problems";
    updateRequestTimer.start(PROGRESS_UPDATE_FREQUENCY);
    break;
  default:
    qDebug() << "SchedulerClient got error message with unknown id";
  }
}

void SchedulerClient::processRequest(const QJsonObject &message) {
  QString method = message.value("method").toString();
  QJsonArray params = message.value("params").toArray();

  if (method == "finishedScheduling") {
    stopScheduling();
    qDebug() << "Scheduling successful";
    if (params[0].isObject()) {
      emit schedulingComplete(params[0].toObject());
    } else {
      qDebug() << "Got finishedScheduling with invalid params";
    }
    return;
  }

  if (method == "failedScheduling") {
    stopScheduling();
    qDebug() << "Failed scheduling";
    if (params[0].isString()) {
      emit schedulingFailed(params[0].toString());
    } else {
      qDebug() << "Got failedScheduling with invalid params";
    }
    return;
  }

  if (method == "emitWarning") {
    qDebug() << "Got warning";
    if (params[0].isString()) {
      emit warning(params[0].toString());
    } else {
      qDebug() << "Got emitWarning with invalid params";
    }
    return;
  }

  if (method == "updateProgress") {
    qDebug() << "Got progress";
    if (params[0].isDouble()) {
      emit progressChanged(params[0].toDouble());
    } else {
      qDebug() << "Got updateProgress with invalid params";
    }
    return;
  }

  qDebug() << "Got unknown signal";
  return;
}

void SchedulerClient::stopScheduling() {
  updateRequestTimer.stop();
  finished = true;
}
