#include "mnode.h"

MNode::MNode()
{
    this->TIME=0;
}

void MNode::addNode(NodeAbstract* node){
    this->nodeList.append(node);
}

void MNode::addEdge(EdgeAbstract* edge, int sysId){
    NodeAbstract *src = edge->getSrc();
    QList<QPair<EdgeAbstract*,int> > temp;
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

