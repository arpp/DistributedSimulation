#include "event.h"

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
    unsigned long nodeId = node->getNodeId();
    QList<EventData> toSend;
    for(int i=0;i<nodeList.size();++i)
    {
        if(nodeList[i]->getNodeId() == nodeId)
        {
            //Generate random dest node
            int j = qrand() % edgeList[i].size();
            unsigned long destNodeId = edgeList[i][j].first->getNodeId();
            EventData * newEvent = new EventData(0, nodeId, destNodeId, 2);
            toSend.append(*newEvent);
        }
    }

    return toSend;
}

unsigned long Event::getTimestamp(){
    return this->eventData->getTimestamp();
}
