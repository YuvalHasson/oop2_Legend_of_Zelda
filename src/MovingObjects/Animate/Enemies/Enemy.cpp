#include "Enemy.h"
#include "Board.h"

Enemy::Enemy(const sf::Texture& texture, const sf::Vector2f& position, const sf::Vector2f& size, const sf::Vector2f& originOffset)
	: Animate(texture, position, size, originOffset), m_isHit(false)
{
	addHitColor(sf::Color(255,93,0));
	m_hitTimer.restart();
}

void Enemy::update(const sf::Time& ){
	if(m_hitTimer.getElapsedTime() >= EnemyHitAnimationTime){
		m_isHit = false;
	}
}

void Enemy::updateHitAnimation(const sf::Time& deltaTime){

	if(m_isHit){
		Animate::updateHitAnimation(deltaTime);
		getSprite().setColor(getCurrentColor());
	}
	else{
		getSprite().setColor(getBaseColor());
	}
}

//raycasting
bool Enemy::castRay(const sf::Vector2f& enemyPos ,const sf::Vector2f& linkPos)const{
	//find direction vector
	sf::Vector2f direction = linkPos - enemyPos;

	//normalize the direction
	float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
	sf::Vector2f unitDirection = direction/length;

	//how many pixels we move each iteration of progressing the ray
	//lower number = better accuracy worse performance
	float stepSize = 8.f; 
	sf::Vector2f currentPos = enemyPos;

	while (std::sqrt((currentPos.x - enemyPos.x) * (currentPos.x - enemyPos.x) + (currentPos.y - enemyPos.y) * (currentPos.y - enemyPos.y)) < length) {
        if (isHittingObjects(currentPos)) {
            return false; 
        }
        currentPos += unitDirection * stepSize;
    }
	return true;
}

bool Enemy::isHittingObjects(const sf::Vector2f& position)const{
	for(const auto& object : Board::getStaticRects()){
		if(object.contains(position)){
			return true;
		}
	}
	return false;
}

void Enemy::hit(){
	if(!m_isHit){
		m_isHit = true;
		m_hitTimer.restart();
	}
}