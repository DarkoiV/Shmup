#pragma once
#include "Gng2D/types/scene.hpp"
#include "Gng2D/gui/text.hpp"
#include "Gng2D/gui/icon.hpp"
#include "entities/player_ship.hpp"

struct FlightSceneGui
{
    FlightSceneGui(Gng2D::Scene& s, PlayerShip ps);

    void operator()();

    void setHP(unsigned HP, unsigned maxHP);
    void renderHitPoints(SDL_Renderer*);
    void renderFocusMode(SDL_Renderer*);
    void renderPauseText(SDL_Renderer*);
private:
    Gng2D::Scene&       scene;
    PlayerShip          playerShip;
    Gng2D::gui::Text    focus{"charmap-oldschool_white", "FOCUS"};
    Gng2D::gui::Text    pause{"charmap-oldschool_white", "PAUSE"};
    Gng2D::gui::Icon    hitPointsFull{"hitpoints", SDL_Rect{0, 0, 24, 20}};
    Gng2D::gui::Icon    hitPointsEmpty{"hitpoints", SDL_Rect{24, 0, 24, 20}};

    unsigned HP{5};
    unsigned maxHP{5};
};

