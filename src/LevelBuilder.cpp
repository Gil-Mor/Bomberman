
#include "LevelBuilder.h"
#include <fstream>
#include <stdexcept>
#include "Logger.h"
#include <memory>
#include "definitions.h"
#include "GameObject.h"
#include "Player.h"
#include "LevelFileException.h"
#include "ExplodingWall.h"
#include "StoneWall.h"
#include "Bonus.h"
#include <algorithm>
#include "Teleport.h"
#include "FreeTile.h"
#include <cstdlib> // rand
#include "Board.h"
#include "AgressiveEnemy.h"
#include <sstream>

using std::stringstream;
using std::unique_ptr;
using std::ifstream;
using std::to_string;
using std::exception;

const string LEVELS_DIR = "../levels/";

// game Objects Symbols in level file...
const char FREE_TILE_SYMBOL = ' ';
const char STONE_WALL_SYMBOL = '#';
const char PLACE_HOLDER_SYMBOL = '*';
const char TELEPORT_SYMBOL = 'x';

LevelBuilder::LevelBuilder()
{
    ifstream file;
    try {
        file = openFile(LEVELS_DIR + "levels.txt");
    }

    // don't throw from ctor.
    catch (std::exception& e) {
        Logger::getInstance().log("error opening levels file.");
        _buildSuccess = false;
    }

    if (_buildSuccess) {
        _levelsFiles = getLevels(file);
    }

    file.close();

}


vector<string> LevelBuilder::getLevels(ifstream& file)
{
    string line;
    vector<string> files;
    try
    {
        while (!file.eof())
        {
            getline(file, line);
            if (!line.empty())
                files.push_back(LEVELS_DIR + line);
        }
    }

    // function called from ctor so don't throw...
    catch (std::exception& e)
    {
        Logger::getInstance().log("error reading levels file.");
        _buildSuccess = false;
        // nothrow!!!
    }

    return files;
}

Board::GameObjects LevelBuilder::getLevel(size_t level,
    const size_t numOfPlayers, size_t numOfEnemies, const Posf& windowSize) const
{
    try
    {
        ifstream txtfile = openFile(_levelsFiles[level]);


        Board::GameObjects objects;

        // look for time in the file. 
        std::pair<bool, int> levelTime = getLevelTime(txtfile);

        if (levelTime.first) {
            objects.levelTime = levelTime.second;
        }


        // transfer the board to a matrix because it's easier to look for stuff like teleports id's
        v_file file = fileToMatrix(txtfile);


        objects.boardSize = Posb(file.size(), file[0].size());

        objects.board.resize(objects.boardSize.i);
        for (size_t i = 0; i < objects.boardSize.i; ++i) {
            objects.board.at(i).resize(objects.boardSize.j);
        }

        objects.FreeTiles.resize(objects.boardSize.i);
        for (size_t i = 0; i < objects.boardSize.i; ++i) {
            objects.FreeTiles.at(i).resize(objects.boardSize.j, false);

        }


        fillPositionMap(windowSize, objects);

        fillWithBomberMan(numOfPlayers, numOfEnemies, objects);

        fillFromFile(objects, file);



        return std::move(objects);

    }

    catch (std::exception& e)
    {
        Logger::getInstance().log("error building level: " + level);
        throw;
    }
}

