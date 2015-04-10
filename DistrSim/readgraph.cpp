#include "readgraph.h"
#include "mnode.h"
#include "examplenode.h"
#include "exampleedge.h"
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
            int id = atoi(line);

            exampleNode *en = new exampleNode(id);

            n->addNode(en);
        }


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

            QString str(line);
            QStringList strList = str.split(" ");

            exampleNode *sn = new exampleNode(strList[0].toLong());            
            exampleNode *dn = new exampleNode(strList[1].toLong());

            exampleEdge *ee = new exampleEdge(sn, dn);
            n->addEdge(ee, strList[2].toLong());
        }
        fe.close();
    }
    else {
        qDebug() << "ERROR: edgepartition could not be opened. Exiting... ";
        exit(-1);
    }
}
