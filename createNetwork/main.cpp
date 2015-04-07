#include "connector.h"
#include <QCoreApplication>
#include <QTextStream>
#include <QObject>
#include <QPair>
#include <QMap>
#include <QTcpSocket>
#include <QHostAddress>

int main(int argc, char* argv[])
{
  QCoreApplication app(argc, argv);

  connector c("../connections.config");
  c.begin();
  QTextStream(stdout) << "Connections established\n";
  QMap<int, QTcpSocket*> senders = c.getSenders();
  QMap<int, QTcpSocket*> receivers = c.getReceivers();


  int stat = senders[1]->write("Hellokdsbgkjbsdbvkbfkhgbkjsdnvkjbsfkjgndsjlnvkjsdfgjndskjbgdskj Wosjfhjavsfjavsjasvfjasagshvfrld", 200);
  bool xx = senders[1]->waitForBytesWritten(-1);
  QTextStream(stdout) << "sdfds " << senders[1]->peerAddress().toString() << "  " << stat << senders[1]->state() << xx;


//  Client *cl2 = new Client("10.140.237.99", 3456);
//  QThread *cthread2 = new QThread();
//  cl2->moveToThread(cthread2);
//  QObject::connect(cthread2, SIGNAL(started()), cl2, SLOT(reconnect()));
//  cthread2->start();





  return app.exec();
}
