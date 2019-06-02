#ifndef PLAYERENTITY_HPP
#define PLAYERENTITY_HPP

#include "Entity.hpp"
#include "Body.hpp"

class PlayerEntity : public Entity, public Body
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
