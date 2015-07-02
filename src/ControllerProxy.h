#pragma once
/* 
  Encapsulates calls to methods in the controller.
  Also holds the ControllerState enum so that everyone can use it.
*/
#include "definitions.h"

class Controller;


enum ControllerState
{
    MAIN_MENU,           // play game, instructions and exit buttons.
    GAME_MENU,           // choose num of players, num of Opponents and difficulty.
    INSTRUCTION_MENU, 
    LEVELS_MENU,
    PLAYING,
    PAUSE,               // showing pause menu
    EXITING
};


class ControllerProxy
{
public:

    ControllerProxy(Controller& c);

    
    const ControllerState& getState() const;
    void setState(const ControllerState& );
    void goToPreviousState();

    void setNextLevel(int level);
    void loadNextLevel();

    /* Functions for game menu buttons. */
    void setNumOfPlayers(size_t numOfPlayers);
    void setNumOfEnemies(size_t numOfAI);

    Posf getWindowSize() const;


private:
    Controller& _controller;
};

