#include "EnemyFactory.hpp"

Body basic("*   * ***   *  ", 5, 3);
void basicBehavior(EnemyEntity &self)
{
	self.setVelocity(Vec2(0, 0.05));
	self.setPosition(self.getVelocity() + self.getPosition());
}

Body trident("  *   *** ^ ^ ^", 5, 3);

EnemyEntity *EnemyFactory::createEnemy(EnemyFactory::EnemyTypes t, const Vec2 position)
{
	switch (t)
	{
		case BASIC:
			return (new EnemyEntity(position, basic, &basicBehavior));
		case TRIDENT:
			return (new EnemyEntity(position, trident));
	}
}
