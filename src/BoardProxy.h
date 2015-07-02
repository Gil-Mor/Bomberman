#pragma once
/* Base class for all board proxies. Has methods that mostly the player uses. 
Different game objects use mostly getelapsedTime. enemyBoardProxy and
ExplosionBoardProxy are derived from this class and they also use most of the 
methods that the player uses. 
*/

#include <memory>
#include "definitions.h"

class Dynamite;
class GameObject;
class ExlodingWall;
class Bonus;
class ExplosionsBoardProxy; // for bomber man to give to dynamites which gives to explosions.
                            // much safer

class Board;

class BoardProxy
{
public:

    BoardProxy(Board& level);
    ~BoardProxy();

    const tile& getTile(const Posb& cell) const;

    void moveOnBoard(GameObject* obj, const Posb& from, const Posb& to);

    // all the different removal and add methods are needed
    // to update the board in the board buffer.
    void removeExplodingWall(ExplodingWall* wall);
    void removeBonus(Bonus* bonus);

    void placeBonus(bonus_up& bonus);
    void placeDynamite(dynamite_up& dynamite);

    sf::Time getElapsedTime() const;

    float getElapsedTimeAsSeconds() const;


    const Posf& getTilePosf(const Posb& posb) const;

    bool validPosb(const Posb& posb) const;


    // BomberMan gets the explosion proxy just to give it to 
    // dynamites on creation.
     ExplosionsBoardProxy& getExplosionProxy() ;


protected:
    Board& _board;
};

