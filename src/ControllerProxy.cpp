#include "ControllerProxy.h"
#include "Controller.h"

ControllerProxy::ControllerProxy(Controller& controller)
    : _controller(controller)
{
}

const ControllerState& ControllerProxy::getState() const
{
    return _controller.getState();
}

void ControllerProxy::setState(const ControllerState& state)
{
    _controller.setState(state);
}

void ControllerProxy::goToPreviousState()
{
    _controller.goToPreviousState();
}

void ControllerProxy::setNumOfPlayers(size_t numOfPlayers)
{
    _controller.setNumOfPlayersForLevel(numOfPlayers);
}


void ControllerProxy::setNumOfEnemies(size_t numOfAI)
{
    _controller.setNumOfEnemiesForLevel(numOfAI);
}

Posf ControllerProxy::getWindowSize() const
{
    return _controller.getWindowSize();
}



void ControllerProxy::setNextLevel(int level)
{
    _controller.setNextLevel(level);
}

void ControllerProxy::loadNextLevel()
{
    _controller.loadNextLevel();
}

