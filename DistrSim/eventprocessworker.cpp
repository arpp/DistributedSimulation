#include "eventprocessworker.h"

#include<QThread>
#include<QDebug>

EventProcessWorker::EventProcessWorker(EventQueues *q, unsigned long *t, int m_id, QObject *parent) :
    QObject(parent)
{
    this->q = q;
    this->time=t;
    this->m_id=m_id;
}

void EventProcessWorker::process(){
    (*(this->time))++;
    qDebug()<<"Event process thread: "<<QThread::currentThreadId()<<"\n"<<*(this->time)<<"\n";


}
