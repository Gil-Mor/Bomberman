I've recreated the [BomberMan](https://en.wikipedia.org/wiki/Bomberman) game with C++, [boost](https://www.boost.org/), and [SFML](https://www.sfml-dev.org) lib.

Here's a [Demo](https://www.youtube.com/watch?v=OxSsXRgE7nM) of the final result 

--------------- OBJECT ORIENTED DESIGN -----------------

--- Controller ---
Controls the flow of the program by switching states. 
Activates the menus, loads levels from level builder. 
The states are set through the 'ControllerProxy' which is given to classes
that need to communicate with the controller.

* Controller States are:  MAIN_MENU,  GAME_MENU, INSTRUCTION_MENU, 
                          LEVELS_MENU, PLAYING, PAUSE, EXITING.



--- Level ---
Level runs a single level. The level has a board, 
GameClock (encapsulates 'Chronometer' which is a clock from sf::tools Tool pack),
Level Proxy and Level Status Bar.

---- Board ----
Since many objects can be on the same tile and moving objects
need to move from tile to tile a lot the Board is a 2d vector of forward_lists.

* The Board runs the game by updating all the objects.
  The board has a BoardProxy which encapsulates calls to the board's methods
  from game objects.

* Board has an AIMap which is a map that's used to build paths (using boost::bfs) for the
  enemies. paths to the nearest player or the a safe position.

*** Board Buffer - objects 'update' their state each round and tell the board
    what they did (moved, added stuff to the board, removed stuff), the board
    saves this information in the BoardBuffer and after each round the Buffer
    applies these changes to the board.

    The Buffer uses std::set to save the pointers of objects to remove because
    there's a chance that two things will ask to remove something twice 
    (BomberMan and Bonus..)..


* Board Proxies - There are three types of Proxies. BoardProxy is the base class
  and provides basic operations and player related operations. 
  'EnemyBoardProxy' provides the enemies information like is the next tile is free
  and paths to the player or to a safe place. 
  It would be simple to add more functionalities like going to the nearest bonus
  or Barrel..


--- Level Construction ----
LevelBuilder is a singleton responsible for reading levels from the files.
It saves the objects in the Board::GameObjects struct and then passes it
to the level.

--- Logging Errors ---
Logger is a singleton which logs errors to a log file.
Mostly used by LevelBuilder.


--- Exceptions ---
LevelBuilder throws LevelFileException if something fails.




-------- Game Objects ------------


* Game objects have their board position. It makes it easier to do stuff when
  the object knows it's own position. 

