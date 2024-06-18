#include "GameOverState.h"

GameOverState::GameOverState(sf::RenderWindow* window)
	: State(window), m_background()
{
	getWindow()->setView(getWindow()->getDefaultView());

	m_background.setSize(sf::Vector2f(windowHeight, WindowWidth));
	m_background.setTexture(Resources::getResource().getTexture(TEXTURE::GameOver));


	add("Back", std::make_unique<BackToMenuButton>(this));
	m_options.back().second->setPosition(sf::Vector2f(450, 450));
	add("Load", std::make_unique<LoadButton>(this));
	m_options.back().second->setPosition(sf::Vector2f(450, 550));
}

void GameOverState::update(const sf::Time&)
{
	for (auto& option : m_options)
	{
		option.second->overButton(*getWindow());
	}
}

void GameOverState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = getWindow();
	}
	target->draw(m_background);
	for (auto& option : m_options)
	{
		option.second->draw(*getWindow());
	}
}

std::unique_ptr<State> GameOverState::handleInput(GAME_STATE gameState)
{
	switch (gameState)
	{
	case GAME_STATE::MAIN_MENU:
		return std::make_unique<MainMenu>(getWindow());
	//case GAME_STATE::LOAD:
	//	return std::make_unique<LoadButton>(getWindow());
	}
	return nullptr;
}

void GameOverState::buttonPressed(sf::RenderWindow& window, const sf::Event& event)
{
	for (auto& option : m_options)
	{
		if (option.second->isButtonPressed(window, event.mouseButton))
		{
			option.second->execute();
		}
	}
}

void GameOverState::add(const std::string& str, std::unique_ptr<Button> c)
{
	m_options.emplace_back(std::make_pair(str, std::move(c)));
}
