#include "systems/bullet_enemy_collision.hpp"

void BulletEnemyCollision::onOverlap(entt::entity bullet, entt::entity enemy)
{
    scene.destroyEntity(bullet);
    auto enemyObject = scene.getEntity(enemy);

    auto& enemyHP = enemyObject.getComponent<HitPoints>().value;
    enemyHP--;

    if (enemyHP == 0) scene.destroyEntity(enemy);
}

