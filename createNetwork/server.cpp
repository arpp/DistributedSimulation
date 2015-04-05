#include "server.h"
#include <iostream>
#include <QTextStream>

Server::Server(QObject* parent, int port): QObject(parent)
{
  this->c = new Connections(0);
  this->port = port;
  connect(this, SIGNAL(startServer()), this, SLOT(startListening()));
}

Server::Server(QObject* parent, Connections *c, QString ownIP):QObject(parent)
{
  this->c = new Connections(*c);
  this->port = this->c->getPort(ownIP);
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
    std::cout << "Server is listening to " << port << " " << y << "\n";
    bool x = server.waitForNewConnection(-1);
}

void Server::acceptConnection()
{
  QTcpSocket* cl = server.nextPendingConnection();
  client.push_back(cl);
  QTextStream(stdout) << (cl->peerAddress()).toString() <<" has connected\n";
//  if(client.size()+1 == c->length()) {
//     server.pauseAccepting();
//  }
  connect(cl, SIGNAL(readyRead()), this, SLOT(startRead()));
}

void Server::startRead()
{
    QTextStream(stdout) << "Hello world\n";
//  char buffer[1024] = {0};
//  cl->read(buffer, cl->bytesAvailable());
//  std::cout << buffer << std::endl;
//  cl->close();
}