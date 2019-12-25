#pragma once
/*
  The opening menu of the program.
*/
#include "Menu.h"

class ControllerProxy;

class GraphicWindow;

class MainMenu : public Menu
{
public:
    enum Buttons { Play_B = 0, Exit_B, VOLUME_UP_B, VOLUME_DOWN_B };

    MainMenu(ControllerProxy& controller);

    ~MainMenu();

private:
    virtual void setButtons();

    // void setPlayButton();
    // void setExitButton();
    // void setVolumeUpButton();
    // void setVolumeDownButton();
};
