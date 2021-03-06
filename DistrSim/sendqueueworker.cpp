#include "sendqueueworker.h"

#include <QThread>
#include <QDebug>
#include <QTime>
#include "createNetwork/blockwriter.h"
#include <QHostAddress>

SendQueueWorker::SendQueueWorker(EventQueues *q, unsigned long *t, QMap<int,QTcpSocket*> outSoc, int m_id,
                                 QMutex *sendQueueMutex, QMutex *timeStampMutex, QWaitCondition *sendQueueNotEmpty, QObject *parent) :
    QObject(parent)
{
    this->q = q;
    this->time=t;
    this->outSoc=outSoc;
    this->m_id=m_id;
    this->sendQueueMutex=sendQueueMutex;
    this->timeStampMutex=timeStampMutex;
    this->sendQueueNotEmpty=sendQueueNotEmpty;
}

int SendQueueWorker::findDestMId(unsigned long srcNodeId, unsigned long nodeId)
{
    QList<NodeAbstract*> nodeList = q->nodeList;

    for (int i = 0; i < nodeList.size(); ++i)
    {
        //Find srcNode in nodeList
        if(nodeList.at(i)->getNodeId() == srcNodeId)
        {
//            qDebug() << "node is : " << srcNodeId << "";
            QList<QPair<NodeAbstract*,int> > edges = (q->edgeList).at(i);
            for(int j = 0; j < edges.size(); ++j)
            {
//                qDebug() << edges.at(j).first->getNodeId() << " " << edges.at(j).second;
                if(edges.at(j).first->getNodeId() == nodeId)                    
                    return edges.at(j).second;
            }
        }
    }
    qDebug() << "ye ho gaya";
    return this->m_id;//Just to be safe
}

void SendQueueWorker::process(){
    qDebug() << QTime::currentTime().toString() << "SendQueueWorker: Send process thread: "<<QThread::currentThreadId();

    while(true){

        //Dequeue an event if sendQueue is not empty
        sendQueueMutex->lock();
        if ((q->sendQueue).size() == 0)
            sendQueueNotEmpty->wait(sendQueueMutex);
        sendQueueMutex->unlock();

        sendQueueMutex->lock();
        EventData* currentEvent = (q->sendQueue).dequeue();//Consume event
        sendQueueMutex->unlock();

        if(currentEvent->getType()==-1){
            QMap<int,QTcpSocket*>::iterator iter;
            for(iter=this->outSoc.begin();iter!=this->outSoc.end();++iter){
                BlockWriter(iter.value()).stream()<<(*currentEvent);
                (iter.value())->waitForBytesWritten(-1);
            }
            break;
        }



//        qDebug() << "SendQueueWorker: Send process thread: "<<QThread::currentThreadId()<<" Type: "<<currentEvent->getType()<<"\n";
        QTcpSocket* socket;
        if(currentEvent->getType() == 0 || currentEvent->getType() == 1)//NULL or DEMAND Message
        {
            //Here destNodeId is the destMId
            socket = outSoc[currentEvent->getNodeId()];
        }
        else//General Message
        {
            unsigned long srcNodeId = currentEvent->getSrcNodeId();
            unsigned long nodeId = currentEvent->getNodeId();
            int destMId = findDestMId(srcNodeId, nodeId);
            socket = outSoc[destMId];

            timeStampMutex->lock();
            (*time)++;
            currentEvent->setTimestamp(*time);
            timeStampMutex->unlock();

        }
        qDebug() << "SendQueueWorker: Send process thread: "<<QThread::currentThreadId()<<" type = "<<currentEvent->getType()<<" timestamp = "<<currentEvent->getTimestamp();
        qDebug() << "socket peer : " << socket->peerAddress().toString();
        BlockWriter(socket).stream()<<(*currentEvent);
        socket->waitForBytesWritten(-1);
//        QDataStream st(socket);
//        st<<(*currentEvent);
    }
}
