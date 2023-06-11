#pragma once
#include <entt/entt.hpp>
#include "Gng2D/scene/scene.hpp"
#include "Gng2D/types/menu_handle.hpp"

struct MainMenuScene : Gng2D::Scene
{
    MainMenuScene();

    void onEnter()              override;
    void onExit()               override;
    void update()               override;
    void render(SDL_Renderer*)  override;

    void onKeyDown(SDL_KeyboardEvent&) override;

private:
    Gng2D::MenuHandle menuHandle;
};

