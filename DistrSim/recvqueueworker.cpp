#include "recvqueueworker.h"

#include <QDebug>
#include <QThread>

RecvQueueWorker::RecvQueueWorker(EventQueues *q, unsigned long *t, QList<QTcpSocket*> incSoc, QObject *parent) :
    QObject(parent)
{
    this->q = q;
    this->time=t;
    this->incSoc=incSoc;

}

void RecvQueueWorker::process(){
    (*(this->time))++;
    qDebug()<<"recv process thread: "<<QThread::currentThreadId()<<"\n"<<*(this->time)<<"\n";
}
