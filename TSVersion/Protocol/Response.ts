import {ProxyRequestPattern} from "../ProxySession"


export interface SHResponse{
    type: string
    operation: string
}


export class SHCryptoHandshakeResponse implements SHResponse{
    readonly type: string = "response"
    readonly operation: string = ProxyRequestPattern.handshake
    UUID: string
    key: string
}


export class SHCryptoDataResponse implements SHResponse{
    readonly type: string = "response"
    operation: string
    response: string
}


export class SHDataResponse implements SHResponse{
    readonly type: string = "response"
    operation: string
    result: any
}


export class SHStatusResponse implements SHResponse{
    readonly type: string = "response"
    operation: string
    result: boolean = true
    result_message: string
    description: string
}