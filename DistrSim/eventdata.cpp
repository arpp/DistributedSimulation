#include "eventdata.h"

EventData::EventData(unsigned long ts, unsigned long srcNodeId, unsigned long destNodeId, int type)
{
    this->timestamp = ts;
    this->srcNodeId = srcNodeId;
    this->destNodeId = destNodeId;
    this->type = type;
}

unsigned long EventData::getSrcNodeId()
{
    return this->srcNodeId;
}

unsigned long EventData::getDestNodeId()
{
    return this->destNodeId;
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
    out << (quint64)(eventData.getTimestamp()) << (quint64)(eventData.getSrcNodeId()) << (quint64)(eventData.getDestNodeId()) << eventData.getType();
    return out;
}

QDataStream& operator>>(QDataStream& in, EventData & eventData)
{
    quint64 ts, srcNodeId, destNodeId;
    int type;
    in >> ts >> srcNodeId >> destNodeId >> type;
    eventData = EventData((unsigned long)ts, (unsigned long)srcNodeId, (unsigned long)  destNodeId, type);
    return in;
}
