#ifndef MOB_HPP
#define MOB_HPP

#include "Entity.hpp"

class Mob : virtual public Entity
{
public:
	Mob();
	Mob(const Vec2 &position);
	Mob(const Vec2 &position, const Vec2 &velocity);
	Mob(const Mob &other);

	Mob &operator=(const Mob other);

	void setVelocity(const Vec2 &velocity);
	const Vec2 &getVelocity() const;
	virtual void update();

protected:
	Vec2 _velocity;
};

#endif
