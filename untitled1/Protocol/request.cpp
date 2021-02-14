#include "request.h"
#include <QObject>



//struct RequestPattern

RequestPattern::RequestPattern(QString operation){
    if (operation == RequestPattern_handshake){
        type = RequestPattern_Enum::cryptoHandshake;
    }
    else
        if (operation == RequestPattern_data){
            type = RequestPattern_Enum::cryptoData;
        }
        else{
            type = RequestPattern_Enum::undefined;
        }
}


QString RequestPattern::toOperation(){
    switch (type) {
    case RequestPattern_Enum::cryptoHandshake:
        return RequestPattern_handshake;
    case RequestPattern_Enum::cryptoData:
        return RequestPattern_data;
    default:
        return RequestPattern_undefined;
    }
}



//class SHRequest : public QObject

void SHRequest::read(const QJsonObject &json){
    operation = json["operation"].toString();
}


void SHRequest::write(const QJsonObject &json){
    json["operation"] = operation;
}



//class SHCryptoHandshakeRequest: public SHRequest

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



//class SHSecuredRequest: public SHRequest

void SHSecuredRequest::read(const QJsonObject &json){
    SHRequest::read(json);
    UID = json["UID"].toString();
    stayAlive = json["stayAlive"].toBool();
    request = json["request"].toString();
}


void SHSecuredRequest::write(const QJsonObject &json){
    SHRequest::write(json);
    json["UID"] = UID;
    json["stayAlive"] = stayAlive;
    json["request"] = request;
}



//class SHAuthorizeRequest: public SHRequest

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
