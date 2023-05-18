#include <SDL2/SDL.h>
#include "Gng2D/core/scene_registry.hpp"
#include "Gng2D/core/window.hpp"
#include "Gng2D/types/scene.hpp"

using Gng2D::Scene;
using Gng2D::GameObject;

void Scene::operator()()
{
    if (pause) return;

    runCoroutines();
    update();
}

bool Scene::isPaused() const
{
    return pause;
}

std::optional<GameObject> Scene::getGameObject(const std::string& name)
{
    if (namedEntities.contains(name))
        return GameObject(*this, namedEntities[name]);
    else
        return std::nullopt;
}

GameObject Scene::getGameObject(entt::entity id)
{
    return GameObject(*this, id);
}

bool Scene::entityExists(entt::entity id) const
{
    return registry.valid(id);
}

void Scene::destroyEntity(entt::entity id)
{
    if (registry.all_of<CallDestroy>(id))
    {
        auto& onDestroy = registry.get<CallDestroy>(id);
        onDestroy(*this, id);
    }
    if (registry.all_of<GameObject::NameTag>(id))
    {
        auto& tag = registry.get<GameObject::NameTag>(id);
        namedEntities.erase(tag.name);
    }
    registry.destroy(id);
}

bool Scene::isKeyPressed(SDL_Scancode scancode) const
{
    const Uint8* keyboardState = SDL_GetKeyboardState(NULL);
    return keyboardState[scancode];
}

void Scene::runCoroutines()
{
    for (auto& coro : coroutines) coro();
    std::erase_if(coroutines, [](Coroutine& coro) 
    {
        return coro.isCompleted(); 
    });
}

