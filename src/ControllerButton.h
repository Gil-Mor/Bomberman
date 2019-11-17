#pragma once

/* Buttons that get ControllerProxy and use it to call methods in the controller. */
#include "Button.h"

class ControllerProxy;

class ControllerButton : public Button
{
public:
    ControllerButton(const Posf& pos, ControllerProxy& controller);

    virtual ~ControllerButton() = 0;

protected:
    ControllerProxy& _controller;
};
