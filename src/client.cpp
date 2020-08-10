#include "client.h"

//void Client::onMsgFromServer(QString message) {
//    qDebug() << "onMsgFromServer: " << message;

//    // parse the json message
//    QJsonParseError err;
//    QJsonDocument jsonDoc = QJsonDocument::fromJson(message.toUtf8(), &err);

//    if (err.error != QJsonParseError::NoError) {
//        emit InterfaceError("Interner Fehler 1 in ClientInterface::SlotMsgFromServer()");

//        return;
//    }

//    QJsonObject jsonObj = jsonDoc.object();

//    if (fromJSON(jsonObj, "method").toString() == "readyRead") {
//        // no mode change

//        emit readyRead(fromJSON(jsonObj, "data").toString());
//    } else if (fromJSON(jsonObj, "method").toString() == "readyInterface") {
//        bool isEmulation = fromJSON(jsonObj, "isEmulation").toBool();

//        if (isEmulation)
//            mode = CONNECTED_EMULATION;
//        else
//            mode = CONNECTED_SERIAL;

//        emit readyInterface();
//    } else if (fromJSON(jsonObj, "method").toString() == "readyOpen") {
//        bool isEmulation = fromJSON(jsonObj, "isEmulation").toBool();

//        if (isEmulation)
//            mode = OPEN_EMULATION;
//        else
//            mode = OPEN_SERIAL;

//        emit readyOpen();
//    } else if (fromJSON(jsonObj, "method").toString() == "fillSerialPortList") {
//        // no mode change

//        emit readySerialPortList(fromJSONtoQVector<SerialPortInfo>(jsonObj, "serialPortList"));
//    } else if (fromJSON(jsonObj, "method").toString() == "InterfaceError") {
//        emit InterfaceError(fromJSON(jsonObj, "errString").toString());

//        exit(1);
//    } else {

//        emit InterfaceError("Interner Fehler 2 in ClientInterface::SlotMsgFromServer()");

//        exit(1);
//    }
//}

Client::Client(const QUrl &url, QObject *parent):
    QObject(parent), url(url), planning(false)
{
    connect(&webSocket, &QWebSocket::connected, this, &Client::onConnected);
    connect(&timer, SIGNAL(timeout()), this, SLOT(requestProgress()));
    connect(&webSocket, QOverload<QAbstractSocket::SocketError>::of(&QWebSocket::error), this, &Client::onError);
}

void Client::updatePlan()
{
    webSocket.sendTextMessage("{\"jsonrpc\":\"2.0\",\"method\":\"getPlans\",\"id\":\"3\"}");
}

void Client::startPlanning(QJsonValue plan)
{
    QString message = "{\"jsonrpc\":\"2.0\",\"method\":\"startPlanning\",\"params\":[";
    message.append(QJsonDocument(plan.toObject()).toJson(QJsonDocument::Compact));
    message.append("],\"id\":\"4\"}");
    webSocket.sendTextMessage(message);
    timer.start(500);
}

void Client::open()
{
    webSocket.open(QUrl(url));
}

void Client::onError(QAbstractSocket::SocketError error)
{
    emit socketError();
}

void Client::login(const QString& token){
    QString loginRequest = QString("{\"jsonrpc\":\"2.0\",\"method\":\"login\",\"params\":[\"%1\"],\"id\":\"7\"}").arg(token);
    webSocket.sendTextMessage(loginRequest);
}

void Client::onConnected()
{
    qDebug() << "WebSocket connected";
    connect(&webSocket, &QWebSocket::textMessageReceived, this, &Client::onTextMessageReceived);
    connect(&webSocket, &QWebSocket::binaryMessageReceived, this, &Client::onTextMessageReceived);
}

void Client::onTextMessageReceived(QString message)
{
    QJsonDocument document = QJsonDocument::fromJson(message.toUtf8());
    QJsonObject response = document.object();
    QJsonValue result = response.value("result");
    int id = response.value("id").toString().toInt();
    qDebug() << id << " got message:" << QJsonDocument(response).toJson(QJsonDocument::Compact);
    switch (id){
        case 3:
            emit gotResult(result);
            break;
    case 6:
            emit finishedPlanning(result);
            break;
    case 5:
    {
        int progress = result.toInt();
        if(progress == 100){
            timer.stop();
            webSocket.sendTextMessage("{\"jsonrpc\":\"2.0\",\"method\":\"getPlannedPlan\",\"id\":\"6\"}");
            planning = false;
        }
        emit setProgress(result.toInt());
        break;}
    case 7:
            qDebug() << "got " << result;
            if(result.toBool()){
                emit loginSuccess();
            }else{
                emit loginFailed();
            }
            break;
    default:
        qDebug() << "Unknown id";
    }

}

void Client::requestProgress()
{
    webSocket.sendTextMessage("{\"jsonrpc\":\"2.0\",\"method\":\"getPlanningProgress\",\"id\":\"5\"}");
    if(planning){
        timer.start(500);
    }
}
