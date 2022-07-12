#include "protocolhandler.h"
#include <QMetaEnum>


ProtocolHandler::ProtocolHandler(Settings *settings, LogWriter* logWriter, QObject *parent): QObject(parent)
{
    this->settings = settings;
    this->logWriter = logWriter;
}


ProtocolHandler::~ProtocolHandler()
{
    if (readData != nullptr){
        delete readData;
        readData = nullptr;
    }

    if (readStream != nullptr){
        delete readStream;
        readStream = nullptr;
    }

    if (request != nullptr){
        delete request;
        request = nullptr;
    }

    if (cryptoHandshakeRequest != nullptr){
        delete cryptoHandshakeRequest;
        cryptoHandshakeRequest = nullptr;
    }

    if (cryptoDataRequest != nullptr){
        delete cryptoDataRequest;
        cryptoDataRequest = nullptr;
    }

    if (shDataSocket != nullptr){
        shDataSocket->deleteLater();
        shDataSocket = nullptr;
    }

    if (bytesToServer != nullptr){
        delete bytesToServer;
        bytesToServer = nullptr;
    }

    logWriter->log("Деинициализация обработчика протокола\n", LogWriter::Status);
}


void ProtocolHandler::handleRequest(QByteArray &requestData)
{
    //qDebug() << "ProtocolHandler::handleRequest, thread: " << QThread::currentThreadId();

    QJsonDocument requestDocument = QJsonDocument::fromJson(requestData);
    QJsonArray request_list = requestDocument.array();

    status = ProtocolHandlerStatus::notHandled;

    QJsonObject firstRequest = request_list[0].toObject();
    request = new QJsonObject(firstRequest);

    QString operation = firstRequest["operation"].toString();
    ProtocolPattern requestType(operation);

    try {
        switch (requestType.type) {
        case ProtocolPattern_Enum::cryptoHandshake:
            handleCryptoHandshakeRequest(firstRequest);
            break;
        case ProtocolPattern_Enum::cryptoData:
            handleCryptoDataRequest(firstRequest);
            break;
        default:
            handleUnknownRequest(firstRequest);
        }
    }  catch (QException &e) {
        handleException(e);
    }
}


//CRYPTO_HANDSHAKE
void ProtocolHandler::handleCryptoHandshakeRequest(QJsonObject &request_obj)
{
    logWriter->log("Запрос обрабатывается как \"рукопожатие\"\n", LogWriter::Status);

    status = ProtocolHandlerStatus::handled;
    request_scenario = ProtocolPattern_Enum::cryptoHandshake;

    //qDebug("%s",QJsonDocument(request_obj).toJson().data());

    SHCryptoHandshakeRequest handshake;
    handshake.read(request_obj);
    cryptoHandshakeRequest = new SHCryptoHandshakeRequest(handshake);

    RSAKeyPair keyPair(handshake.key);
    RSACryptoProxy *crypto = new RSACryptoProxy(keyPair);

    security_handler = new SecurityHandler(crypto, this);
    crypto->setParent(security_handler);

    QString serverKey = security_handler->getPublicKey();

    SHCryptoHandshakeResponse response;
    response.key = serverKey;

    QJsonObject jsonObject = QJsonObject();
    response.write(jsonObject);

    QJsonDocument jsonDocument(jsonObject);
    QByteArray result = jsonDocument.toJson(QJsonDocument::JsonFormat::Compact);

    logWriter->log("Сформировал ответ:\n", LogWriter::Status);
    logWriter->log(result + "\n", LogWriter::Status);

    emit responseReady(result);
}


