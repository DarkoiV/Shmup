#pragma once
#include <entt/entt.hpp>
#include "Gng2D/components/position.hpp"
#include "Gng2D/components/velocity.hpp"

struct EntityFactory
{
    EntityFactory(entt::registry&);

    void spawnSparrow(Gng2D::Position, Gng2D::Velocity = {0.0f, 2.0f});

private:
    entt::registry& reg;
};

