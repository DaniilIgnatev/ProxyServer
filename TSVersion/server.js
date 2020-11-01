//http://www.hacksparrow.com/tcp-socket-programming-in-node-js.html.)

const crypto = require("crypto");
const { read } = require("fs");
const net = require('net');

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


console.log("PUBLIC KEY: " + publicKey)
console.log("PRIVATE KEY: " + privateKey)


let RSA = {
    publicServerKey: publicKey,
    publicServerKeyObject: crypto.createPublicKey(publicKey),

    privateServerKey: privateKey,
    privateServerKeyObject: crypto.createPrivateKey(privateKey),

    publicClientKey: null,
    publicClientKeyObject: null,

    isReady: function () {
        return this.publicClientKey != null && this.publicClientKeyObject != null
    },

    encrypt: function (data) {
        const encryptedData = crypto.publicEncrypt(
            {
                key: this.publicClientKey,
                padding: crypto.constants.RSA_PKCS1_OAEP_PADDING,
                oaepHash: "sha256",
            },
            // We convert the data string to a buffer using `Buffer.from`
            Buffer.from(data)
        ).toString("base64")
        return encryptedData
    },

    decrypt: function (base64) {
        const decryptedData = crypto.privateDecrypt(
            {
                key: this.privateServerKeyObject,
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
}

readBuffer = null

let server = net.createServer(function (socket) {
    socket.setTimeout(1000)

    socket.on("data", (data) => {
        let requestJSON = data.toString()
        console.log("Read: " + requestJSON)

        if (readBuffer == null) {
            readBuffer = data
        }
        else {
            readBuffer = Buffer.concat([readBuffer, data])
        }
    })
    socket.on("timeout", (e) => {
        console.log("timeout!!!!")
        socket.end()
        serveBuffer()
    })
    socket.on("end", (e) => {
        console.log(e)
        serveBuffer()
    })
});


function serveBuffer() {
    requestJSON = readBuffer.toString()
    readBuffer = null

    let request = null
    try {
        request = JSON.parse(requestJSON)
        let l = request.array.length
        console.log(l)
        console.log(request.operation)
    }
    catch (e) {

    }

    let securedRequest = handleRequestSecurity(request, requestJSON)
    if (securedRequest) {
        let response = prepareResponse(securedRequest)
        let responseJSON = handleResponseSecurity(response)

        socket.write(responseJSON)
    }
}


server.listen(8084, '127.0.0.1');


function handleRequestSecurity(request, requestJSON) {
    var decodedRequest = request
    var decodedRequestJSON = requestJSON

    if (decodedRequest == null) {
        if (RSA.isReady()) {
            decodedRequestJSON = RSA.decrypt(Buffer.from(requestJSON, "base64"))
            decodedRequest = JSON.parse(decodedRequestJSON)
            console.log("Decrypted: " + decodedRequestJSON)
        }
    }

    if (decodedRequest == null || decodedRequest == undefined || decodedRequest.type == undefined || decodedRequest.operation == undefined) {
        return undefined
    }

    let passed = false
    let unixTime = new Date().valueOf()

    if (Math.abs(Number(decodedRequest.time) - unixTime) < 5000) {
        if (decodedRequest.operation == "security") {
            RSA.publicClientKey = decodedRequest.key
            RSA.publicClientKeyObject = crypto.createPublicKey(RSA.publicClientKey)
            passed = true
        }
        else {
            let credential = decodedRequest.credential
            let user = credential.user
            let password = credential.password
            if (user && password != undefined) {
                user = "user1"
                password = "1"
                let hash = crypto.createHash('sha256').update(password).digest('hex')
                passed = hash == "6b86b273ff34fce19d6b804eff5a3f5747ada4eaa22f1d49c01e52ddb7875b4b"
            }
        }
    }

    return passed ? decodedRequest : undefined
}


function prepareResponse(request) {
    var response = {
        type: response,
        operation: request.operation,
        result: null
    }

    switch (request.operation) {
        case "security":
            response.result = RSA.publicServerKey
            break
        case "test":
            response.result = true
            break
    }

    return response
}


function handleResponseSecurity(response) {
    let responseJSON = JSON.stringify(response)
    if (response.operation != "security") {
        return RSA.encrypt(responseJSON)
    }
    else {
        return responseJSON
    }
}