#ifndef EVENTABSTRACT_H
#define EVENTABSTRACT_H

#include "nodeabstract.h"
#include "edgeabstract.h"

class EventAbstract
{
public:
    EventAbstract();
    virtual void runEvent(NodeAbstract *node)=0;

private:

};

#endif // EVENTABSTRACT_H
