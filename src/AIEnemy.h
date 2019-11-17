#pragma once
/* Base Class for enemies. enemies can differ in the order of
updating their state. 
*/
#include "BomberMan.h"
#include "definitions.h"
#include <memory>
#include "AIMap.h"

using std::pair;
class EnemyBoardProxy;

class GameObject;
class Player;
class AIEnemy;
class Bonus;
class Dynamite;

typedef pair<bool, Movable::Direction> HasDirection;
typedef stack<Movable::Direction> OptionalDirections;

class AIEnemy : public BomberMan
{
public:

    enum EnemyState
    {
        RUNAWAY_S,

        IN_SHELTER_S,
        ATTACKING_S,
        REACHED_TARGET_S
    };


    AIEnemy(const Posf& posf, const Posb& posb, int enemyNum);

    void setEnemyProxy(EnemyBoardProxy* enemyProxy);

    virtual ~AIEnemy() = 0;

protected:

    EnemyBoardProxy* _enemyProxy;

    struct Attack
    {
        Posb generalDirection;
        Path path;

    }_attack;


    void goToAttackState();
    void continueInAttackPath();
    bool finishedAttackPath();


    // 
    virtual void placeDynamite(BoardProxy& board) override;


    struct RunAway
    {
        // time of danger discovery.
        float time = 0;
        Path path;

    }_runAway;


    void goToRunAwayState();
    void continueInRunAwayPath();
    bool finishedRunAway();


    struct Shelter
    {
        float time = 0; 
    } _shelter;

    void goToShelterState();
    bool enoughTimeInShelter(float shelterTime);


    OptionalDirections directionToPos(const Posb& pos);

    bool isFreeTile(Movable::Direction dir);


    EnemyState _enemyState = ATTACKING_S;

    // in danger means standing on potential explosion
    bool inDanger() const;
    bool dangerousPos(const Posb& pos, DangerType danger) const;
};

