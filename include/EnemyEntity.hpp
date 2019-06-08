#ifndef ENEMYENTITY_HPP
#define ENEMYENTITY_HPP

#include "Entity.hpp"
#include "Body.hpp"
#include "IKillable.hpp"

class EnemyEntity : public Entity, public Body, public IKillable
{
public:
	EnemyEntity(const Vec2 position, const Body &body);
	EnemyEntity(const Body &body);

	void moveUP();
	void moveDOWN();
	void moveLEFT();
	void moveRIGHT();

private:
	EnemyEntity();
};

#endif
