#pragma once
/* 
Derived from BoardProxy. encapsulates calls to board for enemy
which needs the location of the nearest player, path to the closest position
to the player and path so a safe position.
*/

#include "BoardProxy.h"
#include "definitions.h"
#include "AIMap.h"

enum DangerType;

class Board;
class GameObject;
class Player;
class AIEnemy;
class Bonus;
class Dynamite;

class EnemyBoardProxy : public BoardProxy
{
public:
    EnemyBoardProxy(Board& board);

    Posb getNearestPlayerPos(const Posb& mypos);

    // bfs builds shortest path to a safe place.
    Path pathToSaftey(const Posb& source);

    // bfs builds shortest path to a destination (the palyer..)
    Path pathToDestination(const Posb& source, const Posb& dest);

    bool isFreeTile(const Posb& pos);

    bool dangerousPos(const Posb& pos, const DangerType& danger) const;



};