//CRYPTO_DATA
void ProtocolHandler::handleCryptoDataRequest(QJsonObject &request_obj)
{
    logWriter->log("Запрос обрабатывается как \"обмен данными\"\n", LogWriter::Status);

    status = ProtocolHandlerStatus::handled;
    request_scenario = ProtocolPattern_Enum::cryptoData;

    //qDebug("%s",QJsonDocument(request_obj).toJson().data());

    SHCryptoDataRequest dataRequest;
    dataRequest.read(request_obj);
    cryptoDataRequest = new SHCryptoDataRequest(dataRequest);

    this->stayAlive = dataRequest.stayAlive;
    this->secureResponse = dataRequest.secureResponse;

    RSAKeyPair keyPair(dataRequest.key);
    RSACryptoProxy *crypto = new RSACryptoProxy(keyPair);
    security_handler = new SecurityHandler(crypto, this);
    crypto->setParent(security_handler);

    SHNakedRequest nakedRequest = security_handler->removeShell(dataRequest);
    bytesToServer = new QByteArray(nakedRequest.decryptedRequest.toUtf8());

    shDataSocket = new QTcpSocket(this);
    connect(shDataSocket,QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),this,&ProtocolHandler::shDataSocket_onError);
    connect(shDataSocket, &QTcpSocket::connected, this, &ProtocolHandler::shDataSocket_onConnected);
    connect(shDataSocket, &QTcpSocket::disconnected, this, &ProtocolHandler::shDataSocket_onDisconnected);
    connect(shDataSocket, &QTcpSocket::readyRead, this, &ProtocolHandler::shDataSocket_onReadyRead);
    shDataSocket->connectToHost(this->settings->shAdress(), this->settings->shPort());
}


//UNKNOWN_REQUEST
void ProtocolHandler::handleUnknownRequest(QJsonObject &request_obj)
{
    Q_UNUSED(request_obj);
    logWriter->log("Запрос обрабатывается как \"неопознанный\"\n", LogWriter::Status);

    status = ProtocolHandlerStatus::error;

    //qDebug("%s",QJsonDocument(request_obj).toJson().data());

    SHStatusResponse unknownResponse;
    unknownResponse.result_message = "error";
    unknownResponse.result_message = "unknown request type";

    QJsonObject jsonObject;
    unknownResponse.write(jsonObject);

    QJsonDocument jsonDocument(jsonObject);
    QByteArray result = jsonDocument.toJson(QJsonDocument::JsonFormat::Compact);

    emit responseReady(result);
}


//EXCEPTION
void ProtocolHandler::handleException(QException &e)
{
    status = ProtocolHandlerStatus::error;

    SHStatusResponse exceptionResponse;
    exceptionResponse.result_message = "error";
    exceptionResponse.result_message = "exception occured";
    exceptionResponse.result_message.append(qPrintable(e.what()));

    QJsonObject jsonObject;
    exceptionResponse.write(jsonObject);

    QJsonDocument jsonDocument(jsonObject);
    auto jsonBytes = jsonDocument.toJson(QJsonDocument::JsonFormat::Compact);
    QByteArray result = jsonBytes.data();

    emit responseReady(result);
}



//SH_SOCKET_EVENTS
void ProtocolHandler::shDataSocket_onConnected()
{
    logWriter->log("Подключился к серверу умного дома\n", LogWriter::Status);

    if (bytesToServer != nullptr && bytesToServer->length() > 0){
        shDataSocket->write(*bytesToServer);

        logWriter->log("Отправил запрос серверу умного дома " + QString::number(bytesToServer->size()).toUtf8() + " байт\n", LogWriter::Status);
        logWriter->log("Содержимое запроса:\n", LogWriter::Content);
        logWriter->log(bytesToServer, LogWriter::Content);
        logWriter->log("\n\n", LogWriter::Content);
    }

    if (bytesToServer != nullptr){
        delete bytesToServer;
        bytesToServer = nullptr;
    }
}


void ProtocolHandler::shDataSocket_onDisconnected()
{
    logWriter->log("Отключился от сервера умного дома\n", LogWriter::Status);
    processResponse();
}


