#include "systems/enemy_weapons.hpp"
#include "components/enemy_weapon_types.hpp"
#include "components/colliders.hpp"
#include "Gng2D/components/layer.hpp"
#include "Gng2D/components/sprite.hpp"
#include "Gng2D/components/roation.hpp"
#include "Gng2D/scene/scene.hpp"
#include "Gng2D/types/entity_compositor.hpp"
#include "flight_scene_layers.hpp"

using namespace entt::literals;

EnemyWeapons::EnemyWeapons(entt::registry& r)
    : reg(r)
{
}

void EnemyWeapons::operator()()
{
    targeting();
    vulcan();
}

void EnemyWeapons::vulcan()
{
    for (auto&& [enemy, weapon, rotation] : reg.view<EnemyVulcan, Gng2D::Rotation>().each())
    {
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

void EnemyWeapons::targeting()
{
    auto player = reg.ctx()
        .get<Gng2D::Scene&>()
        .getEntity("Player");
    auto playerPos = reg.get<Gng2D::Position>(player);

    for (auto&& [enemy, weapon, rotation] : reg.view<EnemyTargeting, Gng2D::Rotation>().each())
    {
        if (weapon.remainingRotationCooldown == 0)
        {
            const auto pos              = reg.get<Gng2D::Position>(enemy);
            const auto targetingVector  = playerPos - pos;
            auto& turretAngle           = reg.get<Gng2D::Rotation>(enemy).angle;
            const auto turretVector     = Gng2D::V2d::rot(turretAngle, 1);
            const auto angleDiff        = Gng2D::V2d::angle(targetingVector, turretVector);
            if (angleDiff > 3.0f)   turretAngle -= 5.0f;
            if (angleDiff < -3.0f)  turretAngle += 5.0f;
            weapon.remainingRotationCooldown = weapon.rotationCooldown;
        }
        else -- weapon.remainingRotationCooldown;
    }
}

void EnemyWeapons::spawnBullet(Gng2D::Position pos, Gng2D::Velocity vel)
{
    Gng2D::EntityCompositor(reg)
        .with<Gng2D::Sprite>("enemy_bullet")
        .with<Gng2D::Position>(pos)
        .with<Gng2D::Velocity>(vel)
        .with<EnemyBulletCollider>(4.0f)
        .with<Gng2D::Layer>(FlightSceneLayer::Bullets);
}

