#pragma once

/* 
enum that connects between names of textures to the
vector of textures in GraphicObjectsManager.
Graphic object need to ask GraphicObjectsManager for a texture with this enum
but it's not right that this enum will be in GraphicObject class
which represents only one graphic object.That object doesn't need
to know of all the other textures.
So here we are..
*/

enum Textures
{

    // game objects sprite sheet
    ALL_GAME_OBJECTS_T = 0,

    // menus
    MAIN_MENU_T,
    PLAY_BUTTON_T,
    ONE_PLAYER_BUTTON_T,
    TWO_PLAYER_BUTTON_T,
    NO_ENEMIES_BUTTON_T,
    ONE_ENEMY_BUTTON_T,
    TWO_ENEMIES_BUTTON_T,
    THREE_ENEMIES_BUTTON_T,
    EXIT_BUTTON_T,
    MAIN_MENU_BUTTON_T,
    LEVELS_MENU_BUTTON_T,
    INSTRUCTIONS_PAGE_BUTTON_T,

    // instruction pages textures
    INSTRUCTION_PAGE_1_T,
    INSTRUCTION_PAGE_2_T,
    INSTRUCTION_PAGE_3_T,
    INSTRUCTION_PAGE_4_T,
    INSTRUCTION_PAGE_5_T,
    FLIP_NEXT_BUTTON_T,
    FLIP_BACK_BUTTON_T,

    RETURN_BUTTON_T,


    LEVEL_1_BUTTON_T,
    LEVEL_2_BUTTON_T,
    LEVEL_3_BUTTON_T,
    LEVEL_4_BUTTON_T,

    MUSIC_ON_BUTTON_T,
    MUSIC_OFF_BUTTON_T,
    VOL_UP_BUTTON_T,
    VOL_DOWN_BUTTON_T,
    FX_ON_BUTTON_T,
    FX_OFF_BUTTON_T,

    GAME_MENU_T,

    LEVEL_BACKGROUND_T,
    WIN_SCREEN_T,
    LOSE_SCREEN_T,

    
    BOARD_BACKGROUND_T,
    FREE_TILE_T,
    BOMBER_MAN_T,
    GRAVE_T,
    DYNAMITE_T,
    STONE_WALL_T,
    EXPLODING_WALL_T,
    EXPLOSION_T,
    BONUSES_T,
    TELEPORT_T,




    NUM_OF_TEXTURES
};

