cmake_minimum_required(VERSION 3.10.2)  # CMake version check
project(Bomberman)                      # Create project "simple_example"
set(CMAKE_CXX_STANDARD 14)              # Enable c++14 standard

add_compile_options(-Wall -Wno-switch)

IF (NOT CMAKE_BUILD_TYPE)
    message(STATUS "Setting CMAKE_BUILD_TYPE TO Debug")
    SET(CMAKE_BUILD_TYPE Debug)
    message(STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
ENDIF ()

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