#include "recvqueueworker.h"

#include <QDebug>
#include <QThread>

RecvQueueWorker::RecvQueueWorker(EventQueues *q, unsigned long *t, QList<QTcpSocket*> incSoc, QObject *parent) :
    QObject(parent)
{
    this->q = q;
    this->time=t;
    this->incSoc=incSoc;

    //find size of incSoc and create multiple threads in a loop here i have done till three and passed null socket to each complete when done with sockets
    this->th = new QThread*[3];
    this->workers = new RecvQSocketWorker*[3];
    for(int i=0;i<3;i++){
        th[i] = new QThread();
        workers[i] = new RecvQSocketWorker(q,t,0);
        QObject::connect(th[i],SIGNAL(started()),workers[i],SLOT(process()));
        workers[i]->moveToThread(th[i]);
        th[i]->start();


//        RecvQSocketWorker *w = new RecvQSocketWorker(q,t,0);
//        QThread *thread1 = new QThread();
//        QObject::connect(thread1,SIGNAL(started()),w,SLOT(process()));
//        this->th.append(thread1);
//        this->workers.append(w);
//        thread1->start();
    }
}

void RecvQueueWorker::process(){
    (*(this->time))++;
    qDebug()<<"recv process thread: "<<QThread::currentThreadId()<<"\n"<<*(this->time)<<"\n";
}



/*this->evWork = new EventProcessWorker(this->events,&(this->TIME));
this->evWorkThread = new QThread();

QObject::connect(evWorkThread,SIGNAL(started()),evWork,SLOT(process()));
evWork->moveToThread(evWorkThread);
evWorkThread->start();*/
