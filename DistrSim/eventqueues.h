#ifndef EVENTQUEUES_H
#define EVENTQUEUES_H

#include <QList>
#include <QPair>
#include <QMap>
#include <QQueue>
#include "event.h"

class EventQueues
{
public:
    EventQueues(QMap<int,QQueue<Event*> > evQueue, QQueue<Event*> sendQueue, QList<NodeAbstract*> nodeList, QList<QList<QPair<NodeAbstract*,int> > > edgeList);
    void addToEventQueue(Event* e);
    void addToSendQueue(Event* e);
    Event* getNextEvent();
    Event* removeSendQueue();

private:
    QMap<int, QQueue<Event*> > evQueue;

    QQueue<Event*> sendQueue;
    QList<NodeAbstract*> nodeList;
    QList<QList<QPair<NodeAbstract*,int> > > edgeList;
};

#endif // EVENTQUEUES_H
