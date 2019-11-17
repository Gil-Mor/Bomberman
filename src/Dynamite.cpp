#include "Dynamite.h"
#include "BomberManProxy.h"
#include "Explosion.h"
#include "ExplosionsBoardProxy.h"
#include "BomberMan.h"
#include "FreeTile.h"
#include "StoneWall.h"
#include "ExplodingWall.h"
#include "Teleport.h"
#include "Bonus.h"
#include "GraphicObjectsManager.h"
#include "AudioManager.h"

const float TICKING_TIME = 2;

Dynamite::Dynamite(const Posf& posf, const Posb& posb, const size_t& radius, Color color, 
    BomberManProxy& owner, ExplosionsBoardProxy& explosionProxy)
    : Movable(posf, posb), _radius(radius), _owner(owner), _dynamiteProxy(explosionProxy)
{
    
    _sprite.setTexture(GraphicObjectsManager::getInstance().getTexture(DYNAMITE_T));
    _sprite.setColor(color);

    _animation.animation = GraphicObjectsManager::getInstance().getDynamiteAnimation();
    _animation.frameDuration = TICKING_TIME / _animation.animation.getNumOfFrames();
    _sprite.setVisibleRect(_animation.animation.getFrame());

    _explosionSound = AudioManager::getInstance().getSound(AudioManager::EXPLOSION);
    _tickSound = AudioManager::getInstance().getSound(AudioManager::DYNAMITE_TICK);



    setObjectBoardProxy(&_dynamiteProxy);
    _triggeredTime = _dynamiteProxy.getElapsedTime().asSeconds();

    _tickSound->play();
}

Dynamite::~Dynamite()
{
}

void Dynamite::update()
{

    Movable::update();

    // moving at the beginning. stop moving as soon as stopped once.
    // _moving is dynamite's continuous '_moved' boolean. if it's stopped once
    // it won't move again.
    if (_kicked && _moving) {
        tryMove(_direction);
        if (_moving) 
        {
            setMoveOnBoard();

        }
    }


    _animation.animation.update(_boardProxy->getElapsedTimeAsSeconds(), _animation.frameDuration);
    _sprite.setVisibleRect(_animation.animation.getFrame());

    if (_boardProxy->getElapsedTimeAsSeconds() - _triggeredTime >= TICKING_TIME)
    {
        explode();
    }

   
}


void Dynamite::explode()
{

    _tickSound->stop();
    // let the owner know that this dynamite exploded
    _owner.dynamiteExploded();



    _dynamiteProxy.placeExplosion(explosion_up(new Explosion(_posf, _posb, _radius,
        _sprite.getColor(), _dynamiteProxy)));

    _dynamiteProxy.removeDynamiteFromBoard(this);
    _explosionSound->play();

}

void Dynamite::kicked(Movable::Direction dir)
{
    _kicked = true;
    _moving = true;

    _direction = dir;
}


void Dynamite::colide(GameObject& other)
{
    other.colide(*this);
}

void Dynamite::colide(Dynamite& other)
{
    _movedTile = true;
    _moving = true;
}

void Dynamite::colide(Explosion& other)
{
    _movedTile = true;
    _moving = true;

}

void Dynamite::colide(BomberMan& other)
{
    _movedTile = false;
    _moving = false;
}


void Dynamite::colide(FreeTile& other)
{
    _movedTile = true;
    _moving = true;

}

void Dynamite::colide(StoneWall& other)
{
    _movedTile = false;

}

void Dynamite::colide(ExplodingWall& other)
{
    _movedTile = false;
}

void Dynamite::colide(Teleport& other)
{
    _movedTile = true;
    _moving = true;

    teleport(other);
}

void Dynamite::colide(Bonus& other)
{
    _movedTile = true;
    _moving = true;

}

int Dynamite::getExplosionRadius() const
{
    return _radius;
}
