#pragma once
/*
Holds and controls the game objects.
The board holds all the game objects in 2d vector of forward_list.
(more then one object can be on one tile).
Gives information and get requests from the objects through proxies.
*/

#include <memory>
#include <vector>
#include <list>
#include "BoardProxy.h"
#include "EnemyBoardProxy.h"
#include "ExplosionsBoardProxy.h"
#include "GameObject.h"
#include "Player.h"
#include "Explosion.h"
#include "Dynamite.h"
#include "ExplodingWall.h"
#include "Bonus.h"
#include "definitions.h"
#include "BoardBuffer.h"
#include "AIMap.h"
#include "LevelStatusBar.h"

using std::list;
using std::pair;
class LevelProxy;

class Board
{
public:
    struct GameObjects
    {
        GameObjects(){};
        GameObjects(GameObjects&& g) :
            board(std::move(g.board)), players(g.players), enemies(g.enemies), posfMap(std::move(g.posfMap)),
            FreeTiles(std::move(g.FreeTiles)), levelTime(g.levelTime)
        {}

        board3d board;
        vector<player_p> players;
        vector<enemy_p> enemies;
        // fixed tiles positions
        PosfMap posfMap;
        FreeTilesMap FreeTiles;
        int levelTime = 180;
        Posb boardSize;
    };

    // "Default" cotr = Doing what needs to be done...
    Board(LevelProxy& level);
    void setBoard(GameObjects objects);

    virtual ~Board() = default;

    // not const because level status bar changes.
    void display(int levelTime, GraphicWindow& window);

    // these two methods are called by Level.
    // playPlayers is called when there's some keyboard input
    void playPlayers(sf::Keyboard::Key key);

    // play objects is called at each frame.
    void update();

    // for collisions
    tile& getTile(const Posb& cell);

    // give run away path to enemy
    Path pathToSaftey(const Posb& source);

    // bfs builds shortest path to a destination (the palyer..)
    Path pathToDestination(const Posb& source, const Posb& dest);

    //----------- OBJECTS UPDATES ------------------
    void moveOnBoard(GameObject* obj, const Posb& from, const Posb& to);

    // all those different functions to save th changes in th buffer
    void placeExplosion(explosion_up explosion);
    void placeDynamite(dynamite_up dynamite);
    void placeBonus(bonus_up obj);

    void removeExplosionFromBoard(Explosion* dynamite);
    void removeDynamiteFromBoard(Dynamite* dynamite);
    void removeExplodingwall(ExplodingWall* wall);
    void removeBonus(Bonus* wall);

    const Posf& getTilePosf(const Posb& tile) const;
    bool validPosb(const Posb& posb) const;
    sf::Time getElapsedTime() const;

    bool isFreeTile(const Posb& pos);
    bool dangerousPos(const Posb& pos, const DangerType& danger) const;
    // for enemies.
    Posb getNearestPlayerPos(const Posb& mypos);

    // bomberman asks this to give to dynamite.. this way the dynamite can has this
    // on construction and it's safer.
    ExplosionsBoardProxy& getExplosionProxy();

    // level asks the board for this
    struct Results
    {
        bool gameEnded = false;
        float endTime = 0;
        size_t numOfDeadPlayers = 0;
        bool playersWon = false, enemiesWon = false;

    } _results;

    bool gameEnded();

    // for level.
    Results getResults();

private:
    // --------- PROXIES -----------
    LevelProxy& _levelProxy;
    BoardProxy _boardProxy;
    EnemyBoardProxy _enemyProxy;
    // given to dynamites and explosions.
    ExplosionsBoardProxy _explosionProxy;
    //======================================

    // the board.
    board3d _board;

    // fixed tiles positions
    PosfMap _posfMap;

    vector<player_p> _players;
    vector<enemy_p> _enemies;

    // faster addition and removal..
    // dynamites could be a deque if we trust timing completely
    // but explosions can get more complicated..
    DynamitesList _dynamites;
    ExplosionsList _explosions;

    // ---- AI stuff ---------
    AIMap _AIMap;
    // BoardBuffer.
    // at the end of each frame we'll remove objects marked for removal from the board.
    BoardBuffer _buffer;
    LevelStatusBar _statusBar;

    // ==================== HANDLE INPUT ==============

    bool player1Key(sf::Keyboard::Key key) const;
    bool player2Key(sf::Keyboard::Key key) const;

    Sprite _bgImg;
};
