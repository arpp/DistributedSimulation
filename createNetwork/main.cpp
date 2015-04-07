#include "connector.h"
#include "fileshare.h"
#include <QCoreApplication>
#include <QTextStream>
#include <QObject>
#include <QPair>
#include <QMap>
#include <QTcpSocket>
#include <QHostAddress>
#include <QFile>
#include <QFileInfo>
#include <QByteArray>
#include <QIODevice>
#include <QDataStream>

int main(int argc, char* argv[])
{
  QCoreApplication app(argc, argv);

    connector c("../DistributedSimulation/connections.config");
    c.begin();
    QTextStream(stdout) << "Connections established\n";
    QMap<int, QTcpSocket*> senders = c.getSenders();
    QMap<int, QTcpSocket*> receivers = c.getReceivers();

//    FileShare fs;
//    fs.sync("../recvfile.txt", 0, 1, receivers, senders);


//    QFile inputFile("../requirements.txt");

//    if(inputFile.open(QIODevice::ReadOnly)) {

//        QFileInfo fileinfo(inputFile.fileName());
//        int sizeofFile = fileinfo.size();
//        QByteArray filesize;
//        filesize.append(QByteArray::number((qint32)fileinfo.size()));
//        QTextStream(stdout) << filesize;

//        int tt = senders[0]->write(filesize);
//        senders[0]->waitForBytesWritten();
//        QTextStream(stdout) << "Size sent: " << t << "\n";
////        while (!toSend.atEnd())
////        {
////            QByteArray rawFile;
////            rawFile = toSend.read(50000);
////            out << rawFile;
////            qDebug() << "ToSend"<<rawFile.size();
////            s+=rawFile.size();
////        }

////        qDebug() << "Total:" << s;

//    }

//    QTextStream(stdout) << receivers[1]->peerAddress().toString();
//       }

//  int stat = senders[1]->write("Hellokdsbgkjbsdbvkbfkhgbkjsdnvkjbsfkjgndsjlnvkjsdfgjndskjbgdskj Wosjfhjavsfjavsjasvfjasagshvfrld", 200);
//  bool xx = senders[1]->waitForBytesWritten(-1);
//  QTextStream(stdout) << "sdfds " << senders[1]->peerAddress().toString() << "  " << stat << senders[1]->state() << xx;


//  Client *cl2 = new Client("10.140.237.99", 3456);
//  QThread *cthread2 = new QThread();
//  cl2->moveToThread(cthread2);
//  QObject::connect(cthread2, SIGNAL(started()), cl2, SLOT(reconnect()));
//  cthread2->start();





  return app.exec();
}
