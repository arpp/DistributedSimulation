#include "edgeabstract.h"

EdgeAbstract::EdgeAbstract(NodeAbstract* srcNode, NodeAbstract *destNode)
{
    this->srcNode = srcNode;
    this->destNode = destNode;
}

NodeAbstract* EdgeAbstract::getSrc(){
    return this->srcNode;
}

NodeAbstract* EdgeAbstract::getDst(){
    return this->destNode;
}

