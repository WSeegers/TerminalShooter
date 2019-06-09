#include "EnemyEntity.hpp"

EnemyEntity::EnemyEntity(const Vec2 position, const Body &body)
		: Entity(position), Body(body), _age(0) {}

EnemyEntity::EnemyEntity(const Body &body)
		: Entity(), Body(body), _age(0) {}

EnemyEntity::EnemyEntity(const Vec2 position, const Body &body, void (*update)(EnemyEntity &))
		: Entity(position), Body(body), _update(update), _age(0) {}

void EnemyEntity::update()
{
	this->_age++;

	if (this->_update)
	{
		this->_update(*this);
	}
}

uint32_t EnemyEntity::getAge()
{
	return (this->_age);
}

void EnemyEntity::setAge(uint32_t age)
{
	this->_age = age;
}
