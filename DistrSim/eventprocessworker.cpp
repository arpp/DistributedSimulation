#include "eventprocessworker.h"

#include<QThread>
#include<QDataStream>
#include<QTime>
#include<QDebug>
#include<QCoreApplication>
#include "examplenode.h"
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
    qDebug()<< QTime::currentTime().toString()<<" EVENT_PROCESS_WORKER: Event process thread: "<<QThread::currentThreadId();

    while(true){
       //search whether any queue is empty then we will
       QMap<int,QQueue<Event*> >::iterator it;
       Event *event;
       QList<int> l;
       int flag=0;
       int count=0;
       unsigned long minTS=(*time);//ULONG_MAX;
       this->evQueueMutex->lock();
       for(it=this->q->evQueue.begin();it!=this->q->evQueue.end();it++){
           if(!it.value().isEmpty()){
                if(minTS>it.value().head()->getTimestamp()){
                    minTS=it.value().head()->getTimestamp();
                }
           }
       }
       for(it=this->q->evQueue.begin();it!=this->q->evQueue.end();it++){
           if(!it.value().isEmpty()){

           }
           else if(it.key()!=this->m_id){
                if(minTS>this->q->safeTime.value(it.key())){
                    l.append(it.key());
                    flag=1;
                }
                count++;
           }
           else if(it.key() == this->m_id)
           {
               count++;
           }
       }

       if(count==this->q->evQueue.size()){
            this->evQueueNotEmpty->wait(this->evQueueMutex);
//           continue;
       }
       else if(flag==1){
            foreach(int i,l){
                //create a DEMAND msg for each i-th mnode and enqueue it in sendQueue
                EventData *demand = new EventData(*(this->time),m_id,i,1);

                this->sendQueueMutex->lock();
                this->q->sendQueue.enqueue(demand);
                this->sendQueueNotEmpty->wakeAll();
                this->sendQueueMutex->unlock();
            }
            this->evQueueNotEmpty->wait(this->evQueueMutex);
       }
       this->evQueueMutex->unlock();

       this->evQueueMutex->lock();
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
//       event=this->q->evQueue.find(k).value().dequeue();
       if(k==-1)
       {
           evQueueMutex->unlock();
           continue;
       }
       else if(q->evQueue[k].isEmpty())
       {
           evQueueMutex->unlock();
           continue;
       }

       event = q->evQueue[k].dequeue();
       if(q->evQueue[k].isEmpty()){
           q->safeTime[k]=(q->safeTime[k]>event->getTimestamp()+1)?q->safeTime[k]:event->getTimestamp()+1;
       }
       this->evQueueMutex->unlock();

       qDebug()<< QTime::currentTime().toString()<<" EVENT_PROCESS_WORKER: Event process thread: "<<QThread::currentThreadId()<<"Processed event timestamp: "<<event->getTimestamp()<<"";

       QList<EventData*> genEvents = event->runEvent();

       int closeFlag=0;
       for(int i=0;i<genEvents.size();i++){
           int lfl=0;
           NodeAbstract *nabs;
           EventData* d = genEvents[i];
           if(d->getType()==-1){
                this->sendQueueMutex->lock();
                this->q->sendQueue.enqueue(d);
                this->sendQueueNotEmpty->wakeAll();
                this->sendQueueMutex->unlock();
                closeFlag=1;
                break;
           }
           for(int j=0;j<this->q->nodeList.size();j++){
               if(this->q->nodeList.at(j)->getNodeId()==d->getNodeId()){
                   nabs=this->q->nodeList.at(j);
                   lfl=1;
                   break;
               }
           }
           qDebug()<<"lfl="<<lfl;
           if(lfl==1){
               //add locally
               this->timeStampMutex->lock();
               (*(this->time))++;
               qDebug() << "local timestamp is : " << *time;
               d->setTimestamp(*time);
               this->timeStampMutex->unlock();

               this->evQueueMutex->lock();
               qDebug()<<"to build event";
               Event *ev = new Event(nabs,d,q->nodeList, q->edgeList);
               qDebug()<<"event built";
               q->evQueue[m_id].enqueue((ev));
//               this->q->evQueue.find(this->m_id).value().enqueue(ev);
               this->evQueueMutex->unlock();
           }
           else{
               //add to send queue
               this->sendQueueMutex->lock();
               this->q->sendQueue.enqueue(d);
               this->sendQueueNotEmpty->wakeAll();
               this->sendQueueMutex->unlock();
           }
       }
       if(closeFlag==1)
           break;
    }

    QTextStream(stdout)<<"---------------------------------------------------------------------------------------------\n";
    for(int i=0;i<this->q->nodeList.size();i++){
        exampleNode* enode = dynamic_cast<exampleNode*>(q->nodeList.at(i));
        QTextStream(stdout)<< q->nodeList.at(i)->getNodeId() <<" "<< enode->getVisitCount()<<"\n";
    }
    QThread::sleep(10);
    QCoreApplication::quit();
}
