#include "event.h"
#include <QDebug>
#include <QTime>

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

QList<EventData> Event::runEvent()
{
//    int typeOfEvent = eventData->getTypeOfEvent();
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());

    unsigned long nodeId = node->getNodeId();
    qDebug() << "current nopde is : " << nodeId;
    QList<EventData> toSend;
    for(int i=0;i<nodeList.size();++i)
    {
        if(nodeList[i]->getNodeId() == nodeId)
        {
            for(int k=0;k<edgeList[i].size();++k)
                qDebug() << edgeList[i][k].first->getNodeId() << " ";

            //Generate random dest node
            int j = qrand() % edgeList[i].size();
            unsigned long destNodeId = edgeList[i][j].first->getNodeId();
            qDebug() << "dest is " << destNodeId;
            EventData * newEvent = new EventData(0, nodeId, destNodeId, 2);
            toSend.append(*newEvent);            
        }
    }

    qDebug() << "Event ran ";
    return toSend;
}

unsigned long Event::getTimestamp(){
    return this->eventData->getTimestamp();
}
