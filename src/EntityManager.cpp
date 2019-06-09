#include "EntityManager.hpp"
#include "GameEngine.hpp"
#include "EnemyEntity.hpp"
#include <unistd.h>

static Vec2 makeRandomSpawn()
{
	double x = rand() / (double)INT_MAX * (GameEngine::FIELD_WIDTH - 2) + 1;
	return Vec2(x, -3);
}

static PlayerEntity makeDefaultPlayer()
{
	// std::string l0(" <x> ");
	// std::string l1("H=x=H");
	// std::string l2("# x #");

	std::string l0("  .  ");
	std::string l1(" .'. ");
	std::string l2(" |o| ");
	std::string l3(".'o'.");
	std::string l4("|.-.|");
	std::string l5("'   '");

	std::string rawBody = (l0 + l1 + l2 + l3 + l4 + l5);
	Body playerBody(rawBody, 5, 6);
	PlayerEntity player(Vec2(GameEngine::FIELD_HEIGHT - 10, GameEngine::FIELD_WIDTH / 2), playerBody);
	player.setWeaponOffset(Vec2((player.getWidth() / 2), 0));

	return player;
};

EntityManager::EntityManager(WINDOW *_gameField, Scoreboard &scoreboard) : _enemyFactory(*this),
																		   _gameField(_gameField),
																		   _scoreboard(scoreboard),
																		   _player(makeDefaultPlayer())
{
	for (int i = 0; i < EntityManager::PLAYER_PROJECTILE_MAX; i++)
	{
		this->_playerProjectilesPool[i] = new Projectile(
			Vec2(),
			Vec2(0, -0.7),
			Body(std::string("O"), 1, 1));
		this->_playerProjectilesPool[i]->kill();
	}

	bzero(this->_enemyPool, sizeof(this->_enemyPool));
	this->initEnemyProjectilePool();
	bzero(this->_starPool, sizeof(this->_starPool));
	this->_boss = this->_enemyFactory.createEnemy(EnemyFactory::BATTLESHIP, Vec2(-20, -300));
}

EntityManager::~EntityManager()
{
	int i;

	for (i = 0; i < EntityManager::PLAYER_PROJECTILE_MAX; i++)
	{
		delete this->_playerProjectilesPool[i];
	}
}

void EntityManager::update(int frameCount)
{
	this->_removeBody(*this->_boss);
	this->updateStars();
	this->updateEnemyProjectiles();
	this->updateProjectiles();
	this->updatePlayer();
	this->updateEnemies();
	this->_boss->update();

	this->checkCollisions();

	wattron(this->_gameField, COLOR_PAIR(1));
	this->drawStars();
	wattron(this->_gameField, COLOR_PAIR(5));
	this->drawEnemyProjectiles();
	this->drawProjectiles();
	wattron(this->_gameField, COLOR_PAIR(6));
	this->drawPlayer();
	wattron(this->_gameField, COLOR_PAIR(7));
	this->drawEnemies();
	this->_drawBody(*this->_boss);
	wattron(this->_gameField, COLOR_PAIR(1));

	box(this->_gameField, 0, 0);
	wrefresh(this->_gameField);

	// Testing enemy creation
	if (!(frameCount % 120))
		this->createEnemy(EnemyFactory::BASIC, makeRandomSpawn());

	// Testing star creation
	if (!(frameCount % 3))
		this->createStars();
}

void EntityManager::createPlayerShot()
{
	Projectile *projectile;

	for (int i = 0; i < EntityManager::PLAYER_PROJECTILE_MAX; i++)
	{
		projectile = _playerProjectilesPool[i];
		if (!projectile->isAlive())
		{
			projectile->revive();
			projectile->setPosition(this->_player.getWeaponPosition());
			break;
		}
	}
}

