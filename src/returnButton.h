#pragma once
/* 
  A Button which tells the controller to go back to the previous state.
  Used by Instruction page which can be called both from the main menu 
  and the level so we need to go back to the previous state.
*/
#include "ControllerButton.h"
class returnButton : public ControllerButton
{
public:
    returnButton(const Posf& pos, ControllerProxy& controller);
    ~returnButton();

    void action() const override;
};

