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
  Client(QString, quint16, QObject* parent = 0);
  ~Client();
  void start();
  QTcpSocket* getClientHandle();
public slots:
  void reconnect();
  void startTransfer();
signals:
  void attemptConnection();
private:
  QTcpSocket client;
  QString hostname;
  quint16 port;
  long waitingTime;
};

#endif // CLIENT_H
