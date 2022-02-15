#pragma once

#include "core/scene.hpp"

class TestScene : public Scene
{
    bool eventHandler(SDL_Event &event) override;

public:
    TestScene(EventManager& em, SceneManager& sm): 
        Scene(em, sm) {};

    void update() override;
    bool completed() override;
    static auto factory(EventManager& em, SceneManager& sm) -> Scene*;
};
