#include "connector.h"
#include <QCoreApplication>
#include <QTextStream>
#include <QObject>
#include <QPair>
#include <vector>
#include <QTcpSocket>
#include <QHostAddress>

int main(int argc, char* argv[])
{
  QCoreApplication app(argc, argv);

  connector c("../connections.config");
  c.begin();
  QTextStream(stdout) << "Connections established\n";
  std::vector<QPair<int, QTcpSocket*> > senders = c.getSenders();
  std::vector<QPair<int, QTcpSocket*> > receivers = c.getReceivers();


  int stat = senders[0].second->write("Hello World", 13);
  QTextStream(stdout) << "sdfds " << (senders[0].second)->peerAddress().toString() << "  " << stat;


//  Client *cl2 = new Client("10.140.237.99", 3456);
//  QThread *cthread2 = new QThread();
//  cl2->moveToThread(cthread2);
//  QObject::connect(cthread2, SIGNAL(started()), cl2, SLOT(reconnect()));
//  cthread2->start();





  return app.exec();
}
