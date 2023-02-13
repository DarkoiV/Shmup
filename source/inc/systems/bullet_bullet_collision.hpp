#pragma once
#include "Gng2D/systems/overlap_system.hpp"
#include "player_ship.hpp"
#include "bullet.hpp"

struct BulletBulletCollision : Gng2D::OverlapSystem<AllyBullet::Collider, EnemyBullet::Collider>
{
    BulletBulletCollision(Gng2D::Scene& s)
        : OverlapSystem(s)
    {}

    void onOverlap(entt::entity, entt::entity) override;
};

