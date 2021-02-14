import { Socket } from "net"
import { ProtocolHandler } from "./Protocol/ProtocolHandler"
import * as uuid from "uuid"
import { Server } from "http"
import { ProxyServer } from "./ProxyServer"
import { clearTimeout } from "timers"


///Цель общения с клиентом
export enum ProxyRequestPattern {
    handshake = "cryptoHandshake",
    data = "cryptoData"
}


///Направление ответа
export enum ProxyResponsePattern {
    toClient,
    toServer
}


export class ProxySession {

    readonly id: string


    readonly delegate: ProxyServer


    readonly protocol_handler: ProtocolHandler = new ProtocolHandler()


    public constructor(socket: Socket, delegate: ProxyServer) {
        this.id = uuid.v1()

        this.sh_client = socket
        this.delegate = delegate
        this.client_on_data_invoker(this)
        this.client_on_end_invoker(this)
        this.client_on_close_invoker(this)

        this.sh_server = new Socket()
        this.server_on_data(this)
        this.server_on_end(this)
        this.server_on_close(this)
    }


    //SH_CLIENT
    readonly sh_client: Socket


    client_input_buffer: Buffer = null


    client_input_timer: NodeJS.Timeout = null


    client_input_ended = false


    client_input_timeout_ms = 50


    client_on_data_invoker(invoker: ProxySession){
        var invoker = invoker

        this.sh_client.on("data",  (data) => {
            if (invoker.client_input_buffer == null) {
                invoker.client_input_buffer = data
            }
            else {
                invoker.client_input_buffer = Buffer.concat([invoker.client_input_buffer, data])
            }
            invoker.client_input_timer = setTimeout(invoker.client_end_handler, invoker.client_input_timeout_ms, invoker)
        })
    }


    client_on_end_invoker(invoker: ProxySession) {
        var invoker = invoker
        this.sh_client.on("end", (had_error) => {
            invoker.client_end_handler(invoker)
        })
    }


    async client_end_handler(invoker: ProxySession){
        //try {
            var invoker = invoker
            if (invoker.client_input_ended){
                return
            }
            
            clearTimeout(invoker.client_input_timer)
            invoker.client_input_timer = null
            invoker.client_input_ended = true

            let request_Str = invoker.client_input_buffer.toString()
            invoker.client_input_buffer = null
            console.log("Request from client: " + request_Str)
            let request_Obj = JSON.parse(request_Str)

            let response_str = await invoker.protocol_handler.handleRequest(request_Obj)
            switch (invoker.protocol_handler.response_scenario) {
                case ProxyResponsePattern.toClient:
                    invoker.sh_client.end(response_str)

                    break;
                case ProxyResponsePattern.toServer:
                    invoker.response_str = response_str
                    invoker.sh_server.connect(8084, "95.104.194.120")
                    //возможно нужно ожидать завершения connect, а не обрабатывать асинхронно
                    break
            }
        //}
        //catch (e) {
            //console.error("ProxySession client_on_data: %s", e)
        //}
    }


    client_on_close_invoker(invoker: ProxySession) {
        var invoker = invoker
        this.sh_client.on("close", (had_error) => {
            if (had_error) {
                console.log("ProxySession client_on_close had_error")
            }
            
            invoker.sh_client.destroy()
            invoker.sh_server.destroy()
            invoker.delegate.remove_session(invoker)
            invoker.protocol_handler.dispose()
        })
    }


    //SH_SERVER
    readonly sh_server: Socket


    server_input_buffer: Buffer = null

    response_str: string = null


    server_on_connect(invoker: ProxySession) {
        var invoker = invoker
        this.sh_server.on("connect", () => {
            invoker.sh_server.end(invoker.response_str)
        })
    }


    server_on_data(invoker: ProxySession) {
        var invoker = invoker
        this.sh_server.on("data", (data) => {
            let response_Str = data.toString()
            console.log("ProxySession Response from server: " + response_Str)
    
            if (invoker.protocol_handler.stay_alive) {
                let secured_response = invoker.protocol_handler.secureResponse(response_Str)
                invoker.sh_client.write(secured_response)
            }
            else {
                if (invoker.server_input_buffer == null) {
                    invoker.server_input_buffer = data
                }
                else {
                    invoker.server_input_buffer = Buffer.concat([invoker.server_input_buffer, data])
                }
            }
        })
    }


    server_on_end(invoker: ProxySession) {
        var invoker = invoker
        this.sh_server.on("end", () => {
            if (invoker.server_input_buffer != null){
                let message = invoker.server_input_buffer.toString()
                let secured_response = invoker.protocol_handler.secureResponse(message)
                invoker.server_input_buffer = null
    
                invoker.sh_client.end(secured_response)
                invoker.sh_server.destroy()
            }
        })
    }


    server_on_close(invoker: ProxySession) {
        var invoker = invoker
        this.sh_server.on("close", (had_error) => {
            if (had_error) {
                console.log("ProxySession server_on_close had_error")
            }
    
            invoker.sh_client.destroy()
            invoker.sh_server.destroy()
            //Проверить. При server_on_end должен вызываться server_on_close!
            invoker.delegate.remove_session(invoker)
            invoker.protocol_handler.dispose()
        })
    }
}