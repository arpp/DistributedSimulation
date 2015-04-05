#include "client.h"
#include "server.h"
#include "connections.h"
#include "connecttoall.h"
#include <QCoreApplication>
#include <QTextStream>
#include <QThread>
#include <QObject>
#include <QHostAddress>
#include <QNetworkInterface>
#include <QAbstractSocket>

int main(int argc, char* argv[])
{
  QCoreApplication app(argc, argv);

  Connections *c = new Connections("../connections.config");
  c->printConnections();

  QString ownIP;
  foreach (const QHostAddress &address, QNetworkInterface::allAddresses()) {
      if (address.protocol() == QAbstractSocket::IPv4Protocol && address != QHostAddress(QHostAddress::LocalHost))
           ownIP = address.toString();
  }


  ConnectToAll *cta = new ConnectToAll(c, ownIP);
  emit cta->createConnections();

  QTextStream(stdout) << "IP of this system is " << ownIP << " " << c->getPort(ownIP);

  Server *server = new Server(0, c, ownIP);
  emit server->startServer();

//  QThread *cthread = new QThread();
//  cta->moveToThread(cthread);
//  QObject::connect(cthread, SIGNAL(started()), cta, SLOT(startConnecting()));
//  cthread->start();

//  Client *cl2 = new Client("10.140.237.99", 3456);
//  QThread *cthread2 = new QThread();
//  cl2->moveToThread(cthread2);
//  QObject::connect(cthread2, SIGNAL(started()), cl2, SLOT(reconnect()));
//  cthread2->start();



//  QThread *sthread = new QThread();
//  Server *server= new Server(0,c,ownIP);
//  server->moveToThread(sthread);
//  QObject::connect(sthread, SIGNAL(started()), server, SLOT(startListening()));
//  sthread->start();

  return app.exec();
}
