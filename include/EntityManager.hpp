#ifndef ENTITYMANAGER_HPP
#define ENTITYMANAGER_HPP

#include "ncurses.h"

#include "Projectile.hpp"
#include "PlayerEntity.hpp"
#include "EnemyFactory.hpp"

class EntityManager
{
public:
	static const int PLAYER_PROJECTILE_MAX = 15;
	static const int ENEMY_PROJECTILE_MAX = 15;

	static const int ENEMY_POOL_MAX = 20;

	EntityManager();
	~EntityManager();

	void update();

private:
	void _drawBody(int y, int x, const Body &body);
	void _removeBody(int y, int x, const Body &body);

	PlayerEntity _player;
	void updatePlayer();
	void drawPlayer();
	void _createPlayerShot();

	Projectile *_playerProjectilesPool[EntityManager::PLAYER_PROJECTILE_MAX];
	void updateProjectiles();
	void drawProjectiles();

	EnemyEntity *_enemyPool[EntityManager::ENEMY_POOL_MAX];
	void createEnemy(EnemyFactory::EnemyTypes t, const Vec2 position);
};

#endif
