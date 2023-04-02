#include "systems/flight_scene_gui.hpp"
#include "Gng2D/gui/text_animations.hpp"

using Gng2D::gui::pulse;
using Gng2D::gui::fadeIn;
using Gng2D::gui::Icon;
using Gng2D::gui::Element;

FlightSceneGui::FlightSceneGui(Gng2D::Scene& s, const PlayerControlls& pc, PlayerShip ps)
    : scene(s)
    , playerControlls(pc)
    , playerShip(ps)
{
    focus.setOriginPoint(5, 5);
    focus.addAnimation(pulse);

    pause.setScale(2);
    pause.setPosition(Element::Align::Center);
    pause.addAnimation(pulse);

    hitPointsFull.setOpacity(240);
    hitPointsEmpty.setOpacity(240);
}

void FlightSceneGui::operator()()
{
    if (popUpTextTicksRemaining > 0) popUpTextTicksRemaining--;
    inFocusMode = playerControlls.inFocusMode();
}

void FlightSceneGui::render(SDL_Renderer* r)
{
    renderHitPoints(r);
    if (inFocusMode) renderFocusMode(r);

    if (scene.isPaused()) renderPauseText(r);
    else renderPopUpText(r);
}

void FlightSceneGui::addPopUpText(const std::string& str, unsigned ticks)
{
    popUpTextTicksRemaining = ticks;
    popUpText.changeString(str);
    popUpText.addAnimation(fadeIn);
    popUpText.setScale(3);
    popUpText.setPosition(Element::Align::Center);
}

void FlightSceneGui::renderHitPoints(SDL_Renderer* r)
{
    const auto& [HP, maxHP] = playerShip.getComponent<HitPoints>();

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

void FlightSceneGui::renderPopUpText(SDL_Renderer* r)
{
    if (popUpTextTicksRemaining == 0) return;

    popUpText.render(r);
}

