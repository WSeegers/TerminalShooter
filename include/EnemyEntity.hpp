#ifndef ENEMYENTITY_HPP
#define ENEMYENTITY_HPP

#include "Body.hpp"
#include "Mob.hpp"
#include "IKillable.hpp"

class EnemyEntity : public Body, public IKillable, public Mob
{
public:
	EnemyEntity(const Vec2 position, const Body &body);
	EnemyEntity(const Body &body);
	EnemyEntity(const Vec2 position, const Body &body, void (*update)(EnemyEntity &));

	void update();

	uint32_t getAge();
	void setAge(uint32_t age);

private:
	EnemyEntity();
	void (*_update)(EnemyEntity &self);
	uint32_t _age;
};

#endif
