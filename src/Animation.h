#pragma once
/* update  the position of a frame (sf::IntRect) on a texture. */
#include <SFML/Graphics.hpp>
#include "GameClock.h"


class Animation
{
public:

    Animation();
    Animation(const sf::IntRect frame, int numOfFrames);
    ~Animation();

    void update(float time, float duration);

    sf::IntRect getFrame() const;

    int getNumOfFrames() const;

    // returns the number of seconds in floating point since the last update
    float getTimeOfLastUpdate() const;



private:

    sf::IntRect _firstFrame;
    sf::IntRect _frame;
    int _currFrame = 0;
    int _numOfFrames;


    // instead of every object saving this it will be saved here.
    float _timeOfLastUpdate = 0;

    float _frameDuration = 0;


};

