#include "ExplosionsBoardProxy.h"
#include "Board.h"
#include "definitions.h"

ExplosionsBoardProxy::ExplosionsBoardProxy(Board& board)
    : BoardProxy(board)
{
}


ExplosionsBoardProxy::~ExplosionsBoardProxy()
{
}

void ExplosionsBoardProxy::placeExplosion(explosion_up explosion)
{
    _board.placeExplosion(std::move(explosion));
}

void ExplosionsBoardProxy::removeDynamiteFromBoard(Dynamite* dynamite)
{
    _board.removeDynamiteFromBoard(dynamite);
}

void ExplosionsBoardProxy::removeExplosionFromBoard(Explosion* dynamite)
{
    _board.removeExplosionFromBoard(dynamite);
}
