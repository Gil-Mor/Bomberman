#pragma once

/*
  A single level. The level holds the board and updates it 
  and displays it in each iteration.
*/
#include "GameClock.h"
#include "Board.h"
#include "LevelProxy.h"
#include "AudioManager.h"

class GraphicWindow;

class ControllerProxy;


class Level
{
public:

    enum LevelState
    {
        RUN_S,
        PAUSE_S
    };

    // Default cotr = Doing what needs to be done...
    Level(ControllerProxy& controller);


    //Level(Board::GameObjects& objects, ControllerProxy& controller);


    /* used to set up a new level.. Sorry but I couldn't do all the move operators for
    everything I needed within time boundaries.
    */
    void setLevel(Board::GameObjects objects);


    /* run the game loop.
    The program can leave and come back to the game loop
    and the current game will be on pause. */
    void run(GraphicWindow& window);



    void display(GraphicWindow& window);

    void resume();


    sf::Time getElapsedTime() const;

private:

    ControllerProxy& _controller;
    LevelProxy _levelProxy;
    Board _board;

    Sprite _bgImg;

    GameClock _clock;
    int _levelTime = 0;

    void handleKeyboard(sf::Keyboard::Key key);

    LevelState _state = RUN_S;

    Board::Results _results;
    bool _gameRunning = true;

    bool timePassed(float start, float duration);

    Sprite _winScreen, _loseScreen;

    GameSound_p _playersWonSound, _playersLostSound;




};

