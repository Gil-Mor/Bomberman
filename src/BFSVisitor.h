#pragma once

/* Derived from BFS Visitor. executes commands on bfs events.
Initializing every vertex predecessor to null. 
When discovering a 'tree edge', sets it's predecessor. 
'tree edges' are the edges that form the shortest path between vertices on the board.*/

#include "AIMapBFSProxy.h"
#include "definitions.h"
#include <boost/graph/breadth_first_search.hpp>

class BFSVisitor : public boost::default_bfs_visitor
{
public:

    BFSVisitor(AIMapBFSProxy mapProxy);

    void initializeVertex(const vertex_d& d);

    void setVertexPredecessor(const edge_d& e);

    void setVertexPredecessor(const vertex_d& e);


    bool checkStopCondition(const vertex_d& d);

    template < typename Edge, typename Graph >
    void tree_edge(Edge e, const Graph& g)
    {
        if (_keepBuildingPath)
        {
            setVertexPredecessor(e);
            

            // we found the first tile that fulfilles the stopping condition
            if (checkStopCondition(boost::target(e, g))) {
                _keepBuildingPath = false;
            }
        }
    }


    template < typename Vertex, typename Graph >
    void initialize_vertex(Vertex u, const Graph& g)
    {
        initializeVertex(u);
    }



private:


    // true while _stopCondition wasn't fulfilled. 
    // when false. bfswill stop to add vertices to the path.
    bool _keepBuildingPath = true;
    AIMapBFSProxy _mapProxy;

};

