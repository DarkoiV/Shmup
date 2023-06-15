#pragma once
#include <entt/entt.hpp>
#include "Gng2D/components/position.hpp"
#include "Gng2D/components/velocity.hpp"
#include "Gng2D/types/entity_compositor.hpp"
#include "components/pickup.hpp"

struct EntityFactory
{
    EntityFactory(entt::registry&);

    Gng2D::EntityCompositor spawnSparrow(Gng2D::Position, float rotation = 90);
    Gng2D::EntityCompositor spawnLaserSparrow(Gng2D::Position, float rotation = 90);
    Gng2D::EntityCompositor spawnTurretBoat(Gng2D::Position, float rotation = 90);
    Gng2D::EntityCompositor spawnEnemyBullet(Gng2D::Position, Gng2D::Velocity);
    Gng2D::EntityCompositor spawnPickup(Gng2D::Position, Pickup::Type);
    Gng2D::EntityCompositor spawnDrone(entt::entity parent, Gng2D::RelativePosition);
    Gng2D::EntityCompositor spawnTurret(entt::entity parent, Gng2D::RelativePosition);

private:
    entt::registry&         reg;

};

