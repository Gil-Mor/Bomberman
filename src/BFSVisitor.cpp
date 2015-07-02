#include "BFSVisitor.h"
#include "AIMapBFSProxy.h"


BFSVisitor::BFSVisitor(AIMapBFSProxy& map)
    :_mapProxy(map)
{}


void BFSVisitor::setVertexPredecessor(const edge_d& e)
{
    _mapProxy.setVertexPredecessor(e);
}


bool BFSVisitor::checkStopCondition(const vertex_d& d)
{
    return _mapProxy.checkStopCondition(d);
}

void BFSVisitor::initializeVertex(const vertex_d& d)
{
    _mapProxy.initializeVertex(d);
}

void BFSVisitor::setVertexPredecessor(const vertex_d& d)
{
    _mapProxy.setVertexPredecessor(d);
}


