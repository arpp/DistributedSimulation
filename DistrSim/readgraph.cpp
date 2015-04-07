#include "readgraph.h"
#include "mnode.h"
#include "examplenode.h"
#include "exampleedge.h"
#include <QFile>

readGraph::readGraph(MNode *n)
{
    QFile fn("nodepartition"+n->getMId());
    fn.open(QIODevice::ReadOnly);

    while(!fn.atEnd())
    {
        char line[1000];
        fn.readLine(line, 1000);
        int id = atoi(line);

        exampleNode *en = new exampleNode(id);

        n->addNode(en);
    }

    fn.close();

    QFile fe("edgepartition"+n->getMId());
    fe.open(QIODevice::ReadOnly);

    while(!fe.atEnd())
    {
        char line[1000];
        fe.readLine(line, 1000);

        QString str(line);
        QStringList strList = str.split(" ");

        exampleNode *sn = new exampleNode(strList[0]);
        exampleNode *dn = new exampleNode(strList[1]);

        exampleEdge *ee = new exampleEdge(sn, dn);

        n->addEdge(ee, strList[2].toLong());
    }
}
