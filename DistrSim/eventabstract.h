#ifndef EVENTABSTRACT_H
#define EVENTABSTRACT_H

#include "nodeabstract.h"
#include "edgeabstract.h"
#include <QList>

class EventAbstract
{
public:
    EventAbstract(NodeAbstract *n);
    virtual QList<EventAbstract*> runEvent()=0;
    void updateTimestamp(unsigned long ts);

private:
    unsigned long timestamp;
    NodeAbstract *node;
};

#endif // EVENTABSTRACT_H
