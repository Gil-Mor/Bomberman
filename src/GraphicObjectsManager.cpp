#include "GraphicObjectsManager.h"
#include "definitions.h"
#include "Logger.h"
#include "Sprite.h"
#include "Animation.h"
#include "BomberMan.h"
#include "Teleport.h"
#include "Bonus.h"

// This font is used by any module that displays a message on the window.
const std::string ORBITRON_FONT = "../font/orbitron.ttf";

const std::string TEXTURE_DIR = "../img/";
const std::string GAME_OBJECTS_DIR = "../img/objects/";
const std::string LEVEL_TEX_DIR = "../img/levelTex/";
const std::string INSTRUCTIONS_DIR = "../img/instructions/";



const std::string MENUS_DIR = "../img/menus/";

GraphicObjectsManager::GraphicObjectsManager()
{
    loadTextures();
    _font.loadFromFile(ORBITRON_FONT);
    setAnimations();

}

const sf::Font& GraphicObjectsManager::getOrbitronFont() const
{
    return _font;
}

void GraphicObjectsManager::loadTextures()
{
    try
    {
        _textures.resize(NUM_OF_TEXTURES);

        // fill with Texture objects.
        for (texture_p& t : _textures) {
            t.reset(new sf::Texture);
        }

        _textures[STONE_WALL_T]->loadFromFile(GAME_OBJECTS_DIR + "stoneWall.jpg");

        _textures[EXPLODING_WALL_T]->loadFromFile(GAME_OBJECTS_DIR + "explodingWall.png");

        _textures[MAIN_MENU_T]->loadFromFile(MENUS_DIR + "MainMenuBG.jpg");

        _textures[BOMBER_MAN_T]->loadFromFile(GAME_OBJECTS_DIR + "bomberMan.png");

        _textures[GRAVE_T]->loadFromFile(GAME_OBJECTS_DIR + "grave.png");

        _textures[EXPLOSION_T]->loadFromFile(GAME_OBJECTS_DIR + "explosion.png");

        _textures[DYNAMITE_T]->loadFromFile(GAME_OBJECTS_DIR + "dynamite.png");

        _textures[BONUSES_T]->loadFromFile(GAME_OBJECTS_DIR + "bonuses.png");

        _textures[TELEPORT_T]->loadFromFile(GAME_OBJECTS_DIR + "teleport.png");





        _textures[LEVEL_BACKGROUND_T]->loadFromFile(LEVEL_TEX_DIR + "levelBG.jpg");
        _textures[WIN_SCREEN_T]->loadFromFile(LEVEL_TEX_DIR + "winScreen.jpg");
        _textures[LOSE_SCREEN_T]->loadFromFile(LEVEL_TEX_DIR + "loseScreen.png");




        _textures[LEVEL_1_BUTTON_T]->loadFromFile(MENUS_DIR + "level1Button.jpg");
        _textures[LEVEL_2_BUTTON_T]->loadFromFile(MENUS_DIR + "level2Button.jpg");
        _textures[LEVEL_3_BUTTON_T]->loadFromFile(MENUS_DIR + "level3Button.jpg");
        _textures[LEVEL_4_BUTTON_T]->loadFromFile(MENUS_DIR + "level4Button.jpg");





        _textures[PLAY_BUTTON_T]->loadFromFile(MENUS_DIR + "playButton.png");
        _textures[EXIT_BUTTON_T]->loadFromFile(MENUS_DIR + "exitButton.png");
        _textures[MAIN_MENU_BUTTON_T]->loadFromFile(MENUS_DIR + "mainMenuButton.png");
        _textures[LEVELS_MENU_BUTTON_T]->loadFromFile(MENUS_DIR + "levelsButton.png");
        _textures[INSTRUCTIONS_PAGE_BUTTON_T]->loadFromFile(MENUS_DIR + "instructionsPageButton.png");
        _textures[FLIP_NEXT_BUTTON_T]->loadFromFile(MENUS_DIR + "flipNextButton.png");
        _textures[FLIP_BACK_BUTTON_T]->loadFromFile(MENUS_DIR + "flipBackButton.png");
        _textures[RETURN_BUTTON_T]->loadFromFile(MENUS_DIR + "returnButton.png");



        _textures[ONE_PLAYER_BUTTON_T]->loadFromFile(MENUS_DIR + "1PlayerButton.png");
        _textures[TWO_PLAYER_BUTTON_T]->loadFromFile(MENUS_DIR + "2PlayersButton.png");
        _textures[NO_ENEMIES_BUTTON_T]->loadFromFile(MENUS_DIR + "0EnemiesButton.png");
        _textures[ONE_ENEMY_BUTTON_T]->loadFromFile(MENUS_DIR + "1EnemyButton.png");
        _textures[TWO_ENEMIES_BUTTON_T]->loadFromFile(MENUS_DIR + "2EnemiesButton.png");
        _textures[THREE_ENEMIES_BUTTON_T]->loadFromFile(MENUS_DIR + "3EnemiesButton.png");
        _textures[MUSIC_ON_BUTTON_T]->loadFromFile(MENUS_DIR + "musicOnButton.png");
        _textures[MUSIC_OFF_BUTTON_T]->loadFromFile(MENUS_DIR + "musicOffButton.png");
        _textures[VOL_UP_BUTTON_T]->loadFromFile(MENUS_DIR + "volumeUpButton.png");
        _textures[VOL_DOWN_BUTTON_T]->loadFromFile(MENUS_DIR + "volumeDownButton.png");
        _textures[FX_ON_BUTTON_T]->loadFromFile(MENUS_DIR + "FXonButton.png");
        _textures[FX_OFF_BUTTON_T]->loadFromFile(MENUS_DIR + "FXoffButton.png");


           
        // ------------- load instruction pages -------------------


        _textures[INSTRUCTION_PAGE_1_T]->loadFromFile(INSTRUCTIONS_DIR + "instructionPage1.jpg");
        _textures[INSTRUCTION_PAGE_2_T]->loadFromFile(INSTRUCTIONS_DIR + "instructionPage2.jpg");
        _textures[INSTRUCTION_PAGE_3_T]->loadFromFile(INSTRUCTIONS_DIR + "instructionPage3.jpg");
        _textures[INSTRUCTION_PAGE_4_T]->loadFromFile(INSTRUCTIONS_DIR + "instructionPage4.jpg");
        _textures[INSTRUCTION_PAGE_5_T]->loadFromFile(INSTRUCTIONS_DIR + "instructionPage5.jpg");


    }
    catch (std::exception& e)
    {
        Logger::getInstance().log("error loading Textures.");
        throw;
    }

}

