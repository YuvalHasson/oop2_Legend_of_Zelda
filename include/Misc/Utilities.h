#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

const int OBJ_AMOUNT = 5;

enum GAME_STATE { MAIN_MENU, NEW_GAME, EXIT, LOAD_GAME, GAME_RUNNING , ENDGAME};

//might want to map each direction to a sf::Vector2i with a map for easy accesing to direction vector
enum Input{
    PRESS_UP,
    PRESS_DOWN,
    PRESS_LEFT,
    PRESS_RIGHT,
    PRESS_UP_RIGHT,
    PRESS_UP_LEFT,
    PRESS_DOWN_RIGHT,
    PRESS_DOWN_LEFT,
    PRESS_SPACE,
	NONE
};

#define windowHeight 1000
#define WindowWidth 800
#define tileSize 16

namespace TEXTURE
{
	constexpr int Menu = 0;
	constexpr int Map = 1;
	constexpr int Link = 2;
	constexpr int MapObjects = 3;
	constexpr int Enemies = 4;
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
}

//might be useless
namespace DIRECTIONS
{
	const sf::Vector2i Up(0,-1);
	const sf::Vector2i Down(0,1);
	const sf::Vector2i Left(-1,0);
	const sf::Vector2i Right(1,0);
	const sf::Vector2i UpLeft(-1,-1);
	const sf::Vector2i UpRight(1,-1);
	const sf::Vector2i DownLeft(-1,1);
	const sf::Vector2i DownRight(1,1);
}

struct Cell
{
	int value;
	int row;
	int col;
};

