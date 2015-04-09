#ifndef EVENT_H
#define EVENT_H

#include "nodeabstract.h"
#include "edgeabstract.h"
#include "eventdata.h"
#include <QList>

class Event
{
public:
    Event(NodeAbstract *n, EventData *ev, QList<NodeAbstract*> nodeList, QList<QList<QPair<NodeAbstract*,int> > > edgeList);
    QList<EventData> runEvent();
    unsigned long getNodeID();
    unsigned long getTimestamp();

    QList<NodeAbstract*> nodeList;
    QList<QList<QPair<NodeAbstract*,int> > > edgeList;

private:
    NodeAbstract *node;
    EventData *eventData;

};

#endif // EVENT_H
