#pragma once
/* Exploding Walls that can contain a bonus. Explode when hit by explosion*/
#include "GameObject.h"
#include "Bonus.h"
#include "definitions.h"
#include "Animation.h"

class ExplodingWall : public GameObject
{
public:

    ExplodingWall(const Posf& posf, const Posb& posi, Bonus::BonusType type);



    virtual ~ExplodingWall();

    virtual void update() override;

    void explode();


    // ----------- DOUBLE DISPATCH ------------
    virtual void colide(GameObject& other) override;

    virtual void colide(Dynamite& other) override;

    virtual void colide(Explosion& other) override;

    virtual void colide(BomberMan& other) override;

private:

    Bonus::BonusType _bonusType;

    struct ExplosionInfo
    {
        Animation animation;
        bool exploded = false;
        float frameDuration;
        float timeOfExplosion;


    } _explosion;

    void Init();

};

