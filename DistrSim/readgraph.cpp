#include "readgraph.h"
#include "mnode.h"
#include "personnode.h"
#include "contactedge.h"
#include <QFile>

readGraph::readGraph(MNode *n)
{
    QString filename="nodepartition";
    if(n->getMId() == 0) {
        filename="nodepartition0";
    }
    QFile fn(filename);
    if(fn.open(QIODevice::ReadOnly)){

        while(!fn.atEnd())
        {
            char line[1000];
            fn.readLine(line, 1000);
            QString str(line);
            QStringList strList = str.split(" ");

            //id, infection period, incubation period
            PersonNode *en = new PersonNode(strList[0].toLong(), strList[1].toInt(), strList[2].toInt());

            n->addNode(en);
        }

     //   qDebug()<< "all people read";

        fn.close();
    }
    else {
        qDebug() << "ERROR: nodepartition could not be opened. Exiting... ";
        exit(-1);
    }

    filename = "edgepartition";
    if(n->getMId() == 0) {
        filename="edgepartition0";
    }

    QFile fe(filename);
    if(fe.open(QIODevice::ReadOnly)) {

        while(!fe.atEnd())
        {
            char line[1000];
            fe.readLine(line, 1000);

            QString str(line);  //line = srcid destid weight sysid
            QStringList strList = str.split(" ");

        //    qDebug()<<line;

            PersonNode *p = new PersonNode(strList[1].toLong(), 0, 0, 0);
      //      qDebug()<<line;
            PersonNode *np = new PersonNode(p->getNodeId(), p, strList[2].toInt());

     //       qDebug()<<line;

            //srcid, dest*, sysid
            n->addEdge(strList[0].toLong(), np, strList[3].toLong());
     //       qDebug()<<line;
        }

        fe.close();
    }
    else {
        qDebug() << "ERROR: edgepartition could not be opened. Exiting... ";
        exit(-1);
    }
}
