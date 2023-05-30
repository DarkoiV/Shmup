#include "systems/enemy_weapons.hpp"
#include "components/enemy_basic_weapon.hpp"
#include "components/enemy_targeting_turret.hpp"
#include "components/colliders.hpp"
#include "Gng2D/components/layer.hpp"
#include "Gng2D/components/sprite.hpp"
#include "Gng2D/components/roation.hpp"
#include "Gng2D/types/scene.hpp"
#include "Gng2D/types/entity_builder.hpp"
#include "flight_scene_layers.hpp"

using namespace entt::literals;

EnemyWeapons::EnemyWeapons(entt::registry& r)
    : reg(r)
{
}

void EnemyWeapons::operator()()
{
    basicWeapons();
    targetingTurret();
}

void EnemyWeapons::basicWeapons()
{
    for (auto&& [enemy, weapon] : reg.view<EnemyBasicWeapon>().each())
    {
        if (weapon.remainigCooldown == 0)
        {
            const auto pos = reg.get<Gng2D::Position>(enemy);
            const auto vel = reg.get<Gng2D::Velocity>(enemy);
            const auto offset       = 10 * Gng2D::V2d::normalize(vel);
            const auto bulletPos    = Gng2D::Position{pos + offset};
            const auto bulletVel    = Gng2D::Velocity{4 * Gng2D::V2d::normalize(vel)};
            spawnBullet(bulletPos, bulletVel);
            weapon.remainigCooldown = weapon.cooldownTicks;
        }
        else --weapon.remainigCooldown;
    }
}

void EnemyWeapons::targetingTurret()
{
    auto player = reg.ctx()
        .get<Gng2D::Scene&>()
        .getEntity("Player");
    auto playerPos = reg.get<Gng2D::Position>(player);

    for (auto&& [enemy, weapon, rotation] : reg.view<EnemyTargetingTurret, Gng2D::Rotation>().each())
    {
        if (weapon.remainingRotationCooldown == 0)
        {
            const auto pos              = reg.get<Gng2D::Position>(enemy);
            const auto targetingVector  = playerPos - pos;
            auto& turretAngle           = reg.get<Gng2D::Rotation>(enemy).angle;
            const auto turretVector     = Gng2D::V2d::rot(turretAngle, 1);
            const auto angleDiff        = std::trunc(Gng2D::V2d::angle(targetingVector, turretVector));
            if (angleDiff > 4.0f)   turretAngle -= 5.0f;
            if (angleDiff < -4.0f)  turretAngle += 5.0f;
            weapon.remainingRotationCooldown = weapon.rotationCooldown;
        }
        else -- weapon.remainingRotationCooldown;

        if (weapon.remainigCooldown == 0)
        {
            const auto pos = reg.get<Gng2D::Position>(enemy);
            const auto offset       = Gng2D::V2d::rot(rotation.angle, 10);
            const auto bulletPos    = Gng2D::Position{pos + offset};
            const auto bulletVel    = Gng2D::Velocity{Gng2D::V2d::rot(rotation.angle, 4)};
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

