#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

const int OBJ_AMOUNT = 7;
const int SOUND_AMOUNT = 1;
const int BACK_SOUND_AMNT = 2;

enum Level
{
	MAIN,
	FIRST_DUNGEON,
};

enum GAME_STATE {
	MAIN_MENU,
	NEW_GAME,
	EXIT,
	LOAD_GAME,
	GAME_RUNNING,
	SETTINGS,
	PAUSE_MENU,
	DEATH,
	GAME_OVER,
	SWITCH_LEVEL
};

//might want to map each direction to a sf::Vector2i with a map for easy accesing to direction vector
//might need to be held in links class since only link uses those specific states
enum Input {
	PRESS_UP,
	PRESS_DOWN,
	PRESS_LEFT,
	PRESS_RIGHT,
	PRESS_UP_RIGHT,
	PRESS_UP_LEFT,
	PRESS_DOWN_RIGHT,
	PRESS_DOWN_LEFT,
	PRESS_SPACE,
	STANDING,
	NONE
};

#define windowHeight 1000
#define WindowWidth 800
#define tileSize 16
#define VOLUME 0.f

namespace TEXTURE
{
	constexpr int Menu = 0;
	constexpr int Map = 1;
	constexpr int Link = 2;
	constexpr int MapObjects = 3;
	constexpr int Enemies = 4;
	constexpr int StatusBar = 5;
	constexpr int GameOver = 6;
	constexpr int Dungeon1 = 7;
}

namespace BACKGROUND_SOUND
{
	constexpr int Menu = 0;
	constexpr int StartGame = 1;
}

namespace ANIMATIONS_POSITIONS
{

	const sf::Vector2u LinkUp(35,42);
	const sf::Vector2u LinkDown(1,42);
	const sf::Vector2u LinkLeft(35,11);
	const sf::Vector2u LinkRight(69,42);
	const sf::Vector2u LinkAttackUp(52,86);
	const sf::Vector2u LinkAttackDown(1,86);
	const sf::Vector2u LinkAttackLeft(103,86);
	const sf::Vector2u LinkAttackRight(137,86);
	const sf::Vector2u LinkPushDown(188, 11);
	const sf::Vector2u LinkPushUp(222, 11);
	const sf::Vector2u LinkPushLeft(256, 11);
	const sf::Vector2u LinkPushRight(290, 11);
	const sf::Vector2u SwordUp(52,103);
	const sf::Vector2u SwordDown(1,103);
	const sf::Vector2u SwordLeft(103,103);
	const sf::Vector2u SwordRight(137,103);
	const sf::Vector2u OctorokDown(197, 143);
	const sf::Vector2u OctorokLeft(231, 143);
	const sf::Vector2u OctorokUp(291, 143);
	const sf::Vector2u OctorokRight(325, 143);

	const sf::Vector2u PigWarriorUp(35, 229);
	const sf::Vector2u PigWarriorDown(1, 229);
	const sf::Vector2u PigWarriorLeft(68, 229);
	const sf::Vector2u PigWarriorRight(107, 229);
	const sf::Vector2u ArrowUp(35, 126);
	const sf::Vector2u ArrowDown(52, 126);
	const sf::Vector2u ArrowLeft(1, 126);
	const sf::Vector2u ArrowRight(18, 126);
	const sf::Vector2u LinkShieldLeft(103, 59);
	const sf::Vector2u LinkShieldRight(137, 59);
	const sf::Vector2u LinkShieldUp(69, 59);
	const sf::Vector2u LinkShieldDown(1, 59);

}

//might be useless
namespace DIRECTIONS
{
	const sf::Vector2i Up(0, -1);
	const sf::Vector2i Down(0, 1);
	const sf::Vector2i Left(-1, 0);
	const sf::Vector2i Right(1, 0);
	const sf::Vector2i UpLeft(-1, -1);
	const sf::Vector2i UpRight(1, -1);
	const sf::Vector2i DownLeft(-1, 1);
	const sf::Vector2i DownRight(1, 1);
}

struct Cell
{
	int value;
	int row;
	int col;
};

