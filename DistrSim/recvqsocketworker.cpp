#include "recvqsocketworker.h"
#include <QDebug>
#include "eventdata.h"
#include <QThread>

RecvQSocketWorker::RecvQSocketWorker(EventQueues *q, unsigned long *t, QTcpSocket* incSoc, int m_id,
                                     QMutex *evQueueMutex, QMutex *timeStampMutex, QWaitCondition *evQueueNotEmpty, QObject *parent) :
    QObject(parent)
{
    this->q = q;
    this->time = t;
    this->socket = incSoc;
    this->m_id = m_id;
    this->evQueueMutex=evQueueMutex;
    this->timeStampMutex=timeStampMutex;
    this->evQueueNotEmpty=evQueueNotEmpty;
}

void RecvQSocketWorker::process(){
//The code to listen and add to the queues go here
    qDebug()<<"recv process thread worker: "<<QThread::currentThreadId()<<"\n";

    while(true){
        this->socket->waitForReadyRead(-1);
        //New event received
        timeStampMutex->lock();
        (*time)++;
        timeStampMutex->unlock();

        EventData *ev = new EventData(0,0,0,0);
        QDataStream st(this->socket);
        st>>(*ev);

        int type = ev->getType();
        if(type==0){
            //Null message
            unsigned long timeStampOtherMachine = ev->getTimestamp();
        }
        else if(type==1){
            //Demand message
            //TODO:Do we increment timestamp for demand message??
            unsigned long timeStampToSend = *time;
        }
        else{
            //Write code to create EventData and Event and add Event to eventQueue at value m_id

            NodeAbstract* n = 0;
            for(int i=0;i<q->nodeList.size();++i)
            {
                if(q->nodeList.at(i)->getNodeId() == ev->getDestNodeId())
                    n = q->nodeList.at(i);
            }
            Event * newEvent = new Event(n, ev);

            evQueueMutex->lock();
            q->evQueue.find(m_id).value().enqueue(newEvent);
            evQueueNotEmpty->wakeAll();
            evQueueMutex->unlock();
        }
    }
}
