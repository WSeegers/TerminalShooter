#include <Vec2.hpp>

Vec2::Vec2(): x(0), y(0){}
Vec2::Vec2(double x, double y): x(x), y(y){}
Vec2::Vec2(const Vec2 &other): x(other.x), y(other.y){}

Vec2 &Vec2::operator=(const Vec2 &other)
{
    if (this != &other)
    {
        this->x = other.x;
        this->y = other.y;
    }
}

Vec2 Vec2::operator+(const Vec2 &other) const
{
    return Vec2(this->x + other.x, this->y + other.y);
}

Vec2 Vec2::operator-(const Vec2 &other) const
{
    return Vec2(this->x - other.x, this->y - other.y);
}

Vec2 &Vec2::operator+=(const Vec2 &other)
{
    this->x += other.x;
    this->y += other.y;
    return *this;
}

Vec2 &Vec2::operator-=(const Vec2 &other)
{
    this->x -= other.x;
    this->y -= other.y;
    return *this;
}