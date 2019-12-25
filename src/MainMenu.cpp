#include "MainMenu.h"
#include "ControllerProxy.h"
#include "ControllerStateButton.h"
#include "MusicButton.h"
#include "GraphicObjectsManager.h"
#include "GraphicWindow.h"
#include "Controller.h" // for ControllerState enum
#include "MusicButton.h"

MainMenu::MainMenu(ControllerProxy& controller) : Menu(controller)
{
    _bgImg.setTexture(GraphicObjectsManager::getInstance().getTexture(MAIN_MENU_T));
    _bgImg.setSize(controller.getWindowSize());

    _keysToStates[sf::Keyboard::Return] = ControllerState::GAME_MENU;
    _keysToStates[sf::Keyboard::Escape] = ControllerState::EXITING;

    setButtons();
}

MainMenu::~MainMenu()
{}

void MainMenu::setButtons()
{
    Posf pos(30, 130);

    _buttons.push_back(button_p(new ControllerStateButton(pos, _controller, ControllerState::GAME_MENU)));

    pos.y += _buttons.back()->getSize().y + 20;

    _buttons.emplace_back(new ControllerStateButton(pos, _controller, ControllerState::INSTRUCTION_MENU));

    pos.y += _buttons.back()->getSize().y + 20;

    _buttons.push_back(button_p(new ControllerStateButton(pos, _controller, ControllerState::EXITING)));

    pos = {_controller.getWindowSize().x - 400, 150};

    _buttons.push_back(button_p(new MusicButton(pos, MusicButton::STOP)));

    pos.y += _buttons.back()->getSize().y + 20;

    _buttons.push_back(button_p(new MusicButton(pos, MusicButton::PLAY)));

    pos.y += _buttons.back()->getSize().y + 20;

    _buttons.push_back(button_p(new MusicButton(pos, MusicButton::VOLUME_UP)));

    pos.y += _buttons.back()->getSize().y + 20;

    _buttons.push_back(button_p(new MusicButton(pos, MusicButton::VOLUME_DOWN)));

    pos.y += _buttons.back()->getSize().y + 20;
}
