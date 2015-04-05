#include <QtNetwork>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QString>
#include <vector>
#include "connections.h"

#ifndef SERVER_H
#define SERVER_H

class Server:public QObject {
Q_OBJECT
public:
  Server(QObject * parent, int);
  Server(QObject * parent, Connections *c, QString ownIP);
  ~Server();
  std::vector<QTcpSocket*> getSockets();
signals:
  void startServer();
  void allClientsConnected(std::vector<QTcpSocket*>);
public slots:
  void acceptConnection();
  void startListening();
  void startRead();
private:
    QTcpServer server;
    std::vector<QTcpSocket*> client;
    int port;
    Connections *c;
};

#endif // SERVER_H
