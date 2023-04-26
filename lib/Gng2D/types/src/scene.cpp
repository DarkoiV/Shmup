#include <SDL2/SDL.h>
#include "Gng2D/core/scene_registry.hpp"
#include "Gng2D/core/window.hpp"
#include "Gng2D/types/scene.hpp"

void Gng2D::Scene::operator()()
{
    if (pause) return;

    runCoroutines();
    update();
}

bool Gng2D::Scene::isPaused() const
{
    return pause;
}

Gng2D::GameObject Gng2D::Scene::getGameObject(entt::entity id)
{
    return GameObject(*this, id);
}

bool Gng2D::Scene::entityExists(entt::entity id) const
{
    return registry.valid(id);
}

void Gng2D::Scene::destroyEntity(entt::entity id)
{
    registry.destroy(id);
}

bool Gng2D::Scene::isKeyPressed(SDL_Scancode scancode) const
{
    const Uint8* keyboardState = SDL_GetKeyboardState(NULL);
    return keyboardState[scancode];
}

void Gng2D::Scene::runCoroutines()
{
    for (auto& coro : coroutines) coro();
    std::erase_if(coroutines, [](Coroutine& coro) 
    {
        return coro.isCompleted(); 
    });
}

