#pragma once
/* Power Ups BomberMan can collect. */
#include "GameObject.h"
#include <memory>


// status bar uses them to create it's images.
const sf::IntRect MORE_DYNAMITES_R(0, 0, 50, 50);
const sf::IntRect EXPLOSION_RADUIS_R(50, 0, 50, 50);
const sf::IntRect SPEED_R(100, 0, 50, 50);
const sf::IntRect KICKABILITY_R(150, 0, 50, 50);
const sf::IntRect HEALTH_R(200, 0, 50, 50);




class Bonus : public GameObject
{
public:

    enum BonusType
    {
        NONE = 0,
        HEALTH,
        SPEED,
        EXPLOSION_RADIUS,
        MORE_DYNAMITES,
        KICKABILITY,

        NUM_OF_BONUSES
    };

    Bonus(const Posf& posf, const Posb& posb, const BonusType& type);

    ~Bonus();

    BonusType getType() const;


    // ----------- DOUBLE DISPATCH ------------
    virtual void colide(GameObject& );

    virtual void colide(Dynamite& );

    virtual void colide(Explosion& );

    virtual void colide(BomberMan& );

private:
    BonusType _type;

};

