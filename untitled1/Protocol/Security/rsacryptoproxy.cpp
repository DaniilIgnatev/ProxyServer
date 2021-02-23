#include "rsacryptoproxy.h"



RSACryptoProxy::RSACryptoProxy(RSAKeyPair *keys, QObject *parent) : QObject(parent)
{
    this->keys = keys;
}


QString RSACryptoProxy::encrypt(QString str)
{
    QString encoded = enCrypt(str, *keys->client_public_key);
    QString base64 = QString::fromUtf8(encoded.toUtf8().toBase64());
    return base64;
}


QString RSACryptoProxy::decrypt(QString base64String)
{
    QString str = QString::fromUtf8(QByteArray::fromBase64(base64String.toUtf8()));
    QString decoded = deCrypt(str, *keys->self_private_key);
    return decoded;
}


int RSACryptoProxy::powBig(int num, int exp, int mod)
{
    int sum = num;
    int x = exp;
    while (x > 1) {
        sum = (num * sum) % mod;
        x--;
    }

    return sum;
}


QString RSACryptoProxy::enCrypt(QString str, CryptoKey publicKey)
{
    QString encodedStr = "";
    uint encodedInt = 0;
    QString encodedHex = "";

    QByteArray utf8Bytes = str.toUtf8();
    for (int i = 0;i < utf8Bytes.count();i++){
        quint8 byte = (quint8)utf8Bytes[i];
        encodedInt = powBig(byte, publicKey.x, publicKey.y);
        encodedHex = QString::number(encodedInt, 16).toUpper();
        encodedStr += encodedHex + "_";
    }

    return encodedStr;
}


QString RSACryptoProxy::deCrypt(QString str, CryptoKey privateKey)
{
    quint8 mTemp = 0;

    QStringList hexList = str.split("_");
    QByteArray bytes;
    for (int i = 0; i < hexList.count(); i++){
       int encodedInt = hexList[i].toInt(nullptr,16);
       mTemp = (quint8)powBig(encodedInt, privateKey.x, privateKey.y);
       bytes.append(mTemp);
    }

    QString decodedStr = QString::fromUtf8(bytes);
    return decodedStr;
}


