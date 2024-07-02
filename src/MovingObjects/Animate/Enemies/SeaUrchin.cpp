#include "SeaUrchin.h"

bool SeaUrchin::m_registerit = Factory<Enemy>::instance()->registerit("SeaUrchin",
	[](const sf::Vector2f& position) -> std::unique_ptr<Enemy>
	{
		return std::make_unique<SeaUrchin>(*Resources::getResource().getTexture(TEXTURE::Enemies), position);
	});

SeaUrchin::SeaUrchin(const sf::Texture& texture, const sf::Vector2f& position)
	: Enemy(texture, position, sf::Vector2f(12.f * 0.8f, 12.f * 0.8f), sf::Vector2f(-2, -2))
{
	setGraphics(ANIMATIONS_POSITIONS::SeaUrchin, 2);
	updateSprite();
	setHp(1);
}

sf::Vector2f SeaUrchin::getLinkPos()
{
	return sf::Vector2f();
}

std::unique_ptr<Inanimate> SeaUrchin::getAttack()
{
	return nullptr;
}

void SeaUrchin::update(const sf::Time& deltaTime)
{
	updateGraphics(deltaTime);
	updateSprite();


	if (getHp() <= MIN_HEALTH)
	{
		destroy();
		SoundResource::getSound().playSound(SOUNDS::EnemyDie);
	}
}

const sf::Vector2u SeaUrchin::getAnimationTexturePosition(Input)
{
	return sf::Vector2u(0,0);
}

EnemyType SeaUrchin::getType() const
{
	return SEA_URCHIN;
}
