#ifndef MNODE_H
#define MNODE_H

#include <QQueue>
#include <QList>
#include <QPair>
#include <QMap>
#include <QThread>
#include <QTcpSocket>
#include <QWaitCondition>
#include <QMutex>
#include "edgeabstract.h"
#include "nodeabstract.h"
#include "eventqueues.h"
#include "eventprocessworker.h"
#include "recvqueueworker.h"
#include "sendqueueworker.h"
#include "createNetwork/connector.h"
#include "createNetwork/fileshare.h"



//Multiple consecutive nulls and null on the top of a queue are useless do not add
//Todo: Seeding

class MNode
{
public:
    MNode(QString configFile);
    int getMId();
    void addNode(NodeAbstract* node);
    void addEdge(unsigned long srcId, NodeAbstract* dest, unsigned long sysId);
    NodeAbstract* getNodeFromNodeId(unsigned long nodeId);
    void print();
    void initTransfer();
    void initQueues();
    void beginSimulation();
    unsigned long TIME;
    EventQueues *events;

    QList<NodeAbstract*> nodeList;
    QList<QList<QPair<NodeAbstract*,int> > > edgeList;

private:
    int m_id;
    QString configFile;

    QMap<unsigned long, unsigned long> nodeIdToIndex;

    void initProcessQueueThread();
    void initRecvThread();
    void initSendThread();
    void initConnection();
    void transferFiles();


    EventProcessWorker *evWork;             //send all mutex and waitcond
    RecvQueueWorker *recWork;               //send eventqueue
    SendQueueWorker *senWork;               //send sendqueue

    QThread *evWorkThread, *recWorkThread, *senWorkThread;

    QMap<int,QTcpSocket*> incomingConnection;
    QMap<int,QTcpSocket*> outgoingConnection;

    QWaitCondition *evQueueNotEmpty;
    QWaitCondition *sendQueueNotEmpty;
    QMutex *evQueueMutex;//TODO:Keep n mutexes, 1 for each event queue
    QMutex *sendQueueMutex;
    QMutex *timeStampMutex;
};

#endif // MNODE_H
