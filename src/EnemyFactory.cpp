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
	if (self.getAge() > 3000)
		self.kill();
	if (self.getAge() % 345 == 222)
	{
		self.em.createEnemyShot(self.getPosition());
	}
}

Body mine(" * *H* * ", 3, 3);
void mineBehavior(EnemyEntity &self)
{
	Vec2 dir = self.em.getPlayerPosition() - self.getPosition();
	dir = dir.getNormalized();
	dir.x = dir.x * 0.1;
	dir.y = dir.y * 0.1;

	self.setVelocity(dir);
	self.setPosition(self.getVelocity() + self.getPosition());
}

EnemyEntity *EnemyFactory::createEnemy(EnemyFactory::EnemyTypes t, const Vec2 position)
{
	switch (t)
	{
	case BASIC:
		return (new EnemyEntity(this->_em, position, basic, &basicBehavior));
	case TRIDENT:
		return (new EnemyEntity(this->_em, position, trident, &tridentBehavior));
	case MINE:
		return (new EnemyEntity(this->_em, position, mine, &mineBehavior));
	}
}
