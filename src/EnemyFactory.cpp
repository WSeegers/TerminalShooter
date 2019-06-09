#include "EnemyFactory.hpp"
#include "EntityManager.hpp"
#include "EnemyEntity.hpp"

EnemyFactory::EnemyFactory(EntityManager &em) : _em(em) {}
EnemyFactory::~EnemyFactory() {}

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
	if (self.getAge() % 345 == 222)
	{
		self.em.createEnemyShot(self.getPosition());
	}
}

EnemyEntity *EnemyFactory::createEnemy(EnemyFactory::EnemyTypes t, const Vec2 position)
{
	switch (t)
	{
	case BASIC:
		return (new EnemyEntity(this->_em, position, basic, &basicBehavior));
	case TRIDENT:
		return (new EnemyEntity(this->_em, position, trident, &tridentBehavior));
	}
}
