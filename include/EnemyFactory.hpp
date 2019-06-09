#ifndef ENEMYFACTORY_HPP
#define ENEMYFACTORY_HPP

#include "Vec2.hpp"
#include "Body.hpp"

class EntityManager;
class EnemyEntity;

class EnemyFactory
{
public:
	EnemyFactory(EntityManager &em);
	~EnemyFactory();

	enum EnemyTypes
	{
		BASIC,
		TRIDENT,
		MINE
	};

	EnemyEntity *createEnemy(EnemyFactory::EnemyTypes type, const Vec2 position);

private:
	EntityManager &_em;
};

#endif
