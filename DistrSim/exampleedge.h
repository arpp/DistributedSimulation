#ifndef EXAMPLEEDGE_H
#define EXAMPLEEDGE_H

#include "edgeabstract.h"
#include "nodeabstract.h"

class exampleEdge:public EdgeAbstract
{
public:
    exampleEdge(NodeAbstract* srcNode, NodeAbstract *destNode);
};

#endif // EXAMPLEEDGE_H
