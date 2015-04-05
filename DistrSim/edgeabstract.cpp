#include "edgeabstract.h"

EdgeAbstract::EdgeAbstract(NodeAbstract* srcNode, NodeAbstract *destNode)
{
}

NodeAbstract* EdgeAbstract::getSrc(){
    return this->srcNode;
}

NodeAbstract* EdgeAbstract::getDst(){
    return this->destNode;
}

