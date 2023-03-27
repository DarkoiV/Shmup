#pragma once
#include "Gng2D/systems/overlap_system.hpp"
#include "Gng2D/types/coroutine.hpp"
#include "entities/sparrow.hpp"
#include "entities/bullet.hpp"

struct BulletEnemyCollision : Gng2D::OverlapSystem<AllyBullet::Collider, EnemyShipCollider>
{
    BulletEnemyCollision(Gng2D::Scene& s)
        : OverlapSystem(s)
    {}

    void onOverlap(entt::entity, entt::entity) override;
    static Gng2D::Coroutine flashShip(Gng2D::GameObject);
};

