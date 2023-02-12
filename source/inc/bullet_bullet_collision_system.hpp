#pragma once
#include "Gng2D/systems/overlap_system.hpp"
#include "player_ship.hpp"
#include "bullet.hpp"

struct BulletBulletCollisionSystem : Gng2D::OverlapSystem<AllyBullet::Collider, EnemyBullet::Collider>
{
    BulletBulletCollisionSystem(entt::registry& r)
        : OverlapSystem(r)
    {}

    void onOverlap(entt::entity, entt::entity) override;
};