void EntityManager::updateProjectiles()
{
	int i;
	Projectile *projectile;

	for (i = 0; i < EntityManager::PLAYER_PROJECTILE_MAX; i++)
	{
		projectile = _playerProjectilesPool[i];
		if (projectile->isAlive())
		{

			this->_removeBody(*projectile);
			projectile->update();
			if (projectile->getPosition().y <= 1)
				projectile->kill();
		}
	}
}

void EntityManager::drawProjectiles()
{
	int i;
	Projectile *projectile;

	for (i = 0; i < EntityManager::PLAYER_PROJECTILE_MAX; i++)
	{
		projectile = _playerProjectilesPool[i];
		if (projectile->isAlive())
		{

			this->_drawBody(*projectile);
		}
	}
}

void EntityManager::_playShotSound()
{
	this->_soundPid = fork();

	if (!this->_soundPid)
	{
		execlp("afplay", "afplay", FSOUND, NULL);
		exit(0);
	}
}

void EntityManager::updatePlayer()
{
	this->_removeBody(this->_player);
	static int coolShot;
	coolShot--;
	int y = this->_player.getPosition().y;
	int x = this->_player.getPosition().x;

	switch (getch())
	{
	case 'w':
		if (y > 1)
			this->_player.moveUP();
		break;
	case 'a':
		if (x > 1)
			this->_player.moveLEFT();
		break;
	case 's':
		this->_player.moveDOWN();
		break;
	case 'd':
		this->_player.moveRIGHT();
		break;
	case ' ':
		if (coolShot < 1)
		{
			this->createPlayerShot();
			this->_playShotSound();
			coolShot = 16;
		}
	}
	this->_player.update();
}

void EntityManager::drawPlayer()
{
	this->_drawBody(this->_player);
}

void EntityManager::_drawBody(const Body &body)
{
	int _cy = -1;
	int _cx;
	char bodyPart;

	int x = body.getPosition().x;
	int y = body.getPosition().y;
	int width = body.getWidth();
	int height = body.getHeight();
	const std::string &_body = body.getBody();

	while (++_cy < height)
	{
		_cx = -1;
		while (++_cx < width)
		{
			bodyPart = _body[_cx + _cy * width];
			if (bodyPart != ' ')
				mvwaddch(
					this->_gameField,
					_cy + y,
					_cx + x,
					bodyPart);
		}
	}
}

void EntityManager::_removeBody(const Body &body)
{
	int _cy = -1;
	int _cx;
	char bodyPart;

	int x = body.getPosition().x;
	int y = body.getPosition().y;
	int width = body.getWidth();
	int height = body.getHeight();
	const std::string &_body = body.getBody();

	while (++_cy < height)
	{
		_cx = -1;
		while (++_cx < width)
		{
			bodyPart = _body[_cx + _cy * width];
			if (bodyPart != ' ')
				mvwaddch(
					this->_gameField,
					_cy + y,
					_cx + x,
					' ');
		}
	}
}

void EntityManager::createEnemy(EnemyFactory::EnemyTypes type, const Vec2 position)
{
	for (int i = 0; i < EntityManager::ENEMY_POOL_MAX; i++)
	{
		if (!_enemyPool[i])
		{
			_enemyPool[i] = this->_enemyFactory.createEnemy(type, position);
			return;
		}
	}
}

void EntityManager::createStars()
{
	Vec2 position;
	Vec2 velocity;
	for (int i = 0; i < EntityManager::STAR_POOL_MAX; i++)
	{
		Body star(".", 1, 1);
		position = Vec2(rand() % (getmaxx(this->_gameField) + 1) + 2, 0);
		velocity = Vec2(0, ((rand() % 70 + 1) / 100.0f) + 0.2);
		if (velocity.y > 0.5)
			star.setBody("*", 1, 1);
		if (!_starPool[i])
		{
			_starPool[i] = new StarEntity(star, position, velocity);
			return;
		}
	}
}

