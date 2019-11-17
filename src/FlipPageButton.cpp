#include "FlipPageButton.h"
#include "InstructionPage.h"
#include "GraphicObjectsManager.h"

FlipPageButton::FlipPageButton(const Posf& pos, Direction dir, InstructionPage& page) :
    Button(pos), _dir(dir), _page(page)
{
    switch (dir) {
        case FlipPageButton::NEXT:
            _sprite.setTexture(GraphicObjectsManager::getInstance().getTexture(FLIP_NEXT_BUTTON_T));
            break;

        case FlipPageButton::BACK:
            _sprite.setTexture(GraphicObjectsManager::getInstance().getTexture(FLIP_BACK_BUTTON_T));

            break;
        default:
            break;
    }
    _sprite.setColor(Color::White);

    _sprite.setSize(Posf(_sprite.getSprite().getTextureRect().width, _sprite.getSprite().getTextureRect().height));
}

FlipPageButton::~FlipPageButton()
{}

void FlipPageButton::action() const
{
    _page.flipPage(_dir);
}