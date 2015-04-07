#include "eventdata.h"

EventData::EventData(unsigned long ts, unsigned long nodeId, int type)
{
    this->timestamp = ts;
    this->nodeId = nodeId;
    this->type = type;
}

unsigned long EventData::getNodeId()
{
    return this->nodeId;
}

unsigned long EventData::getTimestamp()
{
    return this->timestamp;
}

int EventData::getType(){
    return this->type;
}

QDataStream& operator<<(QDataStream& out, EventData &eventData)
{
    out << (quint64)(eventData.getTimestamp()) << (quint64)(eventData.getNodeId()) << eventData.getType();
    return out;
}

QDataStream& operator>>(QDataStream& in, EventData & eventData)
{
    quint64 ts, nodeId;
    int type;
    in >> ts >> nodeId >> type;
    eventData = EventData((unsigned long)ts, (unsigned long)nodeId, type);
    return in;
}
