#ifndef EXAMPLENODE_H
#define EXAMPLENODE_H

#include "nodeabstract.h"

class exampleNode:public NodeAbstract
{
public:
    exampleNode(unsigned long vid);
    void visit();
    int getVisitCount();
private:
    int visitCount;
};

#endif // EXAMPLENODE_H
