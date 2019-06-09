#include "StarEntity.hpp"

StarEntity::StarEntity(const Body &body, const Vec2 position, const Vec2 velocity)
	: Entity(position), Body(body), Mob(position, velocity) {}
