#include "Gng2D/core/scene_controller.hpp"

Gng2D::SceneController::SceneController(Scene& s)
    : scene(s)
{
}

void Gng2D::SceneController::operator()()
{
    for (auto& coro : coroutines) coro();
    std::erase_if(coroutines, [](Coroutine& coro) 
    {
        return coro.isCompleted(); 
    });
}

