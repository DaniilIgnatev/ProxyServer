import {ProxyRequestPattern} from "../ProxySession"


export interface SHRequest{
    type: string
    operation: string
}


export class SHCryptoHandshakeRequest implements SHRequest{
    readonly type: string = "request"
    readonly operation: string = ProxyRequestPattern.handshake
    ///Номер метода шифрования
    method: number
    ///Публичный ключ клиента
    key: string
}


export class SHSecuredRequest implements SHRequest{
    readonly type: string = "request"
    operation: string
    UID: string
    stayAlive: boolean
    request: string
}


export class SHAuthorizeRequest implements SHRequest{
    type: string
    operation: string

    user: string
    password: string
    time: string
}


export class SHClearRequest extends SHSecuredRequest{
    authorizeRequest: SHAuthorizeRequest
    dataRequest: SHRequest
}