#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include "Mob.hpp"
#include "Body.hpp"
#include "IKillable.hpp"

class Projectile : public Mob, public Body, public IKillable
{
public:
	Projectile(const Vec2 &position,
						 const Vec2 &velocity,
						 const Body &body);

private:
	Projectile();
};

#endif
