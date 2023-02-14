#pragma once
#include "Gng2D/types/game_object.hpp"
#include "Gng2D/components/circle_colider.hpp"
#include "Gng2D/components/velocity.hpp"
#include "Gng2D/components/position.hpp"
#include "Gng2D/components/sprite.hpp"
#include "components/stats.hpp"

struct PlayerShip : Gng2D::GameObject
{
    struct Collider : public Gng2D::CircleCollider {};

    PlayerShip(Gng2D::Scene& s)
        : Gng2D::GameObject(s)
    {
        addComponent<Gng2D::Position>(320.0f, 200.0f);
        addComponent<Gng2D::Velocity>(0.0f, 0.0f);
        addComponent<Gng2D::Sprite>("player_ship");
        addComponent<Collider>(5.0f);
        addComponent<Stats>(100);
    }
};

