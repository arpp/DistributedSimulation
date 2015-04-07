#ifndef SENDQUEUEWORKER_H
#define SENDQUEUEWORKER_H

#include "eventqueues.h"

#include <QObject>
#include <QTcpSocket>

class SendQueueWorker : public QObject
{
    Q_OBJECT
public:
    explicit SendQueueWorker(EventQueues *q, unsigned long *t, QMap<int,QTcpSocket*> outSoc, int m_id, QObject *parent = 0);

signals:

public slots:

private slots:
    void process();                 //This will simply use the sendQueue and send the msgs from queue need to use qwait condition

private:
    EventQueues *q;
    unsigned long *time;
    QMap<int,QTcpSocket*> outSoc;
    int m_id;
};

#endif // SENDQUEUEWORKER_H
