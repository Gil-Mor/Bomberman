#pragma once

/*Let's Dynamites and Explosions put explosions on the board.
only they can place explosions on th board.just a security so that 
BomberMan won't place an explosion instead of a dynamite.
*/


#include "BoardProxy.h"

class Explosion;

class ExplosionsBoardProxy : public BoardProxy
{
public:

    ExplosionsBoardProxy(Board& board);

    ~ExplosionsBoardProxy();

    void placeExplosion(explosion_up explosion);

    void removeDynamiteFromBoard(Dynamite* dynamite);

    void removeExplosionFromBoard(Explosion* dynamite);

};

