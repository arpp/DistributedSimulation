#ifndef MNODE_H
#define MNODE_H

#include <QQueue>
#include <QList>
#include <QPair>
#include "edgeabstract.h"
#include "nodeabstract.h"
#include "eventqueues.h"
#include "eventprocessworker.h"
#include "recvqueueworker.h"
#include "sendqueueworker.h"


//Multiple consecutive nulls and null on the top of a queue are useless do not add
//Todo: Seeding

class MNode
{
public:
    MNode();
    void addNode(NodeAbstract* node);
    void addEdge(NodeAbstract* edge, int sysId);
    void beginSimulation();
    unsigned long TIME;

private:
    QList<NodeAbstract*> nodeList;
    QList<QList<QPair<EdgeAbstract*,int> > > edgeList;
    EventQueues *events;

    void initProcessQueueThread();
    void initRecvThread();
    void initSendThread();


    EventProcessWorker *evWork;
    RecvQueueWorker *recWork;
    SendQueueWorker *senWork;

};

#endif // MNODE_H
