#include "EnemyEntity.hpp"

EnemyEntity::EnemyEntity(const Vec2 position, const Body &body)
		: Entity(position), Body(body) {}

EnemyEntity::EnemyEntity(const Body &body)
		: Entity(), Body(body) {}

void EnemyEntity::update()
{
	this->_position += _velocity;
}
