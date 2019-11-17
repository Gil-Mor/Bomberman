#pragma once
/* Explosion on a single tile. Dynamite puts a "center" explosion on the board.
The center explosion propagates 4 explosions in all 4 directions, 
then each one of them propagates in it's own direction.
Explosions don't move. they propagate. they create another explosion with radius <- radius - 1
until radius reaches 0.*/

#include "Movable.h"
#include "definitions.h"
#include "Animation.h"

class ExplosionsBoardProxy;

class Explosion : public Movable
{

public:

    // The dynamite uses this 
    Explosion(const Posf& posf, const Posb& posb, int radius, Color& color, 
        ExplosionsBoardProxy& explosionProxy);



    ~Explosion();

    // override movable update
    virtual void update() override;


    // ----------- DOUBLE DISPATCH ------------
    virtual void colide(GameObject&) override;

    virtual void colide(Dynamite&) override;

    virtual void colide(Explosion&) override;

    virtual void colide(BomberMan&) override;

    virtual void colide(FreeTile& other);

    virtual void colide(StoneWall& other);

    virtual void colide(ExplodingWall& other);

    virtual void colide(Teleport& other);

    virtual void colide(Bonus& other);

private:

    ExplosionsBoardProxy& _explosionProxy;

    int _radius;

    bool _propagate = false;
    bool _center = false;

    vector<int> _centerPropagate;

    //PropagationDirection _propagationDir;

    float _explosionTime = 0;

    bool stillPropagate() const;

    // only an explosion can create another explosion. 
    // The first explosion will create 4 different explosions
    // the rest of them 
    Explosion(const Posf& posf, const Posb& posb, int radius, Color& color, 
        Movable::Direction dir, ExplosionsBoardProxy& explosionProxy);

    //Posb getNextTile() const;


     struct AnimationInfo
    {
        float frameDuration;
        Animation animation;

     } _animation;

    void Init(const Color& color);


};

