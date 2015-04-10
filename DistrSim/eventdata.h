#ifndef EVENTDATA_H
#define EVENTDATA_H

#include <QDataStream>

class EventData
{
public:
    EventData(unsigned long ts, unsigned long srcNodeId, unsigned long NodeId, int type);
    unsigned long getTimestamp();
    unsigned long getSrcNodeId();
    unsigned long getNodeId();
    int getTypeOfEvent();
    int getType();
    void setType(int type);
    void setTimestamp(unsigned long ts);
    void setTypeOfEvent(int tp);


    friend QDataStream& operator<<(QDataStream& out, EventData &eventData);
    friend QDataStream& operator>>(QDataStream& in, EventData & eventData);

private:
    unsigned long timestamp;
    unsigned long srcNodeId;
    unsigned long NodeId;
    int type;
    int typeOfEvent;//send/receive
};

#endif // EVENTDATA_H
