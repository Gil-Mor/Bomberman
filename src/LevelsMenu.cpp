#include "LevelsMenu.h"
#include "ControllerProxy.h"
#include "LevelButton.h"
#include "GraphicObjectsManager.h"

const float LEVEL_BUTTON_WIDTH = 200;

const Posf GAP = { 40, 50 };

LevelsMenu::LevelsMenu(ControllerProxy& controller)
    :Menu(controller)
{


    _bgImg.setTexture(GraphicObjectsManager::getInstance().getTexture(MAIN_MENU_T));
    _bgImg.setSize(_controller.getWindowSize());

    _keysToStates[sf::Keyboard::Escape] = ControllerState::GAME_MENU;

    setButtons();
}


LevelsMenu::~LevelsMenu()
{
}

void LevelsMenu::setButtons()
{

    Posf posf(50, 150);


    _buttons.emplace_back(new LevelButton({ 180, 150 }, LevelButton::LEVEL_2, _controller));

    posf.y += _buttons.back()->getSize().y + GAP.y;

    _buttons.emplace_back(new LevelButton(posf, LevelButton::LEVEL_1, _controller));

    posf.y += _buttons.back()->getSize().y + GAP.y;


    posf = { _controller.getWindowSize().x - 400, 150 };

    _buttons.emplace_back(new LevelButton(posf, LevelButton::LEVEL_3, _controller));

    posf.y += _buttons.back()->getSize().y + GAP.y;

    _buttons.emplace_back(new LevelButton({ posf.x + 30, posf.y }, LevelButton::LEVEL_4, _controller));

    posf.y += _buttons.back()->getSize().y + GAP.y;





}
