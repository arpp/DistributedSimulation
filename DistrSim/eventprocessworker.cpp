#include "eventprocessworker.h"

#include<QThread>
#include<QTime>
#include<QDebug>

EventProcessWorker::EventProcessWorker(EventQueues *q, unsigned long *t, int m_id, QMutex *evQueueMutex, QMutex *sendQueueMutex, QMutex *timeStampMutex, QWaitCondition *evQueueNotEmpty, QWaitCondition *sendQueueNotEmpty, QObject *parent) :
    QObject(parent)
{
    this->q = q;
    this->time=t;
    this->m_id=m_id;
    this->evQueueMutex=evQueueMutex;
    this->sendQueueMutex=sendQueueMutex;
    this->timeStampMutex=timeStampMutex;
    this->evQueueNotEmpty=evQueueNotEmpty;
    this->sendQueueNotEmpty=sendQueueNotEmpty;
}

void EventProcessWorker::process(){
//    (*(this->time))++;
    qDebug()<< QTime::currentTime().toString()<<" EVENT_PROCESS_WORKER: Event process thread: "<<QThread::currentThreadId()<<"\n";

    while(true){
        //search whether any queue is empty then we will
       QMap<int,QQueue<Event*> >::iterator it;
       QList<int> l;
       this->evQueueMutex->lock();
       for(it=this->q->evQueue.begin();it!=this->q->evQueue.end();it++){
           if(it.value().isEmpty()){

           }
       }
       this->evQueueMutex->unlock();
    }

}
