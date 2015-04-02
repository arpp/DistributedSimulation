#include "sendqueueworker.h"

SendQueueWorker::SendQueueWorker(EventQueues *q, unsigned long *t, QObject *parent) :
    QObject(parent)
{
    this->q = q;
    this->time=t;
}

void SendQueueWorker::process(){

}
