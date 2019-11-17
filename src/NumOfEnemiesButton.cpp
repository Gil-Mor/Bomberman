#include "NumOfEnemiesButton.h"
#include "ControllerProxy.h"
#include "GraphicObjectsManager.h"

NumOfEnemiesButton::NumOfEnemiesButton(const Posf& pos, size_t numOfEnemies, ControllerProxy& controller) :
    ControllerButton(pos, controller), _numOfEnemies(numOfEnemies)
{
    switch (numOfEnemies) {
        case 0:
            _sprite.setTexture(GraphicObjectsManager::getInstance().getTexture(NO_ENEMIES_BUTTON_T));
            break;

        case 1:
            _sprite.setTexture(GraphicObjectsManager::getInstance().getTexture(ONE_ENEMY_BUTTON_T));
            break;

        case 2:
            _sprite.setTexture(GraphicObjectsManager::getInstance().getTexture(TWO_ENEMIES_BUTTON_T));
            break;

        case 3:
            _sprite.setTexture(GraphicObjectsManager::getInstance().getTexture(THREE_ENEMIES_BUTTON_T));
            break;
    }

    _sprite.setSize(Posf(_sprite.getSprite().getTextureRect().width, _sprite.getSprite().getTextureRect().height));
}

NumOfEnemiesButton::~NumOfEnemiesButton()
{}

void NumOfEnemiesButton::draw(GraphicWindow& window)
{
    if (_active) {
        Button::draw(window);
    }
}

void NumOfEnemiesButton::action() const
{
    if (_active) {
        _controller.setNumOfEnemies(_numOfEnemies);
    }
}

void NumOfEnemiesButton::turnOFF3EnemiesButton()
{
    _active = false;
}

void NumOfEnemiesButton::turnOn3EnemiesButton()
{
    _active = true;
}
