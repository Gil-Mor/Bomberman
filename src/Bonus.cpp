#include "Bonus.h"
#include "Dynamite.h"
#include "Explosion.h"
#include "BomberMan.h"
#include "GraphicObjectsManager.h"




Bonus::Bonus(const Posf& posf, const Posb& posb, const Bonus::BonusType& type)
    : GameObject(posf, posb), _type(type)
{
    _sprite.setTexture(GraphicObjectsManager::getInstance().getTexture(BONUSES_T));

    switch (type)
    {
        case MORE_DYNAMITES:
            _sprite.setVisibleRect(MORE_DYNAMITES_R);
            break;

        case EXPLOSION_RADIUS:
            _sprite.setVisibleRect(EXPLOSION_RADUIS_R);
            break;

        case SPEED:
            _sprite.setVisibleRect(SPEED_R);
            break;

        case KICKABILITY:
            _sprite.setVisibleRect(KICKABILITY_R);
            break;

        case HEALTH:
            _sprite.setVisibleRect(HEALTH_R);
            break;

        default:
            break;
    }
}

Bonus::~Bonus()
{}


void Bonus::colide(GameObject& other)
{
    other.colide(*this);
}

void Bonus::colide(Dynamite& other)
{
    other.colide(*this);
}

void Bonus::colide(Explosion& other)
{
    other.colide(*this);
}

void Bonus::colide(BomberMan& other)
{

    other.colide(*this);
}

Bonus::BonusType Bonus::getType() const
{
    return _type;
}