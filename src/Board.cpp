#include "Board.h"
#include "Player.h"
#include "AIEnemy.h"
#include "Dynamite.h"
#include "StoneWall.h"
#include "FreeTile.h"
#include "ExplodingWall.h"
#include <algorithm>
#include "Bonus.h"
#include "Explosion.h"
#include "GraphicWindow.h"
#include "GraphicObjectsManager.h"
#include "LevelProxy.h"
#include "boardUtils.h"
#include <algorithm>

// "Default" cotr = Doing what needs to be done...


Board::Board(LevelProxy& level)
    :_levelProxy(level),
    _boardProxy(*this),
    _enemyProxy(*this),
    _explosionProxy(*this)

{
    _bgImg.setColor({ 255, 255, 255, 50 });



}



void Board::setBoard(GameObjects objects)
{
    _dynamites.clear();
    _explosions.clear();


    _AIMap = AIMap(std::move(objects.FreeTiles));
    _board = std::move(objects.board);
    _players = std::move(objects.players);
    _enemies = std::move(objects.enemies);
    _posfMap = std::move(objects.posfMap);


    _bgImg.setSize({ float(_board.at(0).size())*TILE_SIZE.x, float(_board.size())*TILE_SIZE.y });
    _bgImg.setPosition(_posfMap.at(0).at(0));

    for (auto& line : _board) {
        for (auto& tile : line) {
            for (auto& obj : tile) {
                obj->setObjectBoardProxy(&_boardProxy);
            }
        }
    }


    for (auto& enemy : _enemies) {
        enemy->setEnemyProxy(&_enemyProxy);
    }


}



/*
Board::Board(Board::GameObjects& objects, LevelProxy& level)
    :
    _AIMap(std::move(objects.FreeTiles)),
    //_freeTiles(std::move(objects.FreeTiles)),
    _board(std::move(objects.board)),
    _players(std::move(objects.players)),
    _enemies(std::move(objects.enemies)),
    _posfMap(std::move(objects.posfMap)),

    _levelProxy(level),
    _boardProxy(*this),
    _enemyProxy(*this),
    _explosionProxy(*this)
{
    _bgImg.setSize({ float(_board.at(0).size())*TILE_SIZE.x, float(_board.size())*TILE_SIZE.y });
    _bgImg.setPosition(_posfMap.at(0).at(0));
    _bgImg.setColor({ 255, 255, 255, 50 });

    for (auto& line : _board) {
        for (auto& tile : line) {
            for (auto& obj : tile) {
                obj->setObjectBoardProxy(&_boardProxy);

            }
        }
    }


    for (auto& enemy : _enemies) {
        enemy->setEnemyProxy(&_enemyProxy);
    }


}
*/


Board::~Board()
{
}

void Board::update()
{


    int i = 0, j = 0;
    for (auto& line : _board)
    {
        for (auto& tile : line)
        {
            for (auto& obj : tile)
            {
                obj->update();
            }
        }
    }
    _buffer.update(_board, _posfMap, _dynamites, _explosions, _AIMap);

    // update danger map once each round. dangerMap is more complex to update then
    // the freeTiles map because of dynamite movement so it won't be updated in the buffer.
    // freeTiles do update inside the buffer.
    _AIMap.updateDangers(_dynamites, _explosions);


}


void Board::playPlayers(sf::Keyboard::Key key)
{

    // pressed key is saved but player only plays in the update iteration.
    if (player1Key(key))
    {
        _players[0]->saveKey(key);
    }

    else if (player2Key(key))
    {
        _players[1]->saveKey(key);
    }
}

void Board::moveOnBoard(GameObject* obj, const Posb& from, const Posb& to)
{

    _buffer.moveObject(obj, from, to);
}



bool Board::gameEnded()
{
    _results.numOfDeadPlayers = 0;

    for (const auto& player : _players) {
        if (player->getState() == BomberMan::COMPLETELY_DEAD_S) {
            ++_results.numOfDeadPlayers;
        }
    }


    if (_results.numOfDeadPlayers == _players.size())
    {
        _results.endTime = _levelProxy.getElapsedTime().asSeconds();
        _results.playersWon = false;
        _results.enemiesWon = true;
        _results.gameEnded = true;
        return true;
    }

    if (std::all_of(_enemies.begin(), _enemies.end(),
        []( const BomberMan* bomberMan) { return bomberMan->getState() == BomberMan::State::COMPLETELY_DEAD_S; }))
    {

        // if all the enemies are dead but two players are still playing go on..
        if (_players.size() - _results.numOfDeadPlayers > 1) {
            return false;
        }
        _results.endTime = _levelProxy.getElapsedTime().asSeconds();
        _results.playersWon = true;
        _results.enemiesWon = false;
        _results.gameEnded = true;
        return true;

    }
    return false;
}

