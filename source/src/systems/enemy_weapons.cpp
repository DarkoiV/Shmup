#include "systems/enemy_weapons.hpp"
#include "components/enemy_basic_weapon.hpp"
#include "components/colliders.hpp"
#include "Gng2D/components/layer.hpp"
#include "Gng2D/components/sprite.hpp"
#include "Gng2D/types/entity_builder.hpp"
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
            const auto offset       = 10 * Gng2D::V2d::normalize(vel);
            const auto bulletPos    = Gng2D::Position{pos + offset};
            const auto bulletVel    = Gng2D::Velocity{vel + vel};
            spawnBullet(bulletPos, bulletVel);
            weapon.remainigCooldown = weapon.cooldownTicks;
        }
        else --weapon.remainigCooldown;
    }
}

void EnemyWeapons::spawnBullet(Gng2D::Position pos, Gng2D::Velocity vel)
{
    Gng2D::EntityBuilder(reg)
        .with<Gng2D::Sprite>("enemy_bullet")
        .with<Gng2D::Position>(pos)
        .with<Gng2D::Velocity>(vel)
        .with<EnemyBulletCollider>(4.0f)
        .with<Gng2D::Layer>(FlightSceneLayer::Bullets);
}

