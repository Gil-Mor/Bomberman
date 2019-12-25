#include "Explosion.h"
#include "Dynamite.h"
#include "BomberMan.h"
#include "Chronometer.h"
#include "ExplosionsBoardProxy.h"
#include "FreeTile.h"
#include "StoneWall.h"
#include "ExplodingWall.h"
#include "Teleport.h"
#include "Bonus.h"
#include "GraphicObjectsManager.h"

const float PROPAGATE_DURATION = 0.2;
const float EXPLOSION_DURATION = 1;

// static
// Explosion::AnimationInfo Explosion::_animation;

Explosion::Explosion(
    const Posf& posf, const Posb& posb, size_t radius, Color color, ExplosionsBoardProxy& explosionProxy) :
    Movable(posf, posb),
    _explosionProxy(explosionProxy), _radius(radius)
{
    _center = true;
    _propagate = true;

    Init(color);
}

// private ctor
Explosion::Explosion(
    const Posf& posf,
    const Posb& posb,
    size_t radius,
    Color color,
    Movable::Direction dir,
    ExplosionsBoardProxy& explosionProxy) :
    Movable(posf, posb),
    _explosionProxy(explosionProxy), _radius(radius)
{
    _direction = dir;
    _propagate = true;

    Init(color);
}

void Explosion::Init(const Color& color)
{
    // very important.. the explosions has to move one tile each move.
    _speed = TILE_SIZE.x;

    _explosionTime = _explosionProxy.getElapsedTime().asSeconds();

    _animation.animation = GraphicObjectsManager::getInstance().getExplosionsAnimation();
    _animation.frameDuration = EXPLOSION_DURATION / _animation.animation.getNumOfFrames();

    _sprite.setTexture(GraphicObjectsManager::getInstance().getTexture(EXPLOSION_T));
    _sprite.setVisibleRect(_animation.animation.getFrame());

    _sprite.setColor(color);

    setObjectBoardProxy(&_explosionProxy);
}

Explosion::~Explosion()
{}

void Explosion::update()
{
    // if it's time to explode
    if (_propagate && _explosionProxy.getElapsedTime().asSeconds() - _explosionTime >= PROPAGATE_DURATION) {
        size_t saveRadius = _radius;
        // center explosion propagate all 4 directions
        if (_center && _propagate) {
            // the center also has to collide with objects.
            colideWithNextTile(_posb);

            Posb pos = getPosbInDirection(UP);
            if (tryMove(UP)) {
                _explosionProxy.placeExplosion(explosion_up(new Explosion(
                    _explosionProxy.getTilePosf(pos), pos, _radius - 1, _sprite.getColor(), UP, _explosionProxy)));
            }

            // in case one direction radius was reduced.
            _radius = saveRadius;

            pos = getPosbInDirection(DOWN);

            if (tryMove(DOWN)) {
                _explosionProxy.placeExplosion(explosion_up(new Explosion(
                    _explosionProxy.getTilePosf(pos), pos, _radius - 1, _sprite.getColor(), DOWN, _explosionProxy)));
            }

            // in case one direction radius was reduced.
            _radius = saveRadius;

            pos = getPosbInDirection(LEFT);

            if (tryMove(LEFT)) {
                _explosionProxy.placeExplosion(explosion_up(new Explosion(
                    _explosionProxy.getTilePosf(pos), pos, _radius - 1, _sprite.getColor(), LEFT, _explosionProxy)));
            }

            // in case one direction radius was reduced.
            _radius = saveRadius;

            pos = getPosbInDirection(RIGHT);
            if (tryMove(RIGHT)) {
                _explosionProxy.placeExplosion(explosion_up(new Explosion(
                    _explosionProxy.getTilePosf(pos), pos, _radius - 1, _sprite.getColor(), RIGHT, _explosionProxy)));
            }
        }

        // else directed explosion moves in it's own direction.
        else if (_propagate && _radius > 0) {
            // if it can move in his direction
            Posb nextPos = getPosbInDirection(_direction);
            if (tryMove(_direction) && stillPropagate()) {
                _explosionProxy.placeExplosion(explosion_up(new Explosion(
                    _explosionProxy.getTilePosf(nextPos),
                    nextPos,
                    _radius - 1,
                    _sprite.getColor(),
                    _direction,
                    _explosionProxy)));
            }
        }

        // PROPAGATE ONCE!!!!!!!!!!!!!!!!!!
        _propagate = false;
    }

    else if (_explosionProxy.getElapsedTime().asSeconds() - _explosionTime >= EXPLOSION_DURATION) {
        _explosionProxy.removeExplosionFromBoard(this);
    }

    _animation.animation.update(_boardProxy->getElapsedTimeAsSeconds(), _animation.frameDuration);
    _sprite.setVisibleRect(_animation.animation.getFrame());
}

// void Explosion::update() {
//
//    // render stuff...
//}

bool Explosion::stillPropagate() const
{
    return _radius > 0 && _propagate;
}

void Explosion::colide(GameObject& other)
{
    other.colide(*this);
}

void Explosion::colide(Dynamite& other)
{
    (void)other;
    _movedTile = true;
}

void Explosion::colide(Explosion& other)
{
    (void)other;
    _movedTile = true;
}

void Explosion::colide(BomberMan& other)
{
    _movedTile = true;
    other.hitFromExplosion();
    // other.colide(*this);
}

void Explosion::colide(FreeTile& other)
{
    (void)other;
    _movedTile = true;
}

void Explosion::colide(StoneWall& other)
{
    (void)other;
    _propagate = false;
    _movedTile = false;
}

void Explosion::colide(ExplodingWall& other)
{
    _radius = 1; // propagate one more explosion
    other.explode();

    _movedTile = true;
}

void Explosion::colide(Teleport& other)
{
    (void)other;
    _movedTile = true;
}

void Explosion::colide(Bonus& other)
{
    (void)other;
    _movedTile = true;
}