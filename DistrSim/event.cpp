#include "event.h"
#include "personnode.h"
#include <QDebug>
#include <QTime>
#include <QFile>
#include <QtMath>

#define r 0.2

Event::Event(NodeAbstract *n, EventData *ev, QList<NodeAbstract*> nodeList, QList<QList<QPair<NodeAbstract*,int> > > edgeList)
{
    this->node=n;
    this->eventData=ev;
    this->nodeList = nodeList;
    this->edgeList = edgeList;
}

unsigned long Event::getNodeID(){
    return this->node->getNodeId();
}

QList<EventData*> Event::runEvent()
{
//    int typeOfEvent = eventData->getTypeOfEvent();
//    QTime time = QTime::currentTime();
//    qsrand((uint)time.msec());

    PersonNode* pnode = dynamic_cast<PersonNode*>(this->node);
    QList<EventData*> toSend;
    int nodeId = node->getNodeId();

    //if pnode is susceptible, ie state = 0
    if(pnode->getState() == 0) {
        qDebug() << pnode->getNodeId() << " exposed on " + eventData->getDay();
        int presentDay = eventData->getDay()+pnode->getIncubationTime();
        qDebug() << pnode->getNodeId() << " gets infected on " << presentDay;

        unsigned long i = pnode->getIndex();

        for(int j=0; j<edgeList[i].size(); j++)
        {
            PersonNode* nPnode = dynamic_cast<PersonNode*>(edgeList[i][j].first);
            if(qrand()%100 < 100*(1-pow(1-r, nPnode->getWeight())))
            {
                int destNodeId = nodeList[i]->getNodeId();
                EventData * newEvent = new EventData(0, nodeId, destNodeId, 2);
                newEvent->setDay(presentDay);
                toSend.append(newEvent);
            }
        }

        qDebug() << pnode->getNodeId() << " removed on " << presentDay + pnode->getInfectionTime();
        pnode->setState(1); //exposed
        pnode->setDay(presentDay + pnode->getInfectionTime());
    }

    else {

    }

//    unsigned long nodeId = node->getNodeId();
//    qDebug() << "current node is : " << nodeId;
//    QList<EventData*> toSend;
//    unsigned long destNodeId;
//    for(int i=0;i<nodeList.size();++i)
//    {
//        if(nodeList[i]->getNodeId() == nodeId)
//        {
////            for(int k=0;k<edgeList[i].size();++k)
////                qDebug() << edgeList[i][k].first->getNodeId() << " ";

//            //Generate random dest node
//            int j = qrand() % edgeList[i].size();
//            destNodeId = edgeList[i][j].first->getNodeId();
//            EventData * newEvent = new EventData(0, nodeId, destNodeId, 2);
//            toSend.append(newEvent);
//        }
//    }

    qDebug() << "Event ran timstamp is :" << eventData->getTimestamp() ;
    //qDebug() << "dest is " << destNodeId;
    return toSend;
}

unsigned long Event::getTimestamp(){
    return this->eventData->getTimestamp();
}

int Event::getType()
{
    return eventData->getType();
}

unsigned long Event::meraFunctionObfuscated()
{
    return eventData->getSrcNodeId();
}
