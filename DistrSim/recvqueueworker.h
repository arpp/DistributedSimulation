#ifndef RECVQUEUEWORKER_H
#define RECVQUEUEWORKER_H

#include "eventqueues.h"

#include <QObject>
#include <QTcpSocket>

class RecvQueueWorker : public QObject
{
    Q_OBJECT
public:
    explicit RecvQueueWorker(EventQueues *q, unsigned long *t, QList<QTcpSocket*> incSoc, QObject *parent = 0);

signals:

public slots:

private slots:
    void process();

private:
    EventQueues *q;
    QList<QTcpSocket*> incSoc;
    unsigned long *time;
};

#endif // RECVQUEUEWORKER_H