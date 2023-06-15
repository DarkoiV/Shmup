#include "systems/enemy_weapons.hpp"
#include "components/enemy_weapon_types.hpp"
#include "components/colliders.hpp"
#include "Gng2D/components/layer.hpp"
#include "Gng2D/components/sprite.hpp"
#include "Gng2D/components/roation.hpp"
#include "Gng2D/scene/scene.hpp"
#include "Gng2D/types/entity_compositor.hpp"
#include "animations.hpp"
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
    laser();
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

void EnemyWeapons::laser()
{
    for (auto&& [enemy, weapon] : reg.view<EnemyLaser>().each())
    {
        if (weapon.phase == EnemyLaser::charging)
        {
            if (weapon.remainigPhaseTicks == (weapon.cooldownTicks / 3)) 
            {
                weapon.chargeMarker = spawnLaserChargeMarker(enemy, 14.0f);
            }

            if (weapon.remainigPhaseTicks == 0)
            {
                weapon.laser                = spawnLaser(enemy, 14.0f);
                weapon.phase                = EnemyLaser::shooting;
                weapon.remainigPhaseTicks   = weapon.shootingDuration;
                reg.destroy(weapon.chargeMarker);
            }
            else --weapon.remainigPhaseTicks;
        }
        else if (weapon.phase == EnemyLaser::shooting)
        {
            if (weapon.remainigPhaseTicks == 0)
            {
                reg.destroy(weapon.laser);
                weapon.phase                = EnemyLaser::charging;
                weapon.remainigPhaseTicks   = weapon.cooldownTicks;
            }
            else --weapon.remainigPhaseTicks;
        }
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

entt::entity EnemyWeapons::spawnLaser(entt::entity parent, float distanceFromParent)
{
    double angle = 0.0;
    if (auto* rotation = reg.try_get<Gng2D::Rotation>(parent))
    {
        angle = rotation->angle;
    }

    constexpr float LASER_LEN = 1200.0f;
    constexpr float SPRITE_WIDTH = 320.0f;
    constexpr float X_STRECH_FACTOR = LASER_LEN / SPRITE_WIDTH;

    return Gng2D::EntityCompositor(reg)
        .with<Gng2D::Sprite>("enemy_laser")
        .with<Gng2D::SpriteStretch>(X_STRECH_FACTOR, 1.0f)
        .with<Gng2D::Rotation>(angle)
        .modify<Gng2D::Sprite>([](auto& sprite, auto& reg, auto e)
        {
            sprite.srcRect.h /= 4;
            emplaceAnimation(laserShoot, reg, e);
        })
        .withParent(parent)
        .with<Gng2D::RelativePosition>(Gng2D::V2d::rot(angle, distanceFromParent + (LASER_LEN/2)))
        .with<EnemyLaserCollider>(5.0f, LASER_LEN).get();
}

entt::entity EnemyWeapons::spawnLaserChargeMarker(entt::entity parent, float distanceFromParent)
{
    double angle = 0.0;
    if (auto* rotation = reg.try_get<Gng2D::Rotation>(parent))
    {
        angle = rotation->angle;
    }

    auto marker = Gng2D::EntityCompositor(reg)
        .with<Gng2D::Sprite>("enemy_charge_marker")
        .with<Gng2D::SpriteStretch>(1.0f, 1.0f)
        .with<Gng2D::Rotation>(0.0)
        .withParent(parent)
        .with<Gng2D::RelativePosition>(Gng2D::V2d::rot(angle, distanceFromParent + 5.0f))
        .get();

    emplaceAnimation(rotateChargeMarker, reg, marker);

    return marker;
}

