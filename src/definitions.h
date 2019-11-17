#pragma once
/*
  general type definitions.
*/
#include <string>
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <deque>
#include <forward_list>
#include <list>
#include "Posb.h"

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_traits.hpp>

using std::deque;
using std::forward_list;
using std::list;
using std::vector;

class Player;
class AIEnemy;
class GameObject;
class Dynamite;
class Explosion;
class Movable;
class Bonus;
class ExplodingWall;
class Vertex;
class AIMap;

using std::unique_ptr;

//---------- SFML STUFF ------------
typedef sf::Vector2f Posf;
typedef sf::Vector2u Posu;
typedef sf::Vector2i Posi;
typedef sf::Color Color;

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> Graph;
typedef boost::graph_traits<Graph>::vertex_descriptor vertex_d;
typedef boost::graph_traits<Graph>::edge_descriptor edge_d;

// ----------- USED IN BOARD ------------
typedef Player* player_p;
typedef unique_ptr<Player> player_up;

typedef AIEnemy* enemy_p;
typedef unique_ptr<AIEnemy> enemy_up;

typedef Dynamite* dynamite_p;
typedef Explosion* explosion_p;
typedef unique_ptr<Explosion> explosion_up;
typedef unique_ptr<Dynamite> dynamite_up;
typedef list<Dynamite*> DynamitesList;
typedef list<Explosion*> ExplosionsList;

typedef unique_ptr<GameObject> object_up;
typedef forward_list<object_up> tile;

// the board is a 2d grid of linked-lists of objects and a fixed position of each tile
// lists for better inserting and removing objects

typedef vector<vector<tile>> board3d;

// those will be the fixed original positions of the tiles.
typedef vector<vector<Posf>> PosfMap;

// typedef unique_ptr<Vertex> vertex_up;

typedef vector<deque<bool>> FreeTilesMap;

typedef unique_ptr<Bonus> bonus_up;
