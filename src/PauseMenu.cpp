#include "PauseMenu.h"
#include "ControllerProxy.h"
#include "GraphicObjectsManager.h"
#include "ControllerStateButton.h"
#include "MusicButton.h"

PauseMenu::PauseMenu(ControllerProxy& controller)
    :Menu(controller)
{

    _bgImg.setTexture(GraphicObjectsManager::getInstance().getTexture(MAIN_MENU_T));
    _bgImg.setSize(controller.getWindowSize());


    _keysToStates[sf::Keyboard::Return] = ControllerState::PLAYING;
    _keysToStates[sf::Keyboard::Space] = ControllerState::PLAYING;
    _keysToStates[sf::Keyboard::Escape] = ControllerState::MAIN_MENU;

    setButtons();
}


PauseMenu::~PauseMenu()
{
}

void PauseMenu::setButtons()
{

    Posf pos(50, 200);



    _buttons.push_back(button_p(new ControllerStateButton(pos, _controller, ControllerState::PLAYING)));

    pos.y += _buttons.back()->getSize().y + 20;

    _buttons.push_back(button_p(new ControllerStateButton(pos, _controller, ControllerState::INSTRUCTION_MENU)));

    pos.y += _buttons.back()->getSize().y + 20;


    _buttons.push_back(button_p(new ControllerStateButton(pos, _controller, ControllerState::MAIN_MENU)));

    pos.y += _buttons.back()->getSize().y + 20;

    pos = { _controller.getWindowSize().x - 300, 130 };

    _buttons.push_back(button_p(new MusicButton(pos, MusicButton::STOP)));

    pos.y += _buttons.back()->getSize().y + 20;

    _buttons.push_back(button_p(new MusicButton(pos, MusicButton::PLAY)));

    pos.y += _buttons.back()->getSize().y + 20;

    _buttons.push_back(button_p(new MusicButton(pos, MusicButton::VOLUME_UP)));

    pos.y += _buttons.back()->getSize().y + 20;

    _buttons.push_back(button_p(new MusicButton(pos, MusicButton::VOLUME_DOWN)));

    pos.y += _buttons.back()->getSize().y + 20;

    _buttons.push_back(button_p(new MusicButton(pos, MusicButton::FX_OFF)));

    pos.y += _buttons.back()->getSize().y + 20;

    _buttons.push_back(button_p(new MusicButton(pos, MusicButton::FX_ON)));

    pos.y += _buttons.back()->getSize().y + 20;

}
