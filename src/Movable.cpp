#include "Movable.h"
#include "BoardProxy.h"
#include "Teleport.h"

const float MOVE_PER_FRAME = TILE_SIZE.x / 5.f;
const float COLLISION_BOX_SIZE = TILE_SIZE.x / 4.f;

Movable::Movable(const Posf& posf, const Posb& posb) : GameObject(posf, posb), _nextPosb(posb)
{}

Movable::~Movable()
{}

bool Movable::tryMove(const Direction dir)
{
    if (dir == Direction::UNDEFINED) {
        return false;
    }

    _movedTile = false;
    _direction = dir;

    _moveOffset.movedInOffset = true;

    takeOffset(dir);

    Posf prevOffset = _moveOffset.offsetCounter;

    _moveOffset.offsetCounter += Posf(_moveOffset.x, _moveOffset.y);

    Posb posFromOffset = getPosbFromOffset();

    // if not enough offset we don't change position but keep the offset
    if (posFromOffset == _posb) {
        _movedTile = false;
        return false;
    }

    // only when the object moves between tiles collide it with the next tile.
    bool success = tryMove(posFromOffset);

    // got stuck in obsticle.
    if (!success) {
        _moveOffset.offsetCounter = prevOffset;
        _moveOffset.movedInOffset = false;
    }

    updateOffsetCounter();

    return success;
}

bool Movable::tryMove(Posb& nextPos)
{
    if (!_boardProxy->validPosb(nextPos)) {
        return false;
    }

    if (nextPos != _posb) {
        colideWithNextTile(nextPos);
    }

    if (_movedTile && !_teleportationInfo.teleported) {
        _nextPosb = nextPos;
    }

    return _movedTile;
}

void Movable::updateOffsetCounter()
{
    if (_movedTile) {
        _moveOffset.offsetCounter = -_moveOffset.offsetCounter;
    }
}

void Movable::takeOffset(Movable::Direction dir)
{
    switch (dir) {
        case UP:
            _moveOffset.y = -_speed * MOVE_PER_FRAME;
            _moveOffset.x = 0;
            _moveOffset.offsetCounter.x = 0;
            break;

        case DOWN:
            _moveOffset.y = _speed * MOVE_PER_FRAME;
            _moveOffset.x = 0;
            _moveOffset.offsetCounter.x = 0;
            break;

        case LEFT:
            _moveOffset.x = -_speed * MOVE_PER_FRAME;
            _moveOffset.y = 0;
            _moveOffset.offsetCounter.y = 0;
            break;

        case RIGHT:
            _moveOffset.x = _speed * MOVE_PER_FRAME;
            _moveOffset.y = 0;
            _moveOffset.offsetCounter.y = 0;
            break;

        default:
            break;
    }
}

Posb Movable::getPosbFromOffset()
{
    Posf fixedPos = _boardProxy->getTilePosf(_posb);

    Posb nextPos = _posb;

    Posf mytopLeftPosf = _moveOffset.offsetCounter + _posf;

    // moved to the left tile
    if (_direction == LEFT && mytopLeftPosf.x <= fixedPos.x - COLLISION_BOX_SIZE) {
        _moveOffset.offsetCounter.x = -COLLISION_BOX_SIZE;
        --nextPos.j;
    }

    // moved to the right tile
    else if (_direction == RIGHT && mytopLeftPosf.x + TILE_SIZE.x > fixedPos.x + TILE_SIZE.x + COLLISION_BOX_SIZE) {
        _moveOffset.offsetCounter.x = COLLISION_BOX_SIZE;

        ++nextPos.j;
    }

    // moved to upper tile
    else if (_direction == UP && mytopLeftPosf.y < fixedPos.y - COLLISION_BOX_SIZE) {
        _moveOffset.offsetCounter.y = -COLLISION_BOX_SIZE;

        --nextPos.i;
    }

    // moved down
    else if (_direction == DOWN && mytopLeftPosf.y + TILE_SIZE.y > fixedPos.y + TILE_SIZE.y + COLLISION_BOX_SIZE) {
        _moveOffset.offsetCounter.y = COLLISION_BOX_SIZE;

        ++nextPos.i;
    }
    return nextPos;
}

void Movable::colideWithNextTile(const Posb& nextTilePos)
{
    const tile& nextTile = _boardProxy->getTile(nextTilePos);

    // if there is something in the position then collide with it.
    // action only happen in collisions.
    for (auto& object : nextTile) {
        object->colide(*this);
    }
}

void Movable::setMoveOnBoard()
{
    if (_movedTile) {
        if (_teleportationInfo.teleported) {
            _nextPosb = _teleportationInfo.twinPosb;
        }

        _posf = _boardProxy->getTilePosf(_nextPosb);
        _boardProxy->moveOnBoard(this, _posb, _nextPosb);
    }
}

void Movable::update()
{
    if (_movedTile) {
        _posb = _nextPosb;
    }

    _sprite.setPosition(_posf + _moveOffset.offsetCounter);
    _moveOffset.movedInOffset = false;
    _movedTile = false;
    _teleportationInfo.teleported = false;
}

void Movable::teleport(Teleport& teleport)
{
    if (_boardProxy->getElapsedTime().asSeconds() - _teleportationInfo._lastTeleportation >= TELEPORTATION_GAP) {
        _teleportationInfo.teleported = true;
        _teleportationInfo._lastTeleportation = _boardProxy->getElapsedTime().asSeconds();
        _teleportationInfo.twinPosb = teleport.getTwinPosition();
        _nextPosb = _teleportationInfo.twinPosb;

    } else {
        _nextPosb = teleport.getPosb();
    }
}

Posb Movable::getPosbInDirection(Movable::Direction dir) const
{
    Posb nextPosb = _posb;

    if (dir == UP) {
        --nextPosb.i;
    }

    else if (dir == DOWN) {
        ++nextPosb.i;
    }

    else if (dir == LEFT) {
        --nextPosb.j;
    }

    else if (dir == RIGHT) {
        ++nextPosb.j;
    }

    return nextPosb;
}

bool Movable::timeToMove(float movePause) const
{
    float now = _boardProxy->getElapsedTime().asSeconds();

    if (now - _lastMove >= movePause) {
        return true;
    }
    return false;
}

void Movable::setLastMoveToNow()
{
    _lastMove = _boardProxy->getElapsedTime().asSeconds();
}
