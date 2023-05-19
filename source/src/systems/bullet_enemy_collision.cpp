#include "systems/bullet_enemy_collision.hpp"
#include "components/enemy_animation.hpp"
#include "components/destroyed_by_player.hpp"
#include "entities/red_x.hpp"

void BulletEnemyCollision::onOverlap(Gng2D::GameObject bullet, Gng2D::GameObject enemy)
{
    scene.destroyEntity(bullet.getId());
    auto& enemyHP = enemy.getComponent<HitPoints>().value;
    enemyHP--;

    if (enemyHP == 0) 
    {
        enemy.addComponent<DestroyedByPlayer>();
        scene.destroyEntity(enemy.getId());
    }
    else enemy.addOrReplaceComponent<EnemyAnimation>(enemy, EnemyAnimation::Type::flash);
}

