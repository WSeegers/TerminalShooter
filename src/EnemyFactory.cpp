#include <limits.h>

#include "EnemyFactory.hpp"
#include "EntityManager.hpp"
#include "EnemyEntity.hpp"
#include "GameEngine.hpp"

EnemyFactory::EnemyFactory(EntityManager &em) : _em(em) {}
EnemyFactory::~EnemyFactory() {}

Body basic("*   * ***   *  ", 5, 3);
void basicBehavior(EnemyEntity &self)
{
	self.setVelocity(Vec2(0, 0.05));
	self.setPosition(self.getVelocity() + self.getPosition());
	if (self.getPosition().y > GameEngine::FIELD_HEIGHT)
		self.kill();
	if (self.getAge() % 345 == 222)
	{
		self.em.createEnemyShot(self.getPosition() + Vec2(self.getWidth() / 2, 0));
	}
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
	dir.x = dir.x * 0.15;
	dir.y = dir.y * 0.15;

	dir.x += (rand() - INT_MAX / 2) / (double)INT_MAX * 0.2;
	dir.y += (rand() - INT_MAX / 2) / (double)INT_MAX * 0.2;

	self.setVelocity(dir);
	self.setPosition(self.getVelocity() + self.getPosition());
}

std::string bs1("        //-A-\\\\        ");
std::string bs2("  ___---=======---___  ");
std::string bs3("(=__\\   /.. ..\\   /__=)");
std::string bs4("     ---\\__O__/---     ");

std::string battleshipRaw(bs1 + bs2 + bs3 + bs4);
Body battleship(battleshipRaw, bs1.size(), 4);
void battleshipBehavior(EnemyEntity &self)
{
	Vec2 dest(GameEngine::FIELD_WIDTH / 2, 10);
	dest = dest - Vec2(self.getWidth() / 2, 0);
	Vec2 dir(0, 0);
	if (self.getPosition().y < dest.y)
	{
		dir = dest - self.getPosition();
		dir = dir.getNormalized();
		dir.x = dir.x * 0.06;
		dir.y = dir.y * 0.06;
	}
	self.setVelocity(dir);

	self.setPosition(self.getVelocity() + self.getPosition());

	if (self.getAge() % 150 == 0)
		self.em.createEnemy(EnemyFactory::MINE, self.getPosition() + Vec2(self.getWidth() / 2, 0));
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
	case BATTLESHIP:
		return (new EnemyEntity(this->_em, position, battleship, &battleshipBehavior));
	}
}
