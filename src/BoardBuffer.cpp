#include "BoardBuffer.h"
#include "FreeTile.h"
#include "GameObject.h"
#include "Dynamite.h"
#include "Explosion.h"
#include "ExplodingWall.h"
#include "Bonus.h"

BoardBuffer::BoardBuffer()
{
}


BoardBuffer::~BoardBuffer()
{
}

void BoardBuffer::update(board3d& board, PosfMap& posfMap, 
    DynamitesList& dynamites, ExplosionsList& explosions,
    AIMap& aiMap)
{
    removeFromBoard(board, posfMap, dynamites, explosions, aiMap);

    moveOnBoard(board);

    addToBoard(board, posfMap, dynamites, explosions);
}

void BoardBuffer::moveOnBoard(board3d& board)
{
    for (auto& movment : _moveBuffer.gameObjects)
    {
        for (auto& other : board[movment.oldPosb.i][movment.oldPosb.j]) {
            if (other.get() == movment.object) {
                board[movment.newPosb.i][movment.newPosb.j].push_front(std::move(other));
                board[movment.oldPosb.i][movment.oldPosb.j].remove(other);
                break;
            }
        }
    }

    _moveBuffer.gameObjects.clear();
}


void BoardBuffer::addToBoard(board3d& board, PosfMap& posfMap, 
    DynamitesList& dynamites, ExplosionsList& explosions)
{

    for (auto& dynamite : _addBuffer.dynamites)
    {
        Posb pos = dynamite->getPosb();

        board[pos.i][pos.j].push_front(std::move(dynamite));
        dynamites.push_back(static_cast<Dynamite*>(board[pos.i][pos.j].front().get()));

    }

    for (auto& explosion : _addBuffer.explosions)
    {
        Posb pos = explosion->getPosb();

        board[pos.i][pos.j].push_front(std::move(explosion));
        explosions.push_back(static_cast<Explosion*>(board[pos.i][pos.j].front().get()));
    }

    for (auto& object : _addBuffer.gameObjects)

    {
        Posb pos = object->getPosb();

        board[pos.i][pos.j].push_front(std::move(object));

    }

    _addBuffer.dynamites.clear();
    _addBuffer.explosions.clear();
    _addBuffer.gameObjects.clear();
}


void BoardBuffer::removeFromBoard(board3d& board, PosfMap& posfMap, 
    DynamitesList& dynamites, ExplosionsList& explosions,
    AIMap& aiMap)
{

    for (auto& dynamite : _removalBuffer.dynamites)
    {

        // add dynamite to remove from board list
        _removalBuffer.gameObjects.insert(dynamite);
        dynamites.remove(dynamite);
    }

    for (auto& explosion : _removalBuffer.explosions)

    {
        // add explosion to remove from board list
        _removalBuffer.gameObjects.insert(explosion);
        explosions.remove(explosion);
    }

    for (auto& wall : _removalBuffer.explodingWalls)
    {

        aiMap.setTileTypeToFree(wall->getPosb());
        // add explosion to remove from board list
        _removalBuffer.gameObjects.insert(wall);


    }

    for (auto& object : _removalBuffer.gameObjects)
    {
        Posb pos = object->getPosb();

        for (auto& other : board[pos.i][pos.j]) {
            if (other.get() == object) {  
                board[pos.i][pos.j].remove(other);
                break;
            }
        }

        if (board[pos.i][pos.j].empty())
        {
            board[pos.i][pos.j].emplace_front(new FreeTile(posfMap[pos.i][pos.j], pos));
        }

    }

    _removalBuffer.dynamites.clear();
    _removalBuffer.explosions.clear();
    _removalBuffer.explodingWalls.clear();
    _removalBuffer.gameObjects.clear();
}


void BoardBuffer::removeBonus(Bonus* bonus)
{
    _removalBuffer.gameObjects.insert(bonus);
}

void BoardBuffer::removeExplodingWall(ExplodingWall* wall)
{
    _removalBuffer.explodingWalls.push_back(wall);
}


void BoardBuffer::removeDynamite(Dynamite* dynamite)
{
    _removalBuffer.dynamites.push_back(dynamite);
}


void BoardBuffer::removeExplosion(Explosion* explosion)
{
    _removalBuffer.explosions.push_back(explosion);

}

void BoardBuffer::addBonus(bonus_up bonus)
{
    _addBuffer.gameObjects.push_back(std::move(bonus));
}

void BoardBuffer::addDynamite(dynamite_up dynamite)
{
    _addBuffer.dynamites.push_back(std::move(dynamite));
}


void BoardBuffer::addExplosion(explosion_up explosion)
{
    _addBuffer.explosions.push_back(std::move(explosion));
}

void BoardBuffer::moveObject(GameObject* obj, Posb oldPos, Posb newPos)
{
    _moveBuffer.gameObjects.push_back({ obj, oldPos, newPos });
}


