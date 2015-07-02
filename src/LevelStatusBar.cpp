#include "LevelStatusBar.h"
#include "GraphicObjectsManager.h"
#include "Animation.h"
#include "Bonus.h"
#include "Player.h"
#include "GraphicWindow.h"

#include <string>

using std::to_string;

const Posf PLAYER_IMG_SIZE = { 100, 100 };

const Posf PLAYER_1_POS = { 0, 20 };
const Posf PLAYER_2_POS = { 0, PLAYER_1_POS.y + PLAYER_IMG_SIZE.y + 30 };

const Posf PLAYER_1_DYNAMITES_POS = { PLAYER_1_POS.x + PLAYER_IMG_SIZE.x - 15, PLAYER_1_POS.y + 10 };
const Posf PLAYER_2_DYNAMITES_POS = { PLAYER_2_POS.x + PLAYER_IMG_SIZE.x - 15, PLAYER_2_POS.y + 10 };

const Posf PLAYER_1_DYNAMITES_TEXT_POS = { PLAYER_1_DYNAMITES_POS.x + 60, PLAYER_1_DYNAMITES_POS.y + 5 };
const Posf PLAYER_2_DYNAMITES_TEXT_POS = { PLAYER_2_DYNAMITES_POS.x + 60, PLAYER_2_DYNAMITES_POS.y + 5 };

const Posf PLAYER_1_HEALTH_POS = { PLAYER_1_POS.x + PLAYER_IMG_SIZE.x - 5, PLAYER_1_POS.y + 60 };
const Posf PLAYER_2_HEALTH_POS = { PLAYER_2_POS.x + PLAYER_IMG_SIZE.x - 5, PLAYER_2_POS.y + 60 };

const Posf PLAYER_1_HEALTH_TEXT_POS = { PLAYER_1_HEALTH_POS.x + 45, PLAYER_1_HEALTH_POS.y - 5};
const Posf PLAYER_2_HEALTH_TEXT_POS = { PLAYER_2_HEALTH_POS.x + 45, PLAYER_2_HEALTH_POS .y - 5};

const Posf TIME_LEFT_POS = { PLAYER_2_POS.x + 10, PLAYER_2_POS.y + PLAYER_IMG_SIZE.y + 40 };


const float TEXT_SIZE = 25;
const float TIME_TEXT_SIZE = 20;

LevelStatusBar::LevelStatusBar()
{
    Animation auxRect;
    _bg.setColor({ 255, 255, 255, 50 });
    _bg.setSize({ 250, 350 });

    _font = GraphicObjectsManager::getInstance().getOrbitronFont();
    _text.setFont(_font);
    _text.setColor({ 220, 39, 73, 255 });
    _text.setCharacterSize(TEXT_SIZE);
    


    
    // grave img
    _graveImg.setTexture(GraphicObjectsManager::getInstance().getTexture(GRAVE_T));
    _graveImg.setSize(PLAYER_IMG_SIZE);


    _playerImg.setTexture(GraphicObjectsManager::getInstance().getTexture(BOMBER_MAN_T));
    auxRect = GraphicObjectsManager::getInstance().getBomberManAnimations()[0];
    _playerImg.setVisibleRect(auxRect.getFrame());
    _playerImg.setColor(PLAYER_1_COLOR);

    _playerImg.setSize(PLAYER_IMG_SIZE);



    // player dynamite img
    _dynamiteImg.setTexture(GraphicObjectsManager::getInstance().getTexture(DYNAMITE_T));
    auxRect = GraphicObjectsManager::getInstance().getDynamiteAnimation();
    _dynamiteImg.setVisibleRect(auxRect.getFrame());
    _dynamiteImg.setSize({ 40, 40 });

    // player health img
    _healthImg.setTexture(GraphicObjectsManager::getInstance().getTexture(BONUSES_T));
    _healthImg.setVisibleRect(HEALTH_R);

    _healthImg.setSize({ 25, 25 });


}


LevelStatusBar::~LevelStatusBar()
{
}

void LevelStatusBar::dispaly(int timeLeft, 
    const vector<Player*> players, GraphicWindow& window)
{
    window.draw(_bg);

    _text.setPosition(TIME_LEFT_POS);
    _text.setCharacterSize(TIME_TEXT_SIZE);
    _text.setString("COUNT DOWN: " + to_string(timeLeft));
    window.draw(_text);

    _text.setCharacterSize(TEXT_SIZE);

    
    if (players[0]->getState() == BomberMan::COMPLETELY_DEAD_S) 
    {
        _player1Alive = false;
        _graveImg.setPosition(PLAYER_1_POS);
        window.draw(_graveImg);
        

    }
    if (players.size() > 1 && players[1]->getState() == BomberMan::LAST_EXPLOSION_S) {
        _graveImg.setPosition(PLAYER_2_POS);
        window.draw(_graveImg);
        _player2Alive = false;
    }

    if (!_player2Alive && !_player1Alive) {
        return;
    }

    if (_player1Alive)
    { 
        _playerImg.setColor(PLAYER_1_COLOR);
        _playerImg.setPosition(PLAYER_1_POS);
        _dynamiteImg.setPosition(PLAYER_1_DYNAMITES_POS);
        _healthImg.setPosition(PLAYER_1_HEALTH_POS);

        _text.setPosition(PLAYER_1_DYNAMITES_TEXT_POS);
        _text.setString(to_string(players[0]->getAvailableDynamites()));
        window.draw(_text);

        _text.setPosition(PLAYER_1_HEALTH_TEXT_POS);
        _text.setString(to_string(players[0]->getHealth()));
        window.draw(_text);

        window.draw(_playerImg);
        window.draw(_dynamiteImg);
        window.draw(_healthImg);


    }
    


    if (players.size() > 1 && _player2Alive) 
    {


        _playerImg.setColor(PLAYER_2_COLOR);
        _playerImg.setPosition(PLAYER_2_POS);
        _dynamiteImg.setPosition(PLAYER_2_DYNAMITES_POS);
        _healthImg.setPosition(PLAYER_2_HEALTH_POS);

        _text.setPosition(PLAYER_2_DYNAMITES_TEXT_POS);
        _text.setString(to_string(players[1]->getAvailableDynamites()));
        window.draw(_text);

        _text.setPosition(PLAYER_2_HEALTH_TEXT_POS);
        _text.setString(to_string(players[1]->getHealth()));
        window.draw(_text);


        window.draw(_playerImg);
        window.draw(_dynamiteImg);
        window.draw(_healthImg);


    }

}
