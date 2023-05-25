#pragma once
#include <entt/entt.hpp>
#include "Gng2D/components/position.hpp"
#include "Gng2D/components/velocity.hpp"
#include "Gng2D/types/scene.hpp"

struct EntityFactory
{
    EntityFactory(Gng2D::Scene&, entt::registry&);

    void spawnSparrow(Gng2D::Position, Gng2D::Velocity = {0.0f, 2.0f});
    void spawnEnemyBullet(Gng2D::Position, Gng2D::Velocity);

private:
    entt::registry& reg;
    Gng2D::Scene&   scene;
};

