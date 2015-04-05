#ifndef SENDQUEUEWORKER_H
#define SENDQUEUEWORKER_H

#include "eventqueues.h"

#include <QObject>
#include <QTcpSocket>

class SendQueueWorker : public QObject
{
    Q_OBJECT
public:
    explicit SendQueueWorker(EventQueues *q, unsigned long *t, QList<QTcpSocket*> outSoc, QObject *parent = 0);

signals:

public slots:

private slots:
    void process();

private:
    EventQueues *q;
    unsigned long *time;
    QList<QTcpSocket*> outSoc;
};

#endif // SENDQUEUEWORKER_H