void EntityManager::updateEnemies()
{
	EnemyEntity *enemy;
	Vec2 position;

	for (int i = 0; i < EntityManager::ENEMY_POOL_MAX; i++)
	{
		if (this->_enemyPool[i])
		{
			enemy = this->_enemyPool[i];
			position = enemy->getPosition();

			this->_removeBody(*enemy);
			if (!enemy->isAlive())
			{
				delete enemy;
				this->_enemyPool[i] = nullptr;
			}
			else
			{
				this->_enemyPool[i]->update();
			}
		}
	}
}

void EntityManager::drawEnemies()
{
	EnemyEntity *enemy;
	Vec2 position;

	for (int i = 0; i < EntityManager::ENEMY_POOL_MAX; i++)
	{
		if (this->_enemyPool[i])
		{
			enemy = this->_enemyPool[i];
			position = enemy->getPosition();
			this->_drawBody(*enemy);
		}
	}
}

void EntityManager::updateStars()
{
	StarEntity *star;
	Vec2 position;

	for (int i = 0; i < EntityManager::STAR_POOL_MAX; i++)
	{
		if (this->_starPool[i])
		{
			star = this->_starPool[i];
			position = star->getPosition();

			this->_removeBody(*star);
			if (position.y >= getmaxy(this->_gameField))
			{
				delete star;
				this->_starPool[i] = nullptr;
			}
			else
			{
				this->_starPool[i]->update();
			}
		}
	}
}

void EntityManager::drawStars()
{
	StarEntity *star;
	Vec2 position;

	for (int i = 0; i < EntityManager::STAR_POOL_MAX; i++)
	{
		if (this->_starPool[i])
		{
			star = this->_starPool[i];
			position = star->getPosition();
			this->_drawBody(*star);
		}
	}
}

void EntityManager::checkCollisions()
{
	static int bossLives = EntityManager::BOSS_LIVES;
	mvprintw(GameEngine::FIELD_HEIGHT + 1, 0, "%.2d", bossLives);

	// Check player bullet collision with enemies
	for (int i = 0; i < EntityManager::PLAYER_PROJECTILE_MAX; i++)
	{
		if (this->_playerProjectilesPool[i]->isAlive())
		{
			if (this->_boss->isColliding(*this->_playerProjectilesPool[i]))
			{
				bossLives--;
				if (bossLives < 0)
				{
					endwin();
					exit(0);
				} // We need to win
				this->_playerProjectilesPool[i]->kill();
			}

			for (int j = 0; j < EntityManager::ENEMY_POOL_MAX; j++)
			{
				if (this->_enemyPool[j])
				{
					if (this->_playerProjectilesPool[i]->isColliding(*(this->_enemyPool[j])))
					{
						this->_enemyPool[j]->kill();
						this->_playerProjectilesPool[i]->kill();
						this->_scoreboard.incScore(1);
						break;
					}
				}
			}
		}
	}

	// Check player collision with enemies
	for (int i = 0; i < EntityManager::ENEMY_POOL_MAX; i++)
	{
		if (this->_enemyPool[i])
		{
			if (this->_player.isColliding(*(this->_enemyPool[i])))
			{
				// Game Over situation here
				this->_player.setPosition(Vec2(GameEngine::FIELD_HEIGHT - 10, GameEngine::FIELD_WIDTH / 2));
				this->_enemyPool[i]->kill();

				this->_scoreboard.decLives(1);
			}
		}
	}

	// Check player collision with enemies projectiles
	for (int i = 0; i < EntityManager::ENEMY_PROJECTILE_MAX; i++)
	{
		if (_enemyProjectilesPool[i]->isAlive())
		{
			if (this->_player.isColliding(*this->_enemyProjectilesPool[i]))
			{
				// Game Over situation here
				this->_player.setPosition(Vec2(GameEngine::FIELD_HEIGHT - 10, GameEngine::FIELD_WIDTH / 2));
				this->_enemyProjectilesPool[i]->kill();

				this->_scoreboard.decLives(1);
			}
		}
	}

	// Boos collisions
}

const Vec2 &EntityManager::getPlayerPosition() const
{
	return this->_player.getPosition();
};