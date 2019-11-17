#pragma once
/* Unpassable barrier. */
#include "GameObject.h"
class BoardProxy;

class StoneWall : public GameObject
{
public:
    StoneWall(const Posf& posf, const Posb& posb);

    
    virtual ~StoneWall();

    // ----------- DOUBLE DISPATCH ------------
    virtual void colide(GameObject& other) override;

    virtual void colide(Dynamite& other) override;

    virtual void colide(Explosion& other) override;

    virtual void colide(BomberMan& other) override;
};

