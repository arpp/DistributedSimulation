#include "mnode.h"

MNode::MNode()
{
    this->TIME=0;
}

void MNode::addNode(NodeAbstract* node){
    (this->nodeList).insert(node);
}

void MNode::addEdge(NodeAbstract* edge, int sysId){

}

void MNode::beginSimulation(){

}

void MNode::initProcessQueueThread(){

}

void MNode::initRecvThread(){

}

void MNode::initSendThread(){

}

