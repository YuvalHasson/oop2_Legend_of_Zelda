#include "HelpState.h"

HelpState::HelpState(sf::RenderWindow* window)
	: State(window)
{
	m_helpScreen.setSize(sf::Vector2f(windowHeight, WindowWidth));
	m_helpScreen.setTexture(Resources::getResource().getTexture(TEXTURE::Help));

	add("Menu", std::make_unique<BackToMenuButton>(this));
}

void HelpState::update(const sf::Time& deltaTime)
{
	for (const auto& option : m_options)
	{
		option.second->overButton(*getWindow());
	}
}

void HelpState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = getWindow();
	}

	target->draw(m_helpScreen);
	for (const auto& option : m_options)
	{
		option.second->draw(*target);
	}
}

std::unique_ptr<State> HelpState::handleInput(const GAME_STATE& gameState)
{
	if (gameState == GAME_STATE::MAIN_MENU)
	{
		return std::make_unique<MainMenu>(getWindow());
	}
	return nullptr;
}

void HelpState::buttonPressed(sf::RenderWindow& window, const sf::Event& event)
{
	for (const auto& option : m_options)
	{
		if (option.second->isButtonPressed(window, event.mouseButton))
		{
			option.second->execute();
		}
	}
}

void HelpState::add(const std::string& str, std::unique_ptr<Button> c)
{
	m_options.emplace_back(std::make_pair(str, std::move(c)));
}
