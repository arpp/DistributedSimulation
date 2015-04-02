#ifndef SENDQUEUEWORKER_H
#define SENDQUEUEWORKER_H

#include "eventqueues.h"

#include <QObject>

class SendQueueWorker : public QObject
{
    Q_OBJECT
public:
    explicit SendQueueWorker(QObject *parent = 0);

signals:

public slots:

private slots:
    void process();

private:
    EventQueues *q;
};

#endif // SENDQUEUEWORKER_H
