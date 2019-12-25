#include "AIEnemy.h"
#include "Dynamite.h"
#include "Explosion.h"
#include "Bonus.h"
#include "EnemyBoardProxy.h"

#include "FreeTile.h"
#include "StoneWall.h"
#include "ExplodingWall.h"
#include "Teleport.h"
#include "Bonus.h"

#include <algorithm> // find

#include "AIMap.h"

AIEnemy::AIEnemy(const Posf& posf, const Posb& posb, int enemyNum) : BomberMan(posf, posb)
{
    switch (enemyNum) {
        case 1:
            _sprite.setColor({255, 251, 101, 255});
            break;

        case 2:
            _sprite.setColor({255, 191, 23, 255});
            break;

        case 3:
            _sprite.setColor({255, 139, 142, 255});
            break;
    }
}

void AIEnemy::setEnemyProxy(EnemyBoardProxy* enemyProxy)
{
    _enemyProxy = enemyProxy;
}

AIEnemy::~AIEnemy()
{}

bool AIEnemy::inDanger() const
{
    return dangerousPos(_posb, DangerType::EXPLOSION_POTENTIAL_D);
}

bool AIEnemy::dangerousPos(const Posb& pos, DangerType danger) const
{
    return _enemyProxy->dangerousPos(pos, danger);
}

void AIEnemy::goToRunAwayState()
{
    _enemyState = RUNAWAY_S;
    _runAway.time = _enemyProxy->getElapsedTimeAsSeconds();
    _runAway.path = _enemyProxy->pathToSaftey(_posb);
}

void AIEnemy::goToAttackState()
{
    _enemyState = ATTACKING_S;

    _attack.generalDirection = _enemyProxy->getNearestPlayerPos(_posb);
    _attack.path = _enemyProxy->pathToDestination(_posb, _attack.generalDirection);
}

void AIEnemy::continueInRunAwayPath()
{
    if (_runAway.path.empty()) {
        return;
    }

    Posb nextPos = _runAway.path.top();

    OptionalDirections options = directionToPos(nextPos);

    while (!options.empty()) {
        _direction = options.top();
        options.pop();
        if (isFreeTile(_direction)) {
            if (tryMove(_direction)) {
                setMoveOnBoard();
                _runAway.path.pop(); // pop next position only if we moved.
                return;
            } else {
                _lastMove = 0;
            }
        }
    }
}

void AIEnemy::continueInAttackPath()
{
    if (_attack.path.empty()) {
        return;
    }

    Posb nextPos = _attack.path.top();

    OptionalDirections options = directionToPos(nextPos);

    while (!options.empty()) {
        _direction = options.top();
        options.pop();

        if (isFreeTile(_direction)) {
            if (tryMove(_direction)) {
                setMoveOnBoard();
                _attack.path.pop(); // pop next position only if we moved.
                return;
            } else {
                _lastMove = 0;
            }
        }
    }
}

bool AIEnemy::isFreeTile(Movable::Direction dir)
{
    Posb pos = getPosbInDirection(dir);
    return _enemyProxy->isFreeTile(pos);
}

bool AIEnemy::finishedAttackPath()
{
    return _attack.path.empty();
}

OptionalDirections AIEnemy::directionToPos(const Posb& nextPos)
{
    OptionalDirections options;
    Posb currPos = _posb;

    if (currPos.i < nextPos.i)
        options.push(Movable::Direction::DOWN);

    if (currPos.i > nextPos.i)
        options.push(Movable::Direction::UP);

    if (currPos.j < nextPos.j)
        options.push(Movable::Direction::RIGHT);

    if (currPos.j > nextPos.j)
        options.push(Movable::Direction::LEFT);

    return options;
}

bool AIEnemy::finishedRunAway()
{
    return _runAway.path.empty();
}

void AIEnemy::goToShelterState()
{
    _enemyState = IN_SHELTER_S;
    _shelter.time = _enemyProxy->getElapsedTimeAsSeconds();
}

bool AIEnemy::enoughTimeInShelter(float shelterTime)
{
    return _enemyProxy->getElapsedTimeAsSeconds() - _shelter.time >= shelterTime;
}

void AIEnemy::placeDynamite(BoardProxy& board)
{
    BomberMan::placeDynamite(board);
}