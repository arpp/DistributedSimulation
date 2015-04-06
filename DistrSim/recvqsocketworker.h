#ifndef RECVQSOCKETWORKER_H
#define RECVQSOCKETWORKER_H

#include <QObject>
#include <QTcpSocket>
#include "eventqueues.h"

class RecvQSocketWorker : public QObject
{
    Q_OBJECT
public:
    explicit RecvQSocketWorker(EventQueues *q, unsigned long *t, QTcpSocket* incSoc, QObject *parent = 0);

signals:

public slots:

private slots:
    void process();         //This process does nothing but it just creates the other threads for listening to the given sockets and  updating the evQueues

private:
    QTcpSocket *socket;
    EventQueues *q;
    unsigned long *time;
};

#endif // RECVQSOCKETWORKER_H
