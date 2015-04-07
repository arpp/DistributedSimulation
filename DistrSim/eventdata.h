#ifndef EVENTDATA_H
#define EVENTDATA_H

class EventData
{
public:
    EventData(unsigned long ts, unsigned long nodeId);
    unsigned long getTimestamp();
    unsigned long getNodeId();

private:
    unsigned long timestamp;
    unsigned long nodeId;
};

#endif // EVENTDATA_H
