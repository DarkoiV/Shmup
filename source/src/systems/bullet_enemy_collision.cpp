#include "systems/bullet_enemy_collision.hpp"
#include "components/enemy_animation.hpp"
#include "entities/red_x.hpp"

void BulletEnemyCollision::onOverlap(entt::entity bullet, entt::entity enemy)
{
    scene.destroyEntity(bullet);
    auto enemyObject = scene.getGameObject(enemy);

    auto& enemyHP = enemyObject.getComponent<HitPoints>().value;
    enemyHP--;

    if (enemyHP == 0) 
    {
        auto pos = enemyObject.getComponent<Gng2D::Position>();
        scene.spawnObject<RedX>(pos);
        scene.destroyEntity(enemy);
    }
    else enemyObject.addOrReplaceComponent<EnemyAnimation>(enemyObject, EnemyAnimation::Type::flash);
}

