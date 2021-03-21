#include "protocolpattern.h"



//struct ProtocolPattern

ProtocolPattern::ProtocolPattern(QString operation){
    if (operation == ProtocolPattern_handshake){
        type = ProtocolPattern_Enum::cryptoHandshake;
    }
    else
        if (operation == ProtocolPattern_data){
            type = ProtocolPattern_Enum::cryptoData;
        }
        else{
            type = ProtocolPattern_Enum::unknown;
        }
}


QString ProtocolPattern::toOperation(){
    switch (type) {
    case ProtocolPattern_Enum::cryptoHandshake:
        return ProtocolPattern_handshake;
    case ProtocolPattern_Enum::cryptoData:
        return ProtocolPattern_data;
    default:
        return ProtocolPattern_unknown;
    }
}
