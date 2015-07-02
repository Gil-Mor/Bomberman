#pragma once

/* Saves location of free tiles and dangers (explosions or explosion areas)
And gives that information to th AIEnemy. Also calculates shortest paths to 
position with BFS. 
*/

#include "definitions.h"
#include "Vertex.h"
#include <stack>
#include <unordered_map>

using std::unordered_map;
using std::stack;


enum DangerType
{

    NONE_D,
    EXPLOSION_POTENTIAL_D,
    EXPLOSION_D,
};

typedef vector< vector< Vertex> > Tiles;
typedef vector< vector< DangerType> > DangerMap;
typedef stack<Posb> Path;
typedef unordered_map <vertex_d, Posb> MapDescriptorsToPos;


// ------- stop conditions for bfs visitor -----------
enum BfsStopCondition
{
    SAFE_C,
    DESTINATION_C,
};



class AIMap
{
public:

    // another result of the need for level's default cotr.
    AIMap();


    // straight from level builder. the skeleton of the map
    AIMap(const FreeTilesMap& freeTiles);
    ~AIMap();


    // updates dynamites areas and explosions areas. 
    void updateDangers(const DynamitesList& dynamites, const ExplosionsList& explosions);


    // called from buffer.
    void setTileTypeToFree(const Posb& pos);


    bool dangerPos(const Posb& pos, DangerType danger) const;


    // bfs builds shortest path to a safe place.

    Path pathToSaftey(const Posb& source);

    // bfs builds shortest path to a destination (the palyer..)
    Path pathToDestination(const Posb& source, const Posb& dest);

    // for bfs visitor proxy
    void initializeVertex(const vertex_d& d);
    void setVertexPredecessor(const edge_d& e);
    void setVertexPredecessor(const vertex_d& d);

    bool checkStopCondition(const vertex_d& d, BfsStopCondition stopCondition);

    bool isFreeTile(const Posb& pos) const;



private:


    struct BFSPath
    {
        Vertex* source;
        // the first vertex that fulfills the stop condition.
        Vertex* result;

        // optional..
        Posb target;

    } _path;

    void saveResult(const vertex_d& d);



    // it's too hard to sync isFree and dangers in one map.. so we has two maps.
    Tiles _tiles;
    DangerMap _dangerMap;
    Graph _graph;
    MapDescriptorsToPos _d2pMap;

    void addEdge(const Vertex& a, const Vertex& b);

    // called from setTileToFree
    void updateVertexNeighbors(const Posb& vertex);


    bool validPos(int i, int j) const;
    bool validPos(const Posb& pos) const;


    Vertex* descriptorToVertex(const vertex_d& d);

};