void ProtocolHandler::shDataSocket_onReadyRead()
{
    logWriter->log("Получил порцию данных от сервера умного дома\n", LogWriter::Status, false);

    if (!stayAlive){
        if (onReadDataTimer == nullptr){
            onReadDataTimer = new QTimer(this);
            onReadDataTimer->setSingleShot(true);
            connect(onReadDataTimer, &QTimer::timeout, this, &ProtocolHandler::onReadDataTimeout);
        }

        onReadDataTimer->start(ON_READ_TIMEOUT_MS);
    }


    if (readData == nullptr){
        readData = new QByteArray();
    }
    if (readStream == nullptr){
        readStream = new QDataStream(shDataSocket);
    }

    quint32 bytes_read_add = shDataSocket->bytesAvailable();

    QByteArray newReadData = shDataSocket->readAll();
    readData->append(newReadData);
    bytes_read += bytes_read_add;
    timeoutTimes = 0;

    if (stayAlive){
        processResponse();
    }
}


void ProtocolHandler::onReadDataTimeout(){
    timeoutTimes++;
    logWriter->log("Таймаут сокета умного дома №" + QString::number(timeoutTimes).toUtf8() + "\n", LogWriter::Status, false);

    if (bytes_read > 0 /*&& (!readData->endsWith("}]" && readData->startsWith("[{")))*/){
        if (timeoutTimes * ON_READ_TIMEOUT_MS < ON_READ_MAX_TIMEOUT_DATA_MS){
//            logWriter->log("Количество таймаутов не превышено", LogWriter::Status, false);
            onReadDataTimer->start(ON_READ_TIMEOUT_MS);
        }
        else{
            logWriter->log("Превышено время ожидания " + QString::number(ON_READ_TIMEOUT_MS < ON_READ_MAX_TIMEOUT_DATA_MS).toUtf8() + " мс. Данные получены частично!", LogWriter::Status);
            shDataSocket->close();
        }
    }
    else{
        if (timeoutTimes * ON_READ_TIMEOUT_MS >= ON_READ_MAX_TIMEOUT_EMPTY_MS){
            logWriter->log("Превышено время ожидания " + QString::number(ON_READ_TIMEOUT_MS < ON_READ_MAX_TIMEOUT_DATA_MS).toUtf8() + " мс. Данные не получены!", LogWriter::Status);
            shDataSocket->close();
        }
    }
}


void ProtocolHandler::shDataSocket_onError(QAbstractSocket::SocketError errorCode)
{
    if (errorCode != QAbstractSocket::SocketError::RemoteHostClosedError){
        QException exception;

        QMetaEnum metaEnum = QMetaEnum::fromType<QAbstractSocket::SocketError>();
        QString errorCodeString = metaEnum.valueToKey(errorCode);
        logWriter->log("\nОшибка сокета умного дома!!!\n", LogWriter::Status);
        logWriter->log("Код: " + errorCodeString.toUtf8() + "\n", LogWriter::Status);
        logWriter->log("Описание:" + QString(exception.what()).toUtf8() + "\n\n", LogWriter::Status);

        handleException(exception);
    }
}


void ProtocolHandler::processResponse(){
    if (bytes_read > 0){
        QString unsecuredResponse = QString::fromUtf8(*readData);
        readData->clear();
        bytes_read = 0;
        timeoutTimes = 0;

        logWriter->log("Принял ответ от сервера умного дома на " + QString::number(bytes_read).toUtf8() + " байт\n", LogWriter::Status);
        logWriter->log("Содержимое ответа:\n", LogWriter::Content);
        logWriter->log(readData, LogWriter::Content);
        logWriter->log("\n\n", LogWriter::Content);

        SHCryptoDataResponse dataResponse = security_handler->putInShell(unsecuredResponse, secureResponse);
        QJsonObject responseObject;
        dataResponse.write(responseObject);

        QJsonDocument responseDocument(responseObject);
        QByteArray responseData = responseDocument.toJson(QJsonDocument::JsonFormat::Compact);

        emit responseReady(responseData);
    }
}
