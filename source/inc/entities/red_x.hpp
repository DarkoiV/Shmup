#pragma once
#include "Gng2D/types/game_object.hpp"
#include "Gng2D/components/layer.hpp"
#include "Gng2D/components/position.hpp"
#include "Gng2D/components/sprite.hpp"
#include "components/timed_existence.hpp"
#include "flight_scene_layers.hpp"

struct RedX : Gng2D::GameObject 
{
    using Gng2D::GameObject::GameObject;
    void onCreate(Gng2D::Position p)
    {
        addComponent<Gng2D::Position>(p);
        addComponent<Gng2D::Layer>(FlightSceneLayer::BackgroundEffects);
        addComponent<Gng2D::Sprite>("red_x").opacity = 135;
        addComponent<TimedExistence>(35u);
    }
};

