#include "Menu.h"
#include <SFML/Graphics.hpp>
#include "ControllerProxy.h"
#include "GraphicWindow.h"
#include "Button.h"
#include "Controller.h" // for controllerState enum

Menu::Menu(ControllerProxy& controller) : _controller(controller)
{}

Menu::~Menu()
{}

void Menu::run(GraphicWindow& window)
{
    sf::Event event;
    Posf mouse;

    // we don't know in which menu we're in but will stay here until the controller
    // state changes.
    ControllerState currState = _controller.getState();

    // have to has the full functionality of the sfml window here.
    sf::RenderWindow& sfWindow = window.getWindow();

    while (_controller.getState() == currState) {
        mouse = sfWindow.mapPixelToCoords(sf::Mouse::getPosition(sfWindow));

        while (sfWindow.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::MouseMoved: {
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && buttonWasPressed()) {
                        handleMouseDrag(mouse);
                    }

                    else {
                        handleMouseMove(mouse);
                    }
                    break;
                }
                case sf::Event::MouseButtonPressed: {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        handleMousePress();
                    }
                    break;
                }

                case sf::Event::MouseButtonReleased: {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        handleMouseRelease();
                    }
                    break;
                }

                case sf::Event::Closed:
                    _controller.setState(ControllerState::EXITING);
                    break;

                case sf::Event::KeyPressed: {
                    if (_keysToStates.find(event.key.code) == _keysToStates.end())
                        break;

                    _controller.setState(_keysToStates[event.key.code]);
                    /*if (event.key.code == sf::Keyboard::Escape)
                    {
                        _controller.setState(ControllerState::MAIN_MENU);
                    }
                    if (event.key.code == sf::Keyboard::Return)
                    {
                        _controller.setState(ControllerState::GAME_MENU);
                    }*/

                    break;
                }
            }
        }

        sfWindow.clear();
        display(window);
        window.display();
    }
    cleanMouse();
}

void Menu::handleMouseMove(const Posf mouse)
{
    for (size_t i = 0; i < _buttons.size(); ++i) {
        if (_buttons[i]->mouseOver(mouse)) {
            _buttons[i]->setInFocus(true);
        } else {
            _buttons[i]->setInFocus(false);
        }
    }
}

void Menu::handleMouseDrag(const Posf mouse)
{
    for (size_t i = 0; i < _buttons.size(); ++i) {
        if (_buttons[i]->mouseOver(mouse)) {
            _buttons[i]->setInFocus(true);
            _buttons[i]->setChosen(true);
        } else {
            _buttons[i]->setChosen(false);
            _buttons[i]->setInFocus(false);
        }
    }
}

void Menu::handleMousePress()
{
    for (size_t i = 0; i < _buttons.size(); ++i) {
        if (_buttons[i]->getInFocus()) {
            _buttons[i]->setChosen(true);
            _chosenButton = _buttons[i].get();
        } else {
            _buttons[i]->setChosen(false);
        }
    }
}

void Menu::handleMouseRelease()
{
    for (size_t i = 0; i < _buttons.size(); ++i) {
        if (_buttons[i]->getChosen()) {
            _buttons[i]->action();
        }
    }
}

bool Menu::buttonWasPressed() const
{
    for (size_t i = 0; i < _buttons.size(); ++i) {
        if (_buttons[i]->getChosen())
            return true;
    }
    return false;
}

void Menu::display(GraphicWindow& window) const
{
    window.draw(_bgImg);

    for (size_t i = 0; i < _buttons.size(); ++i) {
        _buttons[i]->draw(window);
    }
}

void Menu::cleanMouse()
{
    for (size_t i = 0; i < _buttons.size(); ++i) {
        _buttons[i]->setInFocus(false);
        _buttons[i]->setChosen(false);
    }
}
