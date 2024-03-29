#include "EnemyEntity.hpp"
#include "EntityManager.hpp"

EnemyEntity::EnemyEntity(EntityManager &em, const Vec2 position, const Body &body)
	: Entity(position), Body(body), em(em), _age(0) {}

EnemyEntity::EnemyEntity(EntityManager &em, const Vec2 position, const Body &body, void (*update)(EnemyEntity &))
	: Entity(position), Body(body), em(em), _update(update), _age(0) {}

EnemyEntity::EnemyEntity(EnemyEntity &other)
	: Entity(other._position), Body(other), em(other.em), _update(other._update), _age(other._age) {}

EnemyEntity::~EnemyEntity() {}

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

EnemyEntity &EnemyEntity::operator=(EnemyEntity &rhs)
{
	this->_update = rhs._update;
	this->_age = rhs._age;

	return (*this);
}
