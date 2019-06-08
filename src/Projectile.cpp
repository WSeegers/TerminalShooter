#include "Projectile.hpp"

Projectile::Projectile(const Vec2 &position,
											 const Vec2 &velocity,
											 const Body &body)
		: Mob(position, velocity), Body(body), IKillable() {}
