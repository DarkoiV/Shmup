#pragma once
#include "Gng2D/systems/overlap_system.hpp"
#include "player_ship.hpp"
#include "bullet.hpp"

struct PlayerBulletCollisionSystem : Gng2D::OverlapSystem<PlayerShip::Collider, Bullet::Collider>
{
    PlayerBulletCollisionSystem(entt::registry& r)
        : OverlapSystem(r)
    {}

    void onOverlap(entt::entity, entt::entity) override;
};
