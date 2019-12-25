#include "InstructionPage.h"
#include "GraphicObjectsManager.h"
#include "ControllerProxy.h"
#include "FlipPageButton.h"
#include "returnButton.h"

const size_t NUM_OF_INSTRUCTION_PAGES = 2;
InstructionPage::InstructionPage(ControllerProxy& controller) : Menu(controller)
{
    _pages.resize(NUM_OF_PAGES);
    _pages[0].setTexture(GraphicObjectsManager::getInstance().getTexture(INSTRUCTION_PAGE_1_T));
    _pages[1].setTexture(GraphicObjectsManager::getInstance().getTexture(INSTRUCTION_PAGE_2_T));
    _pages[2].setTexture(GraphicObjectsManager::getInstance().getTexture(INSTRUCTION_PAGE_3_T));
    _pages[3].setTexture(GraphicObjectsManager::getInstance().getTexture(INSTRUCTION_PAGE_4_T));
    _pages[4].setTexture(GraphicObjectsManager::getInstance().getTexture(INSTRUCTION_PAGE_5_T));

    for (auto& page : _pages) {
        page.setSize(controller.getWindowSize());
    }

    // menu base class draws it's background img so the instruction page will
    // set it's _bgImg to be the curr page
    _bgImg = _pages[PAGE_ONE];

    setButtons();
}

InstructionPage::~InstructionPage()
{}

void InstructionPage::setButtons()
{
    Posf winSize = _controller.getWindowSize();

    _buttons.emplace_back(new returnButton({30, 50}, _controller));

    _buttons.emplace_back(new FlipPageButton({30, winSize.y - 100}, FlipPageButton::BACK, *this));

    _buttons.emplace_back(new FlipPageButton(
        {winSize.x - 200, winSize.y - 100},

        FlipPageButton::NEXT,
        *this));
}

// void InstructionPage::run(GraphicWindow& window)
//{
//    Menu::run(window);
//    _controller.goToPreviousState();
//}

void InstructionPage::flipPage(FlipPageButton::Direction dir)
{
    switch (dir) {
        case FlipPageButton::Direction::NEXT: {
            if (_currPage < _pages.size() - 1) {
                ++_currPage;
                _bgImg = _pages[_currPage];
            }
            break;
        }
        case FlipPageButton::Direction::BACK: {
            if (_currPage > 0) {
                --_currPage;
                _bgImg = _pages[_currPage];
            }
            break;
        }
    }
}
