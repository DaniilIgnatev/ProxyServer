#ifndef JSON_EXTENSION_H
#define JSON_EXTENSION_H

#include <QByteArray>
#include <QString>


class JSON_Extension
{
private:
    static const QString ext_response;


    static const QString ext_front;


    static const QString ext_back;

public:
    JSON_Extension();


    static size_t extention_size();


    static void makeResponseArray(QByteArray &response){
        response.insert(1, JSON_Extension::ext_response.toUtf8());
        response.push_front(JSON_Extension::ext_front.toUtf8());
        response.push_back(JSON_Extension::ext_back.toUtf8());
    }
};

#endif // JSON_EXTENSION_H
