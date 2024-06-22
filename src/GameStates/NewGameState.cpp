#include "NewGameState.h"

NewGameState::NewGameState(sf::RenderWindow* window)
	:State(window), m_background(), m_board(), m_view(sf::FloatRect(sf::Vector2f(80.f, 140.f), sf::Vector2f(250.f, 165.f)))
{
	m_background.setTexture(*Resources::getResource().getTexture(TEXTURE::Map));
	m_board.makeLink();
	m_board.setMap();

	m_view.setCenter(m_board.getLink().getPosition()); //think about a better way to get link position.

	SoundResource::getSound().playBackground(BACKGROUND_SOUND::StartGame);
}

void NewGameState::update(const sf::Time& deltaTime)
{
	updateState(GAME_STATE::GAME_RUNNING);
}

void NewGameState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = getWindow();
	}
	target->setView(m_view);
	target->draw(m_background);

	sf::FloatRect viewBound(target->getView().getCenter() - target->getView().getSize() /2.f, target->getView().getSize());
	m_board.draw(*target, viewBound);
}

std::unique_ptr<State> NewGameState::handleInput(const GAME_STATE& gameState)
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

void NewGameState::buttonPressed(sf::RenderWindow&, const sf::Event&) {}
