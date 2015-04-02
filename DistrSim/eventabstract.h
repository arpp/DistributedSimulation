#ifndef EVENTABSTRACT_H
#define EVENTABSTRACT_H

#include "nodeabstract.h"
#include "edgeabstract.h"
#include <QList>

class EventAbstract
{
public:
    EventAbstract(NodeAbstract *n, unsigned long ts);
    virtual QList<EventAbstract*> runEvent()=0;
    long int getNodeID();
//    void updateTimestamp(unsigned long ts);
    unsigned long getTimestamp();

private:
    unsigned long timestamp;
    NodeAbstract *node;
};

#endif // EVENTABSTRACT_H
