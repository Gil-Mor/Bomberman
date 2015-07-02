#include "StoneWall.h"
#include "GraphicObjectsManager.h"
#include "Dynamite.h"
#include "Explosion.h"
#include "BomberMan.h"

StoneWall::StoneWall(const Posf& posf, const Posb& posb)
    : GameObject(posf, posb)
{
    _sprite.setTexture(GraphicObjectsManager::getInstance().getTexture(STONE_WALL_T));
}



StoneWall::~StoneWall()
{
}

void StoneWall::colide(GameObject& other)
{
    other.colide(*this);
}

void StoneWall::colide(Dynamite& other)
{
    other.colide(*this);
}

void StoneWall::colide(Explosion& other )
{
    other.colide(*this);
}

void StoneWall::colide(BomberMan& other)
{
    other.colide(*this);
}
