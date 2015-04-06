#ifndef EVENTPROCESSWORKER_H
#define EVENTPROCESSWORKER_H

#include "eventqueues.h"

#include <QObject>

class EventProcessWorker : public QObject
{
    Q_OBJECT
public:
    explicit EventProcessWorker(EventQueues *q, unsigned long *t, QObject *parent = 0);

signals:

public slots:

private slots:
    void process();             // This will take elements from the evQueue and put elements in send queue need to use QWaitCondition

private:
    EventQueues *q;
    unsigned long *time;
};

#endif // EVENTPROCESSWORKER_H
