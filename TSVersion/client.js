//http://www.hacksparrow.com/tcp-socket-programming-in-node-js.html.)

const crypto = require("crypto")

// The `generateKeyPairSync` method accepts two arguments:
// 1. The type ok keys we want, which in this case is "rsa"
// 2. An object with the properties of the key
const { publicKey, privateKey } = crypto.generateKeyPairSync("rsa", {
    // The standard secure default length for RSA keys is 2048 bits
    modulusLength: 2048,
    namedCurve: 'secp256k1',
    publicKeyEncoding: {
        type: 'spki',
        format: 'pem'
    },
    privateKeyEncoding: {
        type: 'pkcs8',
        format: 'pem'
    }
})

var publicClientKey = publicKey
var publicClientKeyObject = crypto.createPublicKey(publicKey)

var privateClientKey = privateKey
var privateClientKeyObject = crypto.createPrivateKey(privateKey)


console.log("PUBLIC KEY: " + publicKey)
console.log("PRIVATE KEY: " + privateKey)


function encrypt(str, serverKey) {
    const encryptedData = crypto.publicEncrypt(
        {
            key: serverKey,
            padding: crypto.constants.RSA_PKCS1_OAEP_PADDING,
            oaepHash: "sha256",
        },
        // We convert the data string to a buffer using `Buffer.from`
        Buffer.from(str)
    ).toString("base64")
    return encryptedData
}


function decrypt(base64) {
    const decryptedData = crypto.privateDecrypt(
        {
            key: privateClientKeyObject,
            // In order to decrypt the data, we need to specify the
            // same hashing function and padding scheme that we used to
            // encrypt the data in the previous step
            padding: crypto.constants.RSA_PKCS1_OAEP_PADDING,
            oaepHash: "sha256"
        },
        Buffer.from(base64, "base64")
    ).toString()
    return decryptedData
}


//CLIENT


var net = require('net');
const { read } = require("fs")

var securityRequest = {
    type: "request",
    operation: "security",
    key: publicClientKey
}

var testRequest = {
    type: "request",
    operation: "test",
    credential: {
        user: "user1",
        password: "1"
    }
}

var client = new net.Socket();
client.connect(8084, '127.0.0.1', function () {
    console.log('Connected');

    securityRequest.time = new Date().valueOf().toString()
    securityRequest.array = new Array(900000).fill(100)
    let securityJSON = JSON.stringify(securityRequest)
    client.write(securityJSON);
});

var sentTest = false
var serverPublicKey = null
var serverPublicKeyObject = null

client.on('data', function (data) {
    let responseJSON = data.toString()
    console.log('Received: ' + responseJSON);

    let response = null
    try {
        response = JSON.parse(responseJSON)
    }
    catch (e) {

    }

    if (response == null){
        let decryptedResponseJSON = decrypt(responseJSON)
        let decryptedResponse = JSON.parse(decryptedResponseJSON)
        console.log("decrypted: " + decryptedResponseJSON)
        response = decryptedResponse
        responseJSON = decryptedResponseJSON
    }

    if (response.operation == "security") {
        serverPublicKey = response.result
        serverPublicKeyObject = crypto.createPublicKey(serverPublicKey)
        console.log("server key: " + serverPublicKey)
    }
    else
        if (response.operation == "test") {
            console.log("test: " + response.result)
        }

    if (!sentTest) {
        testRequest.time = new Date().valueOf().toString()
        let testJSON = JSON.stringify(testRequest)
        let encryptedTestJSON = encrypt(testJSON, serverPublicKeyObject)
        client.write(encryptedTestJSON)
        sentTest = true
    }
    else{
        client.end()
    }
});

client.on('close', function () {
    console.log('Connection closed');
});