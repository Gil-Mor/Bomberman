#include "LevelButton.h"
#include "ControllerProxy.h"
#include "GraphicObjectsManager.h"

LevelButton::LevelButton(const Posf& pos, Levels level, ControllerProxy& controller) :
    ControllerButton(pos, controller), _level(level)
{
    switch (level) {
        case LevelButton::LEVEL_1:
            _sprite.setTexture(GraphicObjectsManager::getInstance().getTexture(LEVEL_1_BUTTON_T));
            break;

        case LevelButton::LEVEL_2:
            _sprite.setTexture(GraphicObjectsManager::getInstance().getTexture(LEVEL_2_BUTTON_T));
            break;

        case LevelButton::LEVEL_3:
            _sprite.setTexture(GraphicObjectsManager::getInstance().getTexture(LEVEL_3_BUTTON_T));
            break;

        case LevelButton::LEVEL_4:
            _sprite.setTexture(GraphicObjectsManager::getInstance().getTexture(LEVEL_4_BUTTON_T));

            break;

        default:
            break;
    }

    _sprite.setSize(Posf(_sprite.getSprite().getTextureRect().width, _sprite.getSprite().getTextureRect().height));
}

LevelButton::~LevelButton()
{}

void LevelButton::action() const
{
    _controller.setNextLevel(static_cast<int>(_level));
    _controller.loadNextLevel();
    _controller.setState(ControllerState::PLAYING);
}