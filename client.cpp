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

Client::Client(const QUrl &url, QObject *parent)
{
    connect(&webSocket, &QWebSocket::connected, this, &Client::onConnected);
    this->url = url;
}

void Client::updatePlan()
{
    webSocket.open(QUrl(url));
}

void Client::onConnected()
{
    qDebug() << "WebSocket connected";
    connect(&webSocket, &QWebSocket::textMessageReceived, this, &Client::onTextMessageReceived);
    connect(&webSocket, &QWebSocket::binaryMessageReceived, this, &Client::onTextMessageReceived);
    webSocket.sendTextMessage("{\"jsonrpc\":\"2.0\",\"method\":\"getPlans\",\"id\":\"3\"}");
}

void Client::onTextMessageReceived(QString message)
{
    qDebug() << "got message";
    QJsonDocument document = QJsonDocument::fromJson(message.toUtf8());
    QJsonObject response = document.object();
    qDebug() << "got message2" << QJsonDocument(response).toJson();
    QJsonValue result = response.value("result");
    emit gotResult(result);
}
