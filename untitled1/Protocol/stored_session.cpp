#include "stored_session.h"



Stored_Session::Stored_Session(QString uuid, int method, QString key)
{
    this->uuid = uuid;
    this->method = method;
    this->key = key;
}


void Stored_Session::read(const QJsonObject &json){
    uuid = json["uuid"].toString();
    method = json["method"].toInt();
    key = json["key"].toString();
}

void Stored_Session::write(const QJsonObject &json){
    uuid = json["uuid"].toString();
    method = json["method"].toInt();
    key = json["key"].toString();
}
