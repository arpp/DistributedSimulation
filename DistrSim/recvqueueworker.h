#ifndef RECVQUEUEWORKER_H
#define RECVQUEUEWORKER_H

#include "eventqueues.h"

#include <QObject>

class RecvQueueWorker : public QObject
{
    Q_OBJECT
public:
    explicit RecvQueueWorker(EventQueues *q, unsigned long *t, QObject *parent = 0);

signals:

public slots:

private slots:
    void process();

private:
    EventQueues *q;
    unsigned long *time;
};

#endif // RECVQUEUEWORKER_H
