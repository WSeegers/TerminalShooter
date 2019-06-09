#include "EntityManager.hpp"
#include "GameEngine.hpp"
#include "PlayerEntity.hpp"
#include "Body.hpp"

static PlayerEntity makeDefaultPlayer()
{
	std::string l0(" <x> ");
	std::string l1("H=x=H");
	std::string l2("# x #");

	std::string rawBody = (l0 + l1 + l2);
	Body playerBody(rawBody, 5, 3);
	PlayerEntity player(Vec2(4, 25), playerBody);
	player.setWeaponOffset(Vec2((player.getWidth() / 2), (player.getHeight() / 2)));

	return player;
};

EntityManager::EntityManager(WINDOW *_gameField) : _gameField(_gameField), _player(makeDefaultPlayer())
{
	int i;

	for (i = 0; i < EntityManager::PLAYER_PROJECTILE_MAX; i++)
	{
		this->_playerProjectilesPool[i] = new Projectile(
			Vec2(),
			Vec2(0, -0.7),
			Body(std::string("O"), 1, 1));
		this->_playerProjectilesPool[i]->kill();
	}

	bzero(this->_enemyPool, sizeof(this->_enemyPool));
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
	this->updateProjectiles();
	this->updatePlayer();
	this->updateEnemies();

	this->checkCollisions();

	this->drawProjectiles();
	this->drawPlayer();
	this->drawEnemies();

	wrefresh(this->_gameField);
	
	// Testing enemy creation
	if (!(frameCount % 100))
		this->createEnemy(EnemyFactory::TRIDENT, Vec2(1, 10));
}

void EntityManager::_createPlayerShot()
{
	int i;
	Projectile *projectile;

	for (i = 0; i < EntityManager::PLAYER_PROJECTILE_MAX; i++)
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
		if (y + this->_player.getHeight() < GameEngine::FIELD_HEIGHT)
			this->_player.moveDOWN();
		break;
	case 'd':
		if (x + this->_player.getWidth() < GameEngine::FIELD_WIDTH)
			this->_player.moveRIGHT();
		break;
	case ' ':
		if (coolShot < 1)
		{
			this->_createPlayerShot();
			coolShot = 25;
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
			_enemyPool[i] = EnemyFactory::createEnemy(type, position);
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

void EntityManager::checkCollisions()
{
	// Check player bullet collision with enemies
	for (int i = 0; i < EntityManager::PLAYER_PROJECTILE_MAX; i++)
	{
		if (this->_playerProjectilesPool[i]->isAlive())
		{
			for (int j = 0; j < EntityManager::ENEMY_POOL_MAX; j++)
			{
				if (this->_enemyPool[j])
				{
					if (this->_playerProjectilesPool[i]->isColliding(*(this->_enemyPool[j])))
					{
						this->_enemyPool[j]->kill();
						this->_playerProjectilesPool[i]->kill();
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
				this->_player.setPosition(20, 20);
				this->_enemyPool[i]->kill();
			}
		}
	}
}
