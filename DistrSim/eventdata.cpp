#include "eventdata.h"

EventData::EventData(unsigned long ts, unsigned long nodeId)
{
    this->timestamp = ts;
    this->nodeId = nodeId;
}
