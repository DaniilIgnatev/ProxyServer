import { Server, Socket, createServer } from "net";
import {ProxySession} from "./ProxySession";



export class ProxyServer{
    port = 0
    sesssionsList: Array<ProxySession> = []

    constructor(port) {
        this.port = port
    }

    server_socket = createServer(this.client_socket_handler)


    client_socket_handler(socket){
        console.log("New socket")
        let new_session = new ProxySession(socket, server)
        server.sesssionsList.push(new_session)
    }

    
    remove_session(session){
        server.sesssionsList = server.sesssionsList.filter((s) => s.id != session.id)
    }


    listen(){
        this.server_socket.listen(this.port)
    }
}

var server = new ProxyServer(8085)
server.listen()