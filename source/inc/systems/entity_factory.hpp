#pragma once
#include <entt/entt.hpp>
#include "Gng2D/components/position.hpp"
#include "Gng2D/components/velocity.hpp"
#include "Gng2D/types/entity_builder.hpp"

struct EntityFactory
{
    EntityFactory(entt::registry&);

    Gng2D::EntityBuilder spawnSparrow(Gng2D::Position, float rotation = 90);
    Gng2D::EntityBuilder spawnEnemyBullet(Gng2D::Position, Gng2D::Velocity);

private:
    entt::registry& reg;
};

