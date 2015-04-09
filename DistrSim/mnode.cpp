#include "mnode.h"
#include <QPair>
#include <QDebug>
#include <QString>
#include <QHostAddress>

MNode::MNode(QString configFile)
{
    this->TIME=0;
    this->configFile = configFile;
    this->nodeList = QList<NodeAbstract*>();
    this-> edgeList = QList<QList<QPair<NodeAbstract*,int> > >();
}

int MNode::getMId(){
    return this->m_id;
}

void MNode::addNode(NodeAbstract* node){
    this->nodeList.append(node);
    this->nodeIdToIndex[node->getNodeId()] = this->nodeList.count()-1;

    QList<QPair<NodeAbstract*,int> > temp;
    this->edgeList.append(temp);
}

void MNode::addEdge(EdgeAbstract* edge, unsigned long sysId){
    NodeAbstract *src = edge->getSrc();
    unsigned long index = this->nodeIdToIndex[src->getNodeId()];
    QPair<NodeAbstract*, unsigned long> nodeSysPair;
    nodeSysPair.first = edge->getDst();
    nodeSysPair.second = sysId;

    (this->edgeList[index]).append(nodeSysPair);
}

void MNode::print(){
    //printf adjacency list

    for(int i=0; i<this->edgeList.count(); i++)
    {
        QDebug debug = qDebug();
        debug<<nodeList[i]->getNodeId()<<":";
        for(int j=0; j<this->edgeList[i].count(); j++)
        {
            debug<<" "<<this->edgeList[i][j].first->getNodeId();
        }
    }
}

void MNode::initConnection()
{
    connector c(this->configFile);
    c.begin();
    this->incomingConnection = c.getReceivers();
    this->outgoingConnection = c.getSenders();

//    QMap<int, QTcpSocket*>::iterator iter;
//    for(iter=incomingConnection.begin();iter!=incomingConnection.end();++iter)
//        qDebug()<<iter.key() << ": " << iter.value()->peerAddress().toString();

//    for(iter=outgoingConnection.begin();iter!=outgoingConnection.end();++iter)
//        qDebug()<<iter.key() << ": " << iter.value()->peerAddress().toString();

    this->m_id = c.getOwnID();
}

void MNode::transferFiles()
{
    FileShare fs;
    fs.sync("nodepartition", this->m_id, 0, this->incomingConnection, this->outgoingConnection);
    fs.sync("edgepartition", this->m_id, 0, this->incomingConnection, this->outgoingConnection);
}

void MNode::initTransfer()
{
    initConnection();
    transferFiles();
}

void MNode::initQueues()
{
    QMap<int,QQueue<Event*> > evQueue = QMap<int,QQueue<Event*> >();
    QQueue<EventData*> sendQueue = QQueue<EventData*>();
    this->events = new EventQueues(evQueue, sendQueue, this->nodeList, this->edgeList);
}

void MNode::beginSimulation(){

    this->evQueueMutex = new QMutex();
    this->sendQueueMutex = new QMutex();
    this->timeStampMutex = new QMutex();
    this->evQueueNotEmpty = new QWaitCondition();
    this->sendQueueNotEmpty = new QWaitCondition();

    initProcessQueueThread();
    initRecvThread();
    initSendThread();
}

void MNode::initProcessQueueThread(){
    this->evWork = new EventProcessWorker(this->events,&(this->TIME),this->m_id,this->evQueueMutex,this->sendQueueMutex,this->timeStampMutex,this->evQueueNotEmpty,this->sendQueueNotEmpty);
    this->evWorkThread = new QThread();

    QObject::connect(evWorkThread,SIGNAL(started()),evWork,SLOT(process()));
    evWork->moveToThread(evWorkThread);
    evWorkThread->start();
}

void MNode::initRecvThread(){
    this->recWork = new RecvQueueWorker(this->events,&(this->TIME),this->incomingConnection, this->m_id,this->evQueueMutex,this->timeStampMutex,this->evQueueNotEmpty, this->sendQueueMutex, this->sendQueueNotEmpty);
    this->recWorkThread = new QThread();

    QObject::connect(recWorkThread,SIGNAL(started()),recWork,SLOT(process()));
    recWork->moveToThread(recWorkThread);
    recWorkThread->start();
}

void MNode::initSendThread(){
    this->senWork = new SendQueueWorker(this->events,&(this->TIME),this->outgoingConnection, this->m_id,this->sendQueueMutex, this->timeStampMutex, this->sendQueueNotEmpty);
    this->senWorkThread = new QThread();

    QObject::connect(senWorkThread,SIGNAL(started()),senWork,SLOT(process()));
    senWork->moveToThread(senWorkThread);
    senWorkThread->start();
}

