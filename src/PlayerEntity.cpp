#include "PlayerEntity.hpp"

PlayerEntity::PlayerEntity(const Vec2 position, const Body &body)
		: Entity(position), Body(body) {}

PlayerEntity::PlayerEntity(const Body &body)
		: Entity(), Body(body) {}

void PlayerEntity::moveUP()
{
	this->_position.y--;
}

void PlayerEntity::moveDOWN()
{
	this->_position.y++;
}

void PlayerEntity::moveLEFT()
{
	this->_position.x--;
}

void PlayerEntity::moveRIGHT()
{
	this->_position.x++;
}
