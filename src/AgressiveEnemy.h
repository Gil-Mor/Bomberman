#pragma once
/* an Enamy that chases the player. */
#include "AIEnemy.h"
class AgressiveEnemy :
    public AIEnemy
{
public:
    AgressiveEnemy(const Posf& posf, const Posb& posb, int enemyNum);
    virtual ~AgressiveEnemy();

    virtual void update() override;


protected:

    void updateState();

    bool agressiveTimeToMove();

};

