#include "eventprocessworker.h"

EventProcessWorker::EventProcessWorker(EventQueues *q, unsigned long *t, QObject *parent) :
    QObject(parent)
{
    this->q = q;
    this->time=t;
}

void EventProcessWorker::process(){

}
