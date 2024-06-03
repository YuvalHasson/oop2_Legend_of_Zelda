#pragma once

const int OBJ_AMOUNT = 9;

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
}