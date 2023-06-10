#pragma once
#include "Gng2D/scene/scene.hpp"

struct GameOverScene : Gng2D::Scene
{
    void onEnter()              override;
    void onExit()               override;
    void update()               override;
    void render(SDL_Renderer*)  override;
};

