#include "ControllerStateButton.h"
#include "ControllerProxy.h"
#include "GraphicObjectsManager.h"

ControllerStateButton::ControllerStateButton(const Posf& pos, ControllerProxy& controller, ControllerState state) :
    ControllerButton(pos, controller), _state(state)
{
    switch (_state) {
        case ControllerState::EXITING:
            _sprite.setTexture(GraphicObjectsManager::getInstance().getTexture(EXIT_BUTTON_T));
            break;

        case ControllerState::MAIN_MENU:
            _sprite.setTexture(GraphicObjectsManager::getInstance().getTexture(MAIN_MENU_BUTTON_T));
            break;

            // in main menu, play button actually gets you to the game menu.
        case ControllerState::GAME_MENU:
        case ControllerState::PLAYING:

            _sprite.setTexture(GraphicObjectsManager::getInstance().getTexture(PLAY_BUTTON_T));
            break;

        case ControllerState::LEVELS_MENU: {
            _sprite.setTexture(GraphicObjectsManager::getInstance().getTexture(LEVELS_MENU_BUTTON_T));
            break;
        }

        case INSTRUCTION_MENU:
            _sprite.setTexture(GraphicObjectsManager::getInstance().getTexture(INSTRUCTIONS_PAGE_BUTTON_T));
            break;
    }

    // set the button size to the size of the texture which contains a text..
    _sprite.setSize(
        Posf(float(_sprite.getSprite().getTextureRect().width), float(_sprite.getSprite().getTextureRect().height)));
}

ControllerStateButton::~ControllerStateButton()
{}

void ControllerStateButton::action() const
{
    _controller.setState(_state);
}