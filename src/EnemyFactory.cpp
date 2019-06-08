#include "EnemyFactory.hpp"

Body basic("*   * ***   *  ", 5, 3);
Body trident("  *   *** ^ ^ ^", 5, 3);

EnemyEntity *EnemyFactory::createEnemy(EnemyFactory::EnemyTypes t, const Vec2 position)
{
	switch (t)
	{
		case BASIC:
			return (new EnemyEntity(position, basic));
		case TRIDENT:
			return (new EnemyEntity(position, trident));
	}
}
