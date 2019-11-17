#include "GameMenu.h"
#include "GraphicObjectsManager.h"
#include "GraphicWindow.h"
#include "ControllerStateButton.h"
#include "NumOfPlayersButton.h"
#include "NumOfEnemiesButton.h"
#include "ControllerProxy.h"

GameMenu::GameMenu(ControllerProxy& controller) : Menu(controller)
{
    _bgImg.setTexture(GraphicObjectsManager::getInstance().getTexture(MAIN_MENU_T));
    _bgImg.setSize(controller.getWindowSize());

    _keysToStates[sf::Keyboard::Return] = ControllerState::LEVELS_MENU;
    _keysToStates[sf::Keyboard::Escape] = ControllerState::MAIN_MENU;

    setButtons();
}

GameMenu::~GameMenu()
{}

void GameMenu::setButtons()
{
    //--------------- ENEMIES BUTTONS -------------------
    // has to create first because we gives them to players buttons.
    Posf pos = {100, 600};

    _buttons.resize(NUM_OF_BUTTONS);

    _buttons[NO_ENEMIES] = (button_p(new NumOfEnemiesButton(pos, 0, _controller)));
    pos.x += _buttons[NO_ENEMIES]->getSize().x;

    _buttons[ONE_ENEMY] = (button_p(new NumOfEnemiesButton(pos, 1, _controller)));
    pos.x += _buttons[ONE_ENEMY]->getSize().x;

    _buttons[TWO_ENEMIES] = (button_p(new NumOfEnemiesButton(pos, 2, _controller)));
    pos.x += _buttons[TWO_ENEMIES]->getSize().x;

    _buttons[THREE_ENEMIES_B] = (button_p(new NumOfEnemiesButton(pos, 3, _controller)));
    pos.x += _buttons[THREE_ENEMIES_B]->getSize().x;

    // NumOfEnemiesButton* threeEnemiesButton = static_cast<NumOfEnemiesButton*>(_buttons[3].get());
    // ------------- PLAYERS BUTTONS ----------------------

    pos = {30, 130};

    _buttons[LEVELS_MENU] = (button_p(new ControllerStateButton(pos, _controller, ControllerState::LEVELS_MENU)));

    pos.y += _buttons[LEVELS_MENU]->getSize().y;

    _buttons[MAIN_MENU] = (button_p(new ControllerStateButton(pos, _controller, ControllerState::MAIN_MENU)));

    pos.y += _buttons[MAIN_MENU]->getSize().y + 20;

    _buttons[ONE_PLAYER] = (button_p(new NumOfPlayersButton(pos, 1, _controller)));

    // different positioning for the 2 players button
    pos.x = _controller.getWindowSize().x - 500;

    _buttons[TWO_PLAYERS] = (button_p(new NumOfPlayersButton(pos, 2, _controller)));
}

void GameMenu::turnOFF3EnemiesButton()
{
    // make absolute position
    dynamic_cast<NumOfEnemiesButton*>(_buttons[THREE_ENEMIES_B].get())->turnOFF3EnemiesButton();
}

void GameMenu::turnOn3EnemiesButton()
{
    dynamic_cast<NumOfEnemiesButton*>(_buttons[THREE_ENEMIES_B].get())->turnOn3EnemiesButton();
}
