#include "Rsa.h"

using namespace std;

int main()
{
    loadAscii();
    string originalMessage="K", //Original Message
           decryptedMessage = "", //decryptedMessage
           encryptedMessage=""; //encryptedMessage
    key tKey;

    //cout << "Message: ";
    //getline(cin, originalMessage);

    //Display Keys
    tKey = getPrivateKey();
    cout << "Private Key = (" << tKey.x << ", " << tKey.y << ")" << endl;
    tKey = getPublicKey();
    cout << "Public Key = (" << tKey.x << ", " << tKey.y << ")" << endl;

    //Encode Message via Private Key
    encryptedMessage = enCrypt(originalMessage, getPrivateKey());
    cout << "\nEncoded Message (private key):\n" << encryptedMessage << endl << endl;

    //Decode Message via Public Key
    decryptedMessage = deCrypt(encryptedMessage, getPublicKey());
    cout << "Decoded Message (public key): " << decryptedMessage << endl;

    //Encode Message via Public Key
    encryptedMessage = enCrypt(originalMessage, getPublicKey());
    cout << "\nEncoded Message (public key):\n" << encryptedMessage << endl << endl;

    //Decode Message via Private Key
    decryptedMessage = deCrypt(encryptedMessage, getPrivateKey());
    cout << "Decoded Message (private key): " << decryptedMessage << endl;

    system("pause");

    return 0;
}
