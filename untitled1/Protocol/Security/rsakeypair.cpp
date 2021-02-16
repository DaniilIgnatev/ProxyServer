#include "rsakeypair.h"

/*
export class RSAKeyPair implements IKeyPair{

        server_private_key_string: string
        server_private_key_object: KeyObject

        server_public_key_string: string
         server_public_key_object: KeyObject

         client_public_key_string: string = null
         client_public_key_object: KeyObject = null


                                                                                                                                                                    constructor(client_public_key_string: string) {
    const { publicKey, privateKey } = CryptoLib.generateKeyPairSync("rsa", {
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
     })


        console.log("PUBLIC SERVER KEY: " + publicKey)
        console.log("PRIVATE SERVER KEY: " + privateKey)

      this.server_private_key_string = privateKey
      this.server_private_key_object = CryptoLib.createPrivateKey(this.server_private_key_string)

      this.server_public_key_string = publicKey
      this.server_public_key_object = CryptoLib.createPublicKey(this.server_public_key_string)


      console.log("PUBLIC CLIENT KEY: " + client_public_key_string)

      this.client_public_key_string = client_public_key_string
      this.client_public_key_object = CryptoLib.createPublicKey(this.client_public_key_string)
}
}
*/

RSAKeyPair::RSAKeyPair(SecurityKey client_public_key)
{
    this->client_public_key = client_public_key;
    this->self_private_key = SecurityKey(QString());
    this->self_public_key = SecurityKey(QString());
}
