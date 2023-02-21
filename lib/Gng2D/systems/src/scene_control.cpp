#include "Gng2D/systems/scene_control.hpp"

Gng2D::SceneControl::SceneControl(Scene& s, CoroHandle h)
    : scene(s)
    , handle(h)
{
}

Gng2D::SceneControl::~SceneControl()
{
    if (handle) handle.destroy();
}

void Gng2D::SceneControl::operator()()
{
    if (completed) return;
    if (waitTicks > 0)
    {
        waitTicks--;
        return;
    }

    handle.resume();
    auto result = handle.promise().returnValue;
    if (std::holds_alternative<WaitTicks>(result)) 
    {
        waitTicks = std::get<WaitTicks>(result);
    }
    if (std::holds_alternative<Promise::Completed>(result)) 
    {
        completed = true;
        handle.destroy();
        handle = nullptr;
    }
}

