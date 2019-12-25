#pragma once

/* Saves changes like removal, addition, and moving objects on the board in each
game round then updates the board and the AIMap once.

*/
#include "definitions.h"
#include <vector>
#include <set>
#include <list>
#include <forward_list>
#include "AIMap.h"

using std::forward_list;
using std::list;
using std::set;
using std::vector;

class GameObject;
class Dynamite;
class Explosions;
class BomberMan;
class ExplodingWall;
class Bonus;

class BoardBuffer
{
public:
    BoardBuffer();
    ~BoardBuffer();

    void update(board3d& board, PosfMap& posfMap, DynamitesList& dynamite, ExplosionsList& explosions, AIMap& aiMap);

    void removeBonus(Bonus* bonus);
    void removeExplodingWall(ExplodingWall* wall);
    void removeDynamite(Dynamite* dynamite);
    void removeExplosion(Explosion* dynamite);

    void addBonus(bonus_up bonus);

    void addDynamite(dynamite_up dynamite);
    void addExplosion(explosion_up explosion);

    void moveObject(GameObject* obj, Posb oldPos, Posb newPos);

private:
    // ----------- REMOVE ----------
    struct RemovalBuffer
    {
        // gameObjects is the one that removes from the board.
        // it could happen that an item is inserted twice and then
        // after it's deleted once the next time it's POsb will be garbage
        set<GameObject*> gameObjects;
        vector<ExplodingWall*> explodingWalls;
        vector<Dynamite*> dynamites;
        vector<Explosion*> explosions;

    } _removalBuffer;

    void removeFromBoard(
        board3d& board, PosfMap& posfMap, DynamitesList& dynamite, ExplosionsList& explosions, AIMap& aiMap);

    //------------ ADD ----------------
    struct AddBuffer
    {
        vector<object_up> gameObjects;
        vector<dynamite_up> dynamites;
        vector<explosion_up> explosions;
    } _addBuffer;

    void addToBoard(board3d& board, DynamitesList& dynamite, ExplosionsList& explosions);

    // ---------- MOVE ----------------
    struct Movement
    {
        GameObject* object;
        Posb oldPosb, newPosb;
    };

    struct MoveBuffer
    {
        vector<Movement> gameObjects;

    } _moveBuffer;

    void moveOnBoard(board3d& board);

    //----------------------------

    //---------- NAGER MAP ---------
};
