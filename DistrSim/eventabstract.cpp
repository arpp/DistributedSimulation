#include "eventabstract.h"

EventAbstract::EventAbstract(NodeAbstract *n, unsigned long ts)
{
    this->node=n;
    this->timestamp=ts;
}

unsigned long EventAbstract::getNodeID(){
    return this->node->getNodeId();
}

unsigned long EventAbstract::getTimestamp(){
    return this->timestamp;
}
