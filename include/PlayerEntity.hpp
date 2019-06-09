#ifndef PLAYERENTITY_HPP
#define PLAYERENTITY_HPP

#include <math.h>

#include "Body.hpp"
#include "IKillable.hpp"
#include "Mob.hpp"

class PlayerEntity : public Body, public IKillable, public Mob
{
public:
	static const double DECELERATION;
	PlayerEntity(const Vec2 position, const Body &body);
	PlayerEntity(const Body &body);
	PlayerEntity(const PlayerEntity &other);
	~PlayerEntity();

	void moveUP();
	void moveDOWN();
	void moveLEFT();
	void moveRIGHT();

	void setWeaponOffset(const Vec2 offset);
	Vec2 getWeaponPosition();
	void update();

private:
	Vec2 _weaponOffset;
	PlayerEntity();
};

#endif
