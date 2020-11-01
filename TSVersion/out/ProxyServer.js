"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.ProxyServer = void 0;
var net_1 = require("net");
var ProxySession_1 = require("./ProxySession");
var ProxyServer = /** @class */ (function () {
    function ProxyServer(port) {
        this.port = 0;
        this.sesssionsList = [];
        this.server_socket = net_1.createServer(this.client_socket_handler);
        this.port = port;
    }
    ProxyServer.prototype.client_socket_handler = function (socket) {
        console.log("New socket");
        var new_session = new ProxySession_1.ProxySession(socket, server);
        server.sesssionsList.push(new_session);
    };
    ProxyServer.prototype.remove_session = function (session) {
        server.sesssionsList = server.sesssionsList.filter(function (s) { return s.id != session.id; });
    };
    ProxyServer.prototype.listen = function () {
        this.server_socket.listen(this.port);
    };
    return ProxyServer;
}());
exports.ProxyServer = ProxyServer;
var server = new ProxyServer(8085);
server.listen();
//# sourceMappingURL=ProxyServer.js.map