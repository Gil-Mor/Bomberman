#include "ExplodingWall.h"
#include "GraphicObjectsManager.h"
#include "Dynamite.h"
#include "Explosion.h"
#include "BomberMan.h"
#include "BoardProxy.h"

const float EXPLOSION_DURATION = 1;

// ExplodingWall::ExplodingWall(const Posf& posf, const Posb& posb, bonus_up bonus)
//    : GameObject(posf, posb), _bonus(std::move(bonus))
//{
//    _hasBonus = true;
//
//    Init();
//
//
//}
//
// ExplodingWall::ExplodingWall(const Posf& posf, const Posb& posb)
//    : GameObject(posf, posb)
//{
//    _bonus.reset(nullptr);
//    _hasBonus = false;
//
//    Init();
//
//
//}

ExplodingWall::ExplodingWall(const Posf& posf, const Posb& posb, Bonus::BonusType bonus) :
    GameObject(posf, posb), _bonusType(bonus)
{
    Init();
}

void ExplodingWall::Init()
{
    _sprite.setTexture(GraphicObjectsManager::getInstance().getTexture(EXPLODING_WALL_T));

    _explosion.animation = GraphicObjectsManager::getInstance().getExplodingWallAnimation();

    _explosion.frameDuration = EXPLOSION_DURATION / _explosion.animation.getNumOfFrames();

    _sprite.setVisibleRect(_explosion.animation.getFrame());
}

ExplodingWall::~ExplodingWall()
{}

void ExplodingWall::update()
{
    if (_explosion.exploded) {
        if (_boardProxy->getElapsedTimeAsSeconds() - _explosion.timeOfExplosion >= EXPLOSION_DURATION) {
            if (_bonusType != Bonus::BonusType::NONE) {
                _boardProxy->placeBonus(std::move(bonus_up(new Bonus(_posf, _posb, _bonusType))));
            }

            _boardProxy->removeExplodingWall(this);
        }

        _explosion.animation.update(_boardProxy->getElapsedTimeAsSeconds(), _explosion.frameDuration);
        _sprite.setVisibleRect(_explosion.animation.getFrame());
    }
}

void ExplodingWall::explode()
{
    _explosion.exploded = true;
    _explosion.timeOfExplosion = _boardProxy->getElapsedTimeAsSeconds();
}

void ExplodingWall::colide(GameObject& other)
{
    other.colide(*this);
}

void ExplodingWall::colide(Dynamite& other)
{
    other.colide(*this);
}

void ExplodingWall::colide(Explosion& other)
{
    explode();
    other.colide(*this);
}

void ExplodingWall::colide(BomberMan& other)
{
    other.colide(*this);
}
