#include "EnemyFactory.hpp"

Body basic("  *   *** * * ** * *", 5, 4);

EnemyEntity *EnemyFactory::createEnemy(EnemyFactory::EnemyTypes t, const Vec2 position)
{
	switch (t)
	{
		case BASIC:
			return (new EnemyEntity(position, basic));
	}
}
