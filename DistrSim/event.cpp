#include "event.h"

Event::Event(NodeAbstract *n, EventData *ev)
{
    this->node=n;
    this->eventData=ev;
}

unsigned long Event::getNodeID(){
    return this->node->getNodeId();
}

QList<EventData> Event::runEvent()
{

}
