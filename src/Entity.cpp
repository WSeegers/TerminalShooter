#include "Entity.hpp"

Entity::Entity() : _position(Vec2(0, 0)) {}
Entity::Entity(const Vec2 &position) : _position(position) {}
Entity::Entity(double x, double y) : _position(Vec2(x, y)) {}
Entity::Entity(const Entity &other) : _position(other._position) {}

Entity &Entity::operator=(const Entity other)
{
	if (this != &other)
	{
		this->_position = other._position;
	}
	return *this;
}

void Entity::setPosition(const Vec2 &position)
{
	this->_position = position;
}

void Entity::setPosition(double x, double y)
{
	this->_position.x = x;
	this->_position.y = y;
}

const Vec2 &Entity::getPosition() const
{
	return this->_position;
}
