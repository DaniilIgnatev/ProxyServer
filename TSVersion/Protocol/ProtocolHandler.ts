import * as Request from "./Request"
import * as Response from "./Response"
import { ProxyRequestPattern, ProxyResponsePattern } from "../ProxySession"
import { SecurityHandler } from "./Security/SecurityHandler"
import * as uuid from "uuid"
import { CryptoProxyMethods, CryptoProxyMethods_Array, RSACryptoProxy } from "./Security/CryptoProxy"
import * as MongoDB from "mongodb";
import { RSAKeyPair } from "./Security/KeyPair"
import { SHSecuredRequest } from "./Request"
import { Stored_Session } from "./Documents"



function sleep(ms: number) {
    return new Promise((resolve) => {
        setTimeout(resolve, ms);
    });
}


export enum ProtocolHandlerStatus{
    notHandled,
    error,
    handled
}


//обработка протокола обмена с сервером
export class ProtocolHandler {

    security_handler: SecurityHandler = null


    request_scenario: ProxyRequestPattern = null


    response_scenario = ProxyResponsePattern.toClient


    status = ProtocolHandlerStatus.notHandled


    readonly url = "mongodb://localhost:27017/";
    readonly mongoClient = new MongoDB.MongoClient(this.url, { useNewUrlParser: true });


    constructor() {
        this.mongoClient.connect();
    }


    dispose() {
        this.mongoClient.close(true)
    }


    operation: string = null


    ///Возвращает строковый ответ.
    public async handleRequest(reqeust_list: any): Promise<string> {
        this.status = ProtocolHandlerStatus.notHandled

        let firstRequest = reqeust_list[0]
        this.operation = firstRequest.operation
        
        let error_response = new Response.SHStatusResponse();
        error_response.operation = this.operation

        let response = null
        //try {
            switch (this.operation) {
                case ProxyRequestPattern.handshake:
                    this.request_scenario = ProxyRequestPattern.handshake
                    this.response_scenario = ProxyResponsePattern.toClient
                    response = await this.handleHandshake(firstRequest)
                    this.status = ProtocolHandlerStatus.handled
                    break
                default:
                    this.request_scenario = ProxyRequestPattern.data
                    this.response_scenario = ProxyResponsePattern.toServer
                    response = await this.handleData(firstRequest)
                    this.status = ProtocolHandlerStatus.handled
                    break
            }
        //}
        // catch (error) {
        //     this.status = ProtocolHandlerStatus.error
        //     this.response_scenario = ProxyResponsePattern.toClient
        //     error_response.result_message = error
        //     error_response.description = error
        //     return JSON.stringify(error_response)
        // }

        return response
    }


    //HANDSHAKE
    async handleHandshake(request_obj: any): Promise<string> {
        let handshakeRequest = new Request.SHCryptoHandshakeRequest()
        handshakeRequest.key = request_obj.key
        handshakeRequest.method = request_obj.method
        

        let method = CryptoProxyMethods[CryptoProxyMethods[handshakeRequest.method]]
        let key_pair = new RSAKeyPair(handshakeRequest.key)
        let proxy = new RSACryptoProxy(key_pair)

        this.security_handler = new SecurityHandler(method, proxy)

        let UUID = await this.appendUUID(handshakeRequest)
        let key = this.security_handler.cryptoProxy.keys.server_public_key_string

        let handshakeResponse = new Response.SHCryptoHandshakeResponse()
        handshakeResponse.UUID = UUID
        handshakeResponse.key = key

        let response = [handshakeResponse]
        let response_str = JSON.stringify(response)
        return response_str
    }


    async appendUUID(request: Request.SHCryptoHandshakeRequest): Promise<string> {
        let UUID = uuid.v1()
        var mongoClient = this.mongoClient
        while (!mongoClient.isConnected()) {
            await sleep(10)
        }

        const db = mongoClient.db("SecurityProxy")
        const collection = db.collection("Sessions")
        let session: Stored_Session = { uuid: UUID, method: request.method, key: request.key }
        collection.insertOne(session, function (err, result) {
            if (err) {
                return console.log(err)
            }
            console.log(result.ops)
            mongoClient.close()
        })

        return UUID
    }


    //DATA
    stay_alive: boolean = false


    async handleData(request_obj: any): Promise<string> {
        let secured_request: SHSecuredRequest = request_obj
        this.stay_alive = secured_request.stayAlive

        while (!this.mongoClient.isConnected()) {
            await sleep(10)
        }

        const db = this.mongoClient.db("SecurityProxy")
        const collection = db.collection("Sessions")
        let session: Stored_Session = await collection.findOne({ uuid: secured_request.UID })

        let method = CryptoProxyMethods[CryptoProxyMethods[session.method]]
        let key_pair = new RSAKeyPair(session.key)
        let proxy = new RSACryptoProxy(key_pair)
        this.security_handler = new SecurityHandler(method, proxy)

        let unsecured_request = this.security_handler.removeShell(secured_request)

        if (!this.security_handler.checkAuthorize(unsecured_request.authorizeRequest)){
            throw new Error("Request validation error")
        }

        return unsecured_request.request
    }


    secureResponse(message: string): string{
        let cryptoResponse = this.security_handler.putInShell(message, this.operation)
        let response = [cryptoResponse]
        let response_str = JSON.stringify(response)
        return response_str
    }
}