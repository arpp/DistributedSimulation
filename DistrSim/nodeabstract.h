#ifndef NODEABSTRACT_H
#define NODEABSTRACT_H

class NodeAbstract
{
public:
    NodeAbstract(unsigned long vid);
    virtual unsigned long getNodeId();

private:
    unsigned long vertexId;
};

#endif // NODEABSTRACT_H
