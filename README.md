# The Legend Of Zelda Clone
Our rendition of the classic game made using C++ and SFML as graphics library.<br />The player's goal is to navigate through dungeons filled with puzzles and enemies. The first, is a mandatory dungeon and rewards the player with a sword, essential for progressing to the optional next dungeon, where a powerful bow awaits. Ultimately, the game concludes with a battle against the evil wizard, whose defeat marks the end of game.

## Video Overview:
[![IMAGE ALT TEXT HERE](https://img.youtube.com/vi/jM9-a42St-8/0.jpg)](https://www.youtube.com/watch?v=jM9-a42St-8)

## Game Rules and Objectives:
In the game there are 3 types of enemies:

•	PigWarriors – Smart enemies that attacks from a short distance and uses a sword to stab the player.<br />
•	Octoroks – Random enemies that roam around the map and randomly shoot projectiles.<br />
•	Wizard(end boss) – The wizard has two phases, in phase one the wizard will get close to stab the enemy, in phase two the wizard will become invincible and will shoot many projectiles in a circle pattern. It will switch between those two phases until it is defeated.

Besides battling enemies, players will face puzzles that involve pushing boulders to clear paths or position them correctly.

The player can earn two types of weapons:<br />
•	Sword – Used for close combat.<br />
•	Bow – After earning the bow the player can use it to shoot arrows at enemies.

Additionally the player is equipped with a shield right from the start,
Which is used to block stabs and deflect projectiles, making it crucial for progressing through the game.

The game features an open-world design with no specific level structure, allowing the players to walk around the map and progress in the way they choose to, only after defeating the wizard the game will end.

## Controls:
**Arrow keys/WASD** – Player movement  
**E** – Hold to interact with the signs around the map  
**B** – Hold B to use defend with your shield in your current direction  
**TAB** – Switch weapon  
**SPACE** – Attack  
**ESC** – Pause menu

# Development
## Project Structure
•	**src/**: Source code  
•	**include/**: Header files  
•	**Resources/**: Game assets (images, sounds, etc.)  
•	**CMakeLists.txt**: Build configuration

## Notable Algorithms used:
•	**BFS** – as smart movement strategy for enemies.  
•	**Ray-Casting** – casting a ray between the enemy and the player and checks if the ray reaches the player to check for line of sight between them.

## Installation
### Via the installation script
•	Download the InstallGame.bat
•	Download the InstallGame.ps1
•	Run the batch script(Game will be installed in documents folder)

### Building the project
•	SFML 2.6.0
•	CMake 3.26 or higher
•	A C++17 compatible compiler

#### Building the Project
```sh
git clone https://github.com/YuvalHasson/oop2_Legend_of_Zelda.git
cd oop2_Legend_of_Zelda
mkdir build && cd build
cmake ..
make
./oop2_project
```

# Made by:
[Yuval Hasson](https://github.com/YuvalHasson)  
[Or Shain](https://github.com/orshain)  
[Yehu Raccah](https://www.linkedin.com/in/yehu-raccah-8530b92b9/)

## Credits:
- SFML
- Noam Debel for making the overview video
- Hadassah Academic College
