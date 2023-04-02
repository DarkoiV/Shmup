#pragma once
#include <map>
#include "Gng2D/types/scene.hpp"
#include "Gng2D/gui/text.hpp"
#include "Gng2D/gui/icon.hpp"
#include "systems/player_controlls.hpp"
#include "entities/player_ship.hpp"

struct FlightSceneGui
{
    FlightSceneGui(Gng2D::Scene& s, const PlayerControlls&, PlayerShip ps);

    void operator()();
    void render(SDL_Renderer*);
    void addPopUpText(const std::string&, unsigned ticks = 160);

private:
    void renderHitPoints(SDL_Renderer*);
    void renderFocusMode(SDL_Renderer*);
    void renderPauseText(SDL_Renderer*);
    void renderPopUpText(SDL_Renderer*);

    Gng2D::Scene&           scene;
    const PlayerControlls&  playerControlls;
    PlayerShip              playerShip;
    bool                    inFocusMode;

    Gng2D::gui::Text    focus{"charmap-oldschool_white", "FOCUS"};
    Gng2D::gui::Text    pause{"charmap-oldschool_white", "PAUSE"};
    Gng2D::gui::Icon    hitPointsFull{"hitpoints", SDL_Rect{0, 0, 24, 20}};
    Gng2D::gui::Icon    hitPointsEmpty{"hitpoints", SDL_Rect{24, 0, 24, 20}};

    Gng2D::gui::Text    popUpText{"charmap-oldschool_white", ""};
    unsigned            popUpTextTicksRemaining{0};
};

