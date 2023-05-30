#pragma once
#include <entt/entt.hpp>
#include "Gng2D/components/position.hpp"
#include "Gng2D/components/velocity.hpp"
#include "Gng2D/types/entity_builder.hpp"
#include "components/pickup.hpp"

struct EntityFactory
{
    EntityFactory(entt::registry&);

    Gng2D::EntityBuilder spawnSparrow(Gng2D::Position, float rotation = 90);
    Gng2D::EntityBuilder spawnEnemyBullet(Gng2D::Position, Gng2D::Velocity);
    Gng2D::EntityBuilder spawnPickup(Gng2D::Position, Pickup::Type);
    Gng2D::EntityBuilder spawnDrone(entt::entity parent, Gng2D::RelativePosition);
    Gng2D::EntityBuilder spawnTurret(entt::entity parent, Gng2D::RelativePosition);

private:
    entt::registry& reg;
};

