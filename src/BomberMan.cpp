#include "BomberMan.h"
#include "Dynamite.h"
#include "BoardProxy.h"
#include "GraphicObjectsManager.h"
#include "AudioManager.h"
#include "FreeTile.h"
#include "StoneWall.h"
#include "ExplodingWall.h"
#include "Teleport.h"
#include "Bonus.h"
#include "Explosion.h"

const float HIT_DURATION = 2;
const int MAX_HEALTH = 5;

BomberMan::BomberMan(const Posf& posf, const Posb& posb)
    : Movable(posf, posb), _bomberManProxy(*this)
{
    _sprite.setTexture(GraphicObjectsManager::getInstance().getTexture(BOMBER_MAN_T));
    _animations = GraphicObjectsManager::getInstance().getBomberManAnimations();
    _sprite.setVisibleRect(_animations[DOWN_A].getFrame());

    _hit.hitFrameDuration = HIT_DURATION / _animations[EXPLODING_A].getNumOfFrames();


    _dyingSound = AudioManager::getInstance().getSound(AudioManager::DIE);
    _hitSound = AudioManager::getInstance().getSound(AudioManager::GETTING_HIT);


}


BomberMan::~BomberMan()
{
}


void BomberMan::updateAnimation()
{
    if (_bomberManState == LAST_EXPLOSION_S)
    {
        if (!enoughTime(_hit.hitTime, HIT_DURATION))
        {
            _animations[EXPLODING_A].update(getTimeAsSeconds(), _hit.hitFrameDuration);
            _sprite.setVisibleRect(_animations[_currAnimation].getFrame());

        }
        // else - last explosions's over.. now dead..
        else
        {
            _bomberManState = COMPLETELY_DEAD_S;
            _sprite.setTexture(GraphicObjectsManager::getInstance().getTexture(GRAVE_T));
            restoreVisibleRect();
        }
        return;

    }

    else if (_bomberManState == EXPLODING_S)
    {
        _currAnimation = EXPLODING_A;

        if (!enoughTime(_hit.hitTime, HIT_DURATION))
        {
            _animations[_currAnimation].update(getTimeAsSeconds(), _hit.hitFrameDuration);
            _sprite.setVisibleRect(_animations[_currAnimation].getFrame());
            

        }
        else
        {
            _bomberManState = PLAYING_S;

            _currAnimation = getAnimationFromDirection();
            _sprite.setVisibleRect(_animations[_currAnimation].getFrame());
        }
        
    }

    else if (_moveOffset.movedInOffset) {
        _currAnimation = getAnimationFromDirection();
        _animations[_currAnimation].update(_boardProxy->getElapsedTimeAsSeconds(), 0);
        _sprite.setVisibleRect(_animations[_currAnimation].getFrame());

    }

}


void BomberMan::placeDynamite(BoardProxy& board)
{
    if (_availbleDynamites > 0)
    {
        board.placeDynamite(std::move(dynamite_up(new Dynamite(_posf, _posb, _explosionRadius, _sprite.getColor(),
            _bomberManProxy, _boardProxy->getExplosionProxy()))));
        --_availbleDynamites;
    }
}

BomberMan::Animations BomberMan::getAnimationFromDirection()
{
    switch (_direction)
    {
        case Movable::UP:
            return UP_A;
            break;

        case Movable::DOWN:
            return DOWN_A;
            break;

        case Movable::LEFT:
            return LEFT_A;
            break;

        case Movable::RIGHT:
            return RIGHT_A;
            break;


            // bomberMan facing forward.
        default:
            return DOWN_A;

            break;
    }
}

void BomberMan::hitFromExplosion()
{
    if (_bomberManState == EXPLODING_S
        || _bomberManState == LAST_EXPLOSION_S 
        || _bomberManState == COMPLETELY_DEAD_S) {
        return;
    }

    _hitSound->play();

    _health -= HEALTH_CHANGE;
    if (_health <= 0) {
        _bomberManState = LAST_EXPLOSION_S;
        _dyingSound->play();
    }
    else
    {
        _bomberManState = EXPLODING_S;

    }
    _currAnimation = EXPLODING_A;

    _hit.hitTime = _boardProxy->getElapsedTime().asSeconds();

}

BomberMan::State BomberMan::getState() const
{
    return _bomberManState;
}


void BomberMan::colide(GameObject& other)
{
    other.colide(*this);
}

void BomberMan::colide(Dynamite& other)
{
    if (_kickability) {
        other.kicked(_direction);
    }

    _movedTile = true;
}

void BomberMan::colide(Explosion& other)
{
    (void)other;
    hitFromExplosion();
    _movedTile = true;
}

void BomberMan::colide(BomberMan& other)
{
    (void)other;
    _movedTile = true;
}


void BomberMan::colide(FreeTile& other)
{
    (void)other;
    _movedTile = true;

}

void BomberMan::colide(StoneWall& other)
{
    (void)other;
    _movedTile = false;
}

void BomberMan::colide(ExplodingWall& other)
{
    (void)other;
    _movedTile = false;
}

void BomberMan::colide(Teleport& other)
{
    _movedTile = true;
    teleport(other);

}

void BomberMan::colide(Bonus& other)
{
    switch (other.getType())
    {
        case Bonus::BonusType::HEALTH:
            _health += HEALTH_CHANGE;
            if (_health > MAX_HEALTH)
                _health = MAX_HEALTH;
            break;


        case Bonus::BonusType::SPEED:
            ++_speed;
            break;

        case Bonus::BonusType::EXPLOSION_RADIUS:
            ++_explosionRadius;
            break;

        case Bonus::BonusType::MORE_DYNAMITES:
            ++_availbleDynamites;
            break;

        case Bonus::BonusType::KICKABILITY:
            _kickability = true;
            break;


    }
    _movedTile = true;
    _boardProxy->removeBonus(&other);
}

// call back from dynamite
void BomberMan::dynamiteExploded()
{
    ++_availbleDynamites;
}


