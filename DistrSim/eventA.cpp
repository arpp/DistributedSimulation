#include "eventA.h"
#include "iostream"

EventA::EventA():EventAbstract()
{
    this->a=10;
    std::cout<<"Event A created\n";
}

void EventA::runEvent(NodeAbstract *n){
    std::cout<<"Run Event";
}
