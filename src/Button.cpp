#include "Button.h"
#include "GraphicObjectsManager.h" 
#include "GraphicWindow.h"


const Color BUTTON_FOCUS_COLOR = { 255, 74, 169, 150 };
const Color BUTTON_NO_FOCUS_COLOR = { 252, 183, 0, 200 };

const Color BUTTON_PRESSED_COLOR = { 200, 32, 180, 150 };


Button::Button(const Posf& pos)
{
    _sprite.setPosition(pos);
    _sprite.setColor(BUTTON_NO_FOCUS_COLOR);
    
}


Button::~Button()
{
}

void Button::setInFocus(bool f)
{
    _inFocus = f;
    if (f)
    {
        _sprite.setColor(BUTTON_FOCUS_COLOR);

    }
    else
    {
        _sprite.setColor(BUTTON_NO_FOCUS_COLOR);

    }
}

bool Button::getInFocus() const
{
    return _inFocus;
}


bool Button::getChosen() const
{
    return _chosen;
}

void Button::setChosen(bool c)
{
    _chosen = c;
    if (c) {
        _sprite.setColor(BUTTON_PRESSED_COLOR);
       
    }
    else {
        _sprite.setColor(BUTTON_NO_FOCUS_COLOR);

    }
}

void Button::draw(GraphicWindow& window)
{
    window.draw(_sprite);
}

bool Button::mouseOver(const Posf& mouse) const
{
    return _sprite.getSprite().getGlobalBounds().contains(mouse);
}


const Posf& Button::getSize() const
{
    return _sprite.getSize();
}
