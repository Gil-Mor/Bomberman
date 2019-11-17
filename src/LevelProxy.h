#pragma once
/* Level proxy is used to give the time from the game clock. */
#include "definitions.h"

class Level;
class LevelProxy
{
public:
    LevelProxy(Level& level);
    ~LevelProxy();

    sf::Time getElapsedTime() const;

private:

    Level& _level;
};

