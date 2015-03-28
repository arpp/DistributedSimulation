#ifndef MNODE_H
#define MNODE_H

#include <QQueue>
#include <QList>
#include <QPair>
#include "eventabstract.h"
#include "edgeabstract.h"
#include "nodeabstract.h"


//Multiple consecutive nulls and null on the top of a queue are useless do not add


class MNode
{
public:
    MNode();
    void addNode(NodeAbstract* node);
    void addEdge(NodeAbstract* edge, int sysId);
    void processQueueThread();
    void recvThread();
    void sendThread();

private:
    QList<QQueue<EventAbstract*> > evQueue;
    QQueue<EventAbstract*> localQueue;
    QQueue<EventAbstract*> sendQueue;
    QList<NodeAbstract*> nodeList;
    QList<QList<QPair<EdgeAbstract*,int> > > edgeList;
    void insertEvent(EventAbstract* e);
    EventAbstract* removeEvent();

    static int TIME = 0;
};

#endif // MNODE_H
