#ifndef RECVQUEUEWORKER_H
#define RECVQUEUEWORKER_H

#include "eventqueues.h"

#include <QObject>
#include <QTcpSocket>
#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include "recvqsocketworker.h"

class RecvQueueWorker : public QObject
{
    Q_OBJECT
public:
    explicit RecvQueueWorker(EventQueues *q, unsigned long *t, QMap<int,QTcpSocket*> incSoc, int m_id,
    QMutex *evQueueMutex, QMutex *timeStampMutex, QWaitCondition *evQueueNotEmpty, QObject *parent = 0);

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

    QWaitCondition *evQueueNotEmpty;
    QMutex *evQueueMutex;
    QMutex *timeStampMutex;

    int m_id;
};

#endif // RECVQUEUEWORKER_H
