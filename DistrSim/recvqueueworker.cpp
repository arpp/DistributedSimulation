#include "recvqueueworker.h"

#include <QDebug>
#include <QThread>

RecvQueueWorker::RecvQueueWorker(EventQueues *q, unsigned long *t, QMap<int,QTcpSocket*> incSoc, int m_id, QObject *parent) :
    QObject(parent)
{
    this->q = q;
    this->time=t;
    this->incSoc=incSoc;
    this->m_id=m_id;
}

void RecvQueueWorker::process(){
    (*(this->time))++;
    qDebug()<<"recv process thread: "<<QThread::currentThreadId()<<"\n"<<*(this->time)<<"\n";

    //find size of incSoc and create multiple threads in a loop here i have done till three and passed null socket to each complete when done with sockets
    int size = 3;   //incSoc.size();
    this->th = new QThread*[size];
    this->workers = new RecvQSocketWorker*[size];


    for(int i=0;i<size;i++){
        th[i] = new QThread();
        workers[i] = new RecvQSocketWorker(q,time,0,0);      //new RecvQSocketWorker(q,t,incSoc.at(i),);
        QObject::connect(th[i],SIGNAL(started()),workers[i],SLOT(process()));
        workers[i]->moveToThread(th[i]);
        th[i]->start();
    }

    /*int i=0;
    QMapIterator<int,QTcpSocket*>  j(this->incSoc);
    while(j.hasNext()){
        j.next();
        th[i] = new QThread();
        workers[i] = new RecvQSocketWorker(q,time,j.value(),j.key());      //new RecvQSocketWorker(q,t,incSoc.at(i),);
        QObject::connect(th[i],SIGNAL(started()),workers[i],SLOT(process()));
        workers[i]->moveToThread(th[i]);
        th[i]->start();
        i++;
    }*/
}


