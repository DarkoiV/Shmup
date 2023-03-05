#pragma once
#include "Gng2D/types/game_object.hpp"
#include "Gng2D/components/position.hpp"
#include "Gng2D/components/sprite.hpp"
#include "Gng2D/components/velocity.hpp"
#include "Gng2D/components/circle_colider.hpp"

struct AllyBullet : public Gng2D::GameObject
{
    using Gng2D::GameObject::GameObject;
    struct Collider : public Gng2D::CircleCollider {};

    void onCreate(Gng2D::Position p, Gng2D::Velocity v)
    {
        addComponent<Gng2D::Position>(p);
        addComponent<Gng2D::Velocity>(v);
        addComponent<Gng2D::Sprite>("ally_bullet");
        addComponent<Collider>(4.0f);
    }
};

struct EnemyBullet : public Gng2D::GameObject
{
    using Gng2D::GameObject::GameObject;
    struct Collider : public Gng2D::CircleCollider {};

    void onCreate(Gng2D::Position p, Gng2D::Velocity v)
    {
        addComponent<Gng2D::Position>(p);
        addComponent<Gng2D::Velocity>(v);
        addComponent<Gng2D::Sprite>("enemy_bullet");
        addComponent<Collider>(4.0f);
    }
};
