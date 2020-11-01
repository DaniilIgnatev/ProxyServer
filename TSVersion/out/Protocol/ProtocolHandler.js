"use strict";
var __awaiter = (this && this.__awaiter) || function (thisArg, _arguments, P, generator) {
    function adopt(value) { return value instanceof P ? value : new P(function (resolve) { resolve(value); }); }
    return new (P || (P = Promise))(function (resolve, reject) {
        function fulfilled(value) { try { step(generator.next(value)); } catch (e) { reject(e); } }
        function rejected(value) { try { step(generator["throw"](value)); } catch (e) { reject(e); } }
        function step(result) { result.done ? resolve(result.value) : adopt(result.value).then(fulfilled, rejected); }
        step((generator = generator.apply(thisArg, _arguments || [])).next());
    });
};
var __generator = (this && this.__generator) || function (thisArg, body) {
    var _ = { label: 0, sent: function() { if (t[0] & 1) throw t[1]; return t[1]; }, trys: [], ops: [] }, f, y, t, g;
    return g = { next: verb(0), "throw": verb(1), "return": verb(2) }, typeof Symbol === "function" && (g[Symbol.iterator] = function() { return this; }), g;
    function verb(n) { return function (v) { return step([n, v]); }; }
    function step(op) {
        if (f) throw new TypeError("Generator is already executing.");
        while (_) try {
            if (f = 1, y && (t = op[0] & 2 ? y["return"] : op[0] ? y["throw"] || ((t = y["return"]) && t.call(y), 0) : y.next) && !(t = t.call(y, op[1])).done) return t;
            if (y = 0, t) op = [op[0] & 2, t.value];
            switch (op[0]) {
                case 0: case 1: t = op; break;
                case 4: _.label++; return { value: op[1], done: false };
                case 5: _.label++; y = op[1]; op = [0]; continue;
                case 7: op = _.ops.pop(); _.trys.pop(); continue;
                default:
                    if (!(t = _.trys, t = t.length > 0 && t[t.length - 1]) && (op[0] === 6 || op[0] === 2)) { _ = 0; continue; }
                    if (op[0] === 3 && (!t || (op[1] > t[0] && op[1] < t[3]))) { _.label = op[1]; break; }
                    if (op[0] === 6 && _.label < t[1]) { _.label = t[1]; t = op; break; }
                    if (t && _.label < t[2]) { _.label = t[2]; _.ops.push(op); break; }
                    if (t[2]) _.ops.pop();
                    _.trys.pop(); continue;
            }
            op = body.call(thisArg, _);
        } catch (e) { op = [6, e]; y = 0; } finally { f = t = 0; }
        if (op[0] & 5) throw op[1]; return { value: op[0] ? op[1] : void 0, done: true };
    }
};
Object.defineProperty(exports, "__esModule", { value: true });
exports.ProtocolHandler = exports.ProtocolHandlerStatus = void 0;
var Request = require("./Request");
var Response = require("./Response");
var ProxySession_1 = require("../ProxySession");
var SecurityHandler_1 = require("./Security/SecurityHandler");
var uuid = require("uuid");
var CryptoProxy_1 = require("./Security/CryptoProxy");
var MongoDB = require("mongodb");
var KeyPair_1 = require("./Security/KeyPair");
function sleep(ms) {
    return new Promise(function (resolve) {
        setTimeout(resolve, ms);
    });
}
var ProtocolHandlerStatus;
(function (ProtocolHandlerStatus) {
    ProtocolHandlerStatus[ProtocolHandlerStatus["notHandled"] = 0] = "notHandled";
    ProtocolHandlerStatus[ProtocolHandlerStatus["error"] = 1] = "error";
    ProtocolHandlerStatus[ProtocolHandlerStatus["handled"] = 2] = "handled";
})(ProtocolHandlerStatus = exports.ProtocolHandlerStatus || (exports.ProtocolHandlerStatus = {}));
//обработка протокола обмена с сервером
var ProtocolHandler = /** @class */ (function () {
    function ProtocolHandler() {
        this.security_handler = null;
        this.request_scenario = null;
        this.response_scenario = ProxySession_1.ProxyResponsePattern.toClient;
        this.status = ProtocolHandlerStatus.notHandled;
        this.url = "mongodb://localhost:27017/";
        this.mongoClient = new MongoDB.MongoClient(this.url, { useNewUrlParser: true });
        this.operation = null;
        //DATA
        this.stay_alive = false;
        this.mongoClient.connect();
    }
    ProtocolHandler.prototype.dispose = function () {
        this.mongoClient.close(true);
    };
    ///Возвращает строковый ответ.
    ProtocolHandler.prototype.handleRequest = function (reqeust_list) {
        return __awaiter(this, void 0, void 0, function () {
            var firstRequest, error_response, response, _a;
            return __generator(this, function (_b) {
                switch (_b.label) {
                    case 0:
                        this.status = ProtocolHandlerStatus.notHandled;
                        firstRequest = reqeust_list[0];
                        this.operation = firstRequest.operation;
                        error_response = new Response.SHStatusResponse();
                        error_response.operation = this.operation;
                        response = null;
                        _a = this.operation;
                        switch (_a) {
                            case ProxySession_1.ProxyRequestPattern.handshake: return [3 /*break*/, 1];
                        }
                        return [3 /*break*/, 3];
                    case 1:
                        this.request_scenario = ProxySession_1.ProxyRequestPattern.handshake;
                        this.response_scenario = ProxySession_1.ProxyResponsePattern.toClient;
                        return [4 /*yield*/, this.handleHandshake(firstRequest)];
                    case 2:
                        response = _b.sent();
                        this.status = ProtocolHandlerStatus.handled;
                        return [3 /*break*/, 5];
                    case 3:
                        this.request_scenario = ProxySession_1.ProxyRequestPattern.data;
                        this.response_scenario = ProxySession_1.ProxyResponsePattern.toServer;
                        return [4 /*yield*/, this.handleData(firstRequest)];
                    case 4:
                        response = _b.sent();
                        this.status = ProtocolHandlerStatus.handled;
                        return [3 /*break*/, 5];
                    case 5: 
                    //}
                    // catch (error) {
                    //     this.status = ProtocolHandlerStatus.error
                    //     this.response_scenario = ProxyResponsePattern.toClient
                    //     error_response.result_message = error
                    //     error_response.description = error
                    //     return JSON.stringify(error_response)
                    // }
                    return [2 /*return*/, response];
                }
            });
        });
    };
    //HANDSHAKE
    ProtocolHandler.prototype.handleHandshake = function (request_obj) {
        return __awaiter(this, void 0, void 0, function () {
            var handshakeRequest, method, key_pair, proxy, UUID, key, handshakeResponse, response, response_str;
            return __generator(this, function (_a) {
                switch (_a.label) {
                    case 0:
                        handshakeRequest = new Request.SHCryptoHandshakeRequest();
                        handshakeRequest.key = request_obj.key;
                        handshakeRequest.method = request_obj.method;
                        method = CryptoProxy_1.CryptoProxyMethods[CryptoProxy_1.CryptoProxyMethods[handshakeRequest.method]];
                        key_pair = new KeyPair_1.RSAKeyPair(handshakeRequest.key);
                        proxy = new CryptoProxy_1.RSACryptoProxy(key_pair);
                        this.security_handler = new SecurityHandler_1.SecurityHandler(method, proxy);
                        return [4 /*yield*/, this.appendUUID(handshakeRequest)];
                    case 1:
                        UUID = _a.sent();
                        key = this.security_handler.cryptoProxy.keys.server_public_key_string;
                        handshakeResponse = new Response.SHCryptoHandshakeResponse();
                        handshakeResponse.UUID = UUID;
                        handshakeResponse.key = key;
                        response = [handshakeResponse];
                        response_str = JSON.stringify(response);
                        return [2 /*return*/, response_str];
                }
            });
        });
    };
    ProtocolHandler.prototype.appendUUID = function (request) {
        return __awaiter(this, void 0, void 0, function () {
            var UUID, mongoClient, db, collection, session;
            return __generator(this, function (_a) {
                switch (_a.label) {
                    case 0:
                        UUID = uuid.v1();
                        mongoClient = this.mongoClient;
                        _a.label = 1;
                    case 1:
                        if (!!mongoClient.isConnected()) return [3 /*break*/, 3];
                        return [4 /*yield*/, sleep(10)];
                    case 2:
                        _a.sent();
                        return [3 /*break*/, 1];
                    case 3:
                        db = mongoClient.db("SecurityProxy");
                        collection = db.collection("Sessions");
                        session = { uuid: UUID, method: request.method, key: request.key };
                        collection.insertOne(session, function (err, result) {
                            if (err) {
                                return console.log(err);
                            }
                            console.log(result.ops);
                            mongoClient.close();
                        });
                        return [2 /*return*/, UUID];
                }
            });
        });
    };
    ProtocolHandler.prototype.handleData = function (request_obj) {
        return __awaiter(this, void 0, void 0, function () {
            var secured_request, db, collection, session, method, key_pair, proxy, unsecured_request;
            return __generator(this, function (_a) {
                switch (_a.label) {
                    case 0:
                        secured_request = request_obj;
                        this.stay_alive = secured_request.stayAlive;
                        _a.label = 1;
                    case 1:
                        if (!!this.mongoClient.isConnected()) return [3 /*break*/, 3];
                        return [4 /*yield*/, sleep(10)];
                    case 2:
                        _a.sent();
                        return [3 /*break*/, 1];
                    case 3:
                        db = this.mongoClient.db("SecurityProxy");
                        collection = db.collection("Sessions");
                        return [4 /*yield*/, collection.findOne({ uuid: secured_request.UID })];
                    case 4:
                        session = _a.sent();
                        method = CryptoProxy_1.CryptoProxyMethods[CryptoProxy_1.CryptoProxyMethods[session.method]];
                        key_pair = new KeyPair_1.RSAKeyPair(session.key);
                        proxy = new CryptoProxy_1.RSACryptoProxy(key_pair);
                        this.security_handler = new SecurityHandler_1.SecurityHandler(method, proxy);
                        unsecured_request = this.security_handler.removeShell(secured_request);
                        if (!this.security_handler.checkAuthorize(unsecured_request.authorizeRequest)) {
                            throw new Error("Request validation error");
                        }
                        return [2 /*return*/, unsecured_request.request];
                }
            });
        });
    };
    ProtocolHandler.prototype.secureResponse = function (message) {
        var cryptoResponse = this.security_handler.putInShell(message, this.operation);
        var response = [cryptoResponse];
        var response_str = JSON.stringify(response);
        return response_str;
    };
    return ProtocolHandler;
}());
exports.ProtocolHandler = ProtocolHandler;
//# sourceMappingURL=ProtocolHandler.js.map