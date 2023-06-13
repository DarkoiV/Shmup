#pragma once
#include <entt/entt.hpp>
#include "Gng2D/components/position.hpp"
#include "Gng2D/components/velocity.hpp"

struct EnemyWeapons
{
    EnemyWeapons(entt::registry&);

    void operator()();

private:
    entt::registry& reg;

    void targeting();
    void vulcan();

    void spawnBullet(Gng2D::Position, Gng2D::Velocity);
    void spawnLaser(entt::entity parent, Gng2D::RelativePosition);
};

