#pragma once
/* Base class for all game objects. an object has a board position, 
graphic position (Posf), sprite, etc..
Virtual collide functions with all moving objects.
*/

#include "definitions.h"
#include "Sprite.h"
#include <memory>

class GraphicWindow;

/* For das Double Dispatch. */
class Dynamite;
class Explosion;
class BomberMan;
class Bonus;
class FreeTile;
class ExplodingWall;
class StoneWall;
class Teleport;



class BoardProxy;

const Posf TILE_SIZE = { 35, 35 };

class GameObject
{
public:

    GameObject(const Posf& posf, const Posb& posb);

    void setObjectBoardProxy(BoardProxy* board);

    virtual ~GameObject() = 0;


    // movable and non movable objects need to update their next state
    // and animations. it's very general..
    virtual void update();


    // this does the drawing of inanimated sprites..
    // animated objects should override this.
    virtual void draw(GraphicWindow& window);


    const Posf& getPosf() const;
    const Posb& getPosb() const;

    float getTimeAsSeconds() const;

    bool enoughTime(float since, float duration);

    // ----------- DOUBLE DISPATCH ------------
    
    virtual void colide(GameObject& other) = 0;

    virtual void colide(Dynamite& other) = 0;

    virtual void colide(Explosion& other) = 0;

    virtual void colide(BomberMan& other) = 0;


protected:

    // general proxy for all objects. 
    // since I'm using level builder it's impossible to give th objects
    //  on construction because the board doesn't exist when they are create.
    // they need the elapsed time
    BoardProxy* _boardProxy;


    Posb _posb;
    Posf _posf;

    Sprite _sprite;


    // for objects with animation, restores their texture rect to 
    // the position of the first frame.
    void restoreVisibleRect();
};

