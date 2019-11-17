#pragma once
/*
  Base class for all buttons. Implements Button common functionality
*/
#include "Sprite.h"
#include "definitions.h"

class GraphicWindow;

class Button
{
public:
    Button(const Posf& pos);

    virtual ~Button() = 0;

    virtual void action() const = 0;

    /* Returns true if the mouse is over this object RectangleShape.
    the mouse coordinates are given in 'world' coordinates -
    from window.mapPixelToCoords function.
    That's why Vector2f and not 2i. */
    bool mouseOver(const Posf& mouse) const;

    bool getInFocus() const;
    virtual bool getChosen() const;

    virtual void setInFocus(bool f);
    virtual void setChosen(bool c);

    virtual void draw(GraphicWindow& window);

    const Posf& getSize() const;

protected:
    bool _inFocus = false, _chosen = false;

    Sprite _sprite;
};
