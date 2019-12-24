#include "Sprite.h"
#include "GraphicWindow.h"

Sprite::Sprite(const Posf& size)
{
    _sprite.setSize(size);
}

sf::RectangleShape& Sprite::getSprite()
{
    return _sprite;
}

const sf::RectangleShape& Sprite::getSprite() const
{
    return _sprite;
}

void Sprite::setSize(const Posf& size)
{
    _sprite.setSize(size);
}

void Sprite::setVisibleRect(const Posf& size)
{
    _sprite.setTextureRect(sf::IntRect(0, 0, size.x, size.y));
}

void Sprite::setVisibleRect(sf::IntRect rect)
{
    _sprite.setTextureRect(rect);

}

Color Sprite::getColor() const
{
    return _sprite.getFillColor();
}


const Posf& Sprite::getPosition() const
{
    return _sprite.getPosition();
}


void Sprite::setPosition(const Posf& pos)
{
    _sprite.setPosition(pos);
}


void Sprite::setColor(const Color& color)
{
    _sprite.setFillColor(color);
}

void Sprite::setTexture(sf::Texture* tex)
{
    _sprite.setTexture(tex);
}

const Posf& Sprite::getSize() const
{
    return _sprite.getSize();
}

void Sprite::draw(GraphicWindow& window) 
{
    window.draw(_sprite);
}
