#pragma once

#include "Gng2D/systems/overlap_system.hpp"
#include "entities/player_ship.hpp"
#include "components/enemy_ship_collider.hpp"

struct PlayerEnemyCollision : Gng2D::OverlapSystem<PlayerShip::Collider, EnemyShipCollider>
{
    PlayerEnemyCollision(Gng2D::Scene& s)
        : OverlapSystem(s)
    {}

    void onOverlap(entt::entity, entt::entity) override;
};