Path Board::pathToSaftey(const Posb& source)
{
    return _AIMap.pathToSaftey(source);
}

Path Board::pathToDestination(const Posb& source, const Posb& dest)
{
    return _AIMap.pathToDestination(source, dest);
}

bool Board::isFreeTile(const Posb& pos)
{
    return _AIMap.isFreeTile(pos);
}

bool Board::dangerousPos(const Posb& pos, const DangerType& danger) const
{
    return _AIMap.dangerPos(pos, danger);
}

Board::Results Board::getResults()
{
    return _results;
}

void Board::placeExplosion(explosion_up explosion)
{
    _buffer.addExplosion(std::move(explosion));
}

void Board::placeDynamite(dynamite_up dynamite)
{
    _buffer.addDynamite(std::move(dynamite));
}

void Board::placeBonus(bonus_up bonus)
{
    _buffer.addBonus(std::move(bonus));
}

void Board::removeBonus(Bonus* bonus)
{
    _buffer.removeBonus(bonus);
}

void Board::removeExplodingwall(ExplodingWall* wall)
{
    _buffer.removeExplodingWall(wall);
}


void Board::removeExplosionFromBoard(Explosion* explosion)
{
    _buffer.removeExplosion(explosion);
}


void Board::removeDynamiteFromBoard(Dynamite* dynamite)
{
    _buffer.removeDynamite(dynamite);
}



tile& Board::getTile(const Posb& pos)
{
    return _board[pos.i][pos.j];
}


bool Board::validPosb(const Posb& posb) const
{
    return 0 <= posb.i && posb.i < _board.size()
        && 0 <= posb.j && posb.j < _board.at(posb.i).size();
}


void Board::display(int levelTime, GraphicWindow& window)
{
    window.draw(_bgImg);

    for (const auto& line : _board) {
        for (const auto& tile : line)
        {
            for (const auto& obj : tile) {
                obj->draw(window);
            }
        }
    }

    for (const auto& player : _players)
    {
        player->draw(window);
    }

    for (const auto& enemy : _enemies) {
        enemy->draw(window);
    }

    _statusBar.dispaly(levelTime - int(_levelProxy.getElapsedTime().asSeconds()), _players, window);

}

sf::Time Board::getElapsedTime() const
{
    return _levelProxy.getElapsedTime();
}

const Posf& Board::getTilePosf(const Posb& tile) const
{
    return _posfMap[tile.i][tile.j];
}

ExplosionsBoardProxy& Board::getExplosionProxy()
{
    return _explosionProxy;
}

Posb Board::getNearestPlayerPos(const Posb& mypos)
{


    if (_players.size() == 1) {
        return _players[0]->getPosb();
    }


    // if both players are dead just return the first player position so that
    // the enemy will keep going..
    if (_players[0]->getState() == BomberMan::State::COMPLETELY_DEAD_S
        && _players[1]->getState() == BomberMan::State::COMPLETELY_DEAD_S)
    {
        return _players[0]->getPosb();
    }


    // if just one is dead return the other
    if (_players[0]->getState() == BomberMan::State::COMPLETELY_DEAD_S) {
        return _players[1]->getPosb();

    }

    if (_players[1]->getState() == BomberMan::State::COMPLETELY_DEAD_S) {
        return _players[0]->getPosb();

    }


    //else return the one closer
    if (ManhattanDistance(_players[0]->getPosb(), mypos)
        < ManhattanDistance(_players[1]->getPosb(), mypos))
    {
        return _players[0]->getPosb();
    }


    return _players[1]->getPosb();

}



bool Board::player1Key(sf::Keyboard::Key key) const
{
    return key == sf::Keyboard::Left
        || key == sf::Keyboard::Right
        || key == sf::Keyboard::Up
        || key == sf::Keyboard::Down
        || key == sf::Keyboard::RControl;
}

bool Board::player2Key(sf::Keyboard::Key key) const
{
    return key == sf::Keyboard::W
        || key == sf::Keyboard::A
        || key == sf::Keyboard::D
        || key == sf::Keyboard::S
        || key == sf::Keyboard::LControl;
}

