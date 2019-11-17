#pragma once
/* A Free tile*/
#include "GameObject.h"
class FreeTile : public GameObject
{
public:
    FreeTile(const Posf& posf, const Posb& posb);
    ~FreeTile();

    // ----------- DOUBLE DISPATCH ------------
    virtual void colide(GameObject& other) override;

    virtual void colide(Dynamite& other) override;

    virtual void colide(Explosion& other) override;

    virtual void colide(BomberMan& other) override;
};
