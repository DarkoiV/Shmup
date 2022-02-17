#pragma once

#include "core/scene.hpp"

class TestScene : public Scene
{
    bool eventHandler(SDL_Event &event) override;

public:
    TestScene(SceneManager& sm): 
        Scene(sm) {};

    void update() override;
    bool completed() override;
};
