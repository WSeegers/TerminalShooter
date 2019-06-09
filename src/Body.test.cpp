#include "Body.hpp"

#include <iostream>

static bool testCollision()
{
    Body b1("xxxx", 2, 2);
    Body b2("xxxx", 2, 2);

    if (b1.isColliding(b2) != true)
        return false;

    b2.setPosition(1, 1);

    if (b1.isColliding(b2) != true)
        return false;
    if (b2.isColliding(b1) != true)
        return false;

    b1.setPosition(2, 2);

    if (b1.isColliding(b2) != true)
        return false;
    if (b2.isColliding(b1) != true)
        return false;

    b2.setPosition(3, 1);
    
    if (b1.isColliding(b2) != true)
        return false;
    if (b2.isColliding(b1) != true)
        return false;

    b2.setPosition(1, 3);
    
    if (b1.isColliding(b2) != true)
        return false;
    if (b2.isColliding(b1) != true)
        return false;

    b2.setPosition(4, 2);

    if (b1.isColliding(b2) == true)
        return false;
    if (b2.isColliding(b1) == true)
        return false;

    Body b3("xxxx", 2, 2);
    Body b4("  xx", 2, 2);

    b4.setPosition(0, 1);

    if (b4.isColliding(b3) == true)
        return false;
    if (b3.isColliding(b4) == true)
        return false;

    Body b5("xxxx", 2, 2);
    Body b6(" x x", 2, 2);

    b6.setPosition(1, 0);

    if (b6.isColliding(b5) == true)
        return false;
    if (b5.isColliding(b6) == true)
        return false;

    Body b7("xxxx", 2, 2);
    Body b8(" xxx", 2, 2);

    b7.setPosition(1, 1);
    b8.setPosition(2, 2);

    if (b8.isColliding(b7) == true)
        return false;
    if (b7.isColliding(b8) == true)
        return false;

    Body b9("xxxx", 2, 2);
    Body b10("x xx", 2, 2);

    b9.setPosition(1, 1);
    b10.setPosition(0, 2);

    if (b10.isColliding(b9) == true)
        return false;
    if (b9.isColliding(b10) == true)
        return false;

    Body b11("xxxx", 2, 2);
    Body b12("xxx ", 2, 2);

    b11.setPosition(1, 1);
    b12.setPosition(0, 0);

    if (b12.isColliding(b11) == true)
        return false;
    if (b11.isColliding(b12) == true)
        return false;

    return true;
}

bool Body::test()
{
    if (!testCollision())
    {
        std::cout << "Body Collision Test Failed!" << std::endl;
        return false;
    }
    return true;
}

/*


ƸƷ


*/