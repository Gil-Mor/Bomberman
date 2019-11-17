#include "GameObject.h"
#include "GraphicWindow.h"
#include "BoardProxy.h"

GameObject::GameObject(const Posf& posf, const Posb& posb) : _posf(posf), _posb(posb)
{
    _sprite.setSize(TILE_SIZE);
    _sprite.setPosition(posf);
}

void GameObject::setObjectBoardProxy(BoardProxy* board)
{
    _boardProxy = board;
}

GameObject::~GameObject()
{}

void GameObject::update()
{}

float GameObject::getTimeAsSeconds() const
{
    return _boardProxy->getElapsedTimeAsSeconds();
}

bool GameObject::enoughTime(float activationTime, float duration)
{
    return getTimeAsSeconds() - activationTime >= duration;
}

void GameObject::restoreVisibleRect()
{
    _sprite.setVisibleRect(sf::IntRect(0, 0, TILE_SIZE.x, TILE_SIZE.y));
}

void GameObject::draw(GraphicWindow& window)
{
    window.draw(_sprite);
}

const Posb& GameObject::getPosb() const
{
    return _posb;
}

const Posf& GameObject::getPosf() const
{
    return _posf;
}
