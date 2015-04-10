#include "server.h"
#include <iostream>
#include <QTextStream>
#include <QThread>

Server::Server(QObject* parent, int port): QObject(parent)
{
  this->c = new Connections(0);
  this->port = port;
  connect(this, SIGNAL(startServer()), this, SLOT(startListening()));
}

Server::Server(QObject* parent, Connections *c, QString ownIP):QObject(parent)
{
  this->c = new Connections(*c);
  this->port = (this->c)->getPort(ownIP);
  this->c->printConnections();
  connect(this, SIGNAL(startServer()), this, SLOT(startListening()));
}

Server::~Server()
{
    delete c;
    server.close();
}

void Server::startListening() {
    connect(&server, SIGNAL(newConnection()),
      this, SLOT(acceptConnection()));
    QHostAddress ha(QHostAddress::Any);
    bool y = server.listen(ha, port);
    std::cout << "Server is listening to " << port << " " << y << "";
    bool x = server.waitForNewConnection(-1);
}

void Server::acceptConnection()
{
  QTcpSocket* cl = server.nextPendingConnection();
  client.push_back(cl);
  QTextStream(stderr) << (cl->peerAddress()).toString() <<" has connected";
  if(client.size()+1 == c->length()) {
      QTextStream(stderr) << "All connections have been made";
      server.pauseAccepting();
      //exit thread
      QThread::currentThread()->exit();
      QTextStream(stderr) << "Server hasn't exited";

  }

}

void Server::startRead(QTcpSocket* cl)
{
    QTextStream(stderr) << "waiting for write by " << cl->peerAddress().toString()<<  "";
    bool x = cl->waitForReadyRead();
    if(x) {

    char buffer[1024] = {0};
    cl->read(buffer, cl->bytesAvailable());
    QTextStream(stderr) << buffer << "sdfds";
    }
    else {
        QTextStream(stderr) << "holy fuck";
    }
//  std::cout << buffer << std::endl;
//  cl->close();
}

std::vector<QTcpSocket*> Server::getSockets() {
    return client;
}
