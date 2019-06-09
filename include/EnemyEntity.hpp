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

	void update();

private:
	EnemyEntity();
};

#endif
