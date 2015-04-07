#include "sendqueueworker.h"

#include <QThread>
#include <QDebug>
#include <QTime>

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

int SendQueueWorker::findDestMId(unsigned long srcNodeId, unsigned long destNodeId)
{
    QList<NodeAbstract*> nodeList = q->nodeList;

    for (int i = 0; i < nodeList.size(); ++i)
    {
        //Find srcNode in nodeList
        if(nodeList.at(i)->getNodeId() == srcNodeId)
        {
            QList<QPair<NodeAbstract*,int> > edges = (q->edgeList).at(i);
            for(int j = 0; j < edges.size(); ++j)
            {
                if(edges.at(j).first->getNodeId() == destNodeId)
                    return edges.at(j).second;
            }
        }
    }
}

void SendQueueWorker::process(){

    while(true){
        qDebug() << QTime::currentTime().toString() << "SendQueueWorker: Send process thread: "<<QThread::currentThreadId()<<"\n";

        //Dequeue an event if sendQueue is not empty
        sendQueueMutex->lock();
        if ((q->sendQueue).size() == 0)
            sendQueueNotEmpty->wait(sendQueueMutex);

        EventData* currentEvent = (q->sendQueue).dequeue();
        sendQueueMutex->unlock();

        QTcpSocket* socket;
        if(currentEvent->getType() == 0 || currentEvent->getType() == 1)//NULL or DEMAND Message
        {
            //Here destNodeId is the destMId
            socket = outSoc[currentEvent->getDestNodeId()];
        }
        else//General Message
        {
            unsigned long srcNodeId = currentEvent->getSrcNodeId();
            unsigned long destNodeId = currentEvent->getDestNodeId();
            int destMId = findDestMId(srcNodeId, destNodeId);
            socket = outSoc[destMId];
        }

        QDataStream st(socket);
        st<<(*currentEvent);
    }
}
