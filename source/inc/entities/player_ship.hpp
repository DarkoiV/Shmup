#pragma once
#include "Gng2D/components/circle_colider.hpp"
#include "Gng2D/components/layer.hpp"
#include "Gng2D/components/position.hpp"
#include "Gng2D/components/sprite.hpp"
#include "Gng2D/components/velocity.hpp"
#include "Gng2D/types/game_object.hpp"
#include "components/basic_weapon.hpp"
#include "components/hit_points.hpp"
#include "flight_scene_layers.hpp"

struct PlayerShip : Gng2D::GameObject
{
    using Gng2D::GameObject::GameObject;
    struct Collider : public Gng2D::CircleCollider {};

    // SPRITE SHEET DESCRIPTION
    static constexpr unsigned horizontalFrames = 3;
    static constexpr unsigned verticalFrames   = 1;

    enum class Frame : unsigned
    {
        Forward,
        Right,
        Left
    };

    static void divideSprite(Gng2D::Sprite& s)
    {
        s.srcRect.w /= horizontalFrames;
        s.srcRect.h /= verticalFrames;
    }

    static void setFrame(Frame f, Gng2D::Sprite& s)
    {
        int horizontalFrame = static_cast<int>(f) % horizontalFrames;
        int verticalFrame   = static_cast<int>(f) / horizontalFrames;
        s.srcRect.x = horizontalFrame * s.srcRect.w;
        s.srcRect.y = verticalFrame * s.srcRect.h;
    }

    void onCreate()
    {
        addComponent<Gng2D::Position>(320.0f, 200.0f);
        addComponent<Gng2D::Velocity>(0.0f, 0.0f);
        addComponent<Gng2D::Layer>(FlightSceneLayer::Ships);

        auto& sprite = addComponent<Gng2D::Sprite>("player_ship", 1);
        divideSprite(sprite);
        setFrame(Frame::Forward, sprite);

        addComponent<Collider>(6.0f);
        addComponent<HitPoints>(5u, 5u);
        addComponent<BasicWeapon>();
    }
};

