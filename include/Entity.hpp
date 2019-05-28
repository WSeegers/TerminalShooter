#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <Vec2.hpp>

class Entity
{
public:
    Entity();
    Entity(const Vec2 &position);
    Entity(double x, double y);
    Entity(const Entity &other);

    Entity &operator=(const Entity other);

    void setPosition(const Vec2 &position);
    void setPosition(double x, double y);
    Vec2 &getPosition();

protected:
    Vec2 _position;
};

#endif