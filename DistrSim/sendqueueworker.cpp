#include "sendqueueworker.h"

#include <QThread>
#include <QDebug>

SendQueueWorker::SendQueueWorker(EventQueues *q, unsigned long *t, QList<QTcpSocket*> outSoc, QObject *parent) :
    QObject(parent)
{
    this->q = q;
    this->time=t;
    this->outSoc=outSoc;
}

void SendQueueWorker::process(){
    qDebug()<<"Send process thread: "<<QThread::currentThreadId()<<"\n";
}
