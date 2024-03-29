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
    void laser();

    void            spawnBullet(Gng2D::Position, Gng2D::Velocity);
    entt::entity    spawnLaser(entt::entity parent, float distanceFromParent);
    entt::entity    spawnLaserChargeMarker(entt::entity parent, float distanceFromParent);
};

