"use strict";
var __extends = (this && this.__extends) || (function () {
    var extendStatics = function (d, b) {
        extendStatics = Object.setPrototypeOf ||
            ({ __proto__: [] } instanceof Array && function (d, b) { d.__proto__ = b; }) ||
            function (d, b) { for (var p in b) if (Object.prototype.hasOwnProperty.call(b, p)) d[p] = b[p]; };
        return extendStatics(d, b);
    };
    return function (d, b) {
        extendStatics(d, b);
        function __() { this.constructor = d; }
        d.prototype = b === null ? Object.create(b) : (__.prototype = b.prototype, new __());
    };
})();
Object.defineProperty(exports, "__esModule", { value: true });
exports.SHAuthorizeRequest = exports.SHClearRequest = exports.SHSecuredRequest = exports.SHCryptoHandshakeRequest = void 0;
var ProxySession_1 = require("../ProxySession");
var SHCryptoHandshakeRequest = /** @class */ (function () {
    function SHCryptoHandshakeRequest() {
        this.type = "request";
        this.operation = ProxySession_1.ProxyRequestPattern.handshake;
    }
    return SHCryptoHandshakeRequest;
}());
exports.SHCryptoHandshakeRequest = SHCryptoHandshakeRequest;
var SHSecuredRequest = /** @class */ (function () {
    function SHSecuredRequest() {
        this.type = "request";
    }
    return SHSecuredRequest;
}());
exports.SHSecuredRequest = SHSecuredRequest;
var SHClearRequest = /** @class */ (function (_super) {
    __extends(SHClearRequest, _super);
    function SHClearRequest() {
        return _super !== null && _super.apply(this, arguments) || this;
    }
    return SHClearRequest;
}(SHSecuredRequest));
exports.SHClearRequest = SHClearRequest;
var SHAuthorizeRequest = /** @class */ (function () {
    function SHAuthorizeRequest() {
    }
    return SHAuthorizeRequest;
}());
exports.SHAuthorizeRequest = SHAuthorizeRequest;
//# sourceMappingURL=Request.js.map