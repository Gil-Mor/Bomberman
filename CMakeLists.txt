cmake_minimum_required(VERSION 3.10)
project(Bomberman)

IF (NOT CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE Debug)
ENDIF ()

# Create compilation data base for tools (e.g. clang-tidy)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 14)
add_compile_options(
    # Dialect options
    -Wdelete-non-virtual-dtor
    -Wnon-virtual-dtor
    # Warning options
    -Wall
    -Wextra
    -Werror
    -Wunused-local-typedefs
    -Wfloat-equal
    -Wunused-macros
    -Wredundant-decls
    # Ignore SFML errors
    -Wno-switch
)

if(NOT RUN_CLANG_TIDY)
    # These compilation flags aren't supported by clang so they'll
    # mess up clang-tidy output. Add them if not using clang-tidy
    add_compile_options(
        -Wlogical-op
        -Wnoexcept
        -Wstrict-null-sentinel
        -Wunused-but-set-variable
    )
endif()


set(SOURCES
    src/AIEnemy.cpp
    src/AIMap.cpp
    src/AIMapBFSProxy.cpp
    src/AgressiveEnemy.cpp
    src/Animation.cpp
    src/AudioManager.cpp
    src/BFSVisitor.cpp
    src/Board.cpp
    src/BoardBuffer.cpp
    src/BoardProxy.cpp
    src/BomberMan.cpp
    src/BomberManProxy.cpp
    src/Bonus.cpp
    src/Button.cpp
    src/Controller.cpp
    src/ControllerButton.cpp
    src/ControllerProxy.cpp
    src/ControllerStateButton.cpp
    src/Dynamite.cpp
    src/EnemyBoardProxy.cpp
    src/ExplodingWall.cpp
    src/Explosion.cpp
    src/ExplosionsBoardProxy.cpp
    src/FlipPageButton.cpp
    src/FreeTile.cpp
    src/GameClock.cpp
    src/GameMenu.cpp
    src/GameObject.cpp
    src/GraphicObjectsManager.cpp
    src/GraphicWindow.cpp
    src/InstructionPage.cpp
    src/Level.cpp
    src/LevelBuilder.cpp
    src/LevelButton.cpp
    src/LevelFileException.cpp
    src/LevelProxy.cpp
    src/LevelStatusBar.cpp
    src/LevelsMenu.cpp
    src/Logger.cpp
    src/MainMenu.cpp
    src/Menu.cpp
    src/Movable.cpp
    src/MusicButton.cpp
    src/NumOfEnemiesButton.cpp
    src/NumOfPlayersButton.cpp
    src/PauseMenu.cpp
    src/Player.cpp
    src/Posb.cpp
    src/Sprite.cpp
    src/StoneWall.cpp
    src/Teleport.cpp
    src/Vertex.cpp
    src/boardUtils.cpp
    src/main.cpp
    src/returnButton.cpp
)

add_executable(bomberman ${SOURCES})
target_include_directories(bomberman
    PRIVATE
        src
)

find_package(Boost 1.56 REQUIRED COMPONENTS graph)
target_link_libraries(bomberman PRIVATE Boost::graph)

# SFML-2.4.2 version
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake_modules)
find_package(SFML 2.4.2 REQUIRED COMPONENTS graphics audio window system)

target_include_directories(bomberman PRIVATE ${SFML_INCLUDE_DIR})
target_link_libraries(bomberman PRIVATE ${SFML_DEPENDENCIES})
target_link_libraries(bomberman PRIVATE ${SFML_LIBRARIES})

add_custom_target(copy_sfml_libs_to_bin_dir
    ALL
    cp /usr/lib/x86_64-linux-gnu/libsfml-graphics.so.2.4 ${CMAKE_BINARY_DIR} &&
    cp /usr/lib/x86_64-linux-gnu/libsfml-audio.so.2.4 ${CMAKE_BINARY_DIR} &&
    cp /usr/lib/x86_64-linux-gnu/libsfml-window.so.2.4 ${CMAKE_BINARY_DIR} &&
    cp /usr/lib/x86_64-linux-gnu/libsfml-system.so.2.4 ${CMAKE_BINARY_DIR} &&
    cp /usr/lib/x86_64-linux-gnu/libopenal.so.1 ${CMAKE_BINARY_DIR} &&
    cp /usr/lib/x86_64-linux-gnu/libsndio.so.6.1 ${CMAKE_BINARY_DIR}
    DEPENDS bomberman
)

include(CodeFormatter)
if (RUN_CLANG_TIDY)
    include (StaticCodeAnalysis)
endif()