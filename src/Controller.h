#pragma once

/* Controls the flow of the program. activates the menus, loads levels from 
level builder and calls level.run().
*/

#include <string>
#include "GraphicWindow.h"
#include "MainMenu.h"
#include "GameMenu.h"
#include "InstructionPage.h"
#include "ControllerProxy.h"
#include "Board.h"
#include "Level.h"
#include "PauseMenu.h"
#include "LevelsMenu.h"

using std::string;


class Controller
{
public:
    Controller();
    ~Controller();

    void run();

    // called from ControlerState Buttons.
    void setState(ControllerState);
    const ControllerState& getState() const;
    void goToPreviousState();


    // called from buttons
    void setNumOfPlayersForLevel(size_t num);
    void setNumOfEnemiesForLevel(size_t num);


    // called from Controller Proxy by everything that needs
    // to set it's size according to the window..
    // menus, levels, etc..
    Posf getWindowSize() const;


    // called from LevelButton from Levels Menu
    void setNextLevel(int level);
    void loadNextLevel();

private:

    /* Interface for using SFML RenderWindow. 
    already initialized. */
    GraphicWindow _window;

    // Initualized in ctor
    ControllerProxy _proxy;
    MainMenu _mainMenu;
    GameMenu _gameMenu;
    PauseMenu _pauseMenu;
    LevelsMenu _levelsMenu;
    InstructionPage _instructionPages;
    Level _level; // has to save the level for pausing and resuming.

    // indicates that the Controller was successfully built.
    bool _buildSuccess = true;

    ControllerState _state = ControllerState::MAIN_MENU;

    // keeps it's previous state so that if a state can be entered to 
    // from multiple states it'll know where to go back to.
    // for instance instruction pages can be reached to 
    // from the pause menu or from main menu. how can the controller
    // know where to go after he leaves instruction pages?
    ControllerState _prevState = ControllerState::MAIN_MENU;

    // proporties are set by buttons and are sent to the level builder.
    struct LevelProporties
    {
        size_t numOfPlayers = 1, numOfEnemies = 1,
            currLevel = 0;
    } _levelProporties;

};

