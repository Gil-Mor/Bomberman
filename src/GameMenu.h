#pragma once
/*
  Game Menu. Where the user chooses number of players and number of enemies.
*/

#include "Menu.h"

class ControllerProxy;

class GameMenu : public Menu
{
public:
    enum Buttons {

        MAIN_MENU,
        LEVELS_MENU,
        ONE_PLAYER,
        TWO_PLAYERS,
        NO_ENEMIES,
        ONE_ENEMY,
        TWO_ENEMIES,
        THREE_ENEMIES_B,

        NUM_OF_BUTTONS
    };

    GameMenu(ControllerProxy& controller);

    ~GameMenu();

    void turnOFF3EnemiesButton();

    void turnOn3EnemiesButton();

private:
    void setButtons();
};
