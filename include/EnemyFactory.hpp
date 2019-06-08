#ifndef ENEMYFACTORY_HPP
#define ENEMYFACTORY_HPP

#include "EnemyEntity.hpp"
#include "Vec2.hpp"
#include "Body.hpp"

class EnemyFactory
{
public:
    EnemyFactory();
    ~EnemyFactory();

    enum EnemyTypes
    {
        BASIC
    };

    static EnemyEntity *createEnemy(EnemyFactory::EnemyTypes type, const Vec2 position);

private:
};

#endif
