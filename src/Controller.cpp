#include "Controller.h"
#include "LevelBuilder.h"
#include "Level.h"
#include "Logger.h"
#include <stdexcept>
#include "LevelFileException.h"
#include "ControllerProxy.h"
#include "AudioManager.h"

using std::exception;

Controller::Controller()
    : _proxy(*this),
    _mainMenu(_proxy),
    _gameMenu(_proxy),
    _pauseMenu(_proxy),
    _levelsMenu(_proxy),
    _instructionPages(_proxy),
    _level(_proxy)
{

    try {

        size_t numOfLevels = LevelBuilder::getInstance().getNumOfLevels();


        if (numOfLevels == 0)
        {
            _buildSuccess = false;
        }
    }
    catch (std::exception& e) {
        _buildSuccess = false;
    }

    


}


Controller::~Controller()
{
}

void Controller::run()
{
    if (!_buildSuccess)
    {
        Logger::getInstance().log("Error with LevelBuilder. Controller couldn't get levels.");
        throw LevelFileException("Error with LevelBuilder.");
    }

    try
    {
        AudioManager::getInstance().playSoundTrack();

        while (_state != EXITING)
        {
            switch (_state)
            {
                case MAIN_MENU:
                {
                    _mainMenu.run(_window);
                    break;
                }

                case INSTRUCTION_MENU:
                {
                    _instructionPages.run(_window);
                    break;
                }

                case GAME_MENU:
                {
                    _gameMenu.run(_window);
                    break;
                }

                case PLAYING:
                {
                    _level.resume();
                    _level.run(_window);
                    break;
                }

                case PAUSE:
                {
                    _pauseMenu.run(_window);
                    break;
                }

                case LEVELS_MENU:
                {
                    _levelsMenu.run(_window);
                    break;
                }

            }

        }
        AudioManager::getInstance().stopSoundTrack();

        _window.close();

    }

    catch (std::exception& e)
    {
        Logger::getInstance().log("error in controller loop. State was " + _state);
        _window.close();
        throw;
    }
}

void Controller::loadNextLevel()
{

    try
    {
        _level.setLevel(LevelBuilder::getInstance().getLevel
            (_levelProporties.currLevel,
            _levelProporties.numOfPlayers,
            _levelProporties.numOfEnemies,
            getWindowSize()));

        _state = PLAYING;

    }
    catch (exception& e) {
        Logger::getInstance().log("error loading level " + _levelProporties.currLevel);
        throw;
    }

}

void Controller::setNextLevel(int level)
{
    _levelProporties.currLevel = level;
}


void Controller::setState(ControllerState state)
{
    // keep former state
    _prevState = _state;
    _state = state;
}

void Controller::goToPreviousState()
{
    _state = _prevState;
}


const ControllerState& Controller::getState() const
{
    return _state;
}

void Controller::setNumOfPlayersForLevel(size_t num)
{
    if (num == 2) {
        _gameMenu.turnOFF3EnemiesButton();
    }
    else
        _gameMenu.turnOn3EnemiesButton();

    _levelProporties.numOfPlayers = num;
}


void Controller::setNumOfEnemiesForLevel(size_t num)
{
    _levelProporties.numOfEnemies = num;

}


Posf Controller::getWindowSize() const
{
    return _window.getSizeF();
}
