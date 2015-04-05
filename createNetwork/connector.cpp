#include "connector.h"
#include "connecttoall.h"
#include "server.h"
#include <QThread>
#include <QString>
#include <QTextStream>


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

    QTextStream(stdout) << "Done dona done\n";
}
