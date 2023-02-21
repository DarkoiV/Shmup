#include "Gng2D/systems/scene_control.hpp"

Gng2D::SceneControl::SceneControl(CoroHandle h)
    : handle(h)
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
    auto status = handle.promise().status;
    if (std::holds_alternative<WaitTicks>(status)) 
    {
        waitTicks = std::get<WaitTicks>(status);
    }
    if (std::holds_alternative<Completed>(status)) 
    {
        completed = true;
        handle.destroy();
        handle = nullptr;
    }
}

