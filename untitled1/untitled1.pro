QT -= gui
QT += network
QT +=sql

CONFIG += c++11 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        Protocol/Security/cryptoproxy.cpp \
        Protocol/Security/keypair.cpp \
        Protocol/Security/securityhandler.cpp \
        Protocol/protocolhandler.cpp \
        Protocol/request.cpp \
        Protocol/response.cpp \
        Protocol/storage.cpp \
        Protocol/stored_session.cpp \
        main.cpp \
        server.cpp \
        session.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    Protocol/Security/cryptoproxy.h \
    Protocol/Security/keypair.h \
    Protocol/Security/securityhandler.h \
    Protocol/protocolhandler.h \
    Protocol/request.h \
    Protocol/response.h \
    Protocol/storage.h \
    Protocol/stored_session.h \
    server.h \
    session.h
