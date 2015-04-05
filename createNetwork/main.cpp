#include "connector.h"
#include <QCoreApplication>
#include <QTextStream>
#include <QObject>

int main(int argc, char* argv[])
{
  QCoreApplication app(argc, argv);

  connector c("../connections.config");
  c.begin();




//  Client *cl2 = new Client("10.140.237.99", 3456);
//  QThread *cthread2 = new QThread();
//  cl2->moveToThread(cthread2);
//  QObject::connect(cthread2, SIGNAL(started()), cl2, SLOT(reconnect()));
//  cthread2->start();





  return app.exec();
}
