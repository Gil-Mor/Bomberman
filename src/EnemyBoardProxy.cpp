#include "EnemyBoardProxy.h"
#include "Board.h"

EnemyBoardProxy::EnemyBoardProxy(Board& board)
    : BoardProxy(board)
{
}

Posb EnemyBoardProxy::getNearestPlayerPos(const Posb& mypos)
{
    return _board.getNearestPlayerPos(mypos);
}

// bfs builds shortest path to a safe place.

Path EnemyBoardProxy::pathToSaftey(const Posb& source)
{
    return _board.pathToSaftey(source);
}


// bfs builds shortest path to a destination (the palyer..)
Path EnemyBoardProxy::pathToDestination(const Posb& source, const Posb& dest)
{
    return _board.pathToDestination(source, dest);
}

bool EnemyBoardProxy::isFreeTile(const Posb& pos)
{
    return _board.isFreeTile(pos);
}

bool EnemyBoardProxy::dangerousPos(const Posb& pos, const DangerType& danger) const
{
    return _board.dangerousPos(pos, danger);
}

