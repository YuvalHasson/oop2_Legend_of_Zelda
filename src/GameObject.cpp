#include "GameObject.h"

GameObject::GameObject(b2World& world, const sf::Texture& texture, const sf::Vector2f& position)
    : m_position(position)
{
    // Define the dynamic body. We set its position and call the body
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(0.f, 0.f);
    m_body = world.CreateBody(&bodyDef);

    // Define another box shape for our dynamic body
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1.0f, 1.0f);

    // Define the dynamic body fixture
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;

    // Set the box density to be non-zero, so it will be dynamic
    fixtureDef.density = 1.0f;

    // Override the default friction
    fixtureDef.friction = 0.3f;

    // Add the shape to the body
    m_body->CreateFixture(&fixtureDef);

    m_sprite.setTexture(texture);
    m_sprite.setPosition(position);

	m_sprite.setScale(0.5f / tileSize, 1.0f / tileSize); //tmp i think
	m_sprite.setOrigin(tileSize / 2, tileSize / 2); //tmp i think
}

GameObject::~GameObject(){};

void GameObject::draw(sf::RenderWindow& window)
{
    window.draw(m_sprite);
}

bool GameObject::checkCollision(const GameObject& other) const
{
    return m_sprite.getGlobalBounds().intersects(other.m_sprite.getGlobalBounds());
}

void GameObject::update()
{
    b2Vec2 position = m_body->GetPosition();
    float angle = m_body->GetAngle();

    m_sprite.setPosition(position.x * 50.0f, position.y * 50.0f);
    m_sprite.setRotation(angle * 180.0f / b2_pi);//mabye cause him to spin?
}

