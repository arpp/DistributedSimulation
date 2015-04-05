#include "eventqueues.h"

EventQueues::EventQueues(QList<QQueue<EventAbstract*> > evQueue, QQueue<EventAbstract*> localQueue, QQueue<EventAbstract*> sendQueue, QList<NodeAbstract*> nodeList, QList<QList<QPair<EdgeAbstract*,int> > > edgeList)
{
    this->evQueue = evQueue;
    this->localQueue = localQueue;
    this->sendQueue = sendQueue;
    this->nodeList = nodeList;
    this->edgeList = edgeList;
}
