#include "eventprocessworker.h"

EventProcessWorker::EventProcessWorker(EventQueues *q, QObject *parent) :
    QObject(parent)
{
    this->q = q;
}

void EventProcessWorker::process(){

}
