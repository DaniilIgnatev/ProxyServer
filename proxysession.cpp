#include "proxysession.h"
#include "QTimer"


//THREAD
ProxySession::ProxySession(qintptr ID, QObject *parent): QThread(parent)
{
    this->proxy_server = parent;
    this->client_Socket_ID = ID;
    this->client_timeout.singleShot(50,this, SLOT(client_on_complete()));
    this->client_timeout.stop();
}


void ProxySession::run(){
    qDebug() << "Thread started";

    client_socket = new QTcpSocket();
    if (!client_socket->setSocketDescriptor(this->client_Socket_ID)){
        emit client_error(client_socket -> error());
        return;
    }

    //Direct connection -- invoke slot immedeately
    connect(client_socket, SIGNAL(readyRead()), this, SLOT(client_package()), Qt::DirectConnection);
    connect(client_socket, SIGNAL(disconnected()), this, SLOT(client_disconnect()));

    qDebug() << client_Socket_ID << " Client connected";
    exec();
}



//CLIENT_SOCKET
void ProxySession::client_package(){
    QByteArray new_data = read_data->append(client_socket->readAll());
    free(this->read_data);
    *(this->read_data) = new_data;

    qDebug() << client_Socket_ID << " Data in: " << new_data;

    client_timeout.start();
}


void ProxySession::client_on_complete(){
    QJsonDocument document = QJsonDocument::fromJson(*read_data);
    if (document.isArray()){

    }
    else{
        this->exit(-1);
    }
}


void ProxySession::client_disconnect(){
    qDebug() << client_Socket_ID << " Disconnected";

    client_socket->deleteLater();
    exit(0);
}



//SERVER_SOCKET
void ProxySession::server_package(){

}


void ::ProxySession::server_on_complete(){

}


void ProxySession::server_disconnect(){

}
