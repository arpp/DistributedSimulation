#ifndef EVENTQUEUES_H
#define EVENTQUEUES_H

#include <QList>
#include <QQueue>
#include "eventabstract.h"

class EventQueues
{
public:
    EventQueues();
    void addToEventQueue(EventAbstract* e);
    void addToSendQueue(EventAbstract* e);
    EventAbstract* getNextEvent();
    EventAbstract* removeSendQueue();

private:
    QList<QQueue<EventAbstract*> > evQueue;
    QQueue<EventAbstract*> localQueue;
    QQueue<EventAbstract*> sendQueue;
};

#endif // EVENTQUEUES_H
