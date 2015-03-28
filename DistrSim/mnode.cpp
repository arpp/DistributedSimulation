#include "mnode.h"
#include "iostream"

MNode::MNode()
{
    std::cout<<"mnode created\n";
}

void MNode::insertEvent(EventAbstract* e){
    evQueue.enqueue(e);
    std::cout<<"Event added\n";
}

EventAbstract* MNode::removeEvent(){
    return evQueue.dequeue();
}
