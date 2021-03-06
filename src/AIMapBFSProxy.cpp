#include "AIMapBFSProxy.h"

AIMapBFSProxy::AIMapBFSProxy(AIMap& map, BfsStopCondition stopCondition) : _map(map), _stopCondition(stopCondition)
{}

AIMapBFSProxy::~AIMapBFSProxy()
{}
void AIMapBFSProxy::setVertexPredecessor(const edge_d& e)
{
    _map.setVertexPredecessor(e);
}

bool AIMapBFSProxy::checkStopCondition(const vertex_d& d)
{
    return _map.checkStopCondition(d, _stopCondition);
}

void AIMapBFSProxy::initializeVertex(const vertex_d& d)
{
    _map.initializeVertex(d);
}