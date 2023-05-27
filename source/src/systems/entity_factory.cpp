#include "systems/entity_factory.hpp"
#include "Gng2D/components/layer.hpp"
#include "Gng2D/components/velocity.hpp"
#include "Gng2D/types/entity_builder.hpp"
#include "components/colliders.hpp"
#include "components/enemy_basic_weapon.hpp"
#include "components/hit_points.hpp"
#include "flight_scene_layers.hpp"
#include "sprite_sheets.hpp"

EntityFactory::EntityFactory(entt::registry& r)
    : reg(r)
{
}

void EntityFactory::spawnSparrow(Gng2D::Position pos, Gng2D::Velocity vel)
{
    auto sparrow = Gng2D::EntityBuilder(reg)
        .with<Gng2D::Position>(pos)
        .with<Gng2D::Velocity>(vel)
        .with<Gng2D::Layer>(FlightSceneLayer::Ships)
        .with<EnemyCollider>(5.0f)
        .with<HitPoints>(3u, 3u)
        .with<EnemyBasicWeapon>(75u)
        .get();

        auto& sprite = reg.emplace<Gng2D::Sprite>(sparrow, "sparrow", 1);
        EnemySpriteSheet::divideSprite(sprite);
        EnemySpriteSheet::setHFrame(EnemySpriteSheet::HFrame::Forward, sprite);
}

void EntityFactory::spawnEnemyBullet(Gng2D::Position pos, Gng2D::Velocity vel)
{
    Gng2D::EntityBuilder(reg)
        .with<Gng2D::Position>(pos)
        .with<Gng2D::Velocity>(vel)
        .with<Gng2D::Sprite>("enemy_bullet")
        .with<EnemyBulletCollider>(4.0f)
        .with<Gng2D::Layer>(FlightSceneLayer::Bullets);
}

