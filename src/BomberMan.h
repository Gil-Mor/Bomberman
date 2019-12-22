#pragma once
/* Base class for BomberMan. Player and enemies. 
Collisions are mostly the same for players and enemies. 
updating animation according to state is the same.
*/
#include "Movable.h"
#include "SpritesList.h"
#include "BomberManProxy.h"
#include "Animation.h"
#include "AudioManager.h"

class BoardProxy;

const float HIT_TIME = 3;

const int HEALTH_CHANGE = 1;
const int SPEED_CHANE = 5;


class BomberMan : public Movable
{
public:

    enum State
    {
        PLAYING_S,
        EXPLODING_S,
        LAST_EXPLOSION_S,
        COMPLETELY_DEAD_S
    };

    enum Animations
    {
        DOWN_A,
        UP_A,      
        LEFT_A,
        RIGHT_A,
        EXPLODING_A,
        NUM_OF_BOMBERMAN_ANIMATIONS
    };

    BomberMan(const Posf& posf, const Posb& posb);

    virtual ~BomberMan() = 0;

    // explosions also call this..
    void hitFromExplosion();

    // call back from dynamite.
    // dynamites let the bomberman know that they exploded.
    void dynamiteExploded();

    State getState() const;

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


protected:
    // proxy that BomberMan gives to it's dynamites so that they can
    // call back to him when they explode, incrementing it's available 
    // dynamites count.
    BomberManProxy _bomberManProxy;

    State _bomberManState = PLAYING_S;
    
    int _health = 3;

    // The explosion radius of the bombs this BomberMan puts.
    int _explosionRadius = 2;

    // total number of this BomberMan Dynamites that can be on the board at once.
    int _maxDynamites = 1;


    // overridden by AIenemy which saves some date.
    virtual void placeDynamite(BoardProxy& board);


    int _availbleDynamites = _maxDynamites;

    void updateAnimation();
 
    

    // save info about hit
    struct Hit
    {
        float hitTime;
        float hitFrameDuration;

    }_hit; 


    Animations getAnimationFromDirection();

    GameSound_p _hitSound;

    GameSound_p _dyingSound;

private:

    float _lastTeleportation = TELEPORTATION_GAP;

    vector<Animation> _animations;

    Animations _currAnimation = UP_A;

    // if bomberman can kick dynamites.
    bool _kickability = false;
};

