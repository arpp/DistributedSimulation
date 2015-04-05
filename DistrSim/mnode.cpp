#include "mnode.h"
#include <QPair>

MNode::MNode()
{
    this->TIME=0;
}

void MNode::addNode(NodeAbstract* node){
    this->nodeList.append(node);
    this->nodeToIndex[node] = this->nodeToIndex.count();

    QList<QPair<NodeAbstract*,int> > temp;
    this->edgeList.append(temp);
}

void MNode::addEdge(EdgeAbstract* edge, unsigned long sysId){
    NodeAbstract *src = edge->getSrc();
    unsigned long index = this->nodeToIndex[src];
    QPair<NodeAbstract*, unsigned long> nodeSysPair;
    nodeSysPair.first = edge->getDst();
    nodeSysPair.second = sysId;

    (this->edgeList[index]).append(nodeSysPair);
}

void MNode::beginSimulation(){
    initProcessQueueThread();
    initRecvThread();
    initSendThread();
}

void MNode::initProcessQueueThread(){
    this->evWork = new EventProcessWorker(this->events,&(this->TIME));
    this->evWorkThread = new QThread();

    QObject::connect(evWorkThread,SIGNAL(started()),evWork,SLOT(process()));
    evWork->moveToThread(evWorkThread);
    evWorkThread->start();
}

void MNode::initRecvThread(){
    this->recWork = new RecvQueueWorker(this->events,&(this->TIME));
    this->recWorkThread = new QThread();

    QObject::connect(recWorkThread,SIGNAL(started()),recWork,SLOT(process()));
    recWork->moveToThread(recWorkThread);
    recWorkThread->start();
}

void MNode::initSendThread(){
    this->senWork = new SendQueueWorker(this->events,&(this->TIME));
    this->senWorkThread = new QThread();

    QObject::connect(senWorkThread,SIGNAL(started()),senWork,SLOT(process()));
    senWork->moveToThread(senWorkThread);
    senWorkThread->start();
}

