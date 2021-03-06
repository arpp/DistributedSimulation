#include <QCoreApplication>
#include "mnode.h"
#include "examplenode.h"
#include "exampleedge.h"
#include "readgraph.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    //TODO:Path from build
    MNode *n = new MNode("../DistributedSimulation/connections.config");
    n->initTransfer();
    readGraph rg(n);
    n->initQueues();
    n->print();

    qDebug() << "starting mid : " << n->getMId();

    for(int i=0;i<n->nodeList.size();++i)
    {
        if((qrand() % 1000) < 100)
        {
            unsigned long startNode = n->nodeList.at(i)->getNodeId();
            EventData * evData = new EventData(0,startNode,startNode,2);
            Event * seedEvent = new Event(n->nodeList.at(i), evData, n->nodeList, n->edgeList);
            n->events->evQueue[n->getMId()].enqueue(seedEvent);
        }
    }

    qDebug() << "seed size is : " << n->events->evQueue[n->getMId()].size();
    qDebug() << "started";
    n->beginSimulation();

    /*exampleNode* n1 = new exampleNode(10);
    exampleNode* n2 = new exampleNode(12);
    exampleNode* n3 = new exampleNode(14);
    exampleNode* n4 = new exampleNode(16);
    exampleNode* n5 = new exampleNode(18);
    exampleNode* n6 = new exampleNode(20);

    exampleEdge* e1 = new exampleEdge(n1, n2);
    exampleEdge* e2 = new exampleEdge(n1, n4);
    exampleEdge* e3 = new exampleEdge(n1, n6);
    exampleEdge* e4 = new exampleEdge(n2, n3);
    exampleEdge* e5 = new exampleEdge(n2, n5);
    exampleEdge* e6 = new exampleEdge(n3, n4);
    exampleEdge* e7 = new exampleEdge(n3, n5);
    exampleEdge* e8 = new exampleEdge(n3, n6);

    n->addNode(n1);
    n->addNode(n2);
    n->addNode(n3);

    n->addEdge(e1, 1);
    n->addEdge(e2, 2);
    n->addEdge(e3, 2);
    n->addEdge(e4, 1);
    n->addEdge(e5, 2);
    n->addEdge(e6, 2);
    n->addEdge(e7, 2);
    n->addEdge(e8, 2);

    n->print();*/

    return a.exec();
}
