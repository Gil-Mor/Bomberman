#pragma once
/* 
Teleport. Has a twin.
*/
#include "GameObject.h"
#include "definitions.h"
#include "Animation.h"
#include "AudioManager.h"

class Teleport : public GameObject
{
public:

    enum Animations { 
        REST_A,
        ACTIVE_A,

        NUM_OF_ANIMATIONS_A
    };


    Teleport(const Posf& posf, const Posb& selfPosi, int ID);

    // set by level builder
    void setTwinPos(const Posb& pos);

    /* Returns the teleport's ID. */
    size_t getID() const;

    /* Get the position of the twin teleport. */
    const Posb& getTwinPosition() const;


    // for validation in level builder
    bool getHasTwin() const;



    virtual void update() override;

    // ----------- DOUBLE DISPATCH ------------
    virtual void colide(GameObject& other) override;

    virtual void colide(Dynamite& other) override;

    virtual void colide(Explosion& other) override;

    virtual void colide(BomberMan& other) override;

private:


    // last time of teleportation. for animation.
    float _teleportationTime = 0;


    float _activeDuration;


    void activate();

    // The twin's position is given as 2d array index.
    Posb _twinPos;

    bool twinWasSet = false;

    // ID of the twin teleports.
    // each couple of teleports has a unique ID which is
    // a one digit number.
    // int and not size_t because of std::stoi
    int _ID;

    Animations _currAnimation = REST_A;

    vector<Animation> _animations;

    GameSound_p _teleportSound;


};

