TARGET   = shproxyserver
TEMPLATE = app
CONFIG   += console qt
QT = core network core-private concurrent

SOURCES  = main.cpp \
    ../ProxyServer/Protocol/Security/cryptokey.cpp \
    ../ProxyServer/Protocol/Security/cryptokeysdescriptor.cpp \
    ../ProxyServer/Protocol/Security/rsacryptoproxy.cpp \
    ../ProxyServer/Protocol/Security/rsagenerator.cpp \
    ../ProxyServer/Protocol/Security/rsageneratorsingletron.cpp \
    ../ProxyServer/Protocol/Security/rsakeypair.cpp \
    ../ProxyServer/Protocol/Security/securityhandler.cpp \
    ../ProxyServer/Protocol/protocolhandler.cpp \
    ../ProxyServer/Protocol/protocolpattern.cpp \
    ../ProxyServer/Protocol/request.cpp \
    ../ProxyServer/Protocol/response.cpp \
    ../ProxyServer/json_extension.cpp \
    ../ProxyServer/logwriter.cpp \
    ../ProxyServer/server.cpp \
    ../ProxyServer/session.cpp \
    ../ProxyServer/settings.cpp \
    proxyservice.cpp


include(qtservice/qtservice.pri)

HEADERS += \
    ../ProxyServer/Protocol/Security/cryptokey.h \
    ../ProxyServer/Protocol/Security/cryptokeysdescriptor.h \
    ../ProxyServer/Protocol/Security/rsacryptoproxy.h \
    ../ProxyServer/Protocol/Security/rsagenerator.h \
    ../ProxyServer/Protocol/Security/rsageneratorsingletron.h \
    ../ProxyServer/Protocol/Security/rsakeypair.h \
    ../ProxyServer/Protocol/Security/securityhandler.h \
    ../ProxyServer/Protocol/protocolhandler.h \
    ../ProxyServer/Protocol/protocolpattern.h \
    ../ProxyServer/Protocol/request.h \
    ../ProxyServer/Protocol/response.h \
    ../ProxyServer/json_extension.h \
    ../ProxyServer/logwriter.h \
    ../ProxyServer/server.h \
    ../ProxyServer/session.h \
    ../ProxyServer/settings.h \
    proxyservice.h

SUBDIRS += \
    ../ProxyServer/ProxyServer.pro


