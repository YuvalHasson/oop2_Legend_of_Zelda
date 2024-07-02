#include "VictoryState.h"

VictoryState::VictoryState(sf::RenderWindow* window)
	: State(window), m_elapsedTime(sf::Time::Zero), m_direction(1)
{
	m_background.setTexture(Resources::getResource().getTexture(TEXTURE::End));
	m_background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
	m_sprite.setTexture(*Resources::getResource().getTexture(TEXTURE::EndingSpriteSheet));
	m_sprite.setTextureRect(sf::IntRect(9, 146, 40, 63));
	m_sprite.setScale(3.5f, 3.5f);
	m_sprite.setPosition(window->getSize().x / 2.f, window->getSize().y / 2.f);

	m_text.setFont(*Resources::getResource().getFont());
	m_text.setString("Congragulation\nYou  Have  Won");
	m_text.setCharacterSize(50);
	m_text.setLetterSpacing(4);
	m_text.setFillColor(sf::Color::Black);
	m_text.setPosition(window->getSize().x / 2.f - 325, window->getSize().y / 2.f - 300);
}

void VictoryState::update(const sf::Time& deltaTime)
{
	m_elapsedTime += deltaTime;

	if (m_elapsedTime.asSeconds() < 8)
	{
		float moveSpeed = 50.0f;
		float moveDistance = moveSpeed * deltaTime.asSeconds();
		m_sprite.move(0, moveDistance * m_direction);

		if (m_sprite.getPosition().y > getWindow()->getSize().y / 2.f + 50 || m_sprite.getPosition().y < getWindow()->getSize().y / 2.f - 50)
		{
			m_direction *= -1;
		}
	}
	else
	{
		updateState(GAME_STATE::MAIN_MENU);
	}
}

void VictoryState::render(sf::RenderTarget* target)
{
	if (target == nullptr)
	{
		target = getWindow();
	}
	target->draw(m_background);
	target->draw(m_sprite);
	target->draw(m_text);
}

std::unique_ptr<State> VictoryState::handleInput(const GAME_STATE& gameState)
{
	if (gameState == GAME_STATE::MAIN_MENU)
	{
		return std::make_unique<MainMenu>(getWindow());
	}
	else if (gameState == GAME_STATE::EXIT)
	{
		getWindow()->close();
	}
	return nullptr;
}

void VictoryState::buttonPressed(sf::RenderWindow&, const sf::Event&) {}