#include "systems/enemy_bullet_spawner.hpp"
#include "Gng2D/components/position.hpp"
#include "components/enemy_basic_weapon.hpp"
#include "entities/bullet.hpp"

void EnemyBulletSpawner::operator()()
{
    for (const auto& [e, bw] : scene.view<EnemyBasicWeapon>())
    {
        if (bw.remainigCooldown == 0)
        {
            auto enemyObject = scene.getEntity(e);
            const auto enemyPos = enemyObject.getComponent<Gng2D::Position>();
            const auto enemyVel = enemyObject.getComponent<Gng2D::Velocity>();
            const auto bulletPos  = Gng2D::Position{enemyPos + Gng2D::Position{0, 15.0f}};
            const auto bulletVelo = Gng2D::Velocity{enemyVel + Gng2D::Velocity{0, 1.0f}};
            scene.spawnObject<EnemyBullet>(bulletPos, bulletVelo);
            bw.remainigCooldown = bw.cooldownTicks;
        }
        else --bw.remainigCooldown;
    }
}

