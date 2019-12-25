#include "LevelProxy.h"
#include "Level.h"

LevelProxy::LevelProxy(Level& level) : _level(level)
{}

LevelProxy::~LevelProxy()
{}

sf::Time LevelProxy::getElapsedTime() const
{
    return _level.getElapsedTime();
}
