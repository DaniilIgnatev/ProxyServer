#ifndef JSON_EXTENSION_H
#define JSON_EXTENSION_H

#include <QByteArray>


class JSON_Extension
{
public:
    JSON_Extension();

    static void makeResponseArray(QByteArray &response){
        response.insert(1,"\"type\":\"response\",");
        response.insert(0,"[");
        response.push_back(']');
    }
};

#endif // JSON_EXTENSION_H
