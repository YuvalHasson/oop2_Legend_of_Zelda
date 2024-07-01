#pragma once

#include "State.h"
#include "Board.h"
#include "GameRunningState.h"
#include "Link.h"

class SaveState : public State
{
public:
	SaveState(sf::RenderWindow*, std::vector<Board>&&, sf::View&&, Level);

	virtual void update(const sf::Time&) override;
	virtual void render(sf::RenderTarget* = nullptr) override;
	virtual std::unique_ptr<State> handleInput(const GAME_STATE&) override;
	virtual void buttonPressed(sf::RenderWindow&, const sf::Event&) override;

	void saveGame() const;

private:
	Level m_level;
	sf::View m_view;
	std::vector<Board> m_boardLevels;
	std::unique_ptr<Link> m_link;
};