#include "recvqsocketworker.h"
#include <QDebug>
#include "eventdata.h"
#include <QThread>
#include <QTime>
#include "createNetwork/blockreader.h"

RecvQSocketWorker::RecvQSocketWorker(EventQueues *q, unsigned long *t, QTcpSocket* incSoc, int m_id, int s_id,
                                     QMutex *evQueueMutex, QMutex *timeStampMutex, QWaitCondition *evQueueNotEmpty, QMutex *sendQueueMutex, QWaitCondition *sendQueueNotEmpty, QObject *parent) :
    QObject(parent)
{
    this->q = q;
    this->time = t;
    this->socket = incSoc;
    this->m_id = m_id;
    this->s_id = s_id;
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
        //New event received

        EventData *ev = new EventData(0,0,0,0);
//        QDataStream st(this->socket);

        BlockReader(this->socket).stream()>>(*ev);


        int type = ev->getType();
//        qDebug()<<"RecvProcessSocketWorker: "<<QThread::currentThreadId()<<" tom: "<<type<<"";


        if(type==0){
            //Null message
            unsigned long timeStampOtherMachine = ev->getTimestamp();
            q->safeTime[ev->getSrcNodeId()]=timeStampOtherMachine;

            QMap<int,QQueue<Event*> >::iterator it;
            int flag=0;
            unsigned long minTS=(*time);//ULONG_MAX
//            qDebug() << "num 0: " << q->evQueue[0].size();
//            qDebug() << "num 1: " << q->evQueue[1].size();

            this->evQueueMutex->lock();

            for(it=this->q->evQueue.begin();it!=this->q->evQueue.end();it++){
                if(!it.value().isEmpty()){
                     if(minTS>it.value().head()->getTimestamp()){
                         minTS=it.value().head()->getTimestamp();
                     }
                }
                else if(it.key()!=this->m_id){
//                     qDebug()<<"itkey"<<it.key();
                     if(minTS>this->q->safeTime.value(it.key())){
                         qDebug()<<minTS<<" "<<this->q->safeTime.value(it.key());
                         minTS=this->q->safeTime.value(it.key());
                         flag=1;
                     }
                }
            }
            qDebug()<<flag;
            if(flag==0)
                this->evQueueNotEmpty->wakeAll();
            this->evQueueMutex->unlock();
            qDebug()<<"RecvProcessSocketWorker: "<<QThread::currentThreadId()<<" nulmsg, tmeup: "<<timeStampOtherMachine<<"";
        }
        else if(type==1){
            //Demand message
            timeStampMutex->lock();
            (*time)++;
            *time = (*time)>(ev->getTimestamp() + 1)?(*time):(ev->getTimestamp() + 1);
            timeStampMutex->unlock();

            //Create NULL Message. Add to send queue.
            EventData *nullMessage = new EventData(*time+5, m_id, ev->getSrcNodeId(), 0);
            timeStampMutex->lock();
            (*time)+=5;
            timeStampMutex->unlock();

            qDebug()<<"RecvProcessSocketWorker: "<<QThread::currentThreadId()<<" dmdmsg, tmeup: "<<*time<<"";
            sendQueueMutex->lock();
            q->sendQueue.enqueue(nullMessage);
            sendQueueNotEmpty->wakeAll();
            sendQueueMutex->unlock();
        }
        else{
            //Write code to create EventData and Event and add Event to eventQueue at value m_id

            timeStampMutex->lock();
            (*time)++;
            *time = (*time)>(ev->getTimestamp() + 1)?(*time):(ev->getTimestamp() + 1);
            qDebug()<<"RecvProcessSocketWorker: "<<QThread::currentThreadId()<<" tstamp updated: "<<*time<<"";
            timeStampMutex->unlock();

            NodeAbstract* n = 0;
            for(int i=0;i<q->nodeList.size();++i)
            {
                if(q->nodeList.at(i)->getNodeId() == ev->getNodeId())
                    n = q->nodeList[i];
            }
            //Update timestamp of event
            ev->setTimestamp(*time);
            Event * newEvent = new Event(n, ev, q->nodeList, q->edgeList);
            qDebug()<<"RecvProcessSocketWorker: "<<QThread::currentThreadId()<<" nmlmsg, tmeup: "<<*time<<"";
            evQueueMutex->lock();
            q->evQueue[s_id].enqueue(newEvent);
//            q->evQueue.find(m_id).value().enqueue(newEvent);

//            qDebug() << "1";
            QMap<int,QQueue<Event*> >::iterator it;
            int flag=0;
            unsigned long minTS=(*time);//ULONG_MAX;
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

            qDebug() << "mid is : " << m_id;
            QList<int> emptyMNodes;
            int myFlag = 0;
            for(it=this->q->evQueue.begin();it!=this->q->evQueue.end();it++){
                if(it.value().isEmpty()){
                    if(it.key()==this->m_id)
                    {
                        qDebug() << "mehbfuej";
                        myFlag = 1;
                    }
                    else
                    {
                        qDebug() << "other";
                        emptyMNodes.append(it.key());
                    }
                }
            }

            qDebug() << "em" << emptyMNodes.size();
            if(myFlag == 1 && (emptyMNodes.size() == q->evQueue.size() - 2))
            {
                qDebug() << "empty send demand";
                foreach(int i,emptyMNodes){
                    //create a DEMAND msg for each i-th mnode and enqueue it in sendQueue
                    EventData *demand = new EventData(*(this->time),m_id,i,1);

                    this->sendQueueMutex->lock();
                    this->q->sendQueue.enqueue(demand);
                    this->sendQueueNotEmpty->wakeAll();
                    this->sendQueueMutex->unlock();
                }
            }

            qDebug() << "flag is:" << flag;
            if(flag == 0)
                evQueueNotEmpty->wakeAll();
            evQueueMutex->unlock();
//            qDebug() << "5";

            qDebug() << "num 0: " << q->evQueue[0].size();
            qDebug() << "num 1: " << q->evQueue[1].size();


        }
    }
}
