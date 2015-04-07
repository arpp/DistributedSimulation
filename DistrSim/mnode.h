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
    void addNode(NodeAbstract* node);
    void addEdge(EdgeAbstract* edge, unsigned long sysId);
    void print();
    void initTransfer();
    void beginSimulation();
    unsigned long TIME;

private:
    int m_id;
    QString configFile;

    QList<NodeAbstract*> nodeList;
    QList<QList<QPair<NodeAbstract*,int> > > edgeList;
    QMap<NodeAbstract*, unsigned long> nodeToIndex;
    EventQueues *events;

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
    QMutex *evQueueMutex;
    QMutex *sendQueueMutex;
    QMutex *timeStampMutex;
};

#endif // MNODE_H
