#ifndef ENEMYENTITY_HPP
#define ENEMYENTITY_HPP

class EntityManager;

#include "Body.hpp"
#include "Mob.hpp"
#include "IKillable.hpp"

class EntityManager;

class EnemyEntity : public Body, public IKillable, public Mob
{
public:
	EnemyEntity(EntityManager &em, const Vec2 position, const Body &body);
	EnemyEntity(EntityManager &em, const Vec2 position, const Body &body, void (*update)(EnemyEntity &));
	EnemyEntity(EnemyEntity &other);

	void update();

	EntityManager &em;

	uint32_t getAge();
	void setAge(uint32_t age);

	EnemyEntity operator=(EnemyEntity &rhs);

private:
	EnemyEntity();

	void (*_update)(EnemyEntity &self);
	uint32_t _age;
};

#endif
