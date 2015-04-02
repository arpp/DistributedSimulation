#ifndef EVENTPROCESSWORKER_H
#define EVENTPROCESSWORKER_H

#include "eventqueues.h"

#include <QObject>

class EventProcessWorker : public QObject
{
    Q_OBJECT
public:
    explicit EventProcessWorker(QObject *parent = 0);

signals:

public slots:

private:
    EventQueues *q;
};

#endif // EVENTPROCESSWORKER_H
