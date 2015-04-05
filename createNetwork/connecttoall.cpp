#include "connecttoall.h"
#include "client.h"
#include <QObject>
#include <QThread>
#include <QTextStream>

ConnectToAll::ConnectToAll(QObject *parent): QObject(parent)
{
    c = NULL;
    connect(this, SIGNAL(createConnections()), this, SLOT(startConnecting()));
}

ConnectToAll::ConnectToAll(Connections *c, QString ownIP, QObject* parent): QObject(parent) {
    this->c = new Connections(*c);
    this->ownIP = ownIP;
    connect(this, SIGNAL(createConnections()), this, SLOT(startConnecting()));
}

void ConnectToAll::startConnecting() {
    QTextStream(stdout) << "Client thread is running\n";
    if(c == NULL) {

        Client *cl = new Client("10.138.39.52", 1234);
        clients.push_back(cl);
        emit cl->attemptConnection();

    }
    else {
        Client *cl;
        for (int i = 0; i < c->length(); ++i) {
            if(ownIP.compare(c->getIP(i)) != 0) {
                QTextStream(stdout) << "Connecting to " << c->getIP(i) << " on " << c->getPort(i) << "\n";
                cl = new Client(c->getIP(i), c->getPort(i));
                clients.push_back(cl);
                cl->attemptConnection();
            }
        }
    }
}

ConnectToAll::~ConnectToAll() {

}
