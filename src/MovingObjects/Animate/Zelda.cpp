#include "Zelda.h"

bool Zelda::m_registerit = Factory<Zelda>::instance()->registerit("Zelda",
	[](const sf::Vector2f& position) -> std::unique_ptr<Zelda>
	{
		return std::make_unique<Zelda>(*Resources::getResource().getTexture(TEXTURE::Zelda), position);
	});

Zelda::Zelda(const sf::Texture& texture, const sf::Vector2f& position)
	:Enemy(texture, position, sf::Vector2f(tileSize * 1.1f, tileSize * 1.1f), sf::Vector2f(tileSize, tileSize)),
	m_hitBox(position, sf::Vector2f(tileSize * 0.8f, tileSize * 0.8f), sf::Vector2f(tileSize - 3.f, tileSize - 3.f)), m_active(false),
	m_currInput(PRESS_RIGHT), 
	m_moveStrategy(nullptr)
{
	m_text.setFont(*Resources::getResource().getFont());
	m_text.scale(0.9f, 0.9f);
	m_text.setLineSpacing(1.6f);
	m_text.setLetterSpacing(2.f);
	m_text.setFillColor(sf::Color::White);
	m_text.setString("Go  kill  the  wizard");

	setSpeed(0.5f);
	getSprite().setOrigin(tileSize, tileSize);
	setGraphics(ANIMATIONS_POSITIONS::Zelda, 2);
	updateSprite();

	auto posmove = std::make_unique<PositionMovement>();
	posmove->setDestination(sf::Vector2f(120, 75));
	setMoveStrategy(std::move(posmove));
	
}

std::unique_ptr<Inanimate> Zelda::getAttack()
{
	return nullptr;
}

void Zelda::update(const sf::Time& deltaTime)
{
	//5x5 pixels threshold from the desired position
	if ((getPosition().x < 125 && getPosition().x > 115) && (getPosition().y < 80 && getPosition().y > 70)) {
		setMoveStrategy(std::make_unique<Standing>());
		return;
	}
	m_hitBox.setPosition(getSprite().getPosition());
	updateGraphics(deltaTime);
	updateSprite();
	PerformMove();
}

void Zelda::setMoveStrategy(std::unique_ptr<MovementStrategy> move)
{
	m_moveStrategy = std::move(move);
}

void Zelda::PerformMove()
{
	m_moveStrategy->move(m_currInput, *this, &m_directionChangeClock);

}

void Zelda::setActive(bool active)
{
	m_active = active;
}

void Zelda::draw(sf::RenderTarget& target)
{
	GameObject::draw(target);

	auto curr = target.getView();
	target.setView(target.getDefaultView());


	if (m_active)
	{
		sf::RectangleShape rect(sf::Vector2f(WindowWidth * 1.3f, tileSize * 6.f));
		rect.setPosition(0, windowHeight / 1.57f);
		rect.setOrigin(tileSize / 2.f, tileSize / 2.f);
		rect.setFillColor(sf::Color(0, 0, 0, 200));
		target.draw(rect);

		m_text.setPosition(20.f, rect.getPosition().y - 5.f);
		target.draw(m_text);
		
	}
	m_active = false;
	target.setView(curr);
}

bool Zelda::checkInnerCollision(const HitBox& box) const
{
	return m_hitBox.checkCollision(box);
}
