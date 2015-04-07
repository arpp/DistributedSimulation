#ifndef EVENTPROCESSWORKER_H
#define EVENTPROCESSWORKER_H

#include "eventqueues.h"

#include <QObject>
#include <QMutex>
#include <QWaitCondition>

class EventProcessWorker : public QObject
{
    Q_OBJECT
public:
    explicit EventProcessWorker(EventQueues *q, unsigned long *t, int m_id, QMutex *evQueueMutex, QMutex *sendQueueMutex, QMutex *timeStampMutex, QWaitCondition *evQueueNotEmpty, QWaitCondition *sendQueueNotEmpty, QObject *parent = 0);

signals:

public slots:

private slots:
    void process();             // This will take elements from the evQueue and put elements in send queue need to use QWaitCondition

private:
    EventQueues *q;
    unsigned long *time;
    int m_id;

    QWaitCondition *evQueueNotEmpty;
    QWaitCondition *sendQueueNotEmpty;
    QMutex *evQueueMutex;
    QMutex *sendQueueMutex;
    QMutex *timeStampMutex;

};

#endif // EVENTPROCESSWORKER_H
