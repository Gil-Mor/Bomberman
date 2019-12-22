#include "AIMap.h"
#include "Dynamite.h"
#include "Explosion.h"
#include <boost/graph/breadth_first_search.hpp>
#include "AIMapBFSProxy.h"
#include "BFSVisitor.h"
#include "boardUtils.h"

const bool FREE = true;
const bool NOT_FREE = false;

AIMap::AIMap()
{}


AIMap::AIMap(const FreeTilesMap& freeTiles)
{

    _tiles.resize(freeTiles.size());

    for (size_t i = 0; i < freeTiles.size(); ++i)
    {
        for (size_t j = 0; j < freeTiles[i].size(); ++j)
        {
            vertex_d vertexDescriptor = boost::add_vertex(_graph);

            if (freeTiles[i][j])
            {
                _tiles[i].push_back(Vertex(Posb(i, j), vertexDescriptor, FREE));
            }
            else
            {
                _tiles[i].push_back(Vertex(Posb(i, j), vertexDescriptor, NOT_FREE));

            }

            _d2pMap.insert(std::pair<vertex_d, Posb>(_tiles[i][j].getDescriptor(), Posb(i, j)));
        }

    }

    // connect neighbors
    for (size_t i = 0; i < _tiles.size(); ++i)
    {
        for (size_t j = 0; j < _tiles[i].size(); ++j)
        {
            if (_tiles[i][j].isFree())
                updateVertexNeighbors(Posb(i, j));
        }
    }


    // prepere danger map
    _dangerMap.resize(_tiles.size());
    for (size_t i = 0; i < _tiles.size(); ++i) {
        _dangerMap[i].resize(_tiles[i].size(), DangerType::NONE_D);
    }

}


AIMap::~AIMap()
{
}

Vertex* AIMap::descriptorToVertex(const vertex_d& d) {
    return &_tiles[_d2pMap[d].i][_d2pMap[d].j];
}

Path AIMap::pathToDestination(const Posb& source, const Posb& dest)
{
    _path.source = &_tiles[source.i][source.j];
    _path.result = _path.source;
    _path.target = dest;

   
    boost::breadth_first_search(_graph, _path.source->getDescriptor(),
        boost::visitor(BFSVisitor(AIMapBFSProxy(*this, DESTINATION_C))));



    Vertex* traveler = _path.result;

    Path path;

    while (traveler != _path.source)
    {
        if (traveler == nullptr) {
            return Path();
        }


        path.push(traveler->getPosb());
        traveler = traveler->getPredecessor();
    }

    return path;
}


Path AIMap::pathToSaftey(const Posb& source)
{

    _path.source = &_tiles[source.i][source.j];
    _path.result = nullptr;


    boost::breadth_first_search(_graph, _path.source->getDescriptor(),
        boost::visitor(BFSVisitor(AIMapBFSProxy(*this, SAFE_C))));


    Vertex* traveler = _path.result;

    Path path;

    while (traveler != _path.source)
    {
        if (traveler == nullptr) {
            return Path();
        }


        path.push(traveler->getPosb());
        traveler = traveler->getPredecessor();
    }


    return path;
}

bool AIMap::checkStopCondition(const vertex_d& d, BfsStopCondition stopCondition)
{
    Posb currPos = _d2pMap[d];

    switch (stopCondition)
    {
        case SAFE_C:
        {
            if (_dangerMap[currPos.i][currPos.j] == DangerType::NONE_D) {
                saveResult(d);
                return true;
            }
            return false;
            break;
        }

        case DESTINATION_C:
        {

            if (currPos == _path.target) {
                saveResult(d);
                return true;
            }
            
            if (_dangerMap[currPos.i][currPos.j] != DangerType::EXPLOSION_D 
                &&_dangerMap[currPos.i][currPos.j] != DangerType::EXPLOSION_POTENTIAL_D
                && AisclosertoCthenB(currPos, _path.result->getPosb(), _path.target))
            {
                saveResult(d);
            }

            return false;
            break;
        }


        default:
            return false; // TODO: check
    }
}

void AIMap::saveResult(const vertex_d& d)
{
    _path.result = descriptorToVertex(d);
}

void AIMap::initializeVertex(const vertex_d& d)
{
   descriptorToVertex(d)->setPredecessor(nullptr);
}

void AIMap::setVertexPredecessor(const edge_d& e)
{
    vertex_d source = boost::source(e, _graph);
    vertex_d target = boost::target(e, _graph);

    descriptorToVertex(target)->setPredecessor(descriptorToVertex(source));
}

