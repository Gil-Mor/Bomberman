#pragma once
/*
  The menu with level buttons.
*/
#include "Menu.h"

class ControllerProxy;

class LevelsMenu : public Menu
{
public:
    LevelsMenu(ControllerProxy& controller);
    virtual ~LevelsMenu();

private:
    void setButtons();
};
