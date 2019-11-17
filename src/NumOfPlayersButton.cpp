#include "NumOfPlayersButton.h"
#include "ControllerProxy.h"
#include "GraphicObjectsManager.h"

NumOfPlayersButton::NumOfPlayersButton(const Posf& pos, size_t num, ControllerProxy& controller)

    :
    ControllerButton(pos, controller),
    _numOfPlayers(num)
{
    switch (num) {
        case 1:
            _sprite.setTexture(GraphicObjectsManager::getInstance().getTexture(ONE_PLAYER_BUTTON_T));
            break;

        case 2:
            _sprite.setTexture(GraphicObjectsManager::getInstance().getTexture(TWO_PLAYER_BUTTON_T));
            break;

        default:
            break;
    }

    _sprite.setSize(Posf(_sprite.getSprite().getTextureRect().width, _sprite.getSprite().getTextureRect().height));
}

NumOfPlayersButton::~NumOfPlayersButton()
{}

void NumOfPlayersButton::action() const
{
    _controller.setNumOfPlayers(_numOfPlayers);
}