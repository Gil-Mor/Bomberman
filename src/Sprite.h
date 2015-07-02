#pragma once
/*
Encapsulates a Sprite (sf::RectangleShape) in this case. 
The encapsulation can make it easier to replace a graphic library
since in most places we just use the draw function on the Sprite.
so if we changes the content of the Sprite class and the Graphicwindow class
we can almost not change anything else in the code.

sf::RectangleShape is only used for heavier stuff like getTextureRect..

*/
#include <SFML/Graphics.hpp>
#include "SpritesList.h"
#include "definitions.h" 

class GraphicWindow;

class Sprite
{
public:

    Sprite();
    Sprite(const Posf& size);

    ~Sprite();

    virtual void draw(GraphicWindow& window);

    sf::RectangleShape& getSprite();

    const sf::RectangleShape& getSprite() const;
    
    const Posf& getSize() const;

    void setSize(const Posf& size);
    void setVisibleRect(const Posf& size);
    void setVisibleRect(sf::IntRect rect);


    /* get The SFML shape position of the object. */
    const Posf& getPosition() const;

    /* sets the SFML shape position. */
    void setPosition(const Posf& pos);

    /* sets the SFML color of the object*/
    void setColor(const Color& color);

    Color getColor() const;


    void setTexture(sf::Texture* tex);

private:

    sf::RectangleShape _sprite;

};

