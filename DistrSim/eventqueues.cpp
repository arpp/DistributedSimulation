#include "eventqueues.h"

EventQueues::EventQueues(QMap<int,QQueue<Event*> > evQueue, QQueue<EventData*> sendQueue, QList<NodeAbstract*> nodeList, QList<QList<QPair<NodeAbstract*,int> > > edgeList)
{
    this->evQueue = evQueue;
    this->sendQueue = sendQueue;
    this->nodeList = nodeList;
    this->edgeList = edgeList;

    QMap<int,QQueue<Event*> >::iterator iter;
    for(iter=evQueue.begin();iter!=evQueue.end();++iter)
    {
        safeTime[iter.key()] = 0;
    }
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
