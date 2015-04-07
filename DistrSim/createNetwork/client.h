#ifndef CLIENT_H
#define CLIENT_H
#include <QtNetwork>
#include <QObject>
#include <QString>
#include <QTcpSocket>
#include <QThread>

class Client: public QObject
{
Q_OBJECT
public:
  Client(QString, quint16, int, QObject* parent = 0);
  ~Client();
  void start();
  QTcpSocket* getClientHandle();
  int getID();
public slots:
  void reconnect();
  void startTransfer();
signals:
  void attemptConnection();
  void clientConnectedOK();
private:
  QTcpSocket client;
  QString hostname;
  quint16 port;
  long waitingTime;
  int id;
};

#endif // CLIENT_H
