#ifndef RECVQSOCKETWORKER_H
#define RECVQSOCKETWORKER_H

#include <QObject>
#include <QTcpSocket>
#include <QMutex>
#include <QWaitCondition>
#include "eventqueues.h"

class RecvQSocketWorker : public QObject
{
    Q_OBJECT
public:
    explicit RecvQSocketWorker(EventQueues *q, unsigned long *t, QTcpSocket* incSoc, int m_id,
                               QMutex *evQueueMutex, QMutex *timeStampMutex, QWaitCondition *evQueueNotEmpty, QObject *parent = 0);

signals:

public slots:

private slots:
    void process();         //This process does nothing but it just creates the other threads for listening to the given sockets and  updating the evQueues

private:
    QTcpSocket *socket;
    EventQueues *q;
    unsigned long *time;
    int m_id;

    QWaitCondition *evQueueNotEmpty;
    QMutex *evQueueMutex;
    QMutex *timeStampMutex;
};

#endif // RECVQSOCKETWORKER_H
