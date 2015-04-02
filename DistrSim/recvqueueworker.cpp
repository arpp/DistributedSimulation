#include "recvqueueworker.h"

RecvQueueWorker::RecvQueueWorker(EventQueues *q, QObject *parent) :
    QObject(parent)
{
    this->q = q;
}

void RecvQueueWorker::process(){

}
