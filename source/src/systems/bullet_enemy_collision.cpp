#include "systems/bullet_enemy_collision.hpp"

void BulletEnemyCollision::onOverlap(entt::entity bullet, entt::entity enemy)
{
    scene.destroyEntity(bullet);
    auto enemyObject = scene.getEntity(enemy);

    auto& enemyHP = enemyObject.getComponent<HitPoints>().value;
    enemyHP--;

    if (enemyHP == 0) scene.destroyEntity(enemy);
    else scene.addCoroutine(flashShip, enemyObject);
}

Gng2D::Coroutine BulletEnemyCollision::flashShip(Gng2D::GameObject enemyObject)
{
    {
        auto& srcRect = enemyObject.getComponent<Gng2D::Sprite>().srcRect;
        srcRect.y = srcRect.h;
    }
    co_yield Gng2D::Coroutine::WaitTicks{7};
    {
        auto& srcRect = enemyObject.getComponent<Gng2D::Sprite>().srcRect;
        srcRect.y = 0;
    }
}

