"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.SecurityHandler = void 0;
var Request_1 = require("../Request");
var Response_1 = require("../Response");
///Снимает и устанавливает защитную оболочку вокруг пакета данных
var SecurityHandler = /** @class */ (function () {
    function SecurityHandler(cryptoMethod, cryptoProxy) {
        this.cryptoMethod = cryptoMethod;
        this.cryptoProxy = cryptoProxy;
    }
    ///Снятие защиты
    SecurityHandler.prototype.removeShell = function (secured_request) {
        var decryptedRequest = this.cryptoProxy.decrypt(secured_request.request);
        var decryptedRequestJSON = JSON.parse(decryptedRequest);
        var authorizeRequest = decryptedRequestJSON[0];
        var dataRequest = decryptedRequestJSON[1];
        var authorizeRequestTyped = new Request_1.SHAuthorizeRequest();
        authorizeRequestTyped.type = authorizeRequest.type;
        authorizeRequestTyped.operation = authorizeRequest.operation;
        authorizeRequestTyped.user = authorizeRequest.user;
        authorizeRequestTyped.password = authorizeRequest.password;
        authorizeRequestTyped.time = authorizeRequest.time;
        var unsecuredRequest = {
            type: secured_request.type,
            operation: secured_request.operation,
            UID: secured_request.UID,
            request: secured_request.request,
            stayAlive: secured_request.stayAlive,
            authorizeRequest: authorizeRequestTyped,
            dataRequest: dataRequest
        };
        return unsecuredRequest;
    };
    ///Проверка доступа
    SecurityHandler.prototype.checkAuthorize = function (authorize) {
        var unixTime = new Date().valueOf();
        var timeCheck = (Math.abs(Number(authorize.time) - unixTime) < 5000);
        return timeCheck;
    };
    SecurityHandler.prototype.putInShell = function (str, operation) {
        var encrypted = this.cryptoProxy.encrypt(str);
        var cryptoResponse = new Response_1.SHCryptoDataResponse();
        cryptoResponse.operation = operation;
        cryptoResponse.response = encrypted;
        return cryptoResponse;
    };
    return SecurityHandler;
}());
exports.SecurityHandler = SecurityHandler;
//# sourceMappingURL=SecurityHandler.js.map