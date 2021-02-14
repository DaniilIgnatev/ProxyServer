#ifndef PROTOCOLPATTERN_H
#define PROTOCOLPATTERN_H


#include <QString>


#define ProtocolPattern_unknown "unknown"
#define ProtocolPattern_handshake "cryptoHandshake"
#define ProtocolPattern_data "cryptoData"



///Цель общения с клиентом
enum struct ProtocolPattern_Enum{
    unknown = 0,
    cryptoHandshake = 1,
    cryptoData = 2
};



///Цель общения с клиентом, логика
struct ProtocolPattern {
    ProtocolPattern_Enum type;

    ProtocolPattern(QString operation);

    QString toOperation();
};



///Направление ответа
enum struct DestinationPattern_Enum {
    unknown = 0,
    toClient = 1,
    toServer = 2
};

#endif // PROTOCOLPATTERN_H