void AIMap::setVertexPredecessor(const vertex_d& d)
{
    //descriptorToVertex(d);
}


void AIMap::updateDangers(const DynamitesList& dynamites, const ExplosionsList& explosions)
{
    for (auto& vec : _dangerMap)
        std::fill(vec.begin(), vec.end(), DangerType::NONE_D);

    for (const auto& dynamite : dynamites) {

        // also fill danger around the dynamite.

        Posb dPos = dynamite->getPosb();

        bool stopUp = false, stopDown = false, stopRight = false, stopLeft = false;
        for (size_t i = 0, j = 0; i <= dynamite->getExplosionRadius()+1; ++i, ++j)
        {
            if (stopUp && stopDown && stopRight && stopLeft) {
                break;
            }


            if (i == 0 && j == 0) {
                _dangerMap[dPos.i][dPos.j] = DangerType::EXPLOSION_POTENTIAL_D;
                continue;

            }

            Posb up = dPos - Posb(i, 0);
            Posb down = dPos + Posb(i, 0);
            Posb left = dPos - Posb(0, j);
            Posb right = dPos + Posb(0, j);

            if (!stopUp && validPos(up) && isFreeTile(up)) {
                _dangerMap[up.i][up.j] = DangerType::EXPLOSION_POTENTIAL_D;
            }
            else {
                stopUp = true;
            }

            if (!stopDown && validPos(down) && isFreeTile(down)) {
                _dangerMap[down.i][down.j] = DangerType::EXPLOSION_POTENTIAL_D;
            }
            else {
                stopDown = true;
            }

            if (!stopLeft && validPos(left) && isFreeTile(left)) {
                _dangerMap[left.i][left.j] = DangerType::EXPLOSION_POTENTIAL_D;
            }
            else {
                stopLeft = true;
            }

            if (!stopRight && validPos(right) && isFreeTile(right)) {
                _dangerMap[right.i][right.j] = DangerType::EXPLOSION_POTENTIAL_D;
            }
            else {
                stopRight = true;
            }
        }
    }

    for (const auto& explosion : explosions) {
        _dangerMap[explosion->getPosb().i][explosion->getPosb().j] = DangerType::EXPLOSION_D;
    }
}


void AIMap::updateVertexNeighbors(const Posb& pos)
{

    if (!_tiles[pos.i][pos.j].isFree()) {
        return;
    }

    Posb up = pos - Posb(1, 0);
    Posb down = pos + Posb(1, 0);
    Posb left = pos - Posb(0, 1);
    Posb right = pos + Posb(0, 1);

    if (isFreeTile(up))
    {
        addEdge(_tiles[pos.i][pos.j], _tiles[up.i][up.j]);
    }

    if (isFreeTile(down))
    {
        addEdge(_tiles[pos.i][pos.j], _tiles[down.i][down.j]);
    }


    if (isFreeTile(left))
    {
        addEdge(_tiles[pos.i][pos.j], _tiles[left.i][left.j]);
    }

    if (isFreeTile(right))
    {
        addEdge(_tiles[pos.i][pos.j], _tiles[right.i][right.j]);
    }
}

void AIMap::addEdge(const Vertex& a, const Vertex& b)
{
    // if this edge doesn't exist in the graph so add it
    if (!boost::edge(a.getDescriptor(), b.getDescriptor(), _graph).second)
    {
        boost::add_edge(a.getDescriptor(), b.getDescriptor(), _graph);
    }
}

void AIMap::setTileTypeToFree(const Posb& pos)
{
    if (validPos(pos.i, pos.j))
    {
        _tiles[pos.i][pos.j].setToFree();
        updateVertexNeighbors(pos);
    }
}


bool AIMap::validPos(size_t i, size_t j) const
{
    if (i == Posb::INVALID_POS || j == Posb::INVALID_POS) {
        return false;
    }
    return i < _tiles.size()
        && j < _tiles[0].size();
}

bool AIMap::validPos(const Posb& pos) const
{
    return validPos(pos.i, pos.j);
}

bool AIMap::isFreeTile(const Posb& pos) const
{
    return validPos(pos) && _tiles[pos.i][pos.j].isFree();
}

bool AIMap::dangerPos(const Posb& pos, DangerType danger) const
{
    return _dangerMap[pos.i][pos.j] == danger;
}

