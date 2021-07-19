#include "json_extension.h"


const QString JSON_Extension::ext_response = QString("\"type\":\"response\",");


const QString JSON_Extension::ext_front = QString("[");


const QString JSON_Extension::ext_back = QString("]");


JSON_Extension::JSON_Extension()
{

}


size_t JSON_Extension::extention_size()
{
    return ext_response.toUtf8().size() + ext_front.toUtf8().size() + ext_back.toUtf8().size();
}
