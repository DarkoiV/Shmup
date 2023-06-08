#pragma once
#include <entt/entt.hpp>
#include "Gng2D/scene/scene.hpp"

struct MainMenuScene : Gng2D::Scene
{
    void onEnter()              override;
    void onExit()               override;
    bool isCompleted()          override;
    void update()               override;
    void render(SDL_Renderer*)  override;

private:
    entt::entity menu;
};