* Movable objects are derived from Movable class which executes the movement operations.
  All Movable objects move just the same except the explosion.

  the object has a Movable::Direction. it tries to move in that direction,
  it's offset is moved by '_speed*MOVE_PER_FRAME', then, if the offset is big enough
  it collides with the next tile and updates it's '_movedTile' boolean flag in the collision
  methods. Then if it moved Movable tells the board to move it.
  Teleportation is a special case that needs to be handled but all movable objects
  get teleported just the same (except explosions which don't teleport).

* Objects move in 'offset' meaning they don't move a tile in each movement but
  they can move inside a tile and move 'smoothly' between tiles.

* Enemy movement - Although the enemy gets path with position to go to he's 
converting the path to directions
because it's a lot more easy to handle the smooth movement when dealing with
requests to go in a certain direction then to do this with absolute positions.

 
* BomberMan
Is the base class of the BomberMan. Player and AIEnemy. 
Their collisions and animation are the same.. Player overrides Bonus collision
because the player plays a sound when collecting a bonus.



--- Enemies ----

AIEnemy is the base class of enemies.
Enemies also have states that they move between according to information like
if they're in danger.

I had Stupid enemy which had random movement
and AggressiveEnemy which took a path to one of the players. I deleted Stupid enemy
and stayed with only Aggressive Enemy but we could add more enemies that
act differently by changing the order of states and adding more functionality
to AIMap.



* Dynamites - BomberMan places a dynamite and gives it a 'BomberManProxy'
  so that the dynamite can make a call back to the BomberMan to increment it's
  available dynamites count.

  The Dynamite places a 'center explosion'. 

* Explosions - The center Explosion collides with all four tiles
  in four directions. If the Explosion 'moved' (didn't hit a stone wall)
  then it propagates four different explosions, all with radius-1 and each one
  with it's own direction.
  Then, each explosions tries to move in it's own direction.
  If it succeed then it propagates another explosions in the same direction
  with radius-1. on and on until the explosion hits a wall and sets it's 
  _propagate flag to false or until radius == 0.


--- Explosion Proxy ---
since only dynamites and explosions need to place explosions on the board, 
so in order that BomberMan won't accidentally place an explosions
instead of a Dynamite, we give that ability only to dynamites and Explosions.


--- Collisions ---
I'm using double Dispatch inside the classes.



* Exploding Walls - are walls that explode when colliding with explosions.


* Bonuses - Since all Bonuses act exactly the same I'll 
  do one Bonus class and it'll have an enum
  with bonus types. It'll get it's type on construction.



---- Graphics ----
I encapsulated sfml objects inside my own classes like Sprite and GrpahicWindow.
Since the use of these objects is th same in most cases (draw a sprite, set texture etc..),
If you'd want to change the graphic library or the sfml object type used you won't need
to all the code just the parts where the use is more heavy like poll events and 'mapCoordsToPixles'..
The Sprite class encapsulates sf::RectangleShape and GraphicWindow encapsulates sf::RenderWindow.


--- Audio ---
AudioManager is a singleton responsible for loading sounds. It saves them
and gives references to the objects so it's possible, for example,
to turn off all the sound effects.
MusicButton class controls these operations.




-------- Menus ---------
All Menus inherit from Menu base class.
The menus just set their different buttons and background image 
but they all use the 'run' method of the Base class.

------- Buttons ---------
Button is the base class for all buttons and implements the functionality of
a button.

* ControllerButton - is a button that calls methods in the controller 
  like number of players and number of enemies.

* ControllerStateButton - has a certain ControllerState and 
  it calls the controller's setState method.


--- Proxies to objects after construction---

Since I'm building the objects in LevelBuilder, 
The Level and the board can't be ready before the objects are so i can't
give the proxies...



--- Level and Board default cotrs ---
I didn't find a way of loading a level, playing, possibly pausing and then resuming 
without having a Level member in the controller which enforces me to give it a default cotr
which has to initialize the level proxies and the board which in turn also has to 
initialize it's own proxies.. 
If I want to be able to show the instruction page when pausing it means going 
out to the controller 
I'm doing what needs to be done...


--------------- LIST OF FILES -----------------

* AgressiveEnemy.h / .cpp
  an Enemy that chases the player.

* AIEnemy.h / .cpp
  Base Class for enemies.

* AIMap.h / .cpp
  Saves location of free tiles and dangers (explosions or explosion areas)
  And gives that information to th AIEnemy. 

* AIMapBFSProxy.h / .cpp
  Proxy for BFS visitor. 

* Animation.h / .cpp
  update  the position of a frame (sf::IntRect) on a texture. 

* AudioManager.h / .cpp
  Singleton that loads and saves audio files. 

* BFSVisitor.h / .cpp
  Derived from BFS Visitor. executes commands on bfs events.

* Board.h / .cpp
  Holds and controls the game objects.
  
* BoardBuffer.h / .cpp
  Saves changes like removal, addition, and moving objects on the board in each
  game round then updates the board and the AIMap once.

* BoardProxy.h / .cpp
  Base class for all board proxies. Has methods that mostly the player uses.

* boardUtils.h / .cpp
  Some utility methods like Manhattan Distance and to ask
  if position a is closer to position c then position b. 

* BomberMan.h / .cpp
  Base class for BomberMan. Player and enemies. 

* BomberManProxy.h / .cpp
  BomberMan gives this to dynamites when he places them on the board
  so that they can tell him they exploded, incrementing it's dynamite count.

* Bonus.h / .cpp
  Power Ups BomberMan can collect. 

* Button.h / .cpp
  Base class for all buttons. Implements Button common functionality

* Chronometer.h
  Aux tool from sf::tools tool pack. 

* Controller.h / .cpp
  Controls the flow of the program. 

* ControllerButton.h / .cpp
  Buttons that get ControllerProxy and use it to call methods in the controller.

* ControllerProxy.h / .cpp
  Encapsulates calls to methods in the controller.
  Also holds the ControllerState enum so that everyone can use it.

* ControllerStateButton.h / .cpp
  Buttons that change a state in the controller. 

* definitions.h
  general type definitions.

* Dynamite.h / .cpp
  The bomb. Placed by BomberManon the board, ticks, and then places an explosion. 

* EnemyBoardProxy.h / .cpp
  Derived from BoardProxy. encapsulates calls to board for enemy
  which needs the location of the nearest player, path to the closest position
  to the player and path so a safe position.


* ExplodingWall.h / .cpp
  Exploding Walls that can contain a bonus. Explode when hit by explosion

* Explosion.h / .cpp
  Explosion on a single tile. 

* ExplosionsBoardProxy.h / .cpp
  Let's Dynamites and Explosions put explosions on the board.

* FlipPageButton.h / .cpp
  Flips a page in the Instruction Pages.

* FreeTile.h / .cpp
  A Free tile

* GameClock.h / .cpp
  The game Clock.

* GameMenu.h / .cpp
  Game Menu. Where the user chooses number of players and number of enemies.

* GameObject.h / .cpp
  Base class for all game objects.

* GraphicObjectsManager.h / .cpp
  Singleton that's in charge of loading Textures and preparing Animations
  for objects.

* GraphicWindow.h / .cpp
  Encapsulates a graphic window. (sf::RenderWindow). 

* InstructionPage.h / .cpp
  The Instruction pages. Derived from menu for the buttons..

* Level.h / .cpp
  A single level. The level holds the board and updates it 
  and displays it in each iteration.

* LevelBuilder.h / .cpp
  Singleton that reads levels from txt files and builds them.

* LevelButton.h / .cpp
  Tells the controller which level to load.

* LevelFileException.h / .cpp
  Exception that is thrown when an error occurred while reading level file. 
 
* LevelProxy.h / .cpp
  Level proxy is used to give the time from the game clock. 

* LevelsMenu.h / .cpp
  The menu with level buttons.

* LevelStatusBar.h / .cpp
  Displays the players status.

* Logger.h / .cpp
  Singleton that logs error to a log file.  

* MainMenu.h / .cpp
  The opening menu of the program. 

* Menu.h / .cpp
  Base class for all menus. The menus just set their different buttons
  and background image but they all use the 'run' method of this class.

* Movable.h / .cpp
  Base class for all objects that use collisions to check the tiles around them.
  Almost all of the operation involved in movement are preformed in this class.

* MusicButton.h / .cpp
  Button that controls the music. Calls methods in the 'AudioManager' Singleton.

* NumOfEnemiesButton.h / .cpp
  Tells the controller how many enemies need to be in the level.

* NumOfPlayersButton.h / .cpp
  Tells the controller how many players need to be in the level.

* PauseMenu.h / .cpp
  Like Main menu only that play button leads back to the game.

* Player.h / .cpp
  BomberMan controlled by the player. 

* Posb.h / .cpp
  Position on the board. row and column. 

* returnButton.h / .cpp
  A Button which tells the controller to go back to the previous state.

* Sprite.h / .cpp
  Encapsulates a Sprite (sf::RectangleShape) in this case. 

* SpritesList.h 
  enum that connects between names of textures to the
  vector of textures in GraphicObjectsManager.

* StoneWall.h / .cpp
  Unpassable barrier. 

* Teleport.h / .cpp
  Teleport. Has a twin.

* Vertex.h / .cpp
  Wrapper for Boost graph vertex. The private member vertex_d



--------------- DATA STRUCTURES -----------------

* Proxies: BoardProxy

* Singletons: Logger, LevelBuilder, GraphicObjectManager

* menus bind keyboard keys to controller states with a map.

* Double Buffer for updating the board at once.


--------------- NOTABLE ALGORITHMS -----------------

* BFS to find the shortest path to a destination 
  (or as close to the destination as possible).
  
-------------- CREATE YOUR OWN LEVEL ---------------

Look at the levels in 'levels' folder. 
The level have to be surrounded with walls '#'.
The Bomberman will be placed in the corners and the Barrles are placed randomly so you need to put placeholders '*' in the corners to avoid collisions.
Place teleports with 'x' (lower case) and put a single digit somewhere around it.
The digit is the teleport's ID. Put the same digit around that teleport 'twin'.
You can specify the time given to the level by writing 
'time' and the time in seconds you give to win this board.
The default time is 3 minutes.
Give the file some name and add it to the 'levels.txt' file.

Actually... There is a button for every level so in order to add
a level you need to add a button but you just replace one of the files
level1, level2, .. level4 and then look for the button that loads this level..

The Level buttons order is:
top left: level2
top right: level 3
bottom left: level1
bottom right level4

NOTE: Like in all versions of the game i played.. If the board is not in the shape of
      # # # # ... # meaning wall space wall space, There's a chance the enemies
      will be stuck because the dynamites they'll place won't hit any barrels.
      You can make different levels but just make sure you dont have ### 3 walls
      without a space.





