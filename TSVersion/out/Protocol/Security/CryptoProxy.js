"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.RSACryptoProxy = exports.CryptoProxyMethods_Array = exports.CryptoProxyMethods = void 0;
var CryptoLib = require("crypto");
var CryptoProxyMethods;
(function (CryptoProxyMethods) {
    CryptoProxyMethods[CryptoProxyMethods["NONE"] = 0] = "NONE";
    CryptoProxyMethods[CryptoProxyMethods["RSA"] = 1] = "RSA";
})(CryptoProxyMethods = exports.CryptoProxyMethods || (exports.CryptoProxyMethods = {}));
exports.CryptoProxyMethods_Array = [CryptoProxyMethods.NONE, CryptoProxyMethods.RSA];
var RSACryptoProxy = /** @class */ (function () {
    function RSACryptoProxy(keys) {
        this.method = CryptoProxyMethods.RSA;
        this.keys = keys;
    }
    RSACryptoProxy.prototype.encrypt = function (str) {
        var encryptedData = CryptoLib.publicEncrypt({
            key: this.keys.client_public_key_string,
            padding: CryptoLib.constants.RSA_PKCS1_OAEP_PADDING,
            oaepHash: "sha256"
        }, 
        // We convert the data string to a buffer using `Buffer.from`
        Buffer.from(str)).toString("base64");
        return encryptedData;
    };
    RSACryptoProxy.prototype.decrypt = function (base64) {
        var buffer = Buffer.from(base64, "base64");
        var str = buffer.toString();
        var decryptedData = CryptoLib.privateDecrypt({
            key: this.keys.server_private_key_object,
            // In order to decrypt the data, we need to specify the
            // same hashing function and padding scheme that we used to
            // encrypt the data in the previous step
            padding: CryptoLib.constants.RSA_PKCS1_OAEP_PADDING,
            oaepHash: "sha256"
        }, buffer).toString();
        return decryptedData;
    };
    return RSACryptoProxy;
}());
exports.RSACryptoProxy = RSACryptoProxy;
//# sourceMappingURL=CryptoProxy.js.map