#include "EnemyFactory.hpp"

Body basic("*   * ***   *  ", 5, 3);
void basicBehavior(EnemyEntity &self)
{
	self.setVelocity(Vec2(0, 0.05));
	self.setPosition(self.getVelocity() + self.getPosition());
	if (self.getAge() > 300)
		self.kill();
}

Body trident("  *   *** ^ ^ ^", 5, 3);
void tridentBehavior(EnemyEntity &self)
{
	self.setVelocity(Vec2(0.05, 0));
	self.setPosition(self.getVelocity() + self.getPosition());
	if (self.getAge() > 1500)
		self.kill();
}

EnemyEntity *EnemyFactory::createEnemy(EnemyFactory::EnemyTypes t, const Vec2 position)
{
	switch (t)
	{
		case BASIC:
			return (new EnemyEntity(position, basic, &basicBehavior));
		case TRIDENT:
			return (new EnemyEntity(position, trident, &tridentBehavior));
	}
}
