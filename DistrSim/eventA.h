#ifndef EVENTA_H
#define EVENTA_H

#include "eventabstract.h"

class EventA : public EventAbstract
{
public:
    EventA();
    void runEvent(NodeAbstract *n);

private:
    int a;
};

#endif // EVENTA_H
