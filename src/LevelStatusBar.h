#pragma once
/*
  Displays the players status.
*/

#include "Sprite.h"
#include <vector>

class GraphicWindow;
class Player;

using std::vector;

class LevelStatusBar
{
public:
    LevelStatusBar();
    ~LevelStatusBar();

    void dispaly(int timeLeft, const vector<Player*> players, GraphicWindow& window);

private:
    sf::Font _font;
    sf::Text _text;

    Sprite _bg;

    bool _player1Alive = true, _player2Alive = true;

    Sprite _playerImg, _dynamiteImg, _healthImg, _graveImg;
};
