#include "FreeTile.h"
#include "Dynamite.h"
#include "Explosion.h"
#include "BomberMan.h"
#include "GraphicObjectsManager.h"


FreeTile::FreeTile(const Posf& posf, const Posb& posb)
    : GameObject(posf, posb)
{
    _sprite.setColor(Color::Transparent);
}


FreeTile::~FreeTile()
{
}

void FreeTile::colide(GameObject& other)
{
    other.colide(*this);
}

void FreeTile::colide(Dynamite& other)
{
    other.colide(*this);
}

void FreeTile::colide(Explosion& other)
{
    other.colide(*this);
}

void FreeTile::colide(BomberMan& other)
{
    other.colide(*this);
}
