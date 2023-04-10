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
#include "sprite_sheets.hpp"

struct PlayerShip : Gng2D::GameObject
{
    using Gng2D::GameObject::GameObject;
    struct Collider : public Gng2D::CircleCollider {};

    void onCreate()
    {
        addComponent<Gng2D::Position>(320.0f, 200.0f);
        addComponent<Gng2D::Velocity>(0.0f, 0.0f);
        addComponent<Gng2D::Layer>(FlightSceneLayer::Ships);

        auto& sprite = addComponent<Gng2D::Sprite>("player_ship", 1);
        PlayerSpriteSheet::divideSprite(sprite);
        PlayerSpriteSheet::setHFrame(PlayerSpriteSheet::HFrame::Forward, sprite);

        addComponent<Collider>(6.0f);
        addComponent<HitPoints>(5u, 5u);
        addComponent<BasicWeapon>();
    }
};

