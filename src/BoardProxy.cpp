#include "BoardProxy.h"
#include "Board.h"
#include "Bonus.h"

BoardProxy::BoardProxy(Board& board)
    : _board(board)
{
}


BoardProxy::~BoardProxy()
{}

void BoardProxy::moveOnBoard(GameObject* obj, const Posb& from, const Posb& to)
{
    _board.moveOnBoard(obj, from, to);
}

//GameObject* BoardProxy::getFromBoard(const Pos3D& pos) const
//{
//    return _board.getObject(pos);
//}


const Posf& BoardProxy::getTilePosf(const Posb& posb) const
{
    return _board.getTilePosf(posb);
}

bool BoardProxy::validPosb(const Posb& posb) const
{
    return _board.validPosb(posb);
}

void BoardProxy::removeExplodingWall(ExplodingWall* wall)
{
    _board.removeExplodingwall(wall);
}


void BoardProxy::removeBonus(Bonus* bonus)
{
    _board.removeBonus(bonus);
}

void BoardProxy::placeBonus(bonus_up& bonus)
{
    _board.placeBonus(std::move(bonus));
}

float BoardProxy::getElapsedTimeAsSeconds() const
{
    return getElapsedTime().asSeconds();
}

void BoardProxy::placeDynamite(dynamite_up& dynamite)
{
    _board.placeDynamite(std::move(dynamite));
}

sf::Time BoardProxy::getElapsedTime() const
{
    return _board.getElapsedTime();
}

const tile& BoardProxy::getTile(const Posb& tile) const
{
    return _board.getTile(tile);
}

 ExplosionsBoardProxy& BoardProxy::getExplosionProxy() 
{
    return _board.getExplosionProxy();
}


