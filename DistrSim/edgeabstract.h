#ifndef EDGEABSTRACT_H
#define EDGEABSTRACT_H

#include "nodeabstract.h"

class EdgeAbstract
{
public:
    EdgeAbstract(NodeAbstract* srcNode, NodeAbstract *destNode);
    NodeAbstract* getSrc();
    NodeAbstract* getDst();

private:
    NodeAbstract *srcNode, *destNode;
//    unsigned long edgeId;
};

#endif // EDGEABSTRACT_H
