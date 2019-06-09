#ifndef VEC2I_HPP
#define VEC2I_HPP

class Vec2
{
public:
    Vec2();
    Vec2(double x, double y);
    Vec2(const Vec2 &other);

    Vec2 &operator=(const Vec2 &other);
    Vec2 operator+(const Vec2 &other) const;
    Vec2 operator-(const Vec2 &v) const;
    Vec2 &operator+=(const Vec2 &);
    Vec2 &operator-=(const Vec2 &);

    double getDist();
    Vec2 getNormalized();

    double x;
    double y;
};

#endif