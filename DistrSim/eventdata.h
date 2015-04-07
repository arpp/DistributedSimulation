#ifndef EVENTDATA_H
#define EVENTDATA_H

#include <QDataStream>

class EventData
{
public:
    EventData(unsigned long ts, unsigned long srcNodeId, unsigned long destNodeId, int type);
    unsigned long getTimestamp();
    unsigned long getSrcNodeId();
    unsigned long getDestNodeId();
    int getType();

    friend QDataStream& operator<<(QDataStream& out, EventData &eventData);
    friend QDataStream& operator>>(QDataStream& in, EventData & eventData);

private:
    unsigned long timestamp;
    unsigned long srcNodeId;
    unsigned long destNodeId;
    int type;
};

#endif // EVENTDATA_H
