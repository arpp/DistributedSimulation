#include "personnode.h"

PersonNode::PersonNode(unsigned long vid, int infPeriod, int incubPeriod):NodeAbstract(vid)
{
    this->infectionTime = infPeriod;
    this->incubationTime = incubPeriod;
    this->state = 0;
    this->day = 1;
}

PersonNode::PersonNode(unsigned long vid, int infPeriod, int incubPeriod, int state):NodeAbstract(vid)
{
    this->infectionTime = infPeriod;
    this->incubationTime = incubPeriod;
    this->state = state;
    this->day = 1;
}

PersonNode::PersonNode(unsigned long vid, int infPeriod, int incubPeriod, int state, int weight):NodeAbstract(vid)
{
    this->infectionTime = infPeriod;
    this->incubationTime = incubPeriod;
    this->state = state;
    this->day = 1;
    this->weight = weight;
}

PersonNode::PersonNode(unsigned long vid, PersonNode* p, int w):NodeAbstract(vid)
{
    this->day = p->getDay();
    this->incubationTime = p->getIncubationTime();
    this->infectionTime = p->getInfectionTime();
    this->state = p->getState();
    this->weight = w;
}

int PersonNode::getInfectionTime()
{
    return this->infectionTime;
}
int PersonNode::getIncubationTime()
{
    return this->incubationTime;
}
int PersonNode::getState()
{
    return this->state;
}
int PersonNode::getDay()
{
    return this->day;
}
int PersonNode::getWeight()
{
    return this->weight;
}
void PersonNode::setState(int st)
{
    this->state = st;
}
void PersonNode::setDay(int d)
{
    this->day = d;
}
