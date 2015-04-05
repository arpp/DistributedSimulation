#ifndef MNODE_H
#define MNODE_H

#include <QQueue>
#include <QList>
#include <QPair>
#include <QMap>
#include <QThread>
#include <QTcpSocket>
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
    void addEdge(EdgeAbstract* edge, unsigned long sysId);
    void print();
    void beginSimulation();
    unsigned long TIME;

private:
    QList<NodeAbstract*> nodeList;
    QList<QList<QPair<NodeAbstract*,int> > > edgeList;
    QMap<NodeAbstract*, unsigned long> nodeToIndex;
    EventQueues *events;

    void initProcessQueueThread();
    void initRecvThread();
    void initSendThread();


    EventProcessWorker *evWork;
    RecvQueueWorker *recWork;
    SendQueueWorker *senWork;

    QThread *evWorkThread, *recWorkThread, *senWorkThread;

    QList<QTcpSocket*> incomingConnection;
    QList<QTcpSocket*> outgoingConnection;
};

#endif // MNODE_H
