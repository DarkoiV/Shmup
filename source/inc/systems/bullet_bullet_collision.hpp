#pragma once
#include "Gng2D/systems/overlap_system.hpp"
#include "entities/player_ship.hpp"
#include "entities/bullet.hpp"

struct BulletBulletCollision : Gng2D::OverlapSystem<AllyBullet::Collider, EnemyBullet::Collider>
{
    BulletBulletCollision(Gng2D::Scene& s)
        : OverlapSystem(s)
    {}

    void onOverlap(Gng2D::GameObject, Gng2D::GameObject) override;
};

