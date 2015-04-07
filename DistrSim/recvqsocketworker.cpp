#include "recvqsocketworker.h"
#include <QDebug>
#include "eventdata.h"
#include <QThread>

RecvQSocketWorker::RecvQSocketWorker(EventQueues *q, unsigned long *t, QTcpSocket* incSoc, int m_id,
                                     QMutex *evQueueMutex, QMutex *timeStampMutex, QWaitCondition *evQueueNotEmpty, QObject *parent) :
    QObject(parent)
{
    this->q = q;
    this->time = t;
    this->socket = incSoc;
    this->m_id = m_id;
    this->evQueueMutex=evQueueMutex;
    this->timeStampMutex=timeStampMutex;
    this->evQueueNotEmpty=evQueueNotEmpty;
}

void RecvQSocketWorker::process(){
//The code to listen and add to the queues go here
    qDebug()<<"recv process thread worker: "<<QThread::currentThreadId()<<"\n";

    while(true){
        this->socket->waitForReadyRead(-1);
        int type;
        EventData *ev = new EventData(0,0,0);
        QDataStream st(this->socket);
        st>>(*ev);
        if(type==0){
            //Null message
        }
        else if(type==1){
            //Demand message
        }
        else{
            //Write code to create EventData and Event and add Event to eventQueue at value m_id
        }
    }
}
