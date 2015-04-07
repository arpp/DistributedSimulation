#include "eventqueues.h"

EventQueues::EventQueues(QMap<int,QQueue<EventAbstract*> > evQueue, QQueue<EventAbstract*> sendQueue, QList<NodeAbstract*> nodeList, QList<QList<QPair<EdgeAbstract*,int> > > edgeList)
{
    this->evQueue = evQueue;
    this->sendQueue = sendQueue;
    this->nodeList = nodeList;
    this->edgeList = edgeList;
}
