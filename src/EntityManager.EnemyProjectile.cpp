#include "EntityManager.hpp"
#include "GameEngine.hpp"
#include "EnemyEntity.hpp"

void EntityManager::initEnemyProjectilePool(void)
{
    for (int i = 0; i < EntityManager::PLAYER_PROJECTILE_MAX; i++)
    {
        this->_enemyProjectilesPool[i] = new Projectile(
            Vec2(),
            Vec2(0, 0.3),
            Body(std::string("V"), 1, 1));
        this->_enemyProjectilesPool[i]->kill();
    }
}

void EntityManager::drawEnemyProjectiles()
{
    Projectile *enemyProjectile;

    for (int i = 0; i < EntityManager::PLAYER_PROJECTILE_MAX; i++)
    {
        enemyProjectile = this->_enemyProjectilesPool[i];
        if (this->_enemyProjectilesPool[i]->isAlive())
            this->_drawBody(*enemyProjectile);
    }
}

void EntityManager::updateEnemyProjectiles()
{
    int i;
    Projectile *enemyProjectile;

    for (i = 0; i < EntityManager::PLAYER_PROJECTILE_MAX; i++)
    {
        enemyProjectile = this->_enemyProjectilesPool[i];
        if (enemyProjectile->isAlive())
        {
            this->_removeBody(*enemyProjectile);
            enemyProjectile->update();
            if (enemyProjectile->getPosition().y >= GameEngine::FIELD_HEIGHT)
                enemyProjectile->kill();
        }
    }
}

void EntityManager::createEnemyShot(EnemyEntity &enemy)
{
    Projectile *projectile;

    for (int i = 0; i < EntityManager::PLAYER_PROJECTILE_MAX; i++)
    {
        projectile = this->_enemyProjectilesPool[i];
        if (!projectile->isAlive())
        {
            projectile->revive();
            projectile->setPosition(enemy.getPosition());
            break;
        }
    }
}

void EntityManager::createEnemyShot(const Vec2 &pos)
{
    Projectile *projectile;

    for (int i = 0; i < EntityManager::PLAYER_PROJECTILE_MAX; i++)
    {
        projectile = this->_enemyProjectilesPool[i];
        if (!projectile->isAlive())
        {
            projectile->revive();
            projectile->setPosition(pos);
            break;
        }
    }
}