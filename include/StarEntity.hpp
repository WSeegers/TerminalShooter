#ifndef STARENTITY_HPP
#define STARENTITY_HPP

#include "Body.hpp"
#include "Mob.hpp"

class StarEntity : public Body, public Mob
{
public:
	StarEntity();
	StarEntity(const Body &body, const Vec2 position, const Vec2 velocity);

private:
};

#endif
