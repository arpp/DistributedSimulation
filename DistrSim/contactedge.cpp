#include "contactedge.h"

ContactEdge::ContactEdge(NodeAbstract* srcNode, NodeAbstract *destNode, int w):EdgeAbstract(srcNode, destNode)
{
    this->weight = w;
}

float ContactEdge::getWeight() {
    return weight;
}
