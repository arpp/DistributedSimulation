#include "eventprocessworker.h"

#include<QThread>
#include<QDebug>

EventProcessWorker::EventProcessWorker(EventQueues *q, unsigned long *t, QObject *parent) :
    QObject(parent)
{
    this->q = q;
    this->time=t;
}

void EventProcessWorker::process(){
    (*(this->time))++;
    qDebug()<<"Event process thread: "<<QThread::currentThreadId()<<"\n"<<*(this->time)<<"\n";


}
