import * as CryptoLib from "crypto"
import {IKeyPair, RSAKeyPair} from "./KeyPair"



export enum CryptoProxyMethods{
    NONE = 0,
    RSA = 1
}


export const CryptoProxyMethods_Array = [CryptoProxyMethods.NONE, CryptoProxyMethods.RSA]



export interface ICryptoProxy{
    method: CryptoProxyMethods

    keys: IKeyPair

    encrypt(str: string): string

    decrypt(base64: string): string
}



export class RSACryptoProxy implements ICryptoProxy {

    method = CryptoProxyMethods.RSA

    
    keys: RSAKeyPair


    constructor(keys: RSAKeyPair){
        this.keys = keys
    }


    encrypt(str: any) {
        const encryptedData = CryptoLib.publicEncrypt(
            {
                key: this.keys.client_public_key_string,
                padding: CryptoLib.constants.RSA_PKCS1_OAEP_PADDING,
                oaepHash: "sha256"
            },
            // We convert the data string to a buffer using `Buffer.from`
            Buffer.from(str)
        ).toString("base64")
        return encryptedData
    }


    decrypt(base64: any) {
        let buffer = Buffer.from(base64, "base64")
        let str = buffer.toString()
        
        const decryptedData = CryptoLib.privateDecrypt(
            {
                key: this.keys.server_private_key_object,
                // In order to decrypt the data, we need to specify the
                // same hashing function and padding scheme that we used to
                // encrypt the data in the previous step
                padding: CryptoLib.constants.RSA_PKCS1_OAEP_PADDING,
                oaepHash: "sha256"
            },
            buffer
        ).toString()
        return decryptedData
    }
}