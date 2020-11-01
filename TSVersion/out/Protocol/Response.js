"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.SHStatusResponse = exports.SHDataResponse = exports.SHCryptoDataResponse = exports.SHCryptoHandshakeResponse = void 0;
var ProxySession_1 = require("../ProxySession");
var SHCryptoHandshakeResponse = /** @class */ (function () {
    function SHCryptoHandshakeResponse() {
        this.type = "response";
        this.operation = ProxySession_1.ProxyRequestPattern.handshake;
    }
    return SHCryptoHandshakeResponse;
}());
exports.SHCryptoHandshakeResponse = SHCryptoHandshakeResponse;
var SHCryptoDataResponse = /** @class */ (function () {
    function SHCryptoDataResponse() {
        this.type = "response";
    }
    return SHCryptoDataResponse;
}());
exports.SHCryptoDataResponse = SHCryptoDataResponse;
var SHDataResponse = /** @class */ (function () {
    function SHDataResponse() {
        this.type = "response";
    }
    return SHDataResponse;
}());
exports.SHDataResponse = SHDataResponse;
var SHStatusResponse = /** @class */ (function () {
    function SHStatusResponse() {
        this.type = "response";
        this.result = true;
    }
    return SHStatusResponse;
}());
exports.SHStatusResponse = SHStatusResponse;
//# sourceMappingURL=Response.js.map