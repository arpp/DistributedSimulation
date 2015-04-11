#include "eventdata.h"

EventData::EventData(unsigned long ts, unsigned long srcNodeId, unsigned long nodeId, int type)
{
    this->timestamp = ts;
    this->srcNodeId = srcNodeId;
    this->NodeId = nodeId;
    this->type = type;
}

unsigned long EventData::getSrcNodeId()
{
    return this->srcNodeId;
}

unsigned long EventData::getNodeId()
{
    return this->NodeId;
}

int EventData::getTypeOfEvent()
{
    return typeOfEvent;
}

unsigned long EventData::getTimestamp()
{
    return this->timestamp;
}

int EventData::getType(){
    return this->type;
}

void EventData::setTimestamp(unsigned long ts)
{
    this->timestamp = ts;
}

void EventData::setTypeOfEvent(int tp)
{
    typeOfEvent = tp;
}

void EventData::setDay(int day) {
    this->day = day;
}

QDataStream& operator<<(QDataStream& out, EventData &eventData)
{
    out << (quint64)(eventData.getTimestamp()) << (quint64)(eventData.getSrcNodeId()) << (quint64)(eventData.getNodeId()) << eventData.getType();
    return out;
}

QDataStream& operator>>(QDataStream& in, EventData & eventData)
{
    quint64 ts, srcNodeId, nodeId;
    int type;
    in >> ts >> srcNodeId >> nodeId >> type;
    eventData = EventData((unsigned long)ts, (unsigned long)srcNodeId, (unsigned long) nodeId, type);
    return in;
}

int EventData::getDay() {
    return day;
}
