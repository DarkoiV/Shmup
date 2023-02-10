#pragma once
#include "Gng2D/components/game_object.hpp"
#include "Gng2D/components/position.hpp"
#include "Gng2D/components/velocity.hpp"
#include "Gng2D/components/circle_colider.hpp"

struct Bullet : public Gng2D::GameObject
{
    struct Collider : public Gng2D::CircleCollider {};

    Bullet(entt::registry& r)
        : Gng2D::GameObject(r)
    {
        addComponent<Gng2D::Position>(320.0f, 0.0f);
        addComponent<Gng2D::Velocity>(0.0f, 2.0f);
        addComponent<Collider>(3.0f);
    }

};
