#ifndef EVENTQUEUES_H
#define EVENTQUEUES_H

#include <QList>
#include <QPair>
#include <QMap>
#include <QQueue>
#include "eventabstract.h"

class EventQueues
{
public:
    EventQueues(QMap<int,QQueue<EventAbstract*> > evQueue, QQueue<EventAbstract*> sendQueue, QList<NodeAbstract*> nodeList, QList<QList<QPair<NodeAbstract*,int> > > edgeList);
    void addToEventQueue(EventAbstract* e);
    void addToSendQueue(EventAbstract* e);
    EventAbstract* getNextEvent();
    EventAbstract* removeSendQueue();

private:
    QMap<int, QQueue<EventAbstract*> > evQueue;

    QQueue<EventAbstract*> sendQueue;
    QList<NodeAbstract*> nodeList;
    QList<QList<QPair<NodeAbstract*,int> > > edgeList;
};

#endif // EVENTQUEUES_H
