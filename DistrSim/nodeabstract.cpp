#include "nodeabstract.h"

NodeAbstract::NodeAbstract(unsigned long vid)
{
    this->vertexId = vid;
}

unsigned long NodeAbstract::getNodeId()
{
    return this->vertexId;
}

unsigned long NodeAbstract::getIndex()
{
    return this->index;
}

void NodeAbstract::setIndex(int i)
{
    this->index = i;
}
