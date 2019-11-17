#pragma once
/* Base class for all objects that use collisions to check the tiles around them.
Almost all of the operation involved in movement are preformed in this class.

Explosions are also derived from this class although they don't really move
but they need to collide with the tiles around them.
*/

#include "GameObject.h"
#include "definitions.h"

class BoardProxy;

// If an object gets teleported there a 3 seconds gap before it
// gets teleported again (so that it won't get into an infinite loop).
const float TELEPORTATION_GAP = 3;

class Movable : public GameObject
{
public:
    enum Direction { UP, DOWN, LEFT, RIGHT, UNDEFINED };

    Movable(const Posf& posf, const Posb& posi);

    virtual ~Movable() = 0;

    // each derived class has to call this at the beginning of her
    // override update method!!!
    virtual void update() override;

protected:
    // movement per frame = speed*MOVE_PER_FRAME.
    // _speed has min and max. see readme.
    int _speed = 1;

    // tries to move the object in the direction and returns true
    // if it moved and false if not.
    bool tryMove(const Movable::Direction dir);

    // face the user at the beginning.
    Direction _direction = DOWN;

    // flag if the object changed a tile on the board.
    // not every movement is a change in tile. there movement offsets
    // and also the object could collide with unpassable obstacle
    bool _movedTile = false;

    // make the object colidewith all objects in the next tile
    void colideWithNextTile(const Posb& nextTilePos);

    // each movable type can has it's own pausing Time
    bool timeToMove(float movePause) const;
    void setLastMoveToNow();
    float _lastMove = 0;

    // tell the board that the object moved so it could update the buffer
    void setMoveOnBoard();

    // teleport the object.
    // teleportation is a special case of movment.
    void teleport(Teleport& teleport);

    // for a movable object that's going in a direction,
    // get the next tile in his path.
    Posb getPosbInDirection(Movable::Direction dir) const;

    // save information about the position offset (movement inside tiles)
    // so we can draw the object and know when it changed a tile.
    struct PosfOffset
    {
        Posf offsetCounter = {0, 0};
        float x = 0, y = 0;
        bool movedInOffset = false;

    } _moveOffset;

private:
    // can't be public because it doesn't take into account the offset counter
    // which can lead to accidents if wrong object uses it.. The objects animation
    // won't update correctly.
    // if an object needs to move one tile each time (explosions) give it a speed
    // of TILE_SIZE.
    bool tryMove(Posb& nextPos);

    // save information about teleportation
    struct Teleported
    {
        Teleported() : teleported(false), twinPosb({Posb::INVALID_POS, Posb::INVALID_POS}), _lastTeleportation(0)
        {}

        bool teleported;
        Posb twinPosb;
        float _lastTeleportation;
    } _teleportationInfo;

    Posb getPosbFromOffset();

    void takeOffset(Direction dir);

    void updateOffsetCounter();

    // save the next position. The position only updates at the end of the move.
    Posb _nextPosb;
};
