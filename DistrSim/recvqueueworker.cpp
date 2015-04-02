#include "recvqueueworker.h"

RecvQueueWorker::RecvQueueWorker(EventQueues *q, unsigned long *t, QObject *parent) :
    QObject(parent)
{
    this->q = q;
    this->time=t;
}

void RecvQueueWorker::process(){

}
