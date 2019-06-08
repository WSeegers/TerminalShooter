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

EntityManager::EntityManager() : _player(makeDefaultPlayer())
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
}

EntityManager::~EntityManager()
{
	int i;

	for (i = 0; i < EntityManager::PLAYER_PROJECTILE_MAX; i++)
	{
		delete this->_playerProjectilesPool[i];
	}
}

void EntityManager::update()
{
	this->updateProjectiles();
	this->updatePlayer();

	this->drawProjectiles();
	this->drawPlayer();
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

			this->_removeBody(projectile->getPosition().y,
							  projectile->getPosition().x,
							  *projectile);
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

			this->_drawBody(projectile->getPosition().y,
							projectile->getPosition().x,
							*projectile);
		}
	}
}

void EntityManager::updatePlayer()
{
	this->_removeBody(this->_player.getPosition().y,
					  this->_player.getPosition().x,
					  this->_player);
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
		if (coolShot < 1){
			this->_createPlayerShot();
			coolShot = 25;
		}
		
	}
	this->_player.update();
}

void EntityManager::drawPlayer()
{
	this->_drawBody(this->_player.getPosition().y,
					this->_player.getPosition().x,
					this->_player);
}

void EntityManager::_drawBody(int y, int x, const Body &body)
{
	int _cy = -1;
	int _cx;
	char bodyPart;

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
				mvaddch(
					_cy + y,
					_cx + x,
					bodyPart);
		}
	}
}

void EntityManager::_removeBody(int y, int x, const Body &body)
{
	int _cy = -1;
	int _cx;
	char bodyPart;

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
				mvaddch(
					_cy + y,
					_cx + x,
					' ');
		}
	}
}
