"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.RSAKeyPair = void 0;
var CryptoLib = require("crypto");
var RSAKeyPair = /** @class */ (function () {
    function RSAKeyPair(client_public_key_string) {
        this.client_public_key_string = null;
        this.client_public_key_object = null;
        var _a = CryptoLib.generateKeyPairSync("rsa", {
            // The standard secure default length for RSA keys is 2048 bits
            modulusLength: 2048,
            //namedCurve: 'secp256k1',
            publicKeyEncoding: {
                type: 'spki',
                format: 'pem'
            },
            privateKeyEncoding: {
                type: 'pkcs8',
                format: 'pem'
            }
        }), publicKey = _a.publicKey, privateKey = _a.privateKey;
        console.log("PUBLIC SERVER KEY: " + publicKey);
        console.log("PRIVATE SERVER KEY: " + privateKey);
        this.server_private_key_string = privateKey;
        this.server_private_key_object = CryptoLib.createPrivateKey(this.server_private_key_string);
        this.server_public_key_string = publicKey;
        this.server_public_key_object = CryptoLib.createPublicKey(this.server_public_key_string);
        console.log("PUBLIC CLIENT KEY: " + client_public_key_string);
        this.client_public_key_string = client_public_key_string;
        this.client_public_key_object = CryptoLib.createPublicKey(this.client_public_key_string);
    }
    return RSAKeyPair;
}());
exports.RSAKeyPair = RSAKeyPair;
//# sourceMappingURL=KeyPair.js.map