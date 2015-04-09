#include "recvqsocketworker.h"
#include <QDebug>
#include "eventdata.h"
#include <QThread>

RecvQSocketWorker::RecvQSocketWorker(EventQueues *q, unsigned long *t, QTcpSocket* incSoc, int m_id,
                                     QMutex *evQueueMutex, QMutex *timeStampMutex, QWaitCondition *evQueueNotEmpty, QMutex *sendQueueMutex, QWaitCondition *sendQueueNotEmpty, QObject *parent) :
    QObject(parent)
{
    this->q = q;
    this->time = t;
    this->socket = incSoc;
    this->m_id = m_id;
    this->evQueueMutex=evQueueMutex;
    this->timeStampMutex=timeStampMutex;
    this->evQueueNotEmpty=evQueueNotEmpty;
    this->sendQueueMutex = sendQueueMutex;
    this->sendQueueNotEmpty = sendQueueNotEmpty;
}

void RecvQSocketWorker::process(){
//The code to listen and add to the queues go here
    qDebug()<<"recv process thread worker: "<<QThread::currentThreadId()<<"\n";

    while(true){
        this->socket->waitForReadyRead(-1);
        //New event received

        EventData *ev = new EventData(0,0,0,0);
        QDataStream st(this->socket);
        st>>(*ev);

        int type = ev->getType();
        if(type==0){
            //Null message
            unsigned long timeStampOtherMachine = ev->getTimestamp();
            q->safeTime.find(ev->getSrcNodeId()).value() = timeStampOtherMachine;
        }
        else if(type==1){
            //Demand message
            //TODO:Do we increment timestamp for demand message??
            //Create NULL Message. Add to send queue.
            EventData *nullMessage = new EventData(*time, m_id, ev->getSrcNodeId(), 0);
            sendQueueMutex->lock();
            q->sendQueue.enqueue(nullMessage);
            sendQueueNotEmpty->wakeAll();
            sendQueueMutex->unlock();
        }
        else{
            //Write code to create EventData and Event and add Event to eventQueue at value m_id

            timeStampMutex->lock();
            (*time)++;
            ev->setTimestamp(*time);
            timeStampMutex->unlock();

            NodeAbstract* n = 0;
            for(int i=0;i<q->nodeList.size();++i)
            {
                if(q->nodeList.at(i)->getNodeId() == ev->getNodeId())
                    n = q->nodeList.at(i);
            }
            //Update timestamp of event
            Event * newEvent = new Event(n, ev);

            evQueueMutex->lock();
            q->evQueue.find(m_id).value().enqueue(newEvent);
            evQueueNotEmpty->wakeAll();
            evQueueMutex->unlock();
        }
    }
}
