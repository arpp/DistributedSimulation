#include "eventdata.h"

EventData::EventData(unsigned long ts, unsigned long nodeId)
{
    this->timestamp = ts;
    this->nodeId = nodeId;
}

unsigned long EventData::getNodeId()
{
    return this->nodeId;
}

unsigned long EventData::getTimestamp()
{
    return this->timestamp;
}

QDataStream& operator<<(QDataStream& out, EventData &eventData)
{
    out << (quint64)(eventData.getTimestamp()) << (quint64)(eventData.getNodeId());
    return out;
}

QDataStream& operator>>(QDataStream& in, EventData & eventData)
{
    quint64 ts, nodeId;
    in >> ts >> nodeId;
    eventData = EventData((unsigned long)ts, (unsigned long)nodeId);
    return in;
}
