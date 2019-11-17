#pragma once
/* 
the game Clock. the level has it. everything in the game needs to be synchronized 
to it so LevelProxy can ask the time from level. 
BoardProxy can ask from level proxy. 
*/
#include "Chronometer.h"

class GameClock
{
public:
    GameClock();
    ~GameClock();

    sf::Time getElapsedTime() const;

    void pause();
    void resume();
    void reset();
    bool isRunning() const;


private:

    sftools::Chronometer _clock;
};

