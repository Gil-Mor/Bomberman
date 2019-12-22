#pragma once
/* 
  The Instruction pages. Derived from menu for the buttons..
*/
#include "Menu.h"
#include "FlipPageButton.h"
#include "Sprite.h"
#include <vector>

using std::vector;

class InstructionPage : public Menu
{
public:
    enum Pages
    {
        PAGE_ONE,
        PAGE_TWO,
        PAGE_THREE,
        PAGE_FOUR,
        PAGE_FIVE,

        NUM_OF_PAGES
    };

    InstructionPage(ControllerProxy& controller);
    ~InstructionPage();

    void flipPage(FlipPageButton::Direction dir);

private:


    vector<Sprite> _pages;

    // the current page were at.
    size_t _currPage = PAGE_ONE;

    void setButtons();


    
};

