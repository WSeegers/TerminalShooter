#include "EnemyFactory.hpp"

Body basic("*", 1, 1);

EnemyEntity *EnemyFactory::createEnemy(EnemyFactory::EnemyTypes t, const Vec2 position)
{
	switch (t)
	{
		case BASIC:
			return (new EnemyEntity(position, basic));
	}
}
