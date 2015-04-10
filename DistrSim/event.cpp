#include "event.h"
#include "examplenode.h"
#include <QDebug>
#include <QTextStream>
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

QList<EventData*> Event::runEvent()
{

    exampleNode* enode = dynamic_cast<exampleNode*>(node);
    enode->visit();
    qDebug() << "visited count for " << node->getNodeId() << " is " << enode->getVisitCount();
    QTextStream(stdout)<<node->getNodeId()<<" visited\n";
    unsigned long nodeId = node->getNodeId();
    qDebug() << "current nopde is : " << nodeId;
    QList<EventData*> toSend;
    unsigned long destNodeId;
    for(int i=0;i<nodeList.size();++i)
    {
        if(nodeList.at(i)->getNodeId() == nodeId)
        {
            //Generate random dest node
            int j = qrand() % edgeList[i].size();
            destNodeId = edgeList[i][j].first->getNodeId();
            EventData * newEvent = new EventData(0, nodeId, destNodeId, 2);
            if(enode->getVisitCount()==250){
                newEvent->setType(-1);
            }
            toSend.append(newEvent);
        }
    }

    qDebug() << "Event ran timstamp is :" << eventData->getTimestamp() ;
    qDebug() << "dest is " << destNodeId;

    return toSend;
}

unsigned long Event::getTimestamp(){
    return this->eventData->getTimestamp();
}
