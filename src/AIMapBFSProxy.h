#pragma once
/* Proxy for BFS visitor. The BFS Visitor needs to check the stop condition in the map
and save the result. */

#include "AIMap.h"
#include "definitions.h"

class AIMap;

enum BfsStopCondition;

class AIMapBFSProxy
{
public:
    AIMapBFSProxy(AIMap& map, BfsStopCondition stopConditoin);
    ~AIMapBFSProxy();

    void initializeVertex(const vertex_d& d);

    void setVertexPredecessor(const edge_d& e);

    bool checkStopCondition(const vertex_d& d);

private:

    AIMap& _map;
    BfsStopCondition _stopCondition;
};

