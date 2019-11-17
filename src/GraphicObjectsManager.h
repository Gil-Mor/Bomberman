#pragma once

/* Singleton that's in charge of loading Textures and preparing Animations
for objects. */

#include <SFML\Graphics.hpp>
#include <vector>
#include <memory>
#include "Sprite.h"
#include "SpritesList.h"
#include "Animation.h"

using std::unique_ptr;
using std::vector;

typedef unique_ptr<sf::Texture> texture_p;


class GraphicObjectsManager
{
public:

    static GraphicObjectsManager& getInstance();

    sf::Texture* getTexture(const Textures& tex);


    const vector<Animation>& getBomberManAnimations() const;
    const Animation& getDynamiteAnimation() const;
    const Animation& getExplosionsAnimation() const;
    const Animation& getExplodingWallAnimation() const;
    const vector<Animation>& getTeleportAnimation() const;


    const sf::Font& getOrbitronFont() const;

private:

    
    vector<texture_p> _textures;

    vector<Animation> _bomberManAnimations;
    Animation _dynamiteAnimation;
    Animation _explosionAnimation;
    Animation _explodingWallAnimation;
    vector<Animation> _teleportAnimations;


    void setAnimations();

    sf::Font _font;

    void loadTextures();

    // private ctor, copy-ctor and = operator.
    GraphicObjectsManager();
    GraphicObjectsManager(const GraphicObjectsManager&);
    GraphicObjectsManager operator=(const GraphicObjectsManager&);

};

