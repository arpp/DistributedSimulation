#include "recvqsocketworker.h"
#include <QDebug>
#include <QThread>

RecvQSocketWorker::RecvQSocketWorker(EventQueues *q, unsigned long *t, QTcpSocket* incSoc, int m_id, QObject *parent) :
    QObject(parent)
{
    this->q = q;
    this->time = t;
    this->socket = incSoc;
    this->m_id = m_id;
}

void RecvQSocketWorker::process(){
//The code to listen and add to the queues go here
    qDebug()<<"recv process thread worker: "<<QThread::currentThreadId()<<"\n";

   /* while(true){
        this->socket->waitForReadyRead(-1);
        QByteArray buffer;
        QDataStream st(this->socket);
        st>>buffer;
        //Write code to create EventData and Event and add Event to eventQueue at value m_id
    }*/
}
