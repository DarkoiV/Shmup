#include "systems/entity_factory.hpp"
#include "Gng2D/components/layer.hpp"
#include "Gng2D/components/roation.hpp"
#include "Gng2D/components/velocity.hpp"
#include "Gng2D/components/relationship.hpp"
#include "Gng2D/types/entity_compositor.hpp"
#include "components/colliders.hpp"
#include "components/enemy_weapon_types.hpp"
#include "components/basic_weapon.hpp"
#include "components/hit_points.hpp"
#include "flight_scene_layers.hpp"
#include "sprite_sheets.hpp"
#include "animations.hpp"

EntityFactory::EntityFactory(entt::registry& r)
    : reg(r)
{
}

Gng2D::EntityCompositor EntityFactory::spawnSparrow(Gng2D::Position pos, float rotation)
{
    return Gng2D::EntityCompositor(reg)
        .with<Gng2D::Position>(pos)
        .with<Gng2D::Velocity>(Gng2D::V2d::rot(rotation, 2.0f))
        .with<Gng2D::Layer>(FlightSceneLayer::Ships)
        .with<EnemyCollider>(6.0f)
        .with<HitPoints>(3u, 3u)
        .with<EnemyVulcan>(75u)
        .with<Gng2D::Rotation>(rotation)
        .with<Gng2D::Sprite>("sparrow")
        .modify<Gng2D::Sprite>([](auto& sprite)
        {
            EnemySpriteSheet::divideSprite(sprite);
            EnemySpriteSheet::setHFrame(EnemySpriteSheet::HFrame::Forward, sprite);
        });
}

Gng2D::EntityCompositor EntityFactory::spawnLaserSparrow(Gng2D::Position pos, float rotation)
{
    return Gng2D::EntityCompositor(reg)
        .with<Gng2D::Position>(pos)
        .with<Gng2D::Velocity>(Gng2D::V2d::rot(rotation, 2.0f))
        .with<Gng2D::Layer>(FlightSceneLayer::Ships)
        .with<EnemyCollider>(6.0f)
        .with<HitPoints>(3u, 3u)
        .with<EnemyLaser>(100u, 20u)
        .with<Gng2D::Rotation>(rotation)
        .with<Gng2D::Sprite>("sparrow")
        .modify<Gng2D::Sprite>([](auto& sprite)
        {
            EnemySpriteSheet::divideSprite(sprite);
            EnemySpriteSheet::setHFrame(EnemySpriteSheet::HFrame::Forward, sprite);
        });
}

Gng2D::EntityCompositor EntityFactory::spawnTurretBoat(Gng2D::Position pos, float rotation)
{
    auto builder = Gng2D::EntityCompositor(reg)
        .with<Gng2D::Position>(pos)
        .with<Gng2D::Velocity>(Gng2D::V2d::rot(rotation, 1.5f))
        .with<Gng2D::Rotation>(rotation)
        .with<Gng2D::Layer>(FlightSceneLayer::Ships)
        .with<Gng2D::Sprite>("turret_boat")
        .with<EnemyCollider>(6.0f)
        .with<HitPoints>(3u, 3u)
        .modify<Gng2D::Sprite>([](auto& sprite)
        {
            EnemySpriteSheet::divideSprite(sprite);
            EnemySpriteSheet::setHFrame(EnemySpriteSheet::HFrame::Forward, sprite);
        });

    spawnTurret(builder.get(), Gng2D::RelativePosition{Gng2D::V2d::rot(rotation, -3.0f)});

    return builder;
}

Gng2D::EntityCompositor EntityFactory::spawnEnemyBullet(Gng2D::Position pos, Gng2D::Velocity vel)
{
    return Gng2D::EntityCompositor(reg)
        .with<Gng2D::Position>(pos)
        .with<Gng2D::Velocity>(vel)
        .with<Gng2D::Sprite>("enemy_bullet")
        .with<EnemyBulletCollider>(4.0f)
        .with<Gng2D::Layer>(FlightSceneLayer::Bullets);
}

Gng2D::EntityCompositor EntityFactory::spawnPickup(Gng2D::Position pos, Pickup::Type type)
{
    return Gng2D::EntityCompositor(reg)
        .with<Gng2D::Position>(pos)
        .with<Gng2D::Velocity>(0.0f, 2.5f)
        .with<Gng2D::Sprite>("pickup")
        .modify<Gng2D::Sprite>([](auto& sprite, auto& reg, auto pickup)
        {
            sprite.srcRect.w /= 4;
            emplaceAnimation(rotatePickup, reg, pickup);
        })
        .with<Gng2D::Layer>(FlightSceneLayer::PickUps)
        .with<PickupCollider>(7.0f)
        .with<Pickup>(type);
}

Gng2D::EntityCompositor EntityFactory::spawnDrone(entt::entity parent, Gng2D::RelativePosition rpos)
{
    return Gng2D::EntityCompositor(reg)
        .with<Gng2D::Parent>(parent)
        .with<Gng2D::RelativePosition>(rpos)
        .with<BasicWeapon>()
        .with<Gng2D::Sprite>("drone");
}

Gng2D::EntityCompositor EntityFactory::spawnTurret(entt::entity parent, Gng2D::RelativePosition rpos)
{
    return Gng2D::EntityCompositor(reg)
        .withParent(parent)
        .with<Gng2D::RelativePosition>(rpos)
        .with<Gng2D::Sprite>("turret")
        .with<Gng2D::Rotation>(90.0)
        .with<EnemyTargeting>(8u)
        .with<EnemyVulcan>(125u);
}


