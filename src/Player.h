#pragma once
/* 
BomberMan controlled by the player. 
*/
#include "BomberMan.h"

// level status bar uses these to create it's images.
const Color PLAYER_1_COLOR = { 184, 237, 255, 255 };
const Color PLAYER_2_COLOR = { 162, 255, 180, 255 };



class Player : public BomberMan
{
public:

    enum Action
    {
        NOTHING,
        PUT_DYNAMITE,
    };

    Player(const Posf& posf, const Posb& posb, size_t PlayerNum);

    ~Player();
    

    // When the user presses a key, the bomber man saves it
    // and only uses it when the board updates all objects.
    void saveKey(sf::Keyboard::Key key);

    virtual void update() override;

    // ----------- DOUBLE DISPATCH ------------
    virtual void colide(GameObject& other) override;

    // overrides bomberman to play bonus sound only players play
    virtual void colide(Bonus& other) override;

    
    // for level status bar
    int getAvailableDynamites() const;
    int getHealth() const;


private:

    // for when playing 2 players. the number of the player.
    size_t _playerNum;

    bool movementKey(sf::Keyboard::Key key) const;

    Movable::Direction keyToDirection(sf::Keyboard::Key key) const;

    Action keyToAction(sf::Keyboard::Key key) const;

    struct Key
    {
        bool keyPressed;
        sf::Keyboard::Key key;
    } _key;
    GameSound_p _bonusSound;

};

