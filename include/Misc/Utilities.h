#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

const int OBJ_AMOUNT = 17;
const int SOUND_AMOUNT = 17;
const int BACK_SOUND_AMNT = 5;

enum Level
{
	Home,
	MAIN,
	FIRST_DUNGEON,
	SECOND_DUNGEON,
	BOSS_DUNGEON
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
	SWITCH_LEVEL,
	HELP,
	SAVE,
	VICTORY
};

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

enum EnemyType {
	PIG_WARRIOR,
	OCTOROK,
	SEA_URCHIN
};

enum Weapons{NoWeapon, SwordWeapon, BowWeapon};

#define windowHeight 1000
#define WindowWidth 800
#define tileSize 16
#define VOLUME 0.f

#define MAX_HEALTH 6
#define MIN_HEALTH 0

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
	constexpr int PickableItems = 8;
	constexpr int Dungeon2 = 9;
	constexpr int Home = 10;
	constexpr int Help = 11;
	constexpr int Controls = 12;
	constexpr int Zelda = 13;
	constexpr int End = 14;
	constexpr int BossDungeon = 15;
	constexpr int EndingSpriteSheet = 16;
}

namespace BACKGROUND_SOUND
{
	constexpr int Menu = 0;
	constexpr int House = 1;
	constexpr int OverWorld = 2;
	constexpr int Death = 3;
	constexpr int Dungeon01 = 4;
}

namespace SOUNDS
{
	constexpr int Death = 0;
	constexpr int LinkGetSword = 1;
	constexpr int LinkArrow = 2;
	constexpr int LinkDamaged = 3;
	constexpr int LinkSwordSlash01 = 4;
	constexpr int LinkSwordSlash02 = 5;
	constexpr int LinkSwordSlash03 = 6;
	constexpr int LinkSwordSlash04 = 7;
	constexpr int LinkGetItem = 8;
	constexpr int EnemyHit = 9;
	constexpr int EnemyDie = 10;
	constexpr int SeaUrchinPush1 = 11;
	constexpr int SeaUrchinPush2 = 12;
	constexpr int PauseMenuOpen = 13;
	constexpr int PauseMenuClose = 14;
	constexpr int BushCut = 15;
	constexpr int ShieldDeflect = 16;
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

	const sf::Vector2u EnemySwordUp(90, 262);
	const sf::Vector2u EnemySwordDown(107, 262);
	const sf::Vector2u EnemySwordLeft(124, 262);
	const sf::Vector2u EnemySwordRight(141, 262);

	const sf::Vector2u SeaUrchin(1, 301);

	const sf::Vector2u None(160, 160);
}

namespace SPRITE_POSITIONS
{
	const sf::Vector2i Shrub(103, 173);
	const sf::Vector2i Pot(156, 208);
	const sf::Vector2i SwordItem(166, 1);
	const sf::Vector2i BowItem(291, 1);
	const sf::Vector2i HeartItem(166, 31);
	const sf::Vector2u Projectile(265, 143);
	const sf::Vector2u Boulder(190, 170);
	const sf::Vector2i Equipped(120, 210);
	const sf::Vector2i Shield(48, 41);
	const sf::Vector2i FullHeart(48, 61);
	const sf::Vector2i HalfHeart(68, 61);
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

