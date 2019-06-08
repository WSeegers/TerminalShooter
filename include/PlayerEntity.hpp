#ifndef PLAYERENTITY_HPP
#define PLAYERENTITY_HPP

#include "Body.hpp"
#include "IKillable.hpp"

class PlayerEntity : public Body, public IKillable
{
public:
	PlayerEntity(const Vec2 position, const Body &body);
	PlayerEntity(const Body &body);

	void moveUP();
	void moveDOWN();
	void moveLEFT();
	void moveRIGHT();

private:
	PlayerEntity();
};

#endif
