#include "systems/flight_scene_gui.hpp"
#include "Gng2D/gui/text_animations.hpp"

using Gng2D::gui::pulse;
using Gng2D::gui::Icon;
using Gng2D::gui::Element;

FlightSceneGui::FlightSceneGui(Gng2D::Scene& s, PlayerShip ps)
    : scene(s)
    , playerShip(ps)
{
    focus.setOriginPoint(5, 5);
    focus.addAnimation(pulse);

    pause.setScale(2);
    pause.setPosition(Element::Align::Center, 0, 0);
    pause.addAnimation(pulse);

    hitPointsFull.setOpacity(240);
    hitPointsEmpty.setOpacity(240);
}

void FlightSceneGui::operator()()
{
    const auto& [HP, maxHP] = playerShip.getComponent<HitPoints>();
    this->HP    = HP;
    this->maxHP = maxHP;
}

void FlightSceneGui::renderHitPoints(SDL_Renderer* r)
{
    constexpr int HP_BAR_WIDTH = 15;
    for (unsigned i = 0; i < HP; i++)
    {
        hitPointsFull.setPosition(Icon::Align::TopRight, 
                                  -5 - (HP_BAR_WIDTH * i),
                                  5);
        hitPointsFull.render(r);
    }
    for (unsigned i = HP; i < maxHP; i++)
    {
        hitPointsEmpty.setPosition(Icon::Align::TopRight, 
                                  -5 - (HP_BAR_WIDTH * i),
                                  5);
        hitPointsEmpty.render(r);
    }
}

void FlightSceneGui::renderFocusMode(SDL_Renderer* r)
{
    focus.render(r);
}

void FlightSceneGui::renderPauseText(SDL_Renderer* r)
{
    pause.render(r);
}

