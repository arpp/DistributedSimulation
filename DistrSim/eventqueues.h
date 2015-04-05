#ifndef EVENTQUEUES_H
#define EVENTQUEUES_H

#include <QList>
#include <QPair>
#include <QQueue>
#include "eventabstract.h"

class EventQueues
{
public:
    EventQueues(QList<QQueue<EventAbstract*> > evQueue, QQueue<EventAbstract*> localQueue, QQueue<EventAbstract*> sendQueue, QList<NodeAbstract*> nodeList, QList<QList<QPair<EdgeAbstract*,int> > > edgeList);
    void addToEventQueue(EventAbstract* e);
    void addToSendQueue(EventAbstract* e);
    EventAbstract* getNextEvent();
    EventAbstract* removeSendQueue();

private:
    QList<QQueue<EventAbstract*> > evQueue;
    QQueue<EventAbstract*> localQueue;
    QQueue<EventAbstract*> sendQueue;
    QList<NodeAbstract*> nodeList;
    QList<QList<QPair<EdgeAbstract*,int> > > edgeList;
};

#endif // EVENTQUEUES_H
