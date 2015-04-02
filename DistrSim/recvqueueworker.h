#ifndef RECVQUEUEWORKER_H
#define RECVQUEUEWORKER_H

#include "eventqueues.h"

#include <QObject>

class RecvQueueWorker : public QObject
{
    Q_OBJECT
public:
    explicit RecvQueueWorker(EventQueues *q, QObject *parent = 0);

signals:

public slots:

private slots:
    void process();

private:
    EventQueues *q;
};

#endif // RECVQUEUEWORKER_H
