QT -= gui
QT += network

CONFIG += c++11 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
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
        ../ProxyServer/server.cpp \
        ../ProxyServer/session.cpp \
        ../ProxyServer/settings.cpp \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

SUBDIRS += \
    ../ProxyServer/ProxyServer.pro

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
    ../ProxyServer/server.h \
    ../ProxyServer/session.h \
    ../ProxyServer/settings.h
