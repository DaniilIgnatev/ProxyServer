#include "request.h"
#include <QObject>



//struct SHRequest : public QObject

void SHRequest::read(const QJsonObject &json){
    operation = json["operation"].toString();
}


void SHRequest::write(QJsonObject &json){
    json.insert("operation", operation);
}



//struct SHCryptoHandshakeRequest: public SHRequest

void SHCryptoHandshakeRequest::read(const QJsonObject &json){
    SHRequest::read(json);
    method = json["method"].toInt();
    key = json["key"].toString();
}


void SHCryptoHandshakeRequest::write(QJsonObject &json){
    SHRequest::write(json);
    json["method"] = method;
    json["key"] = key;
}



//struct SHSecuredRequest: public SHRequest

void SHCryptoDataRequest::read(const QJsonObject &json){
    SHRequest::read(json);
    key = json["key"].toString();
    stayAlive = json["stayAlive"].toBool();
    request = json["request"].toString();
}


void SHCryptoDataRequest::write(QJsonObject &json){
    SHRequest::write(json);
    json["key"] = key;
    json["stayAlive"] = stayAlive;
    json["request"] = request;
}



//struct SHAuthorizeRequest: public SHRequest

void SHAuthorizeRequest::read(const QJsonObject &json){
    SHRequest::read(json);
    user = json["user"].toString();
    password = json["password"].toString();
    time = json["time"].toString();
}


void SHAuthorizeRequest::write(QJsonObject &json){
    SHRequest::write(json);
    json["user"] = user;
    json["password"] = password;
    json["time"] = time;
}



//struct SHNakedRequest: SHCryptoDataRequest
SHNakedRequest::SHNakedRequest(const SHCryptoDataRequest &dataRequest, QString decryptedRequest)
{
    this->key = dataRequest.key;
    this->operation = dataRequest.operation;
    this->request = dataRequest.request;
    this->stayAlive = dataRequest.stayAlive;
    this->decryptedRequest = decryptedRequest;


    QJsonDocument jsonRequest = QJsonDocument::fromJson(decryptedRequest.toUtf8());
    QJsonArray jsonRequestArray = jsonRequest.array();

    QJsonObject authorizeJson = jsonRequestArray.first().toObject();
    SHAuthorizeRequest authorizeRequest;
    authorizeRequest.read(authorizeJson);
    this->authorizeRequest = authorizeRequest;
}
