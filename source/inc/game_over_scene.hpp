#pragma once
#include "Gng2D/gui/text.hpp"
#include "Gng2D/types/scene.hpp"
#include "Gng2D/types/coroutine.hpp"

struct GameOverScene : Gng2D::Scene
{
    void onEnter()              override;
    void onExit()               override;
    bool isCompleted()          override;
    void update()               override;
    void render(SDL_Renderer*)  override;

private:
    Gng2D::gui::Text gameOverText{"charmap-oldschool_white", "GAME OVER"};
};
