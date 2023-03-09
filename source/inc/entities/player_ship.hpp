#pragma once
#include "Gng2D/types/game_object.hpp"
#include "Gng2D/components/circle_colider.hpp"
#include "Gng2D/components/velocity.hpp"
#include "Gng2D/components/position.hpp"
#include "Gng2D/components/sprite.hpp"
#include "components/hit_points.hpp"

struct PlayerShip : Gng2D::GameObject
{
    using Gng2D::GameObject::GameObject;
    struct Collider : public Gng2D::CircleCollider {};

    void onCreate()
    {
        addComponent<Gng2D::Position>(320.0f, 200.0f);
        addComponent<Gng2D::Velocity>(0.0f, 0.0f);

        // There are 3 animation states forward/right/left
        auto& srcRect = addComponent<Gng2D::Sprite>("player_ship", 1).srcRect;
        srcRect.w /= 3;

        addComponent<Collider>(6.0f);
        addComponent<HitPoints>(5u);
    }
};

