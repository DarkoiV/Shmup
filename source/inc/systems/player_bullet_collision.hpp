#pragma once
#include "Gng2D/systems/overlap_system.hpp"
#include "player_ship.hpp"
#include "bullet.hpp"

struct PlayerBulletCollision : Gng2D::OverlapSystem<PlayerShip::Collider, EnemyBullet::Collider>
{
    PlayerBulletCollision(Gng2D::Scene& s)
        : OverlapSystem(s)
    {}

    void onOverlap(entt::entity, entt::entity) override;
};
