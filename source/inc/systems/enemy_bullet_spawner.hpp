#pragma once
#include <entt/entt.hpp>
#include "Gng2D/components/position.hpp"
#include "Gng2D/components/velocity.hpp"

struct EnemyBulletSpawner
{
    EnemyBulletSpawner(entt::registry&);

    void operator()();

private:
    entt::registry& reg;

    void spawnBullet(Gng2D::Position, Gng2D::Velocity);
};

