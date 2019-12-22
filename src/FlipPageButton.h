#pragma once
/* 
  Flips a page in the Instruction Pages.
*/
#include "Button.h"

class InstructionPage;

class FlipPageButton :
    public Button
{
public:

    enum Direction
    {
        NEXT,
        BACK
    };
    FlipPageButton(const Posf& pos, Direction dir, InstructionPage& page);
    ~FlipPageButton();

    void action() const override;

private:
    Direction _dir;
    InstructionPage& _page;
};

