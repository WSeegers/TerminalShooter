#include "EnemyEntity.hpp"

EnemyEntity::EnemyEntity(const Vec2 position, const Body &body)
		: Entity(position), Body(body) {}

EnemyEntity::EnemyEntity(const Body &body)
		: Entity(), Body(body) {}

void EnemyEntity::moveUP()
{
	this->_position.y--;
}

void EnemyEntity::moveDOWN()
{
	this->_position.y++;
}

void EnemyEntity::moveLEFT()
{
	this->_position.x--;
}

void EnemyEntity::moveRIGHT()
{
	this->_position.x++;
}
