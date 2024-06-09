#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

const int OBJ_AMOUNT = 11;

enum GAME_STATE { MAIN_MENU, NEW_GAME, EXIT, LOAD_GAME, GAME_RUNNING , ENDGAME};

#define windowHeight 1000
#define WindowWidth 800
#define tileSize 16

namespace TEXTURE
{
	constexpr int Stick = 0;
	constexpr int Menu = 1;
	constexpr int Button = 2;
	constexpr int Score = 3;
	constexpr int Clock = 4;
	constexpr int EndGameScreen = 5;
	constexpr int HelpButton = 6;
	constexpr int SaveButton = 7;
	constexpr int Map = 8;
	constexpr int Link = 9;
	constexpr int MapObjects = 10;
}

namespace ANIMATIONS_POSITIONS{
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
namespace DIRECTIONS{
	const sf::Vector2i Up(0,-1);
	const sf::Vector2i Down(0,1);
	const sf::Vector2i Left(-1,0);
	const sf::Vector2i Right(1,0);
	const sf::Vector2i UpLeft(-1,-1);
	const sf::Vector2i UpRight(1,-1);
	const sf::Vector2i DownLeft(-1,1);
	const sf::Vector2i DownRight(1,1);
}

struct Cell {
	int value;
	int row;
	int col;
};

namespace TEXTURE_DICTIONARY {
	std::vector<std::string> textureDict[1000];
	void initialize() {
		textureDict[264] = { "wall" };
		textureDict[265] = { "wall" };
		textureDict[267] = { "wall" };
		textureDict[268] = { "wall" };
		textureDict[269] = { "wall" };
		textureDict[270] = { "wall" };
		textureDict[274] = { "wall" };
		textureDict[275] = { "wall" };
		textureDict[288] = { "wall" };
		textureDict[290] = { "wall" };
		textureDict[291] = { "wall" };
		textureDict[292] = { "wall" };
		textureDict[293] = { "wall" };
		textureDict[312] = { "wall" };
		textureDict[313] = { "wall" };
		textureDict[339] = { "wall" };
		textureDict[340] = { "wall" };
		textureDict[253] = { "flowers" };
		textureDict[229] = { "flowers" };
		textureDict[152] = { "tree" };
		textureDict[153] = { "tree" };
		textureDict[154] = { "tree" };
		textureDict[176] = { "tree" };
		textureDict[177] = { "tree" };
		textureDict[200] = { "tree" };
		textureDict[201] = { "tree" };
		textureDict[130] = { "tree" };
		textureDict[131] = { "tree" };
		textureDict[154] = { "tree" };
		textureDict[155] = { "tree" };
		textureDict[225] = { "tree" };
		textureDict[249] = { "tree" };
		textureDict[49] = { "house" };
		textureDict[60] = { "house" };
		textureDict[61] = { "house" };
		textureDict[62] = { "house" };
		textureDict[9] = { "house" };
		textureDict[10] = { "house" };
		textureDict[11] = { "house" };
		textureDict[33] = { "house" };
		textureDict[34] = { "house" };
		textureDict[35] = { "house" };
		textureDict[48] = { "house" };
	};
}