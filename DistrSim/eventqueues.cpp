#include "eventqueues.h"

EventQueues::EventQueues(QMap<int,QQueue<Event*> > evQueue, QQueue<EventData*> sendQueue, QList<NodeAbstract*> nodeList, QList<QList<QPair<NodeAbstract*,int> > > edgeList)
{
    this->evQueue = evQueue;
    this->sendQueue = sendQueue;
    this->nodeList = nodeList;
    this->edgeList = edgeList;
}


void EventQueues::addToEventQueue(Event* e){

}

void EventQueues::addToSendQueue(EventData* e){
    this->sendQueue.enqueue(e);
}

Event* EventQueues::getNextEvent(){

}

EventData* EventQueues::removeSendQueue(){

}
