#include "sendqueueworker.h"

SendQueueWorker::SendQueueWorker(EventQueues *q, QObject *parent) :
    QObject(parent)
{
    this->q = q;
}

void SendQueueWorker::process(){

}
