#ifndef EVENTDATA_H
#define EVENTDATA_H

#include <QDataStream>

class EventData
{
public:
    EventData(unsigned long ts, unsigned long nodeId);
    unsigned long getTimestamp();
    unsigned long getNodeId();

    friend QDataStream& operator<<(QDataStream& out, EventData &eventData);
    friend QDataStream& operator>>(QDataStream& in, EventData & eventData);

private:
    unsigned long timestamp;
    unsigned long nodeId;
};

#endif // EVENTDATA_H
