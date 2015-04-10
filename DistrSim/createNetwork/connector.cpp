#include "connector.h"
#include "connecttoall.h"
#include "client.h"
#include "server.h"
#include <QThread>
#include <QString>
#include <QTextStream>
#include <vector>
#include <QPair>


connector::connector(QString filename)
{
    c = new Connections(filename);
//    c->printConnections();
}

void connector::begin() {
    QString ownIP;
    foreach (const QHostAddress &address, QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != QHostAddress(QHostAddress::LocalHost))
             ownIP = address.toString();
    }

    if(c->length() ==1)return;

    ConnectToAll *cta = new ConnectToAll(c, ownIP);
    c->printConnections();
    QThread *cthread = new QThread();
    cta->moveToThread(cthread);
    QObject::connect(cthread, SIGNAL(started()), cta, SLOT(startConnecting()));
    cthread->start();

    QTextStream(stderr) << "IP of this system is " << ownIP << " " << c->getPort(ownIP);

    Server *server = new Server(0, c, ownIP);
  //  emit server->startServer();
    QThread *sthread = new QThread();
    server->moveToThread(sthread);
    QObject::connect(sthread, SIGNAL(started()), server, SLOT(startListening()));
    sthread->start();

    cthread->wait();
    sthread->wait();

    std::vector<Client*> clients = cta->getClients();
    std::vector<QTcpSocket*> sockets = server->getSockets();

    for(int i=0; i<clients.size(); i++) {
        Client* x = clients[i];
        senders[x->getID()] = x->getClientHandle();
        QTcpSocket* qts = sockets[i];
        receivers[c->getID((qts->peerAddress()).toString())] = qts;
    }
    QTextStream(stderr) << "Done dona done";
}

QMap<int, QTcpSocket*> connector::getSenders() {
    return senders;
}

QMap<int, QTcpSocket*> connector::getReceivers() {
    return receivers;
}

int connector::getOwnID() {
    QString ownIP;
    foreach (const QHostAddress &address, QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != QHostAddress(QHostAddress::LocalHost))
             ownIP = address.toString();
    }
    return c->getID(ownIP);
}
