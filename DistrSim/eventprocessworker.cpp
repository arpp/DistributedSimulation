#include "eventprocessworker.h"

#include<QThread>
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
    qDebug()<<"Event process thread: "<<QThread::currentThreadId()<<"\n"<<*(this->time)<<"\n";


}
