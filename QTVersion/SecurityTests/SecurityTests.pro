QT -= gui
QT += testlib

CONFIG += c++11 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        ../ExecutableProject/Protocol/Security/cryptokey.cpp \
        ../ExecutableProject/Protocol/Security/cryptokeysdescriptor.cpp \
        ../ExecutableProject/Protocol/Security/rsacryptoproxy.cpp \
        ../ExecutableProject/Protocol/Security/rsagenerator.cpp \
        ../ExecutableProject/Protocol/Security/rsageneratorsingletron.cpp \
        ../ExecutableProject/Protocol/Security/rsakeypair.cpp \
        ../ExecutableProject/Protocol/Security/securityhandler.cpp \
        ../ExecutableProject/Protocol/protocolhandler.cpp \
        ../ExecutableProject/Protocol/protocolpattern.cpp \
        ../ExecutableProject/Protocol/request.cpp \
        ../ExecutableProject/Protocol/response.cpp \
        main.cpp \
        testqstring.cpp \
        testrsacryptoproxy.cpp \
        testrsagenerator.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    ../ExecutableProject/Protocol/Security/cryptokey.h \
    ../ExecutableProject/Protocol/Security/cryptokeysdescriptor.h \
    ../ExecutableProject/Protocol/Security/rsacryptoproxy.h \
    ../ExecutableProject/Protocol/Security/rsagenerator.h \
    ../ExecutableProject/Protocol/Security/rsageneratorsingletron.h \
    ../ExecutableProject/Protocol/Security/rsakeypair.h \
    ../ExecutableProject/Protocol/Security/securityhandler.h \
    ../ExecutableProject/Protocol/protocolhandler.h \
    ../ExecutableProject/Protocol/protocolpattern.h \
    ../ExecutableProject/Protocol/request.h \
    ../ExecutableProject/Protocol/response.h \
    testqstring.h \
    testrsacryptoproxy.h \
    testrsagenerator.h
