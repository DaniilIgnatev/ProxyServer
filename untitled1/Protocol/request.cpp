#include "request.h"
#include <QObject>



//struct SHRequest : public QObject

void SHRequest::read(const QJsonObject &json){
    operation = json["operation"].toString();
}


void SHRequest::write(const QJsonObject &json){
    json["operation"] = operation;
}



//struct SHCryptoHandshakeRequest: public SHRequest

void SHCryptoHandshakeRequest::read(const QJsonObject &json){
    SHRequest::read(json);
    method = json["method"].toInt();
    key = json["key"].toString();
}


void SHCryptoHandshakeRequest::write(const QJsonObject &json){
    SHRequest::write(json);
    json["method"] = method;
    json["key"] = key;
}



//struct SHSecuredRequest: public SHRequest

void SHCryptoDataRequest::read(const QJsonObject &json){
    SHRequest::read(json);
    stayAlive = json["stayAlive"].toBool();
    request = json["request"].toString();
}


void SHCryptoDataRequest::write(const QJsonObject &json){
    SHRequest::write(json);
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


void SHAuthorizeRequest::write(const QJsonObject &json){
    SHRequest::write(json);
    json["user"] = user;
    json["password"] = password;
    json["time"] = time;
}
