#include "systems/flight_scene_gui.hpp"

using Gng2D::Coroutine;
using Gng2D::gui::Text;
using Gng2D::gui::Icon;

static Coroutine pulse(Text& t)
{
    while (true)
    {
        for (int i = 0; i <= 25; ++i)
        {
            t.setOpacity(255 - (i * 7));
            co_yield Coroutine::WaitTicks{2};
        }
        co_yield Coroutine::WaitTicks{15};
        for (int i = 25; i >= 0; --i)
        {
            t.setOpacity(255 - (i * 7));
            co_yield Coroutine::WaitTicks{2};
        }
        co_yield Coroutine::WaitTicks{15};
    }
}

FlightSceneGui::FlightSceneGui(Gng2D::Scene& s)
    : scene(s)
{
    textAnimation = Coroutine(pulse, focus);
    focus.setOriginPoint(5, 5);
    hitPointsFull.setOpacity(240);
    hitPointsEmpty.setOpacity(240);
}

void FlightSceneGui::setHP(unsigned HP, unsigned maxHP)
{
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
    textAnimation();
    focus.render(r);
}

