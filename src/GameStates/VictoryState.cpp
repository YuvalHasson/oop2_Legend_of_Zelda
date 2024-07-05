#include "VictoryState.h"

VictoryState::VictoryState(sf::RenderWindow* window)
	: State(window), m_elapsedTime(sf::Time::Zero), m_direction(1), m_buttonPressed(false)
{
	m_background.setTexture(Resources::getResource().getTexture(TEXTURE::End));
	m_background.setSize(sf::Vector2f(static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y)));
	m_sprite.setTexture(*Resources::getResource().getTexture(TEXTURE::EndingSpriteSheet));
	m_sprite.setTextureRect(sf::IntRect(9, 146, 40, 63));
	m_sprite.setScale(3.5f, 3.5f);
	m_sprite.setPosition(window->getSize().x / 2.f, window->getSize().y / 2.f);

	m_text.setFont(*Resources::getResource().getFont());
	m_text.setString("Congratulation\nYou  Have  Won");
	m_text.setCharacterSize(50);
	m_text.setLetterSpacing(4);
	m_text.setFillColor(sf::Color::Black);
	m_text.setPosition(window->getSize().x / 2.f - 325, window->getSize().y / 2.f - 300);

	m_fadingRectangle.setPosition(0,0);
	m_fadingRectangle.setSize({1000.f,1000.f});
	m_fadingRectangle.setFillColor(sf::Color(0,0,0,255));
}

void VictoryState::update(const sf::Time& deltaTime)
{
	if(m_fadingRectangle.getFillColor().a != 0){
		sf::Color newAlpha = m_fadingRectangle.getFillColor();
		newAlpha.a -= 1;
		m_fadingRectangle.setFillColor(newAlpha);
	}

	m_elapsedTime += deltaTime;

	if (!m_buttonPressed)
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
	target->draw(m_fadingRectangle);
}

std::unique_ptr<State> VictoryState::handleInput(const GAME_STATE& gameState)
{
	if (gameState == GAME_STATE::MAIN_MENU)
	{
		SoundResource::getSound().StopBackground();
		SoundResource::getSound().playBackground(BACKGROUND_SOUND::Menu);
		return std::make_unique<MainMenu>(getWindow());
	}
	else if (gameState == GAME_STATE::EXIT)
	{
		getWindow()->close();
	}
	return nullptr;
}

void VictoryState::buttonPressed(sf::RenderWindow&, const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed || event.type == sf::Event::MouseButtonPressed)
	{
		m_buttonPressed = true;
	}
}