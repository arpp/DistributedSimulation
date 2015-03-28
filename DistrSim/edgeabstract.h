#ifndef EDGEABSTRACT_H
#define EDGEABSTRACT_H

#include "nodeabstract.h"

class EdgeAbstract
{
public:
    EdgeAbstract(NodeAbstract* srcNode, NodeAbstract *destNode);

private:
    NodeAbstract *srcNode, *destNode;
//    unsigned long edgeId;
};

#endif // EDGEABSTRACT_H
