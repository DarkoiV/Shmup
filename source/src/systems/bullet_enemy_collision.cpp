#include "systems/bullet_enemy_collision.hpp"
#include "components/enemy_animation.hpp"
#include "components/destroyed_by_player.hpp"
#include "entities/red_x.hpp"

void BulletEnemyCollision::onOverlap(entt::entity bullet, entt::entity enemy)
{
    scene.destroyEntity(bullet);
    auto enemyObject = scene.getGameObject(enemy);

    auto& enemyHP = enemyObject.getComponent<HitPoints>().value;
    enemyHP--;

    if (enemyHP == 0) 
    {
        enemyObject.addComponent<DestroyedByPlayer>();
        scene.destroyEntity(enemy);
    }
    else enemyObject.addOrReplaceComponent<EnemyAnimation>(enemyObject, EnemyAnimation::Type::flash);
}