std::pair<bool, int> LevelBuilder::getLevelTime(ifstream& file) const
{
    try
    {

        int levelTime = -1;
        string line;
        while (file.peek() != STONE_WALL_SYMBOL)
        {
            getline(file, line);
            size_t pos = line.find("time");
            if (pos != string::npos) {
                
                try {
                    
                    line = line.substr(pos+4);
                    stringstream ss(line);
                    ss >> levelTime;
                    return std::pair<bool, int>(true, levelTime);
                }
                catch (exception& e) {
                    Logger::getInstance().log("problem reading level time");
                    throw;
                }
            }

        }
        return std::pair<bool, int>(false, -1);


    }
    catch (exception& e) {
        Logger::getInstance().log("problem reading level time from the file");
        throw;
    }

}


    void LevelBuilder::fillPositionMap(const Posf& windowSize, Board::GameObjects& objects) const
    {
        try
        {
            Posf boardSizef(float(objects.boardSize.j*TILE_SIZE.x), float(objects.boardSize.i*TILE_SIZE.y));

            Posf difference(windowSize.x - boardSizef.x, windowSize.y - boardSizef.y);

            Posf leftCornerPos(difference.x / 2.f, difference.y / 2.f);

            Posf pos = leftCornerPos;

            objects.posfMap.resize(objects.boardSize.i);

            for (size_t i = 0; i < objects.boardSize.i; ++i)
            {
                for (size_t j = 0; j < objects.boardSize.j; ++j) {
                    objects.posfMap.at(i).push_back(pos);
                    pos.x += TILE_SIZE.x;
                }
                pos.x = leftCornerPos.x;
                pos.y += TILE_SIZE.y;

            }
        }
        catch (exception& e) {
            Logger::getInstance().log("error filling Positions map member of Board::GameObjects.");
            throw;
        }
    }

    void LevelBuilder::fillFromFile(Board::GameObjects& objects, const v_file& file) const
    {
        Posb posb;
        try
        {
            vector<Posb> teleports; // used to save teleports positions for coupling them at the end.

            for (size_t i = 0; i < file.size(); ++i)
            {
                for (size_t j = 0; j < file.at(i).size(); ++j)
                {
                    posb = { i, j };

                    switch (file.at(posb.i).at(posb.j))
                    {
                        // place holder. place only free tiles.
                        case PLACE_HOLDER_SYMBOL:

                            objects.board.at(posb.i).at(posb.j).emplace_front(new FreeTile(objects.posfMap.at(posb.i).at(posb.j), posb));
                            objects.FreeTiles.at(posb.i).at(posb.j) = true;
                            break;


                        case FREE_TILE_SYMBOL:

                            // randomly place exploding walls with bonuses on free tiles except the corners
                            // where the players are.
                            if (randomPlaceExplodingWall(posb, objects))
                            {
                                objects.FreeTiles.at(posb.i).at(posb.j) = false;
                                break;
                            }

                            else {
                                objects.board.at(posb.i).at(posb.j).emplace_front(new FreeTile(objects.posfMap.at(posb.i).at(posb.j), posb));
                                objects.FreeTiles.at(posb.i).at(posb.j) = true;
                            }
                            break;


                        case STONE_WALL_SYMBOL:
                            objects.board.at(posb.i).at(posb.j).emplace_front(new StoneWall(objects.posfMap.at(posb.i).at(posb.j), posb));
                            objects.FreeTiles.at(posb.i).at(posb.j) = false;
                            break;

                        case TELEPORT_SYMBOL:
                        {
                            int id = findTeleportID(file, posb);
                            objects.board.at(posb.i).at(posb.j).emplace_front(new Teleport(objects.posfMap.at(posb.i).at(posb.j), posb, id));
                            teleports.push_back(posb);
                            objects.FreeTiles.at(posb.i).at(posb.j) = true;
                            break;
                        }



                        default:

                            // if the unknown symbol isn't a teleport id..
                            if (!isdigit(file[posb.i][posb.j]))
                            {
                                Logger::getInstance().log("invalid char is level file: " + file.at(posb.i).at(posb.j));
                                throw LevelFileException("invalid char is level file: " + file.at(posb.i).at(posb.j));
                            }
                            else {
                                objects.board.at(posb.i).at(posb.j).emplace_front(new FreeTile(objects.posfMap.at(posb.i).at(posb.j), posb));
                                objects.FreeTiles.at(posb.i).at(posb.j) = true;
                            }
                            break;
                    }
                }
            }

            coupleTeleports(objects, teleports);

        }
        catch (exception& e)
        {
            Logger::getInstance().log("error reading line from file. line is: " + file[posb.i]);
            throw;
        }

    }

    bool LevelBuilder::randomPlaceExplodingWall(const Posb& posb, Board::GameObjects& board) const
    {

        try
        {
            int bonusChance = 40;
            int wallChance = 50;

            int r = rand() % 100;

            bool placedWall = false;
            if (r > wallChance)
            {
                Posf posf = board.posfMap.at(posb.i).at(posb.j);

                placedWall = true;


                int r = rand() % 100;
                if (r > bonusChance)
                {
                    Bonus::BonusType bonus = randomBonus(r);

                    board.board.at(posb.i).at(posb.j).emplace_front(new ExplodingWall(posf, posb, bonus));
                }
                else {
                    board.board.at(posb.i).at(posb.j).emplace_front(new ExplodingWall(posf, posb, Bonus::BonusType::NONE));
                }

            }

            return placedWall;
        }

        catch (exception& e) {
            Logger::getInstance().log("error placing random exploding walls.");
            throw;
        }
    }

    Bonus::BonusType LevelBuilder::randomBonus(int r) const
    {

        switch (static_cast<Bonus::BonusType>(r % Bonus::NUM_OF_BONUSES))
        {
            case Bonus::BonusType::HEALTH:
                return Bonus::BonusType::HEALTH;
                break;

            case Bonus::BonusType::EXPLOSION_RADIUS:
                return Bonus::BonusType::EXPLOSION_RADIUS;
                break;

            case Bonus::BonusType::KICKABILITY:
                return Bonus::BonusType::KICKABILITY;
                break;

            case Bonus::BonusType::MORE_DYNAMITES:
                return Bonus::BonusType::MORE_DYNAMITES;
                break;

            case Bonus::BonusType::SPEED:
                return Bonus::BonusType::SPEED;
                break;

            default:
                return Bonus::BonusType::HEALTH;
                break;
        }

    }


    void LevelBuilder::fillWithBomberMan(size_t numOfPlayers,
        size_t numOfEnemies, Board::GameObjects& objects) const
    {
        try
        {
            placePlayers(numOfPlayers, objects);

            enemy_up enemy;


            Posb bottomLeft = { objects.boardSize.i - 2, 1 };
            Posb bottomRight = { objects.boardSize.i - 2, objects.boardSize.j - 2 };
            Posb topRight = { 1, objects.boardSize.j - 2 };


            if (numOfEnemies >= 1)
            {
                Posb pos = bottomLeft;

                enemy.reset(new AgressiveEnemy(objects.posfMap.at(pos.i).at(pos.j), pos, 1));

                // place higher level enemy.
                /*if (level == 1) {
                enemy.reset(new StupidEnemy(objects.posfMap[bottomRight.y][bottomRight.x], bottomRight));
                }*/

                // ... etc...

                objects.board.at(pos.i).at(pos.j).push_front(std::move(enemy));

                objects.enemies.push_back(static_cast<AIEnemy*>(
                    objects.board.at(pos.i).at(pos.j).begin()->get()));
            }

            if (numOfEnemies >= 2)
            {
                Posb pos = topRight;

                enemy.reset(new AgressiveEnemy(objects.posfMap.at(pos.i).at(pos.j), pos, 2));


                // place higher level enemy.
                /*if (level == 1) {
                enemy.reset(new StupidEnemy(objects.posfMap[bottomRight.y][bottomRight.x], bottomRight));
                }*/

                // ... etc...
                objects.board.at(pos.i).at(pos.j).push_front(std::move(enemy));

                objects.enemies.push_back(static_cast<AIEnemy*>(
                    objects.board.at(pos.i).at(pos.j).begin()->get()));
            }


            // maybe need to make sure we's don't have 2 players.
            if (numOfEnemies == 3 && numOfPlayers != 2)
            {
                Posb pos = bottomRight;

                enemy.reset(new AgressiveEnemy(objects.posfMap.at(pos.i).at(pos.j), pos, 3));



                // place higher level enemy.
                /*if (level == 1) {
                enemy.reset(new StupidEnemy(objects.posfMap[bottomRight.y][bottomRight.x], bottomRight));
                }*/

                // ... etc...
                objects.board.at(pos.i).at(pos.j).push_front(std::move(enemy));

                objects.enemies.push_back(static_cast<AIEnemy*>(
                    objects.board.at(pos.i).at(pos.j).begin()->get()));
            }

        }
        catch (exception& e) {
            Logger::getInstance().log("error placing BomberMan on board.");
            throw;
        }


    }


    void LevelBuilder::placePlayers(size_t numOfPlayers, Board::GameObjects& objects) const
    {
        try
        {
            Posb topLeft = { 1, 1 };
            player_up p(new Player(objects.posfMap.at(topLeft.i).at(topLeft.j), topLeft, 1));

            objects.players.push_back(p.get()); // first push to players vector

            objects.board.at(topLeft.i).at(topLeft.j).push_front(std::move(p)); // then move to board.

            if (numOfPlayers == 2) {

                Posb bottomRight = { objects.boardSize.i - 2, objects.boardSize.j - 2 };


                player_up p(new Player(objects.posfMap.at(bottomRight.i).at(bottomRight.j), bottomRight, 2));

                objects.players.push_back(p.get()); // first push to players vector

                objects.board.at(bottomRight.i).at(bottomRight.j).push_front(std::move(p)); // then move.

            }

        }
        catch (exception& e) {
            Logger::getInstance().log("error placing Players on board.");
            throw;
        }


    }


    void LevelBuilder::ridOfEmptyLines(ifstream& txtFile) const
    {
        try
        {
            while (!txtFile.eof() && (txtFile.peek() != STONE_WALL_SYMBOL))
                txtFile.get();
        }
        catch (exception& e) {
            Logger::getInstance().log("error while ridding of empty lines at the beginning of the file.");
            throw;
        }

    }

    v_file LevelBuilder::fileToMatrix(ifstream& txtfile) const
    {
        try
        {

            // skip empty lines..
            ridOfEmptyLines(txtfile);

            v_file file;
            string line;


            // handle first wall separetly
            getline(txtfile, line);

            size_t lineSize = line.find_last_of(STONE_WALL_SYMBOL);

            if (lineSize == string::npos) {
                throw LevelFileException("error with surrounding walls in the level file.");
            }

            // find last of returns the index not the size.. to use as size we need to increment
            ++lineSize;

            // rid of white space after last wall.
            line = line.substr(0, lineSize);
            file.push_back(line);


            while (getline(txtfile, line))
            {
                if (line.find(STONE_WALL_SYMBOL) == string::npos)
                    break;

                // rid of white space after last wall.
                line = line.substr(0, lineSize);
                file.push_back(line);
            }

            return file;
        }

        catch (exception& e) {
            Logger::getInstance().log("error with surrounding Walls in the level file.");
            throw;
        }


    }


    void LevelBuilder::coupleTeleports(Board::GameObjects& objects,
        vector<Posb>& _teleports) const
    {
        try
        {
            int id1, id2;
            Teleport* tmp1, *tmp2;
            for (size_t i = 0; i < _teleports.size(); ++i)
            {
                Posb pos(_teleports[i]);
                // [0] because the teleport have to be in the upper layer...
                tmp1 = dynamic_cast<Teleport*>(objects.board.at(pos.i).at(pos.j).begin()->get());
                if (tmp1 != nullptr) {

                    id1 = tmp1->getID();
                }
                else {
                    throw LevelFileException("problem with teleports.");
                }


                // for each teleport, look for it's twin in the rest of the teleports
                for (size_t j = i + 1; j < _teleports.size(); ++j)
                {
                    Posb pos(_teleports[j]);
                    tmp2 = dynamic_cast<Teleport*>(objects.board.at(pos.i).at(pos.j).front().get());
                    if (tmp2 != nullptr) {

                        id2 = tmp2->getID();
                    }
                    else {
                        throw LevelFileException("problem with teleports.");
                    }

                    // if the teleports have the same id and tmp2 wasn't 
                    if (id1 == id2)
                    {
                        tmp1->setTwinPos(tmp2->getPosb());
                        tmp2->setTwinPos(tmp1->getPosb());
                        break;
                    }
                }

            }


            // make sure that all teleports have a twin.
            for (size_t i = 0; i < _teleports.size(); ++i)
            {
                Posb pos(_teleports[i]);
                tmp1 = dynamic_cast<Teleport*>(objects.board.at(pos.i).at(pos.j).begin()->get());
                if (tmp1 != nullptr)
                {
                    if (!tmp1->getHasTwin()) {
                        Logger::getInstance().log("there's a teleport with out a twin. teleport's id is " + tmp1->getID());
                        throw LevelFileException("there's a teleport with out a twin. teleport's id is " + tmp1->getID());
                    }
                }
            }
        }

        catch (exception& e) {
            Logger::getInstance().log("something wrong with teleports in level file");
            throw;
        }

        // that's it..
    }

    int LevelBuilder::findTeleportID(const v_file& file, Posb posi) const
    {
        try
        {
            for (size_t row = posi.i - 1; row <= posi.i + 1; ++row)
            {
                for (size_t col = posi.j - 1; col <= posi.j + 1; ++col)
                {
                    if (row < file.size() && col < file.at(row).size())
                    {
                        if (isdigit(file.at(row).at(col))) {
                            return file.at(row).at(col) - 48;
                        }
                    }
                }

            }
            Logger::getInstance().log("no id around teleport.");
            throw LevelFileException("no id around teleport");
        }
        catch (std::exception& e) {
            throw;
        }
    }

    size_t LevelBuilder::getNumOfLevels() const
    {
        return _levelsFiles.size();
    }

    ifstream LevelBuilder::openFile(const string& s) const
    {
        ifstream file;
        file.open(s);
        if (!file.is_open())
        {
            Logger::getInstance().log("couldn't open file. file name: " + s);
            throw std::invalid_argument(s);
        }
        return file;
    }

    LevelBuilder& LevelBuilder::getInstance()
    {
        static LevelBuilder _instance;
        return _instance;
    }