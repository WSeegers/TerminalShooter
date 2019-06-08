#include "Mob.hpp"

Mob::Mob(){};
Mob::Mob(const Vec2 &position) : Entity(position) {}
Mob::Mob(const Vec2 &position, const Vec2 &velocity)
		: Entity(position), _velocity(velocity) {}
Mob::Mob(const Mob &other)
		: Entity(other._position), _velocity(other._velocity) {}

Mob &Mob::operator=(const Mob other)
{
	if (this != &other)
	{
		this->_position = _position;
		this->_velocity = _velocity;
	}
	return *this;
}

void Mob::setVelocity(const Vec2 &velocity)
{
	this->_velocity = velocity;
}

const Vec2 &Mob::getVelocity() const
{
	return this->_velocity;
}

void Mob::update()
{
	this->_position += _velocity;
}
