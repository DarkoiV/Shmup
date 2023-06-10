#pragma once
#include <entt/entt.hpp>
#include "Gng2D/scene/scene.hpp"

struct MainMenuScene : Gng2D::Scene
{
    void onEnter()              override;
    void onExit()               override;
    void update()               override;
    void render(SDL_Renderer*)  override;

    void onKeyDown(SDL_KeyboardEvent&) override;

private:
    entt::entity menu;
};

