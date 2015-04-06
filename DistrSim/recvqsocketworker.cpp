#include "recvqsocketworker.h"
#include <QDebug>
#include <QThread>

RecvQSocketWorker::RecvQSocketWorker(EventQueues *q, unsigned long *t, QTcpSocket* incSoc, QObject *parent) :
    QObject(parent)
{
    this->q = q;
    this->time = t;
    this->socket = incSoc;
}

void RecvQSocketWorker::process(){
//The code to listen and add to the queues go here
    qDebug()<<"recv process thread worker: "<<QThread::currentThreadId()<<"\n";
}
