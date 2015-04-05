#include "nodeabstract.h"

NodeAbstract::NodeAbstract(unsigned long vid)
{
    this->vertexId = vid;
}

unsigned long NodeAbstract::getNodeId()
{
    return this->vertexId;
}
