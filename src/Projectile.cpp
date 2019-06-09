#include "Projectile.hpp"

Projectile::Projectile(const Vec2 &position,
											 const Vec2 &velocity,
											 const Body &body)
		: Mob(position, velocity), Body(body), IKillable() {}

Projectile::Projectile(Projectile &other) : Mob(other._position, other._velocity), Body(other), IKillable() {}

Projectile::~Projectile() {}

Projectile &Projectile::operator=(Projectile &rhs)
{
	this->_velocity = rhs._velocity;
	this->_position = rhs._position;
	return (*this);
}
