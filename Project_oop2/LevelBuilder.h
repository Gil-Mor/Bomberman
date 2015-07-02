#pragma once
/* 
  Singleton that reads levels from txt files and builds them.
   Controller asks for the levels.
*/
#include <vector>
#include <string>
#include "Level.h"
#include <fstream>
#include "definitions.h"
#include <unordered_map>
#include "Bonus.h"

using std::unordered_map;
using std::vector;
using std::string;
using std::ifstream;

typedef vector< string> v_file;

class LevelBuilder
{
public:

    static LevelBuilder& getInstance();

    Board::GameObjects getLevel(size_t i, const size_t numOfPlayers, size_t numOfEnemies,const  Posf& windowSize) const;

    size_t getNumOfLevels() const;

private:

    vector<string> _levelsFiles;

    //unordered_map<char, 

    // indicates that the initial file reading was successful.
    bool _buildSuccess = true;

    // fills the _levels vector with the levels file names.
    vector<string> getLevels(ifstream& file);

    std::pair<bool, int> getLevelTime(ifstream& file) const;

    v_file fileToMatrix(ifstream& txtfile) const;

    void ridOfEmptyLines(ifstream& txtFile) const ;

    void fillPositionMap(const Posf& windowSize, Board::GameObjects& objects) const;

    //void fillWithFreeTiles(Board::GameObjects& objects) const;

    void fillFromFile(Board::GameObjects& objects, const v_file& file) const;

    bool randomPlaceExplodingWall(const Posb& posi, Board::GameObjects& board) const;
    Bonus::BonusType randomBonus(int r) const;
    //void placeExplodingWallWithBonus(int type, const Posb& posb, Board::GameObjects& board) const;

    void LevelBuilder::fillWithBomberMan(size_t level, size_t numOfPlayers,
        size_t numOfEnemies, Board::GameObjects& objects) const;

    //bool corner(const Posb& posi, const Posb& boardsize) const;

    void placePlayers(size_t numOfPlayers, Board::GameObjects& objects) const;


    int findTeleportID(const v_file& file, Posb posi) const;

    ifstream openFile(const string& s) const;

    void coupleTeleports(Board::GameObjects& objects, vector<Posb>& _teleportCollector) const;

    // make ctor, copy-ctor and assignment operator private.
    LevelBuilder();
    LevelBuilder(const LevelBuilder&);
    LevelBuilder& operator=(LevelBuilder const& copy);

};