void GraphicObjectsManager::setAnimations()
{
    {

        _bomberManAnimations.resize(BomberMan::Animations::NUM_OF_BOMBERMAN_ANIMATIONS);

        _bomberManAnimations[BomberMan::Animations::DOWN_A] = Animation(sf::IntRect(0, 0, 24, 20), 3);

        _bomberManAnimations[BomberMan::Animations::UP_A] = Animation(sf::IntRect(72, 0, 24, 20), 3);

        _bomberManAnimations[BomberMan::Animations::LEFT_A] = Animation(sf::IntRect(144, 0, 24, 20), 3);

        _bomberManAnimations[BomberMan::Animations::RIGHT_A] = Animation(sf::IntRect(216, 0, 24, 20), 3);

        _bomberManAnimations[BomberMan::Animations::EXPLODING_A] = Animation(sf::IntRect(288, 0, 24, 20), 8);
    }


    {
        _explodingWallAnimation = Animation(sf::IntRect(0, 0, 63, 60), 4);
    }

    {
        _explosionAnimation = Animation(sf::IntRect(2, 0, 50, 48), 48);
    }

    {
        _dynamiteAnimation = Animation(sf::IntRect(0, 0, 27, 33), 5);
    }

    {
        _teleportAnimations.resize(Teleport::NUM_OF_ANIMATIONS_A);
        _teleportAnimations[Teleport::Animations::REST_A] = Animation(sf::IntRect(0, 0, 96, 103), 4);
        _teleportAnimations[Teleport::Animations::ACTIVE_A] = Animation(sf::IntRect(0, 130, 96, 103), 8);

    }



}


const vector<Animation>& GraphicObjectsManager::getBomberManAnimations() const
{
    return _bomberManAnimations;
}

const Animation& GraphicObjectsManager::getExplodingWallAnimation() const
{
    return _explodingWallAnimation;
}

const vector<Animation>& GraphicObjectsManager::getTeleportAnimation() const
{
    return _teleportAnimations;
}



const Animation& GraphicObjectsManager::getDynamiteAnimation() const
{
    return _dynamiteAnimation;
}

const Animation& GraphicObjectsManager::getExplosionsAnimation() const
{
    return _explosionAnimation;
}

sf::Texture* GraphicObjectsManager::getTexture(const Textures& tex)
{
    return _textures[tex].get();
}


GraphicObjectsManager& GraphicObjectsManager::getInstance()
{
    static GraphicObjectsManager instance;
    return instance;
}
