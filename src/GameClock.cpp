#include "GameClock.h"

GameClock::GameClock()
{
    _clock.reset();
}

GameClock::~GameClock()
{}

sf::Time GameClock::getElapsedTime() const
{
    return _clock.getElapsedTime();
}

void GameClock::pause()
{
    _clock.pause();
}

void GameClock::resume()
{
    _clock.resume();
}

void GameClock::reset()
{
    _clock.reset();
}

bool GameClock::isRunning() const
{
    return _clock.isRunning();
}
