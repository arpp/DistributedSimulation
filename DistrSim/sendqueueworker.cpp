#include "sendqueueworker.h"

#include <QThread>
#include <QDebug>

SendQueueWorker::SendQueueWorker(EventQueues *q, unsigned long *t, QObject *parent) :
    QObject(parent)
{
    this->q = q;
    this->time=t;
}

void SendQueueWorker::process(){
    qDebug()<<"Send process thread: "<<QThread::currentThreadId()<<"\n";
}
