#pragma once
/*
  Base class for all menus. The menus just set their different buttons
  and background image but they all use the 'run' method of this class.

*/
#include <memory>
#include <vector>
#include "ControllerProxy.h"
#include "definitions.h"
#include "Sprite.h"
#include "Button.h"
#include <unordered_map>

class ControllerProxy;

class GraphicWindow;

using std::unordered_map;
using std::vector;
using std::unique_ptr;

typedef unique_ptr<Button> button_p;

class Menu
{
public:


    Menu(ControllerProxy& controller);

    virtual ~Menu() = 0;

    /* Iterate through the buttons and activate action
    In the button that was clicked.
    former state so that if the menu can be called from multiple places,
    like the instruction pages, it'll know where to send the controller back to. 
    */
    virtual void run(GraphicWindow& graphics);

protected:

    vector<button_p> _buttons;

    // each menu can map keyboard keys to wanted state
    unordered_map<sf::Keyboard::Key, ControllerState> _keysToStates;

    Button* _chosenButton = nullptr;

    ControllerProxy& _controller;

    Sprite _bgImg;

    void display(GraphicWindow& window) const;

    void handleEvent(const GraphicWindow& graphics, const sf::Event event);

    void handleMouseMove(const Posf mouse);
    void handleMouseDrag(const Posf mouse);
    void handleMousePress();
    void handleMouseRelease();

    void cleanMouse();
    bool buttonWasPressed() const;


};

