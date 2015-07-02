#include "ControllerButton.h"


ControllerButton::ControllerButton(const Posf& pos, ControllerProxy& controller)
    :Button(pos), _controller(controller)
{
}

ControllerButton::~ControllerButton()
{}