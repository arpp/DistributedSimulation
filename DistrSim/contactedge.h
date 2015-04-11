#ifndef EXAMPLEEDGE_H
#define EXAMPLEEDGE_H

#include "edgeabstract.h"
#include "nodeabstract.h"

class ContactEdge:public EdgeAbstract
{
public:
    ContactEdge(NodeAbstract* srcNode, NodeAbstract *destNode, int w);
    float getWeight();
private:
    float weight;
};

#endif // EXAMPLEEDGE_H
