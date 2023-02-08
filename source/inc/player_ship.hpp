#pragma once
#include "Gng2D/components/game_object.hpp"
#include "Gng2D/components/circle_colider.hpp"

struct PlayerCollider : Gng2D::CircleCollider
{
};

struct PlayerShip : Gng2D::GameObject
{
    PlayerShip(entt::registry&);
};

