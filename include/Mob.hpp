#ifndef MOB_HPP
#define MOB_HPP

#include <Entity.hpp>

class Mob : virtual public Entity
{
public:
    Mob(Vec2 &position);
    Mob(const Mob &other);

    Mob &operator=(const Mob other);

    void setVelocity(const Vec2 &position);
    void setVelocity(double x, double y);
    Vec2 &getVelocity();

protected:
    Vec2 _velocity;
};

#endif