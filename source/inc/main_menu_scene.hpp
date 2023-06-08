#pragma once
#include <entt/entt.hpp>
#include "Gng2D/types/scene.hpp"
#include "Gng2D/systems/entity_renderer.hpp"
#include "Gng2D/systems/gui_system.hpp"
#include "Gng2D/systems/position_system.hpp"

struct MainMenuScene : Gng2D::Scene
{
    void onEnter()              override;
    void onExit()               override;
    bool isCompleted()          override;
    void update()               override;
    void render(SDL_Renderer*)  override;

private:
    entt::entity menu;
    Gng2D::GuiSystem        gui{reg};
    Gng2D::EntityRenderer   entityRenderer{reg};
    Gng2D::PositionSystem   positionSystem{reg};
};

