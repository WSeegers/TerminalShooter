#ifndef ENTITYMANAGER_HPP
#define ENTITYMANAGER_HPP

#include <ncurses.h>

#include "Projectile.hpp"
#include "PlayerEntity.hpp"
#include "EnemyFactory.hpp"

class EntityManager
{
public:
	static const int PLAYER_PROJECTILE_MAX = 15;
	static const int ENEMY_PROJECTILE_MAX = 50;

	static const int ENEMY_POOL_MAX = 20;

	EntityManager(WINDOW* _gameField);
	~EntityManager();

	void update(int frameCount);

private:
	EntityManager();
	
	WINDOW *_gameField;
	void _drawBody(const Body &body);
	void _removeBody(const Body &body);

	PlayerEntity _player;
	void updatePlayer();
	void drawPlayer();

	Projectile *_playerProjectilesPool[EntityManager::PLAYER_PROJECTILE_MAX];
	void createPlayerShot();
	void updateProjectiles();
	void drawProjectiles();

	EnemyEntity *_enemyPool[EntityManager::ENEMY_POOL_MAX];
	void createEnemy(EnemyFactory::EnemyTypes t, const Vec2 position);
	void updateEnemies();
	void drawEnemies();

	Projectile *_enemyProjectilesPool[EntityManager::ENEMY_PROJECTILE_MAX];
	void createEnemyShot(EnemyEntity &enemy);
	void createEnemyShot(Vec2 &pos);
	void initEnemyProjectilePool(void);
	void updateEnemyProjectiles();
	void drawEnemyProjectiles();


	void checkCollisions();
};

#endif
