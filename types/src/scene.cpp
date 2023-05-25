#include <SDL2/SDL.h>
#include "Gng2D/components/name_tag.hpp"
#include "Gng2D/core/scene_registry.hpp"
#include "Gng2D/core/window.hpp"
#include "Gng2D/types/scene.hpp"

using Gng2D::Scene;

Scene::Scene()
{
    enttRegistry
        .on_construct<Gng2D::NameTag>()
        .connect<&Scene::addNamedEntity>(this);
    enttRegistry
        .on_destroy<Gng2D::NameTag>()
        .connect<&Scene::removeNamedEntity>(this);
}

Scene::~Scene()
{
    enttRegistry
        .on_construct<Gng2D::NameTag>()
        .disconnect<&Scene::addNamedEntity>(this);
    enttRegistry
        .on_destroy<Gng2D::NameTag>()
        .disconnect<&Scene::removeNamedEntity>(this);
}

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

bool Scene::isKeyPressed(SDL_Scancode scancode) const
{
    const Uint8* keyboardState = SDL_GetKeyboardState(NULL);
    return keyboardState[scancode];
}

Gng2D::EntityBuilder Scene::newEntity()
{
    return EntityBuilder(enttRegistry);
}

entt::entity Scene::getEntity(const std::string& name)
{
    [[unlikely]]
    if (not namedEntities.contains(name))
    {
        Gng2D::LOG::INFO("No entity with name: \"", name, "\"");
        return entt::null;
    }
    return namedEntities[name];
}

void Scene::runCoroutines()
{
    for (auto& coro : coroutines) coro();
    std::erase_if(coroutines, [](Coroutine& coro) 
    {
        return coro.isCompleted(); 
    });
}

void Scene::addNamedEntity(entt::registry& reg, entt::entity entity)
{
    auto& name = reg.get<NameTag>(entity).value;

    [[unlikely]]
    if (namedEntities.contains(name))
    {
        Gng2D::LOG::ERROR("Entity with name: \"", name, "\" alread registered");
        reg.get<NameTag>(entity).value = "";
    }
    else
        namedEntities.emplace(name, entity);
}

void Scene::removeNamedEntity(entt::registry& reg, entt::entity entity)
{
    auto& name = reg.get<NameTag>(entity).value;
    namedEntities.erase(name);
}

