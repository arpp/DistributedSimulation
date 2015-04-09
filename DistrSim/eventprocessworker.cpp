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
       Event *event;
       QList<int> l;
       int flag=0;
       int count=0;
       unsigned long minTS=ULONG_MAX;
       this->evQueueMutex->lock();
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
                count++;
                l.append(it.key());
           }
       }
       if(count==this->q->evQueue.size()-1){
            this->evQueueNotEmpty->wait(this->evQueueMutex);
       }
       else if(flag==1){
            foreach(int i,l){
                //create a DEMAND msg for each i-th mnode and enqueue it in sendQueue
                EventData *demand = new EventData(*(this->time),i,i,1);

                this->sendQueueMutex->lock();
                this->q->sendQueue.enqueue(demand);
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
           event=this->q->evQueue.find(k).value().dequeue();
       }
       this->evQueueMutex->unlock();

       QList<EventData> genEvents = event->runEvent();
       for(int i=0;i<genEvents.size();i++){
           int lfl=0;
           NodeAbstract *nabs;
           EventData d = genEvents[i];
           for(int j=0;j<this->q->nodeList.size();j++){
               if(this->q->nodeList[j]->getNodeId()==d.getNodeId()){
                   nabs=this->q->nodeList[j];
                   lfl=1;
                   break;
               }
           }
           if(lfl==1){
               //add locally
               this->evQueueMutex->lock();
               this->timeStampMutex->lock();
               (*(this->time))++;
               d.setTimestamp(*time);
               this->timeStampMutex->unlock();
               Event *ev = new Event(nabs,&d);
               this->q->evQueue.find(this->m_id).value().enqueue(ev);
               this->evQueueMutex->unlock();
           }
           else{
               //add to send queue
               this->sendQueueMutex->lock();
               this->q->sendQueue.enqueue(&d);
               this->sendQueueNotEmpty->wakeAll();
               this->sendQueueMutex->unlock();
           }
       }
    }

}
