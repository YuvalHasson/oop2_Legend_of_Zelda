#pragma once

#include "State.h"
#include "MainMenu.h"
#include "GameRunningState.h"
#include "Board.h"

#include "BadFileName.h"
#include "BadFileFormat.h"

class LoadGameState : public State
{
public:
	LoadGameState(sf::RenderWindow*, GAME_STATE);
	LoadGameState(sf::RenderWindow*, GAME_STATE, std::vector<Board>&& , sf::View&&, Level);

	virtual void update(const sf::Time&) override;
	virtual void render(sf::RenderTarget* = nullptr) override;
	virtual std::unique_ptr<State> handleInput(const GAME_STATE&) override;
	virtual void buttonPressed(sf::RenderWindow&, const sf::Event&) override;

	void errorFileMsg(sf::RenderWindow* window, std::string msg);

	void updateLink();
	void updateLevel();

private:
	void setMap();
	void loadGame(sf::RenderWindow* window);
	void initialize(sf::RenderWindow*);
	std::vector<Board> m_boardLevels;
	sf::View m_view;
	std::vector<std::unique_ptr<Enemy>> m_enemyObjects;
	std::vector<std::unique_ptr<Inanimate>> m_inanimateObjects;
	std::vector<std::unique_ptr<StaticObjects>> m_staticObjects;
	
	GAME_STATE m_cameFromState;
	std::vector<Board> m_boardLevelsIfNoSave;
	Level m_levelIfNoSave;

	// about Link
	std::unique_ptr<Link> m_link;
	sf::Vector2f m_linkPosition;
	int m_linkLife;
	std::vector<int> m_weaponIds;

	// about the level
	std::vector<std::pair<sf::Vector2f, EnemyType>> m_enemiesPositions;
	std::vector<sf::Vector2f> m_boulderPositions;
	std::vector<sf::Vector2f> m_shrubPositions;
	std::vector<sf::Vector2f> m_potsPositions;
	int m_level;

	// for exceptions
	bool m_isGameLoad = false;
	bool m_isLoadFail = false;
};
