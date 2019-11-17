#pragma once
/* Encapsulates a graphic window. (sf::RenderWindow).
The encapsulation can make it easier to replace a graphic library
since in most places we just use the draw function on the Sprite class that
encapsulates a sprite. so if we changes the content of these two classes
we can almost not change anything else in the code.

The sf::Renderwindow itself is only used when there's a need for
more features like poll event and mapCoordsToPixels..
*/

class Sprite;
#include <SFML/Graphics.hpp>
#include "definitions.h"

class GraphicWindow
{
public:
    GraphicWindow();
    virtual ~GraphicWindow() = default;

    virtual void clearScreen();

    void draw(const Sprite& object);
    void draw(const sf::Text& text);
    void draw(const sf::RectangleShape& rect);

    // when extensive use of sfml RenderWindow functionality is required
    // like when handling events.
    sf::RenderWindow& getWindow();

    virtual void display();

    virtual void close();

    Posf getSizeF() const;

private:
    sf::RenderWindow _window;
};