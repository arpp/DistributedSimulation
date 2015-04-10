#include "examplenode.h"

exampleNode::exampleNode(unsigned long vid): NodeAbstract(vid)
{
    visitCount = 0;
}

void exampleNode::visit() {
    visitCount++;
}
