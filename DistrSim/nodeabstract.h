#ifndef NODEABSTRACT_H
#define NODEABSTRACT_H

class NodeAbstract
{
public:
    NodeAbstract(unsigned long vid);
    virtual unsigned long getNodeId();
    virtual unsigned long getIndex();
    virtual void setIndex(int i);

private:
    unsigned long vertexId;
    unsigned long index;
};

#endif // NODEABSTRACT_H
