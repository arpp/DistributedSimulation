#ifndef SENDQUEUEWORKER_H
#define SENDQUEUEWORKER_H

#include "eventqueues.h"

#include <QObject>
#include <QTcpSocket>
#include <QMutex>
#include <QWaitCondition>

class SendQueueWorker : public QObject
{
    Q_OBJECT
public:
    explicit SendQueueWorker(EventQueues *q, unsigned long *t, QMap<int,QTcpSocket*> outSoc, int m_id,
                             QMutex *sendQueueMutex, QMutex *timeStampMutex, QWaitCondition *sendQueueNotEmpty, QObject *parent = 0);

signals:

public slots:

private slots:
    void process();                 //This will simply use the sendQueue and send the msgs from queue need to use qwait condition

private:
    EventQueues *q;
    unsigned long *time;
    QMap<int,QTcpSocket*> outSoc;
    int m_id;

    QWaitCondition *sendQueueNotEmpty;
    QMutex *sendQueueMutex;
    QMutex *timeStampMutex;

    int findDestMId(unsigned long srcNodeId, unsigned long destNodeId);
};

#endif // SENDQUEUEWORKER_H
