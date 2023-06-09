#include "../include/Entities/Entity.h"

using namespace Entities;

Entity::Entity(const sf::Vector2f pos, const sf::Vector2f size, ID id) : 
	Being(id),
	Position(pos.x, pos.y),
	grounded(false),
	Velocity(sf::Vector2f(0, 0)),
	Size(size)
{
}
Entity::~Entity()
{
}

void Entity::Gravity()
{
	float mult = 60;
	Velocity.y += gravity * dt * mult;
}

void Entity::setGrounded(bool b) { grounded = b; }

void Entity::setPosition(sf::Vector2f pos)
{
	Position = pos;
}

void Entity::setPosition(float x, float y)
{
	Position.x = x;
	Position.y = y;
}

void Entity::setVelocity(sf::Vector2f vel)
{
	Velocity = vel;
}

void Entity::setVelocity(float x, float y)
{
	Velocity.x = x;
	Velocity.y = y;
}

sf::Vector2f Entity::getVelocity() const
{
	return Velocity;
}

sf::Vector2f Entity::getPosition() const
{
	return Position;
}

sf::Vector2f Entity::getSize() const
{
	return Size;
}

void Entity::updateDeltaTime(float dt)
{
	Entity::dt = dt; 
}

float Entities::Entity::getDt()
{
    return dt;
}

const bool Entity::getGrounded() const { return grounded; }

float Entity::dt(0);
const float Entity::gravity(0.78f); // 8.166 valor de teste

