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
exports.ProxySession = exports.ProxyResponsePattern = exports.ProxyRequestPattern = void 0;
var net_1 = require("net");
var ProtocolHandler_1 = require("./Protocol/ProtocolHandler");
var uuid = require("uuid");
var timers_1 = require("timers");
///Цель общения с клиентом
var ProxyRequestPattern;
(function (ProxyRequestPattern) {
    ProxyRequestPattern["handshake"] = "cryptoHandshake";
    ProxyRequestPattern["data"] = "";
})(ProxyRequestPattern = exports.ProxyRequestPattern || (exports.ProxyRequestPattern = {}));
///Направление ответа
var ProxyResponsePattern;
(function (ProxyResponsePattern) {
    ProxyResponsePattern[ProxyResponsePattern["toClient"] = 0] = "toClient";
    ProxyResponsePattern[ProxyResponsePattern["toServer"] = 1] = "toServer";
})(ProxyResponsePattern = exports.ProxyResponsePattern || (exports.ProxyResponsePattern = {}));
var ProxySession = /** @class */ (function () {
    function ProxySession(socket, delegate) {
        this.protocol_handler = new ProtocolHandler_1.ProtocolHandler();
        this.client_input_buffer = null;
        this.client_input_timer = null;
        this.client_input_ended = false;
        this.client_input_timeout_ms = 50;
        this.server_input_buffer = null;
        this.response_str = null;
        this.id = uuid.v1();
        this.sh_client = socket;
        this.delegate = delegate;
        this.client_on_data_invoker(this);
        this.client_on_end_invoker(this);
        this.client_on_close_invoker(this);
        this.sh_server = new net_1.Socket();
        this.server_on_data(this);
        this.server_on_end(this);
        this.server_on_close(this);
    }
    ProxySession.prototype.client_on_data_invoker = function (invoker) {
        var invoker = invoker;
        this.sh_client.on("data", function (data) {
            if (invoker.client_input_buffer == null) {
                invoker.client_input_buffer = data;
            }
            else {
                invoker.client_input_buffer = Buffer.concat([invoker.client_input_buffer, data]);
            }
            invoker.client_input_timer = setTimeout(invoker.client_end_handler, invoker.client_input_timeout_ms, invoker);
        });
    };
    ProxySession.prototype.client_on_end_invoker = function (invoker) {
        var invoker = invoker;
        this.sh_client.on("end", function (had_error) {
            invoker.client_end_handler(invoker);
        });
    };
    ProxySession.prototype.client_end_handler = function (invoker) {
        var invoker;
        return __awaiter(this, void 0, void 0, function () {
            var request_Str, request_Obj, response_str;
            return __generator(this, function (_a) {
                switch (_a.label) {
                    case 0:
                        invoker = invoker;
                        if (invoker.client_input_ended) {
                            return [2 /*return*/];
                        }
                        timers_1.clearTimeout(invoker.client_input_timer);
                        invoker.client_input_timer = null;
                        invoker.client_input_ended = true;
                        request_Str = invoker.client_input_buffer.toString();
                        invoker.client_input_buffer = null;
                        console.log("Request from client: " + request_Str);
                        request_Obj = JSON.parse(request_Str);
                        return [4 /*yield*/, invoker.protocol_handler.handleRequest(request_Obj)];
                    case 1:
                        response_str = _a.sent();
                        switch (invoker.protocol_handler.response_scenario) {
                            case ProxyResponsePattern.toClient:
                                invoker.sh_client.end(response_str);
                                break;
                            case ProxyResponsePattern.toServer:
                                invoker.response_str = response_str;
                                invoker.sh_server.connect(8084, "95.104.194.120");
                                //возможно нужно ожидать завершения connect, а не обрабатывать асинхронно
                                break;
                        }
                        return [2 /*return*/];
                }
            });
        });
    };
    ProxySession.prototype.client_on_close_invoker = function (invoker) {
        var invoker = invoker;
        this.sh_client.on("close", function (had_error) {
            if (had_error) {
                console.log("ProxySession client_on_close had_error");
            }
            invoker.sh_client.destroy();
            invoker.sh_server.destroy();
            invoker.delegate.remove_session(invoker);
            invoker.protocol_handler.dispose();
        });
    };
    ProxySession.prototype.server_on_connect = function (invoker) {
        var invoker = invoker;
        this.sh_server.on("connect", function () {
            invoker.sh_server.end(invoker.response_str);
        });
    };
    ProxySession.prototype.server_on_data = function (invoker) {
        var invoker = invoker;
        this.sh_server.on("data", function (data) {
            var response_Str = data.toString();
            console.log("ProxySession Response from server: " + response_Str);
            if (invoker.protocol_handler.stay_alive) {
                var secured_response = invoker.protocol_handler.secureResponse(response_Str);
                invoker.sh_client.write(secured_response);
            }
            else {
                if (invoker.server_input_buffer == null) {
                    invoker.server_input_buffer = data;
                }
                else {
                    invoker.server_input_buffer = Buffer.concat([invoker.server_input_buffer, data]);
                }
            }
        });
    };
    ProxySession.prototype.server_on_end = function (invoker) {
        var invoker = invoker;
        this.sh_server.on("end", function () {
            if (invoker.server_input_buffer != null) {
                var message = invoker.server_input_buffer.toString();
                var secured_response = invoker.protocol_handler.secureResponse(message);
                invoker.server_input_buffer = null;
                invoker.sh_client.end(secured_response);
                invoker.sh_server.destroy();
            }
        });
    };
    ProxySession.prototype.server_on_close = function (invoker) {
        var invoker = invoker;
        this.sh_server.on("close", function (had_error) {
            if (had_error) {
                console.log("ProxySession server_on_close had_error");
            }
            invoker.sh_client.destroy();
            invoker.sh_server.destroy();
            //Проверить. При server_on_end должен вызываться server_on_close!
            invoker.delegate.remove_session(invoker);
            invoker.protocol_handler.dispose();
        });
    };
    return ProxySession;
}());
exports.ProxySession = ProxySession;
//# sourceMappingURL=ProxySession.js.map