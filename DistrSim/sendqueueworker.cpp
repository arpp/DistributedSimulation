#include "sendqueueworker.h"

#include <QThread>
#include <QDebug>

SendQueueWorker::SendQueueWorker(EventQueues *q, unsigned long *t, QMap<int,QTcpSocket*> outSoc, int m_id, QObject *parent) :
    QObject(parent)
{
    this->q = q;
    this->time=t;
    this->outSoc=outSoc;
    this->m_id=m_id;
}

void SendQueueWorker::process(){
    qDebug()<<"Send process thread: "<<QThread::currentThreadId()<<"\n";
}
