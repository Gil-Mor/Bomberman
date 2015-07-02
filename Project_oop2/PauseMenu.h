#pragma once
/* 
  Like Main menu only that play button leads back to the game.
*/
#include "Menu.h"

class ControllerProxy;

class PauseMenu :
    public Menu
{
public:


    PauseMenu(ControllerProxy& controller);

    virtual ~PauseMenu();

private:
    void setButtons();
};

