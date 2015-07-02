#include "returnButton.h"
#include "ControllerProxy.h"
#include "GraphicObjectsManager.h"

returnButton::returnButton(const Posf& pos, ControllerProxy& controller)
    :ControllerButton(pos, controller)
{

    _sprite.setTexture(GraphicObjectsManager::getInstance().getTexture(RETURN_BUTTON_T));
    // set the button size to the size of the texture which contains a text..
    _sprite.setSize(Posf(float(_sprite.getSprite().getTextureRect().width), float(_sprite.getSprite().getTextureRect().height)));
}


returnButton::~returnButton()
{
}

void returnButton::action() const
{
    _controller.goToPreviousState();
}