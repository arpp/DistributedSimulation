#include "client.h"
#include <QHostAddress>
#include <QTextStream>
#include <QMetaObject>

Client::Client(QString hostname, quint16 port, int id, QObject* parent): QObject(parent)
{
    this->hostname = hostname;
    this->port = port;
    this->waitingTime = 0;
    this->id = id;
    connect(&client, SIGNAL(connected()), this, SLOT(startTransfer()));
    connect(this, SIGNAL(attemptConnection()), this, SLOT(reconnect()));
    connect(&client, SIGNAL(disconnected()), this, SLOT(reconnect()));
    QTextStream(stdout) << "the client is running\n";
}

Client::~Client()
{
  qDebug("Bye bye!");
}

void Client::start()
{
  QTextStream(stdout) << "connecting to " << hostname << " on " << port << "\n";
  client.connectToHost(hostname, port);
  if(client.waitForConnected(100)) {
      QTextStream(stdout) << "Could not connect\n";
  }
}

void Client::reconnect() {
  if(waitingTime == -1) {
      QTextStream(stdout) << "Disconnected. Try to reconnect to " << hostname << " on " << port << "\n";
      waitingTime = 1000;
  }
  else if(waitingTime == 0) {
        QTextStream(stdout) << "Connecting to " << hostname << " on " << port << "\n";
        waitingTime = 1000;
  }
  else {
      QTextStream(stdout) << "Reconnecting to " << hostname << " on " << port << "\n";
      waitingTime = 2*waitingTime;
  }

  client.connectToHost(hostname, port);
  if(!client.waitForConnected(100)) {
      QTextStream(stdout) << "Could not connect. Waiting for " <<  waitingTime/1000<< " sec(s)\n";
      QTimer::singleShot(waitingTime, this, SLOT(reconnect()));
  }
  else {
      waitingTime = -1;
      emit clientConnectedOK();
  }
}

QTcpSocket* Client::getClientHandle() {
    return &client;
}

void Client::startTransfer()
{
    QTextStream(stdout) << "connected yay\n";
    client.write("Hello, world", 13);
}

