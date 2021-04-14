#include "response.h"



//struct SHResponse

void SHResponse::read(const QJsonObject &json){
    type = json["type"].toString();
    operation = json["operation"].toString();
}


void SHResponse::write(QJsonObject &json){
    json["operation"] = operation;
}



//struct SHCryptoHandshakeResponse: public SHResponse

SHCryptoHandshakeResponse::SHCryptoHandshakeResponse()
{
    operation = ProtocolPattern_handshake;
}

void SHCryptoHandshakeResponse::read(const QJsonObject &json){
    SHResponse::read(json);
    key = json["key"].toString();
}


void SHCryptoHandshakeResponse::write(QJsonObject &json){
    SHResponse::write(json);
    json["key"] = key;
}



//struct SHCryptoDataResponse: public SHResponse

SHCryptoDataResponse::SHCryptoDataResponse()
{
    operation = ProtocolPattern_data;
}

void SHCryptoDataResponse::read(const QJsonObject &json){
    SHResponse::read(json);
    response = json["response"].toString();
}


void SHCryptoDataResponse::write(QJsonObject &json){
    SHResponse::write(json);
    json["response"] = response;
}



//struct SHStatusResponse: public SHResponse

SHStatusResponse::SHStatusResponse()
{

}

void SHStatusResponse::read(const QJsonObject &json){
    SHResponse::read(json);
    result = json["result"].toBool();
    result_message = json["result_message"].toString();
    description = json["description"].toString();
}


void SHStatusResponse::write(QJsonObject &json){
    SHResponse::write(json);
    json["result"] = result;
    json["result_message"] = result_message;
    json["description"] = description;
}
