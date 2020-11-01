TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        RSA/Rsa.cpp \
        main.cpp

DISTFILES += \
    RSA/Other Keys.txt \
    RSA/PrivateKey \
    RSA/PublicKey \
    RSA/Rsa.exe \
    RSA/ascii_table.txt

HEADERS += \
    Rsa.h
