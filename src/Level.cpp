#include "Level.h"
#include "GraphicWindow.h"
#include "ControllerProxy.h"
#include "GraphicObjectsManager.h"
#include <utility>
#include "AudioManager.h"

//  Doing what needs to be done...


// linger 3 seconds after all the players / enemies have died
const float END_GAME_DURATION = 5;

Level::Level(ControllerProxy& controller)
    : _controller(controller),
    _levelProxy(*this),
    _board(_levelProxy)
{
    _bgImg.setTexture(GraphicObjectsManager::getInstance().getTexture(LEVEL_BACKGROUND_T));

    _bgImg.setSize({ 1600, 1200 });



    _winScreen.setTexture(GraphicObjectsManager::getInstance().getTexture(WIN_SCREEN_T));
    _winScreen.setSize(_controller.getWindowSize());
    _winScreen.setColor({ 255, 255, 255, 60 });

    _winScreen.setPosition({( _controller.getWindowSize().x - _winScreen.getSize().x) / 2,
        (_controller.getWindowSize().y - _winScreen.getSize().y) / 2 });


    _loseScreen.setTexture(GraphicObjectsManager::getInstance().getTexture(LOSE_SCREEN_T));
    _loseScreen.setSize({ _controller.getWindowSize().x - 50, 400 });
    _loseScreen.setPosition({ 0, 300 });


    _loseScreen.setPosition({ (_controller.getWindowSize().x - _loseScreen.getSize().x )/ 2,
        (_controller.getWindowSize().y - _loseScreen.getSize().y) / 2 });

    _playersWonSound = AudioManager::getInstance().getSound(AudioManager::APPLAUSE);
    _playersLostSound = AudioManager::getInstance().getSound(AudioManager::LOSING_BOO);

}

//Level::Level(Board::GameObjects& objects, ControllerProxy& controller)
//    : _levelProxy(*this), _controller(controller),
//    _board(objects, _levelProxy)
//{
//    _bgImg.setTexture(GraphicObjectsManager::getInstance().getTexture(LEVEL_BACKGROUND_T));
//    _bgImg.setSize({ 1600, 1200 });
//
//}

void Level::setLevel(Board::GameObjects objects)
{
    //_board.setBoard(std::move(objects));

    _board.setBoard(std::move(objects));
    _gameRunning = true;
    _levelTime = objects.levelTime;
    _clock.reset();
}

void Level::run(GraphicWindow& window)
{
    if (!_clock.isRunning())
    {
        _clock.resume();
    }


    sf::RenderWindow& sfWindow = window.getWindow();


    sf::Vector2f mouse;
    while (_controller.getState() == ControllerState::PLAYING)
    {


        if (_gameRunning && _board.gameEnded())
        {
            _results = _board.getResults();
            if (_results.playersWon) {
                _playersWonSound->play();
            }
            if (_results.enemiesWon) {
                _playersLostSound->play();
            }
            _gameRunning = false;
        }

        else if (!_gameRunning && timePassed(_results.endTime, END_GAME_DURATION))
        {
            _controller.setState(ControllerState::LEVELS_MENU);
        }

        if (_gameRunning && timePassed(0, _levelTime)) {
            _gameRunning = false;
            _results.enemiesWon = true;
            _playersLostSound->play();
            _results.endTime = getElapsedTime().asSeconds();
        }

        sf::Event event;
        while (sfWindow.pollEvent(event))
        {
            // always convert pixels to window coordinates
            mouse = sfWindow.mapPixelToCoords(sf::Mouse::getPosition(sfWindow));
            switch (event.type)
            {
                case sf::Event::KeyPressed:
                {
                    handleKeyboard(event.key.code);
                    break;
                }
                // catch the resize events
                case sf::Event::Resized:
                {
                    // update the view to the new size of the window
                    sf::FloatRect visible(0.f, 0.f, (float)event.size.width, (float)event.size.height);
                    sfWindow.setView(sf::View(visible));
                    break;
                }

                case sf::Event::Closed:
                    _controller.setState(ControllerState::EXITING);
                    break;

                default:
                    break;
            }
        }

        // players were played already
        if (_state == RUN_S) {
            _board.update();

        }

        sfWindow.clear();
        display(window);
        sfWindow.display();
    }

}


bool Level::timePassed(float start, float duration)
{
    return getElapsedTime().asSeconds() - start >= duration;
}


void Level::display(GraphicWindow& window)
{
    window.draw(_bgImg);

    _board.display(_levelTime, window);

    if (!_gameRunning && _results.playersWon) {
        window.draw(_winScreen);
    }
    else if (!_gameRunning && _results.enemiesWon){
        window.draw(_loseScreen);
    }



}

sf::Time Level::getElapsedTime() const
{
    return _clock.getElapsedTime();
}

void Level::handleKeyboard(sf::Keyboard::Key key)
{
    if (key == sf::Keyboard::Escape) {
        switch (_state)
        {
            case RUN_S:
            {
                _state = PAUSE_S;
                _controller.setState(PAUSE);
                _clock.pause();
                break;
            }
            case PAUSE_S:
            {
                resume();
                break;
            }
        }
    }
    else if (_state == RUN_S) {
        _board.playPlayers(key);
    }
}

void Level::resume()
{
    _state = RUN_S;
    _clock.resume();
}