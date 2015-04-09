#include "recvqsocketworker.h"
#include <QDebug>
#include "eventdata.h"
#include <QThread>
#include <QTime>
#include "createNetwork/blockreader.h"

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
    qDebug()<< QTime::currentTime().toString()<<" RecvQSocketWorker: Receive process thread: "<<QThread::currentThreadId();

    while(true){

//        this->socket->waitForReadyRead(-1);
        //New event received

        EventData *ev = new EventData(0,0,0,0);
//        QDataStream st(this->socket);

        BlockReader(this->socket).stream()>>(*ev);

        timeStampMutex->lock();
        (*time)++;
        *time = (*time)>(ev->getTimestamp() + 1)?(*time):(ev->getTimestamp() + 1);
        timeStampMutex->unlock();

        int type = ev->getType();
        qDebug()<<"RecvProcessSocketWorker: socket::thread worker: "<<QThread::currentThreadId()<<" type of message: "<<type<<"";

        if(type==0){
            //Null message
            unsigned long timeStampOtherMachine = ev->getTimestamp();
            q->safeTime.find(ev->getSrcNodeId()).value() = timeStampOtherMachine;
        }
        else if(type==1){
            //Demand message
            //Create NULL Message. Add to send queue.
            EventData *nullMessage = new EventData(*time, m_id, ev->getSrcNodeId(), 0);
            sendQueueMutex->lock();
            q->sendQueue.enqueue(nullMessage);
            sendQueueNotEmpty->wakeAll();
            sendQueueMutex->unlock();
        }
        else{
            //Write code to create EventData and Event and add Event to eventQueue at value m_id

            NodeAbstract* n = 0;
            for(int i=0;i<q->nodeList.size();++i)
            {
                if(q->nodeList.at(i)->getNodeId() == ev->getNodeId())
                    n = q->nodeList.at(i);
            }
            //Update timestamp of event
            ev->setTimestamp(*time);
            Event * newEvent = new Event(n, ev, q->nodeList, q->edgeList);

            evQueueMutex->lock();
            q->evQueue[m_id].enqueue(newEvent);
//            q->evQueue.find(m_id).value().enqueue(newEvent);

            QMap<int,QQueue<Event*> >::iterator it;
            int flag=0;
            unsigned long minTS=ULONG_MAX;
            for(it=this->q->evQueue.begin();it!=this->q->evQueue.end();it++){
                if(!it.value().isEmpty()){
                     if(minTS>it.value().head()->getTimestamp()){
                         minTS=it.value().head()->getTimestamp();
                     }
                }
                else if(it.key()!=this->m_id){
                     if(minTS>this->q->safeTime.value(it.key())){
                         minTS=this->q->safeTime.value(it.key());
                         flag=1;
                     }
                }
            }

            QList<int> emptyMNodes;
            int myFlag = 0;
            for(it=this->q->evQueue.begin();it!=this->q->evQueue.end();it++){
                if(it.value().isEmpty()){
                    if(it.key()==this->m_id)
                        myFlag = 1;
                    else
                        emptyMNodes.append(it.key());
                }
            }

            if(myFlag == 1 && (emptyMNodes.size() == q->evQueue.size() - 2))
            {
                foreach(int i,emptyMNodes){
                    //create a DEMAND msg for each i-th mnode and enqueue it in sendQueue
                    EventData *demand = new EventData(*(this->time),m_id,i,1);

                    this->sendQueueMutex->lock();
                    this->q->sendQueue.enqueue(demand);
                    this->sendQueueNotEmpty->wakeAll();
                    this->sendQueueMutex->unlock();
                }
            }


            if(flag == 0)
                evQueueNotEmpty->wakeAll();
            evQueueMutex->unlock();
        }
    }
}
