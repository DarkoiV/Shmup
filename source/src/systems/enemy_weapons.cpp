#include "systems/enemy_weapons.hpp"
#include "components/enemy_basic_weapon.hpp"
#include "components/colliders.hpp"
#include "Gng2D/components/sprite.hpp"
#include "Gng2D/components/layer.hpp"
#include "flight_scene_layers.hpp"

EnemyWeapons::EnemyWeapons(entt::registry& r)
    : reg(r)
{
}

void EnemyWeapons::operator()()
{
    for (auto&& [enemy, weapon] : reg.view<EnemyBasicWeapon>().each())
    {
        if (weapon.remainigCooldown == 0)
        {
            const auto pos = reg.get<Gng2D::Position>(enemy);
            const auto vel = reg.get<Gng2D::Velocity>(enemy);
            const auto bulletPos = Gng2D::Position{pos + Gng2D::Position{0, 15.0f}};
            const auto bulletVel = Gng2D::Velocity{vel + Gng2D::Velocity{0, 1.0f}};
            spawnBullet(bulletPos, bulletVel);
            weapon.remainigCooldown = weapon.cooldownTicks;
        }
        else --weapon.remainigCooldown;
    }
}

void EnemyWeapons::spawnBullet(Gng2D::Position pos, Gng2D::Velocity vel)
{
    auto bullet = reg.create();
    reg.emplace<Gng2D::Sprite>(bullet, "enemy_bullet");
    reg.emplace<Gng2D::Position>(bullet, pos);
    reg.emplace<Gng2D::Velocity>(bullet, vel);
    reg.emplace<EnemyBulletCollider>(bullet, 4.0f);
    reg.emplace<Gng2D::Layer>(bullet, FlightSceneLayer::Bullets);
}

