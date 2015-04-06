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
    c = new Connections("../connections.config");
//    c->printConnections();
}

void connector::begin() {
    QString ownIP;
    foreach (const QHostAddress &address, QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != QHostAddress(QHostAddress::LocalHost))
             ownIP = address.toString();
    }

    ConnectToAll *cta = new ConnectToAll(c, ownIP);
    c->printConnections();
    QThread *cthread = new QThread();
    cta->moveToThread(cthread);
    QObject::connect(cthread, SIGNAL(started()), cta, SLOT(startConnecting()));
    cthread->start();

    QTextStream(stdout) << "IP of this system is " << ownIP << " " << c->getPort(ownIP);

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
        QPair<int, QTcpSocket*> p(x->getID(), x->getClientHandle());
        senders.push_back(p);
        QTcpSocket* qts = sockets[i];
        QPair<int, QTcpSocket*> p2 = qMakePair(c->getID((qts->peerAddress()).toString()), qts);
        receivers.push_back(p2);
    }
    QTextStream(stdout) << "Done dona done\n";
}

std::vector<QPair<int , QTcpSocket*> > connector::getSenders() {
    return senders;
}

std::vector<QPair<int , QTcpSocket*> > connector::getReceivers() {
    return receivers;
}

