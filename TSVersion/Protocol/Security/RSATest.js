

var keys = keypair.RSAKeyPair()
let sprivks = keys.server_private_key_string
let sprivko = keys.server_private_key_object
console.log("private key:" + sprivks)    

let spubks = keys.erver_public_key_string
let spubko = keys.server_public_key_object
console.log("public key:" + spubks)

function testEncrypt(){

}



function testDecrypt(){

}