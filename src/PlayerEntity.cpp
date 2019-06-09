#include "PlayerEntity.hpp"
#include "GameEngine.hpp"

const float PlayerEntity::DECELERATION = 0.005;

PlayerEntity::PlayerEntity(const Vec2 position, const Body &body)
	: Entity(position), Body(body) {}

PlayerEntity::PlayerEntity(const Body &body)
	: Entity(), Body(body) {}

void PlayerEntity::moveUP()
{
	this->_velocity.y = -0.25;
}

void PlayerEntity::moveDOWN()
{
	this->_velocity.y = 0.25;
}

void PlayerEntity::moveLEFT()
{
	this->_velocity.x = -0.5;
}

void PlayerEntity::moveRIGHT()
{
	this->_velocity.x = 0.5;
}

void PlayerEntity::setWeaponOffset(const Vec2 offset)
{
	this->_weaponOffset = offset;
}

Vec2 PlayerEntity::getWeaponPosition()
{
	Vec2 weaponPosition = this->getPosition();
	weaponPosition += this->_weaponOffset;

	return weaponPosition;
}

void PlayerEntity::update()
{

	//Friction

	if (std::abs(this->_velocity.x) < 0.01)
		this->_velocity.x = 0;
	else if (this->_velocity.x > 0)
		_velocity.x -= PlayerEntity::DECELERATION;
	else if (this->_velocity.x < 0)
		_velocity.x += PlayerEntity::DECELERATION;
	if (std::abs(this->_velocity.y) < 0.01)
		this->_velocity.y = 0;
	else if (this->_velocity.y > 0)
		_velocity.y -= PlayerEntity::DECELERATION;
	else if (this->_velocity.y < 0)
		_velocity.y += PlayerEntity::DECELERATION;

	this->_position += _velocity;

	// Border
	if (this->_position.x <= 1)
	{
		this->_position.x = 1;
		this->_velocity.x = 0;
	}
	else if (this->_position.x + this->getWidth() >= GameEngine::FIELD_WIDTH - 1)
	{
		this->_position.x = GameEngine::FIELD_WIDTH - this->getWidth() - 1;
		this->_velocity.x = 0;
	}
	if (this->_position.y <= 1)
	{
		this->_position.y = 1;
		this->_velocity.y = 0;
	}
	else if (this->_position.y + this->getHeight() >= GameEngine::FIELD_HEIGHT - 1)
	{
		this->_position.y = GameEngine::FIELD_HEIGHT - this->getHeight() - 1;
		this->_velocity.y = 0;
	}
}
