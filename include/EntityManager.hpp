#ifndef ENTITYMANAGER_HPP
#define ENTITYMANAGER_HPP

#include <ncurses.h>

#include "Projectile.hpp"
#include "PlayerEntity.hpp"
#include "EnemyFactory.hpp"
#include "StarEntity.hpp"
#include "Scoreboard.hpp"

class GameEngine;
class EnemyEntity;

class EntityManager
{
public:
	static const int PLAYER_PROJECTILE_MAX = 15;
	static const int ENEMY_PROJECTILE_MAX = 50;

	static const int ENEMY_POOL_MAX = 20;
	static const int STAR_POOL_MAX = 100;

	static const int BOSS_LIVES = 20;

	EntityManager(WINDOW* _gameField, Scoreboard &scoreboard);
	~EntityManager();

	void update(int frameCount);
	void createEnemyShot(EnemyEntity &enemy);
	void createEnemyShot(const Vec2 &pos);
	const Vec2 &getPlayerPosition() const;
	void createEnemy(EnemyFactory::EnemyTypes t, const Vec2 position);

private:
	EntityManager();
	EnemyFactory _enemyFactory;
	EnemyEntity *_boss;

	WINDOW *_gameField;
	void _drawBody(const Body &body);
	void _removeBody(const Body &body);

	Scoreboard &_scoreboard;

	PlayerEntity _player;
	void updatePlayer();
	void drawPlayer();

	Projectile *_playerProjectilesPool[EntityManager::PLAYER_PROJECTILE_MAX];
	void createPlayerShot();
	void updateProjectiles();
	void drawProjectiles();
	void _playShotSound();
	pid_t _soundPid;

	EnemyEntity *_enemyPool[EntityManager::ENEMY_POOL_MAX];
	void updateEnemies();
	void drawEnemies();

	Projectile *_enemyProjectilesPool[EntityManager::ENEMY_PROJECTILE_MAX];
	void initEnemyProjectilePool(void);
	void updateEnemyProjectiles();
	void drawEnemyProjectiles();

	StarEntity *_starPool[EntityManager::STAR_POOL_MAX];
	void createStars();
	void updateStars();
	void drawStars();

	void checkCollisions();
};

#endif
