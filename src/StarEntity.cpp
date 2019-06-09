#include "StarEntity.hpp"

Body star(".", 1, 1);

StarEntity::StarEntity(const Vec2 position, const Vec2 velocity) : Entity(position), Body(star), Mob(position, velocity) {}
