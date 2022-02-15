#pragma once

#include "core/scene.hpp"

class TestScene : public Scene
{
    bool eventHandler(SDL_Event &event) override;

public:
    TestScene(EventManager& em)
        : Scene(em) {};

    void update() override;
    bool completed() override;
    static auto factory(EventManager& em) -> Scene*;
};
