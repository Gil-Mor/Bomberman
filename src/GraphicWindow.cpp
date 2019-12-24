#include "GraphicWindow.h"
#include "definitions.h"
#include "Sprite.h"

GraphicWindow::GraphicWindow()
{
    _window.create(sf::VideoMode::getFullscreenModes()[0], "I Blow Things Up", sf::Style::Fullscreen);
    _window.setFramerateLimit(60);
}

void GraphicWindow::clearScreen()
{
    _window.clear();
}

void GraphicWindow::draw(const Sprite& sprite)
{
    _window.draw(sprite.getSprite());
}

void GraphicWindow::draw(const sf::Text& text)
{
    _window.draw(text);
}

void GraphicWindow::draw(const sf::RectangleShape& rect)
{
    _window.draw(rect);
}


void GraphicWindow::display()
{
    _window.display();
}

void GraphicWindow::close()
{
    _window.close();
}

sf::RenderWindow& GraphicWindow::getWindow()
{
    return _window;
}

Posf GraphicWindow::getSizeF() const
{
    return Posf(static_cast<float>(_window.getSize().x), static_cast<float>(_window.getSize().y) );
}

