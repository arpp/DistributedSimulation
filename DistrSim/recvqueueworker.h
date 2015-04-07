#ifndef RECVQUEUEWORKER_H
#define RECVQUEUEWORKER_H

#include "eventqueues.h"

#include <QObject>
#include <QTcpSocket>
#include <QThread>
#include "recvqsocketworker.h"

class RecvQueueWorker : public QObject
{
    Q_OBJECT
public:
    explicit RecvQueueWorker(EventQueues *q, unsigned long *t, QMap<int,QTcpSocket*> incSoc, int m_id, QObject *parent = 0);

signals:

public slots:

private slots:
    void process();                 // This will have an infinite loop and will read from the sockets and write to the event

private:
    EventQueues *q;
    QMap<int, QTcpSocket*> incSoc;
    unsigned long *time;

    QThread** th;
    RecvQSocketWorker** workers;

    int m_id;
};

#endif // RECVQUEUEWORKER_H
