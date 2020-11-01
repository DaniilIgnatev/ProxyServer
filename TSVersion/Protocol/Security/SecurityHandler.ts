import { SHAuthorizeRequest, SHSecuredRequest, SHClearRequest } from "../Request"
import { SHCryptoDataResponse } from "../Response"
//обработка безопасности протокола

import * as CryptoProxy from "./CryptoProxy"


///Снимает и устанавливает защитную оболочку вокруг пакета данных
export class SecurityHandler {

    constructor(cryptoMethod: CryptoProxy.CryptoProxyMethods, cryptoProxy: CryptoProxy.ICryptoProxy) {
        this.cryptoMethod = cryptoMethod
        this.cryptoProxy = cryptoProxy
    }


    readonly cryptoMethod: CryptoProxy.CryptoProxyMethods


    readonly cryptoProxy: CryptoProxy.ICryptoProxy
    

    ///Снятие защиты
    removeShell(secured_request: SHSecuredRequest): SHClearRequest{
        let decryptedRequest = this.cryptoProxy.decrypt(secured_request.request)
        let decryptedRequestJSON = JSON.parse(decryptedRequest)

        let authorizeRequest = decryptedRequestJSON[0]
        let dataRequest = decryptedRequestJSON[1]

        let authorizeRequestTyped = new SHAuthorizeRequest()
        authorizeRequestTyped.type = authorizeRequest.type
        authorizeRequestTyped.operation = authorizeRequest.operation
        authorizeRequestTyped.user = authorizeRequest.user
        authorizeRequestTyped.password = authorizeRequest.password
        authorizeRequestTyped.time = authorizeRequest.time

        let unsecuredRequest: SHClearRequest = {
            type: secured_request.type,
            operation: secured_request.operation,
            UID: secured_request.UID,
            request: secured_request.request,
            stayAlive: secured_request.stayAlive,
            authorizeRequest: authorizeRequestTyped,
            dataRequest: dataRequest
        }

        return unsecuredRequest
    }


    ///Проверка доступа
    checkAuthorize(authorize: SHAuthorizeRequest): boolean  {
        let unixTime = new Date().valueOf()
    
        let timeCheck = (Math.abs(Number(authorize.time) - unixTime) < 5000)
        return timeCheck
    }


    putInShell(str: string, operation: string): SHCryptoDataResponse{
        let encrypted = this.cryptoProxy.encrypt(str)
        
        let cryptoResponse = new SHCryptoDataResponse()
        cryptoResponse.operation = operation
        cryptoResponse.response = encrypted
        
        return cryptoResponse
    }
}