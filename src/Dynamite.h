#pragma once
/* The bomb. Placed by BomberManon the board, ticks, and then places an explosion. 
Dynamites and explosions have a special "Explosion Board Proxy" so that only them can
place explosions on th board. just a security so that BomberMan won't place an explosion
instead of a dynamite.
*/
#include "Movable.h"
#include "definitions.h"
#include "Animation.h"
#include "AudioManager.h"

class ExplosionsBoardProxy;
class BomberManProxy;

class Dynamite : public Movable
{
public:

    Dynamite(const Posf& posf, const Posb& posb, const size_t& radius, Color& color, 
        BomberManProxy& owner, ExplosionsBoardProxy& explosionProxy);

    //void setDynamiteProxy(ExplosionsBoardProxy* board);

    ~Dynamite();

    virtual void update() override;


    void kicked(Movable::Direction dir);

    int getExplosionRadius() const;

    // ----------- DOUBLE DISPATCH ------------
    virtual void colide(GameObject& other) override;

    virtual void colide(Dynamite& other) override;

    virtual void colide(Explosion& other) override;

    virtual void colide(BomberMan& other) override;

    virtual void colide(FreeTile& other);

    virtual void colide(StoneWall& other);

    virtual void colide(ExplodingWall& other);

    virtual void colide(Teleport& other);

    virtual void colide(Bonus& other);

private:

    ExplosionsBoardProxy& _dynamiteProxy;

    // Dynamite explosion radius.
    // explosion is the size of radius*tileSize
    size_t _radius = 2;

    void explode();

    // let the owner know when this exploded.
    BomberManProxy& _owner;

    // time when the dynamite was placed.
    float _triggeredTime = 0;

    bool _kicked = false;

    // when kicked. try to move and then stop trying as soon as you stop once.
    bool _moving = true;

    struct AnimationInfo
    {
        Animation animation;
        float frameDuration;
    } _animation;


    GameSound_p _tickSound, _explosionSound;

};

