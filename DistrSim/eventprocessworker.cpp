#include "eventprocessworker.h"

#include<QThread>
#include<QTime>
#include<QDebug>
#include "limits.h"

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
       QEvent *event;
       QList<int> l;
       int flag=0;
       this->evQueueMutex->lock();
       for(it=this->q->evQueue.begin();it!=this->q->evQueue.end();it++){
           if(it.value().isEmpty()){
               if(it.key()!=this->m_id){
                    l.append(it.key());
                    flag=1;
               }
           }
       }
       if(flag==1){
            foreach(int i,l){
                //create a DEMAND msg for each i-th mnode and enqueue it in sendQueue
                EventData *demand = new EventData(this->time,i,i,1);
                this->q->sendQueue.enqueue(demand);
                this->sendQueueMutex->lock();
                this->sendQueueNotEmpty->wakeAll();
                this->sendQueueMutex->unlock();
            }
            this->evQueueNotEmpty->wait(this->evQueueMutex);
       }
       else{
           unsigned long maxts=ULONG_MAX;
           int k=-1;
           for(it=this->q->evQueue.begin();it!=this->q->evQueue.end();it++){
                 if(!it.value().isEmpty()){
                    if(it.value().front()->getTimestamp()<maxts){
                        maxts=it.value().front()->getTimestamp();
                        k=it.key();
                    }
                 }
           }
           event=this->q->evQueue.value(k).dequeue();
       }
       this->evQueueMutex->unlock();

    }

}
