#include "NewGameState.h"

NewGameState::NewGameState(sf::RenderWindow* window)
	:State(window), m_background(), m_board(), m_view(sf::FloatRect(sf::Vector2f(80.f, 140.f), sf::Vector2f(250.f, 165.f)))
{
	m_background.setTexture(*Resources::getResource().getTexture(TEXTURE::Map));
	m_board.setMap();
	m_board.makeLink();

	m_view.setCenter(m_board.getSprite().getPosition()); //think about a better way to get link position.

	SoundResource::getSound().playBackground(BACKGROUND_SOUND::StartGame);
}

void NewGameState::update(const sf::Time& deltaTime)
{
	updateState(GAME_STATE::GAME_RUNNING);
}

void NewGameState::render(sf::RenderTarget* target)
{
	getWindow()->setView(m_view);
	if (!target)
	{
		target = getWindow();
	}
	target->draw(m_background);

	sf::FloatRect viewBound(target->getView().getCenter() - target->getView().getSize() /2.f, target->getView().getSize());
	m_board.draw(*getWindow(), viewBound);
}

std::unique_ptr<State> NewGameState::handleInput(GAME_STATE gameState)
{
	if(gameState == GAME_STATE::MAIN_MENU)
	{
		return std::make_unique<MainMenu>(getWindow());
	}
	else if (gameState == GAME_STATE::GAME_RUNNING)
	{
		return std::make_unique<GameRunningState>(getWindow(), std::move(m_board), std::move(m_view), m_background);
	}
	else if(gameState == GAME_STATE::EXIT)
	{
		getWindow()->close();
	}
	return nullptr;
}

void NewGameState::buttonPressed(sf::RenderWindow&, const sf::Event&)
{
	//no button here..
}
