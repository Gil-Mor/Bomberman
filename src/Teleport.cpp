#include "Teleport.h"
#include "Dynamite.h"
#include "Explosion.h"
#include "BomberMan.h"
#include "GraphicObjectsManager.h"
#include "BoardProxy.h"
#include "AudioManager.h"

const float FRAME_DURATION = 0.2;
const float TELEPORTATION_DURATION = 3;

Teleport::Teleport(const Posf& posf, const Posb& posb, int ID)
    : GameObject(posf, posb), _ID(ID)
{

    _sprite.setTexture(GraphicObjectsManager::getInstance().getTexture(TELEPORT_T));
    

    _animations = GraphicObjectsManager::getInstance().getTeleportAnimation();

    _activeDuration = _animations[ACTIVE_A].getNumOfFrames() / TELEPORTATION_DURATION;

    _sprite.setVisibleRect(_animations[_currAnimation].getFrame());

    Color color;

    _teleportSound = AudioManager::getInstance().getSound(AudioManager::TELEPORT);


    if (ID == 1) {
        color = { 255, 255, 255, 255 };

    }
    if (ID == 2) {
        color = { 0, 100, 220, 255 };
    }

    if (ID == 3) {
        color = { 0, 214, 100, 255 };
    }

    if (ID == 4) {
        color = { 200, 0, 200, 255 };
    }

    if (ID == 4) {
        color = { 100, 100, 200, 255 };
    }

    _sprite.setColor(color);
}


void Teleport::update() 
{

    if (_currAnimation == ACTIVE_A) {
        if (enoughTime(_teleportationTime, _activeDuration))
        {
            _currAnimation = REST_A;
        }
    }

    _animations[_currAnimation].update(getTimeAsSeconds(), FRAME_DURATION);
    _sprite.setVisibleRect(_animations[_currAnimation].getFrame());

}


void Teleport::setTwinPos(const Posb& pos)
{
    _twinPos = pos;
    twinWasSet = true; // for debugging when building level.
}


void Teleport::activate()
{
    _currAnimation = ACTIVE_A;
    _teleportationTime = getTimeAsSeconds();
    _teleportSound->play();
}

size_t Teleport::getID() const
{
    return _ID;
}

const Posb& Teleport::getTwinPosition() const
{
    return _twinPos;
}

bool Teleport::getHasTwin() const
{
    return twinWasSet;
}

void Teleport::colide(GameObject& other)
{
    other.colide(*this);
}

void Teleport::colide(Dynamite& other)
{
    activate();
    other.colide(*this);
}

void Teleport::colide(Explosion& other)
{
    other.colide(*this);
}

void Teleport::colide(BomberMan& other)
{
    activate();
    other.colide(*this);
}