#ifndef EXAMPLENODE_H
#define EXAMPLENODE_H

#include "nodeabstract.h"

class PersonNode:public NodeAbstract
{

public:
    PersonNode(unsigned long, int, int);
    PersonNode(unsigned long, int, int, int);
    PersonNode(unsigned long, int, int, int, int);
    PersonNode(unsigned long, PersonNode*, int);
    int getInfectionTime();
    int getIncubationTime();
    int getState();
    int getDay();
    int getWeight();
    void setState(int st);
    void setDay(int d);
private:
    int infectionTime;
    int incubationTime;
    int state;//0-S, 1-E, 2-I, 3-R
    int day;
    int weight;
};

#endif // EXAMPLENODE_H
