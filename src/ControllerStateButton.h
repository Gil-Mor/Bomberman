#pragma once
/*
  Buttons that change a state in the controller.
*/
#include "ControllerProxy.h"
#include "ControllerButton.h"

class ControllerProxy;

class ControllerStateButton : public ControllerButton
{
public:
    ControllerStateButton(const Posf& pos, ControllerProxy& controller, ControllerState state);

    virtual ~ControllerStateButton();

    virtual void action() const override;

private:
    ControllerState _state;
};
