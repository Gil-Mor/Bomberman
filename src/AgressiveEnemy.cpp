#include "AgressiveEnemy.h"
#include "EnemyBoardProxy.h"
#include "Player.h"

const float AGRESSIVE_ATTACK_MOVE_PAUSE = 0.25;
const float AGRESSIVE_RUNAWAY_MOVE_PAUSE = 0.15;
const float AGRESSIVE_TIME_IN_SHELTER = 3.5;

// time to give the aggressive one to go in random direction.
const float MAX_RANDOM_DIRECTION_DURATION = 1;

const float AGGRESSIVE_BLOW_UP_WALLS_PAUSE = AGRESSIVE_TIME_IN_SHELTER + 2;

AgressiveEnemy::AgressiveEnemy(const Posf& posf, const Posb& posb, int enemyNum) : AIEnemy(posf, posb, enemyNum)
{}

AgressiveEnemy::~AgressiveEnemy()
{}

void AgressiveEnemy::update()
{
    Movable::update();

    switch (BomberMan::_bomberManState) {
        case BomberMan::COMPLETELY_DEAD_S:
        case LAST_EXPLOSION_S:
        case EXPLODING_S: {
            break;
        }

        case BomberMan::PLAYING_S: {
            if (!agressiveTimeToMove()) {
                break;
            }

            setLastMoveToNow();

            switch (AIEnemy::_enemyState) {
                case ATTACKING_S: {
                    if (inDanger()) {
                        goToRunAwayState();
                        break;
                    }
                    if (finishedAttackPath()) {
                        _enemyState = REACHED_TARGET_S;
                        break;
                    }
                    continueInAttackPath();
                    break;
                }

                case REACHED_TARGET_S: {
                    placeDynamite(*_enemyProxy);
                    // Immidiatly runaway after placing dynamite.
                    goToRunAwayState();
                    break;
                }

                case RUNAWAY_S: {
                    if (finishedRunAway()) {
                        goToShelterState();
                        break;
                    }
                    continueInRunAwayPath();
                    break;
                }
                case IN_SHELTER_S: {
                    if (inDanger()) {
                        goToRunAwayState();
                    }

                    else if (!enoughTimeInShelter(AGRESSIVE_TIME_IN_SHELTER)) {
                        break;
                    }

                    else {
                        goToAttackState();
                    }

                    break;
                }
            }
            break;
        }
        default:
            break;
    }

    updateAnimation();
}

void AgressiveEnemy::updateState()
{
    switch (_enemyState) {
        case ATTACKING_S: {
            if (inDanger()) {
                goToRunAwayState();
                break;
            }
            if (finishedAttackPath()) {
                _enemyState = REACHED_TARGET_S;
                break;
            }
            break;
        }

        case REACHED_TARGET_S: {
            if (inDanger()) {
                goToRunAwayState();
                break;
            }

            goToAttackState();

            break;
        }

        case RUNAWAY_S: {
            if (finishedRunAway()) {
                goToShelterState();
            }
            break;
        }

        case IN_SHELTER_S: {
            if (inDanger()) {
                goToRunAwayState();
            }

            if (!enoughTimeInShelter(AGRESSIVE_TIME_IN_SHELTER)) {
                break;
            }

            else {
                goToAttackState();
            }
            break;
        }
    }
}

bool AgressiveEnemy::agressiveTimeToMove()
{
    switch (_enemyState) {
        case ATTACKING_S:
            return timeToMove(AGRESSIVE_ATTACK_MOVE_PAUSE);

        case RUNAWAY_S:
            return timeToMove(AGRESSIVE_RUNAWAY_MOVE_PAUSE);

        case IN_SHELTER_S:
            return timeToMove(AGRESSIVE_ATTACK_MOVE_PAUSE);

        default:
            return true;
    }
}
