#include "connecttoall.h"
#include "client.h"
#include <QObject>
#include <QThread>
#include <QTextStream>

ConnectToAll::ConnectToAll(QObject *parent): QObject(parent)
{
    c = NULL;
    count = 0;
    connect(this, SIGNAL(createConnections()), this, SLOT(startConnecting()));
}

ConnectToAll::ConnectToAll(Connections *c, QString ownIP, QObject* parent): QObject(parent) {
    count = 0;
    this->c = new Connections(*c);
    this->ownIP = ownIP;
    connect(this, SIGNAL(createConnections()), this, SLOT(startConnecting()));
}

void ConnectToAll::startConnecting() {
    QTextStream(stderr) << "Client thread is running";
    if(c == NULL) {

        Client *cl = new Client("10.138.39.52", 1234, 0);
        clients.push_back(cl);
        emit cl->attemptConnection();

    }
    else {
        QTextStream(stderr) <<"#yolo";
        Client *cl;
        for (int i = 0; i < c->length(); ++i) {
//            QTextStream(stderr) <<"#yolosdf";
            if(ownIP.compare(c->getIP(i)) != 0) {
                QTextStream(stderr) << "Connecting to " << c->getIP(i) << " on " << c->getPort(i) << "";
                cl = new Client(c->getIP(i), c->getPort(i), c->getID(i));
                clients.push_back(cl);
                QObject::connect(cl, SIGNAL(clientConnectedOK()), this, SLOT(clientConnectedPeace()));
                emit cl->attemptConnection();
            }
        }
    }
}

void ConnectToAll::clientConnectedPeace() {
    count++;
    if(count == c->length()-1) {
        QThread::currentThread()->exit();
        //exit thread
        QTextStream(stderr) << "This thread was supposed to exit";
    }
}

std::vector<Client*> ConnectToAll::getClients() {
    return clients;
}

ConnectToAll::~ConnectToAll() {

}
